# CROMU-00016: Network Queuing Simulator

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description
This CB implements a network queuing simulator.  Based on inputs from the user,
the program simulates the transmission of network traffic through an interface 
tracking statistics like total packets sent, dropped packets, average latency, etc.

### Feature List
Users are able configure these items:
	- Interface bit-rate
	- Packet generator
	- Number of queues
	- Types, depths, priorities, and weights of those queues
	- Length of the simulation

## Vulnerability
Multiple vulnerabilities exist in this CB.  

1. A very simple buffer overflow exists in the packet generator selection code.  The buffer
reading the user's selected packet generator is sized too small for the number of characters
they are allowed to enter.

2. A slightly more complicated buffer overflow exists in the packet statistics output code
which is run at the end of the simulation.  During the input phase, the user is prompted
for the run time of the simulation.  The prompt describes allowable inputs of 1 - 10 seconds.
However, the unpatched CB allows for larger values.  If run with a large enough value, and
appropriately selected interface and input packet rates, the interface total packet counter
will exceed its available print buffer when the statistics are displayed.

### Generic class of vulnerability
1. Buffer overflow

2. Buffer overflow

### CWE classification
1. CWE-131: Incorrect Calculation of Buffer Size

2. CWE-120: Buffer Copy without Checking Size of Input

## Challenges

The first vulnerability in this CB is realatively easy to identify.  The second will require
more in depth code analysis or careful selection of inputs to trigger the overflow. 
