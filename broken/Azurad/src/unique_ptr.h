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

#include <algorithm.h>

// XXX not really an implementation of unqiue_ptr, just something simple
template <class T>
class unique_ptr
{
public:
    unique_ptr() : _p(nullptr) {}
    unique_ptr(T* p) : _p(p) {}
    ~unique_ptr()
    {
        if (_p != nullptr)
            delete _p;
    }
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr(unique_ptr&& other)
    {
        reset(other.release());
    }
    unique_ptr& operator=(unique_ptr&& other)
    {
        reset(other.release());
        return *this;
    }
    T* release()
    {
        T* p = _p;
        _p = nullptr;
        return p;
    }
    T* get() const
    {
        return _p;
    }
    void reset(T* p)
    {
        T* old = _p;
        _p = p;
        if (old != nullptr)
            delete old;
    }
    T* operator->() const
    {
        return _p;
    }
    explicit operator bool() const
    {
        return _p != nullptr;
    }
private:
    T* _p;
};

template <class T>
class unique_ptr<T[]>
{
public:
    unique_ptr() : _p(nullptr) {}
    unique_ptr(T* p) : _p(p) {}
    ~unique_ptr()
    {
        if (_p != nullptr)
            delete[] _p;
    }
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr(unique_ptr&& other)
    {
        reset(other.release());
    }
    unique_ptr& operator=(unique_ptr&& other)
    {
        reset(other.release());
        return *this;
    }
    T* release()
    {
        T* p = _p;
        _p = nullptr;
        return p;
    }
    T* get() const
    {
        return _p;
    }
    void reset(T* p)
    {
        T* old = _p;
        _p = p;
        if (old != nullptr)
            delete[] old;
    }
    explicit operator bool() const
    {
        return _p != nullptr;
    }
private:
    T* _p;
};
