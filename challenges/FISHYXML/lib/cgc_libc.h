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

#ifndef LIBC_H
#define LIBC_H 1

#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_errno.h"
#include "cgc_memset.h"
#include "cgc_memcpy.h"
#include "cgc_send.h"
#include "cgc_recv_until_delim.h"
#include "cgc_pi_prng.h"
#include "cgc_strncpy.h"
#include "cgc_list.h"


#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#define PAGE_SIZE (1 << 12)

/**
 * Return the lesser of a and b
 * 
 * @param a The first value
 * @param b The second value
 * @return a if a < b else b
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * Return the greater of a and b
 *
 * @param a The first value
 * @param b The second value
 * @return a if a > b else b
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Find the offset of a struct member
 *
 * @param type The struct type to examine
 * @param member The member to calculate the offset of
 * @return The offset of member in type
 */
#define OFFSETOF(type, member) ((cgc_size_t)(&((type *)NULL)->member))

/**
 * Find the container structure from a pointer to a member.
 *
 * @param type The struct type to examine
 * @param member The member ptr points to
 * @param ptr A pointer to a member
 * @return A pointer to the containing structure
 */
#define CONTAINEROF(type, member, ptr) ({                               \
    char *__ptr = (char *)(ptr);                                        \
    __ptr ? ((type *)(__ptr - OFFSETOF(type, member))) : NULL;          \
})


/**
 * Allocate a chunk of memory on the heap.
 *
 * @param size The size of the chunk to allocate
 * @return A pointer to the new chunk, or NULL if allocation failed
 */
void *cgc_malloc(cgc_size_t size);

/**
 * Free a chunk of memory allocated with malloc().
 *
 * @param ptr The chunk to free
 */
void cgc_free(void *ptr);

/**
 * Allocate a zeroed chunk of memory on the heap.
 *
 * Note: This differs from standard libc malloc by taking the full size of the
 *      chunk to allocate as its only parameter.
 *
 * @param size The size of the chunk to allocate
 * @return A pointer to the new chunk, or NULL if allocation failed
 */
void *cgc_calloc(cgc_size_t size);

/**
 * Resize a chunk of memory allocated with malloc().
 *
 * @param ptr The chunk to resize
 * @param size The new size of the chunk
 * @return A pointer to the new chunk, or NULL if allocation failed
 */
void *cgc_realloc(void *ptr, cgc_size_t size);



#endif
