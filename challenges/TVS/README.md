# CGC Challenge Binary (KPRCA\_00050): TVS

### DARPA performer group
Kaprica Security (KPRCA)

## Description
TVS is a vault service with a time lock. Unless the current time is in the allowed range, users are not able to retrieve items from the vault. At any time, a user is allowed to store new items or list the item IDs that are in the vault. In order to keep the current time accurate, the vault service synchronizes its time with a remote server.

### Feature List

 * Support for up to 500 vault items
 * Fast O(1) retrieval of vault items
 * Time and Vault Services are multiplexed for performance
 * Protection to prevent attackers from changing time
 * Software attestation via fixed addresses

## Vulnerability
There are two vulnerabilities, but both are due to vault IDs being used a locker_t pointers. This gives an attacker the ability to access or modify to arbitrary memory locations. Patching the vulnerability requires verifying that the pointer the attacker provides is proper, e.g. points to an allocated element in the contents array and is properly aligned.

A third vulnerability also exists in the interaction between main and realloc. In some implementations of realloc, a realloc with a length of 0 can return NULL. The logic in main expects this function to return NULL only if there is an error, so it will try to continue to use the pointer that has just been freed by realloc resulting in a double free.

### Generic class of vulnerability

Untrusted Pointer Dereference

### CWE classification

CWE-822: Untrusted Pointer Dereference

## Challenges
Triggering the vulnerability to modify memory locations is easy, while triggering the vulnerability to access memory locations is difficult because it requires unlocking the vault. Additionally, the IO is obfuscated using XOR which makes fuzzing more challenging, e.g. changing a single byte or bit cascades into the following bytes.
