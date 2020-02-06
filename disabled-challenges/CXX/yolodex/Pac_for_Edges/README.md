# Pac_for_Edges

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This service creates an interface in which someone can play a game where you drive a character around to collect all the dots.
You cannot drive into the side walls, or the middle walls (shown as "+"), and you only have a limited number of moves in which
to collect all of the dots. If you are successful in collecting all the dots before you run out of moves, then you are able 
to send an image to the service. Edge detection is then performed on this image and another image is returned containing
only the edges of the image which was sent in. 

To move the initial game, the program expects the following charachters, followed by new lines. 
w = move up, d = move right, a = move left, s = move down. 
Additionally, q enters into a teleport mode which you can then send a number which linearly maps to board positions. 

### Feature List

If the initial game is won, the service makes available an awesome edge detector which does a particularly good job extracting
edges from portraits. This algortihm is realtivly quick given the power of the results. 

## Vulnerability

### Vulnerability 1

The vulnerability is triggered by overflowing the buffer which holds the width field of the image. In order to get the program to
continue execution, the overflow should start with "512 " and then can contain your desired exploit. In the POV provided, we 
utilize the overflow to control the next and prev pointers of the next free block to overwrite a saved ebp on the stack.

To patch, we terminate if the attacker tries to load 20 bytes into the buffer. 

#### Generic class of vulnerability
Heap-based Buffed Overflow

#### CWE classification
CWE-122: Heap-based Buffer Overflow

#### Challenges

Discovery via un-intelligent fuzzing would be difficult as it would take more than the allowed number of moves to random walk the map.
This said, if you figure out that "q" is a teleport, then simply incrementing the teleport location (second input) will solve the game.  

#### Difficulty

 - **Discovery**: Medium
 - **Proving**: Medium
 - **Patching**: Easy
