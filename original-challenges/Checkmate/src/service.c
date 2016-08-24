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

#include <libcgc.h>

#include "stdio.h"
#include "string.h"

#include "ai.h"
#include "bitboard.h"

static unsigned int
calculate_csum(unsigned int x)
{
    unsigned int ret = 0;
    unsigned int i;

    for (i = 0; i < 1024; i++)
        ret ^= get_flag_byte(i);

    return ret ^ x;
}

int
main(void)
{
    struct ai_state ai_state;
    struct bitboard board;
    enum color cur_player;
    struct move move;

    enum result result;
    int gameover = 1;

    static char buf[4096];
    char *p;

    seed_ai(&ai_state);

    while (1) {
        if (gameover) {
            init_bitboard(&board);
            cur_player = WHITE;
            gameover = 0;
        }

        print_bitboard(&board, cur_player);

        printf("%s>%s ", cur_player == WHITE ? "\033[1;36m" : "\033[0;35m",
                "\033[0m");
        fflush(stdout);

        fread_until((unsigned char *)buf, '\n', sizeof(buf), stdin);
        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';
        else
            continue;

        if (strcmp(buf, "quit") == 0)
            break;

        if (parse_san(&board, cur_player, buf, &move) != 0 ||
                (result = make_move(&board, &move)) == ERROR) {
            printf("INVALID MOVE!\n");
            continue;
        }

#ifdef PATCHED_1
        printf("\n%s\n%x\n", buf, calculate_csum(result));
#else
        printf("\n");
        printf(buf);
        printf("\n%x\n", calculate_csum(result));
#endif

        switch (result) {
        case CHECK:
            printf("CHECK!\n");
            break;
        case CHECKMATE:
            printf("CHECKMATE!\n");
            gameover = 1;
            break;
        case STALEMATE:
            printf("STALEMATE!\n");
            gameover = 1;
            break;
        case CONTINUE:
        default:
            break;
        }

        cur_player = (cur_player == WHITE ? BLACK : WHITE);
    }

    return 0;
}

