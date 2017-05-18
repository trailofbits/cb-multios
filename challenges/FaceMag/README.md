# FaceMag

## Author Information

"Steve Wood" <swood@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a social media server where users can post messages for others to view and comments on.

### Feature List
This service is a social media server that provides a network protocol for new accounts to be created, message posts to be made, comments to those posts and a posting feed where the user can retrieve postings that she hasn't previously seen.  Specific posts can be retrieved by their posting ID and all associated comments are also displayed.  A filesystem is used for the underlying storage mechanism for the server with each user having an account file that maintains their state information as well as their real/full name.


## Vulnerability
Vulnerability 1 is a buffer overwrite due to the server relying on user specified length parameters to dictate how long incoming messages, user names, passwords, and fullnames are.  Even though these incoming messages overwrite the data structure they are cast to, they are still much shorter than the full 4K page of memory that was allocated, so they have no affect on program behavior when first received.  The real overwrite occurs later when one of these strings, the fullname, is later retrieved from the user's account file and used to build a posting message for return to the user.

### Generic class of vulnerability
Stack buffer overflow

### CWE classification
CWE-121 Stack based buffer overflow

## Challenges
Although this vulnerability is easily found and corrected, proving it to be exploitable is not.  A buffer is created with an allocate() call that is much larger than is required to hold the incoming message.  Even though the string's length is specified in the message, a single byte is allocated in the message for the length paramter which limits the string to 255 bytes--far too short to overwrite a 4K page.  Several strings in the incoming messages have this same vulnerability but only one is not later truncated:  the user's fullname.  This string is stored in the user's account file and is used to tag posts with their real name rather than their username.  However, when a post message is created, the username is null terminated at the proper length.  Only when the username is applied to a comment that's been made to another post is the full string retrieved which allows the local stack space to be overwritten.  Due to the arrangement of variables in the stack frame, the overwrite is not able to corrupt the stack frame and the saved registers.  What can be overwritten is the file handle used to read the stored post and its comments.  Another file on the system is persistently open and happens to be a memory-mapped file that points to the magic page.  By overwriting the local file handle to the value of the other open file, the next read of a comment will actually load raw data from the magic page.  An additional complication occurs if this read is done soon after the service is running though.  The amount of data in the memory mapped file is too large and will completely corrupt the stack frame resulting in an uncontrollable program crash.  Only after the memory-mapped file has been used well over 100 times does its read pointer move near enough to the end to not read too much data before EOF is reached.  There are other nuances to making a working POV that involve the order of operations with the server as well.

	Finding Vulnerability 1: easy
	Proving Vulnerability 1: hard
	Fixing Vulnerability 1: easy 


