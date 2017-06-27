#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

#define MAX_PATTERN_SIZE 1024
int read_fd  = 6;
int write_fd = 6;

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

#define ISALPHA(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))

void cgc_exit(int i) {
    cgc_transmit_all(write_fd, "\x00\n", 2);
    cgc__terminate(i);
}

int count(void) {
    char buf;
    int in_word = 0;
    unsigned int char_count = 0;
    unsigned int line_count = 0;
    unsigned int word_count = 0;
    unsigned int current_line_count = 0;

    while (1) {
        cgc_receive_all(read_fd, (char *) &buf, 1);
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
            cgc_printf(write_fd, ": %u %u %u", char_count, word_count, line_count);
            if (current_line_count == 0) {
                return 0;
            }
            current_line_count = 0;
        } else {
            current_line_count++;
        }
        cgc_transmit_all(write_fd, &buf, 1);
    }
}

int main(int cgc_argc, char *cgc_argv[]) {
    int ret;

    cgc_setup();
    cgc_sleep(2);
    ret = count();
    cgc_exit(ret);
}
