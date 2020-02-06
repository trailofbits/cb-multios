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
#ifndef __STRING_H__
#define __STRING_H__

#include "libcgc.h"

cgc_size_t cgc_strlen( const char *str );
void cgc_bzero(void *s, cgc_size_t n);
void *cgc_memset( void *ptr, int value, cgc_size_t num );
char *cgc_strchr(char *s, int c);
char *cgc_strstr( char *str, char *sub, cgc_size_t len);
char *cgc_strtok(char *str, char *sep);
int cgc_strcmp(const char *s1, const char *s2);
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
char *cgc_strcat(char *restrict s1, const char *restrict s2);
char *cgc_strncat(char *s1, char *s2, cgc_size_t n);
int cgc_memcmp( const void *s1, const void *s2, cgc_size_t n );

#endif // __STRING_H__
