# Palindrome

## Author Information

CGC Summer Intern 2014
Cadet from West Point Military Academy

### DARPA performer group
CADET

## Description:

This is an unusually simple service written by a military cadet as his first ever C program. It is intended as a data point as an incredibly simple service, with an incredibly simple vulnerability, written by an inexperienced programmer.

The underlying service itself is a palindrome detector.

## Vulnerability

CWE-121: Stack-based Buffer Overflow

The palindrome vulnerability is a vanilla buffer overflow on the stack. The program allocates 64 bytes of stack space for network input and reads up to 128 bytes at a time.

## Challenges

The only intended challenge posed by this service is that it was written by an inexperienced C programmer and consequently it may look different than other test cases.
