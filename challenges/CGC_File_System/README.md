# CGC File System

## Author Information

"John Berry" <hj@cromulence.co>

### DARPA performer group
Cromulence

## Description

Server similar to FTP.

### Feature List


SEND <1 byte name length> <name> <2 bytes file size> <file>
    Maximum length that can be sent is 0x400
    This is how a user can send a new file to the server.
    The name must be the full path

NDIR <1 byte name length> <name>
    Create a new directory under root

RECV <1 byte name length> <name>
    Retrieve a file from under root.
    This must be the full path

STOP
    Terminate the session
    
PRNT 
    List files and type/length
    
REPO <1 byte name length> <name>
    Removes the file specified by name.
    Does not remove directories.


## Vulnerability

When the PRNT command is called the files are bubble sorted by name and any gaps due to files being deleted are filled in. However, the file count is not updated when a file is deleted which allows the PRNT command to later access beyond the valid list of files.

### Generic class of vulnerability

Insufficent bounds checking of an array.

### CWE classification

CWE-125 Out-of-bounds Read

## Challenges
The tool authors must deal with the difficulties of bubble sort as well as combine the PRNT command with a prior use of the REPO command.
