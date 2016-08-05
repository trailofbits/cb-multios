#include <stdio.h>
#include "readuntil.h"

int read_until(int fd, char *buf, size_t len, char delim)
{
    fflush(stdout);
    return freaduntil(buf, len, delim, stdin);
}

int read_n(int fd, char *buf, size_t len)
{
    fflush(stdout);
    return fread(buf, len, stdin);
}
