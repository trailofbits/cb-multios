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

#ifndef SERVICE_H
#define SERVICE_H

// Messages
#define INITMSG "Welcome to Tick-A-Tack.\n"
#define INITCHOICES "Make your selection:\n" \
		        "PLAY\n" \
        		"QUIT\n"
#define REPLAYCHOICES "Make your selection:\n" \
        		"PLAY AGAIN\n" \
        		"START OVER\n" \
        		"QUIT\n"
#define WAT "Wat?\n"
#define COMPMOVE "Computer's move: ~n ~n.\n"
#define CHARCHOICE "P goes first. Do you want P or Q?\n"
#define MAKEMOVE "It's your move. Enter 'row col'\n"
#define BADMOVE "Invalid coordinates!\n"
#define WIN "Congratulations! You Win!\n"
#define LOSE "Nice effort. Maybe next time.\n"
#define SCORE "~n wins. ~n losses.\n"
#define GO "Game on!\n"
#define BADSTRERROR "\nI don't think that means what you think it means.\n"
#define BYEBYE "Give up?. Don't be a stranger!\n"

// Prompts
#define ROOTPROMPT "$ "

void do_menu(size_t replay);
void do_quit();
void do_select_char();
void send_current_board();
void make_move();
void send_game_results();
void do_play();

#endif
