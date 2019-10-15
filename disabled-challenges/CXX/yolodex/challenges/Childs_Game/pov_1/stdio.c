#include "cgc_stdio_private.h"

FILE _stdin = {
    .fd = STDIN,
    .rw = F_READ,
    .idx = 0,
    .length = 0
};
FILE _stdout = {
    .fd = STDOUT,
    .rw = F_WRITE,
    .idx = -1,
    .length = 0
};
FILE _stderr = {
    .fd = STDERR,
    .rw = F_WRITE,
    .idx = -1,
    .length = 0
};

FILE * const cgc_stdin = &_stdin;
FILE * const cgc_stdout = &_stdout;
FILE * const cgc_stderr = &_stderr;
