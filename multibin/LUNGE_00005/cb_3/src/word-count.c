#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"

#define MAX_PATTERN_SIZE 1024
int read_fd  = 6;
int write_fd = 6;

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

#define ISALPHA(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))

void exit(int i) {
    transmit_all(write_fd, "\x00\n", 2);
    _terminate(i);
}

int count(void) {
    char buf;
    int in_word = 0;
    unsigned int char_count = 0;
    unsigned int line_count = 0;
    unsigned int word_count = 0;
    unsigned int current_line_count = 0;

    while (1) {
        receive_all(read_fd, (char *) &buf, 1);
        char_count++;

        if (buf == 0) {
            return 0;
        }

        if (ISALPHA(buf)) {
            if (in_word == 0)
                in_word = 1;
        } else {
            if (in_word == 1) {
                in_word = 0;
                word_count++;
            }
        }
        if (buf == '\n') {
            line_count++;
            printf(write_fd, ": %u %u %u", char_count, word_count, line_count);
            if (current_line_count == 0) {
                return 0;
            }
            current_line_count = 0;
        } else {
            current_line_count++;
        }
        transmit_all(write_fd, &buf, 1);
    }
}

int main(void) {
    int ret;

    setup();
    sleep(2);
    ret = count();
    exit(ret);
}
