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
#include <new.h>

namespace std
{
    template <typename T>
    T* addressof(T& ref)
    {
        return reinterpret_cast<T*>(&reinterpret_cast<char&>(ref));
    }
};

template <class T>
class vector
{
public:
    vector() : size(0), allocated(0), items(nullptr) {};
    vector(unsigned int initial)
    {
        enlarge(initial);
    }
    vector(const vector &other)
    {
        size = other.size;
        allocated = other.size;
        if (size)
        {
            items = (T *)malloc(sizeof(T) * size);
            for (unsigned int i = 0; i < size; i++)
                items[i] = other.items[i];
        }
    }
    ~vector()
    {
        for (unsigned int i = 0; i < allocated; i++)
        {
            items[i].~T();
        }
        if (allocated)
        {
            free(items);
            items = nullptr;
        }
    }

    vector(vector &&) = delete;
    vector& operator=(const vector& other)
    {
        size = other.size;
        allocated = other.size;
        if (size)
        {
            items = (T *)malloc(sizeof(T) * size);
            for (unsigned int i = 0; i < size; i++)
                items[i] = other.items[i];
        }
        return *this;
    }

    unsigned int length() const
    {
        return size;
    }

    T& operator[] (unsigned int i)
    {
        if (i >= size)
            exit(1);
        return items[i];
    }

    const T& operator[] (unsigned int i) const
    {
        if (i >= size)
            exit(1);
        return items[i];
    }

    void push_back(const T& item)
    {
        if (size == allocated)
            enlarge(allocated == 0 ? 8 : allocated * 2);
        items[size++] = item;
    }

    void enlarge(unsigned int length)
    {
        if (length > allocated)
        {
            items = (T *)realloc(items, sizeof(T) * length);
            if (items == nullptr)
                exit(1);

            T *start = std::addressof(items[allocated]);
            T *end = std::addressof(items[length]);
            while (start < end)
            {
                new (start++) T();
            }

            allocated = length;
        }
    }

    void resize(unsigned int length)
    {
        enlarge(length);

        if (size < length)
        {
            // items are already set to default values
            size = length;
        }
        else
        {
            // clear items
            for (unsigned int i = length; i < size; i++)
                items[i] = T();
            size = length;
        }
    }
private:
    unsigned int size;
    unsigned int allocated;
    T *items;
};
