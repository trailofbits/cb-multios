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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "kty.h"
#include "strdup.h"

#define MAGIC_PRIME 0x9e370001UL
#define UINT_MAX 4294967295

htbl_t* htbl_create(int size, free_value_fn *fptr)
{
  htbl_t *table = (htbl_t *) malloc(sizeof(htbl_t));
  if (table == NULL || fptr == NULL)
    goto fail;
  memset(table, 0, sizeof(htbl_t));
  table->free_value = fptr;
  table->size = size > 0 ? size : 16;
  table->count = 0;
  table->table = (entry_t **) malloc(table->size * sizeof(entry_t *));
  if (table->table == NULL)
    goto fail;
  memset(table->table, 0x00, table->size * sizeof(entry_t *));
  return table;

fail:
  if (table)
  {
    if (table->table)
      free(table->table);
    free(table);
  }
  return NULL;
}

int _htbl_hash(htbl_t *tab, char *key)
{
  int i;
  unsigned int hash = MAGIC_PRIME;
  for (i = 0; i < strlen(key); ++i)
  {
    hash += key[i];
    hash = hash << 5;
  }
  hash %= MAGIC_PRIME;
  return hash % tab->size;
}

int _htbl_double_size(htbl_t *tab)
{
  entry_t **tmp;
  if (tab->size > (UINT_MAX / 2) / sizeof(entry_t *))
    return -1;
  tmp = (entry_t **) realloc(tab->table, tab->size * 2 * sizeof(entry_t *));
  if (tmp == NULL)
    return -1;
  memset(&tmp[tab->size], 0, tab->size * sizeof(entry_t *));
  tab->table = tmp;
  tab->size *= 2;
  return 0;
}

int htbl_put(htbl_t *tab, char *key, void *val)
{
  int idx;
  entry_t *it, *new;

  if (tab && key && val)
  {
    if (tab->count >= tab->size * 0.7)
      if (_htbl_double_size(tab) != 0)
        return -1;
    idx = _htbl_hash(tab, key);
    while (1)
    {
      it = tab->table[idx];
      if (it == NULL)
        break;
      if (it && it->key && strcmp(it->key, key) == 0)
      {
        tab->free_value(it->val);
        it->val = val;
        return 0;
      }
      idx++;
      if (idx == tab->size)
        idx = 0;
    }

    new = (entry_t *) malloc(sizeof(entry_t));
    if (new == NULL)
      return -1;
    new->key = strdup(key);
    new->val = val;
    new->next = NULL;
    if (tab->tail == NULL)
      tab->tail = tab->head = new;
    else
    {
      tab->tail->next = new;
      tab->tail = new;
    }
    tab->table[idx] = new;
    tab->count++;
    return 0;
  }
  return -1;
}

void* htbl_get(htbl_t *tab, char *key)
{
  int idx, i;
  entry_t *ret;

  if (tab && key && tab->count > 0)
  {
    idx = _htbl_hash(tab, key);
    for (i = 0; i < tab->size; ++i)
    {
      ret = tab->table[idx];
      if (ret == NULL)
        break;
      if (ret->key && strcmp(ret->key, key) == 0)
        return ret->val;
      idx++;
      if (idx == tab->size)
        idx = 0;
    }
  }
  return NULL;
}

void htbl_destroy(htbl_t *tab)
{
  int i;
  entry_t *it;

  if (tab)
  {
    if (tab->table)
    {
      for (i = 0; i < tab->size; ++i)
      {
        it = tab->table[i];
        if (it)
        {
          if (it->key)
            free(it->key);
          if (it->val)
            tab->free_value(it->val);
          free(it);
          it = NULL;
        }
      }
      free(tab->table);
      tab->table = NULL;
    }
    free(tab);
    tab = NULL;
  }
}
