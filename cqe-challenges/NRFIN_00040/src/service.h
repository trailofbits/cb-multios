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

#ifndef SERVICE_H
#define SERVICE_H

#include <libcgc.h>
#include "libc.h"

#define FALSE 0
#define TRUE 1
#define SZ_PAGE 4096

#define BUF_RX_SZ 65535

#define NUM_OBJS 256
#define SZ_INSN_OP 3 // e.g. "NEW"
#define SZ_INSN_TYPE 6 // e.g. "NUMBER"
#define MAX_SZ_LINE 256

// Space consumed prior to STRING:
// ID: up to 3B
// (delim): 1B
// TYPE: 6B
// (delim): 1B
// total: 17B; we'll do 20 to be safe
#define MAX_SZ_STRING (MAX_SZ_LINE - 20)

#define OFF_NUMBER 4
#define OFF_STRING 8

// Ref: https://stackoverflow.com/questions/3437404
#define MIN(a,b) \
	({	__typeof__ (a) _a = (a); \
		__typeof__ (b) _b = (b); \
		_a < _b ? _a : _b; })

typedef enum __attribute__ ((__packed__)) {
	CMD_UNKNOWN = 0,
	CMD_DESERIALIZE, // 0x01
	CMD_SERIALIZE, // 0x02
	CMD_EXIT // 0x03
} command_t;

typedef enum {
	TYPE_UNKNOWN = 0,
	TYPE_NUMBER, // 1 
	TYPE_STRING, // 2
	TYPE_BOGUS = MAX_UINT32
} objtype_t;

typedef struct {
	uint8_t id;
	objtype_t type;
	uint32_t *number;
	char *string;
} object_t;

typedef struct {
	object_t *obj[NUM_OBJS];
} namespace_t;

#endif
