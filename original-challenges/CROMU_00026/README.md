# Packet Receiver

## Author Information

"Jason Williams" <jdw@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is an fictional implementation of a radio receiver after demodulation. The service reads in raw data bits, acquires preamble lock, bit/byte synchronization and begins decoding packets and rendering them as they are received to stdout.

### Feature List

The service features preamble locking (0101010101 or 1010101010 sequence), bit/byte synchronization using 16-bits to acquire byte pattern lock, and checksums for packet integrity checking. Packets support 32-bit and 16-bit checksums as well as fragmentation. Fragmentation is optional and up to 16 fragments can be assembled into a full message packet. Fragmentation uses a fragmentation list to assemble packets with the same sequence numbers into a completed message. After reassembly a message is rendered using a combination of text markup (underline, bold, italics) and formatting characters (tabstop, break, paragraph, and newline) to standard output.

## Vulnerability

There are two vulnerabilities present in this service. The first vulnerability is in the packet fragmentation code. It is possible to send a packet outside of the maximum fragment number (a last packet bit signifies the maximum number of fragments to the reassembler). An invalid calculation of length occurs when the assembled size of the full message is calculated up all of the sub packets within range but during assembly all the packets are concatenated together resulting in a heap overwrite. The last bug is in the message renderer a stack overflow can occur when a message is assembled that exceeds the render buffer. This is possible becomes the render buffer naively assumes that full messages cannot exceed the number of bytes in a maximum fully assembled packet. The error exists due to the special formatting codes that result in writing data to the render buffer that exceeds 1-byte in length, therefore allowing a stack overflow to occur.

### Generic class of vulnerability

Improper calculation of Buffer Size
Out of bounds write

### CWE classification
CWE-131: Improper Calculation of Buffer Size
CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
CWE-121: Stack-based Buffer Overflow

## Challenges

This CB has two vulnerabilities. These vulnerabilities will require a CRS system to reason at the bit level to generate properly formatted packets. Proper state machine tracking is required in both cases as both vulnerabilities are accessible via packet fragmentation. As this service mimics an RF front-end (which is always subjected to noise) fuzzing will be statistically improbable to yield any results (unlikely to ever pass bit/byte synchronization let alone checksum verification of the packet).
