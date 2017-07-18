

#ifndef __GC_STRING_H
#define __GC_STRING_H

#include "cgc_types.h"

void *cgc_memcpy(void *dst, const void *src, cgc_size_t len);
int cgc_memcmp(const void *b1, const void *b2, cgc_size_t n);
void *cgc_memset(void *b, int c, cgc_size_t len);

char *strcpy(char *dst, const char *src);

int cgc_strcmp(const char *s1, const char *s2);
int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);

cgc_size_t cgc_strlen(const char *str);

char *cgc_strchr(const char *s, int c);

#endif
