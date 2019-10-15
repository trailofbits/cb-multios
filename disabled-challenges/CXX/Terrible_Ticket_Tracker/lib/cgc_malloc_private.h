/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#ifndef MALLOC_PRIVATE_H_
#define MALLOC_PRIVATE_H_

#include "cgc_stdlib.h"
#include "cgc_stdint.h"

#define RUN_SIZE (1024 * 1024)
#define TINY_SIZE (4)
#define SMALL_SIZE (16)
#define LARGE_SIZE (128 * 1024)
#define MAX_SIZE ((unsigned int)INT_MAX)
#define NUM_SMALL_BINS (128)
#define NUM_TINY_BINS ((SMALL_SIZE / TINY_SIZE) - 1)
#define NUM_BINS (NUM_TINY_BINS + NUM_SMALL_BINS)
#define NUM_RUNS ((UINT_MAX / RUN_SIZE) + 1)

enum {
    MM_UNALLOCATED,
    MM_TINY,
    MM_SMALL,
    MM_LARGE
};

typedef struct {
    struct cgc_malloc_free *free_list[NUM_BINS];
    unsigned char mem_map[NUM_RUNS];

    /* tiny-specific metadata */
    struct tiny_page *tiny_pages[NUM_TINY_BINS];
    void *tiny_run;
    cgc_size_t tiny_offset;
} malloc_t;

typedef struct {
    union {
        cgc_size_t prev_size; /* small allocations */
        malloc_t *heap; /* large allocations */
    };
    cgc_size_t size_flags;
    char data[0];
} malloc_hdr_t;

typedef struct {
    int unused;
} small_run_t;

typedef struct tiny_page {
    unsigned short size;
    unsigned short offset;
} tiny_page_t;

typedef struct malloc_tiny_free {
    struct malloc_tiny_free *next;
} malloc_tiny_free_t;

typedef struct malloc_small_free {
    malloc_hdr_t hdr;
    struct malloc_small_free *prev, *next;
} malloc_small_free_t;

typedef struct cgc_malloc_free {
    union
    {
        malloc_tiny_free_t tiny;
        malloc_small_free_t small;
    };
} malloc_free_t;

malloc_t g_heap;

void *cgc_malloc_alloc(malloc_t *heap, cgc_size_t n);
void malloc_free(malloc_t *heap, void *ptr);
void *cgc_malloc_realloc(malloc_t *heap, void *ptr, cgc_size_t n);
cgc_size_t cgc_malloc_size(malloc_t *heap, void *ptr);

static inline int cgc_size_to_bin(cgc_size_t n)
{
    if (n < SMALL_SIZE)
        return (n / 4) - 1;
    else if (n <= 512)
        return NUM_TINY_BINS + (n / 16) - 1;
    else if (n <= 4096 + 512)
        return NUM_TINY_BINS + (512 / 16) + ((n - 512) / 128) - 1;
    else if (n <= LARGE_SIZE)
        return NUM_TINY_BINS + (512 / 16) + (4096 / 128) + ((n - 4096 - 512) / 2048) - 1;
    else
        return NUM_TINY_BINS + NUM_SMALL_BINS - 1;
}

#endif
