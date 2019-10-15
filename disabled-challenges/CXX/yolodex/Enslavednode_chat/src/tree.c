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

#include "cgc_stdlib.h"
#include "cgc_common.h"
#include "cgc_list.h"
#include "cgc_error.h"
#include "cgc_tree.h"

tree *cgc_init_tree(HASH h, const DATA d)
{
  tree *new = cgc_calloc(1, sizeof(tree));
  if (!new)
    error(EALLOC);

  if (h && d) {
    new->h = h;
    new->dl = cgc_init_list(d);
  }

  return new;
}

list *cgc_get_tree(tree *t, HASH h)
{
  if (!t)
    return NULL;

  if (h < t->h)
    return cgc_get_tree(t->l, h);

  if (h > t->h)
    return cgc_get_tree(t->r, h);

  return t->dl;
}

int cgc_ins_tree(tree *t, HASH h, const DATA d)
{
  if (!t)
    return -1;

  tree **next = NULL;

  if (h < t->h) {
    next = &t->l;
  } else if (h > t->h) {
    next = &t->r;
  } else {
    cgc_append_list(&t->dl, d, 0);
    return 0;
  }

  if (*next)
    return cgc_ins_tree(*next, h, d);

  *next = cgc_init_tree(h, d);

  return 0;
}

cgc_size_t cgc_num_nodes(tree *t)
{
  if (!t)
    return 0;

  return 1 + cgc_num_nodes(t->l) + cgc_num_nodes(t->r);
}

int cgc__tree_to_list(tree *t, list *l)
{
  if (!t)
    return 0;

  cgc_append_list(&l, t->dl, 1);

  if (cgc__tree_to_list(t->l, l) < 0)
    return -1;
  if (cgc__tree_to_list(t->r, l) < 0)
    return -1;

  return 0;
}

list *cgc_tree_to_list(tree *t)
{
  list *l = NULL;

  if (!t)
    return NULL;

  l = cgc_init_list(t->dl);

  if (cgc__tree_to_list(t->l, l) < 0)
    return NULL;

  if (cgc__tree_to_list(t->r, l) < 0)
    return NULL;

  return l;
}
