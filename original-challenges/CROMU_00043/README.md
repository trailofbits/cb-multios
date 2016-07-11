# CROMU_00043 - Packet Analyzer

## Author Information

"Debbie Nuttall" <debbie@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a protocol aware packet analyzer. It analyzes packets in the newly defined DCAP file format and produces text output with varying levels of detail. It can also operate in continuous mode to analyze traffic as it is received. 

### Feature List

The Packet Parser is aware of the following protocols:
  Physical Layer - Wire, Radio, and Raw 
  Transport Layer - Stream and Message
  Network Layer - Endpoint, Broadcast, and Debug
  Application Layer - Web, Music, Video, Email, and File

Upon first connecting to the service, a header is sent to configure the mode and display parameters. The modes are:
  File - In file mode a DCAP file is sent, the output is returned, and the session ends.
  Stream - In stream mode the service continuously receives packets and sends output until a zero length packet is received. 

The display parameters are:
  Physical - enable/disable display of the physical layer information
  Transport - enable/disable display of the transport layer information
  Connection - enable/disable display of the connection information
  Application - enable/disable display of the content information
  Statistics - enable/disable display of packet statistics

Multiple positive and negative packet filters can be applied to each session. 

## Vulnerability
There are two vulnerabilities in this service. 

The first vulnerability in this service is an uncontrolled format string vulnerability. The TransmitOptionHeader function in packet_analysis.c passes a user supplied string directly to the TransmitFormattedBytes function which takes a variable number of arguments and processes a formatted string for output similar to printf. The TransmitFormattedBytes has a format specifier that reads an address and value from the input stream and writes that value to that address. If the user supplied string contains the appropriate format specifier, the result will be a write of user supplied data to a user supplied address. 

The second vulnerability in this service is an out of bounds read. In the AnalyzeApplicationLayer function, a specially crafted packet can cause the parser to read past the end of the packet buffer in memory. The vulnerability occurs because the length field of the To and Subject fields of an email message are not checked for proper bounds. 

### Generic class of vulnerability
Uncontrolled format string that results in a write what where condition.
Out of bounds read past the end of a heap buffer. 

### CWE classification
CWE-134 - Uncontrolled Format String
CWE-125 - Out of Bounds Read

## Challenges
No example inputs are provided to the CRS for this challenge. The CRS must discover the proper input format by examining the binary. In order to leverage the write what where vulnerability, the CRS must create an input that passes enough format checks to reach the point in the service where a format string will be passed to the output function. It must then include a format specifier in the correct place within the input to trigger the vulnerability. 

In order to prove the out of bounds read vulnerability the CRS must construct an input that passes every analysis step to reach the inner Application layer of the packet. The Application layer must be properly constructed except for an invalid length field in either the To or Subject email field. 
