# CGC Challenge Binary (KPRCA\_00041): Differ

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Differ is an application that allows a user to look at two files and determine how they... differ. It was built to be "Slow" by making the diff analysis N^2.

### Feature List

The service allows a user to upload two "Simple" files, or SFILEs. The file header is pretty simple. It has a magic value of "SFP", a few bytes to spcecify the file type (binary or asci), the name of the file (up to 15 characters) and finally the size of file data. 

The user can compare the file, ignore whitespaces or treat a file as text regardless of whether it's specified as binary or ascii.

The program pre processes the entire list, and tries to help the comparison code by creating two hashes for each line as well as a version of the line that has no whitespaces (' ', '\t', '\r'). The program then painfully compares each file line by line and tries to find a best fit for changes. The goal for the "best" fit is to try to prioritize larger groupings of matched text. Because everything is using trees, instead of graphs, it's a weak fitting but good enough.

The final ouptut is a list of lines that differ from one another, as well as the text that has been added, removed, or changed.

## Vulnerability

The vulnerability is based on an "easter egg" embedded in the program. If a user has two files that are identical on every line except the 1^2, 2^2, 3^2......18^2 line, the program outputs an additional output of 
":D=<line contents>"

However. The easter egg does an unsafe strcpy, and potentially allows a user to overflow onto the stack. From here it would be possible to take advantage of the system by overwriting stack variables.

### Generic class of vulnerability

Stack Buffer Overflow

### CWE classification

Stack-based Buffer Overflow (CWE-121)

## Challenges

This service is focused on testing code coverage of input based attacks. The easter egg is slightly contrived, but the hope is that by forcing a file of at least 961 lines, and an input of at least 4096+ bytes on the 961 (vulnerable) line, the goal is to push how effective a competitors's genetic algorithms/code coverage analysis/input generation algorithms/etc characteristics are. 
