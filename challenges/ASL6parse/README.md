# KPRCA-00020

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a parser and pretty printer for a Type-Length-Value
protocol known as ASL6. ASL6 is commonly used amongst retro online-chat
enthusiasts who desire an easy to exchange basic information about themselves
to eachother such as age,gender,or geographic location.

### Feature List

This service simply reads a ASL6 element up to 32KB in size and pretty prints
its contents back the the user. It is able to handle a variety of complex
datetypes such as time and object identifiers.

## Vulnerability

This service's vulnerability lies in the `print_oid` function. This function
parsers and prints the `OID` element type according to the format defined in
the ASL6 protocol. The function both fails to do a required bounds check on the
index into the array containing the OID data after it is updated and to correctly
pass an upper bounds on a slice into the data to a corresponding helper function.
These flaws in conjuction result in an out of bounds read.

### Generic class of vulnerability
Out-of-bounds Read

### CWE classification
CWE-125: Out-of-bounds Read

## Challenges

The challanges introducted to competitors in this service are a slightly
complicated protocol which the competitors must adhere to in order to progress
through the states of the servic, a variety of integrity checks inherent to the
encoding scheme to which they also must adhere.
