/*
Copyright (c) 2014 Cromulence LLC

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

#include "bitstream.h"

void freeStream( pBitStream *stream )
{
	pBitStream t;

	if ( stream == NULL ) {
		return;
	}

	t = *stream;

	if (t == NULL ) {
		return;
	}

	/// Ensure the stream pointer is valid before attempting to free it.
	if ( t->stream ) {
		free(t->stream);
	}

	/// Free the meta structure
	free( t );

	/// Set the meta structure to NULL
	*stream = NULL;

	return;
}

pBitStream initStream( char *newData, unsigned int newDataLength )
{
	pBitStream pbs = NULL;

	if ( newData == NULL ) {
		return pbs;
	}

	if ( newDataLength == 0 ) {
		return pbs;
	}

	pbs = malloc( sizeof(BitStream) );

	if ( pbs == NULL ) {
		return pbs;
	}

	memset( pbs, 0, sizeof( BitStream ) );

	pbs->stream = malloc( newDataLength );

	if ( pbs->stream == NULL ) {
		free(pbs);
		pbs = NULL;
		return pbs;
	}

	pbs->streamLength = newDataLength;

	memcpy( pbs->stream, newData, newDataLength );

	return pbs;		
}

int readBits( pBitStream stream, unsigned int bitCount, unsigned int *outBits )
{
	int outIndex = 0;
	int retval = 0;
	char tempChar;
	unsigned int outval = 0;

	if ( stream == NULL || outBits == NULL || bitCount == 0 ) {
		return retval;
	}

	if ( stream->stream == NULL ) {
		return retval;
	}

	if ( bitCount > 32 ) {
		return retval;
	}

	/// Calculate the end index after the read
	outIndex = stream->byteIndex * 8;
	outIndex += stream->bitIndex + bitCount;

	/// Ensure that the read does not go beyond the buffer
	if ( stream->streamLength * 8 < outIndex ) {
		return retval;
	}

	/// Copy the number of bits
	while ( bitCount ) {
		/// Pull out the current byte
		tempChar = stream->stream[ stream->byteIndex ];

		/// This pulls out the current bit.
		tempChar = (tempChar >> ( 7 - stream->bitIndex)) & 0x1;		

		/// Shift over for the new bit
		outval <<= 1;

		/// OR it in
		outval |= tempChar;

		stream->bitIndex = (stream->bitIndex + 1) % 8;

		/// If the bit counters % 8 equals 0 then the next byte must now be used
		if ( stream->bitIndex == 0 ) {
			stream->byteIndex++;
		}

		bitCount--;
		retval++;
	}

	/// Set the outbits
	*outBits = outval;

	return retval;
}
