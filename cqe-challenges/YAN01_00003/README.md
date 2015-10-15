# Character Statistics

## Description

This service implements a simple character counter. It takes in a stream of input, echos it, and then outputs the number of lower case letters, upper case letter, numbers, spaces (incldues tabs), special characters (other printable characters) and finally others (non-printable characters). 

## Vulnerabilities

The vulnerability is an out of bounds read that is induced by an integer overwrite due to incorrect type coersion. In short, an uint32 add operation was used on an uint8 in memory, which leads to the overwrite of adjacent memory when the sum overflows the uint8 type. Since the adjacent memory is a pointer, a carefully chosen number of space characters will result in an overwrite that leads to a segmentation fault.

## Notes

This vulnerability falls under the CWE-681: Incorrect Conversion between types since the uint32 should have been converted back to an uint8 before committing or memory (or that uint8 add should have been used instead). CWE-189 falls under numeric errors.  

