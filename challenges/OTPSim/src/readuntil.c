#include "cgc_stdio.h"
#include "cgc_readuntil.h"

int cgc_read_until(int fd, char *buf, cgc_size_t len, char delim)
{
    cgc_fflush(cgc_stdout);
    return cgc_freaduntil(buf, len, delim, cgc_stdin);
}

int cgc_read_n(int fd, char *buf, cgc_size_t len)
{
    cgc_fflush(cgc_stdout);
    return cgc_fread(buf, len, cgc_stdin);
}
