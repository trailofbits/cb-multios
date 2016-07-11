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
#include "joke.h"

#ifndef SERVICE_H
#define SERVICE_H

// Messages
#define INITMSG "This is the Chuck Norris (joke) Management Protocol (CNMP).\n" \
        "We know you need a break, so take some time and amuse yourself. " \
        "If you have a good Chuck Norris joke, you can add it to our listing.\n"
#define CHOICES "Enter one of these commands:\n" \
        "  LIST  - list all jokes\n" \
        "  ADD   - upload your own joke\n" \
        "  COUNT - find out how many jokes we have to offer you\n" \
        "  SHOW  - show a joke\n" \
        "  MENU  - display this menu\n" \
        "  HELP  - you gotta be kididin' me!\n" \
        "  QUIT  - take off eh?\n"
#define ADDJOKE "So, you think you have a good Chuck Norris joke? "\
        "Give me the joke string already....\n"
#define JOKESTORED "Joke added. Thanks for sharing! Your joke is ID: ~n\n"
#define BADJOKEERROR "\nThat joke you gave me is crap! " \
        "For that, you get to start over!\n"
#define JOKEDBFULL "Lordy, lordy, I've had enough Chuck Norris jokes. Go away.\n"
#define SHOWWHICHID "Give me the ID of the joke you want to read. Or better yet, " \
        "enter RANDOM and I'll choose one for you.\n" 
#define BADIDERROR "\nWhat do you take me for? That ID is bogus! Try again.\n"
#define BADSTRERROR "\nAre you kidding me? What is that garbage? "\
        "I thought my instructions were pretty straight forward. Try again.\n"
#define EASTEREGG "Congratulations, you are the only person in the past, present " \
        "or future to beat Chuck Norris.\n"
#define INSULT "Is our menu so extensive that you cannot remember all of the commands? " \
        "Here, let me jog all 6 of your neurons:\n"
#define JOKECOUNT "Current CNMP joke count is ~n. Enjoy!\n"
#define BYEBYE "Thanks for the laughs. Come back soon!\n"

// Prompts
#define ROOTPROMPT "> "
#define ADDPROMPT "ADD> "
#define SHOWPROMPT "SHOW> "




int prompt_user(char* prompt_str, char* res_buf, size_t res_buf_size);
int send_random_joke(jokedb_struct *jokedb);
int send_joke(joke_struct *joke);
int send_all_jokes(jokedb_struct *jokedb);
int do_list(jokedb_struct *jokedb);
int do_add(jokedb_struct *jokedb);
int do_show(jokedb_struct *jokedb);
int do_menu();
int do_help();

#endif
