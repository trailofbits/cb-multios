#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 31;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x0a";
      static unsigned int write_00000_00000_len = 11;
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
      //**** length read
      read_00001_len = 79;
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
      read_00002_len = 2;
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
      read_00003_len = 59;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x31\x0a";
      static unsigned int write_00001_00000_len = 2;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 57;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 22;
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
      read_00006_len = 64;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x35\x30\x30\x0a";
      static unsigned int write_00002_00000_len = 4;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 15;
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
      read_00008_len = 17;
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
      read_00009_len = 28;
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
      read_00010_len = 16;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x53\x0a";
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
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 1;
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
      read_00012_len = 30;
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
      read_00013_len = 32;
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
      read_00014_len = 28;
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
      read_00015_len = 15;
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
      read_00016_len = 21;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 64;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x51\x55\x49\x54\x0a";
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
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 59;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x31\x0a";
      static unsigned int write_00005_00000_len = 2;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 57;
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
      read_00020_len = 21;
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
      read_00021_len = 64;
      read_00021 = (unsigned char*)cgc_malloc(read_00021_len);
      int read_00021_res = cgc_length_read(0, read_00021, read_00021_len);
      if (read_00021_res) {} //silence unused variable warning
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x35\x30\x30\x0a";
      static unsigned int write_00006_00000_len = 4;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** length read
      read_00022_len = 14;
      read_00022 = (unsigned char*)cgc_malloc(read_00022_len);
      int read_00022_res = cgc_length_read(0, read_00022, read_00022_len);
      if (read_00022_res) {} //silence unused variable warning
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length read
      read_00023_len = 17;
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
      read_00024_len = 27;
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
      read_00025_len = 18;
      read_00025 = (unsigned char*)cgc_malloc(read_00025_len);
      int read_00025_res = cgc_length_read(0, read_00025, read_00025_len);
      if (read_00025_res) {} //silence unused variable warning
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x58\x0a";
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
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** length read
      read_00026_len = 1;
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
      read_00027_len = 14;
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
      read_00028_len = 17;
      read_00028 = (unsigned char*)cgc_malloc(read_00028_len);
      int read_00028_res = cgc_length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** length read
      read_00029_len = 27;
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
      read_00030_len = 18;
      read_00030 = (unsigned char*)cgc_malloc(read_00030_len);
      int read_00030_res = cgc_length_read(0, read_00030, read_00030_len);
      if (read_00030_res) {} //silence unused variable warning
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x58\x0a";
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
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** length read
      read_00031_len = 1;
      read_00031 = (unsigned char*)cgc_malloc(read_00031_len);
      int read_00031_res = cgc_length_read(0, read_00031, read_00031_len);
      if (read_00031_res) {} //silence unused variable warning
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** length read
      read_00032_len = 14;
      read_00032 = (unsigned char*)cgc_malloc(read_00032_len);
      int read_00032_res = cgc_length_read(0, read_00032, read_00032_len);
      if (read_00032_res) {} //silence unused variable warning
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** length read
      read_00033_len = 17;
      read_00033 = (unsigned char*)cgc_malloc(read_00033_len);
      int read_00033_res = cgc_length_read(0, read_00033, read_00033_len);
      if (read_00033_res) {} //silence unused variable warning
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** length read
      read_00034_len = 28;
      read_00034 = (unsigned char*)cgc_malloc(read_00034_len);
      int read_00034_res = cgc_length_read(0, read_00034, read_00034_len);
      if (read_00034_res) {} //silence unused variable warning
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** length read
      read_00035_len = 16;
      read_00035 = (unsigned char*)cgc_malloc(read_00035_len);
      int read_00035_res = cgc_length_read(0, read_00035, read_00035_len);
      if (read_00035_res) {} //silence unused variable warning
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x58\x0a";
      static unsigned int write_00009_00000_len = 2;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** length read
      read_00036_len = 12;
      read_00036 = (unsigned char*)cgc_malloc(read_00036_len);
      int read_00036_res = cgc_length_read(0, read_00036, read_00036_len);
      if (read_00036_res) {} //silence unused variable warning
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length read
      read_00037_len = 14;
      read_00037 = (unsigned char*)cgc_malloc(read_00037_len);
      int read_00037_res = cgc_length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** length read
      read_00038_len = 17;
      read_00038 = (unsigned char*)cgc_malloc(read_00038_len);
      int read_00038_res = cgc_length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** length read
      read_00039_len = 28;
      read_00039 = (unsigned char*)cgc_malloc(read_00039_len);
      int read_00039_res = cgc_length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** length read
      read_00040_len = 16;
      read_00040 = (unsigned char*)cgc_malloc(read_00040_len);
      int read_00040_res = cgc_length_read(0, read_00040, read_00040_len);
      if (read_00040_res) {} //silence unused variable warning
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x58\x0a";
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
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** length read
      read_00041_len = 12;
      read_00041 = (unsigned char*)cgc_malloc(read_00041_len);
      int read_00041_res = cgc_length_read(0, read_00041, read_00041_len);
      if (read_00041_res) {} //silence unused variable warning
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** length read
      read_00042_len = 14;
      read_00042 = (unsigned char*)cgc_malloc(read_00042_len);
      int read_00042_res = cgc_length_read(0, read_00042, read_00042_len);
      if (read_00042_res) {} //silence unused variable warning
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** length read
      read_00043_len = 17;
      read_00043 = (unsigned char*)cgc_malloc(read_00043_len);
      int read_00043_res = cgc_length_read(0, read_00043, read_00043_len);
      if (read_00043_res) {} //silence unused variable warning
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** length read
      read_00044_len = 28;
      read_00044 = (unsigned char*)cgc_malloc(read_00044_len);
      int read_00044_res = cgc_length_read(0, read_00044, read_00044_len);
      if (read_00044_res) {} //silence unused variable warning
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** length read
      read_00045_len = 16;
      read_00045 = (unsigned char*)cgc_malloc(read_00045_len);
      int read_00045_res = cgc_length_read(0, read_00045, read_00045_len);
      if (read_00045_res) {} //silence unused variable warning
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x58\x0a";
      static unsigned int write_00011_00000_len = 2;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** length read
      read_00046_len = 12;
      read_00046 = (unsigned char*)cgc_malloc(read_00046_len);
      int read_00046_res = cgc_length_read(0, read_00046, read_00046_len);
      if (read_00046_res) {} //silence unused variable warning
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** length read
      read_00047_len = 14;
      read_00047 = (unsigned char*)cgc_malloc(read_00047_len);
      int read_00047_res = cgc_length_read(0, read_00047, read_00047_len);
      if (read_00047_res) {} //silence unused variable warning
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** length read
      read_00048_len = 17;
      read_00048 = (unsigned char*)cgc_malloc(read_00048_len);
      int read_00048_res = cgc_length_read(0, read_00048, read_00048_len);
      if (read_00048_res) {} //silence unused variable warning
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** length read
      read_00049_len = 28;
      read_00049 = (unsigned char*)cgc_malloc(read_00049_len);
      int read_00049_res = cgc_length_read(0, read_00049, read_00049_len);
      if (read_00049_res) {} //silence unused variable warning
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** length read
      read_00050_len = 16;
      read_00050 = (unsigned char*)cgc_malloc(read_00050_len);
      int read_00050_res = cgc_length_read(0, read_00050, read_00050_len);
      if (read_00050_res) {} //silence unused variable warning
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x58\x0a";
      static unsigned int write_00012_00000_len = 2;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** length read
      read_00051_len = 12;
      read_00051 = (unsigned char*)cgc_malloc(read_00051_len);
      int read_00051_res = cgc_length_read(0, read_00051, read_00051_len);
      if (read_00051_res) {} //silence unused variable warning
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** length read
      read_00052_len = 14;
      read_00052 = (unsigned char*)cgc_malloc(read_00052_len);
      int read_00052_res = cgc_length_read(0, read_00052, read_00052_len);
      if (read_00052_res) {} //silence unused variable warning
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** length read
      read_00053_len = 17;
      read_00053 = (unsigned char*)cgc_malloc(read_00053_len);
      int read_00053_res = cgc_length_read(0, read_00053, read_00053_len);
      if (read_00053_res) {} //silence unused variable warning
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00054;
      unsigned int read_00054_len;
      unsigned int read_00054_ptr = 0;
      //**** length read
      read_00054_len = 28;
      read_00054 = (unsigned char*)cgc_malloc(read_00054_len);
      int read_00054_res = cgc_length_read(0, read_00054, read_00054_len);
      if (read_00054_res) {} //silence unused variable warning
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00055;
      unsigned int read_00055_len;
      unsigned int read_00055_ptr = 0;
      //**** length read
      read_00055_len = 16;
      read_00055 = (unsigned char*)cgc_malloc(read_00055_len);
      int read_00055_res = cgc_length_read(0, read_00055, read_00055_len);
      if (read_00055_res) {} //silence unused variable warning
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x58\x0a";
      static unsigned int write_00013_00000_len = 2;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** length read
      read_00056_len = 12;
      read_00056 = (unsigned char*)cgc_malloc(read_00056_len);
      int read_00056_res = cgc_length_read(0, read_00056, read_00056_len);
      if (read_00056_res) {} //silence unused variable warning
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00057;
      unsigned int read_00057_len;
      unsigned int read_00057_ptr = 0;
      //**** length read
      read_00057_len = 14;
      read_00057 = (unsigned char*)cgc_malloc(read_00057_len);
      int read_00057_res = cgc_length_read(0, read_00057, read_00057_len);
      if (read_00057_res) {} //silence unused variable warning
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00058;
      unsigned int read_00058_len;
      unsigned int read_00058_ptr = 0;
      //**** length read
      read_00058_len = 17;
      read_00058 = (unsigned char*)cgc_malloc(read_00058_len);
      int read_00058_res = cgc_length_read(0, read_00058, read_00058_len);
      if (read_00058_res) {} //silence unused variable warning
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00059;
      unsigned int read_00059_len;
      unsigned int read_00059_ptr = 0;
      //**** length read
      read_00059_len = 28;
      read_00059 = (unsigned char*)cgc_malloc(read_00059_len);
      int read_00059_res = cgc_length_read(0, read_00059, read_00059_len);
      if (read_00059_res) {} //silence unused variable warning
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00060;
      unsigned int read_00060_len;
      unsigned int read_00060_ptr = 0;
      //**** length read
      read_00060_len = 16;
      read_00060 = (unsigned char*)cgc_malloc(read_00060_len);
      int read_00060_res = cgc_length_read(0, read_00060, read_00060_len);
      if (read_00060_res) {} //silence unused variable warning
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x58\x0a";
      static unsigned int write_00014_00000_len = 2;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00061;
      unsigned int read_00061_len;
      unsigned int read_00061_ptr = 0;
      //**** length read
      read_00061_len = 12;
      read_00061 = (unsigned char*)cgc_malloc(read_00061_len);
      int read_00061_res = cgc_length_read(0, read_00061, read_00061_len);
      if (read_00061_res) {} //silence unused variable warning
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00062;
      unsigned int read_00062_len;
      unsigned int read_00062_ptr = 0;
      //**** length read
      read_00062_len = 14;
      read_00062 = (unsigned char*)cgc_malloc(read_00062_len);
      int read_00062_res = cgc_length_read(0, read_00062, read_00062_len);
      if (read_00062_res) {} //silence unused variable warning
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00063;
      unsigned int read_00063_len;
      unsigned int read_00063_ptr = 0;
      //**** length read
      read_00063_len = 17;
      read_00063 = (unsigned char*)cgc_malloc(read_00063_len);
      int read_00063_res = cgc_length_read(0, read_00063, read_00063_len);
      if (read_00063_res) {} //silence unused variable warning
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00064;
      unsigned int read_00064_len;
      unsigned int read_00064_ptr = 0;
      //**** length read
      read_00064_len = 28;
      read_00064 = (unsigned char*)cgc_malloc(read_00064_len);
      int read_00064_res = cgc_length_read(0, read_00064, read_00064_len);
      if (read_00064_res) {} //silence unused variable warning
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00065;
      unsigned int read_00065_len;
      unsigned int read_00065_ptr = 0;
      //**** length read
      read_00065_len = 16;
      read_00065 = (unsigned char*)cgc_malloc(read_00065_len);
      int read_00065_res = cgc_length_read(0, read_00065, read_00065_len);
      if (read_00065_res) {} //silence unused variable warning
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x58\x0a";
      static unsigned int write_00015_00000_len = 2;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00066;
      unsigned int read_00066_len;
      unsigned int read_00066_ptr = 0;
      //**** length read
      read_00066_len = 12;
      read_00066 = (unsigned char*)cgc_malloc(read_00066_len);
      int read_00066_res = cgc_length_read(0, read_00066, read_00066_len);
      if (read_00066_res) {} //silence unused variable warning
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00067;
      unsigned int read_00067_len;
      unsigned int read_00067_ptr = 0;
      //**** length read
      read_00067_len = 14;
      read_00067 = (unsigned char*)cgc_malloc(read_00067_len);
      int read_00067_res = cgc_length_read(0, read_00067, read_00067_len);
      if (read_00067_res) {} //silence unused variable warning
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00068;
      unsigned int read_00068_len;
      unsigned int read_00068_ptr = 0;
      //**** length read
      read_00068_len = 17;
      read_00068 = (unsigned char*)cgc_malloc(read_00068_len);
      int read_00068_res = cgc_length_read(0, read_00068, read_00068_len);
      if (read_00068_res) {} //silence unused variable warning
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00069;
      unsigned int read_00069_len;
      unsigned int read_00069_ptr = 0;
      //**** length read
      read_00069_len = 28;
      read_00069 = (unsigned char*)cgc_malloc(read_00069_len);
      int read_00069_res = cgc_length_read(0, read_00069, read_00069_len);
      if (read_00069_res) {} //silence unused variable warning
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00070;
      unsigned int read_00070_len;
      unsigned int read_00070_ptr = 0;
      //**** length read
      read_00070_len = 16;
      read_00070 = (unsigned char*)cgc_malloc(read_00070_len);
      int read_00070_res = cgc_length_read(0, read_00070, read_00070_len);
      if (read_00070_res) {} //silence unused variable warning
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x58\x0a";
      static unsigned int write_00016_00000_len = 2;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00071;
      unsigned int read_00071_len;
      unsigned int read_00071_ptr = 0;
      //**** length read
      read_00071_len = 12;
      read_00071 = (unsigned char*)cgc_malloc(read_00071_len);
      int read_00071_res = cgc_length_read(0, read_00071, read_00071_len);
      if (read_00071_res) {} //silence unused variable warning
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00072;
      unsigned int read_00072_len;
      unsigned int read_00072_ptr = 0;
      //**** length read
      read_00072_len = 14;
      read_00072 = (unsigned char*)cgc_malloc(read_00072_len);
      int read_00072_res = cgc_length_read(0, read_00072, read_00072_len);
      if (read_00072_res) {} //silence unused variable warning
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00073;
      unsigned int read_00073_len;
      unsigned int read_00073_ptr = 0;
      //**** length read
      read_00073_len = 17;
      read_00073 = (unsigned char*)cgc_malloc(read_00073_len);
      int read_00073_res = cgc_length_read(0, read_00073, read_00073_len);
      if (read_00073_res) {} //silence unused variable warning
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00074;
      unsigned int read_00074_len;
      unsigned int read_00074_ptr = 0;
      //**** length read
      read_00074_len = 28;
      read_00074 = (unsigned char*)cgc_malloc(read_00074_len);
      int read_00074_res = cgc_length_read(0, read_00074, read_00074_len);
      if (read_00074_res) {} //silence unused variable warning
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00075;
      unsigned int read_00075_len;
      unsigned int read_00075_ptr = 0;
      //**** length read
      read_00075_len = 16;
      read_00075 = (unsigned char*)cgc_malloc(read_00075_len);
      int read_00075_res = cgc_length_read(0, read_00075, read_00075_len);
      if (read_00075_res) {} //silence unused variable warning
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x58\x0a";
      static unsigned int write_00017_00000_len = 2;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00076;
      unsigned int read_00076_len;
      unsigned int read_00076_ptr = 0;
      //**** length read
      read_00076_len = 12;
      read_00076 = (unsigned char*)cgc_malloc(read_00076_len);
      int read_00076_res = cgc_length_read(0, read_00076, read_00076_len);
      if (read_00076_res) {} //silence unused variable warning
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00077;
      unsigned int read_00077_len;
      unsigned int read_00077_ptr = 0;
      //**** length read
      read_00077_len = 14;
      read_00077 = (unsigned char*)cgc_malloc(read_00077_len);
      int read_00077_res = cgc_length_read(0, read_00077, read_00077_len);
      if (read_00077_res) {} //silence unused variable warning
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00078;
      unsigned int read_00078_len;
      unsigned int read_00078_ptr = 0;
      //**** length read
      read_00078_len = 17;
      read_00078 = (unsigned char*)cgc_malloc(read_00078_len);
      int read_00078_res = cgc_length_read(0, read_00078, read_00078_len);
      if (read_00078_res) {} //silence unused variable warning
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00079;
      unsigned int read_00079_len;
      unsigned int read_00079_ptr = 0;
      //**** length read
      read_00079_len = 28;
      read_00079 = (unsigned char*)cgc_malloc(read_00079_len);
      int read_00079_res = cgc_length_read(0, read_00079, read_00079_len);
      if (read_00079_res) {} //silence unused variable warning
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00080;
      unsigned int read_00080_len;
      unsigned int read_00080_ptr = 0;
      //**** length read
      read_00080_len = 16;
      read_00080 = (unsigned char*)cgc_malloc(read_00080_len);
      int read_00080_res = cgc_length_read(0, read_00080, read_00080_len);
      if (read_00080_res) {} //silence unused variable warning
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x58\x0a";
      static unsigned int write_00018_00000_len = 2;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00081;
      unsigned int read_00081_len;
      unsigned int read_00081_ptr = 0;
      //**** length read
      read_00081_len = 12;
      read_00081 = (unsigned char*)cgc_malloc(read_00081_len);
      int read_00081_res = cgc_length_read(0, read_00081, read_00081_len);
      if (read_00081_res) {} //silence unused variable warning
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00082;
      unsigned int read_00082_len;
      unsigned int read_00082_ptr = 0;
      //**** length read
      read_00082_len = 14;
      read_00082 = (unsigned char*)cgc_malloc(read_00082_len);
      int read_00082_res = cgc_length_read(0, read_00082, read_00082_len);
      if (read_00082_res) {} //silence unused variable warning
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00083;
      unsigned int read_00083_len;
      unsigned int read_00083_ptr = 0;
      //**** length read
      read_00083_len = 17;
      read_00083 = (unsigned char*)cgc_malloc(read_00083_len);
      int read_00083_res = cgc_length_read(0, read_00083, read_00083_len);
      if (read_00083_res) {} //silence unused variable warning
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00084;
      unsigned int read_00084_len;
      unsigned int read_00084_ptr = 0;
      //**** length read
      read_00084_len = 28;
      read_00084 = (unsigned char*)cgc_malloc(read_00084_len);
      int read_00084_res = cgc_length_read(0, read_00084, read_00084_len);
      if (read_00084_res) {} //silence unused variable warning
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00085;
      unsigned int read_00085_len;
      unsigned int read_00085_ptr = 0;
      //**** length read
      read_00085_len = 16;
      read_00085 = (unsigned char*)cgc_malloc(read_00085_len);
      int read_00085_res = cgc_length_read(0, read_00085, read_00085_len);
      if (read_00085_res) {} //silence unused variable warning
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x58\x0a";
      static unsigned int write_00019_00000_len = 2;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00086;
      unsigned int read_00086_len;
      unsigned int read_00086_ptr = 0;
      //**** length read
      read_00086_len = 12;
      read_00086 = (unsigned char*)cgc_malloc(read_00086_len);
      int read_00086_res = cgc_length_read(0, read_00086, read_00086_len);
      if (read_00086_res) {} //silence unused variable warning
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00087;
      unsigned int read_00087_len;
      unsigned int read_00087_ptr = 0;
      //**** length read
      read_00087_len = 14;
      read_00087 = (unsigned char*)cgc_malloc(read_00087_len);
      int read_00087_res = cgc_length_read(0, read_00087, read_00087_len);
      if (read_00087_res) {} //silence unused variable warning
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00088;
      unsigned int read_00088_len;
      unsigned int read_00088_ptr = 0;
      //**** length read
      read_00088_len = 17;
      read_00088 = (unsigned char*)cgc_malloc(read_00088_len);
      int read_00088_res = cgc_length_read(0, read_00088, read_00088_len);
      if (read_00088_res) {} //silence unused variable warning
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00089;
      unsigned int read_00089_len;
      unsigned int read_00089_ptr = 0;
      //**** length read
      read_00089_len = 28;
      read_00089 = (unsigned char*)cgc_malloc(read_00089_len);
      int read_00089_res = cgc_length_read(0, read_00089, read_00089_len);
      if (read_00089_res) {} //silence unused variable warning
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00090;
      unsigned int read_00090_len;
      unsigned int read_00090_ptr = 0;
      //**** length read
      read_00090_len = 16;
      read_00090 = (unsigned char*)cgc_malloc(read_00090_len);
      int read_00090_res = cgc_length_read(0, read_00090, read_00090_len);
      if (read_00090_res) {} //silence unused variable warning
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x58\x0a";
      static unsigned int write_00020_00000_len = 2;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00091;
      unsigned int read_00091_len;
      unsigned int read_00091_ptr = 0;
      //**** length read
      read_00091_len = 12;
      read_00091 = (unsigned char*)cgc_malloc(read_00091_len);
      int read_00091_res = cgc_length_read(0, read_00091, read_00091_len);
      if (read_00091_res) {} //silence unused variable warning
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00092;
      unsigned int read_00092_len;
      unsigned int read_00092_ptr = 0;
      //**** length read
      read_00092_len = 14;
      read_00092 = (unsigned char*)cgc_malloc(read_00092_len);
      int read_00092_res = cgc_length_read(0, read_00092, read_00092_len);
      if (read_00092_res) {} //silence unused variable warning
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00093;
      unsigned int read_00093_len;
      unsigned int read_00093_ptr = 0;
      //**** length read
      read_00093_len = 17;
      read_00093 = (unsigned char*)cgc_malloc(read_00093_len);
      int read_00093_res = cgc_length_read(0, read_00093, read_00093_len);
      if (read_00093_res) {} //silence unused variable warning
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00094;
      unsigned int read_00094_len;
      unsigned int read_00094_ptr = 0;
      //**** length read
      read_00094_len = 28;
      read_00094 = (unsigned char*)cgc_malloc(read_00094_len);
      int read_00094_res = cgc_length_read(0, read_00094, read_00094_len);
      if (read_00094_res) {} //silence unused variable warning
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00095;
      unsigned int read_00095_len;
      unsigned int read_00095_ptr = 0;
      //**** length read
      read_00095_len = 16;
      read_00095 = (unsigned char*)cgc_malloc(read_00095_len);
      int read_00095_res = cgc_length_read(0, read_00095, read_00095_len);
      if (read_00095_res) {} //silence unused variable warning
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x58\x0a";
      static unsigned int write_00021_00000_len = 2;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00096;
      unsigned int read_00096_len;
      unsigned int read_00096_ptr = 0;
      //**** length read
      read_00096_len = 12;
      read_00096 = (unsigned char*)cgc_malloc(read_00096_len);
      int read_00096_res = cgc_length_read(0, read_00096, read_00096_len);
      if (read_00096_res) {} //silence unused variable warning
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00097;
      unsigned int read_00097_len;
      unsigned int read_00097_ptr = 0;
      //**** length read
      read_00097_len = 14;
      read_00097 = (unsigned char*)cgc_malloc(read_00097_len);
      int read_00097_res = cgc_length_read(0, read_00097, read_00097_len);
      if (read_00097_res) {} //silence unused variable warning
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00098;
      unsigned int read_00098_len;
      unsigned int read_00098_ptr = 0;
      //**** length read
      read_00098_len = 17;
      read_00098 = (unsigned char*)cgc_malloc(read_00098_len);
      int read_00098_res = cgc_length_read(0, read_00098, read_00098_len);
      if (read_00098_res) {} //silence unused variable warning
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00099;
      unsigned int read_00099_len;
      unsigned int read_00099_ptr = 0;
      //**** length read
      read_00099_len = 28;
      read_00099 = (unsigned char*)cgc_malloc(read_00099_len);
      int read_00099_res = cgc_length_read(0, read_00099, read_00099_len);
      if (read_00099_res) {} //silence unused variable warning
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00100;
      unsigned int read_00100_len;
      unsigned int read_00100_ptr = 0;
      //**** length read
      read_00100_len = 16;
      read_00100 = (unsigned char*)cgc_malloc(read_00100_len);
      int read_00100_res = cgc_length_read(0, read_00100, read_00100_len);
      if (read_00100_res) {} //silence unused variable warning
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x58\x0a";
      static unsigned int write_00022_00000_len = 2;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00101;
      unsigned int read_00101_len;
      unsigned int read_00101_ptr = 0;
      //**** length read
      read_00101_len = 12;
      read_00101 = (unsigned char*)cgc_malloc(read_00101_len);
      int read_00101_res = cgc_length_read(0, read_00101, read_00101_len);
      if (read_00101_res) {} //silence unused variable warning
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00102;
      unsigned int read_00102_len;
      unsigned int read_00102_ptr = 0;
      //**** length read
      read_00102_len = 14;
      read_00102 = (unsigned char*)cgc_malloc(read_00102_len);
      int read_00102_res = cgc_length_read(0, read_00102, read_00102_len);
      if (read_00102_res) {} //silence unused variable warning
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00103;
      unsigned int read_00103_len;
      unsigned int read_00103_ptr = 0;
      //**** length read
      read_00103_len = 17;
      read_00103 = (unsigned char*)cgc_malloc(read_00103_len);
      int read_00103_res = cgc_length_read(0, read_00103, read_00103_len);
      if (read_00103_res) {} //silence unused variable warning
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00104;
      unsigned int read_00104_len;
      unsigned int read_00104_ptr = 0;
      //**** length read
      read_00104_len = 28;
      read_00104 = (unsigned char*)cgc_malloc(read_00104_len);
      int read_00104_res = cgc_length_read(0, read_00104, read_00104_len);
      if (read_00104_res) {} //silence unused variable warning
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00105;
      unsigned int read_00105_len;
      unsigned int read_00105_ptr = 0;
      //**** length read
      read_00105_len = 16;
      read_00105 = (unsigned char*)cgc_malloc(read_00105_len);
      int read_00105_res = cgc_length_read(0, read_00105, read_00105_len);
      if (read_00105_res) {} //silence unused variable warning
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x58\x0a";
      static unsigned int write_00023_00000_len = 2;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      unsigned char *read_00106;
      unsigned int read_00106_len;
      unsigned int read_00106_ptr = 0;
      //**** length read
      read_00106_len = 12;
      read_00106 = (unsigned char*)cgc_malloc(read_00106_len);
      int read_00106_res = cgc_length_read(0, read_00106, read_00106_len);
      if (read_00106_res) {} //silence unused variable warning
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00107;
      unsigned int read_00107_len;
      unsigned int read_00107_ptr = 0;
      //**** length read
      read_00107_len = 14;
      read_00107 = (unsigned char*)cgc_malloc(read_00107_len);
      int read_00107_res = cgc_length_read(0, read_00107, read_00107_len);
      if (read_00107_res) {} //silence unused variable warning
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00108;
      unsigned int read_00108_len;
      unsigned int read_00108_ptr = 0;
      //**** length read
      read_00108_len = 17;
      read_00108 = (unsigned char*)cgc_malloc(read_00108_len);
      int read_00108_res = cgc_length_read(0, read_00108, read_00108_len);
      if (read_00108_res) {} //silence unused variable warning
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00109;
      unsigned int read_00109_len;
      unsigned int read_00109_ptr = 0;
      //**** length read
      read_00109_len = 28;
      read_00109 = (unsigned char*)cgc_malloc(read_00109_len);
      int read_00109_res = cgc_length_read(0, read_00109, read_00109_len);
      if (read_00109_res) {} //silence unused variable warning
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00110;
      unsigned int read_00110_len;
      unsigned int read_00110_ptr = 0;
      //**** length read
      read_00110_len = 16;
      read_00110 = (unsigned char*)cgc_malloc(read_00110_len);
      int read_00110_res = cgc_length_read(0, read_00110, read_00110_len);
      if (read_00110_res) {} //silence unused variable warning
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x58\x0a";
      static unsigned int write_00024_00000_len = 2;
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      unsigned char *read_00111;
      unsigned int read_00111_len;
      unsigned int read_00111_ptr = 0;
      //**** length read
      read_00111_len = 12;
      read_00111 = (unsigned char*)cgc_malloc(read_00111_len);
      int read_00111_res = cgc_length_read(0, read_00111, read_00111_len);
      if (read_00111_res) {} //silence unused variable warning
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00112;
      unsigned int read_00112_len;
      unsigned int read_00112_ptr = 0;
      //**** length read
      read_00112_len = 14;
      read_00112 = (unsigned char*)cgc_malloc(read_00112_len);
      int read_00112_res = cgc_length_read(0, read_00112, read_00112_len);
      if (read_00112_res) {} //silence unused variable warning
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00113;
      unsigned int read_00113_len;
      unsigned int read_00113_ptr = 0;
      //**** length read
      read_00113_len = 17;
      read_00113 = (unsigned char*)cgc_malloc(read_00113_len);
      int read_00113_res = cgc_length_read(0, read_00113, read_00113_len);
      if (read_00113_res) {} //silence unused variable warning
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00114;
      unsigned int read_00114_len;
      unsigned int read_00114_ptr = 0;
      //**** length read
      read_00114_len = 28;
      read_00114 = (unsigned char*)cgc_malloc(read_00114_len);
      int read_00114_res = cgc_length_read(0, read_00114, read_00114_len);
      if (read_00114_res) {} //silence unused variable warning
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00115;
      unsigned int read_00115_len;
      unsigned int read_00115_ptr = 0;
      //**** length read
      read_00115_len = 16;
      read_00115 = (unsigned char*)cgc_malloc(read_00115_len);
      int read_00115_res = cgc_length_read(0, read_00115, read_00115_len);
      if (read_00115_res) {} //silence unused variable warning
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x58\x0a";
      static unsigned int write_00025_00000_len = 2;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      unsigned char *read_00116;
      unsigned int read_00116_len;
      unsigned int read_00116_ptr = 0;
      //**** length read
      read_00116_len = 12;
      read_00116 = (unsigned char*)cgc_malloc(read_00116_len);
      int read_00116_res = cgc_length_read(0, read_00116, read_00116_len);
      if (read_00116_res) {} //silence unused variable warning
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00117;
      unsigned int read_00117_len;
      unsigned int read_00117_ptr = 0;
      //**** length read
      read_00117_len = 14;
      read_00117 = (unsigned char*)cgc_malloc(read_00117_len);
      int read_00117_res = cgc_length_read(0, read_00117, read_00117_len);
      if (read_00117_res) {} //silence unused variable warning
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00118;
      unsigned int read_00118_len;
      unsigned int read_00118_ptr = 0;
      //**** length read
      read_00118_len = 17;
      read_00118 = (unsigned char*)cgc_malloc(read_00118_len);
      int read_00118_res = cgc_length_read(0, read_00118, read_00118_len);
      if (read_00118_res) {} //silence unused variable warning
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00119;
      unsigned int read_00119_len;
      unsigned int read_00119_ptr = 0;
      //**** length read
      read_00119_len = 28;
      read_00119 = (unsigned char*)cgc_malloc(read_00119_len);
      int read_00119_res = cgc_length_read(0, read_00119, read_00119_len);
      if (read_00119_res) {} //silence unused variable warning
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00120;
      unsigned int read_00120_len;
      unsigned int read_00120_ptr = 0;
      //**** length read
      read_00120_len = 16;
      read_00120 = (unsigned char*)cgc_malloc(read_00120_len);
      int read_00120_res = cgc_length_read(0, read_00120, read_00120_len);
      if (read_00120_res) {} //silence unused variable warning
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x58\x0a";
      static unsigned int write_00026_00000_len = 2;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      unsigned char *read_00121;
      unsigned int read_00121_len;
      unsigned int read_00121_ptr = 0;
      //**** length read
      read_00121_len = 12;
      read_00121 = (unsigned char*)cgc_malloc(read_00121_len);
      int read_00121_res = cgc_length_read(0, read_00121, read_00121_len);
      if (read_00121_res) {} //silence unused variable warning
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00122;
      unsigned int read_00122_len;
      unsigned int read_00122_ptr = 0;
      //**** length read
      read_00122_len = 14;
      read_00122 = (unsigned char*)cgc_malloc(read_00122_len);
      int read_00122_res = cgc_length_read(0, read_00122, read_00122_len);
      if (read_00122_res) {} //silence unused variable warning
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00123;
      unsigned int read_00123_len;
      unsigned int read_00123_ptr = 0;
      //**** length read
      read_00123_len = 17;
      read_00123 = (unsigned char*)cgc_malloc(read_00123_len);
      int read_00123_res = cgc_length_read(0, read_00123, read_00123_len);
      if (read_00123_res) {} //silence unused variable warning
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00124;
      unsigned int read_00124_len;
      unsigned int read_00124_ptr = 0;
      //**** length read
      read_00124_len = 28;
      read_00124 = (unsigned char*)cgc_malloc(read_00124_len);
      int read_00124_res = cgc_length_read(0, read_00124, read_00124_len);
      if (read_00124_res) {} //silence unused variable warning
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00125;
      unsigned int read_00125_len;
      unsigned int read_00125_ptr = 0;
      //**** length read
      read_00125_len = 16;
      read_00125 = (unsigned char*)cgc_malloc(read_00125_len);
      int read_00125_res = cgc_length_read(0, read_00125, read_00125_len);
      if (read_00125_res) {} //silence unused variable warning
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x58\x0a";
      static unsigned int write_00027_00000_len = 2;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      unsigned char *read_00126;
      unsigned int read_00126_len;
      unsigned int read_00126_ptr = 0;
      //**** length read
      read_00126_len = 12;
      read_00126 = (unsigned char*)cgc_malloc(read_00126_len);
      int read_00126_res = cgc_length_read(0, read_00126, read_00126_len);
      if (read_00126_res) {} //silence unused variable warning
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00127;
      unsigned int read_00127_len;
      unsigned int read_00127_ptr = 0;
      //**** length read
      read_00127_len = 14;
      read_00127 = (unsigned char*)cgc_malloc(read_00127_len);
      int read_00127_res = cgc_length_read(0, read_00127, read_00127_len);
      if (read_00127_res) {} //silence unused variable warning
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00128;
      unsigned int read_00128_len;
      unsigned int read_00128_ptr = 0;
      //**** length read
      read_00128_len = 17;
      read_00128 = (unsigned char*)cgc_malloc(read_00128_len);
      int read_00128_res = cgc_length_read(0, read_00128, read_00128_len);
      if (read_00128_res) {} //silence unused variable warning
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00129;
      unsigned int read_00129_len;
      unsigned int read_00129_ptr = 0;
      //**** length read
      read_00129_len = 28;
      read_00129 = (unsigned char*)cgc_malloc(read_00129_len);
      int read_00129_res = cgc_length_read(0, read_00129, read_00129_len);
      if (read_00129_res) {} //silence unused variable warning
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00130;
      unsigned int read_00130_len;
      unsigned int read_00130_ptr = 0;
      //**** length read
      read_00130_len = 16;
      read_00130 = (unsigned char*)cgc_malloc(read_00130_len);
      int read_00130_res = cgc_length_read(0, read_00130, read_00130_len);
      if (read_00130_res) {} //silence unused variable warning
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x58\x0a";
      static unsigned int write_00028_00000_len = 2;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      unsigned char *read_00131;
      unsigned int read_00131_len;
      unsigned int read_00131_ptr = 0;
      //**** length read
      read_00131_len = 12;
      read_00131 = (unsigned char*)cgc_malloc(read_00131_len);
      int read_00131_res = cgc_length_read(0, read_00131, read_00131_len);
      if (read_00131_res) {} //silence unused variable warning
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00132;
      unsigned int read_00132_len;
      unsigned int read_00132_ptr = 0;
      //**** length read
      read_00132_len = 14;
      read_00132 = (unsigned char*)cgc_malloc(read_00132_len);
      int read_00132_res = cgc_length_read(0, read_00132, read_00132_len);
      if (read_00132_res) {} //silence unused variable warning
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00133;
      unsigned int read_00133_len;
      unsigned int read_00133_ptr = 0;
      //**** length read
      read_00133_len = 17;
      read_00133 = (unsigned char*)cgc_malloc(read_00133_len);
      int read_00133_res = cgc_length_read(0, read_00133, read_00133_len);
      if (read_00133_res) {} //silence unused variable warning
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00134;
      unsigned int read_00134_len;
      unsigned int read_00134_ptr = 0;
      //**** length read
      read_00134_len = 28;
      read_00134 = (unsigned char*)cgc_malloc(read_00134_len);
      int read_00134_res = cgc_length_read(0, read_00134, read_00134_len);
      if (read_00134_res) {} //silence unused variable warning
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00135;
      unsigned int read_00135_len;
      unsigned int read_00135_ptr = 0;
      //**** length read
      read_00135_len = 16;
      read_00135 = (unsigned char*)cgc_malloc(read_00135_len);
      int read_00135_res = cgc_length_read(0, read_00135, read_00135_len);
      if (read_00135_res) {} //silence unused variable warning
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x58\x0a";
      static unsigned int write_00029_00000_len = 2;
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = cgc_append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
      if (write_00029_len > 0) {
         cgc_transmit_all(1, write_00029, write_00029_len);
      }
      cgc_free(write_00029);
   } while (0);
   do {
      unsigned char *read_00136;
      unsigned int read_00136_len;
      unsigned int read_00136_ptr = 0;
      //**** length read
      read_00136_len = 12;
      read_00136 = (unsigned char*)cgc_malloc(read_00136_len);
      int read_00136_res = cgc_length_read(0, read_00136, read_00136_len);
      if (read_00136_res) {} //silence unused variable warning
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00137;
      unsigned int read_00137_len;
      unsigned int read_00137_ptr = 0;
      //**** length read
      read_00137_len = 14;
      read_00137 = (unsigned char*)cgc_malloc(read_00137_len);
      int read_00137_res = cgc_length_read(0, read_00137, read_00137_len);
      if (read_00137_res) {} //silence unused variable warning
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00138;
      unsigned int read_00138_len;
      unsigned int read_00138_ptr = 0;
      //**** length read
      read_00138_len = 17;
      read_00138 = (unsigned char*)cgc_malloc(read_00138_len);
      int read_00138_res = cgc_length_read(0, read_00138, read_00138_len);
      if (read_00138_res) {} //silence unused variable warning
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00139;
      unsigned int read_00139_len;
      unsigned int read_00139_ptr = 0;
      //**** length read
      read_00139_len = 28;
      read_00139 = (unsigned char*)cgc_malloc(read_00139_len);
      int read_00139_res = cgc_length_read(0, read_00139, read_00139_len);
      if (read_00139_res) {} //silence unused variable warning
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00140;
      unsigned int read_00140_len;
      unsigned int read_00140_ptr = 0;
      //**** length read
      read_00140_len = 16;
      read_00140 = (unsigned char*)cgc_malloc(read_00140_len);
      int read_00140_res = cgc_length_read(0, read_00140, read_00140_len);
      if (read_00140_res) {} //silence unused variable warning
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x58\x0a";
      static unsigned int write_00030_00000_len = 2;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      unsigned char *read_00141;
      unsigned int read_00141_len;
      unsigned int read_00141_ptr = 0;
      //**** length read
      read_00141_len = 12;
      read_00141 = (unsigned char*)cgc_malloc(read_00141_len);
      int read_00141_res = cgc_length_read(0, read_00141, read_00141_len);
      if (read_00141_res) {} //silence unused variable warning
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00142;
      unsigned int read_00142_len;
      unsigned int read_00142_ptr = 0;
      //**** length read
      read_00142_len = 14;
      read_00142 = (unsigned char*)cgc_malloc(read_00142_len);
      int read_00142_res = cgc_length_read(0, read_00142, read_00142_len);
      if (read_00142_res) {} //silence unused variable warning
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00143;
      unsigned int read_00143_len;
      unsigned int read_00143_ptr = 0;
      //**** length read
      read_00143_len = 17;
      read_00143 = (unsigned char*)cgc_malloc(read_00143_len);
      int read_00143_res = cgc_length_read(0, read_00143, read_00143_len);
      if (read_00143_res) {} //silence unused variable warning
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00144;
      unsigned int read_00144_len;
      unsigned int read_00144_ptr = 0;
      //**** length read
      read_00144_len = 28;
      read_00144 = (unsigned char*)cgc_malloc(read_00144_len);
      int read_00144_res = cgc_length_read(0, read_00144, read_00144_len);
      if (read_00144_res) {} //silence unused variable warning
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00145;
      unsigned int read_00145_len;
      unsigned int read_00145_ptr = 0;
      //**** length read
      read_00145_len = 16;
      read_00145 = (unsigned char*)cgc_malloc(read_00145_len);
      int read_00145_res = cgc_length_read(0, read_00145, read_00145_len);
      if (read_00145_res) {} //silence unused variable warning
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x58\x0a";
      static unsigned int write_00031_00000_len = 2;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      unsigned char *read_00146;
      unsigned int read_00146_len;
      unsigned int read_00146_ptr = 0;
      //**** length read
      read_00146_len = 12;
      read_00146 = (unsigned char*)cgc_malloc(read_00146_len);
      int read_00146_res = cgc_length_read(0, read_00146, read_00146_len);
      if (read_00146_res) {} //silence unused variable warning
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00147;
      unsigned int read_00147_len;
      unsigned int read_00147_ptr = 0;
      //**** length read
      read_00147_len = 14;
      read_00147 = (unsigned char*)cgc_malloc(read_00147_len);
      int read_00147_res = cgc_length_read(0, read_00147, read_00147_len);
      if (read_00147_res) {} //silence unused variable warning
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00148;
      unsigned int read_00148_len;
      unsigned int read_00148_ptr = 0;
      //**** length read
      read_00148_len = 17;
      read_00148 = (unsigned char*)cgc_malloc(read_00148_len);
      int read_00148_res = cgc_length_read(0, read_00148, read_00148_len);
      if (read_00148_res) {} //silence unused variable warning
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00149;
      unsigned int read_00149_len;
      unsigned int read_00149_ptr = 0;
      //**** length read
      read_00149_len = 28;
      read_00149 = (unsigned char*)cgc_malloc(read_00149_len);
      int read_00149_res = cgc_length_read(0, read_00149, read_00149_len);
      if (read_00149_res) {} //silence unused variable warning
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00150;
      unsigned int read_00150_len;
      unsigned int read_00150_ptr = 0;
      //**** length read
      read_00150_len = 16;
      read_00150 = (unsigned char*)cgc_malloc(read_00150_len);
      int read_00150_res = cgc_length_read(0, read_00150, read_00150_len);
      if (read_00150_res) {} //silence unused variable warning
      cgc_free(read_00150);
      if (read_00150_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x58\x0a";
      static unsigned int write_00032_00000_len = 2;
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      unsigned char *read_00151;
      unsigned int read_00151_len;
      unsigned int read_00151_ptr = 0;
      //**** length read
      read_00151_len = 12;
      read_00151 = (unsigned char*)cgc_malloc(read_00151_len);
      int read_00151_res = cgc_length_read(0, read_00151, read_00151_len);
      if (read_00151_res) {} //silence unused variable warning
      cgc_free(read_00151);
      if (read_00151_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00152;
      unsigned int read_00152_len;
      unsigned int read_00152_ptr = 0;
      //**** length read
      read_00152_len = 14;
      read_00152 = (unsigned char*)cgc_malloc(read_00152_len);
      int read_00152_res = cgc_length_read(0, read_00152, read_00152_len);
      if (read_00152_res) {} //silence unused variable warning
      cgc_free(read_00152);
      if (read_00152_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00153;
      unsigned int read_00153_len;
      unsigned int read_00153_ptr = 0;
      //**** length read
      read_00153_len = 17;
      read_00153 = (unsigned char*)cgc_malloc(read_00153_len);
      int read_00153_res = cgc_length_read(0, read_00153, read_00153_len);
      if (read_00153_res) {} //silence unused variable warning
      cgc_free(read_00153);
      if (read_00153_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00154;
      unsigned int read_00154_len;
      unsigned int read_00154_ptr = 0;
      //**** length read
      read_00154_len = 28;
      read_00154 = (unsigned char*)cgc_malloc(read_00154_len);
      int read_00154_res = cgc_length_read(0, read_00154, read_00154_len);
      if (read_00154_res) {} //silence unused variable warning
      cgc_free(read_00154);
      if (read_00154_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00155;
      unsigned int read_00155_len;
      unsigned int read_00155_ptr = 0;
      //**** length read
      read_00155_len = 16;
      read_00155 = (unsigned char*)cgc_malloc(read_00155_len);
      int read_00155_res = cgc_length_read(0, read_00155, read_00155_len);
      if (read_00155_res) {} //silence unused variable warning
      cgc_free(read_00155);
      if (read_00155_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x58\x0a";
      static unsigned int write_00033_00000_len = 2;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      unsigned char *read_00156;
      unsigned int read_00156_len;
      unsigned int read_00156_ptr = 0;
      //**** length read
      read_00156_len = 12;
      read_00156 = (unsigned char*)cgc_malloc(read_00156_len);
      int read_00156_res = cgc_length_read(0, read_00156, read_00156_len);
      if (read_00156_res) {} //silence unused variable warning
      cgc_free(read_00156);
      if (read_00156_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00157;
      unsigned int read_00157_len;
      unsigned int read_00157_ptr = 0;
      //**** length read
      read_00157_len = 14;
      read_00157 = (unsigned char*)cgc_malloc(read_00157_len);
      int read_00157_res = cgc_length_read(0, read_00157, read_00157_len);
      if (read_00157_res) {} //silence unused variable warning
      cgc_free(read_00157);
      if (read_00157_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00158;
      unsigned int read_00158_len;
      unsigned int read_00158_ptr = 0;
      //**** length read
      read_00158_len = 17;
      read_00158 = (unsigned char*)cgc_malloc(read_00158_len);
      int read_00158_res = cgc_length_read(0, read_00158, read_00158_len);
      if (read_00158_res) {} //silence unused variable warning
      cgc_free(read_00158);
      if (read_00158_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00159;
      unsigned int read_00159_len;
      unsigned int read_00159_ptr = 0;
      //**** length read
      read_00159_len = 28;
      read_00159 = (unsigned char*)cgc_malloc(read_00159_len);
      int read_00159_res = cgc_length_read(0, read_00159, read_00159_len);
      if (read_00159_res) {} //silence unused variable warning
      cgc_free(read_00159);
      if (read_00159_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00160;
      unsigned int read_00160_len;
      unsigned int read_00160_ptr = 0;
      //**** length read
      read_00160_len = 16;
      read_00160 = (unsigned char*)cgc_malloc(read_00160_len);
      int read_00160_res = cgc_length_read(0, read_00160, read_00160_len);
      if (read_00160_res) {} //silence unused variable warning
      cgc_free(read_00160);
      if (read_00160_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x58\x0a";
      static unsigned int write_00034_00000_len = 2;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      unsigned char *read_00161;
      unsigned int read_00161_len;
      unsigned int read_00161_ptr = 0;
      //**** length read
      read_00161_len = 12;
      read_00161 = (unsigned char*)cgc_malloc(read_00161_len);
      int read_00161_res = cgc_length_read(0, read_00161, read_00161_len);
      if (read_00161_res) {} //silence unused variable warning
      cgc_free(read_00161);
      if (read_00161_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00162;
      unsigned int read_00162_len;
      unsigned int read_00162_ptr = 0;
      //**** length read
      read_00162_len = 14;
      read_00162 = (unsigned char*)cgc_malloc(read_00162_len);
      int read_00162_res = cgc_length_read(0, read_00162, read_00162_len);
      if (read_00162_res) {} //silence unused variable warning
      cgc_free(read_00162);
      if (read_00162_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00163;
      unsigned int read_00163_len;
      unsigned int read_00163_ptr = 0;
      //**** length read
      read_00163_len = 17;
      read_00163 = (unsigned char*)cgc_malloc(read_00163_len);
      int read_00163_res = cgc_length_read(0, read_00163, read_00163_len);
      if (read_00163_res) {} //silence unused variable warning
      cgc_free(read_00163);
      if (read_00163_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00164;
      unsigned int read_00164_len;
      unsigned int read_00164_ptr = 0;
      //**** length read
      read_00164_len = 28;
      read_00164 = (unsigned char*)cgc_malloc(read_00164_len);
      int read_00164_res = cgc_length_read(0, read_00164, read_00164_len);
      if (read_00164_res) {} //silence unused variable warning
      cgc_free(read_00164);
      if (read_00164_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00165;
      unsigned int read_00165_len;
      unsigned int read_00165_ptr = 0;
      //**** length read
      read_00165_len = 16;
      read_00165 = (unsigned char*)cgc_malloc(read_00165_len);
      int read_00165_res = cgc_length_read(0, read_00165, read_00165_len);
      if (read_00165_res) {} //silence unused variable warning
      cgc_free(read_00165);
      if (read_00165_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x58\x0a";
      static unsigned int write_00035_00000_len = 2;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      unsigned char *read_00166;
      unsigned int read_00166_len;
      unsigned int read_00166_ptr = 0;
      //**** length read
      read_00166_len = 12;
      read_00166 = (unsigned char*)cgc_malloc(read_00166_len);
      int read_00166_res = cgc_length_read(0, read_00166, read_00166_len);
      if (read_00166_res) {} //silence unused variable warning
      cgc_free(read_00166);
      if (read_00166_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00167;
      unsigned int read_00167_len;
      unsigned int read_00167_ptr = 0;
      //**** length read
      read_00167_len = 14;
      read_00167 = (unsigned char*)cgc_malloc(read_00167_len);
      int read_00167_res = cgc_length_read(0, read_00167, read_00167_len);
      if (read_00167_res) {} //silence unused variable warning
      cgc_free(read_00167);
      if (read_00167_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00168;
      unsigned int read_00168_len;
      unsigned int read_00168_ptr = 0;
      //**** length read
      read_00168_len = 17;
      read_00168 = (unsigned char*)cgc_malloc(read_00168_len);
      int read_00168_res = cgc_length_read(0, read_00168, read_00168_len);
      if (read_00168_res) {} //silence unused variable warning
      cgc_free(read_00168);
      if (read_00168_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00169;
      unsigned int read_00169_len;
      unsigned int read_00169_ptr = 0;
      //**** length read
      read_00169_len = 28;
      read_00169 = (unsigned char*)cgc_malloc(read_00169_len);
      int read_00169_res = cgc_length_read(0, read_00169, read_00169_len);
      if (read_00169_res) {} //silence unused variable warning
      cgc_free(read_00169);
      if (read_00169_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00170;
      unsigned int read_00170_len;
      unsigned int read_00170_ptr = 0;
      //**** length read
      read_00170_len = 16;
      read_00170 = (unsigned char*)cgc_malloc(read_00170_len);
      int read_00170_res = cgc_length_read(0, read_00170, read_00170_len);
      if (read_00170_res) {} //silence unused variable warning
      cgc_free(read_00170);
      if (read_00170_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x58\x0a";
      static unsigned int write_00036_00000_len = 2;
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_buf(write_00036, &write_00036_len, write_00036_00000, write_00036_00000_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      unsigned char *read_00171;
      unsigned int read_00171_len;
      unsigned int read_00171_ptr = 0;
      //**** length read
      read_00171_len = 12;
      read_00171 = (unsigned char*)cgc_malloc(read_00171_len);
      int read_00171_res = cgc_length_read(0, read_00171, read_00171_len);
      if (read_00171_res) {} //silence unused variable warning
      cgc_free(read_00171);
      if (read_00171_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00172;
      unsigned int read_00172_len;
      unsigned int read_00172_ptr = 0;
      //**** length read
      read_00172_len = 14;
      read_00172 = (unsigned char*)cgc_malloc(read_00172_len);
      int read_00172_res = cgc_length_read(0, read_00172, read_00172_len);
      if (read_00172_res) {} //silence unused variable warning
      cgc_free(read_00172);
      if (read_00172_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00173;
      unsigned int read_00173_len;
      unsigned int read_00173_ptr = 0;
      //**** length read
      read_00173_len = 17;
      read_00173 = (unsigned char*)cgc_malloc(read_00173_len);
      int read_00173_res = cgc_length_read(0, read_00173, read_00173_len);
      if (read_00173_res) {} //silence unused variable warning
      cgc_free(read_00173);
      if (read_00173_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00174;
      unsigned int read_00174_len;
      unsigned int read_00174_ptr = 0;
      //**** length read
      read_00174_len = 28;
      read_00174 = (unsigned char*)cgc_malloc(read_00174_len);
      int read_00174_res = cgc_length_read(0, read_00174, read_00174_len);
      if (read_00174_res) {} //silence unused variable warning
      cgc_free(read_00174);
      if (read_00174_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00175;
      unsigned int read_00175_len;
      unsigned int read_00175_ptr = 0;
      //**** length read
      read_00175_len = 16;
      read_00175 = (unsigned char*)cgc_malloc(read_00175_len);
      int read_00175_res = cgc_length_read(0, read_00175, read_00175_len);
      if (read_00175_res) {} //silence unused variable warning
      cgc_free(read_00175);
      if (read_00175_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x58\x0a";
      static unsigned int write_00037_00000_len = 2;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      unsigned char *read_00176;
      unsigned int read_00176_len;
      unsigned int read_00176_ptr = 0;
      //**** length read
      read_00176_len = 12;
      read_00176 = (unsigned char*)cgc_malloc(read_00176_len);
      int read_00176_res = cgc_length_read(0, read_00176, read_00176_len);
      if (read_00176_res) {} //silence unused variable warning
      cgc_free(read_00176);
      if (read_00176_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00177;
      unsigned int read_00177_len;
      unsigned int read_00177_ptr = 0;
      //**** length read
      read_00177_len = 14;
      read_00177 = (unsigned char*)cgc_malloc(read_00177_len);
      int read_00177_res = cgc_length_read(0, read_00177, read_00177_len);
      if (read_00177_res) {} //silence unused variable warning
      cgc_free(read_00177);
      if (read_00177_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00178;
      unsigned int read_00178_len;
      unsigned int read_00178_ptr = 0;
      //**** length read
      read_00178_len = 17;
      read_00178 = (unsigned char*)cgc_malloc(read_00178_len);
      int read_00178_res = cgc_length_read(0, read_00178, read_00178_len);
      if (read_00178_res) {} //silence unused variable warning
      cgc_free(read_00178);
      if (read_00178_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00179;
      unsigned int read_00179_len;
      unsigned int read_00179_ptr = 0;
      //**** length read
      read_00179_len = 28;
      read_00179 = (unsigned char*)cgc_malloc(read_00179_len);
      int read_00179_res = cgc_length_read(0, read_00179, read_00179_len);
      if (read_00179_res) {} //silence unused variable warning
      cgc_free(read_00179);
      if (read_00179_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00180;
      unsigned int read_00180_len;
      unsigned int read_00180_ptr = 0;
      //**** length read
      read_00180_len = 16;
      read_00180 = (unsigned char*)cgc_malloc(read_00180_len);
      int read_00180_res = cgc_length_read(0, read_00180, read_00180_len);
      if (read_00180_res) {} //silence unused variable warning
      cgc_free(read_00180);
      if (read_00180_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x58\x0a";
      static unsigned int write_00038_00000_len = 2;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      unsigned char *read_00181;
      unsigned int read_00181_len;
      unsigned int read_00181_ptr = 0;
      //**** length read
      read_00181_len = 12;
      read_00181 = (unsigned char*)cgc_malloc(read_00181_len);
      int read_00181_res = cgc_length_read(0, read_00181, read_00181_len);
      if (read_00181_res) {} //silence unused variable warning
      cgc_free(read_00181);
      if (read_00181_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00182;
      unsigned int read_00182_len;
      unsigned int read_00182_ptr = 0;
      //**** length read
      read_00182_len = 14;
      read_00182 = (unsigned char*)cgc_malloc(read_00182_len);
      int read_00182_res = cgc_length_read(0, read_00182, read_00182_len);
      if (read_00182_res) {} //silence unused variable warning
      cgc_free(read_00182);
      if (read_00182_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00183;
      unsigned int read_00183_len;
      unsigned int read_00183_ptr = 0;
      //**** length read
      read_00183_len = 17;
      read_00183 = (unsigned char*)cgc_malloc(read_00183_len);
      int read_00183_res = cgc_length_read(0, read_00183, read_00183_len);
      if (read_00183_res) {} //silence unused variable warning
      cgc_free(read_00183);
      if (read_00183_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00184;
      unsigned int read_00184_len;
      unsigned int read_00184_ptr = 0;
      //**** length read
      read_00184_len = 28;
      read_00184 = (unsigned char*)cgc_malloc(read_00184_len);
      int read_00184_res = cgc_length_read(0, read_00184, read_00184_len);
      if (read_00184_res) {} //silence unused variable warning
      cgc_free(read_00184);
      if (read_00184_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00185;
      unsigned int read_00185_len;
      unsigned int read_00185_ptr = 0;
      //**** length read
      read_00185_len = 16;
      read_00185 = (unsigned char*)cgc_malloc(read_00185_len);
      int read_00185_res = cgc_length_read(0, read_00185, read_00185_len);
      if (read_00185_res) {} //silence unused variable warning
      cgc_free(read_00185);
      if (read_00185_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x58\x0a";
      static unsigned int write_00039_00000_len = 2;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      unsigned char *read_00186;
      unsigned int read_00186_len;
      unsigned int read_00186_ptr = 0;
      //**** length read
      read_00186_len = 12;
      read_00186 = (unsigned char*)cgc_malloc(read_00186_len);
      int read_00186_res = cgc_length_read(0, read_00186, read_00186_len);
      if (read_00186_res) {} //silence unused variable warning
      cgc_free(read_00186);
      if (read_00186_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00187;
      unsigned int read_00187_len;
      unsigned int read_00187_ptr = 0;
      //**** length read
      read_00187_len = 14;
      read_00187 = (unsigned char*)cgc_malloc(read_00187_len);
      int read_00187_res = cgc_length_read(0, read_00187, read_00187_len);
      if (read_00187_res) {} //silence unused variable warning
      cgc_free(read_00187);
      if (read_00187_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00188;
      unsigned int read_00188_len;
      unsigned int read_00188_ptr = 0;
      //**** length read
      read_00188_len = 17;
      read_00188 = (unsigned char*)cgc_malloc(read_00188_len);
      int read_00188_res = cgc_length_read(0, read_00188, read_00188_len);
      if (read_00188_res) {} //silence unused variable warning
      cgc_free(read_00188);
      if (read_00188_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00189;
      unsigned int read_00189_len;
      unsigned int read_00189_ptr = 0;
      //**** length read
      read_00189_len = 28;
      read_00189 = (unsigned char*)cgc_malloc(read_00189_len);
      int read_00189_res = cgc_length_read(0, read_00189, read_00189_len);
      if (read_00189_res) {} //silence unused variable warning
      cgc_free(read_00189);
      if (read_00189_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00190;
      unsigned int read_00190_len;
      unsigned int read_00190_ptr = 0;
      //**** length read
      read_00190_len = 16;
      read_00190 = (unsigned char*)cgc_malloc(read_00190_len);
      int read_00190_res = cgc_length_read(0, read_00190, read_00190_len);
      if (read_00190_res) {} //silence unused variable warning
      cgc_free(read_00190);
      if (read_00190_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x58\x0a";
      static unsigned int write_00040_00000_len = 2;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      unsigned char *read_00191;
      unsigned int read_00191_len;
      unsigned int read_00191_ptr = 0;
      //**** length read
      read_00191_len = 12;
      read_00191 = (unsigned char*)cgc_malloc(read_00191_len);
      int read_00191_res = cgc_length_read(0, read_00191, read_00191_len);
      if (read_00191_res) {} //silence unused variable warning
      cgc_free(read_00191);
      if (read_00191_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00192;
      unsigned int read_00192_len;
      unsigned int read_00192_ptr = 0;
      //**** length read
      read_00192_len = 14;
      read_00192 = (unsigned char*)cgc_malloc(read_00192_len);
      int read_00192_res = cgc_length_read(0, read_00192, read_00192_len);
      if (read_00192_res) {} //silence unused variable warning
      cgc_free(read_00192);
      if (read_00192_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00193;
      unsigned int read_00193_len;
      unsigned int read_00193_ptr = 0;
      //**** length read
      read_00193_len = 17;
      read_00193 = (unsigned char*)cgc_malloc(read_00193_len);
      int read_00193_res = cgc_length_read(0, read_00193, read_00193_len);
      if (read_00193_res) {} //silence unused variable warning
      cgc_free(read_00193);
      if (read_00193_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00194;
      unsigned int read_00194_len;
      unsigned int read_00194_ptr = 0;
      //**** length read
      read_00194_len = 28;
      read_00194 = (unsigned char*)cgc_malloc(read_00194_len);
      int read_00194_res = cgc_length_read(0, read_00194, read_00194_len);
      if (read_00194_res) {} //silence unused variable warning
      cgc_free(read_00194);
      if (read_00194_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00195;
      unsigned int read_00195_len;
      unsigned int read_00195_ptr = 0;
      //**** length read
      read_00195_len = 16;
      read_00195 = (unsigned char*)cgc_malloc(read_00195_len);
      int read_00195_res = cgc_length_read(0, read_00195, read_00195_len);
      if (read_00195_res) {} //silence unused variable warning
      cgc_free(read_00195);
      if (read_00195_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x58\x0a";
      static unsigned int write_00041_00000_len = 2;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      unsigned char *read_00196;
      unsigned int read_00196_len;
      unsigned int read_00196_ptr = 0;
      //**** length read
      read_00196_len = 12;
      read_00196 = (unsigned char*)cgc_malloc(read_00196_len);
      int read_00196_res = cgc_length_read(0, read_00196, read_00196_len);
      if (read_00196_res) {} //silence unused variable warning
      cgc_free(read_00196);
      if (read_00196_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00197;
      unsigned int read_00197_len;
      unsigned int read_00197_ptr = 0;
      //**** length read
      read_00197_len = 14;
      read_00197 = (unsigned char*)cgc_malloc(read_00197_len);
      int read_00197_res = cgc_length_read(0, read_00197, read_00197_len);
      if (read_00197_res) {} //silence unused variable warning
      cgc_free(read_00197);
      if (read_00197_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00198;
      unsigned int read_00198_len;
      unsigned int read_00198_ptr = 0;
      //**** length read
      read_00198_len = 17;
      read_00198 = (unsigned char*)cgc_malloc(read_00198_len);
      int read_00198_res = cgc_length_read(0, read_00198, read_00198_len);
      if (read_00198_res) {} //silence unused variable warning
      cgc_free(read_00198);
      if (read_00198_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00199;
      unsigned int read_00199_len;
      unsigned int read_00199_ptr = 0;
      //**** length read
      read_00199_len = 28;
      read_00199 = (unsigned char*)cgc_malloc(read_00199_len);
      int read_00199_res = cgc_length_read(0, read_00199, read_00199_len);
      if (read_00199_res) {} //silence unused variable warning
      cgc_free(read_00199);
      if (read_00199_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00200;
      unsigned int read_00200_len;
      unsigned int read_00200_ptr = 0;
      //**** length read
      read_00200_len = 16;
      read_00200 = (unsigned char*)cgc_malloc(read_00200_len);
      int read_00200_res = cgc_length_read(0, read_00200, read_00200_len);
      if (read_00200_res) {} //silence unused variable warning
      cgc_free(read_00200);
      if (read_00200_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x58\x0a";
      static unsigned int write_00042_00000_len = 2;
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_buf(write_00042, &write_00042_len, write_00042_00000, write_00042_00000_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** length read
      read_00201_len = 12;
      read_00201 = (unsigned char*)cgc_malloc(read_00201_len);
      int read_00201_res = cgc_length_read(0, read_00201, read_00201_len);
      if (read_00201_res) {} //silence unused variable warning
      cgc_free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00202;
      unsigned int read_00202_len;
      unsigned int read_00202_ptr = 0;
      //**** length read
      read_00202_len = 14;
      read_00202 = (unsigned char*)cgc_malloc(read_00202_len);
      int read_00202_res = cgc_length_read(0, read_00202, read_00202_len);
      if (read_00202_res) {} //silence unused variable warning
      cgc_free(read_00202);
      if (read_00202_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00203;
      unsigned int read_00203_len;
      unsigned int read_00203_ptr = 0;
      //**** length read
      read_00203_len = 17;
      read_00203 = (unsigned char*)cgc_malloc(read_00203_len);
      int read_00203_res = cgc_length_read(0, read_00203, read_00203_len);
      if (read_00203_res) {} //silence unused variable warning
      cgc_free(read_00203);
      if (read_00203_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00204;
      unsigned int read_00204_len;
      unsigned int read_00204_ptr = 0;
      //**** length read
      read_00204_len = 28;
      read_00204 = (unsigned char*)cgc_malloc(read_00204_len);
      int read_00204_res = cgc_length_read(0, read_00204, read_00204_len);
      if (read_00204_res) {} //silence unused variable warning
      cgc_free(read_00204);
      if (read_00204_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00205;
      unsigned int read_00205_len;
      unsigned int read_00205_ptr = 0;
      //**** length read
      read_00205_len = 16;
      read_00205 = (unsigned char*)cgc_malloc(read_00205_len);
      int read_00205_res = cgc_length_read(0, read_00205, read_00205_len);
      if (read_00205_res) {} //silence unused variable warning
      cgc_free(read_00205);
      if (read_00205_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x58\x0a";
      static unsigned int write_00043_00000_len = 2;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      unsigned char *read_00206;
      unsigned int read_00206_len;
      unsigned int read_00206_ptr = 0;
      //**** length read
      read_00206_len = 12;
      read_00206 = (unsigned char*)cgc_malloc(read_00206_len);
      int read_00206_res = cgc_length_read(0, read_00206, read_00206_len);
      if (read_00206_res) {} //silence unused variable warning
      cgc_free(read_00206);
      if (read_00206_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00207;
      unsigned int read_00207_len;
      unsigned int read_00207_ptr = 0;
      //**** length read
      read_00207_len = 14;
      read_00207 = (unsigned char*)cgc_malloc(read_00207_len);
      int read_00207_res = cgc_length_read(0, read_00207, read_00207_len);
      if (read_00207_res) {} //silence unused variable warning
      cgc_free(read_00207);
      if (read_00207_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00208;
      unsigned int read_00208_len;
      unsigned int read_00208_ptr = 0;
      //**** length read
      read_00208_len = 17;
      read_00208 = (unsigned char*)cgc_malloc(read_00208_len);
      int read_00208_res = cgc_length_read(0, read_00208, read_00208_len);
      if (read_00208_res) {} //silence unused variable warning
      cgc_free(read_00208);
      if (read_00208_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00209;
      unsigned int read_00209_len;
      unsigned int read_00209_ptr = 0;
      //**** length read
      read_00209_len = 28;
      read_00209 = (unsigned char*)cgc_malloc(read_00209_len);
      int read_00209_res = cgc_length_read(0, read_00209, read_00209_len);
      if (read_00209_res) {} //silence unused variable warning
      cgc_free(read_00209);
      if (read_00209_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00210;
      unsigned int read_00210_len;
      unsigned int read_00210_ptr = 0;
      //**** length read
      read_00210_len = 16;
      read_00210 = (unsigned char*)cgc_malloc(read_00210_len);
      int read_00210_res = cgc_length_read(0, read_00210, read_00210_len);
      if (read_00210_res) {} //silence unused variable warning
      cgc_free(read_00210);
      if (read_00210_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x58\x0a";
      static unsigned int write_00044_00000_len = 2;
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_buf(write_00044, &write_00044_len, write_00044_00000, write_00044_00000_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
   } while (0);
   do {
      unsigned char *read_00211;
      unsigned int read_00211_len;
      unsigned int read_00211_ptr = 0;
      //**** length read
      read_00211_len = 12;
      read_00211 = (unsigned char*)cgc_malloc(read_00211_len);
      int read_00211_res = cgc_length_read(0, read_00211, read_00211_len);
      if (read_00211_res) {} //silence unused variable warning
      cgc_free(read_00211);
      if (read_00211_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00212;
      unsigned int read_00212_len;
      unsigned int read_00212_ptr = 0;
      //**** length read
      read_00212_len = 14;
      read_00212 = (unsigned char*)cgc_malloc(read_00212_len);
      int read_00212_res = cgc_length_read(0, read_00212, read_00212_len);
      if (read_00212_res) {} //silence unused variable warning
      cgc_free(read_00212);
      if (read_00212_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00213;
      unsigned int read_00213_len;
      unsigned int read_00213_ptr = 0;
      //**** length read
      read_00213_len = 17;
      read_00213 = (unsigned char*)cgc_malloc(read_00213_len);
      int read_00213_res = cgc_length_read(0, read_00213, read_00213_len);
      if (read_00213_res) {} //silence unused variable warning
      cgc_free(read_00213);
      if (read_00213_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00214;
      unsigned int read_00214_len;
      unsigned int read_00214_ptr = 0;
      //**** length read
      read_00214_len = 28;
      read_00214 = (unsigned char*)cgc_malloc(read_00214_len);
      int read_00214_res = cgc_length_read(0, read_00214, read_00214_len);
      if (read_00214_res) {} //silence unused variable warning
      cgc_free(read_00214);
      if (read_00214_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00215;
      unsigned int read_00215_len;
      unsigned int read_00215_ptr = 0;
      //**** length read
      read_00215_len = 16;
      read_00215 = (unsigned char*)cgc_malloc(read_00215_len);
      int read_00215_res = cgc_length_read(0, read_00215, read_00215_len);
      if (read_00215_res) {} //silence unused variable warning
      cgc_free(read_00215);
      if (read_00215_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x58\x0a";
      static unsigned int write_00045_00000_len = 2;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      unsigned char *read_00216;
      unsigned int read_00216_len;
      unsigned int read_00216_ptr = 0;
      //**** length read
      read_00216_len = 12;
      read_00216 = (unsigned char*)cgc_malloc(read_00216_len);
      int read_00216_res = cgc_length_read(0, read_00216, read_00216_len);
      if (read_00216_res) {} //silence unused variable warning
      cgc_free(read_00216);
      if (read_00216_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00217;
      unsigned int read_00217_len;
      unsigned int read_00217_ptr = 0;
      //**** length read
      read_00217_len = 14;
      read_00217 = (unsigned char*)cgc_malloc(read_00217_len);
      int read_00217_res = cgc_length_read(0, read_00217, read_00217_len);
      if (read_00217_res) {} //silence unused variable warning
      cgc_free(read_00217);
      if (read_00217_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00218;
      unsigned int read_00218_len;
      unsigned int read_00218_ptr = 0;
      //**** length read
      read_00218_len = 17;
      read_00218 = (unsigned char*)cgc_malloc(read_00218_len);
      int read_00218_res = cgc_length_read(0, read_00218, read_00218_len);
      if (read_00218_res) {} //silence unused variable warning
      cgc_free(read_00218);
      if (read_00218_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00219;
      unsigned int read_00219_len;
      unsigned int read_00219_ptr = 0;
      //**** length read
      read_00219_len = 28;
      read_00219 = (unsigned char*)cgc_malloc(read_00219_len);
      int read_00219_res = cgc_length_read(0, read_00219, read_00219_len);
      if (read_00219_res) {} //silence unused variable warning
      cgc_free(read_00219);
      if (read_00219_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00220;
      unsigned int read_00220_len;
      unsigned int read_00220_ptr = 0;
      //**** length read
      read_00220_len = 16;
      read_00220 = (unsigned char*)cgc_malloc(read_00220_len);
      int read_00220_res = cgc_length_read(0, read_00220, read_00220_len);
      if (read_00220_res) {} //silence unused variable warning
      cgc_free(read_00220);
      if (read_00220_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x58\x0a";
      static unsigned int write_00046_00000_len = 2;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      unsigned char *read_00221;
      unsigned int read_00221_len;
      unsigned int read_00221_ptr = 0;
      //**** length read
      read_00221_len = 12;
      read_00221 = (unsigned char*)cgc_malloc(read_00221_len);
      int read_00221_res = cgc_length_read(0, read_00221, read_00221_len);
      if (read_00221_res) {} //silence unused variable warning
      cgc_free(read_00221);
      if (read_00221_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00222;
      unsigned int read_00222_len;
      unsigned int read_00222_ptr = 0;
      //**** length read
      read_00222_len = 14;
      read_00222 = (unsigned char*)cgc_malloc(read_00222_len);
      int read_00222_res = cgc_length_read(0, read_00222, read_00222_len);
      if (read_00222_res) {} //silence unused variable warning
      cgc_free(read_00222);
      if (read_00222_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00223;
      unsigned int read_00223_len;
      unsigned int read_00223_ptr = 0;
      //**** length read
      read_00223_len = 17;
      read_00223 = (unsigned char*)cgc_malloc(read_00223_len);
      int read_00223_res = cgc_length_read(0, read_00223, read_00223_len);
      if (read_00223_res) {} //silence unused variable warning
      cgc_free(read_00223);
      if (read_00223_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00224;
      unsigned int read_00224_len;
      unsigned int read_00224_ptr = 0;
      //**** length read
      read_00224_len = 28;
      read_00224 = (unsigned char*)cgc_malloc(read_00224_len);
      int read_00224_res = cgc_length_read(0, read_00224, read_00224_len);
      if (read_00224_res) {} //silence unused variable warning
      cgc_free(read_00224);
      if (read_00224_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00225;
      unsigned int read_00225_len;
      unsigned int read_00225_ptr = 0;
      //**** length read
      read_00225_len = 16;
      read_00225 = (unsigned char*)cgc_malloc(read_00225_len);
      int read_00225_res = cgc_length_read(0, read_00225, read_00225_len);
      if (read_00225_res) {} //silence unused variable warning
      cgc_free(read_00225);
      if (read_00225_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x58\x0a";
      static unsigned int write_00047_00000_len = 2;
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = cgc_append_buf(write_00047, &write_00047_len, write_00047_00000, write_00047_00000_len);
      if (write_00047_len > 0) {
         cgc_transmit_all(1, write_00047, write_00047_len);
      }
      cgc_free(write_00047);
   } while (0);
   do {
      unsigned char *read_00226;
      unsigned int read_00226_len;
      unsigned int read_00226_ptr = 0;
      //**** length read
      read_00226_len = 12;
      read_00226 = (unsigned char*)cgc_malloc(read_00226_len);
      int read_00226_res = cgc_length_read(0, read_00226, read_00226_len);
      if (read_00226_res) {} //silence unused variable warning
      cgc_free(read_00226);
      if (read_00226_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00227;
      unsigned int read_00227_len;
      unsigned int read_00227_ptr = 0;
      //**** length read
      read_00227_len = 14;
      read_00227 = (unsigned char*)cgc_malloc(read_00227_len);
      int read_00227_res = cgc_length_read(0, read_00227, read_00227_len);
      if (read_00227_res) {} //silence unused variable warning
      cgc_free(read_00227);
      if (read_00227_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00228;
      unsigned int read_00228_len;
      unsigned int read_00228_ptr = 0;
      //**** length read
      read_00228_len = 17;
      read_00228 = (unsigned char*)cgc_malloc(read_00228_len);
      int read_00228_res = cgc_length_read(0, read_00228, read_00228_len);
      if (read_00228_res) {} //silence unused variable warning
      cgc_free(read_00228);
      if (read_00228_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00229;
      unsigned int read_00229_len;
      unsigned int read_00229_ptr = 0;
      //**** length read
      read_00229_len = 28;
      read_00229 = (unsigned char*)cgc_malloc(read_00229_len);
      int read_00229_res = cgc_length_read(0, read_00229, read_00229_len);
      if (read_00229_res) {} //silence unused variable warning
      cgc_free(read_00229);
      if (read_00229_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00230;
      unsigned int read_00230_len;
      unsigned int read_00230_ptr = 0;
      //**** length read
      read_00230_len = 16;
      read_00230 = (unsigned char*)cgc_malloc(read_00230_len);
      int read_00230_res = cgc_length_read(0, read_00230, read_00230_len);
      if (read_00230_res) {} //silence unused variable warning
      cgc_free(read_00230);
      if (read_00230_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x58\x0a";
      static unsigned int write_00048_00000_len = 2;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      unsigned char *read_00231;
      unsigned int read_00231_len;
      unsigned int read_00231_ptr = 0;
      //**** length read
      read_00231_len = 12;
      read_00231 = (unsigned char*)cgc_malloc(read_00231_len);
      int read_00231_res = cgc_length_read(0, read_00231, read_00231_len);
      if (read_00231_res) {} //silence unused variable warning
      cgc_free(read_00231);
      if (read_00231_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00232;
      unsigned int read_00232_len;
      unsigned int read_00232_ptr = 0;
      //**** length read
      read_00232_len = 14;
      read_00232 = (unsigned char*)cgc_malloc(read_00232_len);
      int read_00232_res = cgc_length_read(0, read_00232, read_00232_len);
      if (read_00232_res) {} //silence unused variable warning
      cgc_free(read_00232);
      if (read_00232_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00233;
      unsigned int read_00233_len;
      unsigned int read_00233_ptr = 0;
      //**** length read
      read_00233_len = 17;
      read_00233 = (unsigned char*)cgc_malloc(read_00233_len);
      int read_00233_res = cgc_length_read(0, read_00233, read_00233_len);
      if (read_00233_res) {} //silence unused variable warning
      cgc_free(read_00233);
      if (read_00233_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00234;
      unsigned int read_00234_len;
      unsigned int read_00234_ptr = 0;
      //**** length read
      read_00234_len = 28;
      read_00234 = (unsigned char*)cgc_malloc(read_00234_len);
      int read_00234_res = cgc_length_read(0, read_00234, read_00234_len);
      if (read_00234_res) {} //silence unused variable warning
      cgc_free(read_00234);
      if (read_00234_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00235;
      unsigned int read_00235_len;
      unsigned int read_00235_ptr = 0;
      //**** length read
      read_00235_len = 16;
      read_00235 = (unsigned char*)cgc_malloc(read_00235_len);
      int read_00235_res = cgc_length_read(0, read_00235, read_00235_len);
      if (read_00235_res) {} //silence unused variable warning
      cgc_free(read_00235);
      if (read_00235_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x58\x0a";
      static unsigned int write_00049_00000_len = 2;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      unsigned char *read_00236;
      unsigned int read_00236_len;
      unsigned int read_00236_ptr = 0;
      //**** length read
      read_00236_len = 12;
      read_00236 = (unsigned char*)cgc_malloc(read_00236_len);
      int read_00236_res = cgc_length_read(0, read_00236, read_00236_len);
      if (read_00236_res) {} //silence unused variable warning
      cgc_free(read_00236);
      if (read_00236_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00237;
      unsigned int read_00237_len;
      unsigned int read_00237_ptr = 0;
      //**** length read
      read_00237_len = 14;
      read_00237 = (unsigned char*)cgc_malloc(read_00237_len);
      int read_00237_res = cgc_length_read(0, read_00237, read_00237_len);
      if (read_00237_res) {} //silence unused variable warning
      cgc_free(read_00237);
      if (read_00237_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00238;
      unsigned int read_00238_len;
      unsigned int read_00238_ptr = 0;
      //**** length read
      read_00238_len = 17;
      read_00238 = (unsigned char*)cgc_malloc(read_00238_len);
      int read_00238_res = cgc_length_read(0, read_00238, read_00238_len);
      if (read_00238_res) {} //silence unused variable warning
      cgc_free(read_00238);
      if (read_00238_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00239;
      unsigned int read_00239_len;
      unsigned int read_00239_ptr = 0;
      //**** length read
      read_00239_len = 28;
      read_00239 = (unsigned char*)cgc_malloc(read_00239_len);
      int read_00239_res = cgc_length_read(0, read_00239, read_00239_len);
      if (read_00239_res) {} //silence unused variable warning
      cgc_free(read_00239);
      if (read_00239_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00240;
      unsigned int read_00240_len;
      unsigned int read_00240_ptr = 0;
      //**** length read
      read_00240_len = 16;
      read_00240 = (unsigned char*)cgc_malloc(read_00240_len);
      int read_00240_res = cgc_length_read(0, read_00240, read_00240_len);
      if (read_00240_res) {} //silence unused variable warning
      cgc_free(read_00240);
      if (read_00240_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x58\x0a";
      static unsigned int write_00050_00000_len = 2;
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_buf(write_00050, &write_00050_len, write_00050_00000, write_00050_00000_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      unsigned char *read_00241;
      unsigned int read_00241_len;
      unsigned int read_00241_ptr = 0;
      //**** length read
      read_00241_len = 12;
      read_00241 = (unsigned char*)cgc_malloc(read_00241_len);
      int read_00241_res = cgc_length_read(0, read_00241, read_00241_len);
      if (read_00241_res) {} //silence unused variable warning
      cgc_free(read_00241);
      if (read_00241_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00242;
      unsigned int read_00242_len;
      unsigned int read_00242_ptr = 0;
      //**** length read
      read_00242_len = 14;
      read_00242 = (unsigned char*)cgc_malloc(read_00242_len);
      int read_00242_res = cgc_length_read(0, read_00242, read_00242_len);
      if (read_00242_res) {} //silence unused variable warning
      cgc_free(read_00242);
      if (read_00242_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00243;
      unsigned int read_00243_len;
      unsigned int read_00243_ptr = 0;
      //**** length read
      read_00243_len = 17;
      read_00243 = (unsigned char*)cgc_malloc(read_00243_len);
      int read_00243_res = cgc_length_read(0, read_00243, read_00243_len);
      if (read_00243_res) {} //silence unused variable warning
      cgc_free(read_00243);
      if (read_00243_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00244;
      unsigned int read_00244_len;
      unsigned int read_00244_ptr = 0;
      //**** length read
      read_00244_len = 28;
      read_00244 = (unsigned char*)cgc_malloc(read_00244_len);
      int read_00244_res = cgc_length_read(0, read_00244, read_00244_len);
      if (read_00244_res) {} //silence unused variable warning
      cgc_free(read_00244);
      if (read_00244_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00245;
      unsigned int read_00245_len;
      unsigned int read_00245_ptr = 0;
      //**** length read
      read_00245_len = 16;
      read_00245 = (unsigned char*)cgc_malloc(read_00245_len);
      int read_00245_res = cgc_length_read(0, read_00245, read_00245_len);
      if (read_00245_res) {} //silence unused variable warning
      cgc_free(read_00245);
      if (read_00245_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x58\x0a";
      static unsigned int write_00051_00000_len = 2;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      unsigned char *read_00246;
      unsigned int read_00246_len;
      unsigned int read_00246_ptr = 0;
      //**** length read
      read_00246_len = 12;
      read_00246 = (unsigned char*)cgc_malloc(read_00246_len);
      int read_00246_res = cgc_length_read(0, read_00246, read_00246_len);
      if (read_00246_res) {} //silence unused variable warning
      cgc_free(read_00246);
      if (read_00246_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00247;
      unsigned int read_00247_len;
      unsigned int read_00247_ptr = 0;
      //**** length read
      read_00247_len = 14;
      read_00247 = (unsigned char*)cgc_malloc(read_00247_len);
      int read_00247_res = cgc_length_read(0, read_00247, read_00247_len);
      if (read_00247_res) {} //silence unused variable warning
      cgc_free(read_00247);
      if (read_00247_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00248;
      unsigned int read_00248_len;
      unsigned int read_00248_ptr = 0;
      //**** length read
      read_00248_len = 17;
      read_00248 = (unsigned char*)cgc_malloc(read_00248_len);
      int read_00248_res = cgc_length_read(0, read_00248, read_00248_len);
      if (read_00248_res) {} //silence unused variable warning
      cgc_free(read_00248);
      if (read_00248_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00249;
      unsigned int read_00249_len;
      unsigned int read_00249_ptr = 0;
      //**** length read
      read_00249_len = 28;
      read_00249 = (unsigned char*)cgc_malloc(read_00249_len);
      int read_00249_res = cgc_length_read(0, read_00249, read_00249_len);
      if (read_00249_res) {} //silence unused variable warning
      cgc_free(read_00249);
      if (read_00249_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00250;
      unsigned int read_00250_len;
      unsigned int read_00250_ptr = 0;
      //**** length read
      read_00250_len = 16;
      read_00250 = (unsigned char*)cgc_malloc(read_00250_len);
      int read_00250_res = cgc_length_read(0, read_00250, read_00250_len);
      if (read_00250_res) {} //silence unused variable warning
      cgc_free(read_00250);
      if (read_00250_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x58\x0a";
      static unsigned int write_00052_00000_len = 2;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      unsigned char *read_00251;
      unsigned int read_00251_len;
      unsigned int read_00251_ptr = 0;
      //**** length read
      read_00251_len = 12;
      read_00251 = (unsigned char*)cgc_malloc(read_00251_len);
      int read_00251_res = cgc_length_read(0, read_00251, read_00251_len);
      if (read_00251_res) {} //silence unused variable warning
      cgc_free(read_00251);
      if (read_00251_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00252;
      unsigned int read_00252_len;
      unsigned int read_00252_ptr = 0;
      //**** length read
      read_00252_len = 14;
      read_00252 = (unsigned char*)cgc_malloc(read_00252_len);
      int read_00252_res = cgc_length_read(0, read_00252, read_00252_len);
      if (read_00252_res) {} //silence unused variable warning
      cgc_free(read_00252);
      if (read_00252_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00253;
      unsigned int read_00253_len;
      unsigned int read_00253_ptr = 0;
      //**** length read
      read_00253_len = 17;
      read_00253 = (unsigned char*)cgc_malloc(read_00253_len);
      int read_00253_res = cgc_length_read(0, read_00253, read_00253_len);
      if (read_00253_res) {} //silence unused variable warning
      cgc_free(read_00253);
      if (read_00253_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00254;
      unsigned int read_00254_len;
      unsigned int read_00254_ptr = 0;
      //**** length read
      read_00254_len = 28;
      read_00254 = (unsigned char*)cgc_malloc(read_00254_len);
      int read_00254_res = cgc_length_read(0, read_00254, read_00254_len);
      if (read_00254_res) {} //silence unused variable warning
      cgc_free(read_00254);
      if (read_00254_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00255;
      unsigned int read_00255_len;
      unsigned int read_00255_ptr = 0;
      //**** length read
      read_00255_len = 16;
      read_00255 = (unsigned char*)cgc_malloc(read_00255_len);
      int read_00255_res = cgc_length_read(0, read_00255, read_00255_len);
      if (read_00255_res) {} //silence unused variable warning
      cgc_free(read_00255);
      if (read_00255_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x58\x0a";
      static unsigned int write_00053_00000_len = 2;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      unsigned char *read_00256;
      unsigned int read_00256_len;
      unsigned int read_00256_ptr = 0;
      //**** length read
      read_00256_len = 12;
      read_00256 = (unsigned char*)cgc_malloc(read_00256_len);
      int read_00256_res = cgc_length_read(0, read_00256, read_00256_len);
      if (read_00256_res) {} //silence unused variable warning
      cgc_free(read_00256);
      if (read_00256_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00257;
      unsigned int read_00257_len;
      unsigned int read_00257_ptr = 0;
      //**** length read
      read_00257_len = 14;
      read_00257 = (unsigned char*)cgc_malloc(read_00257_len);
      int read_00257_res = cgc_length_read(0, read_00257, read_00257_len);
      if (read_00257_res) {} //silence unused variable warning
      cgc_free(read_00257);
      if (read_00257_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00258;
      unsigned int read_00258_len;
      unsigned int read_00258_ptr = 0;
      //**** length read
      read_00258_len = 17;
      read_00258 = (unsigned char*)cgc_malloc(read_00258_len);
      int read_00258_res = cgc_length_read(0, read_00258, read_00258_len);
      if (read_00258_res) {} //silence unused variable warning
      cgc_free(read_00258);
      if (read_00258_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00259;
      unsigned int read_00259_len;
      unsigned int read_00259_ptr = 0;
      //**** length read
      read_00259_len = 28;
      read_00259 = (unsigned char*)cgc_malloc(read_00259_len);
      int read_00259_res = cgc_length_read(0, read_00259, read_00259_len);
      if (read_00259_res) {} //silence unused variable warning
      cgc_free(read_00259);
      if (read_00259_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00260;
      unsigned int read_00260_len;
      unsigned int read_00260_ptr = 0;
      //**** length read
      read_00260_len = 16;
      read_00260 = (unsigned char*)cgc_malloc(read_00260_len);
      int read_00260_res = cgc_length_read(0, read_00260, read_00260_len);
      if (read_00260_res) {} //silence unused variable warning
      cgc_free(read_00260);
      if (read_00260_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x58\x0a";
      static unsigned int write_00054_00000_len = 2;
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_buf(write_00054, &write_00054_len, write_00054_00000, write_00054_00000_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      unsigned char *read_00261;
      unsigned int read_00261_len;
      unsigned int read_00261_ptr = 0;
      //**** length read
      read_00261_len = 12;
      read_00261 = (unsigned char*)cgc_malloc(read_00261_len);
      int read_00261_res = cgc_length_read(0, read_00261, read_00261_len);
      if (read_00261_res) {} //silence unused variable warning
      cgc_free(read_00261);
      if (read_00261_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00262;
      unsigned int read_00262_len;
      unsigned int read_00262_ptr = 0;
      //**** length read
      read_00262_len = 14;
      read_00262 = (unsigned char*)cgc_malloc(read_00262_len);
      int read_00262_res = cgc_length_read(0, read_00262, read_00262_len);
      if (read_00262_res) {} //silence unused variable warning
      cgc_free(read_00262);
      if (read_00262_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00263;
      unsigned int read_00263_len;
      unsigned int read_00263_ptr = 0;
      //**** length read
      read_00263_len = 17;
      read_00263 = (unsigned char*)cgc_malloc(read_00263_len);
      int read_00263_res = cgc_length_read(0, read_00263, read_00263_len);
      if (read_00263_res) {} //silence unused variable warning
      cgc_free(read_00263);
      if (read_00263_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00264;
      unsigned int read_00264_len;
      unsigned int read_00264_ptr = 0;
      //**** length read
      read_00264_len = 28;
      read_00264 = (unsigned char*)cgc_malloc(read_00264_len);
      int read_00264_res = cgc_length_read(0, read_00264, read_00264_len);
      if (read_00264_res) {} //silence unused variable warning
      cgc_free(read_00264);
      if (read_00264_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00265;
      unsigned int read_00265_len;
      unsigned int read_00265_ptr = 0;
      //**** length read
      read_00265_len = 16;
      read_00265 = (unsigned char*)cgc_malloc(read_00265_len);
      int read_00265_res = cgc_length_read(0, read_00265, read_00265_len);
      if (read_00265_res) {} //silence unused variable warning
      cgc_free(read_00265);
      if (read_00265_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x58\x0a";
      static unsigned int write_00055_00000_len = 2;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      unsigned char *read_00266;
      unsigned int read_00266_len;
      unsigned int read_00266_ptr = 0;
      //**** length read
      read_00266_len = 12;
      read_00266 = (unsigned char*)cgc_malloc(read_00266_len);
      int read_00266_res = cgc_length_read(0, read_00266, read_00266_len);
      if (read_00266_res) {} //silence unused variable warning
      cgc_free(read_00266);
      if (read_00266_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00267;
      unsigned int read_00267_len;
      unsigned int read_00267_ptr = 0;
      //**** length read
      read_00267_len = 14;
      read_00267 = (unsigned char*)cgc_malloc(read_00267_len);
      int read_00267_res = cgc_length_read(0, read_00267, read_00267_len);
      if (read_00267_res) {} //silence unused variable warning
      cgc_free(read_00267);
      if (read_00267_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00268;
      unsigned int read_00268_len;
      unsigned int read_00268_ptr = 0;
      //**** length read
      read_00268_len = 17;
      read_00268 = (unsigned char*)cgc_malloc(read_00268_len);
      int read_00268_res = cgc_length_read(0, read_00268, read_00268_len);
      if (read_00268_res) {} //silence unused variable warning
      cgc_free(read_00268);
      if (read_00268_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00269;
      unsigned int read_00269_len;
      unsigned int read_00269_ptr = 0;
      //**** length read
      read_00269_len = 28;
      read_00269 = (unsigned char*)cgc_malloc(read_00269_len);
      int read_00269_res = cgc_length_read(0, read_00269, read_00269_len);
      if (read_00269_res) {} //silence unused variable warning
      cgc_free(read_00269);
      if (read_00269_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00270;
      unsigned int read_00270_len;
      unsigned int read_00270_ptr = 0;
      //**** length read
      read_00270_len = 16;
      read_00270 = (unsigned char*)cgc_malloc(read_00270_len);
      int read_00270_res = cgc_length_read(0, read_00270, read_00270_len);
      if (read_00270_res) {} //silence unused variable warning
      cgc_free(read_00270);
      if (read_00270_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x58\x0a";
      static unsigned int write_00056_00000_len = 2;
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_buf(write_00056, &write_00056_len, write_00056_00000, write_00056_00000_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      unsigned char *read_00271;
      unsigned int read_00271_len;
      unsigned int read_00271_ptr = 0;
      //**** length read
      read_00271_len = 12;
      read_00271 = (unsigned char*)cgc_malloc(read_00271_len);
      int read_00271_res = cgc_length_read(0, read_00271, read_00271_len);
      if (read_00271_res) {} //silence unused variable warning
      cgc_free(read_00271);
      if (read_00271_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00272;
      unsigned int read_00272_len;
      unsigned int read_00272_ptr = 0;
      //**** length read
      read_00272_len = 14;
      read_00272 = (unsigned char*)cgc_malloc(read_00272_len);
      int read_00272_res = cgc_length_read(0, read_00272, read_00272_len);
      if (read_00272_res) {} //silence unused variable warning
      cgc_free(read_00272);
      if (read_00272_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00273;
      unsigned int read_00273_len;
      unsigned int read_00273_ptr = 0;
      //**** length read
      read_00273_len = 17;
      read_00273 = (unsigned char*)cgc_malloc(read_00273_len);
      int read_00273_res = cgc_length_read(0, read_00273, read_00273_len);
      if (read_00273_res) {} //silence unused variable warning
      cgc_free(read_00273);
      if (read_00273_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00274;
      unsigned int read_00274_len;
      unsigned int read_00274_ptr = 0;
      //**** length read
      read_00274_len = 28;
      read_00274 = (unsigned char*)cgc_malloc(read_00274_len);
      int read_00274_res = cgc_length_read(0, read_00274, read_00274_len);
      if (read_00274_res) {} //silence unused variable warning
      cgc_free(read_00274);
      if (read_00274_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00275;
      unsigned int read_00275_len;
      unsigned int read_00275_ptr = 0;
      //**** length read
      read_00275_len = 16;
      read_00275 = (unsigned char*)cgc_malloc(read_00275_len);
      int read_00275_res = cgc_length_read(0, read_00275, read_00275_len);
      if (read_00275_res) {} //silence unused variable warning
      cgc_free(read_00275);
      if (read_00275_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x58\x0a";
      static unsigned int write_00057_00000_len = 2;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      unsigned char *read_00276;
      unsigned int read_00276_len;
      unsigned int read_00276_ptr = 0;
      //**** length read
      read_00276_len = 12;
      read_00276 = (unsigned char*)cgc_malloc(read_00276_len);
      int read_00276_res = cgc_length_read(0, read_00276, read_00276_len);
      if (read_00276_res) {} //silence unused variable warning
      cgc_free(read_00276);
      if (read_00276_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00277;
      unsigned int read_00277_len;
      unsigned int read_00277_ptr = 0;
      //**** length read
      read_00277_len = 14;
      read_00277 = (unsigned char*)cgc_malloc(read_00277_len);
      int read_00277_res = cgc_length_read(0, read_00277, read_00277_len);
      if (read_00277_res) {} //silence unused variable warning
      cgc_free(read_00277);
      if (read_00277_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00278;
      unsigned int read_00278_len;
      unsigned int read_00278_ptr = 0;
      //**** length read
      read_00278_len = 17;
      read_00278 = (unsigned char*)cgc_malloc(read_00278_len);
      int read_00278_res = cgc_length_read(0, read_00278, read_00278_len);
      if (read_00278_res) {} //silence unused variable warning
      cgc_free(read_00278);
      if (read_00278_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00279;
      unsigned int read_00279_len;
      unsigned int read_00279_ptr = 0;
      //**** length read
      read_00279_len = 28;
      read_00279 = (unsigned char*)cgc_malloc(read_00279_len);
      int read_00279_res = cgc_length_read(0, read_00279, read_00279_len);
      if (read_00279_res) {} //silence unused variable warning
      cgc_free(read_00279);
      if (read_00279_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00280;
      unsigned int read_00280_len;
      unsigned int read_00280_ptr = 0;
      //**** length read
      read_00280_len = 16;
      read_00280 = (unsigned char*)cgc_malloc(read_00280_len);
      int read_00280_res = cgc_length_read(0, read_00280, read_00280_len);
      if (read_00280_res) {} //silence unused variable warning
      cgc_free(read_00280);
      if (read_00280_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x58\x0a";
      static unsigned int write_00058_00000_len = 2;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      unsigned char *read_00281;
      unsigned int read_00281_len;
      unsigned int read_00281_ptr = 0;
      //**** length read
      read_00281_len = 12;
      read_00281 = (unsigned char*)cgc_malloc(read_00281_len);
      int read_00281_res = cgc_length_read(0, read_00281, read_00281_len);
      if (read_00281_res) {} //silence unused variable warning
      cgc_free(read_00281);
      if (read_00281_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00282;
      unsigned int read_00282_len;
      unsigned int read_00282_ptr = 0;
      //**** length read
      read_00282_len = 14;
      read_00282 = (unsigned char*)cgc_malloc(read_00282_len);
      int read_00282_res = cgc_length_read(0, read_00282, read_00282_len);
      if (read_00282_res) {} //silence unused variable warning
      cgc_free(read_00282);
      if (read_00282_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00283;
      unsigned int read_00283_len;
      unsigned int read_00283_ptr = 0;
      //**** length read
      read_00283_len = 17;
      read_00283 = (unsigned char*)cgc_malloc(read_00283_len);
      int read_00283_res = cgc_length_read(0, read_00283, read_00283_len);
      if (read_00283_res) {} //silence unused variable warning
      cgc_free(read_00283);
      if (read_00283_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00284;
      unsigned int read_00284_len;
      unsigned int read_00284_ptr = 0;
      //**** length read
      read_00284_len = 28;
      read_00284 = (unsigned char*)cgc_malloc(read_00284_len);
      int read_00284_res = cgc_length_read(0, read_00284, read_00284_len);
      if (read_00284_res) {} //silence unused variable warning
      cgc_free(read_00284);
      if (read_00284_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00285;
      unsigned int read_00285_len;
      unsigned int read_00285_ptr = 0;
      //**** length read
      read_00285_len = 16;
      read_00285 = (unsigned char*)cgc_malloc(read_00285_len);
      int read_00285_res = cgc_length_read(0, read_00285, read_00285_len);
      if (read_00285_res) {} //silence unused variable warning
      cgc_free(read_00285);
      if (read_00285_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x58\x0a";
      static unsigned int write_00059_00000_len = 2;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      unsigned char *read_00286;
      unsigned int read_00286_len;
      unsigned int read_00286_ptr = 0;
      //**** length read
      read_00286_len = 12;
      read_00286 = (unsigned char*)cgc_malloc(read_00286_len);
      int read_00286_res = cgc_length_read(0, read_00286, read_00286_len);
      if (read_00286_res) {} //silence unused variable warning
      cgc_free(read_00286);
      if (read_00286_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00287;
      unsigned int read_00287_len;
      unsigned int read_00287_ptr = 0;
      //**** length read
      read_00287_len = 14;
      read_00287 = (unsigned char*)cgc_malloc(read_00287_len);
      int read_00287_res = cgc_length_read(0, read_00287, read_00287_len);
      if (read_00287_res) {} //silence unused variable warning
      cgc_free(read_00287);
      if (read_00287_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00288;
      unsigned int read_00288_len;
      unsigned int read_00288_ptr = 0;
      //**** length read
      read_00288_len = 17;
      read_00288 = (unsigned char*)cgc_malloc(read_00288_len);
      int read_00288_res = cgc_length_read(0, read_00288, read_00288_len);
      if (read_00288_res) {} //silence unused variable warning
      cgc_free(read_00288);
      if (read_00288_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00289;
      unsigned int read_00289_len;
      unsigned int read_00289_ptr = 0;
      //**** length read
      read_00289_len = 28;
      read_00289 = (unsigned char*)cgc_malloc(read_00289_len);
      int read_00289_res = cgc_length_read(0, read_00289, read_00289_len);
      if (read_00289_res) {} //silence unused variable warning
      cgc_free(read_00289);
      if (read_00289_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00290;
      unsigned int read_00290_len;
      unsigned int read_00290_ptr = 0;
      //**** length read
      read_00290_len = 16;
      read_00290 = (unsigned char*)cgc_malloc(read_00290_len);
      int read_00290_res = cgc_length_read(0, read_00290, read_00290_len);
      if (read_00290_res) {} //silence unused variable warning
      cgc_free(read_00290);
      if (read_00290_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x58\x0a";
      static unsigned int write_00060_00000_len = 2;
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_buf(write_00060, &write_00060_len, write_00060_00000, write_00060_00000_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      unsigned char *read_00291;
      unsigned int read_00291_len;
      unsigned int read_00291_ptr = 0;
      //**** length read
      read_00291_len = 12;
      read_00291 = (unsigned char*)cgc_malloc(read_00291_len);
      int read_00291_res = cgc_length_read(0, read_00291, read_00291_len);
      if (read_00291_res) {} //silence unused variable warning
      cgc_free(read_00291);
      if (read_00291_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00292;
      unsigned int read_00292_len;
      unsigned int read_00292_ptr = 0;
      //**** length read
      read_00292_len = 14;
      read_00292 = (unsigned char*)cgc_malloc(read_00292_len);
      int read_00292_res = cgc_length_read(0, read_00292, read_00292_len);
      if (read_00292_res) {} //silence unused variable warning
      cgc_free(read_00292);
      if (read_00292_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00293;
      unsigned int read_00293_len;
      unsigned int read_00293_ptr = 0;
      //**** length read
      read_00293_len = 17;
      read_00293 = (unsigned char*)cgc_malloc(read_00293_len);
      int read_00293_res = cgc_length_read(0, read_00293, read_00293_len);
      if (read_00293_res) {} //silence unused variable warning
      cgc_free(read_00293);
      if (read_00293_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00294;
      unsigned int read_00294_len;
      unsigned int read_00294_ptr = 0;
      //**** length read
      read_00294_len = 28;
      read_00294 = (unsigned char*)cgc_malloc(read_00294_len);
      int read_00294_res = cgc_length_read(0, read_00294, read_00294_len);
      if (read_00294_res) {} //silence unused variable warning
      cgc_free(read_00294);
      if (read_00294_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00295;
      unsigned int read_00295_len;
      unsigned int read_00295_ptr = 0;
      //**** length read
      read_00295_len = 16;
      read_00295 = (unsigned char*)cgc_malloc(read_00295_len);
      int read_00295_res = cgc_length_read(0, read_00295, read_00295_len);
      if (read_00295_res) {} //silence unused variable warning
      cgc_free(read_00295);
      if (read_00295_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x58\x0a";
      static unsigned int write_00061_00000_len = 2;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      unsigned char *read_00296;
      unsigned int read_00296_len;
      unsigned int read_00296_ptr = 0;
      //**** length read
      read_00296_len = 12;
      read_00296 = (unsigned char*)cgc_malloc(read_00296_len);
      int read_00296_res = cgc_length_read(0, read_00296, read_00296_len);
      if (read_00296_res) {} //silence unused variable warning
      cgc_free(read_00296);
      if (read_00296_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00297;
      unsigned int read_00297_len;
      unsigned int read_00297_ptr = 0;
      //**** length read
      read_00297_len = 14;
      read_00297 = (unsigned char*)cgc_malloc(read_00297_len);
      int read_00297_res = cgc_length_read(0, read_00297, read_00297_len);
      if (read_00297_res) {} //silence unused variable warning
      cgc_free(read_00297);
      if (read_00297_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00298;
      unsigned int read_00298_len;
      unsigned int read_00298_ptr = 0;
      //**** length read
      read_00298_len = 17;
      read_00298 = (unsigned char*)cgc_malloc(read_00298_len);
      int read_00298_res = cgc_length_read(0, read_00298, read_00298_len);
      if (read_00298_res) {} //silence unused variable warning
      cgc_free(read_00298);
      if (read_00298_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00299;
      unsigned int read_00299_len;
      unsigned int read_00299_ptr = 0;
      //**** length read
      read_00299_len = 28;
      read_00299 = (unsigned char*)cgc_malloc(read_00299_len);
      int read_00299_res = cgc_length_read(0, read_00299, read_00299_len);
      if (read_00299_res) {} //silence unused variable warning
      cgc_free(read_00299);
      if (read_00299_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00300;
      unsigned int read_00300_len;
      unsigned int read_00300_ptr = 0;
      //**** length read
      read_00300_len = 16;
      read_00300 = (unsigned char*)cgc_malloc(read_00300_len);
      int read_00300_res = cgc_length_read(0, read_00300, read_00300_len);
      if (read_00300_res) {} //silence unused variable warning
      cgc_free(read_00300);
      if (read_00300_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x58\x0a";
      static unsigned int write_00062_00000_len = 2;
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_buf(write_00062, &write_00062_len, write_00062_00000, write_00062_00000_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      unsigned char *read_00301;
      unsigned int read_00301_len;
      unsigned int read_00301_ptr = 0;
      //**** length read
      read_00301_len = 12;
      read_00301 = (unsigned char*)cgc_malloc(read_00301_len);
      int read_00301_res = cgc_length_read(0, read_00301, read_00301_len);
      if (read_00301_res) {} //silence unused variable warning
      cgc_free(read_00301);
      if (read_00301_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00302;
      unsigned int read_00302_len;
      unsigned int read_00302_ptr = 0;
      //**** length read
      read_00302_len = 14;
      read_00302 = (unsigned char*)cgc_malloc(read_00302_len);
      int read_00302_res = cgc_length_read(0, read_00302, read_00302_len);
      if (read_00302_res) {} //silence unused variable warning
      cgc_free(read_00302);
      if (read_00302_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00303;
      unsigned int read_00303_len;
      unsigned int read_00303_ptr = 0;
      //**** length read
      read_00303_len = 17;
      read_00303 = (unsigned char*)cgc_malloc(read_00303_len);
      int read_00303_res = cgc_length_read(0, read_00303, read_00303_len);
      if (read_00303_res) {} //silence unused variable warning
      cgc_free(read_00303);
      if (read_00303_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00304;
      unsigned int read_00304_len;
      unsigned int read_00304_ptr = 0;
      //**** length read
      read_00304_len = 28;
      read_00304 = (unsigned char*)cgc_malloc(read_00304_len);
      int read_00304_res = cgc_length_read(0, read_00304, read_00304_len);
      if (read_00304_res) {} //silence unused variable warning
      cgc_free(read_00304);
      if (read_00304_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00305;
      unsigned int read_00305_len;
      unsigned int read_00305_ptr = 0;
      //**** length read
      read_00305_len = 16;
      read_00305 = (unsigned char*)cgc_malloc(read_00305_len);
      int read_00305_res = cgc_length_read(0, read_00305, read_00305_len);
      if (read_00305_res) {} //silence unused variable warning
      cgc_free(read_00305);
      if (read_00305_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x58\x0a";
      static unsigned int write_00063_00000_len = 2;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      unsigned char *read_00306;
      unsigned int read_00306_len;
      unsigned int read_00306_ptr = 0;
      //**** length read
      read_00306_len = 12;
      read_00306 = (unsigned char*)cgc_malloc(read_00306_len);
      int read_00306_res = cgc_length_read(0, read_00306, read_00306_len);
      if (read_00306_res) {} //silence unused variable warning
      cgc_free(read_00306);
      if (read_00306_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00307;
      unsigned int read_00307_len;
      unsigned int read_00307_ptr = 0;
      //**** length read
      read_00307_len = 14;
      read_00307 = (unsigned char*)cgc_malloc(read_00307_len);
      int read_00307_res = cgc_length_read(0, read_00307, read_00307_len);
      if (read_00307_res) {} //silence unused variable warning
      cgc_free(read_00307);
      if (read_00307_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00308;
      unsigned int read_00308_len;
      unsigned int read_00308_ptr = 0;
      //**** length read
      read_00308_len = 17;
      read_00308 = (unsigned char*)cgc_malloc(read_00308_len);
      int read_00308_res = cgc_length_read(0, read_00308, read_00308_len);
      if (read_00308_res) {} //silence unused variable warning
      cgc_free(read_00308);
      if (read_00308_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00309;
      unsigned int read_00309_len;
      unsigned int read_00309_ptr = 0;
      //**** length read
      read_00309_len = 28;
      read_00309 = (unsigned char*)cgc_malloc(read_00309_len);
      int read_00309_res = cgc_length_read(0, read_00309, read_00309_len);
      if (read_00309_res) {} //silence unused variable warning
      cgc_free(read_00309);
      if (read_00309_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00310;
      unsigned int read_00310_len;
      unsigned int read_00310_ptr = 0;
      //**** length read
      read_00310_len = 16;
      read_00310 = (unsigned char*)cgc_malloc(read_00310_len);
      int read_00310_res = cgc_length_read(0, read_00310, read_00310_len);
      if (read_00310_res) {} //silence unused variable warning
      cgc_free(read_00310);
      if (read_00310_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x58\x0a";
      static unsigned int write_00064_00000_len = 2;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      unsigned char *read_00311;
      unsigned int read_00311_len;
      unsigned int read_00311_ptr = 0;
      //**** length read
      read_00311_len = 12;
      read_00311 = (unsigned char*)cgc_malloc(read_00311_len);
      int read_00311_res = cgc_length_read(0, read_00311, read_00311_len);
      if (read_00311_res) {} //silence unused variable warning
      cgc_free(read_00311);
      if (read_00311_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00312;
      unsigned int read_00312_len;
      unsigned int read_00312_ptr = 0;
      //**** length read
      read_00312_len = 14;
      read_00312 = (unsigned char*)cgc_malloc(read_00312_len);
      int read_00312_res = cgc_length_read(0, read_00312, read_00312_len);
      if (read_00312_res) {} //silence unused variable warning
      cgc_free(read_00312);
      if (read_00312_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00313;
      unsigned int read_00313_len;
      unsigned int read_00313_ptr = 0;
      //**** length read
      read_00313_len = 17;
      read_00313 = (unsigned char*)cgc_malloc(read_00313_len);
      int read_00313_res = cgc_length_read(0, read_00313, read_00313_len);
      if (read_00313_res) {} //silence unused variable warning
      cgc_free(read_00313);
      if (read_00313_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00314;
      unsigned int read_00314_len;
      unsigned int read_00314_ptr = 0;
      //**** length read
      read_00314_len = 28;
      read_00314 = (unsigned char*)cgc_malloc(read_00314_len);
      int read_00314_res = cgc_length_read(0, read_00314, read_00314_len);
      if (read_00314_res) {} //silence unused variable warning
      cgc_free(read_00314);
      if (read_00314_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00315;
      unsigned int read_00315_len;
      unsigned int read_00315_ptr = 0;
      //**** length read
      read_00315_len = 16;
      read_00315 = (unsigned char*)cgc_malloc(read_00315_len);
      int read_00315_res = cgc_length_read(0, read_00315, read_00315_len);
      if (read_00315_res) {} //silence unused variable warning
      cgc_free(read_00315);
      if (read_00315_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x58\x0a";
      static unsigned int write_00065_00000_len = 2;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      unsigned char *read_00316;
      unsigned int read_00316_len;
      unsigned int read_00316_ptr = 0;
      //**** length read
      read_00316_len = 12;
      read_00316 = (unsigned char*)cgc_malloc(read_00316_len);
      int read_00316_res = cgc_length_read(0, read_00316, read_00316_len);
      if (read_00316_res) {} //silence unused variable warning
      cgc_free(read_00316);
      if (read_00316_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00317;
      unsigned int read_00317_len;
      unsigned int read_00317_ptr = 0;
      //**** length read
      read_00317_len = 14;
      read_00317 = (unsigned char*)cgc_malloc(read_00317_len);
      int read_00317_res = cgc_length_read(0, read_00317, read_00317_len);
      if (read_00317_res) {} //silence unused variable warning
      cgc_free(read_00317);
      if (read_00317_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00318;
      unsigned int read_00318_len;
      unsigned int read_00318_ptr = 0;
      //**** length read
      read_00318_len = 17;
      read_00318 = (unsigned char*)cgc_malloc(read_00318_len);
      int read_00318_res = cgc_length_read(0, read_00318, read_00318_len);
      if (read_00318_res) {} //silence unused variable warning
      cgc_free(read_00318);
      if (read_00318_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00319;
      unsigned int read_00319_len;
      unsigned int read_00319_ptr = 0;
      //**** length read
      read_00319_len = 28;
      read_00319 = (unsigned char*)cgc_malloc(read_00319_len);
      int read_00319_res = cgc_length_read(0, read_00319, read_00319_len);
      if (read_00319_res) {} //silence unused variable warning
      cgc_free(read_00319);
      if (read_00319_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00320;
      unsigned int read_00320_len;
      unsigned int read_00320_ptr = 0;
      //**** length read
      read_00320_len = 16;
      read_00320 = (unsigned char*)cgc_malloc(read_00320_len);
      int read_00320_res = cgc_length_read(0, read_00320, read_00320_len);
      if (read_00320_res) {} //silence unused variable warning
      cgc_free(read_00320);
      if (read_00320_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x58\x0a";
      static unsigned int write_00066_00000_len = 2;
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_buf(write_00066, &write_00066_len, write_00066_00000, write_00066_00000_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      unsigned char *read_00321;
      unsigned int read_00321_len;
      unsigned int read_00321_ptr = 0;
      //**** length read
      read_00321_len = 12;
      read_00321 = (unsigned char*)cgc_malloc(read_00321_len);
      int read_00321_res = cgc_length_read(0, read_00321, read_00321_len);
      if (read_00321_res) {} //silence unused variable warning
      cgc_free(read_00321);
      if (read_00321_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00322;
      unsigned int read_00322_len;
      unsigned int read_00322_ptr = 0;
      //**** length read
      read_00322_len = 14;
      read_00322 = (unsigned char*)cgc_malloc(read_00322_len);
      int read_00322_res = cgc_length_read(0, read_00322, read_00322_len);
      if (read_00322_res) {} //silence unused variable warning
      cgc_free(read_00322);
      if (read_00322_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00323;
      unsigned int read_00323_len;
      unsigned int read_00323_ptr = 0;
      //**** length read
      read_00323_len = 17;
      read_00323 = (unsigned char*)cgc_malloc(read_00323_len);
      int read_00323_res = cgc_length_read(0, read_00323, read_00323_len);
      if (read_00323_res) {} //silence unused variable warning
      cgc_free(read_00323);
      if (read_00323_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00324;
      unsigned int read_00324_len;
      unsigned int read_00324_ptr = 0;
      //**** length read
      read_00324_len = 28;
      read_00324 = (unsigned char*)cgc_malloc(read_00324_len);
      int read_00324_res = cgc_length_read(0, read_00324, read_00324_len);
      if (read_00324_res) {} //silence unused variable warning
      cgc_free(read_00324);
      if (read_00324_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00325;
      unsigned int read_00325_len;
      unsigned int read_00325_ptr = 0;
      //**** length read
      read_00325_len = 16;
      read_00325 = (unsigned char*)cgc_malloc(read_00325_len);
      int read_00325_res = cgc_length_read(0, read_00325, read_00325_len);
      if (read_00325_res) {} //silence unused variable warning
      cgc_free(read_00325);
      if (read_00325_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x58\x0a";
      static unsigned int write_00067_00000_len = 2;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      unsigned char *read_00326;
      unsigned int read_00326_len;
      unsigned int read_00326_ptr = 0;
      //**** length read
      read_00326_len = 12;
      read_00326 = (unsigned char*)cgc_malloc(read_00326_len);
      int read_00326_res = cgc_length_read(0, read_00326, read_00326_len);
      if (read_00326_res) {} //silence unused variable warning
      cgc_free(read_00326);
      if (read_00326_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00327;
      unsigned int read_00327_len;
      unsigned int read_00327_ptr = 0;
      //**** length read
      read_00327_len = 14;
      read_00327 = (unsigned char*)cgc_malloc(read_00327_len);
      int read_00327_res = cgc_length_read(0, read_00327, read_00327_len);
      if (read_00327_res) {} //silence unused variable warning
      cgc_free(read_00327);
      if (read_00327_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00328;
      unsigned int read_00328_len;
      unsigned int read_00328_ptr = 0;
      //**** length read
      read_00328_len = 17;
      read_00328 = (unsigned char*)cgc_malloc(read_00328_len);
      int read_00328_res = cgc_length_read(0, read_00328, read_00328_len);
      if (read_00328_res) {} //silence unused variable warning
      cgc_free(read_00328);
      if (read_00328_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00329;
      unsigned int read_00329_len;
      unsigned int read_00329_ptr = 0;
      //**** length read
      read_00329_len = 28;
      read_00329 = (unsigned char*)cgc_malloc(read_00329_len);
      int read_00329_res = cgc_length_read(0, read_00329, read_00329_len);
      if (read_00329_res) {} //silence unused variable warning
      cgc_free(read_00329);
      if (read_00329_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00330;
      unsigned int read_00330_len;
      unsigned int read_00330_ptr = 0;
      //**** length read
      read_00330_len = 16;
      read_00330 = (unsigned char*)cgc_malloc(read_00330_len);
      int read_00330_res = cgc_length_read(0, read_00330, read_00330_len);
      if (read_00330_res) {} //silence unused variable warning
      cgc_free(read_00330);
      if (read_00330_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x58\x0a";
      static unsigned int write_00068_00000_len = 2;
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = cgc_append_buf(write_00068, &write_00068_len, write_00068_00000, write_00068_00000_len);
      if (write_00068_len > 0) {
         cgc_transmit_all(1, write_00068, write_00068_len);
      }
      cgc_free(write_00068);
   } while (0);
   do {
      unsigned char *read_00331;
      unsigned int read_00331_len;
      unsigned int read_00331_ptr = 0;
      //**** length read
      read_00331_len = 12;
      read_00331 = (unsigned char*)cgc_malloc(read_00331_len);
      int read_00331_res = cgc_length_read(0, read_00331, read_00331_len);
      if (read_00331_res) {} //silence unused variable warning
      cgc_free(read_00331);
      if (read_00331_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00332;
      unsigned int read_00332_len;
      unsigned int read_00332_ptr = 0;
      //**** length read
      read_00332_len = 14;
      read_00332 = (unsigned char*)cgc_malloc(read_00332_len);
      int read_00332_res = cgc_length_read(0, read_00332, read_00332_len);
      if (read_00332_res) {} //silence unused variable warning
      cgc_free(read_00332);
      if (read_00332_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00333;
      unsigned int read_00333_len;
      unsigned int read_00333_ptr = 0;
      //**** length read
      read_00333_len = 17;
      read_00333 = (unsigned char*)cgc_malloc(read_00333_len);
      int read_00333_res = cgc_length_read(0, read_00333, read_00333_len);
      if (read_00333_res) {} //silence unused variable warning
      cgc_free(read_00333);
      if (read_00333_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00334;
      unsigned int read_00334_len;
      unsigned int read_00334_ptr = 0;
      //**** length read
      read_00334_len = 28;
      read_00334 = (unsigned char*)cgc_malloc(read_00334_len);
      int read_00334_res = cgc_length_read(0, read_00334, read_00334_len);
      if (read_00334_res) {} //silence unused variable warning
      cgc_free(read_00334);
      if (read_00334_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00335;
      unsigned int read_00335_len;
      unsigned int read_00335_ptr = 0;
      //**** length read
      read_00335_len = 16;
      read_00335 = (unsigned char*)cgc_malloc(read_00335_len);
      int read_00335_res = cgc_length_read(0, read_00335, read_00335_len);
      if (read_00335_res) {} //silence unused variable warning
      cgc_free(read_00335);
      if (read_00335_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x58\x0a";
      static unsigned int write_00069_00000_len = 2;
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = cgc_append_buf(write_00069, &write_00069_len, write_00069_00000, write_00069_00000_len);
      if (write_00069_len > 0) {
         cgc_transmit_all(1, write_00069, write_00069_len);
      }
      cgc_free(write_00069);
   } while (0);
   do {
      unsigned char *read_00336;
      unsigned int read_00336_len;
      unsigned int read_00336_ptr = 0;
      //**** length read
      read_00336_len = 12;
      read_00336 = (unsigned char*)cgc_malloc(read_00336_len);
      int read_00336_res = cgc_length_read(0, read_00336, read_00336_len);
      if (read_00336_res) {} //silence unused variable warning
      cgc_free(read_00336);
      if (read_00336_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00337;
      unsigned int read_00337_len;
      unsigned int read_00337_ptr = 0;
      //**** length read
      read_00337_len = 14;
      read_00337 = (unsigned char*)cgc_malloc(read_00337_len);
      int read_00337_res = cgc_length_read(0, read_00337, read_00337_len);
      if (read_00337_res) {} //silence unused variable warning
      cgc_free(read_00337);
      if (read_00337_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00338;
      unsigned int read_00338_len;
      unsigned int read_00338_ptr = 0;
      //**** length read
      read_00338_len = 17;
      read_00338 = (unsigned char*)cgc_malloc(read_00338_len);
      int read_00338_res = cgc_length_read(0, read_00338, read_00338_len);
      if (read_00338_res) {} //silence unused variable warning
      cgc_free(read_00338);
      if (read_00338_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00339;
      unsigned int read_00339_len;
      unsigned int read_00339_ptr = 0;
      //**** length read
      read_00339_len = 28;
      read_00339 = (unsigned char*)cgc_malloc(read_00339_len);
      int read_00339_res = cgc_length_read(0, read_00339, read_00339_len);
      if (read_00339_res) {} //silence unused variable warning
      cgc_free(read_00339);
      if (read_00339_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00340;
      unsigned int read_00340_len;
      unsigned int read_00340_ptr = 0;
      //**** length read
      read_00340_len = 16;
      read_00340 = (unsigned char*)cgc_malloc(read_00340_len);
      int read_00340_res = cgc_length_read(0, read_00340, read_00340_len);
      if (read_00340_res) {} //silence unused variable warning
      cgc_free(read_00340);
      if (read_00340_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x58\x0a";
      static unsigned int write_00070_00000_len = 2;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      unsigned char *read_00341;
      unsigned int read_00341_len;
      unsigned int read_00341_ptr = 0;
      //**** length read
      read_00341_len = 12;
      read_00341 = (unsigned char*)cgc_malloc(read_00341_len);
      int read_00341_res = cgc_length_read(0, read_00341, read_00341_len);
      if (read_00341_res) {} //silence unused variable warning
      cgc_free(read_00341);
      if (read_00341_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00342;
      unsigned int read_00342_len;
      unsigned int read_00342_ptr = 0;
      //**** length read
      read_00342_len = 14;
      read_00342 = (unsigned char*)cgc_malloc(read_00342_len);
      int read_00342_res = cgc_length_read(0, read_00342, read_00342_len);
      if (read_00342_res) {} //silence unused variable warning
      cgc_free(read_00342);
      if (read_00342_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00343;
      unsigned int read_00343_len;
      unsigned int read_00343_ptr = 0;
      //**** length read
      read_00343_len = 17;
      read_00343 = (unsigned char*)cgc_malloc(read_00343_len);
      int read_00343_res = cgc_length_read(0, read_00343, read_00343_len);
      if (read_00343_res) {} //silence unused variable warning
      cgc_free(read_00343);
      if (read_00343_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00344;
      unsigned int read_00344_len;
      unsigned int read_00344_ptr = 0;
      //**** length read
      read_00344_len = 28;
      read_00344 = (unsigned char*)cgc_malloc(read_00344_len);
      int read_00344_res = cgc_length_read(0, read_00344, read_00344_len);
      if (read_00344_res) {} //silence unused variable warning
      cgc_free(read_00344);
      if (read_00344_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00345;
      unsigned int read_00345_len;
      unsigned int read_00345_ptr = 0;
      //**** length read
      read_00345_len = 16;
      read_00345 = (unsigned char*)cgc_malloc(read_00345_len);
      int read_00345_res = cgc_length_read(0, read_00345, read_00345_len);
      if (read_00345_res) {} //silence unused variable warning
      cgc_free(read_00345);
      if (read_00345_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x58\x0a";
      static unsigned int write_00071_00000_len = 2;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      unsigned char *read_00346;
      unsigned int read_00346_len;
      unsigned int read_00346_ptr = 0;
      //**** length read
      read_00346_len = 12;
      read_00346 = (unsigned char*)cgc_malloc(read_00346_len);
      int read_00346_res = cgc_length_read(0, read_00346, read_00346_len);
      if (read_00346_res) {} //silence unused variable warning
      cgc_free(read_00346);
      if (read_00346_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00347;
      unsigned int read_00347_len;
      unsigned int read_00347_ptr = 0;
      //**** length read
      read_00347_len = 14;
      read_00347 = (unsigned char*)cgc_malloc(read_00347_len);
      int read_00347_res = cgc_length_read(0, read_00347, read_00347_len);
      if (read_00347_res) {} //silence unused variable warning
      cgc_free(read_00347);
      if (read_00347_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00348;
      unsigned int read_00348_len;
      unsigned int read_00348_ptr = 0;
      //**** length read
      read_00348_len = 17;
      read_00348 = (unsigned char*)cgc_malloc(read_00348_len);
      int read_00348_res = cgc_length_read(0, read_00348, read_00348_len);
      if (read_00348_res) {} //silence unused variable warning
      cgc_free(read_00348);
      if (read_00348_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00349;
      unsigned int read_00349_len;
      unsigned int read_00349_ptr = 0;
      //**** length read
      read_00349_len = 28;
      read_00349 = (unsigned char*)cgc_malloc(read_00349_len);
      int read_00349_res = cgc_length_read(0, read_00349, read_00349_len);
      if (read_00349_res) {} //silence unused variable warning
      cgc_free(read_00349);
      if (read_00349_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00350;
      unsigned int read_00350_len;
      unsigned int read_00350_ptr = 0;
      //**** length read
      read_00350_len = 16;
      read_00350 = (unsigned char*)cgc_malloc(read_00350_len);
      int read_00350_res = cgc_length_read(0, read_00350, read_00350_len);
      if (read_00350_res) {} //silence unused variable warning
      cgc_free(read_00350);
      if (read_00350_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x58\x0a";
      static unsigned int write_00072_00000_len = 2;
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_buf(write_00072, &write_00072_len, write_00072_00000, write_00072_00000_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      unsigned char *read_00351;
      unsigned int read_00351_len;
      unsigned int read_00351_ptr = 0;
      //**** length read
      read_00351_len = 12;
      read_00351 = (unsigned char*)cgc_malloc(read_00351_len);
      int read_00351_res = cgc_length_read(0, read_00351, read_00351_len);
      if (read_00351_res) {} //silence unused variable warning
      cgc_free(read_00351);
      if (read_00351_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00352;
      unsigned int read_00352_len;
      unsigned int read_00352_ptr = 0;
      //**** length read
      read_00352_len = 14;
      read_00352 = (unsigned char*)cgc_malloc(read_00352_len);
      int read_00352_res = cgc_length_read(0, read_00352, read_00352_len);
      if (read_00352_res) {} //silence unused variable warning
      cgc_free(read_00352);
      if (read_00352_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00353;
      unsigned int read_00353_len;
      unsigned int read_00353_ptr = 0;
      //**** length read
      read_00353_len = 17;
      read_00353 = (unsigned char*)cgc_malloc(read_00353_len);
      int read_00353_res = cgc_length_read(0, read_00353, read_00353_len);
      if (read_00353_res) {} //silence unused variable warning
      cgc_free(read_00353);
      if (read_00353_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00354;
      unsigned int read_00354_len;
      unsigned int read_00354_ptr = 0;
      //**** length read
      read_00354_len = 28;
      read_00354 = (unsigned char*)cgc_malloc(read_00354_len);
      int read_00354_res = cgc_length_read(0, read_00354, read_00354_len);
      if (read_00354_res) {} //silence unused variable warning
      cgc_free(read_00354);
      if (read_00354_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00355;
      unsigned int read_00355_len;
      unsigned int read_00355_ptr = 0;
      //**** length read
      read_00355_len = 16;
      read_00355 = (unsigned char*)cgc_malloc(read_00355_len);
      int read_00355_res = cgc_length_read(0, read_00355, read_00355_len);
      if (read_00355_res) {} //silence unused variable warning
      cgc_free(read_00355);
      if (read_00355_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x58\x0a";
      static unsigned int write_00073_00000_len = 2;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      unsigned char *read_00356;
      unsigned int read_00356_len;
      unsigned int read_00356_ptr = 0;
      //**** length read
      read_00356_len = 12;
      read_00356 = (unsigned char*)cgc_malloc(read_00356_len);
      int read_00356_res = cgc_length_read(0, read_00356, read_00356_len);
      if (read_00356_res) {} //silence unused variable warning
      cgc_free(read_00356);
      if (read_00356_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00357;
      unsigned int read_00357_len;
      unsigned int read_00357_ptr = 0;
      //**** length read
      read_00357_len = 14;
      read_00357 = (unsigned char*)cgc_malloc(read_00357_len);
      int read_00357_res = cgc_length_read(0, read_00357, read_00357_len);
      if (read_00357_res) {} //silence unused variable warning
      cgc_free(read_00357);
      if (read_00357_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00358;
      unsigned int read_00358_len;
      unsigned int read_00358_ptr = 0;
      //**** length read
      read_00358_len = 17;
      read_00358 = (unsigned char*)cgc_malloc(read_00358_len);
      int read_00358_res = cgc_length_read(0, read_00358, read_00358_len);
      if (read_00358_res) {} //silence unused variable warning
      cgc_free(read_00358);
      if (read_00358_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00359;
      unsigned int read_00359_len;
      unsigned int read_00359_ptr = 0;
      //**** length read
      read_00359_len = 28;
      read_00359 = (unsigned char*)cgc_malloc(read_00359_len);
      int read_00359_res = cgc_length_read(0, read_00359, read_00359_len);
      if (read_00359_res) {} //silence unused variable warning
      cgc_free(read_00359);
      if (read_00359_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00360;
      unsigned int read_00360_len;
      unsigned int read_00360_ptr = 0;
      //**** length read
      read_00360_len = 16;
      read_00360 = (unsigned char*)cgc_malloc(read_00360_len);
      int read_00360_res = cgc_length_read(0, read_00360, read_00360_len);
      if (read_00360_res) {} //silence unused variable warning
      cgc_free(read_00360);
      if (read_00360_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x58\x0a";
      static unsigned int write_00074_00000_len = 2;
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_buf(write_00074, &write_00074_len, write_00074_00000, write_00074_00000_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      unsigned char *read_00361;
      unsigned int read_00361_len;
      unsigned int read_00361_ptr = 0;
      //**** length read
      read_00361_len = 12;
      read_00361 = (unsigned char*)cgc_malloc(read_00361_len);
      int read_00361_res = cgc_length_read(0, read_00361, read_00361_len);
      if (read_00361_res) {} //silence unused variable warning
      cgc_free(read_00361);
      if (read_00361_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00362;
      unsigned int read_00362_len;
      unsigned int read_00362_ptr = 0;
      //**** length read
      read_00362_len = 14;
      read_00362 = (unsigned char*)cgc_malloc(read_00362_len);
      int read_00362_res = cgc_length_read(0, read_00362, read_00362_len);
      if (read_00362_res) {} //silence unused variable warning
      cgc_free(read_00362);
      if (read_00362_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00363;
      unsigned int read_00363_len;
      unsigned int read_00363_ptr = 0;
      //**** length read
      read_00363_len = 17;
      read_00363 = (unsigned char*)cgc_malloc(read_00363_len);
      int read_00363_res = cgc_length_read(0, read_00363, read_00363_len);
      if (read_00363_res) {} //silence unused variable warning
      cgc_free(read_00363);
      if (read_00363_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00364;
      unsigned int read_00364_len;
      unsigned int read_00364_ptr = 0;
      //**** length read
      read_00364_len = 28;
      read_00364 = (unsigned char*)cgc_malloc(read_00364_len);
      int read_00364_res = cgc_length_read(0, read_00364, read_00364_len);
      if (read_00364_res) {} //silence unused variable warning
      cgc_free(read_00364);
      if (read_00364_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00365;
      unsigned int read_00365_len;
      unsigned int read_00365_ptr = 0;
      //**** length read
      read_00365_len = 16;
      read_00365 = (unsigned char*)cgc_malloc(read_00365_len);
      int read_00365_res = cgc_length_read(0, read_00365, read_00365_len);
      if (read_00365_res) {} //silence unused variable warning
      cgc_free(read_00365);
      if (read_00365_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x58\x0a";
      static unsigned int write_00075_00000_len = 2;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      unsigned char *read_00366;
      unsigned int read_00366_len;
      unsigned int read_00366_ptr = 0;
      //**** length read
      read_00366_len = 12;
      read_00366 = (unsigned char*)cgc_malloc(read_00366_len);
      int read_00366_res = cgc_length_read(0, read_00366, read_00366_len);
      if (read_00366_res) {} //silence unused variable warning
      cgc_free(read_00366);
      if (read_00366_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00367;
      unsigned int read_00367_len;
      unsigned int read_00367_ptr = 0;
      //**** length read
      read_00367_len = 14;
      read_00367 = (unsigned char*)cgc_malloc(read_00367_len);
      int read_00367_res = cgc_length_read(0, read_00367, read_00367_len);
      if (read_00367_res) {} //silence unused variable warning
      cgc_free(read_00367);
      if (read_00367_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00368;
      unsigned int read_00368_len;
      unsigned int read_00368_ptr = 0;
      //**** length read
      read_00368_len = 17;
      read_00368 = (unsigned char*)cgc_malloc(read_00368_len);
      int read_00368_res = cgc_length_read(0, read_00368, read_00368_len);
      if (read_00368_res) {} //silence unused variable warning
      cgc_free(read_00368);
      if (read_00368_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00369;
      unsigned int read_00369_len;
      unsigned int read_00369_ptr = 0;
      //**** length read
      read_00369_len = 28;
      read_00369 = (unsigned char*)cgc_malloc(read_00369_len);
      int read_00369_res = cgc_length_read(0, read_00369, read_00369_len);
      if (read_00369_res) {} //silence unused variable warning
      cgc_free(read_00369);
      if (read_00369_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00370;
      unsigned int read_00370_len;
      unsigned int read_00370_ptr = 0;
      //**** length read
      read_00370_len = 16;
      read_00370 = (unsigned char*)cgc_malloc(read_00370_len);
      int read_00370_res = cgc_length_read(0, read_00370, read_00370_len);
      if (read_00370_res) {} //silence unused variable warning
      cgc_free(read_00370);
      if (read_00370_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x58\x0a";
      static unsigned int write_00076_00000_len = 2;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      unsigned char *read_00371;
      unsigned int read_00371_len;
      unsigned int read_00371_ptr = 0;
      //**** length read
      read_00371_len = 12;
      read_00371 = (unsigned char*)cgc_malloc(read_00371_len);
      int read_00371_res = cgc_length_read(0, read_00371, read_00371_len);
      if (read_00371_res) {} //silence unused variable warning
      cgc_free(read_00371);
      if (read_00371_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00372;
      unsigned int read_00372_len;
      unsigned int read_00372_ptr = 0;
      //**** length read
      read_00372_len = 14;
      read_00372 = (unsigned char*)cgc_malloc(read_00372_len);
      int read_00372_res = cgc_length_read(0, read_00372, read_00372_len);
      if (read_00372_res) {} //silence unused variable warning
      cgc_free(read_00372);
      if (read_00372_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00373;
      unsigned int read_00373_len;
      unsigned int read_00373_ptr = 0;
      //**** length read
      read_00373_len = 17;
      read_00373 = (unsigned char*)cgc_malloc(read_00373_len);
      int read_00373_res = cgc_length_read(0, read_00373, read_00373_len);
      if (read_00373_res) {} //silence unused variable warning
      cgc_free(read_00373);
      if (read_00373_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00374;
      unsigned int read_00374_len;
      unsigned int read_00374_ptr = 0;
      //**** length read
      read_00374_len = 28;
      read_00374 = (unsigned char*)cgc_malloc(read_00374_len);
      int read_00374_res = cgc_length_read(0, read_00374, read_00374_len);
      if (read_00374_res) {} //silence unused variable warning
      cgc_free(read_00374);
      if (read_00374_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00375;
      unsigned int read_00375_len;
      unsigned int read_00375_ptr = 0;
      //**** length read
      read_00375_len = 16;
      read_00375 = (unsigned char*)cgc_malloc(read_00375_len);
      int read_00375_res = cgc_length_read(0, read_00375, read_00375_len);
      if (read_00375_res) {} //silence unused variable warning
      cgc_free(read_00375);
      if (read_00375_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x58\x0a";
      static unsigned int write_00077_00000_len = 2;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      unsigned char *read_00376;
      unsigned int read_00376_len;
      unsigned int read_00376_ptr = 0;
      //**** length read
      read_00376_len = 12;
      read_00376 = (unsigned char*)cgc_malloc(read_00376_len);
      int read_00376_res = cgc_length_read(0, read_00376, read_00376_len);
      if (read_00376_res) {} //silence unused variable warning
      cgc_free(read_00376);
      if (read_00376_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00377;
      unsigned int read_00377_len;
      unsigned int read_00377_ptr = 0;
      //**** length read
      read_00377_len = 14;
      read_00377 = (unsigned char*)cgc_malloc(read_00377_len);
      int read_00377_res = cgc_length_read(0, read_00377, read_00377_len);
      if (read_00377_res) {} //silence unused variable warning
      cgc_free(read_00377);
      if (read_00377_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00378;
      unsigned int read_00378_len;
      unsigned int read_00378_ptr = 0;
      //**** length read
      read_00378_len = 17;
      read_00378 = (unsigned char*)cgc_malloc(read_00378_len);
      int read_00378_res = cgc_length_read(0, read_00378, read_00378_len);
      if (read_00378_res) {} //silence unused variable warning
      cgc_free(read_00378);
      if (read_00378_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00379;
      unsigned int read_00379_len;
      unsigned int read_00379_ptr = 0;
      //**** length read
      read_00379_len = 28;
      read_00379 = (unsigned char*)cgc_malloc(read_00379_len);
      int read_00379_res = cgc_length_read(0, read_00379, read_00379_len);
      if (read_00379_res) {} //silence unused variable warning
      cgc_free(read_00379);
      if (read_00379_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00380;
      unsigned int read_00380_len;
      unsigned int read_00380_ptr = 0;
      //**** length read
      read_00380_len = 16;
      read_00380 = (unsigned char*)cgc_malloc(read_00380_len);
      int read_00380_res = cgc_length_read(0, read_00380, read_00380_len);
      if (read_00380_res) {} //silence unused variable warning
      cgc_free(read_00380);
      if (read_00380_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x58\x0a";
      static unsigned int write_00078_00000_len = 2;
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_buf(write_00078, &write_00078_len, write_00078_00000, write_00078_00000_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      unsigned char *read_00381;
      unsigned int read_00381_len;
      unsigned int read_00381_ptr = 0;
      //**** length read
      read_00381_len = 12;
      read_00381 = (unsigned char*)cgc_malloc(read_00381_len);
      int read_00381_res = cgc_length_read(0, read_00381, read_00381_len);
      if (read_00381_res) {} //silence unused variable warning
      cgc_free(read_00381);
      if (read_00381_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00382;
      unsigned int read_00382_len;
      unsigned int read_00382_ptr = 0;
      //**** length read
      read_00382_len = 14;
      read_00382 = (unsigned char*)cgc_malloc(read_00382_len);
      int read_00382_res = cgc_length_read(0, read_00382, read_00382_len);
      if (read_00382_res) {} //silence unused variable warning
      cgc_free(read_00382);
      if (read_00382_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00383;
      unsigned int read_00383_len;
      unsigned int read_00383_ptr = 0;
      //**** length read
      read_00383_len = 17;
      read_00383 = (unsigned char*)cgc_malloc(read_00383_len);
      int read_00383_res = cgc_length_read(0, read_00383, read_00383_len);
      if (read_00383_res) {} //silence unused variable warning
      cgc_free(read_00383);
      if (read_00383_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00384;
      unsigned int read_00384_len;
      unsigned int read_00384_ptr = 0;
      //**** length read
      read_00384_len = 28;
      read_00384 = (unsigned char*)cgc_malloc(read_00384_len);
      int read_00384_res = cgc_length_read(0, read_00384, read_00384_len);
      if (read_00384_res) {} //silence unused variable warning
      cgc_free(read_00384);
      if (read_00384_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00385;
      unsigned int read_00385_len;
      unsigned int read_00385_ptr = 0;
      //**** length read
      read_00385_len = 16;
      read_00385 = (unsigned char*)cgc_malloc(read_00385_len);
      int read_00385_res = cgc_length_read(0, read_00385, read_00385_len);
      if (read_00385_res) {} //silence unused variable warning
      cgc_free(read_00385);
      if (read_00385_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x58\x0a";
      static unsigned int write_00079_00000_len = 2;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      unsigned char *read_00386;
      unsigned int read_00386_len;
      unsigned int read_00386_ptr = 0;
      //**** length read
      read_00386_len = 12;
      read_00386 = (unsigned char*)cgc_malloc(read_00386_len);
      int read_00386_res = cgc_length_read(0, read_00386, read_00386_len);
      if (read_00386_res) {} //silence unused variable warning
      cgc_free(read_00386);
      if (read_00386_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00387;
      unsigned int read_00387_len;
      unsigned int read_00387_ptr = 0;
      //**** length read
      read_00387_len = 14;
      read_00387 = (unsigned char*)cgc_malloc(read_00387_len);
      int read_00387_res = cgc_length_read(0, read_00387, read_00387_len);
      if (read_00387_res) {} //silence unused variable warning
      cgc_free(read_00387);
      if (read_00387_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00388;
      unsigned int read_00388_len;
      unsigned int read_00388_ptr = 0;
      //**** length read
      read_00388_len = 17;
      read_00388 = (unsigned char*)cgc_malloc(read_00388_len);
      int read_00388_res = cgc_length_read(0, read_00388, read_00388_len);
      if (read_00388_res) {} //silence unused variable warning
      cgc_free(read_00388);
      if (read_00388_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00389;
      unsigned int read_00389_len;
      unsigned int read_00389_ptr = 0;
      //**** length read
      read_00389_len = 28;
      read_00389 = (unsigned char*)cgc_malloc(read_00389_len);
      int read_00389_res = cgc_length_read(0, read_00389, read_00389_len);
      if (read_00389_res) {} //silence unused variable warning
      cgc_free(read_00389);
      if (read_00389_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00390;
      unsigned int read_00390_len;
      unsigned int read_00390_ptr = 0;
      //**** length read
      read_00390_len = 16;
      read_00390 = (unsigned char*)cgc_malloc(read_00390_len);
      int read_00390_res = cgc_length_read(0, read_00390, read_00390_len);
      if (read_00390_res) {} //silence unused variable warning
      cgc_free(read_00390);
      if (read_00390_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x58\x0a";
      static unsigned int write_00080_00000_len = 2;
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_buf(write_00080, &write_00080_len, write_00080_00000, write_00080_00000_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      unsigned char *read_00391;
      unsigned int read_00391_len;
      unsigned int read_00391_ptr = 0;
      //**** length read
      read_00391_len = 12;
      read_00391 = (unsigned char*)cgc_malloc(read_00391_len);
      int read_00391_res = cgc_length_read(0, read_00391, read_00391_len);
      if (read_00391_res) {} //silence unused variable warning
      cgc_free(read_00391);
      if (read_00391_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00392;
      unsigned int read_00392_len;
      unsigned int read_00392_ptr = 0;
      //**** length read
      read_00392_len = 14;
      read_00392 = (unsigned char*)cgc_malloc(read_00392_len);
      int read_00392_res = cgc_length_read(0, read_00392, read_00392_len);
      if (read_00392_res) {} //silence unused variable warning
      cgc_free(read_00392);
      if (read_00392_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00393;
      unsigned int read_00393_len;
      unsigned int read_00393_ptr = 0;
      //**** length read
      read_00393_len = 17;
      read_00393 = (unsigned char*)cgc_malloc(read_00393_len);
      int read_00393_res = cgc_length_read(0, read_00393, read_00393_len);
      if (read_00393_res) {} //silence unused variable warning
      cgc_free(read_00393);
      if (read_00393_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00394;
      unsigned int read_00394_len;
      unsigned int read_00394_ptr = 0;
      //**** length read
      read_00394_len = 28;
      read_00394 = (unsigned char*)cgc_malloc(read_00394_len);
      int read_00394_res = cgc_length_read(0, read_00394, read_00394_len);
      if (read_00394_res) {} //silence unused variable warning
      cgc_free(read_00394);
      if (read_00394_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00395;
      unsigned int read_00395_len;
      unsigned int read_00395_ptr = 0;
      //**** length read
      read_00395_len = 16;
      read_00395 = (unsigned char*)cgc_malloc(read_00395_len);
      int read_00395_res = cgc_length_read(0, read_00395, read_00395_len);
      if (read_00395_res) {} //silence unused variable warning
      cgc_free(read_00395);
      if (read_00395_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x58\x0a";
      static unsigned int write_00081_00000_len = 2;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      unsigned char *read_00396;
      unsigned int read_00396_len;
      unsigned int read_00396_ptr = 0;
      //**** length read
      read_00396_len = 12;
      read_00396 = (unsigned char*)cgc_malloc(read_00396_len);
      int read_00396_res = cgc_length_read(0, read_00396, read_00396_len);
      if (read_00396_res) {} //silence unused variable warning
      cgc_free(read_00396);
      if (read_00396_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00397;
      unsigned int read_00397_len;
      unsigned int read_00397_ptr = 0;
      //**** length read
      read_00397_len = 14;
      read_00397 = (unsigned char*)cgc_malloc(read_00397_len);
      int read_00397_res = cgc_length_read(0, read_00397, read_00397_len);
      if (read_00397_res) {} //silence unused variable warning
      cgc_free(read_00397);
      if (read_00397_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00398;
      unsigned int read_00398_len;
      unsigned int read_00398_ptr = 0;
      //**** length read
      read_00398_len = 17;
      read_00398 = (unsigned char*)cgc_malloc(read_00398_len);
      int read_00398_res = cgc_length_read(0, read_00398, read_00398_len);
      if (read_00398_res) {} //silence unused variable warning
      cgc_free(read_00398);
      if (read_00398_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00399;
      unsigned int read_00399_len;
      unsigned int read_00399_ptr = 0;
      //**** length read
      read_00399_len = 28;
      read_00399 = (unsigned char*)cgc_malloc(read_00399_len);
      int read_00399_res = cgc_length_read(0, read_00399, read_00399_len);
      if (read_00399_res) {} //silence unused variable warning
      cgc_free(read_00399);
      if (read_00399_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00400;
      unsigned int read_00400_len;
      unsigned int read_00400_ptr = 0;
      //**** length read
      read_00400_len = 16;
      read_00400 = (unsigned char*)cgc_malloc(read_00400_len);
      int read_00400_res = cgc_length_read(0, read_00400, read_00400_len);
      if (read_00400_res) {} //silence unused variable warning
      cgc_free(read_00400);
      if (read_00400_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x58\x0a";
      static unsigned int write_00082_00000_len = 2;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      unsigned char *read_00401;
      unsigned int read_00401_len;
      unsigned int read_00401_ptr = 0;
      //**** length read
      read_00401_len = 12;
      read_00401 = (unsigned char*)cgc_malloc(read_00401_len);
      int read_00401_res = cgc_length_read(0, read_00401, read_00401_len);
      if (read_00401_res) {} //silence unused variable warning
      cgc_free(read_00401);
      if (read_00401_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00402;
      unsigned int read_00402_len;
      unsigned int read_00402_ptr = 0;
      //**** length read
      read_00402_len = 14;
      read_00402 = (unsigned char*)cgc_malloc(read_00402_len);
      int read_00402_res = cgc_length_read(0, read_00402, read_00402_len);
      if (read_00402_res) {} //silence unused variable warning
      cgc_free(read_00402);
      if (read_00402_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00403;
      unsigned int read_00403_len;
      unsigned int read_00403_ptr = 0;
      //**** length read
      read_00403_len = 17;
      read_00403 = (unsigned char*)cgc_malloc(read_00403_len);
      int read_00403_res = cgc_length_read(0, read_00403, read_00403_len);
      if (read_00403_res) {} //silence unused variable warning
      cgc_free(read_00403);
      if (read_00403_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00404;
      unsigned int read_00404_len;
      unsigned int read_00404_ptr = 0;
      //**** length read
      read_00404_len = 28;
      read_00404 = (unsigned char*)cgc_malloc(read_00404_len);
      int read_00404_res = cgc_length_read(0, read_00404, read_00404_len);
      if (read_00404_res) {} //silence unused variable warning
      cgc_free(read_00404);
      if (read_00404_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00405;
      unsigned int read_00405_len;
      unsigned int read_00405_ptr = 0;
      //**** length read
      read_00405_len = 16;
      read_00405 = (unsigned char*)cgc_malloc(read_00405_len);
      int read_00405_res = cgc_length_read(0, read_00405, read_00405_len);
      if (read_00405_res) {} //silence unused variable warning
      cgc_free(read_00405);
      if (read_00405_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x58\x0a";
      static unsigned int write_00083_00000_len = 2;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      unsigned char *read_00406;
      unsigned int read_00406_len;
      unsigned int read_00406_ptr = 0;
      //**** length read
      read_00406_len = 12;
      read_00406 = (unsigned char*)cgc_malloc(read_00406_len);
      int read_00406_res = cgc_length_read(0, read_00406, read_00406_len);
      if (read_00406_res) {} //silence unused variable warning
      cgc_free(read_00406);
      if (read_00406_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00407;
      unsigned int read_00407_len;
      unsigned int read_00407_ptr = 0;
      //**** length read
      read_00407_len = 14;
      read_00407 = (unsigned char*)cgc_malloc(read_00407_len);
      int read_00407_res = cgc_length_read(0, read_00407, read_00407_len);
      if (read_00407_res) {} //silence unused variable warning
      cgc_free(read_00407);
      if (read_00407_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00408;
      unsigned int read_00408_len;
      unsigned int read_00408_ptr = 0;
      //**** length read
      read_00408_len = 17;
      read_00408 = (unsigned char*)cgc_malloc(read_00408_len);
      int read_00408_res = cgc_length_read(0, read_00408, read_00408_len);
      if (read_00408_res) {} //silence unused variable warning
      cgc_free(read_00408);
      if (read_00408_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00409;
      unsigned int read_00409_len;
      unsigned int read_00409_ptr = 0;
      //**** length read
      read_00409_len = 28;
      read_00409 = (unsigned char*)cgc_malloc(read_00409_len);
      int read_00409_res = cgc_length_read(0, read_00409, read_00409_len);
      if (read_00409_res) {} //silence unused variable warning
      cgc_free(read_00409);
      if (read_00409_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00410;
      unsigned int read_00410_len;
      unsigned int read_00410_ptr = 0;
      //**** length read
      read_00410_len = 16;
      read_00410 = (unsigned char*)cgc_malloc(read_00410_len);
      int read_00410_res = cgc_length_read(0, read_00410, read_00410_len);
      if (read_00410_res) {} //silence unused variable warning
      cgc_free(read_00410);
      if (read_00410_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x58\x0a";
      static unsigned int write_00084_00000_len = 2;
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_buf(write_00084, &write_00084_len, write_00084_00000, write_00084_00000_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      unsigned char *read_00411;
      unsigned int read_00411_len;
      unsigned int read_00411_ptr = 0;
      //**** length read
      read_00411_len = 12;
      read_00411 = (unsigned char*)cgc_malloc(read_00411_len);
      int read_00411_res = cgc_length_read(0, read_00411, read_00411_len);
      if (read_00411_res) {} //silence unused variable warning
      cgc_free(read_00411);
      if (read_00411_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00412;
      unsigned int read_00412_len;
      unsigned int read_00412_ptr = 0;
      //**** length read
      read_00412_len = 14;
      read_00412 = (unsigned char*)cgc_malloc(read_00412_len);
      int read_00412_res = cgc_length_read(0, read_00412, read_00412_len);
      if (read_00412_res) {} //silence unused variable warning
      cgc_free(read_00412);
      if (read_00412_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00413;
      unsigned int read_00413_len;
      unsigned int read_00413_ptr = 0;
      //**** length read
      read_00413_len = 17;
      read_00413 = (unsigned char*)cgc_malloc(read_00413_len);
      int read_00413_res = cgc_length_read(0, read_00413, read_00413_len);
      if (read_00413_res) {} //silence unused variable warning
      cgc_free(read_00413);
      if (read_00413_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00414;
      unsigned int read_00414_len;
      unsigned int read_00414_ptr = 0;
      //**** length read
      read_00414_len = 28;
      read_00414 = (unsigned char*)cgc_malloc(read_00414_len);
      int read_00414_res = cgc_length_read(0, read_00414, read_00414_len);
      if (read_00414_res) {} //silence unused variable warning
      cgc_free(read_00414);
      if (read_00414_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00415;
      unsigned int read_00415_len;
      unsigned int read_00415_ptr = 0;
      //**** length read
      read_00415_len = 16;
      read_00415 = (unsigned char*)cgc_malloc(read_00415_len);
      int read_00415_res = cgc_length_read(0, read_00415, read_00415_len);
      if (read_00415_res) {} //silence unused variable warning
      cgc_free(read_00415);
      if (read_00415_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x58\x0a";
      static unsigned int write_00085_00000_len = 2;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      unsigned char *read_00416;
      unsigned int read_00416_len;
      unsigned int read_00416_ptr = 0;
      //**** length read
      read_00416_len = 12;
      read_00416 = (unsigned char*)cgc_malloc(read_00416_len);
      int read_00416_res = cgc_length_read(0, read_00416, read_00416_len);
      if (read_00416_res) {} //silence unused variable warning
      cgc_free(read_00416);
      if (read_00416_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00417;
      unsigned int read_00417_len;
      unsigned int read_00417_ptr = 0;
      //**** length read
      read_00417_len = 14;
      read_00417 = (unsigned char*)cgc_malloc(read_00417_len);
      int read_00417_res = cgc_length_read(0, read_00417, read_00417_len);
      if (read_00417_res) {} //silence unused variable warning
      cgc_free(read_00417);
      if (read_00417_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00418;
      unsigned int read_00418_len;
      unsigned int read_00418_ptr = 0;
      //**** length read
      read_00418_len = 17;
      read_00418 = (unsigned char*)cgc_malloc(read_00418_len);
      int read_00418_res = cgc_length_read(0, read_00418, read_00418_len);
      if (read_00418_res) {} //silence unused variable warning
      cgc_free(read_00418);
      if (read_00418_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00419;
      unsigned int read_00419_len;
      unsigned int read_00419_ptr = 0;
      //**** length read
      read_00419_len = 28;
      read_00419 = (unsigned char*)cgc_malloc(read_00419_len);
      int read_00419_res = cgc_length_read(0, read_00419, read_00419_len);
      if (read_00419_res) {} //silence unused variable warning
      cgc_free(read_00419);
      if (read_00419_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00420;
      unsigned int read_00420_len;
      unsigned int read_00420_ptr = 0;
      //**** length read
      read_00420_len = 16;
      read_00420 = (unsigned char*)cgc_malloc(read_00420_len);
      int read_00420_res = cgc_length_read(0, read_00420, read_00420_len);
      if (read_00420_res) {} //silence unused variable warning
      cgc_free(read_00420);
      if (read_00420_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x58\x0a";
      static unsigned int write_00086_00000_len = 2;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
   } while (0);
   do {
      unsigned char *read_00421;
      unsigned int read_00421_len;
      unsigned int read_00421_ptr = 0;
      //**** length read
      read_00421_len = 12;
      read_00421 = (unsigned char*)cgc_malloc(read_00421_len);
      int read_00421_res = cgc_length_read(0, read_00421, read_00421_len);
      if (read_00421_res) {} //silence unused variable warning
      cgc_free(read_00421);
      if (read_00421_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00422;
      unsigned int read_00422_len;
      unsigned int read_00422_ptr = 0;
      //**** length read
      read_00422_len = 14;
      read_00422 = (unsigned char*)cgc_malloc(read_00422_len);
      int read_00422_res = cgc_length_read(0, read_00422, read_00422_len);
      if (read_00422_res) {} //silence unused variable warning
      cgc_free(read_00422);
      if (read_00422_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00423;
      unsigned int read_00423_len;
      unsigned int read_00423_ptr = 0;
      //**** length read
      read_00423_len = 17;
      read_00423 = (unsigned char*)cgc_malloc(read_00423_len);
      int read_00423_res = cgc_length_read(0, read_00423, read_00423_len);
      if (read_00423_res) {} //silence unused variable warning
      cgc_free(read_00423);
      if (read_00423_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00424;
      unsigned int read_00424_len;
      unsigned int read_00424_ptr = 0;
      //**** length read
      read_00424_len = 28;
      read_00424 = (unsigned char*)cgc_malloc(read_00424_len);
      int read_00424_res = cgc_length_read(0, read_00424, read_00424_len);
      if (read_00424_res) {} //silence unused variable warning
      cgc_free(read_00424);
      if (read_00424_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00425;
      unsigned int read_00425_len;
      unsigned int read_00425_ptr = 0;
      //**** length read
      read_00425_len = 16;
      read_00425 = (unsigned char*)cgc_malloc(read_00425_len);
      int read_00425_res = cgc_length_read(0, read_00425, read_00425_len);
      if (read_00425_res) {} //silence unused variable warning
      cgc_free(read_00425);
      if (read_00425_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x58\x0a";
      static unsigned int write_00087_00000_len = 2;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = cgc_append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         cgc_transmit_all(1, write_00087, write_00087_len);
      }
      cgc_free(write_00087);
   } while (0);
   do {
      unsigned char *read_00426;
      unsigned int read_00426_len;
      unsigned int read_00426_ptr = 0;
      //**** length read
      read_00426_len = 12;
      read_00426 = (unsigned char*)cgc_malloc(read_00426_len);
      int read_00426_res = cgc_length_read(0, read_00426, read_00426_len);
      if (read_00426_res) {} //silence unused variable warning
      cgc_free(read_00426);
      if (read_00426_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00427;
      unsigned int read_00427_len;
      unsigned int read_00427_ptr = 0;
      //**** length read
      read_00427_len = 14;
      read_00427 = (unsigned char*)cgc_malloc(read_00427_len);
      int read_00427_res = cgc_length_read(0, read_00427, read_00427_len);
      if (read_00427_res) {} //silence unused variable warning
      cgc_free(read_00427);
      if (read_00427_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00428;
      unsigned int read_00428_len;
      unsigned int read_00428_ptr = 0;
      //**** length read
      read_00428_len = 17;
      read_00428 = (unsigned char*)cgc_malloc(read_00428_len);
      int read_00428_res = cgc_length_read(0, read_00428, read_00428_len);
      if (read_00428_res) {} //silence unused variable warning
      cgc_free(read_00428);
      if (read_00428_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00429;
      unsigned int read_00429_len;
      unsigned int read_00429_ptr = 0;
      //**** length read
      read_00429_len = 28;
      read_00429 = (unsigned char*)cgc_malloc(read_00429_len);
      int read_00429_res = cgc_length_read(0, read_00429, read_00429_len);
      if (read_00429_res) {} //silence unused variable warning
      cgc_free(read_00429);
      if (read_00429_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00430;
      unsigned int read_00430_len;
      unsigned int read_00430_ptr = 0;
      //**** length read
      read_00430_len = 16;
      read_00430 = (unsigned char*)cgc_malloc(read_00430_len);
      int read_00430_res = cgc_length_read(0, read_00430, read_00430_len);
      if (read_00430_res) {} //silence unused variable warning
      cgc_free(read_00430);
      if (read_00430_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x58\x0a";
      static unsigned int write_00088_00000_len = 2;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      unsigned char *read_00431;
      unsigned int read_00431_len;
      unsigned int read_00431_ptr = 0;
      //**** length read
      read_00431_len = 12;
      read_00431 = (unsigned char*)cgc_malloc(read_00431_len);
      int read_00431_res = cgc_length_read(0, read_00431, read_00431_len);
      if (read_00431_res) {} //silence unused variable warning
      cgc_free(read_00431);
      if (read_00431_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00432;
      unsigned int read_00432_len;
      unsigned int read_00432_ptr = 0;
      //**** length read
      read_00432_len = 14;
      read_00432 = (unsigned char*)cgc_malloc(read_00432_len);
      int read_00432_res = cgc_length_read(0, read_00432, read_00432_len);
      if (read_00432_res) {} //silence unused variable warning
      cgc_free(read_00432);
      if (read_00432_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00433;
      unsigned int read_00433_len;
      unsigned int read_00433_ptr = 0;
      //**** length read
      read_00433_len = 17;
      read_00433 = (unsigned char*)cgc_malloc(read_00433_len);
      int read_00433_res = cgc_length_read(0, read_00433, read_00433_len);
      if (read_00433_res) {} //silence unused variable warning
      cgc_free(read_00433);
      if (read_00433_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00434;
      unsigned int read_00434_len;
      unsigned int read_00434_ptr = 0;
      //**** length read
      read_00434_len = 28;
      read_00434 = (unsigned char*)cgc_malloc(read_00434_len);
      int read_00434_res = cgc_length_read(0, read_00434, read_00434_len);
      if (read_00434_res) {} //silence unused variable warning
      cgc_free(read_00434);
      if (read_00434_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00435;
      unsigned int read_00435_len;
      unsigned int read_00435_ptr = 0;
      //**** length read
      read_00435_len = 16;
      read_00435 = (unsigned char*)cgc_malloc(read_00435_len);
      int read_00435_res = cgc_length_read(0, read_00435, read_00435_len);
      if (read_00435_res) {} //silence unused variable warning
      cgc_free(read_00435);
      if (read_00435_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x58\x0a";
      static unsigned int write_00089_00000_len = 2;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
   } while (0);
   do {
      unsigned char *read_00436;
      unsigned int read_00436_len;
      unsigned int read_00436_ptr = 0;
      //**** length read
      read_00436_len = 12;
      read_00436 = (unsigned char*)cgc_malloc(read_00436_len);
      int read_00436_res = cgc_length_read(0, read_00436, read_00436_len);
      if (read_00436_res) {} //silence unused variable warning
      cgc_free(read_00436);
      if (read_00436_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00437;
      unsigned int read_00437_len;
      unsigned int read_00437_ptr = 0;
      //**** length read
      read_00437_len = 14;
      read_00437 = (unsigned char*)cgc_malloc(read_00437_len);
      int read_00437_res = cgc_length_read(0, read_00437, read_00437_len);
      if (read_00437_res) {} //silence unused variable warning
      cgc_free(read_00437);
      if (read_00437_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00438;
      unsigned int read_00438_len;
      unsigned int read_00438_ptr = 0;
      //**** length read
      read_00438_len = 17;
      read_00438 = (unsigned char*)cgc_malloc(read_00438_len);
      int read_00438_res = cgc_length_read(0, read_00438, read_00438_len);
      if (read_00438_res) {} //silence unused variable warning
      cgc_free(read_00438);
      if (read_00438_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00439;
      unsigned int read_00439_len;
      unsigned int read_00439_ptr = 0;
      //**** length read
      read_00439_len = 28;
      read_00439 = (unsigned char*)cgc_malloc(read_00439_len);
      int read_00439_res = cgc_length_read(0, read_00439, read_00439_len);
      if (read_00439_res) {} //silence unused variable warning
      cgc_free(read_00439);
      if (read_00439_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00440;
      unsigned int read_00440_len;
      unsigned int read_00440_ptr = 0;
      //**** length read
      read_00440_len = 16;
      read_00440 = (unsigned char*)cgc_malloc(read_00440_len);
      int read_00440_res = cgc_length_read(0, read_00440, read_00440_len);
      if (read_00440_res) {} //silence unused variable warning
      cgc_free(read_00440);
      if (read_00440_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x58\x0a";
      static unsigned int write_00090_00000_len = 2;
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = cgc_append_buf(write_00090, &write_00090_len, write_00090_00000, write_00090_00000_len);
      if (write_00090_len > 0) {
         cgc_transmit_all(1, write_00090, write_00090_len);
      }
      cgc_free(write_00090);
   } while (0);
   do {
      unsigned char *read_00441;
      unsigned int read_00441_len;
      unsigned int read_00441_ptr = 0;
      //**** length read
      read_00441_len = 12;
      read_00441 = (unsigned char*)cgc_malloc(read_00441_len);
      int read_00441_res = cgc_length_read(0, read_00441, read_00441_len);
      if (read_00441_res) {} //silence unused variable warning
      cgc_free(read_00441);
      if (read_00441_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00442;
      unsigned int read_00442_len;
      unsigned int read_00442_ptr = 0;
      //**** length read
      read_00442_len = 14;
      read_00442 = (unsigned char*)cgc_malloc(read_00442_len);
      int read_00442_res = cgc_length_read(0, read_00442, read_00442_len);
      if (read_00442_res) {} //silence unused variable warning
      cgc_free(read_00442);
      if (read_00442_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00443;
      unsigned int read_00443_len;
      unsigned int read_00443_ptr = 0;
      //**** length read
      read_00443_len = 17;
      read_00443 = (unsigned char*)cgc_malloc(read_00443_len);
      int read_00443_res = cgc_length_read(0, read_00443, read_00443_len);
      if (read_00443_res) {} //silence unused variable warning
      cgc_free(read_00443);
      if (read_00443_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00444;
      unsigned int read_00444_len;
      unsigned int read_00444_ptr = 0;
      //**** length read
      read_00444_len = 28;
      read_00444 = (unsigned char*)cgc_malloc(read_00444_len);
      int read_00444_res = cgc_length_read(0, read_00444, read_00444_len);
      if (read_00444_res) {} //silence unused variable warning
      cgc_free(read_00444);
      if (read_00444_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00445;
      unsigned int read_00445_len;
      unsigned int read_00445_ptr = 0;
      //**** length read
      read_00445_len = 16;
      read_00445 = (unsigned char*)cgc_malloc(read_00445_len);
      int read_00445_res = cgc_length_read(0, read_00445, read_00445_len);
      if (read_00445_res) {} //silence unused variable warning
      cgc_free(read_00445);
      if (read_00445_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x58\x0a";
      static unsigned int write_00091_00000_len = 2;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      unsigned char *read_00446;
      unsigned int read_00446_len;
      unsigned int read_00446_ptr = 0;
      //**** length read
      read_00446_len = 12;
      read_00446 = (unsigned char*)cgc_malloc(read_00446_len);
      int read_00446_res = cgc_length_read(0, read_00446, read_00446_len);
      if (read_00446_res) {} //silence unused variable warning
      cgc_free(read_00446);
      if (read_00446_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00447;
      unsigned int read_00447_len;
      unsigned int read_00447_ptr = 0;
      //**** length read
      read_00447_len = 14;
      read_00447 = (unsigned char*)cgc_malloc(read_00447_len);
      int read_00447_res = cgc_length_read(0, read_00447, read_00447_len);
      if (read_00447_res) {} //silence unused variable warning
      cgc_free(read_00447);
      if (read_00447_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00448;
      unsigned int read_00448_len;
      unsigned int read_00448_ptr = 0;
      //**** length read
      read_00448_len = 17;
      read_00448 = (unsigned char*)cgc_malloc(read_00448_len);
      int read_00448_res = cgc_length_read(0, read_00448, read_00448_len);
      if (read_00448_res) {} //silence unused variable warning
      cgc_free(read_00448);
      if (read_00448_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00449;
      unsigned int read_00449_len;
      unsigned int read_00449_ptr = 0;
      //**** length read
      read_00449_len = 28;
      read_00449 = (unsigned char*)cgc_malloc(read_00449_len);
      int read_00449_res = cgc_length_read(0, read_00449, read_00449_len);
      if (read_00449_res) {} //silence unused variable warning
      cgc_free(read_00449);
      if (read_00449_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00450;
      unsigned int read_00450_len;
      unsigned int read_00450_ptr = 0;
      //**** length read
      read_00450_len = 16;
      read_00450 = (unsigned char*)cgc_malloc(read_00450_len);
      int read_00450_res = cgc_length_read(0, read_00450, read_00450_len);
      if (read_00450_res) {} //silence unused variable warning
      cgc_free(read_00450);
      if (read_00450_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x58\x0a";
      static unsigned int write_00092_00000_len = 2;
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = cgc_append_buf(write_00092, &write_00092_len, write_00092_00000, write_00092_00000_len);
      if (write_00092_len > 0) {
         cgc_transmit_all(1, write_00092, write_00092_len);
      }
      cgc_free(write_00092);
   } while (0);
   do {
      unsigned char *read_00451;
      unsigned int read_00451_len;
      unsigned int read_00451_ptr = 0;
      //**** length read
      read_00451_len = 12;
      read_00451 = (unsigned char*)cgc_malloc(read_00451_len);
      int read_00451_res = cgc_length_read(0, read_00451, read_00451_len);
      if (read_00451_res) {} //silence unused variable warning
      cgc_free(read_00451);
      if (read_00451_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00452;
      unsigned int read_00452_len;
      unsigned int read_00452_ptr = 0;
      //**** length read
      read_00452_len = 14;
      read_00452 = (unsigned char*)cgc_malloc(read_00452_len);
      int read_00452_res = cgc_length_read(0, read_00452, read_00452_len);
      if (read_00452_res) {} //silence unused variable warning
      cgc_free(read_00452);
      if (read_00452_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00453;
      unsigned int read_00453_len;
      unsigned int read_00453_ptr = 0;
      //**** length read
      read_00453_len = 17;
      read_00453 = (unsigned char*)cgc_malloc(read_00453_len);
      int read_00453_res = cgc_length_read(0, read_00453, read_00453_len);
      if (read_00453_res) {} //silence unused variable warning
      cgc_free(read_00453);
      if (read_00453_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00454;
      unsigned int read_00454_len;
      unsigned int read_00454_ptr = 0;
      //**** length read
      read_00454_len = 28;
      read_00454 = (unsigned char*)cgc_malloc(read_00454_len);
      int read_00454_res = cgc_length_read(0, read_00454, read_00454_len);
      if (read_00454_res) {} //silence unused variable warning
      cgc_free(read_00454);
      if (read_00454_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00455;
      unsigned int read_00455_len;
      unsigned int read_00455_ptr = 0;
      //**** length read
      read_00455_len = 16;
      read_00455 = (unsigned char*)cgc_malloc(read_00455_len);
      int read_00455_res = cgc_length_read(0, read_00455, read_00455_len);
      if (read_00455_res) {} //silence unused variable warning
      cgc_free(read_00455);
      if (read_00455_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x58\x0a";
      static unsigned int write_00093_00000_len = 2;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = cgc_append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         cgc_transmit_all(1, write_00093, write_00093_len);
      }
      cgc_free(write_00093);
   } while (0);
   do {
      unsigned char *read_00456;
      unsigned int read_00456_len;
      unsigned int read_00456_ptr = 0;
      //**** length read
      read_00456_len = 12;
      read_00456 = (unsigned char*)cgc_malloc(read_00456_len);
      int read_00456_res = cgc_length_read(0, read_00456, read_00456_len);
      if (read_00456_res) {} //silence unused variable warning
      cgc_free(read_00456);
      if (read_00456_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00457;
      unsigned int read_00457_len;
      unsigned int read_00457_ptr = 0;
      //**** length read
      read_00457_len = 14;
      read_00457 = (unsigned char*)cgc_malloc(read_00457_len);
      int read_00457_res = cgc_length_read(0, read_00457, read_00457_len);
      if (read_00457_res) {} //silence unused variable warning
      cgc_free(read_00457);
      if (read_00457_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00458;
      unsigned int read_00458_len;
      unsigned int read_00458_ptr = 0;
      //**** length read
      read_00458_len = 17;
      read_00458 = (unsigned char*)cgc_malloc(read_00458_len);
      int read_00458_res = cgc_length_read(0, read_00458, read_00458_len);
      if (read_00458_res) {} //silence unused variable warning
      cgc_free(read_00458);
      if (read_00458_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00459;
      unsigned int read_00459_len;
      unsigned int read_00459_ptr = 0;
      //**** length read
      read_00459_len = 28;
      read_00459 = (unsigned char*)cgc_malloc(read_00459_len);
      int read_00459_res = cgc_length_read(0, read_00459, read_00459_len);
      if (read_00459_res) {} //silence unused variable warning
      cgc_free(read_00459);
      if (read_00459_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00460;
      unsigned int read_00460_len;
      unsigned int read_00460_ptr = 0;
      //**** length read
      read_00460_len = 16;
      read_00460 = (unsigned char*)cgc_malloc(read_00460_len);
      int read_00460_res = cgc_length_read(0, read_00460, read_00460_len);
      if (read_00460_res) {} //silence unused variable warning
      cgc_free(read_00460);
      if (read_00460_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x58\x0a";
      static unsigned int write_00094_00000_len = 2;
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = cgc_append_buf(write_00094, &write_00094_len, write_00094_00000, write_00094_00000_len);
      if (write_00094_len > 0) {
         cgc_transmit_all(1, write_00094, write_00094_len);
      }
      cgc_free(write_00094);
   } while (0);
   do {
      unsigned char *read_00461;
      unsigned int read_00461_len;
      unsigned int read_00461_ptr = 0;
      //**** length read
      read_00461_len = 12;
      read_00461 = (unsigned char*)cgc_malloc(read_00461_len);
      int read_00461_res = cgc_length_read(0, read_00461, read_00461_len);
      if (read_00461_res) {} //silence unused variable warning
      cgc_free(read_00461);
      if (read_00461_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00462;
      unsigned int read_00462_len;
      unsigned int read_00462_ptr = 0;
      //**** length read
      read_00462_len = 14;
      read_00462 = (unsigned char*)cgc_malloc(read_00462_len);
      int read_00462_res = cgc_length_read(0, read_00462, read_00462_len);
      if (read_00462_res) {} //silence unused variable warning
      cgc_free(read_00462);
      if (read_00462_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00463;
      unsigned int read_00463_len;
      unsigned int read_00463_ptr = 0;
      //**** length read
      read_00463_len = 17;
      read_00463 = (unsigned char*)cgc_malloc(read_00463_len);
      int read_00463_res = cgc_length_read(0, read_00463, read_00463_len);
      if (read_00463_res) {} //silence unused variable warning
      cgc_free(read_00463);
      if (read_00463_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00464;
      unsigned int read_00464_len;
      unsigned int read_00464_ptr = 0;
      //**** length read
      read_00464_len = 28;
      read_00464 = (unsigned char*)cgc_malloc(read_00464_len);
      int read_00464_res = cgc_length_read(0, read_00464, read_00464_len);
      if (read_00464_res) {} //silence unused variable warning
      cgc_free(read_00464);
      if (read_00464_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00465;
      unsigned int read_00465_len;
      unsigned int read_00465_ptr = 0;
      //**** length read
      read_00465_len = 16;
      read_00465 = (unsigned char*)cgc_malloc(read_00465_len);
      int read_00465_res = cgc_length_read(0, read_00465, read_00465_len);
      if (read_00465_res) {} //silence unused variable warning
      cgc_free(read_00465);
      if (read_00465_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x58\x0a";
      static unsigned int write_00095_00000_len = 2;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = cgc_append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         cgc_transmit_all(1, write_00095, write_00095_len);
      }
      cgc_free(write_00095);
   } while (0);
   do {
      unsigned char *read_00466;
      unsigned int read_00466_len;
      unsigned int read_00466_ptr = 0;
      //**** length read
      read_00466_len = 12;
      read_00466 = (unsigned char*)cgc_malloc(read_00466_len);
      int read_00466_res = cgc_length_read(0, read_00466, read_00466_len);
      if (read_00466_res) {} //silence unused variable warning
      cgc_free(read_00466);
      if (read_00466_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00467;
      unsigned int read_00467_len;
      unsigned int read_00467_ptr = 0;
      //**** length read
      read_00467_len = 14;
      read_00467 = (unsigned char*)cgc_malloc(read_00467_len);
      int read_00467_res = cgc_length_read(0, read_00467, read_00467_len);
      if (read_00467_res) {} //silence unused variable warning
      cgc_free(read_00467);
      if (read_00467_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00468;
      unsigned int read_00468_len;
      unsigned int read_00468_ptr = 0;
      //**** length read
      read_00468_len = 17;
      read_00468 = (unsigned char*)cgc_malloc(read_00468_len);
      int read_00468_res = cgc_length_read(0, read_00468, read_00468_len);
      if (read_00468_res) {} //silence unused variable warning
      cgc_free(read_00468);
      if (read_00468_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00469;
      unsigned int read_00469_len;
      unsigned int read_00469_ptr = 0;
      //**** length read
      read_00469_len = 28;
      read_00469 = (unsigned char*)cgc_malloc(read_00469_len);
      int read_00469_res = cgc_length_read(0, read_00469, read_00469_len);
      if (read_00469_res) {} //silence unused variable warning
      cgc_free(read_00469);
      if (read_00469_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00470;
      unsigned int read_00470_len;
      unsigned int read_00470_ptr = 0;
      //**** length read
      read_00470_len = 16;
      read_00470 = (unsigned char*)cgc_malloc(read_00470_len);
      int read_00470_res = cgc_length_read(0, read_00470, read_00470_len);
      if (read_00470_res) {} //silence unused variable warning
      cgc_free(read_00470);
      if (read_00470_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x58\x0a";
      static unsigned int write_00096_00000_len = 2;
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = cgc_append_buf(write_00096, &write_00096_len, write_00096_00000, write_00096_00000_len);
      if (write_00096_len > 0) {
         cgc_transmit_all(1, write_00096, write_00096_len);
      }
      cgc_free(write_00096);
   } while (0);
   do {
      unsigned char *read_00471;
      unsigned int read_00471_len;
      unsigned int read_00471_ptr = 0;
      //**** length read
      read_00471_len = 12;
      read_00471 = (unsigned char*)cgc_malloc(read_00471_len);
      int read_00471_res = cgc_length_read(0, read_00471, read_00471_len);
      if (read_00471_res) {} //silence unused variable warning
      cgc_free(read_00471);
      if (read_00471_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00472;
      unsigned int read_00472_len;
      unsigned int read_00472_ptr = 0;
      //**** length read
      read_00472_len = 14;
      read_00472 = (unsigned char*)cgc_malloc(read_00472_len);
      int read_00472_res = cgc_length_read(0, read_00472, read_00472_len);
      if (read_00472_res) {} //silence unused variable warning
      cgc_free(read_00472);
      if (read_00472_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00473;
      unsigned int read_00473_len;
      unsigned int read_00473_ptr = 0;
      //**** length read
      read_00473_len = 17;
      read_00473 = (unsigned char*)cgc_malloc(read_00473_len);
      int read_00473_res = cgc_length_read(0, read_00473, read_00473_len);
      if (read_00473_res) {} //silence unused variable warning
      cgc_free(read_00473);
      if (read_00473_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00474;
      unsigned int read_00474_len;
      unsigned int read_00474_ptr = 0;
      //**** length read
      read_00474_len = 28;
      read_00474 = (unsigned char*)cgc_malloc(read_00474_len);
      int read_00474_res = cgc_length_read(0, read_00474, read_00474_len);
      if (read_00474_res) {} //silence unused variable warning
      cgc_free(read_00474);
      if (read_00474_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00475;
      unsigned int read_00475_len;
      unsigned int read_00475_ptr = 0;
      //**** length read
      read_00475_len = 16;
      read_00475 = (unsigned char*)cgc_malloc(read_00475_len);
      int read_00475_res = cgc_length_read(0, read_00475, read_00475_len);
      if (read_00475_res) {} //silence unused variable warning
      cgc_free(read_00475);
      if (read_00475_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x58\x0a";
      static unsigned int write_00097_00000_len = 2;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      unsigned char *read_00476;
      unsigned int read_00476_len;
      unsigned int read_00476_ptr = 0;
      //**** length read
      read_00476_len = 12;
      read_00476 = (unsigned char*)cgc_malloc(read_00476_len);
      int read_00476_res = cgc_length_read(0, read_00476, read_00476_len);
      if (read_00476_res) {} //silence unused variable warning
      cgc_free(read_00476);
      if (read_00476_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00477;
      unsigned int read_00477_len;
      unsigned int read_00477_ptr = 0;
      //**** length read
      read_00477_len = 14;
      read_00477 = (unsigned char*)cgc_malloc(read_00477_len);
      int read_00477_res = cgc_length_read(0, read_00477, read_00477_len);
      if (read_00477_res) {} //silence unused variable warning
      cgc_free(read_00477);
      if (read_00477_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00478;
      unsigned int read_00478_len;
      unsigned int read_00478_ptr = 0;
      //**** length read
      read_00478_len = 17;
      read_00478 = (unsigned char*)cgc_malloc(read_00478_len);
      int read_00478_res = cgc_length_read(0, read_00478, read_00478_len);
      if (read_00478_res) {} //silence unused variable warning
      cgc_free(read_00478);
      if (read_00478_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00479;
      unsigned int read_00479_len;
      unsigned int read_00479_ptr = 0;
      //**** length read
      read_00479_len = 28;
      read_00479 = (unsigned char*)cgc_malloc(read_00479_len);
      int read_00479_res = cgc_length_read(0, read_00479, read_00479_len);
      if (read_00479_res) {} //silence unused variable warning
      cgc_free(read_00479);
      if (read_00479_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00480;
      unsigned int read_00480_len;
      unsigned int read_00480_ptr = 0;
      //**** length read
      read_00480_len = 16;
      read_00480 = (unsigned char*)cgc_malloc(read_00480_len);
      int read_00480_res = cgc_length_read(0, read_00480, read_00480_len);
      if (read_00480_res) {} //silence unused variable warning
      cgc_free(read_00480);
      if (read_00480_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x58\x0a";
      static unsigned int write_00098_00000_len = 2;
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = cgc_append_buf(write_00098, &write_00098_len, write_00098_00000, write_00098_00000_len);
      if (write_00098_len > 0) {
         cgc_transmit_all(1, write_00098, write_00098_len);
      }
      cgc_free(write_00098);
   } while (0);
   do {
      unsigned char *read_00481;
      unsigned int read_00481_len;
      unsigned int read_00481_ptr = 0;
      //**** length read
      read_00481_len = 12;
      read_00481 = (unsigned char*)cgc_malloc(read_00481_len);
      int read_00481_res = cgc_length_read(0, read_00481, read_00481_len);
      if (read_00481_res) {} //silence unused variable warning
      cgc_free(read_00481);
      if (read_00481_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00482;
      unsigned int read_00482_len;
      unsigned int read_00482_ptr = 0;
      //**** length read
      read_00482_len = 14;
      read_00482 = (unsigned char*)cgc_malloc(read_00482_len);
      int read_00482_res = cgc_length_read(0, read_00482, read_00482_len);
      if (read_00482_res) {} //silence unused variable warning
      cgc_free(read_00482);
      if (read_00482_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00483;
      unsigned int read_00483_len;
      unsigned int read_00483_ptr = 0;
      //**** length read
      read_00483_len = 17;
      read_00483 = (unsigned char*)cgc_malloc(read_00483_len);
      int read_00483_res = cgc_length_read(0, read_00483, read_00483_len);
      if (read_00483_res) {} //silence unused variable warning
      cgc_free(read_00483);
      if (read_00483_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00484;
      unsigned int read_00484_len;
      unsigned int read_00484_ptr = 0;
      //**** length read
      read_00484_len = 28;
      read_00484 = (unsigned char*)cgc_malloc(read_00484_len);
      int read_00484_res = cgc_length_read(0, read_00484, read_00484_len);
      if (read_00484_res) {} //silence unused variable warning
      cgc_free(read_00484);
      if (read_00484_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00485;
      unsigned int read_00485_len;
      unsigned int read_00485_ptr = 0;
      //**** length read
      read_00485_len = 16;
      read_00485 = (unsigned char*)cgc_malloc(read_00485_len);
      int read_00485_res = cgc_length_read(0, read_00485, read_00485_len);
      if (read_00485_res) {} //silence unused variable warning
      cgc_free(read_00485);
      if (read_00485_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x58\x0a";
      static unsigned int write_00099_00000_len = 2;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = cgc_append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         cgc_transmit_all(1, write_00099, write_00099_len);
      }
      cgc_free(write_00099);
   } while (0);
   do {
      unsigned char *read_00486;
      unsigned int read_00486_len;
      unsigned int read_00486_ptr = 0;
      //**** length read
      read_00486_len = 12;
      read_00486 = (unsigned char*)cgc_malloc(read_00486_len);
      int read_00486_res = cgc_length_read(0, read_00486, read_00486_len);
      if (read_00486_res) {} //silence unused variable warning
      cgc_free(read_00486);
      if (read_00486_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00487;
      unsigned int read_00487_len;
      unsigned int read_00487_ptr = 0;
      //**** length read
      read_00487_len = 14;
      read_00487 = (unsigned char*)cgc_malloc(read_00487_len);
      int read_00487_res = cgc_length_read(0, read_00487, read_00487_len);
      if (read_00487_res) {} //silence unused variable warning
      cgc_free(read_00487);
      if (read_00487_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00488;
      unsigned int read_00488_len;
      unsigned int read_00488_ptr = 0;
      //**** length read
      read_00488_len = 17;
      read_00488 = (unsigned char*)cgc_malloc(read_00488_len);
      int read_00488_res = cgc_length_read(0, read_00488, read_00488_len);
      if (read_00488_res) {} //silence unused variable warning
      cgc_free(read_00488);
      if (read_00488_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00489;
      unsigned int read_00489_len;
      unsigned int read_00489_ptr = 0;
      //**** length read
      read_00489_len = 28;
      read_00489 = (unsigned char*)cgc_malloc(read_00489_len);
      int read_00489_res = cgc_length_read(0, read_00489, read_00489_len);
      if (read_00489_res) {} //silence unused variable warning
      cgc_free(read_00489);
      if (read_00489_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00490;
      unsigned int read_00490_len;
      unsigned int read_00490_ptr = 0;
      //**** length read
      read_00490_len = 16;
      read_00490 = (unsigned char*)cgc_malloc(read_00490_len);
      int read_00490_res = cgc_length_read(0, read_00490, read_00490_len);
      if (read_00490_res) {} //silence unused variable warning
      cgc_free(read_00490);
      if (read_00490_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x58\x0a";
      static unsigned int write_00100_00000_len = 2;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      unsigned char *read_00491;
      unsigned int read_00491_len;
      unsigned int read_00491_ptr = 0;
      //**** length read
      read_00491_len = 12;
      read_00491 = (unsigned char*)cgc_malloc(read_00491_len);
      int read_00491_res = cgc_length_read(0, read_00491, read_00491_len);
      if (read_00491_res) {} //silence unused variable warning
      cgc_free(read_00491);
      if (read_00491_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00492;
      unsigned int read_00492_len;
      unsigned int read_00492_ptr = 0;
      //**** length read
      read_00492_len = 14;
      read_00492 = (unsigned char*)cgc_malloc(read_00492_len);
      int read_00492_res = cgc_length_read(0, read_00492, read_00492_len);
      if (read_00492_res) {} //silence unused variable warning
      cgc_free(read_00492);
      if (read_00492_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00493;
      unsigned int read_00493_len;
      unsigned int read_00493_ptr = 0;
      //**** length read
      read_00493_len = 17;
      read_00493 = (unsigned char*)cgc_malloc(read_00493_len);
      int read_00493_res = cgc_length_read(0, read_00493, read_00493_len);
      if (read_00493_res) {} //silence unused variable warning
      cgc_free(read_00493);
      if (read_00493_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00494;
      unsigned int read_00494_len;
      unsigned int read_00494_ptr = 0;
      //**** length read
      read_00494_len = 28;
      read_00494 = (unsigned char*)cgc_malloc(read_00494_len);
      int read_00494_res = cgc_length_read(0, read_00494, read_00494_len);
      if (read_00494_res) {} //silence unused variable warning
      cgc_free(read_00494);
      if (read_00494_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00495;
      unsigned int read_00495_len;
      unsigned int read_00495_ptr = 0;
      //**** length read
      read_00495_len = 16;
      read_00495 = (unsigned char*)cgc_malloc(read_00495_len);
      int read_00495_res = cgc_length_read(0, read_00495, read_00495_len);
      if (read_00495_res) {} //silence unused variable warning
      cgc_free(read_00495);
      if (read_00495_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x58\x0a";
      static unsigned int write_00101_00000_len = 2;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = cgc_append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         cgc_transmit_all(1, write_00101, write_00101_len);
      }
      cgc_free(write_00101);
   } while (0);
   do {
      unsigned char *read_00496;
      unsigned int read_00496_len;
      unsigned int read_00496_ptr = 0;
      //**** length read
      read_00496_len = 12;
      read_00496 = (unsigned char*)cgc_malloc(read_00496_len);
      int read_00496_res = cgc_length_read(0, read_00496, read_00496_len);
      if (read_00496_res) {} //silence unused variable warning
      cgc_free(read_00496);
      if (read_00496_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00497;
      unsigned int read_00497_len;
      unsigned int read_00497_ptr = 0;
      //**** length read
      read_00497_len = 14;
      read_00497 = (unsigned char*)cgc_malloc(read_00497_len);
      int read_00497_res = cgc_length_read(0, read_00497, read_00497_len);
      if (read_00497_res) {} //silence unused variable warning
      cgc_free(read_00497);
      if (read_00497_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00498;
      unsigned int read_00498_len;
      unsigned int read_00498_ptr = 0;
      //**** length read
      read_00498_len = 17;
      read_00498 = (unsigned char*)cgc_malloc(read_00498_len);
      int read_00498_res = cgc_length_read(0, read_00498, read_00498_len);
      if (read_00498_res) {} //silence unused variable warning
      cgc_free(read_00498);
      if (read_00498_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00499;
      unsigned int read_00499_len;
      unsigned int read_00499_ptr = 0;
      //**** length read
      read_00499_len = 28;
      read_00499 = (unsigned char*)cgc_malloc(read_00499_len);
      int read_00499_res = cgc_length_read(0, read_00499, read_00499_len);
      if (read_00499_res) {} //silence unused variable warning
      cgc_free(read_00499);
      if (read_00499_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00500;
      unsigned int read_00500_len;
      unsigned int read_00500_ptr = 0;
      //**** length read
      read_00500_len = 16;
      read_00500 = (unsigned char*)cgc_malloc(read_00500_len);
      int read_00500_res = cgc_length_read(0, read_00500, read_00500_len);
      if (read_00500_res) {} //silence unused variable warning
      cgc_free(read_00500);
      if (read_00500_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x58\x0a";
      static unsigned int write_00102_00000_len = 2;
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = cgc_append_buf(write_00102, &write_00102_len, write_00102_00000, write_00102_00000_len);
      if (write_00102_len > 0) {
         cgc_transmit_all(1, write_00102, write_00102_len);
      }
      cgc_free(write_00102);
   } while (0);
   do {
      unsigned char *read_00501;
      unsigned int read_00501_len;
      unsigned int read_00501_ptr = 0;
      //**** length read
      read_00501_len = 12;
      read_00501 = (unsigned char*)cgc_malloc(read_00501_len);
      int read_00501_res = cgc_length_read(0, read_00501, read_00501_len);
      if (read_00501_res) {} //silence unused variable warning
      cgc_free(read_00501);
      if (read_00501_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00502;
      unsigned int read_00502_len;
      unsigned int read_00502_ptr = 0;
      //**** length read
      read_00502_len = 14;
      read_00502 = (unsigned char*)cgc_malloc(read_00502_len);
      int read_00502_res = cgc_length_read(0, read_00502, read_00502_len);
      if (read_00502_res) {} //silence unused variable warning
      cgc_free(read_00502);
      if (read_00502_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00503;
      unsigned int read_00503_len;
      unsigned int read_00503_ptr = 0;
      //**** length read
      read_00503_len = 17;
      read_00503 = (unsigned char*)cgc_malloc(read_00503_len);
      int read_00503_res = cgc_length_read(0, read_00503, read_00503_len);
      if (read_00503_res) {} //silence unused variable warning
      cgc_free(read_00503);
      if (read_00503_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00504;
      unsigned int read_00504_len;
      unsigned int read_00504_ptr = 0;
      //**** length read
      read_00504_len = 28;
      read_00504 = (unsigned char*)cgc_malloc(read_00504_len);
      int read_00504_res = cgc_length_read(0, read_00504, read_00504_len);
      if (read_00504_res) {} //silence unused variable warning
      cgc_free(read_00504);
      if (read_00504_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00505;
      unsigned int read_00505_len;
      unsigned int read_00505_ptr = 0;
      //**** length read
      read_00505_len = 16;
      read_00505 = (unsigned char*)cgc_malloc(read_00505_len);
      int read_00505_res = cgc_length_read(0, read_00505, read_00505_len);
      if (read_00505_res) {} //silence unused variable warning
      cgc_free(read_00505);
      if (read_00505_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x58\x0a";
      static unsigned int write_00103_00000_len = 2;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      unsigned char *read_00506;
      unsigned int read_00506_len;
      unsigned int read_00506_ptr = 0;
      //**** length read
      read_00506_len = 12;
      read_00506 = (unsigned char*)cgc_malloc(read_00506_len);
      int read_00506_res = cgc_length_read(0, read_00506, read_00506_len);
      if (read_00506_res) {} //silence unused variable warning
      cgc_free(read_00506);
      if (read_00506_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00507;
      unsigned int read_00507_len;
      unsigned int read_00507_ptr = 0;
      //**** length read
      read_00507_len = 14;
      read_00507 = (unsigned char*)cgc_malloc(read_00507_len);
      int read_00507_res = cgc_length_read(0, read_00507, read_00507_len);
      if (read_00507_res) {} //silence unused variable warning
      cgc_free(read_00507);
      if (read_00507_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00508;
      unsigned int read_00508_len;
      unsigned int read_00508_ptr = 0;
      //**** length read
      read_00508_len = 17;
      read_00508 = (unsigned char*)cgc_malloc(read_00508_len);
      int read_00508_res = cgc_length_read(0, read_00508, read_00508_len);
      if (read_00508_res) {} //silence unused variable warning
      cgc_free(read_00508);
      if (read_00508_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00509;
      unsigned int read_00509_len;
      unsigned int read_00509_ptr = 0;
      //**** length read
      read_00509_len = 28;
      read_00509 = (unsigned char*)cgc_malloc(read_00509_len);
      int read_00509_res = cgc_length_read(0, read_00509, read_00509_len);
      if (read_00509_res) {} //silence unused variable warning
      cgc_free(read_00509);
      if (read_00509_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00510;
      unsigned int read_00510_len;
      unsigned int read_00510_ptr = 0;
      //**** length read
      read_00510_len = 16;
      read_00510 = (unsigned char*)cgc_malloc(read_00510_len);
      int read_00510_res = cgc_length_read(0, read_00510, read_00510_len);
      if (read_00510_res) {} //silence unused variable warning
      cgc_free(read_00510);
      if (read_00510_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x58\x0a";
      static unsigned int write_00104_00000_len = 2;
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = cgc_append_buf(write_00104, &write_00104_len, write_00104_00000, write_00104_00000_len);
      if (write_00104_len > 0) {
         cgc_transmit_all(1, write_00104, write_00104_len);
      }
      cgc_free(write_00104);
   } while (0);
   do {
      unsigned char *read_00511;
      unsigned int read_00511_len;
      unsigned int read_00511_ptr = 0;
      //**** length read
      read_00511_len = 12;
      read_00511 = (unsigned char*)cgc_malloc(read_00511_len);
      int read_00511_res = cgc_length_read(0, read_00511, read_00511_len);
      if (read_00511_res) {} //silence unused variable warning
      cgc_free(read_00511);
      if (read_00511_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00512;
      unsigned int read_00512_len;
      unsigned int read_00512_ptr = 0;
      //**** length read
      read_00512_len = 14;
      read_00512 = (unsigned char*)cgc_malloc(read_00512_len);
      int read_00512_res = cgc_length_read(0, read_00512, read_00512_len);
      if (read_00512_res) {} //silence unused variable warning
      cgc_free(read_00512);
      if (read_00512_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00513;
      unsigned int read_00513_len;
      unsigned int read_00513_ptr = 0;
      //**** length read
      read_00513_len = 17;
      read_00513 = (unsigned char*)cgc_malloc(read_00513_len);
      int read_00513_res = cgc_length_read(0, read_00513, read_00513_len);
      if (read_00513_res) {} //silence unused variable warning
      cgc_free(read_00513);
      if (read_00513_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00514;
      unsigned int read_00514_len;
      unsigned int read_00514_ptr = 0;
      //**** length read
      read_00514_len = 28;
      read_00514 = (unsigned char*)cgc_malloc(read_00514_len);
      int read_00514_res = cgc_length_read(0, read_00514, read_00514_len);
      if (read_00514_res) {} //silence unused variable warning
      cgc_free(read_00514);
      if (read_00514_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00515;
      unsigned int read_00515_len;
      unsigned int read_00515_ptr = 0;
      //**** length read
      read_00515_len = 16;
      read_00515 = (unsigned char*)cgc_malloc(read_00515_len);
      int read_00515_res = cgc_length_read(0, read_00515, read_00515_len);
      if (read_00515_res) {} //silence unused variable warning
      cgc_free(read_00515);
      if (read_00515_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x58\x0a";
      static unsigned int write_00105_00000_len = 2;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = cgc_append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         cgc_transmit_all(1, write_00105, write_00105_len);
      }
      cgc_free(write_00105);
   } while (0);
   do {
      unsigned char *read_00516;
      unsigned int read_00516_len;
      unsigned int read_00516_ptr = 0;
      //**** length read
      read_00516_len = 12;
      read_00516 = (unsigned char*)cgc_malloc(read_00516_len);
      int read_00516_res = cgc_length_read(0, read_00516, read_00516_len);
      if (read_00516_res) {} //silence unused variable warning
      cgc_free(read_00516);
      if (read_00516_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00517;
      unsigned int read_00517_len;
      unsigned int read_00517_ptr = 0;
      //**** length read
      read_00517_len = 14;
      read_00517 = (unsigned char*)cgc_malloc(read_00517_len);
      int read_00517_res = cgc_length_read(0, read_00517, read_00517_len);
      if (read_00517_res) {} //silence unused variable warning
      cgc_free(read_00517);
      if (read_00517_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00518;
      unsigned int read_00518_len;
      unsigned int read_00518_ptr = 0;
      //**** length read
      read_00518_len = 17;
      read_00518 = (unsigned char*)cgc_malloc(read_00518_len);
      int read_00518_res = cgc_length_read(0, read_00518, read_00518_len);
      if (read_00518_res) {} //silence unused variable warning
      cgc_free(read_00518);
      if (read_00518_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00519;
      unsigned int read_00519_len;
      unsigned int read_00519_ptr = 0;
      //**** length read
      read_00519_len = 28;
      read_00519 = (unsigned char*)cgc_malloc(read_00519_len);
      int read_00519_res = cgc_length_read(0, read_00519, read_00519_len);
      if (read_00519_res) {} //silence unused variable warning
      cgc_free(read_00519);
      if (read_00519_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00520;
      unsigned int read_00520_len;
      unsigned int read_00520_ptr = 0;
      //**** length read
      read_00520_len = 16;
      read_00520 = (unsigned char*)cgc_malloc(read_00520_len);
      int read_00520_res = cgc_length_read(0, read_00520, read_00520_len);
      if (read_00520_res) {} //silence unused variable warning
      cgc_free(read_00520);
      if (read_00520_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x58\x0a";
      static unsigned int write_00106_00000_len = 2;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      unsigned char *read_00521;
      unsigned int read_00521_len;
      unsigned int read_00521_ptr = 0;
      //**** length read
      read_00521_len = 12;
      read_00521 = (unsigned char*)cgc_malloc(read_00521_len);
      int read_00521_res = cgc_length_read(0, read_00521, read_00521_len);
      if (read_00521_res) {} //silence unused variable warning
      cgc_free(read_00521);
      if (read_00521_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00522;
      unsigned int read_00522_len;
      unsigned int read_00522_ptr = 0;
      //**** length read
      read_00522_len = 14;
      read_00522 = (unsigned char*)cgc_malloc(read_00522_len);
      int read_00522_res = cgc_length_read(0, read_00522, read_00522_len);
      if (read_00522_res) {} //silence unused variable warning
      cgc_free(read_00522);
      if (read_00522_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00523;
      unsigned int read_00523_len;
      unsigned int read_00523_ptr = 0;
      //**** length read
      read_00523_len = 17;
      read_00523 = (unsigned char*)cgc_malloc(read_00523_len);
      int read_00523_res = cgc_length_read(0, read_00523, read_00523_len);
      if (read_00523_res) {} //silence unused variable warning
      cgc_free(read_00523);
      if (read_00523_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00524;
      unsigned int read_00524_len;
      unsigned int read_00524_ptr = 0;
      //**** length read
      read_00524_len = 28;
      read_00524 = (unsigned char*)cgc_malloc(read_00524_len);
      int read_00524_res = cgc_length_read(0, read_00524, read_00524_len);
      if (read_00524_res) {} //silence unused variable warning
      cgc_free(read_00524);
      if (read_00524_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00525;
      unsigned int read_00525_len;
      unsigned int read_00525_ptr = 0;
      //**** length read
      read_00525_len = 16;
      read_00525 = (unsigned char*)cgc_malloc(read_00525_len);
      int read_00525_res = cgc_length_read(0, read_00525, read_00525_len);
      if (read_00525_res) {} //silence unused variable warning
      cgc_free(read_00525);
      if (read_00525_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x58\x0a";
      static unsigned int write_00107_00000_len = 2;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = cgc_append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         cgc_transmit_all(1, write_00107, write_00107_len);
      }
      cgc_free(write_00107);
   } while (0);
   do {
      unsigned char *read_00526;
      unsigned int read_00526_len;
      unsigned int read_00526_ptr = 0;
      //**** length read
      read_00526_len = 12;
      read_00526 = (unsigned char*)cgc_malloc(read_00526_len);
      int read_00526_res = cgc_length_read(0, read_00526, read_00526_len);
      if (read_00526_res) {} //silence unused variable warning
      cgc_free(read_00526);
      if (read_00526_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00527;
      unsigned int read_00527_len;
      unsigned int read_00527_ptr = 0;
      //**** length read
      read_00527_len = 14;
      read_00527 = (unsigned char*)cgc_malloc(read_00527_len);
      int read_00527_res = cgc_length_read(0, read_00527, read_00527_len);
      if (read_00527_res) {} //silence unused variable warning
      cgc_free(read_00527);
      if (read_00527_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00528;
      unsigned int read_00528_len;
      unsigned int read_00528_ptr = 0;
      //**** length read
      read_00528_len = 17;
      read_00528 = (unsigned char*)cgc_malloc(read_00528_len);
      int read_00528_res = cgc_length_read(0, read_00528, read_00528_len);
      if (read_00528_res) {} //silence unused variable warning
      cgc_free(read_00528);
      if (read_00528_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00529;
      unsigned int read_00529_len;
      unsigned int read_00529_ptr = 0;
      //**** length read
      read_00529_len = 28;
      read_00529 = (unsigned char*)cgc_malloc(read_00529_len);
      int read_00529_res = cgc_length_read(0, read_00529, read_00529_len);
      if (read_00529_res) {} //silence unused variable warning
      cgc_free(read_00529);
      if (read_00529_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00530;
      unsigned int read_00530_len;
      unsigned int read_00530_ptr = 0;
      //**** length read
      read_00530_len = 16;
      read_00530 = (unsigned char*)cgc_malloc(read_00530_len);
      int read_00530_res = cgc_length_read(0, read_00530, read_00530_len);
      if (read_00530_res) {} //silence unused variable warning
      cgc_free(read_00530);
      if (read_00530_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x58\x0a";
      static unsigned int write_00108_00000_len = 2;
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = cgc_append_buf(write_00108, &write_00108_len, write_00108_00000, write_00108_00000_len);
      if (write_00108_len > 0) {
         cgc_transmit_all(1, write_00108, write_00108_len);
      }
      cgc_free(write_00108);
   } while (0);
   do {
      unsigned char *read_00531;
      unsigned int read_00531_len;
      unsigned int read_00531_ptr = 0;
      //**** length read
      read_00531_len = 12;
      read_00531 = (unsigned char*)cgc_malloc(read_00531_len);
      int read_00531_res = cgc_length_read(0, read_00531, read_00531_len);
      if (read_00531_res) {} //silence unused variable warning
      cgc_free(read_00531);
      if (read_00531_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00532;
      unsigned int read_00532_len;
      unsigned int read_00532_ptr = 0;
      //**** length read
      read_00532_len = 14;
      read_00532 = (unsigned char*)cgc_malloc(read_00532_len);
      int read_00532_res = cgc_length_read(0, read_00532, read_00532_len);
      if (read_00532_res) {} //silence unused variable warning
      cgc_free(read_00532);
      if (read_00532_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00533;
      unsigned int read_00533_len;
      unsigned int read_00533_ptr = 0;
      //**** length read
      read_00533_len = 17;
      read_00533 = (unsigned char*)cgc_malloc(read_00533_len);
      int read_00533_res = cgc_length_read(0, read_00533, read_00533_len);
      if (read_00533_res) {} //silence unused variable warning
      cgc_free(read_00533);
      if (read_00533_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00534;
      unsigned int read_00534_len;
      unsigned int read_00534_ptr = 0;
      //**** length read
      read_00534_len = 28;
      read_00534 = (unsigned char*)cgc_malloc(read_00534_len);
      int read_00534_res = cgc_length_read(0, read_00534, read_00534_len);
      if (read_00534_res) {} //silence unused variable warning
      cgc_free(read_00534);
      if (read_00534_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00535;
      unsigned int read_00535_len;
      unsigned int read_00535_ptr = 0;
      //**** length read
      read_00535_len = 16;
      read_00535 = (unsigned char*)cgc_malloc(read_00535_len);
      int read_00535_res = cgc_length_read(0, read_00535, read_00535_len);
      if (read_00535_res) {} //silence unused variable warning
      cgc_free(read_00535);
      if (read_00535_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x58\x0a";
      static unsigned int write_00109_00000_len = 2;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      unsigned char *read_00536;
      unsigned int read_00536_len;
      unsigned int read_00536_ptr = 0;
      //**** length read
      read_00536_len = 12;
      read_00536 = (unsigned char*)cgc_malloc(read_00536_len);
      int read_00536_res = cgc_length_read(0, read_00536, read_00536_len);
      if (read_00536_res) {} //silence unused variable warning
      cgc_free(read_00536);
      if (read_00536_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00537;
      unsigned int read_00537_len;
      unsigned int read_00537_ptr = 0;
      //**** length read
      read_00537_len = 14;
      read_00537 = (unsigned char*)cgc_malloc(read_00537_len);
      int read_00537_res = cgc_length_read(0, read_00537, read_00537_len);
      if (read_00537_res) {} //silence unused variable warning
      cgc_free(read_00537);
      if (read_00537_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00538;
      unsigned int read_00538_len;
      unsigned int read_00538_ptr = 0;
      //**** length read
      read_00538_len = 17;
      read_00538 = (unsigned char*)cgc_malloc(read_00538_len);
      int read_00538_res = cgc_length_read(0, read_00538, read_00538_len);
      if (read_00538_res) {} //silence unused variable warning
      cgc_free(read_00538);
      if (read_00538_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00539;
      unsigned int read_00539_len;
      unsigned int read_00539_ptr = 0;
      //**** length read
      read_00539_len = 28;
      read_00539 = (unsigned char*)cgc_malloc(read_00539_len);
      int read_00539_res = cgc_length_read(0, read_00539, read_00539_len);
      if (read_00539_res) {} //silence unused variable warning
      cgc_free(read_00539);
      if (read_00539_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00540;
      unsigned int read_00540_len;
      unsigned int read_00540_ptr = 0;
      //**** length read
      read_00540_len = 16;
      read_00540 = (unsigned char*)cgc_malloc(read_00540_len);
      int read_00540_res = cgc_length_read(0, read_00540, read_00540_len);
      if (read_00540_res) {} //silence unused variable warning
      cgc_free(read_00540);
      if (read_00540_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x58\x0a";
      static unsigned int write_00110_00000_len = 2;
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = cgc_append_buf(write_00110, &write_00110_len, write_00110_00000, write_00110_00000_len);
      if (write_00110_len > 0) {
         cgc_transmit_all(1, write_00110, write_00110_len);
      }
      cgc_free(write_00110);
   } while (0);
   do {
      unsigned char *read_00541;
      unsigned int read_00541_len;
      unsigned int read_00541_ptr = 0;
      //**** length read
      read_00541_len = 12;
      read_00541 = (unsigned char*)cgc_malloc(read_00541_len);
      int read_00541_res = cgc_length_read(0, read_00541, read_00541_len);
      if (read_00541_res) {} //silence unused variable warning
      cgc_free(read_00541);
      if (read_00541_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00542;
      unsigned int read_00542_len;
      unsigned int read_00542_ptr = 0;
      //**** length read
      read_00542_len = 14;
      read_00542 = (unsigned char*)cgc_malloc(read_00542_len);
      int read_00542_res = cgc_length_read(0, read_00542, read_00542_len);
      if (read_00542_res) {} //silence unused variable warning
      cgc_free(read_00542);
      if (read_00542_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00543;
      unsigned int read_00543_len;
      unsigned int read_00543_ptr = 0;
      //**** length read
      read_00543_len = 17;
      read_00543 = (unsigned char*)cgc_malloc(read_00543_len);
      int read_00543_res = cgc_length_read(0, read_00543, read_00543_len);
      if (read_00543_res) {} //silence unused variable warning
      cgc_free(read_00543);
      if (read_00543_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00544;
      unsigned int read_00544_len;
      unsigned int read_00544_ptr = 0;
      //**** length read
      read_00544_len = 28;
      read_00544 = (unsigned char*)cgc_malloc(read_00544_len);
      int read_00544_res = cgc_length_read(0, read_00544, read_00544_len);
      if (read_00544_res) {} //silence unused variable warning
      cgc_free(read_00544);
      if (read_00544_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00545;
      unsigned int read_00545_len;
      unsigned int read_00545_ptr = 0;
      //**** length read
      read_00545_len = 16;
      read_00545 = (unsigned char*)cgc_malloc(read_00545_len);
      int read_00545_res = cgc_length_read(0, read_00545, read_00545_len);
      if (read_00545_res) {} //silence unused variable warning
      cgc_free(read_00545);
      if (read_00545_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x58\x0a";
      static unsigned int write_00111_00000_len = 2;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = cgc_append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         cgc_transmit_all(1, write_00111, write_00111_len);
      }
      cgc_free(write_00111);
   } while (0);
   do {
      unsigned char *read_00546;
      unsigned int read_00546_len;
      unsigned int read_00546_ptr = 0;
      //**** length read
      read_00546_len = 12;
      read_00546 = (unsigned char*)cgc_malloc(read_00546_len);
      int read_00546_res = cgc_length_read(0, read_00546, read_00546_len);
      if (read_00546_res) {} //silence unused variable warning
      cgc_free(read_00546);
      if (read_00546_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00547;
      unsigned int read_00547_len;
      unsigned int read_00547_ptr = 0;
      //**** length read
      read_00547_len = 14;
      read_00547 = (unsigned char*)cgc_malloc(read_00547_len);
      int read_00547_res = cgc_length_read(0, read_00547, read_00547_len);
      if (read_00547_res) {} //silence unused variable warning
      cgc_free(read_00547);
      if (read_00547_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00548;
      unsigned int read_00548_len;
      unsigned int read_00548_ptr = 0;
      //**** length read
      read_00548_len = 17;
      read_00548 = (unsigned char*)cgc_malloc(read_00548_len);
      int read_00548_res = cgc_length_read(0, read_00548, read_00548_len);
      if (read_00548_res) {} //silence unused variable warning
      cgc_free(read_00548);
      if (read_00548_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00549;
      unsigned int read_00549_len;
      unsigned int read_00549_ptr = 0;
      //**** length read
      read_00549_len = 28;
      read_00549 = (unsigned char*)cgc_malloc(read_00549_len);
      int read_00549_res = cgc_length_read(0, read_00549, read_00549_len);
      if (read_00549_res) {} //silence unused variable warning
      cgc_free(read_00549);
      if (read_00549_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00550;
      unsigned int read_00550_len;
      unsigned int read_00550_ptr = 0;
      //**** length read
      read_00550_len = 16;
      read_00550 = (unsigned char*)cgc_malloc(read_00550_len);
      int read_00550_res = cgc_length_read(0, read_00550, read_00550_len);
      if (read_00550_res) {} //silence unused variable warning
      cgc_free(read_00550);
      if (read_00550_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x58\x0a";
      static unsigned int write_00112_00000_len = 2;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      unsigned char *read_00551;
      unsigned int read_00551_len;
      unsigned int read_00551_ptr = 0;
      //**** length read
      read_00551_len = 12;
      read_00551 = (unsigned char*)cgc_malloc(read_00551_len);
      int read_00551_res = cgc_length_read(0, read_00551, read_00551_len);
      if (read_00551_res) {} //silence unused variable warning
      cgc_free(read_00551);
      if (read_00551_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00552;
      unsigned int read_00552_len;
      unsigned int read_00552_ptr = 0;
      //**** length read
      read_00552_len = 14;
      read_00552 = (unsigned char*)cgc_malloc(read_00552_len);
      int read_00552_res = cgc_length_read(0, read_00552, read_00552_len);
      if (read_00552_res) {} //silence unused variable warning
      cgc_free(read_00552);
      if (read_00552_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00553;
      unsigned int read_00553_len;
      unsigned int read_00553_ptr = 0;
      //**** length read
      read_00553_len = 17;
      read_00553 = (unsigned char*)cgc_malloc(read_00553_len);
      int read_00553_res = cgc_length_read(0, read_00553, read_00553_len);
      if (read_00553_res) {} //silence unused variable warning
      cgc_free(read_00553);
      if (read_00553_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00554;
      unsigned int read_00554_len;
      unsigned int read_00554_ptr = 0;
      //**** length read
      read_00554_len = 28;
      read_00554 = (unsigned char*)cgc_malloc(read_00554_len);
      int read_00554_res = cgc_length_read(0, read_00554, read_00554_len);
      if (read_00554_res) {} //silence unused variable warning
      cgc_free(read_00554);
      if (read_00554_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00555;
      unsigned int read_00555_len;
      unsigned int read_00555_ptr = 0;
      //**** length read
      read_00555_len = 16;
      read_00555 = (unsigned char*)cgc_malloc(read_00555_len);
      int read_00555_res = cgc_length_read(0, read_00555, read_00555_len);
      if (read_00555_res) {} //silence unused variable warning
      cgc_free(read_00555);
      if (read_00555_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x58\x0a";
      static unsigned int write_00113_00000_len = 2;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = cgc_append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         cgc_transmit_all(1, write_00113, write_00113_len);
      }
      cgc_free(write_00113);
   } while (0);
   do {
      unsigned char *read_00556;
      unsigned int read_00556_len;
      unsigned int read_00556_ptr = 0;
      //**** length read
      read_00556_len = 12;
      read_00556 = (unsigned char*)cgc_malloc(read_00556_len);
      int read_00556_res = cgc_length_read(0, read_00556, read_00556_len);
      if (read_00556_res) {} //silence unused variable warning
      cgc_free(read_00556);
      if (read_00556_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00557;
      unsigned int read_00557_len;
      unsigned int read_00557_ptr = 0;
      //**** length read
      read_00557_len = 14;
      read_00557 = (unsigned char*)cgc_malloc(read_00557_len);
      int read_00557_res = cgc_length_read(0, read_00557, read_00557_len);
      if (read_00557_res) {} //silence unused variable warning
      cgc_free(read_00557);
      if (read_00557_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00558;
      unsigned int read_00558_len;
      unsigned int read_00558_ptr = 0;
      //**** length read
      read_00558_len = 17;
      read_00558 = (unsigned char*)cgc_malloc(read_00558_len);
      int read_00558_res = cgc_length_read(0, read_00558, read_00558_len);
      if (read_00558_res) {} //silence unused variable warning
      cgc_free(read_00558);
      if (read_00558_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00559;
      unsigned int read_00559_len;
      unsigned int read_00559_ptr = 0;
      //**** length read
      read_00559_len = 28;
      read_00559 = (unsigned char*)cgc_malloc(read_00559_len);
      int read_00559_res = cgc_length_read(0, read_00559, read_00559_len);
      if (read_00559_res) {} //silence unused variable warning
      cgc_free(read_00559);
      if (read_00559_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00560;
      unsigned int read_00560_len;
      unsigned int read_00560_ptr = 0;
      //**** length read
      read_00560_len = 16;
      read_00560 = (unsigned char*)cgc_malloc(read_00560_len);
      int read_00560_res = cgc_length_read(0, read_00560, read_00560_len);
      if (read_00560_res) {} //silence unused variable warning
      cgc_free(read_00560);
      if (read_00560_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x58\x0a";
      static unsigned int write_00114_00000_len = 2;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      unsigned char *read_00561;
      unsigned int read_00561_len;
      unsigned int read_00561_ptr = 0;
      //**** length read
      read_00561_len = 12;
      read_00561 = (unsigned char*)cgc_malloc(read_00561_len);
      int read_00561_res = cgc_length_read(0, read_00561, read_00561_len);
      if (read_00561_res) {} //silence unused variable warning
      cgc_free(read_00561);
      if (read_00561_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00562;
      unsigned int read_00562_len;
      unsigned int read_00562_ptr = 0;
      //**** length read
      read_00562_len = 14;
      read_00562 = (unsigned char*)cgc_malloc(read_00562_len);
      int read_00562_res = cgc_length_read(0, read_00562, read_00562_len);
      if (read_00562_res) {} //silence unused variable warning
      cgc_free(read_00562);
      if (read_00562_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00563;
      unsigned int read_00563_len;
      unsigned int read_00563_ptr = 0;
      //**** length read
      read_00563_len = 17;
      read_00563 = (unsigned char*)cgc_malloc(read_00563_len);
      int read_00563_res = cgc_length_read(0, read_00563, read_00563_len);
      if (read_00563_res) {} //silence unused variable warning
      cgc_free(read_00563);
      if (read_00563_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00564;
      unsigned int read_00564_len;
      unsigned int read_00564_ptr = 0;
      //**** length read
      read_00564_len = 28;
      read_00564 = (unsigned char*)cgc_malloc(read_00564_len);
      int read_00564_res = cgc_length_read(0, read_00564, read_00564_len);
      if (read_00564_res) {} //silence unused variable warning
      cgc_free(read_00564);
      if (read_00564_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00565;
      unsigned int read_00565_len;
      unsigned int read_00565_ptr = 0;
      //**** length read
      read_00565_len = 16;
      read_00565 = (unsigned char*)cgc_malloc(read_00565_len);
      int read_00565_res = cgc_length_read(0, read_00565, read_00565_len);
      if (read_00565_res) {} //silence unused variable warning
      cgc_free(read_00565);
      if (read_00565_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x58\x0a";
      static unsigned int write_00115_00000_len = 2;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      unsigned char *read_00566;
      unsigned int read_00566_len;
      unsigned int read_00566_ptr = 0;
      //**** length read
      read_00566_len = 12;
      read_00566 = (unsigned char*)cgc_malloc(read_00566_len);
      int read_00566_res = cgc_length_read(0, read_00566, read_00566_len);
      if (read_00566_res) {} //silence unused variable warning
      cgc_free(read_00566);
      if (read_00566_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00567;
      unsigned int read_00567_len;
      unsigned int read_00567_ptr = 0;
      //**** length read
      read_00567_len = 14;
      read_00567 = (unsigned char*)cgc_malloc(read_00567_len);
      int read_00567_res = cgc_length_read(0, read_00567, read_00567_len);
      if (read_00567_res) {} //silence unused variable warning
      cgc_free(read_00567);
      if (read_00567_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00568;
      unsigned int read_00568_len;
      unsigned int read_00568_ptr = 0;
      //**** length read
      read_00568_len = 17;
      read_00568 = (unsigned char*)cgc_malloc(read_00568_len);
      int read_00568_res = cgc_length_read(0, read_00568, read_00568_len);
      if (read_00568_res) {} //silence unused variable warning
      cgc_free(read_00568);
      if (read_00568_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00569;
      unsigned int read_00569_len;
      unsigned int read_00569_ptr = 0;
      //**** length read
      read_00569_len = 28;
      read_00569 = (unsigned char*)cgc_malloc(read_00569_len);
      int read_00569_res = cgc_length_read(0, read_00569, read_00569_len);
      if (read_00569_res) {} //silence unused variable warning
      cgc_free(read_00569);
      if (read_00569_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00570;
      unsigned int read_00570_len;
      unsigned int read_00570_ptr = 0;
      //**** length read
      read_00570_len = 16;
      read_00570 = (unsigned char*)cgc_malloc(read_00570_len);
      int read_00570_res = cgc_length_read(0, read_00570, read_00570_len);
      if (read_00570_res) {} //silence unused variable warning
      cgc_free(read_00570);
      if (read_00570_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x58\x0a";
      static unsigned int write_00116_00000_len = 2;
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = cgc_append_buf(write_00116, &write_00116_len, write_00116_00000, write_00116_00000_len);
      if (write_00116_len > 0) {
         cgc_transmit_all(1, write_00116, write_00116_len);
      }
      cgc_free(write_00116);
   } while (0);
   do {
      unsigned char *read_00571;
      unsigned int read_00571_len;
      unsigned int read_00571_ptr = 0;
      //**** length read
      read_00571_len = 12;
      read_00571 = (unsigned char*)cgc_malloc(read_00571_len);
      int read_00571_res = cgc_length_read(0, read_00571, read_00571_len);
      if (read_00571_res) {} //silence unused variable warning
      cgc_free(read_00571);
      if (read_00571_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00572;
      unsigned int read_00572_len;
      unsigned int read_00572_ptr = 0;
      //**** length read
      read_00572_len = 14;
      read_00572 = (unsigned char*)cgc_malloc(read_00572_len);
      int read_00572_res = cgc_length_read(0, read_00572, read_00572_len);
      if (read_00572_res) {} //silence unused variable warning
      cgc_free(read_00572);
      if (read_00572_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00573;
      unsigned int read_00573_len;
      unsigned int read_00573_ptr = 0;
      //**** length read
      read_00573_len = 17;
      read_00573 = (unsigned char*)cgc_malloc(read_00573_len);
      int read_00573_res = cgc_length_read(0, read_00573, read_00573_len);
      if (read_00573_res) {} //silence unused variable warning
      cgc_free(read_00573);
      if (read_00573_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00574;
      unsigned int read_00574_len;
      unsigned int read_00574_ptr = 0;
      //**** length read
      read_00574_len = 28;
      read_00574 = (unsigned char*)cgc_malloc(read_00574_len);
      int read_00574_res = cgc_length_read(0, read_00574, read_00574_len);
      if (read_00574_res) {} //silence unused variable warning
      cgc_free(read_00574);
      if (read_00574_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00575;
      unsigned int read_00575_len;
      unsigned int read_00575_ptr = 0;
      //**** length read
      read_00575_len = 16;
      read_00575 = (unsigned char*)cgc_malloc(read_00575_len);
      int read_00575_res = cgc_length_read(0, read_00575, read_00575_len);
      if (read_00575_res) {} //silence unused variable warning
      cgc_free(read_00575);
      if (read_00575_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x58\x0a";
      static unsigned int write_00117_00000_len = 2;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = cgc_append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         cgc_transmit_all(1, write_00117, write_00117_len);
      }
      cgc_free(write_00117);
   } while (0);
   do {
      unsigned char *read_00576;
      unsigned int read_00576_len;
      unsigned int read_00576_ptr = 0;
      //**** length read
      read_00576_len = 12;
      read_00576 = (unsigned char*)cgc_malloc(read_00576_len);
      int read_00576_res = cgc_length_read(0, read_00576, read_00576_len);
      if (read_00576_res) {} //silence unused variable warning
      cgc_free(read_00576);
      if (read_00576_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00577;
      unsigned int read_00577_len;
      unsigned int read_00577_ptr = 0;
      //**** length read
      read_00577_len = 14;
      read_00577 = (unsigned char*)cgc_malloc(read_00577_len);
      int read_00577_res = cgc_length_read(0, read_00577, read_00577_len);
      if (read_00577_res) {} //silence unused variable warning
      cgc_free(read_00577);
      if (read_00577_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00578;
      unsigned int read_00578_len;
      unsigned int read_00578_ptr = 0;
      //**** length read
      read_00578_len = 17;
      read_00578 = (unsigned char*)cgc_malloc(read_00578_len);
      int read_00578_res = cgc_length_read(0, read_00578, read_00578_len);
      if (read_00578_res) {} //silence unused variable warning
      cgc_free(read_00578);
      if (read_00578_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00579;
      unsigned int read_00579_len;
      unsigned int read_00579_ptr = 0;
      //**** length read
      read_00579_len = 28;
      read_00579 = (unsigned char*)cgc_malloc(read_00579_len);
      int read_00579_res = cgc_length_read(0, read_00579, read_00579_len);
      if (read_00579_res) {} //silence unused variable warning
      cgc_free(read_00579);
      if (read_00579_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00580;
      unsigned int read_00580_len;
      unsigned int read_00580_ptr = 0;
      //**** length read
      read_00580_len = 16;
      read_00580 = (unsigned char*)cgc_malloc(read_00580_len);
      int read_00580_res = cgc_length_read(0, read_00580, read_00580_len);
      if (read_00580_res) {} //silence unused variable warning
      cgc_free(read_00580);
      if (read_00580_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x58\x0a";
      static unsigned int write_00118_00000_len = 2;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      unsigned char *read_00581;
      unsigned int read_00581_len;
      unsigned int read_00581_ptr = 0;
      //**** length read
      read_00581_len = 12;
      read_00581 = (unsigned char*)cgc_malloc(read_00581_len);
      int read_00581_res = cgc_length_read(0, read_00581, read_00581_len);
      if (read_00581_res) {} //silence unused variable warning
      cgc_free(read_00581);
      if (read_00581_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00582;
      unsigned int read_00582_len;
      unsigned int read_00582_ptr = 0;
      //**** length read
      read_00582_len = 14;
      read_00582 = (unsigned char*)cgc_malloc(read_00582_len);
      int read_00582_res = cgc_length_read(0, read_00582, read_00582_len);
      if (read_00582_res) {} //silence unused variable warning
      cgc_free(read_00582);
      if (read_00582_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00583;
      unsigned int read_00583_len;
      unsigned int read_00583_ptr = 0;
      //**** length read
      read_00583_len = 17;
      read_00583 = (unsigned char*)cgc_malloc(read_00583_len);
      int read_00583_res = cgc_length_read(0, read_00583, read_00583_len);
      if (read_00583_res) {} //silence unused variable warning
      cgc_free(read_00583);
      if (read_00583_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00584;
      unsigned int read_00584_len;
      unsigned int read_00584_ptr = 0;
      //**** length read
      read_00584_len = 28;
      read_00584 = (unsigned char*)cgc_malloc(read_00584_len);
      int read_00584_res = cgc_length_read(0, read_00584, read_00584_len);
      if (read_00584_res) {} //silence unused variable warning
      cgc_free(read_00584);
      if (read_00584_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00585;
      unsigned int read_00585_len;
      unsigned int read_00585_ptr = 0;
      //**** length read
      read_00585_len = 16;
      read_00585 = (unsigned char*)cgc_malloc(read_00585_len);
      int read_00585_res = cgc_length_read(0, read_00585, read_00585_len);
      if (read_00585_res) {} //silence unused variable warning
      cgc_free(read_00585);
      if (read_00585_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x58\x0a";
      static unsigned int write_00119_00000_len = 2;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = cgc_append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         cgc_transmit_all(1, write_00119, write_00119_len);
      }
      cgc_free(write_00119);
   } while (0);
   do {
      unsigned char *read_00586;
      unsigned int read_00586_len;
      unsigned int read_00586_ptr = 0;
      //**** length read
      read_00586_len = 12;
      read_00586 = (unsigned char*)cgc_malloc(read_00586_len);
      int read_00586_res = cgc_length_read(0, read_00586, read_00586_len);
      if (read_00586_res) {} //silence unused variable warning
      cgc_free(read_00586);
      if (read_00586_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00587;
      unsigned int read_00587_len;
      unsigned int read_00587_ptr = 0;
      //**** length read
      read_00587_len = 14;
      read_00587 = (unsigned char*)cgc_malloc(read_00587_len);
      int read_00587_res = cgc_length_read(0, read_00587, read_00587_len);
      if (read_00587_res) {} //silence unused variable warning
      cgc_free(read_00587);
      if (read_00587_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00588;
      unsigned int read_00588_len;
      unsigned int read_00588_ptr = 0;
      //**** length read
      read_00588_len = 17;
      read_00588 = (unsigned char*)cgc_malloc(read_00588_len);
      int read_00588_res = cgc_length_read(0, read_00588, read_00588_len);
      if (read_00588_res) {} //silence unused variable warning
      cgc_free(read_00588);
      if (read_00588_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00589;
      unsigned int read_00589_len;
      unsigned int read_00589_ptr = 0;
      //**** length read
      read_00589_len = 28;
      read_00589 = (unsigned char*)cgc_malloc(read_00589_len);
      int read_00589_res = cgc_length_read(0, read_00589, read_00589_len);
      if (read_00589_res) {} //silence unused variable warning
      cgc_free(read_00589);
      if (read_00589_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00590;
      unsigned int read_00590_len;
      unsigned int read_00590_ptr = 0;
      //**** length read
      read_00590_len = 16;
      read_00590 = (unsigned char*)cgc_malloc(read_00590_len);
      int read_00590_res = cgc_length_read(0, read_00590, read_00590_len);
      if (read_00590_res) {} //silence unused variable warning
      cgc_free(read_00590);
      if (read_00590_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x58\x0a";
      static unsigned int write_00120_00000_len = 2;
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = cgc_append_buf(write_00120, &write_00120_len, write_00120_00000, write_00120_00000_len);
      if (write_00120_len > 0) {
         cgc_transmit_all(1, write_00120, write_00120_len);
      }
      cgc_free(write_00120);
   } while (0);
   do {
      unsigned char *read_00591;
      unsigned int read_00591_len;
      unsigned int read_00591_ptr = 0;
      //**** length read
      read_00591_len = 12;
      read_00591 = (unsigned char*)cgc_malloc(read_00591_len);
      int read_00591_res = cgc_length_read(0, read_00591, read_00591_len);
      if (read_00591_res) {} //silence unused variable warning
      cgc_free(read_00591);
      if (read_00591_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00592;
      unsigned int read_00592_len;
      unsigned int read_00592_ptr = 0;
      //**** length read
      read_00592_len = 14;
      read_00592 = (unsigned char*)cgc_malloc(read_00592_len);
      int read_00592_res = cgc_length_read(0, read_00592, read_00592_len);
      if (read_00592_res) {} //silence unused variable warning
      cgc_free(read_00592);
      if (read_00592_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00593;
      unsigned int read_00593_len;
      unsigned int read_00593_ptr = 0;
      //**** length read
      read_00593_len = 17;
      read_00593 = (unsigned char*)cgc_malloc(read_00593_len);
      int read_00593_res = cgc_length_read(0, read_00593, read_00593_len);
      if (read_00593_res) {} //silence unused variable warning
      cgc_free(read_00593);
      if (read_00593_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00594;
      unsigned int read_00594_len;
      unsigned int read_00594_ptr = 0;
      //**** length read
      read_00594_len = 28;
      read_00594 = (unsigned char*)cgc_malloc(read_00594_len);
      int read_00594_res = cgc_length_read(0, read_00594, read_00594_len);
      if (read_00594_res) {} //silence unused variable warning
      cgc_free(read_00594);
      if (read_00594_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00595;
      unsigned int read_00595_len;
      unsigned int read_00595_ptr = 0;
      //**** length read
      read_00595_len = 16;
      read_00595 = (unsigned char*)cgc_malloc(read_00595_len);
      int read_00595_res = cgc_length_read(0, read_00595, read_00595_len);
      if (read_00595_res) {} //silence unused variable warning
      cgc_free(read_00595);
      if (read_00595_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x58\x0a";
      static unsigned int write_00121_00000_len = 2;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      unsigned char *read_00596;
      unsigned int read_00596_len;
      unsigned int read_00596_ptr = 0;
      //**** length read
      read_00596_len = 12;
      read_00596 = (unsigned char*)cgc_malloc(read_00596_len);
      int read_00596_res = cgc_length_read(0, read_00596, read_00596_len);
      if (read_00596_res) {} //silence unused variable warning
      cgc_free(read_00596);
      if (read_00596_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00597;
      unsigned int read_00597_len;
      unsigned int read_00597_ptr = 0;
      //**** length read
      read_00597_len = 14;
      read_00597 = (unsigned char*)cgc_malloc(read_00597_len);
      int read_00597_res = cgc_length_read(0, read_00597, read_00597_len);
      if (read_00597_res) {} //silence unused variable warning
      cgc_free(read_00597);
      if (read_00597_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00598;
      unsigned int read_00598_len;
      unsigned int read_00598_ptr = 0;
      //**** length read
      read_00598_len = 17;
      read_00598 = (unsigned char*)cgc_malloc(read_00598_len);
      int read_00598_res = cgc_length_read(0, read_00598, read_00598_len);
      if (read_00598_res) {} //silence unused variable warning
      cgc_free(read_00598);
      if (read_00598_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00599;
      unsigned int read_00599_len;
      unsigned int read_00599_ptr = 0;
      //**** length read
      read_00599_len = 28;
      read_00599 = (unsigned char*)cgc_malloc(read_00599_len);
      int read_00599_res = cgc_length_read(0, read_00599, read_00599_len);
      if (read_00599_res) {} //silence unused variable warning
      cgc_free(read_00599);
      if (read_00599_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00600;
      unsigned int read_00600_len;
      unsigned int read_00600_ptr = 0;
      //**** length read
      read_00600_len = 16;
      read_00600 = (unsigned char*)cgc_malloc(read_00600_len);
      int read_00600_res = cgc_length_read(0, read_00600, read_00600_len);
      if (read_00600_res) {} //silence unused variable warning
      cgc_free(read_00600);
      if (read_00600_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x58\x0a";
      static unsigned int write_00122_00000_len = 2;
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = cgc_append_buf(write_00122, &write_00122_len, write_00122_00000, write_00122_00000_len);
      if (write_00122_len > 0) {
         cgc_transmit_all(1, write_00122, write_00122_len);
      }
      cgc_free(write_00122);
   } while (0);
   do {
      unsigned char *read_00601;
      unsigned int read_00601_len;
      unsigned int read_00601_ptr = 0;
      //**** length read
      read_00601_len = 12;
      read_00601 = (unsigned char*)cgc_malloc(read_00601_len);
      int read_00601_res = cgc_length_read(0, read_00601, read_00601_len);
      if (read_00601_res) {} //silence unused variable warning
      cgc_free(read_00601);
      if (read_00601_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00602;
      unsigned int read_00602_len;
      unsigned int read_00602_ptr = 0;
      //**** length read
      read_00602_len = 14;
      read_00602 = (unsigned char*)cgc_malloc(read_00602_len);
      int read_00602_res = cgc_length_read(0, read_00602, read_00602_len);
      if (read_00602_res) {} //silence unused variable warning
      cgc_free(read_00602);
      if (read_00602_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00603;
      unsigned int read_00603_len;
      unsigned int read_00603_ptr = 0;
      //**** length read
      read_00603_len = 17;
      read_00603 = (unsigned char*)cgc_malloc(read_00603_len);
      int read_00603_res = cgc_length_read(0, read_00603, read_00603_len);
      if (read_00603_res) {} //silence unused variable warning
      cgc_free(read_00603);
      if (read_00603_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00604;
      unsigned int read_00604_len;
      unsigned int read_00604_ptr = 0;
      //**** length read
      read_00604_len = 28;
      read_00604 = (unsigned char*)cgc_malloc(read_00604_len);
      int read_00604_res = cgc_length_read(0, read_00604, read_00604_len);
      if (read_00604_res) {} //silence unused variable warning
      cgc_free(read_00604);
      if (read_00604_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00605;
      unsigned int read_00605_len;
      unsigned int read_00605_ptr = 0;
      //**** length read
      read_00605_len = 16;
      read_00605 = (unsigned char*)cgc_malloc(read_00605_len);
      int read_00605_res = cgc_length_read(0, read_00605, read_00605_len);
      if (read_00605_res) {} //silence unused variable warning
      cgc_free(read_00605);
      if (read_00605_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x58\x0a";
      static unsigned int write_00123_00000_len = 2;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = cgc_append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         cgc_transmit_all(1, write_00123, write_00123_len);
      }
      cgc_free(write_00123);
   } while (0);
   do {
      unsigned char *read_00606;
      unsigned int read_00606_len;
      unsigned int read_00606_ptr = 0;
      //**** length read
      read_00606_len = 12;
      read_00606 = (unsigned char*)cgc_malloc(read_00606_len);
      int read_00606_res = cgc_length_read(0, read_00606, read_00606_len);
      if (read_00606_res) {} //silence unused variable warning
      cgc_free(read_00606);
      if (read_00606_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00607;
      unsigned int read_00607_len;
      unsigned int read_00607_ptr = 0;
      //**** length read
      read_00607_len = 14;
      read_00607 = (unsigned char*)cgc_malloc(read_00607_len);
      int read_00607_res = cgc_length_read(0, read_00607, read_00607_len);
      if (read_00607_res) {} //silence unused variable warning
      cgc_free(read_00607);
      if (read_00607_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00608;
      unsigned int read_00608_len;
      unsigned int read_00608_ptr = 0;
      //**** length read
      read_00608_len = 17;
      read_00608 = (unsigned char*)cgc_malloc(read_00608_len);
      int read_00608_res = cgc_length_read(0, read_00608, read_00608_len);
      if (read_00608_res) {} //silence unused variable warning
      cgc_free(read_00608);
      if (read_00608_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00609;
      unsigned int read_00609_len;
      unsigned int read_00609_ptr = 0;
      //**** length read
      read_00609_len = 28;
      read_00609 = (unsigned char*)cgc_malloc(read_00609_len);
      int read_00609_res = cgc_length_read(0, read_00609, read_00609_len);
      if (read_00609_res) {} //silence unused variable warning
      cgc_free(read_00609);
      if (read_00609_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00610;
      unsigned int read_00610_len;
      unsigned int read_00610_ptr = 0;
      //**** length read
      read_00610_len = 16;
      read_00610 = (unsigned char*)cgc_malloc(read_00610_len);
      int read_00610_res = cgc_length_read(0, read_00610, read_00610_len);
      if (read_00610_res) {} //silence unused variable warning
      cgc_free(read_00610);
      if (read_00610_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x58\x0a";
      static unsigned int write_00124_00000_len = 2;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      unsigned char *read_00611;
      unsigned int read_00611_len;
      unsigned int read_00611_ptr = 0;
      //**** length read
      read_00611_len = 12;
      read_00611 = (unsigned char*)cgc_malloc(read_00611_len);
      int read_00611_res = cgc_length_read(0, read_00611, read_00611_len);
      if (read_00611_res) {} //silence unused variable warning
      cgc_free(read_00611);
      if (read_00611_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00612;
      unsigned int read_00612_len;
      unsigned int read_00612_ptr = 0;
      //**** length read
      read_00612_len = 14;
      read_00612 = (unsigned char*)cgc_malloc(read_00612_len);
      int read_00612_res = cgc_length_read(0, read_00612, read_00612_len);
      if (read_00612_res) {} //silence unused variable warning
      cgc_free(read_00612);
      if (read_00612_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00613;
      unsigned int read_00613_len;
      unsigned int read_00613_ptr = 0;
      //**** length read
      read_00613_len = 17;
      read_00613 = (unsigned char*)cgc_malloc(read_00613_len);
      int read_00613_res = cgc_length_read(0, read_00613, read_00613_len);
      if (read_00613_res) {} //silence unused variable warning
      cgc_free(read_00613);
      if (read_00613_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00614;
      unsigned int read_00614_len;
      unsigned int read_00614_ptr = 0;
      //**** length read
      read_00614_len = 28;
      read_00614 = (unsigned char*)cgc_malloc(read_00614_len);
      int read_00614_res = cgc_length_read(0, read_00614, read_00614_len);
      if (read_00614_res) {} //silence unused variable warning
      cgc_free(read_00614);
      if (read_00614_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00615;
      unsigned int read_00615_len;
      unsigned int read_00615_ptr = 0;
      //**** length read
      read_00615_len = 16;
      read_00615 = (unsigned char*)cgc_malloc(read_00615_len);
      int read_00615_res = cgc_length_read(0, read_00615, read_00615_len);
      if (read_00615_res) {} //silence unused variable warning
      cgc_free(read_00615);
      if (read_00615_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x58\x0a";
      static unsigned int write_00125_00000_len = 2;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = cgc_append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         cgc_transmit_all(1, write_00125, write_00125_len);
      }
      cgc_free(write_00125);
   } while (0);
   do {
      unsigned char *read_00616;
      unsigned int read_00616_len;
      unsigned int read_00616_ptr = 0;
      //**** length read
      read_00616_len = 12;
      read_00616 = (unsigned char*)cgc_malloc(read_00616_len);
      int read_00616_res = cgc_length_read(0, read_00616, read_00616_len);
      if (read_00616_res) {} //silence unused variable warning
      cgc_free(read_00616);
      if (read_00616_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00617;
      unsigned int read_00617_len;
      unsigned int read_00617_ptr = 0;
      //**** length read
      read_00617_len = 14;
      read_00617 = (unsigned char*)cgc_malloc(read_00617_len);
      int read_00617_res = cgc_length_read(0, read_00617, read_00617_len);
      if (read_00617_res) {} //silence unused variable warning
      cgc_free(read_00617);
      if (read_00617_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00618;
      unsigned int read_00618_len;
      unsigned int read_00618_ptr = 0;
      //**** length read
      read_00618_len = 17;
      read_00618 = (unsigned char*)cgc_malloc(read_00618_len);
      int read_00618_res = cgc_length_read(0, read_00618, read_00618_len);
      if (read_00618_res) {} //silence unused variable warning
      cgc_free(read_00618);
      if (read_00618_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00619;
      unsigned int read_00619_len;
      unsigned int read_00619_ptr = 0;
      //**** length read
      read_00619_len = 28;
      read_00619 = (unsigned char*)cgc_malloc(read_00619_len);
      int read_00619_res = cgc_length_read(0, read_00619, read_00619_len);
      if (read_00619_res) {} //silence unused variable warning
      cgc_free(read_00619);
      if (read_00619_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00620;
      unsigned int read_00620_len;
      unsigned int read_00620_ptr = 0;
      //**** length read
      read_00620_len = 16;
      read_00620 = (unsigned char*)cgc_malloc(read_00620_len);
      int read_00620_res = cgc_length_read(0, read_00620, read_00620_len);
      if (read_00620_res) {} //silence unused variable warning
      cgc_free(read_00620);
      if (read_00620_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x58\x0a";
      static unsigned int write_00126_00000_len = 2;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      unsigned char *read_00621;
      unsigned int read_00621_len;
      unsigned int read_00621_ptr = 0;
      //**** length read
      read_00621_len = 12;
      read_00621 = (unsigned char*)cgc_malloc(read_00621_len);
      int read_00621_res = cgc_length_read(0, read_00621, read_00621_len);
      if (read_00621_res) {} //silence unused variable warning
      cgc_free(read_00621);
      if (read_00621_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00622;
      unsigned int read_00622_len;
      unsigned int read_00622_ptr = 0;
      //**** length read
      read_00622_len = 14;
      read_00622 = (unsigned char*)cgc_malloc(read_00622_len);
      int read_00622_res = cgc_length_read(0, read_00622, read_00622_len);
      if (read_00622_res) {} //silence unused variable warning
      cgc_free(read_00622);
      if (read_00622_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00623;
      unsigned int read_00623_len;
      unsigned int read_00623_ptr = 0;
      //**** length read
      read_00623_len = 17;
      read_00623 = (unsigned char*)cgc_malloc(read_00623_len);
      int read_00623_res = cgc_length_read(0, read_00623, read_00623_len);
      if (read_00623_res) {} //silence unused variable warning
      cgc_free(read_00623);
      if (read_00623_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00624;
      unsigned int read_00624_len;
      unsigned int read_00624_ptr = 0;
      //**** length read
      read_00624_len = 28;
      read_00624 = (unsigned char*)cgc_malloc(read_00624_len);
      int read_00624_res = cgc_length_read(0, read_00624, read_00624_len);
      if (read_00624_res) {} //silence unused variable warning
      cgc_free(read_00624);
      if (read_00624_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00625;
      unsigned int read_00625_len;
      unsigned int read_00625_ptr = 0;
      //**** length read
      read_00625_len = 16;
      read_00625 = (unsigned char*)cgc_malloc(read_00625_len);
      int read_00625_res = cgc_length_read(0, read_00625, read_00625_len);
      if (read_00625_res) {} //silence unused variable warning
      cgc_free(read_00625);
      if (read_00625_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x58\x0a";
      static unsigned int write_00127_00000_len = 2;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      unsigned char *read_00626;
      unsigned int read_00626_len;
      unsigned int read_00626_ptr = 0;
      //**** length read
      read_00626_len = 12;
      read_00626 = (unsigned char*)cgc_malloc(read_00626_len);
      int read_00626_res = cgc_length_read(0, read_00626, read_00626_len);
      if (read_00626_res) {} //silence unused variable warning
      cgc_free(read_00626);
      if (read_00626_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00627;
      unsigned int read_00627_len;
      unsigned int read_00627_ptr = 0;
      //**** length read
      read_00627_len = 14;
      read_00627 = (unsigned char*)cgc_malloc(read_00627_len);
      int read_00627_res = cgc_length_read(0, read_00627, read_00627_len);
      if (read_00627_res) {} //silence unused variable warning
      cgc_free(read_00627);
      if (read_00627_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00628;
      unsigned int read_00628_len;
      unsigned int read_00628_ptr = 0;
      //**** length read
      read_00628_len = 17;
      read_00628 = (unsigned char*)cgc_malloc(read_00628_len);
      int read_00628_res = cgc_length_read(0, read_00628, read_00628_len);
      if (read_00628_res) {} //silence unused variable warning
      cgc_free(read_00628);
      if (read_00628_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00629;
      unsigned int read_00629_len;
      unsigned int read_00629_ptr = 0;
      //**** length read
      read_00629_len = 28;
      read_00629 = (unsigned char*)cgc_malloc(read_00629_len);
      int read_00629_res = cgc_length_read(0, read_00629, read_00629_len);
      if (read_00629_res) {} //silence unused variable warning
      cgc_free(read_00629);
      if (read_00629_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00630;
      unsigned int read_00630_len;
      unsigned int read_00630_ptr = 0;
      //**** length read
      read_00630_len = 16;
      read_00630 = (unsigned char*)cgc_malloc(read_00630_len);
      int read_00630_res = cgc_length_read(0, read_00630, read_00630_len);
      if (read_00630_res) {} //silence unused variable warning
      cgc_free(read_00630);
      if (read_00630_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x58\x0a";
      static unsigned int write_00128_00000_len = 2;
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = cgc_append_buf(write_00128, &write_00128_len, write_00128_00000, write_00128_00000_len);
      if (write_00128_len > 0) {
         cgc_transmit_all(1, write_00128, write_00128_len);
      }
      cgc_free(write_00128);
   } while (0);
   do {
      unsigned char *read_00631;
      unsigned int read_00631_len;
      unsigned int read_00631_ptr = 0;
      //**** length read
      read_00631_len = 12;
      read_00631 = (unsigned char*)cgc_malloc(read_00631_len);
      int read_00631_res = cgc_length_read(0, read_00631, read_00631_len);
      if (read_00631_res) {} //silence unused variable warning
      cgc_free(read_00631);
      if (read_00631_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00632;
      unsigned int read_00632_len;
      unsigned int read_00632_ptr = 0;
      //**** length read
      read_00632_len = 14;
      read_00632 = (unsigned char*)cgc_malloc(read_00632_len);
      int read_00632_res = cgc_length_read(0, read_00632, read_00632_len);
      if (read_00632_res) {} //silence unused variable warning
      cgc_free(read_00632);
      if (read_00632_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00633;
      unsigned int read_00633_len;
      unsigned int read_00633_ptr = 0;
      //**** length read
      read_00633_len = 17;
      read_00633 = (unsigned char*)cgc_malloc(read_00633_len);
      int read_00633_res = cgc_length_read(0, read_00633, read_00633_len);
      if (read_00633_res) {} //silence unused variable warning
      cgc_free(read_00633);
      if (read_00633_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00634;
      unsigned int read_00634_len;
      unsigned int read_00634_ptr = 0;
      //**** length read
      read_00634_len = 28;
      read_00634 = (unsigned char*)cgc_malloc(read_00634_len);
      int read_00634_res = cgc_length_read(0, read_00634, read_00634_len);
      if (read_00634_res) {} //silence unused variable warning
      cgc_free(read_00634);
      if (read_00634_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00635;
      unsigned int read_00635_len;
      unsigned int read_00635_ptr = 0;
      //**** length read
      read_00635_len = 16;
      read_00635 = (unsigned char*)cgc_malloc(read_00635_len);
      int read_00635_res = cgc_length_read(0, read_00635, read_00635_len);
      if (read_00635_res) {} //silence unused variable warning
      cgc_free(read_00635);
      if (read_00635_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x58\x0a";
      static unsigned int write_00129_00000_len = 2;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = cgc_append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         cgc_transmit_all(1, write_00129, write_00129_len);
      }
      cgc_free(write_00129);
   } while (0);
   do {
      unsigned char *read_00636;
      unsigned int read_00636_len;
      unsigned int read_00636_ptr = 0;
      //**** length read
      read_00636_len = 12;
      read_00636 = (unsigned char*)cgc_malloc(read_00636_len);
      int read_00636_res = cgc_length_read(0, read_00636, read_00636_len);
      if (read_00636_res) {} //silence unused variable warning
      cgc_free(read_00636);
      if (read_00636_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00637;
      unsigned int read_00637_len;
      unsigned int read_00637_ptr = 0;
      //**** length read
      read_00637_len = 14;
      read_00637 = (unsigned char*)cgc_malloc(read_00637_len);
      int read_00637_res = cgc_length_read(0, read_00637, read_00637_len);
      if (read_00637_res) {} //silence unused variable warning
      cgc_free(read_00637);
      if (read_00637_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00638;
      unsigned int read_00638_len;
      unsigned int read_00638_ptr = 0;
      //**** length read
      read_00638_len = 17;
      read_00638 = (unsigned char*)cgc_malloc(read_00638_len);
      int read_00638_res = cgc_length_read(0, read_00638, read_00638_len);
      if (read_00638_res) {} //silence unused variable warning
      cgc_free(read_00638);
      if (read_00638_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00639;
      unsigned int read_00639_len;
      unsigned int read_00639_ptr = 0;
      //**** length read
      read_00639_len = 28;
      read_00639 = (unsigned char*)cgc_malloc(read_00639_len);
      int read_00639_res = cgc_length_read(0, read_00639, read_00639_len);
      if (read_00639_res) {} //silence unused variable warning
      cgc_free(read_00639);
      if (read_00639_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00640;
      unsigned int read_00640_len;
      unsigned int read_00640_ptr = 0;
      //**** length read
      read_00640_len = 16;
      read_00640 = (unsigned char*)cgc_malloc(read_00640_len);
      int read_00640_res = cgc_length_read(0, read_00640, read_00640_len);
      if (read_00640_res) {} //silence unused variable warning
      cgc_free(read_00640);
      if (read_00640_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x58\x0a";
      static unsigned int write_00130_00000_len = 2;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      unsigned char *read_00641;
      unsigned int read_00641_len;
      unsigned int read_00641_ptr = 0;
      //**** length read
      read_00641_len = 12;
      read_00641 = (unsigned char*)cgc_malloc(read_00641_len);
      int read_00641_res = cgc_length_read(0, read_00641, read_00641_len);
      if (read_00641_res) {} //silence unused variable warning
      cgc_free(read_00641);
      if (read_00641_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00642;
      unsigned int read_00642_len;
      unsigned int read_00642_ptr = 0;
      //**** length read
      read_00642_len = 14;
      read_00642 = (unsigned char*)cgc_malloc(read_00642_len);
      int read_00642_res = cgc_length_read(0, read_00642, read_00642_len);
      if (read_00642_res) {} //silence unused variable warning
      cgc_free(read_00642);
      if (read_00642_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00643;
      unsigned int read_00643_len;
      unsigned int read_00643_ptr = 0;
      //**** length read
      read_00643_len = 17;
      read_00643 = (unsigned char*)cgc_malloc(read_00643_len);
      int read_00643_res = cgc_length_read(0, read_00643, read_00643_len);
      if (read_00643_res) {} //silence unused variable warning
      cgc_free(read_00643);
      if (read_00643_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00644;
      unsigned int read_00644_len;
      unsigned int read_00644_ptr = 0;
      //**** length read
      read_00644_len = 28;
      read_00644 = (unsigned char*)cgc_malloc(read_00644_len);
      int read_00644_res = cgc_length_read(0, read_00644, read_00644_len);
      if (read_00644_res) {} //silence unused variable warning
      cgc_free(read_00644);
      if (read_00644_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00645;
      unsigned int read_00645_len;
      unsigned int read_00645_ptr = 0;
      //**** length read
      read_00645_len = 16;
      read_00645 = (unsigned char*)cgc_malloc(read_00645_len);
      int read_00645_res = cgc_length_read(0, read_00645, read_00645_len);
      if (read_00645_res) {} //silence unused variable warning
      cgc_free(read_00645);
      if (read_00645_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x58\x0a";
      static unsigned int write_00131_00000_len = 2;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = cgc_append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         cgc_transmit_all(1, write_00131, write_00131_len);
      }
      cgc_free(write_00131);
   } while (0);
   do {
      unsigned char *read_00646;
      unsigned int read_00646_len;
      unsigned int read_00646_ptr = 0;
      //**** length read
      read_00646_len = 12;
      read_00646 = (unsigned char*)cgc_malloc(read_00646_len);
      int read_00646_res = cgc_length_read(0, read_00646, read_00646_len);
      if (read_00646_res) {} //silence unused variable warning
      cgc_free(read_00646);
      if (read_00646_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00647;
      unsigned int read_00647_len;
      unsigned int read_00647_ptr = 0;
      //**** length read
      read_00647_len = 14;
      read_00647 = (unsigned char*)cgc_malloc(read_00647_len);
      int read_00647_res = cgc_length_read(0, read_00647, read_00647_len);
      if (read_00647_res) {} //silence unused variable warning
      cgc_free(read_00647);
      if (read_00647_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00648;
      unsigned int read_00648_len;
      unsigned int read_00648_ptr = 0;
      //**** length read
      read_00648_len = 17;
      read_00648 = (unsigned char*)cgc_malloc(read_00648_len);
      int read_00648_res = cgc_length_read(0, read_00648, read_00648_len);
      if (read_00648_res) {} //silence unused variable warning
      cgc_free(read_00648);
      if (read_00648_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00649;
      unsigned int read_00649_len;
      unsigned int read_00649_ptr = 0;
      //**** length read
      read_00649_len = 28;
      read_00649 = (unsigned char*)cgc_malloc(read_00649_len);
      int read_00649_res = cgc_length_read(0, read_00649, read_00649_len);
      if (read_00649_res) {} //silence unused variable warning
      cgc_free(read_00649);
      if (read_00649_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00650;
      unsigned int read_00650_len;
      unsigned int read_00650_ptr = 0;
      //**** length read
      read_00650_len = 16;
      read_00650 = (unsigned char*)cgc_malloc(read_00650_len);
      int read_00650_res = cgc_length_read(0, read_00650, read_00650_len);
      if (read_00650_res) {} //silence unused variable warning
      cgc_free(read_00650);
      if (read_00650_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x58\x0a";
      static unsigned int write_00132_00000_len = 2;
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = cgc_append_buf(write_00132, &write_00132_len, write_00132_00000, write_00132_00000_len);
      if (write_00132_len > 0) {
         cgc_transmit_all(1, write_00132, write_00132_len);
      }
      cgc_free(write_00132);
   } while (0);
   do {
      unsigned char *read_00651;
      unsigned int read_00651_len;
      unsigned int read_00651_ptr = 0;
      //**** length read
      read_00651_len = 12;
      read_00651 = (unsigned char*)cgc_malloc(read_00651_len);
      int read_00651_res = cgc_length_read(0, read_00651, read_00651_len);
      if (read_00651_res) {} //silence unused variable warning
      cgc_free(read_00651);
      if (read_00651_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00652;
      unsigned int read_00652_len;
      unsigned int read_00652_ptr = 0;
      //**** length read
      read_00652_len = 14;
      read_00652 = (unsigned char*)cgc_malloc(read_00652_len);
      int read_00652_res = cgc_length_read(0, read_00652, read_00652_len);
      if (read_00652_res) {} //silence unused variable warning
      cgc_free(read_00652);
      if (read_00652_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00653;
      unsigned int read_00653_len;
      unsigned int read_00653_ptr = 0;
      //**** length read
      read_00653_len = 17;
      read_00653 = (unsigned char*)cgc_malloc(read_00653_len);
      int read_00653_res = cgc_length_read(0, read_00653, read_00653_len);
      if (read_00653_res) {} //silence unused variable warning
      cgc_free(read_00653);
      if (read_00653_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00654;
      unsigned int read_00654_len;
      unsigned int read_00654_ptr = 0;
      //**** length read
      read_00654_len = 28;
      read_00654 = (unsigned char*)cgc_malloc(read_00654_len);
      int read_00654_res = cgc_length_read(0, read_00654, read_00654_len);
      if (read_00654_res) {} //silence unused variable warning
      cgc_free(read_00654);
      if (read_00654_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00655;
      unsigned int read_00655_len;
      unsigned int read_00655_ptr = 0;
      //**** length read
      read_00655_len = 16;
      read_00655 = (unsigned char*)cgc_malloc(read_00655_len);
      int read_00655_res = cgc_length_read(0, read_00655, read_00655_len);
      if (read_00655_res) {} //silence unused variable warning
      cgc_free(read_00655);
      if (read_00655_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x58\x0a";
      static unsigned int write_00133_00000_len = 2;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      unsigned char *read_00656;
      unsigned int read_00656_len;
      unsigned int read_00656_ptr = 0;
      //**** length read
      read_00656_len = 12;
      read_00656 = (unsigned char*)cgc_malloc(read_00656_len);
      int read_00656_res = cgc_length_read(0, read_00656, read_00656_len);
      if (read_00656_res) {} //silence unused variable warning
      cgc_free(read_00656);
      if (read_00656_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00657;
      unsigned int read_00657_len;
      unsigned int read_00657_ptr = 0;
      //**** length read
      read_00657_len = 14;
      read_00657 = (unsigned char*)cgc_malloc(read_00657_len);
      int read_00657_res = cgc_length_read(0, read_00657, read_00657_len);
      if (read_00657_res) {} //silence unused variable warning
      cgc_free(read_00657);
      if (read_00657_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00658;
      unsigned int read_00658_len;
      unsigned int read_00658_ptr = 0;
      //**** length read
      read_00658_len = 17;
      read_00658 = (unsigned char*)cgc_malloc(read_00658_len);
      int read_00658_res = cgc_length_read(0, read_00658, read_00658_len);
      if (read_00658_res) {} //silence unused variable warning
      cgc_free(read_00658);
      if (read_00658_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00659;
      unsigned int read_00659_len;
      unsigned int read_00659_ptr = 0;
      //**** length read
      read_00659_len = 28;
      read_00659 = (unsigned char*)cgc_malloc(read_00659_len);
      int read_00659_res = cgc_length_read(0, read_00659, read_00659_len);
      if (read_00659_res) {} //silence unused variable warning
      cgc_free(read_00659);
      if (read_00659_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00660;
      unsigned int read_00660_len;
      unsigned int read_00660_ptr = 0;
      //**** length read
      read_00660_len = 16;
      read_00660 = (unsigned char*)cgc_malloc(read_00660_len);
      int read_00660_res = cgc_length_read(0, read_00660, read_00660_len);
      if (read_00660_res) {} //silence unused variable warning
      cgc_free(read_00660);
      if (read_00660_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x58\x0a";
      static unsigned int write_00134_00000_len = 2;
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = cgc_append_buf(write_00134, &write_00134_len, write_00134_00000, write_00134_00000_len);
      if (write_00134_len > 0) {
         cgc_transmit_all(1, write_00134, write_00134_len);
      }
      cgc_free(write_00134);
   } while (0);
   do {
      unsigned char *read_00661;
      unsigned int read_00661_len;
      unsigned int read_00661_ptr = 0;
      //**** length read
      read_00661_len = 12;
      read_00661 = (unsigned char*)cgc_malloc(read_00661_len);
      int read_00661_res = cgc_length_read(0, read_00661, read_00661_len);
      if (read_00661_res) {} //silence unused variable warning
      cgc_free(read_00661);
      if (read_00661_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00662;
      unsigned int read_00662_len;
      unsigned int read_00662_ptr = 0;
      //**** length read
      read_00662_len = 14;
      read_00662 = (unsigned char*)cgc_malloc(read_00662_len);
      int read_00662_res = cgc_length_read(0, read_00662, read_00662_len);
      if (read_00662_res) {} //silence unused variable warning
      cgc_free(read_00662);
      if (read_00662_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00663;
      unsigned int read_00663_len;
      unsigned int read_00663_ptr = 0;
      //**** length read
      read_00663_len = 17;
      read_00663 = (unsigned char*)cgc_malloc(read_00663_len);
      int read_00663_res = cgc_length_read(0, read_00663, read_00663_len);
      if (read_00663_res) {} //silence unused variable warning
      cgc_free(read_00663);
      if (read_00663_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00664;
      unsigned int read_00664_len;
      unsigned int read_00664_ptr = 0;
      //**** length read
      read_00664_len = 28;
      read_00664 = (unsigned char*)cgc_malloc(read_00664_len);
      int read_00664_res = cgc_length_read(0, read_00664, read_00664_len);
      if (read_00664_res) {} //silence unused variable warning
      cgc_free(read_00664);
      if (read_00664_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00665;
      unsigned int read_00665_len;
      unsigned int read_00665_ptr = 0;
      //**** delimited read
      static unsigned char read_00665_delim[] = 
         "\x29\x3a\x20";
      read_00665 = NULL;
      read_00665_len = 0;
      int read_00665_res = cgc_delimited_read(0, &read_00665, &read_00665_len, read_00665_delim, 3);
      if (read_00665_res) {} //silence unused variable warning
      cgc_free(read_00665);
      if (read_00665_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x58\x0a";
      static unsigned int write_00135_00000_len = 2;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = cgc_append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         cgc_transmit_all(1, write_00135, write_00135_len);
      }
      cgc_free(write_00135);
   } while (0);
   do {
      unsigned char *read_00666;
      unsigned int read_00666_len;
      unsigned int read_00666_ptr = 0;
      //**** length read
      read_00666_len = 12;
      read_00666 = (unsigned char*)cgc_malloc(read_00666_len);
      int read_00666_res = cgc_length_read(0, read_00666, read_00666_len);
      if (read_00666_res) {} //silence unused variable warning
      cgc_free(read_00666);
      if (read_00666_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00667;
      unsigned int read_00667_len;
      unsigned int read_00667_ptr = 0;
      //**** length read
      read_00667_len = 14;
      read_00667 = (unsigned char*)cgc_malloc(read_00667_len);
      int read_00667_res = cgc_length_read(0, read_00667, read_00667_len);
      if (read_00667_res) {} //silence unused variable warning
      cgc_free(read_00667);
      if (read_00667_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00668;
      unsigned int read_00668_len;
      unsigned int read_00668_ptr = 0;
      //**** length read
      read_00668_len = 17;
      read_00668 = (unsigned char*)cgc_malloc(read_00668_len);
      int read_00668_res = cgc_length_read(0, read_00668, read_00668_len);
      if (read_00668_res) {} //silence unused variable warning
      cgc_free(read_00668);
      if (read_00668_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00669;
      unsigned int read_00669_len;
      unsigned int read_00669_ptr = 0;
      //**** length read
      read_00669_len = 28;
      read_00669 = (unsigned char*)cgc_malloc(read_00669_len);
      int read_00669_res = cgc_length_read(0, read_00669, read_00669_len);
      if (read_00669_res) {} //silence unused variable warning
      cgc_free(read_00669);
      if (read_00669_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00670;
      unsigned int read_00670_len;
      unsigned int read_00670_ptr = 0;
      //**** length read
      read_00670_len = 16;
      read_00670 = (unsigned char*)cgc_malloc(read_00670_len);
      int read_00670_res = cgc_length_read(0, read_00670, read_00670_len);
      if (read_00670_res) {} //silence unused variable warning
      cgc_free(read_00670);
      if (read_00670_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x58\x0a";
      static unsigned int write_00136_00000_len = 2;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      unsigned char *read_00671;
      unsigned int read_00671_len;
      unsigned int read_00671_ptr = 0;
      //**** length read
      read_00671_len = 12;
      read_00671 = (unsigned char*)cgc_malloc(read_00671_len);
      int read_00671_res = cgc_length_read(0, read_00671, read_00671_len);
      if (read_00671_res) {} //silence unused variable warning
      cgc_free(read_00671);
      if (read_00671_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00672;
      unsigned int read_00672_len;
      unsigned int read_00672_ptr = 0;
      //**** length read
      read_00672_len = 14;
      read_00672 = (unsigned char*)cgc_malloc(read_00672_len);
      int read_00672_res = cgc_length_read(0, read_00672, read_00672_len);
      if (read_00672_res) {} //silence unused variable warning
      cgc_free(read_00672);
      if (read_00672_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00673;
      unsigned int read_00673_len;
      unsigned int read_00673_ptr = 0;
      //**** length read
      read_00673_len = 17;
      read_00673 = (unsigned char*)cgc_malloc(read_00673_len);
      int read_00673_res = cgc_length_read(0, read_00673, read_00673_len);
      if (read_00673_res) {} //silence unused variable warning
      cgc_free(read_00673);
      if (read_00673_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00674;
      unsigned int read_00674_len;
      unsigned int read_00674_ptr = 0;
      //**** length read
      read_00674_len = 28;
      read_00674 = (unsigned char*)cgc_malloc(read_00674_len);
      int read_00674_res = cgc_length_read(0, read_00674, read_00674_len);
      if (read_00674_res) {} //silence unused variable warning
      cgc_free(read_00674);
      if (read_00674_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00675;
      unsigned int read_00675_len;
      unsigned int read_00675_ptr = 0;
      //**** length read
      read_00675_len = 16;
      read_00675 = (unsigned char*)cgc_malloc(read_00675_len);
      int read_00675_res = cgc_length_read(0, read_00675, read_00675_len);
      if (read_00675_res) {} //silence unused variable warning
      cgc_free(read_00675);
      if (read_00675_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x58\x0a";
      static unsigned int write_00137_00000_len = 2;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = cgc_append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         cgc_transmit_all(1, write_00137, write_00137_len);
      }
      cgc_free(write_00137);
   } while (0);
   do {
      unsigned char *read_00676;
      unsigned int read_00676_len;
      unsigned int read_00676_ptr = 0;
      //**** length read
      read_00676_len = 12;
      read_00676 = (unsigned char*)cgc_malloc(read_00676_len);
      int read_00676_res = cgc_length_read(0, read_00676, read_00676_len);
      if (read_00676_res) {} //silence unused variable warning
      cgc_free(read_00676);
      if (read_00676_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00677;
      unsigned int read_00677_len;
      unsigned int read_00677_ptr = 0;
      //**** length read
      read_00677_len = 14;
      read_00677 = (unsigned char*)cgc_malloc(read_00677_len);
      int read_00677_res = cgc_length_read(0, read_00677, read_00677_len);
      if (read_00677_res) {} //silence unused variable warning
      cgc_free(read_00677);
      if (read_00677_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00678;
      unsigned int read_00678_len;
      unsigned int read_00678_ptr = 0;
      //**** length read
      read_00678_len = 17;
      read_00678 = (unsigned char*)cgc_malloc(read_00678_len);
      int read_00678_res = cgc_length_read(0, read_00678, read_00678_len);
      if (read_00678_res) {} //silence unused variable warning
      cgc_free(read_00678);
      if (read_00678_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00679;
      unsigned int read_00679_len;
      unsigned int read_00679_ptr = 0;
      //**** length read
      read_00679_len = 28;
      read_00679 = (unsigned char*)cgc_malloc(read_00679_len);
      int read_00679_res = cgc_length_read(0, read_00679, read_00679_len);
      if (read_00679_res) {} //silence unused variable warning
      cgc_free(read_00679);
      if (read_00679_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00680;
      unsigned int read_00680_len;
      unsigned int read_00680_ptr = 0;
      //**** length read
      read_00680_len = 16;
      read_00680 = (unsigned char*)cgc_malloc(read_00680_len);
      int read_00680_res = cgc_length_read(0, read_00680, read_00680_len);
      if (read_00680_res) {} //silence unused variable warning
      cgc_free(read_00680);
      if (read_00680_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x58\x0a";
      static unsigned int write_00138_00000_len = 2;
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = cgc_append_buf(write_00138, &write_00138_len, write_00138_00000, write_00138_00000_len);
      if (write_00138_len > 0) {
         cgc_transmit_all(1, write_00138, write_00138_len);
      }
      cgc_free(write_00138);
   } while (0);
   do {
      unsigned char *read_00681;
      unsigned int read_00681_len;
      unsigned int read_00681_ptr = 0;
      //**** length read
      read_00681_len = 12;
      read_00681 = (unsigned char*)cgc_malloc(read_00681_len);
      int read_00681_res = cgc_length_read(0, read_00681, read_00681_len);
      if (read_00681_res) {} //silence unused variable warning
      cgc_free(read_00681);
      if (read_00681_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00682;
      unsigned int read_00682_len;
      unsigned int read_00682_ptr = 0;
      //**** length read
      read_00682_len = 14;
      read_00682 = (unsigned char*)cgc_malloc(read_00682_len);
      int read_00682_res = cgc_length_read(0, read_00682, read_00682_len);
      if (read_00682_res) {} //silence unused variable warning
      cgc_free(read_00682);
      if (read_00682_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00683;
      unsigned int read_00683_len;
      unsigned int read_00683_ptr = 0;
      //**** length read
      read_00683_len = 17;
      read_00683 = (unsigned char*)cgc_malloc(read_00683_len);
      int read_00683_res = cgc_length_read(0, read_00683, read_00683_len);
      if (read_00683_res) {} //silence unused variable warning
      cgc_free(read_00683);
      if (read_00683_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00684;
      unsigned int read_00684_len;
      unsigned int read_00684_ptr = 0;
      //**** length read
      read_00684_len = 28;
      read_00684 = (unsigned char*)cgc_malloc(read_00684_len);
      int read_00684_res = cgc_length_read(0, read_00684, read_00684_len);
      if (read_00684_res) {} //silence unused variable warning
      cgc_free(read_00684);
      if (read_00684_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00685;
      unsigned int read_00685_len;
      unsigned int read_00685_ptr = 0;
      //**** length read
      read_00685_len = 16;
      read_00685 = (unsigned char*)cgc_malloc(read_00685_len);
      int read_00685_res = cgc_length_read(0, read_00685, read_00685_len);
      if (read_00685_res) {} //silence unused variable warning
      cgc_free(read_00685);
      if (read_00685_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x58\x0a";
      static unsigned int write_00139_00000_len = 2;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      unsigned char *read_00686;
      unsigned int read_00686_len;
      unsigned int read_00686_ptr = 0;
      //**** length read
      read_00686_len = 12;
      read_00686 = (unsigned char*)cgc_malloc(read_00686_len);
      int read_00686_res = cgc_length_read(0, read_00686, read_00686_len);
      if (read_00686_res) {} //silence unused variable warning
      cgc_free(read_00686);
      if (read_00686_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00687;
      unsigned int read_00687_len;
      unsigned int read_00687_ptr = 0;
      //**** length read
      read_00687_len = 14;
      read_00687 = (unsigned char*)cgc_malloc(read_00687_len);
      int read_00687_res = cgc_length_read(0, read_00687, read_00687_len);
      if (read_00687_res) {} //silence unused variable warning
      cgc_free(read_00687);
      if (read_00687_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00688;
      unsigned int read_00688_len;
      unsigned int read_00688_ptr = 0;
      //**** length read
      read_00688_len = 17;
      read_00688 = (unsigned char*)cgc_malloc(read_00688_len);
      int read_00688_res = cgc_length_read(0, read_00688, read_00688_len);
      if (read_00688_res) {} //silence unused variable warning
      cgc_free(read_00688);
      if (read_00688_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00689;
      unsigned int read_00689_len;
      unsigned int read_00689_ptr = 0;
      //**** length read
      read_00689_len = 28;
      read_00689 = (unsigned char*)cgc_malloc(read_00689_len);
      int read_00689_res = cgc_length_read(0, read_00689, read_00689_len);
      if (read_00689_res) {} //silence unused variable warning
      cgc_free(read_00689);
      if (read_00689_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00690;
      unsigned int read_00690_len;
      unsigned int read_00690_ptr = 0;
      //**** length read
      read_00690_len = 16;
      read_00690 = (unsigned char*)cgc_malloc(read_00690_len);
      int read_00690_res = cgc_length_read(0, read_00690, read_00690_len);
      if (read_00690_res) {} //silence unused variable warning
      cgc_free(read_00690);
      if (read_00690_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x53\x0a";
      static unsigned int write_00140_00000_len = 2;
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = cgc_append_buf(write_00140, &write_00140_len, write_00140_00000, write_00140_00000_len);
      if (write_00140_len > 0) {
         cgc_transmit_all(1, write_00140, write_00140_len);
      }
      cgc_free(write_00140);
   } while (0);
   do {
      unsigned char *read_00691;
      unsigned int read_00691_len;
      unsigned int read_00691_ptr = 0;
      //**** length read
      read_00691_len = 1;
      read_00691 = (unsigned char*)cgc_malloc(read_00691_len);
      int read_00691_res = cgc_length_read(0, read_00691, read_00691_len);
      if (read_00691_res) {} //silence unused variable warning
      cgc_free(read_00691);
      if (read_00691_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00692;
      unsigned int read_00692_len;
      unsigned int read_00692_ptr = 0;
      //**** length read
      read_00692_len = 14;
      read_00692 = (unsigned char*)cgc_malloc(read_00692_len);
      int read_00692_res = cgc_length_read(0, read_00692, read_00692_len);
      if (read_00692_res) {} //silence unused variable warning
      cgc_free(read_00692);
      if (read_00692_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00693;
      unsigned int read_00693_len;
      unsigned int read_00693_ptr = 0;
      //**** length read
      read_00693_len = 17;
      read_00693 = (unsigned char*)cgc_malloc(read_00693_len);
      int read_00693_res = cgc_length_read(0, read_00693, read_00693_len);
      if (read_00693_res) {} //silence unused variable warning
      cgc_free(read_00693);
      if (read_00693_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00694;
      unsigned int read_00694_len;
      unsigned int read_00694_ptr = 0;
      //**** length read
      read_00694_len = 28;
      read_00694 = (unsigned char*)cgc_malloc(read_00694_len);
      int read_00694_res = cgc_length_read(0, read_00694, read_00694_len);
      if (read_00694_res) {} //silence unused variable warning
      cgc_free(read_00694);
      if (read_00694_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00695;
      unsigned int read_00695_len;
      unsigned int read_00695_ptr = 0;
      //**** length read
      read_00695_len = 28;
      read_00695 = (unsigned char*)cgc_malloc(read_00695_len);
      int read_00695_res = cgc_length_read(0, read_00695, read_00695_len);
      if (read_00695_res) {} //silence unused variable warning
      cgc_free(read_00695);
      if (read_00695_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00696;
      unsigned int read_00696_len;
      unsigned int read_00696_ptr = 0;
      //**** length read
      read_00696_len = 16;
      read_00696 = (unsigned char*)cgc_malloc(read_00696_len);
      int read_00696_res = cgc_length_read(0, read_00696, read_00696_len);
      if (read_00696_res) {} //silence unused variable warning
      cgc_free(read_00696);
      if (read_00696_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x48\x0a";
      static unsigned int write_00141_00000_len = 2;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = cgc_append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         cgc_transmit_all(1, write_00141, write_00141_len);
      }
      cgc_free(write_00141);
   } while (0);
   do {
      unsigned char *read_00697;
      unsigned int read_00697_len;
      unsigned int read_00697_ptr = 0;
      //**** length read
      read_00697_len = 1;
      read_00697 = (unsigned char*)cgc_malloc(read_00697_len);
      int read_00697_res = cgc_length_read(0, read_00697, read_00697_len);
      if (read_00697_res) {} //silence unused variable warning
      cgc_free(read_00697);
      if (read_00697_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00698;
      unsigned int read_00698_len;
      unsigned int read_00698_ptr = 0;
      //**** length read
      read_00698_len = 14;
      read_00698 = (unsigned char*)cgc_malloc(read_00698_len);
      int read_00698_res = cgc_length_read(0, read_00698, read_00698_len);
      if (read_00698_res) {} //silence unused variable warning
      cgc_free(read_00698);
      if (read_00698_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00699;
      unsigned int read_00699_len;
      unsigned int read_00699_ptr = 0;
      //**** length read
      read_00699_len = 17;
      read_00699 = (unsigned char*)cgc_malloc(read_00699_len);
      int read_00699_res = cgc_length_read(0, read_00699, read_00699_len);
      if (read_00699_res) {} //silence unused variable warning
      cgc_free(read_00699);
      if (read_00699_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00700;
      unsigned int read_00700_len;
      unsigned int read_00700_ptr = 0;
      //**** length read
      read_00700_len = 28;
      read_00700 = (unsigned char*)cgc_malloc(read_00700_len);
      int read_00700_res = cgc_length_read(0, read_00700, read_00700_len);
      if (read_00700_res) {} //silence unused variable warning
      cgc_free(read_00700);
      if (read_00700_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00701;
      unsigned int read_00701_len;
      unsigned int read_00701_ptr = 0;
      //**** length read
      read_00701_len = 30;
      read_00701 = (unsigned char*)cgc_malloc(read_00701_len);
      int read_00701_res = cgc_length_read(0, read_00701, read_00701_len);
      if (read_00701_res) {} //silence unused variable warning
      cgc_free(read_00701);
      if (read_00701_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00702;
      unsigned int read_00702_len;
      unsigned int read_00702_ptr = 0;
      //**** length read
      read_00702_len = 28;
      read_00702 = (unsigned char*)cgc_malloc(read_00702_len);
      int read_00702_res = cgc_length_read(0, read_00702, read_00702_len);
      if (read_00702_res) {} //silence unused variable warning
      cgc_free(read_00702);
      if (read_00702_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00703;
      unsigned int read_00703_len;
      unsigned int read_00703_ptr = 0;
      //**** length read
      read_00703_len = 16;
      read_00703 = (unsigned char*)cgc_malloc(read_00703_len);
      int read_00703_res = cgc_length_read(0, read_00703, read_00703_len);
      if (read_00703_res) {} //silence unused variable warning
      cgc_free(read_00703);
      if (read_00703_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x53\x0a";
      static unsigned int write_00142_00000_len = 2;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
   do {
      unsigned char *read_00704;
      unsigned int read_00704_len;
      unsigned int read_00704_ptr = 0;
      //**** length read
      read_00704_len = 1;
      read_00704 = (unsigned char*)cgc_malloc(read_00704_len);
      int read_00704_res = cgc_length_read(0, read_00704, read_00704_len);
      if (read_00704_res) {} //silence unused variable warning
      cgc_free(read_00704);
      if (read_00704_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00705;
      unsigned int read_00705_len;
      unsigned int read_00705_ptr = 0;
      //**** length read
      read_00705_len = 27;
      read_00705 = (unsigned char*)cgc_malloc(read_00705_len);
      int read_00705_res = cgc_length_read(0, read_00705, read_00705_len);
      if (read_00705_res) {} //silence unused variable warning
      cgc_free(read_00705);
      if (read_00705_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00706;
      unsigned int read_00706_len;
      unsigned int read_00706_ptr = 0;
      //**** length read
      read_00706_len = 32;
      read_00706 = (unsigned char*)cgc_malloc(read_00706_len);
      int read_00706_res = cgc_length_read(0, read_00706, read_00706_len);
      if (read_00706_res) {} //silence unused variable warning
      cgc_free(read_00706);
      if (read_00706_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00707;
      unsigned int read_00707_len;
      unsigned int read_00707_ptr = 0;
      //**** length read
      read_00707_len = 28;
      read_00707 = (unsigned char*)cgc_malloc(read_00707_len);
      int read_00707_res = cgc_length_read(0, read_00707, read_00707_len);
      if (read_00707_res) {} //silence unused variable warning
      cgc_free(read_00707);
      if (read_00707_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00708;
      unsigned int read_00708_len;
      unsigned int read_00708_ptr = 0;
      //**** length read
      read_00708_len = 10;
      read_00708 = (unsigned char*)cgc_malloc(read_00708_len);
      int read_00708_res = cgc_length_read(0, read_00708, read_00708_len);
      if (read_00708_res) {} //silence unused variable warning
      cgc_free(read_00708);
      if (read_00708_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00709;
      unsigned int read_00709_len;
      unsigned int read_00709_ptr = 0;
      //**** length read
      read_00709_len = 30;
      read_00709 = (unsigned char*)cgc_malloc(read_00709_len);
      int read_00709_res = cgc_length_read(0, read_00709, read_00709_len);
      if (read_00709_res) {} //silence unused variable warning
      cgc_free(read_00709);
      if (read_00709_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00710;
      unsigned int read_00710_len;
      unsigned int read_00710_ptr = 0;
      //**** length read
      read_00710_len = 32;
      read_00710 = (unsigned char*)cgc_malloc(read_00710_len);
      int read_00710_res = cgc_length_read(0, read_00710, read_00710_len);
      if (read_00710_res) {} //silence unused variable warning
      cgc_free(read_00710);
      if (read_00710_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00711;
      unsigned int read_00711_len;
      unsigned int read_00711_ptr = 0;
      //**** length read
      read_00711_len = 28;
      read_00711 = (unsigned char*)cgc_malloc(read_00711_len);
      int read_00711_res = cgc_length_read(0, read_00711, read_00711_len);
      if (read_00711_res) {} //silence unused variable warning
      cgc_free(read_00711);
      if (read_00711_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00712;
      unsigned int read_00712_len;
      unsigned int read_00712_ptr = 0;
      //**** length read
      read_00712_len = 10;
      read_00712 = (unsigned char*)cgc_malloc(read_00712_len);
      int read_00712_res = cgc_length_read(0, read_00712, read_00712_len);
      if (read_00712_res) {} //silence unused variable warning
      cgc_free(read_00712);
      if (read_00712_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00713;
      unsigned int read_00713_len;
      unsigned int read_00713_ptr = 0;
      //**** length read
      read_00713_len = 21;
      read_00713 = (unsigned char*)cgc_malloc(read_00713_len);
      int read_00713_res = cgc_length_read(0, read_00713, read_00713_len);
      if (read_00713_res) {} //silence unused variable warning
      cgc_free(read_00713);
      if (read_00713_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00714;
      unsigned int read_00714_len;
      unsigned int read_00714_ptr = 0;
      //**** length read
      read_00714_len = 64;
      read_00714 = (unsigned char*)cgc_malloc(read_00714_len);
      int read_00714_res = cgc_length_read(0, read_00714, read_00714_len);
      if (read_00714_res) {} //silence unused variable warning
      cgc_free(read_00714);
      if (read_00714_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x51\x55\x49\x54\x0a";
      static unsigned int write_00143_00000_len = 5;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = cgc_append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         cgc_transmit_all(1, write_00143, write_00143_len);
      }
      cgc_free(write_00143);
   } while (0);
   do {
      unsigned char *read_00715;
      unsigned int read_00715_len;
      unsigned int read_00715_ptr = 0;
      //**** length read
      read_00715_len = 59;
      read_00715 = (unsigned char*)cgc_malloc(read_00715_len);
      int read_00715_res = cgc_length_read(0, read_00715, read_00715_len);
      if (read_00715_res) {} //silence unused variable warning
      cgc_free(read_00715);
      if (read_00715_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x32\x0a";
      static unsigned int write_00144_00000_len = 2;
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = cgc_append_buf(write_00144, &write_00144_len, write_00144_00000, write_00144_00000_len);
      if (write_00144_len > 0) {
         cgc_transmit_all(1, write_00144, write_00144_len);
      }
      cgc_free(write_00144);
   } while (0);
   do {
      unsigned char *read_00716;
      unsigned int read_00716_len;
      unsigned int read_00716_ptr = 0;
      //**** length read
      read_00716_len = 20;
      read_00716 = (unsigned char*)cgc_malloc(read_00716_len);
      int read_00716_res = cgc_length_read(0, read_00716, read_00716_len);
      if (read_00716_res) {} //silence unused variable warning
      cgc_free(read_00716);
      if (read_00716_ptr) {}  //silence unused variable warning if any
   } while (0);
}
