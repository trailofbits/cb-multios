# BIRC

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A binary protocol inspired by an internet relay chat service service

### Feature List

The CB proivdes a Client/Server model with the server holding all of the program's state and the client interfacing with the user
to make requests and receive responses.
A client may make the following request to the sever:
    -Register an account
    -Verify user password
    -Search for registered accounts
    -Add a channel
    -Join other channels
    -Search for registered channels
    -Leave a channel
    -Delete a channel if the user is its creator
    -Request server tokens, if the user is a remote admin
    -Exit Client/Server
The local client also allows a user to switch between accounts via a login/logout


## Vulnerability
### Vuln 1

The vulnerability is triggered by a buffer overflow which allows an attacker to overwrite the name of 
the first cached user. This allows an attacker to change the client's username to {12, 34, 56, 78} 
(which is supposed to represent some well known admin string, such as "root" or "admin"). This special value
represents the server's internal default admin user whose password is the same as its username (think admin/admin).
By exploiting this realitively simple 4 byte user/pass combination the client can access functionality that
it was never supposed to have access to. This gives the attacker access to a privileged function call 
that can access the server's secret data.

The patch not only fixes the buffer overflow, but changes the remote server authentication from a short
and guessable password to a longer and harder to brute force token.

#### Generic class of vulnerability

Buffer overflow
Weak permission/authentication

#### CWE classification

CWE-121: Stack-based Buffer Overflow
CWE-287: Improper Authentication
CWE-521: Weak Password Requirements

#### Challenges

The challenege for this CB is understanding how both the client and the server function in order to enable the info leak.
The CB has built a nontrivial communication protocol between the client and server in order to test the CRS's ability to
interpret structured data. With this model the data sent from the CRS to the client does not use the same structure as
the data protocol between the client and server. This forces the CRS to deduce the communication protocol strictly through
binary analysis and not through pcap data.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: hard
 - **Patching**: medium
