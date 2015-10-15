# CGC Challenge Binary (KPRCA\_00021): KTY Pretty Printer

### DARPA performer group
Kaprica Security (KPRCA)

## Description

KTY (read as Kitty) is a JSON-like text-based data-interchange format that provides more amazing data types than JSON does. While KTY does not support unicode, it has a special type called 'cat' because cats are awesome. This program parses KTY data and prints a nicely formatted output. It even has a hidden feature for Nyan-lovers.

### Feature List

The service provides three (and one hidden) menus:

  - Import KTY
  - Pretty print KTY
  - Quit
  - (Hidden) Nyan

Nyan menu prints nyan cat ascii art only if the currently imported KTY has 3 or more instances of cat-type values.

Supported types are:

  - string
  - number
  - object
  - array
  - boolean (true/false)
  - null
  - cat (=^.^=)

## Vulnerability

Nyan function will print the ascii art along with the text, which can be specified with a field in KTY object. Specifically, the program will look for **nyan_says** key that is a string type as its value. The bug is that it will copy each instance of **nyan_says** string into a stack buffer with a static size, allowing an attacker to perform a stack overflow.

When given a string that doesn't result in a valid type, the item object is uninitiailzied, which causes a double-free to happen later.

### Generic class of vulnerability

Stack Buffer Overlfow
Double Free
Uninitialized Memory

### CWE classification

Stack-based Buffer Overflow (CWE-121)
Double Free (CWE-415)
Use of Uninitialized Resource (CWE-908)

## Challenges

This CB tests if the competitors can reason about the triggering condition for the vulnerable function as well as the vulnerability itself. Lots of data structure are involved and most importantly, the program makes use of union inside of the KTY item struct for the flexible data representation.
