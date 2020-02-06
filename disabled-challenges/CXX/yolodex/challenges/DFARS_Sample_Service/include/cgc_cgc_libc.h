#ifndef _EXTERNAL_API_H
#define _EXTERNAL_API_H

#include "libcgc.h"
#include "cgc_cgc_types.h"
#include "cgc_printf.h"

#define assert(x) \
    do { if (!(x)) { cgc_printf("fail: " #x " at %s (%u)\n", __FILE__, __LINE__); } } while(0)

char *cgc_strchr(const char *s, int c);
char *cgc_strdup(const char *src);
char *cgc_strtok(char *str, const char *sep);
int cgc_strcmp(const char *s1, const char *s2);
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
cgc_size_t cgc_strcspn(const char *s1, const char *s2);
cgc_size_t cgc_strlcat(char *dst, const char *src, const cgc_size_t size);
cgc_size_t cgc_strlcpy(char *dst, const char *src, const cgc_size_t size);
cgc_size_t cgc_strlen(const char *s);
cgc_size_t cgc_strspn(const char *s1, const char *s2);
void *cgc_calloc(cgc_size_t count, cgc_size_t size);
void *cgc_memset(void *b, int c, cgc_size_t len);
void *cgc_memcpy(void *dst, const void *src, cgc_size_t size);
void cgc_err(unsigned int id, char *str); // __attribute__((noreturn));
int cgc_transmit_str(int fd, char *str);
int cgc_transmit_all(int fd, const char *str, cgc_size_t size);

#endif /* _EXTERNAL_API_H */
