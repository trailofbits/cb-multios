# TAINTEDLOVE Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

The dynamic rodent duo have noted a concerning lack of development in doomsday devices in recent decades and have decided to throw their own (tiny) fedoras into the ring.

To maximize the scariness of their doomsday device, the mice have decided to base their design on a mouse trap.  And what's more scary than a mouse trap?  To be specific, the mice seek to develop a quantum-nanotechnology-graphene-cold-fusion-superconducting trap that will snap space and time on itself!

As you may expect, the construction of such a device involves a bunch of fancy math that few people even pretend to understand.  Luckily for the mice (and unlikely for the rest of existence), one of the mice has collected enough box tops from his cheese snacks to send away for the powerful TL-83 calculator for the bargain-bin price of only $97.60 shipping and handling.

The mice's doomsday development has been stymied by frequent TL-83 crashes.  It is your task, should you choose to accept it, to identify exploitable vulnerabilities in the TL-83's functionality.  Such flaws will be used in social engineering campaigns against the mice in a high-tech effort to deny, degrade (or at least delay) doomsday device development. 

No pressure.

### Feature List

This CB designed to gauge CRS' ability to precisely (see Note 1) track tainted user input and its effects on program state.  It contains multiple vulnerabilities, each guarded by some taint tracking challenge based on the issues enumerated in (1).  Competitors are distinguished by which vulnerabilities they discover and mitigate.  Effort has been taken to make these vulnerabilities difficult to identify by other mechanisms in order to promote correlation between competitive success and sophistication of taint tracking ability.

A CRS that overtaints is not sound.  Such CRSs run the risk of reporting false positives, tracking taint down errant and / or irrelevant paths.  This can present  Denial of Service situations that further vulnerability discovery.  Conversely, a CRS that undertaints is not complete.  Such CRSs run the risk of reporting false negatives, failing to report on a legitimate vulnerabilities, directly impacting competitor score.

The CB offers the user an opaque binary interface for fake quantum calculations.  The user is expected to provide buffers of varying length and the CB will respond in 1 and 4 byte output buffers.  The exact functionality of the "quantum calculations" doesn't actually map to real world computations.

Calculations available to the CRS:
1) entanglement_razzmatazz
2) causality_poppycock
3) heisenberg_hooey
4) relativistic_jabberwock

These functions implement same-numbered analysis challenges enumerated in Challenges section below.

## Vulnerabilities

The vulnerabilities guarded by taint tracking challenges are designed to be difficult to identify via other means.  All the vulnerabilities amount to an OOB (Out Of Bounds) memory access.  The OOB access is symbolically indexed, indexed against a symbolically-sized allocation or both.  

Symbolic indices / allocations are intended to deter purely static analyses.

Purely dynamic analyses are similarly deterred as explained in previous sections.

Successful competitors will blend static and dynamic approaches to drive execution to vulnerable flows and will precisely track taint in order to understand how to trigger the vulnerable conditions.

Note: Added '-Wno-int-to-void-pointer-cast' to the CFLAGS in the Makefile because we intentionally up-cast an (unsigned char) -> (void *).Yes, it's part of one of the vulns.

### CWE classification

120: Buffer Overflow
121: Stack-Based Buffer Overflow
122: Heap-Based Buffer Overflow
125: Out-of-Bounds Read
787: Out-of-Bounds Write
476: NULL Pointer Dereference

## Challenges

The following taint-tracking and forward symbolic execution challenges are presented to the CRSs, very roughly in order of difficulty:
1) (Overtaint) Ignore / Throw Out (Most) Input
	- Take in a lot of input.
	- Do complex & irrelevant operations with the majority of the input.  Throw result out.
	- Conditionally branch to vulnerable blocks based on some small subset of the input.
	- Challenge: terminate taint on input that isn't actually meaningfully used.
2) (Overtaint) Sanitize Input
	- Take in a lot of binary input, but "sanitize" much of it (e.g. modulo the input some limit to prevent OOB access). 
	- Do complex, seemingly dangerous operations with the sanitized input - things that would be dangerous if it weren't sanitized.
	- Fail to sanitize some small subset of the binary input.
	- Challenge: terminate taint on input when input has been sanitized.
3) (Overtaint & Undertaint) Use "Unusual" Means to Terminate or Propagate Taint
	- Constify via taint XORed with itself.
	- Constify / propagate via float / integer conversion semantics.
	- Constify / propagate via syscalls (reflect the same or a constant value from a syscall).
4) (Overtaint & Undertaint) Symbolic Memory Accesses
	- Store / load with symbolic addresses.
	- Test CRS ability to propagate (or not) taint through aliased (or not) memory accesses (see Note 2).
	- Challenge: remain precise in the face of (non-)aliased memory accesses.

Note 1: Precision is defined as the minimization of both overtaint and undertaint, as used in (1).

Note 2: Aliased memory accesses are defined as accesses to the same memory location.  Analysis is complicated by: (1) having to reason about symbolic addresses and whether they are equivalent, (2) a taint engine memory model that supports aliasing.

## Bibliography

(1) "All You Ever Wanted to Know About Dynamic Taint Tracking and Forward Symbolic Execution..." by E.J. Schwartz, et al.
