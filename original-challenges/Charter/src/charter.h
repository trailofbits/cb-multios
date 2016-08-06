#pragma once
#include <libcgc.h>

/* from limits.h, but it doesn't include right */
#define UINT32_MAX 4294967295U
typedef unsigned int uint32;

typedef struct {
  uint32 size;
  uint32* contents;
} data_package;

size_t read(void* buf, size_t expected_size);

/* took the limit from `ulimit -a` and chopped it in half */
//#define MAX_STACK_SIZE (8388608 / 2)
#define MAX_STACK_SIZE 0x10000
#define MAX_ALLOCATE_SIZE 0x1000 

#define l(s) transmit_all(STDERR, s, sizeof(s))
