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
extern "C"
{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include "common.h"

uint32_t ReadBytes( uint8_t *pDest, uint32_t numBytes )
{
	if ( !pDest )
		return (0);

	size_t bytes_read = 0;
	for ( bytes_read = 0; bytes_read < numBytes; )
	{
		size_t num_bytes_read;
		size_t bytes_remaining = (numBytes - bytes_read);

		if ( receive( STDIN, (void *)(pDest+bytes_read), bytes_remaining, &num_bytes_read ) != 0 )
			_terminate( -1 );

		if ( num_bytes_read == 0 )
			_terminate( -1 );

		bytes_read += num_bytes_read;
	}

	return (bytes_read);
}
