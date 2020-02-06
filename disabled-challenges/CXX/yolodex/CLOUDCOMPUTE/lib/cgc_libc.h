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
#ifndef LIBC_H
#define LIBC_H 1

// #define DEBUG 1

#include "cgc_stdint.h"
#include "cgc_memset.h"
#include "cgc_memcpy.h"
#include "cgc_recv_until_delim_n.h"
#include "cgc_send_bytes.h"
#include "cgc_recv_bytes.h"
#include "cgc_char.h"
#include "cgc_streq.h"
#include "cgc_strlen.h"
#include "cgc_list.h"
#include "cgc_malloc.h"

#ifdef DEBUG
#include "cgc_debug.h"
#endif

#define SUCCESS 0

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int 
#define uint64_t unsigned long long 

#define MAX_UINT8 0xff
#define MAX_UINT32 0xffffffff
 
#define BASE_ADDR_SZ 3

#define FLAG_PAGE 0x4347C000

#endif
