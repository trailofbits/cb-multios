/*
 * Author: Garrett Barboza <garrett.barboza@kapricasecurity.com>
 *
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "malloc.h"
#include "stdlib.h"

/* Get some more memory through allocate */
static int allocate_new_blk(void)
{
  void *ret;
  struct blk_t *new_blk;
  size_t size = NEW_CHUNK_SIZE;

  if (allocate(size, 0, &ret) != 0) {
    return 1;
  }

  if (ret == NULL)
    return 1;

  new_blk = (struct blk_t *)ret;
  new_blk->size = size;
  new_blk->free = 1;
  new_blk->fpred = NULL;
  new_blk->fsucc = NULL;
  new_blk->prev = NULL;
  new_blk->next = NULL;

  insert_into_flist(new_blk);
  return 0;
}

/* Find first fit block for a size */
static int find_fit(size_t size, struct blk_t **blk)
{
  int sc_i = get_size_class(size);

  for (; sc_i < NUM_FREE_LISTS; sc_i++) {
    *blk = free_lists[sc_i];
    for(; *blk != NULL; *blk = (*blk)->fsucc)
      if ((*blk)->size >= size)
        return sc_i;
  }

  *blk = NULL;
  return -1;
}

static void *malloc_huge(size_t size)
{
    void *mem;
    size += HEADER_PADDING;
    if (allocate(size, 0, &mem) != 0)
        return NULL;
    struct blk_t *blk = mem;
    blk->size = size;
    blk->free = 0;
    blk->fpred = NULL;
    blk->fsucc = NULL;
    blk->prev = NULL;
    blk->next = NULL;
    return (void *)((intptr_t)blk + HEADER_PADDING);
}

void *malloc(size_t size)
{
  if (size == 0)
    return NULL;

  if (size + HEADER_PADDING >= NEW_CHUNK_SIZE)
    return malloc_huge(size);

  if (size % ALIGNMENT != 0)
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

  size += HEADER_PADDING;

  struct blk_t *blk = NULL;
  int sc_i = find_fit(size, &blk);

  /* Allocate a new block if no fit */
  if (blk == NULL) {
    if (allocate_new_blk() != 0) {
      return NULL;
    } else {
      sc_i = NUM_FREE_LISTS - 1;
      blk = free_lists[sc_i];
    }
  }

  /* Remove the block we're going to use from the free list */
  remove_from_flist(blk);

  /* Split the block into two pieces if possible */
  size_t sdiff = blk->size - size;
  if (sdiff > 2*HEADER_PADDING) {
    struct blk_t *nb = (struct blk_t *)((intptr_t)blk + size);

    nb->size = sdiff;
    nb->free = 1;
    nb->fsucc = NULL;
    nb->fpred = NULL;

    blk->size = size;

    /* Patch up blk list pointers */
    nb->prev = blk;
    nb->next = blk->next;
    if (blk->next)
      blk->next->prev = nb;
    blk->next = nb;

    /* Put the new block into the free list */
    insert_into_flist(nb);
  }

  return (void *)((intptr_t)blk + HEADER_PADDING);
}
