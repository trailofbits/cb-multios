#ifndef MY_LIB_C_H
#define MY_LIB_C_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

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

//reads in a new line and returns the number of characters cgc_read
// Returns the number of characters cgc_read otherwise it will return 0
// or an errno on error
// errno can be
// The errno from fdwait or receive
// it can also be -EINVAL if buf is NULL.
// it can also be -EPIPE if EOF -- Notice that EPIPE is not used by either fdwait or receive
cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len);
cgc_size_t cgc_myStrLen(const char* str);
cgc_size_t cgc_my_printf(const char* str);
int cgc_snprintdecimal(char* str, cgc_size_t len, uint32_t num);
uint32_t cgc_strToUint32(const char* str);

#endif//MY_LIB_C_H
