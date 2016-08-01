# DARPA Challenge Binaries in Linux and OS X

[![Slack Status](https://empireslacking.herokuapp.com/badge.svg)](https://empireslacking.herokuapp.com)

These programs (CBs) were specifically designed with vulnerabilities that represent a wide variety of software flaws. They are more than simple test cases, they approximate real software with enough complexity to stress both manual and automated vulnerability discovery.

The CBs are the best available benchmark to evaluate program analysis tools. Using them, it is possible to make comparisons such as:

* How good are tools from the Cyber Grand Challenge vs. existing program analysis and bug finding tools
* When a new tool is released, how does it stack up against the current best?
* Do static analysis tools that work with source code find more bugs than dynamic analysis tools that work with binaries?
* Are tools written for Mac OS X better than tools written for Linux, and are they better than tools written for Windows?

Windows support coming soon!

## Building

To build all challenges, run:

```bash
$ ./build.sh
```

To build individual challenges, list them as arguments to `build.sh`, for example:

```bash
$ ./build.sh CADET_00001 CROMU_00001
```

These commands will build both the patched and unpatched versions of the challenges.

## Testing

`cb_tester.py` is a wrapper around `cb-test` that can be used to test challenges and summarize results.

### Options

```
-a / --all: Run tests against all challenges
-c / --chals [CHALS ...]: Run tests against individual challenges
--povs: Only test POVs for every challenge
--polls: Only test POLLs for every challenge
-o / --output OUTPUT: Output a summary of the results to an excel spreadsheet
```

### Example Usages

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

## Porting Notes

The challenge binaries were written for a platform without a standard libc. Each binary re-implemented just the necessary libc features. Therefore, standard symbols were redefined. By using the `-nostdinc` flag during compilation, we were able to disable the use of standard library headers, and avoid rewriting a lot of challenge binary code.

We are working to make the use of this repository easier to understand and use for the evaluation of tools. If you have questions about the challenge binaries, please [join our Slack](https://empireslacking.herokuapp.com) and we'll be happy to answer any of your questions.
