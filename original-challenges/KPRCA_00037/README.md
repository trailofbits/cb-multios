# CGC Challenge Binary (KPRCA\_00037): CGC Symbol Viewer (CSV)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This service prints out the section and symbol information for a given CGC exectuable.

### Feature List

**Features**

- Parses and validates CGC executables
- Displays section info (name, type, address, offset, and size)
- Displays symbol info (name, value, size, type, and bind)
- Output format is similar to what readcgcef utility outputs
  - It's a lot less strict about the actual contents, however.

**Protocol**

- Input: Raw bytes that represent the CGC executable file, prepended by its size in bytes.
- Output: Text display showing information about the file (sections and symbols).

## Vulnerability

- The parser does not correctly validate the value of index to the section headers when calculating the offset to the section header data.
- The *idx* value can be negative passing the check of *idx < shnum* in cgcf.c:125.
- Also, there's an integer overflow bug which can be caused by supplying large (yet valid) field values.
- This may yield an access violation on invalid memory, given a carefully crafted input.

### Generic class of vulnerability

Insufficient range check
Integer Overflow

### CWE classification

CWE-839: Numeric Range Comparison Without Minimum Check
CWE-190: Integer Overflow or Wraparound

## Challenges

- Lots of mutable fields that can affect the state of the parsing
- Sometimes mutating one field is not enough to trigger the bug due to other checks. In such case, multiple fields must be carefully manipulated in order to trigger the bug.
