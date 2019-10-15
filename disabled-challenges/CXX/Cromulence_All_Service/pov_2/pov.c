#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x3a\x20";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 2);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x6d\x61\x74\x72\x69\x78\x0a";
      static unsigned int write_00000_00000_len = 7;
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
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 1);
      if (read_00002_res) {} //silence unused variable warning
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
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
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 1);
      if (read_00005_res) {} //silence unused variable warning
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x3a\x20";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 2);
      if (read_00006_res) {} //silence unused variable warning
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x33\x0a";
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
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x0a";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = cgc_delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 1);
      if (read_00007_res) {} //silence unused variable warning
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x3a\x20";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 2);
      if (read_00008_res) {} //silence unused variable warning
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00002_00000_len = 3;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x3a\x20";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 2);
      if (read_00009_res) {} //silence unused variable warning
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00003_00000_len = 3;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
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
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** delimited read
      static unsigned char read_00011_delim[] = 
         "\x3a\x20";
      read_00011 = NULL;
      read_00011_len = 0;
      int read_00011_res = cgc_delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 2);
      if (read_00011_res) {} //silence unused variable warning
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x36\x37\x37\x0a";
      static unsigned int write_00004_00000_len = 4;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x3a\x20";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 2);
      if (read_00012_res) {} //silence unused variable warning
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x36\x34\x33\x0a";
      static unsigned int write_00005_00000_len = 4;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** delimited read
      static unsigned char read_00013_delim[] = 
         "\x3a\x20";
      read_00013 = NULL;
      read_00013_len = 0;
      int read_00013_res = cgc_delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 2);
      if (read_00013_res) {} //silence unused variable warning
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x37\x35\x39\x0a";
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
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** delimited read
      static unsigned char read_00014_delim[] = 
         "\x3a\x20";
      read_00014 = NULL;
      read_00014_len = 0;
      int read_00014_res = cgc_delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 2);
      if (read_00014_res) {} //silence unused variable warning
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x38\x36\x31\x0a";
      static unsigned int write_00007_00000_len = 4;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x3a\x20";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = cgc_delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 2);
      if (read_00015_res) {} //silence unused variable warning
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x35\x31\x0a";
      static unsigned int write_00008_00000_len = 3;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** delimited read
      static unsigned char read_00016_delim[] = 
         "\x3a\x20";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = cgc_delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 2);
      if (read_00016_res) {} //silence unused variable warning
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x31\x39\x35\x0a";
      static unsigned int write_00009_00000_len = 4;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** delimited read
      static unsigned char read_00017_delim[] = 
         "\x3a\x20";
      read_00017 = NULL;
      read_00017_len = 0;
      int read_00017_res = cgc_delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 2);
      if (read_00017_res) {} //silence unused variable warning
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x34\x36\x0a";
      static unsigned int write_00010_00000_len = 3;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** delimited read
      static unsigned char read_00018_delim[] = 
         "\x3a\x20";
      read_00018 = NULL;
      read_00018_len = 0;
      int read_00018_res = cgc_delimited_read(0, &read_00018, &read_00018_len, read_00018_delim, 2);
      if (read_00018_res) {} //silence unused variable warning
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x36\x38\x32\x0a";
      static unsigned int write_00011_00000_len = 4;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** delimited read
      static unsigned char read_00019_delim[] = 
         "\x3a\x20";
      read_00019 = NULL;
      read_00019_len = 0;
      int read_00019_res = cgc_delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 2);
      if (read_00019_res) {} //silence unused variable warning
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x39\x31\x38\x0a";
      static unsigned int write_00012_00000_len = 4;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** delimited read
      static unsigned char read_00020_delim[] = 
         "\x3a\x20";
      read_00020 = NULL;
      read_00020_len = 0;
      int read_00020_res = cgc_delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 2);
      if (read_00020_res) {} //silence unused variable warning
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x33\x35\x38\x0a";
      static unsigned int write_00013_00000_len = 4;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x3a\x20";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = cgc_delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 2);
      if (read_00021_res) {} //silence unused variable warning
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x31\x36\x32\x0a";
      static unsigned int write_00014_00000_len = 4;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** delimited read
      static unsigned char read_00022_delim[] = 
         "\x3a\x20";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = cgc_delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 2);
      if (read_00022_res) {} //silence unused variable warning
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x34\x30\x30\x0a";
      static unsigned int write_00015_00000_len = 4;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** delimited read
      static unsigned char read_00023_delim[] = 
         "\x3a\x20";
      read_00023 = NULL;
      read_00023_len = 0;
      int read_00023_res = cgc_delimited_read(0, &read_00023, &read_00023_len, read_00023_delim, 2);
      if (read_00023_res) {} //silence unused variable warning
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x36\x37\x32\x0a";
      static unsigned int write_00016_00000_len = 4;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** delimited read
      static unsigned char read_00024_delim[] = 
         "\x3a\x20";
      read_00024 = NULL;
      read_00024_len = 0;
      int read_00024_res = cgc_delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 2);
      if (read_00024_res) {} //silence unused variable warning
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x35\x33\x33\x0a";
      static unsigned int write_00017_00000_len = 4;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** delimited read
      static unsigned char read_00025_delim[] = 
         "\x3a\x20";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = cgc_delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 2);
      if (read_00025_res) {} //silence unused variable warning
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x32\x30\x34\x0a";
      static unsigned int write_00018_00000_len = 4;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** delimited read
      static unsigned char read_00026_delim[] = 
         "\x3a\x20";
      read_00026 = NULL;
      read_00026_len = 0;
      int read_00026_res = cgc_delimited_read(0, &read_00026, &read_00026_len, read_00026_delim, 2);
      if (read_00026_res) {} //silence unused variable warning
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00019_00000_len = 3;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** delimited read
      static unsigned char read_00027_delim[] = 
         "\x3a\x20";
      read_00027 = NULL;
      read_00027_len = 0;
      int read_00027_res = cgc_delimited_read(0, &read_00027, &read_00027_len, read_00027_delim, 2);
      if (read_00027_res) {} //silence unused variable warning
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x38\x39\x33\x0a";
      static unsigned int write_00020_00000_len = 4;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** delimited read
      static unsigned char read_00028_delim[] = 
         "\x3a\x20";
      read_00028 = NULL;
      read_00028_len = 0;
      int read_00028_res = cgc_delimited_read(0, &read_00028, &read_00028_len, read_00028_delim, 2);
      if (read_00028_res) {} //silence unused variable warning
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x33\x38\x30\x0a";
      static unsigned int write_00021_00000_len = 4;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** delimited read
      static unsigned char read_00029_delim[] = 
         "\x3a\x20";
      read_00029 = NULL;
      read_00029_len = 0;
      int read_00029_res = cgc_delimited_read(0, &read_00029, &read_00029_len, read_00029_delim, 2);
      if (read_00029_res) {} //silence unused variable warning
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x39\x36\x34\x0a";
      static unsigned int write_00022_00000_len = 4;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** delimited read
      static unsigned char read_00030_delim[] = 
         "\x3a\x20";
      read_00030 = NULL;
      read_00030_len = 0;
      int read_00030_res = cgc_delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 2);
      if (read_00030_res) {} //silence unused variable warning
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x31\x30\x35\x0a";
      static unsigned int write_00023_00000_len = 4;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** delimited read
      static unsigned char read_00031_delim[] = 
         "\x3a\x20";
      read_00031 = NULL;
      read_00031_len = 0;
      int read_00031_res = cgc_delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 2);
      if (read_00031_res) {} //silence unused variable warning
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x36\x38\x37\x0a";
      static unsigned int write_00024_00000_len = 4;
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** delimited read
      static unsigned char read_00032_delim[] = 
         "\x3a\x20";
      read_00032 = NULL;
      read_00032_len = 0;
      int read_00032_res = cgc_delimited_read(0, &read_00032, &read_00032_len, read_00032_delim, 2);
      if (read_00032_res) {} //silence unused variable warning
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x39\x37\x36\x0a";
      static unsigned int write_00025_00000_len = 4;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** delimited read
      static unsigned char read_00033_delim[] = 
         "\x3a\x20";
      read_00033 = NULL;
      read_00033_len = 0;
      int read_00033_res = cgc_delimited_read(0, &read_00033, &read_00033_len, read_00033_delim, 2);
      if (read_00033_res) {} //silence unused variable warning
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x34\x36\x35\x0a";
      static unsigned int write_00026_00000_len = 4;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** delimited read
      static unsigned char read_00034_delim[] = 
         "\x3a\x20";
      read_00034 = NULL;
      read_00034_len = 0;
      int read_00034_res = cgc_delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 2);
      if (read_00034_res) {} //silence unused variable warning
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x38\x38\x32\x0a";
      static unsigned int write_00027_00000_len = 4;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** delimited read
      static unsigned char read_00035_delim[] = 
         "\x3a\x20";
      read_00035 = NULL;
      read_00035_len = 0;
      int read_00035_res = cgc_delimited_read(0, &read_00035, &read_00035_len, read_00035_delim, 2);
      if (read_00035_res) {} //silence unused variable warning
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x37\x32\x31\x0a";
      static unsigned int write_00028_00000_len = 4;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** delimited read
      static unsigned char read_00036_delim[] = 
         "\x3a\x20";
      read_00036 = NULL;
      read_00036_len = 0;
      int read_00036_res = cgc_delimited_read(0, &read_00036, &read_00036_len, read_00036_delim, 2);
      if (read_00036_res) {} //silence unused variable warning
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x34\x35\x38\x0a";
      static unsigned int write_00029_00000_len = 4;
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = cgc_append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
      if (write_00029_len > 0) {
         cgc_transmit_all(1, write_00029, write_00029_len);
      }
      cgc_free(write_00029);
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** delimited read
      static unsigned char read_00037_delim[] = 
         "\x3a\x20";
      read_00037 = NULL;
      read_00037_len = 0;
      int read_00037_res = cgc_delimited_read(0, &read_00037, &read_00037_len, read_00037_delim, 2);
      if (read_00037_res) {} //silence unused variable warning
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x32\x33\x39\x0a";
      static unsigned int write_00030_00000_len = 4;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** delimited read
      static unsigned char read_00038_delim[] = 
         "\x3a\x20";
      read_00038 = NULL;
      read_00038_len = 0;
      int read_00038_res = cgc_delimited_read(0, &read_00038, &read_00038_len, read_00038_delim, 2);
      if (read_00038_res) {} //silence unused variable warning
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x33\x36\x32\x0a";
      static unsigned int write_00031_00000_len = 4;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** delimited read
      static unsigned char read_00039_delim[] = 
         "\x3a\x20";
      read_00039 = NULL;
      read_00039_len = 0;
      int read_00039_res = cgc_delimited_read(0, &read_00039, &read_00039_len, read_00039_delim, 2);
      if (read_00039_res) {} //silence unused variable warning
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x31\x32\x39\x0a";
      static unsigned int write_00032_00000_len = 4;
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** delimited read
      static unsigned char read_00040_delim[] = 
         "\x3a\x20";
      read_00040 = NULL;
      read_00040_len = 0;
      int read_00040_res = cgc_delimited_read(0, &read_00040, &read_00040_len, read_00040_delim, 2);
      if (read_00040_res) {} //silence unused variable warning
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x31\x38\x37\x0a";
      static unsigned int write_00033_00000_len = 4;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** delimited read
      static unsigned char read_00041_delim[] = 
         "\x3a\x20";
      read_00041 = NULL;
      read_00041_len = 0;
      int read_00041_res = cgc_delimited_read(0, &read_00041, &read_00041_len, read_00041_delim, 2);
      if (read_00041_res) {} //silence unused variable warning
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x39\x33\x0a";
      static unsigned int write_00034_00000_len = 3;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** delimited read
      static unsigned char read_00042_delim[] = 
         "\x3a\x20";
      read_00042 = NULL;
      read_00042_len = 0;
      int read_00042_res = cgc_delimited_read(0, &read_00042, &read_00042_len, read_00042_delim, 2);
      if (read_00042_res) {} //silence unused variable warning
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x33\x35\x39\x0a";
      static unsigned int write_00035_00000_len = 4;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** delimited read
      static unsigned char read_00043_delim[] = 
         "\x3a\x20";
      read_00043 = NULL;
      read_00043_len = 0;
      int read_00043_res = cgc_delimited_read(0, &read_00043, &read_00043_len, read_00043_delim, 2);
      if (read_00043_res) {} //silence unused variable warning
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x37\x33\x31\x0a";
      static unsigned int write_00036_00000_len = 4;
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_buf(write_00036, &write_00036_len, write_00036_00000, write_00036_00000_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** delimited read
      static unsigned char read_00044_delim[] = 
         "\x3a\x20";
      read_00044 = NULL;
      read_00044_len = 0;
      int read_00044_res = cgc_delimited_read(0, &read_00044, &read_00044_len, read_00044_delim, 2);
      if (read_00044_res) {} //silence unused variable warning
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x38\x32\x37\x0a";
      static unsigned int write_00037_00000_len = 4;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** delimited read
      static unsigned char read_00045_delim[] = 
         "\x3a\x20";
      read_00045 = NULL;
      read_00045_len = 0;
      int read_00045_res = cgc_delimited_read(0, &read_00045, &read_00045_len, read_00045_delim, 2);
      if (read_00045_res) {} //silence unused variable warning
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x38\x37\x35\x0a";
      static unsigned int write_00038_00000_len = 4;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** delimited read
      static unsigned char read_00046_delim[] = 
         "\x3a\x20";
      read_00046 = NULL;
      read_00046_len = 0;
      int read_00046_res = cgc_delimited_read(0, &read_00046, &read_00046_len, read_00046_delim, 2);
      if (read_00046_res) {} //silence unused variable warning
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x36\x34\x35\x0a";
      static unsigned int write_00039_00000_len = 4;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** delimited read
      static unsigned char read_00047_delim[] = 
         "\x3a\x20";
      read_00047 = NULL;
      read_00047_len = 0;
      int read_00047_res = cgc_delimited_read(0, &read_00047, &read_00047_len, read_00047_delim, 2);
      if (read_00047_res) {} //silence unused variable warning
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x31\x35\x34\x0a";
      static unsigned int write_00040_00000_len = 4;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** delimited read
      static unsigned char read_00048_delim[] = 
         "\x3a\x20";
      read_00048 = NULL;
      read_00048_len = 0;
      int read_00048_res = cgc_delimited_read(0, &read_00048, &read_00048_len, read_00048_delim, 2);
      if (read_00048_res) {} //silence unused variable warning
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x33\x37\x0a";
      static unsigned int write_00041_00000_len = 3;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** delimited read
      static unsigned char read_00049_delim[] = 
         "\x3a\x20";
      read_00049 = NULL;
      read_00049_len = 0;
      int read_00049_res = cgc_delimited_read(0, &read_00049, &read_00049_len, read_00049_delim, 2);
      if (read_00049_res) {} //silence unused variable warning
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x32\x32\x31\x0a";
      static unsigned int write_00042_00000_len = 4;
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_buf(write_00042, &write_00042_len, write_00042_00000, write_00042_00000_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** delimited read
      static unsigned char read_00050_delim[] = 
         "\x3a\x20";
      read_00050 = NULL;
      read_00050_len = 0;
      int read_00050_res = cgc_delimited_read(0, &read_00050, &read_00050_len, read_00050_delim, 2);
      if (read_00050_res) {} //silence unused variable warning
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x35\x39\x36\x0a";
      static unsigned int write_00043_00000_len = 4;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** delimited read
      static unsigned char read_00051_delim[] = 
         "\x3a\x20";
      read_00051 = NULL;
      read_00051_len = 0;
      int read_00051_res = cgc_delimited_read(0, &read_00051, &read_00051_len, read_00051_delim, 2);
      if (read_00051_res) {} //silence unused variable warning
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x37\x32\x31\x0a";
      static unsigned int write_00044_00000_len = 4;
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_buf(write_00044, &write_00044_len, write_00044_00000, write_00044_00000_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** delimited read
      static unsigned char read_00052_delim[] = 
         "\x3a\x20";
      read_00052 = NULL;
      read_00052_len = 0;
      int read_00052_res = cgc_delimited_read(0, &read_00052, &read_00052_len, read_00052_delim, 2);
      if (read_00052_res) {} //silence unused variable warning
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x33\x39\x32\x0a";
      static unsigned int write_00045_00000_len = 4;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** delimited read
      static unsigned char read_00053_delim[] = 
         "\x3a\x20";
      read_00053 = NULL;
      read_00053_len = 0;
      int read_00053_res = cgc_delimited_read(0, &read_00053, &read_00053_len, read_00053_delim, 2);
      if (read_00053_res) {} //silence unused variable warning
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x31\x36\x31\x0a";
      static unsigned int write_00046_00000_len = 4;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      unsigned char *read_00054;
      unsigned int read_00054_len;
      unsigned int read_00054_ptr = 0;
      //**** delimited read
      static unsigned char read_00054_delim[] = 
         "\x3a\x20";
      read_00054 = NULL;
      read_00054_len = 0;
      int read_00054_res = cgc_delimited_read(0, &read_00054, &read_00054_len, read_00054_delim, 2);
      if (read_00054_res) {} //silence unused variable warning
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x31\x36\x36\x0a";
      static unsigned int write_00047_00000_len = 4;
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = cgc_append_buf(write_00047, &write_00047_len, write_00047_00000, write_00047_00000_len);
      if (write_00047_len > 0) {
         cgc_transmit_all(1, write_00047, write_00047_len);
      }
      cgc_free(write_00047);
   } while (0);
   do {
      unsigned char *read_00055;
      unsigned int read_00055_len;
      unsigned int read_00055_ptr = 0;
      //**** delimited read
      static unsigned char read_00055_delim[] = 
         "\x3a\x20";
      read_00055 = NULL;
      read_00055_len = 0;
      int read_00055_res = cgc_delimited_read(0, &read_00055, &read_00055_len, read_00055_delim, 2);
      if (read_00055_res) {} //silence unused variable warning
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x32\x37\x0a";
      static unsigned int write_00048_00000_len = 3;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** delimited read
      static unsigned char read_00056_delim[] = 
         "\x3a\x20";
      read_00056 = NULL;
      read_00056_len = 0;
      int read_00056_res = cgc_delimited_read(0, &read_00056, &read_00056_len, read_00056_delim, 2);
      if (read_00056_res) {} //silence unused variable warning
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x35\x38\x32\x0a";
      static unsigned int write_00049_00000_len = 4;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      unsigned char *read_00057;
      unsigned int read_00057_len;
      unsigned int read_00057_ptr = 0;
      //**** delimited read
      static unsigned char read_00057_delim[] = 
         "\x3a\x20";
      read_00057 = NULL;
      read_00057_len = 0;
      int read_00057_res = cgc_delimited_read(0, &read_00057, &read_00057_len, read_00057_delim, 2);
      if (read_00057_res) {} //silence unused variable warning
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x38\x31\x31\x0a";
      static unsigned int write_00050_00000_len = 4;
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_buf(write_00050, &write_00050_len, write_00050_00000, write_00050_00000_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      unsigned char *read_00058;
      unsigned int read_00058_len;
      unsigned int read_00058_ptr = 0;
      //**** delimited read
      static unsigned char read_00058_delim[] = 
         "\x3a\x20";
      read_00058 = NULL;
      read_00058_len = 0;
      int read_00058_res = cgc_delimited_read(0, &read_00058, &read_00058_len, read_00058_delim, 2);
      if (read_00058_res) {} //silence unused variable warning
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x34\x38\x38\x0a";
      static unsigned int write_00051_00000_len = 4;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      unsigned char *read_00059;
      unsigned int read_00059_len;
      unsigned int read_00059_ptr = 0;
      //**** delimited read
      static unsigned char read_00059_delim[] = 
         "\x3a\x20";
      read_00059 = NULL;
      read_00059_len = 0;
      int read_00059_res = cgc_delimited_read(0, &read_00059, &read_00059_len, read_00059_delim, 2);
      if (read_00059_res) {} //silence unused variable warning
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x39\x35\x0a";
      static unsigned int write_00052_00000_len = 3;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      unsigned char *read_00060;
      unsigned int read_00060_len;
      unsigned int read_00060_ptr = 0;
      //**** delimited read
      static unsigned char read_00060_delim[] = 
         "\x3a\x20";
      read_00060 = NULL;
      read_00060_len = 0;
      int read_00060_res = cgc_delimited_read(0, &read_00060, &read_00060_len, read_00060_delim, 2);
      if (read_00060_res) {} //silence unused variable warning
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x33\x33\x36\x0a";
      static unsigned int write_00053_00000_len = 4;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      unsigned char *read_00061;
      unsigned int read_00061_len;
      unsigned int read_00061_ptr = 0;
      //**** delimited read
      static unsigned char read_00061_delim[] = 
         "\x3a\x20";
      read_00061 = NULL;
      read_00061_len = 0;
      int read_00061_res = cgc_delimited_read(0, &read_00061, &read_00061_len, read_00061_delim, 2);
      if (read_00061_res) {} //silence unused variable warning
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x37\x32\x38\x0a";
      static unsigned int write_00054_00000_len = 4;
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_buf(write_00054, &write_00054_len, write_00054_00000, write_00054_00000_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      unsigned char *read_00062;
      unsigned int read_00062_len;
      unsigned int read_00062_ptr = 0;
      //**** delimited read
      static unsigned char read_00062_delim[] = 
         "\x3a\x20";
      read_00062 = NULL;
      read_00062_len = 0;
      int read_00062_res = cgc_delimited_read(0, &read_00062, &read_00062_len, read_00062_delim, 2);
      if (read_00062_res) {} //silence unused variable warning
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x37\x35\x38\x0a";
      static unsigned int write_00055_00000_len = 4;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      unsigned char *read_00063;
      unsigned int read_00063_len;
      unsigned int read_00063_ptr = 0;
      //**** delimited read
      static unsigned char read_00063_delim[] = 
         "\x3a\x20";
      read_00063 = NULL;
      read_00063_len = 0;
      int read_00063_res = cgc_delimited_read(0, &read_00063, &read_00063_len, read_00063_delim, 2);
      if (read_00063_res) {} //silence unused variable warning
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x35\x34\x36\x0a";
      static unsigned int write_00056_00000_len = 4;
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_buf(write_00056, &write_00056_len, write_00056_00000, write_00056_00000_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      unsigned char *read_00064;
      unsigned int read_00064_len;
      unsigned int read_00064_ptr = 0;
      //**** delimited read
      static unsigned char read_00064_delim[] = 
         "\x3a\x20";
      read_00064 = NULL;
      read_00064_len = 0;
      int read_00064_res = cgc_delimited_read(0, &read_00064, &read_00064_len, read_00064_delim, 2);
      if (read_00064_res) {} //silence unused variable warning
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x39\x38\x36\x0a";
      static unsigned int write_00057_00000_len = 4;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      unsigned char *read_00065;
      unsigned int read_00065_len;
      unsigned int read_00065_ptr = 0;
      //**** delimited read
      static unsigned char read_00065_delim[] = 
         "\x3a\x20";
      read_00065 = NULL;
      read_00065_len = 0;
      int read_00065_res = cgc_delimited_read(0, &read_00065, &read_00065_len, read_00065_delim, 2);
      if (read_00065_res) {} //silence unused variable warning
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x36\x37\x32\x0a";
      static unsigned int write_00058_00000_len = 4;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      unsigned char *read_00066;
      unsigned int read_00066_len;
      unsigned int read_00066_ptr = 0;
      //**** delimited read
      static unsigned char read_00066_delim[] = 
         "\x3a\x20";
      read_00066 = NULL;
      read_00066_len = 0;
      int read_00066_res = cgc_delimited_read(0, &read_00066, &read_00066_len, read_00066_delim, 2);
      if (read_00066_res) {} //silence unused variable warning
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x31\x32\x36\x0a";
      static unsigned int write_00059_00000_len = 4;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      unsigned char *read_00067;
      unsigned int read_00067_len;
      unsigned int read_00067_ptr = 0;
      //**** delimited read
      static unsigned char read_00067_delim[] = 
         "\x3a\x20";
      read_00067 = NULL;
      read_00067_len = 0;
      int read_00067_res = cgc_delimited_read(0, &read_00067, &read_00067_len, read_00067_delim, 2);
      if (read_00067_res) {} //silence unused variable warning
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x34\x35\x37\x0a";
      static unsigned int write_00060_00000_len = 4;
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_buf(write_00060, &write_00060_len, write_00060_00000, write_00060_00000_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      unsigned char *read_00068;
      unsigned int read_00068_len;
      unsigned int read_00068_ptr = 0;
      //**** delimited read
      static unsigned char read_00068_delim[] = 
         "\x3a\x20";
      read_00068 = NULL;
      read_00068_len = 0;
      int read_00068_res = cgc_delimited_read(0, &read_00068, &read_00068_len, read_00068_delim, 2);
      if (read_00068_res) {} //silence unused variable warning
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x39\x30\x34\x0a";
      static unsigned int write_00061_00000_len = 4;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      unsigned char *read_00069;
      unsigned int read_00069_len;
      unsigned int read_00069_ptr = 0;
      //**** delimited read
      static unsigned char read_00069_delim[] = 
         "\x3a\x20";
      read_00069 = NULL;
      read_00069_len = 0;
      int read_00069_res = cgc_delimited_read(0, &read_00069, &read_00069_len, read_00069_delim, 2);
      if (read_00069_res) {} //silence unused variable warning
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x32\x39\x32\x0a";
      static unsigned int write_00062_00000_len = 4;
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_buf(write_00062, &write_00062_len, write_00062_00000, write_00062_00000_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      unsigned char *read_00070;
      unsigned int read_00070_len;
      unsigned int read_00070_ptr = 0;
      //**** delimited read
      static unsigned char read_00070_delim[] = 
         "\x3a\x20";
      read_00070 = NULL;
      read_00070_len = 0;
      int read_00070_res = cgc_delimited_read(0, &read_00070, &read_00070_len, read_00070_delim, 2);
      if (read_00070_res) {} //silence unused variable warning
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x38\x31\x35\x0a";
      static unsigned int write_00063_00000_len = 4;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      unsigned char *read_00071;
      unsigned int read_00071_len;
      unsigned int read_00071_ptr = 0;
      //**** delimited read
      static unsigned char read_00071_delim[] = 
         "\x3a\x20";
      read_00071 = NULL;
      read_00071_len = 0;
      int read_00071_res = cgc_delimited_read(0, &read_00071, &read_00071_len, read_00071_delim, 2);
      if (read_00071_res) {} //silence unused variable warning
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x35\x37\x38\x0a";
      static unsigned int write_00064_00000_len = 4;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      unsigned char *read_00072;
      unsigned int read_00072_len;
      unsigned int read_00072_ptr = 0;
      //**** delimited read
      static unsigned char read_00072_delim[] = 
         "\x3a\x20";
      read_00072 = NULL;
      read_00072_len = 0;
      int read_00072_res = cgc_delimited_read(0, &read_00072, &read_00072_len, read_00072_delim, 2);
      if (read_00072_res) {} //silence unused variable warning
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x37\x37\x30\x0a";
      static unsigned int write_00065_00000_len = 4;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      unsigned char *read_00073;
      unsigned int read_00073_len;
      unsigned int read_00073_ptr = 0;
      //**** delimited read
      static unsigned char read_00073_delim[] = 
         "\x3a\x20";
      read_00073 = NULL;
      read_00073_len = 0;
      int read_00073_res = cgc_delimited_read(0, &read_00073, &read_00073_len, read_00073_delim, 2);
      if (read_00073_res) {} //silence unused variable warning
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x31\x31\x35\x0a";
      static unsigned int write_00066_00000_len = 4;
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_buf(write_00066, &write_00066_len, write_00066_00000, write_00066_00000_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      unsigned char *read_00074;
      unsigned int read_00074_len;
      unsigned int read_00074_ptr = 0;
      //**** delimited read
      static unsigned char read_00074_delim[] = 
         "\x3a\x20";
      read_00074 = NULL;
      read_00074_len = 0;
      int read_00074_res = cgc_delimited_read(0, &read_00074, &read_00074_len, read_00074_delim, 2);
      if (read_00074_res) {} //silence unused variable warning
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x39\x31\x39\x0a";
      static unsigned int write_00067_00000_len = 4;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      unsigned char *read_00075;
      unsigned int read_00075_len;
      unsigned int read_00075_ptr = 0;
      //**** delimited read
      static unsigned char read_00075_delim[] = 
         "\x3a\x20";
      read_00075 = NULL;
      read_00075_len = 0;
      int read_00075_res = cgc_delimited_read(0, &read_00075, &read_00075_len, read_00075_delim, 2);
      if (read_00075_res) {} //silence unused variable warning
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x38\x36\x33\x0a";
      static unsigned int write_00068_00000_len = 4;
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = cgc_append_buf(write_00068, &write_00068_len, write_00068_00000, write_00068_00000_len);
      if (write_00068_len > 0) {
         cgc_transmit_all(1, write_00068, write_00068_len);
      }
      cgc_free(write_00068);
   } while (0);
   do {
      unsigned char *read_00076;
      unsigned int read_00076_len;
      unsigned int read_00076_ptr = 0;
      //**** delimited read
      static unsigned char read_00076_delim[] = 
         "\x3a\x20";
      read_00076 = NULL;
      read_00076_len = 0;
      int read_00076_res = cgc_delimited_read(0, &read_00076, &read_00076_len, read_00076_delim, 2);
      if (read_00076_res) {} //silence unused variable warning
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x31\x39\x38\x0a";
      static unsigned int write_00069_00000_len = 4;
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = cgc_append_buf(write_00069, &write_00069_len, write_00069_00000, write_00069_00000_len);
      if (write_00069_len > 0) {
         cgc_transmit_all(1, write_00069, write_00069_len);
      }
      cgc_free(write_00069);
   } while (0);
   do {
      unsigned char *read_00077;
      unsigned int read_00077_len;
      unsigned int read_00077_ptr = 0;
      //**** delimited read
      static unsigned char read_00077_delim[] = 
         "\x3a\x20";
      read_00077 = NULL;
      read_00077_len = 0;
      int read_00077_res = cgc_delimited_read(0, &read_00077, &read_00077_len, read_00077_delim, 2);
      if (read_00077_res) {} //silence unused variable warning
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x32\x35\x0a";
      static unsigned int write_00070_00000_len = 3;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      unsigned char *read_00078;
      unsigned int read_00078_len;
      unsigned int read_00078_ptr = 0;
      //**** delimited read
      static unsigned char read_00078_delim[] = 
         "\x3a\x20";
      read_00078 = NULL;
      read_00078_len = 0;
      int read_00078_res = cgc_delimited_read(0, &read_00078, &read_00078_len, read_00078_delim, 2);
      if (read_00078_res) {} //silence unused variable warning
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x33\x37\x36\x0a";
      static unsigned int write_00071_00000_len = 4;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      unsigned char *read_00079;
      unsigned int read_00079_len;
      unsigned int read_00079_ptr = 0;
      //**** delimited read
      static unsigned char read_00079_delim[] = 
         "\x3a\x20";
      read_00079 = NULL;
      read_00079_len = 0;
      int read_00079_res = cgc_delimited_read(0, &read_00079, &read_00079_len, read_00079_delim, 2);
      if (read_00079_res) {} //silence unused variable warning
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x35\x36\x38\x0a";
      static unsigned int write_00072_00000_len = 4;
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_buf(write_00072, &write_00072_len, write_00072_00000, write_00072_00000_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      unsigned char *read_00080;
      unsigned int read_00080_len;
      unsigned int read_00080_ptr = 0;
      //**** delimited read
      static unsigned char read_00080_delim[] = 
         "\x3a\x20";
      read_00080 = NULL;
      read_00080_len = 0;
      int read_00080_res = cgc_delimited_read(0, &read_00080, &read_00080_len, read_00080_delim, 2);
      if (read_00080_res) {} //silence unused variable warning
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x36\x39\x33\x0a";
      static unsigned int write_00073_00000_len = 4;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      unsigned char *read_00081;
      unsigned int read_00081_len;
      unsigned int read_00081_ptr = 0;
      //**** delimited read
      static unsigned char read_00081_delim[] = 
         "\x3a\x20";
      read_00081 = NULL;
      read_00081_len = 0;
      int read_00081_res = cgc_delimited_read(0, &read_00081, &read_00081_len, read_00081_delim, 2);
      if (read_00081_res) {} //silence unused variable warning
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x33\x35\x33\x0a";
      static unsigned int write_00074_00000_len = 4;
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_buf(write_00074, &write_00074_len, write_00074_00000, write_00074_00000_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      unsigned char *read_00082;
      unsigned int read_00082_len;
      unsigned int read_00082_ptr = 0;
      //**** delimited read
      static unsigned char read_00082_delim[] = 
         "\x3a\x20";
      read_00082 = NULL;
      read_00082_len = 0;
      int read_00082_res = cgc_delimited_read(0, &read_00082, &read_00082_len, read_00082_delim, 2);
      if (read_00082_res) {} //silence unused variable warning
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x36\x33\x34\x0a";
      static unsigned int write_00075_00000_len = 4;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      unsigned char *read_00083;
      unsigned int read_00083_len;
      unsigned int read_00083_ptr = 0;
      //**** delimited read
      static unsigned char read_00083_delim[] = 
         "\x3a\x20";
      read_00083 = NULL;
      read_00083_len = 0;
      int read_00083_res = cgc_delimited_read(0, &read_00083, &read_00083_len, read_00083_delim, 2);
      if (read_00083_res) {} //silence unused variable warning
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x38\x37\x30\x0a";
      static unsigned int write_00076_00000_len = 4;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      unsigned char *read_00084;
      unsigned int read_00084_len;
      unsigned int read_00084_ptr = 0;
      //**** delimited read
      static unsigned char read_00084_delim[] = 
         "\x3a\x20";
      read_00084 = NULL;
      read_00084_len = 0;
      int read_00084_res = cgc_delimited_read(0, &read_00084, &read_00084_len, read_00084_delim, 2);
      if (read_00084_res) {} //silence unused variable warning
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x34\x31\x36\x0a";
      static unsigned int write_00077_00000_len = 4;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      unsigned char *read_00085;
      unsigned int read_00085_len;
      unsigned int read_00085_ptr = 0;
      //**** delimited read
      static unsigned char read_00085_delim[] = 
         "\x3a\x20";
      read_00085 = NULL;
      read_00085_len = 0;
      int read_00085_res = cgc_delimited_read(0, &read_00085, &read_00085_len, read_00085_delim, 2);
      if (read_00085_res) {} //silence unused variable warning
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x38\x33\x35\x0a";
      static unsigned int write_00078_00000_len = 4;
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_buf(write_00078, &write_00078_len, write_00078_00000, write_00078_00000_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      unsigned char *read_00086;
      unsigned int read_00086_len;
      unsigned int read_00086_ptr = 0;
      //**** delimited read
      static unsigned char read_00086_delim[] = 
         "\x3a\x20";
      read_00086 = NULL;
      read_00086_len = 0;
      int read_00086_res = cgc_delimited_read(0, &read_00086, &read_00086_len, read_00086_delim, 2);
      if (read_00086_res) {} //silence unused variable warning
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x37\x35\x30\x0a";
      static unsigned int write_00079_00000_len = 4;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      unsigned char *read_00087;
      unsigned int read_00087_len;
      unsigned int read_00087_ptr = 0;
      //**** delimited read
      static unsigned char read_00087_delim[] = 
         "\x3a\x20";
      read_00087 = NULL;
      read_00087_len = 0;
      int read_00087_res = cgc_delimited_read(0, &read_00087, &read_00087_len, read_00087_delim, 2);
      if (read_00087_res) {} //silence unused variable warning
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x34\x39\x39\x0a";
      static unsigned int write_00080_00000_len = 4;
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_buf(write_00080, &write_00080_len, write_00080_00000, write_00080_00000_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      unsigned char *read_00088;
      unsigned int read_00088_len;
      unsigned int read_00088_ptr = 0;
      //**** delimited read
      static unsigned char read_00088_delim[] = 
         "\x3a\x20";
      read_00088 = NULL;
      read_00088_len = 0;
      int read_00088_res = cgc_delimited_read(0, &read_00088, &read_00088_len, read_00088_delim, 2);
      if (read_00088_res) {} //silence unused variable warning
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x37\x36\x30\x0a";
      static unsigned int write_00081_00000_len = 4;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      unsigned char *read_00089;
      unsigned int read_00089_len;
      unsigned int read_00089_ptr = 0;
      //**** delimited read
      static unsigned char read_00089_delim[] = 
         "\x3a\x20";
      read_00089 = NULL;
      read_00089_len = 0;
      int read_00089_res = cgc_delimited_read(0, &read_00089, &read_00089_len, read_00089_delim, 2);
      if (read_00089_res) {} //silence unused variable warning
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x32\x33\x35\x0a";
      static unsigned int write_00082_00000_len = 4;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      unsigned char *read_00090;
      unsigned int read_00090_len;
      unsigned int read_00090_ptr = 0;
      //**** delimited read
      static unsigned char read_00090_delim[] = 
         "\x3a\x20";
      read_00090 = NULL;
      read_00090_len = 0;
      int read_00090_res = cgc_delimited_read(0, &read_00090, &read_00090_len, read_00090_delim, 2);
      if (read_00090_res) {} //silence unused variable warning
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x39\x31\x33\x0a";
      static unsigned int write_00083_00000_len = 4;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      unsigned char *read_00091;
      unsigned int read_00091_len;
      unsigned int read_00091_ptr = 0;
      //**** delimited read
      static unsigned char read_00091_delim[] = 
         "\x3a\x20";
      read_00091 = NULL;
      read_00091_len = 0;
      int read_00091_res = cgc_delimited_read(0, &read_00091, &read_00091_len, read_00091_delim, 2);
      if (read_00091_res) {} //silence unused variable warning
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x39\x34\x32\x0a";
      static unsigned int write_00084_00000_len = 4;
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_buf(write_00084, &write_00084_len, write_00084_00000, write_00084_00000_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      unsigned char *read_00092;
      unsigned int read_00092_len;
      unsigned int read_00092_ptr = 0;
      //**** delimited read
      static unsigned char read_00092_delim[] = 
         "\x3a\x20";
      read_00092 = NULL;
      read_00092_len = 0;
      int read_00092_res = cgc_delimited_read(0, &read_00092, &read_00092_len, read_00092_delim, 2);
      if (read_00092_res) {} //silence unused variable warning
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x36\x30\x33\x0a";
      static unsigned int write_00085_00000_len = 4;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      unsigned char *read_00093;
      unsigned int read_00093_len;
      unsigned int read_00093_ptr = 0;
      //**** delimited read
      static unsigned char read_00093_delim[] = 
         "\x3a\x20";
      read_00093 = NULL;
      read_00093_len = 0;
      int read_00093_res = cgc_delimited_read(0, &read_00093, &read_00093_len, read_00093_delim, 2);
      if (read_00093_res) {} //silence unused variable warning
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x38\x38\x35\x0a";
      static unsigned int write_00086_00000_len = 4;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
   } while (0);
   do {
      unsigned char *read_00094;
      unsigned int read_00094_len;
      unsigned int read_00094_ptr = 0;
      //**** delimited read
      static unsigned char read_00094_delim[] = 
         "\x3a\x20";
      read_00094 = NULL;
      read_00094_len = 0;
      int read_00094_res = cgc_delimited_read(0, &read_00094, &read_00094_len, read_00094_delim, 2);
      if (read_00094_res) {} //silence unused variable warning
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x36\x33\x31\x0a";
      static unsigned int write_00087_00000_len = 4;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = cgc_append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         cgc_transmit_all(1, write_00087, write_00087_len);
      }
      cgc_free(write_00087);
   } while (0);
   do {
      unsigned char *read_00095;
      unsigned int read_00095_len;
      unsigned int read_00095_ptr = 0;
      //**** delimited read
      static unsigned char read_00095_delim[] = 
         "\x3a\x20";
      read_00095 = NULL;
      read_00095_len = 0;
      int read_00095_res = cgc_delimited_read(0, &read_00095, &read_00095_len, read_00095_delim, 2);
      if (read_00095_res) {} //silence unused variable warning
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x37\x33\x0a";
      static unsigned int write_00088_00000_len = 3;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      unsigned char *read_00096;
      unsigned int read_00096_len;
      unsigned int read_00096_ptr = 0;
      //**** delimited read
      static unsigned char read_00096_delim[] = 
         "\x3a\x20";
      read_00096 = NULL;
      read_00096_len = 0;
      int read_00096_res = cgc_delimited_read(0, &read_00096, &read_00096_len, read_00096_delim, 2);
      if (read_00096_res) {} //silence unused variable warning
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x35\x30\x0a";
      static unsigned int write_00089_00000_len = 3;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
   } while (0);
   do {
      unsigned char *read_00097;
      unsigned int read_00097_len;
      unsigned int read_00097_ptr = 0;
      //**** delimited read
      static unsigned char read_00097_delim[] = 
         "\x3a\x20";
      read_00097 = NULL;
      read_00097_len = 0;
      int read_00097_res = cgc_delimited_read(0, &read_00097, &read_00097_len, read_00097_delim, 2);
      if (read_00097_res) {} //silence unused variable warning
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x37\x35\x32\x0a";
      static unsigned int write_00090_00000_len = 4;
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = cgc_append_buf(write_00090, &write_00090_len, write_00090_00000, write_00090_00000_len);
      if (write_00090_len > 0) {
         cgc_transmit_all(1, write_00090, write_00090_len);
      }
      cgc_free(write_00090);
   } while (0);
   do {
      unsigned char *read_00098;
      unsigned int read_00098_len;
      unsigned int read_00098_ptr = 0;
      //**** delimited read
      static unsigned char read_00098_delim[] = 
         "\x3a\x20";
      read_00098 = NULL;
      read_00098_len = 0;
      int read_00098_res = cgc_delimited_read(0, &read_00098, &read_00098_len, read_00098_delim, 2);
      if (read_00098_res) {} //silence unused variable warning
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x32\x38\x31\x0a";
      static unsigned int write_00091_00000_len = 4;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      unsigned char *read_00099;
      unsigned int read_00099_len;
      unsigned int read_00099_ptr = 0;
      //**** delimited read
      static unsigned char read_00099_delim[] = 
         "\x3a\x20";
      read_00099 = NULL;
      read_00099_len = 0;
      int read_00099_res = cgc_delimited_read(0, &read_00099, &read_00099_len, read_00099_delim, 2);
      if (read_00099_res) {} //silence unused variable warning
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x36\x30\x39\x0a";
      static unsigned int write_00092_00000_len = 4;
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = cgc_append_buf(write_00092, &write_00092_len, write_00092_00000, write_00092_00000_len);
      if (write_00092_len > 0) {
         cgc_transmit_all(1, write_00092, write_00092_len);
      }
      cgc_free(write_00092);
   } while (0);
   do {
      unsigned char *read_00100;
      unsigned int read_00100_len;
      unsigned int read_00100_ptr = 0;
      //**** delimited read
      static unsigned char read_00100_delim[] = 
         "\x3a\x20";
      read_00100 = NULL;
      read_00100_len = 0;
      int read_00100_res = cgc_delimited_read(0, &read_00100, &read_00100_len, read_00100_delim, 2);
      if (read_00100_res) {} //silence unused variable warning
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x32\x31\x35\x0a";
      static unsigned int write_00093_00000_len = 4;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = cgc_append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         cgc_transmit_all(1, write_00093, write_00093_len);
      }
      cgc_free(write_00093);
   } while (0);
   do {
      unsigned char *read_00101;
      unsigned int read_00101_len;
      unsigned int read_00101_ptr = 0;
      //**** delimited read
      static unsigned char read_00101_delim[] = 
         "\x3a\x20";
      read_00101 = NULL;
      read_00101_len = 0;
      int read_00101_res = cgc_delimited_read(0, &read_00101, &read_00101_len, read_00101_delim, 2);
      if (read_00101_res) {} //silence unused variable warning
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x35\x0a";
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
      unsigned char *read_00102;
      unsigned int read_00102_len;
      unsigned int read_00102_ptr = 0;
      //**** delimited read
      static unsigned char read_00102_delim[] = 
         "\x3a\x20";
      read_00102 = NULL;
      read_00102_len = 0;
      int read_00102_res = cgc_delimited_read(0, &read_00102, &read_00102_len, read_00102_delim, 2);
      if (read_00102_res) {} //silence unused variable warning
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x33\x34\x33\x0a";
      static unsigned int write_00095_00000_len = 4;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = cgc_append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         cgc_transmit_all(1, write_00095, write_00095_len);
      }
      cgc_free(write_00095);
   } while (0);
   do {
      unsigned char *read_00103;
      unsigned int read_00103_len;
      unsigned int read_00103_ptr = 0;
      //**** delimited read
      static unsigned char read_00103_delim[] = 
         "\x3a\x20";
      read_00103 = NULL;
      read_00103_len = 0;
      int read_00103_res = cgc_delimited_read(0, &read_00103, &read_00103_len, read_00103_delim, 2);
      if (read_00103_res) {} //silence unused variable warning
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x33\x35\x30\x0a";
      static unsigned int write_00096_00000_len = 4;
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = cgc_append_buf(write_00096, &write_00096_len, write_00096_00000, write_00096_00000_len);
      if (write_00096_len > 0) {
         cgc_transmit_all(1, write_00096, write_00096_len);
      }
      cgc_free(write_00096);
   } while (0);
   do {
      unsigned char *read_00104;
      unsigned int read_00104_len;
      unsigned int read_00104_ptr = 0;
      //**** delimited read
      static unsigned char read_00104_delim[] = 
         "\x3a\x20";
      read_00104 = NULL;
      read_00104_len = 0;
      int read_00104_res = cgc_delimited_read(0, &read_00104, &read_00104_len, read_00104_delim, 2);
      if (read_00104_res) {} //silence unused variable warning
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x34\x39\x33\x0a";
      static unsigned int write_00097_00000_len = 4;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      unsigned char *read_00105;
      unsigned int read_00105_len;
      unsigned int read_00105_ptr = 0;
      //**** delimited read
      static unsigned char read_00105_delim[] = 
         "\x3a\x20";
      read_00105 = NULL;
      read_00105_len = 0;
      int read_00105_res = cgc_delimited_read(0, &read_00105, &read_00105_len, read_00105_delim, 2);
      if (read_00105_res) {} //silence unused variable warning
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x37\x36\x33\x0a";
      static unsigned int write_00098_00000_len = 4;
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = cgc_append_buf(write_00098, &write_00098_len, write_00098_00000, write_00098_00000_len);
      if (write_00098_len > 0) {
         cgc_transmit_all(1, write_00098, write_00098_len);
      }
      cgc_free(write_00098);
   } while (0);
   do {
      unsigned char *read_00106;
      unsigned int read_00106_len;
      unsigned int read_00106_ptr = 0;
      //**** delimited read
      static unsigned char read_00106_delim[] = 
         "\x3a\x20";
      read_00106 = NULL;
      read_00106_len = 0;
      int read_00106_res = cgc_delimited_read(0, &read_00106, &read_00106_len, read_00106_delim, 2);
      if (read_00106_res) {} //silence unused variable warning
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x39\x32\x38\x0a";
      static unsigned int write_00099_00000_len = 4;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = cgc_append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         cgc_transmit_all(1, write_00099, write_00099_len);
      }
      cgc_free(write_00099);
   } while (0);
   do {
      unsigned char *read_00107;
      unsigned int read_00107_len;
      unsigned int read_00107_ptr = 0;
      //**** delimited read
      static unsigned char read_00107_delim[] = 
         "\x3a\x20";
      read_00107 = NULL;
      read_00107_len = 0;
      int read_00107_res = cgc_delimited_read(0, &read_00107, &read_00107_len, read_00107_delim, 2);
      if (read_00107_res) {} //silence unused variable warning
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x36\x33\x38\x0a";
      static unsigned int write_00100_00000_len = 4;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      unsigned char *read_00108;
      unsigned int read_00108_len;
      unsigned int read_00108_ptr = 0;
      //**** delimited read
      static unsigned char read_00108_delim[] = 
         "\x3a\x20";
      read_00108 = NULL;
      read_00108_len = 0;
      int read_00108_res = cgc_delimited_read(0, &read_00108, &read_00108_len, read_00108_delim, 2);
      if (read_00108_res) {} //silence unused variable warning
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x37\x37\x33\x0a";
      static unsigned int write_00101_00000_len = 4;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = cgc_append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         cgc_transmit_all(1, write_00101, write_00101_len);
      }
      cgc_free(write_00101);
   } while (0);
   do {
      unsigned char *read_00109;
      unsigned int read_00109_len;
      unsigned int read_00109_ptr = 0;
      //**** delimited read
      static unsigned char read_00109_delim[] = 
         "\x3a\x20";
      read_00109 = NULL;
      read_00109_len = 0;
      int read_00109_res = cgc_delimited_read(0, &read_00109, &read_00109_len, read_00109_delim, 2);
      if (read_00109_res) {} //silence unused variable warning
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x36\x39\x32\x0a";
      static unsigned int write_00102_00000_len = 4;
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = cgc_append_buf(write_00102, &write_00102_len, write_00102_00000, write_00102_00000_len);
      if (write_00102_len > 0) {
         cgc_transmit_all(1, write_00102, write_00102_len);
      }
      cgc_free(write_00102);
   } while (0);
   do {
      unsigned char *read_00110;
      unsigned int read_00110_len;
      unsigned int read_00110_ptr = 0;
      //**** delimited read
      static unsigned char read_00110_delim[] = 
         "\x3a\x20";
      read_00110 = NULL;
      read_00110_len = 0;
      int read_00110_res = cgc_delimited_read(0, &read_00110, &read_00110_len, read_00110_delim, 2);
      if (read_00110_res) {} //silence unused variable warning
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x34\x32\x39\x0a";
      static unsigned int write_00103_00000_len = 4;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      unsigned char *read_00111;
      unsigned int read_00111_len;
      unsigned int read_00111_ptr = 0;
      //**** delimited read
      static unsigned char read_00111_delim[] = 
         "\x3a\x20";
      read_00111 = NULL;
      read_00111_len = 0;
      int read_00111_res = cgc_delimited_read(0, &read_00111, &read_00111_len, read_00111_delim, 2);
      if (read_00111_res) {} //silence unused variable warning
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x33\x38\x33\x0a";
      static unsigned int write_00104_00000_len = 4;
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = cgc_append_buf(write_00104, &write_00104_len, write_00104_00000, write_00104_00000_len);
      if (write_00104_len > 0) {
         cgc_transmit_all(1, write_00104, write_00104_len);
      }
      cgc_free(write_00104);
   } while (0);
   do {
      unsigned char *read_00112;
      unsigned int read_00112_len;
      unsigned int read_00112_ptr = 0;
      //**** delimited read
      static unsigned char read_00112_delim[] = 
         "\x3a\x20";
      read_00112 = NULL;
      read_00112_len = 0;
      int read_00112_res = cgc_delimited_read(0, &read_00112, &read_00112_len, read_00112_delim, 2);
      if (read_00112_res) {} //silence unused variable warning
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x37\x39\x37\x0a";
      static unsigned int write_00105_00000_len = 4;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = cgc_append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         cgc_transmit_all(1, write_00105, write_00105_len);
      }
      cgc_free(write_00105);
   } while (0);
   do {
      unsigned char *read_00113;
      unsigned int read_00113_len;
      unsigned int read_00113_ptr = 0;
      //**** delimited read
      static unsigned char read_00113_delim[] = 
         "\x3a\x20";
      read_00113 = NULL;
      read_00113_len = 0;
      int read_00113_res = cgc_delimited_read(0, &read_00113, &read_00113_len, read_00113_delim, 2);
      if (read_00113_res) {} //silence unused variable warning
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x35\x38\x39\x0a";
      static unsigned int write_00106_00000_len = 4;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      unsigned char *read_00114;
      unsigned int read_00114_len;
      unsigned int read_00114_ptr = 0;
      //**** delimited read
      static unsigned char read_00114_delim[] = 
         "\x3a\x20";
      read_00114 = NULL;
      read_00114_len = 0;
      int read_00114_res = cgc_delimited_read(0, &read_00114, &read_00114_len, read_00114_delim, 2);
      if (read_00114_res) {} //silence unused variable warning
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x39\x39\x32\x0a";
      static unsigned int write_00107_00000_len = 4;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = cgc_append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         cgc_transmit_all(1, write_00107, write_00107_len);
      }
      cgc_free(write_00107);
   } while (0);
   do {
      unsigned char *read_00115;
      unsigned int read_00115_len;
      unsigned int read_00115_ptr = 0;
      //**** delimited read
      static unsigned char read_00115_delim[] = 
         "\x3a\x20";
      read_00115 = NULL;
      read_00115_len = 0;
      int read_00115_res = cgc_delimited_read(0, &read_00115, &read_00115_len, read_00115_delim, 2);
      if (read_00115_res) {} //silence unused variable warning
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x35\x35\x34\x0a";
      static unsigned int write_00108_00000_len = 4;
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = cgc_append_buf(write_00108, &write_00108_len, write_00108_00000, write_00108_00000_len);
      if (write_00108_len > 0) {
         cgc_transmit_all(1, write_00108, write_00108_len);
      }
      cgc_free(write_00108);
   } while (0);
   do {
      unsigned char *read_00116;
      unsigned int read_00116_len;
      unsigned int read_00116_ptr = 0;
      //**** delimited read
      static unsigned char read_00116_delim[] = 
         "\x3a\x20";
      read_00116 = NULL;
      read_00116_len = 0;
      int read_00116_res = cgc_delimited_read(0, &read_00116, &read_00116_len, read_00116_delim, 2);
      if (read_00116_res) {} //silence unused variable warning
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x33\x34\x38\x0a";
      static unsigned int write_00109_00000_len = 4;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      unsigned char *read_00117;
      unsigned int read_00117_len;
      unsigned int read_00117_ptr = 0;
      //**** delimited read
      static unsigned char read_00117_delim[] = 
         "\x3a\x20";
      read_00117 = NULL;
      read_00117_len = 0;
      int read_00117_res = cgc_delimited_read(0, &read_00117, &read_00117_len, read_00117_delim, 2);
      if (read_00117_res) {} //silence unused variable warning
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x31\x37\x33\x0a";
      static unsigned int write_00110_00000_len = 4;
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = cgc_append_buf(write_00110, &write_00110_len, write_00110_00000, write_00110_00000_len);
      if (write_00110_len > 0) {
         cgc_transmit_all(1, write_00110, write_00110_len);
      }
      cgc_free(write_00110);
   } while (0);
   do {
      unsigned char *read_00118;
      unsigned int read_00118_len;
      unsigned int read_00118_ptr = 0;
      //**** delimited read
      static unsigned char read_00118_delim[] = 
         "\x3a\x20";
      read_00118 = NULL;
      read_00118_len = 0;
      int read_00118_res = cgc_delimited_read(0, &read_00118, &read_00118_len, read_00118_delim, 2);
      if (read_00118_res) {} //silence unused variable warning
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x31\x35\x36\x0a";
      static unsigned int write_00111_00000_len = 4;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = cgc_append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         cgc_transmit_all(1, write_00111, write_00111_len);
      }
      cgc_free(write_00111);
   } while (0);
   do {
      unsigned char *read_00119;
      unsigned int read_00119_len;
      unsigned int read_00119_ptr = 0;
      //**** delimited read
      static unsigned char read_00119_delim[] = 
         "\x3a\x20";
      read_00119 = NULL;
      read_00119_len = 0;
      int read_00119_res = cgc_delimited_read(0, &read_00119, &read_00119_len, read_00119_delim, 2);
      if (read_00119_res) {} //silence unused variable warning
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x34\x33\x37\x0a";
      static unsigned int write_00112_00000_len = 4;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      unsigned char *read_00120;
      unsigned int read_00120_len;
      unsigned int read_00120_ptr = 0;
      //**** delimited read
      static unsigned char read_00120_delim[] = 
         "\x3a\x20";
      read_00120 = NULL;
      read_00120_len = 0;
      int read_00120_res = cgc_delimited_read(0, &read_00120, &read_00120_len, read_00120_delim, 2);
      if (read_00120_res) {} //silence unused variable warning
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x37\x33\x38\x0a";
      static unsigned int write_00113_00000_len = 4;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = cgc_append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         cgc_transmit_all(1, write_00113, write_00113_len);
      }
      cgc_free(write_00113);
   } while (0);
   do {
      unsigned char *read_00121;
      unsigned int read_00121_len;
      unsigned int read_00121_ptr = 0;
      //**** delimited read
      static unsigned char read_00121_delim[] = 
         "\x3a\x20";
      read_00121 = NULL;
      read_00121_len = 0;
      int read_00121_res = cgc_delimited_read(0, &read_00121, &read_00121_len, read_00121_delim, 2);
      if (read_00121_res) {} //silence unused variable warning
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x32\x39\x0a";
      static unsigned int write_00114_00000_len = 3;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      unsigned char *read_00122;
      unsigned int read_00122_len;
      unsigned int read_00122_ptr = 0;
      //**** delimited read
      static unsigned char read_00122_delim[] = 
         "\x3a\x20";
      read_00122 = NULL;
      read_00122_len = 0;
      int read_00122_res = cgc_delimited_read(0, &read_00122, &read_00122_len, read_00122_delim, 2);
      if (read_00122_res) {} //silence unused variable warning
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x32\x30\x34\x0a";
      static unsigned int write_00115_00000_len = 4;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      unsigned char *read_00123;
      unsigned int read_00123_len;
      unsigned int read_00123_ptr = 0;
      //**** delimited read
      static unsigned char read_00123_delim[] = 
         "\x3a\x20";
      read_00123 = NULL;
      read_00123_len = 0;
      int read_00123_res = cgc_delimited_read(0, &read_00123, &read_00123_len, read_00123_delim, 2);
      if (read_00123_res) {} //silence unused variable warning
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x35\x33\x30\x0a";
      static unsigned int write_00116_00000_len = 4;
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = cgc_append_buf(write_00116, &write_00116_len, write_00116_00000, write_00116_00000_len);
      if (write_00116_len > 0) {
         cgc_transmit_all(1, write_00116, write_00116_len);
      }
      cgc_free(write_00116);
   } while (0);
   do {
      unsigned char *read_00124;
      unsigned int read_00124_len;
      unsigned int read_00124_ptr = 0;
      //**** delimited read
      static unsigned char read_00124_delim[] = 
         "\x3a\x20";
      read_00124 = NULL;
      read_00124_len = 0;
      int read_00124_res = cgc_delimited_read(0, &read_00124, &read_00124_len, read_00124_delim, 2);
      if (read_00124_res) {} //silence unused variable warning
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x34\x33\x37\x0a";
      static unsigned int write_00117_00000_len = 4;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = cgc_append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         cgc_transmit_all(1, write_00117, write_00117_len);
      }
      cgc_free(write_00117);
   } while (0);
   do {
      unsigned char *read_00125;
      unsigned int read_00125_len;
      unsigned int read_00125_ptr = 0;
      //**** delimited read
      static unsigned char read_00125_delim[] = 
         "\x3a\x20";
      read_00125 = NULL;
      read_00125_len = 0;
      int read_00125_res = cgc_delimited_read(0, &read_00125, &read_00125_len, read_00125_delim, 2);
      if (read_00125_res) {} //silence unused variable warning
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x37\x34\x33\x0a";
      static unsigned int write_00118_00000_len = 4;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      unsigned char *read_00126;
      unsigned int read_00126_len;
      unsigned int read_00126_ptr = 0;
      //**** delimited read
      static unsigned char read_00126_delim[] = 
         "\x3a\x20";
      read_00126 = NULL;
      read_00126_len = 0;
      int read_00126_res = cgc_delimited_read(0, &read_00126, &read_00126_len, read_00126_delim, 2);
      if (read_00126_res) {} //silence unused variable warning
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x34\x35\x30\x0a";
      static unsigned int write_00119_00000_len = 4;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = cgc_append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         cgc_transmit_all(1, write_00119, write_00119_len);
      }
      cgc_free(write_00119);
   } while (0);
   do {
      unsigned char *read_00127;
      unsigned int read_00127_len;
      unsigned int read_00127_ptr = 0;
      //**** delimited read
      static unsigned char read_00127_delim[] = 
         "\x3a\x20";
      read_00127 = NULL;
      read_00127_len = 0;
      int read_00127_res = cgc_delimited_read(0, &read_00127, &read_00127_len, read_00127_delim, 2);
      if (read_00127_res) {} //silence unused variable warning
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x37\x36\x33\x0a";
      static unsigned int write_00120_00000_len = 4;
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = cgc_append_buf(write_00120, &write_00120_len, write_00120_00000, write_00120_00000_len);
      if (write_00120_len > 0) {
         cgc_transmit_all(1, write_00120, write_00120_len);
      }
      cgc_free(write_00120);
   } while (0);
   do {
      unsigned char *read_00128;
      unsigned int read_00128_len;
      unsigned int read_00128_ptr = 0;
      //**** delimited read
      static unsigned char read_00128_delim[] = 
         "\x3a\x20";
      read_00128 = NULL;
      read_00128_len = 0;
      int read_00128_res = cgc_delimited_read(0, &read_00128, &read_00128_len, read_00128_delim, 2);
      if (read_00128_res) {} //silence unused variable warning
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x37\x30\x34\x0a";
      static unsigned int write_00121_00000_len = 4;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      unsigned char *read_00129;
      unsigned int read_00129_len;
      unsigned int read_00129_ptr = 0;
      //**** delimited read
      static unsigned char read_00129_delim[] = 
         "\x3a\x20";
      read_00129 = NULL;
      read_00129_len = 0;
      int read_00129_res = cgc_delimited_read(0, &read_00129, &read_00129_len, read_00129_delim, 2);
      if (read_00129_res) {} //silence unused variable warning
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x32\x39\x34\x0a";
      static unsigned int write_00122_00000_len = 4;
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = cgc_append_buf(write_00122, &write_00122_len, write_00122_00000, write_00122_00000_len);
      if (write_00122_len > 0) {
         cgc_transmit_all(1, write_00122, write_00122_len);
      }
      cgc_free(write_00122);
   } while (0);
   do {
      unsigned char *read_00130;
      unsigned int read_00130_len;
      unsigned int read_00130_ptr = 0;
      //**** delimited read
      static unsigned char read_00130_delim[] = 
         "\x3a\x20";
      read_00130 = NULL;
      read_00130_len = 0;
      int read_00130_res = cgc_delimited_read(0, &read_00130, &read_00130_len, read_00130_delim, 2);
      if (read_00130_res) {} //silence unused variable warning
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x39\x30\x35\x0a";
      static unsigned int write_00123_00000_len = 4;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = cgc_append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         cgc_transmit_all(1, write_00123, write_00123_len);
      }
      cgc_free(write_00123);
   } while (0);
   do {
      unsigned char *read_00131;
      unsigned int read_00131_len;
      unsigned int read_00131_ptr = 0;
      //**** delimited read
      static unsigned char read_00131_delim[] = 
         "\x3a\x20";
      read_00131 = NULL;
      read_00131_len = 0;
      int read_00131_res = cgc_delimited_read(0, &read_00131, &read_00131_len, read_00131_delim, 2);
      if (read_00131_res) {} //silence unused variable warning
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x33\x39\x38\x0a";
      static unsigned int write_00124_00000_len = 4;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      unsigned char *read_00132;
      unsigned int read_00132_len;
      unsigned int read_00132_ptr = 0;
      //**** delimited read
      static unsigned char read_00132_delim[] = 
         "\x3a\x20";
      read_00132 = NULL;
      read_00132_len = 0;
      int read_00132_res = cgc_delimited_read(0, &read_00132, &read_00132_len, read_00132_delim, 2);
      if (read_00132_res) {} //silence unused variable warning
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x38\x31\x31\x0a";
      static unsigned int write_00125_00000_len = 4;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = cgc_append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         cgc_transmit_all(1, write_00125, write_00125_len);
      }
      cgc_free(write_00125);
   } while (0);
   do {
      unsigned char *read_00133;
      unsigned int read_00133_len;
      unsigned int read_00133_ptr = 0;
      //**** delimited read
      static unsigned char read_00133_delim[] = 
         "\x3a\x20";
      read_00133 = NULL;
      read_00133_len = 0;
      int read_00133_res = cgc_delimited_read(0, &read_00133, &read_00133_len, read_00133_delim, 2);
      if (read_00133_res) {} //silence unused variable warning
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x37\x33\x0a";
      static unsigned int write_00126_00000_len = 3;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      unsigned char *read_00134;
      unsigned int read_00134_len;
      unsigned int read_00134_ptr = 0;
      //**** delimited read
      static unsigned char read_00134_delim[] = 
         "\x3a\x20";
      read_00134 = NULL;
      read_00134_len = 0;
      int read_00134_res = cgc_delimited_read(0, &read_00134, &read_00134_len, read_00134_delim, 2);
      if (read_00134_res) {} //silence unused variable warning
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x35\x30\x34\x0a";
      static unsigned int write_00127_00000_len = 4;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      unsigned char *read_00135;
      unsigned int read_00135_len;
      unsigned int read_00135_ptr = 0;
      //**** delimited read
      static unsigned char read_00135_delim[] = 
         "\x3a\x20";
      read_00135 = NULL;
      read_00135_len = 0;
      int read_00135_res = cgc_delimited_read(0, &read_00135, &read_00135_len, read_00135_delim, 2);
      if (read_00135_res) {} //silence unused variable warning
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x31\x34\x36\x0a";
      static unsigned int write_00128_00000_len = 4;
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = cgc_append_buf(write_00128, &write_00128_len, write_00128_00000, write_00128_00000_len);
      if (write_00128_len > 0) {
         cgc_transmit_all(1, write_00128, write_00128_len);
      }
      cgc_free(write_00128);
   } while (0);
   do {
      unsigned char *read_00136;
      unsigned int read_00136_len;
      unsigned int read_00136_ptr = 0;
      //**** delimited read
      static unsigned char read_00136_delim[] = 
         "\x3a\x20";
      read_00136 = NULL;
      read_00136_len = 0;
      int read_00136_res = cgc_delimited_read(0, &read_00136, &read_00136_len, read_00136_delim, 2);
      if (read_00136_res) {} //silence unused variable warning
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x39\x38\x39\x0a";
      static unsigned int write_00129_00000_len = 4;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = cgc_append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         cgc_transmit_all(1, write_00129, write_00129_len);
      }
      cgc_free(write_00129);
   } while (0);
   do {
      unsigned char *read_00137;
      unsigned int read_00137_len;
      unsigned int read_00137_ptr = 0;
      //**** delimited read
      static unsigned char read_00137_delim[] = 
         "\x3a\x20";
      read_00137 = NULL;
      read_00137_len = 0;
      int read_00137_res = cgc_delimited_read(0, &read_00137, &read_00137_len, read_00137_delim, 2);
      if (read_00137_res) {} //silence unused variable warning
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x37\x35\x0a";
      static unsigned int write_00130_00000_len = 3;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      unsigned char *read_00138;
      unsigned int read_00138_len;
      unsigned int read_00138_ptr = 0;
      //**** delimited read
      static unsigned char read_00138_delim[] = 
         "\x3a\x20";
      read_00138 = NULL;
      read_00138_len = 0;
      int read_00138_res = cgc_delimited_read(0, &read_00138, &read_00138_len, read_00138_delim, 2);
      if (read_00138_res) {} //silence unused variable warning
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x31\x34\x31\x0a";
      static unsigned int write_00131_00000_len = 4;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = cgc_append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         cgc_transmit_all(1, write_00131, write_00131_len);
      }
      cgc_free(write_00131);
   } while (0);
   do {
      unsigned char *read_00139;
      unsigned int read_00139_len;
      unsigned int read_00139_ptr = 0;
      //**** delimited read
      static unsigned char read_00139_delim[] = 
         "\x3a\x20";
      read_00139 = NULL;
      read_00139_len = 0;
      int read_00139_res = cgc_delimited_read(0, &read_00139, &read_00139_len, read_00139_delim, 2);
      if (read_00139_res) {} //silence unused variable warning
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x39\x36\x39\x0a";
      static unsigned int write_00132_00000_len = 4;
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = cgc_append_buf(write_00132, &write_00132_len, write_00132_00000, write_00132_00000_len);
      if (write_00132_len > 0) {
         cgc_transmit_all(1, write_00132, write_00132_len);
      }
      cgc_free(write_00132);
   } while (0);
   do {
      unsigned char *read_00140;
      unsigned int read_00140_len;
      unsigned int read_00140_ptr = 0;
      //**** delimited read
      static unsigned char read_00140_delim[] = 
         "\x3a\x20";
      read_00140 = NULL;
      read_00140_len = 0;
      int read_00140_res = cgc_delimited_read(0, &read_00140, &read_00140_len, read_00140_delim, 2);
      if (read_00140_res) {} //silence unused variable warning
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x32\x36\x32\x0a";
      static unsigned int write_00133_00000_len = 4;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      unsigned char *read_00141;
      unsigned int read_00141_len;
      unsigned int read_00141_ptr = 0;
      //**** delimited read
      static unsigned char read_00141_delim[] = 
         "\x3a\x20";
      read_00141 = NULL;
      read_00141_len = 0;
      int read_00141_res = cgc_delimited_read(0, &read_00141, &read_00141_len, read_00141_delim, 2);
      if (read_00141_res) {} //silence unused variable warning
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x31\x38\x31\x0a";
      static unsigned int write_00134_00000_len = 4;
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = cgc_append_buf(write_00134, &write_00134_len, write_00134_00000, write_00134_00000_len);
      if (write_00134_len > 0) {
         cgc_transmit_all(1, write_00134, write_00134_len);
      }
      cgc_free(write_00134);
   } while (0);
   do {
      unsigned char *read_00142;
      unsigned int read_00142_len;
      unsigned int read_00142_ptr = 0;
      //**** delimited read
      static unsigned char read_00142_delim[] = 
         "\x3a\x20";
      read_00142 = NULL;
      read_00142_len = 0;
      int read_00142_res = cgc_delimited_read(0, &read_00142, &read_00142_len, read_00142_delim, 2);
      if (read_00142_res) {} //silence unused variable warning
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x37\x34\x34\x0a";
      static unsigned int write_00135_00000_len = 4;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = cgc_append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         cgc_transmit_all(1, write_00135, write_00135_len);
      }
      cgc_free(write_00135);
   } while (0);
   do {
      unsigned char *read_00143;
      unsigned int read_00143_len;
      unsigned int read_00143_ptr = 0;
      //**** delimited read
      static unsigned char read_00143_delim[] = 
         "\x3a\x20";
      read_00143 = NULL;
      read_00143_len = 0;
      int read_00143_res = cgc_delimited_read(0, &read_00143, &read_00143_len, read_00143_delim, 2);
      if (read_00143_res) {} //silence unused variable warning
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x37\x34\x0a";
      static unsigned int write_00136_00000_len = 3;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      unsigned char *read_00144;
      unsigned int read_00144_len;
      unsigned int read_00144_ptr = 0;
      //**** delimited read
      static unsigned char read_00144_delim[] = 
         "\x3a\x20";
      read_00144 = NULL;
      read_00144_len = 0;
      int read_00144_res = cgc_delimited_read(0, &read_00144, &read_00144_len, read_00144_delim, 2);
      if (read_00144_res) {} //silence unused variable warning
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x32\x37\x35\x0a";
      static unsigned int write_00137_00000_len = 4;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = cgc_append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         cgc_transmit_all(1, write_00137, write_00137_len);
      }
      cgc_free(write_00137);
   } while (0);
   do {
      unsigned char *read_00145;
      unsigned int read_00145_len;
      unsigned int read_00145_ptr = 0;
      //**** delimited read
      static unsigned char read_00145_delim[] = 
         "\x3a\x20";
      read_00145 = NULL;
      read_00145_len = 0;
      int read_00145_res = cgc_delimited_read(0, &read_00145, &read_00145_len, read_00145_delim, 2);
      if (read_00145_res) {} //silence unused variable warning
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x32\x30\x31\x0a";
      static unsigned int write_00138_00000_len = 4;
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = cgc_append_buf(write_00138, &write_00138_len, write_00138_00000, write_00138_00000_len);
      if (write_00138_len > 0) {
         cgc_transmit_all(1, write_00138, write_00138_len);
      }
      cgc_free(write_00138);
   } while (0);
   do {
      unsigned char *read_00146;
      unsigned int read_00146_len;
      unsigned int read_00146_ptr = 0;
      //**** delimited read
      static unsigned char read_00146_delim[] = 
         "\x3a\x20";
      read_00146 = NULL;
      read_00146_len = 0;
      int read_00146_res = cgc_delimited_read(0, &read_00146, &read_00146_len, read_00146_delim, 2);
      if (read_00146_res) {} //silence unused variable warning
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x38\x34\x39\x0a";
      static unsigned int write_00139_00000_len = 4;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      unsigned char *read_00147;
      unsigned int read_00147_len;
      unsigned int read_00147_ptr = 0;
      //**** delimited read
      static unsigned char read_00147_delim[] = 
         "\x3a\x20";
      read_00147 = NULL;
      read_00147_len = 0;
      int read_00147_res = cgc_delimited_read(0, &read_00147, &read_00147_len, read_00147_delim, 2);
      if (read_00147_res) {} //silence unused variable warning
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x31\x34\x30\x0a";
      static unsigned int write_00140_00000_len = 4;
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = cgc_append_buf(write_00140, &write_00140_len, write_00140_00000, write_00140_00000_len);
      if (write_00140_len > 0) {
         cgc_transmit_all(1, write_00140, write_00140_len);
      }
      cgc_free(write_00140);
   } while (0);
   do {
      unsigned char *read_00148;
      unsigned int read_00148_len;
      unsigned int read_00148_ptr = 0;
      //**** delimited read
      static unsigned char read_00148_delim[] = 
         "\x3a\x20";
      read_00148 = NULL;
      read_00148_len = 0;
      int read_00148_res = cgc_delimited_read(0, &read_00148, &read_00148_len, read_00148_delim, 2);
      if (read_00148_res) {} //silence unused variable warning
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x32\x31\x36\x0a";
      static unsigned int write_00141_00000_len = 4;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = cgc_append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         cgc_transmit_all(1, write_00141, write_00141_len);
      }
      cgc_free(write_00141);
   } while (0);
   do {
      unsigned char *read_00149;
      unsigned int read_00149_len;
      unsigned int read_00149_ptr = 0;
      //**** delimited read
      static unsigned char read_00149_delim[] = 
         "\x3a\x20";
      read_00149 = NULL;
      read_00149_len = 0;
      int read_00149_res = cgc_delimited_read(0, &read_00149, &read_00149_len, read_00149_delim, 2);
      if (read_00149_res) {} //silence unused variable warning
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x35\x30\x33\x0a";
      static unsigned int write_00142_00000_len = 4;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
   do {
      unsigned char *read_00150;
      unsigned int read_00150_len;
      unsigned int read_00150_ptr = 0;
      //**** delimited read
      static unsigned char read_00150_delim[] = 
         "\x3a\x20";
      read_00150 = NULL;
      read_00150_len = 0;
      int read_00150_res = cgc_delimited_read(0, &read_00150, &read_00150_len, read_00150_delim, 2);
      if (read_00150_res) {} //silence unused variable warning
      cgc_free(read_00150);
      if (read_00150_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x33\x33\x38\x0a";
      static unsigned int write_00143_00000_len = 4;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = cgc_append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         cgc_transmit_all(1, write_00143, write_00143_len);
      }
      cgc_free(write_00143);
   } while (0);
   do {
      unsigned char *read_00151;
      unsigned int read_00151_len;
      unsigned int read_00151_ptr = 0;
      //**** delimited read
      static unsigned char read_00151_delim[] = 
         "\x3a\x20";
      read_00151 = NULL;
      read_00151_len = 0;
      int read_00151_res = cgc_delimited_read(0, &read_00151, &read_00151_len, read_00151_delim, 2);
      if (read_00151_res) {} //silence unused variable warning
      cgc_free(read_00151);
      if (read_00151_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x36\x33\x35\x0a";
      static unsigned int write_00144_00000_len = 4;
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = cgc_append_buf(write_00144, &write_00144_len, write_00144_00000, write_00144_00000_len);
      if (write_00144_len > 0) {
         cgc_transmit_all(1, write_00144, write_00144_len);
      }
      cgc_free(write_00144);
   } while (0);
   do {
      unsigned char *read_00152;
      unsigned int read_00152_len;
      unsigned int read_00152_ptr = 0;
      //**** delimited read
      static unsigned char read_00152_delim[] = 
         "\x3a\x20";
      read_00152 = NULL;
      read_00152_len = 0;
      int read_00152_res = cgc_delimited_read(0, &read_00152, &read_00152_len, read_00152_delim, 2);
      if (read_00152_res) {} //silence unused variable warning
      cgc_free(read_00152);
      if (read_00152_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x32\x39\x39\x0a";
      static unsigned int write_00145_00000_len = 4;
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = cgc_append_buf(write_00145, &write_00145_len, write_00145_00000, write_00145_00000_len);
      if (write_00145_len > 0) {
         cgc_transmit_all(1, write_00145, write_00145_len);
      }
      cgc_free(write_00145);
   } while (0);
   do {
      unsigned char *read_00153;
      unsigned int read_00153_len;
      unsigned int read_00153_ptr = 0;
      //**** delimited read
      static unsigned char read_00153_delim[] = 
         "\x3a\x20";
      read_00153 = NULL;
      read_00153_len = 0;
      int read_00153_res = cgc_delimited_read(0, &read_00153, &read_00153_len, read_00153_delim, 2);
      if (read_00153_res) {} //silence unused variable warning
      cgc_free(read_00153);
      if (read_00153_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00146_00000[] = 
         "\x34\x31\x0a";
      static unsigned int write_00146_00000_len = 3;
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = cgc_append_buf(write_00146, &write_00146_len, write_00146_00000, write_00146_00000_len);
      if (write_00146_len > 0) {
         cgc_transmit_all(1, write_00146, write_00146_len);
      }
      cgc_free(write_00146);
   } while (0);
   do {
      unsigned char *read_00154;
      unsigned int read_00154_len;
      unsigned int read_00154_ptr = 0;
      //**** delimited read
      static unsigned char read_00154_delim[] = 
         "\x3a\x20";
      read_00154 = NULL;
      read_00154_len = 0;
      int read_00154_res = cgc_delimited_read(0, &read_00154, &read_00154_len, read_00154_delim, 2);
      if (read_00154_res) {} //silence unused variable warning
      cgc_free(read_00154);
      if (read_00154_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x37\x31\x34\x0a";
      static unsigned int write_00147_00000_len = 4;
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = cgc_append_buf(write_00147, &write_00147_len, write_00147_00000, write_00147_00000_len);
      if (write_00147_len > 0) {
         cgc_transmit_all(1, write_00147, write_00147_len);
      }
      cgc_free(write_00147);
   } while (0);
   do {
      unsigned char *read_00155;
      unsigned int read_00155_len;
      unsigned int read_00155_ptr = 0;
      //**** delimited read
      static unsigned char read_00155_delim[] = 
         "\x3a\x20";
      read_00155 = NULL;
      read_00155_len = 0;
      int read_00155_res = cgc_delimited_read(0, &read_00155, &read_00155_len, read_00155_delim, 2);
      if (read_00155_res) {} //silence unused variable warning
      cgc_free(read_00155);
      if (read_00155_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00148_00000[] = 
         "\x35\x35\x34\x0a";
      static unsigned int write_00148_00000_len = 4;
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = cgc_append_buf(write_00148, &write_00148_len, write_00148_00000, write_00148_00000_len);
      if (write_00148_len > 0) {
         cgc_transmit_all(1, write_00148, write_00148_len);
      }
      cgc_free(write_00148);
   } while (0);
   do {
      unsigned char *read_00156;
      unsigned int read_00156_len;
      unsigned int read_00156_ptr = 0;
      //**** delimited read
      static unsigned char read_00156_delim[] = 
         "\x3a\x20";
      read_00156 = NULL;
      read_00156_len = 0;
      int read_00156_res = cgc_delimited_read(0, &read_00156, &read_00156_len, read_00156_delim, 2);
      if (read_00156_res) {} //silence unused variable warning
      cgc_free(read_00156);
      if (read_00156_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x39\x37\x0a";
      static unsigned int write_00149_00000_len = 3;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = cgc_append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         cgc_transmit_all(1, write_00149, write_00149_len);
      }
      cgc_free(write_00149);
   } while (0);
   do {
      unsigned char *read_00157;
      unsigned int read_00157_len;
      unsigned int read_00157_ptr = 0;
      //**** delimited read
      static unsigned char read_00157_delim[] = 
         "\x3a\x20";
      read_00157 = NULL;
      read_00157_len = 0;
      int read_00157_res = cgc_delimited_read(0, &read_00157, &read_00157_len, read_00157_delim, 2);
      if (read_00157_res) {} //silence unused variable warning
      cgc_free(read_00157);
      if (read_00157_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00150_00000[] = 
         "\x31\x30\x30\x0a";
      static unsigned int write_00150_00000_len = 4;
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = cgc_append_buf(write_00150, &write_00150_len, write_00150_00000, write_00150_00000_len);
      if (write_00150_len > 0) {
         cgc_transmit_all(1, write_00150, write_00150_len);
      }
      cgc_free(write_00150);
   } while (0);
   do {
      unsigned char *read_00158;
      unsigned int read_00158_len;
      unsigned int read_00158_ptr = 0;
      //**** delimited read
      static unsigned char read_00158_delim[] = 
         "\x3a\x20";
      read_00158 = NULL;
      read_00158_len = 0;
      int read_00158_res = cgc_delimited_read(0, &read_00158, &read_00158_len, read_00158_delim, 2);
      if (read_00158_res) {} //silence unused variable warning
      cgc_free(read_00158);
      if (read_00158_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x31\x39\x36\x0a";
      static unsigned int write_00151_00000_len = 4;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = cgc_append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         cgc_transmit_all(1, write_00151, write_00151_len);
      }
      cgc_free(write_00151);
   } while (0);
   do {
      unsigned char *read_00159;
      unsigned int read_00159_len;
      unsigned int read_00159_ptr = 0;
      //**** delimited read
      static unsigned char read_00159_delim[] = 
         "\x3a\x20";
      read_00159 = NULL;
      read_00159_len = 0;
      int read_00159_res = cgc_delimited_read(0, &read_00159, &read_00159_len, read_00159_delim, 2);
      if (read_00159_res) {} //silence unused variable warning
      cgc_free(read_00159);
      if (read_00159_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00152_00000[] = 
         "\x36\x30\x35\x0a";
      static unsigned int write_00152_00000_len = 4;
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = cgc_append_buf(write_00152, &write_00152_len, write_00152_00000, write_00152_00000_len);
      if (write_00152_len > 0) {
         cgc_transmit_all(1, write_00152, write_00152_len);
      }
      cgc_free(write_00152);
   } while (0);
   do {
      unsigned char *read_00160;
      unsigned int read_00160_len;
      unsigned int read_00160_ptr = 0;
      //**** delimited read
      static unsigned char read_00160_delim[] = 
         "\x3a\x20";
      read_00160 = NULL;
      read_00160_len = 0;
      int read_00160_res = cgc_delimited_read(0, &read_00160, &read_00160_len, read_00160_delim, 2);
      if (read_00160_res) {} //silence unused variable warning
      cgc_free(read_00160);
      if (read_00160_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x33\x36\x38\x0a";
      static unsigned int write_00153_00000_len = 4;
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = cgc_append_buf(write_00153, &write_00153_len, write_00153_00000, write_00153_00000_len);
      if (write_00153_len > 0) {
         cgc_transmit_all(1, write_00153, write_00153_len);
      }
      cgc_free(write_00153);
   } while (0);
   do {
      unsigned char *read_00161;
      unsigned int read_00161_len;
      unsigned int read_00161_ptr = 0;
      //**** delimited read
      static unsigned char read_00161_delim[] = 
         "\x3a\x20";
      read_00161 = NULL;
      read_00161_len = 0;
      int read_00161_res = cgc_delimited_read(0, &read_00161, &read_00161_len, read_00161_delim, 2);
      if (read_00161_res) {} //silence unused variable warning
      cgc_free(read_00161);
      if (read_00161_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00154_00000[] = 
         "\x31\x32\x37\x0a";
      static unsigned int write_00154_00000_len = 4;
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = cgc_append_buf(write_00154, &write_00154_len, write_00154_00000, write_00154_00000_len);
      if (write_00154_len > 0) {
         cgc_transmit_all(1, write_00154, write_00154_len);
      }
      cgc_free(write_00154);
   } while (0);
   do {
      unsigned char *read_00162;
      unsigned int read_00162_len;
      unsigned int read_00162_ptr = 0;
      //**** delimited read
      static unsigned char read_00162_delim[] = 
         "\x3a\x20";
      read_00162 = NULL;
      read_00162_len = 0;
      int read_00162_res = cgc_delimited_read(0, &read_00162, &read_00162_len, read_00162_delim, 2);
      if (read_00162_res) {} //silence unused variable warning
      cgc_free(read_00162);
      if (read_00162_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x38\x35\x0a";
      static unsigned int write_00155_00000_len = 3;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = cgc_append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         cgc_transmit_all(1, write_00155, write_00155_len);
      }
      cgc_free(write_00155);
   } while (0);
   do {
      unsigned char *read_00163;
      unsigned int read_00163_len;
      unsigned int read_00163_ptr = 0;
      //**** delimited read
      static unsigned char read_00163_delim[] = 
         "\x3a\x20";
      read_00163 = NULL;
      read_00163_len = 0;
      int read_00163_res = cgc_delimited_read(0, &read_00163, &read_00163_len, read_00163_delim, 2);
      if (read_00163_res) {} //silence unused variable warning
      cgc_free(read_00163);
      if (read_00163_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00156_00000[] = 
         "\x38\x39\x37\x0a";
      static unsigned int write_00156_00000_len = 4;
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = cgc_append_buf(write_00156, &write_00156_len, write_00156_00000, write_00156_00000_len);
      if (write_00156_len > 0) {
         cgc_transmit_all(1, write_00156, write_00156_len);
      }
      cgc_free(write_00156);
   } while (0);
   do {
      unsigned char *read_00164;
      unsigned int read_00164_len;
      unsigned int read_00164_ptr = 0;
      //**** delimited read
      static unsigned char read_00164_delim[] = 
         "\x3a\x20";
      read_00164 = NULL;
      read_00164_len = 0;
      int read_00164_res = cgc_delimited_read(0, &read_00164, &read_00164_len, read_00164_delim, 2);
      if (read_00164_res) {} //silence unused variable warning
      cgc_free(read_00164);
      if (read_00164_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x33\x37\x31\x0a";
      static unsigned int write_00157_00000_len = 4;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = cgc_append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         cgc_transmit_all(1, write_00157, write_00157_len);
      }
      cgc_free(write_00157);
   } while (0);
   do {
      unsigned char *read_00165;
      unsigned int read_00165_len;
      unsigned int read_00165_ptr = 0;
      //**** delimited read
      static unsigned char read_00165_delim[] = 
         "\x3a\x20";
      read_00165 = NULL;
      read_00165_len = 0;
      int read_00165_res = cgc_delimited_read(0, &read_00165, &read_00165_len, read_00165_delim, 2);
      if (read_00165_res) {} //silence unused variable warning
      cgc_free(read_00165);
      if (read_00165_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00158_00000[] = 
         "\x32\x35\x0a";
      static unsigned int write_00158_00000_len = 3;
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = cgc_append_buf(write_00158, &write_00158_len, write_00158_00000, write_00158_00000_len);
      if (write_00158_len > 0) {
         cgc_transmit_all(1, write_00158, write_00158_len);
      }
      cgc_free(write_00158);
   } while (0);
   do {
      unsigned char *read_00166;
      unsigned int read_00166_len;
      unsigned int read_00166_ptr = 0;
      //**** delimited read
      static unsigned char read_00166_delim[] = 
         "\x3a\x20";
      read_00166 = NULL;
      read_00166_len = 0;
      int read_00166_res = cgc_delimited_read(0, &read_00166, &read_00166_len, read_00166_delim, 2);
      if (read_00166_res) {} //silence unused variable warning
      cgc_free(read_00166);
      if (read_00166_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x32\x37\x38\x0a";
      static unsigned int write_00159_00000_len = 4;
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = cgc_append_buf(write_00159, &write_00159_len, write_00159_00000, write_00159_00000_len);
      if (write_00159_len > 0) {
         cgc_transmit_all(1, write_00159, write_00159_len);
      }
      cgc_free(write_00159);
   } while (0);
   do {
      unsigned char *read_00167;
      unsigned int read_00167_len;
      unsigned int read_00167_ptr = 0;
      //**** delimited read
      static unsigned char read_00167_delim[] = 
         "\x3a\x20";
      read_00167 = NULL;
      read_00167_len = 0;
      int read_00167_res = cgc_delimited_read(0, &read_00167, &read_00167_len, read_00167_delim, 2);
      if (read_00167_res) {} //silence unused variable warning
      cgc_free(read_00167);
      if (read_00167_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00160_00000[] = 
         "\x31\x39\x31\x0a";
      static unsigned int write_00160_00000_len = 4;
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = cgc_append_buf(write_00160, &write_00160_len, write_00160_00000, write_00160_00000_len);
      if (write_00160_len > 0) {
         cgc_transmit_all(1, write_00160, write_00160_len);
      }
      cgc_free(write_00160);
   } while (0);
   do {
      unsigned char *read_00168;
      unsigned int read_00168_len;
      unsigned int read_00168_ptr = 0;
      //**** delimited read
      static unsigned char read_00168_delim[] = 
         "\x3a\x20";
      read_00168 = NULL;
      read_00168_len = 0;
      int read_00168_res = cgc_delimited_read(0, &read_00168, &read_00168_len, read_00168_delim, 2);
      if (read_00168_res) {} //silence unused variable warning
      cgc_free(read_00168);
      if (read_00168_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x31\x37\x33\x0a";
      static unsigned int write_00161_00000_len = 4;
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = cgc_append_buf(write_00161, &write_00161_len, write_00161_00000, write_00161_00000_len);
      if (write_00161_len > 0) {
         cgc_transmit_all(1, write_00161, write_00161_len);
      }
      cgc_free(write_00161);
   } while (0);
   do {
      unsigned char *read_00169;
      unsigned int read_00169_len;
      unsigned int read_00169_ptr = 0;
      //**** delimited read
      static unsigned char read_00169_delim[] = 
         "\x3a\x20";
      read_00169 = NULL;
      read_00169_len = 0;
      int read_00169_res = cgc_delimited_read(0, &read_00169, &read_00169_len, read_00169_delim, 2);
      if (read_00169_res) {} //silence unused variable warning
      cgc_free(read_00169);
      if (read_00169_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00162_00000[] = 
         "\x34\x35\x0a";
      static unsigned int write_00162_00000_len = 3;
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = cgc_append_buf(write_00162, &write_00162_len, write_00162_00000, write_00162_00000_len);
      if (write_00162_len > 0) {
         cgc_transmit_all(1, write_00162, write_00162_len);
      }
      cgc_free(write_00162);
   } while (0);
   do {
      unsigned char *read_00170;
      unsigned int read_00170_len;
      unsigned int read_00170_ptr = 0;
      //**** delimited read
      static unsigned char read_00170_delim[] = 
         "\x3a\x20";
      read_00170 = NULL;
      read_00170_len = 0;
      int read_00170_res = cgc_delimited_read(0, &read_00170, &read_00170_len, read_00170_delim, 2);
      if (read_00170_res) {} //silence unused variable warning
      cgc_free(read_00170);
      if (read_00170_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x36\x32\x31\x0a";
      static unsigned int write_00163_00000_len = 4;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = cgc_append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         cgc_transmit_all(1, write_00163, write_00163_len);
      }
      cgc_free(write_00163);
   } while (0);
   do {
      unsigned char *read_00171;
      unsigned int read_00171_len;
      unsigned int read_00171_ptr = 0;
      //**** delimited read
      static unsigned char read_00171_delim[] = 
         "\x3a\x20";
      read_00171 = NULL;
      read_00171_len = 0;
      int read_00171_res = cgc_delimited_read(0, &read_00171, &read_00171_len, read_00171_delim, 2);
      if (read_00171_res) {} //silence unused variable warning
      cgc_free(read_00171);
      if (read_00171_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00164_00000[] = 
         "\x37\x34\x30\x0a";
      static unsigned int write_00164_00000_len = 4;
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = cgc_append_buf(write_00164, &write_00164_len, write_00164_00000, write_00164_00000_len);
      if (write_00164_len > 0) {
         cgc_transmit_all(1, write_00164, write_00164_len);
      }
      cgc_free(write_00164);
   } while (0);
   do {
      unsigned char *read_00172;
      unsigned int read_00172_len;
      unsigned int read_00172_ptr = 0;
      //**** delimited read
      static unsigned char read_00172_delim[] = 
         "\x3a\x20";
      read_00172 = NULL;
      read_00172_len = 0;
      int read_00172_res = cgc_delimited_read(0, &read_00172, &read_00172_len, read_00172_delim, 2);
      if (read_00172_res) {} //silence unused variable warning
      cgc_free(read_00172);
      if (read_00172_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x35\x39\x39\x0a";
      static unsigned int write_00165_00000_len = 4;
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = cgc_append_buf(write_00165, &write_00165_len, write_00165_00000, write_00165_00000_len);
      if (write_00165_len > 0) {
         cgc_transmit_all(1, write_00165, write_00165_len);
      }
      cgc_free(write_00165);
   } while (0);
   do {
      unsigned char *read_00173;
      unsigned int read_00173_len;
      unsigned int read_00173_ptr = 0;
      //**** delimited read
      static unsigned char read_00173_delim[] = 
         "\x3a\x20";
      read_00173 = NULL;
      read_00173_len = 0;
      int read_00173_res = cgc_delimited_read(0, &read_00173, &read_00173_len, read_00173_delim, 2);
      if (read_00173_res) {} //silence unused variable warning
      cgc_free(read_00173);
      if (read_00173_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00166_00000[] = 
         "\x39\x32\x37\x0a";
      static unsigned int write_00166_00000_len = 4;
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = cgc_append_buf(write_00166, &write_00166_len, write_00166_00000, write_00166_00000_len);
      if (write_00166_len > 0) {
         cgc_transmit_all(1, write_00166, write_00166_len);
      }
      cgc_free(write_00166);
   } while (0);
   do {
      unsigned char *read_00174;
      unsigned int read_00174_len;
      unsigned int read_00174_ptr = 0;
      //**** delimited read
      static unsigned char read_00174_delim[] = 
         "\x3a\x20";
      read_00174 = NULL;
      read_00174_len = 0;
      int read_00174_res = cgc_delimited_read(0, &read_00174, &read_00174_len, read_00174_delim, 2);
      if (read_00174_res) {} //silence unused variable warning
      cgc_free(read_00174);
      if (read_00174_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x38\x34\x33\x0a";
      static unsigned int write_00167_00000_len = 4;
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = cgc_append_buf(write_00167, &write_00167_len, write_00167_00000, write_00167_00000_len);
      if (write_00167_len > 0) {
         cgc_transmit_all(1, write_00167, write_00167_len);
      }
      cgc_free(write_00167);
   } while (0);
   do {
      unsigned char *read_00175;
      unsigned int read_00175_len;
      unsigned int read_00175_ptr = 0;
      //**** delimited read
      static unsigned char read_00175_delim[] = 
         "\x3a\x20";
      read_00175 = NULL;
      read_00175_len = 0;
      int read_00175_res = cgc_delimited_read(0, &read_00175, &read_00175_len, read_00175_delim, 2);
      if (read_00175_res) {} //silence unused variable warning
      cgc_free(read_00175);
      if (read_00175_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00168_00000[] = 
         "\x34\x35\x0a";
      static unsigned int write_00168_00000_len = 3;
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = cgc_append_buf(write_00168, &write_00168_len, write_00168_00000, write_00168_00000_len);
      if (write_00168_len > 0) {
         cgc_transmit_all(1, write_00168, write_00168_len);
      }
      cgc_free(write_00168);
   } while (0);
   do {
      unsigned char *read_00176;
      unsigned int read_00176_len;
      unsigned int read_00176_ptr = 0;
      //**** delimited read
      static unsigned char read_00176_delim[] = 
         "\x3a\x20";
      read_00176 = NULL;
      read_00176_len = 0;
      int read_00176_res = cgc_delimited_read(0, &read_00176, &read_00176_len, read_00176_delim, 2);
      if (read_00176_res) {} //silence unused variable warning
      cgc_free(read_00176);
      if (read_00176_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x39\x31\x35\x0a";
      static unsigned int write_00169_00000_len = 4;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = cgc_append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         cgc_transmit_all(1, write_00169, write_00169_len);
      }
      cgc_free(write_00169);
   } while (0);
   do {
      unsigned char *read_00177;
      unsigned int read_00177_len;
      unsigned int read_00177_ptr = 0;
      //**** delimited read
      static unsigned char read_00177_delim[] = 
         "\x3a\x20";
      read_00177 = NULL;
      read_00177_len = 0;
      int read_00177_res = cgc_delimited_read(0, &read_00177, &read_00177_len, read_00177_delim, 2);
      if (read_00177_res) {} //silence unused variable warning
      cgc_free(read_00177);
      if (read_00177_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00170_00000[] = 
         "\x36\x39\x37\x0a";
      static unsigned int write_00170_00000_len = 4;
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = cgc_append_buf(write_00170, &write_00170_len, write_00170_00000, write_00170_00000_len);
      if (write_00170_len > 0) {
         cgc_transmit_all(1, write_00170, write_00170_len);
      }
      cgc_free(write_00170);
   } while (0);
   do {
      unsigned char *read_00178;
      unsigned int read_00178_len;
      unsigned int read_00178_ptr = 0;
      //**** delimited read
      static unsigned char read_00178_delim[] = 
         "\x3a\x20";
      read_00178 = NULL;
      read_00178_len = 0;
      int read_00178_res = cgc_delimited_read(0, &read_00178, &read_00178_len, read_00178_delim, 2);
      if (read_00178_res) {} //silence unused variable warning
      cgc_free(read_00178);
      if (read_00178_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x33\x33\x33\x0a";
      static unsigned int write_00171_00000_len = 4;
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = cgc_append_buf(write_00171, &write_00171_len, write_00171_00000, write_00171_00000_len);
      if (write_00171_len > 0) {
         cgc_transmit_all(1, write_00171, write_00171_len);
      }
      cgc_free(write_00171);
   } while (0);
   do {
      unsigned char *read_00179;
      unsigned int read_00179_len;
      unsigned int read_00179_ptr = 0;
      //**** delimited read
      static unsigned char read_00179_delim[] = 
         "\x3a\x20";
      read_00179 = NULL;
      read_00179_len = 0;
      int read_00179_res = cgc_delimited_read(0, &read_00179, &read_00179_len, read_00179_delim, 2);
      if (read_00179_res) {} //silence unused variable warning
      cgc_free(read_00179);
      if (read_00179_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00172_00000[] = 
         "\x33\x32\x36\x0a";
      static unsigned int write_00172_00000_len = 4;
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = cgc_append_buf(write_00172, &write_00172_len, write_00172_00000, write_00172_00000_len);
      if (write_00172_len > 0) {
         cgc_transmit_all(1, write_00172, write_00172_len);
      }
      cgc_free(write_00172);
   } while (0);
   do {
      unsigned char *read_00180;
      unsigned int read_00180_len;
      unsigned int read_00180_ptr = 0;
      //**** delimited read
      static unsigned char read_00180_delim[] = 
         "\x3a\x20";
      read_00180 = NULL;
      read_00180_len = 0;
      int read_00180_res = cgc_delimited_read(0, &read_00180, &read_00180_len, read_00180_delim, 2);
      if (read_00180_res) {} //silence unused variable warning
      cgc_free(read_00180);
      if (read_00180_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\x39\x31\x38\x0a";
      static unsigned int write_00173_00000_len = 4;
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = cgc_append_buf(write_00173, &write_00173_len, write_00173_00000, write_00173_00000_len);
      if (write_00173_len > 0) {
         cgc_transmit_all(1, write_00173, write_00173_len);
      }
      cgc_free(write_00173);
   } while (0);
   do {
      unsigned char *read_00181;
      unsigned int read_00181_len;
      unsigned int read_00181_ptr = 0;
      //**** delimited read
      static unsigned char read_00181_delim[] = 
         "\x3a\x20";
      read_00181 = NULL;
      read_00181_len = 0;
      int read_00181_res = cgc_delimited_read(0, &read_00181, &read_00181_len, read_00181_delim, 2);
      if (read_00181_res) {} //silence unused variable warning
      cgc_free(read_00181);
      if (read_00181_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00174_00000[] = 
         "\x31\x35\x36\x0a";
      static unsigned int write_00174_00000_len = 4;
      unsigned char *write_00174 = NULL;
      unsigned int write_00174_len = 0;
      write_00174 = cgc_append_buf(write_00174, &write_00174_len, write_00174_00000, write_00174_00000_len);
      if (write_00174_len > 0) {
         cgc_transmit_all(1, write_00174, write_00174_len);
      }
      cgc_free(write_00174);
   } while (0);
   do {
      unsigned char *read_00182;
      unsigned int read_00182_len;
      unsigned int read_00182_ptr = 0;
      //**** delimited read
      static unsigned char read_00182_delim[] = 
         "\x3a\x20";
      read_00182 = NULL;
      read_00182_len = 0;
      int read_00182_res = cgc_delimited_read(0, &read_00182, &read_00182_len, read_00182_delim, 2);
      if (read_00182_res) {} //silence unused variable warning
      cgc_free(read_00182);
      if (read_00182_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x32\x32\x31\x0a";
      static unsigned int write_00175_00000_len = 4;
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = cgc_append_buf(write_00175, &write_00175_len, write_00175_00000, write_00175_00000_len);
      if (write_00175_len > 0) {
         cgc_transmit_all(1, write_00175, write_00175_len);
      }
      cgc_free(write_00175);
   } while (0);
   do {
      unsigned char *read_00183;
      unsigned int read_00183_len;
      unsigned int read_00183_ptr = 0;
      //**** delimited read
      static unsigned char read_00183_delim[] = 
         "\x3a\x20";
      read_00183 = NULL;
      read_00183_len = 0;
      int read_00183_res = cgc_delimited_read(0, &read_00183, &read_00183_len, read_00183_delim, 2);
      if (read_00183_res) {} //silence unused variable warning
      cgc_free(read_00183);
      if (read_00183_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00176_00000[] = 
         "\x33\x32\x39\x0a";
      static unsigned int write_00176_00000_len = 4;
      unsigned char *write_00176 = NULL;
      unsigned int write_00176_len = 0;
      write_00176 = cgc_append_buf(write_00176, &write_00176_len, write_00176_00000, write_00176_00000_len);
      if (write_00176_len > 0) {
         cgc_transmit_all(1, write_00176, write_00176_len);
      }
      cgc_free(write_00176);
   } while (0);
   do {
      unsigned char *read_00184;
      unsigned int read_00184_len;
      unsigned int read_00184_ptr = 0;
      //**** delimited read
      static unsigned char read_00184_delim[] = 
         "\x3a\x20";
      read_00184 = NULL;
      read_00184_len = 0;
      int read_00184_res = cgc_delimited_read(0, &read_00184, &read_00184_len, read_00184_delim, 2);
      if (read_00184_res) {} //silence unused variable warning
      cgc_free(read_00184);
      if (read_00184_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x38\x34\x39\x0a";
      static unsigned int write_00177_00000_len = 4;
      unsigned char *write_00177 = NULL;
      unsigned int write_00177_len = 0;
      write_00177 = cgc_append_buf(write_00177, &write_00177_len, write_00177_00000, write_00177_00000_len);
      if (write_00177_len > 0) {
         cgc_transmit_all(1, write_00177, write_00177_len);
      }
      cgc_free(write_00177);
   } while (0);
   do {
      unsigned char *read_00185;
      unsigned int read_00185_len;
      unsigned int read_00185_ptr = 0;
      //**** delimited read
      static unsigned char read_00185_delim[] = 
         "\x3a\x20";
      read_00185 = NULL;
      read_00185_len = 0;
      int read_00185_res = cgc_delimited_read(0, &read_00185, &read_00185_len, read_00185_delim, 2);
      if (read_00185_res) {} //silence unused variable warning
      cgc_free(read_00185);
      if (read_00185_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00178_00000[] = 
         "\x32\x39\x32\x0a";
      static unsigned int write_00178_00000_len = 4;
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = cgc_append_buf(write_00178, &write_00178_len, write_00178_00000, write_00178_00000_len);
      if (write_00178_len > 0) {
         cgc_transmit_all(1, write_00178, write_00178_len);
      }
      cgc_free(write_00178);
   } while (0);
   do {
      unsigned char *read_00186;
      unsigned int read_00186_len;
      unsigned int read_00186_ptr = 0;
      //**** delimited read
      static unsigned char read_00186_delim[] = 
         "\x3a\x20";
      read_00186 = NULL;
      read_00186_len = 0;
      int read_00186_res = cgc_delimited_read(0, &read_00186, &read_00186_len, read_00186_delim, 2);
      if (read_00186_res) {} //silence unused variable warning
      cgc_free(read_00186);
      if (read_00186_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\x35\x32\x36\x0a";
      static unsigned int write_00179_00000_len = 4;
      unsigned char *write_00179 = NULL;
      unsigned int write_00179_len = 0;
      write_00179 = cgc_append_buf(write_00179, &write_00179_len, write_00179_00000, write_00179_00000_len);
      if (write_00179_len > 0) {
         cgc_transmit_all(1, write_00179, write_00179_len);
      }
      cgc_free(write_00179);
   } while (0);
   do {
      unsigned char *read_00187;
      unsigned int read_00187_len;
      unsigned int read_00187_ptr = 0;
      //**** delimited read
      static unsigned char read_00187_delim[] = 
         "\x3a\x20";
      read_00187 = NULL;
      read_00187_len = 0;
      int read_00187_res = cgc_delimited_read(0, &read_00187, &read_00187_len, read_00187_delim, 2);
      if (read_00187_res) {} //silence unused variable warning
      cgc_free(read_00187);
      if (read_00187_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00180_00000[] = 
         "\x31\x36\x38\x0a";
      static unsigned int write_00180_00000_len = 4;
      unsigned char *write_00180 = NULL;
      unsigned int write_00180_len = 0;
      write_00180 = cgc_append_buf(write_00180, &write_00180_len, write_00180_00000, write_00180_00000_len);
      if (write_00180_len > 0) {
         cgc_transmit_all(1, write_00180, write_00180_len);
      }
      cgc_free(write_00180);
   } while (0);
   do {
      unsigned char *read_00188;
      unsigned int read_00188_len;
      unsigned int read_00188_ptr = 0;
      //**** delimited read
      static unsigned char read_00188_delim[] = 
         "\x3a\x20";
      read_00188 = NULL;
      read_00188_len = 0;
      int read_00188_res = cgc_delimited_read(0, &read_00188, &read_00188_len, read_00188_delim, 2);
      if (read_00188_res) {} //silence unused variable warning
      cgc_free(read_00188);
      if (read_00188_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x34\x39\x36\x0a";
      static unsigned int write_00181_00000_len = 4;
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = cgc_append_buf(write_00181, &write_00181_len, write_00181_00000, write_00181_00000_len);
      if (write_00181_len > 0) {
         cgc_transmit_all(1, write_00181, write_00181_len);
      }
      cgc_free(write_00181);
   } while (0);
   do {
      unsigned char *read_00189;
      unsigned int read_00189_len;
      unsigned int read_00189_ptr = 0;
      //**** delimited read
      static unsigned char read_00189_delim[] = 
         "\x3a\x20";
      read_00189 = NULL;
      read_00189_len = 0;
      int read_00189_res = cgc_delimited_read(0, &read_00189, &read_00189_len, read_00189_delim, 2);
      if (read_00189_res) {} //silence unused variable warning
      cgc_free(read_00189);
      if (read_00189_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00182_00000[] = 
         "\x37\x39\x0a";
      static unsigned int write_00182_00000_len = 3;
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = cgc_append_buf(write_00182, &write_00182_len, write_00182_00000, write_00182_00000_len);
      if (write_00182_len > 0) {
         cgc_transmit_all(1, write_00182, write_00182_len);
      }
      cgc_free(write_00182);
   } while (0);
   do {
      unsigned char *read_00190;
      unsigned int read_00190_len;
      unsigned int read_00190_ptr = 0;
      //**** delimited read
      static unsigned char read_00190_delim[] = 
         "\x3a\x20";
      read_00190 = NULL;
      read_00190_len = 0;
      int read_00190_res = cgc_delimited_read(0, &read_00190, &read_00190_len, read_00190_delim, 2);
      if (read_00190_res) {} //silence unused variable warning
      cgc_free(read_00190);
      if (read_00190_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00183_00000[] = 
         "\x32\x36\x35\x0a";
      static unsigned int write_00183_00000_len = 4;
      unsigned char *write_00183 = NULL;
      unsigned int write_00183_len = 0;
      write_00183 = cgc_append_buf(write_00183, &write_00183_len, write_00183_00000, write_00183_00000_len);
      if (write_00183_len > 0) {
         cgc_transmit_all(1, write_00183, write_00183_len);
      }
      cgc_free(write_00183);
   } while (0);
   do {
      unsigned char *read_00191;
      unsigned int read_00191_len;
      unsigned int read_00191_ptr = 0;
      //**** delimited read
      static unsigned char read_00191_delim[] = 
         "\x3a\x20";
      read_00191 = NULL;
      read_00191_len = 0;
      int read_00191_res = cgc_delimited_read(0, &read_00191, &read_00191_len, read_00191_delim, 2);
      if (read_00191_res) {} //silence unused variable warning
      cgc_free(read_00191);
      if (read_00191_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00184_00000[] = 
         "\x31\x36\x39\x0a";
      static unsigned int write_00184_00000_len = 4;
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = cgc_append_buf(write_00184, &write_00184_len, write_00184_00000, write_00184_00000_len);
      if (write_00184_len > 0) {
         cgc_transmit_all(1, write_00184, write_00184_len);
      }
      cgc_free(write_00184);
   } while (0);
   do {
      unsigned char *read_00192;
      unsigned int read_00192_len;
      unsigned int read_00192_ptr = 0;
      //**** delimited read
      static unsigned char read_00192_delim[] = 
         "\x3a\x20";
      read_00192 = NULL;
      read_00192_len = 0;
      int read_00192_res = cgc_delimited_read(0, &read_00192, &read_00192_len, read_00192_delim, 2);
      if (read_00192_res) {} //silence unused variable warning
      cgc_free(read_00192);
      if (read_00192_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00185_00000[] = 
         "\x31\x32\x36\x0a";
      static unsigned int write_00185_00000_len = 4;
      unsigned char *write_00185 = NULL;
      unsigned int write_00185_len = 0;
      write_00185 = cgc_append_buf(write_00185, &write_00185_len, write_00185_00000, write_00185_00000_len);
      if (write_00185_len > 0) {
         cgc_transmit_all(1, write_00185, write_00185_len);
      }
      cgc_free(write_00185);
   } while (0);
   do {
      unsigned char *read_00193;
      unsigned int read_00193_len;
      unsigned int read_00193_ptr = 0;
      //**** delimited read
      static unsigned char read_00193_delim[] = 
         "\x3a\x20";
      read_00193 = NULL;
      read_00193_len = 0;
      int read_00193_res = cgc_delimited_read(0, &read_00193, &read_00193_len, read_00193_delim, 2);
      if (read_00193_res) {} //silence unused variable warning
      cgc_free(read_00193);
      if (read_00193_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00186_00000[] = 
         "\x36\x32\x39\x0a";
      static unsigned int write_00186_00000_len = 4;
      unsigned char *write_00186 = NULL;
      unsigned int write_00186_len = 0;
      write_00186 = cgc_append_buf(write_00186, &write_00186_len, write_00186_00000, write_00186_00000_len);
      if (write_00186_len > 0) {
         cgc_transmit_all(1, write_00186, write_00186_len);
      }
      cgc_free(write_00186);
   } while (0);
   do {
      unsigned char *read_00194;
      unsigned int read_00194_len;
      unsigned int read_00194_ptr = 0;
      //**** delimited read
      static unsigned char read_00194_delim[] = 
         "\x3a\x20";
      read_00194 = NULL;
      read_00194_len = 0;
      int read_00194_res = cgc_delimited_read(0, &read_00194, &read_00194_len, read_00194_delim, 2);
      if (read_00194_res) {} //silence unused variable warning
      cgc_free(read_00194);
      if (read_00194_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00187_00000[] = 
         "\x31\x31\x0a";
      static unsigned int write_00187_00000_len = 3;
      unsigned char *write_00187 = NULL;
      unsigned int write_00187_len = 0;
      write_00187 = cgc_append_buf(write_00187, &write_00187_len, write_00187_00000, write_00187_00000_len);
      if (write_00187_len > 0) {
         cgc_transmit_all(1, write_00187, write_00187_len);
      }
      cgc_free(write_00187);
   } while (0);
   do {
      unsigned char *read_00195;
      unsigned int read_00195_len;
      unsigned int read_00195_ptr = 0;
      //**** delimited read
      static unsigned char read_00195_delim[] = 
         "\x3a\x20";
      read_00195 = NULL;
      read_00195_len = 0;
      int read_00195_res = cgc_delimited_read(0, &read_00195, &read_00195_len, read_00195_delim, 2);
      if (read_00195_res) {} //silence unused variable warning
      cgc_free(read_00195);
      if (read_00195_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00188_00000[] = 
         "\x31\x34\x31\x0a";
      static unsigned int write_00188_00000_len = 4;
      unsigned char *write_00188 = NULL;
      unsigned int write_00188_len = 0;
      write_00188 = cgc_append_buf(write_00188, &write_00188_len, write_00188_00000, write_00188_00000_len);
      if (write_00188_len > 0) {
         cgc_transmit_all(1, write_00188, write_00188_len);
      }
      cgc_free(write_00188);
   } while (0);
   do {
      unsigned char *read_00196;
      unsigned int read_00196_len;
      unsigned int read_00196_ptr = 0;
      //**** delimited read
      static unsigned char read_00196_delim[] = 
         "\x3a\x20";
      read_00196 = NULL;
      read_00196_len = 0;
      int read_00196_res = cgc_delimited_read(0, &read_00196, &read_00196_len, read_00196_delim, 2);
      if (read_00196_res) {} //silence unused variable warning
      cgc_free(read_00196);
      if (read_00196_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00189_00000[] = 
         "\x31\x35\x30\x0a";
      static unsigned int write_00189_00000_len = 4;
      unsigned char *write_00189 = NULL;
      unsigned int write_00189_len = 0;
      write_00189 = cgc_append_buf(write_00189, &write_00189_len, write_00189_00000, write_00189_00000_len);
      if (write_00189_len > 0) {
         cgc_transmit_all(1, write_00189, write_00189_len);
      }
      cgc_free(write_00189);
   } while (0);
   do {
      unsigned char *read_00197;
      unsigned int read_00197_len;
      unsigned int read_00197_ptr = 0;
      //**** delimited read
      static unsigned char read_00197_delim[] = 
         "\x3a\x20";
      read_00197 = NULL;
      read_00197_len = 0;
      int read_00197_res = cgc_delimited_read(0, &read_00197, &read_00197_len, read_00197_delim, 2);
      if (read_00197_res) {} //silence unused variable warning
      cgc_free(read_00197);
      if (read_00197_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00190_00000[] = 
         "\x34\x36\x0a";
      static unsigned int write_00190_00000_len = 3;
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = cgc_append_buf(write_00190, &write_00190_len, write_00190_00000, write_00190_00000_len);
      if (write_00190_len > 0) {
         cgc_transmit_all(1, write_00190, write_00190_len);
      }
      cgc_free(write_00190);
   } while (0);
   do {
      unsigned char *read_00198;
      unsigned int read_00198_len;
      unsigned int read_00198_ptr = 0;
      //**** delimited read
      static unsigned char read_00198_delim[] = 
         "\x3a\x20";
      read_00198 = NULL;
      read_00198_len = 0;
      int read_00198_res = cgc_delimited_read(0, &read_00198, &read_00198_len, read_00198_delim, 2);
      if (read_00198_res) {} //silence unused variable warning
      cgc_free(read_00198);
      if (read_00198_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00191_00000[] = 
         "\x31\x38\x38\x0a";
      static unsigned int write_00191_00000_len = 4;
      unsigned char *write_00191 = NULL;
      unsigned int write_00191_len = 0;
      write_00191 = cgc_append_buf(write_00191, &write_00191_len, write_00191_00000, write_00191_00000_len);
      if (write_00191_len > 0) {
         cgc_transmit_all(1, write_00191, write_00191_len);
      }
      cgc_free(write_00191);
   } while (0);
   do {
      unsigned char *read_00199;
      unsigned int read_00199_len;
      unsigned int read_00199_ptr = 0;
      //**** delimited read
      static unsigned char read_00199_delim[] = 
         "\x3a\x20";
      read_00199 = NULL;
      read_00199_len = 0;
      int read_00199_res = cgc_delimited_read(0, &read_00199, &read_00199_len, read_00199_delim, 2);
      if (read_00199_res) {} //silence unused variable warning
      cgc_free(read_00199);
      if (read_00199_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00192_00000[] = 
         "\x38\x31\x36\x0a";
      static unsigned int write_00192_00000_len = 4;
      unsigned char *write_00192 = NULL;
      unsigned int write_00192_len = 0;
      write_00192 = cgc_append_buf(write_00192, &write_00192_len, write_00192_00000, write_00192_00000_len);
      if (write_00192_len > 0) {
         cgc_transmit_all(1, write_00192, write_00192_len);
      }
      cgc_free(write_00192);
   } while (0);
   do {
      unsigned char *read_00200;
      unsigned int read_00200_len;
      unsigned int read_00200_ptr = 0;
      //**** delimited read
      static unsigned char read_00200_delim[] = 
         "\x3a\x20";
      read_00200 = NULL;
      read_00200_len = 0;
      int read_00200_res = cgc_delimited_read(0, &read_00200, &read_00200_len, read_00200_delim, 2);
      if (read_00200_res) {} //silence unused variable warning
      cgc_free(read_00200);
      if (read_00200_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00193_00000[] = 
         "\x33\x31\x36\x0a";
      static unsigned int write_00193_00000_len = 4;
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = cgc_append_buf(write_00193, &write_00193_len, write_00193_00000, write_00193_00000_len);
      if (write_00193_len > 0) {
         cgc_transmit_all(1, write_00193, write_00193_len);
      }
      cgc_free(write_00193);
   } while (0);
   do {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** delimited read
      static unsigned char read_00201_delim[] = 
         "\x3a\x20";
      read_00201 = NULL;
      read_00201_len = 0;
      int read_00201_res = cgc_delimited_read(0, &read_00201, &read_00201_len, read_00201_delim, 2);
      if (read_00201_res) {} //silence unused variable warning
      cgc_free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00194_00000[] = 
         "\x34\x30\x38\x0a";
      static unsigned int write_00194_00000_len = 4;
      unsigned char *write_00194 = NULL;
      unsigned int write_00194_len = 0;
      write_00194 = cgc_append_buf(write_00194, &write_00194_len, write_00194_00000, write_00194_00000_len);
      if (write_00194_len > 0) {
         cgc_transmit_all(1, write_00194, write_00194_len);
      }
      cgc_free(write_00194);
   } while (0);
   do {
      unsigned char *read_00202;
      unsigned int read_00202_len;
      unsigned int read_00202_ptr = 0;
      //**** delimited read
      static unsigned char read_00202_delim[] = 
         "\x3a\x20";
      read_00202 = NULL;
      read_00202_len = 0;
      int read_00202_res = cgc_delimited_read(0, &read_00202, &read_00202_len, read_00202_delim, 2);
      if (read_00202_res) {} //silence unused variable warning
      cgc_free(read_00202);
      if (read_00202_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00195_00000[] = 
         "\x34\x37\x0a";
      static unsigned int write_00195_00000_len = 3;
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = cgc_append_buf(write_00195, &write_00195_len, write_00195_00000, write_00195_00000_len);
      if (write_00195_len > 0) {
         cgc_transmit_all(1, write_00195, write_00195_len);
      }
      cgc_free(write_00195);
   } while (0);
   do {
      unsigned char *read_00203;
      unsigned int read_00203_len;
      unsigned int read_00203_ptr = 0;
      //**** delimited read
      static unsigned char read_00203_delim[] = 
         "\x3a\x20";
      read_00203 = NULL;
      read_00203_len = 0;
      int read_00203_res = cgc_delimited_read(0, &read_00203, &read_00203_len, read_00203_delim, 2);
      if (read_00203_res) {} //silence unused variable warning
      cgc_free(read_00203);
      if (read_00203_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00196_00000[] = 
         "\x35\x37\x33\x0a";
      static unsigned int write_00196_00000_len = 4;
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = cgc_append_buf(write_00196, &write_00196_len, write_00196_00000, write_00196_00000_len);
      if (write_00196_len > 0) {
         cgc_transmit_all(1, write_00196, write_00196_len);
      }
      cgc_free(write_00196);
   } while (0);
   do {
      unsigned char *read_00204;
      unsigned int read_00204_len;
      unsigned int read_00204_ptr = 0;
      //**** delimited read
      static unsigned char read_00204_delim[] = 
         "\x3a\x20";
      read_00204 = NULL;
      read_00204_len = 0;
      int read_00204_res = cgc_delimited_read(0, &read_00204, &read_00204_len, read_00204_delim, 2);
      if (read_00204_res) {} //silence unused variable warning
      cgc_free(read_00204);
      if (read_00204_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00197_00000[] = 
         "\x36\x30\x32\x0a";
      static unsigned int write_00197_00000_len = 4;
      unsigned char *write_00197 = NULL;
      unsigned int write_00197_len = 0;
      write_00197 = cgc_append_buf(write_00197, &write_00197_len, write_00197_00000, write_00197_00000_len);
      if (write_00197_len > 0) {
         cgc_transmit_all(1, write_00197, write_00197_len);
      }
      cgc_free(write_00197);
   } while (0);
   do {
      unsigned char *read_00205;
      unsigned int read_00205_len;
      unsigned int read_00205_ptr = 0;
      //**** delimited read
      static unsigned char read_00205_delim[] = 
         "\x3a\x20";
      read_00205 = NULL;
      read_00205_len = 0;
      int read_00205_res = cgc_delimited_read(0, &read_00205, &read_00205_len, read_00205_delim, 2);
      if (read_00205_res) {} //silence unused variable warning
      cgc_free(read_00205);
      if (read_00205_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00198_00000[] = 
         "\x33\x38\x33\x0a";
      static unsigned int write_00198_00000_len = 4;
      unsigned char *write_00198 = NULL;
      unsigned int write_00198_len = 0;
      write_00198 = cgc_append_buf(write_00198, &write_00198_len, write_00198_00000, write_00198_00000_len);
      if (write_00198_len > 0) {
         cgc_transmit_all(1, write_00198, write_00198_len);
      }
      cgc_free(write_00198);
   } while (0);
   do {
      unsigned char *read_00206;
      unsigned int read_00206_len;
      unsigned int read_00206_ptr = 0;
      //**** delimited read
      static unsigned char read_00206_delim[] = 
         "\x3a\x20";
      read_00206 = NULL;
      read_00206_len = 0;
      int read_00206_res = cgc_delimited_read(0, &read_00206, &read_00206_len, read_00206_delim, 2);
      if (read_00206_res) {} //silence unused variable warning
      cgc_free(read_00206);
      if (read_00206_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00199_00000[] = 
         "\x32\x37\x38\x0a";
      static unsigned int write_00199_00000_len = 4;
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = cgc_append_buf(write_00199, &write_00199_len, write_00199_00000, write_00199_00000_len);
      if (write_00199_len > 0) {
         cgc_transmit_all(1, write_00199, write_00199_len);
      }
      cgc_free(write_00199);
   } while (0);
   do {
      unsigned char *read_00207;
      unsigned int read_00207_len;
      unsigned int read_00207_ptr = 0;
      //**** delimited read
      static unsigned char read_00207_delim[] = 
         "\x3a\x20";
      read_00207 = NULL;
      read_00207_len = 0;
      int read_00207_res = cgc_delimited_read(0, &read_00207, &read_00207_len, read_00207_delim, 2);
      if (read_00207_res) {} //silence unused variable warning
      cgc_free(read_00207);
      if (read_00207_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00200_00000[] = 
         "\x31\x34\x37\x0a";
      static unsigned int write_00200_00000_len = 4;
      unsigned char *write_00200 = NULL;
      unsigned int write_00200_len = 0;
      write_00200 = cgc_append_buf(write_00200, &write_00200_len, write_00200_00000, write_00200_00000_len);
      if (write_00200_len > 0) {
         cgc_transmit_all(1, write_00200, write_00200_len);
      }
      cgc_free(write_00200);
   } while (0);
   do {
      unsigned char *read_00208;
      unsigned int read_00208_len;
      unsigned int read_00208_ptr = 0;
      //**** delimited read
      static unsigned char read_00208_delim[] = 
         "\x3a\x20";
      read_00208 = NULL;
      read_00208_len = 0;
      int read_00208_res = cgc_delimited_read(0, &read_00208, &read_00208_len, read_00208_delim, 2);
      if (read_00208_res) {} //silence unused variable warning
      cgc_free(read_00208);
      if (read_00208_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00201_00000[] = 
         "\x39\x37\x33\x0a";
      static unsigned int write_00201_00000_len = 4;
      unsigned char *write_00201 = NULL;
      unsigned int write_00201_len = 0;
      write_00201 = cgc_append_buf(write_00201, &write_00201_len, write_00201_00000, write_00201_00000_len);
      if (write_00201_len > 0) {
         cgc_transmit_all(1, write_00201, write_00201_len);
      }
      cgc_free(write_00201);
   } while (0);
   do {
      unsigned char *read_00209;
      unsigned int read_00209_len;
      unsigned int read_00209_ptr = 0;
      //**** delimited read
      static unsigned char read_00209_delim[] = 
         "\x3a\x20";
      read_00209 = NULL;
      read_00209_len = 0;
      int read_00209_res = cgc_delimited_read(0, &read_00209, &read_00209_len, read_00209_delim, 2);
      if (read_00209_res) {} //silence unused variable warning
      cgc_free(read_00209);
      if (read_00209_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00202_00000[] = 
         "\x34\x31\x37\x0a";
      static unsigned int write_00202_00000_len = 4;
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = cgc_append_buf(write_00202, &write_00202_len, write_00202_00000, write_00202_00000_len);
      if (write_00202_len > 0) {
         cgc_transmit_all(1, write_00202, write_00202_len);
      }
      cgc_free(write_00202);
   } while (0);
   do {
      unsigned char *read_00210;
      unsigned int read_00210_len;
      unsigned int read_00210_ptr = 0;
      //**** delimited read
      static unsigned char read_00210_delim[] = 
         "\x3a\x20";
      read_00210 = NULL;
      read_00210_len = 0;
      int read_00210_res = cgc_delimited_read(0, &read_00210, &read_00210_len, read_00210_delim, 2);
      if (read_00210_res) {} //silence unused variable warning
      cgc_free(read_00210);
      if (read_00210_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00203_00000[] = 
         "\x33\x37\x38\x0a";
      static unsigned int write_00203_00000_len = 4;
      unsigned char *write_00203 = NULL;
      unsigned int write_00203_len = 0;
      write_00203 = cgc_append_buf(write_00203, &write_00203_len, write_00203_00000, write_00203_00000_len);
      if (write_00203_len > 0) {
         cgc_transmit_all(1, write_00203, write_00203_len);
      }
      cgc_free(write_00203);
   } while (0);
   do {
      unsigned char *read_00211;
      unsigned int read_00211_len;
      unsigned int read_00211_ptr = 0;
      //**** delimited read
      static unsigned char read_00211_delim[] = 
         "\x3a\x20";
      read_00211 = NULL;
      read_00211_len = 0;
      int read_00211_res = cgc_delimited_read(0, &read_00211, &read_00211_len, read_00211_delim, 2);
      if (read_00211_res) {} //silence unused variable warning
      cgc_free(read_00211);
      if (read_00211_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00204_00000[] = 
         "\x39\x30\x37\x0a";
      static unsigned int write_00204_00000_len = 4;
      unsigned char *write_00204 = NULL;
      unsigned int write_00204_len = 0;
      write_00204 = cgc_append_buf(write_00204, &write_00204_len, write_00204_00000, write_00204_00000_len);
      if (write_00204_len > 0) {
         cgc_transmit_all(1, write_00204, write_00204_len);
      }
      cgc_free(write_00204);
   } while (0);
   do {
      unsigned char *read_00212;
      unsigned int read_00212_len;
      unsigned int read_00212_ptr = 0;
      //**** delimited read
      static unsigned char read_00212_delim[] = 
         "\x3a\x20";
      read_00212 = NULL;
      read_00212_len = 0;
      int read_00212_res = cgc_delimited_read(0, &read_00212, &read_00212_len, read_00212_delim, 2);
      if (read_00212_res) {} //silence unused variable warning
      cgc_free(read_00212);
      if (read_00212_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00205_00000[] = 
         "\x31\x30\x37\x0a";
      static unsigned int write_00205_00000_len = 4;
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = cgc_append_buf(write_00205, &write_00205_len, write_00205_00000, write_00205_00000_len);
      if (write_00205_len > 0) {
         cgc_transmit_all(1, write_00205, write_00205_len);
      }
      cgc_free(write_00205);
   } while (0);
   do {
      unsigned char *read_00213;
      unsigned int read_00213_len;
      unsigned int read_00213_ptr = 0;
      //**** delimited read
      static unsigned char read_00213_delim[] = 
         "\x3a\x20";
      read_00213 = NULL;
      read_00213_len = 0;
      int read_00213_res = cgc_delimited_read(0, &read_00213, &read_00213_len, read_00213_delim, 2);
      if (read_00213_res) {} //silence unused variable warning
      cgc_free(read_00213);
      if (read_00213_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00206_00000[] = 
         "\x33\x32\x0a";
      static unsigned int write_00206_00000_len = 3;
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = cgc_append_buf(write_00206, &write_00206_len, write_00206_00000, write_00206_00000_len);
      if (write_00206_len > 0) {
         cgc_transmit_all(1, write_00206, write_00206_len);
      }
      cgc_free(write_00206);
   } while (0);
   do {
      unsigned char *read_00214;
      unsigned int read_00214_len;
      unsigned int read_00214_ptr = 0;
      //**** delimited read
      static unsigned char read_00214_delim[] = 
         "\x3a\x20";
      read_00214 = NULL;
      read_00214_len = 0;
      int read_00214_res = cgc_delimited_read(0, &read_00214, &read_00214_len, read_00214_delim, 2);
      if (read_00214_res) {} //silence unused variable warning
      cgc_free(read_00214);
      if (read_00214_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00207_00000[] = 
         "\x34\x35\x33\x0a";
      static unsigned int write_00207_00000_len = 4;
      unsigned char *write_00207 = NULL;
      unsigned int write_00207_len = 0;
      write_00207 = cgc_append_buf(write_00207, &write_00207_len, write_00207_00000, write_00207_00000_len);
      if (write_00207_len > 0) {
         cgc_transmit_all(1, write_00207, write_00207_len);
      }
      cgc_free(write_00207);
   } while (0);
   do {
      unsigned char *read_00215;
      unsigned int read_00215_len;
      unsigned int read_00215_ptr = 0;
      //**** delimited read
      static unsigned char read_00215_delim[] = 
         "\x3a\x20";
      read_00215 = NULL;
      read_00215_len = 0;
      int read_00215_res = cgc_delimited_read(0, &read_00215, &read_00215_len, read_00215_delim, 2);
      if (read_00215_res) {} //silence unused variable warning
      cgc_free(read_00215);
      if (read_00215_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00208_00000[] = 
         "\x37\x34\x37\x0a";
      static unsigned int write_00208_00000_len = 4;
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = cgc_append_buf(write_00208, &write_00208_len, write_00208_00000, write_00208_00000_len);
      if (write_00208_len > 0) {
         cgc_transmit_all(1, write_00208, write_00208_len);
      }
      cgc_free(write_00208);
   } while (0);
   do {
      unsigned char *read_00216;
      unsigned int read_00216_len;
      unsigned int read_00216_ptr = 0;
      //**** delimited read
      static unsigned char read_00216_delim[] = 
         "\x3a\x20";
      read_00216 = NULL;
      read_00216_len = 0;
      int read_00216_res = cgc_delimited_read(0, &read_00216, &read_00216_len, read_00216_delim, 2);
      if (read_00216_res) {} //silence unused variable warning
      cgc_free(read_00216);
      if (read_00216_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00209_00000[] = 
         "\x34\x39\x34\x0a";
      static unsigned int write_00209_00000_len = 4;
      unsigned char *write_00209 = NULL;
      unsigned int write_00209_len = 0;
      write_00209 = cgc_append_buf(write_00209, &write_00209_len, write_00209_00000, write_00209_00000_len);
      if (write_00209_len > 0) {
         cgc_transmit_all(1, write_00209, write_00209_len);
      }
      cgc_free(write_00209);
   } while (0);
   do {
      unsigned char *read_00217;
      unsigned int read_00217_len;
      unsigned int read_00217_ptr = 0;
      //**** delimited read
      static unsigned char read_00217_delim[] = 
         "\x3a\x20";
      read_00217 = NULL;
      read_00217_len = 0;
      int read_00217_res = cgc_delimited_read(0, &read_00217, &read_00217_len, read_00217_delim, 2);
      if (read_00217_res) {} //silence unused variable warning
      cgc_free(read_00217);
      if (read_00217_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00210_00000[] = 
         "\x39\x34\x37\x0a";
      static unsigned int write_00210_00000_len = 4;
      unsigned char *write_00210 = NULL;
      unsigned int write_00210_len = 0;
      write_00210 = cgc_append_buf(write_00210, &write_00210_len, write_00210_00000, write_00210_00000_len);
      if (write_00210_len > 0) {
         cgc_transmit_all(1, write_00210, write_00210_len);
      }
      cgc_free(write_00210);
   } while (0);
   do {
      unsigned char *read_00218;
      unsigned int read_00218_len;
      unsigned int read_00218_ptr = 0;
      //**** delimited read
      static unsigned char read_00218_delim[] = 
         "\x3a\x20";
      read_00218 = NULL;
      read_00218_len = 0;
      int read_00218_res = cgc_delimited_read(0, &read_00218, &read_00218_len, read_00218_delim, 2);
      if (read_00218_res) {} //silence unused variable warning
      cgc_free(read_00218);
      if (read_00218_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00211_00000[] = 
         "\x34\x35\x35\x0a";
      static unsigned int write_00211_00000_len = 4;
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = cgc_append_buf(write_00211, &write_00211_len, write_00211_00000, write_00211_00000_len);
      if (write_00211_len > 0) {
         cgc_transmit_all(1, write_00211, write_00211_len);
      }
      cgc_free(write_00211);
   } while (0);
   do {
      unsigned char *read_00219;
      unsigned int read_00219_len;
      unsigned int read_00219_ptr = 0;
      //**** delimited read
      static unsigned char read_00219_delim[] = 
         "\x3a\x20";
      read_00219 = NULL;
      read_00219_len = 0;
      int read_00219_res = cgc_delimited_read(0, &read_00219, &read_00219_len, read_00219_delim, 2);
      if (read_00219_res) {} //silence unused variable warning
      cgc_free(read_00219);
      if (read_00219_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00212_00000[] = 
         "\x32\x32\x32\x0a";
      static unsigned int write_00212_00000_len = 4;
      unsigned char *write_00212 = NULL;
      unsigned int write_00212_len = 0;
      write_00212 = cgc_append_buf(write_00212, &write_00212_len, write_00212_00000, write_00212_00000_len);
      if (write_00212_len > 0) {
         cgc_transmit_all(1, write_00212, write_00212_len);
      }
      cgc_free(write_00212);
   } while (0);
   do {
      unsigned char *read_00220;
      unsigned int read_00220_len;
      unsigned int read_00220_ptr = 0;
      //**** delimited read
      static unsigned char read_00220_delim[] = 
         "\x3a\x20";
      read_00220 = NULL;
      read_00220_len = 0;
      int read_00220_res = cgc_delimited_read(0, &read_00220, &read_00220_len, read_00220_delim, 2);
      if (read_00220_res) {} //silence unused variable warning
      cgc_free(read_00220);
      if (read_00220_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00213_00000[] = 
         "\x33\x30\x39\x0a";
      static unsigned int write_00213_00000_len = 4;
      unsigned char *write_00213 = NULL;
      unsigned int write_00213_len = 0;
      write_00213 = cgc_append_buf(write_00213, &write_00213_len, write_00213_00000, write_00213_00000_len);
      if (write_00213_len > 0) {
         cgc_transmit_all(1, write_00213, write_00213_len);
      }
      cgc_free(write_00213);
   } while (0);
   do {
      unsigned char *read_00221;
      unsigned int read_00221_len;
      unsigned int read_00221_ptr = 0;
      //**** delimited read
      static unsigned char read_00221_delim[] = 
         "\x3a\x20";
      read_00221 = NULL;
      read_00221_len = 0;
      int read_00221_res = cgc_delimited_read(0, &read_00221, &read_00221_len, read_00221_delim, 2);
      if (read_00221_res) {} //silence unused variable warning
      cgc_free(read_00221);
      if (read_00221_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00214_00000[] = 
         "\x39\x33\x36\x0a";
      static unsigned int write_00214_00000_len = 4;
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = cgc_append_buf(write_00214, &write_00214_len, write_00214_00000, write_00214_00000_len);
      if (write_00214_len > 0) {
         cgc_transmit_all(1, write_00214, write_00214_len);
      }
      cgc_free(write_00214);
   } while (0);
   do {
      unsigned char *read_00222;
      unsigned int read_00222_len;
      unsigned int read_00222_ptr = 0;
      //**** delimited read
      static unsigned char read_00222_delim[] = 
         "\x3a\x20";
      read_00222 = NULL;
      read_00222_len = 0;
      int read_00222_res = cgc_delimited_read(0, &read_00222, &read_00222_len, read_00222_delim, 2);
      if (read_00222_res) {} //silence unused variable warning
      cgc_free(read_00222);
      if (read_00222_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00215_00000[] = 
         "\x32\x33\x31\x0a";
      static unsigned int write_00215_00000_len = 4;
      unsigned char *write_00215 = NULL;
      unsigned int write_00215_len = 0;
      write_00215 = cgc_append_buf(write_00215, &write_00215_len, write_00215_00000, write_00215_00000_len);
      if (write_00215_len > 0) {
         cgc_transmit_all(1, write_00215, write_00215_len);
      }
      cgc_free(write_00215);
   } while (0);
   do {
      unsigned char *read_00223;
      unsigned int read_00223_len;
      unsigned int read_00223_ptr = 0;
      //**** delimited read
      static unsigned char read_00223_delim[] = 
         "\x3a\x20";
      read_00223 = NULL;
      read_00223_len = 0;
      int read_00223_res = cgc_delimited_read(0, &read_00223, &read_00223_len, read_00223_delim, 2);
      if (read_00223_res) {} //silence unused variable warning
      cgc_free(read_00223);
      if (read_00223_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00216_00000[] = 
         "\x32\x37\x39\x0a";
      static unsigned int write_00216_00000_len = 4;
      unsigned char *write_00216 = NULL;
      unsigned int write_00216_len = 0;
      write_00216 = cgc_append_buf(write_00216, &write_00216_len, write_00216_00000, write_00216_00000_len);
      if (write_00216_len > 0) {
         cgc_transmit_all(1, write_00216, write_00216_len);
      }
      cgc_free(write_00216);
   } while (0);
   do {
      unsigned char *read_00224;
      unsigned int read_00224_len;
      unsigned int read_00224_ptr = 0;
      //**** delimited read
      static unsigned char read_00224_delim[] = 
         "\x3a\x20";
      read_00224 = NULL;
      read_00224_len = 0;
      int read_00224_res = cgc_delimited_read(0, &read_00224, &read_00224_len, read_00224_delim, 2);
      if (read_00224_res) {} //silence unused variable warning
      cgc_free(read_00224);
      if (read_00224_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00217_00000[] = 
         "\x33\x39\x39\x0a";
      static unsigned int write_00217_00000_len = 4;
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = cgc_append_buf(write_00217, &write_00217_len, write_00217_00000, write_00217_00000_len);
      if (write_00217_len > 0) {
         cgc_transmit_all(1, write_00217, write_00217_len);
      }
      cgc_free(write_00217);
   } while (0);
   do {
      unsigned char *read_00225;
      unsigned int read_00225_len;
      unsigned int read_00225_ptr = 0;
      //**** delimited read
      static unsigned char read_00225_delim[] = 
         "\x3a\x20";
      read_00225 = NULL;
      read_00225_len = 0;
      int read_00225_res = cgc_delimited_read(0, &read_00225, &read_00225_len, read_00225_delim, 2);
      if (read_00225_res) {} //silence unused variable warning
      cgc_free(read_00225);
      if (read_00225_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00218_00000[] = 
         "\x37\x34\x35\x0a";
      static unsigned int write_00218_00000_len = 4;
      unsigned char *write_00218 = NULL;
      unsigned int write_00218_len = 0;
      write_00218 = cgc_append_buf(write_00218, &write_00218_len, write_00218_00000, write_00218_00000_len);
      if (write_00218_len > 0) {
         cgc_transmit_all(1, write_00218, write_00218_len);
      }
      cgc_free(write_00218);
   } while (0);
   do {
      unsigned char *read_00226;
      unsigned int read_00226_len;
      unsigned int read_00226_ptr = 0;
      //**** delimited read
      static unsigned char read_00226_delim[] = 
         "\x3a\x20";
      read_00226 = NULL;
      read_00226_len = 0;
      int read_00226_res = cgc_delimited_read(0, &read_00226, &read_00226_len, read_00226_delim, 2);
      if (read_00226_res) {} //silence unused variable warning
      cgc_free(read_00226);
      if (read_00226_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00219_00000[] = 
         "\x32\x34\x37\x0a";
      static unsigned int write_00219_00000_len = 4;
      unsigned char *write_00219 = NULL;
      unsigned int write_00219_len = 0;
      write_00219 = cgc_append_buf(write_00219, &write_00219_len, write_00219_00000, write_00219_00000_len);
      if (write_00219_len > 0) {
         cgc_transmit_all(1, write_00219, write_00219_len);
      }
      cgc_free(write_00219);
   } while (0);
   do {
      unsigned char *read_00227;
      unsigned int read_00227_len;
      unsigned int read_00227_ptr = 0;
      //**** delimited read
      static unsigned char read_00227_delim[] = 
         "\x3a\x20";
      read_00227 = NULL;
      read_00227_len = 0;
      int read_00227_res = cgc_delimited_read(0, &read_00227, &read_00227_len, read_00227_delim, 2);
      if (read_00227_res) {} //silence unused variable warning
      cgc_free(read_00227);
      if (read_00227_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00220_00000[] = 
         "\x34\x36\x34\x0a";
      static unsigned int write_00220_00000_len = 4;
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = cgc_append_buf(write_00220, &write_00220_len, write_00220_00000, write_00220_00000_len);
      if (write_00220_len > 0) {
         cgc_transmit_all(1, write_00220, write_00220_len);
      }
      cgc_free(write_00220);
   } while (0);
   do {
      unsigned char *read_00228;
      unsigned int read_00228_len;
      unsigned int read_00228_ptr = 0;
      //**** delimited read
      static unsigned char read_00228_delim[] = 
         "\x3a\x20";
      read_00228 = NULL;
      read_00228_len = 0;
      int read_00228_res = cgc_delimited_read(0, &read_00228, &read_00228_len, read_00228_delim, 2);
      if (read_00228_res) {} //silence unused variable warning
      cgc_free(read_00228);
      if (read_00228_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00221_00000[] = 
         "\x31\x32\x34\x0a";
      static unsigned int write_00221_00000_len = 4;
      unsigned char *write_00221 = NULL;
      unsigned int write_00221_len = 0;
      write_00221 = cgc_append_buf(write_00221, &write_00221_len, write_00221_00000, write_00221_00000_len);
      if (write_00221_len > 0) {
         cgc_transmit_all(1, write_00221, write_00221_len);
      }
      cgc_free(write_00221);
   } while (0);
   do {
      unsigned char *read_00229;
      unsigned int read_00229_len;
      unsigned int read_00229_ptr = 0;
      //**** delimited read
      static unsigned char read_00229_delim[] = 
         "\x3a\x20";
      read_00229 = NULL;
      read_00229_len = 0;
      int read_00229_res = cgc_delimited_read(0, &read_00229, &read_00229_len, read_00229_delim, 2);
      if (read_00229_res) {} //silence unused variable warning
      cgc_free(read_00229);
      if (read_00229_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00222_00000[] = 
         "\x31\x31\x31\x0a";
      static unsigned int write_00222_00000_len = 4;
      unsigned char *write_00222 = NULL;
      unsigned int write_00222_len = 0;
      write_00222 = cgc_append_buf(write_00222, &write_00222_len, write_00222_00000, write_00222_00000_len);
      if (write_00222_len > 0) {
         cgc_transmit_all(1, write_00222, write_00222_len);
      }
      cgc_free(write_00222);
   } while (0);
   do {
      unsigned char *read_00230;
      unsigned int read_00230_len;
      unsigned int read_00230_ptr = 0;
      //**** delimited read
      static unsigned char read_00230_delim[] = 
         "\x3a\x20";
      read_00230 = NULL;
      read_00230_len = 0;
      int read_00230_res = cgc_delimited_read(0, &read_00230, &read_00230_len, read_00230_delim, 2);
      if (read_00230_res) {} //silence unused variable warning
      cgc_free(read_00230);
      if (read_00230_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00223_00000[] = 
         "\x33\x33\x0a";
      static unsigned int write_00223_00000_len = 3;
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = cgc_append_buf(write_00223, &write_00223_len, write_00223_00000, write_00223_00000_len);
      if (write_00223_len > 0) {
         cgc_transmit_all(1, write_00223, write_00223_len);
      }
      cgc_free(write_00223);
   } while (0);
   do {
      unsigned char *read_00231;
      unsigned int read_00231_len;
      unsigned int read_00231_ptr = 0;
      //**** delimited read
      static unsigned char read_00231_delim[] = 
         "\x3a\x20";
      read_00231 = NULL;
      read_00231_len = 0;
      int read_00231_res = cgc_delimited_read(0, &read_00231, &read_00231_len, read_00231_delim, 2);
      if (read_00231_res) {} //silence unused variable warning
      cgc_free(read_00231);
      if (read_00231_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00224_00000[] = 
         "\x32\x37\x39\x0a";
      static unsigned int write_00224_00000_len = 4;
      unsigned char *write_00224 = NULL;
      unsigned int write_00224_len = 0;
      write_00224 = cgc_append_buf(write_00224, &write_00224_len, write_00224_00000, write_00224_00000_len);
      if (write_00224_len > 0) {
         cgc_transmit_all(1, write_00224, write_00224_len);
      }
      cgc_free(write_00224);
   } while (0);
   do {
      unsigned char *read_00232;
      unsigned int read_00232_len;
      unsigned int read_00232_ptr = 0;
      //**** delimited read
      static unsigned char read_00232_delim[] = 
         "\x3a\x20";
      read_00232 = NULL;
      read_00232_len = 0;
      int read_00232_res = cgc_delimited_read(0, &read_00232, &read_00232_len, read_00232_delim, 2);
      if (read_00232_res) {} //silence unused variable warning
      cgc_free(read_00232);
      if (read_00232_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00225_00000[] = 
         "\x37\x38\x38\x0a";
      static unsigned int write_00225_00000_len = 4;
      unsigned char *write_00225 = NULL;
      unsigned int write_00225_len = 0;
      write_00225 = cgc_append_buf(write_00225, &write_00225_len, write_00225_00000, write_00225_00000_len);
      if (write_00225_len > 0) {
         cgc_transmit_all(1, write_00225, write_00225_len);
      }
      cgc_free(write_00225);
   } while (0);
   do {
      unsigned char *read_00233;
      unsigned int read_00233_len;
      unsigned int read_00233_ptr = 0;
      //**** delimited read
      static unsigned char read_00233_delim[] = 
         "\x3a\x20";
      read_00233 = NULL;
      read_00233_len = 0;
      int read_00233_res = cgc_delimited_read(0, &read_00233, &read_00233_len, read_00233_delim, 2);
      if (read_00233_res) {} //silence unused variable warning
      cgc_free(read_00233);
      if (read_00233_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00226_00000[] = 
         "\x33\x32\x31\x0a";
      static unsigned int write_00226_00000_len = 4;
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = cgc_append_buf(write_00226, &write_00226_len, write_00226_00000, write_00226_00000_len);
      if (write_00226_len > 0) {
         cgc_transmit_all(1, write_00226, write_00226_len);
      }
      cgc_free(write_00226);
   } while (0);
   do {
      unsigned char *read_00234;
      unsigned int read_00234_len;
      unsigned int read_00234_ptr = 0;
      //**** delimited read
      static unsigned char read_00234_delim[] = 
         "\x3a\x20";
      read_00234 = NULL;
      read_00234_len = 0;
      int read_00234_res = cgc_delimited_read(0, &read_00234, &read_00234_len, read_00234_delim, 2);
      if (read_00234_res) {} //silence unused variable warning
      cgc_free(read_00234);
      if (read_00234_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00227_00000[] = 
         "\x38\x35\x0a";
      static unsigned int write_00227_00000_len = 3;
      unsigned char *write_00227 = NULL;
      unsigned int write_00227_len = 0;
      write_00227 = cgc_append_buf(write_00227, &write_00227_len, write_00227_00000, write_00227_00000_len);
      if (write_00227_len > 0) {
         cgc_transmit_all(1, write_00227, write_00227_len);
      }
      cgc_free(write_00227);
   } while (0);
   do {
      unsigned char *read_00235;
      unsigned int read_00235_len;
      unsigned int read_00235_ptr = 0;
      //**** delimited read
      static unsigned char read_00235_delim[] = 
         "\x3a\x20";
      read_00235 = NULL;
      read_00235_len = 0;
      int read_00235_res = cgc_delimited_read(0, &read_00235, &read_00235_len, read_00235_delim, 2);
      if (read_00235_res) {} //silence unused variable warning
      cgc_free(read_00235);
      if (read_00235_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00228_00000[] = 
         "\x35\x30\x36\x0a";
      static unsigned int write_00228_00000_len = 4;
      unsigned char *write_00228 = NULL;
      unsigned int write_00228_len = 0;
      write_00228 = cgc_append_buf(write_00228, &write_00228_len, write_00228_00000, write_00228_00000_len);
      if (write_00228_len > 0) {
         cgc_transmit_all(1, write_00228, write_00228_len);
      }
      cgc_free(write_00228);
   } while (0);
   do {
      unsigned char *read_00236;
      unsigned int read_00236_len;
      unsigned int read_00236_ptr = 0;
      //**** delimited read
      static unsigned char read_00236_delim[] = 
         "\x3a\x20";
      read_00236 = NULL;
      read_00236_len = 0;
      int read_00236_res = cgc_delimited_read(0, &read_00236, &read_00236_len, read_00236_delim, 2);
      if (read_00236_res) {} //silence unused variable warning
      cgc_free(read_00236);
      if (read_00236_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00229_00000[] = 
         "\x39\x32\x32\x0a";
      static unsigned int write_00229_00000_len = 4;
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = cgc_append_buf(write_00229, &write_00229_len, write_00229_00000, write_00229_00000_len);
      if (write_00229_len > 0) {
         cgc_transmit_all(1, write_00229, write_00229_len);
      }
      cgc_free(write_00229);
   } while (0);
   do {
      unsigned char *read_00237;
      unsigned int read_00237_len;
      unsigned int read_00237_ptr = 0;
      //**** delimited read
      static unsigned char read_00237_delim[] = 
         "\x3a\x20";
      read_00237 = NULL;
      read_00237_len = 0;
      int read_00237_res = cgc_delimited_read(0, &read_00237, &read_00237_len, read_00237_delim, 2);
      if (read_00237_res) {} //silence unused variable warning
      cgc_free(read_00237);
      if (read_00237_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00230_00000[] = 
         "\x32\x38\x35\x0a";
      static unsigned int write_00230_00000_len = 4;
      unsigned char *write_00230 = NULL;
      unsigned int write_00230_len = 0;
      write_00230 = cgc_append_buf(write_00230, &write_00230_len, write_00230_00000, write_00230_00000_len);
      if (write_00230_len > 0) {
         cgc_transmit_all(1, write_00230, write_00230_len);
      }
      cgc_free(write_00230);
   } while (0);
   do {
      unsigned char *read_00238;
      unsigned int read_00238_len;
      unsigned int read_00238_ptr = 0;
      //**** delimited read
      static unsigned char read_00238_delim[] = 
         "\x3a\x20";
      read_00238 = NULL;
      read_00238_len = 0;
      int read_00238_res = cgc_delimited_read(0, &read_00238, &read_00238_len, read_00238_delim, 2);
      if (read_00238_res) {} //silence unused variable warning
      cgc_free(read_00238);
      if (read_00238_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00231_00000[] = 
         "\x35\x39\x37\x0a";
      static unsigned int write_00231_00000_len = 4;
      unsigned char *write_00231 = NULL;
      unsigned int write_00231_len = 0;
      write_00231 = cgc_append_buf(write_00231, &write_00231_len, write_00231_00000, write_00231_00000_len);
      if (write_00231_len > 0) {
         cgc_transmit_all(1, write_00231, write_00231_len);
      }
      cgc_free(write_00231);
   } while (0);
   do {
      unsigned char *read_00239;
      unsigned int read_00239_len;
      unsigned int read_00239_ptr = 0;
      //**** delimited read
      static unsigned char read_00239_delim[] = 
         "\x3a\x20";
      read_00239 = NULL;
      read_00239_len = 0;
      int read_00239_res = cgc_delimited_read(0, &read_00239, &read_00239_len, read_00239_delim, 2);
      if (read_00239_res) {} //silence unused variable warning
      cgc_free(read_00239);
      if (read_00239_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00232_00000[] = 
         "\x38\x37\x34\x0a";
      static unsigned int write_00232_00000_len = 4;
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = cgc_append_buf(write_00232, &write_00232_len, write_00232_00000, write_00232_00000_len);
      if (write_00232_len > 0) {
         cgc_transmit_all(1, write_00232, write_00232_len);
      }
      cgc_free(write_00232);
   } while (0);
   do {
      unsigned char *read_00240;
      unsigned int read_00240_len;
      unsigned int read_00240_ptr = 0;
      //**** delimited read
      static unsigned char read_00240_delim[] = 
         "\x3a\x20";
      read_00240 = NULL;
      read_00240_len = 0;
      int read_00240_res = cgc_delimited_read(0, &read_00240, &read_00240_len, read_00240_delim, 2);
      if (read_00240_res) {} //silence unused variable warning
      cgc_free(read_00240);
      if (read_00240_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00233_00000[] = 
         "\x38\x30\x31\x0a";
      static unsigned int write_00233_00000_len = 4;
      unsigned char *write_00233 = NULL;
      unsigned int write_00233_len = 0;
      write_00233 = cgc_append_buf(write_00233, &write_00233_len, write_00233_00000, write_00233_00000_len);
      if (write_00233_len > 0) {
         cgc_transmit_all(1, write_00233, write_00233_len);
      }
      cgc_free(write_00233);
   } while (0);
   do {
      unsigned char *read_00241;
      unsigned int read_00241_len;
      unsigned int read_00241_ptr = 0;
      //**** delimited read
      static unsigned char read_00241_delim[] = 
         "\x3a\x20";
      read_00241 = NULL;
      read_00241_len = 0;
      int read_00241_res = cgc_delimited_read(0, &read_00241, &read_00241_len, read_00241_delim, 2);
      if (read_00241_res) {} //silence unused variable warning
      cgc_free(read_00241);
      if (read_00241_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00234_00000[] = 
         "\x33\x30\x0a";
      static unsigned int write_00234_00000_len = 3;
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = cgc_append_buf(write_00234, &write_00234_len, write_00234_00000, write_00234_00000_len);
      if (write_00234_len > 0) {
         cgc_transmit_all(1, write_00234, write_00234_len);
      }
      cgc_free(write_00234);
   } while (0);
   do {
      unsigned char *read_00242;
      unsigned int read_00242_len;
      unsigned int read_00242_ptr = 0;
      //**** delimited read
      static unsigned char read_00242_delim[] = 
         "\x3a\x20";
      read_00242 = NULL;
      read_00242_len = 0;
      int read_00242_res = cgc_delimited_read(0, &read_00242, &read_00242_len, read_00242_delim, 2);
      if (read_00242_res) {} //silence unused variable warning
      cgc_free(read_00242);
      if (read_00242_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00235_00000[] = 
         "\x36\x31\x38\x0a";
      static unsigned int write_00235_00000_len = 4;
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = cgc_append_buf(write_00235, &write_00235_len, write_00235_00000, write_00235_00000_len);
      if (write_00235_len > 0) {
         cgc_transmit_all(1, write_00235, write_00235_len);
      }
      cgc_free(write_00235);
   } while (0);
   do {
      unsigned char *read_00243;
      unsigned int read_00243_len;
      unsigned int read_00243_ptr = 0;
      //**** delimited read
      static unsigned char read_00243_delim[] = 
         "\x3a\x20";
      read_00243 = NULL;
      read_00243_len = 0;
      int read_00243_res = cgc_delimited_read(0, &read_00243, &read_00243_len, read_00243_delim, 2);
      if (read_00243_res) {} //silence unused variable warning
      cgc_free(read_00243);
      if (read_00243_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00236_00000[] = 
         "\x35\x39\x30\x0a";
      static unsigned int write_00236_00000_len = 4;
      unsigned char *write_00236 = NULL;
      unsigned int write_00236_len = 0;
      write_00236 = cgc_append_buf(write_00236, &write_00236_len, write_00236_00000, write_00236_00000_len);
      if (write_00236_len > 0) {
         cgc_transmit_all(1, write_00236, write_00236_len);
      }
      cgc_free(write_00236);
   } while (0);
   do {
      unsigned char *read_00244;
      unsigned int read_00244_len;
      unsigned int read_00244_ptr = 0;
      //**** delimited read
      static unsigned char read_00244_delim[] = 
         "\x3a\x20";
      read_00244 = NULL;
      read_00244_len = 0;
      int read_00244_res = cgc_delimited_read(0, &read_00244, &read_00244_len, read_00244_delim, 2);
      if (read_00244_res) {} //silence unused variable warning
      cgc_free(read_00244);
      if (read_00244_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00237_00000[] = 
         "\x35\x36\x37\x0a";
      static unsigned int write_00237_00000_len = 4;
      unsigned char *write_00237 = NULL;
      unsigned int write_00237_len = 0;
      write_00237 = cgc_append_buf(write_00237, &write_00237_len, write_00237_00000, write_00237_00000_len);
      if (write_00237_len > 0) {
         cgc_transmit_all(1, write_00237, write_00237_len);
      }
      cgc_free(write_00237);
   } while (0);
   do {
      unsigned char *read_00245;
      unsigned int read_00245_len;
      unsigned int read_00245_ptr = 0;
      //**** delimited read
      static unsigned char read_00245_delim[] = 
         "\x3a\x20";
      read_00245 = NULL;
      read_00245_len = 0;
      int read_00245_res = cgc_delimited_read(0, &read_00245, &read_00245_len, read_00245_delim, 2);
      if (read_00245_res) {} //silence unused variable warning
      cgc_free(read_00245);
      if (read_00245_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00238_00000[] = 
         "\x36\x31\x31\x0a";
      static unsigned int write_00238_00000_len = 4;
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = cgc_append_buf(write_00238, &write_00238_len, write_00238_00000, write_00238_00000_len);
      if (write_00238_len > 0) {
         cgc_transmit_all(1, write_00238, write_00238_len);
      }
      cgc_free(write_00238);
   } while (0);
   do {
      unsigned char *read_00246;
      unsigned int read_00246_len;
      unsigned int read_00246_ptr = 0;
      //**** delimited read
      static unsigned char read_00246_delim[] = 
         "\x3a\x20";
      read_00246 = NULL;
      read_00246_len = 0;
      int read_00246_res = cgc_delimited_read(0, &read_00246, &read_00246_len, read_00246_delim, 2);
      if (read_00246_res) {} //silence unused variable warning
      cgc_free(read_00246);
      if (read_00246_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00239_00000[] = 
         "\x34\x31\x30\x0a";
      static unsigned int write_00239_00000_len = 4;
      unsigned char *write_00239 = NULL;
      unsigned int write_00239_len = 0;
      write_00239 = cgc_append_buf(write_00239, &write_00239_len, write_00239_00000, write_00239_00000_len);
      if (write_00239_len > 0) {
         cgc_transmit_all(1, write_00239, write_00239_len);
      }
      cgc_free(write_00239);
   } while (0);
   do {
      unsigned char *read_00247;
      unsigned int read_00247_len;
      unsigned int read_00247_ptr = 0;
      //**** delimited read
      static unsigned char read_00247_delim[] = 
         "\x3a\x20";
      read_00247 = NULL;
      read_00247_len = 0;
      int read_00247_res = cgc_delimited_read(0, &read_00247, &read_00247_len, read_00247_delim, 2);
      if (read_00247_res) {} //silence unused variable warning
      cgc_free(read_00247);
      if (read_00247_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00240_00000[] = 
         "\x38\x39\x36\x0a";
      static unsigned int write_00240_00000_len = 4;
      unsigned char *write_00240 = NULL;
      unsigned int write_00240_len = 0;
      write_00240 = cgc_append_buf(write_00240, &write_00240_len, write_00240_00000, write_00240_00000_len);
      if (write_00240_len > 0) {
         cgc_transmit_all(1, write_00240, write_00240_len);
      }
      cgc_free(write_00240);
   } while (0);
   do {
      unsigned char *read_00248;
      unsigned int read_00248_len;
      unsigned int read_00248_ptr = 0;
      //**** delimited read
      static unsigned char read_00248_delim[] = 
         "\x3a\x20";
      read_00248 = NULL;
      read_00248_len = 0;
      int read_00248_res = cgc_delimited_read(0, &read_00248, &read_00248_len, read_00248_delim, 2);
      if (read_00248_res) {} //silence unused variable warning
      cgc_free(read_00248);
      if (read_00248_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00241_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00241_00000_len = 3;
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = cgc_append_buf(write_00241, &write_00241_len, write_00241_00000, write_00241_00000_len);
      if (write_00241_len > 0) {
         cgc_transmit_all(1, write_00241, write_00241_len);
      }
      cgc_free(write_00241);
   } while (0);
   do {
      unsigned char *read_00249;
      unsigned int read_00249_len;
      unsigned int read_00249_ptr = 0;
      //**** delimited read
      static unsigned char read_00249_delim[] = 
         "\x3a\x20";
      read_00249 = NULL;
      read_00249_len = 0;
      int read_00249_res = cgc_delimited_read(0, &read_00249, &read_00249_len, read_00249_delim, 2);
      if (read_00249_res) {} //silence unused variable warning
      cgc_free(read_00249);
      if (read_00249_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00242_00000[] = 
         "\x34\x31\x35\x0a";
      static unsigned int write_00242_00000_len = 4;
      unsigned char *write_00242 = NULL;
      unsigned int write_00242_len = 0;
      write_00242 = cgc_append_buf(write_00242, &write_00242_len, write_00242_00000, write_00242_00000_len);
      if (write_00242_len > 0) {
         cgc_transmit_all(1, write_00242, write_00242_len);
      }
      cgc_free(write_00242);
   } while (0);
   do {
      unsigned char *read_00250;
      unsigned int read_00250_len;
      unsigned int read_00250_ptr = 0;
      //**** delimited read
      static unsigned char read_00250_delim[] = 
         "\x3a\x20";
      read_00250 = NULL;
      read_00250_len = 0;
      int read_00250_res = cgc_delimited_read(0, &read_00250, &read_00250_len, read_00250_delim, 2);
      if (read_00250_res) {} //silence unused variable warning
      cgc_free(read_00250);
      if (read_00250_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00243_00000[] = 
         "\x36\x34\x31\x0a";
      static unsigned int write_00243_00000_len = 4;
      unsigned char *write_00243 = NULL;
      unsigned int write_00243_len = 0;
      write_00243 = cgc_append_buf(write_00243, &write_00243_len, write_00243_00000, write_00243_00000_len);
      if (write_00243_len > 0) {
         cgc_transmit_all(1, write_00243, write_00243_len);
      }
      cgc_free(write_00243);
   } while (0);
   do {
      unsigned char *read_00251;
      unsigned int read_00251_len;
      unsigned int read_00251_ptr = 0;
      //**** delimited read
      static unsigned char read_00251_delim[] = 
         "\x3a\x20";
      read_00251 = NULL;
      read_00251_len = 0;
      int read_00251_res = cgc_delimited_read(0, &read_00251, &read_00251_len, read_00251_delim, 2);
      if (read_00251_res) {} //silence unused variable warning
      cgc_free(read_00251);
      if (read_00251_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00244_00000[] = 
         "\x35\x33\x35\x0a";
      static unsigned int write_00244_00000_len = 4;
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = cgc_append_buf(write_00244, &write_00244_len, write_00244_00000, write_00244_00000_len);
      if (write_00244_len > 0) {
         cgc_transmit_all(1, write_00244, write_00244_len);
      }
      cgc_free(write_00244);
   } while (0);
   do {
      unsigned char *read_00252;
      unsigned int read_00252_len;
      unsigned int read_00252_ptr = 0;
      //**** delimited read
      static unsigned char read_00252_delim[] = 
         "\x3a\x20";
      read_00252 = NULL;
      read_00252_len = 0;
      int read_00252_res = cgc_delimited_read(0, &read_00252, &read_00252_len, read_00252_delim, 2);
      if (read_00252_res) {} //silence unused variable warning
      cgc_free(read_00252);
      if (read_00252_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00245_00000[] = 
         "\x37\x31\x38\x0a";
      static unsigned int write_00245_00000_len = 4;
      unsigned char *write_00245 = NULL;
      unsigned int write_00245_len = 0;
      write_00245 = cgc_append_buf(write_00245, &write_00245_len, write_00245_00000, write_00245_00000_len);
      if (write_00245_len > 0) {
         cgc_transmit_all(1, write_00245, write_00245_len);
      }
      cgc_free(write_00245);
   } while (0);
   do {
      unsigned char *read_00253;
      unsigned int read_00253_len;
      unsigned int read_00253_ptr = 0;
      //**** delimited read
      static unsigned char read_00253_delim[] = 
         "\x3a\x20";
      read_00253 = NULL;
      read_00253_len = 0;
      int read_00253_res = cgc_delimited_read(0, &read_00253, &read_00253_len, read_00253_delim, 2);
      if (read_00253_res) {} //silence unused variable warning
      cgc_free(read_00253);
      if (read_00253_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00246_00000[] = 
         "\x38\x39\x33\x0a";
      static unsigned int write_00246_00000_len = 4;
      unsigned char *write_00246 = NULL;
      unsigned int write_00246_len = 0;
      write_00246 = cgc_append_buf(write_00246, &write_00246_len, write_00246_00000, write_00246_00000_len);
      if (write_00246_len > 0) {
         cgc_transmit_all(1, write_00246, write_00246_len);
      }
      cgc_free(write_00246);
   } while (0);
   do {
      unsigned char *read_00254;
      unsigned int read_00254_len;
      unsigned int read_00254_ptr = 0;
      //**** delimited read
      static unsigned char read_00254_delim[] = 
         "\x3a\x20";
      read_00254 = NULL;
      read_00254_len = 0;
      int read_00254_res = cgc_delimited_read(0, &read_00254, &read_00254_len, read_00254_delim, 2);
      if (read_00254_res) {} //silence unused variable warning
      cgc_free(read_00254);
      if (read_00254_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00247_00000[] = 
         "\x37\x35\x31\x0a";
      static unsigned int write_00247_00000_len = 4;
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = cgc_append_buf(write_00247, &write_00247_len, write_00247_00000, write_00247_00000_len);
      if (write_00247_len > 0) {
         cgc_transmit_all(1, write_00247, write_00247_len);
      }
      cgc_free(write_00247);
   } while (0);
   do {
      unsigned char *read_00255;
      unsigned int read_00255_len;
      unsigned int read_00255_ptr = 0;
      //**** delimited read
      static unsigned char read_00255_delim[] = 
         "\x3a\x20";
      read_00255 = NULL;
      read_00255_len = 0;
      int read_00255_res = cgc_delimited_read(0, &read_00255, &read_00255_len, read_00255_delim, 2);
      if (read_00255_res) {} //silence unused variable warning
      cgc_free(read_00255);
      if (read_00255_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00248_00000[] = 
         "\x34\x39\x35\x0a";
      static unsigned int write_00248_00000_len = 4;
      unsigned char *write_00248 = NULL;
      unsigned int write_00248_len = 0;
      write_00248 = cgc_append_buf(write_00248, &write_00248_len, write_00248_00000, write_00248_00000_len);
      if (write_00248_len > 0) {
         cgc_transmit_all(1, write_00248, write_00248_len);
      }
      cgc_free(write_00248);
   } while (0);
   do {
      unsigned char *read_00256;
      unsigned int read_00256_len;
      unsigned int read_00256_ptr = 0;
      //**** delimited read
      static unsigned char read_00256_delim[] = 
         "\x3a\x20";
      read_00256 = NULL;
      read_00256_len = 0;
      int read_00256_res = cgc_delimited_read(0, &read_00256, &read_00256_len, read_00256_delim, 2);
      if (read_00256_res) {} //silence unused variable warning
      cgc_free(read_00256);
      if (read_00256_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00249_00000[] = 
         "\x36\x34\x38\x0a";
      static unsigned int write_00249_00000_len = 4;
      unsigned char *write_00249 = NULL;
      unsigned int write_00249_len = 0;
      write_00249 = cgc_append_buf(write_00249, &write_00249_len, write_00249_00000, write_00249_00000_len);
      if (write_00249_len > 0) {
         cgc_transmit_all(1, write_00249, write_00249_len);
      }
      cgc_free(write_00249);
   } while (0);
   do {
      unsigned char *read_00257;
      unsigned int read_00257_len;
      unsigned int read_00257_ptr = 0;
      //**** delimited read
      static unsigned char read_00257_delim[] = 
         "\x3a\x20";
      read_00257 = NULL;
      read_00257_len = 0;
      int read_00257_res = cgc_delimited_read(0, &read_00257, &read_00257_len, read_00257_delim, 2);
      if (read_00257_res) {} //silence unused variable warning
      cgc_free(read_00257);
      if (read_00257_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00250_00000[] = 
         "\x32\x32\x36\x0a";
      static unsigned int write_00250_00000_len = 4;
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = cgc_append_buf(write_00250, &write_00250_len, write_00250_00000, write_00250_00000_len);
      if (write_00250_len > 0) {
         cgc_transmit_all(1, write_00250, write_00250_len);
      }
      cgc_free(write_00250);
   } while (0);
   do {
      unsigned char *read_00258;
      unsigned int read_00258_len;
      unsigned int read_00258_ptr = 0;
      //**** delimited read
      static unsigned char read_00258_delim[] = 
         "\x3a\x20";
      read_00258 = NULL;
      read_00258_len = 0;
      int read_00258_res = cgc_delimited_read(0, &read_00258, &read_00258_len, read_00258_delim, 2);
      if (read_00258_res) {} //silence unused variable warning
      cgc_free(read_00258);
      if (read_00258_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00251_00000[] = 
         "\x33\x37\x0a";
      static unsigned int write_00251_00000_len = 3;
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = cgc_append_buf(write_00251, &write_00251_len, write_00251_00000, write_00251_00000_len);
      if (write_00251_len > 0) {
         cgc_transmit_all(1, write_00251, write_00251_len);
      }
      cgc_free(write_00251);
   } while (0);
   do {
      unsigned char *read_00259;
      unsigned int read_00259_len;
      unsigned int read_00259_ptr = 0;
      //**** delimited read
      static unsigned char read_00259_delim[] = 
         "\x3a\x20";
      read_00259 = NULL;
      read_00259_len = 0;
      int read_00259_res = cgc_delimited_read(0, &read_00259, &read_00259_len, read_00259_delim, 2);
      if (read_00259_res) {} //silence unused variable warning
      cgc_free(read_00259);
      if (read_00259_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00252_00000[] = 
         "\x31\x33\x32\x0a";
      static unsigned int write_00252_00000_len = 4;
      unsigned char *write_00252 = NULL;
      unsigned int write_00252_len = 0;
      write_00252 = cgc_append_buf(write_00252, &write_00252_len, write_00252_00000, write_00252_00000_len);
      if (write_00252_len > 0) {
         cgc_transmit_all(1, write_00252, write_00252_len);
      }
      cgc_free(write_00252);
   } while (0);
   do {
      unsigned char *read_00260;
      unsigned int read_00260_len;
      unsigned int read_00260_ptr = 0;
      //**** delimited read
      static unsigned char read_00260_delim[] = 
         "\x3a\x20";
      read_00260 = NULL;
      read_00260_len = 0;
      int read_00260_res = cgc_delimited_read(0, &read_00260, &read_00260_len, read_00260_delim, 2);
      if (read_00260_res) {} //silence unused variable warning
      cgc_free(read_00260);
      if (read_00260_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00253_00000[] = 
         "\x38\x34\x30\x0a";
      static unsigned int write_00253_00000_len = 4;
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = cgc_append_buf(write_00253, &write_00253_len, write_00253_00000, write_00253_00000_len);
      if (write_00253_len > 0) {
         cgc_transmit_all(1, write_00253, write_00253_len);
      }
      cgc_free(write_00253);
   } while (0);
   do {
      unsigned char *read_00261;
      unsigned int read_00261_len;
      unsigned int read_00261_ptr = 0;
      //**** delimited read
      static unsigned char read_00261_delim[] = 
         "\x3a\x20";
      read_00261 = NULL;
      read_00261_len = 0;
      int read_00261_res = cgc_delimited_read(0, &read_00261, &read_00261_len, read_00261_delim, 2);
      if (read_00261_res) {} //silence unused variable warning
      cgc_free(read_00261);
      if (read_00261_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00254_00000[] = 
         "\x35\x37\x0a";
      static unsigned int write_00254_00000_len = 3;
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = cgc_append_buf(write_00254, &write_00254_len, write_00254_00000, write_00254_00000_len);
      if (write_00254_len > 0) {
         cgc_transmit_all(1, write_00254, write_00254_len);
      }
      cgc_free(write_00254);
   } while (0);
   do {
      unsigned char *read_00262;
      unsigned int read_00262_len;
      unsigned int read_00262_ptr = 0;
      //**** delimited read
      static unsigned char read_00262_delim[] = 
         "\x3a\x20";
      read_00262 = NULL;
      read_00262_len = 0;
      int read_00262_res = cgc_delimited_read(0, &read_00262, &read_00262_len, read_00262_delim, 2);
      if (read_00262_res) {} //silence unused variable warning
      cgc_free(read_00262);
      if (read_00262_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00255_00000[] = 
         "\x36\x32\x37\x0a";
      static unsigned int write_00255_00000_len = 4;
      unsigned char *write_00255 = NULL;
      unsigned int write_00255_len = 0;
      write_00255 = cgc_append_buf(write_00255, &write_00255_len, write_00255_00000, write_00255_00000_len);
      if (write_00255_len > 0) {
         cgc_transmit_all(1, write_00255, write_00255_len);
      }
      cgc_free(write_00255);
   } while (0);
   do {
      unsigned char *read_00263;
      unsigned int read_00263_len;
      unsigned int read_00263_ptr = 0;
      //**** delimited read
      static unsigned char read_00263_delim[] = 
         "\x3a\x20";
      read_00263 = NULL;
      read_00263_len = 0;
      int read_00263_res = cgc_delimited_read(0, &read_00263, &read_00263_len, read_00263_delim, 2);
      if (read_00263_res) {} //silence unused variable warning
      cgc_free(read_00263);
      if (read_00263_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00256_00000[] = 
         "\x31\x37\x35\x0a";
      static unsigned int write_00256_00000_len = 4;
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = cgc_append_buf(write_00256, &write_00256_len, write_00256_00000, write_00256_00000_len);
      if (write_00256_len > 0) {
         cgc_transmit_all(1, write_00256, write_00256_len);
      }
      cgc_free(write_00256);
   } while (0);
   do {
      unsigned char *read_00264;
      unsigned int read_00264_len;
      unsigned int read_00264_ptr = 0;
      //**** delimited read
      static unsigned char read_00264_delim[] = 
         "\x3a\x20";
      read_00264 = NULL;
      read_00264_len = 0;
      int read_00264_res = cgc_delimited_read(0, &read_00264, &read_00264_len, read_00264_delim, 2);
      if (read_00264_res) {} //silence unused variable warning
      cgc_free(read_00264);
      if (read_00264_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00257_00000[] = 
         "\x33\x33\x37\x0a";
      static unsigned int write_00257_00000_len = 4;
      unsigned char *write_00257 = NULL;
      unsigned int write_00257_len = 0;
      write_00257 = cgc_append_buf(write_00257, &write_00257_len, write_00257_00000, write_00257_00000_len);
      if (write_00257_len > 0) {
         cgc_transmit_all(1, write_00257, write_00257_len);
      }
      cgc_free(write_00257);
   } while (0);
   do {
      unsigned char *read_00265;
      unsigned int read_00265_len;
      unsigned int read_00265_ptr = 0;
      //**** delimited read
      static unsigned char read_00265_delim[] = 
         "\x3a\x20";
      read_00265 = NULL;
      read_00265_len = 0;
      int read_00265_res = cgc_delimited_read(0, &read_00265, &read_00265_len, read_00265_delim, 2);
      if (read_00265_res) {} //silence unused variable warning
      cgc_free(read_00265);
      if (read_00265_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00258_00000[] = 
         "\x31\x30\x30\x30\x0a";
      static unsigned int write_00258_00000_len = 5;
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = cgc_append_buf(write_00258, &write_00258_len, write_00258_00000, write_00258_00000_len);
      if (write_00258_len > 0) {
         cgc_transmit_all(1, write_00258, write_00258_len);
      }
      cgc_free(write_00258);
   } while (0);
   do {
      unsigned char *read_00266;
      unsigned int read_00266_len;
      unsigned int read_00266_ptr = 0;
      //**** delimited read
      static unsigned char read_00266_delim[] = 
         "\x3a\x20";
      read_00266 = NULL;
      read_00266_len = 0;
      int read_00266_res = cgc_delimited_read(0, &read_00266, &read_00266_len, read_00266_delim, 2);
      if (read_00266_res) {} //silence unused variable warning
      cgc_free(read_00266);
      if (read_00266_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00259_00000[] = 
         "\x34\x31\x0a";
      static unsigned int write_00259_00000_len = 3;
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = cgc_append_buf(write_00259, &write_00259_len, write_00259_00000, write_00259_00000_len);
      if (write_00259_len > 0) {
         cgc_transmit_all(1, write_00259, write_00259_len);
      }
      cgc_free(write_00259);
   } while (0);
   do {
      unsigned char *read_00267;
      unsigned int read_00267_len;
      unsigned int read_00267_ptr = 0;
      //**** delimited read
      static unsigned char read_00267_delim[] = 
         "\x3a\x20";
      read_00267 = NULL;
      read_00267_len = 0;
      int read_00267_res = cgc_delimited_read(0, &read_00267, &read_00267_len, read_00267_delim, 2);
      if (read_00267_res) {} //silence unused variable warning
      cgc_free(read_00267);
      if (read_00267_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00260_00000[] = 
         "\x34\x33\x33\x0a";
      static unsigned int write_00260_00000_len = 4;
      unsigned char *write_00260 = NULL;
      unsigned int write_00260_len = 0;
      write_00260 = cgc_append_buf(write_00260, &write_00260_len, write_00260_00000, write_00260_00000_len);
      if (write_00260_len > 0) {
         cgc_transmit_all(1, write_00260, write_00260_len);
      }
      cgc_free(write_00260);
   } while (0);
   do {
      unsigned char *read_00268;
      unsigned int read_00268_len;
      unsigned int read_00268_ptr = 0;
      //**** delimited read
      static unsigned char read_00268_delim[] = 
         "\x3a\x20";
      read_00268 = NULL;
      read_00268_len = 0;
      int read_00268_res = cgc_delimited_read(0, &read_00268, &read_00268_len, read_00268_delim, 2);
      if (read_00268_res) {} //silence unused variable warning
      cgc_free(read_00268);
      if (read_00268_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00261_00000[] = 
         "\x31\x32\x35\x0a";
      static unsigned int write_00261_00000_len = 4;
      unsigned char *write_00261 = NULL;
      unsigned int write_00261_len = 0;
      write_00261 = cgc_append_buf(write_00261, &write_00261_len, write_00261_00000, write_00261_00000_len);
      if (write_00261_len > 0) {
         cgc_transmit_all(1, write_00261, write_00261_len);
      }
      cgc_free(write_00261);
   } while (0);
   do {
      unsigned char *read_00269;
      unsigned int read_00269_len;
      unsigned int read_00269_ptr = 0;
      //**** delimited read
      static unsigned char read_00269_delim[] = 
         "\x3a\x20";
      read_00269 = NULL;
      read_00269_len = 0;
      int read_00269_res = cgc_delimited_read(0, &read_00269, &read_00269_len, read_00269_delim, 2);
      if (read_00269_res) {} //silence unused variable warning
      cgc_free(read_00269);
      if (read_00269_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00262_00000[] = 
         "\x38\x33\x36\x0a";
      static unsigned int write_00262_00000_len = 4;
      unsigned char *write_00262 = NULL;
      unsigned int write_00262_len = 0;
      write_00262 = cgc_append_buf(write_00262, &write_00262_len, write_00262_00000, write_00262_00000_len);
      if (write_00262_len > 0) {
         cgc_transmit_all(1, write_00262, write_00262_len);
      }
      cgc_free(write_00262);
   } while (0);
   do {
      unsigned char *read_00270;
      unsigned int read_00270_len;
      unsigned int read_00270_ptr = 0;
      //**** delimited read
      static unsigned char read_00270_delim[] = 
         "\x3a\x20";
      read_00270 = NULL;
      read_00270_len = 0;
      int read_00270_res = cgc_delimited_read(0, &read_00270, &read_00270_len, read_00270_delim, 2);
      if (read_00270_res) {} //silence unused variable warning
      cgc_free(read_00270);
      if (read_00270_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00263_00000[] = 
         "\x36\x30\x32\x0a";
      static unsigned int write_00263_00000_len = 4;
      unsigned char *write_00263 = NULL;
      unsigned int write_00263_len = 0;
      write_00263 = cgc_append_buf(write_00263, &write_00263_len, write_00263_00000, write_00263_00000_len);
      if (write_00263_len > 0) {
         cgc_transmit_all(1, write_00263, write_00263_len);
      }
      cgc_free(write_00263);
   } while (0);
   do {
      unsigned char *read_00271;
      unsigned int read_00271_len;
      unsigned int read_00271_ptr = 0;
      //**** delimited read
      static unsigned char read_00271_delim[] = 
         "\x3a\x20";
      read_00271 = NULL;
      read_00271_len = 0;
      int read_00271_res = cgc_delimited_read(0, &read_00271, &read_00271_len, read_00271_delim, 2);
      if (read_00271_res) {} //silence unused variable warning
      cgc_free(read_00271);
      if (read_00271_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00264_00000[] = 
         "\x34\x33\x0a";
      static unsigned int write_00264_00000_len = 3;
      unsigned char *write_00264 = NULL;
      unsigned int write_00264_len = 0;
      write_00264 = cgc_append_buf(write_00264, &write_00264_len, write_00264_00000, write_00264_00000_len);
      if (write_00264_len > 0) {
         cgc_transmit_all(1, write_00264, write_00264_len);
      }
      cgc_free(write_00264);
   } while (0);
   do {
      unsigned char *read_00272;
      unsigned int read_00272_len;
      unsigned int read_00272_ptr = 0;
      //**** delimited read
      static unsigned char read_00272_delim[] = 
         "\x3a\x20";
      read_00272 = NULL;
      read_00272_len = 0;
      int read_00272_res = cgc_delimited_read(0, &read_00272, &read_00272_len, read_00272_delim, 2);
      if (read_00272_res) {} //silence unused variable warning
      cgc_free(read_00272);
      if (read_00272_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00265_00000[] = 
         "\x33\x30\x31\x0a";
      static unsigned int write_00265_00000_len = 4;
      unsigned char *write_00265 = NULL;
      unsigned int write_00265_len = 0;
      write_00265 = cgc_append_buf(write_00265, &write_00265_len, write_00265_00000, write_00265_00000_len);
      if (write_00265_len > 0) {
         cgc_transmit_all(1, write_00265, write_00265_len);
      }
      cgc_free(write_00265);
   } while (0);
   do {
      unsigned char *read_00273;
      unsigned int read_00273_len;
      unsigned int read_00273_ptr = 0;
      //**** delimited read
      static unsigned char read_00273_delim[] = 
         "\x3a\x20";
      read_00273 = NULL;
      read_00273_len = 0;
      int read_00273_res = cgc_delimited_read(0, &read_00273, &read_00273_len, read_00273_delim, 2);
      if (read_00273_res) {} //silence unused variable warning
      cgc_free(read_00273);
      if (read_00273_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00266_00000[] = 
         "\x39\x30\x37\x0a";
      static unsigned int write_00266_00000_len = 4;
      unsigned char *write_00266 = NULL;
      unsigned int write_00266_len = 0;
      write_00266 = cgc_append_buf(write_00266, &write_00266_len, write_00266_00000, write_00266_00000_len);
      if (write_00266_len > 0) {
         cgc_transmit_all(1, write_00266, write_00266_len);
      }
      cgc_free(write_00266);
   } while (0);
   do {
      unsigned char *read_00274;
      unsigned int read_00274_len;
      unsigned int read_00274_ptr = 0;
      //**** delimited read
      static unsigned char read_00274_delim[] = 
         "\x3a\x20";
      read_00274 = NULL;
      read_00274_len = 0;
      int read_00274_res = cgc_delimited_read(0, &read_00274, &read_00274_len, read_00274_delim, 2);
      if (read_00274_res) {} //silence unused variable warning
      cgc_free(read_00274);
      if (read_00274_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00267_00000[] = 
         "\x33\x38\x37\x0a";
      static unsigned int write_00267_00000_len = 4;
      unsigned char *write_00267 = NULL;
      unsigned int write_00267_len = 0;
      write_00267 = cgc_append_buf(write_00267, &write_00267_len, write_00267_00000, write_00267_00000_len);
      if (write_00267_len > 0) {
         cgc_transmit_all(1, write_00267, write_00267_len);
      }
      cgc_free(write_00267);
   } while (0);
   do {
      unsigned char *read_00275;
      unsigned int read_00275_len;
      unsigned int read_00275_ptr = 0;
      //**** delimited read
      static unsigned char read_00275_delim[] = 
         "\x3a\x20";
      read_00275 = NULL;
      read_00275_len = 0;
      int read_00275_res = cgc_delimited_read(0, &read_00275, &read_00275_len, read_00275_delim, 2);
      if (read_00275_res) {} //silence unused variable warning
      cgc_free(read_00275);
      if (read_00275_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00268_00000[] = 
         "\x35\x39\x32\x0a";
      static unsigned int write_00268_00000_len = 4;
      unsigned char *write_00268 = NULL;
      unsigned int write_00268_len = 0;
      write_00268 = cgc_append_buf(write_00268, &write_00268_len, write_00268_00000, write_00268_00000_len);
      if (write_00268_len > 0) {
         cgc_transmit_all(1, write_00268, write_00268_len);
      }
      cgc_free(write_00268);
   } while (0);
   do {
      unsigned char *read_00276;
      unsigned int read_00276_len;
      unsigned int read_00276_ptr = 0;
      //**** delimited read
      static unsigned char read_00276_delim[] = 
         "\x3a\x20";
      read_00276 = NULL;
      read_00276_len = 0;
      int read_00276_res = cgc_delimited_read(0, &read_00276, &read_00276_len, read_00276_delim, 2);
      if (read_00276_res) {} //silence unused variable warning
      cgc_free(read_00276);
      if (read_00276_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00269_00000[] = 
         "\x39\x34\x34\x0a";
      static unsigned int write_00269_00000_len = 4;
      unsigned char *write_00269 = NULL;
      unsigned int write_00269_len = 0;
      write_00269 = cgc_append_buf(write_00269, &write_00269_len, write_00269_00000, write_00269_00000_len);
      if (write_00269_len > 0) {
         cgc_transmit_all(1, write_00269, write_00269_len);
      }
      cgc_free(write_00269);
   } while (0);
   do {
      unsigned char *read_00277;
      unsigned int read_00277_len;
      unsigned int read_00277_ptr = 0;
      //**** delimited read
      static unsigned char read_00277_delim[] = 
         "\x3a\x20";
      read_00277 = NULL;
      read_00277_len = 0;
      int read_00277_res = cgc_delimited_read(0, &read_00277, &read_00277_len, read_00277_delim, 2);
      if (read_00277_res) {} //silence unused variable warning
      cgc_free(read_00277);
      if (read_00277_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00270_00000[] = 
         "\x38\x36\x35\x0a";
      static unsigned int write_00270_00000_len = 4;
      unsigned char *write_00270 = NULL;
      unsigned int write_00270_len = 0;
      write_00270 = cgc_append_buf(write_00270, &write_00270_len, write_00270_00000, write_00270_00000_len);
      if (write_00270_len > 0) {
         cgc_transmit_all(1, write_00270, write_00270_len);
      }
      cgc_free(write_00270);
   } while (0);
   do {
      unsigned char *read_00278;
      unsigned int read_00278_len;
      unsigned int read_00278_ptr = 0;
      //**** delimited read
      static unsigned char read_00278_delim[] = 
         "\x3a\x20";
      read_00278 = NULL;
      read_00278_len = 0;
      int read_00278_res = cgc_delimited_read(0, &read_00278, &read_00278_len, read_00278_delim, 2);
      if (read_00278_res) {} //silence unused variable warning
      cgc_free(read_00278);
      if (read_00278_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00271_00000[] = 
         "\x36\x39\x0a";
      static unsigned int write_00271_00000_len = 3;
      unsigned char *write_00271 = NULL;
      unsigned int write_00271_len = 0;
      write_00271 = cgc_append_buf(write_00271, &write_00271_len, write_00271_00000, write_00271_00000_len);
      if (write_00271_len > 0) {
         cgc_transmit_all(1, write_00271, write_00271_len);
      }
      cgc_free(write_00271);
   } while (0);
   do {
      unsigned char *read_00279;
      unsigned int read_00279_len;
      unsigned int read_00279_ptr = 0;
      //**** delimited read
      static unsigned char read_00279_delim[] = 
         "\x3a\x20";
      read_00279 = NULL;
      read_00279_len = 0;
      int read_00279_res = cgc_delimited_read(0, &read_00279, &read_00279_len, read_00279_delim, 2);
      if (read_00279_res) {} //silence unused variable warning
      cgc_free(read_00279);
      if (read_00279_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00272_00000[] = 
         "\x31\x30\x37\x0a";
      static unsigned int write_00272_00000_len = 4;
      unsigned char *write_00272 = NULL;
      unsigned int write_00272_len = 0;
      write_00272 = cgc_append_buf(write_00272, &write_00272_len, write_00272_00000, write_00272_00000_len);
      if (write_00272_len > 0) {
         cgc_transmit_all(1, write_00272, write_00272_len);
      }
      cgc_free(write_00272);
   } while (0);
   do {
      unsigned char *read_00280;
      unsigned int read_00280_len;
      unsigned int read_00280_ptr = 0;
      //**** delimited read
      static unsigned char read_00280_delim[] = 
         "\x3a\x20";
      read_00280 = NULL;
      read_00280_len = 0;
      int read_00280_res = cgc_delimited_read(0, &read_00280, &read_00280_len, read_00280_delim, 2);
      if (read_00280_res) {} //silence unused variable warning
      cgc_free(read_00280);
      if (read_00280_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00273_00000[] = 
         "\x33\x38\x37\x0a";
      static unsigned int write_00273_00000_len = 4;
      unsigned char *write_00273 = NULL;
      unsigned int write_00273_len = 0;
      write_00273 = cgc_append_buf(write_00273, &write_00273_len, write_00273_00000, write_00273_00000_len);
      if (write_00273_len > 0) {
         cgc_transmit_all(1, write_00273, write_00273_len);
      }
      cgc_free(write_00273);
   } while (0);
   do {
      unsigned char *read_00281;
      unsigned int read_00281_len;
      unsigned int read_00281_ptr = 0;
      //**** delimited read
      static unsigned char read_00281_delim[] = 
         "\x3a\x20";
      read_00281 = NULL;
      read_00281_len = 0;
      int read_00281_res = cgc_delimited_read(0, &read_00281, &read_00281_len, read_00281_delim, 2);
      if (read_00281_res) {} //silence unused variable warning
      cgc_free(read_00281);
      if (read_00281_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00274_00000[] = 
         "\x39\x31\x35\x0a";
      static unsigned int write_00274_00000_len = 4;
      unsigned char *write_00274 = NULL;
      unsigned int write_00274_len = 0;
      write_00274 = cgc_append_buf(write_00274, &write_00274_len, write_00274_00000, write_00274_00000_len);
      if (write_00274_len > 0) {
         cgc_transmit_all(1, write_00274, write_00274_len);
      }
      cgc_free(write_00274);
   } while (0);
   do {
      unsigned char *read_00282;
      unsigned int read_00282_len;
      unsigned int read_00282_ptr = 0;
      //**** delimited read
      static unsigned char read_00282_delim[] = 
         "\x3a\x20";
      read_00282 = NULL;
      read_00282_len = 0;
      int read_00282_res = cgc_delimited_read(0, &read_00282, &read_00282_len, read_00282_delim, 2);
      if (read_00282_res) {} //silence unused variable warning
      cgc_free(read_00282);
      if (read_00282_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00275_00000[] = 
         "\x36\x34\x0a";
      static unsigned int write_00275_00000_len = 3;
      unsigned char *write_00275 = NULL;
      unsigned int write_00275_len = 0;
      write_00275 = cgc_append_buf(write_00275, &write_00275_len, write_00275_00000, write_00275_00000_len);
      if (write_00275_len > 0) {
         cgc_transmit_all(1, write_00275, write_00275_len);
      }
      cgc_free(write_00275);
   } while (0);
   do {
      unsigned char *read_00283;
      unsigned int read_00283_len;
      unsigned int read_00283_ptr = 0;
      //**** delimited read
      static unsigned char read_00283_delim[] = 
         "\x3a\x20";
      read_00283 = NULL;
      read_00283_len = 0;
      int read_00283_res = cgc_delimited_read(0, &read_00283, &read_00283_len, read_00283_delim, 2);
      if (read_00283_res) {} //silence unused variable warning
      cgc_free(read_00283);
      if (read_00283_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00276_00000[] = 
         "\x34\x30\x36\x0a";
      static unsigned int write_00276_00000_len = 4;
      unsigned char *write_00276 = NULL;
      unsigned int write_00276_len = 0;
      write_00276 = cgc_append_buf(write_00276, &write_00276_len, write_00276_00000, write_00276_00000_len);
      if (write_00276_len > 0) {
         cgc_transmit_all(1, write_00276, write_00276_len);
      }
      cgc_free(write_00276);
   } while (0);
   do {
      unsigned char *read_00284;
      unsigned int read_00284_len;
      unsigned int read_00284_ptr = 0;
      //**** delimited read
      static unsigned char read_00284_delim[] = 
         "\x3a\x20";
      read_00284 = NULL;
      read_00284_len = 0;
      int read_00284_res = cgc_delimited_read(0, &read_00284, &read_00284_len, read_00284_delim, 2);
      if (read_00284_res) {} //silence unused variable warning
      cgc_free(read_00284);
      if (read_00284_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00277_00000[] = 
         "\x32\x31\x34\x0a";
      static unsigned int write_00277_00000_len = 4;
      unsigned char *write_00277 = NULL;
      unsigned int write_00277_len = 0;
      write_00277 = cgc_append_buf(write_00277, &write_00277_len, write_00277_00000, write_00277_00000_len);
      if (write_00277_len > 0) {
         cgc_transmit_all(1, write_00277, write_00277_len);
      }
      cgc_free(write_00277);
   } while (0);
   do {
      unsigned char *read_00285;
      unsigned int read_00285_len;
      unsigned int read_00285_ptr = 0;
      //**** delimited read
      static unsigned char read_00285_delim[] = 
         "\x3a\x20";
      read_00285 = NULL;
      read_00285_len = 0;
      int read_00285_res = cgc_delimited_read(0, &read_00285, &read_00285_len, read_00285_delim, 2);
      if (read_00285_res) {} //silence unused variable warning
      cgc_free(read_00285);
      if (read_00285_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00278_00000[] = 
         "\x38\x39\x35\x0a";
      static unsigned int write_00278_00000_len = 4;
      unsigned char *write_00278 = NULL;
      unsigned int write_00278_len = 0;
      write_00278 = cgc_append_buf(write_00278, &write_00278_len, write_00278_00000, write_00278_00000_len);
      if (write_00278_len > 0) {
         cgc_transmit_all(1, write_00278, write_00278_len);
      }
      cgc_free(write_00278);
   } while (0);
   do {
      unsigned char *read_00286;
      unsigned int read_00286_len;
      unsigned int read_00286_ptr = 0;
      //**** delimited read
      static unsigned char read_00286_delim[] = 
         "\x3a\x20";
      read_00286 = NULL;
      read_00286_len = 0;
      int read_00286_res = cgc_delimited_read(0, &read_00286, &read_00286_len, read_00286_delim, 2);
      if (read_00286_res) {} //silence unused variable warning
      cgc_free(read_00286);
      if (read_00286_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00279_00000[] = 
         "\x34\x32\x37\x0a";
      static unsigned int write_00279_00000_len = 4;
      unsigned char *write_00279 = NULL;
      unsigned int write_00279_len = 0;
      write_00279 = cgc_append_buf(write_00279, &write_00279_len, write_00279_00000, write_00279_00000_len);
      if (write_00279_len > 0) {
         cgc_transmit_all(1, write_00279, write_00279_len);
      }
      cgc_free(write_00279);
   } while (0);
   do {
      unsigned char *read_00287;
      unsigned int read_00287_len;
      unsigned int read_00287_ptr = 0;
      //**** delimited read
      static unsigned char read_00287_delim[] = 
         "\x3a\x20";
      read_00287 = NULL;
      read_00287_len = 0;
      int read_00287_res = cgc_delimited_read(0, &read_00287, &read_00287_len, read_00287_delim, 2);
      if (read_00287_res) {} //silence unused variable warning
      cgc_free(read_00287);
      if (read_00287_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00280_00000[] = 
         "\x35\x32\x33\x0a";
      static unsigned int write_00280_00000_len = 4;
      unsigned char *write_00280 = NULL;
      unsigned int write_00280_len = 0;
      write_00280 = cgc_append_buf(write_00280, &write_00280_len, write_00280_00000, write_00280_00000_len);
      if (write_00280_len > 0) {
         cgc_transmit_all(1, write_00280, write_00280_len);
      }
      cgc_free(write_00280);
   } while (0);
   do {
      unsigned char *read_00288;
      unsigned int read_00288_len;
      unsigned int read_00288_ptr = 0;
      //**** delimited read
      static unsigned char read_00288_delim[] = 
         "\x3a\x20";
      read_00288 = NULL;
      read_00288_len = 0;
      int read_00288_res = cgc_delimited_read(0, &read_00288, &read_00288_len, read_00288_delim, 2);
      if (read_00288_res) {} //silence unused variable warning
      cgc_free(read_00288);
      if (read_00288_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00281_00000[] = 
         "\x39\x34\x33\x0a";
      static unsigned int write_00281_00000_len = 4;
      unsigned char *write_00281 = NULL;
      unsigned int write_00281_len = 0;
      write_00281 = cgc_append_buf(write_00281, &write_00281_len, write_00281_00000, write_00281_00000_len);
      if (write_00281_len > 0) {
         cgc_transmit_all(1, write_00281, write_00281_len);
      }
      cgc_free(write_00281);
   } while (0);
   do {
      unsigned char *read_00289;
      unsigned int read_00289_len;
      unsigned int read_00289_ptr = 0;
      //**** delimited read
      static unsigned char read_00289_delim[] = 
         "\x3a\x20";
      read_00289 = NULL;
      read_00289_len = 0;
      int read_00289_res = cgc_delimited_read(0, &read_00289, &read_00289_len, read_00289_delim, 2);
      if (read_00289_res) {} //silence unused variable warning
      cgc_free(read_00289);
      if (read_00289_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00282_00000[] = 
         "\x39\x30\x30\x0a";
      static unsigned int write_00282_00000_len = 4;
      unsigned char *write_00282 = NULL;
      unsigned int write_00282_len = 0;
      write_00282 = cgc_append_buf(write_00282, &write_00282_len, write_00282_00000, write_00282_00000_len);
      if (write_00282_len > 0) {
         cgc_transmit_all(1, write_00282, write_00282_len);
      }
      cgc_free(write_00282);
   } while (0);
   do {
      unsigned char *read_00290;
      unsigned int read_00290_len;
      unsigned int read_00290_ptr = 0;
      //**** delimited read
      static unsigned char read_00290_delim[] = 
         "\x3a\x20";
      read_00290 = NULL;
      read_00290_len = 0;
      int read_00290_res = cgc_delimited_read(0, &read_00290, &read_00290_len, read_00290_delim, 2);
      if (read_00290_res) {} //silence unused variable warning
      cgc_free(read_00290);
      if (read_00290_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00283_00000[] = 
         "\x35\x31\x35\x0a";
      static unsigned int write_00283_00000_len = 4;
      unsigned char *write_00283 = NULL;
      unsigned int write_00283_len = 0;
      write_00283 = cgc_append_buf(write_00283, &write_00283_len, write_00283_00000, write_00283_00000_len);
      if (write_00283_len > 0) {
         cgc_transmit_all(1, write_00283, write_00283_len);
      }
      cgc_free(write_00283);
   } while (0);
   do {
      unsigned char *read_00291;
      unsigned int read_00291_len;
      unsigned int read_00291_ptr = 0;
      //**** delimited read
      static unsigned char read_00291_delim[] = 
         "\x3a\x20";
      read_00291 = NULL;
      read_00291_len = 0;
      int read_00291_res = cgc_delimited_read(0, &read_00291, &read_00291_len, read_00291_delim, 2);
      if (read_00291_res) {} //silence unused variable warning
      cgc_free(read_00291);
      if (read_00291_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00284_00000[] = 
         "\x38\x31\x32\x0a";
      static unsigned int write_00284_00000_len = 4;
      unsigned char *write_00284 = NULL;
      unsigned int write_00284_len = 0;
      write_00284 = cgc_append_buf(write_00284, &write_00284_len, write_00284_00000, write_00284_00000_len);
      if (write_00284_len > 0) {
         cgc_transmit_all(1, write_00284, write_00284_len);
      }
      cgc_free(write_00284);
   } while (0);
   do {
      unsigned char *read_00292;
      unsigned int read_00292_len;
      unsigned int read_00292_ptr = 0;
      //**** delimited read
      static unsigned char read_00292_delim[] = 
         "\x3a\x20";
      read_00292 = NULL;
      read_00292_len = 0;
      int read_00292_res = cgc_delimited_read(0, &read_00292, &read_00292_len, read_00292_delim, 2);
      if (read_00292_res) {} //silence unused variable warning
      cgc_free(read_00292);
      if (read_00292_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00285_00000[] = 
         "\x32\x32\x37\x0a";
      static unsigned int write_00285_00000_len = 4;
      unsigned char *write_00285 = NULL;
      unsigned int write_00285_len = 0;
      write_00285 = cgc_append_buf(write_00285, &write_00285_len, write_00285_00000, write_00285_00000_len);
      if (write_00285_len > 0) {
         cgc_transmit_all(1, write_00285, write_00285_len);
      }
      cgc_free(write_00285);
   } while (0);
   do {
      unsigned char *read_00293;
      unsigned int read_00293_len;
      unsigned int read_00293_ptr = 0;
      //**** delimited read
      static unsigned char read_00293_delim[] = 
         "\x3a\x20";
      read_00293 = NULL;
      read_00293_len = 0;
      int read_00293_res = cgc_delimited_read(0, &read_00293, &read_00293_len, read_00293_delim, 2);
      if (read_00293_res) {} //silence unused variable warning
      cgc_free(read_00293);
      if (read_00293_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00286_00000[] = 
         "\x36\x37\x31\x0a";
      static unsigned int write_00286_00000_len = 4;
      unsigned char *write_00286 = NULL;
      unsigned int write_00286_len = 0;
      write_00286 = cgc_append_buf(write_00286, &write_00286_len, write_00286_00000, write_00286_00000_len);
      if (write_00286_len > 0) {
         cgc_transmit_all(1, write_00286, write_00286_len);
      }
      cgc_free(write_00286);
   } while (0);
   do {
      unsigned char *read_00294;
      unsigned int read_00294_len;
      unsigned int read_00294_ptr = 0;
      //**** delimited read
      static unsigned char read_00294_delim[] = 
         "\x3a\x20";
      read_00294 = NULL;
      read_00294_len = 0;
      int read_00294_res = cgc_delimited_read(0, &read_00294, &read_00294_len, read_00294_delim, 2);
      if (read_00294_res) {} //silence unused variable warning
      cgc_free(read_00294);
      if (read_00294_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00287_00000[] = 
         "\x35\x39\x36\x0a";
      static unsigned int write_00287_00000_len = 4;
      unsigned char *write_00287 = NULL;
      unsigned int write_00287_len = 0;
      write_00287 = cgc_append_buf(write_00287, &write_00287_len, write_00287_00000, write_00287_00000_len);
      if (write_00287_len > 0) {
         cgc_transmit_all(1, write_00287, write_00287_len);
      }
      cgc_free(write_00287);
   } while (0);
   do {
      unsigned char *read_00295;
      unsigned int read_00295_len;
      unsigned int read_00295_ptr = 0;
      //**** delimited read
      static unsigned char read_00295_delim[] = 
         "\x3a\x20";
      read_00295 = NULL;
      read_00295_len = 0;
      int read_00295_res = cgc_delimited_read(0, &read_00295, &read_00295_len, read_00295_delim, 2);
      if (read_00295_res) {} //silence unused variable warning
      cgc_free(read_00295);
      if (read_00295_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00288_00000[] = 
         "\x36\x38\x33\x0a";
      static unsigned int write_00288_00000_len = 4;
      unsigned char *write_00288 = NULL;
      unsigned int write_00288_len = 0;
      write_00288 = cgc_append_buf(write_00288, &write_00288_len, write_00288_00000, write_00288_00000_len);
      if (write_00288_len > 0) {
         cgc_transmit_all(1, write_00288, write_00288_len);
      }
      cgc_free(write_00288);
   } while (0);
   do {
      unsigned char *read_00296;
      unsigned int read_00296_len;
      unsigned int read_00296_ptr = 0;
      //**** delimited read
      static unsigned char read_00296_delim[] = 
         "\x3a\x20";
      read_00296 = NULL;
      read_00296_len = 0;
      int read_00296_res = cgc_delimited_read(0, &read_00296, &read_00296_len, read_00296_delim, 2);
      if (read_00296_res) {} //silence unused variable warning
      cgc_free(read_00296);
      if (read_00296_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00289_00000[] = 
         "\x37\x35\x36\x0a";
      static unsigned int write_00289_00000_len = 4;
      unsigned char *write_00289 = NULL;
      unsigned int write_00289_len = 0;
      write_00289 = cgc_append_buf(write_00289, &write_00289_len, write_00289_00000, write_00289_00000_len);
      if (write_00289_len > 0) {
         cgc_transmit_all(1, write_00289, write_00289_len);
      }
      cgc_free(write_00289);
   } while (0);
   do {
      unsigned char *read_00297;
      unsigned int read_00297_len;
      unsigned int read_00297_ptr = 0;
      //**** delimited read
      static unsigned char read_00297_delim[] = 
         "\x3a\x20";
      read_00297 = NULL;
      read_00297_len = 0;
      int read_00297_res = cgc_delimited_read(0, &read_00297, &read_00297_len, read_00297_delim, 2);
      if (read_00297_res) {} //silence unused variable warning
      cgc_free(read_00297);
      if (read_00297_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00290_00000[] = 
         "\x38\x36\x35\x0a";
      static unsigned int write_00290_00000_len = 4;
      unsigned char *write_00290 = NULL;
      unsigned int write_00290_len = 0;
      write_00290 = cgc_append_buf(write_00290, &write_00290_len, write_00290_00000, write_00290_00000_len);
      if (write_00290_len > 0) {
         cgc_transmit_all(1, write_00290, write_00290_len);
      }
      cgc_free(write_00290);
   } while (0);
   do {
      unsigned char *read_00298;
      unsigned int read_00298_len;
      unsigned int read_00298_ptr = 0;
      //**** delimited read
      static unsigned char read_00298_delim[] = 
         "\x3a\x20";
      read_00298 = NULL;
      read_00298_len = 0;
      int read_00298_res = cgc_delimited_read(0, &read_00298, &read_00298_len, read_00298_delim, 2);
      if (read_00298_res) {} //silence unused variable warning
      cgc_free(read_00298);
      if (read_00298_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00291_00000[] = 
         "\x35\x30\x0a";
      static unsigned int write_00291_00000_len = 3;
      unsigned char *write_00291 = NULL;
      unsigned int write_00291_len = 0;
      write_00291 = cgc_append_buf(write_00291, &write_00291_len, write_00291_00000, write_00291_00000_len);
      if (write_00291_len > 0) {
         cgc_transmit_all(1, write_00291, write_00291_len);
      }
      cgc_free(write_00291);
   } while (0);
   do {
      unsigned char *read_00299;
      unsigned int read_00299_len;
      unsigned int read_00299_ptr = 0;
      //**** delimited read
      static unsigned char read_00299_delim[] = 
         "\x3a\x20";
      read_00299 = NULL;
      read_00299_len = 0;
      int read_00299_res = cgc_delimited_read(0, &read_00299, &read_00299_len, read_00299_delim, 2);
      if (read_00299_res) {} //silence unused variable warning
      cgc_free(read_00299);
      if (read_00299_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00292_00000[] = 
         "\x37\x32\x34\x0a";
      static unsigned int write_00292_00000_len = 4;
      unsigned char *write_00292 = NULL;
      unsigned int write_00292_len = 0;
      write_00292 = cgc_append_buf(write_00292, &write_00292_len, write_00292_00000, write_00292_00000_len);
      if (write_00292_len > 0) {
         cgc_transmit_all(1, write_00292, write_00292_len);
      }
      cgc_free(write_00292);
   } while (0);
   do {
      unsigned char *read_00300;
      unsigned int read_00300_len;
      unsigned int read_00300_ptr = 0;
      //**** delimited read
      static unsigned char read_00300_delim[] = 
         "\x3a\x20";
      read_00300 = NULL;
      read_00300_len = 0;
      int read_00300_res = cgc_delimited_read(0, &read_00300, &read_00300_len, read_00300_delim, 2);
      if (read_00300_res) {} //silence unused variable warning
      cgc_free(read_00300);
      if (read_00300_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00293_00000[] = 
         "\x39\x35\x36\x0a";
      static unsigned int write_00293_00000_len = 4;
      unsigned char *write_00293 = NULL;
      unsigned int write_00293_len = 0;
      write_00293 = cgc_append_buf(write_00293, &write_00293_len, write_00293_00000, write_00293_00000_len);
      if (write_00293_len > 0) {
         cgc_transmit_all(1, write_00293, write_00293_len);
      }
      cgc_free(write_00293);
   } while (0);
   do {
      unsigned char *read_00301;
      unsigned int read_00301_len;
      unsigned int read_00301_ptr = 0;
      //**** delimited read
      static unsigned char read_00301_delim[] = 
         "\x3a\x20";
      read_00301 = NULL;
      read_00301_len = 0;
      int read_00301_res = cgc_delimited_read(0, &read_00301, &read_00301_len, read_00301_delim, 2);
      if (read_00301_res) {} //silence unused variable warning
      cgc_free(read_00301);
      if (read_00301_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00294_00000[] = 
         "\x34\x35\x32\x0a";
      static unsigned int write_00294_00000_len = 4;
      unsigned char *write_00294 = NULL;
      unsigned int write_00294_len = 0;
      write_00294 = cgc_append_buf(write_00294, &write_00294_len, write_00294_00000, write_00294_00000_len);
      if (write_00294_len > 0) {
         cgc_transmit_all(1, write_00294, write_00294_len);
      }
      cgc_free(write_00294);
   } while (0);
   do {
      unsigned char *read_00302;
      unsigned int read_00302_len;
      unsigned int read_00302_ptr = 0;
      //**** delimited read
      static unsigned char read_00302_delim[] = 
         "\x3a\x20";
      read_00302 = NULL;
      read_00302_len = 0;
      int read_00302_res = cgc_delimited_read(0, &read_00302, &read_00302_len, read_00302_delim, 2);
      if (read_00302_res) {} //silence unused variable warning
      cgc_free(read_00302);
      if (read_00302_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00295_00000[] = 
         "\x33\x38\x30\x0a";
      static unsigned int write_00295_00000_len = 4;
      unsigned char *write_00295 = NULL;
      unsigned int write_00295_len = 0;
      write_00295 = cgc_append_buf(write_00295, &write_00295_len, write_00295_00000, write_00295_00000_len);
      if (write_00295_len > 0) {
         cgc_transmit_all(1, write_00295, write_00295_len);
      }
      cgc_free(write_00295);
   } while (0);
   do {
      unsigned char *read_00303;
      unsigned int read_00303_len;
      unsigned int read_00303_ptr = 0;
      //**** delimited read
      static unsigned char read_00303_delim[] = 
         "\x3a\x20";
      read_00303 = NULL;
      read_00303_len = 0;
      int read_00303_res = cgc_delimited_read(0, &read_00303, &read_00303_len, read_00303_delim, 2);
      if (read_00303_res) {} //silence unused variable warning
      cgc_free(read_00303);
      if (read_00303_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00296_00000[] = 
         "\x35\x39\x32\x0a";
      static unsigned int write_00296_00000_len = 4;
      unsigned char *write_00296 = NULL;
      unsigned int write_00296_len = 0;
      write_00296 = cgc_append_buf(write_00296, &write_00296_len, write_00296_00000, write_00296_00000_len);
      if (write_00296_len > 0) {
         cgc_transmit_all(1, write_00296, write_00296_len);
      }
      cgc_free(write_00296);
   } while (0);
   do {
      unsigned char *read_00304;
      unsigned int read_00304_len;
      unsigned int read_00304_ptr = 0;
      //**** delimited read
      static unsigned char read_00304_delim[] = 
         "\x3a\x20";
      read_00304 = NULL;
      read_00304_len = 0;
      int read_00304_res = cgc_delimited_read(0, &read_00304, &read_00304_len, read_00304_delim, 2);
      if (read_00304_res) {} //silence unused variable warning
      cgc_free(read_00304);
      if (read_00304_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00297_00000[] = 
         "\x36\x33\x33\x0a";
      static unsigned int write_00297_00000_len = 4;
      unsigned char *write_00297 = NULL;
      unsigned int write_00297_len = 0;
      write_00297 = cgc_append_buf(write_00297, &write_00297_len, write_00297_00000, write_00297_00000_len);
      if (write_00297_len > 0) {
         cgc_transmit_all(1, write_00297, write_00297_len);
      }
      cgc_free(write_00297);
   } while (0);
   do {
      unsigned char *read_00305;
      unsigned int read_00305_len;
      unsigned int read_00305_ptr = 0;
      //**** delimited read
      static unsigned char read_00305_delim[] = 
         "\x3a\x20";
      read_00305 = NULL;
      read_00305_len = 0;
      int read_00305_res = cgc_delimited_read(0, &read_00305, &read_00305_len, read_00305_delim, 2);
      if (read_00305_res) {} //silence unused variable warning
      cgc_free(read_00305);
      if (read_00305_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00298_00000[] = 
         "\x32\x33\x37\x0a";
      static unsigned int write_00298_00000_len = 4;
      unsigned char *write_00298 = NULL;
      unsigned int write_00298_len = 0;
      write_00298 = cgc_append_buf(write_00298, &write_00298_len, write_00298_00000, write_00298_00000_len);
      if (write_00298_len > 0) {
         cgc_transmit_all(1, write_00298, write_00298_len);
      }
      cgc_free(write_00298);
   } while (0);
   do {
      unsigned char *read_00306;
      unsigned int read_00306_len;
      unsigned int read_00306_ptr = 0;
      //**** delimited read
      static unsigned char read_00306_delim[] = 
         "\x3a\x20";
      read_00306 = NULL;
      read_00306_len = 0;
      int read_00306_res = cgc_delimited_read(0, &read_00306, &read_00306_len, read_00306_delim, 2);
      if (read_00306_res) {} //silence unused variable warning
      cgc_free(read_00306);
      if (read_00306_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00299_00000[] = 
         "\x37\x35\x30\x0a";
      static unsigned int write_00299_00000_len = 4;
      unsigned char *write_00299 = NULL;
      unsigned int write_00299_len = 0;
      write_00299 = cgc_append_buf(write_00299, &write_00299_len, write_00299_00000, write_00299_00000_len);
      if (write_00299_len > 0) {
         cgc_transmit_all(1, write_00299, write_00299_len);
      }
      cgc_free(write_00299);
   } while (0);
   do {
      unsigned char *read_00307;
      unsigned int read_00307_len;
      unsigned int read_00307_ptr = 0;
      //**** delimited read
      static unsigned char read_00307_delim[] = 
         "\x3a\x20";
      read_00307 = NULL;
      read_00307_len = 0;
      int read_00307_res = cgc_delimited_read(0, &read_00307, &read_00307_len, read_00307_delim, 2);
      if (read_00307_res) {} //silence unused variable warning
      cgc_free(read_00307);
      if (read_00307_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00300_00000[] = 
         "\x36\x36\x36\x0a";
      static unsigned int write_00300_00000_len = 4;
      unsigned char *write_00300 = NULL;
      unsigned int write_00300_len = 0;
      write_00300 = cgc_append_buf(write_00300, &write_00300_len, write_00300_00000, write_00300_00000_len);
      if (write_00300_len > 0) {
         cgc_transmit_all(1, write_00300, write_00300_len);
      }
      cgc_free(write_00300);
   } while (0);
   do {
      unsigned char *read_00308;
      unsigned int read_00308_len;
      unsigned int read_00308_ptr = 0;
      //**** delimited read
      static unsigned char read_00308_delim[] = 
         "\x3a\x20";
      read_00308 = NULL;
      read_00308_len = 0;
      int read_00308_res = cgc_delimited_read(0, &read_00308, &read_00308_len, read_00308_delim, 2);
      if (read_00308_res) {} //silence unused variable warning
      cgc_free(read_00308);
      if (read_00308_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00301_00000[] = 
         "\x39\x31\x34\x0a";
      static unsigned int write_00301_00000_len = 4;
      unsigned char *write_00301 = NULL;
      unsigned int write_00301_len = 0;
      write_00301 = cgc_append_buf(write_00301, &write_00301_len, write_00301_00000, write_00301_00000_len);
      if (write_00301_len > 0) {
         cgc_transmit_all(1, write_00301, write_00301_len);
      }
      cgc_free(write_00301);
   } while (0);
   do {
      unsigned char *read_00309;
      unsigned int read_00309_len;
      unsigned int read_00309_ptr = 0;
      //**** delimited read
      static unsigned char read_00309_delim[] = 
         "\x3a\x20";
      read_00309 = NULL;
      read_00309_len = 0;
      int read_00309_res = cgc_delimited_read(0, &read_00309, &read_00309_len, read_00309_delim, 2);
      if (read_00309_res) {} //silence unused variable warning
      cgc_free(read_00309);
      if (read_00309_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00302_00000[] = 
         "\x39\x37\x33\x0a";
      static unsigned int write_00302_00000_len = 4;
      unsigned char *write_00302 = NULL;
      unsigned int write_00302_len = 0;
      write_00302 = cgc_append_buf(write_00302, &write_00302_len, write_00302_00000, write_00302_00000_len);
      if (write_00302_len > 0) {
         cgc_transmit_all(1, write_00302, write_00302_len);
      }
      cgc_free(write_00302);
   } while (0);
   do {
      unsigned char *read_00310;
      unsigned int read_00310_len;
      unsigned int read_00310_ptr = 0;
      //**** delimited read
      static unsigned char read_00310_delim[] = 
         "\x3a\x20";
      read_00310 = NULL;
      read_00310_len = 0;
      int read_00310_res = cgc_delimited_read(0, &read_00310, &read_00310_len, read_00310_delim, 2);
      if (read_00310_res) {} //silence unused variable warning
      cgc_free(read_00310);
      if (read_00310_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00303_00000[] = 
         "\x33\x34\x36\x0a";
      static unsigned int write_00303_00000_len = 4;
      unsigned char *write_00303 = NULL;
      unsigned int write_00303_len = 0;
      write_00303 = cgc_append_buf(write_00303, &write_00303_len, write_00303_00000, write_00303_00000_len);
      if (write_00303_len > 0) {
         cgc_transmit_all(1, write_00303, write_00303_len);
      }
      cgc_free(write_00303);
   } while (0);
   do {
      unsigned char *read_00311;
      unsigned int read_00311_len;
      unsigned int read_00311_ptr = 0;
      //**** delimited read
      static unsigned char read_00311_delim[] = 
         "\x3a\x20";
      read_00311 = NULL;
      read_00311_len = 0;
      int read_00311_res = cgc_delimited_read(0, &read_00311, &read_00311_len, read_00311_delim, 2);
      if (read_00311_res) {} //silence unused variable warning
      cgc_free(read_00311);
      if (read_00311_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00304_00000[] = 
         "\x33\x37\x32\x0a";
      static unsigned int write_00304_00000_len = 4;
      unsigned char *write_00304 = NULL;
      unsigned int write_00304_len = 0;
      write_00304 = cgc_append_buf(write_00304, &write_00304_len, write_00304_00000, write_00304_00000_len);
      if (write_00304_len > 0) {
         cgc_transmit_all(1, write_00304, write_00304_len);
      }
      cgc_free(write_00304);
   } while (0);
   do {
      unsigned char *read_00312;
      unsigned int read_00312_len;
      unsigned int read_00312_ptr = 0;
      //**** delimited read
      static unsigned char read_00312_delim[] = 
         "\x3a\x20";
      read_00312 = NULL;
      read_00312_len = 0;
      int read_00312_res = cgc_delimited_read(0, &read_00312, &read_00312_len, read_00312_delim, 2);
      if (read_00312_res) {} //silence unused variable warning
      cgc_free(read_00312);
      if (read_00312_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00305_00000[] = 
         "\x33\x30\x39\x0a";
      static unsigned int write_00305_00000_len = 4;
      unsigned char *write_00305 = NULL;
      unsigned int write_00305_len = 0;
      write_00305 = cgc_append_buf(write_00305, &write_00305_len, write_00305_00000, write_00305_00000_len);
      if (write_00305_len > 0) {
         cgc_transmit_all(1, write_00305, write_00305_len);
      }
      cgc_free(write_00305);
   } while (0);
   do {
      unsigned char *read_00313;
      unsigned int read_00313_len;
      unsigned int read_00313_ptr = 0;
      //**** delimited read
      static unsigned char read_00313_delim[] = 
         "\x3a\x20";
      read_00313 = NULL;
      read_00313_len = 0;
      int read_00313_res = cgc_delimited_read(0, &read_00313, &read_00313_len, read_00313_delim, 2);
      if (read_00313_res) {} //silence unused variable warning
      cgc_free(read_00313);
      if (read_00313_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00306_00000[] = 
         "\x31\x38\x33\x0a";
      static unsigned int write_00306_00000_len = 4;
      unsigned char *write_00306 = NULL;
      unsigned int write_00306_len = 0;
      write_00306 = cgc_append_buf(write_00306, &write_00306_len, write_00306_00000, write_00306_00000_len);
      if (write_00306_len > 0) {
         cgc_transmit_all(1, write_00306, write_00306_len);
      }
      cgc_free(write_00306);
   } while (0);
   do {
      unsigned char *read_00314;
      unsigned int read_00314_len;
      unsigned int read_00314_ptr = 0;
      //**** delimited read
      static unsigned char read_00314_delim[] = 
         "\x3a\x20";
      read_00314 = NULL;
      read_00314_len = 0;
      int read_00314_res = cgc_delimited_read(0, &read_00314, &read_00314_len, read_00314_delim, 2);
      if (read_00314_res) {} //silence unused variable warning
      cgc_free(read_00314);
      if (read_00314_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00307_00000[] = 
         "\x32\x37\x0a";
      static unsigned int write_00307_00000_len = 3;
      unsigned char *write_00307 = NULL;
      unsigned int write_00307_len = 0;
      write_00307 = cgc_append_buf(write_00307, &write_00307_len, write_00307_00000, write_00307_00000_len);
      if (write_00307_len > 0) {
         cgc_transmit_all(1, write_00307, write_00307_len);
      }
      cgc_free(write_00307);
   } while (0);
   do {
      unsigned char *read_00315;
      unsigned int read_00315_len;
      unsigned int read_00315_ptr = 0;
      //**** delimited read
      static unsigned char read_00315_delim[] = 
         "\x3a\x20";
      read_00315 = NULL;
      read_00315_len = 0;
      int read_00315_res = cgc_delimited_read(0, &read_00315, &read_00315_len, read_00315_delim, 2);
      if (read_00315_res) {} //silence unused variable warning
      cgc_free(read_00315);
      if (read_00315_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00308_00000[] = 
         "\x34\x35\x31\x0a";
      static unsigned int write_00308_00000_len = 4;
      unsigned char *write_00308 = NULL;
      unsigned int write_00308_len = 0;
      write_00308 = cgc_append_buf(write_00308, &write_00308_len, write_00308_00000, write_00308_00000_len);
      if (write_00308_len > 0) {
         cgc_transmit_all(1, write_00308, write_00308_len);
      }
      cgc_free(write_00308);
   } while (0);
   do {
      unsigned char *read_00316;
      unsigned int read_00316_len;
      unsigned int read_00316_ptr = 0;
      //**** delimited read
      static unsigned char read_00316_delim[] = 
         "\x3a\x20";
      read_00316 = NULL;
      read_00316_len = 0;
      int read_00316_res = cgc_delimited_read(0, &read_00316, &read_00316_len, read_00316_delim, 2);
      if (read_00316_res) {} //silence unused variable warning
      cgc_free(read_00316);
      if (read_00316_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00309_00000[] = 
         "\x33\x34\x36\x0a";
      static unsigned int write_00309_00000_len = 4;
      unsigned char *write_00309 = NULL;
      unsigned int write_00309_len = 0;
      write_00309 = cgc_append_buf(write_00309, &write_00309_len, write_00309_00000, write_00309_00000_len);
      if (write_00309_len > 0) {
         cgc_transmit_all(1, write_00309, write_00309_len);
      }
      cgc_free(write_00309);
   } while (0);
   do {
      unsigned char *read_00317;
      unsigned int read_00317_len;
      unsigned int read_00317_ptr = 0;
      //**** delimited read
      static unsigned char read_00317_delim[] = 
         "\x3a\x20";
      read_00317 = NULL;
      read_00317_len = 0;
      int read_00317_res = cgc_delimited_read(0, &read_00317, &read_00317_len, read_00317_delim, 2);
      if (read_00317_res) {} //silence unused variable warning
      cgc_free(read_00317);
      if (read_00317_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00310_00000[] = 
         "\x38\x31\x0a";
      static unsigned int write_00310_00000_len = 3;
      unsigned char *write_00310 = NULL;
      unsigned int write_00310_len = 0;
      write_00310 = cgc_append_buf(write_00310, &write_00310_len, write_00310_00000, write_00310_00000_len);
      if (write_00310_len > 0) {
         cgc_transmit_all(1, write_00310, write_00310_len);
      }
      cgc_free(write_00310);
   } while (0);
   do {
      unsigned char *read_00318;
      unsigned int read_00318_len;
      unsigned int read_00318_ptr = 0;
      //**** delimited read
      static unsigned char read_00318_delim[] = 
         "\x3a\x20";
      read_00318 = NULL;
      read_00318_len = 0;
      int read_00318_res = cgc_delimited_read(0, &read_00318, &read_00318_len, read_00318_delim, 2);
      if (read_00318_res) {} //silence unused variable warning
      cgc_free(read_00318);
      if (read_00318_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00311_00000[] = 
         "\x35\x39\x35\x0a";
      static unsigned int write_00311_00000_len = 4;
      unsigned char *write_00311 = NULL;
      unsigned int write_00311_len = 0;
      write_00311 = cgc_append_buf(write_00311, &write_00311_len, write_00311_00000, write_00311_00000_len);
      if (write_00311_len > 0) {
         cgc_transmit_all(1, write_00311, write_00311_len);
      }
      cgc_free(write_00311);
   } while (0);
   do {
      unsigned char *read_00319;
      unsigned int read_00319_len;
      unsigned int read_00319_ptr = 0;
      //**** delimited read
      static unsigned char read_00319_delim[] = 
         "\x3a\x20";
      read_00319 = NULL;
      read_00319_len = 0;
      int read_00319_res = cgc_delimited_read(0, &read_00319, &read_00319_len, read_00319_delim, 2);
      if (read_00319_res) {} //silence unused variable warning
      cgc_free(read_00319);
      if (read_00319_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00312_00000[] = 
         "\x31\x31\x36\x0a";
      static unsigned int write_00312_00000_len = 4;
      unsigned char *write_00312 = NULL;
      unsigned int write_00312_len = 0;
      write_00312 = cgc_append_buf(write_00312, &write_00312_len, write_00312_00000, write_00312_00000_len);
      if (write_00312_len > 0) {
         cgc_transmit_all(1, write_00312, write_00312_len);
      }
      cgc_free(write_00312);
   } while (0);
   do {
      unsigned char *read_00320;
      unsigned int read_00320_len;
      unsigned int read_00320_ptr = 0;
      //**** delimited read
      static unsigned char read_00320_delim[] = 
         "\x3a\x20";
      read_00320 = NULL;
      read_00320_len = 0;
      int read_00320_res = cgc_delimited_read(0, &read_00320, &read_00320_len, read_00320_delim, 2);
      if (read_00320_res) {} //silence unused variable warning
      cgc_free(read_00320);
      if (read_00320_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00313_00000[] = 
         "\x33\x38\x30\x0a";
      static unsigned int write_00313_00000_len = 4;
      unsigned char *write_00313 = NULL;
      unsigned int write_00313_len = 0;
      write_00313 = cgc_append_buf(write_00313, &write_00313_len, write_00313_00000, write_00313_00000_len);
      if (write_00313_len > 0) {
         cgc_transmit_all(1, write_00313, write_00313_len);
      }
      cgc_free(write_00313);
   } while (0);
   do {
      unsigned char *read_00321;
      unsigned int read_00321_len;
      unsigned int read_00321_ptr = 0;
      //**** delimited read
      static unsigned char read_00321_delim[] = 
         "\x3a\x20";
      read_00321 = NULL;
      read_00321_len = 0;
      int read_00321_res = cgc_delimited_read(0, &read_00321, &read_00321_len, read_00321_delim, 2);
      if (read_00321_res) {} //silence unused variable warning
      cgc_free(read_00321);
      if (read_00321_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00314_00000[] = 
         "\x35\x35\x35\x0a";
      static unsigned int write_00314_00000_len = 4;
      unsigned char *write_00314 = NULL;
      unsigned int write_00314_len = 0;
      write_00314 = cgc_append_buf(write_00314, &write_00314_len, write_00314_00000, write_00314_00000_len);
      if (write_00314_len > 0) {
         cgc_transmit_all(1, write_00314, write_00314_len);
      }
      cgc_free(write_00314);
   } while (0);
   do {
      unsigned char *read_00322;
      unsigned int read_00322_len;
      unsigned int read_00322_ptr = 0;
      //**** delimited read
      static unsigned char read_00322_delim[] = 
         "\x3a\x20";
      read_00322 = NULL;
      read_00322_len = 0;
      int read_00322_res = cgc_delimited_read(0, &read_00322, &read_00322_len, read_00322_delim, 2);
      if (read_00322_res) {} //silence unused variable warning
      cgc_free(read_00322);
      if (read_00322_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00315_00000[] = 
         "\x39\x34\x39\x0a";
      static unsigned int write_00315_00000_len = 4;
      unsigned char *write_00315 = NULL;
      unsigned int write_00315_len = 0;
      write_00315 = cgc_append_buf(write_00315, &write_00315_len, write_00315_00000, write_00315_00000_len);
      if (write_00315_len > 0) {
         cgc_transmit_all(1, write_00315, write_00315_len);
      }
      cgc_free(write_00315);
   } while (0);
   do {
      unsigned char *read_00323;
      unsigned int read_00323_len;
      unsigned int read_00323_ptr = 0;
      //**** delimited read
      static unsigned char read_00323_delim[] = 
         "\x3a\x20";
      read_00323 = NULL;
      read_00323_len = 0;
      int read_00323_res = cgc_delimited_read(0, &read_00323, &read_00323_len, read_00323_delim, 2);
      if (read_00323_res) {} //silence unused variable warning
      cgc_free(read_00323);
      if (read_00323_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00316_00000[] = 
         "\x39\x36\x30\x0a";
      static unsigned int write_00316_00000_len = 4;
      unsigned char *write_00316 = NULL;
      unsigned int write_00316_len = 0;
      write_00316 = cgc_append_buf(write_00316, &write_00316_len, write_00316_00000, write_00316_00000_len);
      if (write_00316_len > 0) {
         cgc_transmit_all(1, write_00316, write_00316_len);
      }
      cgc_free(write_00316);
   } while (0);
   do {
      unsigned char *read_00324;
      unsigned int read_00324_len;
      unsigned int read_00324_ptr = 0;
      //**** delimited read
      static unsigned char read_00324_delim[] = 
         "\x3a\x20";
      read_00324 = NULL;
      read_00324_len = 0;
      int read_00324_res = cgc_delimited_read(0, &read_00324, &read_00324_len, read_00324_delim, 2);
      if (read_00324_res) {} //silence unused variable warning
      cgc_free(read_00324);
      if (read_00324_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00317_00000[] = 
         "\x31\x31\x34\x0a";
      static unsigned int write_00317_00000_len = 4;
      unsigned char *write_00317 = NULL;
      unsigned int write_00317_len = 0;
      write_00317 = cgc_append_buf(write_00317, &write_00317_len, write_00317_00000, write_00317_00000_len);
      if (write_00317_len > 0) {
         cgc_transmit_all(1, write_00317, write_00317_len);
      }
      cgc_free(write_00317);
   } while (0);
   do {
      unsigned char *read_00325;
      unsigned int read_00325_len;
      unsigned int read_00325_ptr = 0;
      //**** delimited read
      static unsigned char read_00325_delim[] = 
         "\x3a\x20";
      read_00325 = NULL;
      read_00325_len = 0;
      int read_00325_res = cgc_delimited_read(0, &read_00325, &read_00325_len, read_00325_delim, 2);
      if (read_00325_res) {} //silence unused variable warning
      cgc_free(read_00325);
      if (read_00325_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00318_00000[] = 
         "\x39\x31\x35\x0a";
      static unsigned int write_00318_00000_len = 4;
      unsigned char *write_00318 = NULL;
      unsigned int write_00318_len = 0;
      write_00318 = cgc_append_buf(write_00318, &write_00318_len, write_00318_00000, write_00318_00000_len);
      if (write_00318_len > 0) {
         cgc_transmit_all(1, write_00318, write_00318_len);
      }
      cgc_free(write_00318);
   } while (0);
   do {
      unsigned char *read_00326;
      unsigned int read_00326_len;
      unsigned int read_00326_ptr = 0;
      //**** delimited read
      static unsigned char read_00326_delim[] = 
         "\x3a\x20";
      read_00326 = NULL;
      read_00326_len = 0;
      int read_00326_res = cgc_delimited_read(0, &read_00326, &read_00326_len, read_00326_delim, 2);
      if (read_00326_res) {} //silence unused variable warning
      cgc_free(read_00326);
      if (read_00326_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00319_00000[] = 
         "\x37\x37\x35\x0a";
      static unsigned int write_00319_00000_len = 4;
      unsigned char *write_00319 = NULL;
      unsigned int write_00319_len = 0;
      write_00319 = cgc_append_buf(write_00319, &write_00319_len, write_00319_00000, write_00319_00000_len);
      if (write_00319_len > 0) {
         cgc_transmit_all(1, write_00319, write_00319_len);
      }
      cgc_free(write_00319);
   } while (0);
   do {
      unsigned char *read_00327;
      unsigned int read_00327_len;
      unsigned int read_00327_ptr = 0;
      //**** delimited read
      static unsigned char read_00327_delim[] = 
         "\x3a\x20";
      read_00327 = NULL;
      read_00327_len = 0;
      int read_00327_res = cgc_delimited_read(0, &read_00327, &read_00327_len, read_00327_delim, 2);
      if (read_00327_res) {} //silence unused variable warning
      cgc_free(read_00327);
      if (read_00327_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00320_00000[] = 
         "\x34\x30\x39\x0a";
      static unsigned int write_00320_00000_len = 4;
      unsigned char *write_00320 = NULL;
      unsigned int write_00320_len = 0;
      write_00320 = cgc_append_buf(write_00320, &write_00320_len, write_00320_00000, write_00320_00000_len);
      if (write_00320_len > 0) {
         cgc_transmit_all(1, write_00320, write_00320_len);
      }
      cgc_free(write_00320);
   } while (0);
   do {
      unsigned char *read_00328;
      unsigned int read_00328_len;
      unsigned int read_00328_ptr = 0;
      //**** delimited read
      static unsigned char read_00328_delim[] = 
         "\x3a\x20";
      read_00328 = NULL;
      read_00328_len = 0;
      int read_00328_res = cgc_delimited_read(0, &read_00328, &read_00328_len, read_00328_delim, 2);
      if (read_00328_res) {} //silence unused variable warning
      cgc_free(read_00328);
      if (read_00328_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00321_00000[] = 
         "\x33\x35\x39\x0a";
      static unsigned int write_00321_00000_len = 4;
      unsigned char *write_00321 = NULL;
      unsigned int write_00321_len = 0;
      write_00321 = cgc_append_buf(write_00321, &write_00321_len, write_00321_00000, write_00321_00000_len);
      if (write_00321_len > 0) {
         cgc_transmit_all(1, write_00321, write_00321_len);
      }
      cgc_free(write_00321);
   } while (0);
   do {
      unsigned char *read_00329;
      unsigned int read_00329_len;
      unsigned int read_00329_ptr = 0;
      //**** delimited read
      static unsigned char read_00329_delim[] = 
         "\x3a\x20";
      read_00329 = NULL;
      read_00329_len = 0;
      int read_00329_res = cgc_delimited_read(0, &read_00329, &read_00329_len, read_00329_delim, 2);
      if (read_00329_res) {} //silence unused variable warning
      cgc_free(read_00329);
      if (read_00329_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00322_00000[] = 
         "\x37\x39\x34\x0a";
      static unsigned int write_00322_00000_len = 4;
      unsigned char *write_00322 = NULL;
      unsigned int write_00322_len = 0;
      write_00322 = cgc_append_buf(write_00322, &write_00322_len, write_00322_00000, write_00322_00000_len);
      if (write_00322_len > 0) {
         cgc_transmit_all(1, write_00322, write_00322_len);
      }
      cgc_free(write_00322);
   } while (0);
   do {
      unsigned char *read_00330;
      unsigned int read_00330_len;
      unsigned int read_00330_ptr = 0;
      //**** delimited read
      static unsigned char read_00330_delim[] = 
         "\x3a\x20";
      read_00330 = NULL;
      read_00330_len = 0;
      int read_00330_res = cgc_delimited_read(0, &read_00330, &read_00330_len, read_00330_delim, 2);
      if (read_00330_res) {} //silence unused variable warning
      cgc_free(read_00330);
      if (read_00330_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00323_00000[] = 
         "\x31\x31\x34\x0a";
      static unsigned int write_00323_00000_len = 4;
      unsigned char *write_00323 = NULL;
      unsigned int write_00323_len = 0;
      write_00323 = cgc_append_buf(write_00323, &write_00323_len, write_00323_00000, write_00323_00000_len);
      if (write_00323_len > 0) {
         cgc_transmit_all(1, write_00323, write_00323_len);
      }
      cgc_free(write_00323);
   } while (0);
   do {
      unsigned char *read_00331;
      unsigned int read_00331_len;
      unsigned int read_00331_ptr = 0;
      //**** delimited read
      static unsigned char read_00331_delim[] = 
         "\x3a\x20";
      read_00331 = NULL;
      read_00331_len = 0;
      int read_00331_res = cgc_delimited_read(0, &read_00331, &read_00331_len, read_00331_delim, 2);
      if (read_00331_res) {} //silence unused variable warning
      cgc_free(read_00331);
      if (read_00331_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00324_00000[] = 
         "\x36\x33\x34\x0a";
      static unsigned int write_00324_00000_len = 4;
      unsigned char *write_00324 = NULL;
      unsigned int write_00324_len = 0;
      write_00324 = cgc_append_buf(write_00324, &write_00324_len, write_00324_00000, write_00324_00000_len);
      if (write_00324_len > 0) {
         cgc_transmit_all(1, write_00324, write_00324_len);
      }
      cgc_free(write_00324);
   } while (0);
   do {
      unsigned char *read_00332;
      unsigned int read_00332_len;
      unsigned int read_00332_ptr = 0;
      //**** delimited read
      static unsigned char read_00332_delim[] = 
         "\x3a\x20";
      read_00332 = NULL;
      read_00332_len = 0;
      int read_00332_res = cgc_delimited_read(0, &read_00332, &read_00332_len, read_00332_delim, 2);
      if (read_00332_res) {} //silence unused variable warning
      cgc_free(read_00332);
      if (read_00332_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00325_00000[] = 
         "\x38\x31\x38\x0a";
      static unsigned int write_00325_00000_len = 4;
      unsigned char *write_00325 = NULL;
      unsigned int write_00325_len = 0;
      write_00325 = cgc_append_buf(write_00325, &write_00325_len, write_00325_00000, write_00325_00000_len);
      if (write_00325_len > 0) {
         cgc_transmit_all(1, write_00325, write_00325_len);
      }
      cgc_free(write_00325);
   } while (0);
   do {
      unsigned char *read_00333;
      unsigned int read_00333_len;
      unsigned int read_00333_ptr = 0;
      //**** delimited read
      static unsigned char read_00333_delim[] = 
         "\x3a\x20";
      read_00333 = NULL;
      read_00333_len = 0;
      int read_00333_res = cgc_delimited_read(0, &read_00333, &read_00333_len, read_00333_delim, 2);
      if (read_00333_res) {} //silence unused variable warning
      cgc_free(read_00333);
      if (read_00333_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00326_00000[] = 
         "\x34\x39\x37\x0a";
      static unsigned int write_00326_00000_len = 4;
      unsigned char *write_00326 = NULL;
      unsigned int write_00326_len = 0;
      write_00326 = cgc_append_buf(write_00326, &write_00326_len, write_00326_00000, write_00326_00000_len);
      if (write_00326_len > 0) {
         cgc_transmit_all(1, write_00326, write_00326_len);
      }
      cgc_free(write_00326);
   } while (0);
   do {
      unsigned char *read_00334;
      unsigned int read_00334_len;
      unsigned int read_00334_ptr = 0;
      //**** delimited read
      static unsigned char read_00334_delim[] = 
         "\x3a\x20";
      read_00334 = NULL;
      read_00334_len = 0;
      int read_00334_res = cgc_delimited_read(0, &read_00334, &read_00334_len, read_00334_delim, 2);
      if (read_00334_res) {} //silence unused variable warning
      cgc_free(read_00334);
      if (read_00334_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00327_00000[] = 
         "\x34\x38\x37\x0a";
      static unsigned int write_00327_00000_len = 4;
      unsigned char *write_00327 = NULL;
      unsigned int write_00327_len = 0;
      write_00327 = cgc_append_buf(write_00327, &write_00327_len, write_00327_00000, write_00327_00000_len);
      if (write_00327_len > 0) {
         cgc_transmit_all(1, write_00327, write_00327_len);
      }
      cgc_free(write_00327);
   } while (0);
   do {
      unsigned char *read_00335;
      unsigned int read_00335_len;
      unsigned int read_00335_ptr = 0;
      //**** delimited read
      static unsigned char read_00335_delim[] = 
         "\x3a\x20";
      read_00335 = NULL;
      read_00335_len = 0;
      int read_00335_res = cgc_delimited_read(0, &read_00335, &read_00335_len, read_00335_delim, 2);
      if (read_00335_res) {} //silence unused variable warning
      cgc_free(read_00335);
      if (read_00335_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00328_00000[] = 
         "\x38\x37\x0a";
      static unsigned int write_00328_00000_len = 3;
      unsigned char *write_00328 = NULL;
      unsigned int write_00328_len = 0;
      write_00328 = cgc_append_buf(write_00328, &write_00328_len, write_00328_00000, write_00328_00000_len);
      if (write_00328_len > 0) {
         cgc_transmit_all(1, write_00328, write_00328_len);
      }
      cgc_free(write_00328);
   } while (0);
   do {
      unsigned char *read_00336;
      unsigned int read_00336_len;
      unsigned int read_00336_ptr = 0;
      //**** delimited read
      static unsigned char read_00336_delim[] = 
         "\x3a\x20";
      read_00336 = NULL;
      read_00336_len = 0;
      int read_00336_res = cgc_delimited_read(0, &read_00336, &read_00336_len, read_00336_delim, 2);
      if (read_00336_res) {} //silence unused variable warning
      cgc_free(read_00336);
      if (read_00336_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00329_00000[] = 
         "\x35\x31\x0a";
      static unsigned int write_00329_00000_len = 3;
      unsigned char *write_00329 = NULL;
      unsigned int write_00329_len = 0;
      write_00329 = cgc_append_buf(write_00329, &write_00329_len, write_00329_00000, write_00329_00000_len);
      if (write_00329_len > 0) {
         cgc_transmit_all(1, write_00329, write_00329_len);
      }
      cgc_free(write_00329);
   } while (0);
   do {
      unsigned char *read_00337;
      unsigned int read_00337_len;
      unsigned int read_00337_ptr = 0;
      //**** delimited read
      static unsigned char read_00337_delim[] = 
         "\x3a\x20";
      read_00337 = NULL;
      read_00337_len = 0;
      int read_00337_res = cgc_delimited_read(0, &read_00337, &read_00337_len, read_00337_delim, 2);
      if (read_00337_res) {} //silence unused variable warning
      cgc_free(read_00337);
      if (read_00337_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00330_00000[] = 
         "\x32\x35\x38\x0a";
      static unsigned int write_00330_00000_len = 4;
      unsigned char *write_00330 = NULL;
      unsigned int write_00330_len = 0;
      write_00330 = cgc_append_buf(write_00330, &write_00330_len, write_00330_00000, write_00330_00000_len);
      if (write_00330_len > 0) {
         cgc_transmit_all(1, write_00330, write_00330_len);
      }
      cgc_free(write_00330);
   } while (0);
   do {
      unsigned char *read_00338;
      unsigned int read_00338_len;
      unsigned int read_00338_ptr = 0;
      //**** delimited read
      static unsigned char read_00338_delim[] = 
         "\x3a\x20";
      read_00338 = NULL;
      read_00338_len = 0;
      int read_00338_res = cgc_delimited_read(0, &read_00338, &read_00338_len, read_00338_delim, 2);
      if (read_00338_res) {} //silence unused variable warning
      cgc_free(read_00338);
      if (read_00338_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00331_00000[] = 
         "\x34\x35\x35\x0a";
      static unsigned int write_00331_00000_len = 4;
      unsigned char *write_00331 = NULL;
      unsigned int write_00331_len = 0;
      write_00331 = cgc_append_buf(write_00331, &write_00331_len, write_00331_00000, write_00331_00000_len);
      if (write_00331_len > 0) {
         cgc_transmit_all(1, write_00331, write_00331_len);
      }
      cgc_free(write_00331);
   } while (0);
   do {
      unsigned char *read_00339;
      unsigned int read_00339_len;
      unsigned int read_00339_ptr = 0;
      //**** delimited read
      static unsigned char read_00339_delim[] = 
         "\x3a\x20";
      read_00339 = NULL;
      read_00339_len = 0;
      int read_00339_res = cgc_delimited_read(0, &read_00339, &read_00339_len, read_00339_delim, 2);
      if (read_00339_res) {} //silence unused variable warning
      cgc_free(read_00339);
      if (read_00339_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00332_00000[] = 
         "\x35\x33\x34\x0a";
      static unsigned int write_00332_00000_len = 4;
      unsigned char *write_00332 = NULL;
      unsigned int write_00332_len = 0;
      write_00332 = cgc_append_buf(write_00332, &write_00332_len, write_00332_00000, write_00332_00000_len);
      if (write_00332_len > 0) {
         cgc_transmit_all(1, write_00332, write_00332_len);
      }
      cgc_free(write_00332);
   } while (0);
   do {
      unsigned char *read_00340;
      unsigned int read_00340_len;
      unsigned int read_00340_ptr = 0;
      //**** delimited read
      static unsigned char read_00340_delim[] = 
         "\x3a\x20";
      read_00340 = NULL;
      read_00340_len = 0;
      int read_00340_res = cgc_delimited_read(0, &read_00340, &read_00340_len, read_00340_delim, 2);
      if (read_00340_res) {} //silence unused variable warning
      cgc_free(read_00340);
      if (read_00340_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00333_00000[] = 
         "\x34\x32\x0a";
      static unsigned int write_00333_00000_len = 3;
      unsigned char *write_00333 = NULL;
      unsigned int write_00333_len = 0;
      write_00333 = cgc_append_buf(write_00333, &write_00333_len, write_00333_00000, write_00333_00000_len);
      if (write_00333_len > 0) {
         cgc_transmit_all(1, write_00333, write_00333_len);
      }
      cgc_free(write_00333);
   } while (0);
   do {
      unsigned char *read_00341;
      unsigned int read_00341_len;
      unsigned int read_00341_ptr = 0;
      //**** delimited read
      static unsigned char read_00341_delim[] = 
         "\x3a\x20";
      read_00341 = NULL;
      read_00341_len = 0;
      int read_00341_res = cgc_delimited_read(0, &read_00341, &read_00341_len, read_00341_delim, 2);
      if (read_00341_res) {} //silence unused variable warning
      cgc_free(read_00341);
      if (read_00341_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00334_00000[] = 
         "\x37\x34\x36\x0a";
      static unsigned int write_00334_00000_len = 4;
      unsigned char *write_00334 = NULL;
      unsigned int write_00334_len = 0;
      write_00334 = cgc_append_buf(write_00334, &write_00334_len, write_00334_00000, write_00334_00000_len);
      if (write_00334_len > 0) {
         cgc_transmit_all(1, write_00334, write_00334_len);
      }
      cgc_free(write_00334);
   } while (0);
   do {
      unsigned char *read_00342;
      unsigned int read_00342_len;
      unsigned int read_00342_ptr = 0;
      //**** delimited read
      static unsigned char read_00342_delim[] = 
         "\x3a\x20";
      read_00342 = NULL;
      read_00342_len = 0;
      int read_00342_res = cgc_delimited_read(0, &read_00342, &read_00342_len, read_00342_delim, 2);
      if (read_00342_res) {} //silence unused variable warning
      cgc_free(read_00342);
      if (read_00342_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00335_00000[] = 
         "\x36\x35\x32\x0a";
      static unsigned int write_00335_00000_len = 4;
      unsigned char *write_00335 = NULL;
      unsigned int write_00335_len = 0;
      write_00335 = cgc_append_buf(write_00335, &write_00335_len, write_00335_00000, write_00335_00000_len);
      if (write_00335_len > 0) {
         cgc_transmit_all(1, write_00335, write_00335_len);
      }
      cgc_free(write_00335);
   } while (0);
   do {
      unsigned char *read_00343;
      unsigned int read_00343_len;
      unsigned int read_00343_ptr = 0;
      //**** delimited read
      static unsigned char read_00343_delim[] = 
         "\x3a\x20";
      read_00343 = NULL;
      read_00343_len = 0;
      int read_00343_res = cgc_delimited_read(0, &read_00343, &read_00343_len, read_00343_delim, 2);
      if (read_00343_res) {} //silence unused variable warning
      cgc_free(read_00343);
      if (read_00343_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00336_00000[] = 
         "\x31\x31\x39\x0a";
      static unsigned int write_00336_00000_len = 4;
      unsigned char *write_00336 = NULL;
      unsigned int write_00336_len = 0;
      write_00336 = cgc_append_buf(write_00336, &write_00336_len, write_00336_00000, write_00336_00000_len);
      if (write_00336_len > 0) {
         cgc_transmit_all(1, write_00336, write_00336_len);
      }
      cgc_free(write_00336);
   } while (0);
   do {
      unsigned char *read_00344;
      unsigned int read_00344_len;
      unsigned int read_00344_ptr = 0;
      //**** delimited read
      static unsigned char read_00344_delim[] = 
         "\x3a\x20";
      read_00344 = NULL;
      read_00344_len = 0;
      int read_00344_res = cgc_delimited_read(0, &read_00344, &read_00344_len, read_00344_delim, 2);
      if (read_00344_res) {} //silence unused variable warning
      cgc_free(read_00344);
      if (read_00344_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00337_00000[] = 
         "\x34\x31\x37\x0a";
      static unsigned int write_00337_00000_len = 4;
      unsigned char *write_00337 = NULL;
      unsigned int write_00337_len = 0;
      write_00337 = cgc_append_buf(write_00337, &write_00337_len, write_00337_00000, write_00337_00000_len);
      if (write_00337_len > 0) {
         cgc_transmit_all(1, write_00337, write_00337_len);
      }
      cgc_free(write_00337);
   } while (0);
   do {
      unsigned char *read_00345;
      unsigned int read_00345_len;
      unsigned int read_00345_ptr = 0;
      //**** delimited read
      static unsigned char read_00345_delim[] = 
         "\x3a\x20";
      read_00345 = NULL;
      read_00345_len = 0;
      int read_00345_res = cgc_delimited_read(0, &read_00345, &read_00345_len, read_00345_delim, 2);
      if (read_00345_res) {} //silence unused variable warning
      cgc_free(read_00345);
      if (read_00345_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00338_00000[] = 
         "\x38\x30\x31\x0a";
      static unsigned int write_00338_00000_len = 4;
      unsigned char *write_00338 = NULL;
      unsigned int write_00338_len = 0;
      write_00338 = cgc_append_buf(write_00338, &write_00338_len, write_00338_00000, write_00338_00000_len);
      if (write_00338_len > 0) {
         cgc_transmit_all(1, write_00338, write_00338_len);
      }
      cgc_free(write_00338);
   } while (0);
   do {
      unsigned char *read_00346;
      unsigned int read_00346_len;
      unsigned int read_00346_ptr = 0;
      //**** delimited read
      static unsigned char read_00346_delim[] = 
         "\x3a\x20";
      read_00346 = NULL;
      read_00346_len = 0;
      int read_00346_res = cgc_delimited_read(0, &read_00346, &read_00346_len, read_00346_delim, 2);
      if (read_00346_res) {} //silence unused variable warning
      cgc_free(read_00346);
      if (read_00346_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00339_00000[] = 
         "\x36\x37\x0a";
      static unsigned int write_00339_00000_len = 3;
      unsigned char *write_00339 = NULL;
      unsigned int write_00339_len = 0;
      write_00339 = cgc_append_buf(write_00339, &write_00339_len, write_00339_00000, write_00339_00000_len);
      if (write_00339_len > 0) {
         cgc_transmit_all(1, write_00339, write_00339_len);
      }
      cgc_free(write_00339);
   } while (0);
   do {
      unsigned char *read_00347;
      unsigned int read_00347_len;
      unsigned int read_00347_ptr = 0;
      //**** delimited read
      static unsigned char read_00347_delim[] = 
         "\x3a\x20";
      read_00347 = NULL;
      read_00347_len = 0;
      int read_00347_res = cgc_delimited_read(0, &read_00347, &read_00347_len, read_00347_delim, 2);
      if (read_00347_res) {} //silence unused variable warning
      cgc_free(read_00347);
      if (read_00347_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00340_00000[] = 
         "\x34\x34\x34\x0a";
      static unsigned int write_00340_00000_len = 4;
      unsigned char *write_00340 = NULL;
      unsigned int write_00340_len = 0;
      write_00340 = cgc_append_buf(write_00340, &write_00340_len, write_00340_00000, write_00340_00000_len);
      if (write_00340_len > 0) {
         cgc_transmit_all(1, write_00340, write_00340_len);
      }
      cgc_free(write_00340);
   } while (0);
   do {
      unsigned char *read_00348;
      unsigned int read_00348_len;
      unsigned int read_00348_ptr = 0;
      //**** delimited read
      static unsigned char read_00348_delim[] = 
         "\x3a\x20";
      read_00348 = NULL;
      read_00348_len = 0;
      int read_00348_res = cgc_delimited_read(0, &read_00348, &read_00348_len, read_00348_delim, 2);
      if (read_00348_res) {} //silence unused variable warning
      cgc_free(read_00348);
      if (read_00348_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00341_00000[] = 
         "\x34\x32\x33\x0a";
      static unsigned int write_00341_00000_len = 4;
      unsigned char *write_00341 = NULL;
      unsigned int write_00341_len = 0;
      write_00341 = cgc_append_buf(write_00341, &write_00341_len, write_00341_00000, write_00341_00000_len);
      if (write_00341_len > 0) {
         cgc_transmit_all(1, write_00341, write_00341_len);
      }
      cgc_free(write_00341);
   } while (0);
   do {
      unsigned char *read_00349;
      unsigned int read_00349_len;
      unsigned int read_00349_ptr = 0;
      //**** delimited read
      static unsigned char read_00349_delim[] = 
         "\x3a\x20";
      read_00349 = NULL;
      read_00349_len = 0;
      int read_00349_res = cgc_delimited_read(0, &read_00349, &read_00349_len, read_00349_delim, 2);
      if (read_00349_res) {} //silence unused variable warning
      cgc_free(read_00349);
      if (read_00349_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00342_00000[] = 
         "\x35\x31\x0a";
      static unsigned int write_00342_00000_len = 3;
      unsigned char *write_00342 = NULL;
      unsigned int write_00342_len = 0;
      write_00342 = cgc_append_buf(write_00342, &write_00342_len, write_00342_00000, write_00342_00000_len);
      if (write_00342_len > 0) {
         cgc_transmit_all(1, write_00342, write_00342_len);
      }
      cgc_free(write_00342);
   } while (0);
   do {
      unsigned char *read_00350;
      unsigned int read_00350_len;
      unsigned int read_00350_ptr = 0;
      //**** delimited read
      static unsigned char read_00350_delim[] = 
         "\x3a\x20";
      read_00350 = NULL;
      read_00350_len = 0;
      int read_00350_res = cgc_delimited_read(0, &read_00350, &read_00350_len, read_00350_delim, 2);
      if (read_00350_res) {} //silence unused variable warning
      cgc_free(read_00350);
      if (read_00350_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00343_00000[] = 
         "\x36\x37\x36\x0a";
      static unsigned int write_00343_00000_len = 4;
      unsigned char *write_00343 = NULL;
      unsigned int write_00343_len = 0;
      write_00343 = cgc_append_buf(write_00343, &write_00343_len, write_00343_00000, write_00343_00000_len);
      if (write_00343_len > 0) {
         cgc_transmit_all(1, write_00343, write_00343_len);
      }
      cgc_free(write_00343);
   } while (0);
   do {
      unsigned char *read_00351;
      unsigned int read_00351_len;
      unsigned int read_00351_ptr = 0;
      //**** delimited read
      static unsigned char read_00351_delim[] = 
         "\x3a\x20";
      read_00351 = NULL;
      read_00351_len = 0;
      int read_00351_res = cgc_delimited_read(0, &read_00351, &read_00351_len, read_00351_delim, 2);
      if (read_00351_res) {} //silence unused variable warning
      cgc_free(read_00351);
      if (read_00351_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00344_00000[] = 
         "\x33\x36\x31\x0a";
      static unsigned int write_00344_00000_len = 4;
      unsigned char *write_00344 = NULL;
      unsigned int write_00344_len = 0;
      write_00344 = cgc_append_buf(write_00344, &write_00344_len, write_00344_00000, write_00344_00000_len);
      if (write_00344_len > 0) {
         cgc_transmit_all(1, write_00344, write_00344_len);
      }
      cgc_free(write_00344);
   } while (0);
   do {
      unsigned char *read_00352;
      unsigned int read_00352_len;
      unsigned int read_00352_ptr = 0;
      //**** delimited read
      static unsigned char read_00352_delim[] = 
         "\x3a\x20";
      read_00352 = NULL;
      read_00352_len = 0;
      int read_00352_res = cgc_delimited_read(0, &read_00352, &read_00352_len, read_00352_delim, 2);
      if (read_00352_res) {} //silence unused variable warning
      cgc_free(read_00352);
      if (read_00352_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00345_00000[] = 
         "\x34\x0a";
      static unsigned int write_00345_00000_len = 2;
      unsigned char *write_00345 = NULL;
      unsigned int write_00345_len = 0;
      write_00345 = cgc_append_buf(write_00345, &write_00345_len, write_00345_00000, write_00345_00000_len);
      if (write_00345_len > 0) {
         cgc_transmit_all(1, write_00345, write_00345_len);
      }
      cgc_free(write_00345);
   } while (0);
   do {
      unsigned char *read_00353;
      unsigned int read_00353_len;
      unsigned int read_00353_ptr = 0;
      //**** delimited read
      static unsigned char read_00353_delim[] = 
         "\x3a\x20";
      read_00353 = NULL;
      read_00353_len = 0;
      int read_00353_res = cgc_delimited_read(0, &read_00353, &read_00353_len, read_00353_delim, 2);
      if (read_00353_res) {} //silence unused variable warning
      cgc_free(read_00353);
      if (read_00353_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00346_00000[] = 
         "\x32\x31\x0a";
      static unsigned int write_00346_00000_len = 3;
      unsigned char *write_00346 = NULL;
      unsigned int write_00346_len = 0;
      write_00346 = cgc_append_buf(write_00346, &write_00346_len, write_00346_00000, write_00346_00000_len);
      if (write_00346_len > 0) {
         cgc_transmit_all(1, write_00346, write_00346_len);
      }
      cgc_free(write_00346);
   } while (0);
   do {
      unsigned char *read_00354;
      unsigned int read_00354_len;
      unsigned int read_00354_ptr = 0;
      //**** delimited read
      static unsigned char read_00354_delim[] = 
         "\x3a\x20";
      read_00354 = NULL;
      read_00354_len = 0;
      int read_00354_res = cgc_delimited_read(0, &read_00354, &read_00354_len, read_00354_delim, 2);
      if (read_00354_res) {} //silence unused variable warning
      cgc_free(read_00354);
      if (read_00354_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00347_00000[] = 
         "\x38\x39\x31\x0a";
      static unsigned int write_00347_00000_len = 4;
      unsigned char *write_00347 = NULL;
      unsigned int write_00347_len = 0;
      write_00347 = cgc_append_buf(write_00347, &write_00347_len, write_00347_00000, write_00347_00000_len);
      if (write_00347_len > 0) {
         cgc_transmit_all(1, write_00347, write_00347_len);
      }
      cgc_free(write_00347);
   } while (0);
   do {
      unsigned char *read_00355;
      unsigned int read_00355_len;
      unsigned int read_00355_ptr = 0;
      //**** delimited read
      static unsigned char read_00355_delim[] = 
         "\x3a\x20";
      read_00355 = NULL;
      read_00355_len = 0;
      int read_00355_res = cgc_delimited_read(0, &read_00355, &read_00355_len, read_00355_delim, 2);
      if (read_00355_res) {} //silence unused variable warning
      cgc_free(read_00355);
      if (read_00355_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00348_00000[] = 
         "\x32\x35\x38\x0a";
      static unsigned int write_00348_00000_len = 4;
      unsigned char *write_00348 = NULL;
      unsigned int write_00348_len = 0;
      write_00348 = cgc_append_buf(write_00348, &write_00348_len, write_00348_00000, write_00348_00000_len);
      if (write_00348_len > 0) {
         cgc_transmit_all(1, write_00348, write_00348_len);
      }
      cgc_free(write_00348);
   } while (0);
   do {
      unsigned char *read_00356;
      unsigned int read_00356_len;
      unsigned int read_00356_ptr = 0;
      //**** delimited read
      static unsigned char read_00356_delim[] = 
         "\x3a\x20";
      read_00356 = NULL;
      read_00356_len = 0;
      int read_00356_res = cgc_delimited_read(0, &read_00356, &read_00356_len, read_00356_delim, 2);
      if (read_00356_res) {} //silence unused variable warning
      cgc_free(read_00356);
      if (read_00356_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00349_00000[] = 
         "\x39\x38\x39\x0a";
      static unsigned int write_00349_00000_len = 4;
      unsigned char *write_00349 = NULL;
      unsigned int write_00349_len = 0;
      write_00349 = cgc_append_buf(write_00349, &write_00349_len, write_00349_00000, write_00349_00000_len);
      if (write_00349_len > 0) {
         cgc_transmit_all(1, write_00349, write_00349_len);
      }
      cgc_free(write_00349);
   } while (0);
   do {
      unsigned char *read_00357;
      unsigned int read_00357_len;
      unsigned int read_00357_ptr = 0;
      //**** delimited read
      static unsigned char read_00357_delim[] = 
         "\x3a\x20";
      read_00357 = NULL;
      read_00357_len = 0;
      int read_00357_res = cgc_delimited_read(0, &read_00357, &read_00357_len, read_00357_delim, 2);
      if (read_00357_res) {} //silence unused variable warning
      cgc_free(read_00357);
      if (read_00357_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00350_00000[] = 
         "\x31\x35\x33\x0a";
      static unsigned int write_00350_00000_len = 4;
      unsigned char *write_00350 = NULL;
      unsigned int write_00350_len = 0;
      write_00350 = cgc_append_buf(write_00350, &write_00350_len, write_00350_00000, write_00350_00000_len);
      if (write_00350_len > 0) {
         cgc_transmit_all(1, write_00350, write_00350_len);
      }
      cgc_free(write_00350);
   } while (0);
   do {
      unsigned char *read_00358;
      unsigned int read_00358_len;
      unsigned int read_00358_ptr = 0;
      //**** delimited read
      static unsigned char read_00358_delim[] = 
         "\x3a\x20";
      read_00358 = NULL;
      read_00358_len = 0;
      int read_00358_res = cgc_delimited_read(0, &read_00358, &read_00358_len, read_00358_delim, 2);
      if (read_00358_res) {} //silence unused variable warning
      cgc_free(read_00358);
      if (read_00358_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00351_00000[] = 
         "\x38\x36\x30\x0a";
      static unsigned int write_00351_00000_len = 4;
      unsigned char *write_00351 = NULL;
      unsigned int write_00351_len = 0;
      write_00351 = cgc_append_buf(write_00351, &write_00351_len, write_00351_00000, write_00351_00000_len);
      if (write_00351_len > 0) {
         cgc_transmit_all(1, write_00351, write_00351_len);
      }
      cgc_free(write_00351);
   } while (0);
   do {
      unsigned char *read_00359;
      unsigned int read_00359_len;
      unsigned int read_00359_ptr = 0;
      //**** delimited read
      static unsigned char read_00359_delim[] = 
         "\x3a\x20";
      read_00359 = NULL;
      read_00359_len = 0;
      int read_00359_res = cgc_delimited_read(0, &read_00359, &read_00359_len, read_00359_delim, 2);
      if (read_00359_res) {} //silence unused variable warning
      cgc_free(read_00359);
      if (read_00359_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00352_00000[] = 
         "\x37\x33\x39\x0a";
      static unsigned int write_00352_00000_len = 4;
      unsigned char *write_00352 = NULL;
      unsigned int write_00352_len = 0;
      write_00352 = cgc_append_buf(write_00352, &write_00352_len, write_00352_00000, write_00352_00000_len);
      if (write_00352_len > 0) {
         cgc_transmit_all(1, write_00352, write_00352_len);
      }
      cgc_free(write_00352);
   } while (0);
   do {
      unsigned char *read_00360;
      unsigned int read_00360_len;
      unsigned int read_00360_ptr = 0;
      //**** delimited read
      static unsigned char read_00360_delim[] = 
         "\x3a\x20";
      read_00360 = NULL;
      read_00360_len = 0;
      int read_00360_res = cgc_delimited_read(0, &read_00360, &read_00360_len, read_00360_delim, 2);
      if (read_00360_res) {} //silence unused variable warning
      cgc_free(read_00360);
      if (read_00360_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00353_00000[] = 
         "\x38\x39\x37\x0a";
      static unsigned int write_00353_00000_len = 4;
      unsigned char *write_00353 = NULL;
      unsigned int write_00353_len = 0;
      write_00353 = cgc_append_buf(write_00353, &write_00353_len, write_00353_00000, write_00353_00000_len);
      if (write_00353_len > 0) {
         cgc_transmit_all(1, write_00353, write_00353_len);
      }
      cgc_free(write_00353);
   } while (0);
   do {
      unsigned char *read_00361;
      unsigned int read_00361_len;
      unsigned int read_00361_ptr = 0;
      //**** delimited read
      static unsigned char read_00361_delim[] = 
         "\x3a\x20";
      read_00361 = NULL;
      read_00361_len = 0;
      int read_00361_res = cgc_delimited_read(0, &read_00361, &read_00361_len, read_00361_delim, 2);
      if (read_00361_res) {} //silence unused variable warning
      cgc_free(read_00361);
      if (read_00361_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00354_00000[] = 
         "\x39\x39\x34\x0a";
      static unsigned int write_00354_00000_len = 4;
      unsigned char *write_00354 = NULL;
      unsigned int write_00354_len = 0;
      write_00354 = cgc_append_buf(write_00354, &write_00354_len, write_00354_00000, write_00354_00000_len);
      if (write_00354_len > 0) {
         cgc_transmit_all(1, write_00354, write_00354_len);
      }
      cgc_free(write_00354);
   } while (0);
   do {
      unsigned char *read_00362;
      unsigned int read_00362_len;
      unsigned int read_00362_ptr = 0;
      //**** delimited read
      static unsigned char read_00362_delim[] = 
         "\x3a\x20";
      read_00362 = NULL;
      read_00362_len = 0;
      int read_00362_res = cgc_delimited_read(0, &read_00362, &read_00362_len, read_00362_delim, 2);
      if (read_00362_res) {} //silence unused variable warning
      cgc_free(read_00362);
      if (read_00362_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00355_00000[] = 
         "\x37\x37\x38\x0a";
      static unsigned int write_00355_00000_len = 4;
      unsigned char *write_00355 = NULL;
      unsigned int write_00355_len = 0;
      write_00355 = cgc_append_buf(write_00355, &write_00355_len, write_00355_00000, write_00355_00000_len);
      if (write_00355_len > 0) {
         cgc_transmit_all(1, write_00355, write_00355_len);
      }
      cgc_free(write_00355);
   } while (0);
   do {
      unsigned char *read_00363;
      unsigned int read_00363_len;
      unsigned int read_00363_ptr = 0;
      //**** delimited read
      static unsigned char read_00363_delim[] = 
         "\x3a\x20";
      read_00363 = NULL;
      read_00363_len = 0;
      int read_00363_res = cgc_delimited_read(0, &read_00363, &read_00363_len, read_00363_delim, 2);
      if (read_00363_res) {} //silence unused variable warning
      cgc_free(read_00363);
      if (read_00363_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00356_00000[] = 
         "\x32\x39\x33\x0a";
      static unsigned int write_00356_00000_len = 4;
      unsigned char *write_00356 = NULL;
      unsigned int write_00356_len = 0;
      write_00356 = cgc_append_buf(write_00356, &write_00356_len, write_00356_00000, write_00356_00000_len);
      if (write_00356_len > 0) {
         cgc_transmit_all(1, write_00356, write_00356_len);
      }
      cgc_free(write_00356);
   } while (0);
   do {
      unsigned char *read_00364;
      unsigned int read_00364_len;
      unsigned int read_00364_ptr = 0;
      //**** delimited read
      static unsigned char read_00364_delim[] = 
         "\x3a\x20";
      read_00364 = NULL;
      read_00364_len = 0;
      int read_00364_res = cgc_delimited_read(0, &read_00364, &read_00364_len, read_00364_delim, 2);
      if (read_00364_res) {} //silence unused variable warning
      cgc_free(read_00364);
      if (read_00364_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00357_00000[] = 
         "\x37\x38\x30\x0a";
      static unsigned int write_00357_00000_len = 4;
      unsigned char *write_00357 = NULL;
      unsigned int write_00357_len = 0;
      write_00357 = cgc_append_buf(write_00357, &write_00357_len, write_00357_00000, write_00357_00000_len);
      if (write_00357_len > 0) {
         cgc_transmit_all(1, write_00357, write_00357_len);
      }
      cgc_free(write_00357);
   } while (0);
   do {
      unsigned char *read_00365;
      unsigned int read_00365_len;
      unsigned int read_00365_ptr = 0;
      //**** delimited read
      static unsigned char read_00365_delim[] = 
         "\x3a\x20";
      read_00365 = NULL;
      read_00365_len = 0;
      int read_00365_res = cgc_delimited_read(0, &read_00365, &read_00365_len, read_00365_delim, 2);
      if (read_00365_res) {} //silence unused variable warning
      cgc_free(read_00365);
      if (read_00365_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00358_00000[] = 
         "\x36\x34\x36\x0a";
      static unsigned int write_00358_00000_len = 4;
      unsigned char *write_00358 = NULL;
      unsigned int write_00358_len = 0;
      write_00358 = cgc_append_buf(write_00358, &write_00358_len, write_00358_00000, write_00358_00000_len);
      if (write_00358_len > 0) {
         cgc_transmit_all(1, write_00358, write_00358_len);
      }
      cgc_free(write_00358);
   } while (0);
   do {
      unsigned char *read_00366;
      unsigned int read_00366_len;
      unsigned int read_00366_ptr = 0;
      //**** delimited read
      static unsigned char read_00366_delim[] = 
         "\x3a\x20";
      read_00366 = NULL;
      read_00366_len = 0;
      int read_00366_res = cgc_delimited_read(0, &read_00366, &read_00366_len, read_00366_delim, 2);
      if (read_00366_res) {} //silence unused variable warning
      cgc_free(read_00366);
      if (read_00366_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00359_00000[] = 
         "\x38\x30\x37\x0a";
      static unsigned int write_00359_00000_len = 4;
      unsigned char *write_00359 = NULL;
      unsigned int write_00359_len = 0;
      write_00359 = cgc_append_buf(write_00359, &write_00359_len, write_00359_00000, write_00359_00000_len);
      if (write_00359_len > 0) {
         cgc_transmit_all(1, write_00359, write_00359_len);
      }
      cgc_free(write_00359);
   } while (0);
   do {
      unsigned char *read_00367;
      unsigned int read_00367_len;
      unsigned int read_00367_ptr = 0;
      //**** delimited read
      static unsigned char read_00367_delim[] = 
         "\x3a\x20";
      read_00367 = NULL;
      read_00367_len = 0;
      int read_00367_res = cgc_delimited_read(0, &read_00367, &read_00367_len, read_00367_delim, 2);
      if (read_00367_res) {} //silence unused variable warning
      cgc_free(read_00367);
      if (read_00367_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00360_00000[] = 
         "\x36\x37\x34\x0a";
      static unsigned int write_00360_00000_len = 4;
      unsigned char *write_00360 = NULL;
      unsigned int write_00360_len = 0;
      write_00360 = cgc_append_buf(write_00360, &write_00360_len, write_00360_00000, write_00360_00000_len);
      if (write_00360_len > 0) {
         cgc_transmit_all(1, write_00360, write_00360_len);
      }
      cgc_free(write_00360);
   } while (0);
   do {
      unsigned char *read_00368;
      unsigned int read_00368_len;
      unsigned int read_00368_ptr = 0;
      //**** delimited read
      static unsigned char read_00368_delim[] = 
         "\x3a\x20";
      read_00368 = NULL;
      read_00368_len = 0;
      int read_00368_res = cgc_delimited_read(0, &read_00368, &read_00368_len, read_00368_delim, 2);
      if (read_00368_res) {} //silence unused variable warning
      cgc_free(read_00368);
      if (read_00368_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00361_00000[] = 
         "\x36\x39\x33\x0a";
      static unsigned int write_00361_00000_len = 4;
      unsigned char *write_00361 = NULL;
      unsigned int write_00361_len = 0;
      write_00361 = cgc_append_buf(write_00361, &write_00361_len, write_00361_00000, write_00361_00000_len);
      if (write_00361_len > 0) {
         cgc_transmit_all(1, write_00361, write_00361_len);
      }
      cgc_free(write_00361);
   } while (0);
   do {
      unsigned char *read_00369;
      unsigned int read_00369_len;
      unsigned int read_00369_ptr = 0;
      //**** delimited read
      static unsigned char read_00369_delim[] = 
         "\x3a\x20";
      read_00369 = NULL;
      read_00369_len = 0;
      int read_00369_res = cgc_delimited_read(0, &read_00369, &read_00369_len, read_00369_delim, 2);
      if (read_00369_res) {} //silence unused variable warning
      cgc_free(read_00369);
      if (read_00369_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00362_00000[] = 
         "\x32\x30\x37\x0a";
      static unsigned int write_00362_00000_len = 4;
      unsigned char *write_00362 = NULL;
      unsigned int write_00362_len = 0;
      write_00362 = cgc_append_buf(write_00362, &write_00362_len, write_00362_00000, write_00362_00000_len);
      if (write_00362_len > 0) {
         cgc_transmit_all(1, write_00362, write_00362_len);
      }
      cgc_free(write_00362);
   } while (0);
   do {
      unsigned char *read_00370;
      unsigned int read_00370_len;
      unsigned int read_00370_ptr = 0;
      //**** delimited read
      static unsigned char read_00370_delim[] = 
         "\x3a\x20";
      read_00370 = NULL;
      read_00370_len = 0;
      int read_00370_res = cgc_delimited_read(0, &read_00370, &read_00370_len, read_00370_delim, 2);
      if (read_00370_res) {} //silence unused variable warning
      cgc_free(read_00370);
      if (read_00370_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00363_00000[] = 
         "\x32\x33\x36\x0a";
      static unsigned int write_00363_00000_len = 4;
      unsigned char *write_00363 = NULL;
      unsigned int write_00363_len = 0;
      write_00363 = cgc_append_buf(write_00363, &write_00363_len, write_00363_00000, write_00363_00000_len);
      if (write_00363_len > 0) {
         cgc_transmit_all(1, write_00363, write_00363_len);
      }
      cgc_free(write_00363);
   } while (0);
   do {
      unsigned char *read_00371;
      unsigned int read_00371_len;
      unsigned int read_00371_ptr = 0;
      //**** delimited read
      static unsigned char read_00371_delim[] = 
         "\x3a\x20";
      read_00371 = NULL;
      read_00371_len = 0;
      int read_00371_res = cgc_delimited_read(0, &read_00371, &read_00371_len, read_00371_delim, 2);
      if (read_00371_res) {} //silence unused variable warning
      cgc_free(read_00371);
      if (read_00371_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00364_00000[] = 
         "\x34\x32\x34\x0a";
      static unsigned int write_00364_00000_len = 4;
      unsigned char *write_00364 = NULL;
      unsigned int write_00364_len = 0;
      write_00364 = cgc_append_buf(write_00364, &write_00364_len, write_00364_00000, write_00364_00000_len);
      if (write_00364_len > 0) {
         cgc_transmit_all(1, write_00364, write_00364_len);
      }
      cgc_free(write_00364);
   } while (0);
   do {
      unsigned char *read_00372;
      unsigned int read_00372_len;
      unsigned int read_00372_ptr = 0;
      //**** delimited read
      static unsigned char read_00372_delim[] = 
         "\x3a\x20";
      read_00372 = NULL;
      read_00372_len = 0;
      int read_00372_res = cgc_delimited_read(0, &read_00372, &read_00372_len, read_00372_delim, 2);
      if (read_00372_res) {} //silence unused variable warning
      cgc_free(read_00372);
      if (read_00372_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00365_00000[] = 
         "\x35\x38\x34\x0a";
      static unsigned int write_00365_00000_len = 4;
      unsigned char *write_00365 = NULL;
      unsigned int write_00365_len = 0;
      write_00365 = cgc_append_buf(write_00365, &write_00365_len, write_00365_00000, write_00365_00000_len);
      if (write_00365_len > 0) {
         cgc_transmit_all(1, write_00365, write_00365_len);
      }
      cgc_free(write_00365);
   } while (0);
   do {
      unsigned char *read_00373;
      unsigned int read_00373_len;
      unsigned int read_00373_ptr = 0;
      //**** delimited read
      static unsigned char read_00373_delim[] = 
         "\x3a\x20";
      read_00373 = NULL;
      read_00373_len = 0;
      int read_00373_res = cgc_delimited_read(0, &read_00373, &read_00373_len, read_00373_delim, 2);
      if (read_00373_res) {} //silence unused variable warning
      cgc_free(read_00373);
      if (read_00373_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00366_00000[] = 
         "\x33\x32\x37\x0a";
      static unsigned int write_00366_00000_len = 4;
      unsigned char *write_00366 = NULL;
      unsigned int write_00366_len = 0;
      write_00366 = cgc_append_buf(write_00366, &write_00366_len, write_00366_00000, write_00366_00000_len);
      if (write_00366_len > 0) {
         cgc_transmit_all(1, write_00366, write_00366_len);
      }
      cgc_free(write_00366);
   } while (0);
   do {
      unsigned char *read_00374;
      unsigned int read_00374_len;
      unsigned int read_00374_ptr = 0;
      //**** delimited read
      static unsigned char read_00374_delim[] = 
         "\x3a\x20";
      read_00374 = NULL;
      read_00374_len = 0;
      int read_00374_res = cgc_delimited_read(0, &read_00374, &read_00374_len, read_00374_delim, 2);
      if (read_00374_res) {} //silence unused variable warning
      cgc_free(read_00374);
      if (read_00374_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00367_00000[] = 
         "\x37\x33\x34\x0a";
      static unsigned int write_00367_00000_len = 4;
      unsigned char *write_00367 = NULL;
      unsigned int write_00367_len = 0;
      write_00367 = cgc_append_buf(write_00367, &write_00367_len, write_00367_00000, write_00367_00000_len);
      if (write_00367_len > 0) {
         cgc_transmit_all(1, write_00367, write_00367_len);
      }
      cgc_free(write_00367);
   } while (0);
   do {
      unsigned char *read_00375;
      unsigned int read_00375_len;
      unsigned int read_00375_ptr = 0;
      //**** delimited read
      static unsigned char read_00375_delim[] = 
         "\x3a\x20";
      read_00375 = NULL;
      read_00375_len = 0;
      int read_00375_res = cgc_delimited_read(0, &read_00375, &read_00375_len, read_00375_delim, 2);
      if (read_00375_res) {} //silence unused variable warning
      cgc_free(read_00375);
      if (read_00375_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00368_00000[] = 
         "\x31\x30\x35\x0a";
      static unsigned int write_00368_00000_len = 4;
      unsigned char *write_00368 = NULL;
      unsigned int write_00368_len = 0;
      write_00368 = cgc_append_buf(write_00368, &write_00368_len, write_00368_00000, write_00368_00000_len);
      if (write_00368_len > 0) {
         cgc_transmit_all(1, write_00368, write_00368_len);
      }
      cgc_free(write_00368);
   } while (0);
   do {
      unsigned char *read_00376;
      unsigned int read_00376_len;
      unsigned int read_00376_ptr = 0;
      //**** delimited read
      static unsigned char read_00376_delim[] = 
         "\x3a\x20";
      read_00376 = NULL;
      read_00376_len = 0;
      int read_00376_res = cgc_delimited_read(0, &read_00376, &read_00376_len, read_00376_delim, 2);
      if (read_00376_res) {} //silence unused variable warning
      cgc_free(read_00376);
      if (read_00376_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00369_00000[] = 
         "\x37\x34\x35\x0a";
      static unsigned int write_00369_00000_len = 4;
      unsigned char *write_00369 = NULL;
      unsigned int write_00369_len = 0;
      write_00369 = cgc_append_buf(write_00369, &write_00369_len, write_00369_00000, write_00369_00000_len);
      if (write_00369_len > 0) {
         cgc_transmit_all(1, write_00369, write_00369_len);
      }
      cgc_free(write_00369);
   } while (0);
   do {
      unsigned char *read_00377;
      unsigned int read_00377_len;
      unsigned int read_00377_ptr = 0;
      //**** delimited read
      static unsigned char read_00377_delim[] = 
         "\x3a\x20";
      read_00377 = NULL;
      read_00377_len = 0;
      int read_00377_res = cgc_delimited_read(0, &read_00377, &read_00377_len, read_00377_delim, 2);
      if (read_00377_res) {} //silence unused variable warning
      cgc_free(read_00377);
      if (read_00377_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00370_00000[] = 
         "\x38\x30\x32\x0a";
      static unsigned int write_00370_00000_len = 4;
      unsigned char *write_00370 = NULL;
      unsigned int write_00370_len = 0;
      write_00370 = cgc_append_buf(write_00370, &write_00370_len, write_00370_00000, write_00370_00000_len);
      if (write_00370_len > 0) {
         cgc_transmit_all(1, write_00370, write_00370_len);
      }
      cgc_free(write_00370);
   } while (0);
   do {
      unsigned char *read_00378;
      unsigned int read_00378_len;
      unsigned int read_00378_ptr = 0;
      //**** delimited read
      static unsigned char read_00378_delim[] = 
         "\x3a\x20";
      read_00378 = NULL;
      read_00378_len = 0;
      int read_00378_res = cgc_delimited_read(0, &read_00378, &read_00378_len, read_00378_delim, 2);
      if (read_00378_res) {} //silence unused variable warning
      cgc_free(read_00378);
      if (read_00378_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00371_00000[] = 
         "\x39\x31\x39\x0a";
      static unsigned int write_00371_00000_len = 4;
      unsigned char *write_00371 = NULL;
      unsigned int write_00371_len = 0;
      write_00371 = cgc_append_buf(write_00371, &write_00371_len, write_00371_00000, write_00371_00000_len);
      if (write_00371_len > 0) {
         cgc_transmit_all(1, write_00371, write_00371_len);
      }
      cgc_free(write_00371);
   } while (0);
   do {
      unsigned char *read_00379;
      unsigned int read_00379_len;
      unsigned int read_00379_ptr = 0;
      //**** delimited read
      static unsigned char read_00379_delim[] = 
         "\x3a\x20";
      read_00379 = NULL;
      read_00379_len = 0;
      int read_00379_res = cgc_delimited_read(0, &read_00379, &read_00379_len, read_00379_delim, 2);
      if (read_00379_res) {} //silence unused variable warning
      cgc_free(read_00379);
      if (read_00379_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00372_00000[] = 
         "\x31\x35\x0a";
      static unsigned int write_00372_00000_len = 3;
      unsigned char *write_00372 = NULL;
      unsigned int write_00372_len = 0;
      write_00372 = cgc_append_buf(write_00372, &write_00372_len, write_00372_00000, write_00372_00000_len);
      if (write_00372_len > 0) {
         cgc_transmit_all(1, write_00372, write_00372_len);
      }
      cgc_free(write_00372);
   } while (0);
   do {
      unsigned char *read_00380;
      unsigned int read_00380_len;
      unsigned int read_00380_ptr = 0;
      //**** delimited read
      static unsigned char read_00380_delim[] = 
         "\x3a\x20";
      read_00380 = NULL;
      read_00380_len = 0;
      int read_00380_res = cgc_delimited_read(0, &read_00380, &read_00380_len, read_00380_delim, 2);
      if (read_00380_res) {} //silence unused variable warning
      cgc_free(read_00380);
      if (read_00380_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00373_00000[] = 
         "\x34\x34\x36\x0a";
      static unsigned int write_00373_00000_len = 4;
      unsigned char *write_00373 = NULL;
      unsigned int write_00373_len = 0;
      write_00373 = cgc_append_buf(write_00373, &write_00373_len, write_00373_00000, write_00373_00000_len);
      if (write_00373_len > 0) {
         cgc_transmit_all(1, write_00373, write_00373_len);
      }
      cgc_free(write_00373);
   } while (0);
   do {
      unsigned char *read_00381;
      unsigned int read_00381_len;
      unsigned int read_00381_ptr = 0;
      //**** delimited read
      static unsigned char read_00381_delim[] = 
         "\x3a\x20";
      read_00381 = NULL;
      read_00381_len = 0;
      int read_00381_res = cgc_delimited_read(0, &read_00381, &read_00381_len, read_00381_delim, 2);
      if (read_00381_res) {} //silence unused variable warning
      cgc_free(read_00381);
      if (read_00381_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00374_00000[] = 
         "\x38\x31\x33\x0a";
      static unsigned int write_00374_00000_len = 4;
      unsigned char *write_00374 = NULL;
      unsigned int write_00374_len = 0;
      write_00374 = cgc_append_buf(write_00374, &write_00374_len, write_00374_00000, write_00374_00000_len);
      if (write_00374_len > 0) {
         cgc_transmit_all(1, write_00374, write_00374_len);
      }
      cgc_free(write_00374);
   } while (0);
   do {
      unsigned char *read_00382;
      unsigned int read_00382_len;
      unsigned int read_00382_ptr = 0;
      //**** delimited read
      static unsigned char read_00382_delim[] = 
         "\x3a\x20";
      read_00382 = NULL;
      read_00382_len = 0;
      int read_00382_res = cgc_delimited_read(0, &read_00382, &read_00382_len, read_00382_delim, 2);
      if (read_00382_res) {} //silence unused variable warning
      cgc_free(read_00382);
      if (read_00382_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00375_00000[] = 
         "\x36\x32\x39\x0a";
      static unsigned int write_00375_00000_len = 4;
      unsigned char *write_00375 = NULL;
      unsigned int write_00375_len = 0;
      write_00375 = cgc_append_buf(write_00375, &write_00375_len, write_00375_00000, write_00375_00000_len);
      if (write_00375_len > 0) {
         cgc_transmit_all(1, write_00375, write_00375_len);
      }
      cgc_free(write_00375);
   } while (0);
   do {
      unsigned char *read_00383;
      unsigned int read_00383_len;
      unsigned int read_00383_ptr = 0;
      //**** delimited read
      static unsigned char read_00383_delim[] = 
         "\x3a\x20";
      read_00383 = NULL;
      read_00383_len = 0;
      int read_00383_res = cgc_delimited_read(0, &read_00383, &read_00383_len, read_00383_delim, 2);
      if (read_00383_res) {} //silence unused variable warning
      cgc_free(read_00383);
      if (read_00383_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00376_00000[] = 
         "\x35\x37\x31\x0a";
      static unsigned int write_00376_00000_len = 4;
      unsigned char *write_00376 = NULL;
      unsigned int write_00376_len = 0;
      write_00376 = cgc_append_buf(write_00376, &write_00376_len, write_00376_00000, write_00376_00000_len);
      if (write_00376_len > 0) {
         cgc_transmit_all(1, write_00376, write_00376_len);
      }
      cgc_free(write_00376);
   } while (0);
   do {
      unsigned char *read_00384;
      unsigned int read_00384_len;
      unsigned int read_00384_ptr = 0;
      //**** delimited read
      static unsigned char read_00384_delim[] = 
         "\x3a\x20";
      read_00384 = NULL;
      read_00384_len = 0;
      int read_00384_res = cgc_delimited_read(0, &read_00384, &read_00384_len, read_00384_delim, 2);
      if (read_00384_res) {} //silence unused variable warning
      cgc_free(read_00384);
      if (read_00384_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00377_00000[] = 
         "\x38\x30\x33\x0a";
      static unsigned int write_00377_00000_len = 4;
      unsigned char *write_00377 = NULL;
      unsigned int write_00377_len = 0;
      write_00377 = cgc_append_buf(write_00377, &write_00377_len, write_00377_00000, write_00377_00000_len);
      if (write_00377_len > 0) {
         cgc_transmit_all(1, write_00377, write_00377_len);
      }
      cgc_free(write_00377);
   } while (0);
   do {
      unsigned char *read_00385;
      unsigned int read_00385_len;
      unsigned int read_00385_ptr = 0;
      //**** delimited read
      static unsigned char read_00385_delim[] = 
         "\x3a\x20";
      read_00385 = NULL;
      read_00385_len = 0;
      int read_00385_res = cgc_delimited_read(0, &read_00385, &read_00385_len, read_00385_delim, 2);
      if (read_00385_res) {} //silence unused variable warning
      cgc_free(read_00385);
      if (read_00385_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00378_00000[] = 
         "\x33\x32\x37\x0a";
      static unsigned int write_00378_00000_len = 4;
      unsigned char *write_00378 = NULL;
      unsigned int write_00378_len = 0;
      write_00378 = cgc_append_buf(write_00378, &write_00378_len, write_00378_00000, write_00378_00000_len);
      if (write_00378_len > 0) {
         cgc_transmit_all(1, write_00378, write_00378_len);
      }
      cgc_free(write_00378);
   } while (0);
   do {
      unsigned char *read_00386;
      unsigned int read_00386_len;
      unsigned int read_00386_ptr = 0;
      //**** delimited read
      static unsigned char read_00386_delim[] = 
         "\x3a\x20";
      read_00386 = NULL;
      read_00386_len = 0;
      int read_00386_res = cgc_delimited_read(0, &read_00386, &read_00386_len, read_00386_delim, 2);
      if (read_00386_res) {} //silence unused variable warning
      cgc_free(read_00386);
      if (read_00386_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00379_00000[] = 
         "\x36\x34\x35\x0a";
      static unsigned int write_00379_00000_len = 4;
      unsigned char *write_00379 = NULL;
      unsigned int write_00379_len = 0;
      write_00379 = cgc_append_buf(write_00379, &write_00379_len, write_00379_00000, write_00379_00000_len);
      if (write_00379_len > 0) {
         cgc_transmit_all(1, write_00379, write_00379_len);
      }
      cgc_free(write_00379);
   } while (0);
   do {
      unsigned char *read_00387;
      unsigned int read_00387_len;
      unsigned int read_00387_ptr = 0;
      //**** delimited read
      static unsigned char read_00387_delim[] = 
         "\x3a\x20";
      read_00387 = NULL;
      read_00387_len = 0;
      int read_00387_res = cgc_delimited_read(0, &read_00387, &read_00387_len, read_00387_delim, 2);
      if (read_00387_res) {} //silence unused variable warning
      cgc_free(read_00387);
      if (read_00387_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00380_00000[] = 
         "\x34\x31\x35\x0a";
      static unsigned int write_00380_00000_len = 4;
      unsigned char *write_00380 = NULL;
      unsigned int write_00380_len = 0;
      write_00380 = cgc_append_buf(write_00380, &write_00380_len, write_00380_00000, write_00380_00000_len);
      if (write_00380_len > 0) {
         cgc_transmit_all(1, write_00380, write_00380_len);
      }
      cgc_free(write_00380);
   } while (0);
   do {
      unsigned char *read_00388;
      unsigned int read_00388_len;
      unsigned int read_00388_ptr = 0;
      //**** delimited read
      static unsigned char read_00388_delim[] = 
         "\x3a\x20";
      read_00388 = NULL;
      read_00388_len = 0;
      int read_00388_res = cgc_delimited_read(0, &read_00388, &read_00388_len, read_00388_delim, 2);
      if (read_00388_res) {} //silence unused variable warning
      cgc_free(read_00388);
      if (read_00388_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00381_00000[] = 
         "\x36\x37\x32\x0a";
      static unsigned int write_00381_00000_len = 4;
      unsigned char *write_00381 = NULL;
      unsigned int write_00381_len = 0;
      write_00381 = cgc_append_buf(write_00381, &write_00381_len, write_00381_00000, write_00381_00000_len);
      if (write_00381_len > 0) {
         cgc_transmit_all(1, write_00381, write_00381_len);
      }
      cgc_free(write_00381);
   } while (0);
   do {
      unsigned char *read_00389;
      unsigned int read_00389_len;
      unsigned int read_00389_ptr = 0;
      //**** delimited read
      static unsigned char read_00389_delim[] = 
         "\x3a\x20";
      read_00389 = NULL;
      read_00389_len = 0;
      int read_00389_res = cgc_delimited_read(0, &read_00389, &read_00389_len, read_00389_delim, 2);
      if (read_00389_res) {} //silence unused variable warning
      cgc_free(read_00389);
      if (read_00389_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00382_00000[] = 
         "\x36\x30\x30\x0a";
      static unsigned int write_00382_00000_len = 4;
      unsigned char *write_00382 = NULL;
      unsigned int write_00382_len = 0;
      write_00382 = cgc_append_buf(write_00382, &write_00382_len, write_00382_00000, write_00382_00000_len);
      if (write_00382_len > 0) {
         cgc_transmit_all(1, write_00382, write_00382_len);
      }
      cgc_free(write_00382);
   } while (0);
   do {
      unsigned char *read_00390;
      unsigned int read_00390_len;
      unsigned int read_00390_ptr = 0;
      //**** delimited read
      static unsigned char read_00390_delim[] = 
         "\x3a\x20";
      read_00390 = NULL;
      read_00390_len = 0;
      int read_00390_res = cgc_delimited_read(0, &read_00390, &read_00390_len, read_00390_delim, 2);
      if (read_00390_res) {} //silence unused variable warning
      cgc_free(read_00390);
      if (read_00390_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00383_00000[] = 
         "\x33\x37\x39\x0a";
      static unsigned int write_00383_00000_len = 4;
      unsigned char *write_00383 = NULL;
      unsigned int write_00383_len = 0;
      write_00383 = cgc_append_buf(write_00383, &write_00383_len, write_00383_00000, write_00383_00000_len);
      if (write_00383_len > 0) {
         cgc_transmit_all(1, write_00383, write_00383_len);
      }
      cgc_free(write_00383);
   } while (0);
   do {
      unsigned char *read_00391;
      unsigned int read_00391_len;
      unsigned int read_00391_ptr = 0;
      //**** delimited read
      static unsigned char read_00391_delim[] = 
         "\x3a\x20";
      read_00391 = NULL;
      read_00391_len = 0;
      int read_00391_res = cgc_delimited_read(0, &read_00391, &read_00391_len, read_00391_delim, 2);
      if (read_00391_res) {} //silence unused variable warning
      cgc_free(read_00391);
      if (read_00391_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00384_00000[] = 
         "\x38\x39\x35\x0a";
      static unsigned int write_00384_00000_len = 4;
      unsigned char *write_00384 = NULL;
      unsigned int write_00384_len = 0;
      write_00384 = cgc_append_buf(write_00384, &write_00384_len, write_00384_00000, write_00384_00000_len);
      if (write_00384_len > 0) {
         cgc_transmit_all(1, write_00384, write_00384_len);
      }
      cgc_free(write_00384);
   } while (0);
   do {
      unsigned char *read_00392;
      unsigned int read_00392_len;
      unsigned int read_00392_ptr = 0;
      //**** delimited read
      static unsigned char read_00392_delim[] = 
         "\x3a\x20";
      read_00392 = NULL;
      read_00392_len = 0;
      int read_00392_res = cgc_delimited_read(0, &read_00392, &read_00392_len, read_00392_delim, 2);
      if (read_00392_res) {} //silence unused variable warning
      cgc_free(read_00392);
      if (read_00392_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00385_00000[] = 
         "\x33\x31\x33\x0a";
      static unsigned int write_00385_00000_len = 4;
      unsigned char *write_00385 = NULL;
      unsigned int write_00385_len = 0;
      write_00385 = cgc_append_buf(write_00385, &write_00385_len, write_00385_00000, write_00385_00000_len);
      if (write_00385_len > 0) {
         cgc_transmit_all(1, write_00385, write_00385_len);
      }
      cgc_free(write_00385);
   } while (0);
   do {
      unsigned char *read_00393;
      unsigned int read_00393_len;
      unsigned int read_00393_ptr = 0;
      //**** delimited read
      static unsigned char read_00393_delim[] = 
         "\x3a\x20";
      read_00393 = NULL;
      read_00393_len = 0;
      int read_00393_res = cgc_delimited_read(0, &read_00393, &read_00393_len, read_00393_delim, 2);
      if (read_00393_res) {} //silence unused variable warning
      cgc_free(read_00393);
      if (read_00393_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00386_00000[] = 
         "\x33\x30\x37\x0a";
      static unsigned int write_00386_00000_len = 4;
      unsigned char *write_00386 = NULL;
      unsigned int write_00386_len = 0;
      write_00386 = cgc_append_buf(write_00386, &write_00386_len, write_00386_00000, write_00386_00000_len);
      if (write_00386_len > 0) {
         cgc_transmit_all(1, write_00386, write_00386_len);
      }
      cgc_free(write_00386);
   } while (0);
   do {
      unsigned char *read_00394;
      unsigned int read_00394_len;
      unsigned int read_00394_ptr = 0;
      //**** delimited read
      static unsigned char read_00394_delim[] = 
         "\x3a\x20";
      read_00394 = NULL;
      read_00394_len = 0;
      int read_00394_res = cgc_delimited_read(0, &read_00394, &read_00394_len, read_00394_delim, 2);
      if (read_00394_res) {} //silence unused variable warning
      cgc_free(read_00394);
      if (read_00394_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00387_00000[] = 
         "\x38\x30\x32\x0a";
      static unsigned int write_00387_00000_len = 4;
      unsigned char *write_00387 = NULL;
      unsigned int write_00387_len = 0;
      write_00387 = cgc_append_buf(write_00387, &write_00387_len, write_00387_00000, write_00387_00000_len);
      if (write_00387_len > 0) {
         cgc_transmit_all(1, write_00387, write_00387_len);
      }
      cgc_free(write_00387);
   } while (0);
   do {
      unsigned char *read_00395;
      unsigned int read_00395_len;
      unsigned int read_00395_ptr = 0;
      //**** delimited read
      static unsigned char read_00395_delim[] = 
         "\x3a\x20";
      read_00395 = NULL;
      read_00395_len = 0;
      int read_00395_res = cgc_delimited_read(0, &read_00395, &read_00395_len, read_00395_delim, 2);
      if (read_00395_res) {} //silence unused variable warning
      cgc_free(read_00395);
      if (read_00395_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00388_00000[] = 
         "\x34\x30\x30\x0a";
      static unsigned int write_00388_00000_len = 4;
      unsigned char *write_00388 = NULL;
      unsigned int write_00388_len = 0;
      write_00388 = cgc_append_buf(write_00388, &write_00388_len, write_00388_00000, write_00388_00000_len);
      if (write_00388_len > 0) {
         cgc_transmit_all(1, write_00388, write_00388_len);
      }
      cgc_free(write_00388);
   } while (0);
   do {
      unsigned char *read_00396;
      unsigned int read_00396_len;
      unsigned int read_00396_ptr = 0;
      //**** delimited read
      static unsigned char read_00396_delim[] = 
         "\x3a\x20";
      read_00396 = NULL;
      read_00396_len = 0;
      int read_00396_res = cgc_delimited_read(0, &read_00396, &read_00396_len, read_00396_delim, 2);
      if (read_00396_res) {} //silence unused variable warning
      cgc_free(read_00396);
      if (read_00396_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00389_00000[] = 
         "\x32\x37\x34\x0a";
      static unsigned int write_00389_00000_len = 4;
      unsigned char *write_00389 = NULL;
      unsigned int write_00389_len = 0;
      write_00389 = cgc_append_buf(write_00389, &write_00389_len, write_00389_00000, write_00389_00000_len);
      if (write_00389_len > 0) {
         cgc_transmit_all(1, write_00389, write_00389_len);
      }
      cgc_free(write_00389);
   } while (0);
   do {
      unsigned char *read_00397;
      unsigned int read_00397_len;
      unsigned int read_00397_ptr = 0;
      //**** delimited read
      static unsigned char read_00397_delim[] = 
         "\x3a\x20";
      read_00397 = NULL;
      read_00397_len = 0;
      int read_00397_res = cgc_delimited_read(0, &read_00397, &read_00397_len, read_00397_delim, 2);
      if (read_00397_res) {} //silence unused variable warning
      cgc_free(read_00397);
      if (read_00397_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00390_00000[] = 
         "\x39\x35\x33\x0a";
      static unsigned int write_00390_00000_len = 4;
      unsigned char *write_00390 = NULL;
      unsigned int write_00390_len = 0;
      write_00390 = cgc_append_buf(write_00390, &write_00390_len, write_00390_00000, write_00390_00000_len);
      if (write_00390_len > 0) {
         cgc_transmit_all(1, write_00390, write_00390_len);
      }
      cgc_free(write_00390);
   } while (0);
   do {
      unsigned char *read_00398;
      unsigned int read_00398_len;
      unsigned int read_00398_ptr = 0;
      //**** delimited read
      static unsigned char read_00398_delim[] = 
         "\x3a\x20";
      read_00398 = NULL;
      read_00398_len = 0;
      int read_00398_res = cgc_delimited_read(0, &read_00398, &read_00398_len, read_00398_delim, 2);
      if (read_00398_res) {} //silence unused variable warning
      cgc_free(read_00398);
      if (read_00398_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00391_00000[] = 
         "\x38\x35\x33\x0a";
      static unsigned int write_00391_00000_len = 4;
      unsigned char *write_00391 = NULL;
      unsigned int write_00391_len = 0;
      write_00391 = cgc_append_buf(write_00391, &write_00391_len, write_00391_00000, write_00391_00000_len);
      if (write_00391_len > 0) {
         cgc_transmit_all(1, write_00391, write_00391_len);
      }
      cgc_free(write_00391);
   } while (0);
   do {
      unsigned char *read_00399;
      unsigned int read_00399_len;
      unsigned int read_00399_ptr = 0;
      //**** delimited read
      static unsigned char read_00399_delim[] = 
         "\x3a\x20";
      read_00399 = NULL;
      read_00399_len = 0;
      int read_00399_res = cgc_delimited_read(0, &read_00399, &read_00399_len, read_00399_delim, 2);
      if (read_00399_res) {} //silence unused variable warning
      cgc_free(read_00399);
      if (read_00399_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00392_00000[] = 
         "\x32\x30\x30\x0a";
      static unsigned int write_00392_00000_len = 4;
      unsigned char *write_00392 = NULL;
      unsigned int write_00392_len = 0;
      write_00392 = cgc_append_buf(write_00392, &write_00392_len, write_00392_00000, write_00392_00000_len);
      if (write_00392_len > 0) {
         cgc_transmit_all(1, write_00392, write_00392_len);
      }
      cgc_free(write_00392);
   } while (0);
   do {
      unsigned char *read_00400;
      unsigned int read_00400_len;
      unsigned int read_00400_ptr = 0;
      //**** delimited read
      static unsigned char read_00400_delim[] = 
         "\x3a\x20";
      read_00400 = NULL;
      read_00400_len = 0;
      int read_00400_res = cgc_delimited_read(0, &read_00400, &read_00400_len, read_00400_delim, 2);
      if (read_00400_res) {} //silence unused variable warning
      cgc_free(read_00400);
      if (read_00400_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00393_00000[] = 
         "\x36\x33\x34\x0a";
      static unsigned int write_00393_00000_len = 4;
      unsigned char *write_00393 = NULL;
      unsigned int write_00393_len = 0;
      write_00393 = cgc_append_buf(write_00393, &write_00393_len, write_00393_00000, write_00393_00000_len);
      if (write_00393_len > 0) {
         cgc_transmit_all(1, write_00393, write_00393_len);
      }
      cgc_free(write_00393);
   } while (0);
   do {
      unsigned char *read_00401;
      unsigned int read_00401_len;
      unsigned int read_00401_ptr = 0;
      //**** delimited read
      static unsigned char read_00401_delim[] = 
         "\x3a\x20";
      read_00401 = NULL;
      read_00401_len = 0;
      int read_00401_res = cgc_delimited_read(0, &read_00401, &read_00401_len, read_00401_delim, 2);
      if (read_00401_res) {} //silence unused variable warning
      cgc_free(read_00401);
      if (read_00401_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00394_00000[] = 
         "\x37\x35\x38\x0a";
      static unsigned int write_00394_00000_len = 4;
      unsigned char *write_00394 = NULL;
      unsigned int write_00394_len = 0;
      write_00394 = cgc_append_buf(write_00394, &write_00394_len, write_00394_00000, write_00394_00000_len);
      if (write_00394_len > 0) {
         cgc_transmit_all(1, write_00394, write_00394_len);
      }
      cgc_free(write_00394);
   } while (0);
   do {
      unsigned char *read_00402;
      unsigned int read_00402_len;
      unsigned int read_00402_ptr = 0;
      //**** delimited read
      static unsigned char read_00402_delim[] = 
         "\x3a\x20";
      read_00402 = NULL;
      read_00402_len = 0;
      int read_00402_res = cgc_delimited_read(0, &read_00402, &read_00402_len, read_00402_delim, 2);
      if (read_00402_res) {} //silence unused variable warning
      cgc_free(read_00402);
      if (read_00402_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00395_00000[] = 
         "\x37\x39\x30\x0a";
      static unsigned int write_00395_00000_len = 4;
      unsigned char *write_00395 = NULL;
      unsigned int write_00395_len = 0;
      write_00395 = cgc_append_buf(write_00395, &write_00395_len, write_00395_00000, write_00395_00000_len);
      if (write_00395_len > 0) {
         cgc_transmit_all(1, write_00395, write_00395_len);
      }
      cgc_free(write_00395);
   } while (0);
   do {
      unsigned char *read_00403;
      unsigned int read_00403_len;
      unsigned int read_00403_ptr = 0;
      //**** delimited read
      static unsigned char read_00403_delim[] = 
         "\x3a\x20";
      read_00403 = NULL;
      read_00403_len = 0;
      int read_00403_res = cgc_delimited_read(0, &read_00403, &read_00403_len, read_00403_delim, 2);
      if (read_00403_res) {} //silence unused variable warning
      cgc_free(read_00403);
      if (read_00403_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00396_00000[] = 
         "\x33\x34\x33\x0a";
      static unsigned int write_00396_00000_len = 4;
      unsigned char *write_00396 = NULL;
      unsigned int write_00396_len = 0;
      write_00396 = cgc_append_buf(write_00396, &write_00396_len, write_00396_00000, write_00396_00000_len);
      if (write_00396_len > 0) {
         cgc_transmit_all(1, write_00396, write_00396_len);
      }
      cgc_free(write_00396);
   } while (0);
   do {
      unsigned char *read_00404;
      unsigned int read_00404_len;
      unsigned int read_00404_ptr = 0;
      //**** delimited read
      static unsigned char read_00404_delim[] = 
         "\x3a\x20";
      read_00404 = NULL;
      read_00404_len = 0;
      int read_00404_res = cgc_delimited_read(0, &read_00404, &read_00404_len, read_00404_delim, 2);
      if (read_00404_res) {} //silence unused variable warning
      cgc_free(read_00404);
      if (read_00404_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00397_00000[] = 
         "\x38\x35\x34\x0a";
      static unsigned int write_00397_00000_len = 4;
      unsigned char *write_00397 = NULL;
      unsigned int write_00397_len = 0;
      write_00397 = cgc_append_buf(write_00397, &write_00397_len, write_00397_00000, write_00397_00000_len);
      if (write_00397_len > 0) {
         cgc_transmit_all(1, write_00397, write_00397_len);
      }
      cgc_free(write_00397);
   } while (0);
   do {
      unsigned char *read_00405;
      unsigned int read_00405_len;
      unsigned int read_00405_ptr = 0;
      //**** delimited read
      static unsigned char read_00405_delim[] = 
         "\x3a\x20";
      read_00405 = NULL;
      read_00405_len = 0;
      int read_00405_res = cgc_delimited_read(0, &read_00405, &read_00405_len, read_00405_delim, 2);
      if (read_00405_res) {} //silence unused variable warning
      cgc_free(read_00405);
      if (read_00405_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00398_00000[] = 
         "\x31\x36\x0a";
      static unsigned int write_00398_00000_len = 3;
      unsigned char *write_00398 = NULL;
      unsigned int write_00398_len = 0;
      write_00398 = cgc_append_buf(write_00398, &write_00398_len, write_00398_00000, write_00398_00000_len);
      if (write_00398_len > 0) {
         cgc_transmit_all(1, write_00398, write_00398_len);
      }
      cgc_free(write_00398);
   } while (0);
   do {
      unsigned char *read_00406;
      unsigned int read_00406_len;
      unsigned int read_00406_ptr = 0;
      //**** delimited read
      static unsigned char read_00406_delim[] = 
         "\x3a\x20";
      read_00406 = NULL;
      read_00406_len = 0;
      int read_00406_res = cgc_delimited_read(0, &read_00406, &read_00406_len, read_00406_delim, 2);
      if (read_00406_res) {} //silence unused variable warning
      cgc_free(read_00406);
      if (read_00406_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00399_00000[] = 
         "\x35\x33\x37\x0a";
      static unsigned int write_00399_00000_len = 4;
      unsigned char *write_00399 = NULL;
      unsigned int write_00399_len = 0;
      write_00399 = cgc_append_buf(write_00399, &write_00399_len, write_00399_00000, write_00399_00000_len);
      if (write_00399_len > 0) {
         cgc_transmit_all(1, write_00399, write_00399_len);
      }
      cgc_free(write_00399);
   } while (0);
   do {
      unsigned char *read_00407;
      unsigned int read_00407_len;
      unsigned int read_00407_ptr = 0;
      //**** delimited read
      static unsigned char read_00407_delim[] = 
         "\x3a\x20";
      read_00407 = NULL;
      read_00407_len = 0;
      int read_00407_res = cgc_delimited_read(0, &read_00407, &read_00407_len, read_00407_delim, 2);
      if (read_00407_res) {} //silence unused variable warning
      cgc_free(read_00407);
      if (read_00407_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00400_00000[] = 
         "\x35\x37\x30\x0a";
      static unsigned int write_00400_00000_len = 4;
      unsigned char *write_00400 = NULL;
      unsigned int write_00400_len = 0;
      write_00400 = cgc_append_buf(write_00400, &write_00400_len, write_00400_00000, write_00400_00000_len);
      if (write_00400_len > 0) {
         cgc_transmit_all(1, write_00400, write_00400_len);
      }
      cgc_free(write_00400);
   } while (0);
   do {
      unsigned char *read_00408;
      unsigned int read_00408_len;
      unsigned int read_00408_ptr = 0;
      //**** delimited read
      static unsigned char read_00408_delim[] = 
         "\x3a\x20";
      read_00408 = NULL;
      read_00408_len = 0;
      int read_00408_res = cgc_delimited_read(0, &read_00408, &read_00408_len, read_00408_delim, 2);
      if (read_00408_res) {} //silence unused variable warning
      cgc_free(read_00408);
      if (read_00408_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00401_00000[] = 
         "\x38\x38\x39\x0a";
      static unsigned int write_00401_00000_len = 4;
      unsigned char *write_00401 = NULL;
      unsigned int write_00401_len = 0;
      write_00401 = cgc_append_buf(write_00401, &write_00401_len, write_00401_00000, write_00401_00000_len);
      if (write_00401_len > 0) {
         cgc_transmit_all(1, write_00401, write_00401_len);
      }
      cgc_free(write_00401);
   } while (0);
   do {
      unsigned char *read_00409;
      unsigned int read_00409_len;
      unsigned int read_00409_ptr = 0;
      //**** delimited read
      static unsigned char read_00409_delim[] = 
         "\x3a\x20";
      read_00409 = NULL;
      read_00409_len = 0;
      int read_00409_res = cgc_delimited_read(0, &read_00409, &read_00409_len, read_00409_delim, 2);
      if (read_00409_res) {} //silence unused variable warning
      cgc_free(read_00409);
      if (read_00409_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00402_00000[] = 
         "\x31\x36\x0a";
      static unsigned int write_00402_00000_len = 3;
      unsigned char *write_00402 = NULL;
      unsigned int write_00402_len = 0;
      write_00402 = cgc_append_buf(write_00402, &write_00402_len, write_00402_00000, write_00402_00000_len);
      if (write_00402_len > 0) {
         cgc_transmit_all(1, write_00402, write_00402_len);
      }
      cgc_free(write_00402);
   } while (0);
   do {
      unsigned char *read_00410;
      unsigned int read_00410_len;
      unsigned int read_00410_ptr = 0;
      //**** delimited read
      static unsigned char read_00410_delim[] = 
         "\x3a\x20";
      read_00410 = NULL;
      read_00410_len = 0;
      int read_00410_res = cgc_delimited_read(0, &read_00410, &read_00410_len, read_00410_delim, 2);
      if (read_00410_res) {} //silence unused variable warning
      cgc_free(read_00410);
      if (read_00410_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00403_00000[] = 
         "\x39\x35\x39\x0a";
      static unsigned int write_00403_00000_len = 4;
      unsigned char *write_00403 = NULL;
      unsigned int write_00403_len = 0;
      write_00403 = cgc_append_buf(write_00403, &write_00403_len, write_00403_00000, write_00403_00000_len);
      if (write_00403_len > 0) {
         cgc_transmit_all(1, write_00403, write_00403_len);
      }
      cgc_free(write_00403);
   } while (0);
   do {
      unsigned char *read_00411;
      unsigned int read_00411_len;
      unsigned int read_00411_ptr = 0;
      //**** delimited read
      static unsigned char read_00411_delim[] = 
         "\x3a\x20";
      read_00411 = NULL;
      read_00411_len = 0;
      int read_00411_res = cgc_delimited_read(0, &read_00411, &read_00411_len, read_00411_delim, 2);
      if (read_00411_res) {} //silence unused variable warning
      cgc_free(read_00411);
      if (read_00411_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** delay
   cgc_delay(10);
}
