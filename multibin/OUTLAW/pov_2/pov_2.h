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

// #define DEBUG 1

#include <libpov.h>
#include "pov_debug.h"

// common things
#define SUCCESS 0

#define TRUE 1
#define FALSE 0

#define STDIN 0
#define STDOUT 1

#define INT_MAX 0x7FFFFFFF
#define INT_MIN (-2147483647 - 1)
#define UINT_MAX (4294967295)
#define UINT_MIN (0)
#define MAX_UINT8 0xff
#define MAX_UINT32 0xffffffff

#define PIPE_RECV STDIN
#define PIPE_SEND STDOUT

#define CHK_SUCCESS(code, args...) if (SUCCESS != (ret = code)) { ERR(args); }

#define SZ_PAGE 0x1000 // 4096

#define REGNUM_EAX 0

#define DST_CLIENT 3
#define DST_SERVER 5  
#define DST_EXIT 0xdeadbeef

#define OP_ADD 0
#define OP_SUB 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_ACK 4
#define OP_MOD 61

/////////////////////

typedef struct msg {
    uint32_t dst; // 4B
    uint32_t x; // 8B
    uint32_t y; // 12B
    uint8_t op; // 13B
    uint8_t nmb; // 14B
    uint8_t pad[2]; // 16B
    uint64_t result; // 24B
} msg;


 /**
 * The main exploit logic.  
 * Call helper functions to leak auth_token.  
 * Use auth_token to exercise vuln #2.
 */
int main(void);

