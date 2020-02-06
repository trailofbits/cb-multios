# KPRCA-00015

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements the MULTIPASS PROTOCOL, which is a binary protocol for multi-use RFID payment cards. Every issued card has an ID and auth code which is used to authenticate the card for future operations. Auth codes are generated using an ultra secure algorithm that is not patent pending.

### Feature List

The service implements basic functionality such as card balance and reloading, purchases, and refunds, plus issuing new cards and reporting transaction history. All operations are atomic and recorded in a secure transaction log. 

## Vulnerability

The address of transaction structures is used as the transaction's ID (main.c:258). This both leaks memory addresses to an attacker and gives them control over a memory reference. There is some basic verification of the transaction ID to ensure that it is within the array of transactions (main.c:279), but does not check that it is properly aligned. Using the *REFUND* operation, an attacker can specify a transaction ID that is in the middle of a transaction they setup and cause the *REFUND* operation to dereference arbitrary memory (main.c:424).

### CWE classification
CWE-822: Untrusted Pointer Dereference

## Challenges
The first challenge that a competitor faces is getting to the vulnerable code. They must construct an input that will issue a new card, authenticate with that card to make a purchase, and then do a refund. Second, there are verifications that make it impossible to use an arbitrary transaction ID. The input must generate a transaction ID that matches with the location of the transactions array in memory. Additionally, before the transaction's data pointer is dereferenced, there are additional checks that the transaction is valid for a refund operation.

