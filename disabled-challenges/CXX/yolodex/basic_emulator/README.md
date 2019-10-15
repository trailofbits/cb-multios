# KPRCA-00009 

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:
This service implements an emulator of a game system. The user sends a cartridge data which is run by the emulator. The user can send commands to simulate input controls or to quit the emulator. Several times per second the emulator will send the current screen of the game system to the user as ASCII art.

### Feature List
The emulator supports basic I/O, interrupts, timers, and many types of instructions. The emulated ISA is a variation of the Z80, which features variable-length instructions, 8-bit and 16-bit registers, and a 16-bit address space. Capabilities include a 1 MIPS (million instructions per second) CPU, 32KB of ROM, 8KB of RAM, and 8 digital inputs.

## Vulnerability
The vulnerability is present in the cartridge loading functionality. Every cartridge has a header which includes a title field. The emulator iterates over the title field until it hits a non-uppercase character, and copying the characters unless it is passed the end of the title buffer. However, after the loop, it adds a NULL-byte which may be past the end of the buffer if the original title field was not properly terminated.

With this vulnerability, an attacker is able to set a byte of the __bg__ pointer to zero, which will result in a segmentation fault on access. Additionally, the attacker has some control of which bytes get written to the __bg__ memory, though this is not necessary to prove vulnerability.

### Generic class of vulnerability
Buffer Overflow

### CWE classification
CWE-170: Improper Null Termination

## Challenges

Analysis of this service will face challenges with state-space explosion due to the size of the input and the multiple effects of each byte. 

In order to increase the probability of a solution, the vulnerability can be triggered by modifying only the bytes in the cartridge header. Additionally, the vulnerability occurs before the main loop and allows for setting an arbitrary byte of a pointer to zero, which may help narrow the search space for a solution.
