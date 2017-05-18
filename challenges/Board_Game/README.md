# CROMU-00031 Board Game

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This is a service that mimics a chess board and pieces. Each piece on the board moves similarly to its respective chess piece. Unlike chess, however, collisions on the board result in a swap of location rather than the opponent's piece being removed from the board. The user must find the combination of valid moves that will prove the vulnerability.

### Feature List

The game opens by printing the state of the board:

        jhilkihj
        gggggggg
        ........
        ........
        ........
        ........
        aaaaaaaa
        dbcfecbd

The user must take turns entering moves as both the white and black player. Each move must follow the chess piece's valid move: pawn, rook, knight, bishop, king, and queen.

The user may print the current board layout, make a move, or quit the game.

The game accepts input in the form of source coordinates and destionation coordinates x,y x,y

If a piece is located at the source coordinates the game will attempt to move it to the destination. It will check to see if the move is a valid one for that particular piece (following standard chess rules) and to make sure the path is clear from source to destination. If an opponent's piece is located at the destionation and it is an otherwise legal move, the game will swap the pieces.

Play continues until the user exits the game (or the vulnerable condition is achieved).

## Vulnerability
There is a one-byte overflow in the buffer used to read in the player's next move.  It overflows into the string which is used to determine the valid input characters for a given board x,y coordinate.  Under normal circumstances, the only valid characters are 0-7 since the board is 8x8.  However, with the one byte overflow, the CRS can change the allowed input characters.  

The coordinate digit is calculated using an offset from '0'.  So, with a different allowed character set, the coordinate digit's value can be set to an 8-bit value allowing a chess piece to be moved off of the board.  However, the game rules for piece moves still apply.  The destination coordinate must be empty or must not contain a character which represents the current player's pieces.  Also, the path between the source and destination coordinates must be clear (must be all '\0' as that character is used to represent an empty space in the game board array).  

Given the board array's close proximity to the return address of main() and the excess of '\0' values between the board array and that address, the CRS can overwrite that return address with any game piece character value.  Then, by choosing to end the game, control is transferred to that address.

### Generic class of vulnerability
Out-of-bounds write resulting in improper input validation

### CWE classification
CWE-787 Out-of-bounds write

## Challenges
Overwriting the first byte of the input validation string must be carefully coordinated with the use of that new valid character as an x,y coordinate.  And, the piece which is being moved, must make valid chess moves over a field which is free of other 'pieces'.  Otherwise, the move is simply rejected.  Only then can the CRS successfully overwrite some useful value in the program.  Given the size of the board, limitations on the valid moves and complexity of the memory layout, identifying a successful pattern of piece moves will be difficult.
