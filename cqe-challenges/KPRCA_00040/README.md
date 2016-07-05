# KPRCA-00040

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple lossless, text-optimized compression schema
that allows for the efficient storage of data. The user first states whether
they want to compress or decompress and then passes the data to be compressed
or decompressed to the service. The service then returns the result of
performing the requested action on the passed data. There are artificial limits
on the maximum amount of data that can be processed.

### Feature List

The process used to compress data relies upon being able to quickly find
repeated suffixes within the input data. When an substring is found that has
already occurred in the input data we emit a back reference that states how far
to go back into the input stream and how much data to emit from that reference
point. If we haven't seen the input data we simply emit the data verbatim.
Decompression is the process of taking in these verbatim strings and
back reference and reconstructing the original data.

## Vulnerability

The vulnerability for this service is found in the decompression function. The
decompression function writes the decompressed data into a fixed size buffer.
However, the writer method nor the decompression function adequately check
whether or not the bounds of the output buffer have been exceeded. Therefore,
if the decompress function is passed a compressed blob that decompresses to too
large of an uncompressed blob then a buffer overflow occurs.

### Generic class of vulnerability
Buffer overflow
Unchecked array index

### CWE classification
CWE-121: Stack-based Buffer Overflow
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

## Challenges

This services tests the competitor's ability reason about somewhat complex
algorithms and binary data formats.  In order the exploit the vulnerability
found in this service the challenger will have to be able to deduce that a
buffer overflow exists and that it is only exploitable by constructing a
stream of data which expands beyond the bounds of the buffer.
