# CGC Pipelined IPC Challenge Binary 

## Author Information

"Brian Caswell" <bmc@lungetech.com>

### DARPA performer group
Lunge Technology (LUNGE)

## Description

This is an IPC challenge binary for use within DARPA's Cyber Grand Challenge that shows DECREE IPC can be used to replicate pipelined processes.  Traditional unix pipelined processes read data from stdin and send to stdout, providing some sort of transformation or computation on the data.  This challenge binary replicates this execution model by linking together the provided functions made available by disperate challenge binaries in an arbitrary fashion.

### Feature List
This CB includes a number of small executables that provide a unique function that can be linked together in a user defined order to simulate the unix pipeline IPC mechanism.  

A few notes on the underlying implementation:
* Each function made available for the IPC chain is implemented in a unique executable.
* Each 'function' processes input per line, exiting upon recieving a line that begins with a null byte.
* Each 'function' can be configured to receive input from the network client or from another executable.
* Each 'function' can be configured to transmit output from the network client or from another executable.

The functionality made available by the CB is split across the following executables:
* CB\_1 implements the command and control mechanism for setting up the IPC and handles passing any required configuration to the executables in the IPC pipeline.
* CB\_2 provides the 'contain' function for the pipeline.  The 'contain' function implements a 'grep' like function utilizing the Morris-Pratt fast pattern match algorithm.
* CB\_3 provides the 'word-count' function for the pipeline.  The 'word-count' function implements a 'word count' utility, akin to 'wc' on unix systems, which provides counts of the characters, words, and lines for each line.
* CB\_4 provides the 'does-not-contain' function for the pipeline.  The 'does-not-contain' function implements a 'inverse grep' like function utilizing a niave search algorithm.
* CB\_5 provides the 'compress' function for the pipeline.  The 'compress' function implements a per-byte Run-Length-Encoding (RLE) mechanism to compress input.
* CB\_6 provides the 'decompress' function for the pipeline.  The 'decompress' function undoes the RLE mechanism provided by 'compress'.

## Vulnerability
The vulnerability is a stack based buffer overflow in CB\_6, however the CB is not directly accessable.  Input must flow from one of the previous CBs prior to transfering to the final CB.  The CB is written such that it will not process traffic directly from the network.  A POV may pass through any of the other sub-CBs (2 through 5) and prove the vulnerability exists.

### Generic class of vulnerability
Stack based Buffer Overflow

### CWE classification
CWE-121

## Challenges

This CB shows the dynamic data input chaining that can occur within a single challenge binary.  The core idea being expressed is that the IPC model within the CBs can be dynamic in nature, and leveraged as the CB author or CRS determines.
