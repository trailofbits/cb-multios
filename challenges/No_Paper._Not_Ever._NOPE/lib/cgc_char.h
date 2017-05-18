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
#ifndef CHAR_H
#define CHAR_H 1
/**
 * Determine if a char is non-printable (not letter, digit, symbol)
 *
 * @param ch 	Char to test
 * @return TRUE if non-printable, else FALSE
 */
unsigned int cgc_is_non_printable(unsigned char ch);

/**
 * Determine if a char is printable (letter, digit, symbol)
 *
 * @param ch 	Char to test
 * @return TRUE if printable, else FALSE
 */
unsigned int cgc_is_printable(unsigned char ch);

/**
 * Determine if a char is letter
 *
 * @param ch 	Char to test
 * @return TRUE if letter, else FALSE
 */
unsigned int cgc_is_letter(unsigned char ch);

/**
 * Determine if a char is digit
 *
 * @param ch 	Char to test
 * @return TRUE if digit, else FALSE
 */
unsigned int cgc_is_digit(unsigned char ch);

/**
 * Determine if a char is symbol
 *
 * @param ch 	Char to test
 * @return TRUE if symbol, else FALSE
 */
unsigned int cgc_is_symbol(unsigned char ch);

/**
 * Determine if a char is upper case letter
 *
 * @param ch 	Char to test
 * @return TRUE if upper, else FALSE
 */
unsigned int cgc_is_upper(unsigned char ch);

/**
 * Determine if a char is lower case letter
 *
 * @param ch 	Char to test
 * @return TRUE if lower, else FALSE
 */
unsigned int cgc_is_lower(unsigned char ch);

/**
 * Determine if a char is white-space token
 *
 * @param ch 	Char to test
 * @return TRUE if white-space, else FALSE
 */
unsigned int cgc_is_white_space(unsigned char ch);

#endif