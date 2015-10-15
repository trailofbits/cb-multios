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
#include <stdlib.h>
#include <stdint.h>
#include "codes.h"

#define N 32

typedef struct {
    uint16_t K[N+8];
} faith_priv_t;

static inline uint32_t S(uint8_t x, uint8_t y, uint8_t a)
{
    uint8_t t = x + y + a;
    return (t << 2) | (t >> 6);
}

static inline void f(faith_priv_t *priv, int r, uint32_t *pL, uint32_t *pR)
{
    uint8_t a0, a1, a2, a3, b0, b1, f0, f1, f2, f3;
    uint32_t L, R, tmp;
    L = *pL;
    R = *pR;
    tmp = R;

    a0 = R >> 24;
    a1 = R >> 16;
    a2 = R >> 8;
    a3 = R;
    b0 = priv->K[r] >> 8;
    b1 = priv->K[r];

    f1 = a1 ^ b0;
    f2 = a2 ^ b1;
    f1 ^= a0;
    f2 ^= a3;
    f1 = S(f1, f2, 0);
    f2 = S(f2, f1, 1);
    f0 = S(a0, f1, 1);
    f3 = S(a3, f2, 0);

    R = L ^ ((f0 << 24) | (f1 << 16) | (f2 << 8) | (f3));
    L = tmp;

    *pL = L;
    *pR = R;
}

static inline uint32_t fK(uint32_t a, uint32_t b)
{
    uint8_t a0, a1, a2, a3, b0, b1, b2, b3, f0, f1, f2, f3;

    a0 = a >> 24;
    a1 = a >> 16;
    a2 = a >>  8;
    a3 = a;
    b0 = b >> 24;
    b1 = b >> 16;
    b2 = b >>  8;
    b3 = b;

    f1 = a1 ^ a0;
    f2 = a2 ^ a3;
    f1 = S(f1, f2 ^ b0, 1);
    f2 = S(f2, f1 ^ b1, 0);
    f0 = S(a0, f1 ^ b2, 0);
    f3 = S(a3, f2 ^ b3, 1);

    return (f0 << 24) | (f1 << 16) | (f2 << 8) | f3;
}

static int faith_init(code_t *code, const unsigned char *k)
{
    int r;
    uint32_t R1, R2, L1, L2, A, B, D;
    const uint32_t *k32 = (const uint32_t *)k;
    faith_priv_t *priv;

    code->priv = priv = malloc(sizeof(faith_priv_t));
    if (priv == NULL)
        return FAILURE;

    L1 = k32[0];
    L2 = k32[1];
    R1 = k32[2];
    R2 = k32[3];

    A = L1;
    B = L2;
    D = 0;

    for (r = 0; r < N/2 + 4; r++)
    {
        uint32_t Q, tmp;
        if ((r % 3) == 0)
            Q = R1 ^ R2;
        else if ((r % 3) == 1)
            Q = R1;
        else
            Q = R2;
        tmp = fK(A, (B ^ D) ^ Q);

        priv->K[r * 2] = tmp >> 16;
        priv->K[r * 2 + 1] = tmp;

        D = A;
        A = B;
        B = tmp;
    }

    return SUCCESS;
}

static void faith_destroy(code_t *code)
{
    free(code->priv);
}

static int faith_encode(code_t *code, unsigned char *b)
{
    uint32_t *b32 = (uint32_t *)b;
    uint32_t L, R;
    int r;
    faith_priv_t *priv = code->priv;

    L = b32[0];
    R = b32[1];

    L ^= (priv->K[N] << 16) | priv->K[N+1];
    R ^= (priv->K[N+2] << 16) | priv->K[N+3];
    R ^= L;

    f(priv, 0, &L, &R);
    f(priv, 1, &L, &R);
    f(priv, 2, &L, &R);
    f(priv, 3, &L, &R);
    f(priv, 4, &L, &R);
    f(priv, 5, &L, &R);
    f(priv, 6, &L, &R);
    f(priv, 7, &L, &R);
    f(priv, 8, &L, &R);
    f(priv, 9, &L, &R);
    f(priv, 10, &L, &R);
    f(priv, 11, &L, &R);
    f(priv, 12, &L, &R);
    f(priv, 13, &L, &R);
    f(priv, 14, &L, &R);
    f(priv, 15, &L, &R);
    f(priv, 16, &L, &R);
    f(priv, 17, &L, &R);
    f(priv, 18, &L, &R);
    f(priv, 19, &L, &R);
    f(priv, 20, &L, &R);
    f(priv, 21, &L, &R);
    f(priv, 22, &L, &R);
    f(priv, 23, &L, &R);
    f(priv, 24, &L, &R);
    f(priv, 25, &L, &R);
    f(priv, 26, &L, &R);
    f(priv, 27, &L, &R);
    f(priv, 28, &L, &R);
    f(priv, 29, &L, &R);
    f(priv, 30, &L, &R);
    f(priv, 31, &L, &R);

    L ^= R;
    R ^= (priv->K[N+4] << 16) | priv->K[N+5];
    L ^= (priv->K[N+6] << 16) | priv->K[N+7];

    b32[0] = R;
    b32[1] = L;
    return SUCCESS;
}

static int faith_decode(code_t *code, unsigned char *b)
{
    uint32_t *b32 = (uint32_t *)b;
    uint32_t L, R;
    int r;
    faith_priv_t *priv = code->priv;

    R = b32[0];
    L = b32[1];

    R ^= (priv->K[N+4] << 16) | priv->K[N+5];
    L ^= (priv->K[N+6] << 16) | priv->K[N+7];
    L ^= R;

    f(priv, 31, &R, &L);
    f(priv, 30, &R, &L);
    f(priv, 29, &R, &L);
    f(priv, 28, &R, &L);
    f(priv, 27, &R, &L);
    f(priv, 26, &R, &L);
    f(priv, 25, &R, &L);
    f(priv, 24, &R, &L);
    f(priv, 23, &R, &L);
    f(priv, 22, &R, &L);
    f(priv, 21, &R, &L);
    f(priv, 20, &R, &L);
    f(priv, 19, &R, &L);
    f(priv, 18, &R, &L);
    f(priv, 17, &R, &L);
    f(priv, 16, &R, &L);
    f(priv, 15, &R, &L);
    f(priv, 14, &R, &L);
    f(priv, 13, &R, &L);
    f(priv, 12, &R, &L);
    f(priv, 11, &R, &L);
    f(priv, 10, &R, &L);
    f(priv, 9, &R, &L);
    f(priv, 8, &R, &L);
    f(priv, 7, &R, &L);
    f(priv, 6, &R, &L);
    f(priv, 5, &R, &L);
    f(priv, 4, &R, &L);
    f(priv, 3, &R, &L);
    f(priv, 2, &R, &L);
    f(priv, 1, &R, &L);
    f(priv, 0, &R, &L);

    R ^= L;
    L ^= (priv->K[N] << 16) | priv->K[N+1];
    R ^= (priv->K[N+2] << 16) | priv->K[N+3];

    b32[0] = L;
    b32[1] = R;
    return SUCCESS;
}

const code_def_t faith_code = {
    .name = "FAITH",
    .type = C_FAITH,
    .bsize = 64,
    .ksize = 128,
    .init = faith_init,
    .destroy = faith_destroy,
    .decode = faith_decode,
    .encode = faith_encode
};
