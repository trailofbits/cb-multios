# CGC Challenge Binary (KPRCA\_00046): CGC Board

### DARPA performer group
Kaprica Security (KPRCA)

## Description
CGC Board is a service that allows the user to play a board game against a computer opponent. It uses sophisticated techniques, such as brute force and pruning, to provide a challenging yet fun game. Its protocol is similar to other board game protocols and is text-based making it easy to integrate with other software, such as a GUI.

### Feature List

 * Bitboard-based internal representation
 * Configurable search depth
 * Quiescent search up to depth 16
 * Support for random play

## Vulnerability
There are two vulnerabilities in the challenge binary. The first vulnerability is insufficient checks when interpreting a move command. A valid move should be in the range of a1a1-h8h8, but the service only verifies that the second and fourth characters are digits. This allows an attack to specify an invalid command, such as a0a8, which can trigger an out-of-bounds read and write.

The second vulnerability is a failure to check the bounds of the *moves* array in *engine_t*. Whenever a move is applied to the game, it is stored at the end of the *moves* array so that it can be undo-ed later. The array is fixed length, however, and no checks are done to see if the pointer, *current_move*, points beyond the length of the array. This heap buffer overflow will result in an out-of-bounds read and write.

### Generic class of vulnerability

Heap-based Buffer Overflow

### CWE classification

CWE-122: Heap-based Buffer Overflow
CWE-823: Use of Out-of-range Pointer Offset

## Challenges
The first vulnerability was designed to be easy to find, fix, and trigger. The second vulnerability is much more difficult to trigger unless the CRS can determine that the play command (**?**) will advance *current_move* consistently. It would be extremely challenging and unexpected for the CRS to trigger the second vulnerability without using the play command. The goal is not to force the CRS to actually play and understand the game.
