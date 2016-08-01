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
#include "common.h"
#include "rng.h"

typedef struct {
    uint64_t state;
} lcg_priv_t;

static int lcg_init(rng_t *rng)
{
    lcg_priv_t *priv;
    rng->priv = priv = malloc(sizeof(lcg_priv_t));
    if (priv == NULL)
        return FAILURE;

    priv->state = 1;
    return SUCCESS;
}

static uint32_t next(lcg_priv_t *priv)
{
    priv->state = priv->state * 6364136223846793005ULL + 1;
    return priv->state >> 32;
}

static int lcg_get_bytes(rng_t *rng, unsigned char *out, unsigned int cnt)
{
    while (cnt > 0)
    {
        uint32_t x = next(rng->priv);
        *out++ = x >> 24;
        if (--cnt == 0) break;
        *out++ = x >> 16;
        if (--cnt == 0) break;
        *out++ = x >> 8;
        if (--cnt == 0) break;
        *out++ = x;
        if (--cnt == 0) break;
    }
    return SUCCESS;
}

const rng_def_t lcg_rng = {
    .name = "64-bit LCG",
    .id = RNG_LCG,
    .init = lcg_init,
    .get_bytes = lcg_get_bytes
};
