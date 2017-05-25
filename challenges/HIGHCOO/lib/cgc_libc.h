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
#include "libcgc.h"

#ifndef NARF_LIBC_H
#define NARF_LIBC_H

typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


// VA defs for xxprintf functions
#ifdef WIN
#define _VA_LIST
#include <stdarg.h>
#else
#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(al, lp)  __builtin_va_start(al, lp)
#define va_end(al)          __builtin_va_end(al)
#define va_arg(al, t)    __builtin_va_arg(al, t)
#define va_copy(d, s)       __builtin_va_copy(d, s)
#endif


#define SUCCESS 0
typedef enum {
	FALSE = 0,
	TRUE = 1,
} bool_t;

// list errors
#define ERRNO_LIST_PUSH 44
#define ERRNO_ALLOC 5

typedef struct node {
	void * data;
	struct node *next;
	struct node *prev;
} node_t;
// doubly-linked list

typedef struct list {
	node_t *head;
	node_t *tail;
	uint32_t count;
} list_t;

// List related
list_t * cgc_list_create();
int cgc_list_push(list_t *lst, node_t *nd);

// Node related
node_t * cgc_node_create(void * data);

// I/O
int cgc_send(const char * buf, const cgc_size_t size);
int cgc_sendall(int fd, const char * buf, const cgc_size_t size);
unsigned int cgc_recv_all(char *res_buf, cgc_size_t res_buf_size);
unsigned int cgc_read_all(int fd, char *buf, unsigned int size);
int cgc_recvline(int fd, char *buf, cgc_size_t size);

// stdlib
unsigned int cgc_strlen(const char * str);
void * cgc_memset(void * str, int ch, unsigned int n);
void * cgc_memcpy(void * dst, const void * src, cgc_size_t cnt);
int cgc_rand(char *res, cgc_size_t len);
int cgc_vsnprintf(char * buf, cgc_size_t buf_size, const char * fmt, va_list args);
int cgc_snprintf(char * buf, cgc_size_t buf_size, const char * fmt, ...);
int cgc_int2str(char * str_buf, int buf_size, int i);

#endif
