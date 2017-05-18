# Network_File_System_v3

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a reimplementation of a previous network file system. This version uses C++ and a completely rewritten file system that instead of being inode based uses a database storage backend method consisting of C++ classes and linked lists. All the same features are supported including the ability to login/logout, read/write, open, close, rename, and delete a file. These commands are provided via a custom binary protocol that allows a user to perform these actions against the file system on up to 10 files. Directory support is not supported however read/write permissions and file owner are supported in this service. Entropy from the magic page is added to the service by generating the unix timestamps for file creation via a generator function and magic page data.

### Feature List

This service features a binary protocol with 7 available commands: These are Login, Directory, Read, Write, Write Append, Delete and Rename. These commands operate on a back-end database file system that allows up to 10 maximum files to be written. Each file can be up to 1MB in size. Files are stored in a linked list of nodes. The Login command takes a username and password and allows the user to access the network file system and send the remaining commands. Directory provides a directory listing of files on the file system including name, creation timestamp, file size, owner, and file permissions. Read allows the user to read from a file at a specific offset and length. Write allows a user to write to the file with a specific length (and will create a new file if one does not already exist). Write append allows the user to append data to the end of the file. Delete will delete an existing file and takes a file name. Rename allows the user to rename a file on the file system to a new name.

## Vulnerability

The vulnerability in this service is a type 2 POV out of bounds array access. Due to an unsigned to signed integer conversion error it is possible to cause an array access to occur on an extremely large value. This will result in an integer wrap-around of the array access and allow the user to index memory backwards from the address of the array. It is possible to point the array to a data structure in which a pointer to magic page data is present. Using the Read command and this negative value the user can read page data from the heap back (buffer under read) via the Read command and return the page data in the read response. This allows the user to report it as a type 2 vulnerability.

### Generic class of vulnerability
Vulnerability 1 of 1:
Unsigned to Signed Conversion Error
Accessing array with negative value

### CWE classification
Vulnerability 1 of 1:
CWE-196: Unsigned to Signed Conversion Error
CWE-127: Buffer Under-read

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Easy
Proving: Medium
Fixing: Medium

This CB has a single vulnerability present in it. It is a type 2 vulnerability and discloses magic page data. Due to the nature of the vulnerability it is relatively easy to discover a crashing input by specifying a negative value to the offset 32-bit integer for a Read command. If the value is large enough then the buffer under run reads a value outside of an allocated page resulting in SIGSEGV. The difficulty lies in directing the under read to a specific memory address that leaks page data via a pointer to magic page data on the heap. The user also then has to craft the read length to be sufficiently large that the data returned from the read request leaks enough page data back necessary for a type 2 POV.
