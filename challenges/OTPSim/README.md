# OTPSim

### DARPA performer group
Kaprica Security (KPRCA)

## Description

OTPSim provides a way to simulate an OTP (One Time Pad) code generation with limited sessions. When a client initiates the session with the handshake command, the client can generate up to 3 OTP codes of customizable length, unless the session is extended. The extension resets the counter back to 0, allowing the client to generate 3 more OTP codes. The service also provides a way to verify.

### Feature List


```
- Handshake
- Generate OTP token
- Extend the session
- Reset seed value and index
- Verify token
- Quit
```

## Vulnerability

### Vuln 1
- Extension feature receives random non-null bytes from the client and transmits the same content back (with a null byte prepended, indiciating success).
- The client controls the size field to let the service know how much of random bytes it should expect to read.
- However, the service fails to check if it actually has received said number of bytes -- it reads until a null byte or up to the max stack buffer size (8192).
- So, when a malicious client sets the size large, but sends less data than what it promised, memory beyond the random bytes (from the client) is read from the stack -- which may contain sensitive data.
- Since OTPSim uses secret page to generate token data, a malicious client can force the generation of an OTP token, which fills stack memory with data from secret page.
- Because the stack isn't initialized with the extension function, the memory can be leaked.

#### Generic class of vulnerability

Buffer Over-read

#### CWE classification

CWE-126: Buffer Over-read

#### Challenges

- Handshake involves some bit-arithmetic challenge/response procedure
- Need to realize that the stack memory isn't initialized, and may contain secret page data by forcing the service to generate OTP token
- Although there isn't a memory corruption (at least not intended), it is very real-world (Heartbleed) type of bug.

#### Difficulty

 - **Discovery**: medium
 - **Proving**: hard
 - **Patching**: easy
