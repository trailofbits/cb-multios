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
#include <string.h>

#include "bn.h"
#include "codes.h"
#include "common.h"
#include "kx.h"
#include "modes.h"
#include "rng.h"
#include "silk.h"

typedef struct {
#define DIR_OUT 0
#define DIR_IN 1
    code_t code[2];
    mode_t mode[2];
    rng_t rng;

    unsigned int code_id;
    unsigned int mode_id;
    unsigned int ksize;

    unsigned char *recvbuf;
    uint16_t recvbuf_len;
    uint16_t recvbuf_idx;
} silk_priv_t;

int _recv_bytes(void *data, unsigned int n)
{
    size_t bytes;
    if (receive(STDIN, data, n, &bytes) != 0 || bytes != n)
        return FAILURE;
    return SUCCESS;
}

int _recv(uint8_t pktid, void *data, unsigned int n)
{
    uint8_t actual_pktid;
    if (_recv_bytes(&actual_pktid, sizeof(actual_pktid)) != SUCCESS)
        return FAILURE;

    if (actual_pktid != pktid)
    {
        if (actual_pktid == PKT_ERROR)
        {
            // XXX do something with error pkt
        }
        return FAILURE;
    }

    return n > 0 ? _recv_bytes(data, n) : SUCCESS;
}

int _send_bytes(void *data, unsigned int n)
{
    size_t bytes;
    if (transmit(STDOUT, data, n, &bytes) != 0 || bytes != n)
        return FAILURE;
    return SUCCESS;
}

int _send(uint8_t pktid, void *data, unsigned int n)
{
    if (_send_bytes(&pktid, sizeof(pktid)) != SUCCESS)
        return FAILURE;
    return n > 0 ? _send_bytes(data, n) : SUCCESS;
}

int silk_init(silk_t *silk)
{
    silk_priv_t *priv;
    
    silk->priv = priv = malloc(sizeof(silk_priv_t));
    if (priv == NULL)
        return FAILURE;

    if (codes_self_test() != SUCCESS ||
        bn_self_test() != SUCCESS ||
        kx_self_test() != SUCCESS ||
        modes_self_test() != SUCCESS)
        return FAILURE;

    if (rng_init(&priv->rng, RNG_LCG) != SUCCESS)
        return FAILURE;

    priv->recvbuf = NULL;
    priv->recvbuf_len = 0;
    priv->recvbuf_idx = 0;
    return SUCCESS;
}

uint32_t silk_allowed_codes(silk_priv_t *priv)
{
    uint32_t res = 0;
#define ADD(x) res |= 1 << (x);
    ADD(C_NULL)
    ADD(C_FAITH)
    ADD(C_COFFEE)
    ADD(C_BEST)
    ADD(C_DOLPHIN)
    ADD(MODE_NULL + 16)
    ADD(MODE_BCM + 16)
    ADD(MODE_XIM + 16)
    ADD(MODE_XOM + 16)
#undef ADD
    return res;
}

unsigned int silk_preferred_code(silk_priv_t *priv, uint32_t accepted)
{
    uint32_t possible = accepted & silk_allowed_codes(priv);
#define TEST(x) if (possible & (1 << (x))) return (x);
    TEST(C_DOLPHIN)
    TEST(C_BEST)
    TEST(C_COFFEE)
    TEST(C_FAITH)
    TEST(C_NULL)
#undef TEST
    return INVALID;
}

unsigned int silk_preferred_mode(silk_priv_t *priv, uint32_t accepted)
{
    uint32_t possible = accepted & silk_allowed_codes(priv);
#define TEST(x) if (possible & (1 << (16+x))) return (x);
    TEST(MODE_XOM)
    TEST(MODE_XIM)
    TEST(MODE_BCM)
    TEST(MODE_NULL)
#undef TEST
    return INVALID;
}

int silk_negotiate(silk_t *silk)
{
    unsigned int code, mode;
    silk_negotiate_t pkt;
    silk_priv_t *priv = silk->priv;
    
    pkt.codes = silk_allowed_codes(priv);    

    if (_send(PKT_NEGOTIATE, &pkt, sizeof(pkt)) != SUCCESS)
        return FAILURE;

    if (_recv(PKT_NEGOTIATE, &pkt, sizeof(pkt)) != SUCCESS)
        return FAILURE;

    code = silk_preferred_code(priv, pkt.codes);
    if (code == INVALID)
        return FAILURE;
    mode = silk_preferred_mode(priv, pkt.codes);
    if (mode == INVALID)
        return FAILURE;
    if (((1 << code)|(1 << (16+mode))) != pkt.codes)
    {
        pkt.codes = (1 << code) | (1 << (16+mode));
        if (_send(PKT_NEGOTIATE, &pkt, sizeof(pkt)) != SUCCESS)
            return FAILURE;
    }

    priv->code_id = code;
    priv->ksize = codes_ksize(priv->code_id);
    priv->mode_id = mode;

    return SUCCESS;
}

int silk_kx(silk_t *silk)
{
    silk_priv_t *priv = silk->priv;
    int result = FAILURE;
    unsigned int group, idx, i;
    unsigned char *data = NULL, k[MAX_KSIZE / 8];
    uint8_t xorbyte;
    bn_t A, B;
    kx_t kx;
    silk_kx_param_t param;
    silk_kx_reply_t reply;

    if (priv->ksize == 0)
    {
        // ksize==0, so no real kx
        memset(&param, 0, sizeof(param));
        if (_send(PKT_KX_PARAM, &param, sizeof(param)) != SUCCESS)
            return FAILURE;

        if (_recv(PKT_KX_REPLY, &reply, sizeof(reply)) != SUCCESS)
            return FAILURE;
        if (reply.blen != 0)
            return FAILURE;

        if (codes_init(&priv->code[DIR_OUT], priv->code_id, NULL) != SUCCESS)
            return FAILURE;
        if (modes_init(&priv->mode[DIR_OUT], priv->mode_id, &priv->code[DIR_OUT]) != SUCCESS)
            return FAILURE;

        if (codes_init(&priv->code[DIR_IN], priv->code_id, NULL) != SUCCESS)
            return FAILURE;
        if (modes_init(&priv->mode[DIR_IN], priv->mode_id, &priv->code[DIR_IN]) != SUCCESS)
            return FAILURE;

        return SUCCESS;
    }
    else if (priv->ksize <= 128)
    {
        group = KX_GROUP_2048_256;
    }
    else
    {
        group = KX_GROUP_3072_3072;
    }

    bn_init(&A);
    bn_init(&B);

    if (kx_init_std(&kx, group) != SUCCESS)
        return FAILURE;

    if (kx_gen_a(&kx, &priv->rng) != SUCCESS)
        goto fail;
    if (kx_get_A(&kx, &A) != SUCCESS)
        goto fail;

    param.plen = ROUNDUP(bn_length(&kx.P), 8) / 8;
    param.glen = ROUNDUP(bn_length(&kx.G), 8) / 8;
    param.qlen = ROUNDUP(bn_length(&kx.Q), 8) / 8;
    param.alen = ROUNDUP(bn_length(&A), 8) / 8;
    idx = 0;
    data = malloc(param.plen + param.glen + param.qlen + param.alen);
    if (data == NULL)
        goto fail;
    bn_to_bytes(&kx.P, &data[idx], param.plen);
    idx += param.plen;
    bn_to_bytes(&kx.G, &data[idx], param.glen);
    idx += param.glen;
    bn_to_bytes(&kx.Q, &data[idx], param.qlen);
    idx += param.qlen;
    bn_to_bytes(&A, &data[idx], param.alen);
    idx += param.alen;

    if (_send(PKT_KX_PARAM, &param, sizeof(param)) != SUCCESS)
        goto fail;
    if (_send_bytes(data, idx) != SUCCESS)
        goto fail;
    free(data);
    data = NULL;

    if (_recv(PKT_KX_REPLY, &reply, sizeof(reply)) != SUCCESS)
        goto fail;
    data = malloc(reply.blen);
    if (data == NULL)
        goto fail;
    if (_recv_bytes(data, reply.blen) != SUCCESS)
        goto fail;

    if (bn_from_bytes(&B, data, reply.blen) != SUCCESS)
        goto fail;
    if (kx_set_b(&kx, &B) != SUCCESS)
        goto fail;

    if (kx_get_sk(&kx, k, priv->ksize) != SUCCESS)
        goto fail;
    if (codes_init(&priv->code[DIR_OUT], priv->code_id, k) != SUCCESS)
        goto fail;
    if (modes_init(&priv->mode[DIR_OUT], priv->mode_id, &priv->code[DIR_OUT]) != SUCCESS)
        goto fail;

    xorbyte = 0xFF;
    for (i = 0; i < priv->ksize / 8; i++)
    {
        k[i] ^= xorbyte;
        xorbyte ^= k[i] >> 3;
    }

    if (codes_init(&priv->code[DIR_IN], priv->code_id, k) != SUCCESS)
        goto fail;
    if (modes_init(&priv->mode[DIR_IN], priv->mode_id, &priv->code[DIR_IN]) != SUCCESS)
        goto fail;

    result = SUCCESS;

fail:
    free(data);
    bn_destroy(&A);
    bn_destroy(&B);
    kx_destroy(&kx);
    return result;
}

int silk_prepare(silk_t *silk)
{
    if (silk_negotiate(silk) != SUCCESS)
        return FAILURE;

    if (silk_kx(silk) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

int silk_send(silk_t *silk, const unsigned char *data, unsigned int cnt)
{
    const unsigned int max_cnt = 0xFFFF - MAX_BSIZE / 8;
    unsigned char *real_data;
    unsigned int real_cnt;
    silk_priv_t *priv = silk->priv;
    silk_data_t pkt;

    while (cnt > 0)
    {
        unsigned int to_send = cnt > max_cnt ? max_cnt : cnt;
        if (modes_encode(&priv->mode[DIR_OUT], data, to_send, &real_data, &real_cnt) != SUCCESS)
            return FAILURE;

        // sanity check
        if (real_cnt > 0xFFFF)
            return FAILURE;

        pkt.datalen = real_cnt;
        _send(PKT_DATA, &pkt, sizeof(pkt));
        _send_bytes(real_data, real_cnt);
        free(real_data);

        data += to_send;
        cnt -= to_send;
    }
    return SUCCESS;
}

static int _fill_recvbuf(silk_priv_t *priv)
{
    int result = FAILURE;
    unsigned int datalen;
    unsigned char *pkt_data = NULL, *data;
    silk_data_t pkt;
    if (_recv(PKT_DATA, &pkt, sizeof(pkt)) != SUCCESS)
        goto fail;
    pkt_data = malloc(pkt.datalen);
    if (pkt_data == NULL)
        goto fail;
    if (_recv_bytes(pkt_data, pkt.datalen) != SUCCESS)
        goto fail;
    if (modes_decode(&priv->mode[DIR_IN], pkt_data, pkt.datalen, &data, &datalen) != SUCCESS)
        goto fail;

    priv->recvbuf = data;
    priv->recvbuf_len = datalen;
    priv->recvbuf_idx = 0;
    result = SUCCESS;

fail:
    free(pkt_data);
    return result;
}

int silk_recv(silk_t *silk, unsigned char *out, unsigned int cnt)
{
    silk_priv_t *priv = silk->priv;
    while (cnt > 0)
    {
        unsigned int to_copy;

        if (priv->recvbuf == NULL)
        {
            if (_fill_recvbuf(priv) != SUCCESS)
                return FAILURE;
        }

        to_copy = cnt > priv->recvbuf_len ? priv->recvbuf_len : cnt;
        memcpy(out, &priv->recvbuf[priv->recvbuf_idx], to_copy);
        out += to_copy;
        cnt -= to_copy;
        priv->recvbuf_idx += to_copy;
        priv->recvbuf_len -= to_copy;

        if (priv->recvbuf_len == 0)
        {
            free(priv->recvbuf);
            priv->recvbuf = NULL;
            priv->recvbuf_len = priv->recvbuf_idx = 0;
        }
    }
    return SUCCESS;
}
