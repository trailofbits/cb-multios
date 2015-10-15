#ifndef BITS_H_
#define BITS_H_

#include <stdint.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define NEG(x) ((x) < 0 ? 1 : 0)
#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#endif
