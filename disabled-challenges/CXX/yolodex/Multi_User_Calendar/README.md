# Multi_User_Calendar

## Author Information
Kaprica Security

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A multi-user calendar system that allows individual users to create personalized events and view those events.

### Feature List

There are two interfaces the first which allows the creation, deletion and setting of users.
Operations:
    1. View users
    2. Add user
    3. Remove user
    4. Set user
    5. View Calendar
    6. Change Date
    7. Exit

After a user is created and "Set" the "View Calendar" mode is available.
Operations:
    1. View Day
    2. View Month
    3. View Agenda
    4. Change Date
    5. Change View Date
    6. Add Calendar Event
    7. Remove Calendar Event
    8. Return to User Selection

The above operations allow for the creation and viewing of events on a users calendar. As well as the
ability to look at upcoming events with "View Agenda". This will up to 8 events that occur in the next 3 months

## Vulnerability

### Vuln 1
In the `find_user_from_list` funtion there is an improper bounds check on the buffer that is copied into the
`temp_user.username` variable. The vulnerability is only triggered when there are 100+ users in the system.
This is due to a check that processes the user list within the `find_user_from_list` function rather than using the
normal list interface find.

### Generic class of vulnerability
Stack based buffer overflow

### CWE classification
CWE-121

## Challenges

The vulnerability requires a nontrivial amount of users to be added to the system before the bug is triggerable.

## Difficulty

Discovering = Medium
Proving = Easy
Patching = Medium
