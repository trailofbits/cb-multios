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

#include "conv.h"
#include "stdio.h"
#include "string.h"

#include "games.h"

struct monster {
    char *name;
    unsigned char capture_chance, run_chance;
    void (*set_nickname)(size_t, unsigned int);
};

static void
set_nickname(size_t index, unsigned int name)
{
    char name_[sizeof(unsigned int) + 1] = { 0 };
    int i;

#ifdef PATCHED_4
    if (index > 6) {
        printf("Nice try\n");
        return;
    }
#endif

    memcpy(name_, &name, sizeof(unsigned int));

    for (i = 0; i < 6; i++) {
        if (game_state.games.safari_zone.party[i] == 0) {
            printf("%s has joined your party\n", name_);
            game_state.games.safari_zone.party[i] = index;
            return;
        }
    }

    printf("%s was transferred to box 1 in your PC\n", name_);
}

static void
glitch_items(size_t index, unsigned int name)
{
    char buf[40] = { 0 };
    unsigned int item;
    void __attribute__((regparm(1))) (*fnptr)(unsigned int);

    printf("BZZZT!\n");
    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return;
    if (strlen(buf) == 0 || strtou(buf, 16, &item) == EXIT_FAILURE)
        return;

    fnptr = (void *)(name | 0xf0000000);
    fnptr(item);
}

static struct monster data[] = {
#ifdef PATCHED_3
    { "Missingno.", 255, 0, set_nickname },
#else
    { "Missingno.", 255, 0, glitch_items },
#endif
    { "Pidgeon", 128, 128, set_nickname },
    { "RegularRat", 128, 128, set_nickname },
    { "ElectricRat", 128, 128, set_nickname },
    { "Centipede-Thing", 128, 128, set_nickname },
    { "Caterpillar", 128, 128, set_nickname },
    { "Carp", 128, 128, set_nickname },
    { "Mewthree", 255, 0, set_nickname }
};

int
do_safari_zone(void)
{
    char buf[40] = { 0 };
    unsigned int move, round, name;
    size_t num_monsters = sizeof(data) / sizeof(data[0]);
    size_t index = game_state.games.safari_zone.encounter_data + 1;
    struct monster *monster;
    unsigned char capture_chance, run_chance;

    printf("Welcome to the Safari Zone!\n");

    if (!check_cookie(game_state.games.gallon_challenge.cookie))
        return EXIT_FAILURE;

    if (index > num_monsters - 1) {
        printf("Nothing happened...\n");
        return EXIT_SUCCESS;
    }

    monster = &data[index];
    game_state.games.safari_zone.encounter_data = get_flag_byte(index) % (num_monsters - 2);
    capture_chance = monster->capture_chance;
    run_chance = monster->run_chance;
    round = 0;

    printf("A wild %s has appeared!\n", monster->name);
    while (1) {
        printf("What to do?\n"
                "1. Ball\n"
                "2. Rock\n"
                "3. Bait\n"
                "4. Run\n\n");

        if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (strlen(buf) == 0 || strtou(buf, 16, &move) == EXIT_FAILURE)
            return EXIT_FAILURE;

        if (round > 10 || (round > 0 && run_chance >= get_flag_byte(round))) {
            printf("%s got away :(\n", monster->name);
            return EXIT_SUCCESS; 
        }
        round++;

        if (move == 1) {
            if (capture_chance >= get_flag_byte(round++))
                break;
            else
                printf("Darn! Almost had it!\n");
        } else if (move == 2) {
            capture_chance *= 2;
            run_chance *= 2;
        } else if (move == 3) {
            capture_chance /= 2;
            run_chance /= 2;
        } else if (move == 4) {
            printf("Got away safely!\n");
            return EXIT_SUCCESS;
        }
    }

    printf("Congratulations, you've caught %s!\n"
            "Please enter a nickname:\n", monster->name);

    do {
        if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
            continue;
        if (strlen(buf) == 0 || strtou(buf, 16, &name) == EXIT_FAILURE)
            continue;

        break;
    } while(1);

    monster->set_nickname(index, name);

    return EXIT_SUCCESS;
}

