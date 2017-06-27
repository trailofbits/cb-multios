#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

int read_fd  = 10;
int write_fd = 10;
char *pattern;

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

int cgc_write_char(int fd, char value, int count) {
    if (count > 1) {
        cgc_printf(fd, "%u", count);
    } else {
        if (value >= '0' && value <= '9') {
            cgc_printf(fd, "1");
        }
    }

    cgc_transmit_all(fd, (char *) &value, sizeof(value));
    return 1;
}


void cgc_compress(void) {
    char current;
    char last = 0;
    int count = 1;
    int seen = 0;

    while (1) {
        last = current;
        current = cgc_get_byte(read_fd);

        if (current == 0) {
            break;
        }

        if (current == '\n') {
            if (seen > 0) {
                cgc_write_char(write_fd, last, count);
                count = 1;
            } 
            cgc_write_char(write_fd, '\n', 1);
            seen = 0;
        } else {
            if (last == current) {
                count++;
            } else {
                if (seen) {
                    cgc_write_char(write_fd, last, count);
                    count = 1;
                }
            }
            seen++;
        }
    }
}

int main(int cgc_argc, char *cgc_argv[]) {
    cgc_setup();
    cgc_sleep(2);
    cgc_compress();
    cgc_exit(0);
}
