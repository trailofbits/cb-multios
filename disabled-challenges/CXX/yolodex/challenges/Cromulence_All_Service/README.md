# Cromulence All Service

## Author Information

"Jason Williams" <jdw@cromulence.co>
“Joe Rogers” <joe@cromulence.co>
"Debbie Nuttall" <debbie@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a joint effort from multiple Cromulence developers. It includes a command line interface with a command handler and registered command.

The first command is a sort command and allows the user to enter a number of integers to be sorted. The user then enters each integer one line at a time and the sorted list is printed back to the user.

The second command provides basic addition, subtraction, and scalar multiplication matrix math operations.  Depending on the requested operation, the user is prompted to supply the matrices and/or the scalar multiplier.  The resulting matrix is printed out before returning to the matrix operation menu.

The third command is a game similar to Simon says. The game outputs a sequence of colors and the user must generate a reply sequence that matches. After every correct answer, the sequence grows longer. 

The fourth command is a data encoding function similar to Base64.  Raw data is entered and the resulting encoded data is output.
### Feature List

This service features an interactive command line, the ability to list commands, and numerous commands. The first command is the sort command which sorts integers entered by the user.  The second command provides basic matrix math operations. The third command is a simon says game. 

## Vulnerability

This service has the following vulnerabilities.

The first vulnerability is in the sort command. A user can enter a negative number for the number of items to be sorted. Due to a sign/unsigned comparison bug it is possible for the user to enter a negative number and pass the max length check for the sort array. In doing so the user can then write outside of the array and corrupt the stack frame overwriting the return address.

The second vulnerability is in the matrix command.  The program uses a fixed size array to store the matrices.  It incorrectly checks the necessary size of the array by multiplying the supplied dimension values together without properly handling the possibility of an integer overflow. 

The third vulnerability is in the simon command. The user response is written to a stack buffer. If the user successfully plays past the first 236 rounds of play, the response will begin writing past the end of the stack buffer. If the game is successfully played up to the maximum number of 256 rounds, a 20 byte stack overwrite will occur before the simon function exits. 

### Generic class of vulnerability

sort command:
Signed to Unsigned Conversion Error
Stack-based Buffer Overflow

matrix command:
Integer overflow leading to an incorrect calculation of buffer size

simon command:
Stack-based Buffer Overflow

### CWE classification

sort command:
CWE-195: Signed to Unsigned Conversion Error
CWE-121: Stack-based Buffer Overflow

CWE-190: Integer Overflow or Wraparound
CWE-131: Incorrect Calculation of Buffer Size

simon command:
CWE-121: Stack-based Buffer Overflow

## Challenges

This service presents the CRS with a number of possible commands that the CRS can select from. The service is designed to be simple in nature and have multiple bugs for the CRS to exploit. The only challenge is in determining the command table, entering the correct command, and setting the proper states for an exploitable command.

