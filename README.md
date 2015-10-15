#cb-multios
DARPA CGC Challenges Binaries in Linux, Windows, and OS X

#cqe-challenges 
This folder contains all of the challenge binaries that currently work on OS X, with CMakeLists.txt in their folders

#include
This folder contains libcgc, which implements the syscalls to work on non-Decree systems. Currently works on OS X and Linux. 

#tools
This folder contains some python scripts I wrote to aid in the process of porting the challenge binaries
makefiles.py generates CMakeLists.txt files for each challenge binary in a specified folder, using the makefile they already have

cgc_replacer.py takes command line arguments and replaces them in all files in a specified folder with "cgc_" + original argument
Used for naming conflicts, such as when a binary defines their own memcpy
usage: python cgc_replacer.py memcpy 

#Usage
To build the binaries, run "cmake ." and then "make" 
That should build both the original and patched binaries in the bin folder of the respective binary. 

Currently this works on OS X. Some of the binaries also work on Linux, but not all. Yet. 
