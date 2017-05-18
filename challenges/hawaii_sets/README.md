# CGC Challenge Binary Template

## Author Information

"John Berry" <hj@cromulence.co>

### DARPA performer group
Cromulence

## Description

A user can instantiate new sets and combine them via Union, Intersect, Set Difference, and Symmetric Difference. Additionally it can tell a user if a set is a subset of another.

### Feature List

A user can create a new set with up to 15 elements. An element can be an existing set or an alphanumeric value with a maximum length of 10.

New sets can also be created via the Union (+), Intersection (^), Set Difference (-), or Symmetric Difference (~) operators.

A set can be checked if it is the subset of another via the (@) operator.

A user can print a help screen with the '.h' command.
A user can print all current sets with the '.p' command.
A user can print a particular set with all subsets expanded via the '.ps' command.
A user can exit the program via the '.l' command.

## Vulnerability

There are two vulnerabilities in this service. The first is a stack buffer overflow. 

A set can contain another set as one of its elements which would look like this:

> setone = |"hello", "world"|
> settwo = |setone|

Executing the '.p' command would print both sets with any expansion like this:

> .p
setone = |"hello","world"|
settwo = |setone|

To expand any set elements a user can use the '.ps' command though this one requires a set name as an argument like this:

> .ps settwo
settwo = ||"hello","world"||

The string printed by '.ps' is created via recursively expanding all elements that are sets. So, something like this:

> setone = |"hello"|
> settwo = |"world",setone|
> setthree = |setone, settwo, "yo"|
> .ps setthree
setthree = ||"hello"|,|"world",|"hello"||,"yo"|

Both setone and settwo were expanded. Additionally, setone was expanded within settwo.

The expanded string is copied into a statically allocated stack-based buffer. If an attacker could force this expansion to be greater than that value then the overflow will occur and result in a SIGSEGV. However, to make this more difficult, the size of the buffer was calculated to ensure that a minimum of three recursive calls are required to fill be buffer.

Each individual set has a maximum size of 196 bytes:

2 Bytes for the beginning ending '|'
14 Bytes for commas with a maximum of 15 elements
30 Bytes for '"' since each element can have two quotes
150 Bytes for the element data 15*10.

Giving a total of 196. However, if each element of a set were in fact a subset with a maximum of 196 bytes the result would be:

46 Bytes of overhead i.e. commas, quotes and pipes
196*15 = 2940

Add to this a maximum set name length of 16 plus 3 bytes for the ' = ' and you have 2999. For this reason the data length was set to 3200 to ensure at least three total calls to the vulnerable function.

The second vulnerability is a stack overflow caused by infinite recursion exhausting the stack. This occurs when two sets are created that contain a reference to each other. When either of the sets is printed with the .ps command the print_subsets function will call itself recursively until the stack overflow leads to a crash. 

### Generic class of vulnerability
Stack-based buffer overflow
Stack overflow due to infinite recursion. 

### CWE classification
CWE-120 Buffer copy without checking size of input
CWE-400 Uncontrolled Resource Consumption

## Challenges

The major challenge for this CB, aside from deciphering the set operations is that the CGC competitor will be forced to reason about recursive functions to cause an overflow.
