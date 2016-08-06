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

#ifndef XXPRINTF_H
#define XXPRINTF_H 1


// VA defs for xxprintf functions
#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST 1
#endif

/**
 * Initialize a variable arguments list.
 *
 * @param al Arguments list
 * @param lp Last parameter before variable argument list.
 * @return Initialized variable arguments list in al.
 */
#define va_start(al, lp)  __builtin_va_start(al, lp)

/**
 * Signal no further arguments and invalidate arguments list.
 *
 * @param al Arguments list
 */
#define va_end(al)          __builtin_va_end(al)

/**
 * Expand to an expression that has the type and value of the 
 *  next argement in the function call.
 *
 * @param al Arguments list
 * @param t Type
 * @return Expression that has given type and value of next argument
 */
#define va_arg(al, t)    __builtin_va_arg(al, t)

/**
 * Copy the state of the variable agruments list, s, which was previously
 *  initialized by va_start(), to the varible arguments list, d, which was
 *  NOT previously initialized by va_start(), without an intervening call
 *  to va_end().
 *
 * @param d Destination variable arguments list
 * @param s Source variable arguments list
 */
#define va_copy(d, s)       __builtin_va_copy(d, s)

/**
 * A simple, non-standard vsnprintf.
 *
 * Supported format specifiers:
 *  'n' for numbers (signed ints)
 *  'c' for char buffer (strings)
 *  'o' for char (one single char)
 *
 * Format string marker is '~'
 *
 * At this point, it's basically a string insertion routine
 *  with no support for padding, precision or field width.
 * For each format specifier, it will take a value from args
 *  and insert it at that location as that type.
 *
 * Note: vsnprintf does not call va_end, because it takes a va_list, 
 *  caller does so.
 *
 * @param buf Output buffer
 * @param size Max number of chars to copy into buf
 * @param fmt Null-terminated format string
 * @param args Ptr to va_list of arguments to insert into fmt
 * @return Number of bytes written to buf, not counting '\0'
 */
int vsnprintf(char * buf, size_t buf_size, const char * fmt, va_list args);

/**
 * A simple, non-standard snprintf.
 *
 * Supported format specifiers:
 *  'n' for numbers (signed ints)
 *  'c' for char buffer (strings)
 *  'o' for char (one single char)
 *
 * Format string marker is '~'
 *
 * At this point, it's basically a string insertion routine
 *  with no support for padding, precision or field width.
 * For each format specifier, it will take a value from args
 *  and insert it at that location as that type.
 *
 * Note: vsnprintf does not call va_end, because it takes a va_list, 
 *  caller does so.
 *
 * @param buf Output buffer
 * @param size Max number of chars to copy into buf
 * @param fmt Null-terminated format string
 * @param ... Optional arguments to insert into fmt
 * @return Number of bytes written to buf, not counting '\0'
 */
int snprintf(char * buf, size_t buf_size, const char * fmt, ...);

#endif