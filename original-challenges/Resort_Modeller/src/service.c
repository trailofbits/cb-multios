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
#include <stdint.h>
#include "libc.h"
#include "recv_all.h"
#include "send.h"
#include "memcmp.h"
#include "memcpy.h"

#include "resort.h"


const char LOAD_DIGRAPH[4]          =   {'\xd0','\xd1','\xd2','\xd3'};
const char LOAD_RIDER_GROUP[4]      =   {'\x40','\x41','\x42','\x43'};
const char LOAD_RIDER_SINGLE[4]     =   {'\xe0','\xe1','\xe2','\xe3'};
const char UNLOAD_RIDERS[4]         =   {'\xf0','\xf1','\xf2','\xf3'};
const char START[4]                 =   {'\x10','\x11','\x12','\x13'};
const char RESET[4]                 =   {'\x11','\x22','\x33','\x11'};
const char LIFT_STATS[4]            =   {'\x11','\x43','\x34','\x11'};
const char TRAIL_STATS[4]           =   {'\x77','\x11','\xee','\x55'};
const char RIDER_STATS[4]           =   {'\x44','\x11','\x33','\x55'};

static char OK[4] = {0};
static char ERR[4] = {0};

typedef struct request Request;
struct request {
    char cmd[4];
};


/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void gen_result_bufs(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4095; idx+=2) {
        OK[idx % 4] ^= fp[idx];
        ERR[(idx + 1) % 4] ^= fp[idx + 1];
    }
}

int main(void) {

    ssize_t ret = 0;

    gen_result_bufs();

    while (TRUE) {
        Request req;
        RECV(&req, sizeof(Request));

        if (0 == memcmp(LOAD_DIGRAPH, (const char *)req.cmd, sizeof(LOAD_DIGRAPH))) {
            ret = load_resort_digraph();
        } else if (0 == memcmp(LOAD_RIDER_GROUP, (const char *)req.cmd, sizeof(LOAD_RIDER_GROUP))) {
            ret = load_rider_group();
        } else if (0 == memcmp(LOAD_RIDER_SINGLE, (const char *)req.cmd, sizeof(LOAD_RIDER_SINGLE))) {
            ret = load_rider_single();
        } else if (0 == memcmp(UNLOAD_RIDERS, (const char *)req.cmd, sizeof(UNLOAD_RIDERS))) {
            ret = unload_riders();
        } else if (0 == memcmp(START, (const char *)req.cmd, sizeof(START))) {
            ret = start_simulation();
        } else if (0 == memcmp(RESET, (const char *)req.cmd, sizeof(RESET))) {
            ret = reset_simulation();
        } else if (0 == memcmp(LIFT_STATS, (const char *)req.cmd, sizeof(LIFT_STATS))) {
            ret = lift_stats();
        } else if (0 == memcmp(TRAIL_STATS, (const char *)req.cmd, sizeof(TRAIL_STATS))) {
            ret = trail_stats();
        } else if (0 == memcmp(RIDER_STATS, (const char *)req.cmd, sizeof(RIDER_STATS))) {
            ret = rider_stats();
        } else  {
            ret = -1;
        }

        if (0 == ret) {
            send(OK, sizeof(OK));
        } else {
            send(ERR, sizeof(ERR));
	        break;
        }

    }

    return 0;
}
