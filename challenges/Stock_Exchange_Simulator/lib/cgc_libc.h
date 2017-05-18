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
typedef unsigned int uint32_t;


/**
 * Send all characters in buffer
 *
 * @param buf Buffer
 * @param len Length of buffer
 * @return OK on error, errno on failure
 */
int send_all(char * buf, cgc_size_t len);

/**
 * Copy between buffers
 *
 * @param src Source buffer
 * @param dst Destination buffer
 * @param l Number of bytes to copy
 */
void cgc_memcpy(void *src, void *dst, cgc_size_t l);

/**
 * Transmit all bytes in buffer
 *
 * @param buf Source buffer
 * @param s Bytes to send
 * @return OK on success, errno on failure
 */
int cgc_transmit_all(void *buf, cgc_size_t s);

/**
 * Compare two buffers
 *
 * @param l First buffer
 * @param r Second buffer
 * @param s Number of bytes to compare
 * @param OK on match, errno on failure
 */
int cgc_memcmp(void *l, void *r, cgc_size_t s);

/**
 * Receive set number of bytes
 *
 * @param size Number fo bytes to receive
 * @param buf Buffer to receive into
 * @return OK on success, errno on failure
 */
int cgc_recv_all(const cgc_size_t size, void *buf);

/**
 * Find length of C-String
 *
 * @param s String
 * @return Length of string, maximum 65535
 */
cgc_size_t cgc_strlen(char * s);

/**
 * Clear buffer
 *
 * @param l Buffer
 * @param s Size of buffer
 */
void cgc_memclr(void *l, cgc_size_t s);
#endif
