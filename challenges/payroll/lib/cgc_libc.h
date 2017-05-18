/*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#ifndef LIBC_H
#define LIBC_H

int cgc_receive_until(char *dest, cgc_size_t length, char end, cgc_size_t *bytes_read);
cgc_size_t cgc_strlen(char *buf);
void cgc_print(char *buf);
int cgc_equals(char *one, char *two);
void cgc_strncpy(char *dst, char *src, cgc_size_t length);
int cgc_isdigit(char c);
int cgc_atoi(char *str);
void cgc_itoa(char *str, int i);
void cgc_memcpy(char *dst, char *src, cgc_size_t size);
void cgc_memset(char *dst, char c, cgc_size_t size);


#endif // LIBC_H
