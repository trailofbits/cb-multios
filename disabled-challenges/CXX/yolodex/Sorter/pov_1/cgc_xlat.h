#pragma once

#include "libpov.h"

int cgc_xlat_delimited_read(int fd, unsigned char **buf, unsigned int *size, unsigned char *delim, unsigned int delim_len);
int cgc_xlat_length_read(int fd, unsigned char *buf, unsigned int len);
int cgc_xlat_transmit_all(int fd, const void *buf, const cgc_size_t size);
void cgc_xlat_seed(const char *seed);

/* replace libpov functions with xlat functions */
#define delimited_read cgc_xlat_delimited_read
#define length_read cgc_xlat_length_read
#define cgc_transmit_all cgc_xlat_transmit_all
