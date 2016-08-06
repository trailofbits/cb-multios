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
#include "hex.h"
#include <stdint.h>


int is_hex_digit(char digit) {
	if (('A' <= digit) && ('F' >= digit)) {
		return TRUE;
	} else if (('a' <= digit) && ('f' >= digit)) {
		return TRUE;
	} else if (('0' <= digit) && ('9' >= digit)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

char ascii_hex_to_bin(char hex_digit) {
	if (('A' <= hex_digit) && ('F' >= hex_digit)) {
		return hex_digit - 'A' + 10;
	} else if (('a' <= hex_digit) && ('f' >= hex_digit)) {
		return hex_digit - 'a' + 10;
	} else if (('0' <= hex_digit) && ('9' >= hex_digit)) {
		return hex_digit - '0';
	} else {
		return -1;
	}
}

