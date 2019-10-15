#ifndef STRING_H_
#define STRING_H_

#include "cgc_stddef.h"

extern void *cgc_memcpy(void *dest, const void *src, cgc_size_t n);
extern void *cgc_memmove(void *dest, const void *src, cgc_size_t n);
extern void *cgc_memset(void *dest, int c, cgc_size_t n);
extern int memcmp(void *s1, const void *s2, cgc_size_t n);
extern void *memchr(const void *s, int c, cgc_size_t n);

extern cgc_size_t cgc_strlen(const char *s);
extern char *cgc_strcpy(char *dest, const char *src);
extern char *cgc_strncpy(char *dest, const char *src, cgc_size_t n);
extern char *cgc_strchr(const char *s, int c);
extern char *cgc_strsep(char **stringp, const char *delim);
extern int cgc_strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, cgc_size_t n);
extern int cgc_strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, cgc_size_t n);
extern char *cgc_strcat(char *dest, const char *src);
extern char *cgc_strdup(const char *src);

#endif /* !STRING_H_ */
