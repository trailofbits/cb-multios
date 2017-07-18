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

#include "cgc_libc.h"

// NOTE: not POSIX
// MOD: it works in reverse
// RETURN: void
void cgc_memcpy(unsigned char *dst, const unsigned char *src, cgc_size_t n) {

    while (n) {
        dst[n-1] = src[n-1];
        n--;
    }
}

// NOTE: not POSIX
// MOD: returns +/- i (the iterator)
// RETURN: +/- i
int cgc_memcmp(const char *s1, const char *s2, cgc_size_t n) {

    int i = 1;
    while (i < n) {
        if ((unsigned char)s1[i-1] > (unsigned char)s2[i-1]) {
            return i;
        } else if ((unsigned char)s1[i-1] < (unsigned char)s2[i-1]) {
            return -i;
        }
        i++;
    }

    return 0;
}

// NOTE: not POSIX
// MOD: it works in reverse
// RETURN: the first argument
unsigned char * cgc_memset(unsigned char *b, unsigned char c, cgc_size_t len) {

    cgc_size_t i = 0;
    while (len) {
        b[len-1] = c;
        len--;
    }
    return b;
}

// Like strtok, except it's dumb and only finds the first instance.
// RETURN: location of the needle, -1 on error
cgc_size_t cgc_findchar(char *haystack, char needle) {

    cgc_size_t i = 0;
    while ('\0' != haystack[i]) {
        if (haystack[i] == needle) { return i; }
        i++;
    }
    return -1;
}

// Emulate sleep() via a timeout given to cgc_fdwait().
void cgc_pause(cgc_size_t usec) {

    struct cgc_timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = usec;

    cgc_fdwait(0, NULL, NULL, &tv, NULL);
}

// hack because sizeof(MY_STRING) returns the length with NULL and that's messy
// also it makes this libc a little different
int cgc_sendallnulltrunc(int fd, const char *buf, cgc_size_t size) {

    int ret = SUCCESS;

    if ('\0' == buf[size-1]) {
        return cgc_sendall(fd, buf, size-1) + 1;
    }

    return cgc_sendall(fd, buf, size);
}

int cgc_sendall(int fd, const char *buf, cgc_size_t size) {

    cgc_size_t sent = 0;
    char *curbuf = (char *)buf;

    while ((curbuf-(char*)buf) < size) {
        if (cgc_transmit(fd, curbuf, size-(curbuf-(char*)buf), &sent)) {
            return -1;
        }
        
        curbuf += sent;
    }

    return (cgc_size_t)(curbuf-(char*)buf);
}

// raise x to the power of y, modulo UINT32
// implemented as a recusive function for flair
UINT32 cgc_my_pow(UINT32 x, UINT32 y) {

    // base case: anything raised to 0 is 1
    if (0 == y) { return 1; }

    // divide (in halves) and conquer
    UINT32 halve = cgc_my_pow(x, y/2) * cgc_my_pow(x, y/2);
    if (0 != y%2) {
        return x * halve;
    }
    return halve;
}

// given a char array of hex values, convert it into a UINT32
// goes until the NULL or 4 bytes, whichever is shorter
// 0xFFFFFFFF is an error value
#define ERR_hex2UINT32 "invalid hex\n"
UINT32 cgc_hex2UINT32(char *hex) {

    int ret = SUCCESS;
    UINT32 result = 0;
    cgc_size_t i = 0;
    UINT8 len = 0;
    char curr;

    for (len=0; '\0' != hex[len]; ++len);

    for (i=0; i<8; ++i, --len) {
        curr = hex[i];
        if ('\0' == hex[i]) { break; }

        if ('0' <= curr && curr <= '9') {
            result += (curr-'0') * cgc_pow(16, len-1);
        } else if ('A' <= curr && curr <= 'F') {
            result += (curr-'A' + 10) * cgc_pow(16, len-1);
        } else if ('a' <= curr && curr <= 'f') {
            result += (curr-'a' + 10) * cgc_pow(16, len-1);
        } else {
            SENDNULLTRUNC(ERR_hex2UINT32, sizeof(ERR_hex2UINT32), ret);
            return 0xFFFFFFFF;
        }
    }

    return result;
}

// Read until size or we see a '\n'.
// If we receive 0 bytes, keep reading.  
// Reuse should not be concern; rewrote much from original function.
int cgc_recvline(int fd, char *buf, cgc_size_t size) {

    cgc_size_t bytes_read = 0;
    cgc_size_t cursize = size;

    if(!size)
        return 0;
 
    if (!buf)
        return -2;

    // While we still have bytes to cgc_read...
    while (0 != cursize) {

        bytes_read = 0;

        // Try reading 1 byte.
        // XXXX: We *shouldn't* need to check return value here.
        cgc_receive(fd, buf, 1, &bytes_read);
        buf += bytes_read;

        // If we cgc_read 0 bytes, we assume EOF; break.
        if (0 == bytes_read) { break; }

        // If we just cgc_read a newline, we're done; break.
        if ( *(buf-1) == '\n' ) { break; }

        // Subtract cursize by the number of bytes cgc_read.
        // This shouldn't underflow because we only request 1 byte at a time.
        cursize -= bytes_read;
    }

    if (*(buf-1) != '\n')
        return -1;
    else
        *(buf-1) = '\0';

    return size-cursize;
}


