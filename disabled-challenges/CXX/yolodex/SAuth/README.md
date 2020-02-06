# SAuth (KPRCA_00058)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A secure authentication service with an extensible protocol that can support multiple authentication methods and multiple upper layer services.

### Feature List

Full support for the cleartext password authentication method; user can change password using a change request.

Timing attack resistance to prevent exposure of usernames and passwords.

Packets are padded to 8-byte boundaries with random data to make it easier to implement on top of a secure channel in the future.

## Vulnerability
### Vuln 1
In service.c:285, there is an integer overflow that allows an attacker to bypass the length check. This vulnerable function is called from service.c:513 and is passed a stack buffer of a fixed size. An attacker is able to use the integer overflow to cause the stack buffer to overflow if they give a string length of 0xFFFFFFFF and a packet with 0x8000 bytes of data. This is provable with a type 1 POV.

#### Generic class of vulnerability
Buffer overflow

#### CWE classification
CWE-121: Stack-based Buffer Overflow

CWE-190: Integer Overflow or Wraparound

#### Challenges
No major challenges. Requires reasoning about integer overflows and function argument types.

#### Difficulty
 - **Discovery**: easy
 - **Proving**: easy
 - **Fixing**: medium
