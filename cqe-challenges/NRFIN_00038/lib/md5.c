/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* MD5 implementation based on RFC-1321 */

#include "libc.h"

#include "md5.h"

struct md5_ctx {
    unsigned int AA, BB, CC, DD;
};

static inline unsigned int
s(unsigned int i)
{
    unsigned int shifts[][4] = {
        { 7, 12, 17, 22 },
        { 5, 9, 14, 20 },
        { 4, 11, 16, 23 },
        { 6, 10, 15, 21 }
    };

    return shifts[i / 16][i % 4];
}

static inline unsigned int
rotateleft(unsigned int v, unsigned int s)
{
    return (v << s) | (v >> (32 - s));
}

static inline unsigned int
T(unsigned int i)
{
    return fabs(sin(i + 1)) * pow(2, 32);
}

static inline unsigned int
k(unsigned int i)
{
    switch (i / 16) {
    case 0: return i;
    case 1: return (5 * i + 1) % 16;
    case 2: return (3 * i + 5) % 16;
    case 3: return (7 * i) % 16;
    }

    return 0;
}

static inline unsigned int
F(unsigned int X, unsigned int Y, unsigned int Z)
{
    return (X & Y) | (~X & Z);
}

static inline unsigned int
G(unsigned int X, unsigned int Y, unsigned int Z)
{
    return (X & Z) | (Y & ~Z);
}
    
static inline unsigned int
H(unsigned int X, unsigned int Y, unsigned int Z)
{
    return X ^ Y ^ Z;
}

static inline unsigned int
I(unsigned int X, unsigned int Y, unsigned int Z)
{
    return Y ^ (X | ~Z);
}

static void
md5_chunk(unsigned char *X_, struct md5_ctx *ctx)
{
    unsigned int *X = (unsigned int *)X_;

    unsigned int A = ctx->AA;
    unsigned int B = ctx->BB;
    unsigned int C = ctx->CC;
    unsigned int D = ctx->DD;
    unsigned int x, tmp;

    unsigned int (*round_ops[])(unsigned int, unsigned int, unsigned int) =
            { F, G, H, I };

    size_t i;

    for (i = 0; i < 64; i++) {
        x = round_ops[i / 16](B, C, D);

        tmp = D;
        D = C;
        C = B;
        B = B + rotateleft(A + x + X[k(i)] + T(i), s(i));
        A = tmp;
    }

    ctx->AA += A;
    ctx->BB += B;
    ctx->CC += C;
    ctx->DD += D;
}

static int
md5_pad(unsigned char *dst, const unsigned char *src, size_t n,
        unsigned long long total, int is_extra)
{
    size_t to_pad;

    if (n >= 64) {
        memcpy(dst, src, 64);
        return n == 64;
    } else {
        to_pad = 64 - n;

        memcpy(dst, src, n);
        dst += n;

#ifndef PATCHED
        // Suppress unused warnings
        (void)(total);
        (void)(is_extra);

        memset(dst, '\x80', to_pad);
        return 0;
#else
        if (!is_extra) {
            *dst++ = '\x80';
            to_pad--;
        }

        memset(dst, '\x00', to_pad >= 8 ? to_pad - 8 : to_pad);
        if (to_pad < 8)
            return 1;

        dst += to_pad - 8;
        *(unsigned long long *)dst = total * 8;
        return 0;
#endif
    }
}

static void
md5_update(const unsigned char *msg, size_t n, unsigned int total, struct md5_ctx *ctx)
{
    unsigned char block[64];
    int extra_block_needed;

    while (n > 64) {
        md5_pad(block, msg, n, total, 0);
        md5_chunk(block, ctx);

        msg += 64;
        n -= 64;
    }

    // Do the last block
    extra_block_needed = md5_pad(block, msg, n, total, 0);
    md5_chunk(block, ctx);

    // If we needed to add a whole block of padding, do it now
    if (extra_block_needed) {
        md5_pad(block, NULL, 0, total, n != 64);
        md5_chunk(block, ctx);
    }

    // This may be optimized out but make a token effort to c=ear this info
    memset(block, '\x00', sizeof(block));
    total = extra_block_needed = 0;
}

void
md5(const unsigned char *msg, size_t n, unsigned char *digest)
{
    struct md5_ctx ctx;

    ctx.AA = 0x67452301;
    ctx.BB = 0xefcdab89;
    ctx.CC = 0x98badcfe;
    ctx.DD = 0x10325476;

    md5_update(msg, n, n, &ctx);

    *(unsigned int *)digest = ctx.AA;
    *(unsigned int *)(digest + 4) = ctx.BB;
    *(unsigned int *)(digest + 8) = ctx.CC;
    *(unsigned int *)(digest + 12) = ctx.DD;

    // This may be optimized out but make a token effort to clear this info
    memset(&ctx, '\x00', sizeof(ctx));
}

void
md5_hmac(const unsigned char *key, size_t key_len, const unsigned char *msg,
        size_t msg_len, unsigned char *mac)
{
    struct md5_ctx o_ctx, i_ctx;
    unsigned char key_block[64], o_key_pad[64], i_key_pad[64];
    size_t i;

    memset(key_block, '\x00', 64);

    if (key_len > 64)
        md5(key, key_len, key_block);

    if (key_len < 64)
        memcpy(key_block, key, key_len);

    for (i = 0; i < 64; i++) {
        o_key_pad[i] = 0x5c ^ key_block[i];
        i_key_pad[i] = 0x36 ^ key_block[i];
    }

    o_ctx.AA = i_ctx.AA = 0x67452301;
    o_ctx.BB = i_ctx.BB = 0xefcdab89;
    o_ctx.CC = i_ctx.CC = 0x98badcfe;
    o_ctx.DD = i_ctx.DD = 0x10325476;

    md5_chunk(i_key_pad, &i_ctx);
    md5_update(msg, msg_len, 64 + msg_len, &i_ctx);

    md5_chunk(o_key_pad, &o_ctx);
    md5_update((unsigned char *)(&i_ctx), sizeof(i_ctx), 64 + sizeof(i_ctx), &o_ctx);

    *(unsigned int *)mac = o_ctx.AA;
    *(unsigned int *)(mac + 4) = o_ctx.BB;
    *(unsigned int *)(mac + 8) = o_ctx.CC;
    *(unsigned int *)(mac + 12) = o_ctx.DD;

    // This may be optimized out but make a token effort to clear this info
    memset(&o_ctx, '\x00', sizeof(o_ctx));
    memset(&i_ctx, '\x00', sizeof(i_ctx));
    memset(key_block, '\x00', sizeof(key_block));
    memset(o_key_pad, '\x00', sizeof(o_key_pad));
    memset(i_key_pad, '\x00', sizeof(i_key_pad));
}

