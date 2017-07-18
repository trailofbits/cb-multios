
#include "libcgc.h"

unsigned int cgc_read_all(int fd, char *buf, unsigned int size) {
   char ch;
   unsigned int total = 0;
   cgc_size_t nbytes;
   while (size) {
      if (cgc_receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
         break;
      }
      buf[total++] = ch;
      size--;
   }
   return total;
}

/*
 * Read characters into buf until endchar is found. Stop reading when
 * endchar is cgc_read.  Returns the total number of chars cgc_read EXCLUDING
 * endchar.  endchar is NEVER copied into the buffer.  Note that it
 * is possible to perform size+1 reads as long as the last char cgc_read
 * is endchar.
 */
int cgc_read_until_delim(int fd, char *buf, unsigned int size, char endchar) {
   char ch;
   unsigned int total = 0;
   cgc_size_t nbytes;
   while (1) {
      if (cgc_receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
         return -1;
      }
      if (ch == endchar) break;
      if (total >= size) return -1;
      buf[total++] = ch;
   }
   return (int)total;
}
