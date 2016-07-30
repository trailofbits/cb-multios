# cb-multios

DARPA CGC Challenges Binaries in Linux, Windows, and OS X

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

