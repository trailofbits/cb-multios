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

#include <libcgc.h>

#include "libc.h"
#include "list.h"

struct chunk {
    size_t header;
    struct list_node list;
} __attribute__((packed));

static size_t size_class_sizes[] = {
    16, 32, 64, 128, 256, 512, 1024, 2048
};

#define NUM_SIZE_CLASSES (sizeof(size_class_sizes) / sizeof(size_t))

static struct list freelists[NUM_SIZE_CLASSES] = {};

#define ALIGN(x, a) (((x) + (a - 1)) & ~(a - 1))
#define IS_PAGE_ALIGNED(a) ((((size_t)a) & (PAGE_SIZE - 1)) == 0)
#define CHUNK_OVERHEAD (2 * sizeof(size_t))
#define MIN_SIZE (size_class_sizes[0])
#define MAX_SIZE (PAGE_SIZE - 1)
#define SIZE_CLASS_INDEX(size) (log_base_two(size) - log_base_two(MIN_SIZE))

#define CHUNK_SIZE(chunk) ((chunk)->header & ~1)
#define IS_ALLOCATED(chunk) ((chunk)->header & 1)
#define FOOTER(chunk) ((size_t *)((char *)chunk + CHUNK_SIZE(chunk) - sizeof(size_t)))
#define NEXT_CHUNK(chunk) ((struct chunk *)((char *)chunk + CHUNK_SIZE(chunk)))
#define PREV_SIZE(chunk) (CHUNK_SIZE(((struct chunk *)((size_t *)chunk - 1))))
#define PREV_CHUNK(chunk) ((struct chunk *)((char *)chunk - PREV_SIZE(chunk)))

static inline unsigned int
log_base_two(unsigned int x)
{
    unsigned long ret = 0;
    while (x >>= 1)
        ret++;
    return ret;
}

static inline void *
chunk_to_ptr(struct chunk *chunk)
{
    return (char *)chunk + OFFSETOF(struct chunk, list);
}

static inline struct chunk *
ptr_to_chunk(void *ptr)
{
    return CONTAINEROF(struct chunk, list, ptr);
}

static void
mark_allocated(struct chunk *chunk)
{
    chunk->header |= 1;
    *FOOTER(chunk) = chunk->header;
}

static void
mark_free(struct chunk *chunk)
{
    chunk->header &= ~1;
    *FOOTER(chunk) = chunk->header;
}

static int
find_fit(const struct list_node *chunk_, void *size_)
{
    size_t size = (size_t)size_;
    struct chunk *chunk = list_entry(struct chunk, list, chunk_);

    return CHUNK_SIZE(chunk) >= size;
}

static int
size_cmp(const struct list_node *a_, const struct list_node *b_)
{
    const struct chunk *a = list_entry(struct chunk, list, a_);
    const struct chunk *b = list_entry(struct chunk, list, b_);

    return CHUNK_SIZE(b) - CHUNK_SIZE(a);
}

static void *
allocate_large_chunk(size_t size)
{
    struct chunk *chunk;

    if (allocate(size, 0, (void **)&chunk) != 0)
        return NULL;

    chunk->header = size;
    mark_allocated(chunk);

    return chunk_to_ptr(chunk);
}

static struct chunk *
grow_heap(void)
{
    struct chunk *chunk;

    if (allocate(PAGE_SIZE, 0, (void **)&chunk) != 0)
        return NULL;

    chunk->header = PAGE_SIZE;
    mark_free(chunk);

    return chunk;
}

static struct chunk *
split_chunk(struct chunk *chunk, size_t size)
{
    struct chunk *new = (struct chunk *)((char *)chunk + size);
    size_t orig_size = CHUNK_SIZE(chunk);

    if (CHUNK_SIZE(chunk) <= size + MIN_SIZE)
        return chunk;

    chunk->header = size;
    mark_allocated(chunk);

    new->header = orig_size - size;
    mark_allocated(new);
    free(chunk_to_ptr(new));

    return chunk;
}

static struct chunk *
coalesce(struct chunk *chunk)
{
    struct chunk *next = NULL, *prev = NULL;
    unsigned int size_class;

    if (!IS_PAGE_ALIGNED(chunk))
        prev = PREV_CHUNK(chunk);

    if (!IS_PAGE_ALIGNED(NEXT_CHUNK(chunk)))
        next = NEXT_CHUNK(chunk);

    if (prev && !IS_ALLOCATED(prev)) {
        size_class = SIZE_CLASS_INDEX(CHUNK_SIZE(prev));
        if (size_class < NUM_SIZE_CLASSES) {
            list_remove_entry(struct chunk, list, &freelists[size_class], prev);
            prev->header = CHUNK_SIZE(chunk) + CHUNK_SIZE(prev);
            mark_free(prev);

            chunk = prev;
        }
    }

    if (next && !IS_ALLOCATED(next)) {
        size_class = SIZE_CLASS_INDEX(CHUNK_SIZE(next));
        if (size_class < NUM_SIZE_CLASSES) {
            list_remove_entry(struct chunk, list, &freelists[size_class], next);
            chunk->header = CHUNK_SIZE(chunk) + CHUNK_SIZE(next);
            mark_free(chunk);
        }
    }

    return chunk;
}

void *
malloc(size_t size)
{
    struct chunk *chunk = NULL;
    unsigned int size_class;

    if (ALIGN(size, sizeof(size_t)) + CHUNK_OVERHEAD < size)
        return NULL;

    size = ALIGN(size, sizeof(size_t)) + CHUNK_OVERHEAD;

    if (size < MIN_SIZE)
        size = MIN_SIZE;

    if (size > MAX_SIZE)
        return allocate_large_chunk(size);

    size_class = SIZE_CLASS_INDEX(size);
    if (size_class >= NUM_SIZE_CLASSES)
        return NULL;

    while (chunk == NULL && size_class < NUM_SIZE_CLASSES)
        chunk = list_find_entry(struct chunk, list, &freelists[size_class++],
                find_fit, (void *)size);

    if (chunk == NULL)
        chunk = grow_heap();
    else
        list_remove_entry(struct chunk, list, &freelists[size_class - 1], chunk);

    mark_allocated(chunk);
    if (CHUNK_SIZE(chunk) > size)
        chunk = split_chunk(chunk, size);

    return chunk_to_ptr(chunk);
}

void
free(void *ptr)
{
    struct chunk *chunk = ptr_to_chunk(ptr);
    unsigned int size_class;

    if (ptr == NULL)
        return;

    mark_free(chunk);
    chunk = coalesce(chunk);

    size_class = SIZE_CLASS_INDEX(CHUNK_SIZE(chunk));
    if (size_class >= NUM_SIZE_CLASSES)
        size_class = NUM_SIZE_CLASSES - 1;

    list_insert_entry_in_order(struct chunk, list, &freelists[size_class],
            chunk, size_cmp);
}

void *
calloc(size_t size)
{
    void *ret = malloc(size);
    if (ret)
        memset(ret, '\0', size);
    return ret;
}

void *
realloc(void *ptr, size_t size)
{
    size_t orig_size;
    void *ret;

    if (ptr == NULL)
        return malloc(size);

    orig_size = CHUNK_SIZE(ptr_to_chunk(ptr)) - CHUNK_OVERHEAD;
    if (size == orig_size)
        return ptr;
   
    ret = malloc(size);
    memcpy(ret, ptr, MIN(size, orig_size));
    free(ptr);

    return ret;
}

