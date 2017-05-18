# Sensr (KPRCA_00059)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A simple service that receives sensor readings, verifies them, and reports back the latest aggregated reading. 

### Feature List

Three types of sensor inputs:

 * Location (3-dimensions)
 * RPM (revolutions per minute)
 * Speed

Customizable absolute bounds on the inputs to filter out bad inputs. Additionally, change in location is checked against the limits on speed.

Every packet is timestamped. Timestamps are used for ordering and calculating speed from location. If a packet arrives out-of-order, either it will be dropped or the preceding packet will be dropped.

A sensor can send a reset packet if the system is out-of-sync and the state needs to be cleared.

## Vulnerability
### Vuln 1
In queue.h:76, there is an intended bug that causes stateq_pop_tail to return uninitialized heap memory. This can be triggered by the attacker when a packet is sent that causes the previous packet to be dropped. The error packet sent back to the attacker may now contain 4 bytes of uninitialized memory. Because the secret page was copied to the heap at the beginning of the program, and then freed, this uninitialized memory will actually contain some obfuscated bytes of the secret page. Exploitable as a type 2 POV.

#### Generic class of vulnerability
Read of uninitialized memory

#### CWE classification
CWE-125: Out-of-bounds Read

CWE-226: Sensitive Information Uncleared Before Release

#### Challenges
Involves reuse of memory without initialization, so some understanding of heap allocation is helpful. One possible avenue for discovery is fuzzing combined with taint analysis. The sensitive memory is XORd with a deterministic value and a POV must XOR the memory it reads to get the real type 2 value.

#### Difficulty
 - **Discovery**: easy
 - **Proving**: medium
 - **Fixing**: medium
