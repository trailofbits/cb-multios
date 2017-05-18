#ifndef IO_H_
#define IO_H_
#include "cgc_stdlib.h"

int cgc_read_bytes(void *buf, cgc_size_t n);
int cgc_read_until(char *buf, cgc_size_t n, char el);
void cgc_write_bytes(void *buf, cgc_size_t n);
void cgc_write_string(char *buf);

#endif
