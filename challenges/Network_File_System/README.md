# Network_File_System

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

ShortDescription: A basic network file system

### Feature List

The file system supports these functions: Login, Read, Write, WriteAppend, List, Delete, and Rename.  Reads can be requested with an offset allowing specific sections of a file to be retrieved.  

## Vulnerability

A function called CallocAndRead() is used throughout the CB when new filesystem requests are received.  The function allocates space to hold values from the request and copies those values into the allocated buffers.  In order to avoid unterminated strings, the function adds one to any length value it's passed to ensure there's sufficient space for the terminating null character.  However, a mistake in the function declaration resulted in the length parameter being passed as an unsigned 8-bit integer, rather than something larger.  So, if the function is called with a value of 255, the added byte will overflow the 8-bit integer and cause the resulting calloc'd buffer to be too small for the subsequent read which will lead to a heap overflow.

The malloc library uses a linked list for various size free blocks of memory.  By carefully overflowing the first available block in this list, control over the subsequent 'next' pointers is possible resulting in the ability to write to arbitrary memory locations.

The POV in this CB takes advantage of the Rename function and the above vulnerability to overwrite the stack copies of EBP and EIP for the HandleRequest() function.  Since the vulnerability requires a heap overflow of 255 bytes, quite a bit of the heap is corrupted by the overwrite.  In order to keep the CB functioning sufficiently for the Rename function to work, the exploit must reconstruct portions of the heap with valid values.  For example, since the filesystem also relies on heap memory, the inode structures including filenames and data allocations are stored on the heap.  These are obviously critical to the Rename function's file operations and must be correct for that function to work.

### Generic class of vulnerability

Integer overflow leading to an incorrect buffer allocation size and subsequent heap overflow.

### CWE classification

CWE-131: Incorrect Calculation of Buffer Size
CWE-190: Integer Overflow or Wraparound
CWE-122: Heap-based Buffer Overflow

## Challenges

Due to the required size of the heap overflow, large portions of the heap are overwritten causing issues with the CB's key data structures.  While the vulnerability should be easy to identify and patch, crafting a POV which correctly reconstructs the heap while utilizing the malloc library functions to perform the desired stack overwrites should be challenging for the CRS.

Subjective Quantification:
Discovering - Easy
Proving - Hard
Fixing - Easy
