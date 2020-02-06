# LazyCalc

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A very simple, binary protocol calculator that can do basic binary operations. It provides a way to import the operations and export the results. The results are not computed untill it's told to. The service provides a random base, so that a malicious person cannot figure out the correct value of the computation except for the person who initiated the computation.

### Feature List

- Basic math operations: Add, Sub, Mul, Div, Mod
- Import and Export
- Compute

## Vulnerability
### Vuln 1
The interface requires a number of operations to be done in the beggining. This number determines the size of the heap to be allocated to store the operations (type, arguments and the result). However, when the export feature is used, the contents (the result field of the stored heap structs) are copied to the stack buffer that can hold up to 30 integers. The program lacks the check for the maximum size of the operations, allowing an attacker to cause a stack buffer overflow.

#### Generic class of vulnerability

Stack Buffer Overflow

#### CWE classification

CWE-121: Stack-based Buffer Overflow

#### Challenges

 - There's also a pointer to the heap structure that gets overwritten while overwriting the return address on the stack.
 - This pointer gets free'd before the main function returns, so unless the valid pointer is provided the program aborts while trying to free an invalid pointer.
 - free(0) is a valid operation (virtually no-op), so the attacker needs to ensure that the pointer is overwritten with 0.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: easy
 - **Patching**: easy
