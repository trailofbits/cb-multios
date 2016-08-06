# KPRCA-00014

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a basic virtual machine that receives one instruction at a time and sends back the VM's current register state.

The protocol starts with a header that has a magic check and fields to allow initialization of the VM's registers and memory. Each instruction is 32-bits and is generally in the format: 8-bit opcode, 4-bit destination register, 4-bit source register, 16-bit literal.

### Feature List

The virtual machine implements basic arithmetic such as addition, subtraction, division, and multiplication, as well as integer comparisons and basic IO. The machine state consists of 15 general purpose registers and 64KB of memory. For performance, the interpreter utilizes computed gotos instead of the more common if statements or switch statement.

## Vulnerability

The 8-bit opcode that is parsed from the instruction is used to index into an array of label values, and the result is the target of the computed goto statement (main.c:110). There is a check to make sure the opcode is not greater than the number of elements in the array (main.c:109), but the opcode is a signed integer which can lead to an underflow. By specifying a negative 8-bit opcode, an attacker can force the program to execute invalid memory.

### CWE classification
CWE-127: Buffer Under-read

## Challenges

The primary challenge for this service is to correctly reason about computed jumps and then protect against the vulnerability. Depending on the implementation, control flow integrity protections may not correctly handle computed gotos.

Discovering the vulnerability should be possible with any means of testing, including both fuzzing and symbolic execution. The protocol is small and simple which should reduce state explosion.
