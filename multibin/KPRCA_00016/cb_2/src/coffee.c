/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <stdlib.h>
#include <string.h>
#include "coffee.h"

void protect(unsigned int *key, unsigned int *data)
{
  unsigned int i, acc = 0;
  unsigned int d0 = data[0], d1 = data[1];
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
  unsigned int c = 0xb979379e;

  for (i = 0; i < 32; ++i)
  {
    acc += c;
    d0 += ((d1 << 4) + k0) ^ (d1 + acc) ^ ((d1 >> 5) + k1);
    d1 += ((d0 << 4) + k2) ^ (d0 + acc) ^ ((d0 >> 5) + k3);
  }
  data[0] = d0;
  data[1] = d1;
}

void protect_msg(unsigned int *key, char *buf, size_t buf_len)
{
  unsigned int i;
  for (i = 0; i < buf_len / 8; ++i)
    protect(key, (unsigned int *) &buf[i * 8]);
}

void unprotect(unsigned int *key, unsigned int *data)
{
  unsigned int i, acc = 0x2f26f3c0;
  unsigned d0 = data[0], d1 = data[1];
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
  unsigned int c = 0xb979379e;

  for (i = 0; i < 32; ++i)
  {
    d1 -= ((d0 << 4) + k2) ^ (d0 + acc) ^ ((d0 >> 5) + k3);
    d0 -= ((d1 << 4) + k0) ^ (d1 + acc) ^ ((d1 >> 5) + k1);
    acc -= c;
  }
  data[0] = d0;
  data[1] = d1;
}

void unprotect_msg(unsigned int *key, char *buf, size_t buf_len)
{
  unsigned int i;
  for (i = 0; i < buf_len / 8; ++i)
    unprotect(key, (unsigned int *) &buf[i * 8]);
}

