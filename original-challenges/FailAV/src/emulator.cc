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
#include <cstdint.h>
#include <cstdio.h>
#include <cstring.h>
#include "emulator.h"

Emulator::Emulator(void *sp, void *heap)
    : d_stack((unsigned char *)sp), d_heap((unsigned char *)heap)
{
    memset(d_reg, 0, sizeof(d_reg));
    memset(d_dirty_pages, 0, sizeof(d_dirty_pages));
    d_reg[REG_sp] = (int)sp + STACK_SIZE;
    d_zf = 0;
    d_cf = 0;
}

Emulator::~Emulator()
{
}

void Emulator::reset()
{
    // Clear heap and stack memory
    traverse_dirty([this] (int mem) {
        memset(d_heap + mem, 0, 0x1000);
    });
    memset(d_stack, 0, STACK_SIZE);

    // Reset registers
    memset(d_reg, 0, sizeof(d_reg));
    memset(d_dirty_pages, 0, sizeof(d_dirty_pages));
    d_reg[REG_sp] = (int)d_stack + STACK_SIZE;
    d_zf = 0;
    d_cf = 0;
}

void Emulator::set_ip(int ip)
{
    d_ip = ip;
}

bool Emulator::step()
{
    if (!in_heap(d_ip))
        return false;

    Instruction ins = Instruction::disassemble(heap_addr(d_ip), heap_length(d_ip));
    if (!ins.is_valid())
        return false;

    d_instruction = ins;
    d_ip += ins.d_size;
    d_fault = false;

    int x1, x2;
    long long tmpll;
    switch (ins.d_type)
    {
    case INS_cmp:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        tmpll = (long long)x1 - x2;
        set_flags(tmpll, tmpll < INT32_MIN || tmpll > INT32_MAX);
        break;
    case INS_add:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        tmpll = (long long)x1 + x2;
        set_operand(ins.d_operands[0], tmpll, tmpll < INT32_MIN || tmpll > INT32_MAX, true);
        break;
    case INS_sub:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        tmpll = (long long)x1 - x2;
        set_operand(ins.d_operands[0], tmpll, tmpll < INT32_MIN || tmpll > INT32_MAX, true);
        break;
    case INS_or:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        set_operand(ins.d_operands[0], x1 | x2, false, true);
        break;
    case INS_and:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        set_operand(ins.d_operands[0], x1 & x2, false, true);
        break;
    case INS_xor:
        x1 = get_operand(ins.d_operands[0]);
        x2 = get_operand(ins.d_operands[1]);
        set_operand(ins.d_operands[0], x1 ^ x2, false, true);
        break;
    case INS_inc:
        x1 = get_operand(ins.d_operands[0]);
        set_operand(ins.d_operands[0], x1 + 1);
        break;
    case INS_dec:
        x1 = get_operand(ins.d_operands[0]);
        set_operand(ins.d_operands[0], x1 - 1);
        break;
    case INS_mov:
        set_operand(ins.d_operands[0], get_operand(ins.d_operands[1]));
        break;
    case INS_lea:
        if (ins.d_operands[1].d_type != OPR_mem)
            d_fault = true;
        else
            set_operand(ins.d_operands[0], get_operand_mem(ins.d_operands[1]));
        break;
    case INS_push:
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) - 4);
        set_operand(Operand::new_mem(REG_sp, 0), get_operand(ins.d_operands[0]));
        break;
    case INS_pop:
        set_operand(ins.d_operands[0], get_operand(Operand::new_mem(REG_sp, 0)));
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) + 4);
        break;
    case INS_ret:
        x1 = get_operand(Operand::new_mem(REG_sp, 0));
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) + 4);
        if (!in_heap(x1))
            d_fault = true;
        else
            d_ip = x1;
        break;
    case INS_call:
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) - 4);
        set_operand(Operand::new_mem(REG_sp, 0), d_ip);
        // fall through
    case INS_jmp:
do_jmp:
        x1 = get_operand(ins.d_operands[0]);
        if (ins.d_operands[0].d_type == OPR_imm)
            x1 += d_ip;
        if (!in_heap(x1))
            d_fault = true;
        else
            d_ip = x1;
        break;
    case INS_je:
        if (d_zf == 1) goto do_jmp;
        break;
    case INS_jne:
        if (d_zf == 0) goto do_jmp;
        break;
    case INS_pusha:
        set_operand(Operand::new_mem(REG_sp, -4), d_reg[0]);
        set_operand(Operand::new_mem(REG_sp, -8), d_reg[1]);
        set_operand(Operand::new_mem(REG_sp, -12), d_reg[2]);
        set_operand(Operand::new_mem(REG_sp, -16), d_reg[3]);
        set_operand(Operand::new_mem(REG_sp, -20), d_reg[4]);
        set_operand(Operand::new_mem(REG_sp, -24), d_reg[5]);
        set_operand(Operand::new_mem(REG_sp, -28), d_reg[6]);
        set_operand(Operand::new_mem(REG_sp, -32), d_reg[7]);
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) - 32);
        break;
    case INS_popa:
        set_operand(Operand::new_reg(REG_sp), get_operand(Operand::new_reg(REG_sp)) + 32);
        d_reg[0] = get_operand(Operand::new_mem(REG_sp, -4));
        d_reg[1] = get_operand(Operand::new_mem(REG_sp, -8));
        d_reg[2] = get_operand(Operand::new_mem(REG_sp, -12));
        d_reg[3] = get_operand(Operand::new_mem(REG_sp, -16));
        // skip REG_sp (r4)
        d_reg[5] = get_operand(Operand::new_mem(REG_sp, -24));
        d_reg[6] = get_operand(Operand::new_mem(REG_sp, -28));
        d_reg[7] = get_operand(Operand::new_mem(REG_sp, -32));
        break;
    }

    return !d_fault;
}

int Emulator::get_operand_mem(const Operand &opr)
{
    int mem = 0;
    if (opr.d_mem.d_base != REG_invalid)
        mem = d_reg[opr.d_mem.d_base];
    if (opr.d_mem.d_index != REG_invalid)
        mem += d_reg[opr.d_mem.d_index] << opr.d_mem.d_scale;
    return mem + opr.d_mem.d_disp;
}

int Emulator::get_operand(const Operand &opr)
{
    switch (opr.d_type)
    {
    case OPR_reg:
        return d_reg[opr.d_reg];
    case OPR_imm:
        return opr.d_imm;
    case OPR_mem:
        {
            int mem = get_operand_mem(opr);
            if ((unsigned int)mem < 0x1000) // protect zero page
                d_fault = true;
            else if (in_heap(mem) && in_heap(mem + 3))
                return *(int *)(d_heap + mem);
            else if (in_stack(mem) && in_stack(mem + 3))
                return *(int *)mem;
        }
        d_fault = true;
        return 0;
    }
    return 0;
}

void Emulator::set_operand(const Operand &opr, int value)
{
    switch (opr.d_type)
    {
    case OPR_reg:
        d_reg[opr.d_reg] = value;
        break;
    case OPR_mem:
        {
            int mem = get_operand_mem(opr);
            if ((unsigned int)mem < 0x1000) // protect zero page
                d_fault = true;
            else if (in_heap(mem) && in_heap(mem + 3))
            {
                *(int *)(d_heap + mem) = value;
                d_dirty_pages[mem / 0x8000] |= 1 << ((mem / 0x1000) % 8);
            }
            else if (in_stack(mem) && in_stack(mem + 3))
                *(int *)mem = value;
            else
                d_fault = true;
        }
    }
}

#if 1
void Emulator::print_state()
{
    fprintf(stderr, "IP: %08X\tStack: %08X\tHeap: %08X\n", d_ip, d_stack, d_heap);
    for (unsigned int i = 0; i < REG__count; i++)
    {
        fprintf(stderr, "R%d: %08X\n", i, d_reg[i]);
    }
    fprintf(stderr, "\n");
}
#endif
