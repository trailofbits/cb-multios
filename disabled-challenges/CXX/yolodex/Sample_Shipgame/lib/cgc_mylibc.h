#ifndef MY_LIB_C_H
#define MY_LIB_C_H

//reads in a new line and returns the number of characters cgc_read
// Returns the number of characters cgc_read otherwise it will return 0
// or an errno on error
// errno can be
// The errno from fdwait or receive
// it can also be -EINVAL if buf is NULL.
// it can also be -EPIPE if EOF -- Notice that EPIPE is not used by either fdwait or receive
cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len);
cgc_size_t cgc_myStrLen(const char* str);
void cgc_write(int fd, const void* buf, cgc_size_t len);


#endif//MY_LIB_C_H
