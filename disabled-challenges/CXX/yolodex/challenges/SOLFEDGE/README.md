# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

SOLFEDGE is state of the art software used by ARRRRGH, the Academy of Really, Really, Really, Really, Great Harmony, to translate their music between notes and syllables (Solmization).

ARRRRGH teaches their classes in French, so SOFEDGE is designed to use the French 'fixed do' method of solfedge and only recognizes the C major scale.

### Feature List

This service is a translation engine, so it has 2 primary functions:

* It accepts large strings of notes and converts them to syllables.
* It accepts large strings of syllables and converts them to notes.

Valid notes are:
* C
* D
* E
* F
* G
* A
* B

And valid syllables are:
* Ut
* Re
* Mi
* Fa
* Sol
* La
* Si

A single harmony can contain up to 2048 syllables or notes.

## Vulnerability

The buffer that stores syllables is 4096 bytes long. Assuming syllables are 2 bytes, that allows 2048 syllables. The syllable 'sol' is 3 bytes long, while the rest are 2 chars long. So, if the user provides a harmony that contains 2048 notes and one or more of those notes corresponds to the syllable 'sol', then writing those notes as syllables will go beyond the syllables buffer (page) and cause a segfault.

More specifically, in operation.c:process\_notes, the while loop will cause write\_syllable\_to\_buf to write into the syllables\_buf until one of 3 conditions happens. 1) an error is returned, 2) all of the input bytes have been processed, and 3) the total chars written to the syllable buf has reached the MAX\_SYLLABLES\_BYTES. The comparison (total\_bytes\_written < MAX\_SYLLABLES\_BYTES) is a form of an off-by-one error, because each iteration of the loop can write 2 or 3 bytes. So, if total\_bytes\_written is 1 or 2 less than MAX\_SYLLABLES\_BYTES, the loop will run one more iteration. If it is 1 less, that iteration will cause a segfault with both a 2-btye and 3-byte syllable. If it is 2 less, that iteration will cause segfault with a 3-byte syllable.

The segfault will occur in operations.c:write\_syllable\_to\_buf at either line 224 or 227.


There are multiple ways to patch this vuln. The provided PATCHED version uses a more optimal patch that covers both failure conditions. It is also possible to put a much more restrictive bound on total\_bytes\_written (i.e. 100 or 2000), that will prevent the overflow, but will also greatly shorten the possible harmony length.

A more extensive patch, that is unlikely for automated patching is to pass the total\_bytes\_written value into write\_syllable\_to\_buf, and perform a check that can calculate how many more bytes will fit into the buffer before it writes any bytes. It could then return an error value if there are not enough bytes remaining to complete the write.


### Generic class of vulnerability

Improper Input Validation
Improper Validation of Array Index
Off-by-one Error

### CWE classification

Improper Input Validation
CWE-20

Improper Validation of Array Index
CWE-129

Off-by-one Error
CWE-193


## Challenges
* This CB is intentionally on the easier side. A SAT solver should be able to reason about the difference between the syllables' buffer size and the amount of data that can be written to it.
* The way in which a team patches the vuln should indicate if they can reason that both failure points are due to a common cause. If they simply try to patch both failure points separately, they may not have been able to correlate the 2 failure points.
* 
