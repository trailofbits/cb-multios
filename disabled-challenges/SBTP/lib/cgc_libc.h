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

#include "libcgc.h"
#include "cgc_stdint.h"

#define stdin STDIN
#define stdout STDOUT
#define stderr STDERR

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif

#define va_start(al, lp) __builtin_va_start(al, lp)
#define va_end(al) __builtin_va_end(al)
#define va_arg(al, t) __builtin_va_arg(al, t)
#define va_copy(d, s) __builtin_va_copy(d, s)

#define NEWLINE '\n'
#define FMTCHAR '@'

#define ALLOCFAIL 128
#define DEALLOCFAIL 129
#define RANDFAIL 130
#define FDWAITFAIL 131
#define READFAIL 132
#define WRITEFAIL 133

#define INT_MAX 0x7fffffff
#define PAGE_SIZE 4096
#define FLAG_PAGE 0x4347C000

//#define DEBUG 1
#ifdef DEBUG
#define debug(args...) fdprintf(stderr,args)
#else
#define debug(args...)
#endif

/**
 * Exits with code c.
 *
 * @param c Exit code
 * @return Death.
 */
#define DIE(c) cgc__terminate(c)

/**
 * Allocate RW memory.
 *
 * @param s Amount of memory in bytes to allocate.
 * @param a Address to store pointer to new allocation at.
 * @return Address in a.
 */
#define ALLOCRW(s,a) if(allocate(s, 0, &a)) DIE(ALLOCFAIL)

/**
 * Allocate RWX memory.
 *
 * @param s Amount of memory in bytes to allocate.
 * @param a Address to store pointer to new allocation at.
 * @return Address in a.
 */
#define ALLOCRWX(s,a) if(cgc_allocate(s, 1, &a)) DIE(ALLOCFAIL)

/**
 * Deallocate memory.
 *
 * @param a Address of memory to dealloc.
 * @param s Amount of memory in bytes to dealloc.
 * @return Nothing
 */
#define DEALLOC(a,s) if(deallocate(a, s)) DIE(DEALLOCFAIL)

/**
 * Get random bytes.
 *
 * @param s Number of random bytes to return.
 * @param b Buffer to cgc_write random bytes to.
 * @return Bytes in b.
 */
#define RANDOM(s,b)  if(cgc_random(b, s, NULL)) DIE(RANDFAIL)

/**
 * Simple conversion for hex char
 *
 * @param i Number to convert to char
 * @return Char representation
 */
#define HEXC(i) ((i <= 9) ? '0' + i : 'A' - 10 + i)

/**
 * Read in data from stdin
 *
 * @param s struct to cgc_read into
 * @return 1 on success, 0 on failure
 */
#define READDATA(s) (sizeof(s) == cgc_readall(stdin,(char *)&s,sizeof(s)) ? 1 : 0)

/**
 * Send data to stdout
 *
 * @param s struct to cgc_write
 * @return 1 on success, 0 on failure
 */
#define SENDDATA(s) (sizeof(s) == cgc_sendall(stdout,(char *)&s,sizeof(s)) ? 1 : 0)

/**
 * Send a string to stdout
 *
 * @param s string to cgc_write
 * @return 1 on success, 0 on failure
 */
#define SENDSTR(s) (cgc_strlen(s) == sendall(stdout,s,cgc_strlen(s)) ? 1 : 0)

/**
 * Send a string followed by newline to stdout
 *
 * @param s string to cgc_write
 * @return 1 on success, 0 on failre
 */
#define SENDLINE(s) (SENDSTR(s) && SENDSTR("\n"))

/**
 * Length of an array, in number of elements
 * @param x array
 * @return sizeof_array(array)
 */
#define SIZEOFARR(x) (sizeof(x)/sizeof(x[0]))

/**
 * Read until NEWLINE is hit
 *
 * @param fd File descriptor to cgc_read from.
 * @param buf Buffer to cgc_write cgc_read bytes to.
 * @param s Maximum number of bytes to cgc_read
 * @return Number of bytes cgc_read
 */
cgc_size_t cgc_readline(int fd, char *buf, cgc_size_t s);

/**
 * Attempt to cgc_read a fixed number of bytes
 *
 * @param fd File descriptor to cgc_read from.
 * @param buf Buffer to cgc_write cgc_read bytes to.
 * @param s Maximum number of bytes to cgc_read
 * @return Number of bytes cgc_read 
 */
cgc_size_t cgc_readall(int fd, char *buf, cgc_size_t s);

/**
 * Attempt to send a fixed number of bytes
 *
 * @param fd File descriptor to cgc_write to
 * @param buf Buffer to cgc_read bytes from
 * @param s Number of bytes to send
 * @return Number of bytes sent.
 */
cgc_size_t cgc_sendall(int fd, char *buf, cgc_size_t s);

/**
 * Set memory to value.
 *
 * @param s Buffer to set
 * @param c Character to set buffer to
 * @param n Number of bytes to set
 * @return Pointer to buffer
 */
void *cgc_memset(void *s, int c, cgc_size_t n);

/**
 * Compare two strings for equality.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Non-zero if equal, zero if not equal.
 */
int cgc_streq(char *s1, char *s2);

/**
 * Get string length.
 *
 * @param s1 Input string.
 * @return Length of string, not including NULL terminator..
 */
int cgc_strlen(const char *s); 

/**
 * Format string and store in buffer
 *
 * @param buf Dest buffer
 * @param fmt Format string
 * @param ... Additional format arguments
 * @return None.
 */
void cgc_sprintf(char *buf, const char *fmt, ...); 

/**
 * Format string and store in buffer
 *
 * @param buf Dest buffer
 * @param fmt Format string
 * @param argp Additional format arguments
 * @return None.
 */
void cgc_vsprintf(char *buf, const char *fmt, va_list argp); 

/**
 * Print things to stdout.
 *
 * @param fmt Format string
 * @param ... Additional format arguments
 * @return None.
 */
void cgc_printf(const char *fmt, ...); 

/**
 * Print things to file descriptor.
 *
 * @param fd File descriptor to print to.
 * @param fmt Format string
 * @param ... Additional format arguments
 * @return None.
 */
void cgc_fdprintf(int fd, const char *fmt, ...);

/**
 * Print things to file descriptor.
 *
 * @param fd File descriptor to print to.
 * @param fmt Format string
 * @param argp Additional format arguments
 * @return None.
 */
void cgc_vfdprintf(int fd, const char *fmt, va_list argp); 

/**
 * Tokenize string
 *
 * @param s1 Input string.
 * @param sep Seperator to tokenize off of
 * @return Next token in string.
 */
char *cgc_strtok(char *s, char sep); 

/**
 * String copy
 *
 * @param s1 dst
 * @param s2 src
 * @return None.
 */
void cgc_strcpy(char *s1, const char *s2); 

/**
 * String to int
 * @param s String to convert to int
 * @return Integer value
 */
unsigned int cgc_atoi(char *s);

/**
 * String cat
 *
 * @param dest dest
 * @param src src
 * @return None.
 */
char * cgc_strcat(char *dest, const char *src);

/**
 * Memory copy
 *
 * @param dest dest
 * @param src src
 * @param len length
 * @return None.
 */
void cgc_memcpy(void *dest, void *src, cgc_size_t len); 

/**
 * Check if two buffers are equal
 *
 * @param b1 first buffer
 * @param b2 second buffer
 * @param len length
 * @return 0 if not equal, 1 if equal
 */
int cgc_memeq(void *b1, void *b2, cgc_size_t len);
#endif
