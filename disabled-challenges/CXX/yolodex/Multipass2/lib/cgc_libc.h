/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 * Copyright (C) Chris Eagle at Naval Postgraduate School
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

#ifndef NARF_LIBC_H
#define NARF_LIBC_H

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define SUCCESS 0
// list errors
#define ERRNO_LIST_PUSH 404
#define ERRNO_ALLOC 505

typedef struct node {
	void * data;
	struct node *next;
	struct node *prev;
} node_t;
// doubly-linked list
// int node_contains(struct node * nd, const void * value) {}
//  -- should return 0 when node nd contains value, 1 when not.
typedef int(*node_contains_f)(node_t *, void *);

typedef struct list {
	node_t *head;
	node_t *tail;
	uint32_t count;
	node_contains_f node_contains_impl;
} list_t;

// List related
list_t * cgc_list_create(node_contains_f node_contains_impl);
int cgc_list_push(list_t *lst, node_t *nd, void * value);
node_t * cgc_list_find(list_t *lst, void * value);
node_t * cgc_list_remove(list_t *lst, void * value);

// Node related
node_t * cgc_node_create(void * data);
int cgc_node_destroy(node_t *nd);

// I/O
int cgc_send(const char *buf, const cgc_size_t size);
int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size);
unsigned int cgc_recv_all(char *res_buf, cgc_size_t res_buf_size);
unsigned int cgc_read_all(int fd, char *buf, unsigned int size);

// stdlib
cgc_size_t cgc_strlen(const char *str);
void *cgc_memset(void *dst, int c, unsigned int n);


#endif
