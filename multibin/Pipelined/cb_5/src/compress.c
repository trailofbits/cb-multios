#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"

int read_fd  = 10;
int write_fd = 10;
char *pattern;

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

int write_char(int fd, char value, int count) {
    if (count > 1) {
        printf(fd, "%u", count);
    } else {
        if (value >= '0' && value <= '9') {
            printf(fd, "1");
        }
    }

    transmit_all(fd, (char *) &value, sizeof(value));
    return 1;
}


void compress(void) {
    char current;
    char last = 0;
    int count = 1;
    int seen = 0;

    while (1) {
        last = current;
        current = get_byte(read_fd);

        if (current == 0) {
            break;
        }

        if (current == '\n') {
            if (seen > 0) {
                write_char(write_fd, last, count);
                count = 1;
            } 
            write_char(write_fd, '\n', 1);
            seen = 0;
        } else {
            if (last == current) {
                count++;
            } else {
                if (seen) {
                    write_char(write_fd, last, count);
                    count = 1;
                }
            }
            seen++;
        }
    }
}

int main(void) {
    setup();
    sleep(2);
    compress();
    exit(0);
}
