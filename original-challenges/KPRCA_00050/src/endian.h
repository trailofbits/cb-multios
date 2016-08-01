#ifndef ENDIAN_H_
#define ENDIAN_H_

#include <stdint.h>

#define betoh32 swap32
#define htobe32 swap32
#define betoh16 swap16
#define htobe16 swap16

static inline uint16_t swap16(uint16_t x)
{
    return (x >> 8) | (x << 8);
}

static inline uint32_t swap32(uint32_t x)
{
    return (swap16(x) << 16) | (swap16(x >> 16));
}

#endif
