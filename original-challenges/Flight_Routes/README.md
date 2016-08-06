# Flight Routes

## Author Information

"Steve Wood" <swood@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service implements a flight planner tool where least cost or least duration flights can be found in a database of airports and their connections to other airports.

### Feature List
Upon its initial start, the service loads airport and connection info from its "database", which in this case is the magic page of data.  After this point, users are allowed to enter new airports and connetions, list all airports or a selected airport, delete airports, and find routes from one endpoint to another.


## Vulnerability
The service contains two vulnerabilities that relate commands being supplied by the user.  For Vulnerability 1, the feature to batch add a new airport and all of its connecting airports is exploited.  Although the input command is sanity checked for many formatting issues, the maximum number of connecting airports is not checked.  As the command is parsed, connection info is copied into a fixed sized array, which can eventually overwrite locals on the stack.  One of the locals is an index into the array used to dereference writes.  This can be used to overwrite the saved values of EBP and EIP in the stack frame.  

The deleteAirport function takes a command argument of the target airport code to delete.  Vulnerability 2 occurs because data in command buffer is not properly checked for length before being copied into a local variable.  In this case, the data entered can be directly copied over the stack frame--overwriting EBP and EIP.

### Generic class of vulnerability
Stack buffer overflow

### CWE classification
CWE-121 Stack-based buffer overflow

## Challenges

Vulnerability 1 is a straightforward buffer overflow and should be easy to detect.  However the length of the incoming data buffer is not long enough to directly overwrite anything that allows for control of the service to be subverted.  Most of the local variables overwritten are also initialized later before they are used.  However, one variable can be overwritten to cause the next write to happen on the stack frame's saved registers.  The challenge is detecting this indirect method over overwriting the stack, and crafting an input that is well-formed enough to pass the validation checks necessary to keep the function for returning early with an error code.  Although there are some challenges, this vulnerability is only medium difficulty.

	Finding Vulnerability 1: easy
	Proving Vulnerability 1: medium
	Fixing Vulnerability 1: easy

Vulnerability 2 is the simplest of stack smashes and really provides little challenge other than ensuring the buffer is NULL and Newline safe.

	Find Vulnerability 2: easy
	Proving Vulnerability 2: easy
	Fixing Vulnerability 2: easy

