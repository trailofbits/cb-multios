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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "malloc_internal.h"

void *realloc(void *ptr, size_t size)
{
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
    {
        return malloc(size);
    }
    block_t *block = (block_t *)((intptr_t)ptr - OVERHEAD_BYTES);
    if (size > block->size/2 && size < block->size-OVERHEAD_BYTES)
    {
        //printf("realloc(%08X, %d) = %08X\n", ptr, size, ptr);
        return ptr;
    }
    void *newmem = malloc(size);
    if (newmem == NULL)
        return NULL;
    size_t tocopy = block->size-OVERHEAD_BYTES;
    if (tocopy > size)
        tocopy = size;
    memcpy(newmem, ptr, tocopy);
    free(ptr);
    //printf("realloc(%08X, %d) = %08X\n", ptr, size, newmem);
    return newmem;
}
