# CROMU_00027 - ASCII Content Server

## Author Information

"Debbie Nuttall" <debbie@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is a content server patterned very loosely after an HTTP web server. It supports a custom markup and scripting language and serves all output as printable ASCII. 

### Feature List
The ASCII Content Server responds to these commands:
 
  REQUEST - retrieves a page from the server
  QUERY - prints the page tree hierarchy on the server
  SEND - upload a new page to the server
  REMOVE - delete a page from the server
  VISUALIZE - process the given page data as ASCII Markup and serve it back
  INTERACT - retrieves a page from the server while overriding the given variables 

The server starts with a default set of pages that exercise the available functionality including a markup language and scripting. 

ASCII Markup Language:
  ~ is the escape character
  ~t insert tab
  ~n insert newline
  ~[ insert left bracket
  ~] insert right bracket
  ~~ insert tilde
  ~# insert hash
  #variable# insert value of variable
  [] are script tags. 
Script actions are:
  var - set a variable
  box - put page data inside an ASCII text box
  line - draw a line of given length

The server supports variables within the page data. Variables can be set via a script or through the data portion of an INTERACT command. Variables can be retrieved by using the #varname# syntax within the page data. Variables set via the INTERACT command will override any variables present in the page data. The server stores all pages on the heap in a tree structure.

## Vulnerability
There are four vulnerabilities in this service. 

The first is an out of bounds write on a stack array. In tree.c:WalkTree() there is an array of pointers called node_stack. The node_stack array is used to perform a depth first search of the page tree. As the function walks the tree, it adds pointers to unexplored nodes to the node_stack along with a depth value to aid in printing the tree. The tree depth is restricted by the 63 byte length restriction on a node's name field. The node_stack is sized to hold a maximum depth tree, but does not account for the indent field stored along with the node so it is thus half the size it should be for a maximum depth tree. When a tree of appropriate dimensions is given to WalkTree(), node_stack will overflow allowing an overwrite of the return pointer on the stack with the address of a TreeNode on the heap. 

The second is a null pointer dereference. If the VISUALIZE or INTERACT commands are sent with a zero length data field, the service attempts to read the pointer to the data field which is null.

The third is a signed to unsigned conversion error that results in invalid memory access. 

### Generic class of vulnerability
Out of bounds write overflowing an array of pointers on the stack. 
Null pointer dereference.
Signed to unsigned conversion error 

### CWE classification
CWE-787 - Out of bounds write
CWE-476 - Null pointer dereference
CWE-195 - Signed to unsigned conversion error

## Challenges
The null pointer dereference and signed to unsigned conversion error should be detected through standard fuzzing. 

Identifying the out of bounds write vulnerability is not as straightforward as a standard buffer overflow because the overwrite does not occur with user generated input, but it can be mitigated using the same basic techniques as a standard buffer overflow. 

The challenge in proving it is for the CRS to construct a tree in memory capable of overflowing the node_stack buffer. The CRS must construct a tree that is at least 33 elements deep with each element also containing a peer. This requires adding one element at a time in a hierarchical fashion that is highly unlikely to occur through fuzzing. The CRS must then initiate a QUERY command at the top level of the tree to access the vulnerable WalkTree() function. 