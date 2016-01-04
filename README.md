#cb-multios
DARPA CGC Challenges Binaries in Linux, Windows, and OS X

#cqe-challenges 
This folder contains all of the challenge binaries with CMakeLists.txt in their folders

#include
This folder contains libcgc, which implements the syscalls to work on non-Decree systems. Currently works on OS X and Linux. 

#tools
This folder contains some python scripts I wrote to aid in the process of porting the challenge binaries
makefiles.py initally generated CMakeLists.txt files for each challenge binary in a specified folder, using the makefile they already have. However many of these makefiles have been changed since to fix bugs in the binaries, and should not be used. Provided for reference. 

cgc_replacer.py takes command line arguments and replaces them in all files in a specified folder with "cgc_" + original argument
Used for naming conflicts, such as when a binary defines their own memcpy or write
usage: python cgc_replacer.py memcpy 

This folder also contains testing helper scripts (more detail below)

#usage
To build the binaries, run "cmake ." and then "make" 
That should build both the original and patched binaries in the bin folder of the respective binary. 

Currently this works on OS X. Some of the binaries also work on Linux, but not all. Yet. 

#testing
The cgc provided testing tools can be made to work with some tweaking. 
Key differences involved:
	Changing the testing script to use SOCAT instead of their own program and adjusting the script accordingly (use local ip, and correct directories, etc)
	Lessening many of the sleep and timeout times so they could run at a reasonable rate

Most changes were in cb-test although there were a few timeout changes in cb-replay. 
I wrote a helper script (cb_wrapper) that handled calling the cb-test script with the appropriate params and saving the testing output to a file. cb-wrapper loops through and tests every single challenge binary, patched and unpatched, against every POV. 
For single testing, I wrote another helper script (cb-runOne) that runs a single binary with a single POV. 

Both files are included under tools, but must be placed in cb-testing to actually work. 

#current State
The cgc testing tools were made to work on both linux and mac and the result of running these tests has been organized in the spreadsheet below. 

https://docs.google.com/spreadsheets/d/1B88nQFs1G7MZemB2leOROhJKSNIz_Rge6sbd1KZESuE/edit?pli=1#gid=1553177307

#Notes
Some issues were found in which system specific constants (ie size of pointers) was hardcoded into certain binaries. I fixed errors of this nature where I could find them, but there may be more still present, specfically in binaries which implement their own malloc, although I am not sure.

