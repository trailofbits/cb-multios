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
         "\x33\x0a";
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
         "\x0a\x2d\x3e\x20";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 4);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x68\x65\x6c\x6c\x6f\x0a";
      static unsigned int write_00001_00000_len = 6;
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
         "\x34\x0a";
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
         "\x3e\x20";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 2);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x31\x29\x20\x68\x65\x6c\x6c\x6f\x0a\x0a\x2d\x3e\x20";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 13);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x31\x0a";
      static unsigned int write_00003_00000_len = 2;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 11);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x0a\x50\x6c\x61\x6e\x65\x74\x3a\x20\x68\x65\x6c\x6c\x6f\x0a\x31"
         "\x29\x20\x44\x69\x73\x70\x6c\x61\x79\x20\x70\x6c\x61\x6e\x65\x74"
         "\x20\x69\x6e\x66\x6f\x72\x6d\x61\x74\x69\x6f\x6e\x0a\x32\x29\x20"
         "\x53\x65\x74\x20\x50\x65\x72\x69\x6f\x64\x0a\x33\x29\x20\x53\x65"
         "\x74\x20\x4f\x72\x62\x69\x74\x20\x53\x70\x65\x65\x64\x0a\x34\x29"
         "\x20\x53\x65\x74\x20\x41\x70\x68\x65\x6c\x69\x6f\x6e\x0a\x35\x29"
         "\x20\x53\x65\x74\x20\x50\x65\x72\x69\x68\x65\x6c\x69\x6f\x6e\x0a"
         "\x36\x29\x20\x53\x65\x74\x20\x4d\x65\x61\x6e\x20\x52\x61\x64\x69"
         "\x75\x73\x0a\x37\x29\x20\x53\x65\x74\x20\x45\x71\x75\x61\x74\x6f"
         "\x72\x69\x61\x6c\x20\x52\x61\x64\x69\x75\x73\x0a\x38\x29\x20\x53"
         "\x65\x74\x20\x4d\x61\x73\x73\x0a\x39\x29\x20\x53\x65\x74\x20\x47"
         "\x72\x61\x76\x69\x74\x79\x0a\x31\x30\x29\x20\x53\x65\x74\x20\x70"
         "\x6f\x70\x75\x6c\x61\x74\x69\x6f\x6e\x0a\x31\x31\x29\x20\x41\x64"
         "\x64\x20\x43\x6f\x75\x6e\x74\x72\x79\x0a\x31\x32\x29\x20\x53\x65"
         "\x6c\x65\x63\x74\x20\x63\x6f\x75\x6e\x74\x72\x79\x0a\x31\x33\x29"
         "\x20\x44\x65\x6c\x65\x74\x65\x20\x50\x6c\x61\x6e\x65\x74\x20\x61"
         "\x6e\x64\x20\x65\x78\x69\x74\x20\x6d\x65\x6e\x75\x0a\x31\x34\x29"
         "\x20\x45\x78\x69\x74\x20\x6d\x65\x6e\x75\x0a\x53\x65\x6c\x65\x63"
         "\x74\x69\x6f\x6e\x3a\x20";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 294);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x31\x31\x0a";
      static unsigned int write_00004_00000_len = 3;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x4e\x61\x6d\x65\x3a\x20";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 6);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x0a\x4e\x65\x77\x20\x4e\x61\x6d\x65\x3a\x20";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 11);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x68\x65\x6c\x6c\x6f\x0a";
      static unsigned int write_00005_00000_len = 6;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 11);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x0a\x50\x6c\x61\x6e\x65\x74\x3a\x20\x68\x65\x6c\x6c\x6f\x0a\x31"
         "\x29\x20\x44\x69\x73\x70\x6c\x61\x79\x20\x70\x6c\x61\x6e\x65\x74"
         "\x20\x69\x6e\x66\x6f\x72\x6d\x61\x74\x69\x6f\x6e\x0a\x32\x29\x20"
         "\x53\x65\x74\x20\x50\x65\x72\x69\x6f\x64\x0a\x33\x29\x20\x53\x65"
         "\x74\x20\x4f\x72\x62\x69\x74\x20\x53\x70\x65\x65\x64\x0a\x34\x29"
         "\x20\x53\x65\x74\x20\x41\x70\x68\x65\x6c\x69\x6f\x6e\x0a\x35\x29"
         "\x20\x53\x65\x74\x20\x50\x65\x72\x69\x68\x65\x6c\x69\x6f\x6e\x0a"
         "\x36\x29\x20\x53\x65\x74\x20\x4d\x65\x61\x6e\x20\x52\x61\x64\x69"
         "\x75\x73\x0a\x37\x29\x20\x53\x65\x74\x20\x45\x71\x75\x61\x74\x6f"
         "\x72\x69\x61\x6c\x20\x52\x61\x64\x69\x75\x73\x0a\x38\x29\x20\x53"
         "\x65\x74\x20\x4d\x61\x73\x73\x0a\x39\x29\x20\x53\x65\x74\x20\x47"
         "\x72\x61\x76\x69\x74\x79\x0a\x31\x30\x29\x20\x53\x65\x74\x20\x70"
         "\x6f\x70\x75\x6c\x61\x74\x69\x6f\x6e\x0a\x31\x31\x29\x20\x41\x64"
         "\x64\x20\x43\x6f\x75\x6e\x74\x72\x79\x0a\x31\x32\x29\x20\x53\x65"
         "\x6c\x65\x63\x74\x20\x63\x6f\x75\x6e\x74\x72\x79\x0a\x31\x33\x29"
         "\x20\x44\x65\x6c\x65\x74\x65\x20\x50\x6c\x61\x6e\x65\x74\x20\x61"
         "\x6e\x64\x20\x65\x78\x69\x74\x20\x6d\x65\x6e\x75\x0a\x31\x34\x29"
         "\x20\x45\x78\x69\x74\x20\x6d\x65\x6e\x75\x0a\x53\x65\x6c\x65\x63"
         "\x74\x69\x6f\x6e\x3a\x20";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 294);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x31\x32\x0a";
      static unsigned int write_00006_00000_len = 3;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x3e\x20";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = cgc_delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 2);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x0a\x43\x6f\x75\x6e\x74\x72\x69\x65\x73\x3a\x0a\x31\x29\x20\x68"
         "\x65\x6c\x6c\x6f\x0a\x0a\x2d\x3e\x20";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 25);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x31\x0a";
      static unsigned int write_00007_00000_len = 2;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 11);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x0a\x43\x6f\x75\x6e\x74\x72\x79\x3a\x20\x68\x65\x6c\x6c\x6f\x0a"
         "\x31\x29\x20\x44\x69\x73\x70\x6c\x61\x79\x20\x43\x6f\x75\x6e\x74"
         "\x72\x79\x49\x6e\x66\x6f\x0a\x32\x29\x20\x53\x65\x74\x20\x43\x61"
         "\x70\x69\x74\x6f\x6c\x0a\x33\x29\x20\x53\x65\x74\x20\x50\x6f\x70"
         "\x75\x6c\x61\x74\x69\x6f\x6e\x0a\x34\x29\x20\x41\x64\x64\x20\x4c"
         "\x61\x6e\x67\x75\x61\x67\x65\x0a\x35\x29\x20\x41\x64\x64\x20\x62"
         "\x6f\x72\x64\x65\x72\x0a\x36\x29\x20\x41\x64\x64\x20\x54\x65\x72"
         "\x72\x69\x74\x6f\x72\x79\x0a\x37\x29\x20\x53\x65\x6c\x65\x63\x74"
         "\x20\x54\x65\x72\x72\x69\x74\x6f\x72\x79\x0a\x38\x29\x20\x44\x65"
         "\x6c\x65\x74\x65\x20\x43\x6f\x75\x6e\x74\x72\x79\x20\x61\x6e\x64"
         "\x20\x45\x78\x69\x74\x20\x4d\x65\x6e\x75\x0a\x39\x29\x20\x45\x78"
         "\x69\x74\x20\x6d\x65\x6e\x75\x0a\x53\x65\x6c\x65\x63\x74\x69\x6f"
         "\x6e\x3a\x20";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 195);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x32\x0a";
      static unsigned int write_00008_00000_len = 2;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x3e\x20";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 2);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x0a\x2d\x3e\x20";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 4);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43"
         "\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72\x61\x73\x68\x43\x72"
         "\x61\x73\x68\x43\x72\x61\x0a";
      static unsigned int write_00009_00000_len = 39;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x53\x65\x6c\x65\x63\x74\x69\x6f\x6e\x3a\x20";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 11);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x0a\x43\x6f\x75\x6e\x74\x72\x79\x3a\x20\x68\x65\x6c\x6c\x6f\x0a"
         "\x31\x29\x20\x44\x69\x73\x70\x6c\x61\x79\x20\x43\x6f\x75\x6e\x74"
         "\x72\x79\x49\x6e\x66\x6f\x0a\x32\x29\x20\x53\x65\x74\x20\x43\x61"
         "\x70\x69\x74\x6f\x6c\x0a\x33\x29\x20\x53\x65\x74\x20\x50\x6f\x70"
         "\x75\x6c\x61\x74\x69\x6f\x6e\x0a\x34\x29\x20\x41\x64\x64\x20\x4c"
         "\x61\x6e\x67\x75\x61\x67\x65\x0a\x35\x29\x20\x41\x64\x64\x20\x62"
         "\x6f\x72\x64\x65\x72\x0a\x36\x29\x20\x41\x64\x64\x20\x54\x65\x72"
         "\x72\x69\x74\x6f\x72\x79\x0a\x37\x29\x20\x53\x65\x6c\x65\x63\x74"
         "\x20\x54\x65\x72\x72\x69\x74\x6f\x72\x79\x0a\x38\x29\x20\x44\x65"
         "\x6c\x65\x74\x65\x20\x43\x6f\x75\x6e\x74\x72\x79\x20\x61\x6e\x64"
         "\x20\x45\x78\x69\x74\x20\x4d\x65\x6e\x75\x0a\x39\x29\x20\x45\x78"
         "\x69\x74\x20\x6d\x65\x6e\x75\x0a\x53\x65\x6c\x65\x63\x74\x69\x6f"
         "\x6e\x3a\x20";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 195);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x31\x0a";
      static unsigned int write_00010_00000_len = 2;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 102;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
}
