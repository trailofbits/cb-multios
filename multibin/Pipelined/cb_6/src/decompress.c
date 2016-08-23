#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"

int read_fd  = 12;
int write_fd = 12;
#define BUFSIZE 256


char read_buf[BUFSIZE];

void exit(int i) {
    transmit_all(write_fd, "\x00\n", 2);
    _terminate(i);
}

char get_byte(int fd) {
    char value;
    size_t size;

    size = receive_all(fd, (char *) &value, sizeof(value));
    if (size != sizeof(value))
        exit(0);
    
    return value;
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

void decompress(void) {
    char write_buf[BUFSIZE * 2]; /* double should always be enough ;) */

    int ret;
    int i;
    int write_offset = 0;
    int write_count = 0;


    while (1) {
        write_offset = 0;
        write_count = 0;

        memset(read_buf, 0, sizeof(read_buf));
        memset(write_buf, 0, sizeof(write_buf));

        ret = read_until(read_fd, read_buf, sizeof(read_buf) - 1, '\n');

        if (read_buf[0] == 0) {
            exit(1);
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

        transmit_all(write_fd, write_buf, write_offset);
        transmit_all(write_fd, "\n", 1);
    }
    
}

int main(void) {
    setup();
    sleep(2);
    if (read_fd == 0) {
        exit(0);
    }
    decompress();
    exit(0);
}
