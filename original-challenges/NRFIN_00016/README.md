# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

ValveChecks is SafeTechs' latest and greatest industrial control system, utilizing industry-leading SomeChecks integrity-assurance technology and a unique, high-security remote management system.


### Feature List

We here at SafeTechs are committed to designing the safest, most resilient, and most reliable industrial control systems the world has ever seen.
We are so dedicated to this task, that each of our hundreds of products employ a unique integrity-assurance technology called SomeChecks, which ensures to the highest degree that received control messages are valid and unharmed.


## Vulnerability

This CB contains six different vulnerabilities, each a variation of a classic buffer overflow.
Each, however, presents a different, unique challenge to competitors trying to discover and patch them, and will help separate them based on their skills at various tasks.


1.) Buffer overflow in admin\_add\_login due to a signed to unsigned conversion problem.
The buffer is checked to see if it is greater than 127; however, if the number is negative it will be coerced into a value greater than 128 in the memcpy, leading to a stack buffer overflow.
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
Mitigations like stack cookies would also likely prevent a crash.
To prove this vulnerability, a CRS must be able to satisfy the relatively simple constraints of an additive checksum function.

2.) Buffer overflow in admin\_addxoradd\_login due to a call to strcpy with unsanitized user input as the source.
This vulnerability is a classic strcpy overflow; the bounds are not properly checked before copying user-provided data to the stack.
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
Mitigations like stack cookies would also likely prevent a crash.
To prove this vulnerability, a CRS must be able to satisfy the somewhat more complex constraints of a multi-step checksum function, as well as correctly calculate any previous checksums.

3.) Buffer overflow in admin\_crc\_login due to an integer underflow.
This vulnerability is yet another classic overflow, due to an integer underflow prior to a copy loop.
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
Mitigations like stack cookies would also likely prevent a crash.
To prove this vulnerability, a CRS must be able to solve the fairly complex constraints of a CRC function (which uses a non-standard initial CRC), as well as correctly calculate any previous checksums.

4.) Buffer overflow in admin\_fp\_login due to improper bounds checking.
This vulnerability is a fairly straightforward overflow, complicated by the use of a floating-point number as the control variable inside a copy loop.
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
Mitigations like stack cookies would also likely prevent a crash.
To prove this vulnerability, a CRS must be able to formulate and satisfy somewhat simple constraints based on floating-point numbers, as well as correctly calculate any previous checksums.

5.) Buffer overflow in admin\_md5\_login due to a call to strcpy with unsanitized user input as the source.
This vulnerability is a very simple stack overflow, as simply reaching the function for a CRS will be very difficult
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
Mitigations like stack cookies would also likely prevent a crash.
To prove this vulnerability, a CRS must be able to correctly determine that the hash that must be matched is the hash of the string "admin", as well as correctly calculate any previous checksums.
This problem, while simple for a human reverse engineer, will be extremely difficult for a CRS.

6.) Buffer overflow in redacted due to improper bounds checking.
This vulnerability is very similar to the overflow in admin\_add\_login, except it is overflowing a global variable rather than a local stack variable.
To patch this vulnerability, a system needs to either properly restrict bounds or remove the vulnerable copy entirely.
To prove this vulnerability, a CRS must be able to correctly calculate all the checksums necessary to reach this path, as well as generate a simple input that triggers the issue.

### Generic class of vulnerability

Buffer overflow
Out-of-bounds write

### CWE classification

CWE-120: Buffer copy without Checking Size of Input
CWE-121: Stack-based buffer overflow
CWE-191: Integer Underflow
CWE-195: Signed to Unsigned Conversion error

## Challenges

This CB presents a large number of different challenges to competitors, in order to better gauge their relative skill at defeating checksums, SAT solving, handling floating-point numbers,and discovering and patching various simple vulnerabilities.

We expect the following, in order of increasing difficulty, to set competitors apart:

1.) Ability to find and, more importantly, patch, simple vulnerabilities in code.
Many of these vulnerabilities are trivial to uncover statically, and we expect most competitors will be able to discover at least one of these in issues during analysis.
However, their ability to patch the vulnerabilities correctly will likely be much more stratifying.

2.) Ability to form and solve the constraints necessary to prove vulnerability.
Four of the vulnerabilities in this CB could reasonably be proved by forming and solving symbolic constraints necessary to reach the vulnerability.
These paths were crafted to increase in difficulty to help determine which CRSs are better at performing this critical task.
It is unlikely any of these will be solved using purely dynamic analysis, as the search space for each is likely prohibitive for fuzzing.

3.) Ability to handle floating-point calculations with some level of correctness.
Current SMT solvers have a large amount of difficulty with floating-point calculations of any kind.
The standard itself is quite complex, and behavior can vary in unintuitive ways.
To prove vulnerability in one part of the challenge, a CRS will need to have advanced the state-of-the-art analysis techniques sufficiently to solve a simple floating-point based additive checksum and correctly handle a loop using floating-point numbers as control variables. 
We expect this will be quite difficult, but will be impressive if solved.

4.) Ability to bypass an MD5 hash check that is trivial for a human analyst.
Even an inexperienced reverse engineer would very quickly realize and bypass this check (the first five bytes must be "admin").
However, we do not anticipate any competitors will be able to solve this portion of the challenge using current techniques.
It was included as an example of a simple, similar situation that is still unapproachable today but might be solvable in the future.
As a bonus, it will help better separate competitors that recognize and ignore impossible/extremely difficult symbolic constraints.
