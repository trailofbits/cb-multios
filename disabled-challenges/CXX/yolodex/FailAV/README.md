# FailAV

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A C++ rule-based malware detection engine, with heuristics to handle different file formats. Utilizes an emulator to unpack malware before apply rules.

### Feature List

Malware engine rules can be updated at run-time. Detection algorithm is fast: speed is not affected by number of rules. Emulator supports 19 common instructions with up to 64KB of stack space and 1GB of heap space. Malware is sandboxed so that it cannot modify memory outside of its stack and heap. Heuristics for both executables and bitmaps.

## Vulnerability
### Vuln 1
In Emulator::in_stack (emulator.h:37), the service fails to ensure that the shadow stack pointer is in-bounds. This allows the attacker to read and write from memory that they shouldn't be able to, such as the C stack. An attacker can overwrite a return address to gain EIP control and then use a gadget to have a complete type-1 exploit.

#### Generic class of vulnerability

Memory Corruption

#### CWE classification

CWE-786: Access of Memory Location Before Start of Buffer

#### Challenges

 - The challenge encountered when proving is how to control both EIP and another register without causing a premature crash. Using a gadget is likely essential. A type 2 is more difficult and would probably require a call to Interface::send_response.
 
 - Discovery with fuzzing should be possible but the required input size is non-trivial. Mutation fuzzing is likely the easiest method to discover the vulnerability.

#### Difficulty

 - **Discovery**: medium
 - **Proving**: medium
 - **Patching**: medium
