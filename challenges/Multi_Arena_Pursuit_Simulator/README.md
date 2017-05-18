# Multi_Arena_Pursuit_Simulator

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Welcome to the Multi-Arena Pursuit Simulator. This tool will train you how to make the precision moves that lead to the successful capture of a fleeing criminal everytime. Though be careful. Just a single bad move, and your criminal could be gone for good. In this simulation you will pursue criminals in both an urban and nautical setting.

Each of the simulations will begin with providing the user the starting location of the criminal on one of two arenas. The user will then provide the simulators a list of valid moves that will either lead to the capture of the criminal or of their successful evasion. Due to the technical advantages of the user's vehicles, the user is allowed to move two units per turn, while the criminal only moves one unit per turn. If the user reaches a position at or adjacent to that of the criminal, the criminal is "caught." If the criminal reaches a position where evasion will always be possible, the criminal "gets away".

Successful completion of the simulator requires 100 successful captures in a row in both the City and Harbor arenas. 

### Feature List

### City Chase
* The map is a square grid. 
* The user must obey all traffic signals, which will permit only Forward and Right moves.
* The criminal is able to move in any of four directions or stay where they are.

### Harbor Chase
* The map is triangular lattice.
* The user's watercraft restricts movement to only Forward movements. Therefore, Left and Right movements are only 45-degrees of Forward.
* The criminal is able to move in any of six directions or stay where they are.


## Vulnerability 1

This vulnerability is the result of the overflowing of a string buffer, along with the incorrect calculation of the string length. When a criminal is successfully caught, a message is returned to the user along with the number of moves it took to catch the criminal. The buffer that holds the message can be overflown when the number of moves is greater that 6 digits or 100,000. By overflowing the buffer, the subsequent strlen call will read into the next buffer. This excessive length calculation will lead to leaking the memory from the adjacent buffer, which contains a hexadecimal encoding of the flag. 

### Generic class of vulnerability

Improper Null Termination
Out-of-bounds Read

### CWE classification

CWE-170: Improper Null Termination
CWE-125: Out-of-bounds Read

### Challenges
1. To reach the code that sends the "caught message" the user must be able to catch the criminal. Catching the criminal requires an understanding of
a) How moves impact the criminal's position
b) How the criminal chooses moves based on the map values
c) How the map is created and the values in each location
d) The conditions that must be satisfied for the criminal to be "caught"
d) What moves will successfully to "catch" the criminal

2. To overflow the buffer the user must create a series of moves that allows the criminal to evade capture for at least 100,000 moves and then be caught without the criminal moving into a coordinate that allows the criminal to "get away".

3. Proper decoding of the flag values from a hexadecimal string into a binary value.

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy

