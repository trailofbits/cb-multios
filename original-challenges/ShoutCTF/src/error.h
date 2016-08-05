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

#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERR_OK,
    ERR_INTERNAL,
    ERR_NICK_LONG,
    ERR_PASS_LONG,
    ERR_NAME_LONG,
    ERR_NO_SUCH_USER,
    ERR_NO_SUCH_CHAL,
    ERR_NO_SUCH_TEAM,
    ERR_CHAL_ALREADY_OPEN,
    ERR_DUPLICATE_FLAG,
    ERR_INVALID_FLAG,
    ERR_USER_EXISTS,
    ERR_TEAM_EXISTS,
    ERR_CHAL_EXISTS,
    ERR_WRONG_PASS,
    ERR_INVALID_VALUE,
} error_t;

const char* error_to_string(error_t err);

#endif
