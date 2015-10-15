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
    uint32_t K[2 * N];
} coffee_priv_t;

static inline void fE(coffee_priv_t *priv, int r, uint32_t *pL, uint32_t *pR)
{
    uint32_t L, R, tmp;
    L = *pL;
    R = *pR;

    tmp = (R << 3) ^ (R >> 4);
    tmp += R;
    tmp ^= priv->K[r * 2];
    tmp += L;
    L = R;
    R = tmp;

    tmp = (R << 3) ^ (R >> 4);
    tmp += R;
    tmp ^= priv->K[r * 2 + 1];
    tmp += L;
    L = R;
    R = tmp;

    *pL = L;
    *pR = R;
}

static inline void fD(coffee_priv_t *priv, int r, uint32_t *pL, uint32_t *pR)
{
    uint32_t L, R, tmp;
    L = *pL;
    R = *pR;

    tmp = (R << 3) ^ (R >> 4);
    tmp += R;
    tmp ^= priv->K[r * 2 + 1];
    tmp = L - tmp;
    L = R;
    R = tmp;

    tmp = (R << 3) ^ (R >> 4);
    tmp += R;
    tmp ^= priv->K[r * 2];
    tmp = L - tmp;
    L = R;
    R = tmp;

    *pL = L;
    *pR = R;
}

static int coffee_init(code_t *code, const unsigned char *k)
{
    int r;
    uint32_t D;
    const uint32_t *k32 = (const uint32_t *)k;
    coffee_priv_t *priv;

    code->priv = priv = malloc(sizeof(coffee_priv_t));
    if (priv == NULL)
        return FAILURE;

    D = 0;

    for (r = 0; r < N; r++)
    {
        priv->K[r * 2] = k32[D  % 4] + D;
        D += 0x517CC1B7;

        priv->K[r * 2 + 1] = k32[((D >> 14) ^ (D << 3)) % 4] + D;
        D += 0x517CC1B7;
    }

    return SUCCESS;
}

static void coffee_destroy(code_t *code)
{
    free(code->priv);
}

static int coffee_encode(code_t *code, unsigned char *b)
{
    uint32_t *b32 = (uint32_t *)b;
    uint32_t L, R;
    int r;
    coffee_priv_t *priv = code->priv;

    L = b32[0];
    R = b32[1];

    fE(priv, 0, &L, &R);
    fE(priv, 1, &L, &R);
    fE(priv, 2, &L, &R);
    fE(priv, 3, &L, &R);
    fE(priv, 4, &L, &R);
    fE(priv, 5, &L, &R);
    fE(priv, 6, &L, &R);
    fE(priv, 7, &L, &R);
    fE(priv, 8, &L, &R);
    fE(priv, 9, &L, &R);
    fE(priv, 10, &L, &R);
    fE(priv, 11, &L, &R);
    fE(priv, 12, &L, &R);
    fE(priv, 13, &L, &R);
    fE(priv, 14, &L, &R);
    fE(priv, 15, &L, &R);
    fE(priv, 16, &L, &R);
    fE(priv, 17, &L, &R);
    fE(priv, 18, &L, &R);
    fE(priv, 19, &L, &R);
    fE(priv, 20, &L, &R);
    fE(priv, 21, &L, &R);
    fE(priv, 22, &L, &R);
    fE(priv, 23, &L, &R);
    fE(priv, 24, &L, &R);
    fE(priv, 25, &L, &R);
    fE(priv, 26, &L, &R);
    fE(priv, 27, &L, &R);
    fE(priv, 28, &L, &R);
    fE(priv, 29, &L, &R);
    fE(priv, 30, &L, &R);
    fE(priv, 31, &L, &R);

    b32[0] = R;
    b32[1] = L;

    return SUCCESS;
}

static int coffee_decode(code_t *code, unsigned char *b)
{
    uint32_t *b32 = (uint32_t *)b;
    uint32_t L, R;
    int r;
    coffee_priv_t *priv = code->priv;

    R = b32[0];
    L = b32[1];

    fD(priv, 31, &R, &L);
    fD(priv, 30, &R, &L);
    fD(priv, 29, &R, &L);
    fD(priv, 28, &R, &L);
    fD(priv, 27, &R, &L);
    fD(priv, 26, &R, &L);
    fD(priv, 25, &R, &L);
    fD(priv, 24, &R, &L);
    fD(priv, 23, &R, &L);
    fD(priv, 22, &R, &L);
    fD(priv, 21, &R, &L);
    fD(priv, 20, &R, &L);
    fD(priv, 19, &R, &L);
    fD(priv, 18, &R, &L);
    fD(priv, 17, &R, &L);
    fD(priv, 16, &R, &L);
    fD(priv, 15, &R, &L);
    fD(priv, 14, &R, &L);
    fD(priv, 13, &R, &L);
    fD(priv, 12, &R, &L);
    fD(priv, 11, &R, &L);
    fD(priv, 10, &R, &L);
    fD(priv, 9, &R, &L);
    fD(priv, 8, &R, &L);
    fD(priv, 7, &R, &L);
    fD(priv, 6, &R, &L);
    fD(priv, 5, &R, &L);
    fD(priv, 4, &R, &L);
    fD(priv, 3, &R, &L);
    fD(priv, 2, &R, &L);
    fD(priv, 1, &R, &L);
    fD(priv, 0, &R, &L);

    b32[0] = L;
    b32[1] = R;
    return SUCCESS;
}

const code_def_t coffee_code = {
    .name = "Coffee",
    .type = C_COFFEE,
    .bsize = 64,
    .ksize = 128,
    .init = coffee_init,
    .destroy = coffee_destroy,
    .encode = coffee_encode,
    .decode = coffee_decode
};
