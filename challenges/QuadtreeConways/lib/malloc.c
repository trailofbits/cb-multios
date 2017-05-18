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
#include "cgc_malloc.h"
#include "cgc_stdlib.h"

/* Get some more memory through allocate */
static int cgc_allocate_new_blk(void)
{
  void *ret;
  struct blk_t *new_blk;
  cgc_size_t size = NEW_CHUNK_SIZE;

  if (cgc_allocate(size, 0, &ret) != 0) {
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

  cgc_insert_into_flist(new_blk);
  return 0;
}

/* Find first fit block for a size */
static int cgc_find_fit(cgc_size_t size, struct blk_t **blk)
{
  int sc_i = cgc_get_size_class(size);

  for (; sc_i < NUM_FREE_LISTS; sc_i++) {
    *blk = cgc_free_lists[sc_i];
    for(; *blk != NULL; *blk = (*blk)->fsucc)
      if ((*blk)->size >= size)
        return sc_i;
  }

  *blk = NULL;
  return -1;
}

static void *cgc_malloc_huge(cgc_size_t size)
{
    void *mem;
    size += HEADER_PADDING;
    if (cgc_allocate(size, 0, &mem) != 0)
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

void *cgc_malloc(cgc_size_t size)
{
  if (size == 0)
    return NULL;

  if (size + HEADER_PADDING >= NEW_CHUNK_SIZE)
    return cgc_malloc_huge(size);

  if (size % ALIGNMENT != 0)
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

  if (size >= 0x80000000)
    return NULL;
  size += HEADER_PADDING;

  struct blk_t *blk = NULL;
  int sc_i = cgc_find_fit(size, &blk);

  /* Allocate a new block if no fit */
  if (blk == NULL) {
    if (cgc_allocate_new_blk() != 0) {
      return NULL;
    } else {
      sc_i = NUM_FREE_LISTS - 1;
      blk = cgc_free_lists[sc_i];
    }
  }

  /* Remove the block we're going to use from the free list */
  cgc_remove_from_flist(blk);

  /* Split the block into two pieces if possible */
  cgc_size_t sdiff = blk->size - size;
  if (sdiff > 2 * HEADER_PADDING) {
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
    cgc_insert_into_flist(nb);
  }

  return (void *)((intptr_t)blk + HEADER_PADDING);
}
