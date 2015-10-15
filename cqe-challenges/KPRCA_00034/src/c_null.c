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
#include "codes.h"

int null_init(code_t *code, const unsigned char *k)
{
    code->priv = NULL;
    return SUCCESS;
}

void null_destroy(code_t *code)
{
    return;
}

int null_encode(code_t *code, unsigned char *b)
{
    return SUCCESS;
}

int null_decode(code_t *code, unsigned char *b)
{
    return SUCCESS;
}

const code_def_t null_code = {
    .name = "Null",
    .type = C_NULL,
    .bsize = 32,
    .ksize = 0,
    .init = null_init,
    .destroy = null_destroy,
    .encode = null_encode,
    .decode = null_decode
};
