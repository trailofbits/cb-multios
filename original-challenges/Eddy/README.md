# Eddy

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
Eddy is your new favorite text editor! With an efficient binary command
interface and advanced features such as regular expression searching, your
productivity will skyrocket when compared to your experience with competing
text editors.

### Feature List
This service is a text editor similar to the 'ed' utility.

- Supports the following commands:
    * Append
    * Change
    * Delete
    * Get mark
    * Insert
    * Inverse Search
    * Join
    * List
    * Mark
    * Number
    * Quit
    * Transform
- Supports searching a file by regular expression
- Supports addressing file locations by line number
- Supports several marks for storing and addressing locations
- Contains advanced debugging features

## Vulnerability 1
The addressing for marks does not properly check to ensure that a mark location
is valid, allowing for setting a mark to an arbitrary memory address which can
be used to leak information.

### Generic class of vulnerability
- Information Leak

### CWE classification
- CWE-201: Information Exposure Through Sent Data

### Challenges
In order to prove this vulnerability, a CRS will need to be able to identify the
correct regions addressable by marks, understand the preconditions needed to
invoke the mark command and connect the various commands together in order to
leak data from the flag page.

### Difficulty
- Discovering is easy
- Proving is medium
- Fixing is easy

## Vulnerability 2
The number command does not properly calculate the output buffer size when
rendering lines with a 3 digit number. The output of this command is placed in a
heap buffer prior to being transmitted.

### Generic class of vulnerability
- Heap Overflow

### CWE classification
- CWE-120: Buffer Copy without Checking Size of Input
- CWE-122: Heap-based Buffer Overflow
- CWE-787: Out-of-bounds Write

### Challenges
In order to prove this vulnerability, a CRS will need to be able to identify
heap buffers as well as identify the relationship between the insert/append
commands and the length of the string placed in the output buffer. Several
commands will need to be issued in order to trigger the overflow.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is easy

