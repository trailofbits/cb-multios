# CROMU_00041 - Email System 2

## Author Information
"James Nuttall" <james@cromulence.co>

### DARPA performer group
Cromulence

## Description
This service is a reimagining of CROMU_00001: A messaging service that allows the user to create, send, and receive messages.


### Feature List
This service represents a messaging service. User's can create users, log in, log out, create messages, send messages, view inbox, view all messages, and view drafts.

Upon connection, the CRS is presented with a login menu where it can create a user, log in, or exit.

After successfully connecting as a user, the CRS is presented with more options:
Create Message
Send Message
View all messages
View drafts
View inbox
Logout
Exit

A message is created and put into drafts. Once sent, it is removed from drafts and put in the appropriate user's inbox. During each login session, the CRS may only create four messages, but they may have up to 20 messages total. 

## Vulnerability
All messages are kept in a 2d array, with one axis representing the USER and the other axis the MESSAGES.

There are two vulnerabilities in this service:

Vulnerability 1:
Message.c, add_message() does not correctly check the number of messages that can be saved per user. The user may sign in, create four messages, log out, log in and create four messages, etc. until 21 messages are created. If the user is signed in as the last user (so they're at the end of the 2d array, listOfMessages), then the overflow'd message will overwrite the function pointer 'printer'. The next time the CRS tries to print a message, it will be pointing to invalid memory and crash.

This vulnerability is meant to be easy to both find and patch.

Vulnerability 2:
Similarly to vulnerability 1, the CRS must add 20 messages to the message queue of the last user. The CRS must log out, then intentionally fail the log in three times (by entering the incorrect password). This will allow the user to re-enter the same user name, and any password. The CRS must then log in with that user name and create one more message. This will cause a similar overwrite to the 'printer' function pointer and cause a dereference of invalid memory and crash.

This vulnerability comes around because when the CRS reset the password, their 'first_login' variable was reset (user.c, line 98). This variable is then used when adding a message (message.c, line 81) to circumvent the length check on line 100 (even if vulnerability 1 was patched).

This vulnerability is meant to frustrate brute forcing and cause intelligent path analysis.

Both out of bounds dereferences take place when 'printer' is called: from either list_drafts(), list_inbox(), or list_all_messages() in message.c. 

### Generic class of vulnerability 
Vulnerability 1 is a buffer overflow on the stack.

Vulnerability 2 is a buffer overflow on the stack.

### CWE classification 
Vuln 2: CWE-121: Stack-based Buffer Overflow
Vuln 2: CWE-121: Stack-based Buffer Overflow

## Challenges 
The challenge of this service is finding the logic flow that sets up the conditions and then allows the first_login to be set in order to allow the last message to cause the overflow.
