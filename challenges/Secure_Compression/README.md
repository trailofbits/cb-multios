# Secure_Compression

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Secure Compression uses Burrows-Wheeler Transform (BWT) and Move-to-Front (MTF) algorithms to compress a given data. It uses 95 byte key from a user, which specifies the ordering of the alphabet (data) which changes the output of the BWT and MTF -- and decompresses to a meaningful data only when the correct ordering (key) is given.

After MTF is performed, a simple bit-encoding is done to actually reduce the length of the data. It encodes each byte with the following rule:

- If the byte is greater than 0x0F, emit bit 1 followed by 8 bit representing the byte value (total of 9 bits)
- If the byte is less than or equal to 0x0F, emit bit 0 followed by 4 bit representing the byte value (total of 5 bits)

### Feature List


```
- Compress
- Decompress
- Quit
```

## Vulnerability

### Vuln 1
- There's a stack buffer overflow when doing reverse-MTF for decompression. The `sz` field that is controllable by the attacker can be greater than the stack buffer size.
- The stack buffer is allocated less than what the maximum `sz` can be, thus causing an overflow is possible.
- Type 1 vulnerability.

### Vuln 2
- When performing reverse-BWT for decompression, the `oidx` (original index within the rotation table) is parsed from the user data and is used without any validation.
- This allows an attacker to point the buffer pointer to contain an attacker-controlled buffer (such as the first block of the data), which then can be used to 
to read arbitrary memory.
- Type 2 vulnerability.

#### Generic class of vulnerability

Stack buffer overflow

Insufficient check on index to memory

#### CWE classification

CWE-121: Stack-based Buffer Overflow

CWE-125: Out-of-bounds Read

CWE-129: Improper Validation of Array Index

#### Challenges

- Lots of bit operations to be analyzed.

#### Difficulty (Vuln1 / Vuln2)

 - **Discovery**: easy / medium
 - **Proving**: medium / hard
 - **Patching**: easy / easy
