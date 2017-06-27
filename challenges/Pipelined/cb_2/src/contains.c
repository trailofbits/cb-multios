#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

#define MAX_PATTERN_SIZE 1024
int read_fd  = 4;
int write_fd = 4;
char pattern[MAX_PATTERN_SIZE];
int pattern_skip[MAX_PATTERN_SIZE];

char * cgc_read_buf(int fd) {
    cgc_size_t recv_size;
    cgc_size_t buf_size;
    char *buf = NULL;

    recv_size = cgc_receive_all(read_fd, (char *) &buf_size, sizeof(buf_size));
    if (recv_size != sizeof(buf_size))
        cgc__terminate(1);

    if (buf_size > 0) {
        buf_size = recv_size;
        buf = cgc_malloc(recv_size);
        cgc_memset(buf, 0, recv_size);
        if (!buf)
            cgc__terminate(3);

        recv_size = cgc_receive_all(read_fd, buf, buf_size);
        if (recv_size != buf_size)
            cgc__terminate(4);
    }

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

    
    if (write_fd > 256) {
        cgc__terminate(0);
    }
}

void cgc_do_config(void) {
    int current_offset = -1;
    int pattern_offset = 0;
    cgc_size_t size = 0;
    int ret;

    ret = cgc_read_until(read_fd, pattern, sizeof(pattern) - 1, '\n');

//    pattern = read_buf(read_fd);
    size = cgc_strlen(pattern);

    if (size == 0)
        return;

    if (size > MAX_PATTERN_SIZE)
        cgc__terminate(3);

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

int cgc_morris_pratt(char *buffer, int buffer_size) {
    int buffer_offset = 0;
    int pattern_offset = 0;
    cgc_size_t pattern_len = cgc_strlen(pattern);

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
        ret = cgc_read_until(read_fd, buf, sizeof(buf) - 1, '\n');
        if (ret == -1)
            cgc_exit(4);

        if (ret > 0) {

            if (buf[0] == 0) {
                cgc_exit(0);
            }

            ret = cgc_morris_pratt(buf, cgc_strlen(buf));
            if (ret == 1) {
                cgc_printf(write_fd, "%s\n", buf);
            }
        }
    }
    cgc_exit(1);
}
