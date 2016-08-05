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

static const String *NAMESPACE_ATTR = String::intern("namespace");
static const String *SPEC_ATTR = String::intern("spec");
static const String *VERSION_ATTR = String::intern("version");

CmlNode::CmlNode(const String *ns, const String *tag)
    : Node(ns, tag, NodeClass::CMLNODE)
{
    d_spec = String::intern("");
    d_version = String::intern("1.0");
    d_childns = String::intern("");
}

void CmlNode::set_attr(const char *name, String *value)
{
    Node::set_attr(name, value);

    const String *sname = String::intern(name);
    if (sname == NAMESPACE_ATTR)
    {
        d_childns = value;
    }
    else if (sname == SPEC_ATTR)
    {
        d_spec = value;
    }
    else if (sname == VERSION_ATTR)
    {
        char *end;
        unsigned int major, minor = 0;
        major = strtoul(value->cstr(), &end, 10);
        if (end != NULL)
        {
            end++;
            minor = strtoul(end, &end, 10);
        }
        d_version = value;
        d_version_code = ((unsigned long long)major << 32) | minor;
    }
}
