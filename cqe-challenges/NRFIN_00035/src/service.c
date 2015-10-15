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
#include "common.h"
#include "operation.h"
#include "service.h"
#include "tank.h"


int main(void) {
	char ret = SUCCESS;
    struct tankset *t = NULL;

    if (SUCCESS != (ret = create_tanks(&t, TANK_QTY))) {goto bail;}

    syslog(LOG_INFO, "H2FLOW Service Ready.");

    while (1) {
        if (SUCCESS != (ret = update_drain_factors(t))) {goto bail;}
        if (SUCCESS != (ret = rxtx(t))) {goto bail;}

        sleep(SLEEP_INT_SEC, SLEEP_INT_USEC);

        if (SUCCESS != (ret = update_water_levels(t))) {goto bail;}
        if (SUCCESS != (ret = check_levels(t))) {goto bail;}
    }

bail:
	if (0 > ret) {
		send((char *)&ret, 1);
	}

	return ret;
}
