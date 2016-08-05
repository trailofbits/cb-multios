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
#include "list.h"
#include <cstring.h>

List::List(void)
{
  cap = MAX_WORKERS;
  size = 0;
}

bool List::Append(Support* s)
{
  if (size == cap)
    return false;

  data[size++] = s;
  return true;
}

Support* List::Get(uint32_t idx)
{
  if (idx >= size)
  {
    return nullptr;
  }

  return data[idx];
}

Support* List::Remove(uint32_t idx)
{
  if (idx >= size)
  {
    return nullptr;
  }

  Support *support = data[idx];
  if (idx < size - 1)
  {
    memmove(&(data[idx]), &(data[idx + 1]), (size - 1 - idx) * sizeof(idx));
  }

  data[size - 1] = nullptr;
  size--;
  return support;
}

uint32_t List::Length()
{
    return size;
}

