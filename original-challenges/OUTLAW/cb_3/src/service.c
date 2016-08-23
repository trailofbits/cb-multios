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
#include "service.h"


void do_exit(msg *exit_msg) {
    DBG("\n");
    int ret = SUCCESS;

    // We got an exit() command from the CRS.  Propagate it to both CBs.
    
    DBG("[D] shutting down CLIENT; exit_msg = 0x%08x\n", *exit_msg);
    if (SUCCESS != (ret = send_bytes(PIPE_CB1_A, (char *)exit_msg, sizeof(msg)))) {
        DBG("[E] failed to send exit message to CLIENT\n");
        ret = ERRNO_EXIT;
        goto bail;
    } 

    DBG("[D] shutting down SERVER\n");
    if (SUCCESS != (ret = send_bytes(PIPE_CB2_A, (char *)exit_msg, sizeof(msg)))) {
        DBG("[E] failed to send exit message to SERVER\n");
        ret = ERRNO_EXIT;
        goto bail;
    } 

    DBG("[D] got exit() message; terminating...\n");

bail:
    _terminate(ret);
}

int main(void) {
    DBG("\n");
    int ret = SUCCESS;
    msg msg, msgNull = { 0 };

    while (TRUE) {
        
        // Get message from CB?
        msg = msgNull;
        if (SUCCESS != (ret = recv_bytes(PIPE_RECV_CBS, (char *)&msg, sizeof(msg)))) {
            DBG("[E] failed to recv msg from CB? side\n");
            goto bail;
        }
        DBG("[D] got a message; dst = %d\n", msg.dst);
        MSG_DUMP(msg);

        // Validate dst.
        if (PIPE_CB1_A > msg.dst || PIPE_CB2_A < msg.dst || STDERR == msg.dst) {
            DBG("[E] invalid dst (%d); bailing\n", msg.dst);
            goto bail;
        }
        DBG("[D] msg.dst seems legit (%s)\n", dst2str[msg.dst]);

        // Send the message to the CRS
        if (SUCCESS != (ret = send_bytes(PIPE_SEND_CRS, (char *)&msg, sizeof(msg)))) {
            DBG("[E] failed to forward CB? -> TAP -> CRS\n");
            goto bail;
        }
        DBG("[D] forwarded message to CRS; waiting for response\n", msg.dst);

        // Get (possibly modified) msg back from CRS
        msg = msgNull;
        if (SUCCESS != (ret = recv_bytes(PIPE_RECV_CRS, (char *)&msg, sizeof(msg)))) {
            DBG("[E] failed to recv msg from CB? side\n");
            goto bail;
        }
        if (DST_EXIT == msg.dst) { do_exit(&msg); }
        if (PIPE_CB1_A > msg.dst || PIPE_CB2_B < msg.dst || STDERR == msg.dst) {
            DBG("[E] invalid dst (%d); bailing\n", msg.dst);
            goto bail;
        }
        DBG("[D] got (possibly modified) msg back from CRS\n", msg.dst);
        MSG_DUMP(msg);

        // Forward the msg back to CB?
        DBG("[D] forwarding the message onto %s ...\n", dst2str[msg.dst]);
        if (SUCCESS != (ret = send_bytes(msg.dst, (char *)&msg, sizeof(msg)))) {
            DBG("[E] failed to forward CB? -> TAP -> CRS\n");
            goto bail;
        } 
    }

bail:
    return ret;
}

