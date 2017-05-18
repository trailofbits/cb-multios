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

#include "cgc_libc.h"

#include "cgc_regex.h"

#define CHAR_SET_SIZE (256 / 8)
typedef unsigned char char_set[CHAR_SET_SIZE];

static void
cgc_init_char_set(char_set set)
{
    cgc_memset(set, '\0', CHAR_SET_SIZE);
}

static void
cgc_set_bit(char_set set, unsigned char bit)
{
    set[bit / 8] |= (1 << (bit % 8));
}

static int
cgc_get_bit( char_set set, unsigned char bit)
{
    return (set[bit / 8] & (1 << (bit % 8))) != 0;
}

static void
cgc_invert_char_set(char_set set)
{
    cgc_size_t i = 0;

    for (i = 0; i < CHAR_SET_SIZE; i++)
        set[i] = ~set[i];
}

struct regex_element {
    char_set set;
    int star;
    int begin_anchor;
    int end_anchor;
};

static int
cgc_parse_regex_element( char *regex, struct regex_element *element, char **next)
{
    char *c = regex;

    cgc_init_char_set(element->set);
    element->star = element->begin_anchor = element->end_anchor = 0;

    if (*c == '^') {
        element->begin_anchor = 1;
        c++;
    }

    if (*c == '.') {
        cgc_invert_char_set(element->set);
        c++;
    } else if (*c == '[') {
        int invert = 0;
        c++;

        if (*c == '^') {
            invert = 1;
            c++;
        }

        for (; *c && *c != ']'; c++)
            cgc_set_bit(element->set, *c);

        if (invert)
            cgc_invert_char_set(element->set);

        if (*c == ']')
            c++;
        else
            return EXIT_FAILURE;
    } else {
        if (*c == '\\')
            c++;

        if (*c)
            cgc_set_bit(element->set, *c);
        else
            return EXIT_FAILURE;

        c++;
    }

    if (*c == '*') {
        element->star = 1;
        c++;
    }

    if (*c == '$') {
        element->end_anchor = 1;
        c++;
    }

    *next = c;
    return EXIT_SUCCESS;
}

static int
cgc_greedy_match_one(char *line, struct regex_element *element, int is_first, char **next)
{
    *next = line;

    if (element->begin_anchor && !is_first)
        return 0;

    if (element->star) {
        while (**next && cgc_get_bit(element->set, **next))
            (*next)++;

        return !element->end_anchor || cgc_strlen(*next) == 0;
    }

    if (*line && cgc_get_bit(element->set, *line)) {
        (*next)++;
        return !element->end_anchor || cgc_strlen(*next) == 0;
    }

    return 0;
}

static int
cgc_do_regex_match(char *line, struct regex_element **elements, int is_first, char **end)
{
    char *next;
    struct regex_element **cur = elements;

    if (*elements == NULL) {
        *end = line;
        return EXIT_SUCCESS;
    }

    if (cgc_greedy_match_one(line, *elements, is_first, &next)) {
        while (next > line || ((*elements)->star && next >= line)) {
            if (cgc_do_regex_match(next, elements + 1, 0, end) == EXIT_SUCCESS)
                return EXIT_SUCCESS;

            next--;
        }
    }

    // If all remaining elements have a star, we still match
    while (*cur && (*cur)->star && !(*cur)->end_anchor)
        cur++;

    if (*cur == NULL) {
        *end = next;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int
cgc_regex_match(char *regex, char *line, char **begin, char **end)
{
    int ret = EXIT_FAILURE;
    int i;
    cgc_size_t count = 0;
    char *c = regex;
    struct regex_element element, **elements = NULL;

    if (cgc_strlen(regex) > MAX_REGEX_LENGTH)
        goto out;

    while (cgc_parse_regex_element(c, &element, &c) == EXIT_SUCCESS)
        count++;

    if ((elements = cgc_calloc((count + 1) * sizeof(struct regex_element *))) == NULL)
        goto out;

    c = regex;
    for (i = 0; i < count; i++) {
        if ((elements[i] = cgc_calloc(sizeof(struct regex_element))) == NULL)
            goto out;

        if (cgc_parse_regex_element(c, elements[i], &c) != EXIT_SUCCESS)
            goto out;
    }

    for (c = line; *c; c++) {
        *begin = c;
        if (cgc_do_regex_match(c, elements, c == line, end) == EXIT_SUCCESS) {
            ret = EXIT_SUCCESS;
            goto out;
        }
    }

    *begin = c;
    if (cgc_do_regex_match(c, elements, c == line, end) == EXIT_SUCCESS) {
        ret = EXIT_SUCCESS;
        goto out;
    }

out:
    if (elements)
        for (i = 0; i < count; i++)
            cgc_free(elements[i]);

    cgc_free(elements);

    return ret;
}

