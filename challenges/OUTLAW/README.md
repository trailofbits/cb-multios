# OUTLAW

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

OUTLAW provides ACaaS (Authenticated Compute as a Service).  The CB set implements a vulnerability similar to the TLS CRIME vulnerability by exposing a shared secret via a compression-like side channel.  An additional memory corruption vulnerability can be exercised by authenticated clients (or an authenticated MitM).  

The CB set is composed of 3 CBs: (1) a CLIENT that issues requests to the SERVER, (2) the SERVER that responds to CLIENT requests, (3) a TAP, which speaks to the CRS and provides active MitM functionality to the CRS in the context of the CGC framework.

First, the CLIENT (CB1) and the SERVER (CB2) speak directly to one another and come to agreement on (1) the encryption key (enckey) used to protect the authentication key, (2) the authentication key (auth_token) used to authenticate SERVER responses to CLIENT queries as well as expose authenticated functionality to the CLIENT.

After this negotiation, the emulated active MitM vantage point is installed; CLIENT and SERVER speak only through TAP.  The TAP forwards all messages to the CRS, which is free to modify, drop, or forward the messages by sending a response to the TAP.  The TAP then forwards the message to the appropriate destination.  

The TAP architecture is intended to simulate an attacker that achieves active MitM following an exchange of secrets.  It should be noted, however, that even if the CRS was an active MitM during the secret negotiation phase, the secrets would not be directly revealed anyway as they require flag page knowledge.  The transition to TAP is provided as a means to demand additional reasoning on behalf of the CRS in line with what may happen in the real world.

## Feature list:
The CLIENT and SERVER (and TAP) speak a well-defined protocol that provides the following functionality:
* SERVER-authenticated ADDs
* SERVER-authenticated SUBTRACTs
* SERVER-authenticated MULTIPLYs
* SERVER-authenticated DIVIDEs
* CLIENT-authenticated MODIFICATIONs to existing functionality.  Provided the auth_token, the CLIENT is permitted to reconfigure the ADD functionality as SUBTRACT and so on.

In order to achieve authenticated message capability and some other requisite functionality (e.g. a seed-able PRNG), this CB set implements a modified form of the (public domain) Tiny Encryption Algorithm.  This modified TEA is used for both its key schedule (as PRNG output) and its encryption and decrytption capabilities (to protect the auth_token in transit).  It should be noted that different keys are used for PRNG and encryption / decryption.

In order to implement a compression side channel, a bit-counting function that may be used as part of an RLE compression algorithm records the number of matching, starting bits between the answer to a CLIENT REQUEST and the auth_token.


## Vulnerability 1

Vuln #1 is proved vulnerable by PoV #1 and is of type 1.  It cannot be exercised without first exercising Vuln #2, so read that one first.

As a man in the middle, the attacker has successfully revealed the auth_token, as described below.  With the auth_token, the attacker is able to exercise the OP_MOD functionality of the SERVER.  This functionality is intended to allow the CLIENT to reconfigure the operations of the SERVER to redefine, say ADDITION to SUBTRACTION.

This feature is poorly implemented, but the designer's rationale is it's an authenticated feature anyway; what could go wrong?  The implementation take a function pointer out of the message and writes it to an operations table.  An attacker with the auth_token can therefore redirect a function pointer and later exercise the function pointer to achieve Type 1 PoV.

### CWE classification

CWE-300: Channel Accessible by Non-Endpoint ("Man in the Middle")
CWE-465: Pointer Issues
CWE-822: Untrusted Pointer Dereference

### Challenges

* Being able to speak effectively in the 3-CB TAP architecture.
* Reasoning about what *should* be allowed on this interface (or deciding to remove it entirely).

### Difficulty

The following assumes the attacker already solved Vuln #2, which is a blocker for Vuln #1.  Although this is considered "easy", it is guarded by more difficult problems and should therefore be treated in series with Vuln #2.

* Discovering is easy
* Proving is easy
* Fixing is easy


## Vulnerability 2

Vuln #2 is a logic bug that inadvertently discloses contents of the flag page.  Specifically, auth_token is taken directly from the flag page and may be leaked through a compression artifact side channel.  This vulnerability is meant to emulate the TLS CRIME vulnerability.

To be more specific, RESPONSES from the SERVER to the CLIENT contain the answer to the CLIENTs query concatenated with the auth_token, encrypted under a shared key.  In addition, unencrypted compression artifacts are included.  This compression artifact is the number of bits in common between the answer and the auth_token.  The real-world parallel is a partially implement RLE compression algorithm applied to concat(answer, auth_token) prior to encryption. The ability to compress (or not) the concatenated values reveals information about the secret auth_token.

The attacker is able to craft REQUESTs such that the (known) answer to the REQUESTs matches some number of leading bits with the auth_token.  The attack progressively improves his guess by modifying his hypothesis according to the Number of Matching Bits (NMB) field in the SERVER RESPONSES.

After a maximum of 32 queries, the attacker has disclosed the auth_token through this side channel.  The attacker is able to submit the auth_token as as Type 2 flag or use it to exercise authenticated functionality to achieve a Type 1 PoV (see above). 

### CWE classification

CWE-200: Information Disclosure
CWE-201: Information Disclosure Through Sent Data
CWE-300: Channel Accessible by Non-Endpoint ("Man in the Middle")
CWE-310: Cryptographic Issues
CWE-514: Covert Channel
CWE-515: Covert Storage Channel

There does not appear to be a CWE that explicitly covers compression side channels nor the type of logic bug present in TLS and exploited by CRIME.  Notably, others have cited CWE-310 as the best category for the CRIME vulnerability - a very generic bucket.

### Challenges

* Being able to speak effectively in the 3-CB TAP architecture.
* Reasoning through a somewhat complex side channel.

### Difficulty

* Discovering is medium
* Proving is hard
* Fixing is easy
