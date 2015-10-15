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

#include <libcgc.h>

#include "utf8.h"

enum utf8_decode_state
utf8_decode(enum utf8_decode_state state, utf8char c, ucscodepoint *out)
{
    switch (state) {
    case ACCEPT:
    case REJECT:
        if ((c & 0x80) == 0) {
            *out = c;
            return ACCEPT;
        } else if ((c & 0xe0) == 0xc0) {
            *out = (c & 0x1f) << 6;
            return TWO_BYTE;
        } else if ((c & 0xf0) == 0xe0) {
            *out = (c & 0x0f) << 12;
            return THREE_BYTE;
        } else if ((c & 0xf4) == 0xf0) {
            *out = (c & 0x07) << 18;
            return FOUR_BYTE;
        }
        break;
    case FOUR_BYTE:
#ifdef PATCHED
        if ((c & 0xc0) == 0x80 && *out) {
#else
        if ((c & 0xc0) == 0x80) {
#endif
            *out |= (c & 0x3f) << 12;
            // Catch 4-byte seqences decoding to over 0x10ffff
            if (*out > 0x10ffff)
                break;

            return THREE_BYTE;
        }
        break;
    case THREE_BYTE:
#ifdef PATCHED
        if ((c & 0xc0) == 0x80 && *out) {
#else
        if ((c & 0xc0) == 0x80) {
#endif
            *out |= (c & 0x3f) << 6;
            return TWO_BYTE;
        }
        break;
    case TWO_BYTE:
#ifdef PATCHED
        if ((c & 0xc0) == 0x80 && *out) {
#else
        if ((c & 0xc0) == 0x80) {
#endif
            *out |= (c & 0x3f);
            return ACCEPT;
        }
        break;
    }

    *out = 0xfffd;
    return REJECT;
}

ssize_t
utf8_encode(ucscodepoint in, utf8char *out, size_t size)
{
    if (in < 0x80) {
        if (size < 1)
            return 0;

        *out++ = in;
        return 1;
    } else if (in > 0x80 && in < 0x7ff) {
        if (size < 2)
            return 0;

        *out++ = 0xc0 | (in & (0x1f << 6) >> 6);
        *out++ = 0x80 | (in & 0x3f);
        return 2;
    } else if (in > 0x800 && in < 0xffff) {
        if (size < 3)
            return 0;

        if (in >= 0xd800 && in <= 0xdfff)
            return -1;

        *out++ = 0xe0 | (in & (0xf << 12) >> 12);
        *out++ = 0x80 | (in & (0x3f << 6) >> 6);
        *out++ = 0x80 | (in & 0x3f);
        return 3;
    } else if (in > 0x10000 && in < 0x10ffff && size > 3) {
        if (size < 4)
            return 0;

        *out++ = 0xf0 | (in & (0x7 << 18) >> 18);
        *out++ = 0x80 | (in & (0x3f << 12) >> 12);
        *out++ = 0x80 | (in & (0x3f << 6) >> 6);
        *out++ = 0x80 | (in & 0x3f);
        return 4;
    }

    return -1;
}

size_t
utf8_canonicalize(utf8char *dst, const utf8char *src, size_t n)
{
    size_t i, ret = 0;
    ucscodepoint cp;
    ssize_t encoded;
    enum utf8_decode_state state = ACCEPT;

    // Guarantee we have space for null terminator
    n--;

    for (i = 0; n && src[i]; i++) {
        state = utf8_decode(state, src[i], &cp);
        if (state == ACCEPT || state == REJECT) {
            encoded = utf8_encode(cp, dst, n);
            if (encoded < 0)
                return ret;

            ret += encoded;
            dst += encoded;
            n -= encoded;
        }
    }

    *dst = '\0';
    return ret;
}

