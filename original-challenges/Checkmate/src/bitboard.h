/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

/** Dimensions of the board, board is a 2d square */
#define BOARD_SIZE (8)
/** Number of moves without capture or pawn movement to call a stalemate */
#define STALEMATE_MOVES (50)

/** The result of one move */
enum result {
    /** Error making move */
    ERROR = -1,
    /** Normal result, continue game */
    CONTINUE = 0,
    /** Opponent is in check */
    CHECK = 1,
    /** Opponent is in checkmate */
    CHECKMATE = 2,
    /** Game is a stalemate */
    STALEMATE = 3
};

/** Color associated with the game's players */
enum color {
    /** White player */
    WHITE,
    /** Black player */
    BLACK,
    /** Used in size computations */
    NUM_COLORS
};

/** Types of pieces */
enum type {
    /** Pawn piece */
    PAWN,
    /** Rook piece */
    ROOK,
    /** Knight piece */
    KNIGHT,
    /** Bishop piece */
    BISHOP,
    /** Queen piece */
    QUEEN,
    /** King piece */
    KING,
    /** Used in size computations */
    NUM_TYPES
};

/** Types of castling moves */
enum castle_type {
    /** Kingside castle */
    KINGSIDE,
    /** Queenside castle */
    QUEENSIDE,
    /** Used in size computations */
    NUM_CASTLE_TYPE
};

/** Represents one piece on the board */
struct piece {
    /** Which player owns the piece */
    enum color color;
    /** The type of the piece */
    enum type type;
};

/** Contains the state of the board */
struct bitboard {
    /** Contains all of the pieces on the board, packed into bitsets */
    unsigned long long boards[NUM_COLORS * NUM_TYPES];
    /** What castling moves are still valid */
    int can_castle[NUM_COLORS][NUM_CASTLE_TYPE];
    /** Can an en passant capture move be made */
    int ep_row, ep_col;
    /** How many moves until stalemate declared */
    unsigned int stalemate_ctr;
};

/** Represents one move */
struct move {
    /** The piece to move */
    struct piece piece;
    /** What piece to promote a pawn to */
    enum type promotion_type;
    /** Is this move a castle */
    int is_castle_kingside, is_castle_queenside;
    /** Is this move a capture */
    int is_capture;
    /** Is this move a pawn promotion */
    int is_promotion;
    /** Is this move check or checkmate */
    int is_check, is_checkmate;
    /** The source coordinates of the piece */
    int src_row, src_col;
    /** The destination coordinates of the piece */
    int dst_row, dst_col;
};

/**
 * Initialize a board to its starting state.
 *
 * @param board The board to initialize
 */
void init_bitboard(struct bitboard *board);

/**
 * Print a board as viewed by one of the players.
 *
 * @param board The board to print
 * @param color The player from who's perspective to print the board
 */
void print_bitboard(struct bitboard *board, enum color color);

/**
 * Set a square on the board to contain a certain piece.
 *
 * @param board The board to modify
 * @param row The row on the board to set
 * @param col The column on the board to set
 * @param piece The piece to set
 * @return 0 on success, -1 on failure
 */
int set_piece(struct bitboard *board, int row, int col,
        struct piece piece);

/**
 * Clear a piece from the board.
 *
 * @param board The board to modify
 * @param row The row on the board to clear
 * @param column The column on the board to clear
 * @return 0 on success, -1 on failure
 */
int clear_piece(struct bitboard *board, int row, int col);

/**
 * Get a piece from the board.
 *
 * @param board The board to examine
 * @param row The row on the board to examine
 * @param col The column on the board to examine
 * @param piece Pointer to place the result in
 * @return 0 if empty, 1 if piece found, -1 on failure
 */
int get_piece(struct bitboard *board, int row, int col,
        struct piece *piece);

/**
 * Apply a move to a board.
 *
 * @param board The board to modify
 * @param move The move to make
 * @return Result of the move
 */
enum result make_move(struct bitboard *board, struct move *move);

/**
 * Parse a move written in standard algebraic notation.
 *
 * @param board The board the move is being made on
 * @param color The player making the move
 * @param san The move in standard algebraic notation
 * @param move Pointer to place the result in
 * @return 0 on success, -1 on failure
 */
int parse_san(struct bitboard *board, enum color color, char *san,
        struct move *move);

#endif /* BITBOARD_H_ */

