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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "ht.h"

#define INITIAL_COUNT 4
#define MAX_COUNT 8192
#define THRESHOLD (0.5)

static unsigned int _hash(unsigned int size, const char *k)
{
    unsigned int result = 0x3505;
    size_t i;
    for (i = 0; k[i]; i++)
        result = result * 37 + tolower(k[i]);
    return result % size;
}

static int _do_insert(struct ht_node_t **tbl, unsigned int size, struct ht_node_t *node)
{
    unsigned int idx = _hash(size, node->k), i;
    // linear probing
    for (i = idx; tbl[i] != NULL; i = (i + 1) & (size-1))
        if (i == ((idx - 1) & (size-1)))
            return FAILURE;

    tbl[i] = node;
    return SUCCESS;
}

static int _ht_resize(ht_t *tbl)
{
    unsigned int new_size = tbl->tbl_size * 2;
    struct ht_node_t **new_entries, *iter;

    // allocate new table
    new_entries = calloc(new_size, sizeof(ht_node_t *));
    if (new_entries == NULL)
        return FAILURE;

    // re-insert nodes into new table
    for (iter = tbl->first; iter != NULL; iter = iter->next)
    {
        if (_do_insert(new_entries, new_size, iter) != SUCCESS)
            goto fail;
    }

    free(tbl->tbl);
    tbl->tbl = new_entries;
    tbl->tbl_size = new_size;
    return SUCCESS;

fail:
    free(new_entries);
    return FAILURE;
}

int ht_init(ht_t *tbl)
{
    memset(tbl, 0, sizeof(ht_t));
    tbl->tbl_size = INITIAL_COUNT;
    return _ht_resize(tbl);
}

int ht_compare(const char *a, const char *b)
{
    return strcasecmp(a, b);
}

int ht_lookup(ht_t *tbl, const char *k, ht_node_t **node)
{
    unsigned int idx = _hash(tbl->tbl_size, k), i;

    for (i = idx; tbl->tbl[i] != NULL; i = (i + 1) % tbl->tbl_size)
        if (ht_compare(tbl->tbl[i]->k, k) == 0)
            break;

    if (tbl->tbl[i] == NULL)
        return FAILURE;

    *node = tbl->tbl[i];
    return SUCCESS;
}

int ht_delete(ht_t *tbl, const char *k, void **v)
{
    unsigned int idx, i, last;
    ht_node_t *node = NULL;
    if (ht_lookup(tbl, k, &node) != SUCCESS)
        return FAILURE;
    
    *v = node->value;

    if (node->prev == NULL)
        tbl->first = node->next;
    else
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    idx = _hash(tbl->tbl_size, node->k);
    for (i = idx; tbl->tbl[i] != node; i = (i + 1) % tbl->tbl_size) ;

    tbl->tbl[i] = NULL;
    tbl->tbl_count--;

    last = i;
    for (i = (i + tbl->tbl_size - 1) % tbl->tbl_size; tbl->tbl[i] != NULL; i = (i + tbl->tbl_size - 1) % tbl->tbl_size)
        idx = i;
    for (i = (last + 1) % tbl->tbl_size; tbl->tbl[i] != NULL; i = (i + 1) % tbl->tbl_size)
    {
        unsigned int idx2 = _hash(tbl->tbl_size, tbl->tbl[i]->k);
        if ((idx <= last && idx <= idx2 && idx2 <= last) ||
            (idx > last && (idx <= idx2 || idx2 <= last)))
        {
            tbl->tbl[last] = tbl->tbl[i];
            tbl->tbl[i] = NULL;
            last = i;
        }
    }

    free(node->k);
    free(node);
    return SUCCESS;
}

int ht_insert(ht_t *tbl, const char *k_, void *v)
{
    char *k;
    ht_node_t *node = NULL;
    if (ht_lookup(tbl, k_, &node) == SUCCESS)
        return FAILURE;

    if (tbl->tbl_count == MAX_COUNT)
        return FAILURE;

    k = strdup(k_);
    if (k == NULL)
        return FAILURE;
    node = malloc(sizeof(ht_node_t));
    node->k = k;
    node->value = v;

    if (tbl->tbl_count+1 >= tbl->tbl_size * THRESHOLD)
    {
        if (_ht_resize(tbl) != SUCCESS)
            goto fail;
    }

    if (_do_insert(tbl->tbl, tbl->tbl_size, node) != SUCCESS)
        goto fail;

    tbl->tbl_count++;
    node->prev = NULL;
    node->next = tbl->first;
    if (node->next)
        node->next->prev = node;
    tbl->first = node;
    return SUCCESS;

fail:
    free(k);
    free(node);
    return FAILURE;
}

ht_node_t *ht_first(ht_t *tbl)
{
    return tbl->first;
}

ht_node_t *ht_next(ht_t *tbl, ht_node_t *n)
{
    return n->next;
}
