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

#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

void dprintf(char *str);

typedef struct _regTarget {
	unsigned char regSel:3;
	unsigned char reg:5;
} regTarget;

typedef struct _fmtQatbInstruction {
	unsigned char op:2;
	unsigned char gt:1;
	unsigned char eq:1;
	unsigned char lt:1;
	unsigned char broff1:2;
	unsigned char io:1;
	union {
		regTarget rs2;
		unsigned char imm;
	} arg2;
	regTarget rs1;
	unsigned char broff2:8;

} fmtQatbInstruction;


#endif