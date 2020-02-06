# KPRCA-00007

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple text-based protocol that mimics the basic functionality of a router interface. The user is provided with the ability to setup routes and routers, and ask which router should be the next hop for a specific IP. The router information is stored in an array indexed by its 16-bit ASN; and the route information is stored in a trie for faster lookups.

### Feature List

The server has two modes: normal and enable. In normal mode, the user is able to add, delete, and query routes; and in enable mode, the user can add, delete, edit, and list routers. The enable mode is protected by an ultra-secure password to prevent malicious access to router controls. With the route query command, the user can find out which router should be the next-hop for the given destination IP.

## Vulnerability

The edit router function (main.c:607) does not verify that the router ASN is greater than 0. Since the router ASN is used to index into an one-based array, this allows an attacker to modify the global variables that come before the array, which include the input buffer, its length, pointer to route memory, and the default route. The ASN member of the router structure is verified (i.e. must be greater than 0 and less than 65535), so the attacker must craft their input such that the correct part of the input buffer is in that range. Causing a crash is trivial with the arbitrary control of a pointer.

### Generic class of vulnerability
Out-of-bounds array access

### CWE classification
CWE-129: Improper Validation of Array Index

## Challenges
This service was designed to be solved with a constraint solver. Dynamic memory allocation is very limited (e.g. no use of malloc) and the contents of the dynamic memory are not important for exploiting the service. The enable password is a short hard-coded string that is compared against user-controlled stack memory. The goal would be to find a path that can modify one of the pointers in the data section.

The challenge will be to find the exploitable path and handle the string comparisons that are required to get to the right path. Additionally, patching the bug requires the knowledge that the memory that comes before the *g_routers* array is not part of the *g_routers* array; and thus, the ASN should be limited to values greater than 0.
