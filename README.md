# DARPA Challenge Binaries on Linux, OS X, and Windows

[![Build Status](https://travis-ci.org/trailofbits/cb-multios.svg?branch=master)](https://travis-ci.org/trailofbits/cb-multios)
[![Build status](https://ci.appveyor.com/api/projects/status/l17viygqmgb404oe/branch/master?svg=true)](https://ci.appveyor.com/project/dguido/cb-multios/branch/master)
[![Slack Status](https://empireslacking.herokuapp.com/badge.svg)](https://empireslacking.herokuapp.com)

The DARPA Challenge Binaries (CBs) are custom-made programs specifically designed to contain vulnerabilities that represent a wide variety of crashing software flaws. They are more than simple test cases, they approximate real software with enough complexity to stress both manual and automated vulnerability discovery. The CBs come with extensive functionality tests, triggers for introduced bugs, patches, and performance monitoring tools, enabling benchmarking of patching tools and bug mitigation strategies.

The CBs were originally developed for DECREE -- a custom Linux-derived operating system that has no signals, no shared memory, no threads, no standard libc runtime, and only seven system calls -- making them incompatible with most existing analysis tools. In this repository, we have modified the CBs to work on Linux and OS X by replacing the build system and re-implementing CGC system calls via standard libc functionality and native operating system semantics. Scripts have been provided that help modify the CBs to support other operating systems.

The CBs are the best available benchmark to evaluate program analysis tools. Using them, it is possible to make comparisons such as:

* How good are tools from the Cyber Grand Challenge vs. existing program analysis and bug finding tools?
* When a new tool is released, how does it stack up against the current best?
* Do static analysis tools that work with source code find more bugs than dynamic analysis tools that work with binaries?
* Are tools written for Mac OS X better than tools written for Linux, and are they better than tools written for Windows?

## Components

### challenges
This directory contains all of the source code for the challenge binaries. Challenges that are not building or are not yet supported are in the `disabled-challenges` directory.

### include
This directory contains `libcgc`, which implements the syscalls to work on non-DECREE systems. `libcgc` currently works on OS X and Linux.

### tools
This folder contains Python scripts that help with modifying, building, and testing the original challenges.

#### tester.py
This is a helper script to test all challenges using `cb-test`. Results are summarized and can be output to an excel spreadsheet. More details in the [testing section](#testing) below.

## Building

The following steps will build both the patched and unpatched binaries in `build/challenges/[challenge]/`.

### OS X/Linux

The following packages are required for building the challenges on Linux:

```
libc6-dev
libc6-dev-i386
gcc-multilib
g++-multilib
clang-3.8 (or higher)
```

To build all challenges, run:

```bash
$ ./build.sh
```

### Windows

The following packages are required for building the challenges on Windows:

|Name                             |  Version/Info                       |
|---------------------------------|-------------------------------------|
| Visual Studio Build Tools       | included in Visual Studio           |
| Windows SDK (for running tests) | optional install with Visual Studio |
| CMake                           | 3.1+                                |
| Clang                           | 3.8+                                |

**Note:** depending on where you clone the repo, you may run into build errors about the path being too long. It's best to clone the repo closer to your root directory, e.g. `C:\cb-multios\`

To build all challenges, run:

```
> powershell .\build.ps1
```

## Testing

The `tester.py` utility is a wrapper around `cb-test` that can be used to test challenges and summarize results. The [`cb-test`](https://github.com/CyberGrandChallenge/cb-testing) tool is a testing utility created for the DARPA Cyber Grand Challenge to verify CBs are fully functional.

`cb-test` has been modified to run tests locally with no networking involved. All changes include:

* The removal of any kind of server for launching challenges
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

The following will run tests against all challenges in `challenges` and save the results to `out.xlsx`:

```bash
$ ./tester.py -a -o out.xlsx
```

To run tests against only two challenges, do this:

```bash
$ ./tester.py -c Palindrome basic_messaging
```

To test all POVs and save the results, run:

```bash
$ ./tester.py -a --povs -o out.xlsx
```

### Types of Tests

All tests are a series of input strings and expected output for a challenge. There are two types of tests that are used:

`POV (Proof of Vulnerability)`: These tests are intended to exploit any vulnerabilities that exist in a challenge. They are expected to pass with the patched versions of the challenges, and in many cases cause the unpatched version to crash.

`POLL`: These tests are used to check that a challenge is functioning correctly, and are expected to pass with both the unpatched and patched versions of challenges.

### Type 1 POV notice

Verifying type 1 POVs relies on analyzing the core dump generated when a process crashes. They can be enabled with:

###### OS X:
```bash
$ sudo sysctl -w kern.coredump=1
```

###### Linux:
```bash
$ ulimit -c unlimited
```

###### Windows:
Merge `tools/win_enable_dumps.reg` into your registry. Note that this will disable the Windows Error Reporting dialog when a program crashes, so it's recommended that you do this in a VM if you want to keep that enabled.

## Current Status

Porting the Challenge Binaries is a work in progress, and the current status of the porting effort is tracked in the following spreadsheet:

https://docs.google.com/spreadsheets/d/1Z2pinCkOqe1exzpvFgwSG2wH3Z09LP9VJk0bm_5jPe4/edit?usp=sharing

## Notes

We use the CMake build system to enable portability across different compilers and operating systems. CMake works across a large matrix of compiler and operating system versions, while providing a consistent interface to check for dependencies and build software projects.

We are working to make this repository easier to use for the evaluation of program analysis tools. If you have questions about the challenge binaries, please [join our Slack](https://empireslacking.herokuapp.com) and we'll be happy to answer them.

## Authors

Porting work was completed by Kareem El-Faramawi and Loren Maggiore, with help from Artem Dinaburg, Peter Goodman, Ryan Stortz, and Jay Little. Challenges were originally created by NARF Industries, Kaprica Security, Chris Eagle, Lunge Technology, Cromulence, West Point Military Academy, Thought Networks, and Air Force Research Labs while under contract for the DARPA Cyber Grand Challenge.
