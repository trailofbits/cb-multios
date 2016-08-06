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

void promptc(char *buf, uint16_t  size, char *prompt) {

    SSEND(strlen(prompt), prompt);

    SRECV((uint32_t)size, buf);
 }

int sendall(int fd, const char *buf, size_t size) {
    size_t sent = 0;
    size_t total = 0;

    if (!buf)
        return -1;

    if (!size)
        return 0;

    while (size) {
        if (transmit(fd, buf, size, &sent)){
            return -1;
        }

        buf += sent;
        total += sent;
        size -= sent;
    }

    return total;
}


int sendline(int fd, const char *buf, size_t size) {
    int ret;
    ret = sendall(fd, buf, size);
    if(ret < 0){
        return ret;
    } else {
        if (transmit(fd, "\n", 1, &size))
            return -1;
        else
            return ++ret;
    }
}

int recv(int fd, char *buf, size_t size) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (receive(fd, buf++, 1, &bytes_read))
            return -1;
        
        total_read++;
        size--;
    }

    return total_read;

}
int recvline(int fd, char *buf, size_t size) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (receive(fd, buf++, 1, &bytes_read))
            return -1;
        
        total_read++;
        size--;
        
        if(*(buf-1) == '\n')
            break;
    }

    if (*(buf-1) != '\n')
        return -2;
    else
        *(buf-1) = '\0';

    return total_read;
}

//non-standard convention, returns num bytes copied instead of s1
size_t strcpy(char *s1, char *s2) {
    char *tmp = s1;
    while(*s2){
        *tmp = *s2;
        tmp++;
        s2++;
    }
    *(tmp++)='\0';
    return tmp-s1-1;
}

//non-standard convention, returns num bytes copied instead of s1
size_t strncpy(char *s1, char *s2, size_t n) {
    char *tmp = s1;
    while((tmp-s1 < n) && *s2){
        *tmp = *s2;
        tmp++;
        s2++;
    }
    *(tmp++)='\0';
    return tmp-s1-1;
}

char * strcat(char *s1, char *s2) {
    char *tmp = s1;
    while(*tmp) tmp++;
    strcpy(tmp,s2);
    return s1;
}

size_t strlen(char *s){
    char *tmp = s;
    while(*tmp) tmp++;
    return (size_t)(tmp-s);
}

int streq(char *s1, char *s2){
    while(*s1 && *s2){
        if(*s1 != *s2)
            return 0;
	s1++;
	s2++;
    }
    return (*s1 == '\0') && (*s2 == '\0');
}

int startswith(char *s1, char *s2){
    while(*s1 && *s2){
        if(*s1 != *s2)
            return 0;
	s1++;
	s2++;
    }
    return *s2 == '\0';
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

// takes a string and converts it to an int32
// MAX int32 is +/- 2^31-1 (2,147,483,647) which is 10 digits
// returns 0 if str_buf is "0" or has no digits.
uint32_t str2uint(const char* str_buf) {
    int result = 0;
    int temp = 0;
    int max_chars = 10; // max number of chars read from str_buf
    int i = 0;

    if (str_buf == NULL)
        return result;

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

    return result;
}

void * memset(void *dst, char c, size_t n) {
    size_t i;
    for(i=0; i<n; i++){
        *((uint8_t*)dst+i) = c;
    }
    return dst;
}

void * memcpy(void *dst, void *src, size_t n) {
    size_t i;
    for(i=0; i<n; i++){
        *((uint8_t*)dst+i) = *((uint8_t*)src+i);
    }
    return dst;
}

char * b2hex(uint8_t b, char *h) {
    if (b>>4 < 10)
        h[0] = (b>>4)+0x30;
    else
        h[0] = (b>>4)+0x41-10;

    if ((b&0xf) < 10)
        h[1] = (b&0xf)+0x30;
    else
        h[1] = (b&0xf)+0x41-10;
    h[2] = '\0';
    return h;
}

char * strchr(char *str, char c) {
    char *tmp = str;
    while(*tmp){
        if(*tmp == c)
            return tmp;
        tmp++;
    }
    return 0;
}

//modulus
int __umoddi3(int a, int b) {
    return a-(a/b*b);
}

void sleep(int s) {
    struct timeval tv;
    tv.tv_sec = s;
    tv.tv_usec = 0;
    fdwait(0, NULL, NULL, &tv, NULL);
}
