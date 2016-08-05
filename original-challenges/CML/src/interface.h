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
#include <cstdio.h>
#include "hashmap.h"
#include "node.h"
#include "parser.h"

enum class Error
{
    SUCCESS = 0,
    INVALID_OP = 1,
    INVALID_DESC = 2,
    NOT_READY = 3,
    INVALID_DATA = 4,
    NOT_FOUND = 5
};

class Interface
{
private:
    Node *get_node();
    char *get_string();
    unsigned char *get_string_binary(uint16_t *psize);
    unsigned int new_descriptor(Node *node);
    void send_error(Error error);
    void send_descriptor(unsigned int desc);
    void send_string(const char *str);

    bool op_init_parser();
    bool op_load_data();
    bool op_get_attr();
    bool op_set_attr();
    bool op_list_attr();
    bool op_get_tag();
    bool op_get_ns();
    bool op_query();
    bool op_version_check();
public:
    Interface(FILE *input, FILE *output);

    bool process();
private:
    FILE *d_in, *d_out;
    unsigned int d_next;
    HashMap<unsigned int, Node *, UIntComparator> d_descriptors;    
    Parser *d_parser;
};
