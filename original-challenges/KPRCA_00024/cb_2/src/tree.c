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
#include <string.h>
#include "tree.h"

static int tree_cmp(unsigned char *a, size_t a_length, node_t *b)
{
    size_t i;
    for (i = 0; i < a_length && i < b->key_length; i++)
    {
        int diff = a[i] - b->key[i];
        if (diff != 0)
            return diff;
    }
    return a_length - b->key_length;
}

static void skew(node_t **T)
{
    node_t *t = *T;
    if (t == NULL)
        return;

    if (t->left == NULL)
        return;

    if (t->left->level == t->level)
    {
        // violates tree invariant, perform skew
        *T = t->left;
        t->left = (*T)->right;
        (*T)->right = t;
    }
}

static void split(node_t **T)
{
    node_t *t = *T;
    if (t == NULL)
        return;

    if (t->right == NULL || t->right->right == NULL)
        return;

    if (t->level == t->right->right->level)
    {
        // violates tree invariant, perform split
        *T = t->right;
        t->right = (*T)->left;
        (*T)->left = t;
        (*T)->level++;
    }
}

node_t *tree_lookup(node_t **T, unsigned char *key, size_t key_length)
{
    node_t *t = *T;
    if (t == NULL)
        return NULL;
    else if (tree_cmp(key, key_length, t) < 0)
        t = tree_lookup(&t->left, key, key_length);
    else if (tree_cmp(key, key_length, t) > 0)
        t = tree_lookup(&t->right, key, key_length);
    return t;
}

node_t *tree_insert(node_t **T, node_t *n)
{
    node_t *old = NULL;
    node_t *t = *T;
    if (t == NULL)
    {
        *T = n;
        n->left = NULL;
        n->right = NULL;
        n->level = 1;
    }
    else if (tree_cmp(n->key, n->key_length, t) < 0)
    {
        old = tree_insert(&t->left, n);
    }
    else if (tree_cmp(n->key, n->key_length, t) > 0)
    {
        old = tree_insert(&t->right, n);
    }
    else
    {
        // replace the node with the new node
        old = t;
        *T = n;
        n->left = t->left;
        n->right = t->right;
        n->level = t->level;
    }

    skew(T);
    split(T);

    return old;
}

node_t *tree_delete(node_t **T, unsigned char *key, size_t key_length)
{
    node_t *old = NULL;
    node_t *t = *T;
    if (t == NULL)
        return NULL;
    else if (tree_cmp(key, key_length, t) < 0)
        old = tree_delete(&t->left, key, key_length);
    else if (tree_cmp(key, key_length, t) > 0)
        old = tree_delete(&t->right, key, key_length);
    else
    {
        old = t;
        if (t->left == NULL && t->right == NULL)
        {
            // we are a leaf, so we just go away
            *T = NULL;
            return old;
        }
        else if (t->left == NULL)
        {
            node_t *succ = tree_succ(T);
            // remove the successor from the tree
            tree_delete(&t->right, succ->key, succ->key_length);
            // replace this node with the successor
            *T = succ;
            succ->left = t->left;
            succ->right = t->right;
            succ->level = t->level;
        }
        else
        {
            node_t *pred = tree_pred(T);
            // remove the predecessor from the tree
            tree_delete(&t->left, pred->key, pred->key_length);
            // replace this node with the predessor
            *T = pred;
            pred->left = t->left;
            pred->right = t->right;
            pred->level = t->level;
        }
    }

    // XXX decrease levels

    skew(T);
    skew(&(*T)->right);
    if ((*T)->right != NULL)
        skew(&(*T)->right->right);
    split(T);
    split(&(*T)->right);
    return old;
}

node_t *tree_smallest(node_t **T)
{
    // the left-most node
    node_t *t = *T;
    while (t->left != NULL)
        t = t->left;
    return t;
}

node_t *tree_largest(node_t **T)
{
    // the right-most node
    node_t *t = *T;
    while (t->right != NULL)
        t = t->right;
    return t;
}

node_t *tree_succ(node_t **T)
{
    node_t *t = *T;
    if (t == NULL || t->right == NULL)
        return NULL;
    t = t->right;
    while (t->left != NULL)
        t = t->left;
    return t;
}

node_t *tree_pred(node_t **T)
{
    node_t *t = *T;
    if (t == NULL || t->left == NULL)
        return NULL;
    t = t->left;
    while (t->right != NULL)
        t = t->right;
    return t;
}

node_t *tree_next(node_t **T, unsigned char *key, size_t key_length)
{
    node_t *t = *T;
    if (t == NULL)
        return NULL;
    else if (tree_cmp(key, key_length, t) < 0)
    {
        t = tree_next(&t->left, key, key_length);
        if (t == NULL)
            return *T;
    }
    else if (tree_cmp(key, key_length, t) > 0)
    {
        t = tree_next(&t->right, key, key_length);
    }
    else
        return tree_succ(T);

    return t;
}

node_t *tree_prev(node_t **T, unsigned char *key, size_t key_length)
{
    node_t *t = *T;
    if (t == NULL)
        return NULL;
    else if (tree_cmp(key, key_length, t) < 0)
    {
        t = tree_prev(&t->left, key, key_length);
    }
    else if (tree_cmp(key, key_length, t) > 0)
    {
        t = tree_prev(&t->right, key, key_length);
        if (t == NULL)
            return *T;
    }
    else
        return tree_pred(T);

    return t;
}
