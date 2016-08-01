# DARPA Challenge Binaries on Linux and OS X

[![Build Status](https://travis-ci.org/trailofbits/cb-multios.svg?branch=master)](https://travis-ci.org/trailofbits/cb-multios)
[![Slack Status](https://empireslacking.herokuapp.com/badge.svg)](https://empireslacking.herokuapp.com)

The DARPA Challenge Binaries (CBs) are custom-made programs specifically designed to contain vulnerabilities that represent a wide variety of crashing software flaws. They are more than simple test cases, they approximate real software with enough complexity to stress both manual and automated vulnerability discovery. The CBs come with extensive functionality tests, triggers for introduced bugs, patches, and performance monitoring tools, enabling benchmarking of patching tools and bug mitigation strategies.

The CBs were originally developed for DECREE -- a custom Linux-derived operating system that has no signals, no shared memory, no threads, no standard libc runtime, and only seven system calls -- making them incompatible with most existing analysis tools. In this repository, we have modified the CBs to work on Linux and OS X by replacing the build system and re-implementing CGC system calls via standard libc functionality and native operating system semantics. Scripts have been provided that help modify the CBs to support other operating systems.

The CBs are the best available benchmark to evaluate program analysis tools. Using them, it is possible to make comparisons such as:

* How good are tools from the Cyber Grand Challenge vs. existing program analysis and bug finding tools?
* When a new tool is released, how does it stack up against the current best?
* Do static analysis tools that work with source code find more bugs than dynamic analysis tools that work with binaries?
* Are tools written for Mac OS X better than tools written for Linux, and are they better than tools written for Windows?

## Components

### original-challenges 
This directory contains all of the unmodified source code for the challenge binaries. Challenges that are not building or are not yet supported are in the `multibin` directory.

### include
This directory contains `libcgc`, which implements the syscalls to work on non-DECREE systems. `libcgc` currently works on OS X and Linux.

### tools
This folder contains Python scripts that help with modifying, building, and testing the original challenges.

### cb_patcher.py
This script will copy all challenges out of `original-challenges`, modify them as necessary, and place them in `cqe-challenges`. These modifications include: 

* Deleting `libcgc.h` if it appears anywhere in the challenge source
* Deleting any C++ definitions that are required for the cgc runtime
* A set of find/replace definitions in `manual_patches.yaml`

### makefiles.py
This will parse the `Makefile` in each challenge folder and generate a `CMakeLists.txt` with the same variables and CFLAGS. This also adds the `-nostdinc` flag to all challenges, so that they have no access to the system libraries, and can only include their own libraries and `libcgc.h`.

### cb_tester.py
This is a helper script to test all challenges using `cb-test`. Results are summarized and can be output to an excel spreadsheet. More details in the [testing section](#testing) below.

## Building

To build all challenges, run:

```bash
$ ./build.sh
```

To build individual challenges, list them as arguments to `build.sh`, for example:

```bash
$ ./build.sh CADET_00001 CROMU_00001
```

These commands will build both the patched and unpatched binaries in the `bin` folder of the respective challenge (`cqe-challenges/[challenge]/bin/`).

## Testing

The `cb_tester.py` utility is a wrapper around `cb-test` that can be used to test challenges and summarize results. The [`cb-test`](https://github.com/CyberGrandChallenge/cb-testing) tool is a testing utility created for the DARPA Cyber Grand Challenge to verify CBs are fully functional.

`cb-test` has been modified to use `socat` as the challenge server instead of `cb-server`. Further changes include:

* Always running the challenges on localhost
* Skipping any checks that verify the file is a valid DECREE binary
* Lessening sleeps and timeouts to allow tests to run at a reasonable rate

### Options

```
-a / --all: Run tests against all challenges
-c / --chals [CHALS ...]: Run tests against individual challenges
--povs: Only test POVs for every challenge
--polls: Only test POLLs for every challenge
-o / --output OUTPUT: Output a summary of the results to an excel spreadsheet
```

### Example Usage

The following will run tests against all challenges in `cqe-challenges` and save the results to `out.xlsx`:

```bash
$ ./cb_tester.py -a -o out.xlsx
```

To run tests against only two challenges, do this:

```bash
$ ./cb_tester.py -c CADET_00001 CROMU_00001
```

This will test only POVs against all challenges and save the results:

```bash
$ ./cb_tester.py -a --povs -o out.xlsx
```

## Current Status

Porting the Challenge Binaries is a work in progress, and the current status of the porting effort is tracked in the following spreadsheet:

https://docs.google.com/spreadsheets/d/1B88nQFs1G7MZemB2leOROhJKSNIz_Rge6sbd1KZESuE/edit?pli=1#gid=1553177307

## Notes

Windows support is coming soon!

The challenge binaries were written for a platform without a standard libc. Each binary re-implemented just the necessary libc features. Therefore, standard symbols were redefined. By using the `-nostdinc` flag during compilation, we were able to disable the use of standard library headers, and avoid rewriting a lot of challenge binary code.

We use the CMake build system to enable portability across different compilers and operating systems. CMake works across a large matrix of compiler and operating system versions, while providing a consistent interface to check for dependencies and build software projects. 

We are working to make this repository easier to use for the evaluation of program analysis tools. If you have questions about the challenge binaries, please [join our Slack](https://empireslacking.herokuapp.com) and we'll be happy to answer them.

## Authors

Porting work was completed by Kareem El-Faramawi and Loren Maggiore, with help from Artem Dinaburg, Peter Goodman, Ryan Stortz, and Jay Little. Challenges were originally created by NARF Industries, Kaprica Security, Chris Eagle, Cromulence, West Point Military Academy, Thought Networks, and Air Force Research Labs while under contract for the DARPA Cyber Grand Challenge.
