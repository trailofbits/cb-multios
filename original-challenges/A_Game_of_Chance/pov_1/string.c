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
#include <libcgc.h>
#include "libc.h"
#include "string.h"

int streq(const char *str1, const char *str2, const char term) {

    if (strlen_(str1, term) != strlen_(str2, term))
        return -1;

    while(*str1 != term) {
        if (*str1++ != *str2++)
            return -1;
    }

    return 0;
}

// int strcmp(const char *str1, const char *str2, const char term) {

//     while ((*str1 != term) && (*str2 != term) && (*str1 == *str2)) {
//         str1++;
//         str2++;
//     }

//     if ((*str1 == term) && (*str2 == term)) {
//         return 0;
//     } else if (*str1 < *str2) {
//         return -1;
//     } else  {
//         return 1;
//     }
// }

unsigned int strlen_(const char *str, const char term) {

	if (NULL == str) {
		return 0;
	}

    unsigned int len = 0;
    while (term != *str) {
        str++;
        len++;
    }

    return len;
}
