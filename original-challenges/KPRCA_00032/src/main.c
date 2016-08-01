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

#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "atree.h"
#include "io.h"

#define NUM_LEVELS 10

enum {
    CMD_QUIT,
    CMD_ADD_WORD,
    CMD_REMOVE_WORD,
    CMD_QUERY,
    CMD_QUERY_SUBSET,
    CMD_PLAY_GAME
};

enum {
    STATUS_SUCCESS,
    STATUS_ERROR
};

typedef struct {
    atree_t *tree;
} main_t;

int read_initial_words(main_t *state)
{
    unsigned int count, i;
    char **words;
    freqtab_t ftab;

    count = read_int();
    if (count >= UINT_MAX / sizeof(char *))
        return 0;

    words = malloc(sizeof(char *) * count);
    if (words == NULL)
        return 0;

    for (i = 0; i < count; i++)
    {
        words[i] = read_string();
        if (words[i] == NULL)
            goto error;

        if (strlen(words[i]) == 0)
            goto error;
    }

    ftab_init1(&ftab);
    for (i = 0; i < count; i++)
        ftab_add(&ftab, words[i]);

    state->tree = atree_init(&ftab);
    if (state->tree == NULL)
        goto error;

    for (i = 0; i < count; i++)
        atree_add(state->tree, words[i]);

//    free(words);
    return 1;

error:
//    for (i = 0; i < count; i++)
//        free(words[i]);
//    free(words);
    return 0;
}

void cmd_add_word(main_t *state)
{
    char *str = read_string();
    if (str == NULL)
    {
        write_int(STATUS_ERROR);
    }
    else
    {
        if (!atree_add(state->tree, str))
        {
            write_int(STATUS_ERROR);
            free(str);
        }
        else
        {
            write_int(STATUS_SUCCESS);
        }
    }
}

void cmd_remove_word(main_t *state)
{
    char *str = read_string();
    if (str == NULL)
    {
        write_int(STATUS_ERROR);
    }
    else
    {
        if (!atree_remove(state->tree, str))
        {
            write_int(STATUS_ERROR);
        }
        else
        {
            write_int(STATUS_SUCCESS);
        }
        free(str);
    }
}

static void sort_results(char **results, int count)
{
    int i, j;
    for (i = 1; i < count; i++)
    {
        char *a = results[i];
        for (j = i; j > 0; j--)
        {
            if (strcmp(results[j-1], a) <= 0)
                break;
            results[j] = results[j-1];
        }
        results[j] = a;
    }
}

void cmd_query(main_t *state, int subset)
{
    char *str, **results;
    str = read_string();
    if (str == NULL)
    {
        write_int(STATUS_ERROR);
    }
    else
    {
        if (subset)
            results = atree_query_subset(state->tree, str);
        else
            results = atree_query(state->tree, str);
        free(str);

        if (results == NULL)
        {
            write_int(STATUS_ERROR);
        }
        else
        {
            char **it;
            int count = 0;
            for (it = results; *it != NULL; it++)
                count++;
            write_int(STATUS_SUCCESS);
            write_int(count);
            sort_results(results, count);
            for (it = results; *it != NULL; it++)
                write_string(*it);
        }
    }
}

void cmd_play_game(main_t *state)
{
    int level;
    const char *words[NUM_LEVELS];

    if (atree_count(state->tree) < NUM_LEVELS)
    {
        write_int(STATUS_ERROR);
        return;
    }

    for (level = 0; level < NUM_LEVELS; level++)
    {
        char **answers, **it;
        int total, solved, goal, i;
        // choose a random word without repeat
        do {
            words[level] = atree_random(state->tree);
            for (i = 0; i < level; i++)
            {
                if (words[i] == words[level])
                {
                    words[level] = NULL;
                    break;
                }
            }
        } while (words[level] == NULL);

        answers = atree_query(state->tree, words[level]);
        if (answers == NULL)
        {
            write_int(STATUS_ERROR);
            break;
        }

        solved = total = 0;
        for (it = answers; *it != NULL; it++)
            total++;
        goal = total / 2;
        if (goal == 0)
            goal = 1;

        write_string(words[level]);
        write_int(goal);

        while (solved < goal)
        {
            char *str = read_string();
            if (str == NULL)
                return;

            for (it = answers; it < answers + total; it++)
            {
                if (*it && strcasecmp(str, *it) == 0)
                {
                    solved++;
                    *it = NULL;
                    write_int(solved);
                    break;
                }
            }

            free(str);
        }

        free(answers);
    }

    write_int(STATUS_SUCCESS);
}

int main()
{
    main_t state;
    memset(&state, 0, sizeof(main_t));

    while (!read_initial_words(&state))
    {
        write_int(STATUS_ERROR);
    }
    write_int(STATUS_SUCCESS);

    while (1)
    {
        int cmd = read_int();
        if (cmd == CMD_QUIT)
            break;

        switch (cmd)
        {
        case CMD_ADD_WORD:
            cmd_add_word(&state);
            break;
        case CMD_REMOVE_WORD:
            cmd_remove_word(&state);
            break;
        case CMD_QUERY:
            cmd_query(&state, 0);
            break;
        case CMD_QUERY_SUBSET:
            cmd_query(&state, 1);
            break;
        case CMD_PLAY_GAME:
            cmd_play_game(&state);
            break;
        default:
            write_int(STATUS_ERROR);
            break;
        }
    }
    write_int(STATUS_SUCCESS);

    return 0;
}
