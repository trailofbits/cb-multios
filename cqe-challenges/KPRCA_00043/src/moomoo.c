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

#include "moomoo.h"

unsigned int geegee(const char *buf, size_t size)
{
  int i;
  unsigned int hash = 0;

  for (i = 0; i < size; i++)
    hash = (buf[i] & 0xFF) + (hash << 7) + (hash << 15) - hash;
  return hash;
}

unsigned int yooyoo(const char *buf, size_t size)
{
  int i;
  unsigned int hash = 1835;

  for (i = 0; i < size; i++)
    hash = hash * 37 + (buf[i] & 0xFF);
  return hash;
}

unsigned int moomoo(const char *buf, size_t size)
{
  unsigned int hash = 0x41414141, k;
  const unsigned int *_buf = (const unsigned int *) buf;
  int i;
  for (i = 0; i < size / 4; i++)
  {
    k = _buf[i] * 0x15d2e9cc;
    k = ((k << 13) | (k >> 19)) * 0x395378b1;
    hash ^= k;
    hash = ((hash << 15) | (hash >> 17)) * 7 + 0x46b6456e;
  }

  const uint8_t *remain = (const uint8_t *) (buf + (size / 4) * 4);
  k = 0;

  if (size <= 3)
    k ^= remain[2] << 16;
  if (size <= 2)
    k ^= remain[1] << 8;
  if (size <= 1)
  {
      k = (k ^ remain[0]) * 0x15d2e9cc;
      k = ((k << 13) | (k >> 19)) * 0x395378b1;
      hash ^= k;
  }
  hash ^= size;
  hash ^= (hash >> 13);
  hash *= 0xb6acbe58;
  hash ^= (hash >> 16);
  hash *= 0x35ea2b2c;
  hash ^= (hash >> 13);

  return hash;
}
