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
#include "cmlnode.h"
#include "textnode.h"
#include "parser.h"

// LEFT SEP* type [SEP+ name ASSIGN data]* SEP* RIGHT
// LEFT CLOSE SEP* type SEP* RIGHT

enum class State
{
    Begin,
    TextOrBegin,
    CloseOrTag,
    Tag,
    RightOrAttrName,
    AssignOrAttrName,
    AssignOrSep,
    ValueOrSep,
    Value,
    Eof,
};

Parser::Parser(char left, char right, char sep, char assign, char close, char escape)
    : d_left(left), d_right(right), d_sep(sep), d_assign(assign),
      d_close(close), d_escape(escape)
{
}

Node *Parser::parse(const char *ns, const char *input)
{
    bool escape = false, close_tag = false;
    const char *ptr = input;
    char *buf = d_buf;
    Node *root = nullptr, *node = nullptr, *new_node = nullptr;
    State st = State::Begin;
    const String *name;

#define COPY_CHAR { \
    if (!escape && *ptr == d_escape) \
    { \
        escape = true; \
        break; \
    } \
    *buf++ = *ptr; \
    escape = false; \
}
#define RESET_BUF buf = d_buf;
    while (*ptr)
    {
        switch (st)
        {
        case State::TextOrBegin:
            if (*ptr != d_left || escape)
            {
                COPY_CHAR
                break;
            }
            if (buf != d_buf)
            {
                // create text node
                *buf = 0;
                new_node = Node::create(nullptr, "");
                static_cast<TextNode*>(new_node)->set_text(String::create(d_buf));
                if (node)
                    node->insert_after(nullptr, new_node);
                RESET_BUF
            }
            st = State::Begin;
            // fall-through
        case State::Begin:
            if (*ptr != d_left)
                goto error;
            st = State::CloseOrTag;
            break;
        case State::CloseOrTag:
            if (*ptr == d_close)
            {
                close_tag = true;
                st = State::Tag;
                break;
            }
            close_tag = false;
            st = State::Tag;
            // fall-through
        case State::Tag:
            if (*ptr == d_left || *ptr == d_assign || *ptr == d_close)
                goto error;
            if (*ptr == d_right && !escape)
            {
                st = State::TextOrBegin;
            }
            else if (*ptr == d_sep && !escape)
            {
                st = State::RightOrAttrName;
            }
            else
            {
                COPY_CHAR
                break;
            }
            *buf = 0;
            if (d_buf[0] == 0)
                goto error;
            if (close_tag)
            {
                if (node == nullptr || strcmp(d_buf, node->tag()->cstr()) != 0)
                    goto error;
                RESET_BUF
                node = node->parent();
                if (node == nullptr)
                    st = State::Eof;
                break;
            }
#ifdef PATCHED_1
            if (node && node->cls() == NodeClass::CMLNODE)
#else
            if (node && node->tag() == CML_TAG)
#endif
                new_node = Node::create(static_cast<CmlNode*>(node)->childns()->cstr(), d_buf);
            else if (node)
                new_node = Node::create(node->ns()->cstr(), d_buf);
            else
                new_node = Node::create(ns, d_buf);
            if (node)
                node->insert_after(nullptr, new_node);
            if (root == nullptr)
                root = new_node;
            node = new_node;
            RESET_BUF
            break;
        case State::RightOrAttrName:
            if (*ptr == d_left || *ptr == d_assign || *ptr == d_close)
                goto error;
            else if (*ptr == d_sep)
                break;
            else if (*ptr == d_right)
            {
                st = State::TextOrBegin;
                break;
            }
            if (close_tag)
                goto error;
            st = State::AssignOrAttrName;
            COPY_CHAR
            break;
        case State::AssignOrAttrName:
            if (!escape)
            {
                if (*ptr == d_left || *ptr == d_right || *ptr == d_close)
                    goto error;
                if (*ptr == d_sep)
                {
                    st = State::AssignOrSep;
                    break;
                }
                if (*ptr == d_assign)
                {
                    st = State::ValueOrSep;
                    *buf = 0;
                    name = String::intern(d_buf);
                    RESET_BUF
                    break;
                }
            }
            COPY_CHAR
            break;
        case State::AssignOrSep:
            if (*ptr == d_sep)
                break;
            else if (*ptr != d_assign)
                goto error;
            st = State::ValueOrSep;
            *buf = 0;
            name = String::intern(d_buf);
            RESET_BUF
            break;
        case State::ValueOrSep:
            if (!escape)
            {
                if (*ptr == d_left || *ptr == d_right || *ptr == d_close || *ptr == d_assign)
                    goto error;
                if (*ptr == d_sep)
                    break;
            }
            st = State::Value;
            COPY_CHAR
            break;
        case State::Value:
            if (!escape)
            {
                if (*ptr == d_left || *ptr == d_close || *ptr == d_assign)
                    goto error;
                if (*ptr == d_sep)
                {
                    st = State::RightOrAttrName;
                    *buf = 0;
                    node->set_attr(name->cstr(), String::create(d_buf));
                    RESET_BUF
                    break;
                }
                if (*ptr == d_right)
                {
                    st = State::TextOrBegin;
                    *buf = 0;
                    node->set_attr(name->cstr(), String::create(d_buf));
                    RESET_BUF
                    break;
                }
            }
            COPY_CHAR
            break;
        case State::Eof:
            goto error;
        }
        ptr++;
        if (buf == &d_buf[MAX_LENGTH+1])
            goto error;
    }
    if (escape || st != State::Eof)
    {
error:
        if (root != nullptr)
            Node::delete_tree(root);
        return nullptr;
    }
    return root;
}
