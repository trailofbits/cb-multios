/*

Author: Dustin Fraze (df@cromulence.com)

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "libc.h"

int strlen(char * string) {
    char *tmp;
    tmp = string;
    while(*tmp) {
        tmp++;
    }
    return tmp-string;
}

unsigned int atoi(char *number)
{
    int i;
    int ret = 0;
    int tmp;
    if(strlen(number) > 8)
        return 0;
    for(i=0;i<strlen(number);i++)
    {
        tmp = number[i]-'0';
        if(i == 0) {
            ret += tmp;
        }
        else {
            ret *= 10;
            ret += tmp;
        }
    }
    return ret;
}

char *itoa(unsigned int number)
{
    static char tmp[16];
    char *ret;
    int i;
    int remaining;
    ret = &tmp[15];

    remaining = number;
    bzero(tmp, 16);
    do {
        *--ret = '0' + (number % 10);
        number = number / 10;
    } while (number != 0);
    return ret;
}

int recvUntil(int fd, char *buf, int max, char delim)
{
    char got = -1;
    int i;
    char *tmp;
    tmp = buf;
    while(i < max && got != delim) {
        receive(0, &got, 1, NULL);
        *tmp = got;
        tmp++;
        i++;
    }
    buf[i-1] = 0; //get rid of delim
    return 0;
}

void bzero(char *what, int howmany) {
    char *tmp;
    int i;
    tmp = what;
    for(i=0;i<howmany;i++) {
        tmp[i] = (char)0;
    }
}

int put(char *string) {
    int i;
    size_t len = strlen(string);
    size_t tx_bytes;
    size_t total_sent = 0;
    int ret;

    while (total_sent < len) {
	    ret = transmit(1, string+total_sent, len-total_sent, &tx_bytes);
	    if (ret != 0 || tx_bytes == 0) {
		    _terminate(1);
            }
	    total_sent += tx_bytes;
    }
    return 0;
}

int memcpy(char *dst, char *src, int size) {
    while(size--)
        *dst++=*src++;
    return 0;
}
