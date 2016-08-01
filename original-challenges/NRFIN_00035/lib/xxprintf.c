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

#include "libc.h"
#include "strlen.h"
#include "int2str.h"
#include "xxprintf.h"

int vsnprintf(char* buf, size_t buf_size, const char* fmt, va_list args) {

    size_t buf_len = 0;
    const char *fmt_ptr = fmt;

    // if fmt is NULL, set fmt_ptr to "" so it will skip the while loop
    if (!fmt_ptr)
        fmt_ptr = "";

    // walk through format string
    while (*fmt_ptr != '\0') {
        if (*fmt_ptr != '~') {
            if (buf_len < buf_size) {
                buf[buf_len++] = *fmt_ptr++;
            } else {
                // buf is full
                // count number of bytes that should have been written given sufficient space
                buf_len++;
                // go to next char in fmt.
                fmt_ptr++; 
            }

        } else {
            char fmt_spec = '\0';
            size_t arg_len = 0;
            unsigned char next_ch = 0;
            const char *next_arg = NULL;  // ptr to the next arg in args (to use this iteration)
            char tmp[32]; // tmp buffer for int2str conversion
            int int_arg = 0;
            int remaining = 0;

            fmt_ptr++; // skip the '~'

            // no flags, precision, or width, so just get specifier
            fmt_spec = *fmt_ptr;
            switch(fmt_spec) {
                case 'n': // deal with number
                    int_arg = va_arg(args, int);
                    int2str(tmp, 32, int_arg);
                    next_arg = tmp;
                    arg_len = strlen(next_arg);

                    break; 
                case 'c': // deal with char buffer (i.e. string)
                    next_arg = va_arg(args, const char *);
                    if (!next_arg) {
                        arg_len = 0;
                    } else { 
                        arg_len = strlen(next_arg);
                    } 

                    break; 
                case 'o': // deal with single char
                    next_ch = (unsigned char)(unsigned int)va_arg(args, unsigned int);
                    if (!next_arg) {
                        arg_len = 0;
                    } else {
                        arg_len = 1;
                    }
                    break;

                default: break;
            }

            if (fmt_spec == 'n' || fmt_spec == 'c') {
                remaining = buf_size - buf_len;
                if (arg_len <= remaining) {
                    memcpy(&buf[buf_len], next_arg, arg_len);
                    buf_len += arg_len;
                } else {
                    memcpy(&buf[buf_len], next_arg, remaining);
                    buf_len += remaining;
                }
            }
            if (fmt_spec == 'o') {
                remaining = buf_size - buf_len;
                if (arg_len <= remaining) {
                    buf[buf_len] = next_ch;
                    buf_len++;
                }
            }

            if (*fmt_ptr != '\0')
                fmt_ptr++;  

        }
    }

    if (buf_size > 0) {
        if (buf_len < buf_size) {
            buf[buf_len] = '\0';
        }
        else {
            buf[buf_size - 1] = '\0';
        }
    }

    return (int) buf_len;

}

int snprintf(char* buf, size_t buf_size, const char* fmt, ...) {
    int buf_len;
    va_list args;

    va_start(args, fmt);
    buf_len = vsnprintf(buf, buf_size, fmt, args);
    va_end(args);

    return buf_len;
}
