# COLLIDEOSCOPE

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
COLLIDEOSCOPE brings convenient four-function signed 32-bit integer math to your
fingertips! Now supporting pointer types and variables. Enter in arbitrary
algebraic expressions and let us do the hard math for you!

### Feature List
- Parses algebraic expressions containing integer values and common arithmatic
  functions
- Create variables consisting of up to 4 lowercase characters for storing past
  results
- Convenient workbook functionality by storing past results in a special
  variable
- Reference variables by taking and dereferencing pointers
- Operator precedence and parenthesis supported
- Supports addition, subtraction, multiplication, division and negation

## Vulnerability 1
This program differentiates between pointer variables and integer variables
who's values are stored in a hash table. Upon assigning the incorrect typed
value to an existing variable, a new variable with that name will be created
with the new type, and the old variable will have its type field clobbered while
persisting its old value. As lookups will prefer the first created variable,
this can be used to gain arbitrary read and write access to the processes'
memory space.

### Generic class of vulnerability
Type confusion

### CWE classification
CWE-119 Improper restriction of operations within the bounds of a memory buffer
CWE-703 Improper check or handling of exceptional conditions
CWE-704 Incorrect type conversion or cast
CWE-843 Access of resource using incompatible type

### Challenges
- The tool requires well-formed algebraic expressions in order to provide
  meaningful results, requiring passing a tokenization stage and parsing stage
  prior to reaching the vulnerability in the evaluation stage, increasing the
  difficulty of random fuzzing.
- Successfully exercising the vulnerability requires manipulation of the
  calculator's variable space over several successful operations with a
  particular structure.
- Bounds checks inserted around the variable dereferencing logic may be
  effective in fixing this vulnerability, once the proper patching location is
  identified by overcoming the above challenges.

### Difficulty
- Discovering is hard
- Proving is medium 
- Fixing is easy

## Vulnerability 2
The negation operator of this program does not correctly update the type of its
destination argument field, allowing an attacker to negate an integer and assign
the resulting value to a pointer variable, allowing arbitrary read and write
access to the processes memory space.

### Generic class of vulnerability
Type confusion

### CWE classification
CWE-119 Improper restriction of operations within the bounds of a memory buffer
CWE-703 Improper check or handling of exceptional conditions
CWE-704 Incorrect type conversion or cast
CWE-843 Access of resource using incompatible type

### Challenges
- All of the challenges for vulnerability 1 also apply to this vulnerability
- Control over the pointer value is limited by the range of signed integer
  types, would need to nest negations in order to dereference a pointer in the
  flag page for instance
- A very specific set of operations is needed to exercise this vulnerability,
  namely negating a value at the top level then dereferencing the result
  variable before its type field is clobbered.
- Bounds checks in the proper locations could also address this vulnerability.

### Difficulty
- Discovering is hard
- Proving is medium
- Fixing is easy

