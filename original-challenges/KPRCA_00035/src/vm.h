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

#ifndef _H_VM_
#define _H_VM_

#define N_REGISTERS 16
#define MEMORY_SIZE (1024 * 64)
#define REG_FLAG (1 << 31)
#define MEM_FLAG 0x0000FFFF

typedef uint8_t reg;

typedef struct state state;
struct state {
  uint32_t registers[N_REGISTERS];
  reg memory[MEMORY_SIZE];
};

typedef struct inst inst;
struct inst {
  uint16_t val;
  uint8_t dstsrc;
  uint8_t op;
} __attribute__((packed));

#define UNK 0
#define LOAD 1
#define STR 2
#define SYS 3
#define ADD 4
#define SUB 5
#define MUL 6
#define DIV 7
#define OR 8
#define AND 9
#define XOR 10
#define SLT 11
#define SLTE 12

#define SRC(i) ((i)->dstsrc & 0x0F)
#define DST(i) (((i)->dstsrc >> 4) & 0x0F)

#endif /* !_H_VM_ */
