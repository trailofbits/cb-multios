# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is the Chuck Norris (joke) Management Protocol (CNMP)

There's an arms race among Chuck Norris joke authors, resulting in a bunch of proprietary joke protocols.  Authors make money licensing joke accessories, necessary for interfacing with their trademarked and totally-better-than-everyone-else protocols.

Humor Corp, noticing a dip in the SNMP market, has decided to move into the joke market.  Today they've announced their just-different-enough CNMP protocol, sure to please all those Chuck Norris fans.

### Feature List

This service is somewhat inspired by SNMP.  Authors can get and set Chuck Norris jokes on a central server using CNMP, much like information might be referenced with OIDs and described with MIBs in SNMP.

Authors can write a large collection of Chuck Norris jokes and browse them to amuse all of their friends.

Authors can check the total number of jokes in the central server, list all of the jokes, list a specific joke, and have the server show them a randomly selected joke.

The service provides a menu system to assist authors with supported commands.

## Vulnerability

Each joke is stored in a fixed-sized buffer (512 bytes) which is 511 chars followed by a '\0'. So, the author can submit jokes that are 511 chars long.

If a joke is 511 chars long and contains 2 or more format specifiers "~c" for a char buffer, the syslog function call in insert_joke, will result in a user controlled format string bug.

* Note: this version of xxprintf uses ~c for char string and ~n for int, which is different from converntional versions.

Specifically, in joke.c:94, the syslog() function is called with the user provided joke string as its format string. Then in libc.c:117 that format string is provided to vnsprintf() as its format string, and in this case, the args parameter is empty. Thus, when vnsprintf() is retrieving values to replace the format specifiers, in libc.c:271/278, it is reading out of bounds from the memory that directly follows the format specifier.

Example exploit for this would be a joke like one of the following examples:

A minimum case:
joke1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa~cbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb~c"

An extreme case:
joke2 = "~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~c~ca"

### Generic class of vulnerability

Uncontrolled Format String

### CWE classification

Uncontrolled Format String
CWE-134

## Challenges

- Finding the precise joke length and joke contents to reach and then trigger the vuln.
- Finding that the format specifiers and format string marker used in this version of libc have different meaning from that in stdlib.
