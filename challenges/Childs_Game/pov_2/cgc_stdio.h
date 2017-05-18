#ifndef STDIO_H_
#define STDIO_H_

#include "libpov.h"

typedef struct FILE FILE;

extern FILE * const cgc_stdin;
extern FILE * const cgc_stdout;
extern FILE * const cgc_stderr;

int cgc_printf(const char *fmt, ...);
int cgc_fprintf(FILE *stream, const char *fmt, ...);
int cgc_sprintf(char *str, const char *fmt, ...);

int cgc_vprintf(const char *fmt, va_list ap);
int cgc_vfprintf(FILE *stream, const char *fmt, va_list ap);
int cgc_vsprintf(char *str, const char *fmt, va_list ap);

cgc_ssize_t fread(void *ptr, cgc_size_t size, FILE *stream);
cgc_ssize_t freaduntil(char *str, cgc_size_t size, char term, FILE *stream);
cgc_ssize_t cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream);
int cgc_fflush(FILE *stream);

void *cgc_memmove(void *dst, const void *src, cgc_size_t n);

#endif
