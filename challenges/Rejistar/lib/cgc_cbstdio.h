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
#ifdef WIN
#include <stdarg.h>
#else
typedef __builtin_va_list va_list;
#define va_start(al, lp)  __builtin_va_start(al, lp)
#define va_end(al)          __builtin_va_end(al)
#define va_arg(al, t)    __builtin_va_arg(al, t)
#endif


/**
* Store a formatted string into a buffer
*
* NOTES: sprintf initializes the va_list and then calls vsprintf
*
* FORMAT: By using '!', the next variable will be converted depending on the
*          character that follows and in the string. The following conversions
*          are supported:
*         'X' - string
*         'U' - unsigned integer value
*         'H' - unsigned hexadecimal value
*
* @param buffer Destination to store the string
* @param fmt The format of the string to store
* @param ... The list of arguments
* @return The number of characters stored in the buffer, or
*          a negative value if there was an error
*/
int cgc_sprintf(char *buf, const char* fmt, ...);
