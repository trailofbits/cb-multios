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
         "\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 1);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
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
         "\x43\x20\x2d\x20\x43\x68\x61\x6e\x67\x65\x20\x44\x69\x76\x65\x72"
         "\x20\x49\x6e\x66\x6f";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 21);
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
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x4c\x20\x2d\x20\x4c\x6f\x67\x20\x61\x20\x4e\x65\x77\x20\x44\x69"
         "\x76\x65";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 18);
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
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x44\x20\x2d\x20\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x20\x44\x69\x76"
         "\x65\x20\x44\x61\x74\x61";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 22);
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
         "\x45\x20\x2d\x20\x45\x64\x69\x74\x20\x44\x69\x76\x65\x73";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 14);
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
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x50\x20\x2d\x20\x50\x72\x69\x6e\x74\x20\x44\x69\x76\x65\x20\x4c"
         "\x6f\x67\x73";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 19);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
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
         "\x52\x20\x2d\x20\x52\x65\x6d\x6f\x76\x65\x20\x44\x69\x76\x65\x73";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 16);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
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
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x53\x20\x2d\x20\x44\x69\x76\x65\x72\x20\x53\x74\x61\x74\x69\x73"
         "\x74\x69\x63\x73";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 20);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
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
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x58\x20\x2d\x20\x45\x78\x69\x74\x20\x41\x70\x70\x6c\x69\x63\x61"
         "\x74\x69\x6f\x6e";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 20);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 1;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x3a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 1);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x6c\x0a";
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
         "\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 1);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 11;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x44\x69\x76\x65\x20\x53\x69\x74\x65\x3a\x20";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 11);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x0a";
      static unsigned int write_00001_00000_len = 1;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 6;
      read_00012 = (unsigned char*)cgc_malloc(read_00012_len);
      int read_00012_res = cgc_length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x44\x61\x74\x65\x3a\x20";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 6);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x0a";
      static unsigned int write_00002_00000_len = 1;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 6;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x54\x69\x6d\x65\x3a\x20";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 6);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x0a";
      static unsigned int write_00003_00000_len = 1;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length read
      read_00014_len = 22;
      read_00014 = (unsigned char*)cgc_malloc(read_00014_len);
      int read_00014_res = cgc_length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x4c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x28\x61\x72\x65\x61\x2f\x63"
         "\x69\x74\x79\x29\x3a\x20";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 22);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x0a";
      static unsigned int write_00004_00000_len = 1;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length read
      read_00015_len = 17;
      read_00015 = (unsigned char*)cgc_malloc(read_00015_len);
      int read_00015_res = cgc_length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x4d\x61\x78\x20\x44\x65\x70\x74\x68\x20\x69\x6e\x20\x66\x74\x3a"
         "\x20";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 17);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x0a";
      static unsigned int write_00005_00000_len = 1;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length read
      read_00016_len = 17;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x41\x76\x67\x20\x44\x65\x70\x74\x68\x20\x69\x6e\x20\x66\x74\x3a"
         "\x20";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 17);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x0a";
      static unsigned int write_00006_00000_len = 1;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 22;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00017_00000[] = 
         "\x44\x69\x76\x65\x20\x44\x75\x72\x61\x74\x69\x6f\x6e\x20\x28\x6d"
         "\x69\x6e\x73\x29\x3a\x20";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 22);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x0a";
      static unsigned int write_00007_00000_len = 1;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 15;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x4f\x32\x20\x50\x65\x72\x63\x65\x6e\x74\x61\x67\x65\x3a\x20";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 15);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x0a";
      static unsigned int write_00008_00000_len = 1;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 19;
      read_00019 = (unsigned char*)cgc_malloc(read_00019_len);
      int read_00019_res = cgc_length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00019_00000[] = 
         "\x50\x72\x65\x73\x73\x75\x72\x65\x20\x49\x6e\x20\x28\x70\x73\x69"
         "\x29\x3a\x20";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 19);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x0a";
      static unsigned int write_00009_00000_len = 1;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length read
      read_00020_len = 20;
      read_00020 = (unsigned char*)cgc_malloc(read_00020_len);
      int read_00020_res = cgc_length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00020_00000[] = 
         "\x50\x72\x65\x73\x73\x75\x72\x65\x20\x4f\x75\x74\x20\x28\x70\x73"
         "\x69\x29\x3a\x20";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 20);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x0a";
      static unsigned int write_00010_00000_len = 1;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x0a";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = cgc_delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 1);
      if (read_00021_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00021_00000[] = 
         "\x0a";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 1);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** delimited read
      static unsigned char read_00022_delim[] = 
         "\x0a";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = cgc_delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 1);
      if (read_00022_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00022_00000[] = 
         "\x43\x20\x2d\x20\x43\x68\x61\x6e\x67\x65\x20\x44\x69\x76\x65\x72"
         "\x20\x49\x6e\x66\x6f";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 21);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** delimited read
      static unsigned char read_00023_delim[] = 
         "\x0a";
      read_00023 = NULL;
      read_00023_len = 0;
      int read_00023_res = cgc_delimited_read(0, &read_00023, &read_00023_len, read_00023_delim, 1);
      if (read_00023_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00023_00000[] = 
         "\x4c\x20\x2d\x20\x4c\x6f\x67\x20\x61\x20\x4e\x65\x77\x20\x44\x69"
         "\x76\x65";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 18);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** delimited read
      static unsigned char read_00024_delim[] = 
         "\x0a";
      read_00024 = NULL;
      read_00024_len = 0;
      int read_00024_res = cgc_delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 1);
      if (read_00024_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00024_00000[] = 
         "\x44\x20\x2d\x20\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x20\x44\x69\x76"
         "\x65\x20\x44\x61\x74\x61";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 22);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** delimited read
      static unsigned char read_00025_delim[] = 
         "\x0a";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = cgc_delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 1);
      if (read_00025_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00025_00000[] = 
         "\x45\x20\x2d\x20\x45\x64\x69\x74\x20\x44\x69\x76\x65\x73";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 14);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** delimited read
      static unsigned char read_00026_delim[] = 
         "\x0a";
      read_00026 = NULL;
      read_00026_len = 0;
      int read_00026_res = cgc_delimited_read(0, &read_00026, &read_00026_len, read_00026_delim, 1);
      if (read_00026_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00026_00000[] = 
         "\x50\x20\x2d\x20\x50\x72\x69\x6e\x74\x20\x44\x69\x76\x65\x20\x4c"
         "\x6f\x67\x73";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 19);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** delimited read
      static unsigned char read_00027_delim[] = 
         "\x0a";
      read_00027 = NULL;
      read_00027_len = 0;
      int read_00027_res = cgc_delimited_read(0, &read_00027, &read_00027_len, read_00027_delim, 1);
      if (read_00027_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00027_00000[] = 
         "\x52\x20\x2d\x20\x52\x65\x6d\x6f\x76\x65\x20\x44\x69\x76\x65\x73";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 16);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** delimited read
      static unsigned char read_00028_delim[] = 
         "\x0a";
      read_00028 = NULL;
      read_00028_len = 0;
      int read_00028_res = cgc_delimited_read(0, &read_00028, &read_00028_len, read_00028_delim, 1);
      if (read_00028_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00028_00000[] = 
         "\x53\x20\x2d\x20\x44\x69\x76\x65\x72\x20\x53\x74\x61\x74\x69\x73"
         "\x74\x69\x63\x73";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 20);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** delimited read
      static unsigned char read_00029_delim[] = 
         "\x0a";
      read_00029 = NULL;
      read_00029_len = 0;
      int read_00029_res = cgc_delimited_read(0, &read_00029, &read_00029_len, read_00029_delim, 1);
      if (read_00029_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00029_00000[] = 
         "\x58\x20\x2d\x20\x45\x78\x69\x74\x20\x41\x70\x70\x6c\x69\x63\x61"
         "\x74\x69\x6f\x6e";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 20);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** delimited read
      static unsigned char read_00030_delim[] = 
         "\x3a";
      read_00030 = NULL;
      read_00030_len = 0;
      int read_00030_res = cgc_delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 1);
      if (read_00030_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00030_00000[] = 
         "\x3a";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 1);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x65\x0a";
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
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** delimited read
      static unsigned char read_00031_delim[] = 
         "\x0a";
      read_00031 = NULL;
      read_00031_len = 0;
      int read_00031_res = cgc_delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 1);
      if (read_00031_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00031_00000[] = 
         "\x0a";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 1);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** delimited read
      static unsigned char read_00032_delim[] = 
         "\x0a";
      read_00032 = NULL;
      read_00032_len = 0;
      int read_00032_res = cgc_delimited_read(0, &read_00032, &read_00032_len, read_00032_delim, 1);
      if (read_00032_res) {} //silence unused variable warning
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** delimited read
      static unsigned char read_00033_delim[] = 
         "\x0a";
      read_00033 = NULL;
      read_00033_len = 0;
      int read_00033_res = cgc_delimited_read(0, &read_00033, &read_00033_len, read_00033_delim, 1);
      if (read_00033_res) {} //silence unused variable warning
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** delimited read
      static unsigned char read_00034_delim[] = 
         "\x0a";
      read_00034 = NULL;
      read_00034_len = 0;
      int read_00034_res = cgc_delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 1);
      if (read_00034_res) {} //silence unused variable warning
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** delimited read
      static unsigned char read_00035_delim[] = 
         "\x0a";
      read_00035 = NULL;
      read_00035_len = 0;
      int read_00035_res = cgc_delimited_read(0, &read_00035, &read_00035_len, read_00035_delim, 1);
      if (read_00035_res) {} //silence unused variable warning
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** delimited read
      static unsigned char read_00036_delim[] = 
         "\x0a";
      read_00036 = NULL;
      read_00036_len = 0;
      int read_00036_res = cgc_delimited_read(0, &read_00036, &read_00036_len, read_00036_delim, 1);
      if (read_00036_res) {} //silence unused variable warning
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length read
      read_00037_len = 11;
      read_00037 = (unsigned char*)cgc_malloc(read_00037_len);
      int read_00037_res = cgc_length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00037_00000[] = 
         "\x44\x69\x76\x65\x20\x53\x69\x74\x65\x3a\x20";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 11);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x0a";
      static unsigned int write_00013_00000_len = 1;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** length read
      read_00038_len = 6;
      read_00038 = (unsigned char*)cgc_malloc(read_00038_len);
      int read_00038_res = cgc_length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00038_00000[] = 
         "\x44\x61\x74\x65\x3a\x20";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 6);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x0a";
      static unsigned int write_00014_00000_len = 1;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** length read
      read_00039_len = 6;
      read_00039 = (unsigned char*)cgc_malloc(read_00039_len);
      int read_00039_res = cgc_length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00039_00000[] = 
         "\x54\x69\x6d\x65\x3a\x20";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 6);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x0a";
      static unsigned int write_00015_00000_len = 1;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** length read
      read_00040_len = 22;
      read_00040 = (unsigned char*)cgc_malloc(read_00040_len);
      int read_00040_res = cgc_length_read(0, read_00040, read_00040_len);
      if (read_00040_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00040_00000[] = 
         "\x4c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x28\x61\x72\x65\x61\x2f\x63"
         "\x69\x74\x79\x29\x3a\x20";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 22);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a"
         "\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x7a\x0a";
      static unsigned int write_00016_00000_len = 331;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** length read
      read_00041_len = 17;
      read_00041 = (unsigned char*)cgc_malloc(read_00041_len);
      int read_00041_res = cgc_length_read(0, read_00041, read_00041_len);
      if (read_00041_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00041_00000[] = 
         "\x4d\x61\x78\x20\x44\x65\x70\x74\x68\x20\x69\x6e\x20\x66\x74\x3a"
         "\x20";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 17);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x0a";
      static unsigned int write_00017_00000_len = 1;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** length read
      read_00042_len = 17;
      read_00042 = (unsigned char*)cgc_malloc(read_00042_len);
      int read_00042_res = cgc_length_read(0, read_00042, read_00042_len);
      if (read_00042_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00042_00000[] = 
         "\x41\x76\x67\x20\x44\x65\x70\x74\x68\x20\x69\x6e\x20\x66\x74\x3a"
         "\x20";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 17);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x0a";
      static unsigned int write_00018_00000_len = 1;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** length read
      read_00043_len = 22;
      read_00043 = (unsigned char*)cgc_malloc(read_00043_len);
      int read_00043_res = cgc_length_read(0, read_00043, read_00043_len);
      if (read_00043_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00043_00000[] = 
         "\x44\x69\x76\x65\x20\x44\x75\x72\x61\x74\x69\x6f\x6e\x20\x28\x6d"
         "\x69\x6e\x73\x29\x3a\x20";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 22);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x0a";
      static unsigned int write_00019_00000_len = 1;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** length read
      read_00044_len = 15;
      read_00044 = (unsigned char*)cgc_malloc(read_00044_len);
      int read_00044_res = cgc_length_read(0, read_00044, read_00044_len);
      if (read_00044_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00044_00000[] = 
         "\x4f\x32\x20\x50\x65\x72\x63\x65\x6e\x74\x61\x67\x65\x3a\x20";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 15);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x0a";
      static unsigned int write_00020_00000_len = 1;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** length read
      read_00045_len = 19;
      read_00045 = (unsigned char*)cgc_malloc(read_00045_len);
      int read_00045_res = cgc_length_read(0, read_00045, read_00045_len);
      if (read_00045_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00045_00000[] = 
         "\x50\x72\x65\x73\x73\x75\x72\x65\x20\x49\x6e\x20\x28\x70\x73\x69"
         "\x29\x3a\x20";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 19);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x0a";
      static unsigned int write_00021_00000_len = 1;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** length read
      read_00046_len = 20;
      read_00046 = (unsigned char*)cgc_malloc(read_00046_len);
      int read_00046_res = cgc_length_read(0, read_00046, read_00046_len);
      if (read_00046_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00046_00000[] = 
         "\x50\x72\x65\x73\x73\x75\x72\x65\x20\x4f\x75\x74\x20\x28\x70\x73"
         "\x69\x29\x3a\x20";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 20);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x0a";
      static unsigned int write_00022_00000_len = 1;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** delimited read
      static unsigned char read_00047_delim[] = 
         "\x0a";
      read_00047 = NULL;
      read_00047_len = 0;
      int read_00047_res = cgc_delimited_read(0, &read_00047, &read_00047_len, read_00047_delim, 1);
      if (read_00047_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00047_00000[] = 
         "\x0a";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 1);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** delimited read
      static unsigned char read_00048_delim[] = 
         "\x0a";
      read_00048 = NULL;
      read_00048_len = 0;
      int read_00048_res = cgc_delimited_read(0, &read_00048, &read_00048_len, read_00048_delim, 1);
      if (read_00048_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00048_00000[] = 
         "\x43\x20\x2d\x20\x43\x68\x61\x6e\x67\x65\x20\x44\x69\x76\x65\x72"
         "\x20\x49\x6e\x66\x6f";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 21);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** delimited read
      static unsigned char read_00049_delim[] = 
         "\x0a";
      read_00049 = NULL;
      read_00049_len = 0;
      int read_00049_res = cgc_delimited_read(0, &read_00049, &read_00049_len, read_00049_delim, 1);
      if (read_00049_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00049_00000[] = 
         "\x4c\x20\x2d\x20\x4c\x6f\x67\x20\x61\x20\x4e\x65\x77\x20\x44\x69"
         "\x76\x65";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 18);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** delimited read
      static unsigned char read_00050_delim[] = 
         "\x0a";
      read_00050 = NULL;
      read_00050_len = 0;
      int read_00050_res = cgc_delimited_read(0, &read_00050, &read_00050_len, read_00050_delim, 1);
      if (read_00050_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00050_00000[] = 
         "\x44\x20\x2d\x20\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x20\x44\x69\x76"
         "\x65\x20\x44\x61\x74\x61";
      read_00050_ptr += cgc_data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 22);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** delimited read
      static unsigned char read_00051_delim[] = 
         "\x0a";
      read_00051 = NULL;
      read_00051_len = 0;
      int read_00051_res = cgc_delimited_read(0, &read_00051, &read_00051_len, read_00051_delim, 1);
      if (read_00051_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00051_00000[] = 
         "\x45\x20\x2d\x20\x45\x64\x69\x74\x20\x44\x69\x76\x65\x73";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 14);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** delimited read
      static unsigned char read_00052_delim[] = 
         "\x0a";
      read_00052 = NULL;
      read_00052_len = 0;
      int read_00052_res = cgc_delimited_read(0, &read_00052, &read_00052_len, read_00052_delim, 1);
      if (read_00052_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00052_00000[] = 
         "\x50\x20\x2d\x20\x50\x72\x69\x6e\x74\x20\x44\x69\x76\x65\x20\x4c"
         "\x6f\x67\x73";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 19);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** delimited read
      static unsigned char read_00053_delim[] = 
         "\x0a";
      read_00053 = NULL;
      read_00053_len = 0;
      int read_00053_res = cgc_delimited_read(0, &read_00053, &read_00053_len, read_00053_delim, 1);
      if (read_00053_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00053_00000[] = 
         "\x52\x20\x2d\x20\x52\x65\x6d\x6f\x76\x65\x20\x44\x69\x76\x65\x73";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 16);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00054;
      unsigned int read_00054_len;
      unsigned int read_00054_ptr = 0;
      //**** delimited read
      static unsigned char read_00054_delim[] = 
         "\x0a";
      read_00054 = NULL;
      read_00054_len = 0;
      int read_00054_res = cgc_delimited_read(0, &read_00054, &read_00054_len, read_00054_delim, 1);
      if (read_00054_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00054_00000[] = 
         "\x53\x20\x2d\x20\x44\x69\x76\x65\x72\x20\x53\x74\x61\x74\x69\x73"
         "\x74\x69\x63\x73";
      read_00054_ptr += cgc_data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 20);
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00055;
      unsigned int read_00055_len;
      unsigned int read_00055_ptr = 0;
      //**** delimited read
      static unsigned char read_00055_delim[] = 
         "\x0a";
      read_00055 = NULL;
      read_00055_len = 0;
      int read_00055_res = cgc_delimited_read(0, &read_00055, &read_00055_len, read_00055_delim, 1);
      if (read_00055_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00055_00000[] = 
         "\x58\x20\x2d\x20\x45\x78\x69\x74\x20\x41\x70\x70\x6c\x69\x63\x61"
         "\x74\x69\x6f\x6e";
      read_00055_ptr += cgc_data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 20);
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** delimited read
      static unsigned char read_00056_delim[] = 
         "\x3a";
      read_00056 = NULL;
      read_00056_len = 0;
      int read_00056_res = cgc_delimited_read(0, &read_00056, &read_00056_len, read_00056_delim, 1);
      if (read_00056_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00056_00000[] = 
         "\x3a";
      read_00056_ptr += cgc_data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 1);
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x70\x0a";
      static unsigned int write_00023_00000_len = 2;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   //*** delay
   cgc_delay(2);
}
