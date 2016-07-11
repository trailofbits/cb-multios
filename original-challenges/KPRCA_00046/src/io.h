#ifndef IO_H_
#define IO_H_

#include <stdlib.h>
#include "engine.h"

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

void init_states();
int read_all(char *buf, size_t n);
int read_keyword(char *input, size_t n);
void write_string(const char *str);
void send_move(move_t move);
void send_result(int result);
void send_draw();
void send_resign();
void send_illegal(const char *reason, move_t move);
void send_error(const char *error, const char *command);
int sink_error(const char *buf);
move_t str_to_move(const char *str);

#endif
