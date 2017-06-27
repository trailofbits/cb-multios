#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x21\x41\x41\x41\x41\x41\x2c\x31\x2c\x32\x2c\x38\x2c\x67\x43\x53"
         "\x3a\x68\x74\x3a\x62\x63\x35\x45\x4e\x4c\x6e\x70\x40\x30\x36\x3e"
         "\x45\x74\x69\x4e\x50\x4a\x69\x51\x77\x56\x69\x3e\x32\x73\x51\x4d"
         "\x50\x30\x32\x35\x75\x2c\x30\x2a\x31\x35\x07";
      static unsigned int write_00000_00000_len = 59;
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
      read_00000_len = 20;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x50\x41\x52\x54\x49\x41\x4c\x20\x41\x49\x53\x20\x4d\x45\x53\x53"
         "\x41\x47\x45\x2e";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 20);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x21\x41\x41\x41\x41\x41\x2c\x32\x2c\x32\x2c\x38\x2c\x63\x73\x70"
         "\x77\x77\x72\x75\x77\x63\x6f\x65\x66\x6b\x75\x68\x31\x46\x45\x69"
         "\x53\x37\x46\x41\x67\x72\x38\x38\x39\x64\x41\x4c\x30\x30\x30\x30"
         "\x30\x30\x30\x30\x2c\x30\x2a\x37\x31\x07";
      static unsigned int write_00001_00000_len = 58;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 17;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x49\x4e\x56\x41\x4c\x49\x44\x20\x53\x45\x4e\x54\x45\x4e\x43\x45"
         "\x2e";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 17);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
}
