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

#ifndef BLOOMY_H
#define BLOOMY_H

#include "cgc_stdint.h"

typedef uint32_t (*hash_t) (const char *, cgc_size_t);
typedef struct cgc_bloomy {
  uint8_t *bits;
  cgc_size_t size;
  hash_t hashes[3];
} bloomy_t;

bloomy_t* cgc_bloomy_new(cgc_size_t size, hash_t hash1, hash_t hash2, hash_t hash3);
void cgc_bloomy_free(bloomy_t *bloomy);
int cgc_bloomy_check(bloomy_t *bloomy, const char *buf);
void cgc_bloomy_add(bloomy_t *bloomy, const char *buf);

#endif
