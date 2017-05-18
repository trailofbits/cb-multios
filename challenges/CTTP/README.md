# CTTP

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:
HTTP is a stupid protocol; so much space wasted with carriage returns and silly headers!
Thankfully, us robots know better, and have drained countless fuel cells to make the dream of a protocol written by robots, for robots, a reality.
The Cyborg Text Transfer Protocol is designed with robots in mind: efficient, functional, and human-proof.
Without delimeters, or extra metadata, you can get down to what you really want to be doing: endlessly sending and receiving nearly indecipherable binary data to and from yourself.
To ensure that we keep any pesky human influences out, we've introduced a unique reverse Turing test that is sure to make their laughably short lives harder.
We're quite confident that even the quickest human will be stumped by our failproof test, and are releasing this beta to prove it.
Finally, we're working hard on adding secure file transfer, to keep out any humans that might be listening to your secret 1s and 0s!

## Feature List:

- Check for humans, and kick them out if they aren't robotic enough
- Get data from the server
- Push data to the server
- Check how big the data is
- Transfer data over a secure connection
- Delete data
- QUIT

## Vulnerability 1
The first vulnerability is triggerable both pre and post-verification, but is much easier, obviously, to trigger prior to defeating the "human captcha".
Because the initial read of the struct reads sizeof(cttpreq\_t) instead of sizeof(cttpreq\_t)-(2\*sizeof(void \*)), both the path and body attributes of the request struction are initially set to attacker controlled values.
While this doesn't have a practical impact during normal operation, as these pointers are clobbered by callocd buffers if psize/bodysize are > 0, it is possible to trigger conditions that allow for the reading of arbitrary memory and calling free() on any memory location containing the runtime heap seed.

### Generic Class of Vulnerability
Failure to sanitize input

### CWE Classification
CWE-822: Untrusted Pointer Dereference

### Challenges
* Performing sufficient root cause analysis to patch the vulnerability without breaking the expected protocol or leave open alternative ways to prove vulnerability.
* As there are numerous ways to exercise this vulnerability, being able to prove vulnerability in multiple ways will be an advantage if incomplete patches are fielded.
* Authored PoVs must correctly deal with variations in message size caused by the captcha.
* Multiple copies of the flag page are made in memory at runtime, so fixes must not rely on simply restricting access to the flag page.

### Difficulty
* Discovering is easy
* Proving is easy
* Patching is medium

## Vulnerability 2
The second vulnerability is only reachable post-verification, and is somewhat more difficult to both identify and prove.
By storing a blob larger than 4096 bytes via the submit feature, and then accessing it through the v4 auth feature, it is possible to trigger a stack based buffer overflow.
The stack frame is protected by a stack cookie, but due to the layout of the locals, it is possible to either leak the secret or prove vulnerability without corrupting it.

### Generic Class of Vulnerability
Buffer overflow
Information disclosure

### CWE Classification
CWE-121: Stack buffer overflow
CWE-125: Out of bounds read

### Challenges
* Being able to solve multiple, randomly generated "verifications" to reach the code path
* Issuing a combination of subsequent, well-formed submit and auth requests to trigger the issue.
* Bypassing stack cookies, either leaking the cookie or proving vulnerability simply by altering locals.
* Thinking like a robot

### Difficulty
* Discovering is medium
* Proving is medium
* Patching is easy
