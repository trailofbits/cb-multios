# Venture_Calculator

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A command line visual stack-based performant RPN calculator. Leveraging the old
to build the new. Guaranteed to net a mad series A.

### Feature List

Support for variety of useful operations:
  
  - `+`
  - `-`
  - `*`
  - `/`
  - `!`
  - `neg`
  - `abs`
  - `mod`
  - `&`
  - `|`
  - `^`
  - `~`
  - `sum`
  - `avg`
  - `dup`
  - `dupn`
  - `dupr`
  - `min`
  - `max`
  - `depth`
  - `drop`
  - `dropn`
  - `undo (we keep a history!)`
  - `ivrt (invert stack, super useful!)`
  - `shuf (shuffle stack, even more useful!)`

Only signed 32bit integers are currently supported, but our
rockst^H^H^H^H^H^Hdevelopers are working on 64bit support and maybe even floats
soon!

## Vulnerability
### Vuln 1

In the `shuf` function, random bytes are loaded from the secret page and then
predictably scrambled. The resulting scrambled bytes are utilized to shuffle
the stack.

In the `dupr` function, the passed position and length arguments are converted
to 16bit unsigned integers and then added to form a slice into the current
stack. The values used to form the index are checked, but the invalidation
routine is faulty.  The resulting indexed values are then pushed onto the
stack. This gives an attacker the ability to load values out of memory within
a limited distance from `Vector` in the `VC` class and push them onto the
`CalcStack` where they will then be printed out.

If the random bytes loaded for the shuffle function are left in memory within
a short enough distance from the accesses made in the `dupr` function, an
attacker could leak secret page data out of the problem.

#### Generic class of vulnerability

Improper cleansing and leaking of sensitive data.

#### CWE classification

  - CWE-125: Out-of-bounds Read
  - CWE-129: Improper Validation of Array Index
  - CWE-398: Indicator of Poor Code Quality

#### Challenges

 - Performing the required heap manipulation to place the secret page data with reach of the out-of-bounds read.

#### Difficulty

 - **Discovery**: Easy
 - **Proving**: Medium
 - **Patching**: Easy
