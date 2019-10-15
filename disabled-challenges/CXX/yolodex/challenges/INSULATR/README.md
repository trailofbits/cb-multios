# INSULATR Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

The mice need more funding.  What better way than to cash in on all the #PoliceState #1984 business going on in the media?  

The market can support at least one more secure messaging system, right?

### Feature List

Well, OK, the rodent duo aren't quite at a viable product yet.  In fact, they're still writing their pseudo-JSON parser.

This pseudo-JSON parser will deserialize blobs into the data types for ultimate use by INSULATR.

Serialize, deserialize, you name it!

The pseudo-JSON language (but not code) is borrowed in part from GREATVIEW, another Challenge Binary.

## Vulnerabilities

INSULATR suffers from a type confusion vulnerability in its deserialization functionality.  This challenge is designed, loosely, after a real-world, unauthenticated, type confusion, RCE vulnerability in BlackPhone's SilentText application.  SilentText misused the YAJL (Yet Another JSON Library) library which ultimately lead to type confusion.  

The vulnerability presented here emulates a different misuse of a quirk in YAJL.  Specifically, YAJL will return a string object when it attempts to parse a number object whose value cannot fit in the object's number field, conducting implicit promotion of the object type.

Specifically, when parsing integers, if the integer exceeds MAX_UINT32, then it returns the value as a string instead.  INSULATR will get confused: its attribute struct will specify that the attribute in question is a NUMBER, when in reality it's actually a STRING.

If you attempt to serialize a confused attribute, INSULATR will attempt to write the *number* field into the output stream, resulting in a NULL pointer dereference and a crash.

### CWE classification

843: Type Confusion
824: Access of Uninitialized Pointer
704: Incorrect Type Conversion or Cast
476: Null Pointer Dereference

## Challenges

This CB is designed to be difficult to patch.  The *correct* way to patch alters promotion behavior in the vulnerable SET command to properly promote the affected object during deserialization.  This change only makes a difference on subsequent requests.

Among other aspects, we expect the following CB characteristics to present difficulty to CRSs:
* State must be tracked across disjoint requests.
* Type inference / reconstruction will likely be required on some level.  This typing system must be malleable to allow for object promotion.
