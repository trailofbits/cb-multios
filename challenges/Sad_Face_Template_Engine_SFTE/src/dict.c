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
#include "cgc_dict.h"

dict_t** cgc_dict_new()
{
  return cgc_calloc(sizeof(dict_t *), TABLE_SIZE);
}

unsigned int cgc__hash(const char *str)
{
  unsigned int ret = 5419;
  if (str)
  {
    while (*str)
      ret = ((ret << 5) + (ret << 2) + ret) + *str++;
  }
  return ret % TABLE_SIZE;
}

void* cgc_dict_find(dict_t **dict, const char *name)
{
  dict_t *cur = dict[cgc__hash(name)];
  while (cur)
  {
    if (cgc_strcmp(cur->name, name) == 0)
      return cur->value;
    cur = cur->next;
  }
  return NULL;
}

void cgc_dict_insert(dict_t **dict, const char *name, void *value)
{
  unsigned int hash;
  dict_t *cur = cgc_dict_find(dict, name);
  if (cur == NULL)
  {
    cur = (dict_t *) cgc_malloc(sizeof(dict_t));
    if (cur == NULL)
      goto error;
    cur->name = cgc_strdup(name);
    if (cur->name == NULL)
      goto error;
    cur->value = value;
    hash = cgc__hash(name);
    cur->next = dict[hash];
    dict[hash] = cur;
  }
  return;

error:
  if (cur)
  {
    if (cur->name)
      cgc_free(cur->name);
    cgc_free(cur);
  }
}

void* cgc_dict_remove(dict_t **dict, const char *name)
{
  void *ret = NULL;
  unsigned int hash = cgc__hash(name);
  dict_t *cur = dict[hash], *prev = NULL;
  while (cur)
  {
    if (cgc_strcmp(cur->name, name) == 0)
    {
      if (prev == NULL)
        dict[hash] = cur->next;
      else
        prev->next = cur->next;
      ret = cur->value;
      cgc_free(cur->name);
      cgc_free(cur);
      break;
    }
    prev = cur;
    cur = cur->next;
  }
  return ret;
}

