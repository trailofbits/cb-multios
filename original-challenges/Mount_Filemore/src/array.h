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

#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstdlib.h>

template <typename T>
class Array
{
  public:
    Array();
    void Append(const T &item);
    void Pop();
    unsigned int length() const;
    T& operator[] (unsigned int idx);
    void Clear();

   private:
    T *data_;
    unsigned int length_;
    unsigned int size_;

    void Init();
};

template <typename T>
Array<T>::Array()
{
    data_ = (T *)NULL;
    length_ = 0;
    size_ = 0;
}

template <typename T>
void Array<T>::Append(const T &item)
{
    if (!data_)
        Init();

    if (length_ == size_) {
        size_ *= 2;
        T *data_copy = new T[size_];
        memcpy(data_copy, data_, sizeof(T) * length_);
        delete[] data_;
        data_ = data_copy;
    }

    data_[length_++] = item;
}

template <typename T>
void Array<T>::Pop()
{
    if (length_)
        --length_;
}

template <typename T>
unsigned int Array<T>::length() const
{
    return length_;
}

template <typename T>
T& Array<T>::operator[] (unsigned int idx)
{
    if (!data_)
        Init();

    if (idx >= length_)
        return data_[0];

    return data_[idx];
}

template <typename T>
void Array<T>::Clear()
{
    if (data_)
        delete[] data_;

    data_ = (T *)NULL;
    length_ = 0;
    size_ = 0;
}

template <typename T>
void Array<T>::Init()
{
    if (!data_)
    {
        length_ = 0;
        size_ = 2;
        data_ = new T[size_];
    }
}
#endif
