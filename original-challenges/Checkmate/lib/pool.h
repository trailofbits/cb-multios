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

#ifndef POOL_H_
#define POOL_H_

#include "bitset.h"

struct pool {
    size_t size;
    struct chunk *head;
};

/**
 * Initialize a fixed-size pool allocator with the given size
 *
 * @param pool The pool to initialize
 * @param size The size of the pool
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int pool_init(struct pool *pool, size_t size);

/**
 * Destroy a fixed-size pool allocator and free all chunks
 *
 * @param pool The pool to destroy
 */
void pool_destroy(struct pool *pool);

/**
 * Allocate a chunk from a pool
 *
 * @param pool The pool to allocate from
 * @return A pointer to a new chunk
 */
void *pool_alloc(struct pool *pool);

/**
 * Free a chunk back into a pool
 *
 * @param pool The pool to return the memory to
 * @param ptr The chunk to free
 */
void pool_free(struct pool *pool, void *ptr);

/**
 * Return all memory to a pool
 *
 * @param pool The pool to free
 */
void pool_free_all(struct pool *pool);

#endif /* POOL_H_ */

