#ifndef IO_H_
#define IO_H_

#include "cgc_stdlib.h"
#include "cgc_stdint.h"

void cgc_read_bytes(void *buf, cgc_size_t count);
uint8_t cgc_read_byte();
int cgc_read_int();
char *cgc_read_string();

void cgc_write_bytes(const void *buf, cgc_size_t count);
void cgc_write_byte(uint8_t b);
void cgc_write_int(int val);
void cgc_write_string(const char *str);

#endif /* !IO_H_ */
