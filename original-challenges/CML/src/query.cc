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
#include "query.h"

static uint16_t swap16(uint16_t x)
{
    return (x >> 8) | (x << 8);
}

Query::Query(const unsigned char *src, unsigned int length)
{
    d_insn[0].d_op = Op::ERROR;

    parse(src, length);
}

Query::~Query()
{
    destroy_insns();
}

void Query::destroy_insns()
{
    for (unsigned int i = 0; i < MAX_DEPTH + 1; i++)
    {
        if (d_insn[i].d_op == Op::ERROR || d_insn[i].d_op == Op::RETURN)
            break;
        switch (d_insn[i].d_op)
        {
        // just here to prevent compiler warnings
        case Op::ERROR:
        case Op::RETURN:
            break;
        case Op::ANCESTORS:
        case Op::DESCENDANTS:
        case Op::PARENT:
        case Op::CHILDREN:
        case Op::SIBLINGS:
        case Op::INDEX:
            break;
        case Op::TAG:
        case Op::NAMESPACE:
            d_insn[i].d_op1_s->destroy();
            break;
        case Op::ATTRIBUTE:
            d_insn[i].d_op1_s->destroy();
            d_insn[i].d_op2_s->destroy();
            break;
        }
    }
    d_insn[0].d_op = Op::ERROR;
}

void Query::parse(const unsigned char *str, unsigned int length)
{
    unsigned int i = 0;
    Instruction *cur = &d_insn[0];
    while (i < length)
    {
        const unsigned char *end;
        if (cur == &d_insn[MAX_DEPTH])
        {
            d_error = Error::RECURSION;
            return;
        }
        cur->d_op = static_cast<Op>(str[i]);
        switch (cur->d_op)
        {
        default:
        case Op::ERROR:
        case Op::RETURN:
            goto invalid;
        case Op::ANCESTORS:
        case Op::DESCENDANTS:
        case Op::PARENT:
        case Op::CHILDREN:
        case Op::SIBLINGS:
            i++;
            break;
        case Op::INDEX:
            i++;
            if (length - i < 2)
                goto invalid;
            cur->d_op1_u = swap16(*(uint16_t *)&str[i]);
            i += 2;
            break;
        case Op::TAG:
        case Op::NAMESPACE:
            i++;
            end = static_cast<const unsigned char *>(memchr(&str[i], 0, length - i));
            if (end == nullptr)
                goto invalid;
            cur->d_op1_s = String::create(reinterpret_cast<const char *>(&str[i]));
            i += end - &str[i] + 1;
            break;
        case Op::ATTRIBUTE:
            i++;
            end = static_cast<const unsigned char *>(memchr(&str[i], 0, length - i));
            if (end == nullptr)
                goto invalid;
            cur->d_op1_s = String::create(reinterpret_cast<const char *>(&str[i]));
            i += end - &str[i] + 1;

            end = static_cast<const unsigned char *>(memchr(&str[i], 0, length - i));
            if (end == nullptr)
                goto invalid;
            cur->d_op2_s = String::create(reinterpret_cast<const char *>(&str[i]));
            i += end - &str[i] + 1;
            break;
        }
        cur++;
    }
    cur->d_op = Op::RETURN;
    d_error = Error::SUCCESS;
    return;

invalid:
    d_error = Error::INVALID;
    d_insn[0].d_op = Op::ERROR;
    return;
}

Node *Query::apply(Node *root, Instruction *cur, unsigned int index)
{
    Attribute *attr;
    Node *node, *child;
    if (d_depth == MAX_RECURSION)
    {
        d_error = Error::RECURSION;
        return nullptr;
    }
    if (static_cast<int>(cur->d_op) & 0x80)
    {
        // test
        switch (cur->d_op)
        {
        case Op::RETURN:
            d_error = Error::SUCCESS;
            return root;
        case Op::TAG:
            if (strcmp(root->tag()->cstr(), cur->d_op1_s->cstr()) != 0)
                return nullptr;
            break;
        case Op::NAMESPACE:
            if (root->ns() == nullptr || strcmp(root->ns()->cstr(), cur->d_op1_s->cstr()) != 0)
                return nullptr;
            break;
        case Op::ATTRIBUTE:
            attr = root->get_attr(cur->d_op1_s->cstr());
            if (attr == nullptr || strcmp(attr->get()->cstr(), cur->d_op2_s->cstr()) != 0)
                return nullptr;
            break;
        case Op::INDEX:
            if (cur->d_op1_u != index)
                return nullptr;
            break;
        default:
            goto invalid;
        }
        d_depth++;
        node = apply(root, cur + 1, index);
        d_depth--;
        return node;
    }
    else
    {
        // target
        if (cur->d_op == Op::ANCESTORS)
        {
            if (root->parent() == nullptr)
                return nullptr;
            d_depth++;
            node = apply(root->parent(), cur + 1, 0);
            d_depth--;
            if (node != nullptr)
                return node;
            d_depth++;
            node = apply(root->parent(), cur, 0);
            d_depth--;
            return node;
        }
        else if (cur->d_op == Op::PARENT)
        {
            if (root->parent() == nullptr)
                return nullptr;
            d_depth++;
            node = apply(root->parent(), cur + 1, 0);
            d_depth--;
            return node;
        }
        else if (cur->d_op == Op::DESCENDANTS)
        {
            for (child = root->first(); child != nullptr; child = child->next())
            {
                d_depth++;
                node = apply(child, cur + 1, 0);
                d_depth--;
                if (node != nullptr)
                    return node;
            }
            for (child = root->first(); child != nullptr; child = child->next())
            {
                d_depth++;
                node = apply(child, cur, 0);
                d_depth--;
                if (node != nullptr)
                    return node;
            }
            return nullptr;
        }
        else if (cur->d_op == Op::CHILDREN)
        {
            index = 0;
            for (child = root->first(); child != nullptr; child = child->next())
            {
                d_depth++;
                node = apply(child, cur + 1, index++);
                d_depth--;
                if (node != nullptr)
                    return node;
            }
            return nullptr;
        }
        else if (cur->d_op == Op::SIBLINGS)
        {
            if (root->parent() == nullptr)
                return nullptr;
            index = 0;
            for (child = root->parent()->first(); child != nullptr; child = child->next())
            {
                d_depth++;
                node = apply(child, cur + 1, index++);
                d_depth--;
                if (node != nullptr)
                    return node;
            }
            return nullptr;
        }
        else
        {
            goto invalid;
        }
    }
invalid:
    d_error = Error::INVALID;
    return nullptr;
}

Node *Query::match(Node *root)
{
    d_depth = 0;
    d_error = Error::NOT_FOUND;
    return apply(root, &d_insn[0], 0);
}
