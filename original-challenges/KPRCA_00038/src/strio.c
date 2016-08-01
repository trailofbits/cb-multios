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
#include "strio.h"

#define MAX_LENGTH (0x10000000)

static int enlarge(strio_t *s, int min)
{
    char *buf;
    int new_length = s->length;

    if (new_length >= min)
        return 1;

    if (min >= MAX_LENGTH)
        return 0;

    while (new_length < min)
        new_length *= 2;

    buf = realloc(s->buf, new_length);
    if (buf == NULL)
        return 0;

    s->buf = buf;
    s->length = new_length;
    return 1;
}

int strio_init(strio_t *s)
{
    s->length = 32;
    s->buf = malloc(s->length);
    s->pos = 0;

    if (s->buf == NULL)
        return 0;

    return 1;
}

void strio_free(strio_t *s)
{
    free(s->buf);
    memset(s, 0, sizeof(strio_t));
}

int strio_append_char(strio_t *s, char c)
{
    if (s->pos == s->length)
    {
        if (!enlarge(s, s->length + 1))
            return 0;
    }

    s->buf[s->pos++] = c;
    return 1;
}

char *strio_dup(strio_t *s)
{
    if (s->pos == s->length)
    {
        if (!enlarge(s, s->length + 1))
            return 0;
    }
    s->buf[s->pos] = 0;
    return strdup(s->buf);
}
