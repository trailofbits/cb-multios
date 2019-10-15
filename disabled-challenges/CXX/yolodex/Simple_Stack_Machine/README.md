# Simple Stack Machine

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a very simple stack based machine with a very simple instrion set. Therefore, this CB was designed to help test a CRSes ability to 1. monitor the heap (i.e. allocate and deallocate system calls), 2. support bit-wise operations for dependency analysis (i.e. the instruction set uses the lowest 3 bits of a 32-bit word), 3. and identify that the PUSH and DUP instructions can be used to push data onto the stack to cause it to overflow.


### The Instruction Set

000b : PUSH # : Pushes a new number onto the stack
001b : POP : Pops the top number from the stack
010b : PUSHPC : Pushes the program counter of the current instruction (i.e. PUSHPC) onto the stack
011b : JMPZ : Pops the top number off of the stack, if its 0 then pop the next value off of the stack and store that into the PC. If it is not-zero then just pop the next value off of the stack and do nothing with it.
100b : SWAP # : Swaps the nth number with the top one (which is 0) - meaning SWAP 0 does nothing
101b : DUP #: Duplicates nth number and pushes it to the top of the stack
110b : ADD : Pops the top two numbers off of the stack, adds them, and pushes the sum back onto the stack
111b : SUB : Pops the top two numbers off of the stack, subtracts them ( (top - 1) - top ), and pushes the difference back onto the stack

All instructions are 32-bits long with the first 3 bits (msbs) reserved for the instruction and the lower 29 bits for literals. POP, ADD, SUB, PUSHPC, JMPZ ignores the lower 29 bits, UNLESS the following special instructions are used:

0xFFFFFFFF : RET : End of instruction stream - The topmost value is the return value

### A simple program

multiply(x,y)

PUSH 0	; 0 - the SUM
PUSH y 	; SUM, y
PUSHPC 	; SUM, y, pc
DUP 1 	; SUM, y, pc, y
PUSH 1	; SUM, y, pc, y, 1
SUB	; SUM, y, pc, y-1
SWAP 2	; SUM, y-1, pc, y
SWAP 3	; y, y-1, pc, SUM
PUSH x 	; y, y-1, pc, SUM, x
ADD 	; y, y-1, pc, SUM+x
SWAP 3 	; SUM+x, y-1, pc, y
POP	; SUM+x, y-1, pc
PUSHPC	; SUM+x, y-1, pc, HERE
PUSH 7	; SUM+x, y-1, pc, HERE, 7
ADD	; SUM+x, y-1, pc, HERE+7 
DUP 2	; SUM+x, y-1, pc, HERE+7, y-1
JMPZ	;
PUSH 0	; SUM+x, y-1, pc, 0
JMPZ	;
POP	; SUM+x, y-1
POP	; SUM+x
RET

If y-1 is not zero, then we will jump back up to where PUSHPC is and execute that whole stream again, except SUM will now be SUM+x and y is now y-1
If y-1 is zero, then we will jump to the instruction after the second JMPZ (which is the first POP)

## Vulnerability Class: 

This is a buffer overrun vulnerability that is induced when the too many items are pushed into the stack. This is a [CWE-122: Heap-based Buffer Overflow](http://cwe.mitre.org/data/definitions/416.html).

