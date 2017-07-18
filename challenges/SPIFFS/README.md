# CROMU-00035: 

## Author Information

“James Connor” <jymbo@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description
SPIFFS (Somewhat Poorly Implemented Fast File System) is an im memory file system. user is provided a prompt from which users, groups, directories, files, and file permissions can be added, removed, appended, and displayed  
### Feature List
Files and directorys have permision attributes for users and groups of users.  
Directories are hierarchical.
Files can be uploaded, appended, displayed, and truncated.
users can be added, removed, added to groups and removed from groups
groups can be added removed and displayed

## Vulnerability
POV1
	File path is malloc'd as needed but then copied via unbounded copy into a fixed size buffer producing a classic buffer overflow

POV2
	deleting the only permision on a file results in a use after free, due to failing to update the perm link in Node_s 

### Generic class of vulnerability
POV1 
	Buffer Overflow

POV2
	Use AFter Free

### CWE classification
CWE-785: Use of Path Manipulation Function without Maximum-sized Buffer
CWE-416: Use After Free
## Challenges
Complex state
file chunks can be reallocated outside of create and destroy
perm tree is sanitized during ls but can contain many unexploitable invalid heap pointers at any given time
Malloc and free are seperated across a recusive call 
