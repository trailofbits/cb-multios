# Blubber

### DARPA performer group
Kaprica Security (KPRCA)

## Description

An IPC server + 2 clients implementation of a social media service where users can 'blub' messages to a list of subscribers.

### Feature List

To first connect, users enter an username that will uniquely identify them to
the blubber service and other blubbers.

Users can blub a message of up to 140 characters with the 'b' command.

Users can subscribe to another blubber with the 's' command.

Users can read new blubs from other blubbers with the 'r' command.

Users can reblub another blubber's blub with the 'y' command.

Users can exit the blubber service with 'e' command.

In addition, there are two IPC clients present with this CB that pseudo
randomly interact with the blubber service. It wouldn't be social otherwise.

## Vulnerability
### Vuln 1

When reblubbing, the user provides a username and number. The number serves as
an index into a vector that stores that users blubs.  Through the use of
strtol, improper types of int for the index and length, and poor bounds checks
in the vector class, it is possibly to negatively index into the vector's
backing array. In this case, the value pulled out of the index is a pointer to
a blub object which stores the username and content of a blub. Therefore, an
attacker can achieve a read-anywhere primitive by blubbing a blub with the
address they want to read in the content and later reblubbing an index that
uses that address as the address of a blub. This allows for a Type 2 POV.

#### Generic class of vulnerability

Out-of-bounds Read

#### CWE classification

CWE-125 Out-of-bounds Read
CWE-129 Inproper Validation of Array Index
CWE-191 Integer Underflow

#### Challenges

- It is our understanding that in CQE, many CRS's did not do well with IPC
  challenges. This challenge was written mostly to evaluate baseline IPC
  performance. The bug itself is present in the 'server' binary, and requires
  no interaction with the two additional IPC 'clients'. I.e, this is a normal
  CB with IPC thrown in for network traffic generation and ostensible
  additional complexity.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: easy
 - **Patching**: easy
