# Space_Attackers

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This service creates an interface in which someone can play an awesome game where the player avoids lasers coming downwards, 
while shooting lasers themself back up at the enemy. Sending a newline steps the game forward. If no key has been pressed when
the newline is sent, the ship will fire. Otherwise, w = move up, d = move right, a = move left, s = move down. 

### Feature List

When the game starts, the user inputs their name and is greeted into the game as the General they will become. The game then proceeds
until either the enemies reach the bottom (lose), the player is hit by an enemy laser (lose) or all the enemies are eliminated (win). 
If the player wins, they are then entered into a "Dance Mode" for celebration.  

## Vulnerability

### Vulnerability 1

If the player inputs their name as "magic", then a special cheat mode is enabled which forces the enemies to move in a simple
pattern and to not fire. This allows the player to easily win the game and enter "Dance Mode". 

Once in "Dance Mode", the player can send "w\n" to increment a counter and "s\n" to save the counter as a byte in a buffer. When
the buffer is in the desired state, the player can send "d\n" to strcpy the buffer being created into a 256 byte buffer residing 
on the stack (service.c:708). 

#### Generic class of vulnerability
Stack-based buffer overflow

#### CWE classification
CWE-121: Stack-based Buffer Overflow

#### Challenges

 - Discovery via fuzzing is difficult because it is hard to win the game without using the cheat mode. Symbolic execution or static analysis may work better to find the vulnerable code.
 - Proving requires using the cheat mode and also generating the correct input which is difficult because there is not data flow from the input to the vulnerable buffer.

#### Difficulty

 - **Discovery**: Medium
 - **Proving**: Medium
 - **Patching**: Easy
