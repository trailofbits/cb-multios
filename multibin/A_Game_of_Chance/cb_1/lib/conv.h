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
#pragma once

#include <libcgc.h>


/**
 * Is the char a digit.
 *
 * digit: '0' - '9'
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_digit(const unsigned char ch);

/**
 * Is the char a hex digit.
 *
 * hex digits: '0' - '9', 'a' - 'f', 'A' - 'F', 
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */

unsigned char is_hexdigit(const unsigned char ch);

/**
 * Is the char a letter.
 *
 * letters: 'a' - 'z', 'A' - 'Z'
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_letter(const unsigned char ch);

/**
 * Is the char an ASCII printable symbol
 *
 * symbols:  0x20 - 0x2F, 0x3A - 0x40, 0x5B - 0x60, 0x7B - 0x7E
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_symbol(const unsigned char ch);

/**
 * Is the char an upper case letter.
 *
 * letters: 'A' - 'Z'
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_upper(const unsigned char ch);

/**
 * Is the char a lower case letter.
 *
 * letters: 'a' - 'z'
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_lower(const unsigned char ch);

/**
 * Is the char non-printable
 *
 * non-printable: 0x0 - 0x1F, 0x7F
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_non_printable(const unsigned char ch);

/**
 * Is the char ASCII printable
 *
 * printable: 0x21 - 0x7E
 * @param ch Char to test
 * @return TRUE if yes, FALSE if no
 */
unsigned char is_printable(const unsigned char ch);


/**
 * Convert c to an uppercase alphabet character if possible.
 *
 * @param c The char to examine
 * @return c as an uppercase alphabet character if possible, else c
 */
int toupper(int c);

/**
 * Convert c to a lowercase alphabet character if possible.
 *
 * @param c The char to examine
 * @return c as a lowercase alphabet character if possible, else c
 */
int tolower(int c);

/**
 * Convert value to a digit in a given base if possible, e.g. 0-15 -> '0'-'f' in
 * hexadecimal.
 *
 * @param value The value to convert
 * @param base The base to use
 * @return The character representing value in base, or '\0'
 */
char todigit(unsigned int value, unsigned int base);

/**
 * Convert c to a value in a given base if possible, e.g. '0'-'f' -> 0-15 in
 * hexadecimal.
 *
 * @param digit The digit to convert
 * @param base The base to use
 * @return The value of digit in base, or ERRNO_CONV
 */
int fromdigit(char digit, unsigned int base);

/**
 * Convert an int into its hex representation and store in a char *.
 *
 * @param hex 	Buffer of size at least 5 to store hex chars
 * @param val 	Int val to conver to hex
 * @param term 	Char to terminate hex string.
 * @return Pointer to updated hex buffer (lowercase hex chars are used).
 */
char *itohex(char *hex, int val, char term);

/**
 * Convert an unsigned int to an ASCII string.
 * Note: str must be large enough to fit the number(s) and term char.
 *
 * @param str Destination buffer
 * @param n Number of bytes str_buf can hold
 * @param i An unsigned integer
 * @param term String termination char
 * @return 0, -1 on error
 */
int utostr(char* str, unsigned int n, unsigned int i, const char term);

/**
 * Convert an int to an ASCII string.
 * Note: str must be large enough to fit the sign, number(s), and term char.
 *
 * @param str Destination buffer
 * @param n Number of bytes str_buf can hold
 * @param i An integer
 * @param term String termination char
 * @return 0, -1 on error
 */
int itostr(char *str, unsigned int n, int i, const char term);

/**
 * Convert string representation of a number in base to an unsigned int value.
 *
 * @param str The str to convert
 * @param base The base to use
 * @param result Pointer to output result to
 * @return Characters used from str on success, else ERRNO_CONV
 */
ssize_t strtou(const char *str, unsigned int base, unsigned int *result);

/**
 * Convert string representation of a number in base to an int value.
 *
 * @param str The str to convert
 * @param base The base to use
 * @param result Pointer to output result to
 * @return Characters used from str on success, else ERRNO_CONV
 */
ssize_t strtoi(const char *str, unsigned int base, int *result);
