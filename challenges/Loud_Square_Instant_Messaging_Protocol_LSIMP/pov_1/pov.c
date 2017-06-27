#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x12\x00\x00\x00\x00\x00\x00\x00\x48\x45\x4c\x4f\x67\x01\xc8\x00"
         "\x00\x00\x58\xce\xdd\x26\x3c\x00\x00\x00\x00\x00\x00\x00\x4b\x45"
         "\x59\x58\x00\x10\x00\x00\x00\x4e\x49\x43\x45\x20\x4b\x45\x59\x20"
         "\x49\x53\x20\x4e\x49\x43\x45\x44\x41\x54\x41\x44\x43\x42\x41\x06"
         "\x00\x00\x00\x59\x4f\x59\x4f\x59\x4f\x4b\x45\x59\x58\x00\x00\x00"
         "\x00\x00\xd7\xd6\x57\x23\x1a\x00\x00\x00\x00\x00\x00\x00\x44\x41"
         "\x54\x41\x01\x00\x00\x00\x06\x00\x00\x00\x59\x4f\x59\x4f\x59\x4f"
         "\x19\xa3\x7c\xe2\x04\x00\x00\x00\x01\x00\x00\x00\x04\x00\x00\x00"
         "\x02\x00\x00\x00";
      static unsigned int write_00000_00000_len = 132;
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
      //**** length read
      read_00000_len = 82;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x51\x55\x45\x55\x45\x44\x0a\x51\x55\x45\x55\x45\x44\x0a\x51\x55"
         "\x45\x55\x45\x44\x0a\x48\x45\x4c\x4f\x20\x5b\x56\x45\x52\x53\x49"
         "\x4f\x4e\x20\x31\x30\x33\x5d\x20\x5b\x53\x45\x43\x55\x52\x45\x20"
         "\x6f\x6e\x5d\x20\x5b\x54\x54\x4c\x20\x32\x30\x30\x5d\x0a\x4e\x4f"
         "\x20\x4b\x45\x59\x0a\x50\x52\x4f\x43\x45\x53\x53\x20\x44\x4f\x4e"
         "\x45\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 82);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
