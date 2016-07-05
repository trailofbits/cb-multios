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

int recv(int fd, char *buf, size_t size) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if (!size)
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

// mod from NRFIN_00001: lines terminated with 
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
        
        if(*(buf-1) == '\x0a')
            break;
    }

    if (*(buf-1) != '\x0a')
        return -77;
    else
        *(buf-1) = '\0';

    return total_read;
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

char* strcat(char *dest, const char* src)
{
    char* ret = dest;
    int pos1, pos2;

    for(pos1 = 0; dest[pos1] != '\0'; pos1++);
    for(pos2 = 0; (dest[pos1] = src[pos2]); pos1++, pos2++);

    return ret;
    
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

int transmit_all(int fd, const char *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;
    int ret;


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

size_t strlen(const char *string) {
    size_t size = 0;
    
    while(1) {
        if(string[size] == '\0')
            return size;
        size++;
    }
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