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
#include "tr.h"

tr_t _tr_rot_left(tr_t root)
{
    tr_node_t *nroot;
    nroot = root->left;
    root->left = nroot->right;
    nroot->right = root;
    return nroot;
}

tr_t _tr_rot_right(tr_t root)
{
    tr_node_t *nroot;
    nroot = root->right;
    root->right = nroot->left;
    nroot->left = root;
    return nroot;
}

tr_t tr_insert(tr_t root, char *key, T value)
{
    if (root == NULL)
    {
        root = (tr_node_t *) malloc(sizeof(tr_node_t));
        root->key = strdup(key);
        random(&(root->prio), sizeof(root->prio), NULL);
        root->value = value;
        root->left = root->right = NULL;
    }
    else if (strcmp(key, root->key) < 0)
    {
        root->left = tr_insert(root->left, key, value);
        if (root->left->prio < root->prio)
            root = _tr_rot_left(root);
    }
    else if (strcmp(key, root->key) > 0)
    {
        root->right = tr_insert(root->right, key, value);
        if (root->right->prio < root->prio)
            root = _tr_rot_right(root);
    }
    else
    {
        destroy_value_fn(root->value);
        root->value = value;
    }

    return root;
}

void _tr_destroy_node(tr_node_t *node)
{
    //destroy_value_fn(node->value);
    free(node->key);
    free(node);
}

tr_t tr_delete(tr_t root, char *key)
{
    tr_node_t *tmp;
    if (root == NULL)
        return NULL;
    if (strcmp(key, root->key) < 0)
        root->left = tr_delete(root->left, key);
    else if (strcmp(key, root->key) > 0)
        root->right = tr_delete(root->right, key);
    else
    {
        if (root->left && root->right)
        {
            if (root->left->prio < root->right->prio)
            {
                root = _tr_rot_left(root);
                root->right = tr_delete(root->right, key);
            }
            else
            {
                root = _tr_rot_right(root);
                root->left = tr_delete(root->left, key);
            }
        }
        else
        {
            tmp = root;
            if (root->left)
                root = root->left;
            else if (root->right)
                root = root->right;
            else
                root = NULL;
            _tr_destroy_node(tmp);
        }
    }
    return root;
}

T tr_find(tr_t root, char *key)
{
    if (root == NULL)
        return NULL;
    if (strcmp(key, root->key) < 0)
        return tr_find(root->left, key);
    else if (strcmp(key, root->key) > 0)
        return tr_find(root->right, key);
    else
        return root->value;
}

void tr_destroy(tr_t root)
{
    if (root != NULL)
    {
        tr_destroy(root->left);
        _tr_destroy_node(root);
        tr_destroy(root->right);
    }
}

void tr_apply(tr_t root, tr_apply_fn apply, void *arg)
{
    if (root != NULL)
    {
        tr_apply(root->left, apply, arg);
        apply(root, arg);
        tr_apply(root->right, apply, arg);
    }
}

void tr_print(tr_t root)
{
    if (root != NULL)
    {
        tr_print(root->left);
        printf("&s (&d)" NL, root->key, (int) root->value);
        tr_print(root->right);
    }
}
