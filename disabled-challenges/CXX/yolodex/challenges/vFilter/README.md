# vFilter

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A constant-time VM interpreter and validator written in C for fast data filtering. The user provides a filter program and a set of data, which is processed and the results returned.

### Feature List

Separate validation and execution stages increases the performance of the interpreter as the amount of data increases. There is a one-time cost to make sure the program is correct, and then the interpreter can make assumptions that increase performance.

Support for many instructions: 13 arthimetic instructions, 4 conditional jumps, byte/half-word/word loads and stores, and read/write system calls. Loops are forbidden to guarantee that the execution is time-bound. During execution, the filter has access to a 1KB stack and the input data. Loads and stores are bounds-checked to prevent undefined behavior.

## Vulnerability
### Vuln 1

The VM interpreter keeps track of the value stored in each VM register and what memory space the VM register references. Normally, a VM register that holds a number will have a NULL memory space pointer. The interpreter takes advantage of this and ORs the memory space pointers together when performing an ADD or SUB instruction. This works because the validator enforces that the operands are either NUMBER-NUMBER, POINTER-NUMBER, or NUMBER-POINTER. So, the result of the OR is either NULL or a valid memory space pointer.

The interpreter fails to set the memory space pointer to NULL in some cases, which causes the aforementioned assumptions to break. This allows an attacker to construct a payload that results in the two memory space pointers being OR'd together, resulting in a memory space pointer that references attacker supplied memory, namely the VM registers. The attacker can set the length of this fake memory space structure to a large value and use a load instruction to read from any memory address or a store instruction to write to any address.

#### Generic class of vulnerability

Logic error

#### CWE classification

CWE-123: Write-what-where Condition
CWE-125: Out-of-bounds Read
CWE-465: Pointer Issues

#### Challenges

- The bug is in a virtual machine interpreter, which makes symbolic execution difficult
- The bug is dependent on the arrangement of heap allocations
- Patching is difficult because the bug is specific to this program and the memory access is inside of a loop that will affect performance if it is naively instrumented

#### Difficulty

 - **Discovery**: hard
 - **Proving**: medium
 - **Patching**: hard
