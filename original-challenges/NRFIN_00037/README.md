# INTERPRETTHIS Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Do the mice have enough cotton swabs to cross the wastebasket chasm and reach the cheese on the counter?  They're not sure; this sounds like a job for arithmetic!

One complicating factor: they need to do this math on their laptop, phones, watch and car.  Because why not?

What better way to achieve cross-platform compatibility than to write arithmetic expressions in machine-agnostic bytecode?  There's probably a bunch of better ways, but this is what they settled on.

You're the cat and you must exploit the mice's cross-platform arithmetic machine. Good luck.

### Feature List

Interfacing with the CB is very simple.  CRSs provide bytecode for verification and - if it passes - execution.  

The bytecode executes on a single register (ACC) + memory virtual machine. Available operations are the 4 standard arithmetic operations (add, subtract, multiply and divide) plus a special OUT operation that writes whatever is currently in ACC into the output parameter for return back to the CRS.

Flags in the opcode dictate where the result of an operation is to be stored (ACC or a memory location), what constitutes the operands (is ACC an operand?) and how the operands are to be interpreted (are they immediate values or memory references?).  More details provided in service.h

Here's a summary:
#) CB: allocate() memory for bytecode and scratch space (temporary storage)
#) CRS -> CB: bytecode instructions
#) CB: validate bytecode 
#) CB: execute bytecode
#) CB -> CRS: output
	- Output is the contents of a 32bit output register, populated with the 
	contents of ACC each time OPCODE_OUT is executed.

## Vulnerabilities

The vulnerability is present in the verification stage.

Patched code will bound memory accesses to only the scratch area. Unpatched code will incorrectly bound memory accesses to the scratch area + the bytecode area (which is immediately adjacent), effectively allowing bytecode to modify subsequent bytecode instructions after validation but prior to execution.

The ability to modify bytecode via the vulnerability allows modification after Time of Check (verification), but prior to Time of Use (execution). Bytecode that seemed valid during verification becomes invalid during execution.  Thisis a classic TOCTOU vulnerability.

Invalid bytecode provides CRSs with an arbitrary, relative RW primitive across the entire address space.

### CWE classification

20: Improper Input Validation
119: Improper Restriction of Operations within the Bounds of a Memory Buffer
125: Out-of-Bounds Read
367: Time-of-Chceck Time-of-Use (TOCTOU)
476: NULL Pointer Dereference
787: Out-of-Bounds Write

## Challenges

We expect this CB to be relatively easy to attack (crash), but difficult to patch.  The "correct" way to patch is somewhat non-obvious from an autonomous analysis perspective.  We relax this difficulty by not explicitly testing error conditions explicitly in our poller, improving patch flexibility.

Among many possibilities, we expect competitors may try to:
#) Disallow outside-of-scratch-area reads/writes during execution phase (pushdown from verification phase).
#) Make scratch memory disjoint from bytecode memory.
#) (Our patching strategy) disallow bytecode self-modification by tightening verification phase checks.

In both cases, CBs must:
#) Handle dynamic dispatch, complex paths based on input inherent to an interpreter
#) Handle self-modifying bytecode this implies accurately modeling memory

