# KPRCA-00028

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a command line evaluation engine for a programming
language referred to as SLUR. The service takes in a SLUR expression and
evaluates it, returning the evaluated expression back to the user. The SLUR
language is based off of lists. Each expression is itself a list, expressions
are written usually to modify or build lists in some interesting way. The SLUR
evaluation engine we provide supports of series of primitive functions which
the user can use to build their programs. In addition to functions and lists,
SLUR also has the concept of atoms which are strings of characters and numbers
that aren't the names of functions. Formally, a list is a parenthesis pair,
enclosing zero or more atoms or lists.

### Feature List

The built in functions are as follow:
	* (quote e) returns e
	* (cons e1 e2) returns the list formed by prepending e1 onto e2
	* (car e) returns the first element of the list e
	* (cdr e) returns all the elements of the list e minus the first one
	* (atom e) returns `t` if e is an atom else returns `nil`
	* (cond (p1 e1) ... (pn en)) returns the first e whose p is `t`
	* (equal e1 e2) returns `t` if e1 = e2 else returns `nil`
	* ((lambda (v1 ... vn) e) e1 ... en) returns e evaluated in the
	  environment where v1 -> e1, ... vn -> en.
 
Our SLUR machine also implements CAKE reduction functionality in the lambda
function. If the result of our evaluated lambda is a list consisting of the
atom "CAKE" repeated 4 times it appends the atom "That's a lot of CAKE!" to the
list.

## Vulnerability

The first vulnerability is trigged in the CAKE reduction functionality. The reduction
functionality has a flaw (eval.c:328) where it incorrectly appends to the internal
list structure representing a SLUR list. It is possible for an attacker to trigger
a null pointer dereference in cases where the CAKE reduction is being performed at
the end of the list, i.e. where the tail of the list is NULL.

The second vulnerability is triggered the lambda functionality. When
substituting symbols in the enclosing lambda, the substitution code does
correctly validate that the object it is attempting to compare to the symbol it
is substituting for which can result in a NULL pointer dereference due to
assumptions the code makes about the state of values in the struct representing
the object.

### Generic class of vulnerability
Null Pointer Dereference
Type Confusion

### CWE classification
CWE-476: Null Pointer Dereference
CWE-843: Access of Resource Using Incompatible Type ('Type Confusion')

## Challenges

In order to trigger the vulnerability, the attacker must be able to successful
build a program that triggers the CAKE reduction functionality. This requires
the attacker to understand how the internal structure of the SLUR lists are
used, how the lambda function evaluates its arguments, and that 4 CAKE atoms
must be present for the vulnerability to the triggered.
