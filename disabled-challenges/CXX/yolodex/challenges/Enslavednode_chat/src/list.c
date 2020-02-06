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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_common.h"
#include "cgc_error.h"
#include "cgc_list.h"

list *cgc_init_list(const DATA d)
{
  list *new = cgc_calloc(1, sizeof(list));
  if (!new)
    error(EALLOC);
  new->d = d;
  return new;
}

void cgc_append_list(list **l, const DATA d, int dups)
{
  if (!*l) {
    *l = cgc_init_list(d);
    return;
  }


  list *i = *l;
  if (!dups) {
    while (i) {
      if (!cgc_strcmp((char *)d, (char *)i->d))
        return;
      i = i->n;
    }
  }

  list *new = cgc_init_list(d);

  i = *l;
  while (i->n)
    i = i->n;
  i->n = new;
  new->p = i;
  new->n = NULL;
  return;
}

list *cgc_concat_list(list *l1, list *l2)
{
  list *l = NULL;

  if (!l1)
    return l2;

  if (!l2)
    return l1;

  l = l1;
  while (l2) {
    cgc_append_list(&l1, l2->d, 1);
    l2 = l2->n;
  }

  return l;
}


cgc_size_t cgc_len_list(const list *l)
{
  if (!l)
    return 0;

  cgc_size_t s = 0;

  while (l)
    s++, l = l->n;

  return s;
}

const DATA cgc_lindex(const list *l, cgc_ssize_t i)
{
  if (!l)
    return NULL;

  if (i < 0) {
    cgc_size_t t = cgc_len_list(l);
    while (i < 0)
      t--, i++;
    i = t;
  }

  if (i >= cgc_len_list(l))
    return NULL;

  for (cgc_size_t k = 0; k < i; k++)
    l = l->n;

  return l->d;
}



list *cgc_copy_list(const list *l, cgc_size_t start, cgc_size_t stop)
{
  if (!l)
    return NULL;

  cgc_size_t len = cgc_len_list(l);

  if (stop == 0 || stop > len)
    stop = len;

  if (start >= stop)
    return NULL;

  list *p = (list *)l;
  list *copy = NULL;

  // Get to start
  for (cgc_size_t i = 0; i < start; i++)
    p = p->n;

  // Copy from start to stop
  for (cgc_size_t i = start; i < stop; i++, p = p->n)
    cgc_append_list(&copy, p->d, 1);

  return copy;
}

void cgc_free_list(const list *l, int leave_data)
{
  const list *it;
  for (it = l; it; it = it->n) {
    if (!leave_data)
      cgc_free((void *)it->d);
    if (it->p)
      cgc_free(it->p);
  }
  cgc_free((void *)it);
}

void cgc_free_list_of_lists(const list *l, int leave_data)
{
  const list *it;
  for (it = l; it; it = it->n) {
    cgc_free_list((list *)l->d, leave_data - 1);
    if (it->p)
      cgc_free(it->p);
  }
  cgc_free((void *)it);
}

const void *cgc_random_element(list *l)
{
  cgc_size_t i, x, len = cgc_len_list(l);
  if (cgc_random(&i, sizeof(cgc_size_t), &x) < 0)
    error(ERAND);

  if (x != sizeof(cgc_size_t))
    return NULL;
  i %= len;
  return cgc_lindex(l, i);
}
