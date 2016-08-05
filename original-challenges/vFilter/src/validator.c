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
#include "insn.h"

typedef struct {
    filter_t *filter;
    unsigned int pc;
    unsigned int registers[16];
} state_t;

typedef struct {
    unsigned int ret;
    unsigned int args[8];
} call_t;

call_t syscalls[] = {
    { VALUE_NUMBER, { VALUE_PTR_FRAME, VALUE_NUMBER, 0 } }, // receive
    { VALUE_NUMBER, { VALUE_PTR_CTX | VALUE_PTR_FRAME, VALUE_NUMBER, 0 } }, // transmit
    { VALUE_UNKNOWN, { VALUE_PTR_FRAME, VALUE_NUMBER, 0 } }, // random
    { 0 }
};

int validate_state(state_t *state);

#include <stdio.h>
int validate_jmp(state_t *state)
{
    unsigned int i;
    state_t copy;
    insn_t *insn = &state->filter->insn[state->pc]; 
    if (insn->op.alu.code == JMP_EQ || insn->op.alu.code == JMP_NE || insn->op.alu.code == JMP_GT || insn->op.alu.code == JMP_GTE)
    {
        unsigned int src;
        if (insn->op.alu.source == SRC_REG)
            src = state->registers[insn->src];
        else
            src = VALUE_NUMBER;
        
        /* check if registers are valid for reading */
        if (src != VALUE_NUMBER || state->registers[insn->dst] != VALUE_NUMBER)
            return 0;
        /* fork state */
        copy = *state;
        copy.pc += insn->offset + 1;
        /* recursively check other execution path */
        return validate_state(&copy);
    }
    else if (insn->op.alu.code == JMP_CALL)
    {
        /* check parameters and return value */
        for (i = 0; syscalls[i].ret != 0; i++)
            if (i == insn->offset)
                break;
        if (syscalls[i].ret == 0)
            /* invalid call */
            return 0;
        for (i = 0; syscalls[insn->offset].args[i] != 0; i++)
            /* validate arguments are correct */
            if ((syscalls[insn->offset].args[i] & state->registers[i]) == 0)
                return 0;
        /* set return register */
        state->registers[0] = syscalls[insn->offset].ret;
        return 1;
    }
    else if (insn->op.alu.code == JMP_RET)
    {
        /* return register must be valid */
        if (state->registers[0] != VALUE_NUMBER)
            return 0;
        return 1;
    }
    return 0;
}

int validate_alu(state_t *state)
{
    unsigned int src;
    insn_t *insn = &state->filter->insn[state->pc]; 
    if (insn->op.alu.code >= ALU__COUNT)
        return 0;

    if (insn->dst == REG_FRAME)
        /* frame pointer is read-only */
        return 0;

    if (insn->op.alu.source == SRC_REG)
        src = state->registers[insn->src];
    else
        src = VALUE_NUMBER;
    
    if (insn->op.alu.code == ALU_NEG || insn->op.alu.code == ALU_END)
    {
        /* unary operators only valid on NUMBER */
        if (state->registers[insn->dst] != VALUE_NUMBER)
            state->registers[insn->dst] = VALUE_UNKNOWN;
    }
    else if (insn->op.alu.code == ALU_MOV)
    {
        /* binary operator that overwrites dst */
        state->registers[insn->dst] = src;
    }
    else
    {
        /* binary operators that read and modify dst */
        unsigned int result = state->registers[insn->dst] | src;
        if (result & VALUE_UNKNOWN)
            /* any operations on UNKNOWN results in UNKNOWN */
            state->registers[insn->dst] = VALUE_UNKNOWN;
        else if (result == VALUE_PTR_CTX || result == VALUE_PTR_FRAME || result == (VALUE_PTR_CTX | VALUE_PTR_FRAME))
            /* any operation using two pointers results in UNKNOWN */
            state->registers[insn->dst] = VALUE_UNKNOWN;
        else if (result & VALUE_PTR_CTX)
            /* operation between NUMBER and PTR_CTX results in PTR_CTX */
            state->registers[insn->dst] = VALUE_PTR_CTX;
        else if (result & VALUE_PTR_FRAME)
            /* operation between NUMBER and PTR_FRAME results in PTR_FRAME */
            state->registers[insn->dst] = VALUE_PTR_FRAME;
        else
            /* operation using NUMBER and NUMBER is a NUMBER */
            state->registers[insn->dst] = VALUE_NUMBER;

        if (insn->op.alu.code != ALU_SUB && insn->op.alu.code != ALU_ADD && (result & (VALUE_PTR_CTX | VALUE_PTR_FRAME)))
            /* only valid operations on pointers is ADD and SUB */
            state->registers[insn->dst] = VALUE_UNKNOWN;
    }
    return 1;
}

int validate_ld(state_t *state)
{
    insn_t *insn = &state->filter->insn[state->pc]; 
    if (insn->op.mem.mode >= MODE__COUNT || insn->op.mem.size >= S__COUNT)
        return 0;

    /* verify that src is a pointer */
    if ((state->registers[insn->src] & (VALUE_PTR_CTX | VALUE_PTR_FRAME)) == 0)
        return 0;

    if (insn->dst == REG_FRAME)
        return 0;

    state->registers[insn->dst] = VALUE_NUMBER;

    return 1;
}

int validate_st(state_t *state)
{
    insn_t *insn = &state->filter->insn[state->pc]; 
    if (insn->op.mem.mode >= MODE__COUNT || insn->op.mem.size >= S__COUNT)
        return 0;

    /* verify that dst is a writable pointer */
    if ((state->registers[insn->dst] & (VALUE_PTR_FRAME)) == 0)
        return 0;

    if (insn->op.alu.type == TYPE_STX)
    {
        /* verify that src is a number */
        if (state->registers[insn->src] != VALUE_NUMBER)
            return 0;
    }

    return 1;
}

int validate_state(state_t *state)
{
    for (; state->pc < state->filter->length; state->pc++)
    {
        insn_t *insn = &state->filter->insn[state->pc]; 
        if (insn->op.alu.type == TYPE_JMP)
        {
            if (!validate_jmp(state))
                return 0;
            if (insn->op.alu.code == JMP_RET)
                return 1;
        }
        else if (insn->op.alu.type == TYPE_ALU)
        {
            if (!validate_alu(state))
                return 0;
        }
        else if (insn->op.alu.type == TYPE_LDX)
        {
            if (!validate_ld(state))
                return 0;
        }
        else if (insn->op.alu.type == TYPE_ST || insn->op.alu.type == TYPE_STX)
        {
            if (!validate_st(state))
                return 0;
        }
        else
            return 0;
    }

    // didn't terminate with a RET
    return 0;
}

int filter_validate(filter_t *filter)
{
    unsigned int i;
    state_t state;
    state.filter = filter;
    state.pc = 0;
    for (i = 0; i < 16; i++)
        state.registers[i] = VALUE_UNKNOWN;
    state.registers[0] = VALUE_PTR_CTX;
    state.registers[REG_FRAME] = VALUE_PTR_FRAME;

    return validate_state(&state);
}
