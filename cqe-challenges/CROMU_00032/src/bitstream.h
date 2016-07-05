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

#ifndef __BITSTREAM__
#define __BITSTREAM__

#include <libcgc.h>
#include <stdlib.h>
#include <malloc.h>

/**
 * Structure to manage a bit stream
 **/
typedef struct BitStream {
	/// Pointer to the stream managed by this structure
	char *stream;

	/// Total length of the stream in bytes
	unsigned int streamLength;

	/// Current byte being read from in the stream index. This should
	///	never be greater than streamLength
	unsigned int byteIndex;

	/// Current bit index within the current byte to be read. This will
	///	never be greater than 7
	unsigned int bitIndex;
} BitStream, *pBitStream;

/**
 * Read the specified number of bits into the buffer pointed to by outBits
 * @param stream Pointer to a stream structure from which the data is read.
 * @param bitCount Number of bits to read from the stream.
 * @param outBits Pointer to the buffer that will receive the data. The calling function
 *		is expected to provide a sufficiently large buffer.
 * @return Returns the number of bits read on success or 0 on failure.
 **/
int readBits( pBitStream stream, unsigned int bitCount, unsigned int *outBits );

/**
 * Initializes a new BitStream structure with the specified buffer and length.
 * The function requires a buffer/length pair since it allocates a new buffer that it alone manages.
 * @param newData Pointer to the data to be associated with this stream.
 * @param newDataLength Length of the buffer pointed to by newData.
 * @return Returns a pointer to a new BitStream structure or NULL on failure.
 **/
pBitStream initStream( char *newData, unsigned int newDataLength);

/**
 * Frees a BitStream along with the data it is pointing to.
 * @param stream BitStream ** that will be freed. This is set to NULL.
 * @return Returns nothing.
 **/
void freeStream( pBitStream *stream );

#endif
