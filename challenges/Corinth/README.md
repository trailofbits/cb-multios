# Corinth

## Author Information

"Bryce Kerley" <bk@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

This binary accepts tuning parameters for a homemade PRNG, validates their
randomness with a Monte Carlo method to calculate pi, and uses the PRNG to
size a stack buffer for a relatively simple buffer overflow.

### Feature List

* Floating-point PRNG
* Monte Carlo simulation calculating pi
* Dynamically-sized stack buffer

## Vulnerability
The service implements two tuning parameters for the PRNG. When they're tuned,
they're used to calculate the value of pi, which is then compared with a known
value for accuracy. As the difference shrinks, the limits for a buffer that is
copied are raised, while the buffer size does not grow as rapidly, which allows
the buffer to be overflowed onto the stack.

### Generic class of vulnerability
Stack-based buffer overflow

### CWE classification
CWE-121: Stack-based Buffer Overflow

## Challenges

This CB begins with a requirement to tune parameters for a floating-point
function with some state, including an initial value from the random page. A
CRS will have to adapt its input for any given execution, including deciding on
an expected buffer size range.

### Subjective quantifications
Discovering: easy. Finding the causal connection between the PRNG and
buffer size shouldn't be difficult.
Proving: hard. Controlling the buffer size requires precise inputs to a
complex algorithm using trigonometric functions.
Fixing: easy.
