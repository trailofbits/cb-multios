# CGC Challenge Binary 00024 - String Storage and Retrieval

## Author Information

Steve Wood <swood@cromulence.co>

### DARPA performer group

Cromulence

## Description

The program is an application for the storage and quick retrieval of string data.  Internally, a token is created for each string and the token is used as the key for a Binary Search Tree where the data is stored.  This allows for very quick retrieval of strings, provided that data is not stored in such a sequence that the tree degenerates into a linked list.  Most BST's do not allow for duplicate keys, but this implimentation does, storing the data common to one key in a linked list that must be sequentially searched.  However, key collisions should be rare and therefore sequential searches very short.  In addition, identical string data is not allowed, further limiting the possibility of key overlap.  

### Feature List

The program allows for strings to be a)dded, d)eleted, f)ound, the entire tree to be w)alked, and tree s)tatistics to be printed. Strings are added by the command a/<string to be added> for example.  Strings to be added must be at least 10 characters in width.

## Vulnerability

The vulnerability occurs in the processing of how data for duplicate keys is handled.  If more than one data element resolves to the same key, the data items are stored in a linked list attached to that that BST node.  During find or delete operations, they key is used to rapidly find the node and the attached linked list is sequentially walked and the string data compared to that being searched for.  If a match is found, the operation completes.  The vulnerability lies in an improper update of a pointer during a delete operation.  If there is a linked list, and the last node of the list is being deleted, the current pointer is updated to the "next" pointer before the memory is released with free().  At the end of the list, this causes a null pointer to be passed to free(), resulting in a SEGFAULT.


### Generic class of vulnerability

NULL Pointer Dereference.

### CWE classification

CWE-476

## Challenges

This vulnerability requires two steps to demonstrate it crashing the program.  First two values with the same resulting token must be found, and then the second and only the second one being deleted will result in a SEGFAULT.  It is certainly an "edge case" condition for the program that would not readily show up with purely random fuzzing.





