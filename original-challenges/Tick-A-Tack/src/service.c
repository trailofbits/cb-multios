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
#include "libc.h"
#include "tt.h"
#include "service.h"

tt_game * game;


void do_menu(size_t replay) {
    if(replay) {
        send(REPLAYCHOICES, strlen(REPLAYCHOICES));
    } else {
        send(INITCHOICES, strlen(INITCHOICES));
    }
}

void do_quit() {
    send(BYEBYE, strlen(BYEBYE));
}

void do_select_char() {
    char choice[3] = { 0 };
    char player_char = '\0';

    while(!player_char) {
        send(CHARCHOICE, strlen(CHARCHOICE));
        prompt_user(ROOTPROMPT, choice, 3, BADSTRERROR);
        // syslog(LOG_DEBUG, "do_select_char: choice: ~o\n", choice[0]);

        if(choice[0] == 'P') {
            player_char = 'P';
        } else if (choice[0] == 'Q') {
            player_char = 'Q';
        } else {
            send(WAT, strlen(WAT));            
        }
    }
    set_player_chars(game->data, player_char);
    if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "player: ~o\n", player_char);}

}

void send_current_board() {
    // board must be a char buff[(17 * 8) + 1] = char buf[137]
    char board[137] = { 0 };
    make_board(game->data, board);

    send(board, strlen(board));
    if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, " board\n~c\n", board);}

}

// process a single move
void make_move() {
    int update_failed;
    tt_move_coords move = { 0 };
    char turn_coords[5] = { 0 }; // '<row> <col>\x07\0'
    // if player's turn, request coordinates
    if(is_players_turn(game->data)) {
        send(MAKEMOVE, strlen(MAKEMOVE));
        prompt_user(ROOTPROMPT, turn_coords, 5, BADSTRERROR);
        move.row = str2int(&turn_coords[0]);
        move.col = str2int(&turn_coords[2]);
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): player\n");}
    } else { 
        // else, select random, but valid coordinates for computer's move
        computer_move(game->data, &move);
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): computer\n");}
        // inform player where computer moved
        // build move message
        // 23 letters/\n/\0 + 2 for 2 single digit numbers
        char move_msg[25] = { 0 };
        snprintf(move_msg, 25, COMPMOVE, 
                    move.row, 
                    move.col); 

        // send computer move msg
        send(move_msg, strlen(move_msg));
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): send computer's move ~n ~n.\n", move.row, move.col);}

    }

    if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): coords '~n', '~n'\n", move.row, move.col);}
    // update board
    update_failed = update_board(game->data, &move);

    // if coordinates are bad, then board update failed
    if(update_failed) {
        // fuss at user
        if(is_players_turn(game->data)) {
            send(BADMOVE, strlen(BADMOVE));
        }
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): bad move\n");}

    } else {
        move_complete(game->data);
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "move_move(): good move\n");}
    }
}

// inform player if they won or lost
// as well as the current win/loss total
void send_game_results() {

    if(is_player_winner(game->data)) {
        // send congrats
        send(WIN, strlen(WIN));
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "send_game_results(): player wins\n");}
    } else {
        // send loss msg
        send(LOSE, strlen(LOSE));
        if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "send_game_results(): computer wins\n");}
    }

    // build score message
    // 15 letters/\n/\0 + 20 for 2 uint32 numbers
    char score_msg[35] = { 0 };
    snprintf(score_msg, 35, SCORE, 
                game->scores->player, 
                game->scores->computer); 

    // send final scores
    send(score_msg, strlen(score_msg));
    if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "~c", score_msg);}
}

// play one game and report final results
void do_play() {

    // select char
    do_select_char();

    // play game
    send(GO, strlen(GO));

    while(1) {

        // send board
        // send_current_board();

        // process a move
        make_move();

        // end game and update scores when
        //  no more moves or if have winner
        if(have_winner(game->data) || !have_moves_remaining(game->data)) {
            update_score(game);
            break;
        }
    }

    // send final board
    // send_current_board();

    send_game_results();
}

int main(void) {
    char choice[14];
    int choice_buf_size = 14;
    size_t replay = 0;
    void * memory_base = NULL;
    void * memory_idx = NULL;

    // send INITMSG
    send(INITMSG, strlen(INITMSG));

    while (1) {

        // init game state memory
        // allocate the space for game state and setup pointers
        if(memory_base && !game->scores->player && !game->scores->computer) {
#ifdef PATCHED
            game = (tt_game *)memory_base;
#else
            game = (tt_game *)memory_idx;
#endif

            if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "Set game state.\n");}
        } else if(!memory_base) {
            // alloc space and setup game state pointers
            int memory_size = sizeof(tt_game) + sizeof(tt_data) + sizeof(tt_scores);
            int result = 0;
            result = allocate(memory_size, 0, &memory_base);

            if(result)
                _terminate(99);

            memory_idx = memory_base;
            game = (tt_game *)memory_idx;
            memory_idx += sizeof(tt_game);
            game->data = (tt_data *)memory_idx;
            memory_idx += sizeof(tt_data);
            game->scores = (tt_scores *)memory_idx;
            if(LOGLEVEL == LOG_DEBUG) {syslog(LOG_DEBUG, "Allocate and set game state.\n");}
        }

        // initialize game data
        init_game_data(game->data);

        // send MENU
        do_menu(replay);
        // send ROOTPROMPT
        prompt_user(ROOTPROMPT, choice, choice_buf_size, BADSTRERROR);

        // receive user input and check for COMMAND
        if (streq(choice, "PLAY") == 0) {
            do_play(); // replay should be 0 here
            replay = 1;
        } else if (replay && streq(choice, "PLAY AGAIN") == 0) {
            do_play(); // replay should be 1 here
        } else if (replay && streq(choice, "START OVER") == 0) {
            replay = 0;
            reset_scores(game->scores);
        } else if (streq(choice, "QUIT") == 0) {
            do_quit();
            break;
        } else {
            send(WAT, strlen(WAT));
            break;
        }
    }

    return 0;
}


