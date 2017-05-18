# CGC Challenge Binary CROMU_00021

## Author Information

"Dustin Fraze" <df@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This is a challenge which implements a simple integer calculator.  It supports variables, and has a number of built-in functions, some of which are arithmetic and some of which aren't.  It also supports booleans and strings, and some functions on those datatypes.

### Feature List

This is a multi-function calculator.  It supports addition, subtraction, multiplication, division, modulus, length, type, int casts, and equality checks on integers, strings, and booleans.

It allows for some pseudo-intelligent operations to occur on different datatypes.  For example, adding a string and an integer will cast the integer to a string, and concatenate the two.  Adding a integer and a string will not add, because I didn't think that made as much sense.

## Vulnerability
There are multiple vulnerabilities of differing severity.

The most severe vulnerability is type confusion.

Most of the internal functions are of special type "Function".  These include "add", "sub", "mul", and their friends.  Many of them have a shorthand notation.  Add, for example, is +.

One can redefine an internal function and have the program "mostly" work - var add = 5 will change add to 5, such that 5 add 5 will return 5 (the function stack will be empty, and the last operand in the operator stack is 5).

Variable names are legally only of a string of letters and numbers, with no whitespace between them.  The shorthand operators are made up of symbol characters.  A shorthand operation is always pushed into the function stack, even if the underlying function has been redefined.  The calculator will attempt to call the type data as a function.  In the case of a string type, the calculator will execute the bytes which make up the string.

There is another bug in the operand and function stack.  All inputs are read into a single, length checked buffer.  Inputs are then tokenized, and shoved into a function stack or operand stack, depending on type information.  Each of these stacks contains 32 elements, and there is no bounds check on insertion.  Without a sufficiently fortunate series of heap allocations, this leads to a crash.

A NULL pointer dref exists if a user passes the "var" command without any arguments. Strtok returns NULL and if it does not find a space without a check before the following dereference.

There is an integer overflow vulnerability in the mul command when multiplying a string by an integer. Depending on the length of the string and the size of the integer, an integer overflow may occur resulting in a too small buffer allocation before the string is written leading to a buffer overflow. 

### Generic class of vulnerability
Type Confusion
Out of bounds read
out of bounds write
NULL Pointer Dereference
Integer overflow

### CWE classification
Type Confusion
CWE-843

Out of bounds read
CWE-125

Ouf of bounds write
CWE-787

CWE-476 NULL Pointer DREF
CWE-190 Integer Overflow or Wraparound

## Challenges

This challenge binary uses a trie to store function pointers to reach deeper functionality.  Exploration of the challenge set will require processing the entries in the trie and generating inputs capable of exercising the application.
