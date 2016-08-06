/*

Author: Jason Williams

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
#include <libcgc.h>
#include <stdlib.h>
#include <stdint.h>
}

#include "comms.h"

uint32_t CommReadBytes( uint8_t *pDest, uint32_t readLen )
{
	if ( !pDest )
		return (0);

	uint32_t readRemaining = readLen;
	uint32_t destPos = 0;

	while ( readRemaining > 0 )
	{
		size_t readBytes;

		if ( receive( STDIN, pDest+destPos, readRemaining, &readBytes ) != 0 )
			_terminate( -1 );	// Read error

		if ( readBytes == 0 )
			_terminate( -1 );	// Read error

		destPos += readBytes;
		readRemaining -= readBytes;
	}

	// Return amount read
	return (destPos);	
}

uint32_t CommSendBytes( uint8_t *pData, uint32_t sendLen )
{
	if ( !pData )
		return (0);

	uint32_t sendRemaining = sendLen;
	uint32_t fromPos = 0;

	while ( sendRemaining > 0 )
	{
		size_t sentBytes;

		if ( transmit( STDOUT, pData+fromPos, sendRemaining, &sentBytes ) != 0 )
			_terminate( -1 );	// Send error

		if ( sentBytes == 0 )
			_terminate( -1 );

		fromPos += sentBytes;
		sendRemaining -= sentBytes;
	}

	return (fromPos);
}
