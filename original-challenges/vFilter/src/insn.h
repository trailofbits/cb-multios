/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

#include <stdint.h>
#include <stdlib.h>

enum {
    TYPE_LDX,
    TYPE_ST,
    TYPE_STX,
    TYPE_ALU,
    TYPE_JMP
};

enum {
    ALU_ADD,
    ALU_SUB,
    ALU_MUL,
    ALU_DIV,
    ALU_MOD,
    ALU_OR,
    ALU_AND,
    ALU_XOR,
    ALU_LSH,
    ALU_RSH,
    ALU_NEG,
    ALU_MOV,
    ALU_END,
    ALU__COUNT
};

enum {
    JMP_EQ,
    JMP_NE,
    JMP_GT,
    JMP_GTE,
    JMP_CALL,
    JMP_RET
};

enum {
    SRC_REG,
    SRC_IMM
};

enum {
    S_B,
    S_H,
    S_W,
    S__COUNT
};

enum {
    MODE_MEM,
    MODE_STACK,
    MODE__COUNT
};

enum {
    VALUE_UNKNOWN = 0x01,
    VALUE_NUMBER = 0x02,
    VALUE_PTR_CTX = 0x04,
    VALUE_PTR_FRAME = 0x08
};

enum {
    REG_FRAME = 15
};

typedef union {
    struct {
        unsigned char type : 3;
        unsigned char source : 1;
        unsigned char code : 4;
    } alu;
    struct {
        unsigned char type : 3;
        unsigned char size : 2;
        unsigned char mode : 3;
    } mem;
} op_t;

typedef struct {
    op_t op;
    unsigned char dst : 4;
    unsigned char src : 4;
    unsigned short offset;
    unsigned int extra;
} insn_t;

typedef struct {
    unsigned int length;
    insn_t insn[0];
} filter_t;

static inline filter_t *filter_alloc(unsigned int length)
{
    filter_t *result;

    if (length > (INT_MAX / sizeof(insn_t) - 1))
        return NULL;

    result = malloc(sizeof(filter_t) + length * sizeof(insn_t));
    if (result != NULL)
    {
        result->length = length;
    }
    return result;
}

static inline void filter_free(filter_t *filter)
{
    free(filter);
}

int filter_validate(filter_t *filter);
unsigned int filter_execute(filter_t *filter, unsigned char *ctx, unsigned int ctx_len);
