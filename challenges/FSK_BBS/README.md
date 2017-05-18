# KPRCA-00029

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a bulletin board system over a FSK modem. Users can create new threads, reply to threads, and read threads and replies. This challenge binary and its vulnerability are based on a real-world program and one of its vulnerabilities.

### Feature List

This bulletin board system is compatible with standard telephone encodings and supports connection speeds of 400 baud. The modem implements error correcting codes with a hamming distance of 9 bits and a checksum with a hamming distance of 4 bits, over a fragment containing 72 bits of usable data. Multiple fragments are then concatenated to form packets with a maximum payload of 1024 bytes.

## Vulnerability

The vulnerability is triggered in **bbs_rx** (bbs.c:327) where the input packet buffer is copied on to the stack without regards for the size of the stack buffer. Since a packet can be up to 1024 bytes and the stack buffer is 101 bytes, this gives an attacker a large amount of control over the stack.

### Generic class of vulnerability
Stack-based Buffer Overflow

### CWE classification
CWE-121: Stack-based Buffer Overflow

## Challenges

This service is very difficult due to the processing done on the input before it gets to the vulnerable function. Not only is the input audio that gets demodulated into bits, those bits are then error-corrected and checksummed to prevent corrupted fragments. Any fuzzing-based approaches would fail because they would not pass the checksum.

Additionally, the low baudrate of the modem results in a significant amount of audio data as input and output. After the error-correcting, for about every 200 bits of input the attacker needs to generate 64 kbits of audio input. Even a small POV is still over 100 kBytes.

The bug should be easy to patch because it is the canonical example of a buffer overflow: Unbounded memcpy into a stack buffer of fixed size. Even without fuzzing or symbolic execution, static analysis should be able to find this bug.
