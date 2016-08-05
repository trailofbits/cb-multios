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

template <class T>
class shared_ptr
{
private:
    struct cb
    {
        cb(T* p) : _p(p), use_count(0) {}
        ~cb()
        {
            delete _p;
        }

        T* _p;
        size_t use_count;
    };
public:
    shared_ptr() : _p(nullptr), _cb(nullptr) {}
    explicit shared_ptr(T* p) : shared_ptr()
    {
        reset(p);
    }
    ~shared_ptr()
    {
        reset(nullptr);
    }
    shared_ptr(const shared_ptr& other)
    {
        _p = other._p;
        _cb = other._cb;
        if (_cb != nullptr)
            _cb->use_count++;
    }
    shared_ptr& operator=(const shared_ptr& other)
    {
        reset(nullptr);
        _p = other._p;
        _cb = other._cb;
        if (_cb != nullptr)
            _cb->use_count++;
        return *this;
    }
    void reset(T* p)
    {
        if (_cb != nullptr)
        {
            _cb->use_count--;
            if (_cb->use_count == 0)
            {
                delete _cb;
            }
        }
        _p = p;
        if (_p != nullptr)
        {
            _cb = new cb(_p);
            _cb->use_count++;
        }
    }
    T* get() const
    {
        return _p;
    }
    explicit operator bool() const
    {
        return _p != nullptr;
    }
private:
    T* _p;
    cb* _cb;
};
