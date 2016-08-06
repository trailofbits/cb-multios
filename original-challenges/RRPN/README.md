# KPRCA-00002: RRPN

## Author Information
"Brian Pak" <brian.pak@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple Reverse Polish Notation (RPN) calculator that 
supports a few arithmetic operations. The service uses Just-In-Time (JIT) 
compilation to emit native x86 code to compute the result.

The RPN calculator works like a normal stack machine, but it uses __%eax__ and 
__%edi__ registers as the first two items on the stack in order to make the 
JIT'd code simpler (with no memory access). The most recent operand always 
resides in __%eax__ and the second most recent opeand is in __%edi__.

In case of (RPN stack) underflow or invalid operator, the service outputs an 
error. Also, the result is whatever the value that is on the top of the stack 
at the end of parsing (in case there are more numbers than operators consumed).

Note: The order of operands used in binary operation is different from the 
normal RPN (where the notation is reversed but not the order of operands). For 
example, if the input is "a b -" (with a being at the bottom of the stack), the 
result is b - a. This should not affect the vulnerability, however.

### Feature List
This calculator supports basic operations like addition, subtraction, 
multiplication, and division, as well as absolute value, bitwise negation, and 
power. Number can be provided in octal, decimal, or hexadecimal, and output 
will be given as both decimal and hexadecimal.

## Vulnerability

The vulnerability is triggered while generating and pushing integers (operands) 
to the allocated memory. The JIT structure contains the code page and the stack 
of fixed sizes, and without the overflow validation, the code generated and the 
operands on the stack could collide each other. The code grows up while the 
stack grows down in memory. With a carefully crafted input, which should be a 
valid input to the RPN calculator, it is possible to run arbitrary code.

### Generic class of vulnerability
Heap-based Buffer Overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow

## Challenges

This service challenges some of the non-trivial, real-world aspects of the 
program analysis:

* executable memory page
* JIT compilation
* string processing

The main focus of this challenge is to test if the program analysis can handle 
dynamically generated code. The vulnerability is not necesarilly related to the 
JIT operation, but one has to realize that the code being generated and the 
data being pushed can collide in memory, which gets executed later.
