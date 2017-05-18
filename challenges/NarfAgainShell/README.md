# CGC Challenge Binary Template

## Author Information

"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is a shell for administering files on a remote file store. The remote file
system supports multiple users and enforces permissions on files and folders in
the store. There is support for system administrators to schedule periodic jobs
in between IO operations. The filesystem supports reading, writing and deleting
files, along with creating links to other files.

Commands take the form of a 4-byte command identifier, followed by optional
arguments. Commands may produce output, but will always end in a 4-byte success
code, 0 on success or -1 on failure.

### Feature List

The following features are available:
 - Change directory, accepts a name of a directory to move to
 - Read file, accepts a filename and returns the contents of that file
 - Write file, accepts a filename and a size, writes the contents to a file
 - Link files, creates a new file which is a link to another file
 - Remove file, deletes a file from the store

## Vulnerability

The link file function does not properly check permissions of the directory it
is being placed into if the directory is itself a link. This allows an attacker
to place files anywhere in the filesystem through manipulation of symbolic
links. Files placed in the cron.d directory will be periodically executed in the
context of the server, meaning access to this protected directory allows
arbitrary code execution.

Cycles in between links are not properly checked, making it possible to create
an infinite chain of links, causing uncontrolled recursion and eventually stack
overflow.

### Generic class of vulnerability

Link resolution errors
Permission enforcement logic error
Uncontrolled recursion / stack overflow

### CWE classification

CWE-59 Improper link resolution before file access
CWE-61 UNIX symbolic link following
CWE-275 Permission issues
CWE-434 Unrestricted upload of file with dangerous type
CWE-674 Uncontrolled recursion

## Challenges

This CB challenges a CRS's ability to reason over complex data structures and
about privilege levels within a custom application. The VFS data structure is a
complex nested hierarchy, separating files from directories and including the
concept of symbolic links, which are addressed in a way other than pointers to
other files. Understanding this relationship between nodes in the file graph is
challenging due to their representation, but is necessary to trigger both
vulnerabilities contained in this CB. The concept of privilege levels is
contained in many applications, with models such as UNIX DAC permissions being
well-studied. Many applications contain their own concept of privilege which
allows further access to functions and a wider attack surface. Understanding
this concept and the intermediate goal of writing to restricted portions of the
filesystem is also necessary to trigger one of the included vulnerabilities.

