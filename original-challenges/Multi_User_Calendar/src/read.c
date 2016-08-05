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
#include <stdio.h>
#include <string.h>
#include "read.h"

int readline(char *buf, size_t buf_size)
{
    if (!buf || buf_size < 2)
        return -1;

    size_t rx, i = 0;
    for (i = 0; i < buf_size; i++)
    {
        if (fread(&buf[i], 1, stdin) == 1)
        {
            if(buf[i] == '\n') {
                buf[i] = '\0';
                break;
            }
        }
        else
        {
            fflush(stdout);
            exit(0);
        }
    }

    if (i == buf_size)
        return FAIL;

    return SUCCESS;
}

int readnum(char *buf, size_t buf_size, int *num)
{
    int retval = readline(buf, buf_size);
    if (retval != SUCCESS)
        *num = 0;
    else
        *num = strtol(&buf[0], NULL, 10);

    return retval;
}

char *q_and_a(char *question, int maxlen, char *buf, size_t buflen, int *recv_status, bool allow_empty)
{
    char *answer = NULL;
    *recv_status = FAIL;
    if (!question || !buf || maxlen > buflen)
        return NULL;

    while(*recv_status != SUCCESS) {
        printf("%s", question);
        *recv_status = readline(buf, buflen);
        switch (*recv_status) {
        case ERROR:
            return NULL;
        case SUCCESS:
            if (strlen(buf) > maxlen || (!allow_empty && !strlen(buf))) {
                *recv_status = FAIL;
            } else {
                answer = strdup(buf);
                break;
            }
        case FAIL:
        default:
            printf("Try again\n");
        }
    }

    return answer;
}

