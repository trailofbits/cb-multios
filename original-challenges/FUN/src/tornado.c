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
#include <stdint.h>

#define M 122
#define N 156

/* from gcc headers */
typedef long long _m128i __attribute__((__vector_size__(16)));
#define _mm_slli_si128 __builtin_ia32_pslldqi128
#define _mm_srli_si128 __builtin_ia32_psrldqi128
#define _mm_slli_epi32 __builtin_ia32_pslldi128
#define _mm_srli_epi32 __builtin_ia32_psrldi128

static int initialized = 0;
static int available_bytes;
static unsigned idx;
static _m128i W[N];
const static _m128i MASK = {0xBFFFFFF6BFFAFFFF, 0xDDFECB7FDFFFFFEF};

void tornado_mix()
{
    int i;
    _m128i g, wA, wB, wC, wD, tmp;

    // generate g
    wA = W[idx];
    wB = W[(idx + M) % N];
    wC = W[(idx + N-2) % N];
    wD = W[(idx + N-1) % N];

    wA = _mm_slli_si128(wA, 1) ^ wA;
    wB = _mm_srli_epi32(wB, 11) & MASK;
    wC = _mm_srli_si128(wC, 1);
    wD = _mm_slli_epi32(wD, 18);

    g = W[idx] ^ wA ^ wB ^ wC ^ wD;

    // shift in g
    W[0] = g;
    idx = (idx + 1) % N;

    available_bytes = N * 4;
}

void tornado_init()
{
    int i;
    uint32_t seed = 0x12345678;
    uint32_t *W32 = (uint32_t *)W;

    initialized = 1;
    available_bytes = 0;
    idx = 0;

    for (i = 0; i < N * 4; i++)
    {
        seed *= 0xdeadbeef;
        seed += 0xabcdef1c;
        W32[i] = seed;
    }

    for (i = 0; i < 1000; i++)
        tornado_mix();
}

uint32_t tornado()
{
    uint32_t result;
    if (!initialized)
        tornado_init();

    if (available_bytes < sizeof(uint32_t))
        tornado_mix();

    result = *(uint32_t *)W + N * 4 - available_bytes/4;
    available_bytes -= sizeof(uint32_t);
    return result;
}
