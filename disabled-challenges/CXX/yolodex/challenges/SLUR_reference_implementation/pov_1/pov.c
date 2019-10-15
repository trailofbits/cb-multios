#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 61;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x74\x68\x65\x20\x53"
         "\x4c\x55\x52\x20\x52\x45\x50\x4c\x2e\x20\x54\x79\x70\x65\x20\x61"
         "\x6e\x20\x65\x78\x70\x72\x65\x73\x73\x69\x6f\x6e\x20\x74\x6f\x20"
         "\x65\x76\x61\x6c\x75\x61\x74\x65\x20\x69\x74\x2e\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 61);
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
         "\x28\x28\x6c\x61\x6d\x62\x64\x61\x20\x28\x78\x29\x20\x28\x78\x20"
         "\x78\x20\x78\x20\x78\x20\x78\x29\x29\x20\x28\x71\x75\x6f\x74\x65"
         "\x20\x43\x41\x4b\x45\x29\x29\x0a";
      static unsigned int write_00000_00000_len = 40;
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
      read_00002_len = 48;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x28\x43\x41\x4b\x45\x20\x43\x41\x4b\x45\x20\x43\x41\x4b\x45\x20"
         "\x43\x41\x4b\x45\x20\x43\x41\x4b\x45\x20\x54\x68\x61\x74\x27\x73"
         "\x20\x61\x20\x6c\x6f\x74\x20\x6f\x66\x20\x43\x41\x4b\x45\x21\x29";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 48);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
}
