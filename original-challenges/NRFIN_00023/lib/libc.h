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

/**
 * Return the greater of the two parameters.
 *
 * @param a The first value
 * @param b The second value
 * @return The greater of a and b
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b));

/**
 * Return the lesser of the two parameters.
 *
 * @param a The first value
 * @param b The second value
 * @return The lesserof a and b
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b));

/**
 * Read exactly n bytes from fd to a buffer.
 *
 * @param fd A file descriptor
 * @param buf The destination buffer
 * @param n The number of bytes to read
 * @return The number of bytes read, or negative on failure
 */
ssize_t read_all(int fd, void *buf, size_t n);

/**
 * Write exactly n bytes to an fd from a buffer.
 *
 * @param fd A file descriptor
 * @param buf The source buffer
 * @param n The number of bytes to write
 * @return The number of bytes written, or negative on failure
 */
ssize_t write_all(int fd, void *buf, size_t n);

/**
 * Set the first n bytes of a block of memory to a value.
 *
 * @param ptr A pointer to a block of memory
 * @param val The value to set each byte to, interpretted as an unsigned char
 * @param n The number of bytes to set
 * @return ptr
 */
void *memset(void *ptr, int val, size_t n);

/**
 * Copy a null-terminated string from src to dst.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @return dst
 */
char *strcpy(char *dst, const char *src);

/**
 * Copy at most the first n characters of a null-terminated string from src to
 * dst.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @param n The maximum number of bytes to copy
 * @return dst
 */
char *strncpy(char *dst, const char *src, size_t n);

/**
 * Append the bytes of a null-terminated string to another.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @return dst
 */
char *strcat(char *dst, const char *src);

/**
 * Append at most the first n bytes of a null-terminated string to another.
 *
 * @param dst The destination buffer
 * @param src The source buffer
 * @param n The maximum number of bytes to copy
 * @return dst
 */
char *strncat(char *dst, const char *src, size_t n);

/**
 * Return the length of a null-terminated string.
 * 
 * @param s The string
 * @return The length of s
 */
size_t strlen(const char *s);

/**
 * Return the length of a null-terminated string, checking at most n bytes.
 *
 * @param s The string
 * @param n Maximum number of bytes to check
 * @return The lesser of the length of s or n
 */
size_t strnlen(const char *s, size_t n);

/**
 * Compare the first n bytes of two null-terminated strings
 *
 * @param a The first string
 * @param b The second string
 * @return negative if a < b, 0 if a == b, positive if a > b
 */
int strncmp(const char *a, const char *b, size_t n);

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
char *itoa(int val, char *s);

#ifdef DEBUG
/* The following is verbatim from EAGLE_00004, but isn't included in the 
 * released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
 */

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/**
 * Formatted output to a stream.
 *
 * @param stream The stream to write to
 * @param format The format specifier
 * @return number of bytes written
 */
int fprintf(FILE * stream, const char *format, ...);

#endif /* DEBUG */

#endif /* LIBC_H_ */
