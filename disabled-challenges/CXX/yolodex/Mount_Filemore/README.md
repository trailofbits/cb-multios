# Mount_Filemore

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A file system image parser. 

### Feature List

Mount Filemore allows a user to send a CGFS compliant image for mounting and editing. 
The full list of commands are:
    -Mount Filesystem
    -List File/Directory
    -Recursively List Files/Directories
    -Preview File
    -Read From File
    -Write To File
    -Update File Size
    -Add File
    -Add Directory
    -Delete File
    -Delete Directory
    -View Mounted Filesystem Metadata
    -Unmount Filesystem


## Vulnerability
### Vuln 1
Files are stored across clusters. The clusters are indexed in a table which essentially creates a linked list of indices.
The vulnerability occurs in cgfs.cc:342. The unpatched CB does not properly factor in the offset when writing bytes 
to a cluster. If a user sends `num_bytes` < `cluster_size` the offset is not properly accounted for. This allows
the an overwrite into the adjacent cluster.

Triggering the exploit requires a little more work. If a user creates a file, creates a directory, and then updates
the file size it creates the directory cluster index will be in between the file's clusters. Using the overwrite
bug allows writing in the directory cluster and creating a file where the starting cluster points to the secret
page (or any arbitrary memory address). The CB keeps all the file entries in memory so in order to get the 
faux file to show up another file or directory must be added.

Finally the leak is triggered via the PreviewFile feature, which prints the first cluster's data.

#### Generic class of vulnerability

Heap Corruption

#### CWE classification

CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
CWE-122 Heap Overflow

#### Challenges

 - This CB requires the CRS to understand how the filesytem is laid out in memory as well as its indexing system through the 
    filesystem cluster table. The CB also must understand the filesystem metadata entries in order to properly add a 
    file in order to trigger the memory leak.
 - Distinguishing between the directory structure stored in memory as well as the filesystem stored in memory is 
    important for the CRS to reason about the proper set of commands to invoke to trigger the exploit

#### Difficulty

 - **Discovery**: medium
 - **Proving**: hard
 - **Patching**: easy
