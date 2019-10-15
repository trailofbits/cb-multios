/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef STDIO_H_
#define STDIO_H_

#include "cgc_stdlib.h"
#include "cgc_stdarg.h"

typedef struct FILE FILE;

extern FILE * const cgc_stdin;
extern FILE * const cgc_stdout;
extern FILE * const cgc_stderr;

int cgc_printf(const char *fmt, ...);
int cgc_fprintf(FILE *stream, const char *fmt, ...);
int cgc_sprintf(char *str, const char *fmt, ...);

int cgc_vprintf(const char *fmt, va_list ap);
int cgc_vfprintf(FILE *stream, const char *fmt, va_list ap);
int cgc_vsprintf(char *str, const char *fmt, va_list ap);

cgc_ssize_t cgc_fread(void *ptr, cgc_size_t size, FILE *stream);
cgc_ssize_t cgc_freaduntil(char *str, cgc_size_t size, char term, FILE *stream);
cgc_ssize_t cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream);
int cgc_fflush(FILE *stream);
void cgc_fbuffered(FILE *stream, int enable);
void cgc_fxlat(FILE *stream, const char *seed);

#endif
