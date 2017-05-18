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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_stdint.h"

#define CSI "\x1b\x5b"

void cgc_EraseToEOL(void) {
	cgc_printf("$sK", CSI);
}

void cgc_EraseLine(uint8_t StartingX) {
	// move to X
	cgc_printf("$s$dG", CSI, StartingX);
	// clear to the end of the line
	cgc_EraseToEOL();
}

void cgc_MoveCursor(uint8_t x, uint8_t y) {
	cgc_printf("$s$d;$dH", CSI, x, y);
}

void cgc_ClearScreen(void) {
	cgc_printf("$s$d$c", CSI, 2, 'J');
	cgc_MoveCursor(1,1);
}

void cgc_CursorRight(uint8_t NumSpaces) {
	cgc_printf("$s$dC", CSI, NumSpaces);
}

void cgc_CursorLeft(uint8_t NumSpaces) {
	cgc_printf("$s$dD", CSI, NumSpaces);
}


