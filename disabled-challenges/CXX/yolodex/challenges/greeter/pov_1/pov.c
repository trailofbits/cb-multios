#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   //*** delay
   cgc_delay(100);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x6c\x6f\x67\x69\x6e\x20\x66\x6f\x6f\x62\x61\x72\x0a";
      static unsigned int write_00000_00000_len = 13;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x67\x72\x65\x65\x74\x20\x63\x6f\x75\x6e\x74\x65\x72\x3d\x64\x65"
         "\x61\x64\x62\x65\x65\x66\x7c\x6e\x61\x6d\x65\x3d\x66\x6f\x6f\x62"
         "\x61\x72\x7c\x31\x30\x35\x66\x34\x35\x31\x65\x33\x31\x31\x37\x34"
         "\x37\x35\x38\x32\x37\x31\x37\x30\x34\x31\x30\x31\x31\x32\x34\x33"
         "\x30\x30\x35\x34\x66\x0a";
      static unsigned int write_00001_00000_len = 70;
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
         "\x71\x75\x69\x74\x0a";
      static unsigned int write_00002_00000_len = 5;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
}
