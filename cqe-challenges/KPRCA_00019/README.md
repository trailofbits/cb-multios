# KPRCA-00019

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service represents a device that implements a human-interface device protocol over a session protocol that is responsible for muxing, fragmentation and reassembly. It is similar to a different protocol known as Bluetooth, but definitely is not Bluetooth. There are three layers of protocols which makes the system very extensible and flexible. 

### Feature List

The bottom layer is designed to interface with a radio and has a fixed packet length that should support speeds up to 723 kb/s. The middle layer supports packet sizes up to 64KB and will fragment them as necessary before sending to the bottom layer. Additionally, the middle layer has support for 65471 dynamic channels that can be created and destroyed as needed, with fixed addresses to multiplex between several applications. The only application that is implemented in this device represents a simple RID, with random data generated rather than human data.

## Vulnerability

The vulnerability is present in the options parsing in session\_configuration\_request. The protocol specifies that unknown required options be sent in the response with a unknown options result. However, the function does not allocate enough memory to hold all of the options if the length of an option goes beyond the end of the command length. This can result in an overflow of up to 254 bytes; more than enough to overwrite the heap structures of the next block or the contents of the next block. From this point, a write-anywhere condition is possible to cause a function pointer to be overwritten.

### Generic class of vulnerability
Heap-based Buffer Overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow

## Challenges

The two primary challenges are the complexity of the protocol and the integrity function. The system is composed of three separate protocols that interact with each other, sometimes using function pointers to do so. The released PCAP only has one session, so attackers will need to analyze the binary as well to understand the protocol. A successful attack is only possible by correctly adjust a couple of length bytes and adding the proper data. The released PCAP is also the only test of the integrity function, which sends back the contents of the code to make sure it has not been modified. Only a very small amount of the main function is verified, so a patch is still possible, but heavy-weight systems may have issues if not designed well.
