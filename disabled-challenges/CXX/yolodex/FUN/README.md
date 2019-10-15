# KPRCA-00044 (FUN)

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple text generator based on a Markov process. The initial states are built using static text from the great essayist Jonathan Swift. Additional states can be introduced by training, during which the service will generate text using the current states and an included dictionary, and if the user approves, the text will be added to the states.

### Feature List

As an ultra-secure service, attempts to exploit this service will fail because of its novel function pointer protection (FUNpro). Additionally, the text generation uses an advanced RNG that makes use of the latest in processor technologies (SSE2).

The available commands are:

 * Reprotect - FUNpro!
 * Add word - add a word to the internal dictionary
 * Sort words - sort the internal dictionary
 * Search words - search through the dictionary for a word or partial word
 * Generate text - generates text randomly using the current states
 * Training - add new states via a machine learning procedure

## Vulnerability

The vulnerability is a buffer overflow of an array of strings in the *.data* section (*words*). The binary fails to check the length of the array when adding new strings to the end of the array (*main.c:421*). By overflowing the array, the attack is able to overwrite data used by *malloc* and eventually the *secret_key* which is used to unobfuscate function pointers.

### Generic class of vulnerability
Buffer overflow

### CWE classification
CWE-788: Access of Memory Location After End of Buffer

## Challenges

This challenge set implements a service with a minimum of direct function calls. Instead, almost all of the function calls from *main.c* are indirect calls through an array of obfuscated function pointers. These function pointers are obfuscated at compile time by adding a constant value to the pointers, and can be reobfuscated at run-time by the user. This will pose a challenge from static analysis of the challenge binary.

Additionally, in order to trigger the buffer overflow the attack must be able to add many valid words to the dictionary. When adding a new word, the service checks that the word does not already exist in the dictionary and that the word partially matches another word in the dictionary. This will post a challenge for trivial fuzzing attempts, but should be easy for symbolic execution. However, if incorrect paths are taken, the solver will need to handle SSE and SSE2 instructions.
