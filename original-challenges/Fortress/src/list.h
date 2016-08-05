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

#pragma once

#include <cstdlib.h>

template <typename T>
class CList
{
    public:
        CList() : m_head(NULL), m_size(0) {}
        CList(const CList<T> & l);
        ~CList();

        size_t GetSize() const { return m_size; }
        bool IsEmpty() const { return m_size == 0; }
        T GetAt(int idx) const ;

        void Append(T item);
        void InsertAt(T item, int idx);
        T RemoveAt(int idx);
        void Remove(T item);
        bool Has(T item);

    private:
        class CNode {
            friend class CList<T>;
            private:
                T m_data;
                CNode *m_next;
            public:
                CNode(T data, CNode *next) : m_data(data), m_next(next) {}
        };

        CNode *m_head;
        size_t m_size;
};

template <typename T>
CList<T>::CList(const CList<T> &l) : m_head(NULL), m_size(0)
{
    CNode *cur = l.m_head;
    while (cur)
    {
        this->Append(cur->m_data);
        cur = cur->m_next;
    }
}

template <typename T>
CList<T>::~CList()
{
    while (!this->IsEmpty())
        this->RemoveAt(0);
}

template <typename T>
void CList<T>::Append(T d)
{
    CNode *node = new CNode(d, NULL);
    if (this->IsEmpty())
        m_head = node;
    else
    {
        CNode *cur = m_head;
        while (cur->m_next)
            cur = cur->m_next;
        cur->m_next = node;
    }
    m_size++;
}

template <typename T>
void CList<T>::InsertAt(T d, int idx)
{
    CNode *cur = m_head, *prev = NULL;
    if (idx > m_size)
        return;
    if (idx == m_size)
    {
        this->Append(d);
        return;
    }
    while (idx--)
    {
        prev = cur;
        cur = cur->m_next;
    }
    CNode *node = new CNode(d, cur);
    if (prev)
        prev->m_next = node;
}

template <typename T>
T CList<T>::GetAt(int idx) const
{
    CNode *cur = m_head;
    if (idx >= m_size)
        return NULL;
    while (idx--)
        cur = cur->m_next;
    return cur->m_data;
}

template <typename T>
T CList<T>::RemoveAt(int idx)
{
    CNode *cur = m_head, *prev = NULL;
    if (idx >= m_size)
        return  NULL;
    while (idx--)
    {
        prev = cur;
        cur = cur->m_next;
    }
    if (prev)
        prev->m_next = cur->m_next;
    else
        m_head = cur->m_next;
    m_size--;
    T& d = cur->m_data;
    delete cur;
    return d;
}

template <typename T>
void CList<T>::Remove(T item)
{
    CNode *cur = m_head, *prev = NULL;
    if (IsEmpty())
        return;
    while (cur)
    {
        if (cur->m_data == item)
        {
            if (cur == m_head)
                m_head = cur->m_next;
            else
                prev->m_next = cur->m_next;
            m_size--;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->m_next;
    }
}

template <typename T>
bool CList<T>::Has(T item)
{
    CNode *cur = m_head;
    if (IsEmpty())
        return false;
    while (cur)
    {
        if (cur->m_data == item)
            return true;
        cur = cur->m_next;
    }
    return false;
}
