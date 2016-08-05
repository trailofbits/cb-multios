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

#include "hashmap.h"
#include "stringmanager.h"

class String
{
private:
    String(const char *str);
    inline ~String() {}
public:
    static String *create(const char *str);
    static inline const String *intern(const char *str)
    {
        return StringManager::get().intern(str);
    }

    inline const char *cstr() const { return d_data; }
    inline void destroy() { free(this); }
private:
    char d_data[];
};

class StringComparator
{
public:
    static inline unsigned int hash(const String *s)
    {
        return CStringComparator::hash(s->cstr());
    }
    static inline bool equals(const String *a, const String *b)
    {
        return CStringComparator::equals(a->cstr(), b->cstr());
    }
};

class InternedComparator
{
public:
    static inline unsigned int hash(const String *s)
    {
        intptr_t p = reinterpret_cast<intptr_t>(s);
        return (p * 761886451) ^ (p << 16);
    }
    static inline bool equals(const String *a, const String *b)
    {
        return a == b;
    }
};
