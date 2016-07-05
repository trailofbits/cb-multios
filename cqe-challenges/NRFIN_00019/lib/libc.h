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

// #define DEBUG 1

#define SUCCESS 0
#define ERRNO_INVALID_EXIT -6
#define ERRNO_RECV -7
#define ERRNO_TRANSMIT -8
#define ERRNO_INSUFFICIENT_BYTES -9
#define ERRNO_BAD_GATE -10
#define ERRNO_RANDOM -11
#define ERRNO_INVALID_OPERATION -12

// Fragmentation related
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes);
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes);

unsigned char * memset(unsigned char *b, unsigned char c, size_t len);

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////
#ifdef DEBUG

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

