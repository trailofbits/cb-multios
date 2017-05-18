# PRU

## Author Information

"Cromulence" <cgc@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is an emulator of an instruction set inspired by the TI ARM PRU. The PRU is featured on the BeagleBone black, and was used to provide high performance I/O on a board at the DEF CON 2015 Capture The Flag.

### Feature List

This service features an ALU and pieces of a branch unit. A user can do a variety of arithmetic operations on 32 registers, and conditional branching as well.

## Vulnerability

SCAN instruction allows the user to scan bytes within the code segment of the emulator. This would allow for a constant table to be placed within the instruction stream. The SCAN instruction validates that the register+immediate offset are within the confines of the code section, but it doesn't do the same check for register+register form of the instruction.

### Generic class of vulnerability
Insufficient bounds checking

### CWE classification
Insufficient bounds checking
CWE-125: Out-of-bounds Read

## Challenges
### Discovery
Medium - many instructions modify state. May not be obvious how much control the CRS has over the pieces which make the vulnerability occur.
### Proving
Medium/Hard - A CRS will have to understand the emulator and use that to feed and transform values in the register states to prove vulnerability.
### Fixing
Easy - a contraint needs to be applied on the register arg2 form of SCAN in much same way it is applied on the immediate form.
