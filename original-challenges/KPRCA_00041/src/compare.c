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

#include "compare.h"

static char *get_no_ws_line(char *line)
{
    if (line == NULL)
        return NULL;

    size_t size = strlen(line) + 1, i;
    char *nline = NULL, *iter;
    nline = malloc(size);
    if (nline == NULL)
        return NULL;

    memset(nline, 0, size);
    iter = nline;
    for (i = 0; i < size; i++) {
        if (strchr(" \t\n", line[i]) == NULL)
            *iter++ = line[i];
    }

    return nline;

}

static size_t count_words(char *str) {
    if (!str)
        return 0;

    int i, len = strlen(str);
    size_t words = 0;
    for (i = 0; i < len; i++) {
        if (strchr(" \t\r\n", str[i]) == NULL)
            words++;
    }

    words = len ? words+1 : words;
    return words;

}

lcll_t *pre_process(SFILE *sfp, size_t *wordc, size_t *linec)
{
    char *data = &sfp->data[0], *line = NULL;
    *wordc = 0, *linec = 1;

    lc_t *new_lc;
    lcll_t *head = NULL, *iter, *next;

    line = strsep(&data, "\n");
    while (line && (strlen(line) || (data && strlen(data)))) {
        next = malloc(sizeof(lcll_t));
        if (!next)
            return NULL;

        new_lc = new_linecmp(line);
        if (new_lc == NULL) {
            free(next);
            next = NULL;
            break;
        }

        next->lc = new_lc;
        next->next = NULL;

        if (!head)
            head = next;
        else
            iter->next = next;
        iter = next;
        line = strsep(&data, "\n");
        wordc += count_words(line);
        (*linec)++;
    }

    return head;
}

lc_t *new_linecmp(char *line)
{
    if (!line)
        return NULL;

    lc_t *new_lc = malloc(sizeof(lc_t));
    if (!new_lc)
        return NULL;

    new_lc->pline = line;
    new_lc->no_ws_line = get_no_ws_line(line);
    new_lc->lhash = get_lhash(line);
    new_lc->no_ws_lhash = get_lhash(new_lc->no_ws_line);

    return new_lc;
}

void free_linecmp_list(lcll_t **head)
{
    lcll_t *iter = *head, *prev;
    while (iter) {
        prev = iter;
        iter = iter->next;
        if (prev->lc->no_ws_line)
            free(prev->lc->no_ws_line);
        free(prev->lc);
        free(prev);
    }

    *head = NULL;
}

