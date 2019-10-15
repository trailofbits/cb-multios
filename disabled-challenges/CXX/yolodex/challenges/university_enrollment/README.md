### DARPA performer group
Kaprica Security (KPRCA)

## Description

This application allows a user to sign up for university classes. It will check for scheduling conflicts
as well as enforce university rules, such as limiting the number of credits taken per semester,
limiting the number of in major classes, and forcing a student to take classes with 3 or more credits
unless it is an in major class.

### Feature List
The application lets a student add classes for the semester. In doing so the student can search for classes
by its Course number, Course Id or professor. Once a student finds a class or classes, he or she can
add up to 7 classes to his or her schedule.

1 - Search Classes
2 - Add Class
3 - Remove Class
4 - Print Schedule
5 - Exit

## Vulnerability

The first vulnerability is due to a bad bounds check. If a user can add enough low credit classes it's possible
to overflow the array containing the list of classes. This may allow the attacker to overwrite a function 
pointer.

The second vulnerability is due to a order of operations error. It's possible to overwrite a byte in the global
g_all_profs variable. The bug is due to readline checking the buf size bounds after the read, instead of before,
allowing 1025 bytes to be written, instead of 1024.

### Generic class of vulnerability

Buffer Overflow

### CWE classification

Operator Precedence Logic Error (CWE-783)
Heap-Based Buffer Overflow (CWE-122)

## Challenges

This binary has been built with a lot of data embedded in it. It's slightly larger than the average CGC
binary, coming in at close to .5 MB. The data itself is always referenced by pointers in order to avoid additional creation on the heap. The CB's goal is to be able to ensure a time can navigate through large text sections.

Overwriting the single byte in the professor address only affects the system if the user then tries to search by professors after.
