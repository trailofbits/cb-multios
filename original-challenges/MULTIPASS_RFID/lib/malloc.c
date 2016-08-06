/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
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
#include <libcgc.h>
#include <stdint.h>

#include "malloc_internal.h"

static int allocate_span()
{
    void *mem;
    if (allocate(SPAN_SIZE << 1, 0, &mem) != 0)
        return 1;

    intptr_t span = ((intptr_t)mem + SPAN_SIZE-1) & ~(SPAN_SIZE-1);
    if (span - (intptr_t)mem)
        deallocate(mem, span - (intptr_t)mem);
    deallocate((void *)(span + SPAN_SIZE), ((intptr_t)mem + (SPAN_SIZE << 1)) - (span + SPAN_SIZE));
    
    free_block_t *block = (free_block_t *)span;
    block->hdr.size = SPAN_SIZE;
    block->hdr.free = 1;
    block->hdr.mmap = 0;
    block->next = g_malloc.free_list[NUM_BUCKETS-1];
    block->prev = NULL;
    g_malloc.free_list[NUM_BUCKETS-1] = block;
    return 0;
}

static free_block_t *pop_block(int i)
{
    free_block_t *blk = g_malloc.free_list[i];
    /* remove from current list */
    if (blk->next != NULL)
        blk->next->prev = blk->prev;
    if (blk->prev != NULL)
        blk->prev->next = blk->next;
    else
        g_malloc.free_list[i] = blk->next;

    blk->next = NULL;
    blk->prev = NULL;
    return blk;
}

void *malloc(size_t size)
{
    size_t min_size = size + OVERHEAD_BYTES;

    if (min_size >= MAX_ALLOC)
    {
        void *ret;
        if (allocate(min_size, 0, &ret) != 0)
            return NULL;
        block_t *block = (block_t *)ret;
        block->free = 0;
        block->mmap = 1;
        block->size = min_size;
        return (void *)((intptr_t)ret + OVERHEAD_BYTES);
    }

    /* use buddy allocator */
    int order;
    for (order = 0; min_size > (MIN_ALLOC << order); order++) ;

    /* find first free bucket */
    int i;
    for (i = order; i < NUM_BUCKETS && g_malloc.free_list[i] == NULL; i++) ;

    if (i == NUM_BUCKETS)
    {
        /* allocate new span */
        if (allocate_span() == 0)
            i = NUM_BUCKETS-1;
        else
            return NULL;
    }

    /* split block until it is the minimum size */
    for (; i > order; i--)
    {
        free_block_t *blk = pop_block(i);

        /* split block */
        blk->hdr.size >>= 1;
        free_block_t *blk2 = (free_block_t *)((intptr_t)blk ^ blk->hdr.size);
        *blk2 = *blk;

        /* add both to next list */
        blk->prev = NULL;
        blk->next = blk2;
        blk2->prev = blk;
        blk2->next = g_malloc.free_list[i-1];
        if (blk2->next)
            blk2->next->prev = blk2;
        g_malloc.free_list[i-1] = blk;
    }

    /* we are now guaranteed that g_malloc.free_list[order] != NULL */
    free_block_t *blk = pop_block(order);
    blk->hdr.free = 0;

    //printf("malloc(%d) = %08X\n", size, ((intptr_t)blk + OVERHEAD_BYTES));
    return (void *)((intptr_t)blk + OVERHEAD_BYTES);
}
