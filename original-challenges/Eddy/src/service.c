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

#include "libc.h"

#include "editor.h"

#define COMMAND_SIZE (sizeof(struct command) + MAX_COMMAND_SIZE + 1)

static unsigned int
generate_csum(char *buf, size_t size)
{
    int i;
    unsigned char *flag_page = (void *)0x4347c000;
    unsigned int ret = 0;

    for (i = 0; i < 1024; i++)
        ret ^= flag_page[i * 4];

    for (i = 0; i < size; i++)
        ret ^= buf[i];

    return ret & 0xff;
}

int
main(void)
{
    int ret;
    struct command *command;
    struct result *result;

    if ((command = calloc(COMMAND_SIZE)) == NULL)
        return -1;

    while (1) {
        memset(command, '\0', COMMAND_SIZE);
        read_all(STDIN, command, sizeof(struct command));
        if (command->size && command->size <= MAX_COMMAND_SIZE)
            read_all(STDIN, command->buf, command->size);

        ret = run_command(command, &result);
        if (result) {
            result->result = ret;
            result->csum = generate_csum(result->buf, result->size);
            write_all(STDOUT, result, sizeof(struct result) + result->size);
            free(result);
        } else {
            write_all(STDOUT, &ret, sizeof(int));
        }
    }

    return 0;
}

