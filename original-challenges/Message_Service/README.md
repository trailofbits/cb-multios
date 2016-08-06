# CROMU-00037 Message Service

## Author Information

"Joe Rogers" <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This is a basic message application with the ability to create new users, log in to existing users and send messages to others.

### Feature List

A user can create new users and subsequently log in to their new account. From here they can send a message to a user, read a single message, list all of their messages, delete a message, log out, or exit the program. Once back at the log in screen they can create additional users, log in, or exit the program. Any new messages are automatically displayed to the user.

## Vulnerability
A hidden, password-protected 'admin' mode is available by using menu option 'a' after logging in using an existing user.  From this mode, broadcast messages to all current users can be sent.  However, this function fails to implement proper maximum message size checks and allows overflowing of the message array.  While an overflow in any user's account would cause corruption of messages, usernames, and read/unread statuses, the bug is particularly harmful if an overly large message is sent to a user who is the MAX user on the system.  

The CB only allows 100 user accounts to be created with each account having a maximum of 255 messages in their inbox.  If the broadcast message is sent to the 100th user and is the 255th message in their inbox, it can overflow beyond the user account array and can be used to control the return address of main().

Once the overflow message has been sent, the CRS must use the admin-mode exit menu option since this is the only one which returns from main().  All other exit menu options in the program call terminate() and wouldn't pass control to the CRS' overwritten return address.

### Generic class of vulnerability
Hard-coded admin credentials allow access to a function which is vulnerable to a buffer overflow.

### CWE classification
CWE-798: Use of Hard-coded Credentials
CWE-131: Incorrect Calculation of Buffer Size

## Challenges
The CB begins with a repeated bubble sort of a 4096-byte array copied from the text section of the binary.  This will help differentiate team performance with computation and memory intensive activities.  After this, the CRS need to identify the hidden menu option, find the hard-coded password and then they can access the vulnerable function.  While corruption of user account data is possible, they will need to determine that the overflowing the max user's maximum message will have the most drastic impact on the CB.
