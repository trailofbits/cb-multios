# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
This service is a simple stack-based virtual machine for your programming pleasure. Using the commands PUSH, POP, ADD, PRINT and COPY you can construct simple programs that the virtual machine will execute on your behalf. 


### Feature List
The service accepts commands that allow you to create and execute programs. After instructing the service to create a new program of a specific size, the service will accept up to that many lines of code and store it for you. Once you are all done submitting programs, you can specify the program number of the program you want to execute.

PUSH pushes the value on top of the stack
POP removes the top value from the stack
ADD will remove the top two values from the stack, adds them together and pushes the result on top top of the stack
PRINT will remove the top value from the stack and send it to STDOUT
COPY will remove the top value from the stack and push a requested number of copies of the value on top of the stack

## Vulnerability
This service has two vulnerabilities.

The first one allows the client to try and execute a program with a negative program number due to a missing check for negative program numbers. This results in an out-of-bounds read.

The second vulnerability is an off-by-one error that allows the VM's stack to overflow by one value. By overflowing the stack one can overwrite the 'size' attribute of a program. The 'size' attribute stipulates how many lines are in the program. This will cause the program to continue advancing line numbers until it attempts to read a portion of memory that is out-of-bounds. 

### Generic class of vulnerability
Off-by-one Error
Stack-based Buffer Overflow
Heap-based Buffer Overflow
Out-of-bounds Read

### CWE classification
Off-by-one Error
CWE-193
Stack-based Buffer Overflow
CWE-121
Heap-based Buffer Overflow
CWE-122
Out-of-bounds Read
CWE-125


## Challenges
* Must determine how the interpreter works in order to construct a valid program.
* Must understand how the stack used when executing a program is stored relative to the program being executed on the heap.
* Must construct a program that causes the stack to overflow and overwrite the 'size' attribute of the executing program.
