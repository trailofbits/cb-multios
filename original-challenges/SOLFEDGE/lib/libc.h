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
#include <libcgc.h>

#ifndef NARF_LIBC_H
#define NARF_LIBC_H

typedef signed char int8_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define SUCCESS 0
#define ERRNO_ALLOC 505


// libc libs borrowed from EAGLE_00004

int send(const char *buf, const size_t size);
int transmit_all(int fd, const char *buf, const size_t size);
unsigned int recv_all(char *res_buf, size_t res_buf_size);
unsigned int read_all(int fd, char *buf, unsigned int size);

void *memset(void *dst, int c, unsigned int n);

#endif
