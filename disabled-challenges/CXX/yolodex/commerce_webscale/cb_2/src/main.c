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
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_db_server.h"
#include "cgc_tree.h"

node_t *root;

static void fill_result(result *res, node_t *n)
{
    res->rec.count = 1;
    res->rec.data = cgc_malloc(sizeof(struct record));
    res->rec.data->k.data.count = n->key_length;
    res->rec.data->k.data.data = n->key;
    res->rec.data->data.count = n->data_length;
    res->rec.data->data.data = n->data;
}

result cgc_DB_CURRENT_db_lookup(key k)
{
    node_t *n;
    result res;

    n = cgc_tree_lookup(&root, k.data.data, k.data.count);

    if (n)
    {
        res.status = SUCCESS;
        fill_result(&res, n);
    }
    else
    {
        res.status = MISSING;
        res.rec.count = 0;
    }
    return res;
}

result cgc_DB_CURRENT_db_insert(record rec)
{
    node_t *n = cgc_malloc(sizeof(*n));
    result res;

    cgc_memset(n, 0, sizeof(*n));
    n->key = rec.k.data.data;
    n->key_length = rec.k.data.count;
    n->data = rec.data.data;
    n->data_length = rec.data.count;

    n = cgc_tree_insert(&root, n);
    if (n)
    {
        res.status = EXISTS;
        fill_result(&res, n);
    }
    else
    {
        res.status = SUCCESS;
        res.rec.count = 0;
    }

    return res;
}

result cgc_DB_CURRENT_db_delete(key k)
{
    node_t *n;
    result res;

    n = cgc_tree_delete(&root, k.data.data, k.data.count);

    if (n)
    {
        res.status = SUCCESS;
        fill_result(&res, n);
    }
    else
    {
        res.status = MISSING;
        res.rec.count = 0;
    }
    return res;
}

result cgc_DB_CURRENT_db_next(key k)
{
    node_t *n;
    result res;

    if (k.data.count == 0)
    {
        n = cgc_tree_smallest(&root);
    }
    else
    {
        n = cgc_tree_next(&root, k.data.data, k.data.count);
    }

    if (n)
    {
        res.status = SUCCESS;
        fill_result(&res, n);
    }
    else
    {
        res.status = MISSING;
        res.rec.count = 0;
    }
    return res;
}

result cgc_DB_CURRENT_db_prev(key k)
{
    node_t *n;
    result res;
    if (k.data.count == 0)
    {
        n = cgc_tree_largest(&root);
    }
    else
    {
        n = cgc_tree_prev(&root, k.data.data, k.data.count);
    }

    if (n)
    {
        res.status = SUCCESS;
        fill_result(&res, n);
    }
    else
    {
        res.status = MISSING;
        res.rec.count = 0;
    }
    return res;
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_database_run(6, 3);
}
