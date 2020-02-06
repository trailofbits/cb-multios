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
#include "cgc_stdint.h"
#include "cgc_char.h"

unsigned char cgc_is_non_printable(const unsigned char ch) {
	if (FALSE == cgc_is_printable(ch)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_printable(const unsigned char ch) {
	// (0x1F < ch) and (0x7F > ch)
	if ((TRUE == cgc_is_digit(ch)) ||
		(TRUE == cgc_is_letter(ch)) ||
		(TRUE == cgc_is_symbol(ch))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_digit(const unsigned char ch) {
	if ((0x30 <= ch) && (0x39 >= ch)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_letter(const unsigned char ch) {
	if ((TRUE == cgc_is_upper(ch)) ||
		(TRUE == cgc_is_lower(ch))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_upper(const unsigned char ch) {
	if ((0x41 <= ch) && (0x5A >= ch)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_lower(const unsigned char ch) {
	if ((0x61 <= ch) && (0x7A >= ch)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned char cgc_is_symbol(const unsigned char ch) {
	if 	(((0x21 <= ch) && (ch <= 0x2F)) || 
		 ((0x3A <= ch) && (ch <= 0x40)) ||
		 ((0x5B <= ch) && (ch <= 0x60)) ||
		 ((0x7B <= ch) && (ch <= 0x7E))) {
		return TRUE;
	} else {
		return FALSE;
	}
}
