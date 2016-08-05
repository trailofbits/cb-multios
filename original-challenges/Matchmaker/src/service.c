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

#include "conv.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "dfa.h"

struct {
    char line[sizeof(struct dfa) / 2];
    struct dfa dfa;
} state;

static unsigned int
calculate_csum(char *line)
{
    unsigned int ret = 0;
    unsigned int i, len;

    for (i = 0; i < 1024; i++)
        ret ^= get_flag_byte(i);

    len = strlen(line);
    for (i = 0; i < len; i++)
        ret ^= line[i];

    return ret;
}

static void __attribute__((regparm(1)))
default_onmatch(void *data)
{
    printf("Got a match! \"%s\"\n", (char *)data);
}

static void __attribute__((regparm(1)))
length_onmatch(void *data)
{
    printf("Got a match of length %u\n", strlen((char *)data));
}

static void __attribute__((regparm(1)))
xor_onmatch(void *data)
{
    char *p;
    unsigned int sum = 0;

    for (p = data; *p; p++)
        sum ^= *p;

    printf("Checksum: %u\n", sum);
}

static void __attribute__((regparm(1)))
magic_onmatch(void *data)
{
    char *p;
    unsigned int sum = 0, guess = UINT_MAX, magic;

    for (p = data; *p; p++)
        sum ^= *p;

#ifdef PATCHED_2
    magic = sum;
#else
    magic = ((unsigned char *)FLAG_PAGE)[sum];
#endif

    printf("I'm thinking of a magic number, can you guess it?!?!\n");
    while (guess != magic) {
        if (fread_until(state.line, '\n', sizeof(state.line), stdin) == EXIT_FAILURE)
            goto fail;

        if ((p = strchr(state.line, '\n')) != NULL)
            *p = '\0';
        else
            return;

        if (strtou(state.line, 10, &guess) == EXIT_FAILURE)
            goto fail;

        if (guess < magic)
            printf("Haha, too small!\n");
        else if (guess > magic)
            printf("Whoa, too big\n");
        else {
            printf("Just right!\n");
            break;
        }

fail:
        printf("WRONG!\n");
        continue;
    }
}

int
main(void)
{
    char *p;
    int ret, parsing_dfa = 1;
    onmatch_handler onmatch = default_onmatch;

    dfa_init(&state.dfa);

    while (1) {
        memset(state.line, '\0', sizeof(state.line));
        if (fread_until(state.line, '\n', sizeof(state.line), stdin) == EXIT_FAILURE)
            return EXIT_FAILURE;

        if ((p = strchr(state.line, '\n')) != NULL)
            *p = '\0';
        else
            return EXIT_FAILURE;

        // Pre-command checking, note that this means you can't match these
        // commands in a parser
        if (strcmp(state.line, "quit") == 0)
            break;

        if (strcmp(state.line, "reset") == 0) {
            printf("Please re-enter state machine\n");
            dfa_init(&state.dfa);
            parsing_dfa = 1;
            continue;
        }

        if (strcmp(state.line, "example") == 0) {
            if (dfa_give_example(&state.dfa, state.line, 40) != EXIT_SUCCESS)
                printf("Error, are you done initializing?\n");
            else
                printf("Here's an example: \"%s\"\n", state.line);
            continue;
        }

        if (strncmp(state.line, "onmatch ", sizeof("onmatch ") - 1) == 0) {
            p = state.line + sizeof("onmatch ") - 1;

            if (strcmp(p, "default") == 0)
                onmatch = default_onmatch;
            else if (strcmp(p, "length") == 0)
                onmatch = length_onmatch;
            else if (strcmp(p, "xor") == 0)
                onmatch = xor_onmatch;
            else if (strcmp(p, "magic") == 0)
                onmatch = magic_onmatch;
            else {
                printf("Unrecognized action\n");
                continue;
            }

            dfa_update_onmatch(&state.dfa, onmatch, state.line);
            printf("Match action updated\n");
            continue;
        }

        if (parsing_dfa) {
            ret = dfa_parse_desc(&state.dfa, state.line, onmatch, state.line);
            if (ret == EXIT_FAILURE) {
                printf("Invalid\n");
                continue;
            } else if (ret == 1) {
                printf("Ok, matching input now\n");
                parsing_dfa = 0;
            }
        } else {
            dfa_reset(&state.dfa);
            for (p = state.line; *p; p++)
                if ((ret = dfa_process_input(&state.dfa, *p)) != 0)
                    break;

            if (ret == 0 || ret == EXIT_FAILURE)
                printf("No match :( \"%s\"\n", state.line);
            else
                printf("%x\n", calculate_csum(state.line));
        }
    }

    return EXIT_SUCCESS;
}

