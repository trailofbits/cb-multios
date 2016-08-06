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
#include "endian.h"
#include "time.h"

/* 2014-12-12 11:13:36 */
#define INITIAL_TIME ((2208988800ULL + 1418382816) * 1000)
#define MAX_DIST 240000

unsigned long long current_time = INITIAL_TIME;

int handle_msg_time(void *data, unsigned int n)
{
    uint32_t fractional, secs;
    unsigned long long new_time;

    if (n < 8)
        return 0;

    fractional = betoh32(*(uint32_t *)(data));
    secs = betoh32(*(uint32_t *)(data + 4));

    new_time = (secs * 1000ULL) + ((fractional * 1000ULL) >> 32);
    if (new_time < current_time || (new_time - current_time) > MAX_DIST)
        return 1;

    current_time = new_time;
    return 1;
}
