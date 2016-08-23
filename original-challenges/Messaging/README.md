# Messaging

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A metadata parser built with message passing primitives.

This service is split into multiple processes to provide for concurrency. The original goal was to model it on message passing primitives. The service is split up into these components:

 - Master process 
 - Network communications and framing
 - Packet correction
 - Metadata parsing

When the service is sent a packet that contains valid metadata, it will traverse from the network process, to master process, to packet correction, to master process, and finally to the metadata process that will send a metadata object back to the master process. The master process will then ask the metadata process to dump the metadata to standard out.

### Feature List

 - Built using concurrency
 - Support for storing metadata with titles, artists, and/or albums
 - Customizable error correction capability up to 5% of input bytes
   - No parity is possible if connection is known to be reliable

## Vulnerability
### Vuln 1

In *cb\_1/src/main.cc*, there is a function *escape\_string* which is responsible for escaping newlines, NUL bytes, and other unsafe characters. It assumes that the buffer it is writing to is long enough to contain the escaped string. The calling function, however, only allocates enough space for the input string and since some characters are escaped as a two byte sequence, this results in a buffer overflow. Conveniently for exploitation, if the input string is short enough, the destination buffer will be right before a *char* pointer that is printed to *stdout*. A type 2 POV is possible by setting the pointer to somewhere in the secret page.

It should also be possible to exploit the vulnerability with a type 1 POV by overflowing into the heap metadata which results in control of the free list pointers. This is left as an exercise for the reader.

#### Generic class of vulnerability

Heap Corruption

#### CWE classification

CWE-122: Heap-based Buffer Overflow

#### Challenges

 - The primary challenge is dataflow analysis through multiple CBs that communicate using IPC.
 - A secondary challenge is the error correction codes that can be optionally enabled. Should be easily bypassed by a symbolic executor if the vulnerability was already found and it is just trying to find a path to the vulnerable code.

#### Difficulty

 - **Discovery**: medium
 - **Proving**: easy
 - **Patching**: easy
