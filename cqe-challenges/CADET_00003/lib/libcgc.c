//#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
#include <libcgc.h>

#if 0
void _terminate(unsigned int status) __attribute__((__noreturn__));
int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes);
int receive(int fd, void *buf, size_t count, size_t *rx_bytes);
int fdwait(int nfds, fd_set *readfds, fd_set *writefds,
	   const struct timeval *timeout, int *readyfds);
int allocate(size_t length, int is_X, void **addr);
int deallocate(void *addr, size_t length);
int random(void *buf, size_t count, size_t *rnd_bytes);
#endif

extern void exit(int status);
extern ssize_t write(int fildes, const void *buf, size_t nbyte);
extern ssize_t read(int fildes, void *buf, size_t nbyte);

extern int errno;

void _terminate(unsigned int status)
{
    exit(status);
}

int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes)
{
    ssize_t num_written = 0;

    num_written = write(fd, buf, count);

    if (num_written < 0)
        return errno;

    if (tx_bytes)
        *tx_bytes = num_written;

    return 0;
}

int receive(int fd, void *buf, size_t count, size_t *rx_bytes)
{
    ssize_t num_read = 0;

    num_read = read(fd, buf, count);

    if (num_read < 0)
        return errno;

    if (rx_bytes)
        *rx_bytes = num_read;

    return 0;
}
