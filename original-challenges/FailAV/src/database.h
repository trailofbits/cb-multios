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
#pragma once

#include <cstdlib.h>

class Database
{
private:
    class PrefixNode
    {
    public:
        PrefixNode() : d_root(1), d_word(0), d_value(0), d_num_edges(0) {}
        PrefixNode(bool word, unsigned char value, unsigned short num_edges) : d_root(0), d_word(word), d_value(value), d_num_edges(num_edges) {}
        ~PrefixNode()
        {
            for (unsigned int i = 0; i < d_num_edges; i++)
            {
                d_next[i]->~PrefixNode();
                free(d_next[i]);
            }
        }

        PrefixNode *get_next(unsigned char ch)
        {
            int i = get_next_idx(ch);
            if (i >= 0)
                return d_next[i];
            if (d_root)
                return this;
            return NULL;
        }
        int get_next_idx(unsigned char ch)
        {
            for (unsigned int i = 0; i < d_num_edges; i++)
                if (d_next[i]->d_value == ch)
                    return i;
            return -1;
        }

        static void add(PrefixNode **root, const unsigned char *word, unsigned int len);
        static void remove(PrefixNode **root, const unsigned char *word, unsigned int len);
        template <typename F>
        static void traverse_tree(PrefixNode *root, F f);
        static unsigned int get_alloc_size(unsigned int len)
        {
            return sizeof(PrefixNode) + len * sizeof(PrefixNode *);
        }

        unsigned char d_root : 1;
        unsigned char d_word : 1;
        unsigned char d_value;
        unsigned short d_num_edges;
        PrefixNode *d_fail;
        PrefixNode *d_tmp;
        PrefixNode *d_next[];
    };

    void rebuild_fsm();
public:
    Database();
    ~Database();

    Database(const Database &) = delete;
    Database& operator=(const Database &) = delete;

    void add(const unsigned char *word, unsigned int len);
    void remove(const unsigned char *word, unsigned int len);
    bool query(const unsigned char *haystack, unsigned int len) const;
private:
    PrefixNode *d_prefix_root;
};
