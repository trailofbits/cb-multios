# CGC Challenge Binary (KPRCA\_00026): Minimalistic Memo Manager (3M)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

3M is a program that allows users to manage their memos. It provides a very simple
interface with minimal yet useful features: create, modify, view, and delete. It supports auto-correction of misspelled words, where the user can specify custom corrections. In order to make the program more efficient, the latest version of the software uses threads!

### Feature List

- **Create a memo**
  - Prompts to fill in the following fields: subject, date, priority, and body.
  - Before it is added to the system, the validation on the input is done.
    - Must be valid year (1970-2500), month (1-12), and date (1-31).
    - Subject must not be longer than 32 alphanumeric characters.
    - Priority must be 0 (Low), 1 (Normal), or 2 (High).
    - Body must not be longer than 4096 bytes.
  - Displays the memo ID when successfully created.
- **Update a memo**
  - Prompts for the memo ID.
  - Prompts to fill in the same fields as "create a memo" menu.
    - However, the user can leave the field empty to keep and use the original data.
  - Validation happens:
    - Memo ID must be valid (i.e. should be in the system)
    - Field validation (same as the memo creation)
  - Displays the memo ID when successfully update
- **View a memo**
  - Prompts for the memo ID.
  - Memo ID must be valid (i.e. should be in the system)
  - Displays in a nice format
- **Delete a memo**
  - Prompts for the memo ID.
  - Memo ID must be valid (i.e. should be in the system)
  - Removes the memo with the memo ID.
- **Add a custom auto-correction word**
  - Prompts for the misspelled word.
  - Prompts for the correct word.
  - Adds the correction (misspelled->correct mapping) to the system
    - Each word must not be longer than 32 characters
    - The maximum number of correction entries is 100 (20 is pre-populated)
- **Quit**
  - Quits the program.


## Vulnerability

The vulnerability is the use of the shared resource without a proper lock in multi-threaded environment. In order to perform the auto-correction of the words when creating a memo, the program runs a separate thread (_ac_process_) that is in charge of checking the queue of words to be examined (_ac_queue_) and updating the words if they are in the auto-correction dictionary.

Since the user can add a custom auto-correction word such that a shorter string to be replaced by a longer string, a heap-based buffer overflow can happen. The program attempts to guarantee that _ac_buffer_ will be large enough to copy in the next word. However, if the _realloc_ triggers a call to _allocate_ then a thread switch may occur, and because the _realloc_ happens before _ac_idx_ is incremented and is not guarded, _ac_idx_ may be modified by the other thread. Thus, once _realloc_ returns, there is not actually enough memory allocated for the _memcpy_. The fix is to put the call to _realloc_ in the guarded code section.

There is also a NULL pointer dereference bug where the buffer is not initialized when recv failed within a different thread. The buffer needs to be checked after achieving the lock for the resource.

The effect of the buffer overflow is attacker control of the heap structures for the subsequent block. This should give the attacker the ability to trigger remote code execution.

### Generic class of vulnerability

Heap Buffer Overlfow

TOCTOU (Time Of Check, Time Of Use) Error

NULL Pointer Dereference

### CWE classification

Heap-based Buffer Overflow (CWE-122)

TOCTOU Error (CWE-367)

NULL Pointer Dereference (CWE-476)

## Challenges

The competitors need to realize that this is a multi-threaded program, and be able to analyze the use of a shared resource (without any locking) among the threads. In order to trigger the bug, the fact that auto-correction does not safely handle the *correction* that increases in string length must be exploited.
