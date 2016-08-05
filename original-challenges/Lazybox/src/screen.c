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
#include "string.h"
#include "stdint.h"

#define CSI "\x1b\x5b"

void EraseToEOL(void) {
	printf("$sK", CSI);
}

void EraseLine(uint8_t StartingX) {
	// move to X
	printf("$s$dG", CSI, StartingX);
	// clear to the end of the line
	EraseToEOL();
}

void MoveCursor(uint8_t x, uint8_t y) {
	printf("$s$d;$dH", CSI, x, y);
}

void ClearScreen(void) {
	printf("$s$d$c", CSI, 2, 'J');
	MoveCursor(1,1);
}

void CursorRight(uint8_t NumSpaces) {
	printf("$s$dC", CSI, NumSpaces);
}

void CursorLeft(uint8_t NumSpaces) {
	printf("$s$dD", CSI, NumSpaces);
}


