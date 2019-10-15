/*

Author: John Berry <hj@cromulence.co>

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

#ifndef __STRING_H__
#define __STRING_H__

#include "libcgc.h"
#include "cgc_stdlib.h"

/**
 * Structure to maintain the buffer and index
 **/
typedef struct string {
        /// Pointer to the data
        char *buffer;

        /// Total length of the string
        int maxlength;

        /// Current index being examined
        int index;
} string, *pstring;

void cgc_freeString(pstring str );
int cgc_skipAlpha( pstring str );
int cgc_incChar( pstring st );
pstring cgc_initString( char *data );
int cgc_skipWhiteSpace( pstring st );
int cgc_atChar( pstring st, char c );
int cgc_skipTo( pstring st, char c );
int cgc_skipLength( pstring st, int count );
int cgc_skipToNonAlphaNum( pstring str );
int cgc_skipToNonAlphaNumSpace( pstring str );
char *cgc_copyData( pstring str, int start, int end );
int cgc_skipFloat( pstring str );
int cgc_skipInt( pstring str );
int cgc_getIndex( pstring str, int *outIndex );
int cgc_skipUrl( pstring str );

#endif
