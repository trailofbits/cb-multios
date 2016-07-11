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
#include <string.h>
#include <ctype.h>

#include "accelio.h"

/* sides = 1, trim front
 * sides = 2, trim back
 * sides = 3, trim both
*/
int strtrim(char *str, size_t size, int sides)
{
    int i, len;
    len = strlen(str) + 1;
    if (len > size)
        return -1;
    else if (len == 1)
        return 0;

    if (sides == TRIM_FRONT || sides == TRIM_ALL) {
        char *tmp = str;
        for (i = 0; i < len; i++, tmp++) {
            if (strchr(WHITESPACE, *tmp) == NULL) {
                memcpy(str, tmp, len - i);
                break;
            }
        }
    }

    if ((sides == TRIM_BACK || sides == TRIM_ALL) && (len - 1 != 0)) {
        for (i = len - 2; i >= 0 ; i--) {
            if (strchr(WHITESPACE, str[i]) == NULL) {
                str[i + 1] = '\0';
                break;
            } else if (i == 0) {
                str[i] = '\0';
                break;
            }
        }
    }

    return 0;
}

//row and col must be buffers of at least len 4
int valid_cell_id(char *input)
{
    if (strlen(input) < 2)
        return -1;

    size_t i = 0, is_num = 0;
    char row[3];
    char col[3];
    char delim = '\0';
    char c = toupper(input[0]);
    if (c < 'A' || c > 'Z')
        return -1;
    row[0] = c;

    c = toupper(input[1]);
    if (!(c >= 'A' && c <= 'Z') && !(c >= '0' && c <= '9' ))
        return -1;

    if (c >= '0' && c <= '9') {
        col[is_num++] = c;
        row[1] = '\0';
    } else {
        row[1] = c;
        row[2] = '\0';
    }

    for (i = 2; i < 5; i++) {
        if (input[i] == delim && is_num) {
            col[is_num] = '\0';
            return 0;
        }
        if (input[i] >= '0' && input[i] <= '9' && is_num < 2) {
            col[is_num++] = input[i];
        }
        else {
            return -1;
        }
    }

    return -1;
}

//row and col must be buffers of at least len 4
int get_rowcol(char *input, char *row, char *col, char delim)
{
    if (strlen(input) < 2)
        return -1;

    size_t i = 0, is_num = 0;
    char c = toupper(input[0]);
    if (c < 'A' || c > 'Z')
        return -1;
    row[0] = c;

    c = toupper(input[1]);
    if (!(c >= 'A' && c <= 'Z') && !(c >= '0' && c <= '9' ))
        return -1;

    if (c >= '0' && c <= '9') {
        col[is_num++] = c;
        row[1] = '\0';
    } else {
        row[1] = c;
        row[2] = '\0';
    }

    for (i = 2; i < 5; i++) {
        if (input[i] == delim && is_num) {
            col[is_num] = '\0';
            return 0;
        }
        if (input[i] >= '0' && input[i] <= '9' && is_num < 2) {
            col[is_num++] = input[i];
        }
        else {
            return -1;
        }
    }

    return -1;
}

int sanitize_formula(char *formula, size_t size)
{
    size_t i, j, len;
    len = strlen(formula);
    if (len > size)
        return -1;

    char *sanitized = calloc(1, size);
    if (sanitized == NULL)
        return -1;


    for (i = 0, j=0; i < len; i++) {
        if (strchr(WHITESPACE, formula[i]) == NULL)
            sanitized[j++] = formula[i];
    }
    memcpy(formula, sanitized, size);
    free(sanitized);
    return 0;
}

