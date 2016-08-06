# KPRCA-00035

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a basic virtual machine that receives one instruction
at a time and sends back the VM's current register state.

The protocol starts with a header that has a magic check and fields to allow
initialization of the VM's registers and memory. Each instruction is 32-bits
and is generally in the format: 8-bit opcode, 4-bit destination register, 4-bit
source register, 16-bit literal.

### Feature List

The virtual machine implements basic arithmetic such as addition, subtraction,
division, and multiplication, as well as integer comparisons and basic IO. The
machine state consists of 15 general purpose registers and 64KB of memory. For
performance, the interpreter utilizes computed gotos instead of the more common
if statements or switch statement.

## Vulnerability

The VM supports a syscall that allows the user to frobnicate a region of
memory.  The fronicate function does not check the arguments that it is called
with to ensure they will only result in the frobnication of memory within the
bounds of the VM's memory array (main.c:113). Therefore, it is possible to
frobnicate a region  of memory outside bounds of the array, which in this case
is heap memory since the VM's state is allocated on the heap.

### CWE classification
CWE-129: Improper Validation of Array Index
CWE-665: Improper Initialization
CWE-787: Out-of-bounds Write

## Challenges

The primary challenge for this service is to get the VM to call the `frob`
syscall function. The syscall function is accessed through a function pointer
on the stack. This function pointer is set appropriately according to the
syscall arguments. Part of the challenge is that there is no code path that
explicitly sets this function pointer to the frobnicate function. However, it
is also that case that unless the arguments are specific values, the function
pointer is not initialized. Therefore, if the address of memory where this
function pointer lies is set to the address of the frobnicate function via some
other code path in the program then the vulnerable frobnicate function is
accessible. Since the `process_xor` function's `new_val` stack variable lies at
the same address as the `process_sys` function's `fp` variable, this task is
achievable. Executing this vulnerability will require symbolic execution or
some other way of reasoning about a way of accessing the frobnicate function.
