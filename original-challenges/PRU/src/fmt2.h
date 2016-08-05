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

#ifndef _FMT2_H
#define _FMT2_H

#include "instructions.h"
#include "cpu.h"

#pragma pack(1)

enum fmt2Enum {
	JMP,
	JAL,
	LDI,
	LMBD,
	SCAN,
	HALT,
	RESERVED_1,
	RESERVED_2,
	RESERVED_3,
	RESERVED_4,
	RESERVED_5,
	RESERVED_6,
	RESERVED_7,
	RESERVED_8,
	RESERVED_9,
	SLP
};

typedef struct _fmt2InstructionHeader {
	unsigned char opFmt:3;
	unsigned char subOp:4;
	unsigned char other:1;
} fmt2InstructionHeader;

typedef struct _fmt2BranchInstructionReg {
	regTarget rs2;
	unsigned char reserved;
} fmt2BranchInstructionReg;

typedef struct _fmt2BranchInstruction {
	fmt2InstructionHeader header;
	union { 
		fmt2BranchInstructionReg reg;
		unsigned short imm;
	} arg2;
	regTarget rd;
} fmt2BranchInstruction;

typedef struct _fmt2LdiInstruction {
	fmt2InstructionHeader header;
	unsigned short imm:16;
	regTarget rd;
} fmt2LdiInstruction;

typedef struct _fmt2LmbdInstruction {
	fmt2InstructionHeader header;
	union {
		regTarget rs2;
		unsigned char imm;
	} arg2;
	regTarget rs1;
	regTarget rd;
} fmt2LmbdInstruction;

typedef struct _fmt2ScanInstruction {
	fmt2InstructionHeader header;
	union {
		regTarget rs2;
		unsigned char imm;
	} arg2;
	regTarget rs1;
	regTarget rd;
} fmt2ScanInstruction;

typedef struct _fmt2HaltInstruction {
	fmt2InstructionHeader header;
	unsigned char res1;
	unsigned char res2;
	unsigned char res3;
} fmt2HaltInstruction;

typedef struct _fmt2SlpInstruction {
	fmt2InstructionHeader header;
	unsigned char WakeOnStatus:1;
	unsigned char res1:7;
	unsigned char res2;
	unsigned char res3;
} fmt2SlpInstruction;

void doBranch(pruCPU *cpu, fmt2BranchInstruction inst);
void doLdi(pruCPU *cpu, fmt2LdiInstruction inst);
void doLmbd(pruCPU *cpu, fmt2LmbdInstruction inst);
void doScan(pruCPU *cpu, fmt2ScanInstruction inst);

#endif