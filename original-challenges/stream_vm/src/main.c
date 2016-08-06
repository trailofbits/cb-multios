/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAGIC 'iVM\x00'
#define MEM_SIZE 0x10000
#define NUM_REGISTERS 16
#define R_ZERO 0

typedef struct {
    uint32_t registers[NUM_REGISTERS];
    uint8_t memory[MEM_SIZE];
} vmstate_t;

typedef int opcode_t;

static vmstate_t state;
#define R_VALUE(x) ((x) == R_ZERO ? 0 : state.registers[(x)])
#define M_VALUE(x) (state.memory[(x) % MEM_SIZE])

static int read_fully(void *_dst, size_t len)
{
    uint8_t *dst = (uint8_t *)_dst;
    while (len > 0)
    {
        size_t bytes;
        if (receive(STDIN, dst, len, &bytes) != 0)
            return 1;
        len -= bytes;
        dst += bytes;
    }
    return 0;
}

static int process_syscall()
{
    size_t bytes;
    switch (state.registers[1])
    {
    case 0:
    {
        // transmit
        unsigned short addr = state.registers[2],
            length = state.registers[3];
        if (addr + length > MEM_SIZE)
            return 1;
        transmit(STDOUT, &M_VALUE(addr), length, &bytes);
        return 0;
    }
    case 1:
    {
        // recv
        unsigned short addr = state.registers[2],
            length = state.registers[3];
        if (addr + length > MEM_SIZE)
            return 1;
        read_fully(&M_VALUE(addr), length);
        return 0;
    }
    default:
        return 1;
    }
}

static int process(opcode_t op)
{
    static void* opcode_table[] = {
        &&do_invalid, &&do_load, &&do_store, &&do_syscall,
        &&do_add, &&do_sub, &&do_mul, &&do_div, 
        &&do_or, &&do_and, &&do_xor,
        &&do_slt, &&do_slte
    };
    #define NUM_OPCODES 13

    int opc = op >> 24,
        rdst = (op >> 20) & 0xf,
        rsrc = (op >> 16) & 0xf,
        lval = (op >> 0) & 0xffff;

#ifdef PATCHED
    if ((unsigned)opc < NUM_OPCODES)
        goto *opcode_table[(unsigned)opc];
#else
    if (opc < NUM_OPCODES)
        goto *opcode_table[opc];
#endif

do_invalid:
    return 1;

do_load:
    state.registers[rdst] = M_VALUE(R_VALUE(rsrc) + lval);
    return 0;

do_store:
    M_VALUE(R_VALUE(rdst) + lval) = R_VALUE(rsrc);
    return 0;

// sign-extend lval
do_and:
    state.registers[rdst] &= R_VALUE(rsrc) | (short)lval;
    return 0;

do_or:
    state.registers[rdst] |= R_VALUE(rsrc) | (short)lval;
    return 0;

do_xor:
    state.registers[rdst] ^= R_VALUE(rsrc) | (short)lval;
    return 0;

do_add:
    state.registers[rdst] += R_VALUE(rsrc) + (short)lval;
    return 0;

do_sub:
    state.registers[rdst] -= R_VALUE(rsrc) + (short)lval;
    return 0;

do_mul:
    state.registers[rdst] *= R_VALUE(rsrc) + (short)lval;
    return 0;

do_div:
    if (R_VALUE(rsrc) + (short)lval == 0)
        return 1;

    state.registers[rdst] = state.registers[rdst] / (R_VALUE(rsrc) + (short)lval);
    return 0;

do_syscall:
    return process_syscall();

do_slt:
    state.registers[rdst] = R_VALUE(rsrc) < R_VALUE(lval & 0xf);
    return 0;

do_slte:
    state.registers[rdst] = R_VALUE(rsrc) <= R_VALUE(lval & 0xf);
    return 0;
}

int main()
{
    size_t bytes;
    memset(&state, 0, sizeof(state));

    uint32_t magic;
    if (read_fully(&magic, sizeof(magic)) != 0 || magic != MAGIC)
        goto bad_init;

    int flags;
    if (read_fully(&flags, sizeof(flags)) != 0)
        goto bad_init;

    if (flags >> 31)
    {
        if (read_fully(state.registers, sizeof(state.registers)) != 0)
            goto bad_init;
    }
    
    if (flags & (MEM_SIZE-1))
    {
        if (read_fully(state.memory, flags & (MEM_SIZE-1)) != 0)
            goto bad_init;
    }

    while (1)
    {
        opcode_t opcode;
        if (read_fully(&opcode, sizeof(opcode)) != 0)
            break;

        if (process(opcode) != 0)
            break;

        transmit(STDOUT, state.registers, sizeof(state.registers), &bytes);
    }

    transmit(STDOUT, "DONE", 4, &bytes);
    return 0;

bad_init:
    transmit(STDOUT, "BAD_INIT", 8, &bytes);
    return 0;
}
