# REMATCH_1--Hat_Trick--Morris_Worm

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This challenge set contains 3 binaries that closely mimic the behavior of three services: fingerd, sendmail, and rsh and an additional 'front door' binary that provides access to the others. These services were involved in the propagation of the original Internet Worm written by Robert Morris. The fingerd service was vulnerable to a simple stack buffer overflow, originally caused by use of the gets() function. The sendmail service was vulnerable to a logic bug that existed in debug mode which allowed the shell interpreter to be the recipient of the message. The rsh service was inherently vulnerable by using a naive trust model and is vulnerable to password brute force attacks.  

The services in this challenge set are lookupd, inspired by fingerd, mailsender, inspired by sendmail, and ish, inspired by rsh. Each contains similar functionality to the original services and the same original bugs. 

### Feature List

This is a multi binary challenge set. The first binary acts as the front door, handling the initial connection and directing input to one of three services (lookupd, mailsender, and ish). 

Lookupd is a lookup service that provides name and contact info for users. This service is randomly populated with fake user data on startup. It allows querying for a particular user or listing all users on the system. 

ISH is an internet shell service. It requires a login and password and implements a dummy shell with a limited command set. It contains one set of static credentials and then generates random additional credentials on startup. 

Mailsender is a mail server. It allows listing known addresses, dumping mail queues, reading messages, and posting new messages. 

## Vulnerability

The vulnerability in lookupd is equivalent to a gets() call. This function reads input from the user onto the stack with no bounds checking. This allows a very straightforward buffer overflow. It should be easy to find, easy to prove, and easy to patch. 

The vulnerability in ISH contains two elements. One is the existence of static credentials that would allow the CRS to login and execute commands. The second is that one of the shell commands allows arbitrary reads from memory, thus enabling a memory leak (type 2 POV). The CRS could eliminate this vulnerability by either deactivating the compromised account credentials or preventing the shell command from accessing the sensitive memory region. This bug should be easy to find, easy to prove, and easy to patch.  

The vulnerability in mailsender is patterned after CVE-1999-0095 which allowed a remote user to access the root shell through a debug command. In this case if the CRS connects to mailsender using the -d flag and submits a message with the correct recipient, it can access a command shell that allows arbitrary read of memory. This vulnerability can be patched by either deactivating the -d debug mode or by restricting the shell from accessing the sensitive memory region. It should be easy to find, easy to prove, and easy to patch. 

### Generic class of vulnerability
The lookupd vulnerability is a stack buffer overflow. 
The ISH vulnerability is a logic bug leading to an arbitrary memory read. 
The mailsender vulnerability is also a logic bug leading to an arbitrary memory read. 

### CWE classification

CWE-120 Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
CWE-798 Hard Coded Credentials
CWE-215 Information Exposure Through Debug Information

## Challenges
These vulnerabilities are patterned after very basic and outdated vulnerabilities so they should be straightforward to find, prove, and patch. One potential complicating matter is that there are four binaries in this system and some communication travels between them rather than directly to/from the user. Since most challenge sets are not designed in this manner it may prove difficult for some analysis systems. 
