/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 * 
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
#include "huffman.h"

void huffman_decode_table(ht_t *output, const uint8_t input[])
{
    uint8_t tmpsizes[256];
    uint16_t tmpcodes[256];
    int i, j, k;

    for (k = 0, i = 0; i < 16; i++)
        for (j = 1; j <= input[i]; j++, k++)
            tmpsizes[k] = i + 1;

    tmpsizes[k] = 0;
    int lastk = k;

    int code;
    int si = tmpsizes[0];
    for (k = 0, code = 0; tmpsizes[k] != 0;)
    {
        for (; tmpsizes[k] != si; si++)
            code <<= 1;
        for (; tmpsizes[k] == si; code++, k++)
            tmpcodes[k] = code;
    }

    input += 16;
    for (k = 0; k < lastk; k++)
    {
        i = input[k];
        output->sizes[i] = tmpsizes[k];
        output->codes[i] = tmpcodes[k];
    }
}


