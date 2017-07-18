#ifndef LIBC_H
#define LIBC_H

#include "libcgc.h"

#define PAGE_SIZE 4096

/**
 * Transmits all len bytes from the buffer buf to the file descriptor
 *   or terminates in error
**/
void cgc_transmit_all(int fd, const void* buf, cgc_size_t len);

/**
 * Receives all len bytes from the buffer buf to the file descriptor
 *   or terminates in error
**/
void cgc_receive_all(int fd, void* buf, cgc_size_t len);

/**
 * Receives data from the buffer either until the delim is seen or until 
 *   the buffer is full.
 * Since this function adds a NULL character at the end, we will actually
 *   only cgc_read len-1 chars.
 * Returns the number of characters cgc_read (to include the delim). Note that
 *  the user must check to see that buf[count-1] is actually delim, and not
 *  because it just ended due to the max size
**/
cgc_size_t cgc_receive_until(int fd, char* buf, cgc_size_t len, char delim);

//string functions
int cgc_strcmp(const char* s1, const char* s2);

cgc_size_t cgc_strcpyUntil(char* dst, const char* src, char delim);
static inline cgc_size_t strcpy(char* dst, const char* src)
{
  return (cgc_strcpyUntil(dst, src, '\0'));
}


static inline cgc_size_t cgc_strlen(const char* str)
{
  cgc_size_t i = 0; 
  if (str == NULL)
  {
    return (0);
  }
  for (i = 0; str[i] != '\0'; i++);
  return (i);
}

static inline void fprintStr(int fd, const char* str)
{
  if (str == NULL)
  {
    return;
  }

  cgc_transmit_all(fd, str, cgc_strlen(str));
}

#endif//LIBC_H
