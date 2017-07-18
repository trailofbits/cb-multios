# Pattern_Finder

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Pattern Finder is a service that user to quickly detect the presence of a set
of known patterns within a blob of data.

The service first reads in a series of pattern definitions from the user. It
then compiles a pattern search machine that will be used to detect patterns in
subsequently data entered by the user. The user is provided with a list of
detected patterns once the search machine has finished running.

### Feature List

 * Supports up to 4096 patterns
 * Supports patterns up 4096 bytes in size
 * Supports detecting patterns in up to 64 kilobytes of input
 * Super fast!

## Vulnerability

### Vulnerability 1

In the ReportMatches function, the stack buffer where the report contents are
gathered before being sent to the user is a fixed 512 bytes in size. Therefore,
a stack buffer overflow is achievable given a large enough set of patterns and
a data blob which contains enough of these patterns to generate a sufficiently
large report.

#### Generic class of vulnerability

Stack buffer overflow

#### CWE classification

CWE-121 Stack-based Buffer Overflow
CWE-787 Out-of-bounds Write

#### Challenges

The complexity behind this challenge lies within the underlying algorithm which
is used to do pattern detection. The algorithm used is Aho-Corasick which is
a string matching algorithm that allows for the simultaneous matching of
patterns through the use of a finite state machine. The author imagines that
sufficiently complex algorithms will test the strength of many code analysis 
engines.

#### Difficulty

 - **Discovery**: Easy
 - **Proving**: Hard
 - **Patching**: Medium
