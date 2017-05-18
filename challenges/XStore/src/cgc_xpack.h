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

#ifndef XPACK_H
#define XPACK_H

#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_string.h"

typedef enum {
    XPK_POSITIVE_FIXINT = 0x00,
    XPK_NEGATIVE_FIXINT = 0xE0,
    XPK_FIXSTRING       = 0x80,
    XPK_NONE            = 0xA0,
    XPK_FALSE           = 0xA1,
    XPK_TRUE            = 0xA2,
    XPK_BYTES           = 0xA3,
    XPK_ARRAY           = 0xA4,
    XPK_MAP             = 0xA5,
    XPK_NIL             = 0xA6,
    XPK_INT8            = 0xB0,
    XPK_INT16           = 0xB1,
    XPK_INT32           = 0xB2,
    XPK_INT64           = 0xB3,
    XPK_UINT8           = 0xC0,
    XPK_UINT16          = 0xC1,
    XPK_UINT32          = 0xC2,
    XPK_UINT64          = 0xC3,
    XPK_STRING          = 0xD0
} __attribute__((packed)) xpk_type;

typedef enum {
    XPK_ERR_NONE            = 0x00,
    XPK_ERR_DATA_LONG       = 0x01,
    XPK_ERR_ARRAY_LONG      = 0x02,
    XPK_ERR_MAP_LONG        = 0x03,
    XPK_ERR_INVALID_TYPE    = 0x04,
    XPK_ERR_INTERNAL        = 0x05,
} __attribute__((packed)) xpk_err;

typedef union {
    uint8_t b;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    cgc_size_t len;
} xpk_data_t;

typedef struct {
    xpk_type type;
    xpk_data_t data;
} xpk_obj_t;

typedef struct {
    char *buf;
    cgc_size_t idx;
    cgc_size_t len;
} xpk_ctx_t;

/* Utility */
xpk_ctx_t* cgc_xpk_init(cgc_size_t size);
void cgc_xpk_reset(xpk_ctx_t *ctx, cgc_size_t size);
xpk_err cgc_xpk_write(xpk_ctx_t *ctx, const char *in, cgc_size_t len);
xpk_err cgc_xpk_read(xpk_ctx_t *ctx, char *out, cgc_size_t len);
xpk_err cgc_xpk_peek(xpk_ctx_t *ctx, char *out, cgc_size_t len);
xpk_err cgc_xpk_read_obj(xpk_ctx_t *ctx, xpk_obj_t *o);
xpk_err cgc_xpk_next_type(xpk_ctx_t *ctx, xpk_type *t);

/* Pack */
xpk_err cgc_xpk_pack_int(xpk_ctx_t *ctx, int64_t si);
xpk_err cgc_xpk_pack_uint(xpk_ctx_t *ctx, uint64_t ui);
xpk_err cgc_xpk_pack_none(xpk_ctx_t *ctx);
xpk_err cgc_xpk_pack_nil(xpk_ctx_t *ctx);
xpk_err cgc_xpk_pack_bool(xpk_ctx_t *ctx, uint8_t b);
xpk_err cgc_xpk_pack_str(xpk_ctx_t *ctx, const char *str);
xpk_err cgc_xpk_pack_bytes(xpk_ctx_t *ctx, const char *bytes, cgc_size_t len);
xpk_err cgc_xpk_pack_array(xpk_ctx_t *ctx, cgc_size_t len);
xpk_err cgc_xpk_pack_map(xpk_ctx_t *ctx, cgc_size_t len);

/* Unpack */
xpk_err cgc_xpk_unpack_int(xpk_ctx_t *ctx, uint64_t *i, uint8_t *sign);
xpk_err cgc_xpk_unpack_nil(xpk_ctx_t *ctx);
xpk_err cgc_xpk_unpack_bool(xpk_ctx_t *ctx, uint8_t *b);
xpk_err cgc_xpk_unpack_str(xpk_ctx_t *ctx, cgc_size_t *len);
xpk_err cgc_xpk_unpack_bytes(xpk_ctx_t *ctx, cgc_size_t *len);
xpk_err cgc_xpk_unpack_array(xpk_ctx_t *ctx, cgc_size_t *len);
xpk_err cgc_xpk_unpack_map(xpk_ctx_t *ctx, cgc_size_t *len);

#endif
