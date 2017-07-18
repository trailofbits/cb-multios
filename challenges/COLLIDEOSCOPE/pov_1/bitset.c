/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_bitset.h"

static int cgc_bitset_set_bit_value(struct bitset *, unsigned int, int);

void
cgc_bitset_init(struct bitset *bitset, cgc_size_t size)
{
    bitset->size = size;
    cgc_bitset_clear(bitset);
}

void
cgc_bitset_clear(struct bitset *bitset)
{
    cgc_memset(bitset->data, '\0', ALIGN(bitset->size, 8) / 8);
}

static int
cgc_bitset_set_bit_value(struct bitset *bitset, unsigned int bit, int value)
{
    unsigned int index = bit / 8;
    unsigned char mask = 1 << (bit % 8);

    if (bit > bitset->size)
        return EXIT_FAILURE;

    if (value)
        bitset->data[index] |= mask;
    else
        bitset->data[index] &= ~mask;

    return EXIT_SUCCESS;
}

int
cgc_bitset_set_bit(struct bitset *bitset, unsigned int bit)
{
    return cgc_bitset_set_bit_value(bitset, bit, 1);
}

int
cgc_bitset_clear_bit(struct bitset *bitset, unsigned int bit)
{
    return cgc_bitset_set_bit_value(bitset, bit, 0);
}

int
cgc_bitset_get_bit(struct bitset *bitset, unsigned int bit)
{
    unsigned int index = bit / 8;
    unsigned char mask = 1 << (bit % 8);

    if (bit > bitset->size)
        return EXIT_FAILURE;

    return bitset->data[index] & mask ? 1 : 0;
}

int
cgc_bitset_find_first(struct bitset *bitset, int set)
{
    unsigned int i;

    for (i = 0; i < bitset->size; i++)
        if (cgc_bitset_get_bit(bitset, i) == set)
            return i;

    return EXIT_FAILURE;
}

