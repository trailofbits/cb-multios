#ifndef TENNISBALL_H
#define TENNISBALL_H

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#define PAGE_SIZE 4096

#define printfstr(_fd, _s) write(_fd, _s, myStrLen(_s))

static double POWERS_OF_TEN[10] = {
  1e0,
  1e1,
  1e2,
  1e3,
  1e4,
  1e5,
  1e6,
  1e7,
  1e8,
  1e9,
};

//I have to define my own NAN constant in this case
// this is the error that is returned if conversion doesn't work
typedef union _DoubleInt
{ 
  double d; 
  uint64_t u; 
} DoubleInt;

static DoubleInt NAN = {.u = 0xFFFFFFFFFFFFFFFFull};

//A function to change a string into a uint32_t
// The important thing to note is that we will only process
// the first 9 characters. This is because the maximum
// value for uint32_t is 0xFFFFFFFF which is 4 294 967 295
// so, if we were reading 10 digits, we will have to deal with
// overflows and all that mess. 
uint32_t strtouint32(const char* str);

double strtodouble(const char* str);

typedef struct _Coords
{
  float x;
  float y;
} Coords;

#endif//TENNISBALL_H
