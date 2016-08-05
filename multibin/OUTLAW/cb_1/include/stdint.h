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
#pragma once

#define	FALSE 0
#define	TRUE 1

#define SZ_PAGE 0x1000 // 4096

typedef unsigned char uint8_t;
typedef uint8_t byte_t;

typedef unsigned short uint16_t;

typedef unsigned int uint32_t;
// typedef long unsigned int size_t;

typedef unsigned long long uint64_t; 

#define MAX_UINT8 0xff
#define MAX_UINT32 0xffffffff

/** The max value of an int */
#define INT_MAX (2147483647)
/** The min value of an int */
#define INT_MIN (-2147483647 - 1)
/** The max value of an unsigned int */
#define UINT_MAX (4294967295)
/** The min value of an unsigned int */
#define UINT_MIN (0)
