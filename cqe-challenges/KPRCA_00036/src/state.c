/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "state.h"

#define MAX_STATES 1000

static unsigned int g_id = 0;
static state_t **g_all_states = NULL;

void init_trex()
{
    if (g_all_states)
        return;

    g_all_states = malloc(sizeof(state_t*) * MAX_STATES);
    g_id = 0;
}

void clear_trex() {
    unsigned int i;
    for (i = 0; i < g_id; i++)
        free(g_all_states[i]);

    g_id = 0;
}

state_t *create_state(unsigned char input)
{
    if (g_id >= MAX_STATES)
        return NULL;

    state_t *s0 = malloc(sizeof(state_t));
    s0->id = g_id;
    s0->input = input;
    s0->is_accepting_state = TRUE;
    s0->t1 = NULL;
    s0->t2 = NULL;
    s0->end_state = NULL;
    g_all_states[g_id++] = s0;

    return s0;
}


#define APPEND_STATE(_s1, _s2)                                      \
    do {                                                            \
        if ( _s1->end_state ) {                                     \
            _s1->end_state->is_accepting_state = FALSE;             \
            if( _s1->end_state->t1 )                                \
                _s1->end_state->t2 = _s2;                           \
            else                                                    \
                _s1->end_state->t1 = _s2;                           \
        } else  {                                                   \
            _s1->t1 = _s2;                                          \
        }                                                           \
        _s1->end_state = _s2->end_state ? _s2->end_state : _s2;     \
    } while(0);



state_t *op_concat(state_t *s1, state_t *s2)
{
    s1->is_accepting_state = FALSE;
    APPEND_STATE(s1, s2);

    return s1;
}


state_t *op_union(state_t *s1, state_t *s2)
{
    state_t *s0 = create_state(EPSILON);
    state_t *s3 = create_state(EPSILON);
    if (!s0 || !s3)
        return NULL;

    s0->is_accepting_state = FALSE;
    s0->t1 = s1;
    s0->t2 = s2;
    s0->end_state = s3;

    s1->is_accepting_state = FALSE;
    APPEND_STATE(s1, s3);
    s2->is_accepting_state = FALSE;
    APPEND_STATE(s2, s3);

    return s0;
}

state_t *op_star(state_t *s1)
{
    if (s1->end_state == s1)
        return s1;

    state_t *s0 = create_state(EPSILON);
    if (!s0)
        return NULL;

    s1->is_accepting_state = FALSE;
    APPEND_STATE(s1, s0);

    s0->t1 = s1;
    s0->end_state = s0;
    s0->is_accepting_state = TRUE;

    return s0;
}

state_t *op_qmark(state_t *s1)
{
    state_t *s0 = create_state(EPSILON);
    state_t *s2 = create_state(EPSILON);
    if (!s0 || !s2)
        return NULL;

    s0->is_accepting_state = FALSE;
    s0->t1 = s1;
    s0->t2 = s2;
    s0->end_state = s2;

    s1->is_accepting_state = FALSE;
    APPEND_STATE(s1, s2);

    return s0;
}

state_t *op_plus(state_t *s1)
{
    state_t *s2 = create_state(EPSILON);
    if (!s2)
        return NULL;

    s1->is_accepting_state = FALSE;
    APPEND_STATE(s1, s2);
    s2->t1 = s1;

    return s1;
}

