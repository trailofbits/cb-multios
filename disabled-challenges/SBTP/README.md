# SBTP

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

SafeTechs realizes that our clients have files worth protecting, but today, there's no good way to transfer files securely and safely.
We're here to help you do it.
After years of work, we have created SBTP, a new way to transfer any data you want, and it will be encrypted, stay encrypted, and well outside the reach of any would-be hackers.
In addition, we've created a Patent-Pending binary verification tool that will ensure you're running the latest, safest version of SBTP.
Today, we've released the beta version of our application, and are offering free accounts on our server for anyone who wants to keep their data safe.

## Feature List:

- Make directories
- List directories
- Add files
- Read files
- Remove files
- Remove directories

## Vulnerability 1

The vulnerability in this CB is loosely based around CVE-2015-0777 in OpenSSH, where a bug in handling reconnections lead to information leakage.
By refraining from sending data for 2 seconds after protocol initiation, it is possible to enter a "reconnection" state with special re-transmission logic.
Due to various failures to sanitize and validate peer provided data, it is possible to map and disclose uninitialized memory, as well as corrupt heap memory.

### Generic Class of Vulnerability

Uninitialized memory disclosure
Improper bounds checking

### CWE Classification
CWE-908: Use of Uninitialized Resource
CWE-125: Out-of-bounds read
CWE-787: Out-of-bounds write

### Challenges
This CB presents a number of rather difficult challenges to would be competitors:

* Vulnerability requires an awareness of timing, as the vulnerable code path will not be triggered unless a timeout occurs.
* The nature of the vulnerability makes useful crashes unlikely during dynamic analysis, further causing problems.
* Poller-verified checksum of the .text section requires competitors to correctly model self-inspecting code when patching.
* Disclosed flag page memory can be obfuscated by built-in "encryption" in the protocol.
* Network analysis is complicated by flag-page based encryption seed.

### Difficulty
* Discovering is hard
* Proving is medium
* Fixing is hard
