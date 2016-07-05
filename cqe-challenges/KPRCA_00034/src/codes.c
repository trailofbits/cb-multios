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
#include <string.h>
#include "codes.h"

//#define DEBUG

const code_def_t *codes[] = {
    [C_NULL] = &null_code,
    [C_FAITH] = &faith_code,
    [C_COFFEE] = &coffee_code,
    [C_BEST] = &best_code,
    [C_DOLPHIN] = &dolphin_code,
    [C_END] = NULL
};

static const uint8_t test_k[MAX_KSIZE / 8] = {
    0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
    0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
    0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
    0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
};

static const uint8_t test_b[MAX_BSIZE / 8] = {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

unsigned int codes_ksize(unsigned int id)
{
    if (id >= C_END)
        return INVALID;
    return codes[id]->ksize;
}

int codes_init(code_t *code, unsigned int id, unsigned char *k)
{
    if (id >= C_END)
        return FAILURE;

    code->def = codes[id];
    return code->def->init(code, k);
}

int codes_self_test()
{
    int i;
    for (i = 0; i < C_END; i++)
    {
        code_t code;
        const code_def_t *def = codes[i];
        uint8_t b[MAX_BSIZE / 8];

#ifdef DEBUG
        fdprintf(STDERR, "Code (%d): %s\n", i, def->name);
#endif

        if (def->ksize > MAX_KSIZE || def->bsize > MAX_BSIZE)
            goto fail;

        code.def = def;
        if (def->init(&code, test_k) != SUCCESS)
            goto fail;

        memcpy(b, test_b, sizeof(b));
        def->encode(&code, b);
        def->decode(&code, b);
        def->destroy(&code);

        if (memcmp(b, test_b, sizeof(b)) != 0)
            goto fail;
    }
    return SUCCESS;

fail:
#ifdef DEBUG
    fdprintf(STDERR, "Self-test FAILED!\n");
#endif
    return FAILURE;
}
