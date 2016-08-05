#pragma once

#include <libpov.h>

int xlat_delimited_read(int fd, unsigned char **buf, unsigned int *size, unsigned char *delim, unsigned int delim_len);
int xlat_length_read(int fd, unsigned char *buf, unsigned int len);
int xlat_transmit_all(int fd, const void *buf, const size_t size);
void xlat_seed(const char *seed);

/* replace libpov functions with xlat functions */
#define delimited_read xlat_delimited_read
#define length_read xlat_length_read
#define transmit_all xlat_transmit_all
