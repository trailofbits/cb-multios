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

#include "instruction.h"


class Emulator
{
private:
    inline bool in_stack(int mem)
    {
#ifdef PATCHED_1
        if ((unsigned char *)mem < d_stack)
            return false;
#endif
        return (unsigned char *)mem - d_stack < STACK_SIZE;
    }
    inline bool in_heap(int mem)
    {
        return (mem >> 30) == 0;
    }
    inline unsigned char *heap_addr(int mem)
    {
        return mem + d_heap;
    }
    inline unsigned int heap_length(int mem)
    {
        if (!in_heap(mem))
            return 0;
        return 0x40000000 - mem;
    }
    inline void set_operand(const Operand &opr, int value, bool carry, bool do_flags)
    {
        if (do_flags)
            set_flags(value, carry);
        set_operand(opr, value);
    }
    inline void set_flags(int value, bool carry)
    {
        d_zf = value == 0;
        d_cf = carry;
    }

public:
    Emulator(void *sp, void *heap);
    ~Emulator();

    void reset();
    void set_ip(int ip);
    bool step();
    void print_state();
    int get_operand_mem(const Operand &opr);
    int get_operand(const Operand &opr);
    void set_operand(const Operand &opr, int value);
    const Instruction &last_instruction()
    {
        return d_instruction;
    }
    template <typename F>
    void traverse_dirty(F f)
    {
        for (unsigned int i = 0; i < sizeof(d_dirty_pages); i++)
        {
            if (d_dirty_pages[i] == 0) continue;
            for (unsigned int j = 0; j < 8; j++)
            {
                if (d_dirty_pages[i] & (1 << j))
                    f((i * 8 + j) * 0x1000);
            }
        }
    }

    static const int HEAP_SIZE = 0x40000000;
    static const int STACK_SIZE = 65536;
private:
    bool d_fault;
    unsigned char *d_stack;
    unsigned char *d_heap;
    unsigned char d_dirty_pages[HEAP_SIZE / 0x8000];

    int d_reg[REG__count];
    int d_ip;
    unsigned int d_zf : 1;
    unsigned int d_cf : 1;
    Instruction d_instruction;
};
