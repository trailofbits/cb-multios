/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "engine.h"
#include "io.h"

#define BIT(r, c) (1ULL << ((r) * 8 + (c)))
#define BIT_IF_VALID(r, c) ((r >= 0 && r <= 7 && c >= 0 && c <= 7) ? BIT(r, c) : 0)
#define DRAW_THRESHOLD -200 /* accept a draw if we are clearly losing */
#define MAX_MOVES_PER_DEPTH 256
#define MAX_DEPTH 8
#define SCORE_MIN -10000000
#define SCORE_MAX  10000000

const int INITIAL_MAX_DEPTH = 3;
const bboard_t INITIAL_WHITE_PAWNS = 0x000000000000FF00ULL;
const bboard_t INITIAL_WHITE_ROOKS = 0x0000000000000081ULL;
const bboard_t INITIAL_WHITE_KNIGHTS = 0x0000000000000042ULL;
const bboard_t INITIAL_WHITE_BISHOPS = 0x0000000000000024ULL;
const bboard_t INITIAL_WHITE_QUEENS = 0x0000000000000008ULL;
const bboard_t INITIAL_WHITE_KINGS = 0x0000000000000010ULL;
const bboard_t INITIAL_BLACK_PAWNS = 0x00FF000000000000ULL;
const bboard_t INITIAL_BLACK_ROOKS = 0x8100000000000000ULL;
const bboard_t INITIAL_BLACK_KNIGHTS = 0x4200000000000000ULL;
const bboard_t INITIAL_BLACK_BISHOPS = 0x2400000000000000ULL;
const bboard_t INITIAL_BLACK_QUEENS = 0x0800000000000000ULL;
const bboard_t INITIAL_BLACK_KINGS = 0x1000000000000000ULL;
bboard_t KING_MOVES[64];
bboard_t KNIGHT_MOVES[64];
bboard_t BISHOP_MOVES[64];
const int PIECE_SCORES[NUM_PIECES] = {
    [PAWN] = 100,
    [KNIGHT] = 300,
    [BISHOP] = 300,
    [ROOK] = 500,
    [QUEEN] = 900,
    [KING] = 999999
};

typedef struct {
    /* game state */
    int active;
    int scores[2];
    int current_color;
    int go;
    int max_depth;
    int random;
    move_t last_move;
    uint8_t num_moves[64]; /* number of moves from a position, used for castling */
    move_t moves[64];
    move_t *moves_buf;
    int accept_draw;
    int current_move;

    /* board representations */
    uint8_t mailbox[64];
    bboard_t all_pieces;
    bboard_t color_pieces[2];
    bboard_t pieces[NUM_PIECES][2];
} engine_t;
static engine_t *engine;

#ifdef DEBUG
static char piece_to_char(uint8_t p)
{
    int color = PIECE_COLOR(p) * 0x20;
    switch (p & PIECE_MASK)
    {
    case PAWN:
        return 'p' ^ color;
    case KNIGHT:
        return 'k' ^ color;
    case BISHOP:
        return 'b' ^ color;
    case ROOK:
        return 'r' ^ color;
    case QUEEN:
        return 'q' ^ color;
    case KING:
        return 'x' ^ color;
    }
    return ' ';
}

static void print_board()
{
    int r, c;
    fprintf(stderr, "  abcdefgh\n");
    for (r = 7; r >= 0; r--)
    {
        fprintf(stderr, "%d ", r + 1);
        for (c = 0; c < 8; c++)
        {
            fprintf(stderr, "%c", piece_to_char(engine->mailbox[r * 8 + c]));
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "  abcdefgh\n");
}

static void print_bboard(bboard_t b)
{
    int r, c;
    fprintf(stderr, "  abcdefgh\n");
    for (r = 7; r >= 0; r--)
    {
        fprintf(stderr, "%d ", r + 1);
        for (c = 0; c < 8; c++)
        {
            fprintf(stderr, "%c", b & BIT(r, c) ? 'x' : ' ');
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "  abcdefgh\n");
}

static void sanity_check_board()
{
    int r, c, bad = 0;

    for (r = 0; r < 8; r++)
    for (c = 0; c < 8; c++)
    {
        uint8_t p;
        for (p = 0; p < NUM_PIECES; p++)
        {
            if (engine->pieces[p][WHITE] & BIT(r, c))
            {
                if (engine->mailbox[r * 8 + c] != (p | (WHITE << COLOR_SHIFT)))
                    bad |= 1 << 0;
                if (!(engine->all_pieces & BIT(r, c)))
                    bad |= 1 << 1;
                if (!(engine->color_pieces[WHITE] & BIT(r, c)))
                    bad |= 1 << 2;
            }
            if (engine->pieces[p][BLACK] & BIT(r, c))
            {
                if (engine->mailbox[r * 8 + c] != (p | (BLACK << COLOR_SHIFT)))
                    bad |= 1 << 3;
                if (!(engine->all_pieces & BIT(r, c)))
                    bad |= 1 << 4;
                if (!(engine->color_pieces[BLACK] & BIT(r, c)))
                    bad |= 1 << 5;
            }
        }

        if (engine->mailbox[r * 8 + c] == EMPTY)
        {
            if (engine->all_pieces & BIT(r, c))
                bad |= 1 << 6;
            if (engine->color_pieces[WHITE] & BIT(r, c))
                bad |= 1 << 7;
            if (engine->color_pieces[BLACK] & BIT(r, c))
                bad |= 1 << 8;
        }
    }

    if (bad)
    {
        fprintf(stderr, "SANITY BAD (%08X)!\n", bad);
        fprintf(stderr, "%016llx\n", engine->color_pieces[WHITE]);
        print_bboard(engine->color_pieces[WHITE]);
        fprintf(stderr, "%016llx\n", engine->color_pieces[BLACK]);
        print_bboard(engine->color_pieces[BLACK]);
        fprintf(stderr, "%016llx\n", engine->all_pieces);
        print_bboard(engine->all_pieces);
    }
}
#endif

void engine_destroy()
{
    if (engine)
    {
        free(engine->moves_buf);
        free(engine);
        engine = NULL;
    }
}

int engine_init()
{
    int r, c;

    engine = malloc(sizeof(engine_t));
    if (engine == NULL)
        return 0;
    memset(engine, 0, sizeof(engine_t));
    memset(engine->mailbox, EMPTY, 64);

    for (r = 0; r < 8; r++)
    for (c = 0; c < 8; c++)
    {
        bboard_t moves = 0;
        
        moves |= BIT_IF_VALID(r-2, c-1);
        moves |= BIT_IF_VALID(r-1, c-2);
        moves |= BIT_IF_VALID(r-2, c+1);
        moves |= BIT_IF_VALID(r-1, c+2);
        moves |= BIT_IF_VALID(r+2, c-1);
        moves |= BIT_IF_VALID(r+1, c-2);
        moves |= BIT_IF_VALID(r+2, c+1);
        moves |= BIT_IF_VALID(r+1, c+2);

        KNIGHT_MOVES[r * 8 + c] = moves;

        moves = 0;
        moves |= BIT_IF_VALID(r-1, c-1);
        moves |= BIT_IF_VALID(r-1, c);
        moves |= BIT_IF_VALID(r-1, c+1);
        moves |= BIT_IF_VALID(r, c-1);
        moves |= BIT_IF_VALID(r, c+1);
        moves |= BIT_IF_VALID(r+1, c-1);
        moves |= BIT_IF_VALID(r+1, c);
        moves |= BIT_IF_VALID(r+1, c+1);

        KING_MOVES[r * 8 + c] = moves;
    }

    for (r = 0; r < 8; r++)
    for (c = 0; c < 8; c++)
    {
        int i;
        bboard_t moves = 0;
        
        for (i = 0; i < 8; i++)
        {
            moves |= BIT_IF_VALID(r-i, c-i);
            moves |= BIT_IF_VALID(r+i, c+i);
        }

        BISHOP_MOVES[r * 8 + c] = moves;
    }

    engine->moves_buf = malloc(MAX_DEPTH * MAX_MOVES_PER_DEPTH * sizeof(move_t));
    if (engine->moves_buf == NULL)
    {
        free(engine);
        return 0;
    }

    return 1;
}

void engine_new()
{
    uint8_t r, c;
    engine->current_color = WHITE;
    engine->max_depth = INITIAL_MAX_DEPTH;
    engine->go = 1;
    engine->random = 0;
    engine->active = 1;

    engine->pieces[PAWN][WHITE] = INITIAL_WHITE_PAWNS;
    engine->pieces[KNIGHT][WHITE] = INITIAL_WHITE_KNIGHTS;
    engine->pieces[BISHOP][WHITE] = INITIAL_WHITE_BISHOPS;
    engine->pieces[ROOK][WHITE] = INITIAL_WHITE_ROOKS;
    engine->pieces[QUEEN][WHITE] = INITIAL_WHITE_QUEENS;
    engine->pieces[KING][WHITE] = INITIAL_WHITE_KINGS;

    engine->pieces[PAWN][BLACK] = INITIAL_BLACK_PAWNS;
    engine->pieces[KNIGHT][BLACK] = INITIAL_BLACK_KNIGHTS;
    engine->pieces[BISHOP][BLACK] = INITIAL_BLACK_BISHOPS;
    engine->pieces[ROOK][BLACK] = INITIAL_BLACK_ROOKS;
    engine->pieces[QUEEN][BLACK] = INITIAL_BLACK_QUEENS;
    engine->pieces[KING][BLACK] = INITIAL_BLACK_KINGS;

    engine->color_pieces[WHITE] = 0x000000000000FFFFULL;
    engine->color_pieces[BLACK] = 0xFFFF000000000000ULL;
    engine->all_pieces = 0xFFFF00000000FFFFULL;

    /* setup mailbox representation */
    engine->scores[WHITE] = 0;
    engine->scores[BLACK] = 0;
    memset(engine->mailbox, EMPTY, 64);
    for (r = 0; r < 8; r++)
    for (c = 0; c < 8; c++)
    {
        uint8_t p;
        for (p = 0; p < NUM_PIECES; p++)
        {
            if (engine->pieces[p][WHITE] & BIT(r, c))
            {
                engine->mailbox[r * 8 + c] = p | (WHITE << COLOR_SHIFT);
                engine->scores[WHITE] += PIECE_SCORES[p];
                break;
            }
            if (engine->pieces[p][BLACK] & BIT(r, c))
            {
                engine->mailbox[r * 8 + c] = p | (BLACK << COLOR_SHIFT);
                engine->scores[BLACK] += PIECE_SCORES[p];
                break;
            }
        }
    }

    engine->last_move.op = EMPTY;
    memset(engine->num_moves, 0, 64);
    engine->current_move = 0;
    engine->accept_draw = 0;
}

static inline bboard_t test_file(uint8_t column, uint8_t min_y, uint8_t abs_dy)
{
    return (0x0101010101010100ULL << (column + 8 * (8 - abs_dy))) >> (8 * (8 - abs_dy - min_y));
}

static inline bboard_t test_rank(uint8_t row, uint8_t min_x, uint8_t abs_dx)
{
    return (bboard_t)(0x7F >> (8 - abs_dx)) << (min_x + 1 + 8 * row);
}

/* return squares that color is attacking */
static bboard_t calculate_attacks(int color)
{
    int i, p;
    bboard_t b, result = 0;

    /* pawns */
    if (color == WHITE)
    {
        result |= (engine->pieces[PAWN][WHITE] & 0x7f7f7f7f7f7f7f7fULL) << 9;
        result |= (engine->pieces[PAWN][WHITE] & 0xfefefefefefefefeULL) << 7;
    }
    else
    {
        result |= (engine->pieces[PAWN][BLACK] & 0x7f7f7f7f7f7f7f7fULL) >> 7;
        result |= (engine->pieces[PAWN][BLACK] & 0xfefefefefefefefeULL) >> 9;
    }

    /* knights */
    for (p = -1, b = engine->pieces[KNIGHT][color]; b != 0 && p < 63; b >>= i + 1)
    {
        i = __builtin_ctzll(b);
        p += i + 1;
        result |= KNIGHT_MOVES[p];
    }

    /* rooks / queens */
    for (p = -1, b = engine->pieces[ROOK][color] | engine->pieces[QUEEN][color]; b != 0 && p < 63; b >>= i + 1)
    {
        bboard_t bit;
        int r, c, j;

        i = __builtin_ctzll(b);
        p += i + 1;

        r = p / 8;
        c = p % 8;

        for (j = c+1, bit = 1ULL << (r * 8 + c + 1); j < 8; j++, bit <<= 1)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }
        for (j = c-1, bit = 1ULL << (r * 8 + c - 1); j >= 0; j--, bit >>= 1)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }
        for (j = r+1, bit = 1ULL << ((r+1) * 8 + c); j < 8; j++, bit <<= 8)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }
        for (j = r-1, bit = 1ULL << ((r-1) * 8 + c); j >= 0; j--, bit >>= 8)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }
    }

    /* bishops / queens */
    for (p = -1, b = engine->pieces[BISHOP][color] | engine->pieces[QUEEN][color]; b != 0 && p < 63; b >>= i + 1)
    {
        bboard_t bit;
        int r, c;

        i = __builtin_ctzll(b);
        p += i + 1;

        r = p / 8 + 1;
        c = p % 8 + 1;
        for (bit = 1ULL << (r * 8 + c); r < 8 && c < 8; r++, c++, bit <<= 9)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }

        r = p / 8 - 1;
        c = p % 8 + 1;
        for (bit = 1ULL << (r * 8 + c); r >= 0 && c < 8; r--, c++, bit >>= 7)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }

        r = p / 8 + 1;
        c = p % 8 - 1;
        for (bit = 1ULL << (r * 8 + c); r < 8 && c >= 0; r++, c--, bit <<= 7)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }

        r = p / 8 - 1;
        c = p % 8 - 1;
        for (bit = 1ULL << (r * 8 + c); r >= 0 && c >= 0; r--, c--, bit >>= 9)
        {
            result |= bit;
            if (engine->all_pieces & bit)
                break;
        }
    }

    /* king */
    result |= KING_MOVES[__builtin_ctzll(engine->pieces[KING][color])];

    return result;
}

static int valid_move(move_t move, piece_t piece)
{
    unsigned int abs_dy = ABS(move.dr - move.sr),
        abs_dx = ABS(move.dc - move.sc),
        neg_dy = NEG(move.dr - move.sr),
        neg_dx = NEG(move.dc - move.sc),
        min_y = MIN(move.sr, move.dr),
        min_x = MIN(move.sc, move.dc),
        color = PIECE_COLOR(piece);
    /* NULL moves are invalid */
    if (abs_dx == 0 && abs_dy == 0)
        return 0;
    /* capturing own piece is invalid */
    if (engine->color_pieces[color] & BIT(move.dr, move.dc))
        return 0;
    /* can only move your own piece */
    if (PIECE_COLOR(piece) != engine->current_color)
        return 0;
    /* piece-specific rules */
    switch (piece & PIECE_MASK)
    {
    case PAWN:
        /* prevent pawn from moving backwards */
        if (color == WHITE && neg_dy)
            return 0;
        if (color == BLACK && !neg_dy)
            return 0;
        /* pawn moving forward one space */
        if (abs_dx == 0 && abs_dy == 1)
            return !(engine->all_pieces & BIT(move.dr, move.dc));
        /* pawn moving forward two space */
        if (abs_dx == 0 && abs_dy == 2)
        {
            if (color == WHITE && move.sr == 1)
                return !(engine->all_pieces & (BIT(move.sr + 1, move.sc) | BIT(move.sr + 2, move.sc)));
            if (color == BLACK && move.sr == 6)
                return !(engine->all_pieces & (BIT(move.sr - 1, move.sc) | BIT(move.sr - 2, move.sc)));
            return 0;
        }
        /* pawn capturing */
        if (abs_dx == 1 && abs_dy == 1)
        {
            /* en passant capture */
#ifdef ENPASSANT
            if ((engine->last_move.op & PIECE_MASK) == PAWN && /* last move piece was a pawn */
                ABS(engine->last_move.sr - engine->last_move.dr) == 2 && /* and it moved forward two */
                engine->last_move.sc == move.dc)
            {
                return (!color == WHITE && engine->last_move.sr + 1 == move.dr) || (!color == BLACK && engine->last_move.sr - 1 == move.dr);
            }
#endif
            /* make sure it is capturing a piece */
            return !!(engine->all_pieces & BIT(move.dr, move.dc));
        }
        return 0;
    case KNIGHT:
        return (abs_dx == 1 && abs_dy == 2) || (abs_dx == 2 && abs_dy == 1);
    case BISHOP:
        if (abs_dx != abs_dy)
            return 0;
        if (neg_dx == neg_dy)
        {
            bboard_t mask = (0x0040201008040201ULL >> ((8 - abs_dy) * 8)) << ((1 + min_y) * 8 - (7 - (abs_dx + min_x)));
            if (engine->all_pieces & mask)
                return 0;
            else
                return 1;
        }
        else
        {
            bboard_t mask = (0x0002040810204080ULL >> ((8 - abs_dy) * 8)) << ((1 + min_y) * 8 + min_x);
            if (engine->all_pieces & mask)
                return 0;
            else
                return 1;
        }
        return 0;
    case ROOK:
        if (abs_dx == 0)
        {
            /* ensure file between sr and dr is empty */
            //if (min_y == move.dr)
            //    min_y++;
            if (engine->all_pieces & test_file(move.sc, min_y, abs_dy))
                return 0;
            else
                return 1;
        }
        else if (abs_dy == 0)
        {
            /* ensure rank between sc and dc is empty */
            //if (min_x == move.dc)
            //    min_x++;
            if (engine->all_pieces & test_rank(move.sr, min_x, abs_dx))
                return 0;
            else
                return 1;
        }
        else
            return 0;
    case QUEEN:
        if (abs_dx == 0)
        {
            /* ensure file between sr and dr is empty */
            if (engine->all_pieces & test_file(move.sc, min_y, abs_dy))
                return 0;
            else
                return 1;
        }
        else if (abs_dy == 0)
        {
            /* ensure rank between sc and dc is empty */
            if (engine->all_pieces & test_rank(move.sr, min_x, abs_dx))
                return 0;
            else
                return 1;
        }
        else if (abs_dy == abs_dx)
        {
            if (neg_dx == neg_dy)
            {
                bboard_t mask = (0x0040201008040201ULL >> ((8 - abs_dy) * 8)) << ((1 + min_y) * 8 - (7 - (abs_dx + min_x)));
                if (engine->all_pieces & mask)
                    return 0;
                else
                    return 1;
            }
            else
            {
                bboard_t mask = (0x0002040810204080ULL >> ((8 - abs_dy) * 8)) << ((1 + min_y) * 8 + min_x);
                if (engine->all_pieces & mask)
                    return 0;
                else
                    return 1;
            }
        }
        else
            return 0;
    case KING:
        /* normal move */
        if (abs_dx <= 1 && abs_dy <= 1)
            return 1;
        /* castling */
        if (abs_dx == 2 && abs_dy == 0 && move.sc == 4 && ((color == WHITE && move.sr == 0) || (color == BLACK && move.sr == 7)))
        {
            bboard_t attacks;
            int rook;
            /* check if under attack */
            attacks = calculate_attacks(!color);
            /* no pieces between rook and king */
            if (move.dc == 2)
            {
                if (attacks & (BIT(move.sr, 1) | BIT(move.sr, 2)))
                    return 0;
                if (engine->all_pieces & (BIT(move.sr, 1) | BIT(move.sr, 2) | BIT(move.sr, 3)))
                    return 0;
                rook = 0;
            }
            else /* if (move.dc == 6) */
            {
                if (attacks & (BIT(move.sr, 5) | BIT(move.sr, 6)))
                    return 0;
                if (engine->all_pieces & (BIT(move.sr, 5) | BIT(move.sr, 6)))
                    return 0;
                rook = 7;
            }

            /* neither rook nor king have already moved */
            if (engine->num_moves[move.sr * 8 + move.sc] != 0 || engine->num_moves[move.sr * 8 + rook] != 0)
                return 0;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

/* check outcome of apply_move:
 *  - !current_color is not in check
 */
static int valid_board()
{
    bboard_t attacks;
    int prev_color = !engine->current_color;

    /* check if in check */
    attacks = calculate_attacks(engine->current_color);
    if (attacks & engine->pieces[KING][prev_color])
        return 0;
    
    return 1;
}

static void apply_move(move_t move, piece_t piece)
{
    bboard_t bit_d = BIT(move.dr, move.dc),
        bit_s = BIT(move.sr, move.sc);
    int color = PIECE_COLOR(piece), p = PIECE_MASK & piece;

    engine->pieces[p][color] = (engine->pieces[p][color] & ~bit_s) | bit_d;
    engine->color_pieces[color] = (engine->color_pieces[color] & ~bit_s) | bit_d;
    engine->all_pieces = (engine->all_pieces & ~bit_s) | bit_d;

    if (engine->color_pieces[!color] & bit_d)
    {
        int enemy_p = engine->mailbox[move.dr * 8 + move.dc] & PIECE_MASK;

        /* capture */
        engine->pieces[enemy_p][!color] &= ~bit_d;
        engine->color_pieces[!color] &= ~bit_d;
        move.cap = enemy_p | 0x40;

        engine->scores[!color] -= PIECE_SCORES[enemy_p];
    }
    else
    {
        /* en passant capture */
#ifdef ENPASSANT
        if (p == PAWN && ABS(move.dc - move.sc) == 1)
        {
            /* capture */
            bboard_t enemy_d = BIT(engine->last_move.dr, engine->last_move.dc);
            engine->pieces[PAWN][!color] &= ~enemy_d;
            engine->color_pieces[!color] &= ~enemy_d;
            engine->all_pieces &= ~enemy_d;
            engine->mailbox[engine->last_move.dr * 8 + engine->last_move.dc] = EMPTY;
            move.cap = PAWN | 0xc0;

            engine->scores[!color] -= PIECE_SCORES[PAWN];
        }
        else
#endif
        {
            move.cap = 0;
        }
    }

    engine->mailbox[move.dr * 8 + move.dc] = piece;
    engine->mailbox[move.sr * 8 + move.sc] = EMPTY;

    /* castling */
    if (p == KING && ABS(move.dc - move.sc) == 2)
    {
        if (move.dc == 2)
        {
            engine->pieces[ROOK][color] = (engine->pieces[ROOK][color] & ~BIT(move.dr, 0)) | BIT(move.dr, 3);
            engine->color_pieces[color] = (engine->color_pieces[color] & ~BIT(move.dr, 0)) | BIT(move.dr, 3);
            engine->all_pieces = (engine->all_pieces & ~BIT(move.dr, 0)) | BIT(move.dr, 3);
            engine->mailbox[move.dr * 8 + 0] = EMPTY;
            engine->mailbox[move.dr * 8 + 3] = (color << COLOR_SHIFT) | ROOK;
        }
        else
        {
            engine->pieces[ROOK][color] = (engine->pieces[ROOK][color] & ~BIT(move.dr, 7)) | BIT(move.dr, 5);
            engine->color_pieces[color] = (engine->color_pieces[color] & ~BIT(move.dr, 7)) | BIT(move.dr, 5);
            engine->all_pieces = (engine->all_pieces & ~BIT(move.dr, 7)) | BIT(move.dr, 5);
            engine->mailbox[move.dr * 8 + 7] = EMPTY;
            engine->mailbox[move.dr * 8 + 5] = (color << COLOR_SHIFT) | ROOK;
        }
    }

    /* TODO promotions */

    engine->last_move = move;
    engine->last_move.op = piece;
    engine->num_moves[move.sr * 8 + move.sc]++;
#ifdef PATCHED
    if (engine->current_move == sizeof(engine->moves) / sizeof(engine->moves[0]))
    {
        engine->active = 0;
        return;
    }
#endif
    engine->moves[engine->current_move++] = move;
    engine->current_color = !engine->current_color;
}

static void undo_move()
{
    move_t move = engine->last_move;
    piece_t piece = engine->mailbox[move.dr * 8 + move.dc];
    bboard_t bit_d = BIT(move.dr, move.dc),
        bit_s = BIT(move.sr, move.sc);
    int color = PIECE_COLOR(piece), p = PIECE_MASK & piece;

    if (engine->current_move <= 0)
        return;

    /* TODO promotions */

    /* castling */
    if (p == KING && ABS(move.dc - move.sc) == 2)
    {
        if (move.dc == 2)
        {
            engine->pieces[ROOK][color] = (engine->pieces[ROOK][color] & ~BIT(move.dr, 3)) | BIT(move.dr, 0);
            engine->color_pieces[color] = (engine->color_pieces[color] & ~BIT(move.dr, 3)) | BIT(move.dr, 0);
            engine->all_pieces = (engine->all_pieces & ~BIT(move.dr, 3)) | BIT(move.dr, 0);
            engine->mailbox[move.dr * 8 + 3] = EMPTY;
            engine->mailbox[move.dr * 8 + 0] = (color << COLOR_SHIFT) | ROOK;
        }
        else
        {
            engine->pieces[ROOK][color] = (engine->pieces[ROOK][color] & ~BIT(move.dr, 5)) | BIT(move.dr, 7);
            engine->color_pieces[color] = (engine->color_pieces[color] & ~BIT(move.dr, 5)) | BIT(move.dr, 7);
            engine->all_pieces = (engine->all_pieces & ~BIT(move.dr, 5)) | BIT(move.dr, 7);
            engine->mailbox[move.dr * 8 + 5] = EMPTY;
            engine->mailbox[move.dr * 8 + 7] = (color << COLOR_SHIFT) | ROOK;
        }
    }

    engine->mailbox[move.dr * 8 + move.dc] = EMPTY;
    engine->mailbox[move.sr * 8 + move.sc] = piece;

    engine->pieces[p][color] = (engine->pieces[p][color] & ~bit_d) | bit_s;
    engine->color_pieces[color] = (engine->color_pieces[color] & ~bit_d) | bit_s;
    engine->all_pieces = (engine->all_pieces & ~bit_d) | bit_s;

    if (move.cap & 0x40)
    {
        if (move.cap & 0x80)
        {
            int enemy_r;
            if (move.dr == 2)
                enemy_r = 3;
            else
                enemy_r = 4;
            engine->pieces[PAWN][!color] |= BIT(enemy_r, move.dc);
            engine->color_pieces[!color] |= BIT(enemy_r, move.dc);
            engine->all_pieces |= BIT(enemy_r, move.dc);
            engine->mailbox[enemy_r * 8 + move.dc] = (!color << COLOR_SHIFT) | PAWN;

            engine->scores[!color] += PIECE_SCORES[PAWN];
        }
        else
        {
            int enemy_p = move.cap & PIECE_MASK;
            engine->pieces[enemy_p][!color] |= bit_d;
            engine->color_pieces[!color] |= bit_d;
            engine->all_pieces |= bit_d;
            engine->mailbox[move.dr * 8 + move.dc] = (!color << COLOR_SHIFT) | enemy_p;

            engine->scores[!color] += PIECE_SCORES[enemy_p];
        }
    }

    engine->num_moves[move.sr * 8 + move.sc]--;
    engine->current_move--;
    if (engine->current_move > 0)
        engine->last_move = engine->moves[engine->current_move-1];
    else
        engine->last_move.op = EMPTY;
    engine->current_color = !engine->current_color;
}

void engine_move(move_t move)
{
    piece_t piece;

    if (!engine->active)
        return;

    piece = engine->mailbox[move.sr * 8 + move.sc];
    if (!valid_move(move, piece))
    {
        send_illegal("invalid move", move);
        return;
    }

    apply_move(move, piece);
    if (!valid_board())
    {
        undo_move();
        send_illegal("illegal move", move);
        return;
    }

#ifdef DEBUG
    print_board();
    sanity_check_board();
#endif

    if (engine->go)
        engine_go();
}

void engine_set_color(int color)
{
    if (!engine->active)
        return;

    engine->current_color = color;
}

void engine_set_go(int go)
{
    if (!engine->active)
        return;

    engine->go = go;
}

void engine_set_depth(int depth)
{
    if (!engine->active)
        return;

    if (depth <= 0)
    {
        send_error("depth too small", "sd");
        return;
    }
    if (depth > MAX_DEPTH)
    {
        send_error("depth too large", "sd");
        return;
    }
    engine->max_depth = depth;
}

void engine_set_random(int random)
{
    if (!engine->active)
        return;

    engine->random = random;
}

static void generate_moves(unsigned int *num_results, move_t *results)
{
    bboard_t b, invalid, valid_captures;
    int color = engine->current_color,
        num_moves = 0,
        i, p, r, c;

#define ADD_MOVE(_sr, _sc, _dr, _dc, _prio) do { \
    results[num_moves].sr = _sr; \
    results[num_moves].sc = _sc; \
    results[num_moves].dr = _dr; \
    results[num_moves].dc = _dc; \
    results[num_moves].prio = _prio; \
    num_moves++; \
} while(0)
#define ADD_MOVE_IF_VALID(sr, sc, dr, dc, _cap) do { \
    int cap = _cap; \
    if (dr < 0 || dr >= 8 || dc < 0 || dc >= 8 || (invalid & BIT(dr, dc))) break; \
    if (valid_captures & BIT(dr, dc)) cap = 1; \
    else if (cap) break; \
    ADD_MOVE(sr, sc, dr, dc, cap ? 100 : 0); \
} while(0)

    /* can't move to our own piece */
    invalid = engine->color_pieces[color];

    valid_captures = engine->color_pieces[!color];

    /* pawns */
    for (p = -1, b = engine->pieces[PAWN][color]; b != 0 && p < 63; b >>= i + 1)
    {
        i = __builtin_ctzll(b);
        p += i + 1;
        r = p / 8;
        c = p % 8;

        if (color == WHITE)
        {
            ADD_MOVE_IF_VALID(r, c, r+1, c-1, 1);
            ADD_MOVE_IF_VALID(r, c, r+1, c+1, 1);
            /* can't capture a piece by going up */
            if (!(valid_captures & BIT(r+1, c)))
                ADD_MOVE_IF_VALID(r, c, r+1, c, 0);
            if (r == 1)
                if (!(valid_captures & BIT(r+2, c)) && !(engine->all_pieces & BIT(r+1, c)))
                    ADD_MOVE_IF_VALID(r, c, r+2, c, 0);
            /* test for en passant capture */
#ifdef ENPASSANT
            if ((engine->last_move.op & PIECE_MASK) == PAWN && /* last move piece was a pawn */
                ABS(engine->last_move.sr - engine->last_move.dr) == 2 && /* and it moved forward two */
                ABS(c - engine->last_move.dc) == 1 && engine->last_move.dr == r)
            {
                ADD_MOVE(r, c, r+1, engine->last_move.dc, 100);
            }
#endif
        }
        else
        {
            ADD_MOVE_IF_VALID(r, c, r-1, c-1, 1);
            ADD_MOVE_IF_VALID(r, c, r-1, c+1, 1);
            /* can't capture a piece by going down */
            if (!(valid_captures & BIT(r-1, c)))
                ADD_MOVE_IF_VALID(r, c, r-1, c, 0);
            if (r == 6)
                if (!(valid_captures & BIT(r-2, c)) && !(engine->all_pieces & BIT(r-1, c)))
                    ADD_MOVE_IF_VALID(r, c, r-2, c, 0);
            /* test for en passant capture */
#ifdef ENPASSANT
            if ((engine->last_move.op & PIECE_MASK) == PAWN && /* last move piece was a pawn */
                ABS(engine->last_move.sr - engine->last_move.dr) == 2 && /* and it moved forward two */
                ABS(c - engine->last_move.dc) == 1 && engine->last_move.dr == r)
            {
                ADD_MOVE(r, c, r-1, engine->last_move.dc, 100);
            }
#endif
        }
    }

    /* knights */
    for (p = -1, b = engine->pieces[KNIGHT][color]; b != 0 && p < 63; b >>= i + 1)
    {
        i = __builtin_ctzll(b);
        p += i + 1;
        r = p / 8;
        c = p % 8;

        ADD_MOVE_IF_VALID(r, c, r+2, c+1, 0);
        ADD_MOVE_IF_VALID(r, c, r+2, c-1, 0);
        ADD_MOVE_IF_VALID(r, c, r-2, c+1, 0);
        ADD_MOVE_IF_VALID(r, c, r-2, c-1, 0);
        ADD_MOVE_IF_VALID(r, c, r+1, c+2, 0);
        ADD_MOVE_IF_VALID(r, c, r+1, c-2, 0);
        ADD_MOVE_IF_VALID(r, c, r-1, c+2, 0);
        ADD_MOVE_IF_VALID(r, c, r-1, c-2, 0);
    }

    /* rooks / queens */
    for (p = -1, b = engine->pieces[ROOK][color] | engine->pieces[QUEEN][color]; b != 0 && p < 63; b >>= i + 1)
    {
        bboard_t bit;
        int j;
        i = __builtin_ctzll(b);
        p += i + 1;
        r = p / 8;
        c = p % 8;

        for (j = c+1, bit = 1ULL << (r * 8 + c + 1); j < 8; j++, bit <<= 1)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(r, c, r, j, 1);
                break;
            }
            ADD_MOVE_IF_VALID(r, c, r, j, 0);
        }
        for (j = c-1, bit = 1ULL << (r * 8 + c - 1); j >= 0; j--, bit >>= 1)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(r, c, r, j, 1);
                break;
            }
            ADD_MOVE_IF_VALID(r, c, r, j, 0);
        }
        for (j = r+1, bit = 1ULL << ((r+1) * 8 + c); j < 8; j++, bit <<= 8)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(r, c, j, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(r, c, j, c, 0);
        }
        for (j = r-1, bit = 1ULL << ((r-1) * 8 + c); j >= 0; j--, bit >>= 8)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(r, c, j, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(r, c, j, c, 0);
        }
    }

    /* bishops / queens */
    for (p = -1, b = engine->pieces[BISHOP][color] | engine->pieces[QUEEN][color]; b != 0 && p < 63; b >>= i + 1)
    {
        int or, oc;
        bboard_t bit;

        i = __builtin_ctzll(b);
        p += i + 1;
        or = p / 8;
        oc = p % 8;

        r = or + 1;
        c = oc + 1;
        for (bit = 1ULL << (r * 8 + c); r < 8 && c < 8; r++, c++, bit <<= 9)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(or, oc, r, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(or, oc, r, c, 0);
        }

        r = or - 1;
        c = oc + 1;
        for (bit = 1ULL << (r * 8 + c); r >= 0 && c < 8; r--, c++, bit >>= 7)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(or, oc, r, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(or, oc, r, c, 0);
        }

        r = or + 1;
        c = oc - 1;
        for (bit = 1ULL << (r * 8 + c); r < 8 && c >= 0; r++, c--, bit <<= 7)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(or, oc, r, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(or, oc, r, c, 0);
        }

        r = or - 1;
        c = oc - 1;
        for (bit = 1ULL << (r * 8 + c); r >= 0 && c >= 0; r--, c--, bit >>= 9)
        {
            if (engine->all_pieces & bit)
            {
                ADD_MOVE_IF_VALID(or, oc, r, c, 1);
                break;
            }
            ADD_MOVE_IF_VALID(or, oc, r, c, 0);
        }
    }

    /* king */
    p = __builtin_ctzll(engine->pieces[KING][color]);
    r = p / 8;
    c = p % 8;
    ADD_MOVE_IF_VALID(r, c, r-1, c-1, 0);
    ADD_MOVE_IF_VALID(r, c, r-1, c, 0);
    ADD_MOVE_IF_VALID(r, c, r-1, c+1, 0);
    ADD_MOVE_IF_VALID(r, c, r, c-1, 0);
    ADD_MOVE_IF_VALID(r, c, r, c+1, 0);
    ADD_MOVE_IF_VALID(r, c, r+1, c-1, 0);
    ADD_MOVE_IF_VALID(r, c, r+1, c, 0);
    ADD_MOVE_IF_VALID(r, c, r+1, c+1, 0);

    /* TODO castling */

    *num_results = num_moves;
}

/* returns positive if WHITE winning, negative if BLACK winning */
static int evaluate()
{
    bboard_t attacks;
    int raw_score = engine->scores[WHITE] - engine->scores[BLACK];

    attacks = calculate_attacks(WHITE);
    raw_score += __builtin_popcountll(attacks & 0x0000007e7e000000ULL);
    raw_score += __builtin_popcountll(attacks & ~engine->color_pieces[WHITE]) * 2;
    raw_score += __builtin_popcountll(attacks & engine->color_pieces[WHITE]);
    attacks = calculate_attacks(BLACK);
    raw_score -= __builtin_popcountll(attacks & 0x0000007e7e000000ULL);
    raw_score -= __builtin_popcountll(attacks & ~engine->color_pieces[BLACK]) * 2;
    raw_score -= __builtin_popcountll(attacks & engine->color_pieces[BLACK]);

    return raw_score;
}

static int quiesce(int depth, int alpha, int beta)
{
    int score, tmp;
    unsigned int i, num_moves = 0;
    bboard_t attacks, captures;
    move_t *moves = &engine->moves_buf[depth * MAX_MOVES_PER_DEPTH];

    score = evaluate();
    if (engine->current_color == BLACK)
        score = -score;

    if (alpha < score)
        alpha = score;
    if (alpha >= beta)
        return beta;

    attacks = calculate_attacks(engine->current_color);
    captures = attacks & engine->color_pieces[!engine->current_color];
    if (!captures || depth >= MAX_DEPTH)
        return score;

#if 0
    /* detect checkmate */
    if (captures & engine->pieces[KING][!engine->current_color])
        return score + PIECE_SCORES[KING];
#endif 

    generate_moves(&num_moves, moves);
    for (i = 0; i < num_moves; i++)
    {
        move_t move = moves[i];
        /* ignore non-capturing moves */
        if (!(captures & BIT(move.dr, move.dc)))
            continue;

        if ((engine->mailbox[move.dr * 8 + move.dc] & PIECE_MASK) == KING)
            return SCORE_MAX;

        apply_move(move, engine->mailbox[move.sr * 8 + move.sc]);
        tmp = -quiesce(depth + 1, -beta, -alpha);
        undo_move();

        /* update best score */
        if (tmp > score)
            score = tmp;
        /* adjust score range */
        if (score > alpha)
            alpha = score;
        /* if we can't reduce score range, give up asap */
        if (alpha >= beta)
            return alpha;
    }

    return score;
}

static int randint(unsigned int max)
{
    uint32_t x;
    size_t bytes;
    random(&x, sizeof(x), &bytes);
    return x % max;
}

static int search(int depth, int alpha, int beta, move_t *best_move)
{
    int score = SCORE_MIN, tmp;
    unsigned int i, num_moves = 0;
    move_t *moves = &engine->moves_buf[depth * MAX_MOVES_PER_DEPTH];

    generate_moves(&num_moves, moves);
    for (i = 0; i < num_moves; i++)
    {
        move_t move = moves[i];

        if ((engine->mailbox[move.dr * 8 + move.dc] & PIECE_MASK) == KING)
            return SCORE_MAX;

        apply_move(move, engine->mailbox[move.sr * 8 + move.sc]);

        if (depth == engine->max_depth)
            tmp = -quiesce(depth + 1, -beta, -alpha);
        else
            tmp = -search(depth + 1, -beta, -alpha, NULL);

        undo_move();

#ifdef DEBUG
        sanity_check_board();
#endif

        if (depth == 0 && engine->random)
            tmp += randint(5) - 2;

        /* update best score */
        if (tmp > score)
        {
            score = tmp;
            if (depth == 0)
                *best_move = move;
        }
        /* adjust score range */
        if (score > alpha)
            alpha = score;
        /* if we can't reduce score range, give up asap */
        if (alpha >= beta)
            return alpha;
    }

    return score;
}

void engine_go()
{
    int score;
    move_t move;

    if (!engine->active)
        return;

    score = search(0, SCORE_MIN, SCORE_MAX, &move);
    engine->accept_draw = score <= DRAW_THRESHOLD;
    if (score == SCORE_MIN)
        send_resign();
    else
    {
        send_move(move);
        apply_move(move, engine->mailbox[move.sr * 8 + move.sc]);
#ifdef DEBUG
        print_board();
        sanity_check_board();
#endif
    }
}

void engine_result()
{
    engine->active = 0;
}

void engine_offer_draw()
{
    if (!engine->active)
        return;

    if (engine->accept_draw)
    {
        send_draw();
    }
}

void engine_undo()
{
    if (!engine->active)
        return;

    undo_move();
}

int engine_get_random()
{
    return engine->random;
}
