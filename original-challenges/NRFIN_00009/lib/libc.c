#include <libcgc.h>
#include "libc.h"

void bzero(char *buf, int n);
int ready(int fd);

void bzero(char *buf, int n) {
    for (int i = 0; i < n; i++) {
        buf[i] = 0;
    }
}

int ready(int fd) {
    fd_set write_fds;
    int err;
    int ready_fd;
    struct timeval tv;

    bzero((char *)&write_fds, sizeof(write_fds));
    FD_SET(fd, &write_fds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    err = fdwait(fd + 1, NULL, &write_fds, &tv, &ready_fd);
    if (err != 0) {
        return err;
    }
    
    if (!FD_ISSET(ready_fd, &write_fds))
        _terminate(11);

    return 0;
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


int strcmp(const char* string1, const char* string2)
{
    int pos;

    for(pos = 0; string1[pos] != '\0' && string1[pos] == string2[pos]; pos++);
    
    return string1[pos] - string2[pos];
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

char* strcat(char *dest, const char* src)
{
    char* ret = dest;
    int pos1, pos2;

    for(pos1 = 0; dest[pos1] != '\0'; pos1++);
    for(pos2 = 0; (dest[pos1] = src[pos2]); pos1++, pos2++);

    return ret;
    
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