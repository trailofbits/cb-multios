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
#include "cgc_stdio_private.h"

FILE _stdin = {
    .fd = STDIN,
    .rw = F_READ,
    .idx = 0,
    .length = 0,
    .xlat_map = 0
};
FILE _stdout = {
    .fd = STDOUT,
    .rw = F_WRITE,
    .idx = -1,
    .length = 0,
    .xlat_map = 0
};
FILE _stderr = {
    .fd = STDERR,
    .rw = F_WRITE,
    .idx = -1,
    .length = 0,
    .xlat_map = 0
};

FILE * const cgc_stdin = &_stdin;
FILE * const cgc_stdout = &_stdout;
FILE * const cgc_stderr = &_stderr;
