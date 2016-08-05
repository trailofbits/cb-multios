# Barcoder

## Author Information
Kaprica Security

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A barcode system

### Feature List

The service allows a user to generate or decode barcodes.
The options are:
1. Input a new barcode
2. View barcode ascii
3. Generate barcode image
4. View cached barcodes
5. Clear cached barcodes
6. Quit

When inputting a barcode, a user may input as text, bacoded ascii (with '|'and ' ') representing the binary values
or as a bitmap that digitally represents the barcode.

Once a barcode is cached (up to 10 items can be cached) it can be viewed as either an ascii or bitmap representation.

## Vulnerability

### Vuln 1
The vulnerability is through a printf vulnerability. If the user inputs a barcode via a bitmap the text
will be printed: `printf(new_barcode->raw_str);` in line main.c:139. This allows for the user to 
lead information from the magic page

### Generic class of vulnerability
Information Exposure

### CWE classification
CWE-134: Uncontrolled Format String
CWE-121: Stack-based Buffer Overflow
CWE-839: Numeric Range Comparison Without Minimum Check
## Challenges

Vulnerability 1 is meant to test the CRS's ability to utilize a program as its own input.
In this instance, while it is possible to reverse the structure and try to create a compliant set
of barcodes to brute force, a human would quickly realize that you can have the program do all this
work for you, and use it as an ability to generate valid bitmaps to use.

## Difficulty

Discovering = Easy
Proving = Medium
Patching = Easy
