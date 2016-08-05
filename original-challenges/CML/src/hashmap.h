/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#include <cstring.h>
#include "smalloc.h"

template <typename K, typename V, typename C>
class HashMap
{
private:
    class Node
    {
    public:
        Node(K key, V value) : d_value(value), d_key(key) {}
    public:
        V d_value;
        K d_key;
        Node *d_next;
    };
    void resize(int new_size)
    {
        Node **nodes = static_cast<Node **>(safe_calloc(new_size, sizeof(Node *)));
        for (unsigned int i = 0; i < d_size; i++)
        {
            Node *node, *next;
            for (node = d_nodes[i]; node != nullptr; node = next)
            {
                unsigned int idx = C::hash(node->d_key) % new_size;
                next = node->d_next;
                node->d_next = nodes[idx];
                nodes[idx] = node;
            }
        }
        d_nodes = nodes;
        d_size = new_size;
    }
    Node *find_node(K key, Node **parent) const
    {
        if (d_length == 0)
            return nullptr;
        Node *node = d_nodes[C::hash(key) % d_size];
        if (parent != nullptr)
            *parent = nullptr;
        for (; node != nullptr; node = node->d_next)
        {
            if (C::equals(key, node->d_key))
                return node;
            if (parent != nullptr)
                *parent = node;
        }
        return nullptr;
    }
public:
    HashMap(int initial_size)
    {
        d_length = 0;
        d_size = initial_size;
        d_nodes = nullptr;
    }
    HashMap() : HashMap(DEFAULT_SIZE) {}
    ~HashMap()
    {
        free(d_nodes);
    }
    inline unsigned int length() const
    {
        return d_length;
    }
    inline unsigned int size() const
    {
        return d_size;
    }
    void insert(K key, V value)
    {
        d_length++;
        if (d_nodes == nullptr)
        {
            int initial_size = d_size;
            d_size = 0;
            resize(initial_size);
        }
        if (d_length * 2 > d_size)
            resize(d_size * 2);

        unsigned int idx = C::hash(key) % d_size;
        Node *node = new Node(key, value);
        node->d_next = d_nodes[idx];
        d_nodes[idx] = node;
    }
    V *lookup(K key) const
    {
        Node *node;
        if (d_length == 0)
            return nullptr;
        node = find_node(key, nullptr);
        return node == nullptr ? nullptr : &node->d_value;
    }
    bool remove(K key)
    {
        Node *node, *parent;
        node = find_node(key, &parent);
        if (node == nullptr)
            return false;
        if (parent == nullptr)
            d_nodes[C::hash(key) % d_size] = node->d_next;
        else
            parent->d_next = node->d_next;
        d_length--;
        delete node;
        return true;
    }
    V *next(V *prev) const
    {
        unsigned int idx = 0;
        if (d_length == 0)
            return nullptr;
        Node *node = reinterpret_cast<Node *>(prev);
        if (node != nullptr)
        {
            if (node->d_next != nullptr)
                return &node->d_next->d_value;
            idx = (C::hash(node->d_key) % d_size) + 1;
        }
        for (; idx < d_size; idx++)
        {
            if (d_nodes[idx] != nullptr)
                return &d_nodes[idx]->d_value;
        }
        return nullptr;
    }
private:
    static const int DEFAULT_SIZE = 10;
    unsigned int d_length;
    unsigned int d_size;
    Node **d_nodes;
};

class CStringComparator
{
public:
    static inline unsigned int hash(const char *str)
    {
        unsigned int h = 0x14159265;
        for (unsigned int i = 0; str[i] != 0; i++)
            h = (h * 43) ^ str[i];
        return h;
    }
    static inline bool equals(const char *a, const char *b)
    {
        return strcmp(a, b) == 0;
    }
};

class UIntComparator
{
public:
    static inline unsigned int hash(unsigned int x)
    {
        unsigned int h = 0x14159265;
        h *= x;
        h ^= (x >> 16);
        h ^= x;
        return h;
    }
    static inline bool equals(unsigned int a, unsigned int b)
    {
        return a == b;
    }
};
