/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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
#include "vector.h"

vector::vector(int c)
{
  if (c == 0)
  {
    cap = 64;
  }
  else
  {
    cap = c;
  }

  len = 0;
  data = (void **)calloc(cap, sizeof(void *));
}

bool vector::set(int idx, void* datum)
{
  if (idx >= len)
  {
    return false;
  }

  data[idx] = datum;
  return true;
}

int vector::length(void)
{
  return len;
}

void vector::remove(int idx)
{
  for (int i = idx + 1; i < len; ++i)
  {
    data[idx - 1] = data[idx];
  }

  data[len - 1] = nullptr;
  len--;
}

bool vector::contains(void* e)
{
  for (int idx = 0; idx < len; ++idx)
  {
    if (get(idx) == e)
    {
      return true;
    }
  }

  return false;
}

void* vector::get(int idx)
{
#ifdef PATCHED_1
  if (idx >= len || idx < 0)
#else
  if (idx >= len)
#endif
  {
    return nullptr;
  }

  return data[idx];
}

void vector::add(void* datum)
{
  if (len == cap)
  {
    data = (void **)realloc(data, cap * 2 * sizeof(void *));
    cap *= 2;
  }

  data[len++] = datum;
}

int vector::index_of(void* e)
{
  for (int idx = 0; idx < len; ++idx)
  {
    if (data[idx] == e)
    {
      return idx;
    }
  }

  return NOT_FOUND;
}
