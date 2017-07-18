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
#include "cgc_stdio_private.h"

static unsigned int hash_seed(const char *seed)
{
    unsigned int i;
    unsigned int H = 0x314abc86;
    
    for (i = 0; seed[i] != 0; i++)
    {
        H *= 37;
        H ^= seed[i];
        H = (H << 13) ^ (H >> 19);
    }

    return H;
}

void cgc_fxlat(FILE *stream, const char *seed)
{
    unsigned int state, i;
    unsigned char *map, *map_inv;

    if (seed == NULL)
    {
        cgc_free(stream->xlat_map);
        stream->xlat_map = NULL;
        stream->xlat_map_inv = NULL;
        return;
    }
    
    map = stream->xlat_map = cgc_realloc(stream->xlat_map, 256);
    map_inv = stream->xlat_map_inv = cgc_realloc(stream->xlat_map_inv, 256);
    state = hash_seed(seed);

    /* initialize map with identity */
    for (i = 0; i < 256; i++)
        map[i] = i;

    /* shuffle using Fisher-Yates */
    for (i = 255; i >= 1; i--)
    {
        unsigned int j = state % i, tmp;
        
        /* iterate state */
        state *= 3;
        state = (state << 13) ^ (state >> 19) ^ (state >> 21);

        /* exchange elements */
        tmp = map[i];
        map[i] = map[j];
        map[j] = tmp;
    }

    /* initialize inverse mapping */
    for (i = 0; i < 256; i++)
    {
        map_inv[map[i]] = i;
    }
}
