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

#include "cgc_stdlib.h"
#include "cgc_pool.h"

struct chunk {
    struct chunk *next;
    cgc_size_t size;
    unsigned int num_free;
    unsigned char *data;
    struct bitset allocated;
};

static int cgc_pool_grow(struct pool *);

int
cgc_pool_init(struct pool *pool, cgc_size_t size)
{
    if (size >= PAGE_SIZE - sizeof(struct chunk))
        return EXIT_FAILURE;

    pool->size = size;
    pool->head = NULL;
    
    return EXIT_SUCCESS;
}

void
cgc_pool_destroy(struct pool *pool)
{
    cgc_pool_free_all(pool);
    pool->size = 0;
}

void *
cgc_pool_alloc(struct pool *pool)
{
    struct chunk *chunk, *p;
    int index;

    if (!pool->head && cgc_pool_grow(pool) != EXIT_SUCCESS)
        return NULL;

    if (pool->head->num_free == 0) {
        for (p = pool->head, chunk = p->next; chunk != NULL; p = chunk, chunk = chunk->next)
            if (chunk->num_free != 0)
                break;

        if (chunk) {
            p->next = chunk->next;
            chunk->next = pool->head;
            pool->head = chunk;
        } else {
            if (cgc_pool_grow(pool) != EXIT_SUCCESS)
                return NULL;
        }
    }

    if ((index = cgc_bitset_find_first(&pool->head->allocated, 0)) == EXIT_FAILURE)
        return NULL;

    if (cgc_bitset_set_bit(&pool->head->allocated, index) == EXIT_FAILURE)
        return NULL;

    pool->head->num_free--;
    return &pool->head->data[pool->size * index];
}

void
cgc_pool_free(struct pool *pool, void *ptr)
{
    struct chunk *chunk;
    unsigned int index;

    chunk = ROUND_TO_PAGE(ptr);
    if (((unsigned char *)ptr - chunk->data) % chunk->size != 0)
        return;

    index = ((unsigned char *)ptr - chunk->data) / chunk->size;
    cgc_bitset_clear_bit(&chunk->allocated, index);
}

void
cgc_pool_free_all(struct pool *pool)
{
    struct chunk *chunk, *n;

    for (chunk = pool->head; chunk != NULL; chunk = n) {
        n = chunk->next;
        cgc_deallocate(chunk, PAGE_SIZE);
    }

    pool->head = NULL;
}

static int
cgc_pool_grow(struct pool *pool)
{
    struct chunk *chunk;

    if (cgc_allocate(PAGE_SIZE, 0, (void **)&chunk) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    chunk->next = pool->head;
    chunk->size = pool->size;

    chunk->num_free = (PAGE_SIZE - sizeof(struct chunk)) / pool->size;
    while ((ALIGN(chunk->num_free, 8) / 8) > (PAGE_SIZE - sizeof(struct chunk) - (pool->size * chunk->num_free)))
        chunk->num_free--;

    cgc_bitset_init(&chunk->allocated, chunk->num_free);
    chunk->data = (unsigned char *)chunk + sizeof(struct chunk) + (ALIGN(chunk->num_free, 8) / 8);

    pool->head = chunk;
    return EXIT_SUCCESS;
}
