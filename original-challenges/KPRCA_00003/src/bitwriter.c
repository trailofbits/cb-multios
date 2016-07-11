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
#include "bitwriter.h"

void bitwriter_output(bitwriter_t *bw, uint32_t value, int8_t bits)
{
    if (bits <= 0 || bits > 32)
        return;

    uint32_t mask;
    for (mask = 1 << (bits-1); mask != 0; mask >>= 1)
    {
        unsigned bit = !!(value & mask);
        bw->partial = (bw->partial << 1) | bit;
        if (++(bw->bits) == 8)
        {
            bw->output(bw->partial);
            bw->bits = 0;
            bw->partial = 0;
        }
    }
}

void bitwriter_flush(bitwriter_t *bw, uint8_t bit)
{
    while (bw->bits != 0) 
    {
        bw->partial = (bw->partial << 1) | bit;
        if (++(bw->bits) == 8)
        {
            bw->output(bw->partial);
            bw->bits = 0;
            bw->partial = 0;
        }
    }
}
