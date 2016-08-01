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
/**
 * @file utf8.h
 *
 * Encode and decode UTF-8 encoded strings.
 */

#ifndef UTF8_H_
#define UTF8_H_

#include <libcgc.h>

enum utf8_decode_state {
    ACCEPT,
    REJECT,
    TWO_BYTE,
    THREE_BYTE,
    FOUR_BYTE
};

typedef unsigned char utf8char;
typedef unsigned int ucscodepoint;

enum utf8_decode_state utf8_decode(enum utf8_decode_state state, utf8char c, ucscodepoint *out);
ssize_t utf8_encode(ucscodepoint in, utf8char *out, size_t size);

size_t utf8_canonicalize(utf8char *dst, const utf8char *src, size_t n);

#endif /* UTF8_H_ */

