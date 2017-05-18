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

#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#include "cgc_bloomy.h"

bloomy_t* cgc_bloomy_new(cgc_size_t size, hash_t hash1, hash_t hash2, hash_t hash3)
{
  bloomy_t *bloomy;

  if (size < 1)
    return NULL;

  bloomy = (bloomy_t *) cgc_malloc(sizeof(bloomy_t));
  if (bloomy == NULL)
    goto fail;
  cgc_memset(bloomy, 0, sizeof(bloomy_t));
  bloomy->size = size;

  bloomy->bits = (uint8_t *) cgc_malloc(size);
  if (bloomy->bits == NULL)
    goto fail;
  cgc_memset(bloomy->bits, 0, size);

  bloomy->hashes[0] = hash1;
  bloomy->hashes[1] = hash2;
  bloomy->hashes[2] = hash3;

  return bloomy;

fail:
  cgc_bloomy_free(bloomy);
  return NULL;
}

void cgc_bloomy_free(bloomy_t *bloomy)
{
  if (bloomy)
  {
    if (bloomy->bits)
      cgc_free(bloomy->bits);
    cgc_free(bloomy);
  }
}

int cgc_bloomy_check(bloomy_t *bloomy, const char *buf)
{
  uint8_t bit;
  unsigned int i, n;
  if (bloomy == NULL || bloomy->bits == NULL)
    return -1;
  for (i = 0; i < sizeof(bloomy->hashes) / sizeof(hash_t); ++i)
  {
    if (bloomy->hashes[i])
    {
      n = (bloomy->hashes[i](buf, cgc_strlen(buf)) % bloomy->size);
      bit = (bloomy->bits[n/8] & (1 << (n%8)));
      if (!bit)
        return 0;
    }
  }
  return 1;
}

void cgc_bloomy_add(bloomy_t *bloomy, const char *buf)
{
  uint8_t bit;
  unsigned int i, n;

  for (i = 0; i < sizeof(bloomy->hashes) / sizeof(hash_t); ++i)
  {
    if (bloomy->hashes[i])
    {
      n = (bloomy->hashes[i](buf, cgc_strlen(buf)) % bloomy->size);
      bloomy->bits[n/8] |= (1 << (n%8));
    }
  }
}
