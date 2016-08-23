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
#pragma once

#include <libcgc.h>
#include "common.h"

const char *CB_NAME = "   TAP";

#define PIPE_RECV_CBS PIPE_TAP_B
#define PIPE_RECV_CRS STDIN

#define PIPE_SEND_CRS STDOUT
#define PIPE_SEND_CB1 PIPE_CB1_A
#define PIPE_SEND_CB2 PIPE_CB2_A

 /**
 * Called when the CRS issues a shutdown command.  This function propagates the 
 * shutdown to all CBs in the set then _terminate(0)s itself.
 *
 * @return void
 */
void do_exit(msg *exit_msg);

 /**
 * Implement a simple blocking router to mediate between the CB set and the CRS.
 * Messages are routed based on their desintation field, allowing the CRS to 
 * address any particular CB.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int main(void);
