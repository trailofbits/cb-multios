# KPRCA-00049

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a simple note taking program.

### Feature List

The following commands are supported by the server.

  * new-note $NAME $CONTENT: Create a new note named $NAME and store $CONTENT in it.

  * append-note $NAME $CONTENT: If a note with name $NAME exists then append $CONTENT to its content.

  * delete-note $NAME: If a note with name $NAME exists then delete it.

  * get-note $NAME: If a note with name $NAME exists then return its contents.

In order to provide a responsive interface this service delays the running of
both the delete and append actions until they are necessarily needed by the
result of some other command. This cuts down on processing time and provides
the user with a fluid and intuitive experience.

## Vulnerability

The first vulnerability is a result of that when processing delayed actions the
call stack grows with the order of delayed actions. It is therefore possible
for an attacker to create a pathological usage case where number of delayed
actions grows exceptionally large and the stack space is exhausted during
runtime.

The second vulnerability is a result of that when appending to a note the
amount that a note's data buffer is grown is a fixed ratio which can result in
a heap overflow if the data being appended is larger than this ratio.

### Generic class of vulnerability

  * Recursion
  * Excessive nested function calls
  * Overflow

### CWE classification

  * CWE-122: Heap-based Buffer Overflow
  * CWE-674: Uncontrolled Recursion

## Challenges

The challenge binary poses tests the following abilities of a system:

  * Ability to detect issues due to excessive stack space usage
  * Ability to construct control flows that result in excessive stack space usage
