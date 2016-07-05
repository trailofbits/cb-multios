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

// doubly-linked list functions
// the nodes in the list should all be of the same type to be comparable.

// Allocates and initializes a list.
// RETURNS
//  success: &(the new list)
//  failure: NULL
list_t * list_create() {
  list_t *new = NULL;
  if (SUCCESS != (allocate(sizeof(list_t), 0, (void **)&new))) { return NULL; }
  new->head = NULL;
  new->tail = NULL;
  new->count = 0;
  return new;
}

// Append the provided node to the provided list.
// RETURNS
//  success: SUCCESS
int list_push(list_t *lst, node_t *nd) {

  int ret = SUCCESS;

  nd->next = NULL;
  nd->prev = lst->tail;

  // 0 elements (base case)
  if (NULL == lst->head) {
    lst->head = nd;
    lst->tail = nd;

  // >= 1 element
  } else {
    lst->tail->next = nd; 
    lst->tail = nd;
  }

  // increment count
  lst->count++;

  return ret;
}

// Allocate space for and initialize a new node struct.
// RETURNS:
//  success: VA of new node
//  failure: NULL
node_t * node_create(void * data) {
  node_t *new = NULL;
  if (SUCCESS != (allocate(sizeof(node_t), 0, (void **)&new))) { return NULL; }
  new->data = data;
  new->next = NULL; // these will be set during list insertion
  new->prev = NULL;
  return new;
}


// I/O functions

int send(const char *buf, const size_t size) {
    if(sendall(STDOUT, buf, size)) {
        _terminate(1);
    }

    return 0;
}

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

// returns number of bytes received
unsigned int recv_all(char *res_buf, size_t res_buf_size) {
    return read_all(STDIN, res_buf, res_buf_size);
}

// borrowed from REDPILL
unsigned int read_all(int fd, char *buf, unsigned int size) {
   char ch;
   unsigned int total = 0;
   size_t nbytes;
   while (size) {
      if (receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
         break;
      }
      buf[total++] = ch;
      size--;
   }
   return total;
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

// stdlib functions

// return number of chars in str, not counting the '\0'
unsigned int strlen(const char *str) {
    unsigned int count = 0;
    while(*str != '\0') {
        count++;
        str++;
    }

    return count;
}

// overwrites the first n chars of str with unsigned char ch.
void * memset(void* str, int ch, unsigned int n) {
    char *ch_ptr = (char*)str;
    while (n > 0) {
        *ch_ptr = (char)ch;
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

// returns 0 on success, non-zero on failure.
int rand(char *res, size_t len) {
    size_t bytes = 0;
    return random(res, len, &bytes);
}

// simple vsnprintf with supported format specifiers
//  - 'n' for numbers (signed ints)
//  - 'c' for char buffer (strings)
//  - 'o' for char (one single char)
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


// simple snprintf with supported format specifiers
//  - 'n' for numbers (signed ints)
//  - 'c' for char buffer (strings)
//  - 'o' for char (one single char)
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
