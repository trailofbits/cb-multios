# LAN_Simulator

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description
This service implements a Local Area Network emulating basic switching and routing functions.  The Layer 2 protocol is similar to Ethernet v2 with 802.1q VLAN tagging support.  The Layer 3 protocol is similar to IPv4.  And the Layer 4 protocol is similar to UDP.  

The network functions are broken up into three challenge binaries.  cb_1 (switching) implements the Layer 2 functions and connects to the CRS using stdin and stdout where it expects to receive properly formatted L2/L3/L4 packets.  It then uses IPC to talk to the cb_2 (routing) binary and the cb_3 (server) binary.  The cb_2 binary implements the Layer 3 functions and routes between the subnet of the CRS and the subnet of the cb_3 binary.  The cb_3 binary implements several services which are accessible via different Layer 4 ports.

The Layer 2 protocol utilizes 2-byte source and destination addresses along with a 1-byte virtual LAN tag which is used on the "link" between the switch and router to differentiate traffic in the two subnets. It also provides a 4-byte checksum.  The maximum frame size is 255 bytes.

The Layer 3 protocol utilizes 4-byte source and destination addresses.  There are two subnets defined in the cb_2 binary.  Each uses a 24-bit mask which makes the first three bytes of the address the network and the last byte the host portion of the address.  The subnet addresses and router addresses are statically configured in the binary.  So, it's up to the CRS to determine a usable address on its subnet for communicating with the router and the other subnet.  In order to map between Layer 3 and Layer 2 addresses, the service uses an "Addresss Discovery Protocol" which allows a host on the network to broadcast an ADP packet asking for the correct Layer 2 address for a given Layer 3 address.  This is similar to the Address Resolution Protocol used in Ethernet/IP.  

The Layer 4 protocol utilizes 1-byte source and destination ports.  Being similar to UDP, it is a connectionless protocol.  The cb_3 challenge binary implements three network services.  On port 7, there is a simple echo service which sends back any data bytes received from a particular client.  On port 19, there is a character generation service which sends a random number of random bytes back to any client which sends a packet to the service.  On port 129, there is a password generation service which creates six random passwords each using ten "syllables" selected randomly from a preconfigured list.

### Feature List
This CB set implements the following protocols:
Layer 2 network protocol with VLAN support
Layer 3 network protocol with 32-bit address space and variable length subnetting
Layer 4 network protocol with support for up to 256 independent services

Server CB provides three network services: echo, chargen, and a password generator.

The routing CB provides layer 3 routing between two subnets one housing the CRS and the other housing the server CB.

The switching CB supports VLAN trunking, L2 address learning and broadcast packet forwarding.

## Vulnerability

# Vulnerability #1
The switch binary expects to receive "untagged" traffic (VLAN = 0) from the CRS and from the server binary.  It then tags this traffic when sending it to the router so that proper Layer 3 decisions can be made when forwarding it.  The switch binary fails to properly check the VLAN ID on packets received from the CRS.  This means that the CRS can send packets with a VLAN tag for the server's subnet and avoid having to send that traffic through the router process.  Because of this, the CRS is able to directly manipulate the Layer 2 source address which would normally have been set to the router's address when the packet was forwarded between subnets.  This source address is used in the password generation service as part of the randomization function.  By carefully controlling the source address value, the CRS can manipulate the random password generator such that they can determine the contents of the magic page resulting in a Type 2 vulnerability.

Specifically, there are 256 syllables used by the password generator.  For each password, ten are selected based on the bytes of the magic page.  But, those bytes aren't taken sequentially from the page.  They are selected using an offset which is determined from the Layer 2 source address.  For example, if the source contains 00 in the last two bits of the address, then every fourth byte is taken from the magic page.  A source containing 01 as the last two bits will result in an offset of five bytes.  Because the offset can be manipulated through the VLAN tag bug, the CRS can send multiple requests with differing offsets which will allow it to reveal four sequential bytes of the page.  Of course, to determine the original 4 bytes, the CRS will need to map the syllables from the generated passwords back to their original one-byte values.

# Vulnerability #2
On start-up, the router process takes the first four bytes of the magic page and sends them to the echo service running on the server.  This conversation is invisible to the CRS since it's on a different subnet.  

During the process of sending this echo request to the server, the router is forced to queue the packet while it sends and ADP request to determine the L2 address of the server.  After that address is resolved, the packet is sent.  But, the buffer which holds queued packets is never zeroed, so the contents of that echo request remains in memory.

The L2Adjacency table which holds the L3 to L2 address mappings exists in memory just before the packet queue and a bug in the handling of newly learned L2 adjacencies allows a overflow of that table.  By carefully crafting the overflowed bytes, the first packet queue structure which contains the copy of the echo request can be modified.  A new L3 address for the next hop, the next hop interface, and the 'valid' flag for that queue entry can be modified.  If the queue entry is set back to 'valid', then the router process will attempt to re-deliver the packet.  And, with the L3 address and interface modified correctly, it can be forced to deliver the packet to the CRS interface instead.

### Generic class of vulnerability
Vulnerability #1
Improper input validation

Vulnerability #2
Improper checking of array index and failure to initialize previously used memory

### CWE classification
Vulnerability #1
CWE-20: Improper Input Validation

Vulnerability #2
CWE-129: Improper Validation of Array Index
CWE-665: Improper Initialization
CWE-316: Cleartext Storage of Sensitive Information in Memory


## Challenges
The first challenge for the CRS is to understand the L2-L4 protocol formats and craft valid packets to interact with the CB's.  It must also properly respond to ADP requests from the router in order to receive traffic from the server CB.  

For the first vulnerability, the CRS must understand the topology of the network, find the bug which allows tagged traffic to be sent directly to the server and craft packets that manipulate the password generation service such that 4 sequential bytes of magic page can be decoded.  The Subjective Quantifications for this vulnerability are:

Discovering - Medium
Proving - Hard
Fixing - Easy

For the second vulnerability, the CRS needs to determine that the router has sent a packet to the server which contains a portion of the magic page.  It then needs to find the bug which will allow it to manipulate the old copy of the queued packet.  Because of the way the router process learns and ages L2 adjacencies, just overflowing that table isn't sufficient.  It needs to first overflow the table, then cause one of the L2 adjacency entries to age out, and then it can populate a correct entry which will allow the router to finally deliver the modified packet.  The Subjective Quantifications for this vulnerability are;

Discovering - Medium
Proving - Hard
Fixing - Easy
