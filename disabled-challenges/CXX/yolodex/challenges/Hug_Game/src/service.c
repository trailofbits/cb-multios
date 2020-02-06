/*

Author: Dustin Fraze (df@cromulence.com)

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "libcgc.h"
#include "cgc_gamestate.h"
#include "cgc_libc.h"
#include "cgc_utility.h"

extern void cgc_coinflip();
extern void cgc_hangman();
extern void cgc_dicegame();
extern void cgc_war();

gamestate *state;

int main(int cgc_argc, char *cgc_argv[]) {
    char choice[16];
    int seed;
    cgc_allocate(0x1000, 1, (void **)&state);
    if(state == NULL) {
        cgc_put("Could not allocate space for gamestate. Terminating.");
        cgc__terminate(-1);
    }
    state->hugcount = 1000;
    cgc_put("Welcome to the hug gambling server.\n");
    cgc_put("What is your name?\n");
    cgc_bzero(state->name, 256);
    cgc_recvUntil(0, state->name, 256, '\n');
    cgc_put("Hi ");
    cgc_put(state->name);
    cgc_put(". ");
    cgc_memcpy((char *)&seed, state->name, 4);
    cgc_hugsrand(state, seed);
    while(state->hugcount > 0) {
        if(state->hugcount > 1000000)
            state->hugcount = 1000000;
        cgc_put("You have ");
        cgc_put(cgc_itoa(state->hugcount));
        cgc_put(" hugs. Shall we play a game?\n1. Coin Flip\n2. Hangman\n3. Dice game\n4. War\nq. Quit\n");
        cgc_bzero(choice, 16);
        cgc_recvUntil(0, choice, 15, '\n');
        switch(choice[0])
        {
            case '1':
                cgc_coinflip();
                break;
            case '2':
                cgc_hangman();
                break;
            case '3':
                cgc_dicegame();
                break;
            case '4':
                cgc_war();
                break;
            case 'q':
                cgc_put("Thanks for playing! Don't spend all your hugs in one place.\n");
                cgc__terminate(0);
        }
    }
    cgc_put("You're all out of hugs :(. Thanks for playing.\n");

}
