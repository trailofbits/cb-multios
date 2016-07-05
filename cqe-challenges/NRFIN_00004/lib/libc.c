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

int sendall(int fd, const char *buf, size_t size) {
    size_t sent = 0;
    size_t total = 0;
    char to_send = '\0';

    if (!buf)
        return -1;

    if (!size)
        return 0;

    while (size) {
        to_send = *buf;
        if (transmit(fd, &to_send, 1, &sent))
            return -1;

        buf += sent;
        total += sent;
        size--;
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
    *(tmp)='\0';
    return tmp-s1;
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
