# CGC Challenge Binary 00014 - SCUBA Dive Logging program

## Author Information

Steve Wood <swood@cromulence.co>

### DARPA performer group
Cromulence

## Description

This challenge binary implements an application for logging a single SCUBA diver's dive activity.  

### Feature List

Dives can be manually entered, edited, removed, and displayed.  In addition, the application also has the ability to download log data from a simulated dive computer.  Statistics are also calculated over the entire log of dives and displayed.


## Vulnerability
Two programming errors have intentionally been inserted into the application.

The first vulnerability is a string buffer overwrite in the edit_dive() function.  All inputs are first read into a temp buffer before being copied to the final buffer in the log data structure.  When dives are initially entered, all inputs are limited to the size of the final destination buffer.  However, in the edit_dive function, the input for dive site is mistakenly limited to the size of the overly large temp buffer, not the final buffer.  A sufficiently large string will overwrite several other members of the data structure.  The final member of this structure is the pointer to the next dive in the linked list.  The next time the dive log list is accessed (by adding a new dive, editing an existing dive, removing a dive, or simply displaying the log), a dereference of this corrrupted pointer will cause a segfault.   

The vulnerability is in update_dive() at edit_dives.c:121.  

The second vulnerability is in the download_dive() function at download_dive.c:185.  When dive computer data is downloaded, the samples, consisting of a timestamp and depth, are collected into a linked list.  The first and last samples are used to calculate the overall duration of the dive.  This duration is used to dynamically allocate an array of 1 minute bins.  Another pass through the linked list ensues, and the timestamp for each sample is used to calculate which bin it belongs to.  The vulnerability is that the timestamp values are not sanity checked and a corrupt one can result in an array offset that is outside the allocated memory.  

### Generic class of vulnerability
Vuln #1: Heap Buffer Overflow
Vuln #2: Out of Bounds Array Pointer

### CWE classification
CWE-122 Heap Buffer Overflow
CWE-129 Improper Validation of Array Index

## Challenges

It takes two steps to reach the first vulnerability.  First, a dive has to be entered either by downloading it or manually entering it.  Then, the dive must be edited.  While editing, the Dive Location input can be overflowed to overwrite the pointer to the next entry in the linked list.  One more step is required to actually demonstrate the vulnerability.  Any additional function that requires the dive list to be enumerated will walk the linked list and will attempt to dereference the bad pointer.

The second vulnerability has a much shorter code path to reach it.  User data is directly used to calculate an offset into an array making this a fairly straightforward bug to find and reach.




