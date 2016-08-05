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

#include "xpack.h"

#define MAX_BUF_LEN (4 * 1024 * 1024)

xpk_ctx_t* xpk_init(size_t size)
{
    xpk_ctx_t *ctx = (xpk_ctx_t *) malloc(sizeof(xpk_ctx_t));
    if (size == 0)
        size = 1024;
    ctx->buf = malloc(sizeof(char) * size);
    ctx->idx = 0;
    ctx->len = size;
    return ctx;
}

int _xpk_resize(xpk_ctx_t *ctx, size_t size)
{
    if (size <= ctx->len)
        return 0;
    if (size <= MAX_BUF_LEN)
    {
        ctx->buf = realloc(ctx->buf, size);
        ctx->len = size;
        return 0;
    }
    return -1;
}

void xpk_reset(xpk_ctx_t *ctx, size_t size)
{
    if (_xpk_resize(ctx, size) == 0)
    {
        memset(ctx->buf, 0, ctx->len);
        ctx->idx = 0;
    }
}

/* Helper to swap endianness */
int16_t le2be16_s(int16_t n)
{
    return (n << 8) | ((n >> 8) & 0xFF);
}
uint16_t le2be16_u(uint16_t n)
{
    return (n << 8) | (n >> 8);
}
int32_t le2be32_s(int32_t n)
{
    n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0x00FF00FF);
    return (n << 16) | ((n >> 16) & 0xFFFF);
}
uint32_t le2be32_u(uint32_t n)
{
    n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0x00FF00FF);
    return (n << 16) | (n >> 16);
}
int64_t le2be64_s(int64_t n)
{
    n = ((n << 8) & 0xFF00FF00FF00FF00) | ((n >> 8) & 0x00FF00FF00FF00FF);
    n = ((n << 16) & 0xFFFF0000FFFF0000) | ((n >> 16) & 0x0000FFFF0000FFFF);
    return (n << 32) | ((n >> 32) & 0xFFFFFFFF);
}
uint64_t le2be64_u(uint64_t n)
{
    n = ((n << 8) & 0xFF00FF00FF00FF00) | ((n >> 8) & 0x00FF00FF00FF00FF);
    n = ((n << 16) & 0xFFFF0000FFFF0000) | ((n >> 16) & 0x0000FFFF0000FFFF);
    return (n << 32) | (n >> 32);
}

xpk_err xpk_pack_fixint(xpk_ctx_t *ctx, uint8_t b)
{
    return xpk_write(ctx, (const char*) &b, sizeof(uint8_t));
}

xpk_err xpk_write_marker(xpk_ctx_t *ctx, xpk_type t)
{
    return xpk_write(ctx, (const char*) &t, sizeof(xpk_type));
}

xpk_err xpk_read_marker(xpk_ctx_t *ctx, xpk_type *t)
{
    xpk_err err;
    if ((err = xpk_read(ctx, (char *) t, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
    return XPK_ERR_NONE;
}

xpk_err xpk_read_obj(xpk_ctx_t *ctx, xpk_obj_t *o)
{
    xpk_err err;
    uint8_t marker = XPK_NONE;

    if ((err = xpk_read_marker(ctx, (xpk_type *) &marker)) != XPK_ERR_NONE) return err;
    o->type = marker;
    switch (marker)
    {
        case XPK_FALSE:
            o->data.b = 0;
            break;
        case XPK_TRUE:
            o->data.b = 1;
            break;
        case XPK_BYTES:
        case XPK_STRING:
            o->data.len = 0;
            if ((err = xpk_read(ctx, (char *) &o->data.len, sizeof(uint16_t))) != XPK_ERR_NONE) return err;
            o->data.len = le2be16_u(o->data.len);
            break;
        case XPK_ARRAY:
        case XPK_MAP:
            o->data.len = 0;
            if ((err = xpk_read(ctx, (char *) &o->data.len, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
            break;
        case XPK_INT8:
            if ((err = xpk_read(ctx, (char *) &o->data.i8, sizeof(int8_t))) != XPK_ERR_NONE) return err;
            break;
        case XPK_INT16:
            if ((err = xpk_read(ctx, (char *) &o->data.i16, sizeof(int16_t))) != XPK_ERR_NONE) return err;
            o->data.i16 = le2be16_s(o->data.i16);
            break;
        case XPK_INT32:
            if ((err = xpk_read(ctx, (char *) &o->data.i32, sizeof(int32_t))) != XPK_ERR_NONE) return err;
            o->data.i32 = le2be32_s(o->data.i32);
            break;
        case XPK_INT64:
            if ((err = xpk_read(ctx, (char *) &o->data.i64, sizeof(int64_t))) != XPK_ERR_NONE) return err;
            o->data.i64 = le2be64_s(o->data.i64);
            break;
        case XPK_UINT8:
            if ((err = xpk_read(ctx, (char *) &o->data.u8, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
            break;
        case XPK_UINT16:
            if ((err = xpk_read(ctx, (char *) &o->data.u16, sizeof(uint16_t))) != XPK_ERR_NONE) return err;
            o->data.u16 = le2be16_u(o->data.u16);
            break;
        case XPK_UINT32:
            if ((err = xpk_read(ctx, (char *) &o->data.u32, sizeof(uint32_t))) != XPK_ERR_NONE) return err;
            o->data.u32 = le2be32_u(o->data.u32);
            break;
        case XPK_UINT64:
            if ((err = xpk_read(ctx, (char *) &o->data.u64, sizeof(uint64_t))) != XPK_ERR_NONE) return err;
            o->data.u64 = le2be64_u(o->data.u64);
            break;
        case XPK_NIL:
            break;
        default:
            if (marker < (1 << 7)) { o->type = XPK_POSITIVE_FIXINT; o->data.u8 = marker; }
            else if (marker < 0xA0) { o->type = XPK_FIXSTRING; o->data.len = marker & 0x1F; }
            else if (marker >= 0xE0) { o->type = XPK_NEGATIVE_FIXINT; o->data.i8 = marker; }
            else { o->type = XPK_NONE; o->data.u64 = 0; }
    }

    return XPK_ERR_NONE;
}

xpk_err xpk_next_type(xpk_ctx_t *ctx, xpk_type *t)
{
    xpk_err err;
    uint8_t marker;
    if ((err = xpk_peek(ctx, (char *) &marker, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
    switch (marker)
    {
        case XPK_FALSE:
        case XPK_TRUE:
        case XPK_BYTES:
        case XPK_STRING:
        case XPK_ARRAY:
        case XPK_MAP:
        case XPK_INT8:
        case XPK_INT16:
        case XPK_INT32:
        case XPK_INT64:
        case XPK_UINT8:
        case XPK_UINT16:
        case XPK_UINT32:
        case XPK_UINT64:
        case XPK_NIL:
            *t = marker;
            break;
        default:
            if (marker < (1 << 7))
                *t = XPK_POSITIVE_FIXINT;
            else if (marker < 0xA0)
                *t = XPK_FIXSTRING;
            else if (marker >= 0xE0)
                *t = XPK_NEGATIVE_FIXINT;
            else
                return XPK_ERR_INVALID_TYPE;
    }
    return XPK_ERR_NONE;
}

xpk_err xpk_write(xpk_ctx_t *ctx, const char *in, size_t len)
{
    if (ctx->idx + len <= ctx->len || _xpk_resize(ctx, ctx->len * 2) == 0)
    {
        memcpy(&ctx->buf[ctx->idx], in, len);
        ctx->idx += len;
        return XPK_ERR_NONE;
    }
    return XPK_ERR_INTERNAL;
}

xpk_err xpk_read(xpk_ctx_t *ctx, char *out, size_t len)
{
    if (ctx->idx + len <= ctx->len)
    {
        memcpy(out, &ctx->buf[ctx->idx], len);
        ctx->idx += len;
        return XPK_ERR_NONE;
    }
    return XPK_ERR_INTERNAL;
}

xpk_err xpk_peek(xpk_ctx_t *ctx, char *out, size_t len)
{
    if (ctx->idx + len > ctx->len)
        return XPK_ERR_INTERNAL;
    memcpy(out, &ctx->buf[ctx->idx], len);
    return XPK_ERR_NONE;
}

xpk_err xpk_pack_int(xpk_ctx_t *ctx, int64_t si)
{
    xpk_err err = XPK_ERR_NONE;
    if (si >= 0)
        return xpk_pack_uint(ctx, si);
    if (si >= -(1 << 5))
        return xpk_pack_fixint(ctx, si);
    else if (si >= -(1 << 7))
    {
        if ((err = xpk_write_marker(ctx, XPK_INT8)) != XPK_ERR_NONE) return err;
        if ((err = xpk_write(ctx, (const char *) &si, sizeof(int8_t))) != XPK_ERR_NONE) return err;
    }
    else if (si >= -(1 << 15))
    {
        if ((err = xpk_write_marker(ctx, XPK_INT16)) != XPK_ERR_NONE) return err;
        si = le2be16_s(si);
        if ((err = xpk_write(ctx, (const char *) &si, sizeof(int16_t))) != XPK_ERR_NONE) return err;
    }
    else if (si >= -(1 << 31))
    {
        if ((err = xpk_write_marker(ctx, XPK_INT32)) != XPK_ERR_NONE) return err;
        si = le2be32_s(si);
        if ((err = xpk_write(ctx, (const char *) &si, sizeof(int32_t))) != XPK_ERR_NONE) return err;
    }
    else
    {
        if ((err = xpk_write_marker(ctx, XPK_INT64)) != XPK_ERR_NONE) return err;
        si = le2be64_s(si);
        if ((err = xpk_write(ctx, (const char *) &si, sizeof(int64_t))) != XPK_ERR_NONE) return err;
    }
    return err;
}

xpk_err xpk_pack_uint(xpk_ctx_t *ctx, uint64_t ui)
{
    xpk_err err = XPK_ERR_NONE;
    if (ui < (1 << 7))
        return xpk_pack_fixint(ctx, ui);
    else if (ui < (1 << 8))
    {
        if ((err = xpk_write_marker(ctx, XPK_UINT8)) != XPK_ERR_NONE) return err;
        if ((err = xpk_write(ctx, (const char *) &ui, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
    }
    else if (ui < (1 << 16))
    {
        if ((err = xpk_write_marker(ctx, XPK_UINT16)) != XPK_ERR_NONE) return err;
        ui = le2be16_u(ui);
        if ((err = xpk_write(ctx, (const char *) &ui, sizeof(uint16_t))) != XPK_ERR_NONE) return err;
    }
    else if (ui <= 0xFFFFFFFF)
    {
        if ((err = xpk_write_marker(ctx, XPK_UINT32)) != XPK_ERR_NONE) return err;
        ui = le2be32_u(ui);
        if ((err = xpk_write(ctx, (const char *) &ui, sizeof(uint32_t))) != XPK_ERR_NONE) return err;
    }
    else
    {
        if ((err = xpk_write_marker(ctx, XPK_UINT64)) != XPK_ERR_NONE) return err;
        ui = le2be64_u(ui);
        if ((err = xpk_write(ctx, (const char *) &ui, sizeof(uint64_t))) != XPK_ERR_NONE) return err;
    }
    return err;
}

xpk_err xpk_pack_none(xpk_ctx_t *ctx)
{
    return xpk_write_marker(ctx, XPK_NONE);
}

xpk_err xpk_pack_nil(xpk_ctx_t *ctx)
{
    return xpk_write_marker(ctx, XPK_NIL);
}

xpk_err xpk_pack_bool(xpk_ctx_t *ctx, uint8_t b)
{
    return b ? xpk_write_marker(ctx, XPK_TRUE) : xpk_write_marker(ctx, XPK_FALSE);
}

xpk_err xpk_pack_str(xpk_ctx_t *ctx, const char *str)
{
    xpk_err err = XPK_ERR_NONE;

    size_t len_b, len = strlen(str);
    if (len <= 0x1F)
    {
        uint8_t val = XPK_FIXSTRING | len;
        if ((err = xpk_write(ctx, (const char *) &val, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
        if (len > 0 && (err = xpk_write(ctx, str, len)) != XPK_ERR_NONE) return err;
    }
    else if (len < (1 << 16))
    {
        if ((err = xpk_write_marker(ctx, XPK_STRING)) != XPK_ERR_NONE) return err;
        len_b = le2be16_u(len);
        if ((err = xpk_write(ctx, (const char *) &len_b, sizeof(uint16_t))) != XPK_ERR_NONE) return err;
        if (len > 0 && (err = xpk_write(ctx, str, len)) != XPK_ERR_NONE) return err;
    }
    else
        err = XPK_ERR_DATA_LONG;

    return err;
}

xpk_err xpk_pack_bytes(xpk_ctx_t *ctx, const char *bytes, size_t len)
{
    xpk_err err = XPK_ERR_NONE;

    size_t len_b;
    if (len < (1 << 16))
    {
        if ((err = xpk_write_marker(ctx, XPK_BYTES)) != XPK_ERR_NONE) return err;
        len_b = le2be16_u(len);
        if ((err = xpk_write(ctx, (const char *) &len_b, sizeof(uint16_t))) != XPK_ERR_NONE) return err;
        if (len > 0 && (err = xpk_write(ctx, bytes, len)) != XPK_ERR_NONE) return err;
    }
    else
        err = XPK_ERR_DATA_LONG;

    return err;
}

xpk_err xpk_pack_array(xpk_ctx_t *ctx, size_t len)
{
    xpk_err err = XPK_ERR_NONE;

    if (len < (1 << 8))
    {
        if ((err = xpk_write_marker(ctx, XPK_ARRAY)) != XPK_ERR_NONE) return err;
        if ((err = xpk_write(ctx, (const char *) &len, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
    }
    else
        err = XPK_ERR_ARRAY_LONG;

    return err;
}

xpk_err xpk_pack_map(xpk_ctx_t *ctx, size_t len)
{
    xpk_err err = XPK_ERR_NONE;

    if (len < (1 << 8))
    {
        if ((err = xpk_write_marker(ctx, XPK_MAP)) != XPK_ERR_NONE) return err;
        if ((err = xpk_write(ctx, (const char *) &len, sizeof(uint8_t))) != XPK_ERR_NONE) return err;
    }
    else
        err = XPK_ERR_MAP_LONG;

    return err;
}


xpk_err xpk_unpack_int(xpk_ctx_t *ctx, uint64_t *i, uint8_t *sign)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;

    switch (o.type)
    {
        case XPK_NEGATIVE_FIXINT:
        case XPK_INT8:
            *i = o.data.i8;
            *sign = 1;
            break;
        case XPK_INT16:
            *i = o.data.i16;
            *sign = 1;
            break;
        case XPK_INT32:
            *i = o.data.i32;
            *sign = 1;
            break;
        case XPK_INT64:
            *i = o.data.i64;
            *sign = 1;
            break;
        case XPK_POSITIVE_FIXINT:
        case XPK_UINT8:
            *i = o.data.u8;
            *sign = 0;
            break;
        case XPK_UINT16:
            *i = o.data.u16;
            *sign = 0;
            break;
        case XPK_UINT32:
            *i = o.data.u32;
            *sign = 0;
            break;
        case XPK_UINT64:
            *i = o.data.u64;
            *sign = 0;
            break;
        default:
            return XPK_ERR_INVALID_TYPE;
    }

    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_nil(xpk_ctx_t *ctx)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_NIL)
        return XPK_ERR_INVALID_TYPE;
    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_bool(xpk_ctx_t *ctx, uint8_t *b)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_TRUE && o.type != XPK_FALSE)
        return XPK_ERR_INVALID_TYPE;
    *b = o.data.b;
    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_str(xpk_ctx_t *ctx, size_t *len)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_FIXSTRING && o.type != XPK_STRING)
        return XPK_ERR_INVALID_TYPE;
    *len = o.data.len;
    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_bytes(xpk_ctx_t *ctx, size_t *len)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_BYTES)
        return XPK_ERR_INVALID_TYPE;
    *len = o.data.len;
    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_array(xpk_ctx_t *ctx, size_t *len)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_ARRAY)
        return XPK_ERR_INVALID_TYPE;
    *len = o.data.len;
    return XPK_ERR_NONE;
}

xpk_err xpk_unpack_map(xpk_ctx_t *ctx, size_t *len)
{
    xpk_err err;
    xpk_obj_t o;

    if ((err = xpk_read_obj(ctx, &o)) != XPK_ERR_NONE) return err;
    if (o.type != XPK_MAP)
        return XPK_ERR_INVALID_TYPE;
    *len = o.data.len;
    return XPK_ERR_NONE;
}
