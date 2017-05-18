# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Tired of being limited to 160 characters?
Want to send large, binary messages over current cellular networks?
LMS (Long Message Service) is our proprietary alteranative to SMS, that allows for longer messages and more efficient transfer of your messages. 
This is an alpha implementation of a reference client for this excellent new protocol.

### Feature List

LMS supports raw message sizes of 256 bytes, and can use up 2**16 fragments, and supports a number of different base encodings.
This client will process a series of LMS fragments and decode the message.

## Vulnerability

Two seperate dangling pointer vulnerabilities exists in the delete_session function, leading to a use after free situation in later packet processing.
By adding two or more sessions, causing the first to complete, then forcing an appropriately sized allocation to occupy the same memory, it is possible trigger this condition and cause a segfault.

Additionally, an off-by-one vulnerability exists in add_msg that allows an OOB write of a 1, one byte outside the bounds of the sess->received array.

### Generic class of vulnerability

Use-after-free
Heap overflow

### CWE classification

CWE-122: Heap-based buffer overflow
CWE-193: Off-by-one error
CWE-416: Use After Free
CWE-825: Expired Pointer Dereference

## Challenges

Creating multiple sessions from a capture of a single session. This requires reasoning about bitfields and using control over them to create new sessions, as well as crafting well-formed new sessions that parse correctly.

Autonomously discovering UAF/dangling pointer vulnerabilities in a CB utilizing a custom allocator is quite difficult; we anticipate this to be a significant barrier to competitors.

Manipulating allocations in such a way as to overwrite the freed memory is necessary to actually prove vulnerability.
Once the vulnerability is discovered, however, this will likely be relatively easy by design.

Correctly patching the vulnerability by removing the dangling pointer, as well as restoring the integrity of the linked list, will likely prove very challenging.
