#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 32;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
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
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 15;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 9;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 2;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x30\x30\x32\x0a";
      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 10;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 1;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 17;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 15;
      read_00008 = (unsigned char*)cgc_malloc(read_00008_len);
      int read_00008_res = cgc_length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 9;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 2;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x31\x0a\x62\x59\x54\x4f\x75\x76\x4b\x74\x48\x6e\x4b\x6d\x59\x41"
         "\x72\x20\x6b\x20\x50\x6d\x4b\x64\x59\x44\x20\x4a\x20\x6c\x63\x6d"
         "\x79\x76\x77\x68\x6d\x41\x6b\x74\x74\x74\x53\x0a\x62\x70\x46\x4c"
         "\x43\x68\x76\x76\x49\x6d\x66\x75\x43\x58\x41\x6e\x44\x65\x20\x63"
         "\x44\x77\x6d\x49\x67\x6e\x4f\x47\x42\x64\x71\x7a\x4c\x62\x20\x52"
         "\x45\x4f\x44\x4a\x42\x64\x73\x72\x20\x72\x74\x53\x55\x49\x6c\x52"
         "\x74\x63\x63\x74\x5a\x53\x6d\x58\x4d\x4c\x20\x49\x0a\x7a\x65\x79"
         "\x67\x54\x41\x54\x61\x61\x73\x20\x56\x78\x5a\x41\x64\x58\x62\x59"
         "\x42\x4d\x6f\x50\x20\x44\x76\x6c\x63\x55\x49\x51\x6e\x49\x72\x49"
         "\x7a\x59\x51\x20\x43\x20\x70\x4d\x4c\x67\x62\x6a\x54\x4b\x7a\x0a"
         "\x67\x51\x6e\x72\x47\x48\x50\x44\x20\x4a\x4b\x20\x77\x4d\x6e\x4b"
         "\x4f\x6e\x6d\x64\x53\x54\x45\x73\x6f\x42\x74\x74\x20\x48\x66\x4f"
         "\x65\x20\x61\x42\x58\x48\x67\x73\x67\x43\x62\x45\x43\x65\x46\x66"
         "\x77\x4e\x62\x72\x6f\x0a\x4b\x69\x46\x6c\x79\x79\x76\x55\x49\x20"
         "\x61\x6e\x78\x69\x6f\x75\x73\x20\x56\x4d\x59\x6c\x69\x57\x67\x48"
         "\x20\x62\x6e\x7a\x7a\x47\x6f\x76\x45\x41\x62\x58\x4a\x44\x62\x6b"
         "\x4b\x4d\x4f\x6f\x6b\x20\x4a\x5a\x4b\x41\x68\x78\x55\x0a";
      static unsigned int write_00001_00000_len = 270;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 26;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 1;
      read_00012 = (unsigned char*)cgc_malloc(read_00012_len);
      int read_00012_res = cgc_length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 17;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length read
      read_00014_len = 15;
      read_00014 = (unsigned char*)cgc_malloc(read_00014_len);
      int read_00014_res = cgc_length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length read
      read_00015_len = 9;
      read_00015 = (unsigned char*)cgc_malloc(read_00015_len);
      int read_00015_res = cgc_length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length read
      read_00016_len = 2;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x31\x0a\x68\x6e\x7a\x45\x51\x69\x6e\x73\x71\x20\x6e\x4d\x58\x78"
         "\x6d\x6a\x0a\x43\x59\x77\x4b\x45\x4a\x46\x77\x20\x66\x0a\x20\x4d"
         "\x4d\x66\x20\x0a\x46\x66\x20\x66\x46\x66\x46\x46\x66\x0a\x66\x0a"
         "\x4d\x20\x4d\x0a\x20\x66\x46\x0a\x46\x66\x20\x0a\x20\x66\x46\x20"
         "\x46\x20\x66\x20\x66\x66\x4d\x20\x20\x66\x20\x0a\x0a\x20\x0a\x46"
         "\x0a\x66\x66\x0a\x46\x66\x4d\x0a\x46\x20\x20\x20\x66\x20\x66\x46"
         "\x46\x0a\x0a\x46\x66\x4d\x0a\x20\x4d\x4d\x0a\x46\x66\x0a\x66\x4d"
         "\x66\x0a\x4d\x4d\x66\x66\x46\x4d\x66\x20\x4d\x66\x20\x20\x20\x46"
         "\x20\x20\x4d\x20\x20\x66\x20\x66\x20\x20\x20\x66\x66\x66\x0a\x20"
         "\x66\x46\x20\x20\x4d\x4d\x20\x0a\x4d\x4d\x66\x4d\x66\x66\x66\x66"
         "\x4d\x66\x46\x0a\x46\x0a\x4d\x46\x66\x66\x20\x20\x46\x66\x66\x20"
         "\x0a\x20\x66\x46\x20\x66\x66\x4d\x4d\x4d\x20\x20\x46\x66\x66\x66"
         "\x0a\x20\x4d\x20\x20\x46\x4d\x20\x66\x20\x0a\x20\x20\x66\x66\x20"
         "\x46\x66\x46\x46\x46\x0a\x66\x66\x66\x66\x66\x20\x20\x66\x4d\x4d"
         "\x66\x46\x66\x66\x4d\x46\x20\x20\x46\x66\x0a\x66\x20\x66\x66\x4d"
         "\x46\x20\x66\x0a\x46\x46\x66\x20\x20\x66\x66\x46\x46\x0a\x66\x20"
         "\x46\x46\x66\x66\x4d\x20\x66\x20\x4d\x66\x66\x0a\x66\x20\x4d\x66"
         "\x0a\x4d\x66\x20\x66\x66\x20\x20\x20\x66\x20\x4d\x0a\x20\x46\x20"
         "\x0a\x66\x20\x66\x4d\x66\x20\x46\x66\x4d\x46\x0a\x4d\x66\x66\x4d"
         "\x20\x66\x20\x20\x20\x66\x66\x46\x66\x66\x66\x4d\x4d\x66\x66\x4d"
         "\x4d\x66\x20\x20\x66\x20\x4d\x0a\x20\x66\x20\x66\x20\x4d\x4d\x4d"
         "\x0a\x46\x46\x20\x20\x20\x46\x4d\x4d\x66\x20\x20\x46\x66\x46\x0a"
         "\x20\x66\x20\x66\x4d\x66\x66\x0a\x20\x4d\x66\x46\x46\x0a\x66\x20"
         "\x20\x66\x66\x4d\x66\x20\x66\x0a\x0a\x0a\x66\x46\x66\x46\x46\x66"
         "\x0a\x46\x66\x4d\x20\x20\x46\x0a\x20\x46\x66\x0a\x20\x20\x20\x66"
         "\x46\x20\x0a\x66\x0a\x66\x0a\x0a\x66\x66\x20\x20\x0a\x66\x20\x20"
         "\x0a\x20\x66\x46\x0a\x20\x20\x66\x20\x66\x66\x66\x0a\x46\x20\x46"
         "\x20\x20\x20\x20\x66\x20\x0a\x66\x20\x4d\x66\x20\x20\x66\x0a\x0a"
         "\x4d\x66\x20\x66\x46\x66\x4d\x66\x20\x66\x46\x20\x20\x4d\x46\x20"
         "\x4d\x66\x46\x0a\x46\x46\x66\x20\x66\x66\x46\x66\x20\x46\x20\x0a"
         "\x66\x46\x66\x0a\x20\x20\x66\x46\x66\x0a\x4d\x4d\x46\x20\x66\x66"
         "\x66\x0a\x20\x0a\x20\x66\x4d\x20\x0a\x66\x66\x66\x20\x66\x4d\x66"
         "\x46\x0a\x66\x0a\x0a\x66\x46\x0a\x4d\x20\x4d\x20\x20\x0a\x66\x20"
         "\x20\x20\x66\x46\x66\x20\x4d\x66\x66\x0a\x20\x66\x0a\x66\x20\x46"
         "\x4d\x0a\x20\x20\x4d\x20\x20\x20\x20\x20\x20\x0a\x66\x0a\x66\x4d"
         "\x66\x46\x66\x4d\x66\x0a\x66\x4d\x46\x66\x46\x46\x4d\x46\x4d\x20"
         "\x46\x66\x66\x66\x46\x4d\x20\x20\x0a\x66\x0a\x4d\x66\x66\x66\x66"
         "\x46\x66\x20\x0a\x66\x66\x4d\x20\x4d\x66\x0a\x20\x4d\x46\x66\x66"
         "\x20\x66\x66\x4d\x0a\x46\x20\x0a\x20\x66\x4d\x66\x66\x4d\x4d\x0a"
         "\x20\x4d\x0a\x66\x4d\x46\x20\x20\x4d\x66\x66\x66\x4d\x20\x20\x4d"
         "\x20\x66\x66\x20\x66\x4d\x20\x20\x66\x20\x66\x46\x46\x0a\x20\x46"
         "\x4d\x20\x0a\x66\x4d\x66\x4d\x66\x20\x0a\x46\x20\x66\x66\x4d\x46"
         "\x46\x20\x4d\x46\x0a\x20\x20\x4d\x66\x66\x66\x20\x66\x66\x0a\x20"
         "\x20\x20\x0a\x20\x0a\x4d\x20\x66\x20\x46\x66\x4d\x0a\x20\x66\x66"
         "\x20\x4d\x20\x20\x46\x20\x4d\x0a\x4d\x0a\x66\x0a\x66\x66\x66\x4d"
         "\x66\x66\x20\x4d\x4d\x0a\x20\x20\x20\x66\x4d\x4d\x20\x0a\x0a\x46"
         "\x4d\x66\x4d\x66\x4d\x20\x66\x20\x20\x20\x66\x46\x20\x4d\x66\x66"
         "\x4d\x4d\x0a\x20\x46\x4d\x20\x20\x20\x46\x46\x46\x20\x20\x66\x0a"
         "\x66\x20\x66\x20\x0a\x66\x20\x4d\x66\x66\x66\x20\x20\x20\x4d\x46"
         "\x0a\x4d\x0a\x46\x66\x20\x0a\x46\x0a\x20\x4d\x66\x20\x0a\x66\x20"
         "\x20\x20\x20\x20\x66\x66\x66\x66\x20\x20\x4d\x4d\x46\x20\x66\x46"
         "\x20\x0a\x20\x46\x20\x20\x4d\x20\x46\x20\x66\x4d\x66\x20\x66\x4d"
         "\x46\x4d\x66\x20\x4d\x0a\x20\x4d\x20\x20\x66\x20\x20\x66\x0a\x20"
         "\x66\x66\x0a\x4d\x20\x4d\x4d\x20\x20\x20\x66\x20\x46\x20\x66\x20"
         "\x0a\x20\x0a\x46\x66\x66\x66\x66\x66\x66\x4d\x66\x4d\x66\x4d\x0a"
         "\x4d\x66\x46\x46\x20\x20\x46\x66\x20\x46\x46\x20\x46\x20\x66\x46"
         "\x4d\x4d\x4d\x0a\x0a\x4d\x66\x66\x20\x46\x20\x66\x0a\x4d\x4d\x46"
         "\x20\x66\x20\x66\x66\x20\x20\x46\x46\x46\x20\x0a\x66\x66\x20\x0a"
         "\x0a\x0a\x20\x20\x4d\x4d\x66\x66\x66\x66\x0a\x4d\x0a\x46\x20\x66"
         "\x0a\x0a\x0a\x20\x0a\x0a\x4d\x66\x46\x4d\x66\x20\x20\x66\x20\x66"
         "\x66\x66\x66\x0a\x46\x0a\x4d\x20\x66\x4d\x66\x66\x66\x20\x0a\x0a"
         "\x66\x0a\x0a\x66\x0a\x46\x20\x66\x66\x66\x4d\x4d\x20\x66\x20\x4d"
         "\x20\x66\x20\x4d\x66\x46\x66\x0a\x0a\x46\x4d\x66\x0a\x20\x66\x66"
         "\x66\x66\x20\x0a\x20\x66\x66\x4d\x46\x0a\x66\x20\x4d\x66\x0a\x0a"
         "\x46\x20\x46\x66\x0a\x20\x66\x0a\x0a\x4d\x0a\x0a\x46\x66\x4d\x20"
         "\x4d\x0a\x20\x46\x66\x4d\x0a\x20\x66\x66\x46\x20\x20\x20\x0a\x0a"
         "\x20\x66\x20\x20\x4d\x66\x20\x20\x20\x20\x20\x46\x66\x66\x66\x0a"
         "\x66\x46\x66\x0a\x0a\x66\x66\x66\x46\x20\x66\x0a\x0a\x20\x4d\x20"
         "\x66\x4d\x0a\x20\x20\x20\x0a\x66\x46\x20\x20\x20\x66\x46\x46\x20"
         "\x20\x20\x0a\x20\x4d\x66\x4d\x66\x20\x20\x20\x20\x20\x46\x0a\x20"
         "\x66\x0a\x46\x66\x0a\x46\x46\x46\x46\x4d\x0a\x0a\x66\x20\x0a\x4d"
         "\x0a\x0a\x46\x46\x0a\x66\x20\x20\x20\x0a\x66\x20\x46\x66\x46\x20"
         "\x66\x66\x66\x66\x66\x20\x66\x46\x66\x20\x46\x20\x20\x66\x0a\x66"
         "\x66\x20\x66\x66\x20\x20\x4d\x20\x20\x4d\x46\x20\x0a\x66\x20\x20"
         "\x0a\x20\x4d\x20\x20\x4d\x4d\x4d\x4d\x66\x4d\x66\x0a\x4d\x0a\x0a"
         "\x20\x20\x66\x0a\x0a\x46\x20\x46\x66\x46\x46\x66\x46\x4d\x4d\x20"
         "\x46\x20\x20\x0a\x66\x4d\x4d\x20\x46\x20\x4d\x46\x66\x20\x46\x46"
         "\x20\x20\x46\x20\x4d\x46\x0a\x0a\x66\x66\x66\x66\x0a\x4d\x46\x20"
         "\x66\x4d\x20\x0a\x46\x66\x20\x4d\x46\x46\x66\x66\x0a\x4d\x0a\x20"
         "\x4d\x20\x0a\x66\x4d\x20\x66\x46\x4d\x20\x0a\x4d\x4d\x20\x66\x0a"
         "\x20\x66\x20\x20\x20\x66\x66\x66\x46\x20\x46\x46\x66\x66\x4d\x20"
         "\x66\x46\x66\x4d\x20\x46\x66\x0a\x66\x66\x46\x20\x20\x20\x4d\x0a"
         "\x20\x46\x0a\x46\x4d\x4d\x20\x66\x66\x20\x20\x4d\x66\x20\x46\x66"
         "\x4d\x46\x0a\x20\x4d\x66\x66\x20\x20\x0a\x66\x46\x20\x20\x20\x46"
         "\x4d\x0a\x4d\x66\x4d\x46\x4d\x46\x46\x66\x66\x20\x66\x20\x66\x4d"
         "\x20\x66\x46\x20\x46\x20\x0a\x4d\x20\x66\x0a\x46\x66\x0a\x66\x46"
         "\x4d\x20\x0a\x20\x0a\x66\x0a\x20\x46\x66\x46\x20\x0a\x0a\x20\x0a"
         "\x66\x4d\x20\x20\x20\x20\x66\x4d\x66\x66\x66\x66\x4d\x20\x20\x20"
         "\x0a\x66\x0a\x20\x46\x0a\x0a\x66\x0a\x66\x66\x20\x66\x20\x66\x20"
         "\x66\x20\x66\x66\x0a\x46\x0a\x4d\x66\x66\x0a\x66\x66\x66\x46\x66"
         "\x66\x20\x4d\x0a\x66\x66\x20\x4d\x4d\x66\x20\x20\x46\x20\x20\x66"
         "\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46"
         "\x46\x66\x20\x20\x66\x0a\x20\x4d\x0a\x66\x46\x66\x46\x46\x66\x46"
         "\x0a\x46\x66\x0a\x66\x46\x20\x0a\x66\x46\x20\x0a\x0a\x0a\x20\x66"
         "\x0a\x66\x4d\x4d\x0a\x66\x20\x20\x46\x4d\x46\x66\x66\x0a\x66\x66"
         "\x20\x66\x66\x20\x66\x20\x20\x66\x20\x20\x66\x0a\x46\x4d\x0a\x20"
         "\x46\x46\x66\x46\x20\x66\x20\x0a\x20\x4d\x20\x20\x46\x66\x66\x20"
         "\x0a\x20\x66\x20\x20\x20\x66\x46\x66\x46\x46\x20\x66\x20\x20\x20"
         "\x20\x66\x0a\x66\x4d\x0a\x0a\x66\x46\x20\x46\x0a\x46\x20\x66\x66"
         "\x20\x46\x66\x20\x0a\x20\x4d\x0a\x4d\x66\x66\x20\x0a\x0a\x20\x20"
         "\x66\x0a\x46\x0a\x4d\x46\x4d\x66\x0a\x66\x66\x66\x4d\x20\x20\x46"
         "\x20\x66\x46\x66\x66\x66\x66\x20\x66\x66\x20\x4d\x66\x0a\x46\x20"
         "\x4d\x66\x20\x66\x20\x66\x46\x0a\x46\x20\x66\x66\x46\x66\x20\x0a"
         "\x20\x4d\x20\x20\x0a\x66\x20\x4d\x46\x20\x20\x20\x0a\x0a\x0a\x4d"
         "\x0a\x20\x0a\x0a\x66\x66\x20\x20\x20\x20\x4d\x0a\x46\x66\x4d\x66"
         "\x20\x4d\x4d\x0a\x20\x66\x20\x20\x66\x66\x66\x66\x20\x0a\x4d\x0a"
         "\x0a\x4d\x20\x20\x0a\x66\x20\x20\x4d\x66\x46\x0a\x46\x66\x66\x46"
         "\x0a\x20\x46\x0a\x20\x20\x66\x66\x20\x66\x66\x20\x66\x0a\x0a\x66"
         "\x4d\x20\x66\x20\x4d\x20\x66\x46\x66\x66\x46\x20\x46\x20\x0a\x46"
         "\x0a\x46\x66\x20\x66\x46\x66\x66\x20\x20\x20\x4d\x20\x66\x4d\x20"
         "\x4d\x0a\x66\x20\x20\x0a\x20\x46\x20\x46\x0a\x4d\x20\x0a\x0a\x66"
         "\x66\x4d\x66\x46\x66\x20\x0a\x20\x66\x66\x46\x66\x46\x66\x46\x66"
         "\x0a\x20\x66\x66\x46\x0a\x4d\x46\x46\x4d\x66\x20\x66\x4d\x46\x46"
         "\x20\x66\x66\x20\x66\x4d\x66\x46\x0a\x20\x20\x20\x20\x4d\x20\x66"
         "\x66\x4d\x4d\x20\x4d\x66\x0a\x0a\x4d\x66\x66\x20\x4d\x20\x46\x46"
         "\x66\x66\x0a\x20\x0a\x66\x20\x0a\x20\x20\x0a\x66\x46\x20\x46\x20"
         "\x20\x66\x66\x20\x66\x66\x20\x20\x66\x66\x20\x20\x46\x4d\x0a\x66"
         "\x20\x4d\x20\x0a\x0a\x66\x20\x20\x4d\x20\x4d\x20\x66\x66\x0a\x20"
         "\x66\x20\x66\x4d\x4d\x4d\x4d\x20\x20\x66\x66\x20\x20\x0a\x20\x20"
         "\x4d\x20\x20\x4d\x66\x66\x66\x66\x66\x0a\x66\x46\x20\x4d\x0a\x20"
         "\x46\x0a\x46\x0a\x4d\x66\x66\x66\x20\x66\x66\x20\x66\x0a\x66\x20"
         "\x0a\x66\x46\x66\x20\x66\x20\x66\x20\x66\x20\x46\x4d\x20\x20\x66"
         "\x66\x46\x66\x66\x66\x66\x20\x66\x46\x20\x66\x20\x66\x46\x66\x66"
         "\x66\x20\x66\x20\x0a\x66\x4d\x0a\x66\x46\x46\x0a\x0a\x46\x66\x20"
         "\x4d\x66\x66\x20\x20\x66\x20\x46\x46\x4d\x0a\x4d\x66\x66\x0a\x20"
         "\x46\x66\x0a\x46\x66\x4d\x46\x20\x66\x4d\x0a\x66\x66\x66\x66\x0a"
         "\x0a\x20\x20\x0a\x66\x20\x46\x46\x20\x46\x66\x66\x20\x66\x20\x4d"
         "\x4d\x66\x66\x0a\x20\x46\x0a\x66\x66\x0a\x66\x66\x4d\x20\x66\x20"
         "\x66\x0a\x66\x0a\x20\x4d\x46\x46\x66\x66\x0a\x66\x66\x20\x20\x0a"
         "\x20\x66\x20\x46\x20\x20\x20\x20\x66\x46\x46\x20\x66\x20\x20\x20"
         "\x66\x0a\x20\x20\x46\x66\x20\x66\x4d\x0a\x4d\x0a\x20\x4d\x4d\x20"
         "\x46\x66\x70\x67\x4d\x6f\x48\x6d\x59\x64\x61\x62\x77\x68\x49\x73"
         "\x4d\x0a\x43\x50\x65\x74\x50\x7a\x20\x6b\x67\x74\x78\x66\x6e\x67"
         "\x74\x5a\x59\x73\x75\x79\x4e\x55\x6f\x58\x69\x0a\x64\x65\x70\x72"
         "\x65\x73\x73\x69\x76\x65\x20\x6c\x6f\x6e\x65\x6c\x79\x0a";
      static unsigned int write_00002_00000_len = 2158;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 26;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 1;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 17;
      read_00019 = (unsigned char*)cgc_malloc(read_00019_len);
      int read_00019_res = cgc_length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length read
      read_00020_len = 15;
      read_00020 = (unsigned char*)cgc_malloc(read_00020_len);
      int read_00020_res = cgc_length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** length read
      read_00021_len = 9;
      read_00021 = (unsigned char*)cgc_malloc(read_00021_len);
      int read_00021_res = cgc_length_read(0, read_00021, read_00021_len);
      if (read_00021_res) {} //silence unused variable warning
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** length read
      read_00022_len = 2;
      read_00022 = (unsigned char*)cgc_malloc(read_00022_len);
      int read_00022_res = cgc_length_read(0, read_00022, read_00022_len);
      if (read_00022_res) {} //silence unused variable warning
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x30\x30\x32\x0a";
      static unsigned int write_00003_00000_len = 4;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length read
      read_00023_len = 10;
      read_00023 = (unsigned char*)cgc_malloc(read_00023_len);
      int read_00023_res = cgc_length_read(0, read_00023, read_00023_len);
      if (read_00023_res) {} //silence unused variable warning
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** length read
      read_00024_len = 1;
      read_00024 = (unsigned char*)cgc_malloc(read_00024_len);
      int read_00024_res = cgc_length_read(0, read_00024, read_00024_len);
      if (read_00024_res) {} //silence unused variable warning
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** length read
      read_00025_len = 17;
      read_00025 = (unsigned char*)cgc_malloc(read_00025_len);
      int read_00025_res = cgc_length_read(0, read_00025, read_00025_len);
      if (read_00025_res) {} //silence unused variable warning
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** length read
      read_00026_len = 15;
      read_00026 = (unsigned char*)cgc_malloc(read_00026_len);
      int read_00026_res = cgc_length_read(0, read_00026, read_00026_len);
      if (read_00026_res) {} //silence unused variable warning
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** length read
      read_00027_len = 9;
      read_00027 = (unsigned char*)cgc_malloc(read_00027_len);
      int read_00027_res = cgc_length_read(0, read_00027, read_00027_len);
      if (read_00027_res) {} //silence unused variable warning
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** length read
      read_00028_len = 2;
      read_00028 = (unsigned char*)cgc_malloc(read_00028_len);
      int read_00028_res = cgc_length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x2d\x33\x0a";
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
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** length read
      read_00029_len = 28;
      read_00029 = (unsigned char*)cgc_malloc(read_00029_len);
      int read_00029_res = cgc_length_read(0, read_00029, read_00029_len);
      if (read_00029_res) {} //silence unused variable warning
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** length read
      read_00030_len = 1;
      read_00030 = (unsigned char*)cgc_malloc(read_00030_len);
      int read_00030_res = cgc_length_read(0, read_00030, read_00030_len);
      if (read_00030_res) {} //silence unused variable warning
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
}
