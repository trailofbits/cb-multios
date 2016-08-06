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

#ifndef SYSLOG_H
#define SYSLOG_H 1

// syslog priorities
#define LOG_DEBUG 7		// debug-level message
#define LOG_INFO 6		// informational message
#define LOG_NOTICE 5	// normal, but interesting condition
#define LOG_WARNING 4	// warning condition
#define LOG_ERROR 3		// error condition
#define LOG_CRITICAL 2	// critical condition
#define LOG_ALERT 1		// immediate action required
#define LOG_EMERGENCY 0 // system is unusable
#define LOGLEVEL LOG_INFO

/**
 * Write syslog string to STDERR
 * Terminates with ERRNO_SEND on a failed send
 *
 * @param priority Syslog priority level
 * @param format Format string
 * @param ... Variable argument list to fill into format string
 * @return 0
 */
extern int syslog(int priority, const char *format, ...);

#endif