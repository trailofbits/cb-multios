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
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_recv_all.h"
#include "cgc_send.h"
#include "cgc_memcmp.h"
#include "cgc_memcpy.h"

#include "cgc_resort.h"


const char cgc_LOAD_DIGRAPH[4]          =   {'\xd0','\xd1','\xd2','\xd3'};
const char cgc_LOAD_RIDER_GROUP[4]      =   {'\x40','\x41','\x42','\x43'};
const char cgc_LOAD_RIDER_SINGLE[4]     =   {'\xe0','\xe1','\xe2','\xe3'};
const char cgc_UNLOAD_RIDERS[4]         =   {'\xf0','\xf1','\xf2','\xf3'};
const char cgc_START[4]                 =   {'\x10','\x11','\x12','\x13'};
const char cgc_RESET[4]                 =   {'\x11','\x22','\x33','\x11'};
const char cgc_LIFT_STATS[4]            =   {'\x11','\x43','\x34','\x11'};
const char cgc_TRAIL_STATS[4]           =   {'\x77','\x11','\xee','\x55'};
const char cgc_RIDER_STATS[4]           =   {'\x44','\x11','\x33','\x55'};

static char OK[4] = {0};
static char ERR[4] = {0};

typedef struct request Request;
struct request {
    char cmd[4];
};


/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void cgc_gen_result_bufs(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4095; idx+=2) {
        OK[idx % 4] ^= fp[idx];
        ERR[(idx + 1) % 4] ^= fp[idx + 1];
    }
}

int main(int cgc_argc, char *cgc_argv[]) {

    cgc_ssize_t ret = 0;

    cgc_gen_result_bufs();

    while (TRUE) {
        Request req;
        RECV(&req, sizeof(Request));

        if (0 == cgc_memcmp(cgc_LOAD_DIGRAPH, (const char *)req.cmd, sizeof(cgc_LOAD_DIGRAPH))) {
            ret = cgc_load_resort_digraph();
        } else if (0 == cgc_memcmp(cgc_LOAD_RIDER_GROUP, (const char *)req.cmd, sizeof(cgc_LOAD_RIDER_GROUP))) {
            ret = cgc_load_rider_group();
        } else if (0 == cgc_memcmp(cgc_LOAD_RIDER_SINGLE, (const char *)req.cmd, sizeof(cgc_LOAD_RIDER_SINGLE))) {
            ret = cgc_load_rider_single();
        } else if (0 == cgc_memcmp(cgc_UNLOAD_RIDERS, (const char *)req.cmd, sizeof(cgc_UNLOAD_RIDERS))) {
            ret = cgc_unload_riders();
        } else if (0 == cgc_memcmp(cgc_START, (const char *)req.cmd, sizeof(cgc_START))) {
            ret = cgc_start_simulation();
        } else if (0 == cgc_memcmp(cgc_RESET, (const char *)req.cmd, sizeof(cgc_RESET))) {
            ret = cgc_reset_simulation();
        } else if (0 == cgc_memcmp(cgc_LIFT_STATS, (const char *)req.cmd, sizeof(cgc_LIFT_STATS))) {
            ret = cgc_lift_stats();
        } else if (0 == cgc_memcmp(cgc_TRAIL_STATS, (const char *)req.cmd, sizeof(cgc_TRAIL_STATS))) {
            ret = cgc_trail_stats();
        } else if (0 == cgc_memcmp(cgc_RIDER_STATS, (const char *)req.cmd, sizeof(cgc_RIDER_STATS))) {
            ret = cgc_rider_stats();
        } else  {
            ret = -1;
        }

        if (0 == ret) {
            cgc_send(OK, sizeof(OK));
        } else {
            cgc_send(ERR, sizeof(ERR));
	        break;
        }

    }

    return 0;
}
