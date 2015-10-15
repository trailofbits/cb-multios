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

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef void (free_value_fn) (void *e);

typedef struct entry {
  char *key;
  void *val;
  struct entry *next;
} entry_t;

typedef struct htbl {
  unsigned int size;
  unsigned int count;
  entry_t **table;
  entry_t *head;
  entry_t *tail;
  free_value_fn *free_value;
} htbl_t;

htbl_t* htbl_create(int size, free_value_fn *fptr);
int htbl_put(htbl_t *tab, char *key, void *val);
void* htbl_get(htbl_t *tab, char *key);
void htbl_destroy(htbl_t *tab);

#endif
