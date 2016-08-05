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
#define ENABLE_BUFFERED_PRINTF

#include <libcgc.h>
#include "stdio.h"
#include "stdlib.h"
#include "alu.h"
#include "fmt2.h"
#include "cpu.h"
#include "string.h"

#define MAX_INSNS 2000

void dprintf(char *str) {
//	puts(str);
}

void dumpState(pruCPU *cpu) {
	int regNum;
	printf("============================================\n");
	for(regNum=0;regNum<=31;regNum+=2) {
		printf("R$d:\t0x$0.8x\tR$d:\t0x$0.8x\n", regNum, cpu->r[regNum], regNum+1, cpu->r[regNum+1]);
	}
	printf("PC:\t0x$0.8x\n============================================\n", cpu->pc * 4);
}

void execute(pruCPU *cpu) {
	aluInstruction inst;
	fmt2InstructionHeader fmt2Hdr;
	while(1) {
		int didBranch = 0;
		memcpy(&inst, (aluInstruction *)&cpu->code[cpu->pc], 4);
		switch(inst.opFmt) {
			case 0b000:
				switch(inst.aluOp) {
					case ADD:
						doAdd(cpu, inst);
						break;
					case ADC:
						doAdc(cpu, inst);
						break;
					case SUB:
						doSub(cpu, inst);
						break;
					case SUC:
						doSuc(cpu, inst);
						break;
					case LSL:
						doLsl(cpu, inst);
						break;
					case LSR:
						doLsr(cpu, inst);
						break;
					case RSB:
						doRsb(cpu, inst);
						break;
					case RSC:
						doRsc(cpu, inst);
						break;
					case AND:
						doAnd(cpu, inst);
						break;
					case OR:
						doOr(cpu, inst);
						break;
					case XOR:
						doXor(cpu, inst);
						break;
					case NOT:
						doNot(cpu, inst);
						break;
					case MIN:
						doMin(cpu, inst);
						break;
					case MAX:
						doMax(cpu, inst);
						break;
					case CLR:
						doClr(cpu, inst);
						break;
					case SET:
						doSet(cpu, inst);
						break;
				}
				break;
			case 0b001:
				memcpy(&fmt2Hdr, &inst, sizeof(fmt2Hdr));
				switch(fmt2Hdr.subOp)
				{
					case JMP:
					case JAL:
						;
						fmt2BranchInstruction fmt2Branch;
						memcpy(&fmt2Branch, &inst, 4);
						doBranch(cpu, fmt2Branch);
						didBranch = 1;
						break;
					case LDI:
						;
						fmt2LdiInstruction fmt2Ldi;
						memcpy(&fmt2Ldi, &inst, 4);
						doLdi(cpu, fmt2Ldi);
						break;
					case LMBD:
						;
						fmt2LmbdInstruction fmt2Lmbd;
						memcpy(&fmt2Lmbd, &inst, 4);
						doLmbd(cpu, fmt2Lmbd);
						break;
					case HALT:
						return;
					case SCAN:
						;
						fmt2ScanInstruction fmt2Scan;
						memcpy(&fmt2Scan, &inst, 4);
						doScan(cpu, fmt2Scan);
						break;
					case SLP:
					case RESERVED_1:
					case RESERVED_2:
					case RESERVED_3:
					case RESERVED_4:
					case RESERVED_5:
					case RESERVED_6:
					case RESERVED_7:
					case RESERVED_8:
					case RESERVED_9:
						return;
				}
				break;
			case 0b11:
				;
				fmtQatbInstruction qatbInstruction;
				memcpy(&qatbInstruction, &inst, 4);
				doQATB(cpu, qatbInstruction);			
			default:
				return;
		}
		if(didBranch == 0)
			cpu->pc++;
		cpu->numExecuted++;
		if(cpu->numExecuted >= MAX_INSNS)
			return;

	}
}

int recvInt() {
	char tmp[4];
	size_t recvd = 0;
	size_t totRecvd = 0;
	int ret;
	while(totRecvd<=3) {
		receive(0, tmp+totRecvd, 4-totRecvd, &recvd);
		if(recvd == 0)
			_terminate(0);
		totRecvd+=recvd;
	}
	memcpy(&ret, tmp, 4);
	return ret;
}
int main() {
	int numInstructions;
	int recvd;
	int i;
	pruCPU cpu;
	cpu.numExecuted = 0;
	memset(cpu.code, 0xff, 0x4000);
	numInstructions = recvInt();
	for(i=0;i<numInstructions;i++) {
		cpu.code[i] = recvInt();
	}
	execute(&cpu);
	dumpState(&cpu);
	_terminate(0);

}
