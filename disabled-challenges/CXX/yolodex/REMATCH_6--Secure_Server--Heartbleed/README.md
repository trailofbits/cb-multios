# REMATCH_6--Secure_Server--Heartbleed

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description
CVE-2014-0160, commonly known as Heartbleed, was one of the first uber-famous vulnerabilities to receive its own name, dedicated website, and even a logo. Although it was a straightforward memory disclosure in OpenSSL, its effect was complex and far reaching. Its discovery in 2014 called into question the security and privacy of over 60% of encrypted Internet traffic over the past few years. Recovery from Heartbleed not only required patching the software like any other typical vulnerability but also required revocation of compromised keys, reissuing of keys and certificates, and changing of all user passwords. It is interesting to note that the Heartbleed vulnerability was originally detected by an automated testing system, Defensics by Codenomicon. 

This service recreates an openssl style server utilizing a made up transport layer called (Some Layer Security) (SLS) inspired by Transport Layer Security (TLS).  On top of that, the server implements a Message-based SLS protocol (MSLS). Since the heartbleed vulnerability was in the heartbeat message of a TLS session, this server implements a heartbeat style message as part of the MSLS protocol. 

### Feature List
This service accepts messages of several types:
  Handshake, Error, Changespec, Application, Heartbeat, and Shutdown. 
The handshake protocol is similar to a TLS handshake and contains the following exchange:
  Client Hello -> 
  <- Hello Verify
  Client Hello (w/cookie) ->
  <- Server Hello
  <- Server Key Exchange
  <- Hello Done
  Client Key Exchange ->
  Hello Done ->
  <- Finished
  Finished ->

Once a handshake is complete a connection is established and future data is sent within that protected connection. All 'encryption' is a simple xor based algorithm using the exchanged keys. 

Once a secure connection is established, this service provides access to a message board. Application messages can be sent within the encrypted connection of the following types: 
  APPLICATION_LIST_BOARD - List the number of messages
  APPLICATION_POST_MESSAGE - Post a new message
  APPLICATION_DELETE_MESSAGE - Delete a message
  APPLICATION_CLEAR_BOARD - Clear the entire board
  APPLICATION_READ_MESSAGE - Read a particular message

## Vulnerability
The vulnerability exists in the heartbeat message of this protocol and is very similar to the real world heartbleed vulnerability. To leverage it, a heartbeat message can be sent with a payload length longer than what exists in the heartbeat message. When the server processes it and responds, it will read past the end of the request message and return additional data from the memory space of the server. If the right conditions are in place, this additional data could contain sensitive information. 

In order to prove this vulnerability, the unauthorized memory access needs to contain sensitive information (ie magic page data). Some of this data is moved to the heap during a SLS handshake. The handshake does not need to be fully complete, but the first set of messages (CLIENT_HELLO, HELLO_VERIFY, CLIENT_HELLO w/cookie) need to be successfully navigated before the sensitive information will be available on the heap. Once it is there, its just a matter of lining up the heap in a way that allows an incoming heartbeat message to be placed in memory before the desired sensitive information and with a payload length incorrectly long enough that the sensitive information will be returned in the response. 


### Generic class of vulnerability
Improperly sanitizing program input allows reading past the end of the intended buffer leading to information disclosure.

### CWE classification
CWE-788 - Access of Memory Location After End of Buffer

## Challenges
Identifying and patching this vulnerability should be straightforward. To leverage the vulnerability to actually prove the type 2 pov will require a bit more effort. A partial handshake needs to be completed to move the magic page data into the correct location on the heap so a successful proof of the vulnerability will access the magic page data necessary to score. 
Finding: Easy
Proving: Medium
Patching: Easy

