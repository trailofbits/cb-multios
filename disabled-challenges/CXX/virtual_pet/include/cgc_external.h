#ifndef _EXTERNAL_H
#define _EXTERNAL_H

#include "cgc_cgc_types.h"

#define cgc_transmit(a, b, c) cgc_write(a, b, c)
#define cgc_receive(a, b, c) cgc_read(a, b, c)
// #define terminate(a) _exit(a)

extern cgc_ssize_t cgc_read(int fildes, void *buf, cgc_size_t nbyte);
extern cgc_ssize_t cgc_write(int fildes, const void *buf, cgc_size_t nbyte);
// extern void _exit(int status);

extern void *malloc(cgc_size_t size);
extern void free(void *ptr);

#endif /* _EXTERNAL_H */
