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

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_trex.h"
#include "cgc_constants.h"

#define MAX_STATES 1000

static state_t **g_stack = NULL;
static int *g_states_checked = NULL;
static int *g_epsilon_loop = NULL;
static int g_state_length = 0;

static void cgc_debug_state_helper(state_t *state, int level) {
    if (!state)
        return;

    int i;
    unsigned char str[] = {0,0};
    str[0] = state->input;

    for (i = 0; i < g_state_length; i++)
        if (g_states_checked[i] == state->id)
            return;
    g_states_checked[g_state_length++] = state->id;

    for (i = 0; i < level; i++)
        cgc_printf("---");
    if(str[0] == EPSILON)
        cgc_printf(">%d", state->id);
    else
        cgc_printf(">%s", str);
    if (state->is_accepting_state)
        cgc_printf("::Accepting State Id::%d", state->id);
    cgc_printf("\n");

    cgc_debug_state_helper(state->t1, level + 1);
    cgc_debug_state_helper(state->t2, level + 1);
}

static int cgc_match_helper(state_t *state, unsigned char *str, int match_len, match_type_e match_type) {
    if (!state)
        return 0;

#ifdef PATCHED
    if (g_epsilon_loop[state->id] > cgc_strlen(str))
#else
    if (g_epsilon_loop[state->id] >= cgc_strlen(str))
#endif
        g_epsilon_loop[state->id] = cgc_strlen(str);
    else
        return 0;

    // Defaults to matching ALL
    int len1 = 0, len2 = 0, step = 1, i;
    if(state->input == EPSILON) {
        step = 0;
        if (match_type == PARTIAL) {
            if(state->is_accepting_state && match_len)
                return match_len;
        } else if(!*str && state->is_accepting_state && match_len) {
            return match_len;
        }
    } else if(*str == state->input) {
        if (match_type == PARTIAL) {
            if(state->is_accepting_state)
                return match_len + 1;
        } else if(!str[1] && state->is_accepting_state) {
            return match_len + 1;
        }
    } else {
        return 0;
    }

    if (match_type == PARTIAL)
        if(state->is_accepting_state && match_len)
            return match_len + 1;

    len2 = cgc_match_helper(state->t2, str + step, match_len + step, match_type);
    len1 = cgc_match_helper(state->t1, str + step, match_len + step, match_type);


    return len1 >= len2 ? len1 : len2;
}

void cgc_debug_state(state_t *state)
{
    if(g_states_checked == NULL)
        g_states_checked = cgc_malloc(sizeof(int) * MAX_STATES);
    g_state_length = 0;
    return cgc_debug_state_helper(state, 0);
}



void cgc_match(state_t *state, unsigned char *str, match_type_e match_type)
{
    int i, match_len = 0, end_of_str = 0;
    unsigned char *tstr = cgc_malloc(cgc_strlen(str) + 1), *line = tstr, *tline = tstr, *ptstr = tstr;
    cgc_memcpy(tstr, str, cgc_strlen(str) + 1);

    if(g_epsilon_loop == NULL)
        g_epsilon_loop = cgc_malloc(sizeof(int) * MAX_STATES);

    while(!end_of_str) {
        tstr++;
        if (*tstr == '\n' || *tstr == '\0') {
            end_of_str = *tstr ? 0 : 1;
            *tstr = '\0';
            while(!match_len && *tline) {
                for (i = 0; i < MAX_STATES; i++)
                    g_epsilon_loop[i] = MAX_STATES;

                match_len = cgc_match_helper(state, tline, 0, match_type);
                if (match_len) {
                    cgc_printf("%s\n", line);
                    break;
                } else if (match_type == ALL) {
                    break;
                } else {
                    tline++;
                }
            }
            match_len = 0;
            line = ++tstr;
            tline = line;
        }
    }
    cgc_free(ptstr);
}

state_t *cgc_evalrpn(unsigned char *rpn) {
    if (!g_stack)
        g_stack = cgc_malloc(sizeof(state_t *) * MAX_STATES);

    state_t **stack = g_stack;
    state_t *temp_state;
    state_t *arg1, *arg2;

    for (; *rpn; rpn++ ) {
#ifdef PATCHED
        temp_state = NULL;
#endif
        switch (*rpn) {
        default:
            temp_state = cgc_create_state(*rpn);
            break;
        case CONCAT:
            if (stack == g_stack) break;
            POP(stack, arg2);
            if (stack == g_stack) break;
            POP(stack, arg1);
            temp_state = cgc_op_concat(arg1, arg2);
            break;
        case UNION:
            if (stack == g_stack) break;
            POP(stack, arg2);
            if (stack == g_stack) break;
            POP(stack, arg1);
            temp_state = cgc_op_union(arg1, arg2);
            break;
        case STAR:
            if (stack == g_stack) break;
            POP(stack, arg1);
            temp_state = cgc_op_star(arg1);
            break;
        case QMARK:
            if (stack == g_stack) break;
            POP(stack, arg1);
            temp_state = cgc_op_qmark(arg1);
            break;
        case PLUS:
            if (stack == g_stack) break;
            POP(stack, arg1);
            temp_state = cgc_op_plus(arg1);
            break;
        }

        if ( !temp_state )
            goto failed;
        PUSH(stack, temp_state);
    }

    if (stack == g_stack) goto failed;
    POP(stack, arg1);
    return arg1;

failed:
    cgc_clear_trex();
    return NULL;
}

