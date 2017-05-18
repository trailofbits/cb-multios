#ifndef STDLIB_H_
#define STDLIB_H_

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stddef.h"

extern int debug_printf(const char *fmt, ...);
extern int cgc_fdprintf(int fd, const char *fmt, ...);
extern int cgc_sprintf(char *s, const char *fmt, ...);
extern int cgc_snprintf(char *s, cgc_size_t size, const char *fmt, ...);
extern int cgc_vsnprintf(char *s, cgc_size_t size, const char *fmt, va_list ap);
#define cgc_printf(...) fdprintf(1, __VA_ARGS__)

long cgc_strtol(const char *str, char **endptr, int base);
unsigned long cgc_strtoul(const char *str, char **endptr, int base);

extern void *cgc_malloc(cgc_size_t size);
extern void *cgc_calloc(cgc_size_t nmemb, cgc_size_t size);
extern void *cgc_realloc(void *ptr, cgc_size_t size);
extern void cgc_free(void *ptr);
extern cgc_size_t malloc_size(void *ptr);

static void cgc_exit(int ret)
{
    cgc__terminate(ret);
}

#endif /* !STDLIB_H_ */
