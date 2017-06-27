#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xde\x00";
      static unsigned int write_00000_00000_len = 2;
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
         "\x09\x09\x33\x78\x01\x00\x68\x00\x66\x00\x00\x00\x01\x04\x00\x2a"
         "\x00\x0a\x00\x24\x00\x22\x00\x03\x01\x0b\x01\x1a\x00\x4c\x00\x0d"
         "\x00\x02\x01\x0c\x01\x4a\x00\x66\x00\x34\x00\x0d\x00\x03\x01\x09"
         "\x00\x2e\x00\x35\x00\x2b\x00\x01\x01\x0a\x01\x2b\x00\x12\x00\x2a"
         "\x00\x44\x00\x31\x00\x31\x00\x02\x01\x0d\x00\x44\x00\x67\x00\x10"
         "\x00\x2d\x00\x01\x00\x03\x01\x1c\x00\x62\x00\x18\x00\x42\x00\x1f"
         "\x00\x2c\x00\x02\x00\x05\x01\x2b\x00\x04\x00\x5d\x00\x2d\x00\x01"
         "\x01\x05\x00\x30\x00\x5c\x00\x23\x00\x44\x00\x25\x00\x37\x00\x04"
         "\x01\x02\x00\x55\x00\x00\x00\x11\x00\x03\x00\x08\x00\x4b\x00\x1d"
         "\x00\x1a\x00\x02\x01\x0f\x00\x46\x00\x3a\x00\x0d\x00\x5e\x00\x03"
         "\x00\x0b\x01\x55\x00\x22\x00\x06\x00\x64\x00\x00\x00\x10\x6d\x0a"
         "\xbc\xf6\x28\x36\x0c\xb4\x70\xb1\xd6\x32\xf8\x2b\x3b\x51\x71\xab"
         "\x99\x26\x7e\x67\x89\xa6\x99\xa8\x02\xb6\xe2\x1d\x63\xb9\x4f\x93"
         "\x69\x75\x64\x1e\xd7\xdf\x55\xf7\x33\xdd\x7a\xc3\x27\x99";
      static unsigned int write_00001_00000_len = 222;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
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
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x50\x4d\x58\x7d\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 14);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
