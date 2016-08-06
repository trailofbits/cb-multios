# KPRCA-00001

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple protocol that lets the user call a couple 
functions which implement the root64 and parcour schemes.

The protocol requires the user to authenticate with a token in order to prevent 
trivial DDOS attacks. The server will generate a random sesson token which the 
user must pass back to the server in order to authenticate and access the 
primary functionality.

### Feature List

This is a server that was roughly inspired by the Gopher protocol. It has a few 
protocol commands that are used to authenticate and set up the environment, and 
then the user can request pages which will perform computation and print the 
output. There are three pages: a summary screen showing which pages have been 
called, a root64 encoder and decoder, and a parcour obfuscator.

## Vulnerability

The vulnerability is triggered in the root64 encoding function (main.c:284). 
The check to verify the length of the input is wrong and can result in writing 
260 bytes to a 256 byte buffer. This 4-byte overwrite gives the attacker 
limited control of the ebx register which is later used as a pointer when 
incrementing the call count for the function (main.c:245). Gaining control of 
eip from here is difficult, but causing a crash is trivial.

### Generic class of vulnerability
Stack-based Buffer Overflow

### CWE classification
CWE-121: Stack-based Buffer Overflow

## Challenges

This service uses many primitives that are found in real-world programs:

* string processing (e.g. protocol messages, root64)
* arrays of function pointers
* dynamic memory allocation
* unpredictable data (e.g. authorization token)

In order to reach vulnerable code, the automated binary analysis tool must be 
able to ingest data produced by random() and send it back to the service. The 
rest of the logic is very simple in C, but much more difficult since it 
requires understanding of the malloc implementation and following function 
pointers.
