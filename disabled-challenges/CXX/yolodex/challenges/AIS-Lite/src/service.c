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
#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_common.h"
#include "cgc_service.h"
#include "cgc_sentence.h"
#include "cgc_message.h"

#define INVALID_SENTENCE "INVALID SENTENCE."
#define INVALID_MSG "INVALID MESSAGE."
#define PARTIAL_MSG "PARTIAL AIS MESSAGE."

int main(int cgc_argc, char *cgc_argv[]) {
	char ret = SUCCESS;
    int bytes_received = 0;

    struct sentence_struct ss;
    ss.ais_msg = cgc_malloc(MAX_SENTENCE_LEN*sizeof(char));
    cgc_reset_sentence_struct(&ss);

    while (1) {
        char *buf = cgc_calloc(MAX_SENTENCE_LEN*sizeof(char));
        char *english = cgc_calloc(MAX_ENGLISH_LEN*sizeof(char));

        char *outmsg = NULL;
        char reset = TRUE;

        bytes_received = cgc_recv_until_delim(STDIN, buf, MAX_SENTENCE_LEN, '\x07');
        if ((0 >= bytes_received) || ('\x07' != buf[bytes_received - 1])) {
            ret = -9;
            break;
        } else {
            buf[bytes_received - 1] = '\0';
        }

        if (SUCCESS == cgc_parse_sentence(buf, &ss)) {
            if (DONE == ss.msg_status) {
                if (SUCCESS == cgc_to_english(english, &ss)) {
                    outmsg = english;
                } else {
                    outmsg = INVALID_MSG;
                }
            } else { // PARTIAL == ss->msg_status
                outmsg = PARTIAL_MSG;
                reset = FALSE;
            }
        } else {
            outmsg = INVALID_SENTENCE;
        }

        cgc_send(outmsg, cgc_strlen(outmsg));

        if (TRUE == reset) {
            cgc_reset_sentence_struct(&ss);
        }

        cgc_free(english);
        cgc_free(buf);
    }

	return ret;
}
