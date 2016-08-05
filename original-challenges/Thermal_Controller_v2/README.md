# Thermal_Controller_v2

## Author Information

"James Nuttall" <james@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is a reimplementation of CROMU_00050: a heating element controller. This version uses C++, a String class, and a linked list to differentiate its operations. 

### Feature List

The thermal controller is much more capable than the typical controller found in consumer level appliances such as stoves.  Although it does contain static modes such a maintaining a set temperature, it also supports up to 10 temperature sensors, a smoke sensor, and a 10 step programmable thermal profile.  The different program steps can be based on temperature triggers from any of the configured temperature probes, or can dwell at a fixed temperature for a programmed length of time.  An ideal use of this controller would be in a competition BBQ smoker where different kinds of meat require finely tuned adjustments to temperature during the smoking process to result in proper breakdown of connective tissue, maintenance of moinsture, and control of the smoke generation.  The controller was designed to be remotely operated using a separate "app" on a mobile device, and implements a binary protocol for this purprose.  The controller was designed to be robust and rigorously checks that remote commands correctly configure the device. 

## Vulnerability
The ReadInput function, which reads the intial packet into the system, does not properly reset the buffer position counter. So the CRS can send the initial 0xa5 byte over and over again to grow over the allocated 512 bytes. The CRS must send double the buffer size because every other byte is consumed by the reading process. After the proper buffer size (1046 bytes), the CRS must then send a proper packet so that the ReadInput function returns back to main instead of hitting one of the _terminate() calls.

### Generic class of vulnerability
Stack buffer overflow

### CWE classification
CWE-121 Stack-based Buffer Overflow


## Challenges
Finding and fixing the overflow should prove somewhat difficult for the CRS. However, once found, proving the vulnerability should prove easy.
When finding the vulnerability, dumb fuzzing won't work because it requires the CRS to send a valid packet at the end of the buffer.
When fixing the buffer overflow, simply increasing the size of the buffer won't work.

Subjective Quantification:
Discovering - Medium
Proving - Easy
Fixing - Medium
