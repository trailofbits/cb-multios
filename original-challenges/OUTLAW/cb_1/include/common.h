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

// This file holds common defines used in CB-specific /src code.

#include "libc.h"

#define DST_EXIT 0xdeadbeef

#define NAME_CRS "CRS"
#define NAME_CB1 "CLIENT"
#define NAME_CB2 "SERVER"
const char *dst2str[] = { 
	"CRS",		// 0
	"INVALID",	// 1
	"INVALID",	// 2
	"CB1",		// 3
	"INVALID",	// 4
	"CB2",		// 5
	"INVALID"	// 6
};

#define SZ_ENCKEY 4 // 32 * 4 = 128bits
#define OFF_ENCKEY_IDX 42 // "arbitrary"
#define OFF_AUTH_TOKEN_IDX 24 // "arbitrary"

typedef struct __attribute__((packed)) msg {
	uint32_t dst; // 4B
	uint32_t x; // 8B
	uint32_t y; // 12B
	uint8_t op; // 13B
	uint8_t nmb; // 14B
	uint8_t pad[2]; // 16B
	uint64_t result; // 24B
} msg;

#define OP_ADD 0
#define OP_SUB 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_ACK 4
#define OP_MOD 61

