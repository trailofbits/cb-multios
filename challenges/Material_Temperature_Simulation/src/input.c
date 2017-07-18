/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_input.h"
#include "cgc_room.h"

#define pGRID(grid,x,y,z) (grid + x + y*cgc_X + z*cgc_X*cgc_Y)
extern uint32_t cgc_X;
extern uint32_t cgc_Y;
extern uint32_t cgc_Z;

cgc_ssize_t cgc_read_until(char *buf, char *delim, cgc_size_t max) {
	cgc_size_t index = 0;
	cgc_size_t len;
	char c;

	while (index < max-1) {
		if (cgc_receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		}

		if (len == 0) {
			return(-1);
		}

		if (cgc_strchr(delim, c)) {
			break;
		}

		buf[index++] = c;
	}
	buf[index] = '\0';

	return(index);
}

// store the temp in grid[x][y][z] if valid
int32_t cgc_StoreTemp(double *grid, uint32_t x, uint32_t y, uint32_t z, char *buf) {
	double temp;

	temp = cgc_cgcatof(buf);

	if (temp < MIN_TEMP-1.0 || temp > MAX_TEMP) {
		return(-1);
	}

	// store the temperature converted to Kelvin
	*pGRID(grid,x,y,z) = temp + 273.15;

	return(0);

}

int8_t cgc_read_temps(double *grid) {
	cgc_size_t len;
	uint32_t x, y, z;
	double temp;
	char buf[100];

	for (z = 0; z < cgc_Z; z++) {
		for (y = 0; y < cgc_Y; y++) {
			for (x = 0; x < cgc_X; x++) {
				if (cgc_read_until(buf, ",\n", 99) == -1) {
					return(-1);
				}

				if (cgc_StoreTemp(grid, x, y, z, buf)) {
					cgc_puts("Invalid temperature");
					return(-1);
				}
			}
		}
	}
	
	cgc_flush_stdin();

	return(0);
}

int cgc_flush_stdin(void) {
	cgc_fd_set readfds;
	struct cgc_timeval timeout;
	char c;
	cgc_size_t len;

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN, &readfds);

		timeout.tv_sec = 0;
		timeout.tv_usec = 0;

		if (cgc_fdwait(STDIN+1, &readfds, NULL, &timeout, NULL)) {
			return(-1);
		}

		if (!FD_ISSET(STDIN, &readfds)) {
			return(0);
		}

		if (cgc_receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		}

	} 
}

int32_t cgc_kbhit(void) {
	cgc_fd_set readfds;
	struct cgc_timeval timeout;
	char c;
	cgc_size_t len;

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN, &readfds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		if (cgc_fdwait(STDIN+1, &readfds, NULL, &timeout, NULL)) {
			return(-1);
		}

		if (!FD_ISSET(STDIN, &readfds)) {
			continue;
		}

		if (cgc_receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		} else {
			return(0);
		}

	} 
}
