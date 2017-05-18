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

#include "libcgc.h"
#include "cgc_libc.h"


// libc's created specifically for public release and scored events

// doubly-linked list functions
// the nodes in the list should all be of the same type to be comparable.

// Allocates and initializes a list.
//  There is no requirement for node content to be unique.
// RETURNS
//  success: &(the new list)
//  failure: NULL
list_t * cgc_list_create_dup() {
  list_t *new = NULL;
  if (SUCCESS != (cgc_allocate(sizeof(list_t), 0, (void **)&new))) { return NULL; }
  node_t * head_nd = cgc_node_create(NULL);
  node_t * tail_nd = cgc_node_create(NULL);
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
int cgc_list_append(list_t *lst, node_t *nd) {

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

// Insert the provided node into the provided list,
// such that nodes are sorted ascending (low to high).
// RETURNS
//  success: SUCCESS
int cgc_list_insert_sort(list_t *lst, node_t *nd, node_compare_f node_compare_impl) {

  int ret = SUCCESS;

  // if empty list, insert as first node
  if (lst->head->next == lst->tail) {
    lst->head->next = nd;
    lst->tail->prev = nd;
    nd->next = lst->tail;
    nd->prev = lst->head;
  } else if (node_compare_impl(nd, lst->head->next) < 0) {
    // if this nd's value is < first node's value, insert as first node
    lst->head->next->prev = nd;
    nd->next = lst->head->next;
    nd->prev = lst->head;
    lst->head->next = nd;
  } else {
    // insert node into a non-empty sorted list
    node_t * curr = lst->head->next;
    while(curr != lst->tail) {
      // insert new element as tail
      if(curr->next == lst->tail || (node_compare_impl(nd, curr->next) < 0)) {
        nd->next = curr->next;
        nd->prev = curr;
        nd->next->prev = nd;
        curr->next = nd;
        break;
      }
      curr = curr->next;
    }
  }

  // increment count
  lst->count++;

  return ret;
}

// Allocate space for and initialize a new node struct.
// RETURNS:
//  success: VA of new node
//  failure: NULL
node_t * cgc_node_create(void * data) {
  node_t *new = NULL;
  if (SUCCESS != (cgc_allocate(sizeof(node_t), 0, (void **)&new))) { return NULL; }
  new->data = data;
  new->next = NULL; // these will be set during list insertion
  new->prev = NULL;
  return new;
}

// Get the token head node.
// RETURNS:
//  &node
node_t * cgc_get_list_head(list_t * lst) {
  return lst->head;
}

// Get the token tail node.
// RETURNS:
//  &node
node_t * cgc_get_list_tail(list_t * lst) {
  return lst->tail;
}

// Get the first node in the list used by the client to store data.
// RETURNS:
//  &node
node_t * cgc_get_first_node(list_t * lst) {
  return lst->head->next;
}

// Get the last node in the list used by the client to store data.
// RETURNS:
//  &node
node_t * cgc_get_last_node(list_t * lst) {
  return lst->tail->prev;
}


// cgc_write sz random bytes into buf
// returns 0 on success, non-zero on failure.
int cgc_rand(char *buf, cgc_size_t sz) {
    cgc_size_t bytes = 0;
    return cgc_random(buf, sz, &bytes);
}


////////////////////////////////
// libc libs borrowed from EAGLE_00004


// I/O functions
int cgc_send(const char *buf, const cgc_size_t size) {
    if(cgc_transmit_all(STDOUT, buf, size)) {
        cgc__terminate(111);
    }

    return 0;
}

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

// returns number of bytes received
unsigned int cgc_recv_all(char *res_buf, cgc_size_t res_buf_size) {
    return cgc_read_all(STDIN, res_buf, res_buf_size);
}

unsigned int cgc_read_all(int fd, char *buf, unsigned int size) {
   char ch;
   unsigned int total = 0;
   cgc_size_t nbytes;
   while (size) {
      if (cgc_receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
         break;
      }
      buf[total++] = ch;
      size--;
   }
   return total;
}

// stdlib functions

// overwrites the first n chars of dst with char c.
void *cgc_memset(void *dst, int c, unsigned int n) {
   char *d = (char*)dst;
   while (n--) {*d++ = (char)c;}
   return dst;
}

