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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_read.h"

int cgc_readline(char *buf, cgc_size_t buf_size)
{
    if (!buf || buf_size < 2)
        return -1;

    cgc_size_t rx, i = 0;
    for (i = 0; i < buf_size; i++)
    {
        if (cgc_fread(&buf[i], 1, cgc_stdin) == 1)
        {
            if(buf[i] == '\n') {
                buf[i] = '\0';
                break;
            }
        }
        else
        {
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        }
    }

    if (i == buf_size)
        return FAIL;

    return SUCCESS;
}

int cgc_readnum(char *buf, cgc_size_t buf_size, int *num)
{
    int retval = cgc_readline(buf, buf_size);
    if (retval != SUCCESS)
        *num = 0;
    else
        *num = cgc_strtol(&buf[0], NULL, 10);

    return retval;
}

char *cgc_q_and_a(char *question, int maxlen, char *buf, cgc_size_t buflen, int *recv_status, bool allow_empty)
{
    char *answer = NULL;
    *recv_status = FAIL;
    if (!question || !buf || maxlen > buflen)
        return NULL;

    while(*recv_status != SUCCESS) {
        cgc_printf("%s", question);
        *recv_status = cgc_readline(buf, buflen);
        switch (*recv_status) {
        case ERROR:
            return NULL;
        case SUCCESS:
            if (cgc_strlen(buf) > maxlen || (!allow_empty && !cgc_strlen(buf))) {
                *recv_status = FAIL;
            } else {
                answer = cgc_strdup(buf);
                break;
            }
        case FAIL:
        default:
            cgc_printf("Try again\n");
        }
    }

    return answer;
}

