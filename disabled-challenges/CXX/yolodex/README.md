# CGC Challenge Binary Template

## Author Information

"Dustin Fraze" <df@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

The yolodex is a service roughly based off fingerd.  Fingerd was chosen because the Morris worm, among the first widespread internet worms, targeted a code execution vulnerability in the finger daemon.

### Feature List

This service supports adding, deleting, editing, searching, and sorting contacts, like a rolodex.  It stores a first and last name, phone number, office number, gender, and if the user is known to be a hacker.

## Vulnerability

Editing an existing user holds the incoming change data in a temporary buffer, as to allow a field to remain the same by sending just a newline.  This temporary buffer is recycled for every input the user is allowed to provide.

The structure of a contact buffer is:

	typedef struct _contact {
		char first[32];
		char last[32];
		char phone[16];
		unsigned short officenum;
		char gender;
		char hacker;		
		unsigned int cookie;
		int pad;
		struct _contact *prev; 
		struct _contact *next;
	} contact;

The temporary buffer is 32 bytes long.  Although the phone number is 16 bytes long, the yolodex only accepts 14 bytes for input for the phone number ((NNN)NNN-NNNN\n).  If a user provides more than 16-bytes for the last name, and exactly 14 bytes for the phone number, without a newline in the phone number, a null is not read into the temporary data buffer.

Yolodex will then attempt to copy 14 bytes of phone number + the stale data from last name, until it runs into a NULL.  This allows an overwrite of officenum, gender, hacker, cookie, next, and prev.  Cookie is discussed in challenges.

If cookie's value is preserved, and next or prev are corrupted, a user could cause a dereference of an invalid pointer, or potentially code execution.

### Generic class of vulnerability
Buffer Overflow

### CWE classification
CWE-787: Out-of-bounds Write

## Challenges

This CB uses "heap cookies" between what is supposed to be user-writable and the metadata about the data structure.  Unlike traditional stack cookies, this cookie is set up once at initialization, and never changed during execution.  Corruption of the cookie forces the application to terminate.

A CRS would have to send crafted data longer than the bounds of the buffer, but short enough to not corrupt the cookie.  A properly crafted input would cause the cookie to be leaked at the end of the phone number.  A CRS would have to then read the cookie, craft a new buffer containing the leaked cookie, plus the overwrite, then trigger a dereference of the overwritten pointer through the detail view.
