#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"

#define MAX_PATTERN_SIZE 1024
int read_fd  = 4;
int write_fd = 4;
char pattern[MAX_PATTERN_SIZE];
int pattern_skip[MAX_PATTERN_SIZE];

char * read_buf(int fd) {
    size_t recv_size;
    size_t buf_size;
    char *buf = NULL;

    recv_size = receive_all(read_fd, (char *) &buf_size, sizeof(buf_size));
    if (recv_size != sizeof(buf_size))
        _terminate(1);

    if (buf_size > 0) {
        buf_size = recv_size;
        buf = malloc(recv_size);
        memset(buf, 0, recv_size);
        if (!buf)
            _terminate(3);

        recv_size = receive_all(read_fd, buf, buf_size);
        if (recv_size != buf_size)
            _terminate(4);
    }

    return buf;
}

void setup(void) {
    unsigned int size;

    size = receive_all(read_fd, (char *) &write_fd, sizeof(write_fd));
    if (size != sizeof(write_fd))
        _terminate(0);
    
    size = receive_all(read_fd, (char *) &read_fd, sizeof(read_fd));
    if (size != sizeof(read_fd))
        _terminate(0);

    
    if (write_fd > 256) {
        _terminate(0);
    }
}

void do_config(void) {
    int current_offset = -1;
    int pattern_offset = 0;
    size_t size = 0;
    int ret;

    ret = read_until(read_fd, pattern, sizeof(pattern) - 1, '\n');

//    pattern = read_buf(read_fd);
    size = strlen(pattern);

    if (size == 0)
        return;

    if (size > MAX_PATTERN_SIZE)
        _terminate(3);

    pattern_offset = 0;
    current_offset = -1;
    pattern_skip[0] = current_offset;
    while (pattern_offset < size) {
        while (current_offset  > -1 && pattern[pattern_offset] != pattern[current_offset])
            current_offset = pattern_skip[current_offset];
        pattern_offset++;
        current_offset++;
        pattern_skip[pattern_offset] = current_offset;
    }
}

int morris_pratt(char *buffer, int buffer_size) {
    int buffer_offset = 0;
    int pattern_offset = 0;
    size_t pattern_len = strlen(pattern);

    while (buffer_offset < buffer_size) {
        while (pattern_offset > -1 && pattern[pattern_offset] != buffer[buffer_offset])
            pattern_offset = pattern_skip[pattern_offset];
        pattern_offset++;
        buffer_offset++;
        if (pattern_offset >= pattern_len) {
            return 1;
        }
    }
    return 0;
}

void exit(int i) {
    transmit_all(write_fd, "\x00\n", 2);
    _terminate(i);
}

int main(void) {
    char buf[1024];
    int ret;

    do_config();
    setup();
    sleep(2);

    while (1) {
        memset(buf, 0, sizeof(buf));
        ret = read_until(read_fd, buf, sizeof(buf) - 1, '\n');
        if (ret == -1)
            exit(4);

        if (ret > 0) {

            if (buf[0] == 0) {
                exit(0);
            }

            ret = morris_pratt(buf, strlen(buf));
            if (ret == 1) {
                printf(write_fd, "%s\n", buf);
            }
        }
    }
    exit(1);
}
