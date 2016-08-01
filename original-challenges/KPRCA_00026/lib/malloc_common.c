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

#include "wrapper.h"
#include "libcgc.h"
#include "malloc.h"
#include "stdlib.h"

#ifdef FILAMENTS
mutex_t malloc_mutex;
#endif

size_t size_class_limits[NUM_FREE_LISTS] = {
  2, 3, 4, 8,
  16, 24, 32, 48,
  64, 96, 128, 192,
  256, 384, 512, 768,
  1024, 1536, 2048, 3072,
  4096, 6144, 8192, 12288,
  16384, 24576, 32768, 49152,
  65536, 98304, 131072, INT32_MAX
};

struct blk_t *free_lists[NUM_FREE_LISTS] = {0};

static void remove_from_blist(struct blk_t *blk)
{
  if (blk->prev)
    blk->prev->next = blk->next;

  if (blk->next)
    blk->next->prev = blk->prev;
}

int get_size_class(size_t size)
{
  int i;
  for (i = 0; i < NUM_FREE_LISTS && size > size_class_limits[i]; i++);
  return i;
}


void insert_into_flist(struct blk_t *blk)
{
  int sc_i = get_size_class(blk->size);
  blk->free = 1;

  if (free_lists[sc_i] == NULL) {
    free_lists[sc_i] = blk;
    return;
  }

  blk->fsucc = free_lists[sc_i];
  free_lists[sc_i]->fpred = blk;
  free_lists[sc_i] = blk;
  blk->fpred = NULL;
}

void remove_from_flist(struct blk_t *blk)
{
  int sc_i = get_size_class(blk->size);

  if (blk->fpred)
    blk->fpred->fsucc = blk->fsucc;

  if (blk->fsucc)
    blk->fsucc->fpred = blk->fpred;

  if (free_lists[sc_i] == blk)
    free_lists[sc_i] = blk->fsucc;

  blk->fsucc = NULL;
  blk->fpred = NULL;
  blk->free = 0;
}

void coalesce(struct blk_t *blk)
{
  /* prev and next are free */
  if (blk->prev && blk->prev->free && blk->next && blk->next->free) {
    remove_from_flist(blk->prev);
    remove_from_flist(blk->next);
    remove_from_flist(blk);

    blk->prev->size += blk->size;
    blk->prev->size += blk->next->size;
    remove_from_blist(blk->next);
    remove_from_blist(blk);

    insert_into_flist(blk->prev);
  /* Just prev is free */
  } else if (blk->prev && blk->prev->free) {
    remove_from_flist(blk->prev);
    remove_from_flist(blk);

    blk->prev->size += blk->size;
    remove_from_blist(blk);

    insert_into_flist(blk->prev);
  /* Just next is free */
  } else if (blk->next && blk->next->free) {
    remove_from_flist(blk->next);
    remove_from_flist(blk);

    blk->size += blk->next->size;
    remove_from_blist(blk->next);

    insert_into_flist(blk);
  }
}
