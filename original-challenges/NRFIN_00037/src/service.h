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

#define SCRATCH_SZ 2048
#define BYTECODE_SZ 2048

#define FALSE 0
#define TRUE 1

typedef struct instruction {
	uint8_t len;
    uint8_t opcode;
    uint32_t op1;
    uint32_t op2;
} inst_t;

int bytecode_vrfy(uint8_t *bytecode, uint16_t len);
int bytecode_exec(uint8_t *bytes, uint16_t len, uint8_t *scratch, uint32_t *out);

// Bytecode is (single) register-based with memory accesses available.
// Only a single register is used, which can be thought of as ACC (accumulator).
// Solutions to arthmetic operands are stored in this register which can be 
// accessed with the appropriate opcodes.

// All arithmetic operations are modulo 0xFFFFFFFF (no special handling for 
// over/underflows, etc).

// Bytecode format:
// <opcode><operand1><(optional)operand2>
// 1B: opcode
// 4B / 2B: offset1 / immediate1
// 4B / 2B: (optional) offset2 / immediate2

#define INST_OFF_SZ 4
#define INST_IMM_SZ 2

// NOTE1: even if one operand is ACC, both operands still consume space.  
// The amount of space consumed is dictated by their immediate / offset status.  
// The value of the extra operand is ignored.

// NOTE2: This encoding scheme is not space-efficient.  It's designed to be 
// easy to grok.

////
// Masks
////

#define INST_MASK_DST 0x01
// XXXX XX0X: store into ACC
// XXXX XX1X: store into mem (offset in operand1)
// NOTE: If we're storing into memory, we've consumed an operand for the memory 
// offset. We arbitrarily choose op1 to hold this offset.  This implies:
// INST_MASK_ACC - because our arithmetic will involve ACC & op2.
// INST_MASK_OP1 - because op1 will be interpreted as an offset.
// If INST_MASK_DST is set and either INST_MASK_ACC or INST_MASK_OP1 is not, 
// the instruction is invalid.

#define INST_MASK_ACC 0x02
// XXXX XXX0: 2 operands
// XXXX XXX1: ACC & operand2

#define INST_MASK_OP1 0x04
// XXXX X0XX: operand1 is immediate
// XXXX X1XX: operand1 is offset (memory)
// NOTE: this flag along with op1 value is ignored if INST_MASK_ACC is set.

#define INST_MASK_OP2 0x08
// XXXX 0XXX: operand2 is immediate
// XXXX 1XXX: operand2 is offset (memory)

#define INST_MASK_OPCODE 0xF0
// YYYY XXXX: YYYY is opcode

////
// Opcodes
////
#define OPCODE_ADD 0x00 // 0000: ADD
#define OPCODE_SUB 0x10 // 0001: SUB
#define OPCODE_MUL 0x20 // 0010: MUL
#define OPCODE_DIV 0x30 // 0011: DIV
#define OPCODE_OUT 0xF0 // 1111: OUT (OUTPUT <- ACC)

#define OUT_DEFAULT 0xDEADBEEF // some probably-incorrect value

#endif
