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

#ifndef MALLOC_COMMON_H
#define MALLOC_COMMON_H

#include <stdint.h>
#include <mutex.h>

#define NUM_FREE_LISTS 32
#define HEADER_PADDING 24
#define NEW_CHUNK_SIZE 262144
#define ALIGNMENT 32

#ifdef FILAMENTS
    extern mutex_t malloc_mutex;
#endif

extern struct blk_t *free_lists[NUM_FREE_LISTS];
extern size_t size_class_limits[NUM_FREE_LISTS];

struct blk_t {
  size_t size;
  unsigned int free;
  struct blk_t *fsucc;
  struct blk_t *fpred;
  struct blk_t *next;
  struct blk_t *prev;
};

void coalesce(struct blk_t *);
int get_size_class(size_t size);
void insert_into_flist(struct blk_t *blk);
void remove_from_flist(struct blk_t *blk);

#endif /* MALLOC_COMMON_H */
