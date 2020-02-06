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
 * @file libc.h
 *
 * Reusable standard C functions.
 */

#ifndef LIBC_H_
#define LIBC_H_

#include "libcgc.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#define INT_MIN ((int)(0x80000000))

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
 * Read exactly n bytes from fd to a buffer.
 *
 * @param fd A file descriptor
 * @param buf The destination buffer
 * @param n The number of bytes to cgc_read
 * @return The number of bytes cgc_read, or negative on failure
 */
cgc_ssize_t cgc_read_all(int fd, void *buf, cgc_size_t n);

/**
 * Write exactly n bytes to an fd from a buffer.
 *
 * @param fd A file descriptor
 * @param buf The source buffer
 * @param n The number of bytes to cgc_write
 * @return The number of bytes written, or negative on failure
 */
cgc_ssize_t cgc_write_all(int fd, void *buf, cgc_size_t n);

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

/**
 * Set the first n bytes of a block of memory to a value.
 *
 * @param ptr_ A pointer to a block of memory
 * @param val The value to set each byte to, interpretted as an unsigned char
 * @param n The number of bytes to set
 * @return ptr
 */
void *cgc_memset(void *ptr_, int val, cgc_size_t n);

/**
 * Copy n bytes from src to dst.
 *
 * @param dst_ The destination buffer
 * @param src_ The source buffer
 * @param n The number of bytes to copy
 * @return dst
 */
void *cgc_memcpy(void *dst_, const void *src_, cgc_size_t n);

/**
 * Return the length of a null-terminated string.
 * 
 * @param s The string
 * @return The length of s
 */
cgc_size_t cgc_strlen(const char *s);

/* The following is verbatim from EAGLE_00004, but isn't included in the 
 * released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
 */
#ifdef DEBUG

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *cgc_stdin;
extern FILE *cgc_stdout;
extern FILE *cgc_stderr;

/**
 * Formatted output to a stream.
 *
 * @param stream The stream to cgc_write to
 * @param format The format specifier
 * @return number of bytes written
 */
int fprintf(FILE * stream, const char *format, ...);

/**
 * Formatted output to cgc_stdout.
 *
 * @param stream The stream to cgc_write to
 * @param format The format specifier
 * @return number of bytes written
 */
int cgc_printf(const char *format, ...);

#endif /* DEBUG */

#endif /* LIBC_H_ */

