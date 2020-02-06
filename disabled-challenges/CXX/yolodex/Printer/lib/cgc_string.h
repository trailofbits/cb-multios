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
#ifndef STRING_H_
#define STRING_H_

#include "cgc_stdlib.h"

void *cgc_memcpy(void *dst, const void *src, cgc_size_t n);
void *cgc_memmove(void *dst, const void *src, cgc_size_t n);
int cgc_memcmp(const void *s1, const void *s2, cgc_size_t n);
void *cgc_memchr(const void *s, int c, cgc_size_t n);
void *cgc_memset(void *s, int c, cgc_size_t n);

cgc_size_t cgc_strlen(const char *s);
char *cgc_strcpy(char *dst, const char *src);
char *cgc_strncpy(char *dst, const char *src, cgc_size_t len);
char *cgc_strchr(const char *s, int c);
char *cgc_strsep(char **stringp, const char *delim);
char *cgc_strstr(const char *haystack, const char *needle);
char *cgc_strcasestr(const char *haystack, const char *needle);

int cgc_strcmp(const char *s1, const char *s2);
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
int strcasecmp(const char *s1, const char *s2);
int cgc_strncasecmp(const char *s1, const char *s2, cgc_size_t n);

char *cgc_strdup(const char *s1);
char *cgc_strndup(const char *s1, cgc_size_t n);

#endif
