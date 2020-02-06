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

/*
This libc consists of functions that are all available for release
in sample CB's and scored events.
*/

#ifndef NARF_LIBC_H
#define NARF_LIBC_H

// libc libs for public release and scored events

typedef signed char int8_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef enum {
  FALSE = 0,
  TRUE = 1,
} bool_t;

#define SUCCESS 0
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
list_t * cgc_list_create_dup();
int cgc_list_append(list_t *lst, node_t *nd);

// Node related
node_t * cgc_node_create(void * data);
node_t * cgc_get_list_head(list_t * lst);
node_t * cgc_get_list_tail(list_t * lst);
node_t * cgc_get_first_node(list_t * lst);
node_t * cgc_get_last_node(list_t * lst);

int cgc_rand(char *buf, cgc_size_t sz);

// libc libs borrowed from EAGLE_00004

// I/O
int cgc_send(const char *buf, const cgc_size_t size);
int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size);
unsigned int cgc_recv_all(char *res_buf, cgc_size_t res_buf_size);
unsigned int cgc_read_all(int fd, char *buf, unsigned int size);

// stdlib
void *cgc_memset(void *dst, int c, unsigned int n);


#endif
