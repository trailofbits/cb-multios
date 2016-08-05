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
#include "rng.h"

Random::Random() : state(0xDEADBEEF12345678ULL)
{
}

void Random::addEntropy(const uint8_t *entropy, unsigned int length)
{
    uint8_t *tmp = new uint8_t[(length + 3) & (~3)];
    for (unsigned int i = 0; i < length; i++)
        tmp[i] = entropy[i] ^ 0x55;
    for (unsigned int i = 1; i < length; i++)
        tmp[i] ^= tmp[i - 1] >> 1;
    for (unsigned int i = 0; i < length; i += 4)
    {
        uint32_t x = *(uint32_t *)&tmp[i];
        state ^= state >> 7;
        state ^= x & 0x77777777;
        state ^= state << 17;
    }
    delete tmp;
}

int32_t Random::randomInt32()
{
    int32_t result = state >> 6;

    state ^= state >> 7;
    state ^= state << 17;

    return result;
}
