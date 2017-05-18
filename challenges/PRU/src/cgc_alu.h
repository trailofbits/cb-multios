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

#include "cgc_cpu.h"
#include "cgc_instructions.h"

#ifndef _ALU_H
#define _ALU_H

enum aluEnum {
	ADD,
	ADC,
	SUB,
	SUC,
	LSL,
	LSR,
	RSB,
	RSC,
	AND,
	OR,
	XOR,
	NOT,
	MIN,
	MAX,
	CLR,
	SET
};

typedef struct _aluInstruction {
	unsigned int opFmt:3;
	enum aluEnum aluOp:4;
	unsigned int io:1;
	union _arg2 {
		regTarget rs2;
		unsigned char imm;
	} arg2;
	unsigned int rs1Sel:3;
	unsigned int rs1:5;
	unsigned int rdSel:3;
	unsigned int rd:5;
} aluInstruction;

void cgc_doAdd(pruCPU *cpu, aluInstruction inst);
void cgc_doAdc(pruCPU *cpu, aluInstruction inst);
void cgc_doSub(pruCPU *cpu, aluInstruction inst);
void cgc_doSuc(pruCPU *cpu, aluInstruction inst);
void cgc_doRsb(pruCPU *cpu, aluInstruction inst);
void cgc_doRsc(pruCPU *cpu, aluInstruction inst);
void cgc_doLsl(pruCPU *cpu, aluInstruction inst);
void cgc_doLsr(pruCPU *cpu, aluInstruction inst);
void cgc_doAnd(pruCPU *cpu, aluInstruction inst);
void cgc_doOr(pruCPU *cpu, aluInstruction inst);
void cgc_doXor(pruCPU *cpu, aluInstruction inst);
void cgc_doNot(pruCPU *cpu, aluInstruction inst);
void cgc_doMin(pruCPU *cpu, aluInstruction inst);
void cgc_doMax(pruCPU *cpu, aluInstruction inst);
void cgc_doSet(pruCPU *cpu, aluInstruction inst);
void cgc_doClr(pruCPU *cpu, aluInstruction inst);

void cgc_doQATB(pruCPU *cpu, fmtQatbInstruction qatb);

#endif