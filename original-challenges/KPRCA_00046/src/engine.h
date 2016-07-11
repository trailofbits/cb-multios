#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdint.h>

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

void engine_destroy();
int engine_get_random();
void engine_go();
int engine_init();
void engine_move(move_t move);
void engine_new();
void engine_offer_draw();
void engine_result();
void engine_set_color(int);
void engine_set_depth(int);
void engine_set_go(int);
void engine_set_random(int);
void engine_undo();

#endif
