# Childs_Game

## Author Information
Kaprica Security

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A gaming system that pits a user against a basic AI

### Feature List

After a user registers, there are 3 games that can be played
Games:
    1. Hammer, Sheet, Sheers
    2. Guess my number
    3. Three in a row
    4. Give up

The games are inspired by class children's games.

## Vulnerability

### Vuln 1
The Guess my number game let's a user choose the maximum of the range of numbers the computer will choose.
There is an improper bounds check that doesn't account for negative numbers. The random number is generated
from the magic page and then a bitewise & is done against the value and the range max. If a user changes the
range max to -1, it will & with 0xFFFFFFFF. If the CRS can guess the number by doing a binary search it will
leak 4 bytes from the magic page.

### Vuln 2
Vulnerability 2 is a fairly straightforward buffer overflow. The difficult part is reaching the code control
that allows a user to exploit the system. The vulnerable function is only ever called after the player has
one both games and tied with the computer 600 times in a row. At this point if a player has chosen option 4
to create a custom 'flair', it's possible to overwrite the buffer and take control of eip and ebp. 3 in a row
is a solved game and has deterministic behavior, but the AI will never lose and will always make optimal moves.
Beating the computer requires an oponent to never make a suboptimal move.

### Generic class of vulnerability
Stack based buffer overflow
Information Exposure

### CWE classification
CWE-121: Stack-based Buffer Overflow
CWE-839: Numeric Range Comparison Without Minimum Check
## Challenges

Vulnerability 1 requires using a bounds check error and then requires winning the game to obtain the leak.
Winning the game requires doing a simple binary search against the game.

Vulnerability 2 allows for a function pointer overwrite the second time a user logs in. This function is called
after a player successfully ties with the AI 100 times. The bug is a reference to a 1983 film.

Vulnerability 2 allows for a buffer overflow once the opponent has beaten the AI several times. Specifically
the player must win games 1 and 2 once and tie at game 3 (3 in a row) 600 times without losing.

Both vulnernerabilities were meant to test the reasoning system of the CRS and were created such that brute force
or fuzzing would not be a viable solution for discovering either of the vulnerabilities.

## Difficulty

Discovering = Easy
Proving = Medium
Patching = Medium
