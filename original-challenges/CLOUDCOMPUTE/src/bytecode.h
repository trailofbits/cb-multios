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

#ifndef BYTECODE_H
#define BYTECODE_H

#include <libcgc.h>
#include "libc.h"

#define OPERATION_SZ 8

#define OPCODE_NUL 0x004C554E // 'NUL\x00'
#define OPCODE_SET 0x00544553 // 'SET\x00'
#define OPCODE_ADD 0x00444441 // 'ADD\x00'
#define OPCODE_SUB 0x00425553 // 'SUB\x00'
#define OPCODE_MUL 0x004C554D // 'MUL\x00'
#define OPCODE_DIV 0x00564944 // 'DIV\x00'
#define OPCODE_SHR 0x00524853 // 'SHR\x00'
#define OPCODE_SHL 0x004C4853 // 'SHL\x00'

/**
 * The bytecode virtual machine.  Responsible for interpreting session instance 
 * bytecode and modifying memory in the session's scratch buffer.
 *
 * @param buf Pointer the session's opcode buffer.
 * @param sz The length of the session's opcode buffer.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int bytecode_exec(uint8_t *buf, uint16_t sz);

#endif