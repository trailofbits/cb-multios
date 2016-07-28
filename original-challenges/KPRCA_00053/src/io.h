#ifndef IO_H_
#define IO_H_

#include "file.h"

extern "C" {
#include <stdlib.h>
};

namespace IO {
    static const unsigned int MAX_IO_SIZE = 128;

    char *buf();
    bool readline(size_t max_size=MAX_IO_SIZE);
    int readnum(size_t max_size=MAX_IO_SIZE);
    char *iotextdup(size_t max_size=MAX_IO_SIZE);
    bool readnbytes(size_t nbytes, char *data);
    File *upload_file();
}

#endif
