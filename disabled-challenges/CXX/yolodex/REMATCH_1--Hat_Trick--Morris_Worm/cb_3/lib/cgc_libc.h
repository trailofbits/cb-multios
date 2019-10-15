/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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

#define FLAG_PAGE 0x4347c000
#define PAGE_SIZE 4096

int cgc_receive_all(char *buf, int length);
int cgc_receive_all_fd(int fd, char *buf, int length);
int cgc_send_all(char *buf, int length);
int cgc_send_all_fd(int fd, char *buf, int length);
int cgc_receive_until(char *buf, int length, char delim);
int cgc_receive_until_fd(int fd, char *buf, int length, char delim);
int cgc_equals(char *s, char *d);
int cgc_replace(char *s, char find, char replace, int num);
int cgc_force_newline(char *s, int size, int bytes);
int cgc_getopt(int argc, char **argv, char *optstring, int *opt_index);
void cgc_bcopy(char *s, char *d, cgc_size_t size);
void cgc_exit(int e);

#endif