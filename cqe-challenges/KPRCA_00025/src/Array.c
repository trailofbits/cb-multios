/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "Array.h"

DefineClass(Array, Object)

DefineFunction(Array, void, $init)
{
    this->m_size = this->m_count = 0;
    this->m_elements = NULL;
}

DefineFunction(Array, void, enlarge, size_t min_count)
{
    if (this->m_size >= min_count)
        return;

    this->m_size = min_count * 15 / 10;
    if (this->m_size < min_count)
        this->m_size = min_count;

    this->m_elements = realloc(this->m_elements, this->m_size * sizeof(this->m_elements[0]));
    ASSERT_ALLOC(this->m_elements);
}

DefineFunction(Array, void, push, void *o)
{
    $(this, enlarge, this->m_count+1);
    this->m_elements[this->m_count++] = o;
}

DefineFunction(Array, void *, pop)
{
    if (this->m_count == 0)
        return NULL;

    return this->m_elements[--this->m_count];
}

DefineFunction(Array, void, set, size_t idx, void *o)
{
    $(this, enlarge, idx+1);

    while (idx >= this->m_count)
    {
        this->m_elements[this->m_count++] = NULL;
    }

    this->m_elements[idx] = o;
}

DefineFunction(Array, void *, get, size_t idx)
{
    if (idx >= this->m_count)
        return NULL;

    return this->m_elements[idx];
}

DefineFunction(Array, void *, remove, size_t idx)
{
    if (idx >= this->m_count)
        return NULL;

    void *o = this->m_elements[idx];
    this->m_count--;

    memmove(&this->m_elements[idx], &this->m_elements[idx+1], (this->m_count - idx) * sizeof(void *));
    return o;
}
