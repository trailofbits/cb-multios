#ifndef PRINTF_H
#define PRINTF_H

#include <libcgc.h>

void printf_setFlushOnNewline(int bEnable);

size_t fprintf(int fd, const char* fstr, ...);
size_t printf(const char* fstr, ...);
size_t fflush(int fd);

size_t snprintf(char* str, size_t len, const char* fstr, ...);
 
#endif//PRINTF_H
