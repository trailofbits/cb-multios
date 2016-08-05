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
#include <cstdlib.h>
#include <algorithm.h>
#include "instruction.h"

static bool parse_modrm(Instruction &ins, unsigned char *data, unsigned int len)
{
    unsigned int r1, r2, mod, sib;
    unsigned char *d = &data[ins.d_size];
    if (ins.d_size + 1 > len)
        return false;
    r1 = d[0] & 7;
    r2 = (d[0] >> 3) & 7;
    mod = d[0] >> 6;
    ins.d_size += 1;
    ins.d_operands[1] = Operand::new_reg(r2);
    if (mod != 3 && r1 == 4)
    {
        sib = data[ins.d_size];
        if (ins.d_size + 1 > len)
            return false;
        ins.d_size += 1;
    }
    switch (mod)
    {
    case 0:
        if (r1 == 5)
        {
            if (ins.d_size + 4 > len)
                return false;
            ins.d_operands[0] = Operand::new_mem(REG_invalid, *(int *)&data[ins.d_size]);
            ins.d_size += 4;
        }
        else
        {
            ins.d_operands[0] = Operand::new_mem(r1, 0);
        }
        break;
    case 1:
        if (ins.d_size + 1 > len)
            return false;
        ins.d_operands[0] = Operand::new_mem(r1, (char)data[ins.d_size]);
        ins.d_size += 1;
        break;
    case 2:
        if (ins.d_size + 4 > len)
            return false;
        ins.d_operands[0] = Operand::new_mem(r1, *(int *)&data[ins.d_size]);
        ins.d_size += 4;
        break;
    case 3:
        ins.d_operands[0] = Operand::new_reg(r1);
        break;
    }
    if (mod != 3 && r1 == 4)
    {
        int index = (sib >> 3) & 7;
        if (index == 4)
            index = REG_invalid;
        ins.d_operands[0].d_mem.d_base = sib & 7;
        ins.d_operands[0].d_mem.d_index = index;
        ins.d_operands[0].d_mem.d_scale = sib >> 6;
    }
    return true;
}

static const struct {
    unsigned char value, mask;
    Instruction (*parse) (unsigned char *data, unsigned int len);
} parsers[] = {
    { 0x00, 0xFC, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_add, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        if (data[0] & 0x02)
            std::swap(ins.d_operands[0], ins.d_operands[1]);
        return ins;
    }},
    { 0x05, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 5)
            return Instruction();
        Instruction ins = Instruction(INS_add, 5);
        ins.d_operands[0] = Operand::new_reg(0);
        ins.d_operands[1] = Operand::new_imm(*(int *)&data[1]);
        return ins;
    }},
    { 0x28, 0xFC, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_sub, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        if (data[0] & 0x02)
            std::swap(ins.d_operands[0], ins.d_operands[1]);
        return ins;
    }},
    { 0x2D, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 5)
            return Instruction();
        Instruction ins = Instruction(INS_sub, 5);
        ins.d_operands[0] = Operand::new_reg(0);
        ins.d_operands[1] = Operand::new_imm(*(int *)&data[1]);
        return ins;
    }},
    { 0x38, 0xFC, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_cmp, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        if (data[0] & 0x02)
            std::swap(ins.d_operands[0], ins.d_operands[1]);
        return ins;
    }},
    { 0x3D, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 5)
            return Instruction();
        Instruction ins = Instruction(INS_cmp, 5);
        ins.d_operands[0] = Operand::new_reg(0);
        ins.d_operands[1] = Operand::new_imm(*(int *)&data[1]);
        return ins;
    }},
    { 0x40, 0xF8, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_inc, 1);
        ins.d_operands[0] = Operand::new_reg(data[0] & 7);
        return ins;
    }},
    { 0x48, 0xF8, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_dec, 1);
        ins.d_operands[0] = Operand::new_reg(data[0] & 7);
        return ins;
    }},
    { 0x50, 0xF8, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_push, 1);
        ins.d_operands[0] = Operand::new_reg(data[0] & 7);
        return ins;
    }},
    { 0x58, 0xF8, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_pop, 1);
        ins.d_operands[0] = Operand::new_reg(data[0] & 7);
        return ins;
    }},
    { 0x60, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_pusha, 1); } },
    { 0x61, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_popa, 1); } },
    { 0x74, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 2)
            return Instruction();
        Instruction ins = Instruction(INS_je, 2);
        ins.d_operands[0] = Operand::new_imm((char)data[1]);
        return ins;
    }},
    { 0x75, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 2)
            return Instruction();
        Instruction ins = Instruction(INS_jne, 2);
        ins.d_operands[0] = Operand::new_imm((char)data[1]);
        return ins;
    }},
    { 0x81, 0xFF, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_invalid, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        // sub-opcode in r2
        switch (ins.d_operands[1].d_reg)
        {
        case 0: ins.d_type = INS_add; break;
        case 1: ins.d_type = INS_or; break;
        case 2: ins.d_type = INS_adc; break;
        case 3: ins.d_type = INS_sbb; break;
        case 4: ins.d_type = INS_and; break;
        case 5: ins.d_type = INS_sub; break;
        case 6: ins.d_type = INS_xor; break;
        case 7: ins.d_type = INS_cmp; break;
        }
        // operand is really imm32
        if (ins.d_size + 4 > len)
            return Instruction();
        ins.d_operands[1] = Operand::new_imm(*(int*)&data[ins.d_size]);
        ins.d_size += 4;
        return ins;
    }},
    { 0x83, 0xFF, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_invalid, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        // sub-opcode in r2
        switch (ins.d_operands[1].d_reg)
        {
        case 0: ins.d_type = INS_add; break;
        case 1: ins.d_type = INS_or; break;
        case 2: ins.d_type = INS_adc; break;
        case 3: ins.d_type = INS_sbb; break;
        case 4: ins.d_type = INS_and; break;
        case 5: ins.d_type = INS_sub; break;
        case 6: ins.d_type = INS_xor; break;
        case 7: ins.d_type = INS_cmp; break;
        }
        // operand is really imm8
        if (ins.d_size + 1 > len)
            return Instruction();
        ins.d_operands[1] = Operand::new_imm((char)data[ins.d_size]);
        ins.d_size += 1;
        return ins;
    }},
    { 0x88, 0xFC, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_mov, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        if (data[0] & 0x02)
            std::swap(ins.d_operands[0], ins.d_operands[1]);
        return ins;
    }},
    { 0x90, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_nop, 1); } },
    { 0x9C, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_pushf, 1); } },
    { 0x9D, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_popf, 1); } },
    { 0xC3, 0xFF, [] (unsigned char *, unsigned int) { return Instruction(INS_ret, 1); } },
    { 0xC7, 0xFF, [] (unsigned char *data, unsigned int len) {
        Instruction ins(INS_mov, 1);
        if (!parse_modrm(ins, data, len))
            return Instruction();
        // sub-opcode in r2
        if (ins.d_operands[1].d_reg != 0)
            return Instruction();
        // operand is really imm32
        if (ins.d_size + 4 > len)
            return Instruction();
        ins.d_operands[1] = Operand::new_imm(*(int*)&data[ins.d_size]);
        ins.d_size += 4;
        return ins;
    }},
    { 0xE8, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 5)
            return Instruction();
        Instruction ins = Instruction(INS_call, 5);
        ins.d_operands[0] = Operand::new_imm(*(int *)&data[1]);
        return ins;
    }},
    { 0xE9, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 5)
            return Instruction();
        Instruction ins = Instruction(INS_jmp, 5);
        ins.d_operands[0] = Operand::new_imm(*(int *)&data[1]);
        return ins;
    }},
    { 0xEB, 0xFF, [] (unsigned char *data, unsigned int len) {
        if (len < 2)
            return Instruction();
        Instruction ins = Instruction(INS_jmp, 2);
        ins.d_operands[0] = Operand::new_imm((char)data[1]);
        return ins;
    }},
};

Instruction Instruction::disassemble(unsigned char *data, unsigned int len)
{
    Instruction ins;

    for (unsigned int i = 0; i < sizeof(parsers) / sizeof(parsers[0]); i++)
    {
        if ((data[0] & parsers[i].mask) == parsers[i].value)
        {
            ins = parsers[i].parse(data, len);
            break;
        }
    }

    return ins;
}
