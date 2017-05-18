#ifndef _EXTERNAL_API_H
#define _EXTERNAL_API_H

#include "libcgc.h"
#include "cgc_cgc_types.h"
#include "cgc_printf.h"

#define assert(x) \
    do { if (!(x)) { cgc_printf(STDERR, "fail: " #x " at %s (%u)\n", __FILE__, __LINE__); cgc__terminate(1); } } while(0)

char *cgc_strchr(const char *s, int c);
char *cgc_strdup(const char *src);
char *cgc_strtok(char *str, const char *sep);
int cgc_memcmp(const void *buf1, const void *buf2, cgc_size_t size);
int cgc_read_until(int fd, char *buf, unsigned int size, char endchar);
int cgc_strcmp(const char *s1, const char *s2);
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
int cgc_transmit_all(int fd, const char *str, cgc_size_t size);
int cgc_transmit_str(int fd, char *str);
cgc_size_t cgc_receive_all(int fd, char *buf, const cgc_size_t size);
cgc_size_t cgc_strcspn(const char *s1, const char *s2);
cgc_size_t cgc_strlcat(char *dst, const char *src, const cgc_size_t size);
cgc_size_t cgc_strlcpy(char *dst, const char *src, const cgc_size_t size);
cgc_size_t cgc_strlen(const char *s);
cgc_size_t cgc_strspn(const char *s1, const char *s2);
void *cgc_calloc(cgc_size_t count, cgc_size_t size);
void cgc_err(unsigned int id, char *str); // __attribute__((noreturn));
void *cgc_memcpy(void *dst, const void *src, cgc_size_t size);
void *cgc_memset(void *b, int c, cgc_size_t len);
void cgc_sleep(int amount);

#endif /* _EXTERNAL_API_H */
