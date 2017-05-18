#ifndef IO_H_
#define IO_H_

#include "cgc_stdlib.h"
#include "cgc_engine.h"

#define DEFINE_STATE(n, l) STATE_##n##_START, STATE_##n = STATE_##n##_START+l - 2
enum {
    STATE_ERROR = 1,
    DEFINE_STATE(MOVE, 5),
    DEFINE_STATE(BLACK, 5),
    DEFINE_STATE(CGCBOARD, 8),
    DEFINE_STATE(DRAW, 4),
    DEFINE_STATE(FORCE, 5),
    DEFINE_STATE(GO, 2),
    DEFINE_STATE(NEW, 3),
    DEFINE_STATE(QUIT, 4),
    DEFINE_STATE(RANDOM, 6),
    DEFINE_STATE(SD, 2),
    DEFINE_STATE(UNDO, 4),
    DEFINE_STATE(WHITE, 5),
    STATE_REMOVE_OR_RESULT_START,
    STATE_REMOVE_START,
    STATE_REMOVE = STATE_REMOVE_START + 3,
    STATE_RESULT_START,
    STATE_RESULT = STATE_RESULT_START + 3,
    STATE_PLAY_START,
    STATE_PLAY = STATE_PLAY_START
};
#undef DEFINE_STATE

void cgc_init_states();
int cgc_read_all(char *buf, cgc_size_t n);
int cgc_read_keyword(char *input, cgc_size_t n);
void cgc_write_string(const char *str);
void cgc_send_move(move_t move);
void cgc_send_result(int result);
void cgc_send_draw();
void cgc_send_resign();
void cgc_send_illegal(const char *reason, move_t move);
void cgc_send_error(const char *error, const char *command);
int cgc_sink_error(const char *buf);
move_t cgc_str_to_move(const char *str);

#endif
