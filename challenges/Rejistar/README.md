# Rejistar

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

Secure Registers Inc. is releasing their automated credential registration service, REJISTAR. Recent breaches have demonstrated the impact of stolen credentials. Only through regular and immediate re-credentialing can this impact be reduced. Unfortunately, most credential registration is performed manually, which is slow and error-prone. 

Not any more. With REJISTAR an end point can automatically register or re-register any credential, including certificates and tokens. Now when a vulnerability in a secure communication protocol exposes the integrity of your credentials, immediate re-credentialing a real possibility.

### Feature List

- Certificates
-- Enroll a new certificate with user-defined expiration
-- Re-enroll an expiring certificate
-- Revoke a certificate
-- Request the current Certificate Revocation List

- Tokens
-- Request a new token
-- Refresh an expiring token
-- Revoke a token

## Vulnerability 1

The vulnerability in this CB is a off-by-one error where the amount of memory malloc'ed by the service to store the body of the request is 1 char shorter than what is zero'ed out following the malloc call.

The malloc implementation in this CB divides a page into chunks of equal size depending the type of run, e.g. a 4-byte run. Each run includes a bitmap that keeps track of which chunks are allocated and freed in the currently available page. The page containing the bitmap is allocated right before the first page in the run. Therefore, an overflow in the last chunk in the first page of the run can overwrite the bitmap.

By using the aforementioned off-by-one error to zero out the 1 more byte than what was allocated, the first byte of the bitmap is zero'ed out. The result is that the next 2^8 allocated chunks in the run will be the chunks that have already been allocated. 

In this CB, the name and function pointer of each service is stored in a 16-byte chunk. By overwriting the bitmap for the 16-byte run, a Service structure can be overwritten to cause a Type 1 vulnerability.

### Generic class of vulnerability

Off-by-one
Heap-based buffer overflow

### CWE classification

CWE-193: Off-by-one Error
CWE-122: Heap-based Buffer Overflow
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

### Challenges

1. The off-by-one error should be easily be detected, but understanding how zero'ing out a single byte impacts the allocation of chunks in a non-standard malloc implementation will be difficult. 

2. Successful exploitation will require determination of how input impacts the allocation of chunks of specific sizes in order to allocate the specific chunk at the specific control flow point that will be used to overwrite the Service structure. 

3. The CB requires each message to be authenticated. A user/pass can only be used to request a new token. A token can be used to request tokens and certificates. Certificates can only be used to access certificate services. Also, certificates are "poorly" signed. This should eliminate blind fuzzing that doesn't satisfy the constraints of the authentication subsystem to reach different control paths, including ones needed to exploit vulnerabilities.

### Difficulty
- Discovering is easy
- Proving is hard
- Patching is easy

## Vulnerability 2

The vulnerability in this CB is a off-by-one error in the sendToken function where the amount of memory malloc'ed by the service to store the body of the request is 1 char shorter than what is needed to store a null-terminated string. This results in an improper null termination. When a new token is sent back, the flag is allocated in a 64-byte chunk after the buffer for the new token is allocated. If the new token string is exactly 64-bytes, the flag will be appended to the buffer that is sent to the requestor.


### Generic class of vulnerability

Improper Null Termination
Off-by-one Error
Out-of-bounds Read

### CWE classification

CWE-170: Improper Null Termination
CWE-193: Off-by-one Error
CWE-125: Out-of-bounds Read

### Challenges

1. The off-by-one error should be easily be detected, but understanding how long the token needs to be to be allocated in the chunk preceeding the token could be a challenge.

2. Successful exploitation will require determine how input impacts the size of the token returned, such that the flag is leaked.  

3. The CB requires each message to be authenticated. A valid username and password will be needed to reach the sendToken function. 

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy

