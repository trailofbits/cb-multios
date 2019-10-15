#ifndef STDLIB_H_
#define STDLIB_H_

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stddef.h"

#define isinf(x) __builtin_isinf(x)
#define isnan(x) __builtin_isnan(x)

extern int cgc_fdprintf(int fd, const char *fmt, ...);
extern int cgc_sprintf(char *s, const char *fmt, ...);
#define cgc_printf(...) cgc_fdprintf(STDOUT, __VA_ARGS__)

long cgc_strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);

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
