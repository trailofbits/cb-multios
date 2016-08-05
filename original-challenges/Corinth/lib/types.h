#pragma once

#define UINT8_MAX 0xff
typedef unsigned char uint8;
typedef   signed char sint8;

#define UINT16_MAX 0xffff
typedef unsigned short int uint16;
typedef   signed short int sint16;

#define UINT32_MAX 0xffffffff
typedef unsigned int uint32;
typedef   signed int sint32;

#define UINT64_MAX 0xffffffffffffffff
typedef unsigned long long uint64;
typedef   signed long long sint64;

typedef float  float32;
typedef double float64;

void types_check();
