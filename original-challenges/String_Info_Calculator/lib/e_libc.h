/*
 * Copyright (C) Chris Eagle
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

// this is the libc from EAGLE_00005/pov_1/
// the only change I've made is to define fprintf() in e_libc.c
// this is only used when debugging.
#ifndef E_LIBC_H
#define E_LIBC_H

// size_t strlen(const char *str);
// char *strcpy(char *dst, const char *src);
// int strcmp(const char *s1, const char *s2);
// int memcmp(const char *s1, const char *s2, unsigned int len);
// char *memcpy(char *s1, const char *s2, unsigned int len);
// char *strchr(const char *s, int c);
// int printf(const char *format, ...);

// int toupper(int c);
// int tolower(int c);

// int transmit_all(int fd, const void *buf, const size_t size);
// int receive_all(int fd, char *buf, const size_t size);

#define EOF                  -1

#ifndef NULL
#define NULL ((void*)0)
#endif

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

struct _FILE;
typedef struct _FILE FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

// int  fgetc(FILE *);
// int  getc(FILE *);
// int  getchar(void);

// char *fgets(char *, int, FILE *);
// int fread(void *, size_t, size_t, FILE *);

// int ferror(FILE *stream);
// int feof(FILE *stream);

int fprintf(FILE * stream, const char *format, ...);

#endif
