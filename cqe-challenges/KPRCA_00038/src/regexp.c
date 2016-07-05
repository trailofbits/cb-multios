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
#include <stdint.h>
#include <string.h>
#include "regexp.h"

#define EXTRA_CLASS 32
#define EXTRA_OR (sizeof(rop_t *) * 2)

#define C_BEGIN 0x100
#define C_END 0x101

static rop_t *init_rop(int op, int extra)
{
    rop_t *rop = calloc(1, sizeof(rop_t) + extra);
    if (rop == NULL)
        return NULL;
    rop->op = op;
    return rop;
}

// convert repititions to loops
// link children to next
static int simplify(rop_t **head, rop_t *parent)
{
    unsigned int cnt = 0, ret;
    rop_t *rop = *head, *tmp;

#ifdef PATCHED
    if (rop == NULL)
        return 0;
#endif

    if (rop->op == ROP_GROUP)
    {
        if ((ret = simplify(&rop->r_group.e, rop)) == 0)
            return 0;
        cnt += ret;
    }
    else if (rop->op == ROP_OR)
    {
        if ((ret = simplify(&rop->r_or.e[0], rop)) == 0)
            return 0;
        cnt += ret;
        if ((ret = simplify(&rop->r_or.e[1], rop)) == 0)
            return 0;
        cnt += ret;
    }

    if (rop->next != NULL)
    {
        if ((ret = simplify(&rop->next, parent)) == 0)
            return 0;
        cnt += ret;
    }

    if (rop->flag == RFLAG_ONE_OR_MORE)
    {
        tmp = init_rop(ROP_OR, EXTRA_OR);
        if (tmp == NULL)
            return 0;
        tmp->r_or.e[0] = rop;
        tmp->r_or.e[1] = rop->next;

        rop->next = tmp;
    }
    else if (rop->flag == RFLAG_ZERO_OR_ONE)
    {
        tmp = init_rop(ROP_OR, EXTRA_OR);
        if (tmp == NULL)
            return 0;
        tmp->r_or.e[0] = rop;
        tmp->r_or.e[1] = rop->next;

        *head = tmp;
    }
    else if (rop->flag == RFLAG_ZERO_OR_MORE)
    {
        tmp = init_rop(ROP_OR, EXTRA_OR);
        if (tmp == NULL)
            return 0;
        tmp->r_or.e[0] = rop;
        tmp->r_or.e[1] = rop->next;

        *head = tmp;

        tmp = init_rop(ROP_OR, EXTRA_OR);
        if (tmp == NULL)
            return 0;
        tmp->r_or.e[0] = rop;
        tmp->r_or.e[1] = rop->next;

        rop->next = tmp;
    }

    rop->flag = RFLAG_ONE;
    rop->parent = parent;
    return cnt + 1;
}

static int parse_class(rop_t **result, char *str)
{
    int i, invert = 0, range = 0, last = -1;
    rop_t *op = init_rop(ROP_CLASS, EXTRA_CLASS);
    if (op == NULL)
        goto fail;

#define SET_BIT(x) do { \
        op->r_class.data[((x) / 8)] |= 1 << ((x) % 8); \
    } while (0)

    for (i = 0; str[i] != ']'; i++)
    {
        int c = (unsigned char) str[i];
        if (c == 0)
            goto fail;
        if (i == 0 && c == '^')
            invert = 1;
        else if (c == '-')
        {
            if (last == -1)
                goto ingest;
            else
                range = 1;
        }
        else if (c == '\\')
        {
            if (str[i+1] == 0)
                goto fail;
            c = str[++i];
            goto ingest;
        }
        else
        {
ingest:
            if (range)
            {
                int j;
                if (last <= c)
                    for (j = last; j <= c; j++)
                        SET_BIT(j);
                else
                    SET_BIT('-');
            }

            SET_BIT(c);
            last = c;
            range = 0;
        }
    }

#undef SET_BIT

    if (invert)
        for (i = 0; i < EXTRA_CLASS; i++)
            op->r_class.data[i] = ~op->r_class.data[i];

    *result = op;
    return i + 1;

fail:
    return 0;
}

static int regexp_parse(rop_t **result, char *str, int end)
{
    int i, len;
    rop_t *op = NULL, *tail = NULL;
#if PATCHED
    static int guard = 0;
    if (++guard > 10000)
        goto fail;
#endif

    for (i = 0; str[i] != end; i++)
    {
        rop_t *tmp = NULL;

        if (str[i] == 0)
            goto fail;

        switch (str[i])
        {
        case '.':
            tmp = init_rop(ROP_WILDCARD, 0);
            if (tmp == NULL)
                goto fail;
            break;
        case '^':
            tmp = init_rop(ROP_FRONT, 0);
            if (tmp == NULL)
                goto fail;
            break;
        case '$':
            tmp = init_rop(ROP_BACK, 0);
            if (tmp == NULL)
                goto fail;
            break;
        case '|':
            if (tail == NULL)
                goto fail;

            tmp = init_rop(ROP_OR, EXTRA_OR);
            if (tmp == NULL)
                goto fail;
            *result = tmp;
            tmp->r_or.e[0] = op;
            result = &tmp->r_or.e[1];
            op = tail = NULL;

            // continue
            continue;
        case '*':
            if (tail == NULL || tail->flag != RFLAG_ONE)
                goto fail;
            tail->flag = RFLAG_ZERO_OR_MORE;
            break;
        case '+':
            if (tail == NULL || tail->flag != RFLAG_ONE)
                goto fail;
            tail->flag = RFLAG_ONE_OR_MORE;
            break;
        case '?':
            if (tail == NULL || tail->flag != RFLAG_ONE)
                goto fail;
            tail->flag = RFLAG_ZERO_OR_ONE;
            break;
        case '\\':
            tmp = init_rop(ROP_SEQ, 0);
            if (tmp == NULL || str[i+1] == 0)
                goto fail;
            tmp->r_seq.seq = str[++i];
            break;
        case '(':
            tmp = init_rop(ROP_GROUP, 0);
            if (tmp == NULL)
                goto fail;
            len = regexp_parse(&tmp->r_group.e, &str[i+1], ')');
            if (len == 0)
                goto fail;
            i += len;
            break;
        case '[':
            len = parse_class(&tmp, &str[i+1]);
            if (len == 0)
                goto fail;
            i += len;
            break;
        default:
            tmp = init_rop(ROP_SEQ, 0);
            if (tmp == NULL)
                goto fail;
            tmp->r_seq.seq = str[i];
            break;
        }

        if (tmp != NULL)
        {
            if (op == NULL)
                tail = op = tmp;
            else
                tail = tail->next = tmp;
        }
    }

#ifdef PATCHED
    --guard;
#endif

    *result = op;
    return i + 1;

fail:
#ifdef PATCHED
    --guard;
#endif
    return 0;
}

int regexp_init(regexp_t *r, const char *str)
{
    memset(r, 0, sizeof(regexp_t));
    r->input = strdup(str);
    if (r->input == NULL)
        goto fail;

    if (!regexp_parse(&r->tree, r->input, 0))
        goto fail;

    r->max_states = simplify(&r->tree, NULL);
    if (r->max_states == 0)
        goto fail;

    return 1;

fail:
    regexp_free(r);
    return 0;
}

void _recursive_free(rop_t *r)
{
    if (r == NULL || r->flag == RFLAG_FREED)
        return;

    r->flag = RFLAG_FREED;

    if (r->op == ROP_GROUP)
    {
        _recursive_free(r->r_group.e);
    }
    else if (r->op == ROP_OR)
    {
        _recursive_free(r->r_or.e[0]);
        _recursive_free(r->r_or.e[1]);
    }

    _recursive_free(r->next);

    free(r);
}

int regexp_free(regexp_t *r)
{
    free(r->input);
    _recursive_free(r->tree);
    return 1;
}

static int check_prev_state(regexp_t *r, rop_t *op)
{
    unsigned int i;
    for (i = 0; i < r->num_prev_states; i++)
        if (r->prev_states[i] == op)
            return 0;
    r->prev_states[r->num_prev_states++] = op;
    return 1;
}

static void add_state(regexp_t *r, rop_t *op)
{
    unsigned int i;
    for (i = 0; i < r->num_states; i++)
        if (r->states[i] == op)
            return;
    r->states[r->num_states++] = op;
    return;
}

static int _regexp_match(regexp_t *r, rop_t *op, int c)
{
    int i, len;
    int begin = c == C_BEGIN;
    int end = c == C_END;

    switch (op->op)
    {
    case ROP_FRONT:
        if (!begin)
            goto done;
        if (!check_prev_state(r, op))
            goto done;
        break;
    case ROP_BACK:
        if (!end)
            goto done;
        if (!check_prev_state(r, op))
            goto done;
        break;
    case ROP_WILDCARD:
        if (begin)
        {
            add_state(r, op);
            goto done;
        }
        if (end)
        {
            goto done;
        }
        break;
    case ROP_SEQ:
        if (begin)
        {
            add_state(r, op);
            goto done;
        }
        if (end)
        {
            goto done;
        }
        if (c != op->r_seq.seq)
            goto done;
        break;
    case ROP_CLASS:
        if (begin)
        {
            add_state(r, op);
            goto done;
        }
        if (end)
        {
            goto done;
        }
        if (!(op->r_class.data[c / 8] & (1 << (c % 8))))
            goto done;
        break;
    case ROP_GROUP:
        return _regexp_match(r, op->r_group.e, c);
    case ROP_OR:
        if (_regexp_match(r, op->r_or.e[0], c))
            return 1;
        if (op->r_or.e[1] != NULL)
            return _regexp_match(r, op->r_or.e[1], c);

        while (op != NULL && op->next == NULL)
            op = op->parent;
        
        if (op == NULL)
            return 1;

        return _regexp_match(r, op->next, c);
    }

    while (op != NULL && op->next == NULL)
        op = op->parent;

    if (op == NULL)
        return 1; // match!

    add_state(r, op->next);

done:
    return 0;
}

int regexp_match(regexp_t *r, const char *input)
{
    int i, j, result = 0;
    unsigned int cnt;
    rop_t **states1, **states2, **current;

    states1 = states2 = r->prev_states = NULL;

    states1 = calloc(r->max_states, sizeof(rop_t *));
    if (states1 == NULL)
        goto done;
    states2 = calloc(r->max_states, sizeof(rop_t *));
    if (states2 == NULL)
        goto done;
    r->prev_states = calloc(r->max_states, sizeof(rop_t *));
    if (r->prev_states == NULL)
        goto done;

    result = 1;

    r->states = states1;
    r->num_states = 0;
    r->num_prev_states = 0;
    if (_regexp_match(r, r->tree, C_BEGIN))
        goto done;

    for (i = 0; input[i] != 0; i++)
    {
        add_state(r, r->tree);
        current = r->states;
        cnt = r->num_states;
        r->states = current == states1 ? states2 : states1;
        r->num_states = 0;
        r->num_prev_states = 0;

        for (j = 0; j < cnt; j++)
        {
            if (_regexp_match(r, current[j], input[i]))
                goto done;
        }
    }

    add_state(r, r->tree);
    current = r->states;
    cnt = r->num_states;
    r->states = current == states1 ? states2 : states1;
    r->num_states = 0;
    r->num_prev_states = 0;

    for (j = 0; j < cnt; j++)
    {
        if (_regexp_match(r, current[j], C_END))
            goto done;
    }

    result = 0;

done:
    free(states1);
    free(states2);
    free(r->prev_states);
    r->states = r->prev_states = NULL;
    return result;
}

