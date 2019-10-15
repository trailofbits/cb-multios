/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_filesystem.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_input.h"
#include "cgc_malloc.h"


int cgc_sendStickPost( unsigned int postID ) {

fileHandleType fh;
int retcode;
unsigned char posterName[REALNAME_LEN+1];
unsigned char thePost[MAXPOST_LEN+1];
unsigned int count;
int i;

	if ( postID > 15 ) {

		return -1;

	}

	// this is a memory mapped file to the magic page of data
	fh = cgc_openFile( "sticky.posts", ROOT_ID );

	if ( fh < 0 ) {

		cgc_printf("unable to open sticky posts\n");
		return -1;

	}

	// each post is 160 bytes in size, jump to the offset of the post we want
	cgc_fileReadPosition( fh, postID * 160 );

	if (cgc_readFile( fh, (void *)posterName, REALNAME_LEN, 0, &count, ROOT_ID ) != 0) {

		cgc_printf("error reading sticky post\n");
		return -1;

	}

	if (count != REALNAME_LEN) {

		cgc_printf("Error reading data for sticky post\n");
		return -1;

	}

	posterName[REALNAME_LEN] = 0;

	if ( cgc_readFile( fh, (void *)thePost, MAXPOST_LEN, 0, &count, ROOT_ID ) != 0 ) {

		cgc_printf("error reading sticky post\n");
		return -1;

	}

	if (count != MAXPOST_LEN) {

		cgc_printf("Error reading data for sticky post\n");
		return -1;

	}

	thePost[MAXPOST_LEN] = 0;

	for (i=0; i < REALNAME_LEN; ++ i)
		posterName[i] = (posterName[i] % 26) + 'A';

	for (i=0; i < MAXPOST_LEN; ++ i)
		thePost[i] = (thePost[i] % 26) + 'A';	

	count = REALNAME_LEN;
	cgc_sendResponse( (void *)&count, sizeof(int) );
	cgc_sendResponse( posterName, count );

	count = MAXPOST_LEN;
	cgc_sendResponse( (void *)&count, sizeof(int) );
	cgc_sendResponse( thePost, count );

	cgc_closeFile( fh );

	return 0;
	
}

