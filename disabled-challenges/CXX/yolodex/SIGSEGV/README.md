# SIGSEGV

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

SafeTechs, the company behind the industry-leading SOMECHECKS integrity-assurance and remote management technology, is proud to announce the most recent addition to their outstanding offerings: SIGSEGV (Secure ICS Governance via Signed Executable Group Validation)
SIGSEGV allows for you to manage your ICS infrastructure in a secure, trusted manner, without sacrificing any capability.

### Feature List

SIGSEGV is a groundbreaking technology that allows companies to easily and securely deploy custom management code across their infrastructure.
Gone are the days where you need to have support accounts with static passwords and backdoor ports simply to maintain support access to networks. 
No more do you need to struggle with slow SSH configurations and tricky Telnet sessions.
SIGSEGV is able to do this securely by utilizing a patent-pending verification algorithm and unique executable format to ensure compatibility across a wide range of ICSs, and with a minimal amount of overhead.
As such, it is extremely easy to integrate into just about any system you can imagine, and provides extremely flexible management capabilities, limited only by what code you decide is allowed to run.


## Vulnerability 1
SIGSEGV contains 2 distinct vulnerabilities, each based on real-world vulnerabilities in widely used data verification systems.

The first is due to "unintentional" dead code, which causes verification to be skipped for all SEG objects after the first two,  leads to the execution of untrusted code.
Due to an extra "goto flail;" line following an if statement, all validation is bypassed for later objects.
By providing two or more valid, trusted SEG objects, followed by a well-formed but untrusted one, it is possible to trigger the vulnerability.
This is intended to closely model CVE-2014-1266 (also known as goto fail).
This will crash in the function call at service.c:88


### Generic class of vulnerability

Weak code validation

### CWE classification

CWE-20:  Improper Input Validation
CWE-347: Improper Verification of Cryptographic Signature
CWE-393: Return of Wrong Status Code
CWE-561: Dead Code

### Challenges

Discovering this bug without any pollers demonstrating how to send multiple valid SEG files will likely prove to be challenging to some competitors.
Additionally, correctly patching the vulnerability without hindering legitimate code from running (and thereby breaking the pollers) will be quite hard.
Finally, there are a number of interesting tricks that could be performed because successful PoVs will be able to introduce new, arbitrary system code.
Competitors who can take advantage of this will be rewarded.

### Difficulty
- Discovering is medium
- Proving is easy
- Patching is difficult

## Vulnerability 2
Improper use of strncmp function leads to incomplete verification of hash, allowing for the execution of untrusted code.
Due to the use of strncmp, and the presence of a NULL character in the second byte of one of the trusted hashes, it is possible to discover a collision and load untrusted code.
This vulnerability was inspired by an almost identical vulnerability in the code signing used by Wii game systems.
This will crash in the function call at service.c:88

### Generic class of vulnerability

Weak code validation

### CWE classification

CWE-20:  Improper Input Validation
CWE-187: Partial Comparison
CWE-347: Improper Verification of Cryptographic Signature

## Challenges

This bug presents many of the same challenges as the other vulnerability: difficult to find, difficult to patch, and has an large array of different ways that one could utilize it.
This particular bug will likely be even more difficulty to prove, however, as it requires a non-zero amount of intelligence and processing power to generate a PoV that takes advantage of the strncmp comparison shortcut autonomously.
It is not unlikely that a competitor may discover a crash, but generating a useful one is an entirely different matter.

Additionally, while the fix may appear obvious to a human observer (replacing strncmp with memcmp), these "simple fixes" require an understanding of the code and pollers that stretches current technology..
If a CRS was able to formulate a patch like this, it would represent an impressive capability.

### Difficulty
- Discovering is medium
- Proving is hard
- Patching is difficult
