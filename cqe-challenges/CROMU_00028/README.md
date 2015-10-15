# Carbonate

## Author Information

Bryce Kerley <bk@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This challenge binary requires the solver to provide inputs for an algorithm
that uses mixed floating point and integer operations on its inputs.

### Feature List

The service opens with a simple "hello" message that must be returned by the
client.

The client then sends 32 bits of input to the server, which is expanded using a
custom RNG algorithm using mixed floating-point and integer operations. The
algorithm then takes more input, for a total of 256 bits of input, to reach an
end state matching certain hardcoded properties.

Once the end state has been reached, the client is provided access to a set
data structure implemented as a bitmap on the stack. However, the address space
of the structure is larger than its capacity, allowing stack writes outside of
its bounds.

## Vulnerability

The set data structure on the stack has incorrect bounds checking, allowing
user control of individual bits above it on the stack.

### CWE classification

CWE-129	Improper Validation of Array Index

## Challenges

The primary difficulty with this challenge is solving for specific outputs with
mixed floating-point and integer operations.
