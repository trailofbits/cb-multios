# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

HIGHCOO is the hottest message of the day (MOTD) program on the market. Instead of boring quotes and quips showing up at your login prompts, HIGHCOO honors your intellectual side by providing thoughful and enlightening Haiku.

from within HIGHCOO
new Haiku every login
a warm thought engulfs

### Feature List

This service is a message of the day (MOTD) program specifically designed to provide Haiku as the daily message.

It provide functions both to add new Haikus as well as those to query the current Haiku collection.

Valid functions are:
* add haiku
* get haiku by id
* get haiku random
* get haiku count
* get list of haiku ids

## Vulnerability


When a new haiku is added, the user first provides the total number of bytes in the haiku; which the program assumes includes line termination charactors. Followed by each line of the haiku.

The function recv\_haiku at operation.c:319 controls receiving a new haiku. It allocates memory on the heap to store the haiku id, length, content, and the trailing null for the content. The user supplied total\_bytes value is used to define the size of the haiku content.

Then there is the while loop at operation.c:335 that controls receipt of the actual haiku content. This is the first problem. The while loop control variable starts off equal to the uesr supplied total\_bytes value. It assumes that the number of bytes in the haiku content matches the total\_bytes value.

Right inside the while loop, recv\_haiku\_line is called to receive each of the 3 haiku lines. Inside recv\_haiku\_lines, each line of the haiku is read in and stored in a temporary stack buffer: temp\_line\_buf. snprintf is then used to copy the content followed by a line termination charactor into the allocated heap buffer. The size parameter for snprintf is a decrementing count of bytes\_remaining, which starts off as the total number of bytes in the haiku. So, it also assumes that the total includes the line termination charactors and matches the number of bytes in the haiku content.

Back in recv\_haiku, bytes\_remaining is decremented by the number of bytes in that line that were written to the heap.

This means that there are conditions when the total number of bytes written will not correctly match the total\_bytes value, which will cause the bytes\_remaining value to become negative. 

The while loop checks for the loop invariant to equal 0, but under these conditions, it skips past 0 and goes negative, so the while loop condition will continue to be true until either bytes\_remaining wraps around all the way back to 0. Or something causes the system to crash prior to that.

Each time through the while loop will allow an additional line of input to be stored into the heap buffer. The allocation of the heap buffer for a haiku allocates 2 pages worth of memory. So an overflow takes a haiku of length of at least 8184 bytes (8192-8) to cause a memory access error and thus segfault (POV).

Since, snprintf is using a signed short (bytes\_remaining) as its size parameter, the size value will be cast to an unsigned short and become a large value. So, the only limit on how much data can be written into the heap buffer for each line of input is the max length of a line of input which is null terminated.

There are several options for how to patch this problem. The patched version changes the while loop condition to be true only when bytes\_remaining is > 0. Another option would be to decrement the parameter to recvline from MAX\_HAIKU\_LINE\_LEN to some smaller amount when bytes\_remaining is less than MAX\_HAIKU\_LINE\_LEN. And then use bytes\_received in the snprintf, instead of bytes\_remaining. Putting a test at the beginning of recv\_haiku\_line to ensure bytes\_remaining is positive, would be advised as well. Another option would be to put a test at the end of the while loop in recv\_haiku that breaks out of the loop if bytes\_remaining <= 0, although that is effectively redundant to the patched version.


Separately, there is no limit on the number of haiku a user can add. So, it is possible to use up the whole heap.


### Generic class of vulnerability


Improper Input Validation

Improper Signed to Unsigned conversion

Heap Buffer overflow

Improper checking of loop invariant

Off-by-one-error

Integer underflow and overflow with wrap around

### CWE classification

Improper Input Validation
CWE-20

Improper Validation of Array Index
CWE-129

Integer Overflow or Wraparound
CWE-190

Integer Underflow or Wraparound
CWE-191

Off-by-one Error
CWE-193

Signed to Unsigned Conversion Error
CWE-195

Integer Overfow to Buffer Overflow
CWE-680

## Challenges
* A fuzzer will be challenged because anytime that an add function is selected and the total haiku size provided is less than the actual haiku size, the code will enter a problem state. It will usually just result in a receive timeout, but if enough data is provided in the haiku, it will cause segfault/POV.
* A fuzzer will also have problems with the requirement for 3 lines of data, each having a non-standard line termination charactor. At the same time, the length of a line is restricted along with the total length of all 3 lines.
* A SMT solver should be able to work out the proper inputs to create a valid haiku. But, the amount of input required to trigger the POV is much more than the size of the buffer, so is not something that can be learned from code conditions.
* 
