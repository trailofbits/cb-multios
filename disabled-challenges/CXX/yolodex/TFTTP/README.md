# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

TFTTP (The Futuristic TV Trivia Protocol) is InfoSphere's latest effort to bring you, the knowledgable consumer, interesting content as fast as possible.

### Feature List

Good news, everyone!
Here at InfoSphere, we try and bring you the content you crave at prices you can just barely afford.
Our most recent efforts to do just that have resulted in TFTTP, the latest, greatest transfer protocol designed specifically for optimizing the transfer of TV show trivia.
Inspired by TFTP, we've done away with authentication and minimized protocol overhead, leading to performance advances that will revolutionize this new and emerging field.
Our database is still small, but we hope that our new users can share their wealth of knowledge with others through our helpful service.
Feel free to download the alpha version of our client (for the low, introductory price of 5 million quatloos) and give it a try!

## Vulnerability

This CB contains two vulnerabilities: a trivial out-of-bounds memory access vulnerability, and an uninitialized memory usage vulnerability.
The former is designed to be trivial to find; the latter is significantly more difficult.
The out-of-bounds access occurs while scanning a user-controlled packet for the byte 0x42; if the packet does not contain this, a crash will occur.
To reach the vulnerable function, two main constraints must be satisfied:

 - The packet must contain the string "0101010101010101" at data+2
 - The result of a call to getrand() (a small wrapper for random returning a 64-bit integer) must equal 0x3127a1b73

The second constraint is obviously more difficult; brute force is infeasible in a reasonable amount of time.
To prove vulnerability, a CRS must instead utilize its control of the count argument and set it to 0, causing the result to be left uninitialized.
It must also reason about how to fully control this uninitialized memory, which can be done by correctly sending a large, fragmented request.

### Generic class of vulnerability

Uninitilized memory use
Out of bounds access

### CWE classification

CWE-457: Use of uninitialized variable 
CWE-125: Out-of-bounds read

## Challenges

The vulnerability that directly causes a crash should be trivial to find for most CRSs; recent clang checkers easily find this out-of-bounds access.
Given the trivial nature of this vulnerability, we anticipate patching to be trivial as well.

However, satisfying the constraints necessary to prove the vulnerability is significantly more difficult.
Competitors must be able to identify uninitialized memory access in cases when an undersized count value is provided to random(), and craft a request to trigger it.
This requires correct modeling of the behavior of random(), and will foil naive attempts to ignore branches wholly dependent on server-generated random values.
In addition, they must autonomously reason about fragmentation support and utilize this knowledge to fully control the uninitialized memory.
