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

#ifndef DFA_H_
#define DFA_H_

#include "bitset.h"

// Use state 0xff as a sentinel value
#define MAX_NUM_STATES 255
#define SENTINEL (MAX_NUM_STATES)

typedef __attribute__((regparm(1))) void (*onmatch_handler)(void *);

struct state {
    onmatch_handler onmatch;
    void *data;
#ifdef PATCHED_1
    unsigned char transitions[256];
#else
    char transitions[256];
#endif
};

struct dfa {
    int ready;
    struct state *current;
    struct state states[MAX_NUM_STATES];
    struct {
        struct bitset bitset;
        unsigned char bits[(MAX_NUM_STATES + 1) / 8];
    } accept;
};

/**
 * Initialize a DFA.
 *
 * @param dfa The DFA to initialize
 */
void dfa_init(struct dfa *dfa);

/**
 * Reset an initialized DFA to its start state.
 *
 * @param dfa The DFA to reset
 */
void dfa_reset(struct dfa *dfa);

/**
 * Update the onmatch event handler for all accept states in a DFA.
 *
 * @param dfa The DFA to update
 * @param onmatch The new event handler
 */
void dfa_update_onmatch(struct dfa *dfa, onmatch_handler onmatch, void *data);

/**
 * Parse a line describing the structure of a DFA and update the given DFA.
 *
 * @param dfa The DFA to update
 * @param line The line to parse, one of "state", "transition <symbols>
 *      <state>", or "done"
 * @param onmatch The event handler to call on a match
 * @return 1 if parsing is done, EXIT_SUCCESS on success, EXIT_FAILURE on
 *      failure
 */
int dfa_parse_desc(struct dfa *dfa, char *line, onmatch_handler onmatch, void *data);

/**
 * Parse an input to see if it matches the language accepted by a DFA.
 *
 * @param dfa The DFA to check against
 * @c The symbol to process
 * @return 1 if accepted, 0 if more data needed, EXIT_FAILURE if rejected
 */
int dfa_process_input(struct dfa *dfa, char c);

/**
 * Give an example of a string accepted by the DFA.
 *
 * @param dfa The DFA to examine
 * @param str The destination string
 * @param len The maximum length of the string
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int dfa_give_example(struct dfa *dfa, char *str, size_t len);

#endif /* DFA_H_ */

