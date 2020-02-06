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

#include "libcgc.h"
#include "cgc_fixups.h"

#if DEBUG_ENABLE
#define DEBUG(msg) cgc_transmit(STDERR, msg, sizeof(msg), 0)
#else
#define DEBUG(msg) do {} while (0)
#endif

typedef unsigned int UINT32;
typedef unsigned char UINT8;

#define SUCCESS 0
#define BASE_ID 3
#define ERRNO_SEND BASE_ID+1
#define ERRNO_RECV BASE_ID+2
#define ERRNO_ALLOC BASE_ID+3

void cgc_memcpy(unsigned char *dst, const unsigned char *src, cgc_size_t n);
int cgc_memcmp(const char *s1, const char *s2, cgc_size_t n);
unsigned char * cgc_memset(unsigned char *b, unsigned char c, cgc_size_t len);
cgc_size_t cgc_findchar(char *haystack, char needle);
void cgc_pause(cgc_size_t usec);
int cgc_sendallnulltrunc(int fd, const char *buf, cgc_size_t size);
UINT32 cgc_my_pow(UINT32 x, UINT32 y);
UINT32 cgc_hex2UINT32(char *hex);
int cgc_sendall(int fd, const char *buf, cgc_size_t size);
int cgc_recvline(int fd, char *buf, cgc_size_t size);

#define SEND(b,s,o) o=cgc_sendall(STDOUT,b,s); if (o<=0) cgc__terminate(ERRNO_SEND);
#define SENDNULLTRUNC(b,s,o) o=cgc_sendallnulltrunc(STDOUT,b,s); if (o<=0) cgc__terminate(ERRNO_SEND);
#define RECV(b,s,o) o=cgc_recvline(STDIN,b,s); if(o<0) cgc__terminate(ERRNO_RECV);
#define ALLOC(s,x,a,o) o=cgc_allocate(s,x,a); if(o!=0) cgc__terminate(ERRNO_ALLOC);
#define QUIT() cgc__terminate(SUCCESS);

UINT8 *ptr_credits;

#endif

