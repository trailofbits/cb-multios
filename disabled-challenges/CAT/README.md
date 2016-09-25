# CAT

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Confident Authentication Terminal (CAT) provides real time RAM access for
remote auditors.  CAT is a client for a fictional CAT protocol designed for use
in regulation-heavy industries, such as the gaming industry, where regulatory
bodies need to be able to query RAM contents on demand.

## Feature List:

CAT provides legitimate mechanisms to (R)ead and (W)rite most of the virtual 
address space, but is not supposed to provide a means to introduce and cause 
execution of externally provided instructions.  In other words, there are 
*many* ways to cause a SIGSEGV, but few ways to do anything useful with it. 

Notably, direct (R)eads to the FLAG page, which simulates protected proprietary information are disallowed.  

## Vulnerability 1

This CB, the CAT client, allows for (W)rites to its .data segment.  This is not specified by the CAT protocol and is, in fact, an implementation error.  This allowance is the basis of the vulnerability.  Patched variants disallow such access and send an error response.  

Absent the ability to (W)rite to the .data segment, it should become infeasible to redirect control flow to unintended locations.

### Generic class of vulnerability
Improper input validation
Improper validation of array index
Information Exposure Through Sent Data

### CWE classification
CWE-20: Improper input validation
CWE-129: Improper validation of array index
CWE-201: Information Exposure Through Sent Data

### Challenges
- While exploiting an arbitrary R/W is expected to be simple, patching an 
	arbitrry R/W that's included by design is a difficult task.  It likely 
	requires inferrence of what the intended behavior should be.  This intent 
	can be inferred from pollers (which never attempt (W)rite to the .data 
	segment).
- One of the protocol handlers is a 65536 case switch statement that returns a 
	random 4B value per case.  This functionality is verified for inclusion by 
	pollers.  This large switch statement causes IDA Pro to punt during some 
	component of disassembly and Hex-Rays decompilation is likely infeasible 
	for any realistic amount of allocated RAM.  That being said, the 
	vulnerability does not reside in this massive function, so this code can 
	remain untouched.  It will be difficult to reason about this code for any 
	competitor that is leveraging IDA Pro.
- Pollers verify the (R)eadability of the expected .text section.  This may 
	complicate some defensive ASLR strategies.  If competitors choose to move 
	e(X)ecutable code from its original location, the original location must 
	still be (R)eadable.

### Difficulty
- Discovering is easy
- Proving Type 1 is easy/medium; Type 2 is medium
- Patching is hard
