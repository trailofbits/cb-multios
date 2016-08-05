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
#include "map.h"
#include "unique_ptr.h"

// simple wrapper around a null-terminated string
class CString
{
public:
    CString() : ptr(nullptr) {}
    CString(const char *str) : ptr(str) {}
    CString(const CString& other)
    {
        if (other._ptr)
        {
            ptr = other.ptr;
            ensure();
        }
        else
        {
            _ptr.reset(nullptr);
            ptr = other.ptr;
        }
    }
    CString(CString&& other)
    {
        _ptr.reset(other._ptr.release());
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    CString& operator=(const CString& other)
    {
        if (other._ptr)
        {
            ptr = other.ptr;
            ensure();
        }
        else
        {
            _ptr.reset(nullptr);
            ptr = other.ptr;
        }
        return *this;
    }
    CString& operator=(CString&& other)
    {
        _ptr.reset(other._ptr.release());
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    bool operator==(const CString& other) const
    {
        return strcmp(ptr, other.ptr) == 0;
    }

    CString& ensure()
    {
        if (!_ptr)
        {
            size_t len = length() + 1;
            _ptr.reset(new char [len]);
            memcpy(_ptr.get(), ptr, len);
            ptr = _ptr.get();
        }
        return *this;
    }

    const char *c_str() const
    {
        return ptr;
    }

    size_t hash() const;
    size_t length() const
    {
        return strlen(ptr);
    }
private:
    const char *ptr;
    unique_ptr<char[]> _ptr;
};

template <>
struct hash<CString>
{
    size_t operator() (const CString& t)
    {
        return t.hash();
    }
};

