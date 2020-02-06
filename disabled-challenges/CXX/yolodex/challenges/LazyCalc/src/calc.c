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
#include "cgc_string.h"
#include "cgc_calc.h"

void cgc_calc_add(op_t *op)
{
  if (op->type != OP_ADD)
    return;
  op->result = op->arg1 + op->arg2;
}

void cgc_calc_sub(op_t *op)
{
  if (op->type != OP_SUB)
    return;
  op->result = op->arg1 - op->arg2;
}

void cgc_calc_mul(op_t *op)
{
  if (op->type != OP_MUL)
    return;
  op->result = op->arg1 * op->arg2;
}

void cgc_calc_div(op_t *op)
{
  if (op->type != OP_DIV || op->arg2 == 0)
    return;
  op->result = op->arg1 / op->arg2;
}

void cgc_calc_mod(op_t *op)
{
  if (op->type != OP_MOD || op->arg2 == 0)
    return;
  op->result = op->arg1 % op->arg2;
}


void cgc_calc_compute(op_t *op)
{
  if (op->type != OP_CMP)
    return;
  op_t *cop = (op_t *) op->arg1;
  switch (cop->type)
  {
    case OP_ADD:
      cgc_calc_add(cop);
      break;
    case OP_SUB:
      cgc_calc_sub(cop);
      break;
    case OP_MUL:
      cgc_calc_mul(cop);
      break;
    case OP_DIV:
      cgc_calc_div(cop);
      break;
    case OP_MOD:
      cgc_calc_mod(cop);
      break;
    default:
      break;
  }
}

