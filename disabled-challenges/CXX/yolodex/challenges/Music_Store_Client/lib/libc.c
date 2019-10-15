#include "libcgc.h"
#include "cgc_libc.h"

void cgc_bzero(char *buf, int n);
int cgc_ready(int fd);

void cgc_bzero(char *buf, int n) {
    for (int i = 0; i < n; i++) {
        buf[i] = 0;
    }
}

int cgc_ready(int fd) {
    cgc_fd_set write_fds;
    int err;
    int ready_fd;
    struct cgc_timeval tv;

    cgc_bzero((char *)&write_fds, sizeof(write_fds));
    FD_SET(fd, &write_fds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    err = cgc_fdwait(fd + 1, NULL, &write_fds, &tv, &ready_fd);
    if (err != 0) {
        return err;
    }
    
    if (!FD_ISSET(ready_fd, &write_fds))
        cgc__terminate(11);

    return 0;
}

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;


    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

cgc_size_t cgc_strlen(const char *string) {
    cgc_size_t size = 0;
    
    while(1) {
        if(string[size] == '\0')
            return size;
        size++;
    }
}

// copy cnt bytes from src into dst; src and dst cannot overlap!
void * cgc_memcpy(void* dst, const void* src, cgc_size_t cnt) {

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
void * cgc_memset(void* str, int ch, cgc_size_t n) {
    unsigned char *ch_ptr = str;
    while (n > 0) {
        *ch_ptr = (unsigned char)ch;
        ch_ptr++;
        n--;
    }

    return str;
}


int cgc_strcmp(const char* string1, const char* string2)
{
    int pos;

    for(pos = 0; string1[pos] != '\0' && string1[pos] == string2[pos]; pos++);
    
    return string1[pos] - string2[pos];
}

// mod from FASTLANE: lines terminated with \x07, diff return values, 
int cgc_recvline(int fd, char *buf, cgc_size_t size) {
    cgc_size_t bytes_read = 0;
    cgc_size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -7;

    while (size) {
        if (cgc_receive(fd, buf++, 1, &bytes_read))
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

char* cgc_strcat(char *dest, const char* src)
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
int cgc_str2int(const char* str_buf) {
    int result = 0;
    int temp = 0;
    int max_chars = 10; // max number of chars cgc_read from str_buf
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