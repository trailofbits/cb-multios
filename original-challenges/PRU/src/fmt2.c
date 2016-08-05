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

#include "fmt2.h"
#include "cpu.h"
#include "stdio.h"

void doBranch(pruCPU *cpu, fmt2BranchInstruction inst) {
	if(inst.header.subOp == 1) {
		cpu->r[inst.rd.reg] = cpu->pc+1;
	}
	if(inst.header.other == 0) {
		cpu->pc = cpu->r[inst.arg2.reg.rs2.reg];
	} else {
		cpu->pc = inst.arg2.imm;
	}
}

void doLdi(pruCPU *cpu, fmt2LdiInstruction inst) {
	cpu->r[inst.rd.reg] = inst.imm;
}

void doLmbd(pruCPU *cpu, fmt2LmbdInstruction inst) {
	int i;
	int arg;
	if(inst.header.other == 0)
		arg = cpu->r[inst.arg2.rs2.reg];
	else
		arg = inst.arg2.imm;
	for(i=31;i>=0;i--) {
		if( ! (((cpu->r[inst.rd.reg] >> i) ^ cpu->r[inst.arg2.rs2.reg])&1))
			break;
	}
	if(i<0)
		cpu->r[inst.rd.reg] = 32;
	else
		cpu->r[inst.rd.reg] = i;
		
}

void doScan(pruCPU *cpu, fmt2ScanInstruction inst) {
	if(inst.header.other == 1)
	{
		if(cpu->r[inst.rs1.reg]+inst.arg2.imm < 0x1000)
			cpu->r[inst.rd.reg] = cpu->code[cpu->r[inst.rs1.reg]+inst.arg2.imm];
	} else {
		#ifndef PATCHED_1
		cpu->r[inst.rd.reg] = cpu->code[cpu->r[inst.rs1.reg]+cpu->r[inst.arg2.rs2.reg]];
		#else
		if(cpu->r[inst.rs1.reg]+cpu->r[inst.arg2.rs2.reg] < 0x1000)
			cpu->r[inst.rd.reg] = cpu->code[cpu->r[inst.rs1.reg]+cpu->r[inst.arg2.rs2.reg]];
		#endif
	}
}