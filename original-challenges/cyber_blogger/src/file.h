#ifndef FILEBASE_H_
#define FILEBASE_H_

#include "filetype.h"

extern "C" {
#include <stdlib.h>
};

class File
{
private:
    size_t header_size;
    size_t data_size;
    char filename[64];
    char extension[4];
protected:
    void *raw_header;
    char *raw_data;
    void clear_data_size();
public:
    static const unsigned int MAX_HEADER_SIZE = 128;
    File(size_t _header_size, size_t _data_size, char *_filename);
    virtual ~File();

    virtual unsigned int get_magic() = 0;

    char *get_extension();
    size_t get_header_size();
    size_t get_data_size();
    const ftype tell_filetype();
};

#endif

