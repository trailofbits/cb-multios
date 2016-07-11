# CGC Challenge Binary Template

## Author Information

"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

This is a service for greeting customers. It stores a user's credentials
client-side, tracking their identity and a reference to their profile which is
stored server side. Client-side tokens are signed to prevent tampering by the
user. It responds to the following commands:

 - login <name>, returns a token
 - greet <token>, returns a welcome message
 - quit, quits the program without returning a status

Login and greet both return 0 on success and -1 on failure, represented as a
32-bit hexadecimal 2's complement number printed on its own line.

### Feature List

- Multiple verification methods using different cryptographic algorithms
- Per-user profiles tracking unique visits
- 16-byte usernames

## Vulnerability

There are multiple issues with the cryptographic schemes used by the service
which may allow a malicious user to modify the returned token and still validate
it.

The first method uses a trivial xor with a secret key to "sign" the token,
effectively revealing the key by performing the inverse operation. New tokens
can be forged by extracting the key and signing arbitrary data.

The second method uses a checksum method instead of a cryptographic hash
function, weak against collision attacks and hash extension attacks. A user can
append data to a token and recalculate the hash without knowledge of the secret
value.

The third method uses an MD5 hash, stronger than the checksum used in the second
method, but uses a weakened padding scheme which allows extending a message
without changing its hash value. This allows a user to pass an overlong string
to a fixed-sized stack buffer, overflowing it. This scheme also prepends the
secret value to the token prior to hashing, opening it up to hash length
extension attacks as well.

The patched version of the binary fixes these issues by using a HMAC scheme to
sign the tokens, still using MD5 but hardened against length-extension attacks.

### Generic class of vulnerability

Stack buffer overflow
Untrusted pointer dereference
Information disclosure
Weak cryptographic algorithms
Hash length extension

### CWE classification

CWE-121 Stack-based Buffer Overflow
CWE-822 Untrusted Pointer Dereference
CWE-471 Modification if Assumed-Immutable Data
CWE-201 Information Exposure Through Sent Data
CWE-326 Inadequate Encryption Strength
CWE-327 Use of a Broken or Risky Cryptographic Function
CWE-328 Reversible One-Way Hash

## Challenges

This CB deals with common issues which arise when designing cryptographic
protocols, inspired by real-world schemes such as JWT for storing
presumed-immutable data client-side. The multiple schemes are designed to
provide increasing difficulty for a CRS to analyze. The xor-scheme is only
minimally obfuscated, and should demonstrate the ability of a CRS to identify
the information disclosure. The checksum scheme is harder to analyze, but the
checksum algorithm itself is simple and it should be within the realm of
possibility to discover the ability to extend a token through analysis of the
algorithm's behavior and data flow. The md5 scheme is definitely the hardest,
but the padding issue sticks out due to its lack of incorporation of the length
value into the padded message. Analysis of this should lead to identification of
the many possible collisions per message this introduces. The hash length
extension attack on md5 is by far the most challenging to identify, however the
algorithm should be identifiable as md5, and the pattern of prepending a secret
to a token should be discernable, which should be suficient to discover this
vulnerability.

