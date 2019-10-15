# KPRCA-00030

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This CB is based on Conways Game of Life and uses a Quadtree to implement the infrastructure. The CB turned the rules of Conways game of life into a shooter type game. When imagined it was thought of as a space shooter, where the person is controlling some kind of ship shooting and bombing other enemy ships. But it is completely up to the players imagination. 

The game spans an 8k by 8k board and upon a new game creates 25 "ships" or "runners". Each runner travels the diagnoally across the board to the further corner. The game ends in 10000 steps, which typically isn't enough time for any of the runners to get to the end of the board. A player has two options, the first is to shoot at an unrevealed board and receive 100 points for each successful pixel hit. The second option is to plant a bomb after seeing the current position of the board. Bombs are detonated 10 steps after the runners start moving, and the minimum number of steps a player can choose is 100. This was more or less arbitary but it seemed a litlte more fun this way. Bombing is the way to rack up major points, because each bomb hits 9 squares, the pixel its planted on and the 8 adjacent pixels. Each runner pixel that is blown up via a single bomb gives a multiplicative score bonus.

The rules aren't necessarily explained to the user, but the game is simple enough that it shoudln't be difficult to figure out.

### Feature List
Before the board is revealed, the player may choose:
1. Shoot!
2. Reveal Board
3. New Game
4. Quit

After the board is revealed the player may choose to:
1. Place Bomb
2. Reveal Board
3. Let them Run!
4. New Game
5. Quit

And once the game is over the player may either:
1. New Game
2. Quit

## Vulnerability

The vulnerability is triggered when a user places two bomb close enough to one another such that they both destroy the same cell. The code doesn't properly check the return value from the qt_get_pixel function, but instead assumes that the cell will always exist since it's already in the living cells linked list. However, because the program tries to remove the dead cell from the tree, this assumption is wrong with multiple adjacent bombs and causes the program to crash.

### CWE classification

CWE-690: Unchecked Return Value

## Challenges

This challenge attempts to do a few things in order to make it difficult. The first challenge is obscurity, the program gives no real guidance on how the game should be played and it's not obvious what the rules are. Additionally bombs are triggered after 10 steps, but the minimum number of steps run is 100. This was intended to make it slightly less obvious to determine what triggers a bomb. Additionally the runners follow a Conways game of life time trajectory, but that isn't specified to the player.

The second challenge was contraining resources (namely bombs) while creating a large game board. The size of the board is 8192 x 8192, which is meant to make brute forcing slightly more difficult.
