#ifndef MY_LIB_C_H
#define MY_LIB_C_H

#include "cgc_inttypes.h"
#include "cgc_string.h"
#include "cgc_printf.h"

//reads in a new line and returns the number of characters cgc_read
// Returns the number of characters cgc_read otherwise it will return 0
// or an errno on error
// errno can be
// The errno from fdwait or receive
// it can also be -EINVAL if buf is NULL.
cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len);

#endif//MY_LIB_C_H
