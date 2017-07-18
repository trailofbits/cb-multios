# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is the Tick-A-Tack Game.

This game is quite similar to Tic-Tac-Toe, with a few modifications. First, instead of using X and O for the players, we are using P and Q. And player P always goes first.

To make the game a little more different, the game board is never sent to the player. Only the moves made by the computer are sent to the player. Thus, the player can either keep track of the computer's moves and generate their own board, or the player can simply continue guessing coordinates until the game ends. This will make it more challenging for automated analysis to determine that the protocol is similar to a Tic-Tac-Toe game.

Additionally, the computer always wins a tie, so the onus is on the player to actually try to win their games if they care about the score.

### Feature List

This service is inspired by Tic-Tac-Toe. Players can play a game, select which letter they want to be; which determines who goes first, select to play additional games, start over, or quit playing.

The service provides a menu system to assist players with supported commands.

The moves performed by the computer are determined using a custom pseudo random number generator that walks through the digits of PI. Each request to the PRNG will return subsequent digits of PI. Those digits are used modulo 3 to ensure the computer selects moves that are within a 3x3 grid (the game board).

## Vulnerability

The memory used to store the game data and scores is dynamically allocated at the start of the while(1) loop in main() in service.c one line 205. The first time into the while loop, `memory_base` is undefined, so the else if condition is true. This leads into the code that will allocate the memory and setup the game, `game->data` and `game->scores` pointers (lines 203 - 211).

The `game->data` and `game->scores` structs will then use the newly allocated memory.

The vulnerability comes about because the `memory_idx` varible is walked through the allocated memory to assign the `game->scores` and `game->data` pointers, but is never reset back to `memory_base`. Thus, any future pass through the while loop satisfying the if() conditions will cause the game pointer to be assigned to where `memory_idx` is currently pointing (i.e. the same location as `game->scores`). When it sould be assigned to where `memory_base` is pointing.

Following that incorrect assignment, future references to the game struct will read memory starting with `game->scores` and going off the end of the allocated memory. Since, `game->scores->player` and `game->scores->computer` are both 0 at this point, both game struct pointers are null.

Thus, after the if/else when `init_game_data(game->data)` is called on line 216 of service.c, the first function in `init_game_data` (tt.c line 65) is a memset which will be given null as it's first parameter (`data->top`), causing a segfault.

There are two ways to trigger this vulnerable code path.

1. The user plays 257 * 2 games, wins 257 games and loses 257 games. The scores in `game->scores` (`game->scores->player`, `game->scores->computer`) are both unsigned char, so after 256 games, they will overflow back to 0. 

Since, `memory_base` is defined and the scores have been set to 0, the next pass through the while loop will satisfy the if conditions, leading to the incorrect assignment of the game struct pointer to `memory_idx`.

This trigger method is represented by pov-1.xml. 

2. The user plays one or more games and selects the option "START OVER" from the replay menu. This option assumes that the player wants to continue playing, but with new scores. Thus the scores are re-set to 0 on line 231 of service.c.

So, if the scores both overflow to 0, the if conditions will be satisfied. This leads to the same incorrect assignment of the game struct pointer to `memory_idx`.

This trigger method is represented by pov-2.xml. 


I consider the pov-1 trigger method to be more difficult to find and less obvious to fix.

I consider pov-2 to be a red herring. The use of the START OVER menu option will directly cause the CB to segfault/core. This is reasonably easy to find and I expect the competitor CRS's to vary on their root cause analysis. In the one case, they may choose to patch out the START OVER option. Which is fine, it is not being tested in any pollers.


The support directory contains a few items used to generate pov-1 and pov-2. First, the findpov1.py script is used to determine at which inital index of pi the automated player PRNG should start. The first successful index is 598:

`SUCCESS: player_char: P, pi_index: 598, scores: p=257/c=257`

So, support/genpov1 is the state machine code used to generate pov-1.xml with the player's PRNG starting at the 598th digit of pi.

Because of some unkown extensive overhead in cb-server, I had to make a small change to cb-test to get it fully process pov-1. Around line 146 of cb-test where the parameters are listed for cb-server, I had to add a sufficiently large timeout parameter ('-t', '130').

It takes just over 2 mins to run pov-1.xml, so the cb-server timeout has to be increased in order for the test to complete properly. A timeout of 130 seconds works in testing.

The support/genpov2 directory is the state machine code used to generate pov-2.xml. This one is trivial, so nothing special was required to run it.


### Generic class of vulnerability

Integer Overflow
NULL Pointer Dereference

### CWE classification

Integer Overflow
CWE-120

NULL Pointer Dereference
CWE-476

## Challenges

- The first challenge is to play a full game through to completion. This will provide the player with access to the START OVER menu option.
- The second challenge is to notice that the scores are unsigned char which can overflow. And then correlate that with the guard on the game struct pointer assignment.
- The hardest challenge is to actually play 257 * 2 games and choose the correct player char (P or Q) and win exactly 257 games out of 257 * 2 games.
