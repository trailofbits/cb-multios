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

#include "libcgc.h"

#include "cgc_conv.h"
#include "cgc_limits.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_dfa.h"

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
        ret ^= cgc_get_flag_byte(i);

    len = cgc_strlen(line);
    for (i = 0; i < len; i++)
        ret ^= line[i];

    return ret;
}

static void __attribute__((regparm(1)))
cgc_default_onmatch(void *data)
{
    cgc_printf("Got a match! \"%s\"\n", (char *)data);
}

static void __attribute__((regparm(1)))
cgc_length_onmatch(void *data)
{
    cgc_printf("Got a match of length %u\n", cgc_strlen((char *)data));
}

static void __attribute__((regparm(1)))
cgc_xor_onmatch(void *data)
{
    char *p;
    unsigned int sum = 0;

    for (p = data; *p; p++)
        sum ^= *p;

    cgc_printf("Checksum: %u\n", sum);
}

static void __attribute__((regparm(1)))
cgc_magic_onmatch(void *data)
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

    cgc_printf("I'm thinking of a magic number, can you guess it?!?!\n");
    while (guess != magic) {
        if (cgc_fread_until(state.line, '\n', sizeof(state.line), cgc_stdin) == EXIT_FAILURE)
            goto fail;

        if ((p = cgc_strchr(state.line, '\n')) != NULL)
            *p = '\0';
        else
            return;

        if (cgc_strtou(state.line, 10, &guess) == EXIT_FAILURE)
            goto fail;

        if (guess < magic)
            cgc_printf("Haha, too small!\n");
        else if (guess > magic)
            cgc_printf("Whoa, too big\n");
        else {
            cgc_printf("Just right!\n");
            break;
        }

fail:
        cgc_printf("WRONG!\n");
        continue;
    }
}

int
main(int cgc_argc, char *cgc_argv[])
{
    char *p;
    int ret, parsing_dfa = 1;
    onmatch_handler onmatch = cgc_default_onmatch;

    cgc_dfa_init(&state.dfa);

    while (1) {
        cgc_memset(state.line, '\0', sizeof(state.line));
        if (cgc_fread_until(state.line, '\n', sizeof(state.line), cgc_stdin) == EXIT_FAILURE)
            return EXIT_FAILURE;

        if ((p = cgc_strchr(state.line, '\n')) != NULL)
            *p = '\0';
        else
            return EXIT_FAILURE;

        // Pre-command checking, note that this means you can't match these
        // commands in a parser
        if (cgc_strcmp(state.line, "quit") == 0)
            break;

        if (cgc_strcmp(state.line, "reset") == 0) {
            cgc_printf("Please re-enter state machine\n");
            cgc_dfa_init(&state.dfa);
            parsing_dfa = 1;
            continue;
        }

        if (cgc_strcmp(state.line, "example") == 0) {
            if (cgc_dfa_give_example(&state.dfa, state.line, 40) != EXIT_SUCCESS)
                cgc_printf("Error, are you done initializing?\n");
            else
                cgc_printf("Here's an example: \"%s\"\n", state.line);
            continue;
        }

        if (cgc_strncmp(state.line, "onmatch ", sizeof("onmatch ") - 1) == 0) {
            p = state.line + sizeof("onmatch ") - 1;

            if (cgc_strcmp(p, "default") == 0)
                onmatch = cgc_default_onmatch;
            else if (cgc_strcmp(p, "length") == 0)
                onmatch = cgc_length_onmatch;
            else if (cgc_strcmp(p, "xor") == 0)
                onmatch = cgc_xor_onmatch;
            else if (cgc_strcmp(p, "magic") == 0)
                onmatch = cgc_magic_onmatch;
            else {
                cgc_printf("Unrecognized action\n");
                continue;
            }

            cgc_dfa_update_onmatch(&state.dfa, onmatch, state.line);
            cgc_printf("Match action updated\n");
            continue;
        }

        if (parsing_dfa) {
            ret = cgc_dfa_parse_desc(&state.dfa, state.line, onmatch, state.line);
            if (ret == EXIT_FAILURE) {
                cgc_printf("Invalid\n");
                continue;
            } else if (ret == 1) {
                cgc_printf("Ok, matching input now\n");
                parsing_dfa = 0;
            }
        } else {
            cgc_dfa_reset(&state.dfa);
            for (p = state.line; *p; p++)
                if ((ret = cgc_dfa_process_input(&state.dfa, *p)) != 0)
                    break;

            if (ret == 0 || ret == EXIT_FAILURE)
                cgc_printf("No match :( \"%s\"\n", state.line);
            else
                cgc_printf("%x\n", calculate_csum(state.line));
        }
    }

    return EXIT_SUCCESS;
}

