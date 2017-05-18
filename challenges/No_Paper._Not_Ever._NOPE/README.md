# No Paper. Not Ever. (NOPE)

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

 Individuals and businesses have a lot of information to process when doing taxes. As the leading e-file processing firm, I R Yes, LLC, we are bringing you the fully-functional, zero-paper solution to all of your tax filing needs. We call it, "No Paper, Not Ever", or NOPE for those acronym lovers.


## Feature List:

- Create user account: taxpayer can register for a NOPE account.
- Login: taxpayer can log into their NOPE account.
- Logout: taxpayer can log out of their NOPE account.
- Upload tax forms: taxpayer can upload tax documents to their NOPE account.
- Taxes Due: taxpayer can query to determine taxes due or refund for a tax year.
- Taxes Submitted: taxpayer can query to determine list of tax years where forms were submitted.
- Pay taxes due: taxpayer can pay their taxes owed.
- Get tax refund: taxpayer can receive their tax refund.
- Trigger an audit: taxpayer can send a request to get their taxes audited. Perhaps they are feeling lucky?

## Vulnerability 1

In service.c:370, the Response struct 'r' is not initialized to zero, so each consecutive session has the possibility of stale data in the Response from the previous session(s). Additionally, in service.c:422, the Response.key is only set on a successful session, so any unsuccessful sessions that follow a successful session will get the Response.key from last successful session.

To trigger the vulnerability, a successful create account session should be followed by any number non-successful sessions, which use a Response.answer that is 8 bytes or less. The create account will write a 12 byte password in to the Result.answer. The easiest is just an invalid command, which will use the 8 byte "NICE\_TRY" as the answer, which will only overwrite the first 8 bytes of the 12 byte password. Each of those non-successful sessions will get a Response with the session key from the last successful session (create account) and they Response.answer buffer will contain 4 leftover bytes in the session answer buffer from the newly created account's password.

Xor'ing the last 4 bytes of the Response.key with the 4 stale bytes of the password will give flag page bytes. However, the flag page bytes are only consecutive if the bytes in the Response.key are consecutive. So, the POV can do the easy route and make the last 4 bytes of the Session.key consecutive for the create account request. And then do a simple XOR to get the flag page bytes. If the bytes of the Response.key are not consecutive, then the POV will have to generate a map of the flag page and try again after later successful sessions. The bytes of the Session.key are used as indices into the flag page.

As a side: technically the CRS can just do a create account request and read their own password and calculate the flag page bytes. But, that is weak. The actual POV I'm describing allows a user to discover the credentials of another user. Which is of greater concern in the big picture.

### Generic Class of Vulnerability

Use of improperly initialized memory
Use of uninitialized resource

### CWE Classification

CWE-665: Improper Initialization
CWE-908: Use of Uninitialized Resource

### Challenges

* It should be easy to detect the uninitialized struct with static analysis tools.
* Patching can be as easy as memsetting the struct to 0's, so that should be easy.
* Proving is a bit harder because it requires a successful create account session to have been completed. And then to follow it with a non-successful session where the answer is 8 bytes or less. And if another successful session is run, the data may no longer be useful. So, the challenge is sequencing the proper sessions and then ensuring that the bytes of the Session.key are consecutive.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 2

In service.c:200, because the do_copy function pointer is defined right above the year\_buf, , writing beyond the year\_buf bounds will overwrite the function pointer. And further beyond will overwrite the arguments to taxes\_submitted().

In service.c:214, the taxpayer\_list\_submitted\_tax\_years function is called with one argument being a stack buffer of 128 bytes (year\_buf). Inside this function, taxpayer.c:181, it has no way to determine the size of the year\_buf and does nothing to prevent writing beyond its end. 

Additionally, in service.c:217, the do\_copy function is called immediately following a successful return from the taxpayer\_list\_submitted\_tax\_years function.

So, to trigger the POV, the CRS must first create an account, then with the same user do the following, login, submit 72 tax returns, request taxes submitted list. Each of the tax returns must have a unique tax\_year and must pass the tax form validation function. When the taxes submitted request is processed, the first 64 tax years will fill up the year\_buf. The next 2 tax years will overwrite the do\_copy() function pointer. The next 4 will overwrite the ret and *tp variables. Finally the last 2 will overwrite *r, the second argument to taxes\_submitted(), which also happens to be the first argument to do\_copy(). All of the OOB writing is done and when the function returns, it will call do\_copy() at the address provided (EIP) and its first argument will be r which will have the value provided (EDX). Thus, with CRS controlled EIP and EDX we have POV.

It is true that if the year buffer is filled to the max of 128 bytes, and then in the do\_copy function, service.c:187, the year\_buf content will overflow the r->answer stack buffer. However, that overflows into the Session stack buffer, service.c:381, which is copied after that point, but the altered content does not cause POV. So, this is a valid buffer overflow, but not a POV. A bit of a distraction.

### Generic Class of Vulnerability

OOB write on stack buffer
No bounds checking on writes to stack buffer
Incrementing a pointer out of range of the buffer.

### CWE Classification

CWE-120: Buffer Copy without Checking Size of Input
CWE-121: Stack-based Buffer Overflow
CWE-787: Out-of-bounds Write
CWE-823: Use of Out-of-range Pointer Offset

### Challenges

* It should be easy to detect the OOB writing with static analysis tools. It's also possible with taint tracking or very lucky fuzzing. 
* Fuzzing will be quite difficult for several reasons: 1) the tax form verification function, 2) the requirement for tax years to be unique, and 3) for valid username/password of a valid account to be used for all commands after account creation.
* Patching requires a check to be inserted that stops the while loop at taxpayer.c:181 once the year\_buf has been filled up. The patch uses the bytes\_written value to pass in the max bytes, but there are other solutions that would work. This is a little beyond trivial, so we'll call it medium.
* Proving is a bit harder because it requires a successful create account session to have been completed. And then to follow that with 64 successful tax form submissions where each tax form has a unique year. Following that the EIP and EDX values can be user controlled by adding another batch of tax forms, also requiring unique years. It's actually the unique year test that limits the reach of other potential POV avenues on this function.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is medium

