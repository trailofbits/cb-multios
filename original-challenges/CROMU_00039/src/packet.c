/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "vars.h"
#include "packet.h"

/* packet format

   COMMON HEADER
   uint8_t version
   uint8_t len (total packet length not counting version and len bytes)
   uint8_t packet_type
   uint8_t request_id

   READ packet_type header
   uint8_t name_len
   char name[name_len]
  
   WRITE packet_type header 
   uint8_t name_len
   char name[]
   uint8_t type
   uint8_t value_len
   unsigned char value[value_len]

   RESPONSE packet_type header
   unsigned char value[value_len] 

   ERROR packet_type header
   uint8_t error_code
*/

int32_t ReceivePacket(unsigned char *pkt) {
	uint32_t total_bytes;
	size_t rx_bytes;
	uint8_t pkt_len;
	int retval;

	// receive the first two bytes 
	total_bytes = 0;
	while (total_bytes != 2) {
		if ((retval = receive(0, pkt+total_bytes, 2-total_bytes, &rx_bytes)) < 0) {
			// receive failure
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		total_bytes += rx_bytes;
	}

	// check the version
	if (pkt[0] != 0) {
		return(0);
	}

	// check the length
	if (pkt[1] < 4) {
		return(0);
	}
	if (pkt[1] > 254) {
		return(0);
	}
	pkt_len = pkt[1]+2;

	// read in the rest of the packet as determined by the provided length
	while (total_bytes != pkt_len) {
		if (receive(0, pkt+total_bytes, pkt_len-total_bytes, &rx_bytes) < 0) {
			// receive failure
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		total_bytes += rx_bytes;
	}

	return(total_bytes);
}

int SendError(uint8_t request_id, uint8_t error) {
	unsigned char pkt[256];

	// build the header
	pkt[0] = 0;           // version
	pkt[1] = 3;           // len
	pkt[2] = ERROR;       // type
	pkt[3] = request_id;  

	pkt[4] = error;

	if (write(pkt, 5) != 5) {
		return(0);
	}

	return(1);
}

int SendResponse(uint8_t request_id, vars_t *pm) {
	unsigned char pkt[256];

	// build the header
	pkt[0] = 0;           // version
	pkt[2] = RESPONSE;    // type
	pkt[3] = request_id;  

	if (pm->type == STRING) {
		if (strlen((char *)pm->value) > 252) {
			return(SendError(request_id, ERROR_BADLEN));
		}
		strcpy((char *)pkt+4, (char *)pm->value);
		// pkt length
		pkt[1] = 2+strlen((char *)pm->value);
	} else if (pm->type == INT32) {
		memcpy(pkt+4, pm->value, 4);
		// pkt length
		pkt[1] = 6;
	} else {
		return(SendError(request_id, ERROR_NOTFOUND));
	}

	if (write(pkt, pkt[1]+2) != pkt[1]+2) {
		return(0);
	}

	return(1);
}

int HandleReadRequest(unsigned char *pkt, uint8_t pkt_len) {
	char name[MAX_NAME_LEN];
	uint8_t name_len;
	vars_t *pm;
	uint8_t request_id;
	
	if (!pkt) {
		return(0);
	}

	request_id = pkt[3];

	// copy the name string out of the packet
	bzero(name, MAX_NAME_LEN);
	name_len = pkt[4];
	// name_len should equal the remaining bytes in the packet
	// since only the name var is left in a READ request
	if (name_len != pkt_len-COMMON_HDR_LEN-1) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
#ifdef PATCHED
	if (name_len > MAX_NAME_LEN-1) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
#endif
	strncpy(name, (char *)pkt+5, name_len);

	// find the requested name
	if ((pm = SearchVARS(name)) == NULL) {
		SendError(request_id, ERROR_NOTFOUND);
		return(0);	
	}	
	
	SendResponse(request_id, pm);

	return(1);
}

int HandleWriteRequest(unsigned char *pkt, uint8_t pkt_len) {
	char name[MAX_NAME_LEN];
	char value[MAX_VALUE_LEN];
	vars_t *pm;
	uint8_t request_id;
	uint8_t name_len;
	uint8_t value_len;
	uint8_t curr_len;

	if (!pkt) {
		return(0);
	}

	request_id = pkt[3];
	curr_len = 4;

	// copy the name string out of the packet	
	bzero(name, MAX_NAME_LEN);
	name_len = pkt[4];
	curr_len++;
	// the name field should leave at least 3 bytes at the end
	// of the WRITE packet for the type, value_len, and value fields
	if (name_len > pkt_len-COMMON_HDR_LEN-1-3) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
	if (name_len > MAX_NAME_LEN-1) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
	memcpy(name, pkt+5, name_len);
	curr_len += name_len;

	// copy the type
	uint8_t type;
	type = pkt[COMMON_HDR_LEN+1+name_len];
	curr_len++;

	// copy the value
	bzero(value, MAX_VALUE_LEN);
	value_len = pkt[COMMON_HDR_LEN+1+name_len+1];
	curr_len++;
	// the value field can't be larger than the 
	// remaining available bytes in the packet
	if (value_len > pkt_len-curr_len) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
	if (value_len > MAX_NAME_LEN-1) {
		SendError(request_id, ERROR_BADLEN);
		return(0);
	}
	memcpy(value, pkt+5+name_len+2, value_len);

	if ((pm = UpdateVARSObject(name, type, value)) == NULL) {
		SendError(request_id, ERROR_WRITEFAILED);
	} else {
		SendResponse(request_id, pm);
	}

	return(1);
}

int HandlePacket(unsigned char *pkt) {
	uint8_t pkt_len;
	uint8_t pkt_type;
	uint8_t request_id;
	char name[MAX_NAME_LEN];
	uint8_t name_len;
	char value[MAX_VALUE_LEN];

	if (!pkt) {
		return(0);
	}

	// get common header items
	pkt_len    = pkt[1]+2;
	if (pkt_len < 4) {
		return(0);
	}
	pkt_type   = pkt[2];
	request_id = pkt[3];
	
	switch(pkt_type) {
		case READ_REQUEST:
			// handle the request
			HandleReadRequest(pkt, pkt_len);

			break;

		case WRITE_REQUEST:
			// handle the request
			HandleWriteRequest(pkt, pkt_len);

			break;

		default:
			// send unknown type error
			SendError(request_id, ERROR_UNKNOWN);

			break;
	}

	return(1);
}	
