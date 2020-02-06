/*

Author: Jason Williams <jdw@cromulence.com>

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
#ifndef __STDLIB_H__
#define __STDLIB_H__

#define INUSE_FLAG 1
#define FREE_FLAG 2

#include "libcgc.h"

typedef struct _heap_block_header {
	cgc_size_t remaining_size;
	struct _heap_block_header *next;
	char data[1];
} heap_block_header;


typedef struct _heap_header {
	cgc_size_t size;
	char flags;
} heap_header;

typedef struct _heap_metadata {
	cgc_size_t mem_commit;
	cgc_size_t mem_free;
	cgc_size_t mem_inuse;
	heap_block_header *blocks;
} heap_metadata;

int cgc_isspace( int c );
int cgc_isdigit( int c );
int cgc_isnan( double val );
int cgc_isinf( double val );
double cgc_atof(const char *str);
int cgc_atoi(const char *str);
void *cgc_calloc(cgc_size_t count, cgc_size_t size);
void cgc_free(void *ptr);
void *cgc_malloc(cgc_size_t size);


char *cgc_strcpy( char *dest, char *src );
int cgc_printf( const char *fmt, ... );
void cgc_bzero( void *, cgc_size_t );
int cgc_strcmp( const char *, const char * );
char *cgc_strncat( char *dest, const char *src, cgc_size_t n );
cgc_size_t cgc_receive_until( char *, char, cgc_size_t );
cgc_size_t cgc_strcat( char *, char* );
cgc_size_t cgc_strlen( char * );
cgc_size_t cgc_itoa( char *, cgc_size_t, cgc_size_t );
void cgc_puts( char *t );
void *cgc_memcpy(void *dest, void*src, unsigned int len);
void *cgc_memset(void *dest, char c, unsigned int len);
cgc_size_t cgc_strlen( char * str );

#endif // __STDLIB_H__
