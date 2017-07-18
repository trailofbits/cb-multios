# CGC Challenge Binary (KPRCA\_00043): Bloomy Sunday

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Bloomy Sunday is a safety feature that filters any blacklisted depressing words
in submitted lyrics. To make it more responsive, it implements a bloom filter
to quickly test if the word is not in the blacklist, in which case, doesn't get
banned.

### Feature List

**Features**

- Submit lyrics
  - Check against the filter (automatic)
- View lyrics

**Protocol**

- User-interactive interface

## Vulnerability

- The input is read in a line at a time, which is splitted into multiple words.
- Each word is checked against the filter.
  - When the word is not found by the filter, the word is passed and copied over to the final lyrics buffer. The length is validated to ensure there's no buffer overflow.
  - In case the word is found by the filter, it needs to be tested with the real blacklist table since it could be a false-positive.
  - When the word exists in the table, the submission process is immediately aborted, and reports an error/warning.
  - When the word does not exist in the table (aka. false-positive), the word is copied over to the final lyrics buffer. However, the length check is omitted in this path -- leading to a stack-based buffer overflow.
- Also, there is an one-byte overwrite bug that will cause a segmetation fault.

### Generic class of vulnerability

Stack-based Buffer Overflow

### CWE classification

CWE-121: Stack-based Buffer Overflow

## Challenges

- Competitors need to generate a word that is not in the blacklist table, yet is flagged by the bloom filter (it's using 3 hash functions), such that appending the word will result in a buffer overflow.
