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
#ifndef LIST_H_
#define LIST_H_

#include "libcgc.h"
#include "cgc_bool.h"

typedef struct list list_t;
struct list
{
    list_t *next;
    void *item;
};

bool cgc_insert(list_t **list, void *item);
bool cgc_insert_in_order(list_t **list, void *item, int (*compare)(void *a, void *b));
bool cgc_append(list_t **list, void *item);
void *cgc_popfront(list_t **list);
void *cgc_popback(list_t **list);
void *cgc_find(list_t *list, void *item, int (*compare)(void *a, void *b));
void *cgc_pop(list_t **list, void *item, int (*compare)(void *a, void *b));
void cgc_print(list_t *list, void (*print_item)(void *item));

#endif
