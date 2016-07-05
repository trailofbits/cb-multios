# KPRCA-00013

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Accel is a spreadsheet program that enables a user to store information in a table and calculate numerical formulas based on cell data. Similar to other familiar spreadsheet programs, Accel is meant to assist in organizing large amounts of data that have interdependencies. The functions provided will enable a user to complete most simple financial and arithmetic needs.

### Feature List

Command Line Operations:
-------------------------
**Literal Assignment
A0=1
A0=This is a string

**Formula Assignment
A1==SQRT(9)
A2==A1+97
A3==SIN(A2/A1)

Supported String Commands:
----------------------
CLEAR - Clears a cell
Accel:-$ CLEAR A3

REPR - Show the representation of a cell (helpful with formulas)
Accel:-$ REPR A2 --> =A1+97

SHOW - Show the value of a cell, either literal or computer
Accel:-S SHOW A2 --> 100
Accel:-S SHOW A0 --> This is a string

SHOW TABLE - Shows the contents of the entire table
Accel:-S SHOW TABLE

EXIT - Exits the program
Accel:-S EXIT

Supported Functions:
------------------------------------------------
AVG     - Calculate the average of a list
COUNT   - Count the number of items in a list
MAX     - Return the largest value in a list
MEDIAN  - Calculate the median of a list
MIN     - Return the smallest value in a list
STDDEV  - Calculate the standard deviation of a list
ABS     - Return the absolute value of a number
COS     - Calculate the cosine function of a number
LN      - Caclualte the natural log of a number
LOG10   - Calculate a log base 10 of a number
POWER   - Raise a number to a power
SIN     - Calculate the sine function of a number
SQRT    - Take the square root of a number
SUM     - Return the summation of a list

Supported Operators
------------------------------------------------
+   - Addition
*   - Multiplication
/   - Division
-   - Subtraction

## Vulnerability

In infixtorpn (accel.c:453), an attacker supplied string is parsed into its components. Every time a function name is encountered, it is stored in an array and the index (func_idx) is incremented. The check to test if the array needs to be enlarged is off by one, because the index is incremented between the check and the store. This results in an overflow of the heap buffer, which can allow the attacker to control the heap metadata (size) of the next heap block. Attacker control is limited because the memory is initially set to zero and then incremented every time a comma occurs, but an attacker only needs to get the value to greater than 32 or so to cause a segmentation fault. The fault occurs because the free method will try to split the memory even though it has wrong metadata and overwrite pointers on the heap.

Also, there is an uninitialized variable vulnerability in handle_op_median, where sorted variable wasn't initialized before being cleared.

### Generic class of vulnerability

Generic type: Heap-buffer overflow

Uninitialized variable

### CWE classification

CWE-193: Off-by-one Error
CWE-457: Use of Uninitialized Variable

## Challenges

This cb is meant to be difficult to analyze. The program should provide complexities that are will take some work to reason about. The bug is similar, in that it's difficult to detect what is or isn't a heap overflow especially when dealing with an off-by-one error.
