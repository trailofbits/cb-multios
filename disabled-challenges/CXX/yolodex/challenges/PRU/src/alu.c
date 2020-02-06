/*

Author: Dustin Fraze (df@cromulence.co)

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "libcgc.h"

#include "cgc_alu.h"
#include "cgc_cpu.h"
#include "cgc_stdio.h"

int cgc_getALUOp2(pruCPU *cpu, aluInstruction inst) {
	if(inst.io == 0)
		return cpu->r[inst.arg2.rs2.reg];
	else
		return inst.arg2.imm;
}
	
void cgc_doAdd(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] + cgc_getALUOp2(cpu, inst);
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doAdc(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] + cgc_getALUOp2(cpu, inst) + cpu->carry;
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doSub(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] - cgc_getALUOp2(cpu, inst);
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doSuc(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] - cgc_getALUOp2(cpu, inst) - cpu->carry;
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doRsb(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cgc_getALUOp2(cpu, inst) - cpu->r[inst.rs1];
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doRsc(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cgc_getALUOp2(cpu, inst) - cpu->r[inst.rs1] - cpu->carry;
	cpu->carry = (cpu->r[inst.rd] >> 31) & 1;
}

void cgc_doLsl(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] << (cgc_getALUOp2(cpu, inst) & 0x1f);
}

void cgc_doLsr(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] >> (signed int)(cgc_getALUOp2(cpu, inst) & 0x1f);
}

void cgc_doAnd(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] & cgc_getALUOp2(cpu, inst);
}

void cgc_doOr(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] | cgc_getALUOp2(cpu, inst);
}

void cgc_doXor(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] ^ cgc_getALUOp2(cpu, inst);
}

void cgc_doNot(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = ~cpu->r[inst.rs1];
}

void cgc_doMin(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] < cgc_getALUOp2(cpu, inst) ? cpu->r[inst.rs1] : cgc_getALUOp2(cpu, inst);
}

void cgc_doMax(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] > cgc_getALUOp2(cpu, inst) ? cpu->r[inst.rs1] : cgc_getALUOp2(cpu, inst);
}

void cgc_doClr(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] & ~(1 << (cgc_getALUOp2(cpu, inst) & 0x1f));
}

void cgc_doSet(pruCPU *cpu, aluInstruction inst) {
	cpu->r[inst.rd] = cpu->r[inst.rs1] | (1 << (cgc_getALUOp2(cpu, inst) & 0x1f));
}

void cgc_doQATB(pruCPU *cpu, fmtQatbInstruction qatb) {
	int arg1;
	int arg2;
	char takeBranch = 0;
	if(qatb.io == 0)
		arg2 = cpu->r[qatb.arg2.rs2.reg];
	else
		arg2 = qatb.arg2.imm;

	if(qatb.eq)
		takeBranch = (arg1 == arg2);
	if(qatb.gt)
		takeBranch |= (arg1 > arg2);
	if(qatb.lt)
		takeBranch |= (arg1 < arg2);

	if(takeBranch) {
		cpu->pc += (signed char)qatb.broff2;
		if (cpu->pc < 0)
			cpu->pc = 0;
	}
}