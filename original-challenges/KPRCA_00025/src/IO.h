#ifndef IO_H_
#define IO_H_

#include "oo.h"

DeclareClass(IO, Object)
    int input_fd;
    int output_fd;
EndDeclareClass(IO, Object)

DeclareClassFunctions(IO, Object)
    DeclareFunction(IO, void, format, const char * fmt, ...)
    DeclareFunction(IO, size_t, receive, void *buf, size_t count)
    DeclareFunction(IO, void, wait_for_input)
    DeclareFunction(IO, void, wait_for, char c)
EndDeclareClassFunctions(IO)

#endif
