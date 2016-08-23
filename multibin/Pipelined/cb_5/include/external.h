#ifndef _EXTERNAL_H
#define _EXTERNAL_H

#include "cgc_types.h"

#define transmit(a, b, c) write(a, b, c)
#define receive(a, b, c) read(a, b, c)
// #define terminate(a) _exit(a)

extern ssize_t read(int fildes, void *buf, size_t nbyte);
extern ssize_t write(int fildes, const void *buf, size_t nbyte);
// extern void _exit(int status);

extern void *malloc(size_t size);
extern void free(void *ptr);

#endif /* _EXTERNAL_H */
