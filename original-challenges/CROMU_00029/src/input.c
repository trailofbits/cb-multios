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
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "input.h"
#include "room.h"

#define pGRID(grid,x,y,z) (grid + x + y*X + z*X*Y)
extern uint32_t X;
extern uint32_t Y;
extern uint32_t Z;

ssize_t read_until(char *buf, char *delim, size_t max) {
	size_t index = 0;
	size_t len;
	char c;

	while (index < max-1) {
		if (receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		}

		if (len == 0) {
			return(-1);
		}

		if (strchr(delim, c)) {
			break;
		}

		buf[index++] = c;
	}
	buf[index] = '\0';

	return(index);
}

// store the temp in grid[x][y][z] if valid
int32_t StoreTemp(double *grid, uint32_t x, uint32_t y, uint32_t z, char *buf) {
	double temp;

	temp = cgcatof(buf);

	if (temp < MIN_TEMP-1.0 || temp > MAX_TEMP) {
		return(-1);
	}

	// store the temperature converted to Kelvin
	*pGRID(grid,x,y,z) = temp + 273.15;

	return(0);

}

int8_t read_temps(double *grid) {
	size_t len;
	uint32_t x, y, z;
	double temp;
	char buf[100];

	for (z = 0; z < Z; z++) {
		for (y = 0; y < Y; y++) {
			for (x = 0; x < X; x++) {
				if (read_until(buf, ",\n", 99) == -1) {
					return(-1);
				}

				if (StoreTemp(grid, x, y, z, buf)) {
					puts("Invalid temperature");
					return(-1);
				}
			}
		}
	}
	
	flush_stdin();

	return(0);
}

int flush_stdin(void) {
	fd_set readfds;
	struct timeval timeout;
	char c;
	size_t len;

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN, &readfds);

		timeout.tv_sec = 0;
		timeout.tv_usec = 0;

		if (fdwait(STDIN+1, &readfds, NULL, &timeout, NULL)) {
			return(-1);
		}

		if (!FD_ISSET(STDIN, &readfds)) {
			return(0);
		}

		if (receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		}

	} 
}

int32_t kbhit(void) {
	fd_set readfds;
	struct timeval timeout;
	char c;
	size_t len;

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN, &readfds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		if (fdwait(STDIN+1, &readfds, NULL, &timeout, NULL)) {
			return(-1);
		}

		if (!FD_ISSET(STDIN, &readfds)) {
			continue;
		}

		if (receive(STDIN, &c, 1, &len) != 0) {
			return(-1);
		} else {
			return(0);
		}

	} 
}
