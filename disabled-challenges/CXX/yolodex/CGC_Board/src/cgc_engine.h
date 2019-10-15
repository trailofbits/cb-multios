#ifndef ENGINE_H_
#define ENGINE_H_

#include "cgc_stdint.h"

enum {
    WHITE,
    BLACK
};

enum {
    WHITE_WON,
    BLACK_WON,
    DRAW,
    UNFINISHED
};

enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NUM_PIECES = KING + 1,
    EMPTY = NUM_PIECES
};

typedef uint64_t bboard_t;
typedef uint8_t piece_t;
#define PIECE_MASK 0x0f
#define COLOR_SHIFT 7
#define PIECE_COLOR(p) ((piece_t)(p) >> COLOR_SHIFT)
typedef struct {
    int8_t sr, sc, dr, dc;
    uint8_t p, op, cap, prio;
} move_t;

void cgc_engine_destroy();
int cgc_engine_get_cgc_random();
void cgc_engine_go();
int cgc_engine_init();
void cgc_engine_move(move_t move);
void cgc_engine_new();
void cgc_engine_offer_draw();
void cgc_engine_result();
void cgc_engine_set_color(int);
void cgc_engine_set_depth(int);
void cgc_engine_set_go(int);
void cgc_engine_set_cgc_random(int);
void cgc_engine_undo();

#endif
