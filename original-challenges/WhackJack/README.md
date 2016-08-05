# WhackJack

## Author Information

"Steve Wood" <swood@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This program is a game of chance called WhackJack.  It might or might not bear a similarity to another game with a rhyming name.  It allows up to 8 players to play, with players being human or computer simulated according to various play algorithms.

### Feature List

The service simulates a card game where the goal is to get a higher score than the dealer without going over 21.  Up to 8 players can play with the option of making some of those players computer simulated.  Five different algorithms are included that embody various schools of thought on how to play the game.  The game also includes a training mode whereby human players can get play hints from one of the algorithms. 

## Vulnerability
Vulnerability 1 is a buffer overwrite due to the programmer inadvertently using the wrong #define constant in a bounds check of a read from STDIN.  The read buffer is adjacent to the data structures holding player data, including a function pointer to the simulation algorithm chosen for that player.  An overwrite of this pointer will allow the attacker to jump to arbitrary code.

### Generic class of vulnerability
Stack buffer overwrite

### CWE classification
CWE-121 Stack-based Buffer Overflow

## Challenges

Vulnerability 1 is able to overwrite the function pointer for the simulation module, but not much else in the player data.  Therefore proving this vulnerability requires multiple steps.  First, a player has to be entered and setup as a computer player.  This enables the deference of the function pointer later.  The buffer overwrite is not long enough to set the variable setting the player as a computer simulation.  Next the overwrite needs to happen and setup shellcode to establish the desired register values.  However, the available buffer space is quite small so some creativity is needed to write enough shellcode.  POV_1 enters three fake players, and spreads the shellcode between the name fields in all three players, with the first jumping to the second and the second to the third.  Only the the player 1 data actually uses the vulnerable overwrite to get the first stage shellcode into place.  Once the shellcode is setup and the function pointer overwritten to point to the start of the shellcode, the game must be instructed to play a round of the game to invoke the function poniter.

An additional complexity is added in that a readline-type input function is used so the shellcode data, including the EIP and Register data from the framework, can't have 0x0a in the data.  A strcpy function is used to store the second and third stages of the shellcode, so it also must be null safe, including the values from the framework.  

This vulnerability is easy to find and very easy to fix.  Exploitation is hard given the constraints on the shellcode and the multiple steps required to invoke the shellcode.

	Finding Vulnerability 1: easy
	Proving Vulnerability 1: hard
	Fixing Vulnerability 1: easy

