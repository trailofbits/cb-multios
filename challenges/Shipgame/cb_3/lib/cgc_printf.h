#ifndef PRINTF_H
#define PRINTF_H

#include "libcgc.h"

void cgc_printf_setFlushOnNewline(int bEnable);

cgc_size_t cgc_fprintf(int fd, const char* fstr, ...);
cgc_size_t cgc_printf(const char* fstr, ...);
cgc_size_t cgc_fflush(int fd);

cgc_size_t cgc_snprintf(char* str, cgc_size_t len, const char* fstr, ...);
 
#endif//PRINTF_H
