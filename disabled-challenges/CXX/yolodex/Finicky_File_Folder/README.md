# Finicky_File_Folder

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A interface for storing files in a tree-like structure.

### Feature List

This service exposes an API for storing files. The API features the following
fantastic functions.

 * create - Add a file to the tree. Path components are separated by the '/' character
 * unlink - Remove a file from the tree.
 * read - Read from a file handle.
 * lseek - Set the offset for a file handle.
 * close - Remove a file handle.
 * open - Create a file handle for the file at a specific path.
 * write - Write to a file handle.

## Vulnerability
### Vuln 1

When an user asks to open a file via the API, the API hands them back a number
that corresponds to a FileHandle. Ideally, a File can only be deleted if there
are no more FileHandles referencing it. However, in this service it is possible
to delete a file while 1 FileHandle still references it.  This results in that
singular FileHandle containing a dangling pointer to an area of memory that has
been freed. Through the correct allocation patterns, it is possible for a user
to then gain full write access to this region of memory. This, combined with
the fact that the File object is a C++ class with virtual functions, allows for
the user gain EIP control resulting in a type 1 vulnerability.

#### Generic class of vulnerability

Heap Corruption

#### CWE classification

 * CWE-416: Use After Free
 * CWE-825: Expired Pointer Dereference

#### Challenges

 - The interaction with the service that results in a dangling pointer via the
   FileHandle, while short, is somewhat nuanced. So whatever reasoning
   strategies a CRS is utilizing will need to be moderately intelligent.

 - Furthermore, the allocation pattern that allows for easy writing to the region of memory
   referenced by dangling pointer is also non-trivial to derive. That is, many
   other interactions with the API will result in the dangling pointer pointing
   to region of memory that the CRS cannot easily control.

#### Difficulty

 - **Discovery**: medium
 - **Proving**: hard
 - **Patching**: easy
