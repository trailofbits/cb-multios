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
#include "node.h"
#include "cmlnode.h"
#include "textnode.h"

const String *CML_TAG = String::intern("cml");
const String *EMPTY_TAG = String::intern("");

Node::Node(const String *ns, const String *tag, NodeClass cls)
    : d_ns(ns), d_tag(tag), d_next(nullptr), d_prev(nullptr),
      d_first(nullptr), d_last(nullptr), d_parent(nullptr), d_class(cls)
{
}

Node::Node(const String *ns, const String *tag)
    : Node(ns, tag, NodeClass::NODE)
{
}

Node::~Node()
{
    // free all of the attributes
    Attribute **pattr = nullptr;
    while ((pattr = d_attr.next(pattr)) != nullptr)
    {
        delete (*pattr);
    }
}

Node *Node::create(const char *ns, const char *tag)
{
    const String *s = String::intern(tag);
    const String *nss = ns == nullptr ? nullptr : String::intern(ns);
    if (s == CML_TAG && nss == nullptr)
        return new CmlNode(nss, s);
    else if (s == EMPTY_TAG && nss == nullptr)
        return new TextNode(nss, s);
    else
        return new Node(nss, s);
}

void Node::delete_tree(Node *node)
{
    Node *child, *next;
    for (child = node->first(); child != nullptr; child = next)
    {
        next = child->next();
        delete_tree(child);
    }
    delete node;
}

bool Node::remove_attr(const char *name)
{
    return d_attr.remove(String::intern(name));
}

void Node::set_attr(const char *name, String *value)
{
    const String *sname = String::intern(name);
    Attribute **result, *attr;
    result = d_attr.lookup(sname);
    if (result == nullptr)
    {
        attr = new Attribute(sname);
        d_attr.insert(sname, attr);
    }
    else
        attr = *result;
    attr->set(value);
}

void Node::insert_after(Node *node, Node *new_node)
{
    if (node == nullptr)
        node = last();
    if (node == nullptr)
    {
        d_first = d_last = new_node;
        new_node->d_next = new_node->d_prev = nullptr;
    }
    else if (node == d_last)
    {
        d_last = new_node;
        node->d_next = new_node;
        new_node->d_prev = node;
        new_node->d_next = nullptr;
    }
    else
    {
        new_node->d_prev = node;
        new_node->d_next = node->d_next;
        new_node->d_prev->d_next = new_node;
        new_node->d_next->d_prev = new_node;
    }
    new_node->d_parent = this;
}

void Node::insert_before(Node *node, Node *new_node)
{
    if (node == nullptr)
        node = first();
    if (node == nullptr)
    {
        d_first = d_last = new_node;
        new_node->d_next = new_node->d_prev = nullptr;
    }
    else if (node == d_first)
    {
        d_first = new_node;
        node->d_prev = new_node;
        new_node->d_prev = nullptr;
        new_node->d_next = node;
    }
    else
    {
        new_node->d_prev = node->d_prev;
        new_node->d_next = node;
        new_node->d_prev->d_next = new_node;
        new_node->d_next->d_prev = new_node;
    }
    new_node->d_parent = this;
}

void Node::remove()
{
    if (d_parent == nullptr)
        return;
    if (d_next != nullptr)
        d_next->d_prev = d_prev;
    if (d_prev != nullptr)
        d_prev->d_next = d_next;
    if (d_parent->d_first == this)
        d_parent->d_first = d_next;
    if (d_parent->d_last == this)
        d_parent->d_last = d_prev;
    d_parent = d_next = d_prev = nullptr;
}
