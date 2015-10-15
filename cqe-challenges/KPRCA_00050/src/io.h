#ifndef IO_H_
#define IO_H_
#include <stdlib.h>

int read_bytes(void *buf, size_t n);
int read_until(char *buf, size_t n, char el);
void write_bytes(void *buf, size_t n);
void write_string(char *buf);

#endif
