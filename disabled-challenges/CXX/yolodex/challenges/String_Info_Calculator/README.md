# String_Info_Calculator

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

For all of the authors who write all of their documents in VI, we've created the String Info Calculator. Not everybody has a fancy GUI word processing tool handy when writing a research paper or a book report. And we strongly believe that ALL authors need to be able to determine the statistics of their writing. How else are they going to meet the demanding parameters of their editors?

## Feature List:

This is a service that will tell you the stats on your writing.

- Number of characters
-- Number of total chars
-- Number of printable chars
-- Number of non-printable chars
-- Number of letters
-- Number of numbers
-- Number of symbols

- Number of words
- Number of sentences
- Number of paragraphs
- A cryptographic hash of the content

## Vulnerability 1

The vuln is information leakage of secret data. The compute\_hash() function in strinfo.c uses bytes from user input as the offset into the secret page. The bytes read from the secret page are used in an xor operation to create a hash value that is provided as part of the result sent to the user; the hash field in the result struct. The user can take advantage of the known offset and the hash value to calculate all of the bytes in the secret page.

### Generic Class of Vulnerability

Information Leakage

### CWE classification

CWE-201: Information Exposure Through Sent Data

### Challenges

* The hash value returned from the CB is deterministic and can be controlled by 2 bytes in user input. The CRS will need taint tracking to learn that the hash value contains 4 bytes from the magic page. It need some complex logic to create the checksum, and to xor the checksum with the hash value to extract the bytes that came from the magic page. But it is more advanced than just tracking the taint and doing the xor, because the hash value contains a non-sequential set of bytes from the secret page and when extracted from the hash value they are in reverse order from their ordering in the secret page. Then, the CRS has to learn to perform enough repeated communications with the CB to gather a sufficiently long sequence of magic page bytes, put them all in order, and then submit them.
* This CB was intentionally kept small to give the CRS's a chance at solving this vuln.

### Difficulty

* Discovering is medium
* Proving is hard
* Fixing is easy

