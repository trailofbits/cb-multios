# CGC Challenge Binary (KPRCA_00057): Glue

### DARPA performer group
Kaprica Security (KPRCA)

## Description
Glue is a custom file format meant to be used as an archiving mechanism for
system administrators who desire to store large collections of files as
a single file. This service is command line parser for glue files desired to
allow system administrators to easily examine and validate the contents of
their glue files.

### Feature List

 * Print the follow attributes about each object contained within the archive

 * Name
 * Mode
 * UID
 * GID
 * User Code
 * Size
 * Modification Time
 * Type
 * Link Name
 * Magic Value
 * Version
 * Owner Name
 * Group Name
 * Device Major Number
 * Device Minor Number
 * Prefix

## Vulnerability
The vulnerability for this service exists within the fetching of the user's
user_code for a object in the glue file. user_codes are contained within
a global string in the binary that is indexed into using the product of the
user ID and group ID on the current object being processed. If this computed
index is specially crafted it can be used to cause the service to print out
contents of values in the secret page thus resulting in a type 2 vulnerability.

### Generic class of vulnerability

Invalid Array Index

### CWE classification

CWE-125: Out-of-bounds Read
CWE-129: Improper Validation of Array Index

## Challenges
This is a relatively simple vulnerability to prove. By realizing that the
index into the global user_codes array could result into a type
2 vulnerability, the CRS will then need to identify that the index is based off
of the GID and UID which taken from input provided to the service. Difficulty
does however lie in accurately encoding the desired GID and UID as character
encoded octal numbers which is the format in which the challenge binary expects
them to be encoded.

## Subjective Quantification
Discovering: Easy
Proving: Easy
Fixing: Easy
