# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

Our Single-Sign-On (SSO) solution will allow users to authenticate once in order to access any corporate web service.


### Feature List

Users will first send a request for a given resource. If the user already has a token for the resource, the resource is returned. If not, the user will be required to re-authenticate and obtain a new token for the resource. Once the user is done using the resource, they may send a revocation message to revoke the token for the resource. Once the user is done using all resources they can log out and end their session.

## Vulnerability
This service has 3 vulnerabilities that all must be triggered in order to achieve a POV. 

The first vulnerability is an Access of Memory Location After End of Buffer that can be leveraged in order to leak memory. The leaked memory contains the authentication token. By sending a username that fills up the entire username buffer, the call to strnlen in the memcpy call will copy both the username and the auth\_val into a buffer that is eventually returned as part of the authentication failure message. The value can then be re-sent on subsequent authentication requests to properly authenticate any user.

The second and third vulnerabilities are a Heap-based Buffer Overflow due to the Use of a Uninitialized Variable. The uninitialized message\_buf in the auth\_success function is the same stack location as the message\_buf in the auth\_failure function. The result is that the message\_buf would contain the value of the message\_buf allocated in the auth\_failure function. Therefore, the check for a NULL pointer in auth\_success passes, and the strcat functions will copy data into the buffer. If the username sent to auth\_success is larger than what was allocated in the auth\_failure function strcat can overflow the buffer, since it was never allocated based on the size requirements of auth\_failure. 


### Generic class of vulnerability
Heap-based Buffer Overflow
Use of Uninitialized Variable
Out-of-bounds Write
Access of Memory Location After End of Buffer

### CWE classification
CWE-122	Heap-based Buffer Overflow
CWE-457	Use of Uninitialized Variable
CWE-787	Out-of-bounds Write
CWE-788	Access of Memory Location After End of Buffer

## Challenge

1) Determine how to properly interact with the service, including the structure of requests, in order to authenticate and obtain a resource token. 

2) Leverage the memory leak to authenticate successfully.

3) Model the stack to determine the contents of the uninitialized variable.

4) Determine the size of the buffer contained in the uninitialized variable.
