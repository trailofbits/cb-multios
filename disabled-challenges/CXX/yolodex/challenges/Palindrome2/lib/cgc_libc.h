#ifndef LIBC_H
#define LIBC_H
int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size);
int cgc_receive_delim(int fd, char *buf, const cgc_size_t size, char delim);
#endif
