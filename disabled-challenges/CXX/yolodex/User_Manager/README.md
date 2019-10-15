# User Manager

## Author Information

"Jason Williams" <jdw@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a reimplementation of the service CROMU_00001 specification with additional functionality added including an admin login, admin console, admin and user passwords, and written using C++ classes.

### Feature List

This service features an an initial menu that allows a user to login, a new user to be created, or an administrator to login to administrator console. The service allows users to send messages to each other from there user menu after logging in. New messages that are received are marked as unread and when a user attempts to read their messages they first are prompted with any unread messages. The administrator console allows an admin after proper authentication to list all users, delete a user, or change their password.

## Vulnerability

There is one vulnerability in this service. It is due to the method in which unread messages are tracked per user. An unread message pointer points to the last unread message in the linked list of user messages. When a message is deleted by a user (but not read -- as this will clear the unread message pointer) and that message that is chosen to be deleted is the one the unread message is pointing to the unread message pointer will now point to deleted data. Hence a use after free event can occur. When a user then goes to read a message the program will attempt to display the oldest unread message (which points to deleted data) and a use after free will occur.

### Generic class of vulnerability

Use after free

### CWE classification

CWE-416: Use After Free

## Challenges

This CB requires the reasoning system to login and provide the proper credentials. In order for the reasoning system to effectively do this it must track the state of the users in the database and provide the proper authentication parameters to access the user console where messages can be sent and the vulnerability exercised. Lastly a use after free event does not immediately constitute a crash. The memory pointer that points to stale data on the heap must be manipulated in a manner to cause a crashing event.
