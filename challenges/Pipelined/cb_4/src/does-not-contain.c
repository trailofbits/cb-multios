#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

int read_fd  = 8;
int write_fd = 8;
//char *pattern;

char pattern[1024];

char * cgc_read_buf(int fd) {
    unsigned int recv_size;
    unsigned int buf_size;
    char *buf = NULL;

    recv_size = cgc_receive_all(read_fd, (char *) &buf_size, sizeof(buf_size));
    if (recv_size != sizeof(buf_size))
        cgc__terminate(1);

    if (recv_size == 0)
        cgc__terminate(2);

    buf_size = recv_size;
    buf = cgc_malloc(recv_size);
    if (!buf)
        cgc__terminate(3);

    recv_size = cgc_receive_all(read_fd, buf, buf_size);
    if (recv_size != buf_size)
        cgc__terminate(4);

    return buf;
}

void cgc_setup(void) {
    unsigned int size;

    size = cgc_receive_all(read_fd, (char *) &write_fd, sizeof(write_fd));
    if (size != sizeof(write_fd))
        cgc__terminate(0);

    size = cgc_receive_all(read_fd, (char *) &read_fd, sizeof(read_fd));
    if (size != sizeof(read_fd))
        cgc__terminate(0);

    if (write_fd == 0xFFFF)
        cgc__terminate(0);
}

void cgc_do_config(void) {
    cgc_read_until(read_fd, pattern, sizeof(pattern), '\n');
}

int cgc_search(char *buffer, int buffer_size) {
    cgc_size_t size = cgc_strlen(pattern);
    cgc_size_t offset = 0;

    while (size + offset <= buffer_size) {
        if (cgc_memcmp(buffer + offset, pattern, size) == 0) {
            return 1;
        }
        offset++;
    }
    return 0;
}

void cgc_exit(int i) {
    cgc_transmit_all(write_fd, "\x00\n", 2);
    cgc__terminate(i);
}

int main(int cgc_argc, char *cgc_argv[]) {
    char buf[1024];
    int ret;

    cgc_do_config();
    cgc_setup();
    cgc_sleep(2);

    while (1) {
        cgc_memset(buf, 0, sizeof(buf));
        ret = cgc_read_until(read_fd, buf, sizeof(buf), '\n');
        if (ret == -1)
            cgc_exit(4);

        if (ret > 0) {

            if (buf[0] == 0) {
                cgc_exit(0);
            }

            ret = cgc_search(buf, cgc_strlen(buf));
            if (ret != 1) {
                cgc_printf(write_fd, "%s\n", buf);
            }
        }
    }
    cgc_exit(1);
}
