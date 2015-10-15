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
/**
 * @file rpncalc.h
 *
 * RPN calculator operating on rpnvals.
 */

#ifndef RPNCALC_H_
#define RPNCALC_H_

#include "list.h"
#include "rpnval.h"

struct operand {
    rpnval val;
    struct list_node list;
};

struct rpncalc_state {
    struct list stack;
};

enum rpncalc_op_type {
    PUSH,
    POP,
    CLEAR,
    ADD,
    SUB,
    MUL,
    DIV,
    INV
};

void rpncalc_init(struct rpncalc_state *state);
void rpncalc_destroy(struct rpncalc_state *state);

int perform_rpncalc_op(struct rpncalc_state *state, enum rpncalc_op_type type);

#endif /* RPNCALC_H_ */

