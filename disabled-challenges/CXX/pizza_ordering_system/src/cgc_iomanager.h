#ifndef IOMANAGER_H_
#define IOMANAGER_H_

extern "C" {
#include "cgc_stdlib.h"
};

class IoManager
{
private:
    static const int MAX_LINE = 512;
    int fd;
    char *line;
    cgc_size_t line_size;
    cgc_size_t line_len;
public:
    IoManager(cgc_size_t _line_size=MAX_LINE);
    virtual ~IoManager();

    bool readline(cgc_size_t max_size=0);
    int readnum(cgc_size_t max_size=0);
    void set_fd(int _fd) { fd = _fd; }
    char *get_last_input() { return line_len ? line : NULL; }
};

#endif
