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
#include <stdlib.h>

#include "malloc_internal.h"

void free(void *mem)
{
    //printf("free(%08X)\n", mem);
    if (mem == NULL)
        return;
    free_block_t *block = (free_block_t *)((intptr_t)mem - OVERHEAD_BYTES);
    if (block->hdr.free != 0)
        _terminate(1);
    if (block->hdr.mmap)
    {
        deallocate(block, block->hdr.size);
        return;
    }

    block->hdr.free = 1;
    
    int order;
    for (order = 0; block->hdr.size > (MIN_ALLOC << order); order++) ;

    for (; order < NUM_BUCKETS-1; order++)
    {
        free_block_t *buddy = (free_block_t *)((intptr_t)block ^ block->hdr.size);
        //printf("\tbuddy = %08X, size = %d,%d\n", buddy, block->hdr.size, buddy->hdr.size);
        if (buddy->hdr.free == 0 || buddy->hdr.size != block->hdr.size)
            break;

        /* remove buddy from free list */
        if (buddy->prev == NULL)
            g_malloc.free_list[order] = buddy->next;
        else
            buddy->prev->next = buddy->next;
        if (buddy->next)
            buddy->next->prev = buddy->prev;

        if ((uintptr_t)buddy < (uintptr_t)block)
            block = buddy;
        block->hdr.size <<= 1;
    }

    block->next = g_malloc.free_list[order];
    if (block->next)
        block->next->prev = block;
    block->prev = NULL;
    g_malloc.free_list[order] = block;
}
