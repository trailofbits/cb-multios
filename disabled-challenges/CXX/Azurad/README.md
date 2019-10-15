# Azurad

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A custom language interpreter implementing a simple calculator service. The service lets a user insert and retrieve numbers, perform arithmetic on the numbers, and access a RNG.

### Feature List

While the service is very simple, the language it is implemented in is very featureful. The language includes support for dynamic types, arrays, while loops, conditionals, scoping, and procedures. The library can be easily extended by adding additional external functions written in C, or by creating whole new types similiar to the current array support.

Current library functions:

 - chr
 - ord
 - rand
 - read
 - echo

## Vulnerability
### Vuln 1
In Array::set and Array::get, the library does not properly handle INT32_MIN (0x80000000). This results in some integer overflows which will lead to a trivial heap overflow.

In the POV, we utilize the bug in Array::set to cause the allocated buffer to be small but the number of allocated items to be large. Then we use Array::get to read the *password* variable that is on the heap. This results in a type 2 exploit.

#### Generic class of vulnerability

Heap Corruption

#### CWE classification

CWE-680: Integer Overflow to Buffer Overflow

#### Challenges

 - The primary challenge is naturally the interpreted language, since it obscures the control flow of the service
 - Actual exploitation of the bug is difficult because of the very limited control of memory; though this is easier if relying on stack addresses and WX-stack

#### Difficulty

 - **Discovery**: medium
 - **Proving**: medium
 - **Patching**: medium
