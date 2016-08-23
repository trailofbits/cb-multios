/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "stdio.h"
#include "L3.h"
#include "L4.h"

Handlers Listeners[MAX_HANDLERS];

// Listen on L4 port
uint8_t L4_RegisterHandler(uint8_t NewL4Addr, void *NewHandler) {
	uint8_t i;
	uint8_t FreeHandler = MAX_HANDLERS+1;

	if (!NewHandler) {
		return(0);
	}

	for (i = 0; i < MAX_HANDLERS; i++) {
		if (Listeners[i].Handler == NULL) {
			FreeHandler = i;
		}
		if (Listeners[i].L4Addr == NewL4Addr) {
			return(0);
		}
	}
	if (FreeHandler == MAX_HANDLERS+1) {
		return(0);
	}

	Listeners[FreeHandler].L4Addr = NewL4Addr;
	Listeners[FreeHandler].Handler = NewHandler;

	return(1);
}

