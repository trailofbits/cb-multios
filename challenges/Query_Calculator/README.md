# Query_Calculator

## Author Information

"Bryce Kerley" <bk@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

`cqltor` is a calculator application with some extra string functions,
that parses requests out of a friendly, easy-to-use language that could
be extended to support queries against data sets.

### Feature List

* Lexer and parser compile human-friendly strings in multiple stages
* Compiles requests into an intermediate stack-based language
* Evaluate intermediate requests, including recursive evaluation of
  requests inside requests.
* Integer and string operations

## Vulnerability
The `ord` function returns the integer byte value of the n-th character in
a string. It does not perform any bounds-checking. However, the lexer is
limited in the magnitude of integers it can parse, which limits the damage that
can be done without an attacker constructing arithmetic operations.

### Generic class of vulnerability

Stack-based buffer overflow

### CWE classification

CWE-129: Improper validation of array index

## Challenges

Discovering: medium. The array being accessed is parsed out of a larger string,
and the index can either be hard-coded into the same larger string, or
calculated with user-specified mathematical operations.
Proving: hard. The array being indexed into is far enough from the magic page
that an arithmetic expression with multiple terms has to be generated.
Fixing: easy.

