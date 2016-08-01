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
#include "ptrlist.h"
#include <string.h>

ptrlist_t *create_ptrlist()
{
    ptrlist_t *ptrlist = calloc(1, sizeof(ptrlist_t));
    if (ptrlist == NULL)
        return NULL;

    ptrlist->size = 8;
    ptrlist->length = 0;
    ptrlist->datalist = calloc(1, sizeof(void *) * (ptrlist->size));
    if (ptrlist->datalist == NULL)
        return NULL;

    return ptrlist;
}

int add_item(ptrlist_t *ptrlist, void *pdata)
{
    if (!ptrlist || !pdata)
        return -1;

    if (ptrlist->size == ptrlist->length) {
        void *expanded_list = malloc(sizeof(void *) * (ptrlist->size * 2));
        if (!expanded_list )
            return -1;

        memcpy(expanded_list , ptrlist->datalist, sizeof(void *) * (ptrlist->size));
        free(ptrlist->datalist);
        ptrlist->size *= 2;
        ptrlist->datalist = expanded_list ;
    }

    ptrlist->datalist[ptrlist->length++] = pdata;
    return 0;
}

void *get_pdata(ptrlist_t *ptrlist, size_t idx)
{
    if (!ptrlist || idx > ptrlist->length)
        return NULL;

    return ptrlist->datalist[idx];
}

