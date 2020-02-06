# CGC Challenge Binary Template

## Author Information

"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is a RPN calculator which allows calculations on several types of
mathematical objects (integers, doubles and matrices).

Commands take the form of a 4-byte command identifier, followed by optional
arguments. Commands may produce output but will always end in a 4-byte success
code, 0 on success or -1 on failure.

When a command requires tagging the type of an operand, it will accept a 4-byte
tag with 0 == integer, 1 == matrix, and 2 == double.

Internally, each type is represented using tagged values packed into a double,
with integers and matrices represented by NaN values.

### Feature List

The following commands are available:
 - Push operand (integer, double or matrix)
 - Pop result (integer, double or matrix)
 - Clear stack
 - Add top two operands and push result
 - Subtract top two operands and push result
 - Multiply top two operands and push result
 - Divide top two operands and push result
 - Invert matrix and push result

## Vulnerability

The system does not correctly check for floating point overflow in all cases,
allowing crafted operands which will lead to type confusion. Due to the manner
in which matrices are stored (pointers packed into a double), corrupting a
rpnval to contain an arbitrary address may allow for read/write access to a
significant portion of the process' memory space.

There is also an out of bounds read due to reversal of two array indices in
multiply, which can be triggered by multiplying to matrices such that memory
outside of the data buffer of the result matrix is accessed.

### Generic class of vulnerability
Type confusion
Divide by zero
Integer overflow

### CWE classification
CWE-125 Out of bound read
CWE-190 Integer overflow or wraparound
CWE-369 Divide by zero
CWE-682 Incorrect calculation
CWE-704 Incorrect type conversion or cast
CWE-843 Access of resource using incompatible type

## Challenges

This CB is designed to test the capabilities of a CRS in handling floating point
arithmetic combined with bit-ops. The technique of packing values of different
types into a floating point type is modeled after several real-world
applications, notably the SpiderMonkey and JavaScriptCore (WebKit) Javascript
engines. Modeling the interactions between floating point operations and
bit-level operations requires a precise modeling of IEEE floating point math and
implementation details specific to the target platform. These capabilities are
necessary for analyzing attacks on commonly-targeted software, such as web
browsers using these Javascript implementations. The out of bounds read models a
copy-paste error which can appear in real-world code; it is relatively deep
inside of the control flow of the CB and depends on the layout of the heap to
cause a crash, increasing the challenge of triggering this vulnerability.

