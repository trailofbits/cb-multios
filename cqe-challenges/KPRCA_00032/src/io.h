#ifndef IO_H_
#define IO_H_

#include <stdlib.h>
#include <stdint.h>

void read_bytes(void *buf, size_t count);
uint8_t read_byte();
int read_int();
char *read_string();

void write_bytes(const void *buf, size_t count);
void write_byte(uint8_t b);
void write_int(int val);
void write_string(const char *str);

#endif /* !IO_H_ */
