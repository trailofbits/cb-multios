# CGC Challenge Binary Template

## Author Information

Narf Industries <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Multipass is a new, magical, way to pay for all of life's necessities. Simply swipe and go for gas, food, vending machines, and at conbinis! 

### Feature List

The following transactions are available:
- Make purchase (use multi-pass card to make a purchase from a vendor)
- Refund purchase (use multi-pass card to refund a previous purchase)
- Balance inquiry (use multi-pass card to query its balance)
- List transaction history (use multi-pass card to query the list of recent transactions)
- Issue new Multi-Pass (request a new multi-pass card)
- Add funds to Multi-Pass (use multi-pass card to add funds to the balance)

## Vulnerability

This multipass daemon has a few internal structures to track if a transaction is open/closed. Upon finalizing a transaction its open flag should be set to zero.
The vulnerable version, however, decrements the is_open flag (account.c:205) such that it rolls over to +128 (char var). This offset is used directly as an ERRNO.
The NULL dereference is not triggered immediately, the system waits until it has to generate an error message packet (multipass.c:generate_error). 
In the error generation process, the ERRNO is used as an offset into a table of char * pointers (multipass.h:104). The index is out of bounds in this array of char pointers and causes a null dereference.

Another simpler NULL dereference involves invoking refund operation against a non-refundable transaction. Specifically, all AUTH requests are logged to the MULTIPASS history. AUTH transaction histories do not contain a data section. One of the first steps in the refund operation is to lookup a transaction by ID and dereference the data section. Dereferencing the null data section of an AUTH transaction leads to another NULL pointer dereference. 

### Generic class of vulnerability

Integer underflow followed by NULL dereference.

Plain null dereference.

### CWE classification

NULL Pointer Dereference
CWE-476

## Challenges
* The release poller does not include any information about how to generate error messages.
* The CRS requires taint tracking across a static variable which is touched in a fair amount of the program, this might be optimized away by some competitors.
* The release poller is not indicative of the protocol allowing *multiple* FINS.


