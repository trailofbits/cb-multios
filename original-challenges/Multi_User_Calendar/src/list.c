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
#include <stdio.h>
#include "list.h"

static list_t *create_node(void *item)
{
    list_t *node = malloc(sizeof(list_t));
    if (!node)
        return NULL;

    node->next = NULL;
    node->item = item;
    return node;
}

bool insert(list_t **list, void *item)
{
    if (!item)
        return false;

    list_t *node = create_node(item);
    if (!node)
        return false;

    if (*list)
        node->next = *list;
    *list = node;
    return true;
}

bool insert_in_order(list_t **list, void *item, int (*compare)(void *a, void *b))
{
    if (!item)
        return false;

    list_t *node = create_node(item);
    if (!node)
        return false;
    if (!*list) {
        *list = node;
        return true;
    }

    list_t *iter = *list;
    list_t *prev = *list;
    while (iter) {
        if (compare(item, iter->item) <= 0) {
            if (*list == iter) {
                node->next = *list;
                *list = node;
                return true;
            } else {
                node->next = iter;
                prev->next = node;
                return true;
            }
        } else if(iter->next == NULL) {
            return append(&iter, item);
        }

        prev = iter;
        iter = iter->next;
    }
    return false;
}

bool append(list_t **list, void *item)
{
    if (!item)
        return false;

    list_t *node = create_node(item);
    if (!node)
        return false;

    if (!(*list)) {
        *list = node;
        return true;
    }

    list_t *iter = *list;
    while (iter->next)
        iter = iter->next;
    iter->next = node;
    return true;
}

void *popfront(list_t **list)
{
    if (!(*list))
        return NULL;

    void *item = NULL;
    list_t *iter = *list;
    *list = iter->next;
    iter->next = NULL;
    item = iter->item;
    free(iter);
    return item;
}

void *popback(list_t **list)
{
    if (!(*list))
        return NULL;

    void *item = NULL;
    list_t *iter = *list, *prev = NULL;
    while (iter->next) {
        prev = iter;
        iter = iter->next;
    }
    if(!prev)
        *list = NULL;
    else
        prev->next = NULL;
    free(iter);
    return item;
}

void *find(list_t *list, void *item, int (*compare)(void *a, void *b))
{
    if (!list || !item)
        return NULL;

    list_t *iter = list;
    while (iter && iter->item) {
        if (compare(item, iter->item) == 0)
            return iter->item;
        iter = iter->next;
    }
    return NULL;
}

void *pop(list_t **list, void *item, int (*compare)(void *a, void *b))
{
    void *popval = NULL;
    if (!list || !item)
        return NULL;

    list_t *iter = *list;
    list_t *prev = *list;
    while (iter) {
        if (compare(item, iter->item) == 0) {
            if (iter != *list)
                prev->next = iter->next;
            else
                *list = iter->next;

            popval = iter->item;
            free(iter);
            return popval;
        }
        prev = iter;
        iter = iter->next;
    }
    return NULL;
}

void print(list_t *list, void (*print_item)(void *item))
{
    if (!list)
        return;

    list_t *iter = list;
    while (iter) {
        print_item(iter->item);
        iter = iter->next;
    }
}
