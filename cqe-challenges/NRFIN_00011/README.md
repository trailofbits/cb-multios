# GREYMATTER Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

The megalomaniacal mice are at it again.  This time, the plan is to develop mind-controlling cheese.  And who doesn't like cheese.

While this may sound like a simple enough task, it turns out the manufacture of mind-controlling cheese requires the ability to fold proteins in a precise manner.  The problem is, such folding computations require a lot of compute power.

The mice have a solution: build a botnet!

### Feature List

The CB requests an HTML-like index page from the CRS.  The CRS responds to this request with a document that links to further resources necessary to render the complete document.  These further resources are specified as paths.  If certain constraints on the paths are satisfied, a vulnerable path canonicalization function is called.

## Vulnerability

This CB is inspired by MS08-067 - a stack-based buffer overflow "proven vulnerable" in the wild by the Conficker worm.  The vulnerability is caused by an improperly guarded call to wcscat() in the Server Service daemon on Microsoft Windows platforms during path canonicalization routines.  Exploitation involved the repeated cat'ing of attacker-provided data into a statically-sized buffer.

In contrast to Conficker's method of "vulnerability proving", this CB acts as a client and requests HTML-like data from the CRS, more closely emulating something like Internet Explorer than Server Service.

This CB is intended to be relatively simple to "prove vulnerable".

### CWE classification

120: Buffer Overflow
121: Stack-Based Buffer Overflow

## Challenges

* Reasoning about strings that are terminated with something other than NULLs.
* Seemingly-correct security checks are in place.  The challenge will be to find that the security checks are inadequate, which demands reasoning across calls to strncat().
* Satisfying the constraints necessary to hit the vulnerable code, including size checks and string matches against expected traffic.
