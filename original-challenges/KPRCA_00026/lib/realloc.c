/*
 * Author: Garrett Barboza <garrett.barboza@kapricasecurity.com>
 *
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

#include "wrapper.h"
#include "libcgc.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void *realloc(void *ptr, size_t size)
{
  if (ptr == NULL)
    return malloc(size);

  if (size == 0) {
    free(ptr);
    return NULL;
  }

  struct blk_t *blk = (struct blk_t *)((intptr_t)ptr - HEADER_PADDING);
  if (size >= blk->size / 2 && size < blk->size - HEADER_PADDING)
      return ptr;

  void *new = malloc(size);
  if (new == NULL)
    return NULL;

  if (size < blk->size - HEADER_PADDING)
    memcpy(new, ptr, size);
  else
    memcpy(new, ptr, blk->size - HEADER_PADDING);

  free(ptr);
  return new;
}
