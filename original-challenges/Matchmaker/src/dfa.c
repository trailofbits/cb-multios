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

#include "bitset.h"
#include "conv.h"
#include "stdlib.h"
#include "string.h"

#include "dfa.h"

#define GET_CURRENT_INDEX(dfa) ((unsigned char)((dfa)->current - &(dfa)->states[0]))

void
dfa_init(struct dfa *dfa)
{
    unsigned int i, j;

    for (i = 0; i < MAX_NUM_STATES; i++) {
        for (j = 0; j < 256; j++)
            dfa->states[i].transitions[j] = SENTINEL;

        dfa->states[i].onmatch = NULL;
        dfa->states[i].data = NULL;
    }

    bitset_init(&dfa->accept.bitset, MAX_NUM_STATES);
    dfa->ready = 0;
    dfa->current = NULL;
}

void
dfa_reset(struct dfa *dfa)
{
    dfa->current = &dfa->states[0];
}

void
dfa_update_onmatch(struct dfa *dfa, onmatch_handler onmatch, void *data)
{
    unsigned int i;

    for (i = 0; i < MAX_NUM_STATES; i++) {
        if (dfa->states[i].onmatch != NULL) {
            dfa->states[i].onmatch = onmatch;
            dfa->states[i].data = data;
        }
    }
}

static int
validate_dfa(struct dfa *dfa, unsigned char last_state)
{
    unsigned char dest_state;
    unsigned int i, j;

    for (i = 0; i < last_state; i++)
        for (j = 0; j < 256; j++) {
            dest_state = dfa->states[i].transitions[j];
            if (dest_state != SENTINEL && dest_state > last_state)
                return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}

int
dfa_parse_desc(struct dfa *dfa, char *line, onmatch_handler onmatch, void *data)
{
    char *dest_state_name;
    unsigned int dest_state;

    if (strncmp(line, "state", sizeof("state") - 1) == 0) {
        dfa->current = (dfa->current == NULL ? &dfa->states[0] : dfa->current + 1);
        // Don't let our start state be an accept state
        if (strcmp(line + sizeof("state ") - 1, "accept") == 0 && dfa->current != &dfa->states[0]) {
            dfa->current->onmatch = onmatch;
            dfa->current->data = data;
            return bitset_set_bit(&dfa->accept.bitset, GET_CURRENT_INDEX(dfa));
        }

        return EXIT_SUCCESS;
    } else if (strcmp(line, "done") == 0) {
        if (validate_dfa(dfa, GET_CURRENT_INDEX(dfa) + 1) != EXIT_SUCCESS)
            return EXIT_FAILURE;

        dfa->ready = 1;
        dfa->current = &dfa->states[0];
        return 1;
    } else if (strncmp(line, "transition ", sizeof("transition ") - 1) == 0) {
        line += sizeof("transition") - 1;
        *line++ = '\0';

        if ((dest_state_name = strrchr(line, ' ')) == NULL)
            return EXIT_FAILURE;

        if (strtou(dest_state_name + 1, 10, &dest_state) == EXIT_FAILURE || dest_state > MAX_NUM_STATES)
            return EXIT_FAILURE;

        // '\0' and '\n' is invalid due to reading in statements a line at a time,
        // anything else goes
        while (line != dest_state_name)
            dfa->current->transitions[(unsigned int)*line++] = dest_state;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int
dfa_process_input(struct dfa *dfa, char c)
{
    if (!dfa->ready)
        return EXIT_FAILURE;

    if ((unsigned char)dfa->current->transitions[(unsigned int)c] == SENTINEL)
        return EXIT_FAILURE;

    dfa->current = &dfa->states[dfa->current->transitions[(unsigned int)c]];
    if (bitset_get_bit(&dfa->accept.bitset, GET_CURRENT_INDEX(dfa)) == 1) {
        if (dfa->current->onmatch)
            dfa->current->onmatch(dfa->current->data);

        return 1;
    }

    return 0;
}

int
dfa_give_example(struct dfa *dfa, char *str, size_t len)
{
    int ret = EXIT_FAILURE, can_accept = 0;
    struct state *old_current = dfa->current;
    size_t cur_len = 0;
    unsigned int i, rnd, num_transitions = 0;
    char c;

    dfa->current = &dfa->states[0];

    if (!dfa->ready)
        goto out;

    for (i = 0; i < MAX_NUM_STATES; i++) {
        if (bitset_get_bit(&dfa->accept.bitset, i) == 1) {
            can_accept = 1;
            break;
        }
    }

    if (!can_accept)
        goto out;

    while (cur_len < len - 1 &&
            bitset_get_bit(&dfa->accept.bitset, GET_CURRENT_INDEX(dfa)) == 0) {

        num_transitions = 0;
        for (i = 0; i < 256; i++)
            if ((unsigned char)dfa->current->transitions[i] != SENTINEL)
                num_transitions++;

        if (num_transitions == 0)
            goto out;

        c = '\0';
        rnd = rand() % num_transitions;

        for (i = 0; i < 256; i++) {
            if ((unsigned char)dfa->current->transitions[i] != SENTINEL) {
                if (rnd == 0) {
                    c = (char)i;
                    break;
                }
                rnd--;
            }
        }
            
        if (c == '\0')
            goto out;

        str[cur_len++] = c;
        dfa->current = &dfa->states[(unsigned int)dfa->current->transitions[c]];
    }

    str[cur_len++] = '\0';

    if (bitset_get_bit(&dfa->accept.bitset, GET_CURRENT_INDEX(dfa)) == 1)
        ret = EXIT_SUCCESS;

out:
    dfa->current = old_current;
    return ret;
}

