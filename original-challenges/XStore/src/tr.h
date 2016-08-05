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

#ifndef TR_H
#define TR_H
#include <stdio.h>

typedef void* T;
typedef struct tr_node {
    char *key;
    unsigned int prio;
    T value;
    struct tr_node *left, *right;
} tr_node_t;
typedef tr_node_t* tr_t;
typedef void (*tr_destroy_value) (T value);
typedef void (*tr_apply_fn) (tr_t root, void *arg);

extern tr_destroy_value destroy_value_fn;

tr_t tr_insert(tr_t root, char *key, T value);
tr_t tr_delete(tr_t root, char *key);
T tr_find(tr_t root, char *key);
void tr_destroy(tr_t root);

void tr_apply(tr_t root, tr_apply_fn apply, void *arg);
void tr_print(tr_t root);

#endif
