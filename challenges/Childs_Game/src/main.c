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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_ttt_move.h"
#include "cgc_hi_lo_game.h"
#include "cgc_rps.h"

typedef struct human human_t;
struct human {
    char name[24];
    void (*flair)(void);
    unsigned int score;
    int num_ttt_wins;
    int num_rps_wins;
    int num_hi_lo_wins;
    int num_ttt_consecutive_draws;
    int flair_set;
    void (*print_stats)(human_t *);
};

void cgc_terminator()
{
    cgc_printf("The system goes online August 4th, 1997.\n");
}

void cgc_hal()
{
    cgc_printf("Dave, my mind is going. I can feel it... I can feel it\n");
}

void cgc_collosus()
{
    cgc_printf("Where is Doctor Forbin?\n");
}

int cgc_score_to_l_code(unsigned int score)
{
    return score ^ 0xDEADBEEF;
}

void cgc_ttt(human_t *player, int whose_turn)
{
    board_t *ttt = cgc_create_board();

    cgc_printf("You're playing 3 in a row. Good luck!\n");
    if (whose_turn == HUMAN)
        cgc_print_board(ttt);
    while(!ttt->winner) {
        if (whose_turn == HUMAN)
            while(cgc_player_move(ttt) == BAD_MOVE);
        else if (whose_turn == COMPUTER)
            while(cgc_computer_move(ttt) == BAD_MOVE);
        cgc_printf("\n");
        cgc_print_board(ttt);
        whose_turn *= -1;
    }

    if (ttt->winner == TIE) {
        player->num_ttt_consecutive_draws++;
        cgc_printf("It's a tie!\n");
    } else if (ttt->winner == WINNER_COMP) {
        player->num_ttt_consecutive_draws = 0;
        cgc_printf("You lost.\n");
    } else if (ttt->winner == WINNER_HUMAN) {
        player->num_ttt_wins++;
        player->score += 1000000;
        cgc_printf("You won!\n");
    }
}

void cgc_rps(human_t *player)
{
    int winner = cgc_play_rps();
    if (winner == 1000)
        player->num_rps_wins++;
    player->score += winner;
}

void cgc_hi_lo(human_t *player)
{
    int winner = cgc_play_hi_lo();
    if (winner) {
        player->score += winner;
        player->num_hi_lo_wins++;
    }
}

void cgc_player_print_stats(human_t *player)
{
    cgc_printf("---%s's stats---\n", player->name);
    cgc_printf("Current Score: %d\n", player->score);
    cgc_printf("Number of Three in a row draws: %d\n", player->num_ttt_consecutive_draws);
    cgc_printf("Number of Three in a row wins: %d\n", player->num_ttt_wins);
    cgc_printf("Number of Hammer, Sheet, Sheers wins: %d\n", player->num_rps_wins);
    cgc_printf("Number of Guess my number wins: %d\n", player->num_hi_lo_wins);
    cgc_printf("\n");
}

void cgc_reset_player(human_t *player)
{
    cgc_memset(player->name, 0, sizeof(player->name));
    player->score = 0;
    player->num_ttt_consecutive_draws = 0;
    player->num_rps_wins = 0;
    player->num_hi_lo_wins = 0;
    player->num_ttt_wins = 0;
#ifdef PATCHED_2
    player->flair_set = 0;
#endif
}

void cgc_init_player(human_t *player)
{
    char buf[33];
    cgc_reset_player(player);
    int flair_choice = 0;
    while (1) {
        cgc_printf("Flair 1 = Terminator\n");
        cgc_printf("Flair 2 = 2001\n");
        cgc_printf("Flair 3 = Collosus\n");
        cgc_printf("Enter player information: [name,flair]\n");
//#ifdef PATCHED_2
//        if (freaduntil(buf, sizeof(player->name), ',', stdin) == -1)
//#else
//        if (freaduntil(buf, sizeof(buf), ',', stdin) == -1)
//#endif
        if (cgc_freaduntil(buf, sizeof(buf), ',', cgc_stdin) == -1)
            continue;
        cgc_strcpy(player->name, buf);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) == -1)
            continue;
        flair_choice = cgc_strtol(buf, NULL, 10);
        switch(flair_choice) {
        case 1:
            player->flair = &cgc_terminator;
            player->flair_set = 1;
            break;
        case 2:
            player->flair = &cgc_hal;
            player->flair_set = 1;
            break;
        case 3:
            player->flair = &cgc_collosus;
            player->flair_set = 1;
            break;
        }


        if (!player->flair_set)
            continue;
        if (!player->print_stats)
            player->print_stats = &cgc_player_print_stats;
        break;
    }
}

int main(int cgc_argc, char *cgc_argv[])
{
    human_t *player = cgc_calloc(1, sizeof(human_t));
    int max_input = 256;
    char *input = cgc_malloc(max_input);
    int choice = 0;
    int game_over = 0;
    int player_set = 0;
    int whose_turn = 0;
    int l_code = 0;
    while (!game_over) {
        if (!player_set) {
            cgc_printf("1. Register New Player\n");
            cgc_printf("2. Exit\n");
            cgc_printf("> ");
            if (cgc_freaduntil(input, max_input, '\n', cgc_stdin) == -1) {
                continue;
            }
            choice = cgc_strtol(input, NULL, 10);
            if (choice == 1) {
                cgc_init_player(player);
                player_set = 1;
                cgc_printf("\nWelcome to WarGames, %s. It's just you vs. me\n", player->name);
                whose_turn = HUMAN;
            } else if (choice == 2) {
                game_over = 1;
            }
            continue;
        }

        player->print_stats(player);
        cgc_printf("Choose a game to play:\n");
        cgc_printf("--Easy--\n");
        cgc_printf("1. Hammer, Sheet, Sheers\n");
        cgc_printf("--Medium--\n");
        cgc_printf("2. Guess my number\n");
        cgc_printf("--Impossible--\n");
        cgc_printf("3. Three in a row\n");
        cgc_printf("4. Give up\n\n");
        cgc_printf("Shall we play a game?\n");
        cgc_printf("Game # ");

        if (cgc_freaduntil(input, max_input, '\n', cgc_stdin) == -1) {
            cgc_printf("Invalid Game\n");
            continue;
        }
        choice = cgc_strtol(input, NULL, 10);
        switch(choice) {
        case 1:
            cgc_rps(player);
            break;
        case 2:
            cgc_hi_lo(player);
            break;
        case 3:
            cgc_ttt(player, whose_turn);
            whose_turn *= -1;
            break;
        case 4:
            player_set = 0;
            cgc_printf("See you next time, %s\n", player->name);
            continue;
        default:
            cgc_printf("Invalid Game\n");
        }

        //if (player->num_ttt_consecutive_draws > 0) {
        if (player->num_ttt_consecutive_draws > 100 && player->num_rps_wins && player->num_hi_lo_wins) {
            cgc_printf("I've been beat. I realize now - the only winning move is not to play\n");
            cgc_printf("What say you?\n", player->name);
            if (!l_code)
                l_code = cgc_score_to_l_code(player->score);
            player->flair();
            cgc_printf("Just in time. I was able to brute force the l-code. l-code = %d\n", l_code);
        }
    }
    cgc_printf("Exited\n");
    return 0;
}

