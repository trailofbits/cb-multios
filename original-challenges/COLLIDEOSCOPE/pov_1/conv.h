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

#ifndef CONV_H_
#define CONV_H_

#include <libcgc.h>

/** Number of decimal values to include after the point in dtostr() */
#define DTOSTR_PRECISION 7

/**
 * Return 1 if c is a decimal digit, 0 otherwise.
 *
 * @param c The char to examine
 * @return 1 if c is a decimal digit, 0 otherwise
 */
int isdigit(int c);

/**
 * Return 1 if c is a hexadecmimal digit, 0 otherwise.
 *
 * @param c The char to examine
 * @return 1 if c is a hexadecimal digit, 0 otherwise
 */
int ishexdigit(int c);

/**
 * Return 1 if c is an uppercase or lowercase alphabet character, 0 otherwise.
 *
 * @param c The char to examine
 * @return 1 if c is an uppercase or lowercase alphabet character, 0 otherwise
 */
int isalpha(int c);

/**
 * Return 1 if c is an uppercase alphabet character, 0 otherwise.
 *
 * @param c The char to examine
 * @return 1 if c is an uppercase alphabet character, 0 otherwise
 */
int islower(int c);

/**
 * Return 1 if c is a lowercase alphabet character, 0 otherwise.
 *
 * @param c The char to examine
 * @return 1 if c is a lowercase alphabet character, 0 otherwise
 */
int isupper(int c);

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
 * @return The value of digit in base, or EXIT_FAILURE
 */
int fromdigit(char digit, unsigned int base);

/**
 * Convert unsigned int value to its string representation in base.
 *
 * @param value The value to convert
 * @param base The base to use
 * @param uppercase Should digits > '9' be represented as uppercase letters?
 * @param str The buffer to output to
 * @param num The maximum size of the buffer, including space for a NULL
 *      terminator
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
int utostr(unsigned int value, unsigned int base, int uppercase, char *str, size_t num);

/**
 * Convert int value to its string representation in base.
 *
 * @param value The value to convert
 * @param base The base to use
 * @param uppercase Should digits > '9' be represented as uppercase letters?
 * @param str The buffer to output to
 * @param num The maximum size of the buffer, including space for a NULL
 *      terminator
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
int itostr(int value, unsigned int base, int uppercase, char *str, size_t num);

/**
 * Convert double value to its string representation in base.
 *
 * Implements a very limited conversion from a double value to a string, notably
 * only works for fabs(value) < UINT_MAX + 1.0, provides 7 digit precision only,
 * and always floors the fractional component. Will detect inf/nan/(+/-)0.0
 * correctly.
 *
 * @param value The value to convert
 * @param str The buffer to output to
 * @param num The maximum size of the buffer, including space for a NULL
 *      terminator
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
int dtostr(double value, char *str, size_t num);

/**
 * Convert string representation of a number in base to an unsigned int value.
 *
 * @param str The str to convert
 * @param base The base to use
 * @param result Pointer to output result to
 * @return Characters used from str on success, else EXIT_FAILURE
 */
ssize_t strtou(char *str, unsigned int base, unsigned int *result);

/**
 * Convert string representation of a number in base to an int value.
 *
 * @param str The str to convert
 * @param base The base to use
 * @param result Pointer to output result to
 * @return Characters used from str on success, else EXIT_FAILURE
 */
ssize_t strtoi(char *str, unsigned int base, int *result);

/**
 * Convert string representation of a number to a double value.
 *
 * Implements a very limited conversion from a string to a double value, notably
 * only works for fabs(value) < UINT_MAX + 1.0. Does not preserve value of str.
 *
 * @param str The str to convert
 * @param result Pointer to output result to
 * @return Characters used from str on success, else EXIT_FAILURE
 */
ssize_t strtod(char *str, double *result);

#endif /* CONV_H_ */

