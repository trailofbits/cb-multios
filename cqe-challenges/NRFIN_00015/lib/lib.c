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

// modified to remove "ret"
int transmit_all(int fd, const char *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;

    if (!size)
        return 2;

    while (sent < size) {
        if (transmit(fd, buf + sent, size - sent, &sent_now) != 0) {
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

int strncmp(const char *s1, const char *s2, size_t n)
{
     for(; n>0; s1++, s2++, --n)
     {
        if(*s1!=*s2)
            return *(const unsigned char*) s1 - *(const unsigned char*) s2;
     }

     return 0;
}

// modified to accept string length
// takes a string and converts it to an int32
// MAX int32 is +/- 2^31-1 (2,147,483,647) which is 10 digits
// returns 0 if str_buf is "0" or has no digits.
int strn2int(const char* str_buf, size_t max_chars) {
    int result = 0;
    int temp = 0;
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

// Modified to stop at a max length
size_t strnlen(const char *string, size_t max_len) {
    size_t size = 0;
    
    while(size < max_len) {
        if(string[size] == '\0')
            return size;
        size++;
    }

    return max_len;
}

size_t strlen(const char *string) {
    size_t size = 0;
    
    while(1) {
        if(string[size] == '\0')
            return size;
        size++;
    }
}

// Modified to not use malloc
char * itoaB10(int value){
    int max_width = MAX_WIDTH;
    int ret;
    char *s;
    char *f;

    ret = allocate (max_width, 0, (void **) &s);
    if (ret != 0)
        _terminate(3);

    //char *s = malloc(max_width); // max len of 2**32 + negative to be paranoid
    //if(s == NULL)
    //    return NULL;
    int tmp = value;
    
    if(value == 0){
        memcpy(s, "0\x00", 2);
        return s;
    }
    int neg = 0;
    if(value < 0){
        neg = 1;
        tmp = -tmp;
    }
    int i = 0;
    for(; i < max_width && tmp != 0; ++i){
        int r = tmp % 10;
        if(r > 9)
            s[i] = (r - 10) + 'a';
        else
            s[i] = r + '0';
        tmp = tmp/10;
    }

    if(neg == 1)
        s[i+1] = '-';


    ret = allocate (max_width, 0, (void **) &f);
    if (ret != 0)
        _terminate(3);

    //char *f = malloc(max_width);
    int final_len = strnlen(s, MAX_WIDTH);
    for(int j =0; j < final_len; ++j){
        f[j] = s[final_len-j-1];
    }
    
    ret = deallocate(s, MAX_WIDTH); 
    if (ret != 0)
        _terminate(3);
    
    return f;
}
