# Dungeon_Master

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

You awaken in a dark room to the sound of flapping and moaning. With a torch in your hand, you slowly descend a stone staircase that you can only hope will lead to safety....

Dungeon Master is the lastest thrilling game from No Way Out Entertainment. Can you master your way through the darkness to find the hidden treasure you desire. But beware, the next step you take could lead you closer to or farther from your goal. 

### Feature List

The player is first presented with a menu giving instructions on how to
a) Play the game
b) Display all high scores
c) Retrieve the game instructions
d) Quit the game

Once in the game the player will have the ability to
a) move left or right
b) jump left, right or straight up

The game also uses the player's move choices to determine the configuration of rooms the player will have to traverse until the treasure is reached. 

The dungeon is made up of the following object types:

Floor "-" and Wall "|": These objects make up the boundaries of a game. No object may pass through them.

Empty ' ': These objects represent free space that other moving objects may move to. 

Player "R": A movable object representing the player of the game. If there is no floor present, the player will continue to fall until it reaches a Boundary object. 

Enemies: A moveable object that kills the player when contact is made. Enemies move in one direction according to their movement pattern until they make contact with a Boundary object. Once contact is made they reverse direction. There are two types of enemies:
	
	Bat "v": Move in a V-pattern and do not need to be in contact with the floor.

	Zombie "&": Move until they come in contact with a Wall or Floor. Must be in contact with the Floor or else they will continue to fall.

Treasure "@": Once the player makes contact with the treasure, the game is won.

## Vulnerability 1

The vulnerability in this CB is an off-by-one error in the addMove function, where the amount of memory malloc'ed by the service to store the body of the moveList is 1 char shorter than what is needed to store a null-terminated string. This results in an improper null termination. When a new move list is created, the flag is copied into a 512-byte chunk. So, when the new move list is 512-bytes, the chunk containing the flag will be adjacent. By filling the move list with 512-bytes of player moves, by the time the next move list is created, the old move list and the flag will be copied into the new move list. 

When a player wins the game the move list is sent back to the player. By successfully exploiting this vulnerability, the flag will also be contained within. 

### Generic class of vulnerability

Improper Null Termination
Off-by-one Error
Out-of-bounds Read

### CWE classification

CWE-170: Improper Null Termination
CWE-193: Off-by-one Error
CWE-125: Out-of-bounds Read

### Challenges

1. The off-by-one error should easily be detected, but understanding how long the move list needs to be in order for it to be allocated in a chunk preceeding the flag could be a challenge.

2. Successful exploitation will require determination of how move choices impact the size of the move list, as well as ensuring that the move list is full before a new move list is created.  

3. Only a winning game will return the move list to the user. Therefore, sucessfully creating a winning combination of moves will be required.

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy

## Vulnerability 2

This vulnerability is a stack-based buffer overflow in the sendHighScores function, that has the ability to overwrite the return address of the calling function. When the user requests the list of high scores to be returned, the score of the top player is copied into a static buffer. If the name of the top player is too large it will overflow the buffer and allow an overwrite of the stored return address and base pointer. 

### Generic class of vulnerability

Stack-based Buffer Overflow
Out-of-bounds Write

### CWE classification

CWE-121: Stack-based Buffer Overflow
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

### Challenges

### Challenges
1. Only a winning game will allow the user to provide an overly large name for the winning player. Also, only the top player's name can overflow the buffer. An initial list of high scorers are loaded at the initialization of the service. Therefore, the winning combinations of moves will have to result in less total moves than the top player.

2. The winning player name is received from the user and stored using a different control flow from the one to display the high score list. Therefore, one will have to link the two independent control flows to successfully identify and exploit the vulnerability.

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy

