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

#include "libcgc.h"
#include "cgc_malloc.h"

void cgc_bzero( void *buff, cgc_size_t cgc_len );
char *cgc_strchr(const char *s, int c);
void cgc_int_to_str( int val, char *buf );

char *cgc_strtok(char *str, const char *delim);
char *cgc_strdup(char *s);
int cgc_isspace( int c );
int cgc_isdigit( int c );
int cgc_isnan( double val );
int cgc_isinf( double val );
int cgc_tolower( int c );
int cgc_toupper( int c );
double atof(const char *str);
int cgc_atoi(const char *str);
int cgc_abs( int );

void cgc_puts(char *str);
int cgc_strcmp( char *str1, char *str2 );
char *cgc_strcpy( char *dest, char *src );
char *cgc_strncpy( char *dest, const char *src, cgc_size_t num );
cgc_size_t cgc_strlen( const char *str );
int cgc_printf( const char *fmt, ... );
int cgc_sprintf( char *str, const char *fmt, ... );
cgc_size_t cgc_getline( char *buffer, cgc_size_t len );
cgc_size_t cgc_receive_until( char *, char, cgc_size_t );

void* cgc_memcpy( void *dest, void *src, cgc_size_t numbytes );
void* cgc_memset( void *dest, int value, cgc_size_t num );

#endif // __STDLIB_H__
