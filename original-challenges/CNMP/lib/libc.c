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


#define MAX_SYSLOG_LEN 1024 // max len of a syslog log entry

// syslog
#ifndef SYSLOG_NAMES
#define SYSLOG_NAMES
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

#endif

int sendall(int fd, const char *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;
    int ret;

    if (!buf) 
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

// mod from FASTLANE: lines terminated with \x07, diff return values, 
int recvline(int fd, char *buf, size_t size) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -7;

    while (size) {
        if (receive(fd, buf++, 1, &bytes_read))
            return -7;
        
        total_read++;
        size--;
        
        if(*(buf-1) == '\x07')
            break;
    }

    if (*(buf-1) != '\x07')
        return -77;
    else
        *(buf-1) = '\0';

    return total_read;
}

int syslog(int priority, const char *format, ...) {
    char log_entry[MAX_SYSLOG_LEN] = { 0 };
    char *log_entry_idx = log_entry;
    int ret;
    char *pri_str = priorities_array[priority].code_name;
    int log_entry_len;
    va_list args;

    va_start(args, format);
    // write priority to log_entry buffer
    log_entry_len = snprintf(log_entry_idx, MAX_SYSLOG_LEN, "~c: ", pri_str);
    log_entry_idx += log_entry_len;

    // process format string and write it to log_entry buffer
    log_entry_len += vsnprintf(log_entry_idx, MAX_SYSLOG_LEN - log_entry_len, format, args);
    va_end(args);

    // send log_entry to stdout
    ret = sendall(STDERR, log_entry, (log_entry_len < MAX_SYSLOG_LEN ? log_entry_len : MAX_SYSLOG_LEN));
    if (ret != 0)
        _terminate(4);

    return 0;
}

// return 0 if str1 == str2, else return -1
int streq(const char* str1, const char* str2) {

    if (strlen(str1) != strlen(str2))
        return -1;

    while(*str1 != '\0') {
        if (*str1++ != *str2++)
            return -1;
    }

    return 0;
}

// return number of chars in str, not counting the '\0'
unsigned int strlen(const char *str) {
    unsigned int count = 0;
    while(*str != '\0') {
        count++;
        str++;
    }

    return count;
}

// size bytes of src are copied into dest.
// if strlen(src) < size, dest is padded with '\0' bytes.
// NOTE: if size <= strlen(src), the dest will not be null terminated.
char * strncpy(char* dest, const char* src, size_t size) {

    int idx = 0;
    for (; idx < size && src[idx] != '\0'; idx++) {
        dest[idx] = src[idx];
    }

    for (; idx < size; idx++) {
        dest[idx] = '\0';
    }

    return dest;
}

// overwrites the first n chars of str with unsigned char ch.
void * memset(void* str, int ch, size_t n) {
    unsigned char *ch_ptr = str;
    while (n > 0) {
        *ch_ptr = (unsigned char)ch;
        ch_ptr++;
        n--;
    }

    return str;
}

// copy cnt bytes from src into dst; src and dst cannot overlap!
void * memcpy(void* dst, const void* src, size_t cnt) {

    uint8_t *dst_ptr = (uint8_t *) dst;
    uint8_t *src_ptr = (uint8_t *) src;
    while (cnt--) {
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
    }

    return dst;
}

// find index of char 'ch' in char buffer 'str'
// return pointer to index of ch if found
// return NULL if ch is not found
char * strchr(char *str, char ch) {

    while (*str != '\0') {
        if (*str == ch)
            return str;
        else
            str++;

    }

    return NULL;
}

// write a random number between 0 and (2^32) in res
// returns 0 on success, non-zero on failure.
int rand(uint32_t * res) {
    size_t bytes = 0;
    return random((char *)res, 4, &bytes);
}

// simple vsnprintf with supported format specifiers
//  - 'n' for numbers (signed ints)
//  - 'c' for char buffer (strings)
// the format string marker is '~'
// at this point, it's basically a string insertion routine
// no support for padding, precision or field width
// for each format specifier, it will take a value from args
//  and insert it at that location as that type.
// buf - ptr to output buffer
// size - max number of chars to copy into buf
// fmt - null-terminated format string
// args - ptr to list of arguments to insert into fmt
// returns number of bytes written to buf, not counting '\0'
// note: vsnprintf does not call va_end, because it takes a va_list, caller does so.
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
            const char *next_arg;  // ptr to the next arg in args (to use this iteration)
            char tmp[32]; // tmp buffer for int2str conversion
            int int_arg = 0;
            int remaining = 0;

            fmt_ptr++; // skip the '~'

            // no flags, precision, or width, so just get specifier
            fmt_spec = *fmt_ptr;
            switch(fmt_spec) {
                case 'n': // deal with number
                    int_arg = 0;
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


// simple snprintf with supported format specifiers
//  - 'n' for numbers (signed ints)
//  - 'c' for char buffer (strings)
// the format string marker is '~'
// at this point, it's basically a string insertion routine
// no support for padding, precision or field width
// for each format specifier, it will take a value from args
//  and insert it at that location as that type.
// buf - ptr to output buffer
// size - max number of chars to copy into buf
// fmt - null-terminated format string
// ... - optional arguments for strings to insert into fmt
// returns number of bytes written to buf, not counting '\0'
int snprintf(char* buf, size_t buf_size, const char* fmt, ...) {
    int buf_len;
    va_list args;

    va_start(args, fmt);
    buf_len = vsnprintf(buf, buf_size, fmt, args);
    va_end(args);

    return buf_len;
}


// takes a string and converts it to a uint32
// MAX uint32 is 2^32 which is 10 digits
// returns 0 if str_buf is "0", has no digits, or if there is an error.
uint32_t str2uint32(const char* str_buf) {
    uint32_t result = 0;
    uint32_t temp = 0;
    uint32_t max_chars = 10;

    if (str_buf == NULL)
        return result;

    for (int i = 0; i < max_chars; i++) {
        if ( (str_buf[i] == '0') ||
             (str_buf[i] == '1') ||
             (str_buf[i] == '2') ||
             (str_buf[i] == '3') ||
             (str_buf[i] == '4') ||
             (str_buf[i] == '5') ||
             (str_buf[i] == '6') ||
             (str_buf[i] == '7') ||
             (str_buf[i] == '8') ||
             (str_buf[i] == '9') ) {
            result *= 10;
            temp = str_buf[i] - '0';
            result += temp;

        } else {
            break;
        }
    }

    return result;
}

// takes a string and converts it to an int32
// MAX int32 is +/- 2^31-1 (2,147,483,647) which is 10 digits
// returns 0 if str_buf is "0" or has no digits.
int str2int(const char* str_buf) {
    int result = 0;
    int temp = 0;
    int max_chars = 10; // max number of chars read from str_buf
    int i = 0;
    int sign = 1; // 1 for pos, -1 for neg

    if (str_buf == NULL)
        return result;

    // if the number is negative, change sign, increment 'i' and 'max_chars' by one
    if (str_buf[0] == '-') {
        sign = -1;
        i++;
        max_chars++;
    }

    for (; i < max_chars; i++) {
        if ( (str_buf[i] == '0') ||
             (str_buf[i] == '1') ||
             (str_buf[i] == '2') ||
             (str_buf[i] == '3') ||
             (str_buf[i] == '4') ||
             (str_buf[i] == '5') ||
             (str_buf[i] == '6') ||
             (str_buf[i] == '7') ||
             (str_buf[i] == '8') ||
             (str_buf[i] == '9') ) {
            result *= 10;
            temp = str_buf[i] - '0';
            result += temp;

        } else {
            break;
        }
    }

    return result * sign;
}

// takes an int32 and converts it to a string saved in str_buf
// str_buf must be large enough to fit the sign, number(s), and '\0'
// returns 0 on success, -1 if error due to buf_size
int int2str(char* str_buf, int buf_size, int i) {

    int idx = 0;
    int tmp;
    int digit;

    // at least fits 1 digit and '\0'
    if (buf_size < 2) {
        return -1;
    }

    if (i < 0) {
        if (buf_size < 3)
            return -1;
        str_buf[idx++] = '-';
    } else {
        i *= -1; // make i negative
    }

    // i is always 0 or negative at this point.
    tmp = i;

    // increment index in str_buf to where rightmost digit goes
    do {
        idx++;
        tmp = tmp/10;
    } while(tmp < 0);

    // see if this number will fit in the buffer
    if (idx >= buf_size)
        return -1;

    //testing
    // str_buf[0] = '0' - i;
    // str_buf[1] = '\0';

    // insert '\0'
    str_buf[idx--] = '\0';

    // move left through string, writing digits along the way
    do {
        digit = -1 * (i % 10);
        str_buf[idx--] = '0' + digit;
        i /= 10;

    } while (i < 0);

    return 0;
}

// examine str to determine if it can be converted to a number
// return 0 if yes and 0/positive, 1 if yes and negative, -1 if no.
int is_numeric(const char *str) {
    int sign = 0;

    if (strlen(str) == 0)
        return -1;

    if (*str == '-') {
        str++;
        sign = 1;
    }

    while (*str != '\0') {
        if (*str < '0' || *str > '9')
            return -1;
        str++;
    }
    return sign;
}

// remove \t, \r, \n, and space from end of string
void strip(char *str) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == '\n' ||
            str[i] == '\t' ||
            str[i] == '\r' ||
            str[i] == ' ') {

            str[i] = '\0';
        } else {
            break;
        }
    }
}