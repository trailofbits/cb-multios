# CLOUDCOMPUTE

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

Remember: the Cloud is really just someone else's computer.  Why bog down your own computer when you can use someone else's?

Inspired by LANGSEC, the CLOUDCOMPUTE platform offers arbitrary arithmetic computation in a regular expression language!  By limiting the protocol to the regular domain, it becomes possible to write verifiable recognizers for the language, not that we verified our own.

CLOUDCOMPUTE offers up to 20 distinct arithmetic sessions for all 20 of your arithmetic needs! 

Each session has backing memory that contains (1) BASE_ADDR (explained later), (2) an opcode buffer (of varying length), (3) a scratch buffer (256 bytes).  CLOUDCOMPUTE interprets the bytecode in the opcode buffer and works off memory addressed in part by BASE_ADDR and offsets listed in the opcodes.  Under normal conditions, this will cause writes to memory in the session's scratch buffer, which is returned at the end of a session instance.  Under exploitative conditions, these writes will be directed elsewhere.

Each session has it's own memory segment, depicted below:
------------------------------------------------------------------
| session N's BASE_ADDR | N's opcode buffer | N's scratch buffer | 
------------------------------------------------------------------
^ session N's limit - (3 + N + 256)                              ^ -1 byte from the end of session N-1's space
... 
----------------------------------------------------
| 1's BASE_ADDR | 1's opcode buf | 1's scratch buf | 
----------------------------------------------------
^ session 1's limit - (3 + N + 256)                ^ -1 byte from the end of session 0's space
------------------------------------------------------------------------------------
| 0's BASE_ADDR (3 bytes) | 0's opcode buf (N bytes) | 0's scratch buf (256 bytes) |
------------------------------------------------------------------------------------
^ allocate() limit - (3 + N + 256)                                                 ^ top of the allocate() region

Memory notes:
- As the number of sessions grows, the session memory space grows toward lower addresses.
- Opcode buffer sizes are established during session negotiation and are denoted as N in the above.

Sessions are created and used thusly:
- CRS -> CB: 4B MAGIC_NEW_SESSION
- CRS <- CB: 4B (generated) session ID
- CRS -> CB: 4B session ID | 2B session SZ
- CRS -> CB: 4B session ID | opcodes (of length session->sz)
- CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

Existing sessions are interacted with thusly:
- CRS -> CB: 4B (existing) session ID
- CRS <- CB: 4B (reflected) session ID
- CRS -> CB: 4B session ID | opcodes (of length session->sz)
- CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

During session creation / exercise, opcodes are sent to CLOUDCOMPUTE and are written into the corresponding session's opcode buffer.  These opcodes are the portion of the protocol designed to be LANGSEC-compliant (it's a regular language).

The opcode "spec":
form: [operation][\x00][' '][offset][' '][immediate]
smpl: ADD\x00 \xAA \xBB - will add \xBB to the byte in the session's scratch buffer at offset \xAA

Operations:
"NUL": offset = \x00
"SET": offset = immediate
"ADD": offset += immediate
"SUB": offset -= immediate
"MUL": offset *= immediate
"DIV": offset /= immediate
"SHR": offset >>= immediate
"SHR": offset <<= immediate

Operation notes:
- Over/underflows are not handled in any special manner.
- If the immediate to a DIV instruction is 0, offset is assigned \xAA.
- The SHR & SHL instructions are limited to a maximum of an 8 bit shift.  Anything more results in offset = \x00 to avoid ambiguity among architectures.
- The absolute address of the arithmetic instruction is calculated with the current session's BASE_ADDR, the size of the opcode buffer and the offset encoded in the operation.  BASE_ADDR is a 3 byte value that's supposed to (and is assumed to always) hold the most significant 3 bytes of the scratch base address.  This field is critical to the vulnerability included in this CB.  If an attacker is able to control a session's BASE_ADDR field, the attacker can use CLOUDCOMPUTE functionality to perform arbitrary computation on arbitrary memory.

When done computing, CLOUDCOMPUTE will send the scratch buffer back to the client.  The address of the scratch buffer is computed with BASE_ADDR, meaning control of BASE_ADDR confers the ability to leak the flag page.  The scratch buffer is what is verified by the pollers.

## Vulnerability 1

Despite the opcode protocol being LANGSEC compliant, there exists a vulnerability during session establishment / exercise.  

Each step in session negotiation involves sending the session ID.  If the session ID is changed mid-session, CLOUDCOMPUTE becomes confused and copies opcodes into an opcode buffer with wrong session's size.  If this wrong size is larger than the target opcode buffer, a buffer overflow will occur.  Because sessions are immediately adjacent in memory, this overflow confers the ability to control the adjacent session's BASE_ADDR.

As noted before, control of a session's BASE_ADDR allows the attacker to author both Type 1 and Type 2 PoVs.
- Type 1: Control of BASE_ADDR confuses the location of the scratch buffer and therefore which memory is affected by opcodes.  The attacker can use, e.g. the "SET" opcode to write arbitrary bytes over arbitrary memory, allowing for code execution.
- Type 2: Confusion of the scratch buffer location means the wrong memory is returned during the final step of the protocol.  An attacker can control BASE_ADDR to point to the flag page and wait for the CB to send back 256 bytes of the page during the final protocol step.

### CWE classification

CWE-122: Heap-based Buffer Overflow
CWE-843: Access of Resource Using Incompatible Type ('Type Confusion')

CWE-843 doesn't perfectly fit.  The vulnerability will confuse two different sessions, but they are technically the same "type".  I am not aware of a better CWE identifier for this.

### Challenges

- The memory segments devoted to the different sections will likely appear to be an opaque blob with complex operations.  Some CRSs might have difficulty accurately differentiating sessions in memory - a likely first step in determining where things go wrong.
- CLOUDCOMPUTE provides arbitrary arithmetic operations by design.  Determining the memory that the opcodes access is a relatively complex operation.  Naive patching strategies might try to place bounds on memory accesses / operations wholesale, severely reducing performance.  More sophisticated CRSs will need to perform additional root cause analysis to avoid the performance impact of a naive patching strategy.
- In order to produce a Type 1 PoV, the CRS must utilize opcodes to perform memory accesses - a process that may prove difficult.

### Difficulty
- Discovering is medium
- Proving is medium/hard (depening on PoV type)
- Patching is medium

