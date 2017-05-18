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

extern int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size); // NRFIN_00002
int cgc_recvline(int fd, char *buf, cgc_size_t size); // NRFIN_00001
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
int cgc_strn2int(const char* str_buf, cgc_size_t max_chars); // NRFIN_00001 - modified
void * cgc_memcpy(void* dst, const void* src, cgc_size_t cnt); // NRFIN_00001
cgc_size_t cgc_strnlen(const char *string, cgc_size_t max_len); // NRFIN_00009 - modified
cgc_size_t cgc_strlen(const char *string); // NRFIN_00009
char * cgc_itoaB10(int value); // NRFIN_00007
void * cgc_memset(void* str, int ch, cgc_size_t n); // NRFIN_00001
#endif
