# QUIETSQUARE Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

The mice are hungry and a cheese heist is in order. The heist requires strict operational security to pull off. Quincy (the brains of the mouse duo) will distract Snuggles (the house cat) while Whiskers (the duo's brawn) will bolt into the kitchen and grab the cheese sitting on the counter. The timing of these actions is critical; communication compromise would equate to mission failure and slightly hungrier mice.

Unfortunately for the mice, the only practical communication medium is radio and Snuggles recently earned a wide-spectrum radio jammer by sending in enough box tops from his cat food. However, Snuggles' jammer cannot jam all frequencies at once and must make sweeps over the spectrum. The mice plan to exploit this weakness by frequency hopping, evading the jammer with some likelihood of success for small portions of their message. QUIETSQUARE must reliably reconstruct these fragmented messages.

Because the amount of data that can be sent in any burst is so limited, Quincy sought to minimize cryptographic overhead. Quincy decided on a one-time-pad design and a preshared book of key, to be XORed with ciphertext in transit.
In doing so, Quincy hoped the communications would be: (1) provable secure, (2) zero cryptographic overhead in terms of message length.

Quincy version-tracked his work (of course) on Cheesehub, but inadvertently made the source code public. Snuggles grabbed a copy before Quincy could protect it, but time was running short and Quincy decided to go ahead with the communications mechanism, because the one-time pad had not been compromised.

You take the role of Snuggles and must prevent the mice from stealing your humans' cheese. You can see and inject ciphertext in transit.
You have a copy of QUIETSQUARE (this CB). If you also had the one-time-pad, you could read all of the communications between the mice and it would be game over.

Instead, you plan to (1) enable your sweep-jammer to force message fragmentation, (2) exploit a memory corruption vulnerability in QUIETSQUARE to deny communications ability to the mice.

### Feature List

The QUIETSQUARE client accepts 3 types of messages:
* Connection Termination (ConnTerm).  This is 256 consecutive NULL bytes and causes connection reset).  To avoid ambiguity, no other messages begin with a 0x00 byte.
* One-time-pad: 16B, expected immediately after connection reset.
* Message data, possibly fragmented, length: 256B.

Of note:
* The contents of the one-time-pad are not one-time; the pad is used verbatim over and over again, no special key scheduling algorithm.  Quincy needs to do his cryptography homework.
* Snuggles wins an injection race too infrequently for repeated spamming of the ConnTerm message to have the desired effect; he must string both sides of the conversation along and ultimately cause memory corruption on to both Quincy and Whiskers' clients.

## Vulnerability

This CB is designed to gauge CB reasoning regarding stack overflow (not stack buffer overflow).
Snuggles will be successful if he causes sufficient recursion into the de-fragmentation function, resulting in stack exhaustion and ultimately a write to an unmapped page.

### Generic class of vulnerability

Stack overflow

### CWE classification

CWE-674: Uncontrolled Recursion

Technically, the recursion is controlled, but the control is handed to the CRS, resulting in a vulnerable condition.  There does not appear to be a CWE specifically for stack overflow.  We believe CWE-674 is closest to the vulnerability presented here.

## Challenges & Patching Strategies.

We anticipate a "cheeseball" defense that attempts to avoid the larger problem of sufficiently understanding the vulnerability.

The defense reduces to "increase the size of the stack".  This can be accomplished by allocate()ing memory below (lower addresses) the stack, avoiding a page fault on stack overflow.  Although allocate() doesn't allow specification of chosen virtual address, we have not examined the edge cases regarding, e.g. mapping all of userspace.  We anticipate other mechanisms for defense as well, e.g. rewriting .bss section header to relocate the .bss immediately below the stack during load, accomplishing page fault avoidance.

We don't assume we have investigated such edge cases better than competitors, so instead, we store a crucial pointer to the OTP at a low address in the stack space.  Clobbering this pointer will give probabilistic assurance that either (1) OTP will be incorrectly identified, resulting in wrong responses to polls or (2) page fault via pointer dereference of an unmapped page.

Successful competitors will implement a bail-out case where there is an impending stack overflow.  The CB will silently cease communications with CRS when faced with exploitative input.

We anticipate another defense, although this one is more sophisticated.  A competitor may choose to ingest the CB, optimize it (probably at a semantics-preserving IR level) and re-emit native code.  This is heavy lifting and is prone to error.  Because of the relative risk of this strategy and our desire to evaluate whether CRSs are capable of autonomously fielding optimized binaries for which they lack source, we do not specifically code against this defense.

The defrag() function will cause excessive stack consumption via a huge (and unnecessary) buffer allocated on entry.  This is done so that stack exhaustion conditions can be triggered with a modest packet length in the FRAG protocol. 

This buffer isn't actually used for anything mission-critical.  It has no explicit use when reconstituting packets.  Without some distraction, an optimizing compiler should therefore be expected to remove the allocation.  Without these allocations, it becomes infeasible to stack overflow within the confines of the FRAG protocol packet length.  Similarly, an optimizing CRS will avoid the stack overflow condition in this manner.

