#ifndef STDIO_PRIVATE_H_
#define STDIO_PRIVATE_H_

#include "stdio.h"

#define INVALID_IDX -1
#define F_READ 1
#define F_WRITE 2

struct FILE {
    int fd;
    int rw;
    int idx;
    int length;
    char buffer[1024];
};

#endif
