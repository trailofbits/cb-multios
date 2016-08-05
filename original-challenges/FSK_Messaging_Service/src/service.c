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
#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <prng.h>

#include "common.h"
#include "rx.h"
#include "baseband.h"
#include "packet.h"

#define BYTE_RECEIVE_MAX	(SAMPLE_FS*4)	// 4 seconds

void init_prng( void )
{
	uint32_t randomData[8];
	size_t random_bytes_populated;

	if ( random( (void*)randomData, sizeof(uint32_t)*8, &random_bytes_populated ) != 0 )
	{
		printf( "[[ERROR RANDOM FAILED]]\n" );
		_terminate(1);
	}

	seed_prng_array( randomData, 8 );
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) 
{
	void *secret_page = (void *)secret_page_i;

	tBasebandState oBaseband;

	uint32_t ts = ((uint32_t*)secret_page)[0] + ((uint32_t*)secret_page)[1] + ((uint32_t*)secret_page)[2] + ((uint32_t*)secret_page)[3];
	ts &= 0x7FFFF;

	ts += 1452975630;

	printf( "[[RECEIVER STARTED -- TIMESTAMP: $d]]\n", ts );

	// Initialize random number generator
	init_prng();

	// Initialize baseband
	init_baseband( &oBaseband );

	// Initialize packet handler
	init_packet_handler( );

	// Begin receiing packets
	for ( uint32_t byteCount = 0; byteCount < BYTE_RECEIVE_MAX; )
	{
		uint8_t rx_sample[256];
		size_t rx_count;

        	if ( receive( STDIN, rx_sample, 256, &rx_count) != 0) 
		{
			// Failed ??
			printf( "[[CONNECTION CLOSED EARLY]]\n" );
            		_terminate(1);
        	}

		if ( rx_count < 1 )
		{
			// Failed ??
			printf( "[[RECEIVE ERROR]]\n" );
            		_terminate(1);
		}

		for ( uint32_t i = 0; i < rx_count; i++ )
		{
			if ( byteCount >= BYTE_RECEIVE_MAX )
				break;

			uint8_t sample_result = receive_sample( rx_sample[i] );

			process_sample( &oBaseband, sample_result );

			byteCount++;
		}
	}

	// Display any received packets
	display_packets();

	// Destroy the packet handler
	destroy_packet_handler();

	return 0;
}
