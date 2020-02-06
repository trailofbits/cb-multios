# CROMU-00039: The super fantastic, totally secure, cloud-based string and integer storage system (SFTSCBSISS for short)

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This CB implements a basic service for setting and querying named variables.  It allows for string and 32-bit integer variables to be created, updated and queried by the client.  Communications between the client and service is accomplished over a custom network protocol that defines packet formats for read, write, response, and error types.

### Feature List

The service allows for the creation, update, and querying of named variables.  Names can be things like "system.name".  The contents of these variables can be strings or 32-bit integer values.

## Vulnerability

An error in the read request handler allows for an incorrect variable name length to be specified in the packet which causes a buffer overflow in the local name variable used in that function. 

### Generic class of vulnerability

Buffer overflow

### CWE classification

CWE-120: Buffer Copy without Checking Size of Input

## Challenges

Even though the CB fails to check the supplied length of the name variable, the rest of the packet must still be properly formatted.  It must have the correct version, must be a 'read' request, and must have an overall packet length that is properly calculated.  
