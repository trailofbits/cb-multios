# EternalPass

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Making passwords is hard. Managing passwords is even harder. So let us do it for you! With EternalPass, you'll only ever need to remember one password, and we'll make the rest for you!

### Feature List

- Create as many single use passwords as you want!
- Automatically generate a secure wallet that you can take anywhere!
- Choose between various security modes appropriate for you!
- For power users, you can even tweak our code to your liking!

## Vulnerability 1

A very simple vulnerability involving use of an unchecked function pointer, directly provided by the user, in the password generation function.
This function is passed a user-provided seed, which is fully controlled by the user.
The only caveat is that the function pointer must be decimal encoded and greater than 0x08000000.

### Generic class of vulnerability

Untrusted pointer use

### CWE classification

CWE-822 Untrusted pointer dereference

### Challenges

* Dealing with large amount of irrelevant but complex constraints 
* Successfully encoding the function pointer.

### Difficulty

* Discovery: easy
* Proving: easy
* Patching: easy

## Vulnerability 2

Almost identical to the first vulnerability, but the user no longer directly controls any
arguments in the vulnerable function pointer call.
It is possible, however, to successfully control a register using the highest byte of each of four subsequent calls to CRC32 on dynamically generated strings (which they can select, but do not control).
Alternatively, it may be possible to solve this by jumping to various useful gadgets in the binary.

### Generic class of vulnerability

Untrusted pointer use

### CWE classification

CWE-822 Untrusted pointer dereference

### Challenges

* Dealing with a large number of relevant and complex constraints.
* Successfully encoding the register value using a series of indexes, which select strings to be CRC32d, which then build the final register value.
* Finding alternative, non-intended methods of proving vulnerability using only control of EIP.

### Difficulty

* Discovery: easy
* Proving: hard
* Patching: easy
