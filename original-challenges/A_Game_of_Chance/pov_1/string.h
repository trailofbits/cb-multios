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

/**
 * Compares two strings for equal contents and length.
 *
 * @param str1 First string
 * @param str2 Second string
 * @param term String termination char
 * @return 0 if equal, -1 if not
 */
int streq(const char* str1, const char* str2, const char term);

/**
 * Compares two strings.
 *
 * @param str1 First string
 * @param str2 Second string
 * @param term String termination char
 * @return 0 if equal, -1 if str1 < str2, 1 if str1 > str2
 */
// int strcmp_(const char* str1, const char* str2, const char term);

/**
 * Count number of chars preceeding the term char.
 *
 * @param str Buffer
 * @param term String termination char
 * @returns Number of bytes preceeding the term char.
 */
unsigned int strlen_(const char *str, const char term);
