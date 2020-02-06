# CGC Challenge Binary 00038 - String Storage and Retrieval

## Author Information

Steve Wood <swood@cromulence.co>

### DARPA performer group

Cromulence

## Description

The program is an utility that parses a metadata format used with various types of media.  The utility simply displays the contents of the metadata to STDOUT.

### Feature List

The utility dynamically parses the metadata format as there are no mandatory data tags and additional tags can be added as needed.  If the utility does not understand a particular tag type, the raw data for the tag is displayed.  

## Vulnerability

The utility has three vulnerabilities.  The first is related to a function pointer that is initialized to handle byte swapping functionality depending upon if the metadata is stored in little endian or big endian format in accordance with a value stored in the metadata itself.  The vulnerability is that the utility assumes only a valid flag is passed in via the metadata.  If one of the two valid values isn't passed in, the function pointer is uninitialized and crashes the application upon the first attempt to call the routine.

The second vulnerability is found in a routine that outputs an embedded string in the metadata pointed to by an offset embedded in the data.  The offset is not properly sanity checked and an out of range value will cause the application to crash.

The third vulnerability is an overflow in the way the CB handles vsprintf. If the resulting buffer is greater than 4096 bytes a stacke based buffer overflow will occur.

### Generic class of vulnerability

Vuln 1: Uninitialized pointer
Vuln 2: Out of range pointer
Vuln 3: Stack based buffer overflow

### CWE classification

CWE-824 Access of Uninitialized Pointer
CWE-823 Use of Out-of-Range pointer offset
CWE-120 Buffer copy without checking the size of input

## Challenges







