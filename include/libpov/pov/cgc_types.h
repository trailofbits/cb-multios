#ifndef __TYPES_H
#define __TYPES_H

#include "libcgc.h"

typedef char                __int8_t;
typedef unsigned char       __uint8_t;
typedef short               __int16_t;
typedef unsigned short      __uint16_t;
typedef int                 __int32_t;
typedef unsigned int        __uint32_t;
typedef long long           __int64_t;
typedef unsigned long long  __uint64_t;

typedef __int8_t     int8_t;
typedef __uint8_t    uint8_t;
typedef __int16_t    int16_t;
typedef __uint16_t   uint16_t;
typedef __int32_t    int32_t;
typedef __uint32_t   uint32_t;
typedef __int64_t    int64_t;
typedef __uint64_t   uint64_t;

typedef uint32_t useconds_t;

#ifdef WIN
    #include <stdarg.h>
#else
    typedef __builtin_va_list va_list;
    #define va_start(ap, last) __builtin_va_start((ap), (last))
#endif

#endif
