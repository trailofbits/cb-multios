/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBC_H
#define LIBC_H

#include <libcgc.h>

//#define DEBUG 1
#define STRING_TERMINATOR '\x06'
#define STRING_TERMINATOR_STR "\x06"
#define MAX_RECURSION_DEPTH 1000

#define SUCCESS 0
#define BASE_ID 11
#define ERRNO_CANON BASE_ID+4
#define ERRNO_RECUSION BASE_ID+5

unsigned char * memset(void *b, char c, size_t len);
int recv_until_delim(int fd, char *buf, size_t size);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t len);
size_t strlen(const char *str);
char * strpos(char * haystack, char * needle);
char * strncat(char *s1, const char *s2, size_t n);
char * strncpy(char *dest, const char *src, size_t n);
int transmit_with_term(int fd, const void *buf, size_t count, size_t *tx_bytes);
int receive_with_term(int fd, void *buf, size_t count, size_t *rx_bytes);

// Fragmentation related
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes);
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes);


#ifdef DEBUG

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int fprintf(FILE * stream, const char *format, ...);

#endif
// ^ DEBUG

#endif
// ^ LIBC_H

