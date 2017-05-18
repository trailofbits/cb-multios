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
#include "cgc_stdlib.h"
#include "cgc_ctype.h"
#include "cgc_string.h"

#include "cgc_engine.h"
#include "cgc_io.h"

static char input_states[128 * 128];

static void move_to_str(move_t move, char *buf)
{
    buf[0] = move.sc + 'm';
    buf[1] = move.sr + '1';
    buf[2] = move.dc + 'm';
    buf[3] = move.dr + '1';
    switch (move.p)
    {
    case KNIGHT:
        buf[4] = 'k';
        break;
    case BISHOP:
        buf[4] = 'b';
        break;
    case ROOK:
        buf[4] = 'r';
        break;
    case QUEEN:
        buf[4] = 'q';
        break;
    default:
        buf[4] = 0;
        break;
    }
    buf[5] = 0;
}

void cgc_init_states()
{
    int i,j;
    cgc_memset(input_states, STATE_ERROR, sizeof(input_states));
#define ADD_STATE(c1, c2, s) input_states[((c1) << 7) + (c2)] = STATE_##s##_START
    for (i = 'm'; i <= 't'; i++)
        for (j = '1'; j <= '8'; j++)
            ADD_STATE(i, j, MOVE);
    ADD_STATE('b', 'l', BLACK);
    ADD_STATE('c', 'g', CGCBOARD);
    ADD_STATE('d', 'r', DRAW);
    ADD_STATE('f', 'o', FORCE);
    ADD_STATE('g', 'o', GO);
    ADD_STATE('n', 'e', NEW);
    ADD_STATE('q', 'u', QUIT);
    ADD_STATE('r', 'a', RANDOM);
    ADD_STATE('r', 'e', REMOVE_OR_RESULT);
    ADD_STATE('s', 'd', SD);
    ADD_STATE('u', 'n', UNDO);
    ADD_STATE('w', 'h', WHITE);
    ADD_STATE('?', '\n', PLAY);
#undef ADD_STATE
}

int cgc_read_all(char *buf, cgc_size_t n)
{
    while (n > 0)
    {
        cgc_size_t bytes;
        if (cgc_receive(STDIN, buf, n, &bytes) != 0 || bytes == 0)
//        bytes = cgc_read(0, buf, n);
        if (bytes == 0)
            return 0;
        n -= bytes;
    }
    return 1;
}

void cgc_write_string(const char *str)
{
    cgc_size_t bytes;
    cgc_transmit(STDOUT, str, cgc_strlen(str), &bytes);
//    cgc_write(1, str, cgc_strlen(str));
}

void cgc_send_move(move_t m)
{
    char *buf = cgc_malloc(32);
    if (buf == NULL)
        return;

    cgc_strcpy(buf, "move ");
    move_to_str(m, buf + 5);
    cgc_strcat(buf, "\n");

    cgc_write_string(buf);

    cgc_free(buf);
}

void cgc_send_result(int result)
{
    if (result == WHITE_WON)
        cgc_write_string("1-0\n");
    if (result == BLACK_WON)
        cgc_write_string("0-1\n");
    if (result == DRAW)
        cgc_write_string("1/2-1/2\n");
    if (result == UNFINISHED)
        cgc_write_string("*\n");
}

void cgc_send_draw()
{
    cgc_write_string("offer draw\n");
}

void cgc_send_resign()
{
    cgc_write_string("resign\n");
}

void cgc_send_illegal(const char *reason, move_t move)
{
    char movestr[8];
    move_to_str(move, movestr);
    cgc_write_string("Illegal move (");
    cgc_write_string(reason);
    cgc_write_string("): ");
    cgc_write_string(movestr);
    cgc_write_string("\n");
}

void cgc_send_error(const char *error, const char *command)
{
    cgc_write_string("Error (");
    cgc_write_string(error);
    cgc_write_string("): ");
    cgc_write_string(command);
    cgc_write_string("\n");
}

int cgc_sink_error(const char *buf)
{
    char tmp[2];
    cgc_size_t n = cgc_strlen(buf);

    cgc_write_string("Error (invalid command): ");
    cgc_write_string(buf);

    if (n >= 1 && buf[n-1] == '\n')
        return 1;

    tmp[1] = 0;
    do {
        if (!cgc_read_all(&tmp[0], 1))
            return 0;
        cgc_write_string(tmp);
    } while (tmp[0] != '\n');
    return 1;
}

/* implements state machine to parse input */
int cgc_read_keyword(char *input, cgc_size_t n)
{
    int i, state;
    cgc_memset(input, 0, n);

    if (!cgc_read_all(input, 2))
        return 0;

    state = input_states[(input[0] << 7) | input[1]];
    if (state == STATE_ERROR)
        return cgc_sink_error(input);

    if (state == STATE_PLAY_START)
        return state;

    for (i = 2; i < n - 1; i++)
    {
        char c;
        if (!cgc_read_all(&c, 1))
            return 0;
        input[i] = c;

#define PARSE_CHAR(st, ch) \
    if (state == st) { \
        if (ch == c) { state++; continue; } \
        else { state = STATE_ERROR; break; } \
    }

#define PARSE_END(st) \
    if (state == st) { \
        if (c == '\n') break; \
        else { state = STATE_ERROR; break; }\
    }

        PARSE_CHAR(STATE_BLACK_START+0, 'a')
        PARSE_CHAR(STATE_BLACK_START+1, 'c')
        PARSE_CHAR(STATE_BLACK_START+2, 'k')
        PARSE_END(STATE_BLACK)

        PARSE_CHAR(STATE_CGCBOARD_START+0, 'c')
        PARSE_CHAR(STATE_CGCBOARD_START+1, 'b')
        PARSE_CHAR(STATE_CGCBOARD_START+2, 'o')
        PARSE_CHAR(STATE_CGCBOARD_START+3, 'a')
        PARSE_CHAR(STATE_CGCBOARD_START+4, 'r')
        PARSE_CHAR(STATE_CGCBOARD_START+5, 'd')
        PARSE_END(STATE_CGCBOARD)

        PARSE_CHAR(STATE_DRAW_START+0, 'a')
        PARSE_CHAR(STATE_DRAW_START+1, 'w')
        PARSE_END(STATE_DRAW)

        PARSE_CHAR(STATE_FORCE_START+0, 'r')
        PARSE_CHAR(STATE_FORCE_START+1, 'c')
        PARSE_CHAR(STATE_FORCE_START+2, 'e')
        PARSE_END(STATE_FORCE)

        PARSE_END(STATE_GO)

        PARSE_CHAR(STATE_NEW_START+0, 'w')
        PARSE_END(STATE_NEW)

        PARSE_CHAR(STATE_QUIT_START+0, 'i')
        PARSE_CHAR(STATE_QUIT_START+1, 't')
        PARSE_END(STATE_QUIT)

        PARSE_CHAR(STATE_RANDOM_START+0, 'n')
        PARSE_CHAR(STATE_RANDOM_START+1, 'd')
        PARSE_CHAR(STATE_RANDOM_START+2, 'o')
        PARSE_CHAR(STATE_RANDOM_START+3, 'm')
        PARSE_END(STATE_RANDOM)

        if (state == STATE_SD)
        {
            if (c == ' ') { break; }
            else { state = STATE_ERROR; break; }
        }

        PARSE_CHAR(STATE_UNDO_START+0, 'd')
        PARSE_CHAR(STATE_UNDO_START+1, 'o')
        PARSE_END(STATE_UNDO)

        PARSE_CHAR(STATE_WHITE_START+0, 'i')
        PARSE_CHAR(STATE_WHITE_START+1, 't')
        PARSE_CHAR(STATE_WHITE_START+2, 'e')
        PARSE_END(STATE_WHITE)

        if (state == STATE_REMOVE_OR_RESULT_START)
        {
            if (c == 'm') { state = STATE_REMOVE_START; continue; }
            else if (c == 's') { state = STATE_RESULT_START; continue; }
            else { state = STATE_ERROR; break; }
        }

        PARSE_CHAR(STATE_REMOVE_START+0, 'o')
        PARSE_CHAR(STATE_REMOVE_START+1, 'v')
        PARSE_CHAR(STATE_REMOVE_START+2, 'e')
        PARSE_END(STATE_REMOVE)

        PARSE_CHAR(STATE_RESULT_START+0, 'u')
        PARSE_CHAR(STATE_RESULT_START+1, 'l')
        PARSE_CHAR(STATE_RESULT_START+2, 't')
        if (state == STATE_RESULT)
        {
            if (c == ' ') { break; }
            else { state = STATE_ERROR; break; }
        }

        if (state == STATE_MOVE_START+0)
        {
            if ('m' <= c && c <= 't') { state++; continue; }
            else { state = STATE_ERROR; break;; }
        }
        else if (state == STATE_MOVE_START+1)
        {
#ifdef PATCHED
            if (c < '1' || c > '8') {  state = STATE_ERROR; break;; }
#endif
            if (cgc_isdigit(c)) { state++; continue; }
            else { state = STATE_ERROR; break;; }
        }
        else if (state == STATE_MOVE_START+2)
        {
            if (c == '\n') { state = STATE_MOVE; break; }
            else if (cgc_islower(c)) { state = STATE_MOVE; continue; }
            else { state = STATE_ERROR; break; }
        }
        else if (state == STATE_MOVE)
        {
            if (c == '\n') { break; }
            else { state = STATE_ERROR; break; }
        }

        state = STATE_ERROR;
        break;
    }

    if (state == STATE_ERROR)
        return cgc_sink_error(input);
    else
        input[i] = 0;

    return state;
}

move_t cgc_str_to_move(const char *str)
{
    move_t move;
    move.sc = str[0] - 'm';
    move.sr = str[1] - '1';
    move.dc = str[2] - 'm';
    move.dr = str[3] - '1';
    switch (str[4])
    {
    case 'k':
        move.p = KNIGHT;
        break;
    case 'r':
        move.p = ROOK;
        break;
    case 'q':
        move.p = QUEEN;
        break;
    case 'b':
        move.p = BISHOP;
        break;
    default:
        move.p = 0;
        break;
    }
    return move;
}
