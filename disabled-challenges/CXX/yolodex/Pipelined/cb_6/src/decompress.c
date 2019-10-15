#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

int read_fd  = 12;
int write_fd = 12;
#define BUFSIZE 256


char read_buf[BUFSIZE];

void cgc_exit(int i) {
    cgc_transmit_all(write_fd, "\x00\n", 2);
    cgc__terminate(i);
}

char cgc_get_byte(int fd) {
    char value;
    cgc_size_t size;

    size = cgc_receive_all(fd, (char *) &value, sizeof(value));
    if (size != sizeof(value))
        cgc_exit(0);
    
    return value;
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

void cgc_decompress(void) {
    char write_buf[BUFSIZE * 2]; /* double should always be enough ;) */

    int ret;
    int i;
    int write_offset = 0;
    int write_count = 0;


    while (1) {
        write_offset = 0;
        write_count = 0;

        cgc_memset(read_buf, 0, sizeof(read_buf));
        cgc_memset(write_buf, 0, sizeof(write_buf));

        ret = cgc_read_until(read_fd, read_buf, sizeof(read_buf) - 1, '\n');

        if (read_buf[0] == 0) {
            cgc_exit(1);
        }

        for (i = 0; i < ret; i++) {
            if (read_buf[i] >= '0' && read_buf[i] <= '9') {
                write_count = read_buf[i] - '0';
                if (i + 1 >= ret) {
                    while (write_count > 1) {
                        write_buf[write_offset++] = '\n';
                        write_count--;
#ifdef PATCHED
                        if (write_offset >= BUFSIZE * 2)
                            return;
#endif
                    }
                } else {
                    while (write_count > 0) {
                        write_buf[write_offset++] = read_buf[i+1];
                        write_count--;
#ifdef PATCHED
                        if (write_offset >= BUFSIZE * 2)
                            return;
#endif
                    }
                }
                i++;
            } else {
                write_buf[write_offset++] = read_buf[i];
#ifdef PATCHED
                if (write_offset >= BUFSIZE * 2)
                    return;
#endif
            }
        }

        cgc_transmit_all(write_fd, write_buf, write_offset);
        cgc_transmit_all(write_fd, "\n", 1);
    }
    
}

int main(int cgc_argc, char *cgc_argv[]) {
    cgc_setup();
    cgc_sleep(2);
    if (read_fd == 0) {
        cgc_exit(0);
    }
    cgc_decompress();
    cgc_exit(0);
}
