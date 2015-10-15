# CROMU-00010: Street map service

## Author Information

“James Connor” <jymbo@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description
This service performs routing across the map information provided. A user shell is
provided to allow input of map data, and route requests   

### Feature List
The map supports roads, addresses, and intersections.  Intersections are constucted 
by selecting two roads to join.  Addresses are numbers on road, between two 
intersections. The map can be printed and routes from address to address can be 
resolved.


## Vulnerability
Routing is performed by traversing intersections on a discovered road to discover 
additional connected roads.  As unique roads(nodes) are discovered, they are pushed
to a list stored in a the data[4080] element of a linked list node.  The size limit 
for the number of traversals which can be stored in the data element is checked 
against sizeof(pointer), rather than sizeof(element), resulting in a heap overwrite.

### Generic class of vulnerability
Heap overflow
### CWE classification
CWE-467
## Challenges
Different elements are stored in common data containers, creating a challenge for
inferring data types.  Also, a CRS must created a valid, sufficiently deep graph to 
reach the vulnerable route function.
