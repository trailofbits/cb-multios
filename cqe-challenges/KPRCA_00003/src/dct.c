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
// implementation of fixed point 8x8 DCT and IDCT
// reference: http://www.reznik.org/papers/SPIE07_MPEG-C_IDCT.pdf
#include <stdint.h>
#include "dct.h"

#define A 1024
#define B 1138
#define C 1730
#define D 1609
#define E 1264
#define F 1922
#define G 1788
#define H 2923
#define I 2718
#define J 2528

static const int32_t S[] = {
    A, B, C, D, A, D, C, B,
    B, E, F, G, B, G, F, E,
    C, F, H, I, C, I, H, F,
    D, G, I, J, D, J, I, G,
    A, B, C, D, A, D, C, B,
    D, G, I, J, D, J, I, G,
    C, F, H, I, C, I, H, F,
    B, E, F, G, B, G, F, E
};

#undef A
#undef B
#undef C
#undef D
#undef E
#undef F
#undef G
#undef H
#undef I
#undef J

#define MUL_ALPHA_BETA(x, y, z) \
    do { \
        int32_t t1 = x + (x >> 5); \
        int32_t t2 = t1 >> 2; \
        y = t2 + (x >> 4); \
        z = t1 - t2; \
    } while (0)

#define MUL_DELTA_EPSILON(x, y, z) \
    do { \
        int32_t t1 = (x >> 3) - (x >> 7); \
        int32_t t2 = t1 - (x >> 11); \
        y = x - t1; \
        z = t1 + (t2 >> 1); \
    } while (0)

#define MUL_ETA_THETA(x, y, z) \
    do { \
        int32_t t1 = (x >> 9) - x; \
        z = x >> 1; \
        y = (t1 >> 2) - t1; \
    } while (0)

#define INV_TRANSFORM() \
    do { \
        int32_t x0 = G(0), x1 = G(1), x2 = G(2), x3 = G(3), \
            x4 = G(4), x5 = G(5), x6 = G(6), x7 = G(7), a, b; \
        a = x1 + x7; \
        b = x1 - x7; \
        x7 = x5 + b; \
        x1 = x3 + a; \
        x3 = a - x3; \
        x5 = b - x5; \
        MUL_ETA_THETA(x1, x1, a); \
        MUL_ETA_THETA(x7, x7, b); \
        x1 += b; \
        x7 -= a; \
        MUL_DELTA_EPSILON(x3, x3, a); \
        MUL_DELTA_EPSILON(x5, x5, b); \
        x3 -= b; \
        x5 += a; \
        MUL_ALPHA_BETA(x2, x2, a); \
        MUL_ALPHA_BETA(x6, x6, b); \
        x2 -= b; \
        x6 += a; \
        a = x0 + x4; \
        b = x0 - x4; \
        x0 = a + x6; \
        x4 = b + x2; \
        x2 = b - x2; \
        x6 = a - x6; \
        G(0) = x0 + x1; \
        G(1) = x5 + x4; \
        G(2) = x2 + x3; \
        G(3) = x6 + x7; \
        G(4) = x6 - x7; \
        G(5) = x2 - x3; \
        G(6) = x4 - x5; \
        G(7) = x0 - x1; \
    } while (0)

#define TRANSFORM() \
    do { \
        int32_t x0 = G(0), x1 = G(1), x2 = G(2), x3 = G(3), \
            x4 = G(4), x5 = G(5), x6 = G(6), x7 = G(7), a, b, c, d; \
        a = x3 - x4; \
        b = x2 - x5; \
        c = x1 - x6; \
        d = x0 - x7; \
        x0 += x7; \
        x1 += x6; \
        x2 += x5; \
        x3 += x4; \
        MUL_ETA_THETA(a, x4, a); \
        MUL_ETA_THETA(d, x7, d); \
        x4 = x4 + d; \
        x7 = x7 - a; \
        MUL_DELTA_EPSILON(b, x5, b); \
        MUL_DELTA_EPSILON(c, x6, c); \
        x5 = x5 + c; \
        x6 = x6 - b; \
        a = x4 + x6; \
        d = x5 + x7; \
        G(3) = x7 - x5; \
        G(5) = x4 - x6; \
        G(7) = d - a; \
        G(1) = a + d; \
        a = x0 + x3; \
        b = x1 + x2; \
        c = x1 - x2; \
        d = x0 - x3; \
        G(0) = a + b; \
        G(4) = a - b; \
        MUL_ALPHA_BETA(c, x2, c); \
        MUL_ALPHA_BETA(d, x3, d); \
        G(2) = x2 + d; \
        G(6) = x3 - c; \
    } while (0)


void idct(const int16_t input[], int8_t output[], const uint8_t scaler[])
{
    int u, v;
    int32_t M[64];
    
    // scale input
    for (v = 0; v < 8; v++)
        for (u = 0; u < 8; u++)
            M[v*8 + u] = input[v*8 + u] * S[v*8 + u] * scaler[v*8 + u];
    // add DC bias
    M[0] += 2048;
    // row transforms
#define G(x) M[v*8 + x]
    for (v = 0; v < 8; v++)
        INV_TRANSFORM();
#undef G
    // column transforms
#define G(x) M[x*8 + u]
    for (u = 0; u < 8; u++)
        INV_TRANSFORM();
#undef G
    // shift
    for (v = 0; v < 8; v++)
        for (u = 0; u < 8; u++)
            output[v*8 + u] = M[v*8 + u] >> 13;
}

void dct(const int8_t input[], int16_t output[], const uint8_t scaler[])
{
    int u, v;
    int32_t M[64];
    
    // shift
    for (v = 0; v < 8; v++)
        for (u = 0; u < 8; u++)
            M[v*8 + u] = input[v*8 + u] << 7;
    // column transforms
#define G(x) M[x*8 + u]
    for (u = 0; u < 8; u++)
        TRANSFORM();
#undef G
    // row transforms
#define G(x) M[v*8 + x]
    for (v = 0; v < 8; v++)
        TRANSFORM();
#undef G
    // scale and such
    for (v = 0; v < 8; v++)
        for (u = 0; u < 8; u++)
            output[v*8 + u] = (M[v*8 + u] * S[v*8 + u] / scaler[v*8 + u] + (1 << 19) + (M[v*8 + u] >> 31)) >> 20;
}

