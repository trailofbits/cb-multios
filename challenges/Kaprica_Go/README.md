# KPRCA-00039

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service provides the user with a way to play a game against a simple AI.
The user begins by entering their name and the game begins.  The user then
inputs coordinates on a game board and if their move is valid a stone of their
team color is placed on the board. The AI then performs a move and the game
continues like this until one player runs out of stones of a maximum number of
moves has occurred.

### Feature List

The user is presented with a visual printout of the state of the game as the
game progresses which include board state, team scores, and how many game ticks
have occurred. If the user attempts an invalid move the game is not drawn but
instead they are simply prompted for a new move. The rules of the game are
quite simple. An user can only place a stone on an empty point on the board.
A stone is captured if it can not be connected to a stone of its same color.
Score is a combination of captures and stones on the board. When the game
terminates the user is notified whether they were a winner or a loser.

## Vulnerability

The vulnerability is a simple printf vulnerability, however for the
vulnerability to be triggered the game must reach the end. At that point, the
name the user supplied is passed directly to printf as the format string.

### Generic class of vulnerability
Arbitrary format string

### CWE classification
CWE-134: Uncontrolled Format Sting

## Challenges

The service acts primary to test the strength of the competitor's ability to
reason through fairly complex logic quickly. The competitor must be able to
generate enough valid moves against an AI to successful finish the game in
a reasonable amount of time to be successful against this service.
