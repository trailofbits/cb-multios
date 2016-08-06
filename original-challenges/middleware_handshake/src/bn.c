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
#include "common.h"

//#define DEBUG

void bn_init(bn_t *bn)
{
    bn->data = NULL;
    bn->length = 0;
}

void bn_destroy(bn_t *bn)
{
    free(bn->data);
    bn->data = NULL;
    bn->length = 0;
}

int bn_const(bn_t *bn, uint32_t c)
{
    bn_destroy(bn);
    if (bn_init_bits(bn, 32) != SUCCESS)
        return FAILURE;
    bn->data[0] = c;
    return SUCCESS;
}

int bn_init_bits(bn_t *bn, unsigned int bits)
{
    unsigned int bytes = (bits + 7) / 8;
    unsigned int length = (bytes + sizeof(uint32_t) - 1) / sizeof(uint32_t);
    bn->data = calloc(length, sizeof(uint32_t));
    if (bn->data == NULL)
        return FAILURE;
    bn->length = length;
    return SUCCESS;
}

unsigned int bn_length(const bn_t *bn)
{
    unsigned int d, i, length = bn->length;
    while (length > 0)
    {
        if (bn->data[length-1] != 0)
            break;
        length--;
    }

    if (length == 0)
        return 0;

    d = bn->data[length-1];
    length *= sizeof(uint32_t) * 8;
    for (i = sizeof(uint32_t) * 8; i > 0; i--)
    {
        if (d & (1 << (i - 1)))
            break;
        length--;
    }

    return length;
}

int bn_copy(bn_t *bn, const bn_t *src)
{
    bn_destroy(bn);
    if (bn_init_bits(bn, src->length * sizeof(uint32_t) * 8) != SUCCESS)
        return FAILURE;

    memcpy(bn->data, src->data, src->length * sizeof(uint32_t));
    bn->length = src->length;
    return SUCCESS;
}

int bn_from_bytes(bn_t *bn, const unsigned char *bytes, unsigned int n)
{
    unsigned int i;
    uint32_t *data;

    bn_destroy(bn);
    if (bn_init_bits(bn, n * 8) != SUCCESS)
        return FAILURE;
    data = bn->data;

    for (i = n; i > 0;)
    {
        uint32_t x = 0;
        
        x |= bytes[i-1];
        if (--i == 0)
            goto done;
        x |= bytes[i-1] << 8;
        if (--i == 0)
            goto done;
        x |= bytes[i-1] << 16;
        if (--i == 0)
            goto done;
        x |= bytes[i-1] << 24;
        --i;
done:
        *data++ = x;
    }

    return SUCCESS;
}

void bn_to_bytes(const bn_t *bn, unsigned char *bytes, unsigned int n)
{
    unsigned int len = bn->length * sizeof(uint32_t), i;
    while (n > len)
    {
        *bytes++ = 0;
        n--;
    }

    len = (n + 3) & ~(sizeof(uint32_t) - 1);
    for (i = len / sizeof(uint32_t); i > 0; i--)
    {
        uint32_t x = bn->data[i - 1];
        if (len-- <= n)
            *bytes++ = x >> 24;
        if (len-- <= n)
            *bytes++ = x >> 16;
        if (len-- <= n)
            *bytes++ = x >> 8;
        if (len-- <= n)
            *bytes++ = x;
    }
}

int bn_random(bn_t *bn, const bn_t *max, rng_t *rng)
{
    unsigned int bits = bn_length(max);
    bn_destroy(bn);
    if (bn_init_bits(bn, bits) != SUCCESS)
        return FAILURE;
    
    do {
        // fill with random bytes
        if (rng_get_bytes(rng, (unsigned char *)bn->data, bn->length * sizeof(uint32_t)) != SUCCESS)
            goto fail;

        // apply mask
        if (bits % 32)
            bn->data[bits / 32] &= ~((1 << (bits % 32)) - 1);

        // make sure that this is less than max
    } while (bn_cmp(bn, max) >= 0);

    return SUCCESS;

fail:
    bn_destroy(bn);
    return FAILURE;
}

int bn_cmp(const bn_t *a, const bn_t *b)
{
    unsigned int alen, blen, i;
    for (alen = a->length; alen > b->length; alen--)
        if (a->data[alen - 1] != 0)
            return 1;
    for (blen = b->length; blen > a->length; blen--)
        if (b->data[blen - 1] != 0)
            return -1;
    
    // now alen == blen
    for (i = alen; i > 0; i--)
        if (a->data[i-1] != b->data[i-1])
            return a->data[i-1] > b->data[i-1] ? 1 : -1;

    return 0;
}

int bn_modexp(bn_t *dst, const bn_t *b, const bn_t *e, const bn_t *m)
{
    int result = FAILURE;
    unsigned int i;
    bn_t base, zero, tmp, q;

    bn_init(&base);
    bn_init(&zero);
    bn_init(&tmp);
    bn_init(&q);

    bn_destroy(dst);
    if (bn_init_bits(dst, bn_length(m)) != SUCCESS)
        goto done;
    dst->data[0] = 1;

    if (bn_div(&q, &base, b, m) != SUCCESS)
        goto done;

    for (i = 0; i < bn_length(e); i++)
    {
        if (e->data[i / 32] & (1 << (i % 32)))
        {
            if (bn_mul(&tmp, dst, &base) != SUCCESS)
                goto done;
            if (bn_div(&q, dst, &tmp, m) != SUCCESS)
                goto done;
        }
        if (bn_mul(&tmp, &base, &base) != SUCCESS)
            goto done;
        if (bn_div(&q, &base, &tmp, m) != SUCCESS)
            goto done;
    }

    result = SUCCESS;

done:
    bn_destroy(&base);
    bn_destroy(&zero);
    bn_destroy(&tmp);
    bn_destroy(&q);
    return result;
}

// assumes that dst is large enough to contain result of dst + src
static void _add(uint32_t *dst, uint32_t *src, unsigned int slen)
{
    uint32_t carry, c, sum;
    unsigned int i;
    for (carry = 0, i = 0; i < slen; i++)
    {
        c = 0;
        sum = dst[i] + src[i];
        if (sum < dst[i])
            c = 1;
        sum += carry;
        if (sum < dst[i])
            c = 1;
        carry = c;
        dst[i] = sum;
    }

    while (carry)
    {
        sum = dst[i] + carry;
        if (sum < dst[i])
            carry = 1;
        else
            carry = 0;
        dst[i] = sum;
        i++;
    }
}

// subtract src from dst
static void _sub(uint32_t *dst, uint32_t *src, unsigned int slen)
{
    uint32_t carry, c, sum;
    unsigned int i;
    for (carry = 0, i = 0; i < slen; i++)
    {
        c = 0;
        sum = dst[i] - src[i];
        if (sum > dst[i])
            c = 1;
        sum -= carry;
        if (sum > dst[i])
            c = 1;
        carry = c;
        dst[i] = sum;
    }

    while (carry)
    {
        sum = dst[i] - carry;
        if (sum > dst[i])
            carry = 1;
        else
            carry = 0;
        dst[i] = sum;
        i++;
    }
}

int bn_mul(bn_t *dst, const bn_t *a, const bn_t *b)
{
    unsigned int i, j;
    uint32_t x[2];
    uint64_t x64;
    bn_destroy(dst);
    if (bn_init_bits(dst, bn_length(a) + bn_length(b)) != SUCCESS)
        return FAILURE;

    for (i = 0; i < a->length; i++)
    {
        for (j = 0; j < b->length; j++)
        {
            x64 = (uint64_t)a->data[i] * (uint64_t)b->data[j];
            x[0] = x64;
            x[1] = x64 >> 32;
            _add(&dst->data[i + j], x, 2);
        }
    }

    return SUCCESS;
}

void bn_slr(bn_t *dst, unsigned int cnt)
{
    uint32_t carry;
    unsigned int i;

    while (cnt > 32)
    {
        for (i = dst->length, carry = 0; i > 0; i--)
        {
            uint32_t out = dst->data[i-1];
            dst->data[i-1] = carry;
            carry = out;
        }
        cnt -= 32;
    }

    if (cnt > 0)
    {
        for (i = dst->length, carry = 0; i > 0; i--)
        {
            uint32_t out = dst->data[i-1] << (32 - cnt);
            dst->data[i-1] = (dst->data[i-1] >> cnt) | carry;
            carry = out;
        }
    }
}

static void _sll(bn_t *dst, unsigned int cnt)
{
    uint32_t carry;
    unsigned int i;

    while (cnt > 32)
    {
        for (i = 0, carry = 0; i < dst->length; i++)
        {
            uint32_t out = dst->data[i];
            dst->data[i] = carry;
            carry = out;
        }
        cnt -= 32;
    }

    if (cnt > 0)
    {
        for (i = 0, carry = 0; i < dst->length; i++)
        {
            uint32_t out = dst->data[i] >> (32 - cnt);
            dst->data[i] = (dst->data[i] << cnt) | carry;
            carry = out;
        }
    }
}

int bn_div(bn_t *Q, bn_t *R, const bn_t *N, const bn_t *D)
{
    unsigned int i, len;
    bn_destroy(Q);
    bn_destroy(R);
    if (bn_init_bits(R, bn_length(D) + 1) != SUCCESS)
        return FAILURE;
    if (bn_length(N) > bn_length(D))
        len = bn_length(N) - bn_length(D);
    else
        len = 1;
    if (bn_init_bits(Q, len) != SUCCESS)
    {
        bn_destroy(R);
        return FAILURE;
    }

    for (i = bn_length(N); i-- > 0;)
    {
        _sll(R, 1);
        R->data[0] |= !!(N->data[i / 32] & (1 << (i % 32)));
        if (bn_cmp(R, D) >= 0)
        {
            _sub(R->data, D->data, D->length);
            Q->data[i / 32] |= 1 << (i % 32);
        }
    }

    return SUCCESS;
}

static void _print_bn(bn_t *bn)
{
    unsigned int i;
    fdprintf(STDERR, "0x");
    if (bn->length == 0)
    {
        fdprintf(STDERR, "0");
    }
    else
    {
        for (i = bn->length; i > 0; i--)
            fdprintf(STDERR, "%08X", bn->data[i-1]);
    }
    fdprintf(STDERR, "\n");
}

int bn_self_test()
{
    int result = FAILURE;
    const unsigned char mul_a[] = {0x10, 0x20, 0x30, 0x40, 0x50},
        mul_b[] = {0x55, 0x55, 0x55, 0x55, 0x55},
        mul_exp[] = {0x05, 0x60, 0x10, 0x15, 0x6f, 0xfa, 0x9f, 0xef, 0xea, 0x90},
        q_exp[] = {0x05},
        r_exp[] = {0x04, 0xb4, 0x64, 0x13, 0xc5},
        modpow_g[] = {0xA4, 0xD1, 0xCB, 0xD5, 0xC3, 0xFD, 0x34, 0x12, 0x67, 0x65, 0xA4, 0x42, 0xEF, 0xB9, 0x99, 0x05, 0xF8, 0x10, 0x4D, 0xD2, 0x58, 0xAC, 0x50, 0x7F, 0xD6, 0x40, 0x6C, 0xFF, 0x14, 0x26, 0x6D, 0x31, 0x26, 0x6F, 0xEA, 0x1E, 0x5C, 0x41, 0x56, 0x4B, 0x77, 0x7E, 0x69, 0x0F, 0x55, 0x04, 0xF2, 0x13, 0x16, 0x02, 0x17, 0xB4, 0xB0, 0x1B, 0x88, 0x6A, 0x5E, 0x91, 0x54, 0x7F, 0x9E, 0x27, 0x49, 0xF4, 0xD7, 0xFB, 0xD7, 0xD3, 0xB9, 0xA9, 0x2E, 0xE1, 0x90, 0x9D, 0x0D, 0x22, 0x63, 0xF8, 0x0A, 0x76, 0xA6, 0xA2, 0x4C, 0x08, 0x7A, 0x09, 0x1F, 0x53, 0x1D, 0xBF, 0x0A, 0x01, 0x69, 0xB6, 0xA2, 0x8A, 0xD6, 0x62, 0xA4, 0xD1, 0x8E, 0x73, 0xAF, 0xA3, 0x2D, 0x77, 0x9D, 0x59, 0x18, 0xD0, 0x8B, 0xC8, 0x85, 0x8F, 0x4D, 0xCE, 0xF9, 0x7C, 0x2A, 0x24, 0x85, 0x5E, 0x6E, 0xEB, 0x22, 0xB3, 0xB2, 0xE5},
        modpow_p[] = {0xB1, 0x0B, 0x8F, 0x96, 0xA0, 0x80, 0xE0, 0x1D, 0xDE, 0x92, 0xDE, 0x5E, 0xAE, 0x5D, 0x54, 0xEC, 0x52, 0xC9, 0x9F, 0xBC, 0xFB, 0x06, 0xA3, 0xC6, 0x9A, 0x6A, 0x9D, 0xCA, 0x52, 0xD2, 0x3B, 0x61, 0x60, 0x73, 0xE2, 0x86, 0x75, 0xA2, 0x3D, 0x18, 0x98, 0x38, 0xEF, 0x1E, 0x2E, 0xE6, 0x52, 0xC0, 0x13, 0xEC, 0xB4, 0xAE, 0xA9, 0x06, 0x11, 0x23, 0x24, 0x97, 0x5C, 0x3C, 0xD4, 0x9B, 0x83, 0xBF, 0xAC, 0xCB, 0xDD, 0x7D, 0x90, 0xC4, 0xBD, 0x70, 0x98, 0x48, 0x8E, 0x9C, 0x21, 0x9A, 0x73, 0x72, 0x4E, 0xFF, 0xD6, 0xFA, 0xE5, 0x64, 0x47, 0x38, 0xFA, 0xA3, 0x1A, 0x4F, 0xF5, 0x5B, 0xCC, 0xC0, 0xA1, 0x51, 0xAF, 0x5F, 0x0D, 0xC8, 0xB4, 0xBD, 0x45, 0xBF, 0x37, 0xDF, 0x36, 0x5C, 0x1A, 0x65, 0xE6, 0x8C, 0xFD, 0xA7, 0x6D, 0x4D, 0xA7, 0x08, 0xDF, 0x1F, 0xB2, 0xBC, 0x2E, 0x4A, 0x43, 0x71},
        modpow_q[] = {0xF5, 0x18, 0xAA, 0x87, 0x81, 0xA8, 0xDF, 0x27, 0x8A, 0xBA, 0x4E, 0x7D, 0x64, 0xB7, 0xCB, 0x9D, 0x49, 0x46, 0x23, 0x53};
    bn_t a, b, res, exp, q, r, zero;

    bn_init(&a);
    bn_init(&b);
    bn_init(&res);
    bn_init(&exp);
    bn_init(&q);
    bn_init(&r);
    bn_init(&zero);

    bn_from_bytes(&a, mul_a, sizeof(mul_a));
    bn_from_bytes(&b, mul_b, sizeof(mul_b));
    bn_from_bytes(&exp, mul_exp, sizeof(mul_exp));
    
    bn_mul(&res, &a, &b);
#ifdef DEBUG
    fdprintf(STDERR, "Multiply\n");
    fdprintf(STDERR, "A = "); _print_bn(&a);
    fdprintf(STDERR, "B = "); _print_bn(&b);
    fdprintf(STDERR, "res = "); _print_bn(&res);
    fdprintf(STDERR, "exp = "); _print_bn(&exp);
#endif

    if (bn_cmp(&res, &exp) != 0)
        goto fail;

    bn_div(&q, &r, &exp, &a);
#ifdef DEBUG
    fdprintf(STDERR, "Divide 1\n");
    fdprintf(STDERR, "N = "); _print_bn(&exp);
    fdprintf(STDERR, "D = "); _print_bn(&a);
    fdprintf(STDERR, "Q = "); _print_bn(&q);
    fdprintf(STDERR, "R = "); _print_bn(&r);
#endif

    if (bn_cmp(&q, &b) != 0 || bn_cmp(&zero, &r) != 0)
        goto fail;

    bn_div(&q, &r, &b, &a);
#ifdef DEBUG
    fdprintf(STDERR, "Divide 2\n");
    fdprintf(STDERR, "N = "); _print_bn(&b);
    fdprintf(STDERR, "D = "); _print_bn(&a);
    fdprintf(STDERR, "Q = "); _print_bn(&q);
    fdprintf(STDERR, "R = "); _print_bn(&r);
#endif

    bn_from_bytes(&exp, q_exp, sizeof(q_exp));
    if (bn_cmp(&q, &exp) != 0)
        goto fail;
    bn_from_bytes(&exp, r_exp, sizeof(r_exp));
    if (bn_cmp(&r, &exp) != 0)
        goto fail;

    bn_from_bytes(&a, modpow_g, sizeof(modpow_g));
    bn_from_bytes(&q, modpow_q, sizeof(modpow_q));
    bn_from_bytes(&b, modpow_p, sizeof(modpow_p));

    bn_modexp(&res, &a, &q, &b);
#ifdef DEBUG
    fdprintf(STDERR, "Modular exponentiation\n");
    fdprintf(STDERR, "Base = "); _print_bn(&a);
    fdprintf(STDERR, "Exp = "); _print_bn(&q);
    fdprintf(STDERR, "Mod = "); _print_bn(&b);
    fdprintf(STDERR, "res = "); _print_bn(&res);
#endif

    bn_const(&exp, 1);
    if (bn_cmp(&res, &exp) != 0)
        goto fail;

    result = SUCCESS;

fail:
    if (result != SUCCESS)
        fdprintf(STDERR, "BN self-test FAILED!\n");

    bn_destroy(&a);
    bn_destroy(&b);
    bn_destroy(&res);
    bn_destroy(&exp);
    bn_destroy(&q);
    bn_destroy(&r);
    return result;
}
