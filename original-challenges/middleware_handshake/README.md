# KPRCA-00034

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a basic ecommerce app on top of middleware that is responsible for negotiating the underlying communication channel. The middleware supports several encodings and is app-agnostic, so it can be easily ported to other apps.

### Feature List

The ecommerce app utilizes fixed point numbers which results in higher accuracy for transactions. Basic security prevents another seller from replacing your product in the app. The database is implemented with a O(1) algorithm for more speed. And with the sophisticated underlying middleware, nobody will be able to figure out how to even connect. A big plus for security!

## Vulnerability

The vulnerability, **main.c:123**, is a classic printf vulnerability where an attacker can control a format string. The format string is only printed to STDERR, so the attacker will not see its output, but the attacker can still cause a crash. It is likely that the vulnerability can lead to remote code execution by turning it into a 4-byte write-anywhere primitive.

### Generic class of vulnerability
Arbitrary format string

### CWE classification
CWE-134: Uncontrolled Format Sting

## Challenges

The goal of this challenge set was to use inlining and macros to increase the code size. In terms of LOC, it is about 3 times larger than the average code size of other KPRCA challenge sets. In addition to LOC, the challenge set also has a lot of preprocessing that will slow down attempts to analyze with a symbolic executor and fuzzing, to a lesser extent. The release pollers include a simple case that should be trivially modifiable to get to a crashing input, in order to make the challenge set easier.
