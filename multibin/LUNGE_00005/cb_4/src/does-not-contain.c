#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"

int read_fd  = 8;
int write_fd = 8;
//char *pattern;

char pattern[1024];

char * read_buf(int fd) {
    unsigned int recv_size;
    unsigned int buf_size;
    char *buf = NULL;

    recv_size = receive_all(read_fd, (char *) &buf_size, sizeof(buf_size));
    if (recv_size != sizeof(buf_size))
        _terminate(1);

    if (recv_size == 0)
        _terminate(2);

    buf_size = recv_size;
    buf = malloc(recv_size);
    if (!buf)
        _terminate(3);

    recv_size = receive_all(read_fd, buf, buf_size);
    if (recv_size != buf_size)
        _terminate(4);

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

    if (write_fd == 0xFFFF)
        _terminate(0);
}

void do_config(void) {
    read_until(read_fd, pattern, sizeof(pattern), '\n');
}

int search(char *buffer, int buffer_size) {
    size_t size = strlen(pattern);
    size_t offset = 0;

    while (size + offset <= buffer_size) {
        if (memcmp(buffer + offset, pattern, size) == 0) {
            return 1;
        }
        offset++;
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
        ret = read_until(read_fd, buf, sizeof(buf), '\n');
        if (ret == -1)
            exit(4);

        if (ret > 0) {

            if (buf[0] == 0) {
                exit(0);
            }

            ret = search(buf, strlen(buf));
            if (ret != 1) {
                printf(write_fd, "%s\n", buf);
            }
        }
    }
    exit(1);
}
