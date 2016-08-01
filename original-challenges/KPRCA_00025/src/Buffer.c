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
#include "Buffer.h"

#define ASSERT_LENGTH(x) do { \
    if (this->m_pos + x > this->m_length) \
        raise(EXC_BAD_STATE); \
} while(0)

DefineClass(Buffer, Object)

DefineFunction(Buffer, void, $init)
{
    this->m_buf = NULL;
    this->m_length = 0;
    this->m_pos = 0;
}

DefineFunction(Buffer, void, $destroy)
{
    free(this->m_buf);
}

DefineFunction(Buffer, void, enlarge, size_t length)
{
    if (this->m_length >= length)
        return;

    this->m_length += (length + 0x1FFF) & ~0xFFF;
    this->m_buf = realloc(this->m_buf, this->m_length);
    ASSERT_ALLOC(this->m_buf);
}

DefineFunction(Buffer, void, seek, size_t pos)
{
    if (pos >= this->m_length)
        this->m_pos = this->m_length;
    else
        this->m_pos = pos;
}

DefineFunction(Buffer, size_t, tell)
{
    return this->m_pos;
}

DefineFunction(Buffer, void, write_u8, uint8_t data)
{
    $(this, enlarge, this->m_pos + 1);
    this->m_buf[this->m_pos++] = data;
}

DefineFunction(Buffer, void, write_u16, uint16_t data)
{
    $(this, enlarge, this->m_pos + 2);
    *(uint16_t *)&this->m_buf[this->m_pos] = data;
    this->m_pos += 2;
}

DefineFunction(Buffer, void, write_u32, uint32_t data)
{
    $(this, enlarge, this->m_pos + 4);
    *(uint32_t *)&this->m_buf[this->m_pos] = data;
    this->m_pos += 4;
}

DefineFunction(Buffer, void, write_number, int data)
{
    int neg = data < 0;
    if (neg)
        data = -data;

    $(this, enlarge, this->m_pos + 1);
    this->m_buf[this->m_pos++] = (neg << 6) | (data & 0x3F);
    data >>= 6;
    while (data)
    {
        this->m_buf[this->m_pos - 1] |= (1 << 7);
        $(this, enlarge, this->m_pos + 1);
        this->m_buf[this->m_pos++] = (data & 0x7F);
        data >>= 7;
    }
}

DefineFunction(Buffer, void, write_string, const char *str)
{
    unsigned int size = strlen(str);
    $(this, write_number, (int) size);
    $(this, enlarge, this->m_pos + size);
    memcpy(&this->m_buf[this->m_pos], str, size);
    this->m_pos += size;
}

DefineFunction(Buffer, void, write_bytes, const uint8_t *bytes, size_t size)
{
    $(this, write_number, (int) size);
    $(this, enlarge, this->m_pos + size);
    memcpy(&this->m_buf[this->m_pos], bytes, size);
    this->m_pos += size;
}

DefineFunction(Buffer, uint8_t, read_u8)
{
    ASSERT_LENGTH(1);

    return this->m_buf[this->m_pos++];
}

DefineFunction(Buffer, uint16_t, read_u16)
{
    ASSERT_LENGTH(2);

    uint16_t v = *(uint16_t *)&this->m_buf[this->m_pos];
    this->m_pos += 2;

    return v;
}

DefineFunction(Buffer, uint32_t, read_u32)
{
    ASSERT_LENGTH(1);

    uint32_t v = *(uint32_t *)&this->m_buf[this->m_pos];
    this->m_pos += 4;

    return v;
}

DefineFunction(Buffer, int, read_number)
{
    int neg, result = 0, shift;

    ASSERT_LENGTH(1);
    neg = this->m_buf[this->m_pos] & 0x40;
    result = this->m_buf[this->m_pos] & 0x3F;
    shift = 6;
    while (this->m_buf[this->m_pos++] & 0x80)
    {
        ASSERT_LENGTH(1);
        result |= (this->m_buf[this->m_pos] & 0x7F) << shift;
        shift += 7;
    }

    if (neg)
        result = -result;

    return result;
}

DefineFunction(Buffer, char *, read_string)
{
    int size = $(this, read_number);
    ASSERT_OR_RAISE(size >= 0, EXC_BAD_STATE);

    ASSERT_LENGTH(size);

    char *result = malloc(size + 1);
    ASSERT_ALLOC(result);

    memcpy(result, &this->m_buf[this->m_pos], size);
    result[size] = 0;
    this->m_pos += size;
    return result;
}

DefineFunction(Buffer, size_t, read_bytes, uint8_t *buf, size_t limit)
{
    int size, retval;
    size = retval = $(this, read_number);
    ASSERT_OR_RAISE(size >= 0, EXC_BAD_STATE);

    ASSERT_LENGTH(size);

    if (size > limit)
        size = limit;

    memcpy(buf, &this->m_buf[this->m_pos], size);
    this->m_pos += retval;
    return retval;
}

DefineFunction(Buffer, uint16_t, checksum)
{
    size_t i;
    uint16_t sum = 0xDEAD;

    for (i = 0; i < this->m_pos; i++)
        sum += this->m_buf[i];

    return sum;
}

DefineFunction(Buffer, int, dearmor, const char *asc)
{
    size_t i;
    uint16_t sum;

    if (strlen(asc) < 2)
        return 0;

    $(this, seek, SEEK_BEGIN);
    for (i = 0; i < strlen(asc)-1; i += 2)
    {
        uint8_t byte = (asc[i] - 'A') & 0xF;
        byte = (byte << 4) | ((asc[i+1] - 'A') & 0xF);
        $(this, write_u8, byte);
    }

    if (this->m_pos < 2)
        return 0;

    this->m_pos -= 2;
    sum = $(this, read_u16);
    this->m_pos -= 2;

    return sum == $(this, checksum);
}

DefineFunction(Buffer, char *, armor)
{
    char *result;
    size_t i, count;
    uint16_t sum;

    sum = $(this, checksum);
    $(this, write_u16, sum);

    count = this->m_pos * 2;
    result = malloc(count + 1);
    if (result == NULL)
        return NULL;

    $(this, seek, SEEK_BEGIN);
    for (i = 0; i < count; i += 2)
    {
        uint8_t byte = $(this, read_u8);
        result[i] = (byte >> 4) + 'A';
        result[i+1] = (byte & 0xF) + 'A';
    }
    result[i] = 0;

    return result;
}
