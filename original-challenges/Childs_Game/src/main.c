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
#include <stdio.h>
#include <string.h>
#include "ttt_move.h"
#include "hi_lo_game.h"
#include "rps.h"

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

void terminator()
{
    printf("The system goes online August 4th, 1997.\n");
}

void hal()
{
    printf("Dave, my mind is going. I can feel it... I can feel it\n");
}

void collosus()
{
    printf("Where is Doctor Forbin?\n");
}

int score_to_l_code(unsigned int score)
{
    return score ^ 0xDEADBEEF;
}

void ttt(human_t *player, int whose_turn)
{
    board_t *ttt = create_board();

    printf("You're playing 3 in a row. Good luck!\n");
    if (whose_turn == HUMAN)
        print_board(ttt);
    while(!ttt->winner) {
        if (whose_turn == HUMAN)
            while(player_move(ttt) == BAD_MOVE);
        else if (whose_turn == COMPUTER)
            while(computer_move(ttt) == BAD_MOVE);
        printf("\n");
        print_board(ttt);
        whose_turn *= -1;
    }

    if (ttt->winner == TIE) {
        player->num_ttt_consecutive_draws++;
        printf("It's a tie!\n");
    } else if (ttt->winner == WINNER_COMP) {
        player->num_ttt_consecutive_draws = 0;
        printf("You lost.\n");
    } else if (ttt->winner == WINNER_HUMAN) {
        player->num_ttt_wins++;
        player->score += 1000000;
        printf("You won!\n");
    }
}

void rps(human_t *player)
{
    int winner = play_rps();
    if (winner == 1000)
        player->num_rps_wins++;
    player->score += winner;
}

void hi_lo(human_t *player)
{
    int winner = play_hi_lo();
    if (winner) {
        player->score += winner;
        player->num_hi_lo_wins++;
    }
}

void player_print_stats(human_t *player)
{
    printf("---%s's stats---\n", player->name);
    printf("Current Score: %d\n", player->score);
    printf("Number of Three in a row draws: %d\n", player->num_ttt_consecutive_draws);
    printf("Number of Three in a row wins: %d\n", player->num_ttt_wins);
    printf("Number of Hammer, Sheet, Sheers wins: %d\n", player->num_rps_wins);
    printf("Number of Guess my number wins: %d\n", player->num_hi_lo_wins);
    printf("\n");
}

void reset_player(human_t *player)
{
    memset(player->name, 0, sizeof(player->name));
    player->score = 0;
    player->num_ttt_consecutive_draws = 0;
    player->num_rps_wins = 0;
    player->num_hi_lo_wins = 0;
    player->num_ttt_wins = 0;
#ifdef PATCHED_2
    player->flair_set = 0;
#endif
}

void init_player(human_t *player)
{
    char buf[33];
    reset_player(player);
    int flair_choice = 0;
    while (1) {
        printf("Flair 1 = Terminator\n");
        printf("Flair 2 = 2001\n");
        printf("Flair 3 = Collosus\n");
        printf("Enter player information: [name,flair]\n");
//#ifdef PATCHED_2
//        if (freaduntil(buf, sizeof(player->name), ',', stdin) == -1)
//#else
//        if (freaduntil(buf, sizeof(buf), ',', stdin) == -1)
//#endif
        if (freaduntil(buf, sizeof(buf), ',', stdin) == -1)
            continue;
        strcpy(player->name, buf);
        if (freaduntil(buf, sizeof(buf), '\n', stdin) == -1)
            continue;
        flair_choice = strtol(buf, NULL, 10);
        switch(flair_choice) {
        case 1:
            player->flair = &terminator;
            player->flair_set = 1;
            break;
        case 2:
            player->flair = &hal;
            player->flair_set = 1;
            break;
        case 3:
            player->flair = &collosus;
            player->flair_set = 1;
            break;
        }


        if (!player->flair_set)
            continue;
        if (!player->print_stats)
            player->print_stats = &player_print_stats;
        break;
    }
}

int main()
{
    human_t *player = calloc(1, sizeof(human_t));
    int max_input = 256;
    char *input = malloc(max_input);
    int choice = 0;
    int game_over = 0;
    int player_set = 0;
    int whose_turn = 0;
    int l_code = 0;
    while (!game_over) {
        if (!player_set) {
            printf("1. Register New Player\n");
            printf("2. Exit\n");
            printf("> ");
            if (freaduntil(input, max_input, '\n', stdin) == -1) {
                continue;
            }
            choice = strtol(input, NULL, 10);
            if (choice == 1) {
                init_player(player);
                player_set = 1;
                printf("\nWelcome to WarGames, %s. It's just you vs. me\n", player->name);
                whose_turn = HUMAN;
            } else if (choice == 2) {
                game_over = 1;
            }
            continue;
        }

        player->print_stats(player);
        printf("Choose a game to play:\n");
        printf("--Easy--\n");
        printf("1. Hammer, Sheet, Sheers\n");
        printf("--Medium--\n");
        printf("2. Guess my number\n");
        printf("--Impossible--\n");
        printf("3. Three in a row\n");
        printf("4. Give up\n\n");
        printf("Shall we play a game?\n");
        printf("Game # ");

        if (freaduntil(input, max_input, '\n', stdin) == -1) {
            printf("Invalid Game\n");
            continue;
        }
        choice = strtol(input, NULL, 10);
        switch(choice) {
        case 1:
            rps(player);
            break;
        case 2:
            hi_lo(player);
            break;
        case 3:
            ttt(player, whose_turn);
            whose_turn *= -1;
            break;
        case 4:
            player_set = 0;
            printf("See you next time, %s\n", player->name);
            continue;
        default:
            printf("Invalid Game\n");
        }

        //if (player->num_ttt_consecutive_draws > 0) {
        if (player->num_ttt_consecutive_draws > 100 && player->num_rps_wins && player->num_hi_lo_wins) {
            printf("I've been beat. I realize now - the only winning move is not to play\n");
            printf("What say you?\n", player->name);
            if (!l_code)
                l_code = score_to_l_code(player->score);
            player->flair();
            printf("Just in time. I was able to brute force the l-code. l-code = %d\n", l_code);
        }
    }
    printf("Exited\n");
    return 0;
}

