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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "error.h"
#include "list.h"

list *init_list(const DATA d)
{
  list *new = calloc(1, sizeof(list));
  if (!new)
    error(EALLOC);
  new->d = d;
  return new;
}

void append_list(list **l, const DATA d, int dups)
{
  if (!*l) {
    *l = init_list(d);
    return;
  }


  list *i = *l;
  if (!dups) {
    while (i) {
      if (!strcmp((char *)d, (char *)i->d))
        return;
      i = i->n;
    }
  }

  list *new = init_list(d);

  i = *l;
  while (i->n)
    i = i->n;
  i->n = new;
  new->p = i;
  new->n = NULL;
  return;
}

list *concat_list(list *l1, list *l2)
{
  list *l = NULL;

  if (!l1)
    return l2;

  if (!l2)
    return l1;

  l = l1;
  while (l2) {
    append_list(&l1, l2->d, 1);
    l2 = l2->n;
  }

  return l;
}


size_t len_list(const list *l)
{
  if (!l)
    return 0;

  size_t s = 0;

  while (l)
    s++, l = l->n;

  return s;
}

const DATA lindex(const list *l, ssize_t i)
{
  if (!l)
    return NULL;

  if (i < 0) {
    size_t t = len_list(l);
    while (i < 0)
      t--, i++;
    i = t;
  }

  if (i >= len_list(l))
    return NULL;

  for (size_t k = 0; k < i; k++)
    l = l->n;

  return l->d;
}



list *copy_list(const list *l, size_t start, size_t stop)
{
  if (!l)
    return NULL;

  size_t len = len_list(l);

  if (stop == 0 || stop > len)
    stop = len;

  if (start >= stop)
    return NULL;

  list *p = (list *)l;
  list *copy = NULL;

  // Get to start
  for (size_t i = 0; i < start; i++)
    p = p->n;

  // Copy from start to stop
  for (size_t i = start; i < stop; i++, p = p->n)
    append_list(&copy, p->d, 1);

  return copy;
}

void free_list(const list *l, int leave_data)
{
  const list *it;
  for (it = l; it; it = it->n) {
    if (!leave_data)
      free((void *)it->d);
    if (it->p)
      free(it->p);
  }
  free((void *)it);
}

void free_list_of_lists(const list *l, int leave_data)
{
  const list *it;
  for (it = l; it; it = it->n) {
    free_list((list *)l->d, leave_data - 1);
    if (it->p)
      free(it->p);
  }
  free((void *)it);
}

const void *random_element(list *l)
{
  size_t i, x, len = len_list(l);
  if (random(&i, sizeof(size_t), &x) < 0)
    error(ERAND);

  if (x != sizeof(size_t))
    return NULL;
  i %= len;
  return lindex(l, i);
}
