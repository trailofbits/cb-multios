# GPS Tracker

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a GPS Package Tracking Device simulation. The tracking device implements Geofencing alerts and allows the receiver to track the location of the package. All commands are sent via a custom binary protocol to the device.

### Feature List

The GPS Package Tracking device supports geo fencing by sending it a list of geofence coordinates and a radius for each coordinate. When the devices position is outside the allowed distance for one of these coordinates the device will alert the receiver with a response packet and the coordinate and distance the device is from that geo fenced position. A special debug mode allows the receiver to command and set various parameters of the tracking device and is used by the poller to test the geofencing capability of the device. In addition multiple additional modes are supported including sleep/wake commands, info command which provides information about the tracking device, position command for retrieving current position, and a shutdown command for shutting off the device.

## Vulnerability

There is 2 vulnerabilities in this service. 

The first vulnerability is a rather simple stack overflow of the geofence coordinate data. It is possible to send 3 different geofence update commands. The first command will reset all points in the systems geofence array with the new points sent, up to a maximum of 20. The second command will add a new set of points to the existing geofence coordinates in the array. The vulnerability is here in that the program naively only checks the incoming number of points against the maximum 20, but does not account for existing points in the array already. This allows up to 39 points to be stored causing an overflow. The overflow allows the user to overwrite the stack frame for main with coordinate data. It is possible to completely overwrite the return address with the distance 32-bit value and control one of two registers with 22-bits of data from the packed coordinate data.

The second vulnerability is a memory disclosure vulnerability caused by the usage of an uninitialized variable. In the debug command a challenge token must be presented to the device to access the debug capabilities. This token is a 64-bit value derived from the magic page. It is loaded onto the stack for that function call. When failing this check the stack will unwind and it is then possible to then send a geofence update command and access 6-bytes of this data as packed coordinate data. The POV must however decode the data from its XOR mask at the appropriate offset before submitting at a type 2 memory disclosure.

### Generic class of vulnerability
Vulnerability 1 of 2:
Buffer Copy with Checking Size of Input
Stack based buffer overflow

Vulnerability 2 of 2:
Use of uninitialized variable
Memory disclosure

### CWE classification
Vulnerability 1 of 2:
CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
CWE-121: Stack-based Buffer Overflow

Vulnerability 2 of 2:
CWE-457: Use of Uninitialized Variable
CWE-200: Information Exposure

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Medium/Medium
Proving: Easy/Medium
Fixing: Easy/Easy

This CB has two vulnerabilities. The first is a relatively simple stack based buffer overflow. The difficulty in discovering it lies in setting up the state of the system to allow the geofence update command to write point data beyond the size of point array. The next vulnerability is due to a failure to initialize a variable in a structure which causes a resultant memory disclosure from the stack. It is possible to align the stack in such a manner where a portion of the magic page data exists resulting in a type 2 POV. The difficulty here is both discovering the disclosure data is being sent out and reversing the XOR transformation on this data to submit it.
