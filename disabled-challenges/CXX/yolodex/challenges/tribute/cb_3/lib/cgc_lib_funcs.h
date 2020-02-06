

#ifndef __LIBFUNCS_H
#define __LIBFUNCS_H

unsigned int cgc_read_all(int fd, char *buf, unsigned int size);
int read_until_delim(int fd, char *buf, unsigned int size, char endchar);

#endif

