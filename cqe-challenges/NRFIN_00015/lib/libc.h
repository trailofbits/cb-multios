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

typedef unsigned char uint8_t; // NRFIN_00001
#define MAX_WIDTH 16

extern int transmit_all(int fd, const char *buf, const size_t size); // NRFIN_00002
int recvline(int fd, char *buf, size_t size); // NRFIN_00001
int strncmp(const char *s1, const char *s2, size_t n);
int strn2int(const char* str_buf, size_t max_chars); // NRFIN_00001 - modified
void * memcpy(void* dst, const void* src, size_t cnt); // NRFIN_00001
size_t strnlen(const char *string, size_t max_len); // NRFIN_00009 - modified
size_t strlen(const char *string); // NRFIN_00009
char * itoaB10(int value); // NRFIN_00007
void * memset(void* str, int ch, size_t n); // NRFIN_00001
#endif
