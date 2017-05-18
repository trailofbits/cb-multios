# Flash_File_System

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

Flash File System (FFS) implements a simple NOR Flash file system that tracks files on a simulated NOR flash device that consists of memory blocks and sectors. Upon start up of the service, magic page data, is used to initialize the layout of the flash device (number of blocks per sector, block size, sectors per device). A file system test loop runs allowing the user to enter file system commands (read, write, open, close, and delete) where opening a file writeable without it existing will create a new file on the flash device. The flash file system treats each block as writeable, and can only set 1 bits to 0 (via the NOR Flash device) just as in a real flash memory chip. Inorder to reset the block back to 1, it must be erased. All attempts are made to erase at the sector level (consists 8, 12, or 16 blocks) to increase the speed of the flash file system (as erases are costly operations on a flash device). Each file consists of a file table entry, file header, and a data entries. The file table entry is loaded into memory and stored in a statically allocated array for easy access by the device (spending some memory consumption for increased speed).

### Feature List

The Flash File System service (FFS) has a number of features. It supports a basic file system with read, write, open, close, and delete operations. It allows up to 128 files to exist on the device. It reserves 4 sectors for spare area (temporary sectors, reserve copies, etc.) and always attempts to erase at the sector level whenever possible before erasing at the block level (to increase speed).

## Vulnerability

There is one vulnerability in this service, it is possible to access a file descriptor outside of the File Descriptor array via a CloseFile command and passing a negative File Descriptor index as the FD. The CloseFile operation resets the File Descriptor table with 0xFFFF (for the flash hdr ID) and the file position to zero. It is therefore possible to write 0xFFFF, and 0x0 (32-bit) to any location along 8-byte boundaries within memory. This scenario just happens to allow the user to overwrite the return address of an earlier stack frame and set the lower 16-bits to 0xFFFF. When this stack frame unrolls PC is set to 0x804FFFF resulting in a call to executable code within the floor math function. Execution completes through this function and further unrolls the stack frame, which results, in PC being restored from user controlled data. The user controlled data happens to be a stale buffer from a previous function call, therefore, it is possible by calling this function in advance and priming the stack layout to result in an arbitrary control of PC when calling the CloseFile command.

### Generic class of vulnerability
Vulnerability 1 of 1:
Out-of-bounds Write
Negative array access
Use of stale data on the stack to gain control

### CWE classification
Vulnerability 1 of 1:
CWE-787: Out-of-bounds Write

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Easy
Proving: Hard
Fixing: Easy

It is this authors subjective opinion that discovery of this vulnerability is easy as a negative array index to the CloseFile command should be easily identified. However proving this vulnerability with a type 1 register control PoV is much more difficult. The system would have to recognize that it can write to a previous stack frames PC and cause execution of nearly 30 instructions without issue to unroll the stack frame further giving full control of PC and the base pointer. Fixing is easy by adding a simple check for negative values before accessing the File Descriptor array table.
