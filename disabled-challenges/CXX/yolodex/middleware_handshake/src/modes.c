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
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_codes.h"
#include "cgc_common.h"
#include "cgc_modes.h"

int cgc__do_encode(mode_t *mode, unsigned char *b)
{
#define XOR(a, b, n) for (i = 0; i < (n); i++) (a)[i] ^= (b)[i];
    unsigned int i, bytes = mode->code->def->bsize / 8;
    unsigned char tmp[MAX_BSIZE / 8];
    if (mode->mode == MODE_BCM)
    {
        uint64_t c = mode->state.cm;
        for (i = bytes; i > 0; i--)
        {
            tmp[i-1] = c;
            c = c >> 8;
        }
        if (codes_encode(mode->code, tmp) != SUCCESS)
            return FAILURE;

        XOR(b, tmp, bytes)

        mode->state.cm--;
    }
    else if (mode->mode == MODE_XIM)
    {
        XOR(b, mode->state.xm, bytes)
        if (codes_encode(mode->code, b) != SUCCESS)
            return FAILURE;
        XOR(mode->state.xm, b, bytes)
    }
    else if (mode->mode == MODE_XOM)
    {
        cgc_memcpy(tmp, b, bytes);
        XOR(b, mode->state.xm, bytes)
        if (codes_encode(mode->code, b) != SUCCESS)
            return FAILURE;
        cgc_memcpy(mode->state.xm, tmp, bytes);
        XOR(mode->state.xm, b, bytes)
    }
#undef XOR
    return SUCCESS;
}

int cgc__do_decode(mode_t *mode, unsigned char *b)
{
#define XOR(a, b, n) for (i = 0; i < (n); i++) (a)[i] ^= (b)[i];
    unsigned int i, bytes = mode->code->def->bsize / 8;
    unsigned char tmp[MAX_BSIZE / 8];
    if (mode->mode == MODE_BCM)
    {
        // the same as encoding
        cgc__do_encode(mode, b);
    }
    else if (mode->mode == MODE_XIM)
    {
        cgc_memcpy(tmp, b, bytes);
        if (codes_decode(mode->code, b) != SUCCESS)
            return FAILURE;
        XOR(b, mode->state.xm, bytes)
        XOR(mode->state.xm, tmp, bytes)
    }
    else if (mode->mode == MODE_XOM)
    {
        cgc_memcpy(tmp, b, bytes);
        if (codes_decode(mode->code, b) != SUCCESS)
            return FAILURE;
        XOR(b, mode->state.xm, bytes)

        cgc_memcpy(mode->state.xm, tmp, bytes);
        XOR(mode->state.xm, b, bytes)
    }
#undef XOR
    return SUCCESS;
}

int cgc_modes_init(mode_t *mode, unsigned int mode_id, code_t *code)
{
    if (mode_id >= MODE_END)
        return FAILURE;

    mode->mode = mode_id;
    mode->code = code;
    cgc_memset(&mode->state, 0, sizeof(mode->state));
    return SUCCESS;
}

int cgc_modes_encode(mode_t *mode, const unsigned char *inb, unsigned int inlen, 
    unsigned char **outb, unsigned int *outlen)
{
    int pad = 0;
    unsigned int bytes = mode->code->def->bsize / 8;
    unsigned int i, len = ROUNDUP(inlen, bytes);
    unsigned char *data;
    if (inlen == 0)
    {
        *outlen = 0;
        *outb = NULL;
        return SUCCESS;
    }

    data = cgc_malloc(len + bytes);
    if (data == NULL)
        return FAILURE;

    for (i = 0; i < len; i += bytes)
    {
        unsigned int tocopy = bytes;
        if (inlen < tocopy)
            tocopy = inlen;
        cgc_memcpy(&data[i], inb, tocopy);
        inb += tocopy;
        inlen -= tocopy;

        if (tocopy < bytes)
        {
            pad = 1;
            cgc_memset(&data[i + tocopy], tocopy, bytes - tocopy);
        }

        if (cgc__do_encode(mode, &data[i]) != SUCCESS)
            goto fail;
    }

    if (pad == 0)
    {
        // if there is no padding, append another block for padding
        cgc_memset(&data[len], 0, bytes);
        if (cgc__do_encode(mode, &data[len]) != SUCCESS)
            goto fail;
        len += bytes;
    }

    *outb = data;
    *outlen = len;
    return SUCCESS;

fail:
    cgc_free(data);
    return FAILURE;
}

int cgc_modes_decode(mode_t *mode, const unsigned char *inb, unsigned int inlen, 
    unsigned char **outb, unsigned int *outlen)
{
    unsigned int bytes = mode->code->def->bsize / 8;
    unsigned int i, len;
    unsigned char *data;
    if (inlen == 0)
    {
        *outlen = 0;
        *outb = NULL;
        return SUCCESS;
    }

    // sanity check input
    if ((inlen % bytes) != 0)
        return FAILURE;

    data = cgc_malloc(inlen);
    if (data == NULL)
        return FAILURE;
    cgc_memcpy(data, inb, inlen);

    for (i = 0; i < inlen; i += bytes)
    {
        if (cgc__do_decode(mode, &data[i]) != SUCCESS)
            goto fail;
    }

    // examine last byte to get length of last block
    len = data[inlen-1];
    if (len >= bytes)
        goto fail;

    // sanity check
    for (i = bytes; i > len; i--)
        if (data[inlen - bytes + i-1] != len)
            goto fail;

    // calculate real length
    len = inlen - bytes + len;

    *outb = data;
    *outlen = len;
    return SUCCESS;

fail:
    cgc_free(data);
    return FAILURE;
}

int cgc_modes_self_test()
{
    static unsigned char test[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x55, 0xAA};
    code_t c;
    mode_t m;
    unsigned char *tmp1, *tmp2;
    unsigned int len, id;

    if (cgc_codes_init(&c, C_NULL, NULL) != SUCCESS)
        goto fail;

    for (id = MODE_NULL; id < MODE_END; id++)
    {
        if (cgc_modes_init(&m, id, &c) != SUCCESS)
            goto fail;

        if (cgc_modes_encode(&m, test, sizeof(test), &tmp1, &len) != SUCCESS)
            goto fail;

        if (len != 12)
            goto fail;

        if (cgc_modes_init(&m, id, &c) != SUCCESS)
            goto fail;

        if (cgc_modes_decode(&m, tmp1, len, &tmp2, &len) != SUCCESS)
            goto fail;
        cgc_free(tmp1);

        if (len != sizeof(test))
            goto fail;

        if (cgc_memcmp(tmp2, test, sizeof(test)) != 0)
            goto fail;
        cgc_free(tmp2);
    }
    return SUCCESS;

fail:
    cgc_fdprintf(STDERR, "Modes self-init FAILED!\n");
    return FAILURE;
}
