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

#include "engine.h"
#include "io.h"

static int handle_result()
{
    char tmp[16];
    int result;
    size_t n;

    memset(tmp, 0, sizeof(tmp));
    for (n = 0; n < sizeof(tmp) - 1; n++)
    {
        if (!read_all(&tmp[n], 1))
            return 0;
        if (tmp[n] == ' ' || tmp[n] == '\n')
            break;
    }
    if (n == sizeof(tmp))
        return sink_error("result ... ");

    /* sink until EOL */
    while (tmp[n] != '\n')
    {
        char c;
        if (!read_all(&c, 1))
            return 0;
        if (c == '\n')
            break;
    }

    if (strncmp(tmp, "1-0", 3) == 0)
        result = WHITE_WON;
    else if (strncmp(tmp, "0-1", 3) == 0)
        result = BLACK_WON;
    else if (strncmp(tmp, "1/2-1/2", 7) == 0)
        result = DRAW;
    else if (strncmp(tmp, "*", 1) == 0)
        result = UNFINISHED;
    else
    {
        write_string("Error (invalid command): result\n");
        return 1;
    }

    engine_result(result);
    return 1;
}

static int handle_sd()
{
    char tmp[16];
    size_t n;

    memset(tmp, 0, sizeof(tmp));
    for (n = 0; n < sizeof(tmp) - 1; n++)
    {
        if (!read_all(&tmp[n], 1))
            return 0;
        if (tmp[n] == '\n')
            break;
    }
    if (n == sizeof(tmp))
        return sink_error("sd ... ");

    engine_set_depth(strtol(tmp, 0, 10));
    return 1;
}

int main()
{
    char input[16];
    int done = 0, state;

    if (!engine_init())
        return 1;
    init_states();

    while (!done)
    {
        state = read_keyword(input, sizeof(input));
        if (state == 0)
            break;
        if (state == STATE_ERROR)
            continue;
        
        //fprintf(stderr, "cmd %s state %d\n", input, state);


        switch (state)
        {
        case STATE_BLACK:
            engine_set_color(BLACK);
            break;
        case STATE_WHITE:
            engine_set_color(WHITE);
            break;
        case STATE_CGCBOARD:
            write_string("\n");
            break;
        case STATE_DRAW:
            engine_offer_draw();
            break;
        case STATE_FORCE:
            engine_set_go(0);
            break;
        case STATE_GO:
            engine_set_go(1);
            break;
        case STATE_NEW:
            engine_new();
            break;
        case STATE_RANDOM:
            engine_set_random(!engine_get_random());
            break;
        case STATE_RESULT:
            if (!handle_result())
                done = 1;
            break;
        case STATE_REMOVE:
            engine_undo();
            engine_undo();
            break;
        case STATE_QUIT:
            write_string("bye\n");
            done = 1;
            break;
        case STATE_SD:
            if (!handle_sd())
                done = 1;
            break;
        case STATE_UNDO:
            engine_undo();
            break;
        case STATE_MOVE:
            engine_move(str_to_move(input));
            break;
        case STATE_PLAY:
            engine_go();
            break;
        }
    }

    engine_destroy();

    return 0;
}
