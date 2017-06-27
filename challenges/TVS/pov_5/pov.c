#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xaa\xa8\xac\xad\xac";
      static unsigned int write_00000_00000_len = 5;
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
      read_00000_len = 13;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x55\x57\x57\x5e\x61\xd6\xe4\x14\x30\x38\x38\x38\x34";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 13);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\xae\xac\xb0\xf8\xfb\xe9\x39\x17\xef\xb8\xf1\xc9\xfc\xd4\x2a\x6c"
         "\xc6\x6b\xdc\x64\xbe\x83\xf3\x97\x16\xa4\x5d\x96\x0e\xfd\x3e\x81"
         "\x0f\xd6\xd2\x23\xe6\x35\xef\x36\x32\x26\xb8\x11\xd2\x3a\xfa\x6a"
         "\x6a\x21\xb8\xe9\x05\xb7\x5c\xac\xed\xcc\xf5\x5f\xd0\x20\xdd\xa6"
         "\x4f\x70\x52\xe1\x68\x59\xb3\xd3\x45\x9f\x46\xc1";
      static unsigned int write_00001_00000_len = 76;
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
         "\x31\x33\x33\x26\x4b\x59\x69\xc7\x9f\xf3\x24\x19\x60\x3d\x81\x39"
         "\x84\x92\xe2\x1f\xba\xea\xa8\x53\x70";
      static unsigned int write_00002_00000_len = 25;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 9;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
}
