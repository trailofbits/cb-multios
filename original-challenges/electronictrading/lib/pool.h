/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
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
/**
 * @file pool.h
 *
 * Functions for allocating memory from a fixed-size pool
 */

#ifndef POOL_H_
#define POOL_H_

#include "list.h"

typedef unsigned long uintptr_t;
#define PAGE_SIZE (1 << 12)

struct freeblk;

struct pool {
    size_t size;
    LIST_OF(struct freeblk) freelist;
};

/**
 * Initialize a memory pool with a given size.
 *
 * @param pool The memory pool
 * @param size The size of each chunk allocated from the pool
 */
void pool_init(struct pool *pool, size_t size);

/**
 * Destroy a memory pool, reclaiming memory where possible.
 *
 * @param pool The memory pool
 * return 0 on success, negative on error
 */
int pool_destroy(struct pool *pool);

/**
 * Allocate a chunk from a pool
 *
 * @param pool The memory pool
 * @return The address of the newly allocated chunk
 */
void *pool_alloc(struct pool *pool);

/**
 * Free a chunk, returning to a pool
 *
 * @param pool The memory pool
 * @param addr The chunk to free
 */
void pool_free(struct pool *pool, void *addr);

#endif /* POOL_H_ */

