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
/*
 * Companding algorithm implementation
 */
#ifndef COMP_H_
#define COMP_H_

#include <stdint.h>

static int16_t comp_decode(uint8_t usample)
{
    usample = ~usample;
    int sign = usample & 0x80;
    int exp = (usample >> 4) & 7;
    
    int16_t sample = ((((usample & 0xF) << 1) | 0x21) << exp) - 33;
    if (sign)
        return -sample;
    else
        return sample;
}

static uint8_t comp_encode(int16_t sample)
{
    int exp;
    int sign = sample & 0x8000;
    if (sign)
        sample = -sample;

    if (sample > 8158)
        sample = 8158;
    
    sample += 33;
    
    if (sample & (1 << 12))
        exp = 7;
    else if (sample & (1 << 11))
        exp = 6;
    else if (sample & (1 << 10))
        exp = 5;
    else if (sample & (1 << 9))
        exp = 4;
    else if (sample & (1 << 8))
        exp = 3;
    else if (sample & (1 << 7))
        exp = 2;
    else if (sample & (1 << 6))
        exp = 1;
    else
        exp = 0;

    return ~(((sample >> (exp + 1)) & 0xF) | (exp << 4) | (sign >> 8));
}

#endif /* !COMP_H_ */
