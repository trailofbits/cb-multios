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
#include "Random.h"

#define RAND_MAX 0xFFFF
#define POLYNOMIAL_0 0x29D1E9EB
#define POLYNOMIAL_1 0xF5CDE95

DefineClass(Random, Object)

DefineFunction(Random, void, $init)
{
    this->m_state0 = 1;
    this->m_state1 = 1;
}

DefineFunction(Random, void, init, unsigned int seed)
{
    this->m_state0 = seed;
    this->m_state1 = 1;
}

// returns a number (0, upper]
DefineFunction(Random, unsigned int, randint, unsigned int upper)
{
    unsigned int r;

    do {
        r = $(this, _rand);
    } while (r > ((RAND_MAX + 1) / upper * upper - 1));

    // r is a random number (0, upper*M]
    return r % upper;
}

// returns a number (0, RAND_MAX)
DefineFunction(Random, unsigned int, _rand)
{
    $(this, _update);
    return (this->m_state0 ^ this->m_state1) & 0xFFFF;
}

// mixes up the state
DefineFunction(Random, void, _update)
{
    if (this->m_state0 & 1)
        this->m_state0 = (this->m_state0 >> 1) ^ POLYNOMIAL_0;
    else
        this->m_state0 >>= 1;

    if (this->m_state1 & 1)
        this->m_state1 = (this->m_state1 >> 1) ^ POLYNOMIAL_1;
    else
        this->m_state1 >>= 1;
}
