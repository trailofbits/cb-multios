#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 9;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x41\x63\x63\x65\x6c\x3a\x2d\x24\x20";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 9);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x41\x30\x3d\x3d\x41\x31\x2b\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d"
         "\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53"
         "\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31"
         "\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d"
         "\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53"
         "\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31"
         "\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31"
         "\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x2c\x31\x29\x29\x29\x29"
         "\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x0a";
      static unsigned int write_00000_00000_len = 350;
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
         "\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x53\x75\x63\x63\x65\x73\x73\x2e\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 9);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 9;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x41\x63\x63\x65\x6c\x3a\x2d\x24\x20";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 9);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x53\x48\x4f\x57\x20\x41\x30\x0a";
      static unsigned int write_00001_00000_len = 8;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 1);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x43\x65\x6c\x6c\x20\x56\x61\x6c\x75\x65\x3a\x20\x31\x32\x39\x2e"
         "\x30\x30\x30\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 20);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 1);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x53\x75\x63\x63\x65\x73\x73\x2e\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 9);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 9;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x41\x63\x63\x65\x6c\x3a\x2d\x24\x20";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 9);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x41\x32\x3d\x3d\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c"
         "\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28"
         "\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55"
         "\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c"
         "\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28"
         "\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x53\x55"
         "\x4d\x28\x31\x2c\x53\x55\x4d\x28\x31\x2c\x31\x29\x29\x29\x29\x29"
         "\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x29\x0a";
      static unsigned int write_00002_00000_len = 125;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 1);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x53\x75\x63\x63\x65\x73\x73\x2e\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 9);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 9;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x41\x63\x63\x65\x6c\x3a\x2d\x24\x20";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 9);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x53\x48\x4f\x57\x20\x41\x32\x0a";
      static unsigned int write_00003_00000_len = 8;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x0a";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 1);
      if (read_00008_res) {} //silence unused variable warning
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x0a";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 1);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x53\x75\x63\x63\x65\x73\x73\x2e\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 9);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x45\x58\x49\x54\x0a";
      static unsigned int write_00004_00000_len = 5;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x0a";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 1);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x45\x78\x69\x74\x69\x6e\x67\x2e\x2e\x2e\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 11);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
}
