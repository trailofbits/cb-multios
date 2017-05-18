# KPRCA-00024

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple commerce site that allows users to buy and sell products. The service utilizes a database service that serves as the backend. The protocol between the two servers is a form of RPC. The RPC code was mostly generated automatically from a specification file.

### Feature List

The basic features are: list products, buy a product, and sell a new product. A product has an inventory count and a price. Products are identified by their name which is a standard null-terminated string. The backend database is based on a self-balancing binary search tree, which guarantees good performance.

## Vulnerability

The vulnerability is triggered in the list products functionality (cb_1/src/main.c:58). The output is buffered into a stack buffer of fixed length (4096 bytes) and the length is not checked. This allows for arbitrary control of the contents of the stack, except for null bytes and line terminator bytes.

The second vulnerability is lack of verification of the return value of _checked_calloc; this results in the same memory being used by multiple objects.

### Generic class of vulnerability
Stack-based Buffer Overflow

### CWE classification
CWE-121: Stack-based Buffer Overflow
CWE-252: Unchecked Return Value

## Challenges

The primary challenge is following the data flow between the two services. In order to crash the frontend service, you must first load enough data into the backend. It is probably a lot easier to solve this challenge with a fuzzer, because the protocol is not complicated and reasoning about the flow of data may be difficult. In order to make this more fair, only one sample poll is released to the challengers.
