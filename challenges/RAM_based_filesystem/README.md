# CROMU-00009: RAM-based filesystem

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description
This service implements a RAM-based filesystem and provides a simple shell 
to interact with the filesystem.  

### Feature List
The shell supports the creation and deletion of folders.  It allows for files
with both printable and non-printable data to be created, appended to, and deleted. 
It also provides basic directory listing and filesystem utilization reporting commands.

The filesystem is defined by a superblock which contains a list of pointers
to inode pages.  The inodes on these pages can point to directories or files
made up of blocks.  The block size is 512 bytes.  

## Vulnerability
The directories of the filesystem were designed to support up to 128 subdirectories
or files.  An overflow exists in the directory creation function which allows
129 entries to be written.  Because the last entry overflows into another
block of data, it is possible to craft a proof of vulnerability to gain control over 
an inode definition and the data blocks to which that inode points.  With control 
over those data block pointers, arbitrary writes are possible.

The second vulnerability is due to a NULL pointer dref when indexing file system blocks.

### Generic class of vulnerability
Incorrect array bounds check leading to buffer overflow and arbitrary writes.

### CWE classification
CWE-787: Out-of-bounds Write
CWE-476: NULL Pointer Dereference

## Challenges
After gaining an understanding of the data structures which make up the filesystem,
the CGC competitor will need to identify the specific array bounds check overflow 
and mitigate that bug.
