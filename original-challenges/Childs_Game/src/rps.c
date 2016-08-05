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
#include <string.h>
#include "rps.h"

enum {HAMMER=0, SHEET=1, SHEERS=2, BAD_CHOICE=8};

static const unsigned char *secret = (const unsigned char *)0x4347C000;
static int idx = 0;

int play_rps()
{
    idx %= 4096;
    int max_input = 256;
    unsigned char computer_choice = secret[idx++] % 3;
    unsigned char human_choice = BAD_CHOICE;
    char *input = malloc(max_input);

    while (human_choice == BAD_CHOICE) {
        printf("Choose [HAMMER, SHEET, SHEERS]: ");
        if (freaduntil(input, max_input, '\n', stdin) == -1)
            continue;
        if (strcmp(input, "HAMMER") == 0)
            human_choice = HAMMER;
        else if (strcmp(input, "SHEET") == 0)
            human_choice = SHEET;
        else if (strcmp(input, "SHEERS") == 0)
            human_choice = SHEERS;
        else
            human_choice = BAD_CHOICE;
    }
    free(input);

    switch(human_choice) {
    case HAMMER:
        printf("HAMMER v ");
        switch(computer_choice) {
        case HAMMER:
            printf("HAMMER\n");
            printf("It's a tie!\n");
            return 0;
        case SHEET:
            printf("SHEET\n");
            printf("You Lose.\n");
            return 0;
        case SHEERS:
            printf("SHEERS\n");
            printf("You Win!\n");
            return 1000;
        }
    case SHEET:
        printf("SHEET v ");
        switch(computer_choice) {
        case HAMMER:
            printf("HAMMER\n");
            printf("You Win!\n");
            return 1000;
        case SHEET:
            printf("SHEET\n");
            printf("It's a tie!\n");
            return 0;
        case SHEERS:
            printf("SHEERS\n");
            printf("You Lose.\n");
            return 0;
        }
    case SHEERS:
        printf("SHEERS v ");
        switch(computer_choice) {
        case HAMMER:
            printf("HAMMER\n");
            printf("You Lose.\n");
            return 0;
        case SHEET:
            printf("SHEET\n");
            printf("You Win!\n");
            return 1000;
        case SHEERS:
            printf("SHEERS\n");
            printf("It's a tie!\n");
            return 0;
        }
    }

    return 0;
}

