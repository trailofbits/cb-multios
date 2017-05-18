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
 * Read a line from fd to a buffer, caller responsible for freeing.
 *
 * @param fd A file descriptor
 * @param buf A pointer to be set to the destination buffer
 * @return The number of bytes cgc_read, or negative on failure
 */
cgc_ssize_t cgc_read_line(int fd, char **buf);

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
 * Move n bytes from src to dst.
 *
 * @param dst_ The destination buffer
 * @param src_ The source buffer
 * @param n The number of bytes to copy
 * @return dst
 */
void *cgc_memmove(void *dst_, const void *src_, cgc_size_t n);

/**
 * Compare n bytes from two buffers.
 *
 * @param a_ The first buffer
 * @param b_ The second buffer
 * @param n The number of bytes to compare
 * @return negative if a_ < b_, 0 if a_ == b_, positive if a_ > b_
 */
int cgc_memcmp(const void *a_, const void *b_, cgc_size_t n);

/**
 * Copy a null-terminated string from src to dst.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @return dst
 */
char *cgc_strcpy(char *dst, const char *src);

/**
 * Copy at most the first n characters of a null-terminated string from src to
 * dst.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @param n The maximum number of bytes to copy
 * @return dst
 */
char *cgc_strncpy(char *dst, const char *src, cgc_size_t n);

/**
 * Return the length of a null-terminated string.
 * 
 * @param s The string
 * @return The length of s
 */
cgc_size_t cgc_strlen(const char *s);

/**
 * Return the length of a null-terminated string, checking at most n bytes.
 *
 * @param s The string
 * @param n Maximum number of bytes to check
 * @return The lesser of the length of s or n
 */
cgc_size_t cgc_strnlen(const char *s, cgc_size_t n);

/**
 * Compare two null-terminated strings
 *
 * @param a The first string
 * @param b The second string
 * @return negative if a < b, 0 if a == b, positive if a > b
 */
int cgc_strcmp(const char *a, const char *b);

/**
 * Compare the first n bytes of two null-terminated strings
 *
 * @param a The first string
 * @param b The second string
 * @param n The number of bytes to compare
 * @return negative if a < b, 0 if a == b, positive if a > b
 */
int cgc_strncmp(const char *a, const char *b, cgc_size_t n);

/**
 * Append the bytes of a null-terminated string to another.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @return dst
 */
char *cgc_strcat(char *dst, const char *src);

/**
 * Append at most the first n bytes of a null-terminated string to another.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @param n The maximum number of bytes to copy
 * @return dst
 */
char *cgc_strncat(char *dst, const char *src, cgc_size_t n);

/**
 * Find the first instance of character c in s.
 *
 * @param s The string to search
 * @param c The character to find
 * @return A pointer to the first instance of c in s or NULL if not found
 */
char *cgc_strchr(const char *s, char c);

/**
 * Find the last instance of character c in s.
 *
 * @param s The string to search
 * @param c The character to find
 * @return A pointer to the last instance of c in s or NULL if not found
 */
char *cgc_strrchr(const char *s, char c);

/**
 * Break up a string into tokens separated by a character.
 *
 * NOTE: This differs from standard strtok by only accepting on delimiter
 * character.
 *
 * @param s The string to tokenize or NULL to continue, may be modified
 * @param d The delimeter character
 * @return The next token
 */
char *cgc_strtok(char *s, char d);

/**
 * Convert an unsigned integer value to a hex character.
 *
 * @param v The value to convert
 * @return A hex character representing v, or '\0' on failure
 */
char cgc_to_hex(unsigned char v);

/**
 * Convert a hex character to a nibble.
 *
 * @param c The character to convert
 * @return The nibble c represents, or 0 on failure.
 */
unsigned char cgc_to_bin(char c);

/**
 * Convert binary data to a hex string.
 *
 * @param dst The destination buffer, caller must ensure sufficient size
 * @param src_ The source buffer
 * @param n The number of bytes to convert
 * @return A pointer to the end of the converted hex string
 */
char *cgc_bin_to_hex(char *dst, const void *src_, cgc_size_t n);

/**
 * Convert a 8-byte hex string to a unsigned int
 *
 * @param s The string to convert
 * @return The integer s encodes
 */
unsigned int cgc_hex_to_uint(char *s);

/**
 * Convert an integer value to its decimal string representation.
 *
 * This functionality differs from itoa, primarily in only dealing with decimal
 * representations.
 *
 * @param val The value to convert
 * @param s The buffer to place the converted value, must be large enough to
 *      hold all digits
 * @return s
 */
char *cgc_itoa(int val, char *s);

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

