

#ifndef __GC_STDLIB_H
#define __GC_STDLIB_H

#include "cgc_types.h"

void *cgc_malloc(cgc_size_t size);
void *cgc_realloc(void *ptr, cgc_size_t size);
void cgc_free(void *ptr);

long strtol(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);

int cgc_putenv(const char *name, const unsigned char *value, cgc_size_t value_len);
unsigned char *cgc_getenv(const char *name, cgc_size_t *len);

int cgc_isalnum(int c);
int cgc_isalpha(int c);
int cgc_iscntrl(int c);
int cgc_isdigit(int c);
int cgc_isgraph(int c);
int cgc_islower(int c);
int cgc_isprint(int c);
int cgc_ispunct(int c);
int cgc_isspace(int c);
int cgc_isupper(int c);
int cgc_isxdigit(int c);

#endif
