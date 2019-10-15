# Overflow_Parking

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Flo's Consolidated Parking, Inc is proud to announce the release of our new parking management software, OVERFLOWPARKING.
With this new technology, we wirelessly and automatically manage our vast network of parking lots, and for a nominal fee, you can too!
Complete with violation monitoring and monthly summarized reporting, you can quickly and easily start and run your own parking empire.

### Feature List

Add money to meters.
Assign parking tickets.
Create wealth.
We promise our software can do at least two of these three things!

## Vulnerability

As the name suggests, the vulnerability in this CB is a simple integer overflow vulnerability, leading to heap corruption. This overflow is present in the malloc implementation used by the CB, and by utilizing the full control given over an allocation during processing, it is possible to trigger an allocation smaller than the size of the intended buffer.

### Generic class of vulnerability

Integer overflow

### CWE classification

CWE-190

### Challenges

Firstly, this CB contains *many* integer overflows, the vast majority of which are unimportant, and even in some instances required behavior exercised by the pollers. Systems attempting to explore or patch all of these overflows will likely encounter difficulty attempting to address them all, making techniques similar to -fsanitize=integer problematic.

Secondly, the vulnerability is contained within a standard library function rather than a non-standard function. While this may make patching easier, as some teams may replace malloc altogether, it will make root cause analysis more difficult. 

Thirdly, the protocol this CB uses is a mixture of line-delimited and length:data formats, which can confuse protocol reconstruction attempts.

Finally, proving vulnerability via heap corruption is a non-trivial task, even for humans. Leveraging the somewhat narrow constraints available to achieve a write-what-where primitive, and using that to gain code execution, will likely prove quite challenging for an autonomous system.

### Difficulty
- Discovering is medium
- Proving is hard
- Patching is easy
