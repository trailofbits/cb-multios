# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
Need a quick sorting utility for your massive database of fixed-width records? Use Fables our mythological sorting and reporting tool. There's a moral in their somewhere.


### Feature List
Begin by telling Fables how your data is structured using dummy data separated by delimiters. From there, you can start sending records over to be stored. At any time you can,

a. Generate a Report of all records
b. Generate a Report of all records that a match one or more fields.
c. Sort your data alphabetically by any field you choose. 

## Vulnerability
This service has five vulnerabilities. 

1. The first three are all triggered by an integer overflow related to the size of fields or the size of records. 

a. If the size of records overflows and is negative, then the memory allocation for the 'data' field in the 'record' structure will fail and return NULL. The following memset will fail when trying to access a NULL memory location.

b. If the size of a field overflows so that both the its size and the record's size are positive, but the record's size is less than the field's size, then 'data' buffer in the 'record' structure will be smaller than the amount of data in the receive_buf, causing the following strcpy to overflow the 'data' buffer.

c. If the size of a field is large enough to be negative and the record_size overflows to become positive again, then memory allocation in (a) will succeed, but field_index in newRecord will be negative. When field_index is used to index the 'data' field in the 'record' structure it be accessing memory access outside the bounds of the array. The strcpy will then fail when it attempts to copy data to an invalid memory allocation.

2. The fourth vulnerability is caused by attempting to free in the middle of allocated memory. In the newRecord function, the 'command' variable is set to the last field in the record. If 'command' contains the word "ERROR", then the address it points to is free'd causing the remove function in libc to fail.

3. The fifth vulnerability is caused by sending over 65535 characters without a terminator character, causing an integer overflow and leading to memory corruption.

### Generic class of vulnerability
Heap-based Buffer Overflow
Write-what-where Condition
Integer Overflow or Wraparound
Release of Invalid Pointer or Reference 
Access of Memory Location After End of Buffer


### CWE classification
CWE-122 Heap-based Buffer Overflow
CWE-123 Write-what-where Condition
CWE-190 Integer Overflow or Wraparound
CWE-763 Release of Invalid Pointer or Reference 
CWE-788 Access of Memory Location After End of Buffer


## Challenge
1. Understanding how to control the structure of records in order to cause the various integer overflows that lead to the 5 vulnerabilities above.

2. Identifying the hidden command and properly send a record in order to execute the vulnerable free().

3. Patching the CB with sufficient checks to ensure an integer wrap-around either doesn't occur or doesn't create a vulnerable condition. 
