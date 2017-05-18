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

enum
{
    OPR_invalid,
    OPR_reg,
    OPR_mem,
    OPR_imm
};

enum
{
    REG_invalid = -1,
    REG_sp = 4,
    REG__count = 8
};

enum
{
    INS_invalid,
    INS_nop,
    INS_add,
    INS_adc,
    INS_sub,
    INS_sbb,
    INS_and,
    INS_or,
    INS_xor,
    INS_mov,
    INS_lea,
    INS_cmp,
    INS_pop,
    INS_push,
    INS_ret,
    INS_jmp,
    INS_je,
    INS_jne,
    INS_call,
    INS_inc,
    INS_dec,
    INS_pusha,
    INS_popa,
    INS_pushf,
    INS_popf
};

class Operand
{
public:
    Operand() : d_type(OPR_invalid) {}
    Operand(int type) : d_type(type) {}
    
    static inline Operand new_imm(int imm)
    {
        Operand opr(OPR_imm);
        opr.d_imm = imm;
        return opr;
    }
    static inline Operand new_reg(int reg)
    {
        Operand opr(OPR_reg);
        opr.d_reg = reg;
        return opr;
    }
    static inline Operand new_mem(int base, int disp)
    {
        Operand opr(OPR_mem);
        opr.d_mem.d_base = base;
        opr.d_mem.d_disp = disp;
        opr.d_mem.d_index = REG_invalid;
        opr.d_mem.d_scale = 0;
        return opr;
    }
    
    inline bool is_valid() { return d_type != OPR_invalid; }
public:
    int d_type;
    union {
        int d_reg;
        int d_imm;
        struct {
            int d_base;
            int d_disp;
            int d_index;
            int d_scale;
        } d_mem;
    };
};

class Instruction
{
public:
    Instruction() : d_type(INS_invalid), d_size(0) {}
    Instruction(int type, int size) : d_type(type), d_size(size) {}

    static Instruction disassemble(unsigned char *data, unsigned int len);

    inline bool is_valid() { return d_type != INS_invalid; }
private:
public:
    int d_type;
    int d_size;
    Operand d_operands[3];
};
