# CGC Challenge Binary Template

## Author Information

"Jason L. Wright" <jason@thought.net>

### DARPA performer group

Thought Networks (TNETS)

## Description
Virtual pet ownership.

### Feature List

This services allows the user to create virtual pets and have them
perform a few rudimentary tricks.  When a pet becomes too annoying,
it can be deleted.

## Vulnerability

Normally a pet is given a name right after it is created and never
renamed. However, there's a bug in this program: when you rename a pet
it appends to the current name.  An annoyance to be sure, but worse, it
allows for spilling into an adjacent C++ vtable.

To make life easier for the programmer (not the user), a "debug" trick
can be performed which displays the address of each of the pet's "this"
pointer.

### Generic class of vulnerability

Heap-based Buffer Overflow

### CWE classification

CWE-122: Heap based Buffer Overflow

## Challenges

This CB is primarily provided to demonstrate the use of C++ as a challenge
binary language.  Several language features are used (static constructors/
destructors, virtual functions, overloading, etc.). Several features are
explicitly not used: runtime type information (RTTI) and exceptions.

Future versions of this CB may use RTTI (it's not that hard to implement),
but exceptions look painful (though libcgc.a now has setjmp/longjmp...).

The overflow is easy enough to create: it requires reasoning about the
protocol and realizing that additional names for a pet are blindly
concatenated with the existing name.  To get an exploit working, a valid
vtable must be constructed.  The "debug" trick leaks the value of the
"this" pointer for each pet (this cuts out reasoning about the
"new operator"'s implementation.
