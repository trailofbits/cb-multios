# REMATCH_4--CGCRPC_Server--MS08-067

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description
Microsoft first identified MS08-067 when it started being used 'in the wild' to spread a botnet. While this vulnerability was considered dangerous enough for Microsoft to elicit an out of band patch in October, the patch was not deployed widely enough and malware had great success propagating via this method for a long time afterwards. 

The vulnerability, CVE-2008-4250, is a buffer overflow in the NetPathCanonicalize function of the Microsoft RPC Server. Microsoft compiled this code using stack protection techniques to prevent stack buffer overflows, but the unique characteristics of this bug allowed an attacker to bypass that protection and gain code execution anyway. 

This service is based on the original Microsoft RPC server and contains a similar vulnerability. The service is accessed over an SMB like interface and supports multiple operation primitives including the NetPathCanonicalize service that allows access to the vulnerability.  


### Feature List
This binary mimics the Microsoft RPC Server. It is accessed via the CGCMB protocol which is patterned after SMB as the transport protocol. After processing the CGCMB layer, the service handles the CGCRPC protocol which is patterned after Microsoft RPC. 

Once a connection is established through these layered protocols, the service allows access to the file system through commands like listing the service types, getting file statistics, and canonicalizing the path name. Paths for this service use special characters to delineate the service primitive, nested directories, and filenames. Canonicalizing the path refers to removing any extraneous directories and directory traversal primitives to arrive at the most direct path to that particular file. 

## Vulnerability
This vulnerability allows a stack based buffer overflow. The service that contains the buffer utilizes a stack canary to prevent exploitation via this method. However, the function containing the buffer passes a pointer to the stack buffer to another function that does not utilize stack canaries. While processing inside this secondary function, the program allows moving backwards before the start of the buffer and writing user controlled data which leads to overwriting the stack frame of the secondary function leading to execution control that bypasses the stack protection.  

This vulnerability occurs during path canonicalization. When a directory traversal primitive is encountered, the program walks backwards through the path string to find the last known directory marker. In special circumstances, the program may walk farther back than the beginning of the buffer, thus allowing an out of bounds write on the stack. 

### Generic class of vulnerability
Buffer overflow due to incorrect bounds calculation. 

### CWE classification
CWE-135 - Incorrect Calculation of Multi-Byte String Length

## Challenges
This vulnerability is not as straightforward as a simple buffer overflow. The CRS must determine the specific sequence of characters that allows the improper write to occur as well as correctly handle the buffer that exists in one stack frame to overwrite control in a separate stack frame. Since this bug bypasses traditional stack protection methods, automatic protections may not be as effective in preventing it. 
Finding: Medium
Proving: Medium
Patching: Medium

