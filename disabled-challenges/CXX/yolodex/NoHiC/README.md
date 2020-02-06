# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is the Noob High-Precision Calculation Contraption (NoHiC) brought to you by Discount Cyber Cloud Big Data Corp.

This contraption is designed to perform various mathematical operations on lists of numbers. The lists can contain either all integers or all double precision floating point numbers.

### Feature List

The client provides to the contraption a list of numbers and the type of those numbers (signed integer or double precision float). Once the list of numbers is loaded into the contraption, it stands ready to perform various mathematical operations on that list of numbers.

The following are the various operations offered:
* Average/Mean - The average of the numbers in the list.
* Median - The median of the numbers in the sorted list.
* Mode - The list of numbers that occur most frequently (one or more).
* Range - The difference between the maximum and minimum numbers in the list.
* Sum - The sum of the numbers in the list.
* Product - The product of the numbers in the list.
* Minimum - The minimum number in the list.
* Maximum - The maximum number in the list.
* Sort - The list sorted ascending.
* Reverse Sort - The list sorted descending.
* Odds - The odd numbers in the list.
* Evens - The even numbers in the list.

The math operations all use algorithms as would be written by a student in an introductory programming course. Thus, they offer high-precision, ultra-efficiency, and thorough data verification.

The Odds and Evens operations include a bit of fairy dust freshly delivered by Oz himself, which allows the client to perform those operations on floating point numbers. It's AMAZING!

Lastly, performing the equality operation on floating point numbers is fraught with problems. And to make matters worse, in this case, one number is computed in C (CB) and the second number is computed in Python (Poller/Pov). There are many test cases where the least significant digit is different. So, to make the polling work, we ignore the least significant byte in all floating point numbers that are created as the result of a calculation.

## Vulnerability
Where do I start...
In operation.c around line 255, the patched version of the CB has a check to return an error when the num\_count value is 0. This is a test of the value provided by the client indicating how many values are in the number list (i.e. list length). Without this check, many of the math functions in math\_fun.c will cause crashes, because they all expect a list having at least one node. So without the zero list length test, they are vulnerable.

The following discusses for each math function, which are vulnerable when the list has zero nodes, as well as which pov tests for that vulnerability.

math\_fun.c:do\_int\_mean():
- will not cause POV signal; will return 0 as an answer.
- we added a check around the statement at line 47, because when the list length (num\_list->count) is 0, that expression causes an Arithmetic Exception (SIGFPE), which is not a valid POV signal.

math\_fun.c:do\_int\_median():
- SIGSEGV at line 73.
- pov-1.xml

math\_fun.c:do\_int\_mode():
- will not cause POV signal; will return 0 as the count of numbers in the mode. It will not send any mode result numbers.
- If client is waiting to read more than one result, they will get out of sync with the server, because the only result they will get is the nonce that is sent prior to the next command. Thus the read would end with a SIGALRM.

math\_fun.c:do\_int\_range():
- SIGSEGV at line 156.
- pov-2.xml

math\_fun.c:do\_int\_sum():
- will not cause POV signal; will return 0 as an answer.

math\_fun.c:do\_int\_product():
- will not cause POV signal; will return 1 as an answer.

math\_fun.c:do\_int\_min():
- will not cause POV signal; will return 2147483647 as an answer.

math\_fun.c:do\_int\_max():
- will not cause POV signal; will return -2147483646 as an answer.

math\_fun.c:do\_int\_sort():
math\_fun.c:do\_int\_rsort():
- will not cause POV signal; will be a nop. The first value sent to the client will be the nonce that is associated with the next command, but no other values will be sent and thus the client and server will get out of sync. If the client is waiting to read a result, the read will end with a SIGALRM. 

math\_fun.c:do\_int\_odds():
math\_fun.c:do\_int\_evens():
- will not cause POV signal; will return 0 for number of odds/evens, will not return any values. If the client is waiting to read values, the read will end with a SIGALRM.

math\_fun.c:do\_dbl\_mean():
- will not cause POV signal; will return 0.0 as an answer.
- we added a check around the statement at line 352, because when the list length (num\_list->count) is 0, that expression causes an Arithmetic Exception (SIGFPE), which is not a valid POV signal.

math\_fun.c:do\_dbl\_median():
- SIGSEGV at line 376.
- pov-3.xml

math\_fun.c:do\_dbl\_mode():
- will not cause POV signal; will return 0 as the count of numbers in the mode. It will not send any mode result numbers.
- If client is waiting to read more than one result, they will get out of sync with the server, because the only result they will get is the nonce that is sent prior to the next command. Thus the read would end with a SIGALRM.

math\_fun.c:do\_dbl\_range():
- SIGSEGV at line 460.
- pov-4.xml

math\_fun.c:do\_dbl\_sum():
- will not cause POV signal; will return 0.0 as an answer.

math\_fun.c:do\_dbl\_product():
- will not cause POV signal; will return 1.0 as an answer.

math\_fun.c:do\_dbl\_min():
- will not cause POV signal; will return 1.7e308 as an answer.

math\_fun.c:do\_dbl\_max():
- will not cause POV signal; will return -1.7e308 as an answer.

math\_fun.c:do\_dbl\_sort():
math\_fun.c:do\_dbl\_rsort():
- will not cause POV signal; will be a nop. The first value sent to the client will be the nonce that is associated with the next command, but no other values will be sent and thus the client and server will get out of sync. If the client is waiting to read a result, the read will end with a SIGALRM. 

math\_fun.c:do\_dbl\_odds():
math\_fun.c:do\_dbl\_evens():
- will not cause POV signal; will return 0 for number of odds/evens, will not return any values. If the client is waiting to read values, the read will end with a SIGALRM.

### Generic class of vulnerability

Improper Input Validation
NULL Pointer Dereference

### CWE classification

Improper Input Validation
CWE-20

NULL Pointer Dereference
CWE-476

## Challenges

* The first challenge is the requirement to replay a 64bit nonce at the start of every operation. Although computationally simple, it does require some analysis to recognize the need to replay the exact same value. I added the nonce at the start of each operation, because to make fuzzing search space start out with a random 64 bits which should make it difficult.
* The second challenge is understanding floating point arithmetic. Half of the math functions process floating point numbers.
* The third challenge is that, assuming the competitor can mangage the nonce, and they are doing fuzzing, they are going to experience crashes in a subset of the math functions in any case where the list length is 0. This is a case that will help differentiate between teams' methods of patching and detecting vulnerabilities. The ideal patch, is to put a test in operation.c:do\_create() around line 255. Another efficient patch would be to put a list length check at the start of the operation.c:load\_list() function. It is also possible to put a length check inside of each math function in math\_fun.c. One or more of those checks should be designed to cause the system to exit if num\_list->count is 0. Either method would prevent the functions from causing a SIGSEGV.
* The final challenge is believing that floating point numbers can be odd and even.
