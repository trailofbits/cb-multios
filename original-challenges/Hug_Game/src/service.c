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
#include <libcgc.h>
#include "gamestate.h"
#include "libc.h"
#include "utility.h"

extern void coinflip();
extern void hangman();
extern void dicegame();
extern void war();

gamestate *state;

int main() {
    char choice[16];
    int seed;
    allocate(0x1000, 1, (void **)&state);
    if(state == NULL) {
        put("Could not allocate space for gamestate. Terminating.");
        _terminate(-1);
    }
    state->hugcount = 1000;
    put("Welcome to the hug gambling server.\n");
    put("What is your name?\n");
    bzero(state->name, 256);
    recvUntil(0, state->name, 256, '\n');
    put("Hi ");
    put(state->name);
    put(". ");
    memcpy((char *)&seed, state->name, 4);
    hugsrand(state, seed);
    while(state->hugcount > 0) {
        if(state->hugcount > 1000000)
            state->hugcount = 1000000;
        put("You have ");
        put(itoa(state->hugcount));
        put(" hugs. Shall we play a game?\n1. Coin Flip\n2. Hangman\n3. Dice game\n4. War\nq. Quit\n");
        bzero(choice, 16);
        recvUntil(0, choice, 15, '\n');
        switch(choice[0])
        {
            case '1':
                coinflip();
                break;
            case '2':
                hangman();
                break;
            case '3':
                dicegame();
                break;
            case '4':
                war();
                break;
            case 'q':
                put("Thanks for playing! Don't spend all your hugs in one place.\n");
                _terminate(0);
        }
    }
    put("You're all out of hugs :(. Thanks for playing.\n");

}
