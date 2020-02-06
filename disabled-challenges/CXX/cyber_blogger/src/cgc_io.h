#ifndef IO_H_
#define IO_H_

#include "cgc_file.h"

extern "C" {
#include "cgc_stdlib.h"
};

namespace IO {
    static const unsigned int MAX_IO_SIZE = 128;

    char *buf();
    bool readline(cgc_size_t max_size=MAX_IO_SIZE);
    int readnum(cgc_size_t max_size=MAX_IO_SIZE);
    char *iotextdup(cgc_size_t max_size=MAX_IO_SIZE);
    bool readnbytes(cgc_size_t nbytes, char *data);
    File *upload_file();
}

#endif
