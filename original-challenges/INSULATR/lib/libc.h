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
#define LIBC_H

#include <libcgc.h>

//#define DEBUG 1

#define SUCCESS 0
#define ERRNO_RECV 32
#define ERRNO_TRANSMIT 33

#define ERRNO_MALFORMED_JSON 36
#define ERRNO_NUMBER_TOO_LARGE 37
#define ERRNO_NON_DECIMAL_IN_CONVERSION 38

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int 
#define uint64_t unsigned long long 

#define MAX_UINT8 0xff
#define MAX_UINT32 0xffffffff

// Fragmentation related
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes);
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes);

/**
 * Set a buffer to provided character
 *
 * @param dst Destination buffer
 * @param c Character to repeat
 * @param n Number of times to copy character
 * @return dst
 */
void * memset(void *dst, char c, size_t n); 

/**
 * Convert unsigned integer to string
 *
 * @param str_buf Destination buffere
 * @param buf_size Destination buffer size
 * @param i Integer to convert
 * @return Ascii-representation of i in str_buf
 */
int uint2str32(char* str_buf, int buf_size, uint32_t i);

/**
 * Compare two buffers
 *
 * @param a First buffer
 * @param b Second buffer
 * @param n Number of bytes to compare
 * @return -1 if not equal, 0 if equal
 */
int memcmp(void *a, void *b, size_t n);

/**
 * Convert string to signed integer
 *
 * @param str_buf Source buffer
 * @return integer
 */
int str2unt32n(const char* str_buf, uint32_t max_chars, uint64_t max_val, uint32_t *out);

/**
 * Copy a string with bounds checking
 *
 * @param s1 Destination buffer
 * @param s2 Source buffer
 * @param n Size of destination buffer
 * @return Number of bytes copied
 */
size_t strncpy(char *s1, char *s2, size_t n);

/**
 * Locate character in string
 *
 * @param str String to search
 * @param h Character to find
 * @return Pointer to character in string, or NULL
 */
char * strnchr(char *str, char c, uint32_t n); 

// *
//  * Tokenize string. Loosely based on strtok.
//  *
//  * @param s String to tokenize, or NULL to continue with previous one
//  * @param sep Character to sep on
//  * @return Pointer to next string, or NULL
 
// char * strntok(char *s, char sep, uint32_t n); 

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////
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

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int fprintf(FILE * stream, const char *format, ...);

#endif
// ^ DEBUG

#endif
// ^ LIBC_H

