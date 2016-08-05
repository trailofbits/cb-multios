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

#include <cstdlib.h>
#include <cstring.h>
#include "pair.h"

template <class T>
struct equal_to
{
    bool operator() (const T& a, const T& b)
    {
        return a == b;
    }
};

template <class T>
struct hash
{
    size_t operator() (const T& t)
    {
        return reinterpret_cast<size_t>(t);
    }
};

template <class K, class V, class H=hash<K>, class P=equal_to<K>>
class map
{
private:
    struct _node
    {
        _node(K key)
        {
            value.left = key;
        }

        _node *next, *lnext, *lprev;
        pair<K, V> value;
    };
public:
    class iterator
    {
        struct _node *p;
    public:
        iterator(struct _node *node) : p(node) {}
        iterator& operator++() //prefix
        {
            p = p->lnext;
            return *this;
        }
        iterator& operator++(int) //postfix
        {
            iterator old(*this);
            p = p->lnext;
            return old;
        }
        pair<const K, V>& operator*()
        {
            return p->value;
        }
        bool operator==(const iterator &b)
        {
            return p == b.p;
        }
        bool operator!=(const iterator &b)
        {
            return p != b.p;
        }
    };

    map() : _size(0), _allocated(0), table(nullptr), head(nullptr)
    {
        _enlarge(8);
    }
    ~map()
    {
        if (table)
            delete[] table;
        struct _node *next;
        for (struct _node *node = head; node != nullptr; node = next)
        {
            next = node->lnext;
            delete node;
        }
    }

    map(const map& other) = delete;
    map& operator=(const map& other) = delete;

    V& operator[](const K& key)
    {
        _node *node = _find(key);
        if (node == nullptr)
        {
            node = _insert(key);
        }
        return node->value.right;
    }
    void remove(const K& key)
    {
        H hash;
        P pred;
        size_t h = hash(key) % _allocated;
        struct _node **pnode = &table[h];
        while (*pnode != nullptr)
        {
            if (pred((*pnode)->value.left, key))
            {
                struct _node *node = *pnode;
                *pnode = node->next;
                if (node->lprev) node->lprev->lnext = node->lnext;
                if (node->lnext) node->lnext->lprev = node->lprev;
                if (node == head) head = node->lnext;
                delete node;
                _size--;
                return;
            }
            pnode = &(*pnode)->next;
        }
    }
    bool has(const K& key) const
    {
        return _find(key) != nullptr;
    }
    size_t size() const
    {
        return _size;
    }
    iterator& begin()
    {
        return head;
    }
    iterator& end()
    {
        return nullptr;
    }
private:
    _node *_find(const K& key) const
    {
        H hash;
        P pred;
        size_t h = hash(key) % _allocated;
        for (_node *node = table[h]; node != nullptr; node = node->next)
            if (pred(key, node->value.left))
                return node;
        return nullptr;
    }
    _node *_insert(const K& key)
    {
        if (_size * 3 >= _allocated * 2)
            _enlarge(_allocated * 2);

        _node *node = new _node(key);
        node->lprev = nullptr;
        node->lnext = head;
        head = node;

        _insert_hash(node);
        _size++;
        return node;
    }
    void _insert_hash(_node *node)
    {
        H hash;
        size_t h = hash(node->value.left) % _allocated;
        _node *old = table[h];
        table[h] = node;
        node->next = old;
    }
    void _enlarge(size_t new_size)
    {
        if (_allocated == 0)
        {
            _allocated = new_size;
            table = new _node *[_allocated];
            memset(table, 0, sizeof(_node *) * _allocated);
        }
        else
        {
            delete[] table;
            _allocated = new_size;
            table = new _node *[_allocated];
            memset(table, 0, sizeof(_node *) * _allocated);

            for (_node *node = head; node != nullptr; node = node->lnext)
            {
                _insert_hash(node);
            }
        }
    }
    
    size_t _size;
    size_t _allocated;
    _node **table;
    _node *head;
};
