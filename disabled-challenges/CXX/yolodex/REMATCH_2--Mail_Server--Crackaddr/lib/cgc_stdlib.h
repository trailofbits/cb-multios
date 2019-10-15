/*

Copyright (c) 2015 Cromulence LLC

Authors: Cromulence <cgc@cromulence.com>

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
#ifndef __STDLIB_H__
#define __STDLIB_H__

#include "libcgc.h"

#define RAND_MAX	2147483647

int cgc_rand( void );
void cgc_srand( unsigned int seed );

int cgc_atoi( const char *pStr );
double cgc_atof( char *pStr );
 
char *cgc_strcpy( char *pDest, const char *pSource );
char *cgc_strncpy( char *pDest, const char *pSource, cgc_size_t maxlen );
void *cgc_memcpy( void *pDest, const void *pSrc, cgc_size_t nbytes );
void get_cgc_random( void *dest, int size);

#endif // STDLIB_H__
