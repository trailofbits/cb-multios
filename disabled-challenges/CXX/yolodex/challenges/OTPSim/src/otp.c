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

#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_readuntil.h"
#include "cgc_otp.h"

const char *secret = (const char*) 0x4347C000;

void cgc__otp_populate(otp_t *o)
{
    cgc_size_t i, idx;
    char tmp[4096];

    idx = o->seed_idx % 4096;
    cgc_memcpy(tmp, &secret[idx], 4096 - idx);
    if (idx != 0)
        cgc_memcpy(&tmp[4096 - idx], secret, idx);

    for (idx = i = o->data_len; i < MAX_OTP_LEN; ++i)
    {
        o->data[i] = tmp[idx % 4096] ^ ((char *) &o->seed_value)[i % 4];
        idx += 2;
    }

    o->seed_idx = idx;
    o->data_len = MAX_OTP_LEN;
}

void cgc__otp_consume(otp_t *o, cgc_size_t sz)
{
    cgc_size_t i;
    if (o->data_len < sz)
        return;
    cgc_memcpy(o->data, &o->data[sz], o->data_len - sz);
    o->data_len -= sz;
}

void cgc_otp_handshake(otp_t **o)
{
    if (*o)
    {
        cgc_free(*o);
        *o = NULL;
    }

    unsigned int challenge[2], response[2];
    cgc_random(challenge, sizeof(challenge), NULL);
    cgc_fwrite(challenge, sizeof(challenge), cgc_stdout);

    int i;
    unsigned char *c = (unsigned char *) &challenge;
    for (i = 0; i < sizeof(challenge); ++i, ++c)
        *c = ((*c & 0x0F) << 4 | (*c & 0xF0) >> 4);

    if (cgc_read_n(STDIN, (char *)response, sizeof(response)) != sizeof(response))
        goto fail;

    unsigned int sv = 0;
    if (cgc_read_n(STDIN, (char *)&sv, sizeof(unsigned int)) != sizeof(unsigned int))
        goto fail;

    if (cgc_memcmp(challenge, response, sizeof(challenge)) != 0 &&
        cgc_memcmp((void *)secret, response, sizeof(challenge)) != 0)
        goto fail;

    otp_t *otp = (otp_t *) cgc_malloc(sizeof(otp_t));
    cgc_memset(otp, 0, sizeof(otp_t));
    otp->seed_value = sv;
    unsigned int *sp = (unsigned int *) secret;
    for (i = 0; i < 4096 / 4; ++i)
        otp->seed_idx += sp[i];
    otp->seed_idx %= 4096;

    cgc_fwrite(&otp->seed_idx, sizeof(unsigned int), cgc_stdout);
    cgc_fwrite("\x00", 1, cgc_stdout);
    otp->num_reqs = 3;
    *o = otp;
    return;

fail:
    *o = NULL;
    cgc_fwrite("\xFF", 1, cgc_stdout);
}

void cgc_otp_generate_otp(otp_t *o)
{
    cgc_size_t sz = 0;
    if (cgc_read_n(STDIN, (char *)&sz, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;

    if (!o)
        goto fail;

    if (o->num_reqs == 0)
        goto fail;

    if (sz > MAX_OTP_LEN || sz == 0)
        goto fail;

    if (o->data_len < sz)
        cgc__otp_populate(o);

    int i;
    for (i = 0; i < sz; ++i)
        cgc_printf("%02X", o->data[i]);
    cgc__otp_consume(o, sz);

    cgc_fwrite("\x00", 1, cgc_stdout);
    o->num_reqs--;
    return;

fail:
    cgc_fwrite("\xFF", 1, cgc_stdout);
}

void cgc_otp_extend_session(otp_t *o)
{
    cgc_size_t nread = 0;
    unsigned short sz = 0;
    char buf[8192];
    char *resp = NULL;

    if (cgc_read_n(STDIN, (char *)&sz, sizeof(unsigned short)) != sizeof(unsigned short))
        goto fail;

    if ((nread = cgc_read_until(STDIN, buf, sizeof(buf), '\x00')) <= 0)
        goto fail;

    if (!o)
        goto fail;

#ifdef PATCHED_1
    if (sz == 0 || sz > nread)
#else
    if (sz == 0)
#endif
        goto fail;

    resp = cgc_malloc(sz + 1);
    resp[0] = '\x00';
    cgc_memcpy(&resp[1], buf, sz);
    o->num_reqs = 3;
    cgc_fwrite(resp, sz + 1, cgc_stdout);
    cgc_free(resp);
    return;

fail:
    cgc_fwrite("\xFF", 1, cgc_stdout);
}

void cgc_otp_set_seeds(otp_t *o)
{
    cgc_size_t sv = 0, idx = 0;
    if (cgc_read_n(STDIN, (char *)&sv, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;
    if (cgc_read_n(STDIN, (char *)&idx, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;

    if (!o)
        goto fail;

    o->seed_value = sv;
    o->seed_idx = idx;
    o->data_len = 0;
    cgc_memset(o->data, 0, MAX_OTP_LEN);
    cgc__otp_populate(o);

    cgc_fwrite("\x00", 1, cgc_stdout);
    return;

fail:
    cgc_fwrite("\xFF", 1, cgc_stdout);
}

void cgc_otp_verify_otp(otp_t *o)
{
    char token[MAX_OTP_LEN];
    cgc_size_t sv = 0, idx = 0, sz = 0;
    if (cgc_read_n(STDIN, (char *)&idx, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;
    if (cgc_read_n(STDIN, (char *)&sv, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;
    if (cgc_read_n(STDIN, (char *)&sz, sizeof(cgc_size_t)) != sizeof(cgc_size_t))
        goto fail;
    if (cgc_read_n(STDIN, token, sz) != sz)
        goto fail;

    if (sz > MAX_OTP_LEN || sz == 0)
        goto fail;

    otp_t tmp;
    cgc_memset(&tmp, 0, sizeof(otp_t));
    tmp.seed_value = sv;
    tmp.seed_idx = idx;
    cgc__otp_populate(&tmp);

    if (cgc_memcmp(tmp.data, token, sz) != 0)
        goto fail;

    cgc_fwrite("\x00", 1, cgc_stdout);
    return;

fail:
    cgc_fwrite("\xFF", 1, cgc_stdout);
}

