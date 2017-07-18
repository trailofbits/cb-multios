# CGC Challenge Binary (KPRCA\_00054): FileSys

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Simple shell-like file management system.

### Feature List


```
list [file ..]
 - Lists files and directories.
 
create <filename>
 - Creates a file.
 
open <filename>
 - Opens a file.
 
close <fileno>
 - Closes an open file.
 
close_all
 - Closes all open files.
 
read <fileno> [pos] [len]
 - Reads a file.
 
modify <fileno> [pos]
 - Modifies a file.
 
delete <filename>
 - Deletes a file.
 
mkdir <dirname>
 - Creates a directory.
 
rmdir <dirname>
 - Deletes a directory.
 
chdir <dirname>
 - Changes the working directory.
 
quit
 - Quits the program.
 
help [command]
 - Displays the help message.
 ```
 

## Vulnerability

- When deleting a file, the file object pointer is not removed from the list that keeps track of currently opened files.
- This yields a dangling pointer when a file is deleted while it's opened.
- By allocating similar-sized buffer by writing into another file, it is possible to take over the memory for the dangling pointer -- allowing Use-After-Free condition.
- Arbitrary code execution can be achieved by triggering a virtual function in the file object after carefully setting up the payload.

### Generic class of vulnerability

Use After Free

### CWE classification

CWE-416: Use After Free

## Challenges

- C++
