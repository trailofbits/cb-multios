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
 * Is the char a digit.
 *
 * digit: 0x30 - 0x39
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_digit(const unsigned char ch);

/**
 * Is the char a letter.
 *
 * letters: 0x41 - 0x5A, 0x61 - 0x7A
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_letter(const unsigned char ch);

/**
 * Is the char an ASCII printable symbol
 *
 * symbols:  0x21 - 0x2F, 0x3A - 0x40, 0x5B - 0x60, 0x7B - 0x7E
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_symbol(const unsigned char ch);

/**
 * Is the char an upper case letter.
 *
 * letters: 0x41 - 0x5A
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_upper(const unsigned char ch);

/**
 * Is the char a lower case letter.
 *
 * letters: 0x61 - 0x7A
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_lower(const unsigned char ch);

/**
 * Is the char non-printable
 *
 * non-printable: 0x0 - 0x1F, 0x7F
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_non_printable(const unsigned char ch);

/**
 * Is the char ASCII printable
 *
 * printable: 0x20 - 0x7E
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char cgc_is_printable(const unsigned char ch);

#endif
