/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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
#pragma once

#include "stdlib.h"
#include <stdint.h>

typedef enum {
  OP_ADD = 0x45FD1D19,
  OP_SUB = 0x9B6A4495,
  OP_MUL = 0xA2F78B10,
  OP_DIV = 0xE8BBACD2,
  OP_MOD = 0x2BAE191D,
  OP_IMP = 0xA9A367A0,
  OP_EXP = 0xEC810F07,
  OP_CMP = 0x76FC2ED2
} op_type;

typedef struct {
  op_type type;
  int arg1;
  int arg2;
  int result;
} op_t;

void calc_add(op_t *op);
void calc_sub(op_t *op);
void calc_mul(op_t *op);
void calc_div(op_t *op);
void calc_mod(op_t *op);

void calc_compute(op_t *op);
