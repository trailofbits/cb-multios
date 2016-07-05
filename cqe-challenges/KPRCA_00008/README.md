# KPRCA-00008

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:
This service implements a storage device over a USB-like network protocol. Basic functionality is implemented including read, write, and query size. The protocol implements functionality to eventually support hosting multiple devices on one server.

### Feature List
Protocol based on proven technology used everyday by millions of people. Storage device emulates a 128 blocks with a 512-byte block size. This gives the user an impressive 64KB (!) of disk space. Large enough to hold one picture (maybe?). Privacy guaranteed because your data will never be stored on disk, and is lost as soon as you disconnect.

## Vulnerability
Buffer overflow in the _WRITE_ command allows an attacker to overflow the _memory_ buffer and overwrite the function pointers in the __usb_t__ structure. The _memcpy_fast_ function, used by the _WRITE_ command, assumes that the length of a data packet will be greater than zero, which leads to a 16-byte overflow. If the length is set to zero, then the block address can be set to _NUM_BLOCKS_, which is the end of the _memory_ buffer. This gives 16-byte overwrite of the data after the _memory_ buffer, which is the __usb_t__ structure.

### Generic class of vulnerability
Buffer Overflow

### CWE classification
CWE-787: Out-of-bounds Write

## Challenges
The commands are wrapped in two structures, which increases the depth needed to get to the exploitable function. Additionally, the instructions that result in the overflow use _SSE_ registers, which must be supported by the analysis platform. In order to get to the point where commands can be sent, the _devlist_ command must be sent, the _devid_ extracted, and then sent as part of the _import_ command. Lastly, the use of function pointers may make control flow more difficult to analyze.
