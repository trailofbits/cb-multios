# CROMU_00030 - The Longest Road

## Author Information
"James Nuttall" <james@cromulence.co>

### DARPA performer group
Cromulence

## Description
This service offers a game over a protocol loosely based off of IEEE 802.11. The CRS must authenticate and associate with the game server and play the game to completion. For the game, pieces are placed on the 'board' that contain roads. The CRS must lay game pieces to create a single, long road by choosing what sides of each piece to connect to previous pieces.

### Feature List
Upon connection, the CRS is asked to provide a buffer of data to seed the pseudo-random number generator. This allows the POV to create a deterministic program flow.

For the protocol, the CRS must associate, authenticate, and send proper data packets to play the game.

Within the game, the CRS can select from three options:
During one connection (determined by the association), the CRS can only make 9 actions from the following set:
	1. Lay down piece
	2. Draw a piece
	3. Discard a piece
	4. Ask length of longest road
	5. Exit

After 9 actions, the user must deauthenticate and disassociate then reassociate and reauthenticate to restart the connection. This was done to force complexity and state-awareness.

After 3 incorrect packets the entire connection is reset. This was intended to prevent brute forcing various states of the game.

## Vulnerability
The vulnerability for the CRS to find is a simple buffer overflow that is only available when the user wins the game. The CRS is prompted to enter their name and the receiving buffer only contains 5 characters, but does not properly bounds check the input.


### Generic class of vulnerability 
Stack-based overflow from CRS input. The CRS is able to directly enter a buffer that is stored in a fixed buffer on the stack.

### CWE classification 
CWE-121 Stack-based Buffer Overflow

## Challenges 
The challenge of this binary is providing proper input to create a connection, encryption, and game choices to reach the vulnerable state.
