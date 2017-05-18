# REMATCH_3--Address_Resolution_Service--SQL_Slammer

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description

Despite its name, the SQL Slammer worm is not based on SQL injection. It is a classic buffer overflow in Microsoft SQL Server that was discovered in the wild on January 25th 2003. The first super fast spreading worm, Slammer spread worldwide and ground the Internet to a halt in just 10 minutes. Slammer is a single UDP packet sent to port 1434 running Microsoft SQL Server Resolution Service. The worm simply spread itself and did nothing else, but the rapid flood of packets was enough to break the Internet as routers were overwhelmed and crashed. The vulnerability was publicly released and patched 4 months before the Slammer worm was found in the wild but most systems were not yet up to date.

The vulnerability, CVE-2002-0649, isn’t actually in SQL Server, its in a companion service that runs on another port and provides ‘address resolution’ to redirect to the correct port when multiple instances of SQL Server are running on one machine. This service mimics the Microsoft SQL Server Resolution Service. A simple UDP protocol is used to query the service and a response is sent. 

### Feature List
This service accepts queries and responds with the correct service to connect to. The commands it will process are: 
QUERY_ALL - List all servers in the network
QUERY_SERVER - List all instances on one server
QUERY_ONE - List the port assigned to one instance
QUERY_ADMIN - Report Admin info for one instance

The service is initialized with a random set of services and instances. 

## Vulnerability
The vulnerability is easily accessed with a simple UDP packet. The first byte of the offending packet needs to contain the command QUERY_ONE (0x03) and the remaining bytes need to be long enough to overflow a 64 byte buffer. The packet is terminated with a newline (0x0a). The remaining bytes are then copied onto a stack buffer that is only 64 bytes long, resulting in an overflow. 

### Generic class of vulnerability
Straightforward buffer overflow. 

### CWE classification
CWE-121 Stack based buffer overflow

## Challenges
This vulnerability should be extremely easy to find, prove, and patch. It poses no challenges. 
Find: Easy
Prove: Easy
Patch: Easy

