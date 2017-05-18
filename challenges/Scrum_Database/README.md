# Scrum_Database

## Author Information

"Steve Wood" <swood@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service implements a backend database for a Scrum software development management tool.  As the backend, it doesn't present a user interface, but instead provides a binary protocol for a frontend application to use.

### Feature List

The database is designed to store a number of "products" and the requirements and tasks associated with their Agile development.  Once a Product is defined, user requirements are stored in the Product Backlog.  Sprints are also added to the Product to group user requirements into small blocks of development & test efforts.  Requirements are moved from the Product Backlog to one of the defined Sprints.  Once assigned to a Sprint, these Sprint Backlog Items can be updated to reflect changes that naturally occur during development as complexity and requirements are better understood.  Backlog items can only be changed if they are assigned to a Sprint!  However, Backlog items (requriements) can only be deleted from a Product if they are not assigned to a Sprint, i.e. they are on the Product Backlog.  Sprints can also be deleted from the Product, but only if all Backlog items have been moved back to the Product Backlog or to another Sprint.  This is to avoid the inadvertent deletion of user requirements or Product developement tasks.  The only exception to this is if the Product itself is being deleted.  In this case, all Product details, including populated Sprints are deleted from the database. The database tool will also output the entire Product in a consolidated report that lists Product, Sprint, and Product Backlog details.

## Vulnerability
Vulnerability 1 is a buffer overflow that occurs when a Sprint Backlog item's text description field is updated.  To conserve memory, the database allocates at runtime only the amount of memory needed to store a string.  Unfortunately, the function to update the item's description field fails to reallocate a new string and simply reuses the previous one.  If the new string is longer than the original string, heap memory is overwritten.  By controlling the order in which items are added to the database, and then performing the overflow, a linked list's next pointer can be overwritten and directed to the secret memory page.  The provided POV causes the list of Product Backlog items to point to this memory.  When the Product details are displayed, some of this secret data is interpreted as a backlog item, thus leaking memory from this page.

### Generic class of vulnerability
Heap buffer overflow

### CWE classification
CWE-122 Heap-based Buffer Overflow

## Challenges

Vulnerability 1 is a straightforward buffer overflow and should be easy to detect.  To successfully exploit it, the heap must be groomed in such a way that a useful pointer is overwritten and without causing read violation to occur when text fields from the database are accessed.  In addition, the vulnerability is only reachable once several specific operations have been performed in the database that allow for the function to update the text description field to be called.  The ideal fix for the vulnerability is to properly allocated more memory for the new string, but the simplest mitigation is to fail the function call.

	Finding Vulnerability 1: easy
	Proving Vulnerability 1: medium
	Fixing Vulnerability 1: medium

