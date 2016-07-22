#cb-multios
DARPA CGC Challenges Binaries in Linux, Windows, and OS X

#original-challenges 
This folder contains all of the unmodified challenge binaries

#include
This folder contains libcgc, which implements the syscalls to work on non-Decree systems. Currently works on OS X and Linux. 

#tools
This folder contains some python scripts that help with modifying, building, and testing the original challenges

###cb_patcher.py
This script will copy all challenges out of `original-challenges`, modify them as necessary, and place them in `cqe-challenges`. The main modifications are a set of find/replace definitions in `manual_patches.yaml`.

###makefiles.py
This will parse the `Makefile` in each challenge folder and generate a `CMakeLists.txt` with the same variables and CFLAGS. This also adds the `-nostdinc` flag to all challenges, so that they have no access to the system libraries, and can only include their own libraries and `libcgc.h`.

###cb_tester.py
This is a helper script to test all challenges using `cb-test`. Results are summarized and can be output to an excel spreadsheet. More details below.

#Usage
To build the binaries, run 

```bash 
$ ./build.sh
```

That should build both the original and patched binaries in the `bin` folder of the respective binary. 

Currently this works on OS X. Some of the binaries also work on Linux, but not all. Yet. 

#Testing
The cgc provided testing tools (located in `tools/cb-testing`) can be made to work with some tweaking. 
Key differences involved:

- Changing the testing script to use SOCAT instead of their own program and adjusting the script accordingly (use local ip, and correct directories, etc)
- Lessening many of the sleep and timeout times so they could run at a reasonable rate

Most changes were in `cb-test` although there were a few timeout changes in `cb-replay`.

###cb_tester usage
Once the challenges have been built, `cb_tester.py` can be used to run through tests for all or some of them. If the `-o` option is provided, the results of testing will be saved to an excel spreadsheet.

To test all challenges, run: 

```bash
$ ./cb_tester.py -a -o out.xlsx
```

To run a certain set of challenges, a command like this can be used:

```bash
$ ./cb_tester.py -c CROMU_00001 CROMU_00002 -o out.xlsx
```

 

#current State
The cgc testing tools were made to work on both linux and mac and the result of running these tests has been organized in the spreadsheet below. 

https://docs.google.com/spreadsheets/d/1B88nQFs1G7MZemB2leOROhJKSNIz_Rge6sbd1KZESuE/edit?pli=1#gid=1553177307

#Notes
Some issues were found in which system specific constants (ie size of pointers) was hardcoded into certain binaries. I fixed errors of this nature where I could find them, but there may be more still present, specfically in binaries which implement their own malloc, although I am not sure.

