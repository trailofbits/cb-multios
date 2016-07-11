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
#include <libcgc.h>
#include "libc.h"
#include "operation.h"
#include "service.h"

enum {
    CMD_TO_SYLLABLES = 804619,
    CMD_TO_NOTES = 1128809,
};

int main(void) {

    uint32_t command[1] = {0};
    int ret = 0;

    char *syllables_buf_p;
    ALLOC(BUFFER_LEN, &syllables_buf_p);

    char *notes_buf_p;
    ALLOC(BUFFER_LEN, &notes_buf_p);

    while (1) {
        RECV(command, sizeof(uint32_t));

        switch (command[0]) {
            case CMD_TO_SYLLABLES:
                ret = to_syllables(syllables_buf_p, notes_buf_p);
                break;
            case CMD_TO_NOTES:
                ret = to_notes(syllables_buf_p, notes_buf_p);
                break;
            default:
                ret = ERR_INVALID_CMD;
        }

        if (ret < 0) {
            SENDSI(ret);
            return ret;
        } else {
            memset((void *)syllables_buf_p, 0, BUFFER_LEN);
            memset((void *)notes_buf_p, 0, BUFFER_LEN);
        }
    }
    return ret;
}
