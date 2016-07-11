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

#ifndef NARF_LIBC_H
#define NARF_LIBC_H

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(al, lp)  __builtin_va_start(al, lp)
#define va_end(al)          __builtin_va_end(al)
#define va_arg(al, t)    __builtin_va_arg(al, t)
#define va_copy(d, s)       __builtin_va_copy(d, s)


#define isdigit(c)  ((c) >= '0' && (c) <= '9')

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

int prng_get_next();
int send(const char * buf, const size_t size);
int recv(char * res_buf, size_t res_buf_size, char * err_msg);
int prompt_user(char * prompt_str, char* res_buf, size_t res_buf_size, char * err_msg);
int recvline(int fd, char * buf, size_t size);
int syslog(int priority, const char *format, ...);
int vsnprintf(char * buf, size_t buf_size, const char * fmt, va_list args);
int snprintf(char * buf, size_t buf_size, const char * fmt, ...);
int sendall(int fd, const char * buf, const size_t size);
int streq(const char * str1, const char * str2);
unsigned int strlen(const char * str);
char * strncpy(char * dest, const char * src, size_t size);
char * strchr(char * str, char ch);
void * memset(void * str, int ch, size_t n);
void * memcpy(void * dst, const void * src, size_t cnt);
uint32_t str2uint32(const char * str_buf);
int str2int(const char * str_buf);
int int2str(char * str_buf, int buf_size, int i);
int is_numeric(const char * str);
void strip(char * str);
int rand(uint32_t *res);

#endif
