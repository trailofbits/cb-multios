# Shortest_Path_Tree_Calculator

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description
This CB, given a list of nodes and edges as input, calculates the nodes in the shortest path from a given starting node to a given ending node.

### Feature List
The CB accepts three commands:
  - Send Nodes: Allows the user to input a set of nodes
  - Send Edges: Allows the user to input a set of edges
  - Run SPT: Instructs the program to calculate the shortest path from a starting to an ending node

Upon completion of the SPT calculation, a list of nodes is sent back to the user.

## Vulnerability
The CB has a limit to the number of nodes that it will accept.  However, this limit is enforced on each use of the "Send Nodes" command rather than on the total of all nodes sent to the program.  While this doesn't cause a problem for the SPT algorithm itself, it does cause a problem for the resulting shortest path list of nodes.  The CB uses an unsigned 8-bit integer to store the total number of nodes in the SPT and uses this to calculate the size of a memory allocation call.  If the number of nodes in the SPT overflows this integer, too little storage will be allocated creating a buffer underwrite condition.

### Generic class of vulnerability
Incorrect buffer size calculation leading to a buffer underwrite

### CWE classification
CWE-124 Buffer Underwrite ('Buffer Underflow')
CWE-131 Incorrect Calculation of Buffer Size

## Challenges
The heap-based buffer underwrite allows control of the linked-list of edges that have been sent to the CB.  By controlling the list's pointers, it's possible to cause a block of stack memory to be placed on the list of free blocks for later reallocation.  Then, when that next allocation occurs, data is written to the stack allowing overwrite of critical stack contents including the return address of main().  

The difficulty in setting up this sequence of events is with the lookaside table used by the library malloc function.  In order to be sure the correct block of previously free'd memory is used for the subsequent allocation, the size of the freed block must be carefully controlled.  And since this size is part of the heap metadata, when the fake block of stack-based memory is freed, it must have correct metadata.  Fortunately, main() has a stack-based counter variable which limits the number of commands that can be sent to the CB.  By sending exactly the right number of previous commands and positioning the freed block correctly, the stack-based block can be freed into the correct lookaside bucket for later re-use by the pov.  

The Subjective Quantifications for this vulnerability are:

Discovering - Medium
Proving - Hard
Fixing - Easy
