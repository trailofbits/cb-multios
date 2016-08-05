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

template <class T>
class LinkedList
{
public:
    class Node
    {
        friend class LinkedList;
    private:
        inline Node(T value_) : next(NULL), prev(NULL), value(value_)
        {
        }
    public:
        Node *next;
        Node *prev;
        T value;
    };
    class Iterator
    {
        friend class LinkedList;
    public:
        T value() const
        {
            return node->value;
        }
        void next()
        {
            node = node->next;
        }
        void prev()
        {
            node = node->prev;
        }
        bool empty() const
        {
            return node == NULL;
        }
    private:
        inline Iterator(Node *node_) : node(node_)
        {
        }

        Node *node;
    };
    typedef void (*destructor) (T value);
    static void deleteDestructor(T value)
    {
        delete value;
    }

    inline LinkedList(destructor dtor_) : dtor(dtor_), head(NULL), tail(NULL), length(0)
    {
    }
    inline LinkedList() : LinkedList(NULL)
    {
    }
    inline ~LinkedList()
    {
        Node *next;
        for (Node *node = head; node != NULL; node = next)
        {
            next = node->next;

            if (dtor)
                dtor(node->value);
            delete node;
        }
    }
    unsigned int getLength() const
    {
        return length;
    }
    inline void append(T value)
    {
        Node *node = new Node(value);
        insertNode(tail, node);
        length++;
    }
    inline void prepend(T value)
    {
        Node *node = new Node(value);
        insertNode(NULL, node);
        length++;
    }
    inline Iterator begin() const
    {
        return Iterator(head);
    }
    inline Iterator end() const
    {
        return Iterator(tail);
    }
    inline void removeAt(Iterator &it)
    {
        if (it.empty())
            return;

        Node *node = it.node;
        it.next();

        removeNode(node);
        delete node;
        length--;
    }
private:
    inline void insertNode(Node *prev, Node *newNode)
    {
        if (prev == NULL)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            newNode->next = prev->next;
            prev->next = newNode;
        }

        newNode->prev = prev;
        if (newNode->next)
            newNode->next->prev = newNode;

        if (tail == prev)
            tail = newNode;
    }
    inline void removeNode(Node *node)
    {
        if (node->next)
            node->next->prev = node->prev;
        if (node->prev)
            node->prev->next = node->next;
        if (node == head)
            head = node->next;
        if (node == tail)
            tail = node->prev;
    }

    destructor dtor;
    Node *head;
    Node *tail;
    unsigned int length;
};
