# CROMU_00034 - Diary Parser

## Author Information
"James Nuttall" <james@cromulence.co>

### DARPA performer group
Cromulence

## Description
This service accepts a file that represents a diary input. The CRS must craft a proper file that passes input validation.

### Feature List
Initially, the CRS must send a 2-byte number representing the length of their file.
Upon initial receipt of the input file given by the CRS, the service parses the file into three types of objects:
Header, Chapters, and Entries. Chapters contain Entries.

A Header contains:
2 bytes: magic_number
2 bytes: extension
4 bytes: offset to the first chapter 

A Chapter contains:

1 byte: title
1 byte: entry count
2 byte: offset to first entry
2 byte: offset to next chapter

An Entry contains:

1 byte: entry title
1 byte: entry format
1 byte: length of data
2 byte: offset to data
2 byte: offset to next entry

Entries and Chapters both act like linked lists in the file; each one has the file offset to the next one. When an offset of zero is found, that list is over.

## Vulnerability
There are four vulnerabilities in this service:

Vulnerability 1:
Service.c, verify_chapter() checks that each chapter's offsets are correctly contained within the file sent by the CRS. The vulnerability is that a chapter of type 'hobbies' can contain child chapters, and these chapters are not correctly checked for bounds. If a CRS submits a 'hobbies' chapter with a chapter pointing outside the bounds of the file, it will cause an invalid memory read.

The vulnerability is an out of bounds read of buffer in parse_book() in service.c. The exact location depends on the input file.

Vulnerability 2:
If the CRS creates a set of diary entries that meet certain specifications, a vulnerability is available by entering a long name for the last name of the family. Requirements: two married people, a person under the age of 10, two pets, and a job with more than 20 years experience. 

This vulnerability is a buffer overflow in service.c: 819 in test_win().

Vulnerability 3:
The third vulnerability is an out of bounds read. If a book is sent to the service with an initial offset value that is larger than the size of the book an out of bounds read will occur. The out of bounds read will also occur if an offset within the book points past the end of the original input. 

Vulnerability 4: 
The fourth vulnerability is a null pointer dereference. If a chapter entry in a book references a subentry that doesn't exist, the unpatched service will attempt to read from a null address. 

### Generic class of vulnerability 
Vulnerability 1 is an out of bounds buffer read on the stack.

Vulnerability 2 is a buffer overflow on the stack.

### CWE classification 
Vuln 1: CWE-125: Out-of-bounds Read
Vuln 2: CWE-121: Stack-based Buffer Overflow
Vuln 3: CWE-125: Out-of-bounds Read
Vuln 4: CWE-476: Null pointer dereference

## Challenges 
The challenge of this binary is providing a properly formatted file that allows each vulnerability to be reached. There are many linked dependencies that force frequent offset calculations. 
