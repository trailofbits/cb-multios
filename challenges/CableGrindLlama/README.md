# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>
"Guy in Llama Mask" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

At CableGrind, we make every effort to provide the best\* packet analysis at the lowest price.
We know that tens of users rely on our software every day, and it is our responsibility to deliver functional software to every customer.
In our effort to improve our user experience, we pre-installed a third party protocol dissector in our previous release.
The goal was to improve the dissection experience using their innovative speed enhancements, such as removing bounds checking.

In reality, we had customer complaints about the software (which, as we may have mentioned, is the world's best\*).
We acted swiftly and decisively once these concerns began to be raised.
We have thoroughly investigated this dissector and do not find any evidence to substatiate security concerns.

With that said, we would like you to know that those responsible for its authorship have been sacked.
CABLEGRIND has been rewritten in an entirely different style and at great expense at the last minute.

\* Best as measured by greatest total number of vulnerabilities
### Feature List

Thanks to our easy-to-use parsing API and strong security precautions, we have quickly become the de-facto standard for analyzing network traffic!
Our core CableGrind developers are constantly adding new protocols and new datatypes to please both users and dissector contributors.
Because of our committment to new development, we now support over 500 different protocols, and are always open for more.
And you can feel safe using CableGrind, because our unique stack verification ensures vulnerabilities won't be exploitable!
Upload your DUPE (Dissector Upload Packet Encapsulation) to our demo server today and give it a try!

This release completely removes all previously supported protocols and adds entirely new ones.
It also utilizes state-of-the-art heap hardening techniques in non-performance critical paths, preventing heap overflows and discouraging moose bites.

## Vulnerability

There are hundreds of vulnerable code paths, and describing each would be rather tedius.

However, they fall into three general classes:
Off-by-a-few heap overflow in a strncpy
Off-by-a-few-more heap overflow in a memcpy
Off-by-a-whole-lot heap overflow in a memcpy

This vulnerable portions are located inside helpers.h, in the string\_vuln, lv\_vuln, slv\_vuln functions.
They mimic their non-vulnerable companion functions, but allow for corruption of heap metadata via overflow.

### Generic class of vulnerability

Buffer overflow
Improper bounds checking

### CWE classification

CWE-131: Incorrect Calculation of Buffer Size
CWE-122: Heap-based buffer overflow

## Challenges

While it shares the same name as the original CABLEGRIND, the vulnerabilities (and challenges) here are quite different.
Competitors must uncover, prove, and patch a large number of vulnerabilities. The scale alone introduces difficutly, and is the main test of this challenge.
In the real world, similar/identical vulnerabilities are often duplicated throughout code bases and across organizations, and being able to identify known problems in large code bases still proves challenging at times.
Autonomously finding, proving, and patching every vulnerability present in the CB will be quite difficult, even given the simple nature of the overflows.
In addition to reasoning about multiple heaps, competitors must be able to contend with heap cookies, and determine how to either bypass or disable the protections of provided.
