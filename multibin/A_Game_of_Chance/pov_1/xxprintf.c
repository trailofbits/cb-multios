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
#include <pov/types.h>
#include "memcpy.h"
#include "string.h"
#include "conv.h"
#include "xxprintf.h"
#include "send_bytes.h"


int vsnprintf(char* buf, size_t buf_size, const char fsm, const char term, const char* fmt, va_list args) {

    size_t buf_len = 0;
    const char *fmt_ptr = fmt;

    // if fmt is NULL, set fmt_ptr to "" so it will skip the while loop
    if (!fmt_ptr)
        fmt_ptr = &term;

    // walk through format string
    while (*fmt_ptr != term) {
        if (*fmt_ptr != fsm) {
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
            char fmt_spec = term;
            size_t arg_len = 0;
            unsigned char next_ch = 0;
            const char *next_arg = NULL;  // ptr to the next arg in args (to use this iteration)
            char tmp[32]; // tmp buffer for itoan conversion
            int int_arg = 0;
            int remaining = 0;

            fmt_ptr++; // skip the fsm

            if (*fmt_ptr == term) {
                continue;
            }

            // no flags, precision, or width, so just get specifier
            fmt_spec = *fmt_ptr;
            switch(fmt_spec) {
                case 'I': // deal with signed number
                    int_arg = va_arg(args, int);
                    itostr(tmp, 32, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);

                    break;
                case 'U': // deal with unsigned number
                    int_arg = va_arg(args, int);
                    utostr(tmp, 32, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);

                    break;
                case 'S': // deal with char buffer (i.e. string)
                    next_arg = va_arg(args, const char *);
                    if (!next_arg) {
                        arg_len = 0;
                    } else { 
                        arg_len = strlen_(next_arg, term);
                    }

                    break; 
                case 'L': // deal with single char
                    next_ch = (unsigned char)(unsigned int)va_arg(args, unsigned int);
                    if (!next_ch) {
                        arg_len = 0;
                    } else {
                        arg_len = 1;
                    }
                    break;
                case 'H': // deal with hex number (int to string formatted as hex)
                    int_arg = va_arg(args, int);
                    itohex(tmp, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);

                    break;

                default: break;
            }

            fmt_ptr++;  

            remaining = buf_size - buf_len;
            if (0 > remaining) {
                buf_len += arg_len;
                continue;
            }

            if (fmt_spec == 'I' || fmt_spec == 'S' || fmt_spec == 'U' || fmt_spec == 'H') {
                if (arg_len <= remaining) {
                    memcpy_(&buf[buf_len], next_arg, arg_len);
                    buf_len += arg_len;
                } else {
                    memcpy_(&buf[buf_len], next_arg, remaining);
                    buf_len += remaining;
                }
            }
            if (fmt_spec == 'L') {
                if (arg_len <= remaining) {
                    buf[buf_len] = next_ch;
                    buf_len += arg_len;
                }
            }


        }
    }

    if (buf_size > 0) {
        if (buf_len < buf_size) {
            buf[buf_len] = term;
        }
        else {
            buf[buf_size - 1] = term;
        }
    }

    return (int) buf_len;

}

int vfdprintf(int fd, const char fsm, const char term, const char *fmt, va_list args) {

    size_t bytes_sent = 0;
    const char *fmt_ptr = fmt;

    // if fmt is NULL, nothing to send, we are done.
    if (!fmt_ptr)
        return bytes_sent;

    // walk through format string
    while (*fmt_ptr != term) {
        if (*fmt_ptr != fsm) { // not fsm, so send char
            send_bytes(fd, fmt_ptr, 1);
            // go to next char in fmt.
            fmt_ptr++;
            bytes_sent++;

        } else { // is fsm, so skip fsm, parse fmt_spec, and send arg
            char fmt_spec = term;
            size_t arg_len = 0;
            unsigned char next_ch = 0;
            const char *next_arg = NULL;  // ptr to the next arg in args (to use this iteration)
            char tmp[32]; // tmp buffer for str<->number conversion
            int int_arg = 0;

            fmt_ptr++; // skip the fsm

            if (*fmt_ptr == term) {
                continue;
            }

            // no flags, precision, or width, so just process specifier
            fmt_spec = *fmt_ptr;
            switch(fmt_spec) {
                case 'I': // deal with signed number
                    int_arg = va_arg(args, int);
                    itostr(tmp, 32, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);
                    break;
                case 'U': // deal with unsigned number
                    int_arg = va_arg(args, int);
                    utostr(tmp, 32, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);

                    break;
                case 'S': // deal with char buffer (i.e. string)
                    next_arg = va_arg(args, const char *);
                    if (!next_arg) {
                        arg_len = 0;
                    } else { 
                        arg_len = strlen_(next_arg, term);
                    }

                    break; 
                case 'L': // deal with single char
                    next_ch = (unsigned char)(unsigned int)va_arg(args, unsigned int);
                    if (!next_ch) {
                        arg_len = 0;
                    } else {
                        arg_len = 1;
                    }
                    break;
                case 'H': // deal with hex number (int to string formatted as hex)
                    int_arg = va_arg(args, int);
                    itohex(tmp, int_arg, term);
                    next_arg = tmp;
                    arg_len = strlen_(next_arg, term);

                    break;

                default: break;
            }

            if (0 < arg_len) {
                if (0 != next_ch) {
                    bytes_sent += send_bytes(fd, (const char *)&next_ch, arg_len);
                } else {
                    bytes_sent += send_bytes(fd, next_arg, arg_len);
                }
            }

            fmt_ptr++; // skip the fmt_spec that was just processed
        }
    }

    return bytes_sent;
}

int snprintf(char* buf, size_t buf_size, const char fsm, const char term, const char* fmt, ...) {
    int buf_len;
    va_list args;

    va_start(args, fmt);
    buf_len = vsnprintf(buf, buf_size, fsm, term, fmt, args);
    va_end(args);

    return buf_len;
}

int fdprintf(int fd, const char fsm, const char term, const char *fmt, ...) {
    int bytes_sent;
    va_list args;

    va_start(args, fmt);
    bytes_sent = vfdprintf(fd, fsm, term, fmt, args);
    va_end(args);

    return bytes_sent;    
}

int fprintf(const char fsm, const char term, const char *fmt, ...) {
    int bytes_sent;
    va_list args;

    va_start(args, fmt);
    bytes_sent = vfdprintf(STDOUT, fsm, term, fmt, args);
    va_end(args);

    return bytes_sent;    
}

