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

#include "cgc_service.h"

cgc_size_t cgc_receiveIt( void *data, cgc_size_t length )
{
	cgc_size_t count = 0;
	unsigned char *tdata = (unsigned char *)data;
	int bread = 0;

	if ( data == NULL ) {
		return 0;
	}

	while ( 0 < length ) {
		if ( cgc_receive( 0, tdata + bread, length, &count ) != 0 ) {
			cgc_printf("[ERROR] Failed to receive\n");
			return 0;
		}

		bread += count;
		length -= count;
	}

	return bread;
}

/**
 * This function provides the ability to cgc_read in the size of the video stream followed by the specified number of bytes for the image data. The maximum size for a video is 4096 bytes and the minimum is 8
 * @return Returns a readable bitstream of the newly received data.
 **/
pBitStream cgc_readImageData( void )
{
	int length = 0;
	cgc_size_t bytes_read = 0;
	pBitStream npbs = NULL;
	char *newData = NULL;

	cgc_printf("----------------Stream Me Your Video----------------\n");

	bytes_read = cgc_receiveIt( &length, 4 );

	if ( bytes_read != 4 ) {
		return NULL;
	}

	if ( length > 4096 ) {
		cgc_printf("[ERROR] Image must be smaller than 4096 bytes\n");
		return NULL;
	}

	if ( length < 8 ) {
		cgc_printf("[ERROR] Image must be greater than 8 bytes\n");
		return NULL;
	}

	newData = cgc_malloc( length );

	if ( newData == NULL ) {
		return NULL;
	}

	cgc_memset( newData, 0, length );	

	bytes_read = cgc_receiveIt( newData, length );

	if ( bytes_read != length ) {
		cgc_free( newData );
		return NULL;
	}

	/// This function allocates a new block and copies the existing data 
	/// into that new buffer without freeing the data buffer
	npbs = cgc_initStream( newData, length );

	/// We no longer need the old data so free the buffer.
	cgc_free( newData );
	newData = NULL;

	return npbs;
}

int main(int cgc_argc, char *cgc_argv[])
{
	unsigned char ba = 0;

	pBitStream bs;

	bs = cgc_readImageData( );

	if ( bs == NULL ) {
		return 0;
	}

	cgc_renderCVF( bs );

	cgc_freeStream( &bs );
	return 0;
}
