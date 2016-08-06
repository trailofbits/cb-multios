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
#include <stdint.h>
#include "char.h"

unsigned int is_non_printable(unsigned char ch) {
	return (FALSE == is_printable(ch));
}

unsigned int is_printable(unsigned char ch) {
	return (is_digit(ch)  ||
			is_letter(ch) ||
			is_symbol(ch) ||
			is_white_space(ch));
}

unsigned int is_letter(unsigned char ch) {
	return (is_upper(ch) || is_lower(ch));
}

unsigned int is_digit(unsigned char ch) {
	return (('0' <= ch) && (ch <= '9'));
}

unsigned int is_symbol(unsigned char ch) {
	return ((('!' <= ch) && (ch <='@'))  ||
			(('[' <= ch) && (ch <= '`')) ||
			(('{' <= ch) && (ch <= '~')));
}

unsigned int is_upper(unsigned char ch) {
	return (('A' <= ch) && (ch <= 'Z'));
}

unsigned int is_lower(unsigned char ch) {
	return (('a' <= ch) && (ch <= 'z'));
}

unsigned int is_white_space(unsigned char ch) {
	return ((' ' == ch)  || 
			('\n' == ch) || 
			('\t' == ch) || 
			('\r' == ch));
}
