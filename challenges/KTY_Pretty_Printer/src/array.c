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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_array.h"
#include "cgc_kty.h"

#define UINT_MAX 4294967295

array_t* cgc_array_create(int size, free_element_fn *fptr)
{
  array_t *arr = (array_t *) cgc_malloc(sizeof(array_t));
  if (arr == NULL || fptr == NULL)
    goto fail;
  arr->free_element = fptr;
  arr->length = 0;
  arr->size = size > 0 ? size : 16;
  arr->arr = (void **) cgc_malloc(sizeof(void *) * arr->size);
  if (arr->arr == NULL)
    goto fail;
  return arr;

fail:
  if (arr)
  {
    if (arr->arr)
      cgc_free(arr->arr);
    cgc_free(arr);
  }
  return NULL;
}

int cgc__array_double_size(array_t *arr)
{
  void **tmp;
  if (arr->size > (UINT_MAX / 2) / sizeof(void *))
    return -1;
  tmp = (void **) cgc_realloc(arr->arr, arr->size * 2 * sizeof(void *));
  if (tmp == NULL)
    return -1;
  arr->arr = tmp;
  arr->size *= 2;
  return 0;
}

int cgc_array_append(array_t *arr, void *e)
{
  int i;
  if (arr && e)
  {
    if (arr->size == arr->length && cgc__array_double_size(arr) != 0)
      return -1;
    arr->arr[arr->length] = e;
    arr->length++;
    return 0;
  }
  return -1;
}

void* cgc_array_get(array_t *arr, int idx)
{
  if (arr && idx < arr->length)
    return arr->arr[idx];
  return NULL;
}

int cgc_array_length(array_t *arr)
{
  if (arr)
    return arr->length;
  return 0;
}

void cgc_array_destroy(array_t *arr)
{
  int i;
  if (arr)
  {
    if (arr->arr)
    {
      for (i = 0; i < arr->length; ++i)
      {
        if (arr->arr[i])
          arr->free_element(arr->arr[i]);
      }
      cgc_free(arr->arr);
    }
    cgc_free(arr);
  }
}
