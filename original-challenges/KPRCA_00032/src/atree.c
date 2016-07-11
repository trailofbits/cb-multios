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
#include <stdint.h>
#include <string.h>
#include "atree.h"
#include "random.h"

/* given a frequency table create a new atree */
atree_t *atree_init(freqtab_t *ftab)
{
    int i, j;
    atree_t *tree;

    tree = calloc(sizeof(atree_t), 1);
    if (tree == NULL)
        return NULL;

    for (i = 0; i < ALPHABET_SIZE; i++)
        tree->levelmap[i] = i + ALPHABET_START;

    // in-place insertion sort using ftab for weights
    for (i = 1; i < ALPHABET_SIZE; i++)
    {
        char c = tree->levelmap[i];
        unsigned int freq = ftab->freq[c - ALPHABET_START];
        for (j = i; j > 0; j--)
        {
            // sort in reverse order
            if (ftab->freq[tree->levelmap[j-1] - ALPHABET_START] >= freq)
                break;

            tree->levelmap[j] = tree->levelmap[j-1];
        }
        tree->levelmap[j] = c;
    }

    return tree;
}

#define INVALID ((unsigned int) -1)
static unsigned int _atree_find_freq(atree_node_t *node, unsigned int freq)
{
    unsigned int min = 0, max = node->degree - 1;
    if (node->degree == 0)
        return INVALID;

    while (min + 1 < max)
    {
        unsigned int mid = (max - min) / 2 + min;
        if (node->children[mid].freq == freq)
            return mid;
        else if (node->children[mid].freq > freq)
            max = mid;
        else
            min = mid;
    }

    if (node->children[max].freq <= freq)
        return max;
    else
        return min;
}

static unsigned int _atree_find_word(atree_node_t *node, const char *word)
{
    unsigned int min = 0, max = node->degree - 1;
    if (node->degree == 0)
        return INVALID;

    while (min + 1 < max)
    {
        unsigned int mid = (max - min) / 2 + min;
        int cmp = strcmp(node->words[mid], word);
        if (cmp == 0)
            return mid;
        else if (cmp > 0)
            max = mid;
        else
            min = mid;
    }

    if (strcmp(node->words[max], word) <= 0)
        return max;
    else
        return min;
}

static atree_node_t **_atree_walk(atree_t *tree, freqtab_t *ftab, int is_insert)
{
    char c;
    unsigned int i, idx, freq;
    atree_node_t *node, **pnode;

    pnode = &tree->root;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        // shortcut variables
        c = tree->levelmap[i];
        freq = ftab->freq[c - ALPHABET_START];
        node = *pnode;

        if (node == NULL || node->level > i)
        {
            atree_node_t *n;

            if (freq == 0)
                continue; // skip an empty level

            if (!is_insert)
                return NULL;

            // insert new level
            n = calloc(NODE_MIN_SIZE, 1);
            if (n == NULL)
                return NULL;

            n->level = i;
            n->max_degree = NODE_MIN_DEGREE;
            
            if (node)
            {
                n->children[n->degree].child = node;
                n->children[n->degree].freq = 0;
                n->degree++;
            }

            // set pnode and node appropriately
            node = *pnode = n;
        }

        idx = _atree_find_freq(node, freq);
        if (idx == INVALID || node->children[idx].freq != freq)
        {
            if (!is_insert)
                return NULL;

            // insert new link for this frequency
            node->degree++;
            if (node->degree > node->max_degree)
            {
                unsigned int new_length = node->degree + 2;
                atree_node_t *n = realloc(node, sizeof(atree_node_t) + new_length * sizeof(node->children[0]));
                if (n == NULL)
                {
                    // XXX node->degree already incremented
                    node->degree--;
                    return 0; 
                }

                n->max_degree = new_length;
                node = *pnode = n;
            }

            // set idx appropriately
            if (idx == INVALID)
                idx = 0;
            else if (node->children[idx].freq < freq)
                idx++;

            if (node->degree - 1 > idx)
                memmove(&node->children[idx+1], &node->children[idx], sizeof(node->children[0]) * (node->degree - idx - 1));

            node->children[idx].child = NULL;
            node->children[idx].freq = freq;
        }

        pnode = &node->children[idx].child;
    }

    // leaf node
    node = *pnode;
    if (node == NULL)
    {
        if (!is_insert)
            return NULL;

        *pnode = node = calloc(NODE_MIN_SIZE, 1);
        if (node == NULL)
            return NULL;

        node->level = i;
        node->max_degree = NODE_MIN_DEGREE;
        node->next_leaf = tree->leaf;
        if (node->next_leaf)
            node->next_leaf->prev_leaf = node;
        node->prev_leaf = NULL;
        tree->leaf = node;
    }

    return pnode;
}

/* add a word to the tree */
int atree_add(atree_t *tree, const char *word)
{
    unsigned int i;
    int cmp;
    atree_node_t *node, **pnode;
    freqtab_t ftab;

    ftab_init(&ftab, word);
    pnode = _atree_walk(tree, &ftab, 1);
    if (pnode == NULL)
        return 0;

    node = *pnode;

    // make sure that word is not already in the list
    i = _atree_find_word(node, word);
    if (i == INVALID)
    {
        i = 0;
    }
    else
    {
        cmp = strcmp(node->words[i], word);
        if (cmp == 0)
            return 0;
        else if (cmp < 0)
            i++;
    }

    if (node->degree == UINT16_MAX)
        return 0;

    node->degree++;
    if (node->degree > node->max_degree)
    {
        unsigned int new_length = node->degree + 8;
        node = realloc(node, sizeof(atree_node_t) + sizeof(const char *) * new_length);
        if (node == NULL)
        {
#ifdef PATCHED
            (*pnode)->degree--;
#endif
            return 0; // XXX BUG node->degree was already incremented
        }

        // set node and *pnode, and max_degree appropriately
        if (node->next_leaf)
            node->next_leaf->prev_leaf = node;
        if (node->prev_leaf)
            node->prev_leaf->next_leaf = node;
        else
            tree->leaf = node;
        *pnode = node;

        node->max_degree = new_length;
    }

    if (i < node->degree - 1)
        memmove(&node->words[i+1], &node->words[i], sizeof(const char *) * (node->degree - 1 - i));
    node->words[i] = word;

    tree->count++;
    return 1;
}

/* remove a word from the tree */
int atree_remove(atree_t *tree, const char *word)
{
    unsigned int i;
    atree_node_t *node, **pnode;
    freqtab_t ftab;

    ftab_init(&ftab, word);
    pnode = _atree_walk(tree, &ftab, 0);
    if (pnode == NULL)
        return 0;
    node = *pnode;

    for (i = 0; i < node->degree; i++)
        if (strcmp(word, node->words[i]) == 0)
            break;

    if (i < node->degree)
    {
        if (i < node->degree - 1)
            memmove(&node->words[i], &node->words[i + 1], sizeof(const char *) * (node->degree - i - 1));
        node->degree--;
        tree->count--;
        return 1;
    }
    return 0;
}

/* return a NULL-terminated list of words that are an anagram of word */
char **atree_query(atree_t *tree, const char *word)
{
    char **result;
    atree_node_t *node, **pnode;
    freqtab_t ftab;

    ftab_init(&ftab, word);
    pnode = _atree_walk(tree, &ftab, 0);
    if (pnode == NULL)
    {
        result = calloc(sizeof(const char *), 1);
        if (result == NULL)
            return NULL;
        return result;
    }
    node = *pnode;

    result = calloc(sizeof(const char *), node->degree + 1);
    if (result == NULL)
        return NULL;

    memcpy(result, node->words, sizeof(const char *) * node->degree);
    result[node->degree] = NULL;
    return result;
}

static void _atree_gather_subset(atree_t *tree, freqtab_t *ftab, atree_node_t *node, char ***results, size_t *count)
{
    char c;
    unsigned int i, idx, freq;

    if (node == NULL) // XXX should never happen?
        return;

    if (node->level == ALPHABET_SIZE)
    {
        char **r;
        size_t c = *count + node->degree + 1;
        // leaf node
        r = realloc(*results, c * sizeof(char *));
        if (r == NULL)
            return;
        
        memcpy(&r[*count], node->words, node->degree * sizeof(char *));
        *results = r;
        *count += node->degree;
        return;
    }

    c = tree->levelmap[node->level];
    freq = ftab->freq[c - ALPHABET_START];
    idx = _atree_find_freq(node, freq);

    if (idx == INVALID)
        return; // frequency is too low

    if (freq < node->children[idx].freq)
    {
        if (idx == 0)
            return;
        else
            idx--;
    }

    for (i = 0; i <= idx; i++)
        _atree_gather_subset(tree, ftab, node->children[i].child, results, count);
}

/* return a NULL-terminated list of words that are a subset anagram of word */
char **atree_query_subset(atree_t *tree, const char *word)
{
    char **results = malloc(sizeof(char *));
    size_t count = 0;
    freqtab_t ftab;

    ftab_init(&ftab, word);
    _atree_gather_subset(tree, &ftab, tree->root, &results, &count);
    results[count] = NULL;

    return results;
}

/* return a random word from the tree */
const char *atree_random(atree_t *tree)
{
    unsigned int r;
    atree_node_t *node;

    if (tree->count == 0)
        return NULL;

    r = randint(0, tree->count);
    for (node = tree->leaf; node != NULL; node = node->next_leaf)
    {
        if (r < node->degree)
            break;
        r -= node->degree;
    }

    if (node == NULL) // XXX should never happen
        return NULL;

    return node->words[r];
}
