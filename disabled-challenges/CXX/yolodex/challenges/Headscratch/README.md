# CGC Challenge Binary (KPRCA_00056): Headscratch

### DARPA performer group
Kaprica Security (KPRCA)

## Description
Headscratch is an esoteric programming. Writing in headscratch is very tedious,
results in obscenely verbose programs, and will leave most programmers scrating
their heads out of confusion and frustration. This challenge binary implements
a headscratch interpreter.

### Feature List
  Headscratch supports the following statements.
  
   * \> Increment the data pointer.
   * _ Decrement the data pointer.
   * \+ Increment the value at the data pointer.
   * \- Decrement the value at the data pointer.
   * [  Go to matching ] if the value at the data pointer is zero.
   * ]  Go to matching [ if the value at the data pointer is not zero.
   * . Output the value at the data pointer.
   * , Read a value in and store it at the data pointer.

## Vulnerability

Within the interpreter exists a data pointer that points into memory which can
be modified by the currently running program. One of the statements available
to programmers of headscratch is the '>' statement which increments the data
pointer to point to the next byte in the section of memory used to store the
data available to a program. When incrementing the data pointer, the
interpreter does not check to make sure that the data pointer does not go past
the upper bounds of the data array which is stored on the stack. Therefore, it
is possible to increment that data pointer past the bounds of the array and
onto the stack frame where the program can then arbitrarily modify the stack
frame. This results in a type 1 vulnerability.

### Generic class of vulnerability

Unchecked pointer use.

### CWE classification

CWE-787: Out-of-bounds Write
CWE-823: Use of Out-of-range Pointer Offset

## Challenges
The primary challenge with exploiting this challenge binary is that a CRS must
be able to construct a Headscratch program that allows for the exploitation the
vulnerability.

## Subjective Quantification
Discovering: Easy
Proving: Medium
Fixing: Easy
