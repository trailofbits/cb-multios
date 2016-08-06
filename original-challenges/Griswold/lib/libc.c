/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 * Copyright (C) Chris Eagle from the Naval Postgraduate School
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

#include <libcgc.h>
#include "libc.h"

// libc's created specifically for public release and scored events

// doubly-linked list functions
// the nodes in the list should all be of the same type to be comparable.

// Allocates and initializes a list.
//  There is no requirement for node content to be unique.
// RETURNS
//  success: &(the new list)
//  failure: NULL
list_t * list_create_dup() {
  list_t *new = NULL;
  if (SUCCESS != (allocate(sizeof(list_t), 0, (void **)&new))) { return NULL; }
  node_t * head_nd = node_create(NULL);
  node_t * tail_nd = node_create(NULL);
  head_nd->next = tail_nd;
  head_nd->prev = NULL;
  tail_nd->next = NULL;
  tail_nd->prev = head_nd;

  new->head = head_nd;
  new->tail = tail_nd;
  new->count = 0;
  return new;
}

// Append the provided node to the provided list.
// RETURNS
//  success: SUCCESS
int list_append(list_t *lst, node_t *nd) {

  int ret = SUCCESS;

  // setup node pointers
  nd->next = lst->tail;
  nd->prev = lst->tail->prev;

  // insert node
  lst->tail->prev->next = nd;
  lst->tail->prev = nd;

  // increment count
  lst->count++;

  return ret;
}

// Allocate space for and initialize a new node struct.
// RETURNS:
//  success: VA of new node
//  failure: NULL
node_t * node_create(void * data) {
  node_t *new = NULL;
  if (SUCCESS != (allocate(sizeof(node_t), 0, (void **)&new))) { return NULL; }
  new->data = data;
  new->next = NULL; // these will be set during list insertion
  new->prev = NULL;
  return new;
}

// Get the token head node.
// RETURNS:
//  &node
node_t * get_list_head(list_t * lst) {
  return lst->head;
}

// Get the token tail node.
// RETURNS:
//  &node
node_t * get_list_tail(list_t * lst) {
  return lst->tail;
}

// Get the first node in the list used by the client to store data.
// RETURNS:
//  &node
node_t * get_first_node(list_t * lst) {
  return lst->head->next;
}

// Get the last node in the list used by the client to store data.
// RETURNS:
//  &node
node_t * get_last_node(list_t * lst) {
  return lst->tail->prev;
}


// write sz random bytes into buf
// returns 0 on success, non-zero on failure.
int rand(char *buf, size_t sz) {
    size_t bytes = 0;
    return random(buf, sz, &bytes);
}


////////////////////////////////
// libc libs borrowed from EAGLE_00004


// I/O functions
int send(const char *buf, const size_t size) {
    if(transmit_all(STDOUT, buf, size)) {
        _terminate(111);
    }

    return 0;
}

int transmit_all(int fd, const char *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

// returns number of bytes received
unsigned int recv_all(char *res_buf, size_t res_buf_size) {
    return read_all(STDIN, res_buf, res_buf_size);
}

unsigned int read_all(int fd, char *buf, unsigned int size) {
   char ch;
   unsigned int total = 0;
   size_t nbytes;
   while (size) {
      if (receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
         break;
      }
      buf[total++] = ch;
      size--;
   }
   return total;
}

// stdlib functions

// overwrites the first n chars of dst with char c.
void *memset(void *dst, int c, unsigned int n) {
   char *d = (char*)dst;
   while (n--) {*d++ = (char)c;}
   return dst;
}

