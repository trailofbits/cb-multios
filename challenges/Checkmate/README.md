# Checkmate

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
A simple chess game featuring a state-of-the-art text interface and local
multiplayer support, enabling players to make moves using human-readable
standard algebraic notation to play a game of chess.

### Feature List
This service will allow two players to play a game of chess

- Displays game state based on current player
- Parses input in standard algebraic notation
- Handles move validation
- Tracks captures
- Tracks check, checkmate, stalemate
- Handles castling
- Handles pawn promotion
- Handles en passant
- Future support for AI players planned

## Vulnerability 1
This service leaks data from the flag page. The stub "AI" code initializes a
structure on the stack with 4 bytes from the flag page as a sort of random seed.
As players input moves, they are validated with a parser and against the current
game state, but overlong moves are not thrown out once parsing has completed.
Upon successful validataion of the move, the move is printed out to the user
prior to displaying the updated board state. This print statement uses a
user-controllable format string to perform this operation. A user who is able to
craft a format string which passes the parser and subsequent move validation can
leak bytes from the stack, leading to the disclosure of the flag value.

### Generic class of vulnerability
Improper input validation
Uncontrolled format string
Information exposure through sent data

### CWE classification
CWE-20 Improper input validation
CWE-134 Uncontrolled format string
CWE-201 Information exposure through sent data

### Challenges
- The vulnerability can be discovered by a CRS which performs taint tracking and
  is able to identify and reason about unsafe functions such as printf. This is
  made slightly more difficult by this CB by passing in the string read from
  user input into a complicated parsing and validation function which mixes the
  value with components of game state, however the tainted value itself is
  passed directly to printf in the unpatched version.
- Proving the vulnerability requires the ability to craft an input string which
  contains format specifiers and also represents a valid move to both the parser
  and to the move validator which considers the current state of the game.
  Modeling the behavior of variable argument functions such as printf is
  required, as is taint tracking from the flag page, to identify the presence of
  tainted bytes left on the stack and the potential to leak them with a crafted
  format string.
- Fixing the vulnerability is easy, if it can be identified. A transformation to
  convert printfs with user-controlled format strings to one without should be
  possible.

### Difficulty
- Discovering is medium
- Proving is medium
- Fixing is easy

