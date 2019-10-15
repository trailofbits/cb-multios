#ifndef STDLIB_H_
#define STDLIB_H_

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stddef.h"

extern int cgc_printf(const char *fmt, ...);

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
