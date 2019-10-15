# Gridder

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A simple game that sends a user a 81 cell (9x9) grid. Each cell has a value in it 1-9 and must adhere to 3 simple
rules. A cell's value must be unique to its row, column, and 3x3 subgrid the value is contained in. 

### Feature List

The CB stores 0-1 gridders at any given time. A player may:
    -Request a new Gridder
    -Submit a solution to the Gridder
    -Ask for the max/min difficulty settings
    -Give up on a current gridder
    -Change Difficulty

## Vulnerability
### Vuln 1

When sending a gridder solution, the player client first sends an int containting the  number of cells, which should be 81, 
immediately proceeded by 81 32bit ints. The value check casts the integer into a short to conform with the variable (service.cc:170)
storing the board's number of cells. This allows the client to submit a value where if it's mod by the max short = 81
the check will pass. The raw integer is sent to the `recv_board` function and allows the overwrite. The overwrite is limited
to one byte because `recv_board` does a check to ensure the number of bytes read is no more than `G_GRIDDER_SIZE`.
In the unpatched binary, `G_GRIDDER_SIZE` is incorecctly assigned to `(NUM_CELLS + 1) * sizeof(unsigned int);` service.cc:72
This overwrites the pointer to the error table and allows the attacker to arbitrarily read any 4 bytes, as long as they
submit a correctly solved gridder.


#### Generic class of vulnerability

Buffer overflow

#### CWE classification

CWE-681: Incorrect Conversion between Numeric Types
CWE-121 Stack based Buffer Overflow

#### Challenges

 - The CB implements a simple game that must be properly played in order to enable the type-2 vulnerability. 

#### Difficulty

 - **Discovery**: easy
 - **Proving**: medium
 - **Patching**: easy
