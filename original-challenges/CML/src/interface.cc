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
#include <cstdlib.h>
#include <cstdint.h>
#include "cmlnode.h"
#include "interface.h"
#include "query.h"
#include "smalloc.h"

enum class Op
{
    INIT = 0,
    LOAD_DATA = 1,
    GET_ATTR = 2,
    SET_ATTR = 3,
    LIST_ATTR = 4,
    GET_TAG = 5,
    GET_NS = 6,
    QUERY = 7,
    VERSION_CHECK = 8
};

static uint16_t swap16(uint16_t x)
{
    return (x >> 8) | (x << 8);
}

#ifdef DEBUG
static void print_node(Node *root, int depth)
{
    char tmp[32];
    Attribute **pattr = nullptr;
    memset(tmp, '\t', depth);
    tmp[depth] = 0;
    fprintf(stderr, "%s+ %08X [%s] %s\n", tmp, root, root->ns() == nullptr ? "default" : root->ns()->cstr(), root->tag()->cstr());
    if (root->cls() == NodeClass::TEXTNODE)
        fprintf(stderr, "%s  \"%s\"\n", tmp, reinterpret_cast<TextNode*>(root)->text());
    while ((pattr = root->attr().next(pattr)) != nullptr)
    {
        fprintf(stderr, "%s  %s = \"%s\"\n", tmp, (*pattr)->name()->cstr(), (*pattr)->get()->cstr());
    }
    for (Node *child = root->first(); child != nullptr; child = child->next())
    {
        print_node(child, depth + 1);
    }
}
#endif

Interface::Interface(FILE *input, FILE *output)
    : d_in(input), d_out(output), d_next(0)
{
    fbuffered(d_out, 1);
}

void Interface::send_descriptor(unsigned int desc)
{
    fwrite(&desc, sizeof(desc), d_out);
}

void Interface::send_error(Error error)
{
    unsigned char code = static_cast<unsigned char>(error);
    fwrite(&code, sizeof(code), d_out);
}

void Interface::send_string(const char *str)
{
    uint16_t size = strlen(str);
    uint16_t size_s = swap16(size);
    fwrite(&size_s, sizeof(size_s), d_out);
    fwrite(str, size, d_out);
}

Node *Interface::get_node()
{
    unsigned int desc;
    if (fread(&desc, sizeof(desc), d_in) != sizeof(desc))
        return nullptr;
    Node **result = d_descriptors.lookup(desc);
    return result == nullptr ? nullptr : *result;
}

unsigned char *Interface::get_string_binary(uint16_t *psize)
{
    uint16_t size;
    unsigned char *data;
    if (fread(&size, sizeof(size), d_in) != sizeof(size))
        return nullptr;
    size = swap16(size);
    data = static_cast<unsigned char *>(safe_malloc(size));
    if (fread(data, size, d_in) != size)
    {
        free(data);
        return nullptr;
    }
    *psize = size;
    return data;
}

char *Interface::get_string()
{
    uint16_t size;
    char *data;
    if (fread(&size, sizeof(size), d_in) != sizeof(size))
        return nullptr;
    size = swap16(size);
    data = static_cast<char *>(safe_malloc(size + 1));
    if (fread(data, size, d_in) != size)
    {
        free(data);
        return nullptr;
    }
    data[size] = 0;
    return data;
}

unsigned int Interface::new_descriptor(Node *node)
{
    unsigned int desc = ++d_next;
    d_descriptors.insert(desc, node);
    return desc;
}

bool Interface::process()
{
    unsigned char op;
    if (fread(&op, sizeof(op), d_in) != sizeof(op))
        return false;
#define DO_OP(x, y) case Op::x: if (! y ()) return false; break;
    switch (static_cast<Op>(op))
    {
    DO_OP(INIT, op_init_parser)
    DO_OP(LOAD_DATA, op_load_data)
    DO_OP(GET_ATTR, op_get_attr)
    DO_OP(SET_ATTR, op_set_attr)
    DO_OP(LIST_ATTR, op_list_attr)
    DO_OP(GET_TAG, op_get_tag)
    DO_OP(GET_NS, op_get_ns)
    DO_OP(QUERY, op_query)
    DO_OP(VERSION_CHECK, op_version_check)
    default:
        send_error(Error::INVALID_OP);
        break;
    }
#undef DO_OP
    fflush(d_out);
    return true;
}

bool Interface::op_load_data()
{
    char *data;
    Node *node;
    data = get_string();
    if (data == nullptr)
    {
        return false;
    }
    if (d_parser == nullptr)
    {
        send_error(Error::NOT_READY);
        goto done;
    }
    node = d_parser->parse(data);
    if (node == nullptr)
    {
        send_error(Error::INVALID_DATA);
        goto done;
    }
    send_error(Error::SUCCESS);
    send_descriptor(new_descriptor(node));
done:
    free(data);
    return true;
}

bool Interface::op_get_attr()
{
    Node *node = get_node();
    char *name = get_string();
    if (node == nullptr)
    {
        free(name);
        send_error(Error::INVALID_DESC);
        return true;
    }
    if (name == nullptr)
        return false;
    Attribute *attr = node->get_attr(name);
    free(name);
    if (attr == nullptr)
    {
        send_error(Error::NOT_FOUND);
        return true;
    }
    send_error(Error::SUCCESS);
    send_string(attr->get()->cstr());
    return true;
}

bool Interface::op_set_attr()
{
    Node *node = get_node();
    char *name = get_string();
    char *value = get_string();
    if (node == nullptr)
    {
        free(name);
        free(value);
        send_error(Error::INVALID_DESC);
        return true;
    }
    if (name == nullptr || value == nullptr)
        return false;
    node->set_attr(name, String::create(value));
    free(name);
    free(value);
    send_error(Error::SUCCESS);
    return true;
}

bool Interface::op_init_parser()
{
    unsigned char chr[6];
    if (fread(chr, sizeof(chr), d_in) != sizeof(chr))
        return false;
    // check for duplicates
    for (unsigned int i = 0; i < sizeof(chr) - 1; i++)
    {
        if (memchr(&chr[i + 1], chr[i], sizeof(chr) - i - 1) != nullptr)
        {
            send_error(Error::INVALID_DATA);
            return true;
        }
    }
    d_parser = new Parser(chr[0], chr[1], chr[2], chr[3], chr[4], chr[5]);
    send_error(Error::SUCCESS);
    return true;
}

bool Interface::op_list_attr()
{
    Node *node = get_node();
    if (node == nullptr)
    {
        send_error(Error::INVALID_DESC);
        return true;
    }
    uint16_t size = node->attr().length();
    uint16_t size_s = swap16(size);
    send_error(Error::SUCCESS);
    fwrite(&size_s, sizeof(size_s), d_out);
    Attribute **pattr = nullptr;
    while ((pattr = node->attr().next(pattr)) != nullptr)
    {
        send_string((*pattr)->name()->cstr());
    }
    return true;
}

bool Interface::op_get_tag()
{
    Node *node = get_node();
    if (node == nullptr)
    {
        send_error(Error::INVALID_DESC);
        return true;
    }
    send_error(Error::SUCCESS);
    send_string(node->tag()->cstr());
    return true;
}

bool Interface::op_get_ns()
{
    Node *node = get_node();
    if (node == nullptr)
    {
        send_error(Error::INVALID_DESC);
        return true;
    }
    if (node->ns() == nullptr)
    {
        send_error(Error::NOT_FOUND);
    }
    else
    {
        send_error(Error::SUCCESS);
        send_string(node->ns()->cstr());
    }
    return true;
}

bool Interface::op_query()
{
    Node *node = get_node();
    if (node == nullptr)
    {
        send_error(Error::INVALID_DESC);
        return true;
    }
    uint16_t size;
    unsigned char *data = get_string_binary(&size);
    if (data == nullptr)
    {
        return false;
    }
    Query qs(data, size);
    if (qs.error() != Query::Error::SUCCESS)
    {
        send_error(Error::INVALID_DATA);
        return true;
    }
    Node *result = qs.match(node);
    if (result == nullptr || qs.error() != Query::Error::SUCCESS)
    {
        send_error(Error::NOT_FOUND);
        return true;
    }
    send_error(Error::SUCCESS);
    send_descriptor(new_descriptor(result));
    return true;
}

bool Interface::op_version_check()
{
    Node *node = get_node();
    if (node == nullptr)
    {
        send_error(Error::INVALID_DESC);
        return true;
    }
    if (node->cls() != NodeClass::CMLNODE)
    {
        send_error(Error::INVALID_DATA);
        return true;
    }
    unsigned long long v = static_cast<CmlNode*>(node)->version_code();
    if (v == *(unsigned long long *)0x4347C001)
    {
        send_error(Error::SUCCESS);
    }
    else
    {
        send_error(Error::NOT_FOUND);
    }
    return true;
}
