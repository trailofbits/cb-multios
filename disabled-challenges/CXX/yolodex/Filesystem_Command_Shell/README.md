# Filesystem_Command_Shell

## Author Information

"Steve Wood" <swood@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service implements a command line shell-like interface to an underlying filesystem--providing highlevel commands that encapsulate the lower level API calls of the filesystem.

### Feature List
The filesystem supports "regular" files, and files mapped to a malloc'ed memory region.  Commands are provided to create these files, read and write to them, copy them, and finally to erase them.  In addition, the filesystem supports file ownership and "others" permissions so that access to individual files can be restricted or shared as the file owner desires.  When started, the shell presents with a login prompt that uses data from the magic page for authentication information.  However, the shell does allow for "guest" access using a built-in account with hardcoded credentials.


## Vulnerability
The filesystem allocates one "block" of space to a file directory.  As the block size is decided when the filesystem is initialized, the maximum number of directory entries is variable and is calculated during the initialization.  In one calculation used to calculate the maximum number of files, the programmer forgets to subtract static overhead data from the total before dividing by the size of a directory entry, resulting in an off-by-one error on the maximum count.  If this maximum number of files is created, the last one will overflow into the next block of storage space--overwriting up to 8 bytes of data there.  

### Generic class of vulnerability
Off By One

### CWE classification
CWE-193 Off By One

## Challenges
For the initial startup condition of this service, the block that can be overwritten is already allocated to a file created during initialization of the system.  The block overwritten is essentially its "i-node" block, which has a list of the blocks containing the files data.  Overwriting this data will most likely result in a crash and the read of some other service memory area, but not the magic page.  Any attempt to write to this file will cause the file to be truncated to zero length first, clearing and releasing this corrupt block.  

To successfully exploit this vulnerability, the exiting file using that block must be deleted and a file of the memory mapped type must be created first.  For this file type, these overwritten block does not contain pointers to other blocks containing data, but instead holds the pointer and length of the memory malloc'ed for this file.  By manipulating the filename used in the final file creation that overflows the directory, the pointer in this block can be overwritten to point to the magic page.  The amount of program understanding required to successfully exploit this vulnerability makes this one difficult.

	Finding Vulnerability 1: easy
	Proving Vulnerability 1: hard
	Fixing Vulnerability 1: easy 

