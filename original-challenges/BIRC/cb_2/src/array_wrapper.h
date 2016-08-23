/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#ifndef ARRAY_WRAPPER_H_
#define ARRAY_WRAPPER_H_
#include <cstdio.h>
#include <cstring.h>

template <typename T>
class ArrayWrapper {
  public:
    ArrayWrapper(size_t max_size);
    ArrayWrapper(T *array, size_t max_size);
    ArrayWrapper(T *array, size_t max_size, size_t length);
    bool IsEmpty() const;
    bool IsFull() const;
    const T &Get(size_t idx) const;
    bool Set(size_t idx, const T &item);
    void Pop();
    void Remove(size_t idx, void (*delete_fn)(T*));
    bool Append(const T &item);
    void ForceAppend(const T &item, void (*delete_fn)(T*));
    void DeleteArray(void (*delete_fn)(T*));

    const size_t length() const;
    T *data();

  private:
    size_t size_;
    size_t length_;
    T *data_;
};


template <typename T>
ArrayWrapper<T>::ArrayWrapper(size_t max_size) {
    size_ = max_size;
    length_ = 0;
    data_ = new T[max_size];
}

template <typename T>
ArrayWrapper<T>::ArrayWrapper(T *array, size_t max_size) {
    size_ = max_size;
    length_ = 0;
    data_ = array;
}

template <typename T>
ArrayWrapper<T>::ArrayWrapper(T *array, size_t max_size, size_t length) {
    size_ = max_size;
    length_ = length;
    data_ = array;
}

template <typename T>
bool ArrayWrapper<T>::IsEmpty() const {
    return (length_ == 0);
}

template <typename T>
bool ArrayWrapper<T>::IsFull() const {
    return (length_ == size_);
}

template <typename T>
const T &ArrayWrapper<T>::Get(size_t idx) const {
    if (idx >= length_)
        return data_[0];

    return data_[idx];
}

template <typename T>
bool ArrayWrapper<T>::Set(size_t idx, const T &item) {
    if (idx >= length_)
        return false;

    data_[idx] = item;
    return true;
}


template <typename T>
bool ArrayWrapper<T>::Append(const T &item) {
    if (length_ >= size_)
        return false;

    data_[length_++] = item;
    return true;
}

template <typename T>
void ArrayWrapper<T>::Pop() {
    if (length_)
        --length_;
}

template <typename T>
void ArrayWrapper<T>::Remove(size_t idx, void (*delete_fn)(T*)) {
    if (idx > length_ || !length_)
        return;

    if (delete_fn)
        delete_fn(&data_[idx]);
    if (length_ > 1 && idx < length_ - 1) {
        memmove(&data_[idx], &data_[idx+1], (--length_ - idx) * sizeof(T));
    }
    else {
        --length_;
    }
}

template <typename T>
void ArrayWrapper<T>::ForceAppend(const T &item, void (*delete_fn)(T*)) {
    if (length_ >= size_ && length_ > 1) {
        if (delete_fn)
            delete_fn(&data_[0]);
        memmove(&data_[0], &data_[1], --length_ * sizeof(T));
    }

    data_[length_++] = item;
}

template <typename T>
void ArrayWrapper<T>::DeleteArray(void (*delete_fn)(T*)) {
    size_ = 0;
    length_ = 0;
    if (delete_fn) {
        for (int i = 0; i < length_; i++)
            delete_fn(&data_[i]);
    }

    delete[] data_;
}

template <typename T>
const size_t ArrayWrapper<T>::length() const {
    return length_;
}

template <typename T>
T *ArrayWrapper<T>::data() {
    return data_;
}

#endif /* ARRAY_WRAPPER_H_ */
