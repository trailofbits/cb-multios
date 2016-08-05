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

#include "attribute.h"
#include "string.h"

extern const String *CML_TAG;
extern const String *EMPTY_TAG;

enum class NodeClass
{
    NODE,
    CMLNODE,
    TEXTNODE
};

class Node
{
protected:
    Node(const String *ns, const String *tag);
    Node(const String *ns, const String *tag, NodeClass cls);
public:
    static Node *create(const char *ns, const char *tag);
    static void delete_tree(Node *node);

    virtual ~Node();
    virtual bool remove_attr(const char *name);
    virtual void set_attr(const char *name, String *value);
    inline Attribute *get_attr(const char *name)
    {
        Attribute **result = d_attr.lookup(String::intern(name));
        return result == nullptr ? nullptr : *result;
    }

    inline Node *parent() { return d_parent; }
    inline Node *first() { return d_first; }
    inline Node *last() { return d_last; }
    inline Node *next() { return d_next; }
    inline Node *prev() { return d_prev; }
    virtual void insert_after(Node *node, Node *new_node);
    virtual void insert_before(Node *node, Node *new_node);
    virtual void remove();

    inline const String *ns() { return d_ns; }
    inline const String *tag() { return d_tag; }
    inline AttributeMap &attr() { return d_attr; }
    inline NodeClass cls() { return d_class; }
protected:
    const String *d_ns;
    const String *d_tag;
    AttributeMap d_attr;

    Node *d_next, *d_prev;
    Node *d_first, *d_last, *d_parent;

    NodeClass d_class;
};
