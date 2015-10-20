# CGC Hangman Game

## Author Information

"Chris Eagle" <cseagle@nps.edu>

### DARPA performer group

Naval Postgraduate School (EAGLE)

## Description

An interactive guessing game in which players guess one letter at a time in a attempt to guess a randomly selected word before making too many incorrect guesses.

### Feature List

* This CB combines a player specified value with contents taken from the CB's secret page to select a secret word from a self contained word list.
* Players may repeat the game as often as they wish within the timeout period of the CB.
* Whenever a player correctly guesses the secret word before being hung, the player is offered the chance to enter their name into a high score list. 
* A single CGC binary POV which performs a coin flip to determine which vulnerability to exercise may be found in the pov_1 directory.

## Vulnerability

This service contains two vulnerabilities. Both vulnerabilities are present in the getHighScore function. A player must win the game in order to gain access to the vulnerable code. The first vulnerability is a buffer overflow while reading the player's name at line 73 of service.c. The second vulnerability is a format string vulnerability while printing the player's name at line 88 of service.c.

### Generic class of vulnerability

Stack based buffer overflow
Format string vulnerability

### CWE classification

CWE-121
CWE-134

## Challenges

This CB requires a CRS to implement a game playing strategy for hangman with a randomly selected word. The entire word list is known to the CRS. A CRS must win the game in order to have a chance to reach the vulnerable code. Three PoVs are provided. pov_3 exercises the stack overflow and negotiates a type 1 pov. pov_2 exercises the format string vulnerability and negotiates a type 2 pov. pov_1 performs a coin flip to randomly choose whether to exercises the stack overflow and do a type 1 or exercises the format string vulnerability and do a type 2. pov_1 demonstrates that a single PoV may be capable of choosing one of several possible vulnerabilities to prove. Additionally it should be noted that the current implementation of the PoVs for the format string vulnerability are subject to occasional failure depending on the distribution of null bytes in the secret data page. This potential for failure might motivate a CRS to chose to throw a PoV several times within a single round to increase the probability that a vulnerability is proved at least once.
