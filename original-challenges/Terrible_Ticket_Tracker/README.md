# Terrible_Ticket_Tracker

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A ticket tracking system so you customers can complain and you can continue to
ignore them while their tickets appear to be worked on.

### Feature List

This service provides a series of commands for ticket issuers and ticker takers.
* Hire support person
* Fire support person
* Add ticket
* View tickets by status
* Cancel Ticket
* Check status of ticket
* List support persons status
* List free support persons
* Quit

## Vulnerability
### Vuln 1

When a ticket is successfully resolved by a worker a notification is sent that
include the worker id and the description of the ticket. The printing of the
description is done by `print(desc)` and therefore allows for a type 2 vulnerability.

#### Generic class of vulnerability

CWE-134 Use of Externally-Controlled Format String

#### Challenges

  - The duration that a ticket is in a work queue is sourced from the magic page so CRSs will have produce POVs that handle this.
  - The commands that CRS can use to interact with the system are very high level.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: medium
 - **Patching**: easy
