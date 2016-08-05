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

#include "stdio.h"
#include "string.h"

#include "bitboard.h"

#define PIECE_TO_INDEX(piece) ((piece.type) << 1 | (piece.color))
#define INDEX_TO_PIECE(index) make_piece(index & 1, index >> 1)

static struct piece make_piece(enum color, enum type);
static unsigned long long pawn_moves(struct bitboard *, enum color, int, int);
static unsigned long long rook_moves(struct bitboard *, enum color, int, int);
static unsigned long long knight_moves(struct bitboard *, enum color, int, int);
static unsigned long long bishop_moves(struct bitboard *, enum color, int, int);
static unsigned long long queen_moves(struct bitboard *, enum color, int, int);
static unsigned long long king_moves(struct bitboard *, enum color, int, int);

static unsigned long long (*piece_moves[])(struct bitboard *, enum color, int, int) = {
    pawn_moves,
    rook_moves,
    knight_moves,
    bishop_moves,
    queen_moves,
    king_moves
};

static int is_at_risk(struct bitboard *, enum color, int, int, int);
static int is_checkmate(struct bitboard *, enum color, int, int);
static int is_stalemate(struct bitboard *, enum color);
static int infer_src(struct bitboard *, struct move *);
static int can_castle(struct bitboard *, enum color, enum castle_type);
static int validate_move(struct bitboard *, struct move *);

static struct piece
make_piece(enum color color, enum type type)
{
    struct piece ret = {
        color,
        type 
    };

    return ret;
}

void
init_bitboard(struct bitboard *board)
{
    enum color color;
    unsigned int i;

    memset(board, '\0', sizeof(struct bitboard));
    board->can_castle[WHITE][KINGSIDE] = board->can_castle[BLACK][KINGSIDE] = 1;
    board->can_castle[WHITE][QUEENSIDE] = board->can_castle[BLACK][QUEENSIDE] = 1;
    board->ep_row = board->ep_col = -1;

    for (color = WHITE; color < NUM_COLORS; color++) {
        set_piece(board, 7 * color, 0, make_piece(color, ROOK));
        set_piece(board, 7 * color, 1, make_piece(color, KNIGHT));
        set_piece(board, 7 * color, 2, make_piece(color, BISHOP));
        set_piece(board, 7 * color, 3, make_piece(color, QUEEN));
        set_piece(board, 7 * color, 4, make_piece(color, KING));
        set_piece(board, 7 * color, 5, make_piece(color, BISHOP));
        set_piece(board, 7 * color, 6, make_piece(color, KNIGHT));
        set_piece(board, 7 * color, 7, make_piece(color, ROOK));

        for (i = 0; i < BOARD_SIZE; i++)
            set_piece(board, color ? 6 : 1, i, make_piece(color, PAWN));
    }
}

void
print_bitboard(struct bitboard *board, enum color color)
{
    char *c;
    int i, j, row, col;
    struct piece piece;

#define COLOR(color, square) colors[((square) << 1 | (color))]
    char *colors[] = {
        // White on white
        "\033[1;36;47m",
        // Black on white
        "\033[1;35;47m",
        // White on black
        "\033[1;36;40m",
        // Black on black
        "\033[1;35;40m"
    };

    char *reset = "\033[0m";

#define PIECE(color, type) types[((type) << 1 | (color))]
    char *types[] = {
        // White pawn
        "\xe2\x99\x99\x20",
        // Black pawn
        "\xe2\x99\x9f\x20",
        // White rook
        "\xe2\x99\x96\x20",
        // Black rook
        "\xe2\x99\x9c\x20",
        // White knight
        "\xe2\x99\x98\x20",
        // Black knight
        "\xe2\x99\x9e\x20",
        // White bishop
        "\xe2\x99\x97\x20",
        // Black bishop
        "\xe2\x99\x9d\x20",
        // White queen
        "\xe2\x99\x95\x20",
        // Black queen
        "\xe2\x99\x9b\x20",
        // White king
        "\xe2\x99\x94\x20",
        // Black king
        "\xe2\x99\x9a\x20"
    };

    for (i = 0; i < BOARD_SIZE; i++) {
        row = color == WHITE ? i : BOARD_SIZE - i - 1;
        printf("%d ", BOARD_SIZE - row);

        for (j = 0; j < BOARD_SIZE; j++) {
            col = color == WHITE ? j : BOARD_SIZE - j - 1;

            if (get_piece(board, (BOARD_SIZE - row - 1), col, &piece) == 1)
                printf("%s%s%s", COLOR(piece.color, ((row % 2) + (col % 2)) % 2),
                        PIECE(piece.color, piece.type), reset);
            else
                printf("%s  %s", COLOR(0, ((row % 2) + (col % 2)) % 2), reset);
        }

        printf("\n");
    }

    printf("  ");
    c = "abcdefgh";
    for (c += (color == WHITE ? 0 : 7); *c; c += (color == WHITE ? 1 : -1))
        printf("%c ", *c);
    printf("\n");

#undef COLOR
#undef PIECE
}
    
int
set_piece(struct bitboard *board, int row, int col,
        struct piece piece)
{
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE)
        return -1;

    board->boards[PIECE_TO_INDEX(piece)] |= (1ull << (row * BOARD_SIZE + col));
    return 0;
}

int
clear_piece(struct bitboard *board, int row, int col)
{
    unsigned int i;

    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE)
        return -1;

    for (i = 0; i < sizeof(board->boards) / sizeof(board->boards[0]); i++)
        board->boards[i] &= ~(1ull << (row * BOARD_SIZE + col));

    return 0;
}

int
get_piece(struct bitboard *board, int row, int col,
        struct piece *piece)
{
    unsigned int i;

    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE)
        return -1;

    for (i = 0; i < sizeof(board->boards) / sizeof(board->boards[0]); i++)
        if (board->boards[i] & 1ull << (row * BOARD_SIZE + col)) {
            *piece = INDEX_TO_PIECE(i);
            return 1;
        }

    return 0;
}

static unsigned long long
pawn_moves(struct bitboard *board, enum color color, int row, int col)
{
    unsigned long long ret = 0;
    struct piece piece;

    // Move one forward
    if (get_piece(board, row + (color == WHITE ? 1 : -1), col, &piece) == 0)
        ret |= 1ull << ((row + (color == WHITE ? 1 : -1)) * BOARD_SIZE + col);

    // Move two forward
    if (ret && row == (color == WHITE ? 1 : 6) &&
            get_piece(board, row + (color == WHITE ? 2 : -2), col, &piece) == 0)
        ret |= 1ull << ((row + (color == WHITE ? 2 : -2)) * BOARD_SIZE + col);

    // Capture
    if (get_piece(board, row + (color == WHITE ? 1 : -1), col - 1, &piece) == 1 &&
            piece.color != color)
        ret |= 1ull << ((row + (color == WHITE ? 1 : -1)) * BOARD_SIZE + col - 1);

    if (get_piece(board, row + (color == WHITE ? 1 : -1), col + 1, &piece) == 1 &&
            piece.color != color)
        ret |= 1ull << ((row + (color == WHITE ? 1 : -1)) * BOARD_SIZE + col + 1);

    // En passant
    if (board->ep_row == row + (color == WHITE ? 1 : -1) && board->ep_col == col - 1)
        ret |= 1ull << ((row + (color == WHITE ? 1 : -1)) * BOARD_SIZE + col - 1);

    if (board->ep_row == row + (color == WHITE ? 1 : -1) && board->ep_col == col + 1)
        ret |= 1ull << ((row + (color == WHITE ? 1 : -1)) * BOARD_SIZE + col + 1);

    return ret;
}

static unsigned long long
rook_moves(struct bitboard *board, enum color color, int row, int col)
{
    unsigned int i;
    int j, k, found;
    unsigned long long ret = 0;
    struct piece piece;

    int directions[][2] = {
        { 1, 0 },
        { -1, 0 },
        { 0, 1 },
        { 0, -1 }
    };

    for (i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        j = row + directions[i][0];
        k = col + directions[i][1];

        while ((found = get_piece(board, j, k, &piece)) == 0) {
            ret |= 1ull << (j * BOARD_SIZE + k);
            j += directions[i][0];
            k += directions[i][1];
        }
        if (found == 1 && piece.color != color)
            ret |= 1ull << (j * BOARD_SIZE + k);
    }

    return ret;
}

static unsigned long long
knight_moves(struct bitboard *board, enum color color, int row, int col)
{
    unsigned int i;
    int found;
    unsigned long long ret = 0;
    struct piece piece;

    int moves[][2] = {
        { 2, 1 },
        { 1, 2 },
        { 1, -2},
        { -2, 1 },
        { -2, -1 },
        { -1, -2 },
        { -1, 2 },
        { 2, -1 }
    };

    for (i = 0; i < sizeof(moves) / sizeof(moves[0]); i++) {
        found = get_piece(board, row + moves[i][0], col + moves[i][1], &piece);
        if (found == 0 || (found == 1 && piece.color != color))
            ret |= 1ull << ((row + moves[i][0]) * BOARD_SIZE + col + moves[i][1]);
    }

    return ret;
}

static unsigned long long
bishop_moves(struct bitboard *board, enum color color, int row, int col)
{
    unsigned int i;
    int j, k, found;
    unsigned long long ret = 0;
    struct piece piece;

    int directions[][2] = {
        { 1, 1 },
        { -1, 1 },
        { 1, -1 },
        { -1, -1 }
    };

    for (i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        j = row + directions[i][0];
        k = col + directions[i][1];

        while ((found = get_piece(board, j, k, &piece)) == 0) {
            ret |= 1ull << (j * BOARD_SIZE + k);
            j += directions[i][0];
            k += directions[i][1];
        }
        if (found == 1 && piece.color != color)
            ret |= 1ull << (j * BOARD_SIZE + k);
    }

    return ret;
}

static unsigned long long
queen_moves(struct bitboard *board, enum color color, int row, int col)
{
    return bishop_moves(board, color, row, col) | rook_moves(board, color, row, col);
}

static unsigned long long
king_moves(struct bitboard *board, enum color color, int row, int col)
{
    unsigned int i;
    int found;
    unsigned long long ret = 0;
    struct piece piece;

    int moves[][2] = {
        { 1, 1 },
        { 0, 1 },
        { -1, 1},
        { -1, 0 },
        { -1, -1 },
        { 0, -1 },
        { 1, -1 },
        { 1, 0 }
    };

    for (i = 0; i < sizeof(moves) / sizeof(moves[0]); i++) {
        found = get_piece(board, row + moves[i][0], col + moves[i][1], &piece);
        if (found == 0 || (found == 1 && piece.color != color))
            if (!is_at_risk(board, color, row + moves[i][0], col + moves[i][1], 1) &&
                    row + moves[i][0] >= 0 && row + moves[i][0] < BOARD_SIZE &&
                    col + moves[i][1] >= 0 && col + moves[i][1] < BOARD_SIZE)
                ret |= 1ull << ((row + moves[i][0]) * BOARD_SIZE + col + moves[i][1]);
    }

    return ret;
}

static int
is_at_risk(struct bitboard *board, enum color color, int row, int col, int skip_kings)
{
    unsigned int i;
    unsigned long long b, moves;
    struct piece piece;

    piece.color = color == WHITE ? BLACK : WHITE;
    for (piece.type = PAWN; piece.type < (skip_kings ? KING: NUM_TYPES); piece.type++) {
        b = board->boards[PIECE_TO_INDEX(piece)];
        
        for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            if (b & (1ull << i)) {
                // Special case for pawns
                if (piece.type == PAWN && (i % BOARD_SIZE) == col)
                    continue;

                moves = piece_moves[piece.type](board, piece.color,
                        i / BOARD_SIZE, i % BOARD_SIZE);
                if (moves & (1ull << (row * BOARD_SIZE + col)))
                    return 1;
            }
        }
    }

    return 0;
}

static int
is_checkmate(struct bitboard *board, enum color color, int row, int col)
{
    // BUG: Doesn't check if checkmate can be avoidided by blocking with another
    // friendly piece, shouldn't meaningfully affect CB behavior.
    return is_at_risk(board, color, row, col, 0) == 1 &&
            king_moves(board, color, row, col) == 0;
}

static int
is_stalemate(struct bitboard *board, enum color color)
{
    unsigned int i;
    unsigned long long b, moves = 0;
    struct piece piece;

    if (board->stalemate_ctr >= 2 * STALEMATE_MOVES)
        return 1;

    piece.color = color == WHITE ? BLACK : WHITE;
    for (piece.type = PAWN; piece.type < NUM_TYPES; piece.type++) {
        b = board->boards[PIECE_TO_INDEX(piece)];

        for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            if (b & (1ull << i)) {
                moves |= piece_moves[piece.type](board, piece.color,
                        i / BOARD_SIZE, i % BOARD_SIZE);
            }
        }
    }

    return moves == 0;
}
    
static int
infer_src(struct bitboard *board, struct move *move)
{
    unsigned int i;
    unsigned long long moves, b = board->boards[PIECE_TO_INDEX(move->piece)];

    if (move->dst_row == -1 || move->dst_col == -1)
        return -1;

    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (b & (1ull << i)) {
            moves = piece_moves[move->piece.type](board, move->piece.color,
                    i / BOARD_SIZE, i % BOARD_SIZE);
            if (moves & (1ull << (move->dst_row * BOARD_SIZE + move->dst_col))) {
                if ((move->src_row != -1 && move->src_row != i / BOARD_SIZE) ||
                        (move->src_col != -1 && move->src_col != i % BOARD_SIZE))
                    continue;

                move->src_row = i / BOARD_SIZE;
                move->src_col = i % BOARD_SIZE;
                return 0;
            }
        }
    }

    return -1;
}

static int
can_castle(struct bitboard *board, enum color color, enum castle_type castle_type)
{
    unsigned int i, start_col, end_col;
    int row, king_col, rook_col;
    struct piece piece;

    king_col = 4;
    rook_col = castle_type == KINGSIDE ? 7 : 0;
    row = (color == WHITE ? 0 : 7);

    if (!board->can_castle[color][castle_type])
        return 0;

    if (get_piece(board, row, king_col, &piece) != 1 || piece.type != KING)
        return 0;

    if (get_piece(board, row, rook_col, &piece) != 1 || piece.type != ROOK)
        return 0;

    start_col = MIN(king_col, rook_col) + (castle_type == KINGSIDE ? 1 : 2);
    end_col = MAX(king_col, rook_col);
    for (i = start_col; i < end_col; i++)
        if (get_piece(board, row, i, &piece) != 0 ||
                is_at_risk(board, color, row, i, 0))
            return 0;

    return 1;
}

static int
validate_move(struct bitboard *board, struct move *move)
{
    unsigned long long moves;
    struct piece piece;

    if (move->src_row == -1 || move->src_col == -1 ||
            move->dst_row == -1 || move->dst_col == -1)
        return 0;

    if (get_piece(board, move->src_row, move->src_col, &piece) != 1 ||
            move->piece.color != piece.color || move->piece.type != piece.type)
        return 0;

    if (move->is_promotion && (move->piece.type != PAWN ||
            move->dst_row != (move->piece.color == WHITE ? 7 : 0) ||
            (move->promotion_type > PAWN && move->promotion_type < QUEEN)))
        return 0;

    if ((move->is_check || move->is_checkmate) && move->piece.type == KING)
        return 0;

    if (move->is_castle_kingside || move->is_castle_queenside)
        return can_castle(board, move->piece.color,
                move->is_castle_kingside ? KINGSIDE : QUEENSIDE);

    if (move->is_capture && (get_piece(board, move->dst_row, move->dst_col, &piece) != 1 ||
            piece.color == move->piece.color)) {

        // Check if this is a possible en passant
        if (move->piece.type != PAWN || move->dst_row != board->ep_row ||
                move->dst_col != board->ep_col)
            return 0;
    }

    moves = piece_moves[move->piece.type](board, move->piece.color,
            move->src_row, move->src_col);
    if (moves & (1ull << (move->dst_row * BOARD_SIZE + move->dst_col)))
        return 1;

    return 0;
}

enum result
make_move(struct bitboard *board, struct move *move)
{
    unsigned int i;
    unsigned long long b;
    struct piece piece;

    if (!validate_move(board, move))
        return ERROR;

    if (move->piece.type == PAWN ||
            (get_piece(board, move->dst_row, move->dst_col, &piece) == 1 &&
             piece.color != move->piece.color))
        board->stalemate_ctr = 0;
    else
        board->stalemate_ctr++;

    if (move->is_castle_kingside) {
        clear_piece(board, move->piece.color == WHITE ? 0 : 7, 4);
        clear_piece(board, move->piece.color == WHITE ? 0 : 7, 7);
        set_piece(board, move->piece.color == WHITE ? 0 : 7, 6,
                make_piece(move->piece.color, KING));
        set_piece(board, move->piece.color == WHITE ? 0 : 7, 5,
                make_piece(move->piece.color, ROOK));
        board->can_castle[move->piece.color][KINGSIDE] = 0;
        board->can_castle[move->piece.color][QUEENSIDE] = 0;
    } else if (move->is_castle_queenside) {
        clear_piece(board, move->piece.color == WHITE ? 0 : 7, 4);
        clear_piece(board, move->piece.color == WHITE ? 0 : 7, 0);
        set_piece(board, move->piece.color == WHITE ? 0 : 7, 2,
                make_piece(move->piece.color, KING));
        set_piece(board, move->piece.color == WHITE ? 0 : 7, 3,
                make_piece(move->piece.color, ROOK));
        board->can_castle[move->piece.color][KINGSIDE] = 0;
        board->can_castle[move->piece.color][QUEENSIDE] = 0;
    } else {
        // BUG: If you take the other player's king, call it game over. This
        // shouldn't meaningfully affect CB behavior
        if (get_piece(board, move->dst_row, move->dst_col, &piece) == 1 &&
                piece.color != move->piece.color && piece.type == KING)
            return CHECKMATE;

        clear_piece(board, move->src_row, move->src_col);
        clear_piece(board, move->dst_row, move->dst_col);
        if (move->is_promotion)
            set_piece(board, move->dst_row, move->dst_col,
                    make_piece(move->piece.color, move->promotion_type));
        else
            set_piece(board, move->dst_row, move->dst_col, move->piece);

        if (move->piece.type == KING) {
            board->can_castle[move->piece.color][KINGSIDE] = 0;
            board->can_castle[move->piece.color][QUEENSIDE] = 0;
        }

        if (move->piece.type == ROOK) {
            if (move->src_row == (move->piece.color == WHITE ? 0 : 7) && move->src_col == 7)
                board->can_castle[move->piece.color][KINGSIDE] = 0;
            else if (move->src_row == (move->piece.color == WHITE ? 0 : 7) && move->src_col == 0)
                board->can_castle[move->piece.color][QUEENSIDE] = 0;
        }

        if (move->piece.type == PAWN &&
                move->dst_row == board->ep_row && move->dst_col == board->ep_col) {
            if (move->dst_row > move->src_row &&
                    get_piece(board, move->dst_row - 1, move->dst_col, &piece) == 1 &&
                    piece.type == PAWN && piece.color != move->piece.color)
                clear_piece(board, move->dst_row - 1, move->dst_col);
            else if (move->src_row > move->dst_row &&
                    get_piece(board, move->dst_row + 1, move->dst_col, &piece) == 1 &&
                    piece.type == PAWN && piece.color != move->piece.color)
                clear_piece(board, move->dst_row + 1, move->dst_col);
        }

        if (move->piece.type == PAWN && (move->dst_row - move->src_row == 2 ||
                    move->dst_row - move->src_row == -2)) {
            board->ep_row = (move->dst_row + move->src_row) / 2;
            board->ep_col = move->dst_col;
        } else {
            board->ep_row = board->ep_col = -1;
        }
    }

    if (is_stalemate(board, move->piece.color))
        return STALEMATE;

    piece = make_piece(move->piece.color == WHITE ? BLACK : WHITE, KING);
    b = board->boards[PIECE_TO_INDEX(piece)];
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        if (b & (1ull << i))
            break;

    if (is_at_risk(board, piece.color, i / BOARD_SIZE, i % BOARD_SIZE, 0) == 1) {
        if (is_checkmate(board, piece.color, i / BOARD_SIZE, i % BOARD_SIZE))
            return CHECKMATE;
        else
            return CHECK;
    }

    return CONTINUE;
}

int
parse_san(struct bitboard *board, enum color color, char *san, struct move *move)
{
    char c;
    int processed_capture = 0;

    enum {
        PIECE,
        COL,
        ROW,
        CAPTURE,
        PROMOTION,
        CHECK,
        CHECKMATE,
        DONE
    } state = PIECE;

    memset(move, '\0', sizeof(struct move));
    move->piece.color = color;
    move->src_row = move->src_col = -1;
    move->dst_row = move->dst_col = -1;

    // Castle kingside
    if (strcmp(san, "O-O") == 0) {
        move->piece.type = KING;
        move->is_castle_kingside = 1;
        move->src_row = color ? 7 : 0;
        move->dst_row = move->src_row;
        move->src_col = 4;
        move->dst_col = 6;

        return 0;
    }

    if (strcmp(san, "O-O-O") == 0) {
        move->piece.type = KING;
        move->is_castle_queenside = 1;
        move->src_row = color ? 7 : 0;
        move->dst_row = move->src_row;
        move->src_col = 4;
        move->dst_col = 2;

        return 0;
    }

    while ((c = *san) && state != DONE) {
        switch (state) {
        case PIECE:
            switch (c) {
            case 'R':
                move->piece.type = ROOK;
                break;
            case 'N':
                move->piece.type = KNIGHT;
                break;
            case 'B':
                move->piece.type = BISHOP;
                break;
            case 'Q':
                move->piece.type = QUEEN;
                break;
            case 'K':
                move->piece.type = KING;
                break;
            case 'P':
                move->piece.type = PAWN;
                break;
            case 'a' ... 'h':
                move->piece.type = PAWN;
                move->dst_col = c - 'a';
                break;
            default:
                return -1;
            }

            state = move->dst_col == -1 ? COL : ROW;
            san++;
            break;
        case COL:
            if (c >= 'a' && c <= 'h') {
                move->src_col = move->dst_col;
                move->dst_col = c - 'a';
                state = ROW;
                san++;
            } else {
                state = processed_capture ? PROMOTION : CAPTURE;
            }
            break;
        case ROW:
            if (c >= '1' && c <= '8') {
                move->src_row = move->dst_row;
                move->dst_row = c - '1';
                san++;
            } else if (c >= 'a' && c <= 'h') {
                state = COL;
                continue;
            }
            state = processed_capture ? PROMOTION : CAPTURE;
            break;
        case CAPTURE:
            if (c == 'x') {
                move->is_capture = 1;
                san++;
            }
            processed_capture = 1;
            state = COL;
            break;
        case PROMOTION:
            if (c == '=' && move->piece.type == PAWN) {
                move->is_promotion = 1;
                move->promotion_type = QUEEN;
            } else if (move->is_promotion) {
                state = CHECK;

                switch (c) {
                case 'R':
                    move->promotion_type = ROOK;
                    break;
                case 'N':
                    move->promotion_type = KNIGHT;
                    break;
                case 'B':
                    move->promotion_type = BISHOP;
                    break;
                case 'Q':
                    move->promotion_type = QUEEN;
                    break;
                default:
                    continue;
                }
            } else {
                state = CHECK;
            }
            san++;
            break;
        case CHECK:
            if (c == '+')
                move->is_check = 1;

            state = move->is_check ? DONE : CHECKMATE;
            break;
        case CHECKMATE:
            if (c == '#')
                move->is_checkmate = 1;

            state = DONE;
            break;
        case DONE:
        default:
            // Should never get here
            return -1;
        }
    }

    if (move->dst_row == -1 || move->dst_col == -1)
        return -1;

    if (move->src_row == -1 || move->dst_col == -1)
        if (infer_src(board, move) != 0)
            return -1;

    return 0;
}
