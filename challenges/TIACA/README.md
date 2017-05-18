# TIACA (CROMU_00012)

## Author Information

"Dustin Fraze" <df@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is an opcode service with function names and state were inspired by cars, generally to abstract state tracking for the convience of the author.  Abstracting complicated systems to car analogies is popular in engineering text books.

### Feature List

This service is an abstraction of a car, based on my very poor understanding of how cars work.  A user can arm and disarm the car's alarm, open, load/unload, and close the trunk, manipulate the windows and moonroof, listen to music, and drive the car.  Fuel is accounted poorly, based on car load, speed, and window state.  At the end of a drive, the user can ask for the state of the car.

## Vulnerability

When the "car" is in a high gear, the user is allowed to turn on the radio.  If the radio is in bluetooth mode, the transmitter sends over metadata about whats being played.  This metadata contains a simple buffer overflow.  The overflowed buffer is inside the serviceLoop's frame, and serviceLoop never returns.  Proper exploitation requires overflowing the carstate pointer in the serviceLoop's stack frame.  In the provided POV, I set this pointer to be ESP at the call to updateBTMetadata, such that when updateBTMetadata is called a second time, I overwrite the return address.

It is possible to read beyond the end of the stack if the car is in gear

### Generic class of vulnerability
Buffer Overflow

### CWE classification
NULL Pointer Dereference
CWE-787: Out-of-bounds Write

## Challenges

This service has a poor man's "address sanitization" built in.  All pointers are validated as pointing to within the stack address range or program .text address range.  Return addresses are further validated to be pointing into the program .text, and *returnaddress-5 == 0xe8, the 5 byte version of a call.  The validateRet function emits a cmp eax, 0xe8, which is 0x3de8000000, allowing a system to return to the cmp plus 1 byte, which gets interpreted as a call into an invalid address.  Strengthened versions of memcpy, and a handful of other string functions have been written to take advantage of this pointer validation.

The implementation of address sanitization may cause problems for CRS which attempt to introduce defenses without doing analysis on the application.  If they attempt to introduce ASLR in the .text section, all function calls will fall outside of the validateRet() safeguards, and cause all calls to fail.  If they attempt to move the stack in a similar manner, validatePtr() will fail.  Removing these checks will make the poller fail.

This service also has two cases where an overflow of a return address are done, but they are seemingly useless for exploitation.  In the case where the car alarm is set, and the trunk is opened, the program overwrites a return address with 0x41414141, and attempts to validate the return address.  This will of course fail, and print out a message signifying stack smashing has been detected.  Some overzealous CRS may attempt to disallow this overwrite to occur, spotting it as a vulnerability.  In doing so, they may cause SLA failure, as my poller causes this to happen, and checks for the stack overflow detected notification.  Serviceloop's returns address is also overflowable, but there is no way to get serviceLoop to return, as all exits from serviceLoop are through the _terminate() syscall.
