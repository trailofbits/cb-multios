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
#include <stdio.h>
#include <libcgc.h>
#include "hi_lo_game.h"

#define UPPER_RAND_MAX 0xFFFF

static const int *secret = (const int *)0x4347C000;
static int idx = 0;

static int set_bits_high(unsigned int num)
{
    int bits = 0;
    while (num != 0) {
        bits++;
        num >>= 1;
    }
    while(bits) {
        num <<= 1;
        num |= 1;
        bits--;
    }

    return num;
}

static int get_random(unsigned int *upper_limit)
{
    idx %= 1024;
    int max_input = 256;
    int upper = UPPER_RAND_MAX + 1;
    unsigned int winner = secret[idx++];
    char *input = malloc(max_input);
#ifdef PATCHED_1
    while (upper < 0 || upper > UPPER_RAND_MAX) {
#else
    while (upper > UPPER_RAND_MAX) {
#endif
        printf("Enter max value (Default=%d): ", UPPER_RAND_MAX);
        if (freaduntil(input, max_input, '\n', stdin) == -1)
            continue;
        upper = strtol(input, NULL, 10);
        upper = set_bits_high(upper);
    }

    if (upper == 0) {
        upper = UPPER_RAND_MAX;
    } else {
        printf("We've changed the max value to %d.\n", upper);
        printf("Keep in mind only the games using the default max value are scored.\n");
    }

    if (winner > upper)
        winner &=  upper;

    free(input);
    *upper_limit = upper;
    return winner;
}

int play_hi_lo()
{
    int max_input = 256;
    int guess = 0;

    unsigned int upper_limit;
    int winning_number = get_random(&upper_limit);
    unsigned int guesses_left = log2f(upper_limit) + 1;
    char *input = malloc(max_input);
    while (guesses_left) {
        printf("Guess the number [%d guesses left]: ", guesses_left);
        if (freaduntil(input, max_input, '\n', stdin) == -1)
            continue;
        guess = strtol(input, NULL, 10);
        if (guess < winning_number) {
            printf("Too Low\n");
        } else if (guess > winning_number) {
            printf("Too High\n");
        } else {
            printf("You won!\n");
            free(input);
            if (upper_limit == UPPER_RAND_MAX)
                return 1000;
            else
                return 0;
        }
        guesses_left--;
    }

    printf("Sorry, you lost. Try practicing with a lower max value.\n");
    //printf("The number was: %d\n", winning_number);
    free(input);
    return 0;
}
