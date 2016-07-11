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
#include "xxprintf.h"
#include "syslog.h"
#include "sendall.h"

// syslog
#define MAX_SYSLOG_LEN 1024 // max len of a syslog log entry

typedef struct _syslog_codes {
        char    *code_name;
        int     code_val;
} CODES;

CODES priorities_array[] =
  {
    { "EMERGENCY", LOG_EMERGENCY },
    { "ALERT", LOG_ALERT },
    { "CRITICAL", LOG_CRITICAL },
    { "ERROR", LOG_ERROR },
    { "WARNING", LOG_WARNING },
    { "NOTICE", LOG_NOTICE },
    { "INFO", LOG_INFO },
    { "DEBUG", LOG_DEBUG },
    { NULL, -1 }
  };

int syslog(int priority, const char *format, ...) {
    char log_entry[MAX_SYSLOG_LEN] = { 0 };
    char *log_entry_idx = log_entry;
    int ret;
    char *pri_str = priorities_array[priority].code_name;
    int log_entry_len;
    va_list args;

    // write priority to log_entry buffer
    log_entry_len = snprintf(log_entry_idx, MAX_SYSLOG_LEN, "~c: ", pri_str);
    log_entry_idx += log_entry_len;

    // process format string and write it to log_entry buffer
    va_start(args, format);
    log_entry_len += vsnprintf(log_entry_idx, MAX_SYSLOG_LEN - log_entry_len, format, args);
    va_end(args);

    // send log_entry to stdout
    ret = sendall(STDOUT, log_entry, (log_entry_len < MAX_SYSLOG_LEN ? log_entry_len : MAX_SYSLOG_LEN));
    if (ret != 0)
        _terminate(ERRNO_SEND);

    return 0;
}
