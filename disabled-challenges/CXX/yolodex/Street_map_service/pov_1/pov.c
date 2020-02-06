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
         "\x54\x68\x69\x73\x20\x69\x73\x20\x4d\x61\x70\x70\x65\x72\x2e\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 16);
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
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 8);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 11);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 13);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00002_00000_len = 6;
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
         "\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 1);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 8);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 11);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x31\x0a";
      static unsigned int write_00004_00000_len = 2;
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
         "\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 1);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 13);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
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
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 8);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x42\x0a";
      static unsigned int write_00006_00000_len = 2;
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
         "\x0a";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 1);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 11);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 13);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00008_00000_len = 6;
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
         "\x0a";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 1);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 8);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** delimited read
      static unsigned char read_00011_delim[] = 
         "\x0a";
      read_00011 = NULL;
      read_00011_len = 0;
      int read_00011_res = cgc_delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 1);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 11);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
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
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x0a";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 1);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 13);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00011_00000_len = 6;
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
         "\x0a";
      read_00013 = NULL;
      read_00013_len = 0;
      int read_00013_res = cgc_delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 1);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 8);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** delimited read
      static unsigned char read_00014_delim[] = 
         "\x0a";
      read_00014 = NULL;
      read_00014_len = 0;
      int read_00014_res = cgc_delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 1);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 11);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x0a";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = cgc_delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 1);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 13);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00014_00000_len = 6;
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
         "\x0a";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = cgc_delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 1);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 8);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** delimited read
      static unsigned char read_00017_delim[] = 
         "\x0a";
      read_00017 = NULL;
      read_00017_len = 0;
      int read_00017_res = cgc_delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 1);
      if (read_00017_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00017_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 11);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** delimited read
      static unsigned char read_00018_delim[] = 
         "\x0a";
      read_00018 = NULL;
      read_00018_len = 0;
      int read_00018_res = cgc_delimited_read(0, &read_00018, &read_00018_len, read_00018_delim, 1);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 13);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00017_00000_len = 6;
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
         "\x0a";
      read_00019 = NULL;
      read_00019_len = 0;
      int read_00019_res = cgc_delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 1);
      if (read_00019_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00019_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 8);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** delimited read
      static unsigned char read_00020_delim[] = 
         "\x0a";
      read_00020 = NULL;
      read_00020_len = 0;
      int read_00020_res = cgc_delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 1);
      if (read_00020_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00020_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 11);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 13);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00020_00000_len = 6;
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
         "\x0a";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = cgc_delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 1);
      if (read_00022_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00022_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 8);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 11);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 13);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00023_00000_len = 6;
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
         "\x0a";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = cgc_delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 1);
      if (read_00025_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00025_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 8);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 11);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 13);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00026_00000_len = 6;
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
         "\x0a";
      read_00028 = NULL;
      read_00028_len = 0;
      int read_00028_res = cgc_delimited_read(0, &read_00028, &read_00028_len, read_00028_delim, 1);
      if (read_00028_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00028_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 8);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 11);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** delimited read
      static unsigned char read_00030_delim[] = 
         "\x0a";
      read_00030 = NULL;
      read_00030_len = 0;
      int read_00030_res = cgc_delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 1);
      if (read_00030_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00030_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 13);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00029_00000_len = 6;
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
         "\x0a";
      read_00031 = NULL;
      read_00031_len = 0;
      int read_00031_res = cgc_delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 1);
      if (read_00031_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00031_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 8);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x42\x0a";
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
      //**** read match data
      static unsigned char match_00032_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00032_ptr += cgc_data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 11);
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x31\x0a";
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
      //**** read match data
      static unsigned char match_00033_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00033_ptr += cgc_data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 13);
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00032_00000_len = 6;
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
         "\x0a";
      read_00034 = NULL;
      read_00034_len = 0;
      int read_00034_res = cgc_delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 1);
      if (read_00034_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00034_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00034_ptr += cgc_data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 8);
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x42\x0a";
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
      //**** read match data
      static unsigned char match_00035_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00035_ptr += cgc_data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 11);
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x31\x0a";
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
      //**** read match data
      static unsigned char match_00036_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00036_ptr += cgc_data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 13);
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00035_00000_len = 6;
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
         "\x0a";
      read_00037 = NULL;
      read_00037_len = 0;
      int read_00037_res = cgc_delimited_read(0, &read_00037, &read_00037_len, read_00037_delim, 1);
      if (read_00037_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00037_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 8);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** delimited read
      static unsigned char read_00038_delim[] = 
         "\x0a";
      read_00038 = NULL;
      read_00038_len = 0;
      int read_00038_res = cgc_delimited_read(0, &read_00038, &read_00038_len, read_00038_delim, 1);
      if (read_00038_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00038_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 11);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** delimited read
      static unsigned char read_00039_delim[] = 
         "\x0a";
      read_00039 = NULL;
      read_00039_len = 0;
      int read_00039_res = cgc_delimited_read(0, &read_00039, &read_00039_len, read_00039_delim, 1);
      if (read_00039_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00039_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 13);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00038_00000_len = 6;
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
         "\x0a";
      read_00040 = NULL;
      read_00040_len = 0;
      int read_00040_res = cgc_delimited_read(0, &read_00040, &read_00040_len, read_00040_delim, 1);
      if (read_00040_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00040_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 8);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** delimited read
      static unsigned char read_00041_delim[] = 
         "\x0a";
      read_00041 = NULL;
      read_00041_len = 0;
      int read_00041_res = cgc_delimited_read(0, &read_00041, &read_00041_len, read_00041_delim, 1);
      if (read_00041_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00041_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 11);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** delimited read
      static unsigned char read_00042_delim[] = 
         "\x0a";
      read_00042 = NULL;
      read_00042_len = 0;
      int read_00042_res = cgc_delimited_read(0, &read_00042, &read_00042_len, read_00042_delim, 1);
      if (read_00042_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00042_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 13);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00041_00000_len = 6;
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
         "\x0a";
      read_00043 = NULL;
      read_00043_len = 0;
      int read_00043_res = cgc_delimited_read(0, &read_00043, &read_00043_len, read_00043_delim, 1);
      if (read_00043_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00043_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 8);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** delimited read
      static unsigned char read_00044_delim[] = 
         "\x0a";
      read_00044 = NULL;
      read_00044_len = 0;
      int read_00044_res = cgc_delimited_read(0, &read_00044, &read_00044_len, read_00044_delim, 1);
      if (read_00044_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00044_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 11);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** delimited read
      static unsigned char read_00045_delim[] = 
         "\x0a";
      read_00045 = NULL;
      read_00045_len = 0;
      int read_00045_res = cgc_delimited_read(0, &read_00045, &read_00045_len, read_00045_delim, 1);
      if (read_00045_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00045_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 13);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00044_00000_len = 6;
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
         "\x0a";
      read_00046 = NULL;
      read_00046_len = 0;
      int read_00046_res = cgc_delimited_read(0, &read_00046, &read_00046_len, read_00046_delim, 1);
      if (read_00046_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00046_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 8);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 11);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 13);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00047_00000_len = 6;
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
         "\x0a";
      read_00049 = NULL;
      read_00049_len = 0;
      int read_00049_res = cgc_delimited_read(0, &read_00049, &read_00049_len, read_00049_delim, 1);
      if (read_00049_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00049_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 8);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00050_ptr += cgc_data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 11);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 13);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00050_00000_len = 6;
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
         "\x0a";
      read_00052 = NULL;
      read_00052_len = 0;
      int read_00052_res = cgc_delimited_read(0, &read_00052, &read_00052_len, read_00052_delim, 1);
      if (read_00052_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00052_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 8);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x42\x0a";
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
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 11);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x31\x0a";
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
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00054_ptr += cgc_data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 13);
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00053_00000_len = 6;
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
         "\x0a";
      read_00055 = NULL;
      read_00055_len = 0;
      int read_00055_res = cgc_delimited_read(0, &read_00055, &read_00055_len, read_00055_delim, 1);
      if (read_00055_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00055_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00055_ptr += cgc_data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 8);
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** delimited read
      static unsigned char read_00056_delim[] = 
         "\x0a";
      read_00056 = NULL;
      read_00056_len = 0;
      int read_00056_res = cgc_delimited_read(0, &read_00056, &read_00056_len, read_00056_delim, 1);
      if (read_00056_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00056_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00056_ptr += cgc_data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 11);
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00057;
      unsigned int read_00057_len;
      unsigned int read_00057_ptr = 0;
      //**** delimited read
      static unsigned char read_00057_delim[] = 
         "\x0a";
      read_00057 = NULL;
      read_00057_len = 0;
      int read_00057_res = cgc_delimited_read(0, &read_00057, &read_00057_len, read_00057_delim, 1);
      if (read_00057_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00057_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00057_ptr += cgc_data_match(read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, match_00057_00000, 13);
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00056_00000_len = 6;
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
         "\x0a";
      read_00058 = NULL;
      read_00058_len = 0;
      int read_00058_res = cgc_delimited_read(0, &read_00058, &read_00058_len, read_00058_delim, 1);
      if (read_00058_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00058_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00058_ptr += cgc_data_match(read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, match_00058_00000, 8);
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00059;
      unsigned int read_00059_len;
      unsigned int read_00059_ptr = 0;
      //**** delimited read
      static unsigned char read_00059_delim[] = 
         "\x0a";
      read_00059 = NULL;
      read_00059_len = 0;
      int read_00059_res = cgc_delimited_read(0, &read_00059, &read_00059_len, read_00059_delim, 1);
      if (read_00059_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00059_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00059_ptr += cgc_data_match(read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, match_00059_00000, 11);
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00060;
      unsigned int read_00060_len;
      unsigned int read_00060_ptr = 0;
      //**** delimited read
      static unsigned char read_00060_delim[] = 
         "\x0a";
      read_00060 = NULL;
      read_00060_len = 0;
      int read_00060_res = cgc_delimited_read(0, &read_00060, &read_00060_len, read_00060_delim, 1);
      if (read_00060_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00060_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00060_ptr += cgc_data_match(read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, match_00060_00000, 13);
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00059_00000_len = 6;
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
         "\x0a";
      read_00061 = NULL;
      read_00061_len = 0;
      int read_00061_res = cgc_delimited_read(0, &read_00061, &read_00061_len, read_00061_delim, 1);
      if (read_00061_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00061_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00061_ptr += cgc_data_match(read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, match_00061_00000, 8);
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00062;
      unsigned int read_00062_len;
      unsigned int read_00062_ptr = 0;
      //**** delimited read
      static unsigned char read_00062_delim[] = 
         "\x0a";
      read_00062 = NULL;
      read_00062_len = 0;
      int read_00062_res = cgc_delimited_read(0, &read_00062, &read_00062_len, read_00062_delim, 1);
      if (read_00062_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00062_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00062_ptr += cgc_data_match(read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, match_00062_00000, 11);
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00063;
      unsigned int read_00063_len;
      unsigned int read_00063_ptr = 0;
      //**** delimited read
      static unsigned char read_00063_delim[] = 
         "\x0a";
      read_00063 = NULL;
      read_00063_len = 0;
      int read_00063_res = cgc_delimited_read(0, &read_00063, &read_00063_len, read_00063_delim, 1);
      if (read_00063_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00063_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00063_ptr += cgc_data_match(read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, match_00063_00000, 13);
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00062_00000_len = 6;
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
         "\x0a";
      read_00064 = NULL;
      read_00064_len = 0;
      int read_00064_res = cgc_delimited_read(0, &read_00064, &read_00064_len, read_00064_delim, 1);
      if (read_00064_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00064_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00064_ptr += cgc_data_match(read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, match_00064_00000, 8);
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00065;
      unsigned int read_00065_len;
      unsigned int read_00065_ptr = 0;
      //**** delimited read
      static unsigned char read_00065_delim[] = 
         "\x0a";
      read_00065 = NULL;
      read_00065_len = 0;
      int read_00065_res = cgc_delimited_read(0, &read_00065, &read_00065_len, read_00065_delim, 1);
      if (read_00065_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00065_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00065_ptr += cgc_data_match(read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, match_00065_00000, 11);
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00066;
      unsigned int read_00066_len;
      unsigned int read_00066_ptr = 0;
      //**** delimited read
      static unsigned char read_00066_delim[] = 
         "\x0a";
      read_00066 = NULL;
      read_00066_len = 0;
      int read_00066_res = cgc_delimited_read(0, &read_00066, &read_00066_len, read_00066_delim, 1);
      if (read_00066_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00066_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00066_ptr += cgc_data_match(read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, match_00066_00000, 13);
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00065_00000_len = 6;
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
         "\x0a";
      read_00067 = NULL;
      read_00067_len = 0;
      int read_00067_res = cgc_delimited_read(0, &read_00067, &read_00067_len, read_00067_delim, 1);
      if (read_00067_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00067_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00067_ptr += cgc_data_match(read_00067 + read_00067_ptr, read_00067_len - read_00067_ptr, match_00067_00000, 8);
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00068;
      unsigned int read_00068_len;
      unsigned int read_00068_ptr = 0;
      //**** delimited read
      static unsigned char read_00068_delim[] = 
         "\x0a";
      read_00068 = NULL;
      read_00068_len = 0;
      int read_00068_res = cgc_delimited_read(0, &read_00068, &read_00068_len, read_00068_delim, 1);
      if (read_00068_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00068_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00068_ptr += cgc_data_match(read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, match_00068_00000, 11);
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00069;
      unsigned int read_00069_len;
      unsigned int read_00069_ptr = 0;
      //**** delimited read
      static unsigned char read_00069_delim[] = 
         "\x0a";
      read_00069 = NULL;
      read_00069_len = 0;
      int read_00069_res = cgc_delimited_read(0, &read_00069, &read_00069_len, read_00069_delim, 1);
      if (read_00069_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00069_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00069_ptr += cgc_data_match(read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, match_00069_00000, 13);
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00068_00000_len = 6;
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
         "\x0a";
      read_00070 = NULL;
      read_00070_len = 0;
      int read_00070_res = cgc_delimited_read(0, &read_00070, &read_00070_len, read_00070_delim, 1);
      if (read_00070_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00070_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00070_ptr += cgc_data_match(read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, match_00070_00000, 8);
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00071;
      unsigned int read_00071_len;
      unsigned int read_00071_ptr = 0;
      //**** delimited read
      static unsigned char read_00071_delim[] = 
         "\x0a";
      read_00071 = NULL;
      read_00071_len = 0;
      int read_00071_res = cgc_delimited_read(0, &read_00071, &read_00071_len, read_00071_delim, 1);
      if (read_00071_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00071_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00071_ptr += cgc_data_match(read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, match_00071_00000, 11);
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00072;
      unsigned int read_00072_len;
      unsigned int read_00072_ptr = 0;
      //**** delimited read
      static unsigned char read_00072_delim[] = 
         "\x0a";
      read_00072 = NULL;
      read_00072_len = 0;
      int read_00072_res = cgc_delimited_read(0, &read_00072, &read_00072_len, read_00072_delim, 1);
      if (read_00072_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00072_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00072_ptr += cgc_data_match(read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, match_00072_00000, 13);
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00071_00000_len = 6;
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
         "\x0a";
      read_00073 = NULL;
      read_00073_len = 0;
      int read_00073_res = cgc_delimited_read(0, &read_00073, &read_00073_len, read_00073_delim, 1);
      if (read_00073_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00073_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00073_ptr += cgc_data_match(read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, match_00073_00000, 8);
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00074;
      unsigned int read_00074_len;
      unsigned int read_00074_ptr = 0;
      //**** delimited read
      static unsigned char read_00074_delim[] = 
         "\x0a";
      read_00074 = NULL;
      read_00074_len = 0;
      int read_00074_res = cgc_delimited_read(0, &read_00074, &read_00074_len, read_00074_delim, 1);
      if (read_00074_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00074_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00074_ptr += cgc_data_match(read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, match_00074_00000, 11);
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00075;
      unsigned int read_00075_len;
      unsigned int read_00075_ptr = 0;
      //**** delimited read
      static unsigned char read_00075_delim[] = 
         "\x0a";
      read_00075 = NULL;
      read_00075_len = 0;
      int read_00075_res = cgc_delimited_read(0, &read_00075, &read_00075_len, read_00075_delim, 1);
      if (read_00075_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00075_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00075_ptr += cgc_data_match(read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, match_00075_00000, 13);
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00074_00000_len = 6;
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
         "\x0a";
      read_00076 = NULL;
      read_00076_len = 0;
      int read_00076_res = cgc_delimited_read(0, &read_00076, &read_00076_len, read_00076_delim, 1);
      if (read_00076_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00076_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00076_ptr += cgc_data_match(read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, match_00076_00000, 8);
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00077;
      unsigned int read_00077_len;
      unsigned int read_00077_ptr = 0;
      //**** delimited read
      static unsigned char read_00077_delim[] = 
         "\x0a";
      read_00077 = NULL;
      read_00077_len = 0;
      int read_00077_res = cgc_delimited_read(0, &read_00077, &read_00077_len, read_00077_delim, 1);
      if (read_00077_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00077_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00077_ptr += cgc_data_match(read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, match_00077_00000, 11);
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00078;
      unsigned int read_00078_len;
      unsigned int read_00078_ptr = 0;
      //**** delimited read
      static unsigned char read_00078_delim[] = 
         "\x0a";
      read_00078 = NULL;
      read_00078_len = 0;
      int read_00078_res = cgc_delimited_read(0, &read_00078, &read_00078_len, read_00078_delim, 1);
      if (read_00078_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00078_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00078_ptr += cgc_data_match(read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, match_00078_00000, 13);
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00077_00000_len = 6;
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
         "\x0a";
      read_00079 = NULL;
      read_00079_len = 0;
      int read_00079_res = cgc_delimited_read(0, &read_00079, &read_00079_len, read_00079_delim, 1);
      if (read_00079_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00079_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00079_ptr += cgc_data_match(read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, match_00079_00000, 8);
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00080;
      unsigned int read_00080_len;
      unsigned int read_00080_ptr = 0;
      //**** delimited read
      static unsigned char read_00080_delim[] = 
         "\x0a";
      read_00080 = NULL;
      read_00080_len = 0;
      int read_00080_res = cgc_delimited_read(0, &read_00080, &read_00080_len, read_00080_delim, 1);
      if (read_00080_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00080_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00080_ptr += cgc_data_match(read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, match_00080_00000, 11);
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00081;
      unsigned int read_00081_len;
      unsigned int read_00081_ptr = 0;
      //**** delimited read
      static unsigned char read_00081_delim[] = 
         "\x0a";
      read_00081 = NULL;
      read_00081_len = 0;
      int read_00081_res = cgc_delimited_read(0, &read_00081, &read_00081_len, read_00081_delim, 1);
      if (read_00081_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00081_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00081_ptr += cgc_data_match(read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, match_00081_00000, 13);
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00080_00000_len = 6;
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
         "\x0a";
      read_00082 = NULL;
      read_00082_len = 0;
      int read_00082_res = cgc_delimited_read(0, &read_00082, &read_00082_len, read_00082_delim, 1);
      if (read_00082_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00082_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00082_ptr += cgc_data_match(read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, match_00082_00000, 8);
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00083;
      unsigned int read_00083_len;
      unsigned int read_00083_ptr = 0;
      //**** delimited read
      static unsigned char read_00083_delim[] = 
         "\x0a";
      read_00083 = NULL;
      read_00083_len = 0;
      int read_00083_res = cgc_delimited_read(0, &read_00083, &read_00083_len, read_00083_delim, 1);
      if (read_00083_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00083_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00083_ptr += cgc_data_match(read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, match_00083_00000, 11);
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00084;
      unsigned int read_00084_len;
      unsigned int read_00084_ptr = 0;
      //**** delimited read
      static unsigned char read_00084_delim[] = 
         "\x0a";
      read_00084 = NULL;
      read_00084_len = 0;
      int read_00084_res = cgc_delimited_read(0, &read_00084, &read_00084_len, read_00084_delim, 1);
      if (read_00084_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00084_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00084_ptr += cgc_data_match(read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, match_00084_00000, 13);
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00083_00000_len = 6;
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
         "\x0a";
      read_00085 = NULL;
      read_00085_len = 0;
      int read_00085_res = cgc_delimited_read(0, &read_00085, &read_00085_len, read_00085_delim, 1);
      if (read_00085_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00085_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00085_ptr += cgc_data_match(read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, match_00085_00000, 8);
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00086;
      unsigned int read_00086_len;
      unsigned int read_00086_ptr = 0;
      //**** delimited read
      static unsigned char read_00086_delim[] = 
         "\x0a";
      read_00086 = NULL;
      read_00086_len = 0;
      int read_00086_res = cgc_delimited_read(0, &read_00086, &read_00086_len, read_00086_delim, 1);
      if (read_00086_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00086_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00086_ptr += cgc_data_match(read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, match_00086_00000, 11);
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00087;
      unsigned int read_00087_len;
      unsigned int read_00087_ptr = 0;
      //**** delimited read
      static unsigned char read_00087_delim[] = 
         "\x0a";
      read_00087 = NULL;
      read_00087_len = 0;
      int read_00087_res = cgc_delimited_read(0, &read_00087, &read_00087_len, read_00087_delim, 1);
      if (read_00087_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00087_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00087_ptr += cgc_data_match(read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, match_00087_00000, 13);
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00086_00000_len = 6;
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
         "\x0a";
      read_00088 = NULL;
      read_00088_len = 0;
      int read_00088_res = cgc_delimited_read(0, &read_00088, &read_00088_len, read_00088_delim, 1);
      if (read_00088_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00088_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00088_ptr += cgc_data_match(read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, match_00088_00000, 8);
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00089;
      unsigned int read_00089_len;
      unsigned int read_00089_ptr = 0;
      //**** delimited read
      static unsigned char read_00089_delim[] = 
         "\x0a";
      read_00089 = NULL;
      read_00089_len = 0;
      int read_00089_res = cgc_delimited_read(0, &read_00089, &read_00089_len, read_00089_delim, 1);
      if (read_00089_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00089_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00089_ptr += cgc_data_match(read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, match_00089_00000, 11);
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00090;
      unsigned int read_00090_len;
      unsigned int read_00090_ptr = 0;
      //**** delimited read
      static unsigned char read_00090_delim[] = 
         "\x0a";
      read_00090 = NULL;
      read_00090_len = 0;
      int read_00090_res = cgc_delimited_read(0, &read_00090, &read_00090_len, read_00090_delim, 1);
      if (read_00090_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00090_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00090_ptr += cgc_data_match(read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, match_00090_00000, 13);
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00089_00000_len = 6;
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
         "\x0a";
      read_00091 = NULL;
      read_00091_len = 0;
      int read_00091_res = cgc_delimited_read(0, &read_00091, &read_00091_len, read_00091_delim, 1);
      if (read_00091_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00091_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00091_ptr += cgc_data_match(read_00091 + read_00091_ptr, read_00091_len - read_00091_ptr, match_00091_00000, 8);
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00092;
      unsigned int read_00092_len;
      unsigned int read_00092_ptr = 0;
      //**** delimited read
      static unsigned char read_00092_delim[] = 
         "\x0a";
      read_00092 = NULL;
      read_00092_len = 0;
      int read_00092_res = cgc_delimited_read(0, &read_00092, &read_00092_len, read_00092_delim, 1);
      if (read_00092_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00092_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00092_ptr += cgc_data_match(read_00092 + read_00092_ptr, read_00092_len - read_00092_ptr, match_00092_00000, 11);
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00093;
      unsigned int read_00093_len;
      unsigned int read_00093_ptr = 0;
      //**** delimited read
      static unsigned char read_00093_delim[] = 
         "\x0a";
      read_00093 = NULL;
      read_00093_len = 0;
      int read_00093_res = cgc_delimited_read(0, &read_00093, &read_00093_len, read_00093_delim, 1);
      if (read_00093_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00093_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00093_ptr += cgc_data_match(read_00093 + read_00093_ptr, read_00093_len - read_00093_ptr, match_00093_00000, 13);
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00092_00000_len = 6;
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
         "\x0a";
      read_00094 = NULL;
      read_00094_len = 0;
      int read_00094_res = cgc_delimited_read(0, &read_00094, &read_00094_len, read_00094_delim, 1);
      if (read_00094_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00094_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00094_ptr += cgc_data_match(read_00094 + read_00094_ptr, read_00094_len - read_00094_ptr, match_00094_00000, 8);
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00095;
      unsigned int read_00095_len;
      unsigned int read_00095_ptr = 0;
      //**** delimited read
      static unsigned char read_00095_delim[] = 
         "\x0a";
      read_00095 = NULL;
      read_00095_len = 0;
      int read_00095_res = cgc_delimited_read(0, &read_00095, &read_00095_len, read_00095_delim, 1);
      if (read_00095_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00095_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00095_ptr += cgc_data_match(read_00095 + read_00095_ptr, read_00095_len - read_00095_ptr, match_00095_00000, 11);
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00096;
      unsigned int read_00096_len;
      unsigned int read_00096_ptr = 0;
      //**** delimited read
      static unsigned char read_00096_delim[] = 
         "\x0a";
      read_00096 = NULL;
      read_00096_len = 0;
      int read_00096_res = cgc_delimited_read(0, &read_00096, &read_00096_len, read_00096_delim, 1);
      if (read_00096_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00096_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00096_ptr += cgc_data_match(read_00096 + read_00096_ptr, read_00096_len - read_00096_ptr, match_00096_00000, 13);
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00095_00000_len = 6;
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
         "\x0a";
      read_00097 = NULL;
      read_00097_len = 0;
      int read_00097_res = cgc_delimited_read(0, &read_00097, &read_00097_len, read_00097_delim, 1);
      if (read_00097_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00097_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00097_ptr += cgc_data_match(read_00097 + read_00097_ptr, read_00097_len - read_00097_ptr, match_00097_00000, 8);
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00098;
      unsigned int read_00098_len;
      unsigned int read_00098_ptr = 0;
      //**** delimited read
      static unsigned char read_00098_delim[] = 
         "\x0a";
      read_00098 = NULL;
      read_00098_len = 0;
      int read_00098_res = cgc_delimited_read(0, &read_00098, &read_00098_len, read_00098_delim, 1);
      if (read_00098_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00098_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00098_ptr += cgc_data_match(read_00098 + read_00098_ptr, read_00098_len - read_00098_ptr, match_00098_00000, 11);
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00099;
      unsigned int read_00099_len;
      unsigned int read_00099_ptr = 0;
      //**** delimited read
      static unsigned char read_00099_delim[] = 
         "\x0a";
      read_00099 = NULL;
      read_00099_len = 0;
      int read_00099_res = cgc_delimited_read(0, &read_00099, &read_00099_len, read_00099_delim, 1);
      if (read_00099_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00099_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00099_ptr += cgc_data_match(read_00099 + read_00099_ptr, read_00099_len - read_00099_ptr, match_00099_00000, 13);
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00098_00000_len = 6;
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
         "\x0a";
      read_00100 = NULL;
      read_00100_len = 0;
      int read_00100_res = cgc_delimited_read(0, &read_00100, &read_00100_len, read_00100_delim, 1);
      if (read_00100_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00100_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00100_ptr += cgc_data_match(read_00100 + read_00100_ptr, read_00100_len - read_00100_ptr, match_00100_00000, 8);
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00101;
      unsigned int read_00101_len;
      unsigned int read_00101_ptr = 0;
      //**** delimited read
      static unsigned char read_00101_delim[] = 
         "\x0a";
      read_00101 = NULL;
      read_00101_len = 0;
      int read_00101_res = cgc_delimited_read(0, &read_00101, &read_00101_len, read_00101_delim, 1);
      if (read_00101_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00101_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00101_ptr += cgc_data_match(read_00101 + read_00101_ptr, read_00101_len - read_00101_ptr, match_00101_00000, 11);
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00102;
      unsigned int read_00102_len;
      unsigned int read_00102_ptr = 0;
      //**** delimited read
      static unsigned char read_00102_delim[] = 
         "\x0a";
      read_00102 = NULL;
      read_00102_len = 0;
      int read_00102_res = cgc_delimited_read(0, &read_00102, &read_00102_len, read_00102_delim, 1);
      if (read_00102_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00102_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00102_ptr += cgc_data_match(read_00102 + read_00102_ptr, read_00102_len - read_00102_ptr, match_00102_00000, 13);
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00101_00000_len = 6;
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
         "\x0a";
      read_00103 = NULL;
      read_00103_len = 0;
      int read_00103_res = cgc_delimited_read(0, &read_00103, &read_00103_len, read_00103_delim, 1);
      if (read_00103_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00103_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00103_ptr += cgc_data_match(read_00103 + read_00103_ptr, read_00103_len - read_00103_ptr, match_00103_00000, 8);
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00104;
      unsigned int read_00104_len;
      unsigned int read_00104_ptr = 0;
      //**** delimited read
      static unsigned char read_00104_delim[] = 
         "\x0a";
      read_00104 = NULL;
      read_00104_len = 0;
      int read_00104_res = cgc_delimited_read(0, &read_00104, &read_00104_len, read_00104_delim, 1);
      if (read_00104_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00104_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00104_ptr += cgc_data_match(read_00104 + read_00104_ptr, read_00104_len - read_00104_ptr, match_00104_00000, 11);
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00105;
      unsigned int read_00105_len;
      unsigned int read_00105_ptr = 0;
      //**** delimited read
      static unsigned char read_00105_delim[] = 
         "\x0a";
      read_00105 = NULL;
      read_00105_len = 0;
      int read_00105_res = cgc_delimited_read(0, &read_00105, &read_00105_len, read_00105_delim, 1);
      if (read_00105_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00105_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00105_ptr += cgc_data_match(read_00105 + read_00105_ptr, read_00105_len - read_00105_ptr, match_00105_00000, 13);
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00104_00000_len = 6;
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
         "\x0a";
      read_00106 = NULL;
      read_00106_len = 0;
      int read_00106_res = cgc_delimited_read(0, &read_00106, &read_00106_len, read_00106_delim, 1);
      if (read_00106_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00106_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00106_ptr += cgc_data_match(read_00106 + read_00106_ptr, read_00106_len - read_00106_ptr, match_00106_00000, 8);
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00107;
      unsigned int read_00107_len;
      unsigned int read_00107_ptr = 0;
      //**** delimited read
      static unsigned char read_00107_delim[] = 
         "\x0a";
      read_00107 = NULL;
      read_00107_len = 0;
      int read_00107_res = cgc_delimited_read(0, &read_00107, &read_00107_len, read_00107_delim, 1);
      if (read_00107_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00107_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00107_ptr += cgc_data_match(read_00107 + read_00107_ptr, read_00107_len - read_00107_ptr, match_00107_00000, 11);
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00108;
      unsigned int read_00108_len;
      unsigned int read_00108_ptr = 0;
      //**** delimited read
      static unsigned char read_00108_delim[] = 
         "\x0a";
      read_00108 = NULL;
      read_00108_len = 0;
      int read_00108_res = cgc_delimited_read(0, &read_00108, &read_00108_len, read_00108_delim, 1);
      if (read_00108_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00108_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00108_ptr += cgc_data_match(read_00108 + read_00108_ptr, read_00108_len - read_00108_ptr, match_00108_00000, 13);
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00107_00000_len = 6;
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
         "\x0a";
      read_00109 = NULL;
      read_00109_len = 0;
      int read_00109_res = cgc_delimited_read(0, &read_00109, &read_00109_len, read_00109_delim, 1);
      if (read_00109_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00109_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00109_ptr += cgc_data_match(read_00109 + read_00109_ptr, read_00109_len - read_00109_ptr, match_00109_00000, 8);
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00110;
      unsigned int read_00110_len;
      unsigned int read_00110_ptr = 0;
      //**** delimited read
      static unsigned char read_00110_delim[] = 
         "\x0a";
      read_00110 = NULL;
      read_00110_len = 0;
      int read_00110_res = cgc_delimited_read(0, &read_00110, &read_00110_len, read_00110_delim, 1);
      if (read_00110_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00110_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00110_ptr += cgc_data_match(read_00110 + read_00110_ptr, read_00110_len - read_00110_ptr, match_00110_00000, 11);
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00111;
      unsigned int read_00111_len;
      unsigned int read_00111_ptr = 0;
      //**** delimited read
      static unsigned char read_00111_delim[] = 
         "\x0a";
      read_00111 = NULL;
      read_00111_len = 0;
      int read_00111_res = cgc_delimited_read(0, &read_00111, &read_00111_len, read_00111_delim, 1);
      if (read_00111_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00111_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00111_ptr += cgc_data_match(read_00111 + read_00111_ptr, read_00111_len - read_00111_ptr, match_00111_00000, 13);
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00110_00000_len = 6;
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
         "\x0a";
      read_00112 = NULL;
      read_00112_len = 0;
      int read_00112_res = cgc_delimited_read(0, &read_00112, &read_00112_len, read_00112_delim, 1);
      if (read_00112_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00112_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00112_ptr += cgc_data_match(read_00112 + read_00112_ptr, read_00112_len - read_00112_ptr, match_00112_00000, 8);
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00113;
      unsigned int read_00113_len;
      unsigned int read_00113_ptr = 0;
      //**** delimited read
      static unsigned char read_00113_delim[] = 
         "\x0a";
      read_00113 = NULL;
      read_00113_len = 0;
      int read_00113_res = cgc_delimited_read(0, &read_00113, &read_00113_len, read_00113_delim, 1);
      if (read_00113_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00113_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00113_ptr += cgc_data_match(read_00113 + read_00113_ptr, read_00113_len - read_00113_ptr, match_00113_00000, 11);
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00114;
      unsigned int read_00114_len;
      unsigned int read_00114_ptr = 0;
      //**** delimited read
      static unsigned char read_00114_delim[] = 
         "\x0a";
      read_00114 = NULL;
      read_00114_len = 0;
      int read_00114_res = cgc_delimited_read(0, &read_00114, &read_00114_len, read_00114_delim, 1);
      if (read_00114_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00114_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00114_ptr += cgc_data_match(read_00114 + read_00114_ptr, read_00114_len - read_00114_ptr, match_00114_00000, 13);
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00113_00000_len = 6;
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
         "\x0a";
      read_00115 = NULL;
      read_00115_len = 0;
      int read_00115_res = cgc_delimited_read(0, &read_00115, &read_00115_len, read_00115_delim, 1);
      if (read_00115_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00115_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00115_ptr += cgc_data_match(read_00115 + read_00115_ptr, read_00115_len - read_00115_ptr, match_00115_00000, 8);
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00116;
      unsigned int read_00116_len;
      unsigned int read_00116_ptr = 0;
      //**** delimited read
      static unsigned char read_00116_delim[] = 
         "\x0a";
      read_00116 = NULL;
      read_00116_len = 0;
      int read_00116_res = cgc_delimited_read(0, &read_00116, &read_00116_len, read_00116_delim, 1);
      if (read_00116_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00116_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00116_ptr += cgc_data_match(read_00116 + read_00116_ptr, read_00116_len - read_00116_ptr, match_00116_00000, 11);
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00117;
      unsigned int read_00117_len;
      unsigned int read_00117_ptr = 0;
      //**** delimited read
      static unsigned char read_00117_delim[] = 
         "\x0a";
      read_00117 = NULL;
      read_00117_len = 0;
      int read_00117_res = cgc_delimited_read(0, &read_00117, &read_00117_len, read_00117_delim, 1);
      if (read_00117_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00117_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00117_ptr += cgc_data_match(read_00117 + read_00117_ptr, read_00117_len - read_00117_ptr, match_00117_00000, 13);
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00116_00000_len = 6;
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
         "\x0a";
      read_00118 = NULL;
      read_00118_len = 0;
      int read_00118_res = cgc_delimited_read(0, &read_00118, &read_00118_len, read_00118_delim, 1);
      if (read_00118_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00118_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00118_ptr += cgc_data_match(read_00118 + read_00118_ptr, read_00118_len - read_00118_ptr, match_00118_00000, 8);
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00119;
      unsigned int read_00119_len;
      unsigned int read_00119_ptr = 0;
      //**** delimited read
      static unsigned char read_00119_delim[] = 
         "\x0a";
      read_00119 = NULL;
      read_00119_len = 0;
      int read_00119_res = cgc_delimited_read(0, &read_00119, &read_00119_len, read_00119_delim, 1);
      if (read_00119_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00119_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00119_ptr += cgc_data_match(read_00119 + read_00119_ptr, read_00119_len - read_00119_ptr, match_00119_00000, 11);
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00120;
      unsigned int read_00120_len;
      unsigned int read_00120_ptr = 0;
      //**** delimited read
      static unsigned char read_00120_delim[] = 
         "\x0a";
      read_00120 = NULL;
      read_00120_len = 0;
      int read_00120_res = cgc_delimited_read(0, &read_00120, &read_00120_len, read_00120_delim, 1);
      if (read_00120_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00120_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00120_ptr += cgc_data_match(read_00120 + read_00120_ptr, read_00120_len - read_00120_ptr, match_00120_00000, 13);
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00119_00000_len = 6;
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
         "\x0a";
      read_00121 = NULL;
      read_00121_len = 0;
      int read_00121_res = cgc_delimited_read(0, &read_00121, &read_00121_len, read_00121_delim, 1);
      if (read_00121_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00121_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00121_ptr += cgc_data_match(read_00121 + read_00121_ptr, read_00121_len - read_00121_ptr, match_00121_00000, 8);
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00122;
      unsigned int read_00122_len;
      unsigned int read_00122_ptr = 0;
      //**** delimited read
      static unsigned char read_00122_delim[] = 
         "\x0a";
      read_00122 = NULL;
      read_00122_len = 0;
      int read_00122_res = cgc_delimited_read(0, &read_00122, &read_00122_len, read_00122_delim, 1);
      if (read_00122_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00122_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00122_ptr += cgc_data_match(read_00122 + read_00122_ptr, read_00122_len - read_00122_ptr, match_00122_00000, 11);
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00123;
      unsigned int read_00123_len;
      unsigned int read_00123_ptr = 0;
      //**** delimited read
      static unsigned char read_00123_delim[] = 
         "\x0a";
      read_00123 = NULL;
      read_00123_len = 0;
      int read_00123_res = cgc_delimited_read(0, &read_00123, &read_00123_len, read_00123_delim, 1);
      if (read_00123_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00123_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00123_ptr += cgc_data_match(read_00123 + read_00123_ptr, read_00123_len - read_00123_ptr, match_00123_00000, 13);
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00122_00000_len = 6;
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
         "\x0a";
      read_00124 = NULL;
      read_00124_len = 0;
      int read_00124_res = cgc_delimited_read(0, &read_00124, &read_00124_len, read_00124_delim, 1);
      if (read_00124_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00124_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00124_ptr += cgc_data_match(read_00124 + read_00124_ptr, read_00124_len - read_00124_ptr, match_00124_00000, 8);
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00125;
      unsigned int read_00125_len;
      unsigned int read_00125_ptr = 0;
      //**** delimited read
      static unsigned char read_00125_delim[] = 
         "\x0a";
      read_00125 = NULL;
      read_00125_len = 0;
      int read_00125_res = cgc_delimited_read(0, &read_00125, &read_00125_len, read_00125_delim, 1);
      if (read_00125_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00125_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00125_ptr += cgc_data_match(read_00125 + read_00125_ptr, read_00125_len - read_00125_ptr, match_00125_00000, 11);
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00126;
      unsigned int read_00126_len;
      unsigned int read_00126_ptr = 0;
      //**** delimited read
      static unsigned char read_00126_delim[] = 
         "\x0a";
      read_00126 = NULL;
      read_00126_len = 0;
      int read_00126_res = cgc_delimited_read(0, &read_00126, &read_00126_len, read_00126_delim, 1);
      if (read_00126_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00126_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00126_ptr += cgc_data_match(read_00126 + read_00126_ptr, read_00126_len - read_00126_ptr, match_00126_00000, 13);
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00125_00000_len = 6;
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
         "\x0a";
      read_00127 = NULL;
      read_00127_len = 0;
      int read_00127_res = cgc_delimited_read(0, &read_00127, &read_00127_len, read_00127_delim, 1);
      if (read_00127_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00127_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00127_ptr += cgc_data_match(read_00127 + read_00127_ptr, read_00127_len - read_00127_ptr, match_00127_00000, 8);
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00128;
      unsigned int read_00128_len;
      unsigned int read_00128_ptr = 0;
      //**** delimited read
      static unsigned char read_00128_delim[] = 
         "\x0a";
      read_00128 = NULL;
      read_00128_len = 0;
      int read_00128_res = cgc_delimited_read(0, &read_00128, &read_00128_len, read_00128_delim, 1);
      if (read_00128_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00128_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00128_ptr += cgc_data_match(read_00128 + read_00128_ptr, read_00128_len - read_00128_ptr, match_00128_00000, 11);
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00129;
      unsigned int read_00129_len;
      unsigned int read_00129_ptr = 0;
      //**** delimited read
      static unsigned char read_00129_delim[] = 
         "\x0a";
      read_00129 = NULL;
      read_00129_len = 0;
      int read_00129_res = cgc_delimited_read(0, &read_00129, &read_00129_len, read_00129_delim, 1);
      if (read_00129_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00129_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00129_ptr += cgc_data_match(read_00129 + read_00129_ptr, read_00129_len - read_00129_ptr, match_00129_00000, 13);
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00128_00000_len = 6;
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
         "\x0a";
      read_00130 = NULL;
      read_00130_len = 0;
      int read_00130_res = cgc_delimited_read(0, &read_00130, &read_00130_len, read_00130_delim, 1);
      if (read_00130_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00130_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00130_ptr += cgc_data_match(read_00130 + read_00130_ptr, read_00130_len - read_00130_ptr, match_00130_00000, 8);
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00131;
      unsigned int read_00131_len;
      unsigned int read_00131_ptr = 0;
      //**** delimited read
      static unsigned char read_00131_delim[] = 
         "\x0a";
      read_00131 = NULL;
      read_00131_len = 0;
      int read_00131_res = cgc_delimited_read(0, &read_00131, &read_00131_len, read_00131_delim, 1);
      if (read_00131_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00131_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00131_ptr += cgc_data_match(read_00131 + read_00131_ptr, read_00131_len - read_00131_ptr, match_00131_00000, 11);
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00132;
      unsigned int read_00132_len;
      unsigned int read_00132_ptr = 0;
      //**** delimited read
      static unsigned char read_00132_delim[] = 
         "\x0a";
      read_00132 = NULL;
      read_00132_len = 0;
      int read_00132_res = cgc_delimited_read(0, &read_00132, &read_00132_len, read_00132_delim, 1);
      if (read_00132_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00132_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00132_ptr += cgc_data_match(read_00132 + read_00132_ptr, read_00132_len - read_00132_ptr, match_00132_00000, 13);
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00131_00000_len = 6;
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
         "\x0a";
      read_00133 = NULL;
      read_00133_len = 0;
      int read_00133_res = cgc_delimited_read(0, &read_00133, &read_00133_len, read_00133_delim, 1);
      if (read_00133_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00133_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00133_ptr += cgc_data_match(read_00133 + read_00133_ptr, read_00133_len - read_00133_ptr, match_00133_00000, 8);
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x42\x0a";
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
      unsigned char *read_00134;
      unsigned int read_00134_len;
      unsigned int read_00134_ptr = 0;
      //**** delimited read
      static unsigned char read_00134_delim[] = 
         "\x0a";
      read_00134 = NULL;
      read_00134_len = 0;
      int read_00134_res = cgc_delimited_read(0, &read_00134, &read_00134_len, read_00134_delim, 1);
      if (read_00134_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00134_00000[] = 
         "\x52\x6f\x61\x64\x20\x4e\x61\x6d\x65\x3a\x0a";
      read_00134_ptr += cgc_data_match(read_00134 + read_00134_ptr, read_00134_len - read_00134_ptr, match_00134_00000, 11);
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00135;
      unsigned int read_00135_len;
      unsigned int read_00135_ptr = 0;
      //**** delimited read
      static unsigned char read_00135_delim[] = 
         "\x0a";
      read_00135 = NULL;
      read_00135_len = 0;
      int read_00135_res = cgc_delimited_read(0, &read_00135, &read_00135_len, read_00135_delim, 1);
      if (read_00135_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00135_00000[] = 
         "\x52\x6f\x61\x64\x20\x4c\x65\x6e\x67\x74\x68\x3a\x0a";
      read_00135_ptr += cgc_data_match(read_00135 + read_00135_ptr, read_00135_len - read_00135_ptr, match_00135_00000, 13);
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x34\x32\x33\x34\x32\x0a";
      static unsigned int write_00134_00000_len = 6;
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
         "\x0a";
      read_00136 = NULL;
      read_00136_len = 0;
      int read_00136_res = cgc_delimited_read(0, &read_00136, &read_00136_len, read_00136_delim, 1);
      if (read_00136_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00136_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00136_ptr += cgc_data_match(read_00136 + read_00136_ptr, read_00136_len - read_00136_ptr, match_00136_00000, 8);
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x43\x0a";
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
      unsigned char *read_00137;
      unsigned int read_00137_len;
      unsigned int read_00137_ptr = 0;
      //**** delimited read
      static unsigned char read_00137_delim[] = 
         "\x0a";
      read_00137 = NULL;
      read_00137_len = 0;
      int read_00137_res = cgc_delimited_read(0, &read_00137, &read_00137_len, read_00137_delim, 1);
      if (read_00137_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00137_00000[] = 
         "\x53\x74\x72\x65\x65\x74\x20\x4e\x75\x6d\x62\x65\x72\x3a\x20\x0a";
      read_00137_ptr += cgc_data_match(read_00137 + read_00137_ptr, read_00137_len - read_00137_ptr, match_00137_00000, 16);
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x31\x32\x33\x0a";
      static unsigned int write_00136_00000_len = 4;
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
         "\x0a";
      read_00138 = NULL;
      read_00138_len = 0;
      int read_00138_res = cgc_delimited_read(0, &read_00138, &read_00138_len, read_00138_delim, 1);
      if (read_00138_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00138_00000[] = 
         "\x52\x65\x73\x69\x64\x65\x6e\x74\x3a\x20\x0a";
      read_00138_ptr += cgc_data_match(read_00138 + read_00138_ptr, read_00138_len - read_00138_ptr, match_00138_00000, 11);
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x62\x6f\x62\x0a";
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
      unsigned char *read_00139;
      unsigned int read_00139_len;
      unsigned int read_00139_ptr = 0;
      //**** delimited read
      static unsigned char read_00139_delim[] = 
         "\x0a";
      read_00139 = NULL;
      read_00139_len = 0;
      int read_00139_res = cgc_delimited_read(0, &read_00139, &read_00139_len, read_00139_delim, 1);
      if (read_00139_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00139_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00139_ptr += cgc_data_match(read_00139 + read_00139_ptr, read_00139_len - read_00139_ptr, match_00139_00000, 47);
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00140;
      unsigned int read_00140_len;
      unsigned int read_00140_ptr = 0;
      //**** delimited read
      static unsigned char read_00140_delim[] = 
         "\x0a";
      read_00140 = NULL;
      read_00140_len = 0;
      int read_00140_res = cgc_delimited_read(0, &read_00140, &read_00140_len, read_00140_delim, 1);
      if (read_00140_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00140_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00140_ptr += cgc_data_match(read_00140 + read_00140_ptr, read_00140_len - read_00140_ptr, match_00140_00000, 8);
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x4e\x0a";
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
      unsigned char *read_00141;
      unsigned int read_00141_len;
      unsigned int read_00141_ptr = 0;
      //**** delimited read
      static unsigned char read_00141_delim[] = 
         "\x0a";
      read_00141 = NULL;
      read_00141_len = 0;
      int read_00141_res = cgc_delimited_read(0, &read_00141, &read_00141_len, read_00141_delim, 1);
      if (read_00141_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00141_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00141_ptr += cgc_data_match(read_00141 + read_00141_ptr, read_00141_len - read_00141_ptr, match_00141_00000, 6);
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x31\x0a";
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
      unsigned char *read_00142;
      unsigned int read_00142_len;
      unsigned int read_00142_ptr = 0;
      //**** delimited read
      static unsigned char read_00142_delim[] = 
         "\x0a";
      read_00142 = NULL;
      read_00142_len = 0;
      int read_00142_res = cgc_delimited_read(0, &read_00142, &read_00142_len, read_00142_delim, 1);
      if (read_00142_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00142_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00142_ptr += cgc_data_match(read_00142 + read_00142_ptr, read_00142_len - read_00142_ptr, match_00142_00000, 42);
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00143;
      unsigned int read_00143_len;
      unsigned int read_00143_ptr = 0;
      //**** delimited read
      static unsigned char read_00143_delim[] = 
         "\x0a";
      read_00143 = NULL;
      read_00143_len = 0;
      int read_00143_res = cgc_delimited_read(0, &read_00143, &read_00143_len, read_00143_delim, 1);
      if (read_00143_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00143_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00143_ptr += cgc_data_match(read_00143 + read_00143_ptr, read_00143_len - read_00143_ptr, match_00143_00000, 42);
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00144;
      unsigned int read_00144_len;
      unsigned int read_00144_ptr = 0;
      //**** delimited read
      static unsigned char read_00144_delim[] = 
         "\x0a";
      read_00144 = NULL;
      read_00144_len = 0;
      int read_00144_res = cgc_delimited_read(0, &read_00144, &read_00144_len, read_00144_delim, 1);
      if (read_00144_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00144_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00144_ptr += cgc_data_match(read_00144 + read_00144_ptr, read_00144_len - read_00144_ptr, match_00144_00000, 8);
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x43\x0a";
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
      unsigned char *read_00145;
      unsigned int read_00145_len;
      unsigned int read_00145_ptr = 0;
      //**** delimited read
      static unsigned char read_00145_delim[] = 
         "\x0a";
      read_00145 = NULL;
      read_00145_len = 0;
      int read_00145_res = cgc_delimited_read(0, &read_00145, &read_00145_len, read_00145_delim, 1);
      if (read_00145_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00145_00000[] = 
         "\x53\x74\x72\x65\x65\x74\x20\x4e\x75\x6d\x62\x65\x72\x3a\x20\x0a";
      read_00145_ptr += cgc_data_match(read_00145 + read_00145_ptr, read_00145_len - read_00145_ptr, match_00145_00000, 16);
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x31\x32\x33\x0a";
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
      unsigned char *read_00146;
      unsigned int read_00146_len;
      unsigned int read_00146_ptr = 0;
      //**** delimited read
      static unsigned char read_00146_delim[] = 
         "\x0a";
      read_00146 = NULL;
      read_00146_len = 0;
      int read_00146_res = cgc_delimited_read(0, &read_00146, &read_00146_len, read_00146_delim, 1);
      if (read_00146_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00146_00000[] = 
         "\x52\x65\x73\x69\x64\x65\x6e\x74\x3a\x20\x0a";
      read_00146_ptr += cgc_data_match(read_00146 + read_00146_ptr, read_00146_len - read_00146_ptr, match_00146_00000, 11);
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x62\x6f\x62\x0a";
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
      unsigned char *read_00147;
      unsigned int read_00147_len;
      unsigned int read_00147_ptr = 0;
      //**** delimited read
      static unsigned char read_00147_delim[] = 
         "\x0a";
      read_00147 = NULL;
      read_00147_len = 0;
      int read_00147_res = cgc_delimited_read(0, &read_00147, &read_00147_len, read_00147_delim, 1);
      if (read_00147_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00147_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00147_ptr += cgc_data_match(read_00147 + read_00147_ptr, read_00147_len - read_00147_ptr, match_00147_00000, 47);
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00148;
      unsigned int read_00148_len;
      unsigned int read_00148_ptr = 0;
      //**** delimited read
      static unsigned char read_00148_delim[] = 
         "\x0a";
      read_00148 = NULL;
      read_00148_len = 0;
      int read_00148_res = cgc_delimited_read(0, &read_00148, &read_00148_len, read_00148_delim, 1);
      if (read_00148_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00148_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00148_ptr += cgc_data_match(read_00148 + read_00148_ptr, read_00148_len - read_00148_ptr, match_00148_00000, 8);
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00143_00000_len = 2;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = cgc_append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         cgc_transmit_all(1, write_00143, write_00143_len);
      }
      cgc_free(write_00143);
   } while (0);
   do {
      unsigned char *read_00149;
      unsigned int read_00149_len;
      unsigned int read_00149_ptr = 0;
      //**** delimited read
      static unsigned char read_00149_delim[] = 
         "\x0a";
      read_00149 = NULL;
      read_00149_len = 0;
      int read_00149_res = cgc_delimited_read(0, &read_00149, &read_00149_len, read_00149_delim, 1);
      if (read_00149_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00149_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00149_ptr += cgc_data_match(read_00149 + read_00149_ptr, read_00149_len - read_00149_ptr, match_00149_00000, 6);
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x33\x34\x0a";
      static unsigned int write_00144_00000_len = 3;
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = cgc_append_buf(write_00144, &write_00144_len, write_00144_00000, write_00144_00000_len);
      if (write_00144_len > 0) {
         cgc_transmit_all(1, write_00144, write_00144_len);
      }
      cgc_free(write_00144);
   } while (0);
   do {
      unsigned char *read_00150;
      unsigned int read_00150_len;
      unsigned int read_00150_ptr = 0;
      //**** delimited read
      static unsigned char read_00150_delim[] = 
         "\x0a";
      read_00150 = NULL;
      read_00150_len = 0;
      int read_00150_res = cgc_delimited_read(0, &read_00150, &read_00150_len, read_00150_delim, 1);
      if (read_00150_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00150_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00150_ptr += cgc_data_match(read_00150 + read_00150_ptr, read_00150_len - read_00150_ptr, match_00150_00000, 42);
      cgc_free(read_00150);
      if (read_00150_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00151;
      unsigned int read_00151_len;
      unsigned int read_00151_ptr = 0;
      //**** delimited read
      static unsigned char read_00151_delim[] = 
         "\x0a";
      read_00151 = NULL;
      read_00151_len = 0;
      int read_00151_res = cgc_delimited_read(0, &read_00151, &read_00151_len, read_00151_delim, 1);
      if (read_00151_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00151_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00151_ptr += cgc_data_match(read_00151 + read_00151_ptr, read_00151_len - read_00151_ptr, match_00151_00000, 42);
      cgc_free(read_00151);
      if (read_00151_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00152;
      unsigned int read_00152_len;
      unsigned int read_00152_ptr = 0;
      //**** delimited read
      static unsigned char read_00152_delim[] = 
         "\x0a";
      read_00152 = NULL;
      read_00152_len = 0;
      int read_00152_res = cgc_delimited_read(0, &read_00152, &read_00152_len, read_00152_delim, 1);
      if (read_00152_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00152_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00152_ptr += cgc_data_match(read_00152 + read_00152_ptr, read_00152_len - read_00152_ptr, match_00152_00000, 8);
      cgc_free(read_00152);
      if (read_00152_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x44\x0a";
      static unsigned int write_00145_00000_len = 2;
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
         "\x0a";
      read_00153 = NULL;
      read_00153_len = 0;
      int read_00153_res = cgc_delimited_read(0, &read_00153, &read_00153_len, read_00153_delim, 1);
      if (read_00153_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00153_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00153_ptr += cgc_data_match(read_00153 + read_00153_ptr, read_00153_len - read_00153_ptr, match_00153_00000, 47);
      cgc_free(read_00153);
      if (read_00153_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00154;
      unsigned int read_00154_len;
      unsigned int read_00154_ptr = 0;
      //**** delimited read
      static unsigned char read_00154_delim[] = 
         "\x0a";
      read_00154 = NULL;
      read_00154_len = 0;
      int read_00154_res = cgc_delimited_read(0, &read_00154, &read_00154_len, read_00154_delim, 1);
      if (read_00154_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00154_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00154_ptr += cgc_data_match(read_00154 + read_00154_ptr, read_00154_len - read_00154_ptr, match_00154_00000, 8);
      cgc_free(read_00154);
      if (read_00154_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00146_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00146_00000_len = 2;
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = cgc_append_buf(write_00146, &write_00146_len, write_00146_00000, write_00146_00000_len);
      if (write_00146_len > 0) {
         cgc_transmit_all(1, write_00146, write_00146_len);
      }
      cgc_free(write_00146);
   } while (0);
   do {
      unsigned char *read_00155;
      unsigned int read_00155_len;
      unsigned int read_00155_ptr = 0;
      //**** delimited read
      static unsigned char read_00155_delim[] = 
         "\x0a";
      read_00155 = NULL;
      read_00155_len = 0;
      int read_00155_res = cgc_delimited_read(0, &read_00155, &read_00155_len, read_00155_delim, 1);
      if (read_00155_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00155_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00155_ptr += cgc_data_match(read_00155 + read_00155_ptr, read_00155_len - read_00155_ptr, match_00155_00000, 6);
      cgc_free(read_00155);
      if (read_00155_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x31\x0a";
      static unsigned int write_00147_00000_len = 2;
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = cgc_append_buf(write_00147, &write_00147_len, write_00147_00000, write_00147_00000_len);
      if (write_00147_len > 0) {
         cgc_transmit_all(1, write_00147, write_00147_len);
      }
      cgc_free(write_00147);
   } while (0);
   do {
      unsigned char *read_00156;
      unsigned int read_00156_len;
      unsigned int read_00156_ptr = 0;
      //**** delimited read
      static unsigned char read_00156_delim[] = 
         "\x0a";
      read_00156 = NULL;
      read_00156_len = 0;
      int read_00156_res = cgc_delimited_read(0, &read_00156, &read_00156_len, read_00156_delim, 1);
      if (read_00156_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00156_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00156_ptr += cgc_data_match(read_00156 + read_00156_ptr, read_00156_len - read_00156_ptr, match_00156_00000, 47);
      cgc_free(read_00156);
      if (read_00156_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00157;
      unsigned int read_00157_len;
      unsigned int read_00157_ptr = 0;
      //**** delimited read
      static unsigned char read_00157_delim[] = 
         "\x0a";
      read_00157 = NULL;
      read_00157_len = 0;
      int read_00157_res = cgc_delimited_read(0, &read_00157, &read_00157_len, read_00157_delim, 1);
      if (read_00157_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00157_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00157_ptr += cgc_data_match(read_00157 + read_00157_ptr, read_00157_len - read_00157_ptr, match_00157_00000, 8);
      cgc_free(read_00157);
      if (read_00157_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00148_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00148_00000_len = 2;
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = cgc_append_buf(write_00148, &write_00148_len, write_00148_00000, write_00148_00000_len);
      if (write_00148_len > 0) {
         cgc_transmit_all(1, write_00148, write_00148_len);
      }
      cgc_free(write_00148);
   } while (0);
   do {
      unsigned char *read_00158;
      unsigned int read_00158_len;
      unsigned int read_00158_ptr = 0;
      //**** delimited read
      static unsigned char read_00158_delim[] = 
         "\x0a";
      read_00158 = NULL;
      read_00158_len = 0;
      int read_00158_res = cgc_delimited_read(0, &read_00158, &read_00158_len, read_00158_delim, 1);
      if (read_00158_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00158_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00158_ptr += cgc_data_match(read_00158 + read_00158_ptr, read_00158_len - read_00158_ptr, match_00158_00000, 6);
      cgc_free(read_00158);
      if (read_00158_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x32\x0a";
      static unsigned int write_00149_00000_len = 2;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = cgc_append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         cgc_transmit_all(1, write_00149, write_00149_len);
      }
      cgc_free(write_00149);
   } while (0);
   do {
      unsigned char *read_00159;
      unsigned int read_00159_len;
      unsigned int read_00159_ptr = 0;
      //**** delimited read
      static unsigned char read_00159_delim[] = 
         "\x0a";
      read_00159 = NULL;
      read_00159_len = 0;
      int read_00159_res = cgc_delimited_read(0, &read_00159, &read_00159_len, read_00159_delim, 1);
      if (read_00159_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00159_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00159_ptr += cgc_data_match(read_00159 + read_00159_ptr, read_00159_len - read_00159_ptr, match_00159_00000, 29);
      cgc_free(read_00159);
      if (read_00159_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00160;
      unsigned int read_00160_len;
      unsigned int read_00160_ptr = 0;
      //**** delimited read
      static unsigned char read_00160_delim[] = 
         "\x0a";
      read_00160 = NULL;
      read_00160_len = 0;
      int read_00160_res = cgc_delimited_read(0, &read_00160, &read_00160_len, read_00160_delim, 1);
      if (read_00160_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00160_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00160_ptr += cgc_data_match(read_00160 + read_00160_ptr, read_00160_len - read_00160_ptr, match_00160_00000, 42);
      cgc_free(read_00160);
      if (read_00160_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00161;
      unsigned int read_00161_len;
      unsigned int read_00161_ptr = 0;
      //**** delimited read
      static unsigned char read_00161_delim[] = 
         "\x0a";
      read_00161 = NULL;
      read_00161_len = 0;
      int read_00161_res = cgc_delimited_read(0, &read_00161, &read_00161_len, read_00161_delim, 1);
      if (read_00161_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00161_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00161_ptr += cgc_data_match(read_00161 + read_00161_ptr, read_00161_len - read_00161_ptr, match_00161_00000, 29);
      cgc_free(read_00161);
      if (read_00161_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00162;
      unsigned int read_00162_len;
      unsigned int read_00162_ptr = 0;
      //**** delimited read
      static unsigned char read_00162_delim[] = 
         "\x0a";
      read_00162 = NULL;
      read_00162_len = 0;
      int read_00162_res = cgc_delimited_read(0, &read_00162, &read_00162_len, read_00162_delim, 1);
      if (read_00162_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00162_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00162_ptr += cgc_data_match(read_00162 + read_00162_ptr, read_00162_len - read_00162_ptr, match_00162_00000, 42);
      cgc_free(read_00162);
      if (read_00162_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00163;
      unsigned int read_00163_len;
      unsigned int read_00163_ptr = 0;
      //**** delimited read
      static unsigned char read_00163_delim[] = 
         "\x0a";
      read_00163 = NULL;
      read_00163_len = 0;
      int read_00163_res = cgc_delimited_read(0, &read_00163, &read_00163_len, read_00163_delim, 1);
      if (read_00163_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00163_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00163_ptr += cgc_data_match(read_00163 + read_00163_ptr, read_00163_len - read_00163_ptr, match_00163_00000, 8);
      cgc_free(read_00163);
      if (read_00163_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00150_00000[] = 
         "\x44\x0a";
      static unsigned int write_00150_00000_len = 2;
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = cgc_append_buf(write_00150, &write_00150_len, write_00150_00000, write_00150_00000_len);
      if (write_00150_len > 0) {
         cgc_transmit_all(1, write_00150, write_00150_len);
      }
      cgc_free(write_00150);
   } while (0);
   do {
      unsigned char *read_00164;
      unsigned int read_00164_len;
      unsigned int read_00164_ptr = 0;
      //**** delimited read
      static unsigned char read_00164_delim[] = 
         "\x0a";
      read_00164 = NULL;
      read_00164_len = 0;
      int read_00164_res = cgc_delimited_read(0, &read_00164, &read_00164_len, read_00164_delim, 1);
      if (read_00164_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00164_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00164_ptr += cgc_data_match(read_00164 + read_00164_ptr, read_00164_len - read_00164_ptr, match_00164_00000, 47);
      cgc_free(read_00164);
      if (read_00164_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00165;
      unsigned int read_00165_len;
      unsigned int read_00165_ptr = 0;
      //**** delimited read
      static unsigned char read_00165_delim[] = 
         "\x0a";
      read_00165 = NULL;
      read_00165_len = 0;
      int read_00165_res = cgc_delimited_read(0, &read_00165, &read_00165_len, read_00165_delim, 1);
      if (read_00165_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00165_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00165_ptr += cgc_data_match(read_00165 + read_00165_ptr, read_00165_len - read_00165_ptr, match_00165_00000, 8);
      cgc_free(read_00165);
      if (read_00165_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00151_00000_len = 2;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = cgc_append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         cgc_transmit_all(1, write_00151, write_00151_len);
      }
      cgc_free(write_00151);
   } while (0);
   do {
      unsigned char *read_00166;
      unsigned int read_00166_len;
      unsigned int read_00166_ptr = 0;
      //**** delimited read
      static unsigned char read_00166_delim[] = 
         "\x0a";
      read_00166 = NULL;
      read_00166_len = 0;
      int read_00166_res = cgc_delimited_read(0, &read_00166, &read_00166_len, read_00166_delim, 1);
      if (read_00166_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00166_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00166_ptr += cgc_data_match(read_00166 + read_00166_ptr, read_00166_len - read_00166_ptr, match_00166_00000, 6);
      cgc_free(read_00166);
      if (read_00166_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00152_00000[] = 
         "\x33\x0a";
      static unsigned int write_00152_00000_len = 2;
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = cgc_append_buf(write_00152, &write_00152_len, write_00152_00000, write_00152_00000_len);
      if (write_00152_len > 0) {
         cgc_transmit_all(1, write_00152, write_00152_len);
      }
      cgc_free(write_00152);
   } while (0);
   do {
      unsigned char *read_00167;
      unsigned int read_00167_len;
      unsigned int read_00167_ptr = 0;
      //**** delimited read
      static unsigned char read_00167_delim[] = 
         "\x0a";
      read_00167 = NULL;
      read_00167_len = 0;
      int read_00167_res = cgc_delimited_read(0, &read_00167, &read_00167_len, read_00167_delim, 1);
      if (read_00167_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00167_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00167_ptr += cgc_data_match(read_00167 + read_00167_ptr, read_00167_len - read_00167_ptr, match_00167_00000, 47);
      cgc_free(read_00167);
      if (read_00167_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00168;
      unsigned int read_00168_len;
      unsigned int read_00168_ptr = 0;
      //**** delimited read
      static unsigned char read_00168_delim[] = 
         "\x0a";
      read_00168 = NULL;
      read_00168_len = 0;
      int read_00168_res = cgc_delimited_read(0, &read_00168, &read_00168_len, read_00168_delim, 1);
      if (read_00168_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00168_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00168_ptr += cgc_data_match(read_00168 + read_00168_ptr, read_00168_len - read_00168_ptr, match_00168_00000, 8);
      cgc_free(read_00168);
      if (read_00168_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00153_00000_len = 2;
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = cgc_append_buf(write_00153, &write_00153_len, write_00153_00000, write_00153_00000_len);
      if (write_00153_len > 0) {
         cgc_transmit_all(1, write_00153, write_00153_len);
      }
      cgc_free(write_00153);
   } while (0);
   do {
      unsigned char *read_00169;
      unsigned int read_00169_len;
      unsigned int read_00169_ptr = 0;
      //**** delimited read
      static unsigned char read_00169_delim[] = 
         "\x0a";
      read_00169 = NULL;
      read_00169_len = 0;
      int read_00169_res = cgc_delimited_read(0, &read_00169, &read_00169_len, read_00169_delim, 1);
      if (read_00169_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00169_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00169_ptr += cgc_data_match(read_00169 + read_00169_ptr, read_00169_len - read_00169_ptr, match_00169_00000, 6);
      cgc_free(read_00169);
      if (read_00169_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00154_00000[] = 
         "\x34\x0a";
      static unsigned int write_00154_00000_len = 2;
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = cgc_append_buf(write_00154, &write_00154_len, write_00154_00000, write_00154_00000_len);
      if (write_00154_len > 0) {
         cgc_transmit_all(1, write_00154, write_00154_len);
      }
      cgc_free(write_00154);
   } while (0);
   do {
      unsigned char *read_00170;
      unsigned int read_00170_len;
      unsigned int read_00170_ptr = 0;
      //**** delimited read
      static unsigned char read_00170_delim[] = 
         "\x0a";
      read_00170 = NULL;
      read_00170_len = 0;
      int read_00170_res = cgc_delimited_read(0, &read_00170, &read_00170_len, read_00170_delim, 1);
      if (read_00170_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00170_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00170_ptr += cgc_data_match(read_00170 + read_00170_ptr, read_00170_len - read_00170_ptr, match_00170_00000, 29);
      cgc_free(read_00170);
      if (read_00170_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00171;
      unsigned int read_00171_len;
      unsigned int read_00171_ptr = 0;
      //**** delimited read
      static unsigned char read_00171_delim[] = 
         "\x0a";
      read_00171 = NULL;
      read_00171_len = 0;
      int read_00171_res = cgc_delimited_read(0, &read_00171, &read_00171_len, read_00171_delim, 1);
      if (read_00171_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00171_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00171_ptr += cgc_data_match(read_00171 + read_00171_ptr, read_00171_len - read_00171_ptr, match_00171_00000, 42);
      cgc_free(read_00171);
      if (read_00171_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00172;
      unsigned int read_00172_len;
      unsigned int read_00172_ptr = 0;
      //**** delimited read
      static unsigned char read_00172_delim[] = 
         "\x0a";
      read_00172 = NULL;
      read_00172_len = 0;
      int read_00172_res = cgc_delimited_read(0, &read_00172, &read_00172_len, read_00172_delim, 1);
      if (read_00172_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00172_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00172_ptr += cgc_data_match(read_00172 + read_00172_ptr, read_00172_len - read_00172_ptr, match_00172_00000, 29);
      cgc_free(read_00172);
      if (read_00172_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00173;
      unsigned int read_00173_len;
      unsigned int read_00173_ptr = 0;
      //**** delimited read
      static unsigned char read_00173_delim[] = 
         "\x0a";
      read_00173 = NULL;
      read_00173_len = 0;
      int read_00173_res = cgc_delimited_read(0, &read_00173, &read_00173_len, read_00173_delim, 1);
      if (read_00173_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00173_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00173_ptr += cgc_data_match(read_00173 + read_00173_ptr, read_00173_len - read_00173_ptr, match_00173_00000, 42);
      cgc_free(read_00173);
      if (read_00173_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00174;
      unsigned int read_00174_len;
      unsigned int read_00174_ptr = 0;
      //**** delimited read
      static unsigned char read_00174_delim[] = 
         "\x0a";
      read_00174 = NULL;
      read_00174_len = 0;
      int read_00174_res = cgc_delimited_read(0, &read_00174, &read_00174_len, read_00174_delim, 1);
      if (read_00174_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00174_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00174_ptr += cgc_data_match(read_00174 + read_00174_ptr, read_00174_len - read_00174_ptr, match_00174_00000, 8);
      cgc_free(read_00174);
      if (read_00174_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x44\x0a";
      static unsigned int write_00155_00000_len = 2;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = cgc_append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         cgc_transmit_all(1, write_00155, write_00155_len);
      }
      cgc_free(write_00155);
   } while (0);
   do {
      unsigned char *read_00175;
      unsigned int read_00175_len;
      unsigned int read_00175_ptr = 0;
      //**** delimited read
      static unsigned char read_00175_delim[] = 
         "\x0a";
      read_00175 = NULL;
      read_00175_len = 0;
      int read_00175_res = cgc_delimited_read(0, &read_00175, &read_00175_len, read_00175_delim, 1);
      if (read_00175_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00175_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00175_ptr += cgc_data_match(read_00175 + read_00175_ptr, read_00175_len - read_00175_ptr, match_00175_00000, 47);
      cgc_free(read_00175);
      if (read_00175_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00176;
      unsigned int read_00176_len;
      unsigned int read_00176_ptr = 0;
      //**** delimited read
      static unsigned char read_00176_delim[] = 
         "\x0a";
      read_00176 = NULL;
      read_00176_len = 0;
      int read_00176_res = cgc_delimited_read(0, &read_00176, &read_00176_len, read_00176_delim, 1);
      if (read_00176_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00176_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00176_ptr += cgc_data_match(read_00176 + read_00176_ptr, read_00176_len - read_00176_ptr, match_00176_00000, 8);
      cgc_free(read_00176);
      if (read_00176_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00156_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00156_00000_len = 2;
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = cgc_append_buf(write_00156, &write_00156_len, write_00156_00000, write_00156_00000_len);
      if (write_00156_len > 0) {
         cgc_transmit_all(1, write_00156, write_00156_len);
      }
      cgc_free(write_00156);
   } while (0);
   do {
      unsigned char *read_00177;
      unsigned int read_00177_len;
      unsigned int read_00177_ptr = 0;
      //**** delimited read
      static unsigned char read_00177_delim[] = 
         "\x0a";
      read_00177 = NULL;
      read_00177_len = 0;
      int read_00177_res = cgc_delimited_read(0, &read_00177, &read_00177_len, read_00177_delim, 1);
      if (read_00177_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00177_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00177_ptr += cgc_data_match(read_00177 + read_00177_ptr, read_00177_len - read_00177_ptr, match_00177_00000, 6);
      cgc_free(read_00177);
      if (read_00177_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x35\x0a";
      static unsigned int write_00157_00000_len = 2;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = cgc_append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         cgc_transmit_all(1, write_00157, write_00157_len);
      }
      cgc_free(write_00157);
   } while (0);
   do {
      unsigned char *read_00178;
      unsigned int read_00178_len;
      unsigned int read_00178_ptr = 0;
      //**** delimited read
      static unsigned char read_00178_delim[] = 
         "\x0a";
      read_00178 = NULL;
      read_00178_len = 0;
      int read_00178_res = cgc_delimited_read(0, &read_00178, &read_00178_len, read_00178_delim, 1);
      if (read_00178_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00178_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00178_ptr += cgc_data_match(read_00178 + read_00178_ptr, read_00178_len - read_00178_ptr, match_00178_00000, 47);
      cgc_free(read_00178);
      if (read_00178_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00179;
      unsigned int read_00179_len;
      unsigned int read_00179_ptr = 0;
      //**** delimited read
      static unsigned char read_00179_delim[] = 
         "\x0a";
      read_00179 = NULL;
      read_00179_len = 0;
      int read_00179_res = cgc_delimited_read(0, &read_00179, &read_00179_len, read_00179_delim, 1);
      if (read_00179_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00179_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00179_ptr += cgc_data_match(read_00179 + read_00179_ptr, read_00179_len - read_00179_ptr, match_00179_00000, 8);
      cgc_free(read_00179);
      if (read_00179_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00158_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00158_00000_len = 2;
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = cgc_append_buf(write_00158, &write_00158_len, write_00158_00000, write_00158_00000_len);
      if (write_00158_len > 0) {
         cgc_transmit_all(1, write_00158, write_00158_len);
      }
      cgc_free(write_00158);
   } while (0);
   do {
      unsigned char *read_00180;
      unsigned int read_00180_len;
      unsigned int read_00180_ptr = 0;
      //**** delimited read
      static unsigned char read_00180_delim[] = 
         "\x0a";
      read_00180 = NULL;
      read_00180_len = 0;
      int read_00180_res = cgc_delimited_read(0, &read_00180, &read_00180_len, read_00180_delim, 1);
      if (read_00180_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00180_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00180_ptr += cgc_data_match(read_00180 + read_00180_ptr, read_00180_len - read_00180_ptr, match_00180_00000, 6);
      cgc_free(read_00180);
      if (read_00180_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x36\x0a";
      static unsigned int write_00159_00000_len = 2;
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = cgc_append_buf(write_00159, &write_00159_len, write_00159_00000, write_00159_00000_len);
      if (write_00159_len > 0) {
         cgc_transmit_all(1, write_00159, write_00159_len);
      }
      cgc_free(write_00159);
   } while (0);
   do {
      unsigned char *read_00181;
      unsigned int read_00181_len;
      unsigned int read_00181_ptr = 0;
      //**** delimited read
      static unsigned char read_00181_delim[] = 
         "\x0a";
      read_00181 = NULL;
      read_00181_len = 0;
      int read_00181_res = cgc_delimited_read(0, &read_00181, &read_00181_len, read_00181_delim, 1);
      if (read_00181_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00181_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00181_ptr += cgc_data_match(read_00181 + read_00181_ptr, read_00181_len - read_00181_ptr, match_00181_00000, 29);
      cgc_free(read_00181);
      if (read_00181_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00182;
      unsigned int read_00182_len;
      unsigned int read_00182_ptr = 0;
      //**** delimited read
      static unsigned char read_00182_delim[] = 
         "\x0a";
      read_00182 = NULL;
      read_00182_len = 0;
      int read_00182_res = cgc_delimited_read(0, &read_00182, &read_00182_len, read_00182_delim, 1);
      if (read_00182_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00182_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00182_ptr += cgc_data_match(read_00182 + read_00182_ptr, read_00182_len - read_00182_ptr, match_00182_00000, 42);
      cgc_free(read_00182);
      if (read_00182_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00183;
      unsigned int read_00183_len;
      unsigned int read_00183_ptr = 0;
      //**** delimited read
      static unsigned char read_00183_delim[] = 
         "\x0a";
      read_00183 = NULL;
      read_00183_len = 0;
      int read_00183_res = cgc_delimited_read(0, &read_00183, &read_00183_len, read_00183_delim, 1);
      if (read_00183_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00183_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00183_ptr += cgc_data_match(read_00183 + read_00183_ptr, read_00183_len - read_00183_ptr, match_00183_00000, 29);
      cgc_free(read_00183);
      if (read_00183_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00184;
      unsigned int read_00184_len;
      unsigned int read_00184_ptr = 0;
      //**** delimited read
      static unsigned char read_00184_delim[] = 
         "\x0a";
      read_00184 = NULL;
      read_00184_len = 0;
      int read_00184_res = cgc_delimited_read(0, &read_00184, &read_00184_len, read_00184_delim, 1);
      if (read_00184_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00184_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00184_ptr += cgc_data_match(read_00184 + read_00184_ptr, read_00184_len - read_00184_ptr, match_00184_00000, 42);
      cgc_free(read_00184);
      if (read_00184_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00185;
      unsigned int read_00185_len;
      unsigned int read_00185_ptr = 0;
      //**** delimited read
      static unsigned char read_00185_delim[] = 
         "\x0a";
      read_00185 = NULL;
      read_00185_len = 0;
      int read_00185_res = cgc_delimited_read(0, &read_00185, &read_00185_len, read_00185_delim, 1);
      if (read_00185_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00185_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00185_ptr += cgc_data_match(read_00185 + read_00185_ptr, read_00185_len - read_00185_ptr, match_00185_00000, 8);
      cgc_free(read_00185);
      if (read_00185_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00160_00000[] = 
         "\x44\x0a";
      static unsigned int write_00160_00000_len = 2;
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = cgc_append_buf(write_00160, &write_00160_len, write_00160_00000, write_00160_00000_len);
      if (write_00160_len > 0) {
         cgc_transmit_all(1, write_00160, write_00160_len);
      }
      cgc_free(write_00160);
   } while (0);
   do {
      unsigned char *read_00186;
      unsigned int read_00186_len;
      unsigned int read_00186_ptr = 0;
      //**** delimited read
      static unsigned char read_00186_delim[] = 
         "\x0a";
      read_00186 = NULL;
      read_00186_len = 0;
      int read_00186_res = cgc_delimited_read(0, &read_00186, &read_00186_len, read_00186_delim, 1);
      if (read_00186_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00186_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00186_ptr += cgc_data_match(read_00186 + read_00186_ptr, read_00186_len - read_00186_ptr, match_00186_00000, 47);
      cgc_free(read_00186);
      if (read_00186_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00187;
      unsigned int read_00187_len;
      unsigned int read_00187_ptr = 0;
      //**** delimited read
      static unsigned char read_00187_delim[] = 
         "\x0a";
      read_00187 = NULL;
      read_00187_len = 0;
      int read_00187_res = cgc_delimited_read(0, &read_00187, &read_00187_len, read_00187_delim, 1);
      if (read_00187_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00187_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00187_ptr += cgc_data_match(read_00187 + read_00187_ptr, read_00187_len - read_00187_ptr, match_00187_00000, 8);
      cgc_free(read_00187);
      if (read_00187_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00161_00000_len = 2;
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = cgc_append_buf(write_00161, &write_00161_len, write_00161_00000, write_00161_00000_len);
      if (write_00161_len > 0) {
         cgc_transmit_all(1, write_00161, write_00161_len);
      }
      cgc_free(write_00161);
   } while (0);
   do {
      unsigned char *read_00188;
      unsigned int read_00188_len;
      unsigned int read_00188_ptr = 0;
      //**** delimited read
      static unsigned char read_00188_delim[] = 
         "\x0a";
      read_00188 = NULL;
      read_00188_len = 0;
      int read_00188_res = cgc_delimited_read(0, &read_00188, &read_00188_len, read_00188_delim, 1);
      if (read_00188_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00188_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00188_ptr += cgc_data_match(read_00188 + read_00188_ptr, read_00188_len - read_00188_ptr, match_00188_00000, 6);
      cgc_free(read_00188);
      if (read_00188_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00162_00000[] = 
         "\x37\x0a";
      static unsigned int write_00162_00000_len = 2;
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = cgc_append_buf(write_00162, &write_00162_len, write_00162_00000, write_00162_00000_len);
      if (write_00162_len > 0) {
         cgc_transmit_all(1, write_00162, write_00162_len);
      }
      cgc_free(write_00162);
   } while (0);
   do {
      unsigned char *read_00189;
      unsigned int read_00189_len;
      unsigned int read_00189_ptr = 0;
      //**** delimited read
      static unsigned char read_00189_delim[] = 
         "\x0a";
      read_00189 = NULL;
      read_00189_len = 0;
      int read_00189_res = cgc_delimited_read(0, &read_00189, &read_00189_len, read_00189_delim, 1);
      if (read_00189_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00189_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00189_ptr += cgc_data_match(read_00189 + read_00189_ptr, read_00189_len - read_00189_ptr, match_00189_00000, 47);
      cgc_free(read_00189);
      if (read_00189_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00190;
      unsigned int read_00190_len;
      unsigned int read_00190_ptr = 0;
      //**** delimited read
      static unsigned char read_00190_delim[] = 
         "\x0a";
      read_00190 = NULL;
      read_00190_len = 0;
      int read_00190_res = cgc_delimited_read(0, &read_00190, &read_00190_len, read_00190_delim, 1);
      if (read_00190_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00190_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00190_ptr += cgc_data_match(read_00190 + read_00190_ptr, read_00190_len - read_00190_ptr, match_00190_00000, 8);
      cgc_free(read_00190);
      if (read_00190_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00163_00000_len = 2;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = cgc_append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         cgc_transmit_all(1, write_00163, write_00163_len);
      }
      cgc_free(write_00163);
   } while (0);
   do {
      unsigned char *read_00191;
      unsigned int read_00191_len;
      unsigned int read_00191_ptr = 0;
      //**** delimited read
      static unsigned char read_00191_delim[] = 
         "\x0a";
      read_00191 = NULL;
      read_00191_len = 0;
      int read_00191_res = cgc_delimited_read(0, &read_00191, &read_00191_len, read_00191_delim, 1);
      if (read_00191_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00191_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00191_ptr += cgc_data_match(read_00191 + read_00191_ptr, read_00191_len - read_00191_ptr, match_00191_00000, 6);
      cgc_free(read_00191);
      if (read_00191_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00164_00000[] = 
         "\x38\x0a";
      static unsigned int write_00164_00000_len = 2;
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = cgc_append_buf(write_00164, &write_00164_len, write_00164_00000, write_00164_00000_len);
      if (write_00164_len > 0) {
         cgc_transmit_all(1, write_00164, write_00164_len);
      }
      cgc_free(write_00164);
   } while (0);
   do {
      unsigned char *read_00192;
      unsigned int read_00192_len;
      unsigned int read_00192_ptr = 0;
      //**** delimited read
      static unsigned char read_00192_delim[] = 
         "\x0a";
      read_00192 = NULL;
      read_00192_len = 0;
      int read_00192_res = cgc_delimited_read(0, &read_00192, &read_00192_len, read_00192_delim, 1);
      if (read_00192_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00192_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00192_ptr += cgc_data_match(read_00192 + read_00192_ptr, read_00192_len - read_00192_ptr, match_00192_00000, 29);
      cgc_free(read_00192);
      if (read_00192_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00193;
      unsigned int read_00193_len;
      unsigned int read_00193_ptr = 0;
      //**** delimited read
      static unsigned char read_00193_delim[] = 
         "\x0a";
      read_00193 = NULL;
      read_00193_len = 0;
      int read_00193_res = cgc_delimited_read(0, &read_00193, &read_00193_len, read_00193_delim, 1);
      if (read_00193_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00193_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00193_ptr += cgc_data_match(read_00193 + read_00193_ptr, read_00193_len - read_00193_ptr, match_00193_00000, 42);
      cgc_free(read_00193);
      if (read_00193_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00194;
      unsigned int read_00194_len;
      unsigned int read_00194_ptr = 0;
      //**** delimited read
      static unsigned char read_00194_delim[] = 
         "\x0a";
      read_00194 = NULL;
      read_00194_len = 0;
      int read_00194_res = cgc_delimited_read(0, &read_00194, &read_00194_len, read_00194_delim, 1);
      if (read_00194_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00194_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00194_ptr += cgc_data_match(read_00194 + read_00194_ptr, read_00194_len - read_00194_ptr, match_00194_00000, 29);
      cgc_free(read_00194);
      if (read_00194_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00195;
      unsigned int read_00195_len;
      unsigned int read_00195_ptr = 0;
      //**** delimited read
      static unsigned char read_00195_delim[] = 
         "\x0a";
      read_00195 = NULL;
      read_00195_len = 0;
      int read_00195_res = cgc_delimited_read(0, &read_00195, &read_00195_len, read_00195_delim, 1);
      if (read_00195_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00195_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00195_ptr += cgc_data_match(read_00195 + read_00195_ptr, read_00195_len - read_00195_ptr, match_00195_00000, 42);
      cgc_free(read_00195);
      if (read_00195_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00196;
      unsigned int read_00196_len;
      unsigned int read_00196_ptr = 0;
      //**** delimited read
      static unsigned char read_00196_delim[] = 
         "\x0a";
      read_00196 = NULL;
      read_00196_len = 0;
      int read_00196_res = cgc_delimited_read(0, &read_00196, &read_00196_len, read_00196_delim, 1);
      if (read_00196_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00196_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00196_ptr += cgc_data_match(read_00196 + read_00196_ptr, read_00196_len - read_00196_ptr, match_00196_00000, 8);
      cgc_free(read_00196);
      if (read_00196_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x44\x0a";
      static unsigned int write_00165_00000_len = 2;
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = cgc_append_buf(write_00165, &write_00165_len, write_00165_00000, write_00165_00000_len);
      if (write_00165_len > 0) {
         cgc_transmit_all(1, write_00165, write_00165_len);
      }
      cgc_free(write_00165);
   } while (0);
   do {
      unsigned char *read_00197;
      unsigned int read_00197_len;
      unsigned int read_00197_ptr = 0;
      //**** delimited read
      static unsigned char read_00197_delim[] = 
         "\x0a";
      read_00197 = NULL;
      read_00197_len = 0;
      int read_00197_res = cgc_delimited_read(0, &read_00197, &read_00197_len, read_00197_delim, 1);
      if (read_00197_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00197_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00197_ptr += cgc_data_match(read_00197 + read_00197_ptr, read_00197_len - read_00197_ptr, match_00197_00000, 47);
      cgc_free(read_00197);
      if (read_00197_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00198;
      unsigned int read_00198_len;
      unsigned int read_00198_ptr = 0;
      //**** delimited read
      static unsigned char read_00198_delim[] = 
         "\x0a";
      read_00198 = NULL;
      read_00198_len = 0;
      int read_00198_res = cgc_delimited_read(0, &read_00198, &read_00198_len, read_00198_delim, 1);
      if (read_00198_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00198_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00198_ptr += cgc_data_match(read_00198 + read_00198_ptr, read_00198_len - read_00198_ptr, match_00198_00000, 8);
      cgc_free(read_00198);
      if (read_00198_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00166_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00166_00000_len = 2;
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = cgc_append_buf(write_00166, &write_00166_len, write_00166_00000, write_00166_00000_len);
      if (write_00166_len > 0) {
         cgc_transmit_all(1, write_00166, write_00166_len);
      }
      cgc_free(write_00166);
   } while (0);
   do {
      unsigned char *read_00199;
      unsigned int read_00199_len;
      unsigned int read_00199_ptr = 0;
      //**** delimited read
      static unsigned char read_00199_delim[] = 
         "\x0a";
      read_00199 = NULL;
      read_00199_len = 0;
      int read_00199_res = cgc_delimited_read(0, &read_00199, &read_00199_len, read_00199_delim, 1);
      if (read_00199_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00199_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00199_ptr += cgc_data_match(read_00199 + read_00199_ptr, read_00199_len - read_00199_ptr, match_00199_00000, 6);
      cgc_free(read_00199);
      if (read_00199_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x39\x0a";
      static unsigned int write_00167_00000_len = 2;
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = cgc_append_buf(write_00167, &write_00167_len, write_00167_00000, write_00167_00000_len);
      if (write_00167_len > 0) {
         cgc_transmit_all(1, write_00167, write_00167_len);
      }
      cgc_free(write_00167);
   } while (0);
   do {
      unsigned char *read_00200;
      unsigned int read_00200_len;
      unsigned int read_00200_ptr = 0;
      //**** delimited read
      static unsigned char read_00200_delim[] = 
         "\x0a";
      read_00200 = NULL;
      read_00200_len = 0;
      int read_00200_res = cgc_delimited_read(0, &read_00200, &read_00200_len, read_00200_delim, 1);
      if (read_00200_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00200_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00200_ptr += cgc_data_match(read_00200 + read_00200_ptr, read_00200_len - read_00200_ptr, match_00200_00000, 47);
      cgc_free(read_00200);
      if (read_00200_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** delimited read
      static unsigned char read_00201_delim[] = 
         "\x0a";
      read_00201 = NULL;
      read_00201_len = 0;
      int read_00201_res = cgc_delimited_read(0, &read_00201, &read_00201_len, read_00201_delim, 1);
      if (read_00201_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00201_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00201_ptr += cgc_data_match(read_00201 + read_00201_ptr, read_00201_len - read_00201_ptr, match_00201_00000, 8);
      cgc_free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00168_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00168_00000_len = 2;
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = cgc_append_buf(write_00168, &write_00168_len, write_00168_00000, write_00168_00000_len);
      if (write_00168_len > 0) {
         cgc_transmit_all(1, write_00168, write_00168_len);
      }
      cgc_free(write_00168);
   } while (0);
   do {
      unsigned char *read_00202;
      unsigned int read_00202_len;
      unsigned int read_00202_ptr = 0;
      //**** delimited read
      static unsigned char read_00202_delim[] = 
         "\x0a";
      read_00202 = NULL;
      read_00202_len = 0;
      int read_00202_res = cgc_delimited_read(0, &read_00202, &read_00202_len, read_00202_delim, 1);
      if (read_00202_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00202_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00202_ptr += cgc_data_match(read_00202 + read_00202_ptr, read_00202_len - read_00202_ptr, match_00202_00000, 6);
      cgc_free(read_00202);
      if (read_00202_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x31\x30\x0a";
      static unsigned int write_00169_00000_len = 3;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = cgc_append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         cgc_transmit_all(1, write_00169, write_00169_len);
      }
      cgc_free(write_00169);
   } while (0);
   do {
      unsigned char *read_00203;
      unsigned int read_00203_len;
      unsigned int read_00203_ptr = 0;
      //**** delimited read
      static unsigned char read_00203_delim[] = 
         "\x0a";
      read_00203 = NULL;
      read_00203_len = 0;
      int read_00203_res = cgc_delimited_read(0, &read_00203, &read_00203_len, read_00203_delim, 1);
      if (read_00203_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00203_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00203_ptr += cgc_data_match(read_00203 + read_00203_ptr, read_00203_len - read_00203_ptr, match_00203_00000, 29);
      cgc_free(read_00203);
      if (read_00203_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00204;
      unsigned int read_00204_len;
      unsigned int read_00204_ptr = 0;
      //**** delimited read
      static unsigned char read_00204_delim[] = 
         "\x0a";
      read_00204 = NULL;
      read_00204_len = 0;
      int read_00204_res = cgc_delimited_read(0, &read_00204, &read_00204_len, read_00204_delim, 1);
      if (read_00204_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00204_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00204_ptr += cgc_data_match(read_00204 + read_00204_ptr, read_00204_len - read_00204_ptr, match_00204_00000, 42);
      cgc_free(read_00204);
      if (read_00204_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00205;
      unsigned int read_00205_len;
      unsigned int read_00205_ptr = 0;
      //**** delimited read
      static unsigned char read_00205_delim[] = 
         "\x0a";
      read_00205 = NULL;
      read_00205_len = 0;
      int read_00205_res = cgc_delimited_read(0, &read_00205, &read_00205_len, read_00205_delim, 1);
      if (read_00205_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00205_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00205_ptr += cgc_data_match(read_00205 + read_00205_ptr, read_00205_len - read_00205_ptr, match_00205_00000, 29);
      cgc_free(read_00205);
      if (read_00205_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00206;
      unsigned int read_00206_len;
      unsigned int read_00206_ptr = 0;
      //**** delimited read
      static unsigned char read_00206_delim[] = 
         "\x0a";
      read_00206 = NULL;
      read_00206_len = 0;
      int read_00206_res = cgc_delimited_read(0, &read_00206, &read_00206_len, read_00206_delim, 1);
      if (read_00206_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00206_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00206_ptr += cgc_data_match(read_00206 + read_00206_ptr, read_00206_len - read_00206_ptr, match_00206_00000, 42);
      cgc_free(read_00206);
      if (read_00206_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00207;
      unsigned int read_00207_len;
      unsigned int read_00207_ptr = 0;
      //**** delimited read
      static unsigned char read_00207_delim[] = 
         "\x0a";
      read_00207 = NULL;
      read_00207_len = 0;
      int read_00207_res = cgc_delimited_read(0, &read_00207, &read_00207_len, read_00207_delim, 1);
      if (read_00207_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00207_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00207_ptr += cgc_data_match(read_00207 + read_00207_ptr, read_00207_len - read_00207_ptr, match_00207_00000, 8);
      cgc_free(read_00207);
      if (read_00207_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00170_00000[] = 
         "\x44\x0a";
      static unsigned int write_00170_00000_len = 2;
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = cgc_append_buf(write_00170, &write_00170_len, write_00170_00000, write_00170_00000_len);
      if (write_00170_len > 0) {
         cgc_transmit_all(1, write_00170, write_00170_len);
      }
      cgc_free(write_00170);
   } while (0);
   do {
      unsigned char *read_00208;
      unsigned int read_00208_len;
      unsigned int read_00208_ptr = 0;
      //**** delimited read
      static unsigned char read_00208_delim[] = 
         "\x0a";
      read_00208 = NULL;
      read_00208_len = 0;
      int read_00208_res = cgc_delimited_read(0, &read_00208, &read_00208_len, read_00208_delim, 1);
      if (read_00208_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00208_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00208_ptr += cgc_data_match(read_00208 + read_00208_ptr, read_00208_len - read_00208_ptr, match_00208_00000, 47);
      cgc_free(read_00208);
      if (read_00208_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00209;
      unsigned int read_00209_len;
      unsigned int read_00209_ptr = 0;
      //**** delimited read
      static unsigned char read_00209_delim[] = 
         "\x0a";
      read_00209 = NULL;
      read_00209_len = 0;
      int read_00209_res = cgc_delimited_read(0, &read_00209, &read_00209_len, read_00209_delim, 1);
      if (read_00209_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00209_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00209_ptr += cgc_data_match(read_00209 + read_00209_ptr, read_00209_len - read_00209_ptr, match_00209_00000, 8);
      cgc_free(read_00209);
      if (read_00209_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00171_00000_len = 2;
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = cgc_append_buf(write_00171, &write_00171_len, write_00171_00000, write_00171_00000_len);
      if (write_00171_len > 0) {
         cgc_transmit_all(1, write_00171, write_00171_len);
      }
      cgc_free(write_00171);
   } while (0);
   do {
      unsigned char *read_00210;
      unsigned int read_00210_len;
      unsigned int read_00210_ptr = 0;
      //**** delimited read
      static unsigned char read_00210_delim[] = 
         "\x0a";
      read_00210 = NULL;
      read_00210_len = 0;
      int read_00210_res = cgc_delimited_read(0, &read_00210, &read_00210_len, read_00210_delim, 1);
      if (read_00210_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00210_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00210_ptr += cgc_data_match(read_00210 + read_00210_ptr, read_00210_len - read_00210_ptr, match_00210_00000, 6);
      cgc_free(read_00210);
      if (read_00210_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00172_00000[] = 
         "\x31\x31\x0a";
      static unsigned int write_00172_00000_len = 3;
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = cgc_append_buf(write_00172, &write_00172_len, write_00172_00000, write_00172_00000_len);
      if (write_00172_len > 0) {
         cgc_transmit_all(1, write_00172, write_00172_len);
      }
      cgc_free(write_00172);
   } while (0);
   do {
      unsigned char *read_00211;
      unsigned int read_00211_len;
      unsigned int read_00211_ptr = 0;
      //**** delimited read
      static unsigned char read_00211_delim[] = 
         "\x0a";
      read_00211 = NULL;
      read_00211_len = 0;
      int read_00211_res = cgc_delimited_read(0, &read_00211, &read_00211_len, read_00211_delim, 1);
      if (read_00211_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00211_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00211_ptr += cgc_data_match(read_00211 + read_00211_ptr, read_00211_len - read_00211_ptr, match_00211_00000, 47);
      cgc_free(read_00211);
      if (read_00211_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00212;
      unsigned int read_00212_len;
      unsigned int read_00212_ptr = 0;
      //**** delimited read
      static unsigned char read_00212_delim[] = 
         "\x0a";
      read_00212 = NULL;
      read_00212_len = 0;
      int read_00212_res = cgc_delimited_read(0, &read_00212, &read_00212_len, read_00212_delim, 1);
      if (read_00212_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00212_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00212_ptr += cgc_data_match(read_00212 + read_00212_ptr, read_00212_len - read_00212_ptr, match_00212_00000, 8);
      cgc_free(read_00212);
      if (read_00212_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00173_00000_len = 2;
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = cgc_append_buf(write_00173, &write_00173_len, write_00173_00000, write_00173_00000_len);
      if (write_00173_len > 0) {
         cgc_transmit_all(1, write_00173, write_00173_len);
      }
      cgc_free(write_00173);
   } while (0);
   do {
      unsigned char *read_00213;
      unsigned int read_00213_len;
      unsigned int read_00213_ptr = 0;
      //**** delimited read
      static unsigned char read_00213_delim[] = 
         "\x0a";
      read_00213 = NULL;
      read_00213_len = 0;
      int read_00213_res = cgc_delimited_read(0, &read_00213, &read_00213_len, read_00213_delim, 1);
      if (read_00213_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00213_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00213_ptr += cgc_data_match(read_00213 + read_00213_ptr, read_00213_len - read_00213_ptr, match_00213_00000, 6);
      cgc_free(read_00213);
      if (read_00213_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00174_00000[] = 
         "\x31\x32\x0a";
      static unsigned int write_00174_00000_len = 3;
      unsigned char *write_00174 = NULL;
      unsigned int write_00174_len = 0;
      write_00174 = cgc_append_buf(write_00174, &write_00174_len, write_00174_00000, write_00174_00000_len);
      if (write_00174_len > 0) {
         cgc_transmit_all(1, write_00174, write_00174_len);
      }
      cgc_free(write_00174);
   } while (0);
   do {
      unsigned char *read_00214;
      unsigned int read_00214_len;
      unsigned int read_00214_ptr = 0;
      //**** delimited read
      static unsigned char read_00214_delim[] = 
         "\x0a";
      read_00214 = NULL;
      read_00214_len = 0;
      int read_00214_res = cgc_delimited_read(0, &read_00214, &read_00214_len, read_00214_delim, 1);
      if (read_00214_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00214_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00214_ptr += cgc_data_match(read_00214 + read_00214_ptr, read_00214_len - read_00214_ptr, match_00214_00000, 29);
      cgc_free(read_00214);
      if (read_00214_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00215;
      unsigned int read_00215_len;
      unsigned int read_00215_ptr = 0;
      //**** delimited read
      static unsigned char read_00215_delim[] = 
         "\x0a";
      read_00215 = NULL;
      read_00215_len = 0;
      int read_00215_res = cgc_delimited_read(0, &read_00215, &read_00215_len, read_00215_delim, 1);
      if (read_00215_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00215_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00215_ptr += cgc_data_match(read_00215 + read_00215_ptr, read_00215_len - read_00215_ptr, match_00215_00000, 42);
      cgc_free(read_00215);
      if (read_00215_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00216;
      unsigned int read_00216_len;
      unsigned int read_00216_ptr = 0;
      //**** delimited read
      static unsigned char read_00216_delim[] = 
         "\x0a";
      read_00216 = NULL;
      read_00216_len = 0;
      int read_00216_res = cgc_delimited_read(0, &read_00216, &read_00216_len, read_00216_delim, 1);
      if (read_00216_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00216_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00216_ptr += cgc_data_match(read_00216 + read_00216_ptr, read_00216_len - read_00216_ptr, match_00216_00000, 29);
      cgc_free(read_00216);
      if (read_00216_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00217;
      unsigned int read_00217_len;
      unsigned int read_00217_ptr = 0;
      //**** delimited read
      static unsigned char read_00217_delim[] = 
         "\x0a";
      read_00217 = NULL;
      read_00217_len = 0;
      int read_00217_res = cgc_delimited_read(0, &read_00217, &read_00217_len, read_00217_delim, 1);
      if (read_00217_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00217_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00217_ptr += cgc_data_match(read_00217 + read_00217_ptr, read_00217_len - read_00217_ptr, match_00217_00000, 42);
      cgc_free(read_00217);
      if (read_00217_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00218;
      unsigned int read_00218_len;
      unsigned int read_00218_ptr = 0;
      //**** delimited read
      static unsigned char read_00218_delim[] = 
         "\x0a";
      read_00218 = NULL;
      read_00218_len = 0;
      int read_00218_res = cgc_delimited_read(0, &read_00218, &read_00218_len, read_00218_delim, 1);
      if (read_00218_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00218_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00218_ptr += cgc_data_match(read_00218 + read_00218_ptr, read_00218_len - read_00218_ptr, match_00218_00000, 8);
      cgc_free(read_00218);
      if (read_00218_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x44\x0a";
      static unsigned int write_00175_00000_len = 2;
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = cgc_append_buf(write_00175, &write_00175_len, write_00175_00000, write_00175_00000_len);
      if (write_00175_len > 0) {
         cgc_transmit_all(1, write_00175, write_00175_len);
      }
      cgc_free(write_00175);
   } while (0);
   do {
      unsigned char *read_00219;
      unsigned int read_00219_len;
      unsigned int read_00219_ptr = 0;
      //**** delimited read
      static unsigned char read_00219_delim[] = 
         "\x0a";
      read_00219 = NULL;
      read_00219_len = 0;
      int read_00219_res = cgc_delimited_read(0, &read_00219, &read_00219_len, read_00219_delim, 1);
      if (read_00219_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00219_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00219_ptr += cgc_data_match(read_00219 + read_00219_ptr, read_00219_len - read_00219_ptr, match_00219_00000, 47);
      cgc_free(read_00219);
      if (read_00219_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00220;
      unsigned int read_00220_len;
      unsigned int read_00220_ptr = 0;
      //**** delimited read
      static unsigned char read_00220_delim[] = 
         "\x0a";
      read_00220 = NULL;
      read_00220_len = 0;
      int read_00220_res = cgc_delimited_read(0, &read_00220, &read_00220_len, read_00220_delim, 1);
      if (read_00220_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00220_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00220_ptr += cgc_data_match(read_00220 + read_00220_ptr, read_00220_len - read_00220_ptr, match_00220_00000, 8);
      cgc_free(read_00220);
      if (read_00220_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00176_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00176_00000_len = 2;
      unsigned char *write_00176 = NULL;
      unsigned int write_00176_len = 0;
      write_00176 = cgc_append_buf(write_00176, &write_00176_len, write_00176_00000, write_00176_00000_len);
      if (write_00176_len > 0) {
         cgc_transmit_all(1, write_00176, write_00176_len);
      }
      cgc_free(write_00176);
   } while (0);
   do {
      unsigned char *read_00221;
      unsigned int read_00221_len;
      unsigned int read_00221_ptr = 0;
      //**** delimited read
      static unsigned char read_00221_delim[] = 
         "\x0a";
      read_00221 = NULL;
      read_00221_len = 0;
      int read_00221_res = cgc_delimited_read(0, &read_00221, &read_00221_len, read_00221_delim, 1);
      if (read_00221_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00221_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00221_ptr += cgc_data_match(read_00221 + read_00221_ptr, read_00221_len - read_00221_ptr, match_00221_00000, 6);
      cgc_free(read_00221);
      if (read_00221_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x31\x33\x0a";
      static unsigned int write_00177_00000_len = 3;
      unsigned char *write_00177 = NULL;
      unsigned int write_00177_len = 0;
      write_00177 = cgc_append_buf(write_00177, &write_00177_len, write_00177_00000, write_00177_00000_len);
      if (write_00177_len > 0) {
         cgc_transmit_all(1, write_00177, write_00177_len);
      }
      cgc_free(write_00177);
   } while (0);
   do {
      unsigned char *read_00222;
      unsigned int read_00222_len;
      unsigned int read_00222_ptr = 0;
      //**** delimited read
      static unsigned char read_00222_delim[] = 
         "\x0a";
      read_00222 = NULL;
      read_00222_len = 0;
      int read_00222_res = cgc_delimited_read(0, &read_00222, &read_00222_len, read_00222_delim, 1);
      if (read_00222_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00222_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00222_ptr += cgc_data_match(read_00222 + read_00222_ptr, read_00222_len - read_00222_ptr, match_00222_00000, 47);
      cgc_free(read_00222);
      if (read_00222_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00223;
      unsigned int read_00223_len;
      unsigned int read_00223_ptr = 0;
      //**** delimited read
      static unsigned char read_00223_delim[] = 
         "\x0a";
      read_00223 = NULL;
      read_00223_len = 0;
      int read_00223_res = cgc_delimited_read(0, &read_00223, &read_00223_len, read_00223_delim, 1);
      if (read_00223_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00223_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00223_ptr += cgc_data_match(read_00223 + read_00223_ptr, read_00223_len - read_00223_ptr, match_00223_00000, 8);
      cgc_free(read_00223);
      if (read_00223_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00178_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00178_00000_len = 2;
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = cgc_append_buf(write_00178, &write_00178_len, write_00178_00000, write_00178_00000_len);
      if (write_00178_len > 0) {
         cgc_transmit_all(1, write_00178, write_00178_len);
      }
      cgc_free(write_00178);
   } while (0);
   do {
      unsigned char *read_00224;
      unsigned int read_00224_len;
      unsigned int read_00224_ptr = 0;
      //**** delimited read
      static unsigned char read_00224_delim[] = 
         "\x0a";
      read_00224 = NULL;
      read_00224_len = 0;
      int read_00224_res = cgc_delimited_read(0, &read_00224, &read_00224_len, read_00224_delim, 1);
      if (read_00224_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00224_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00224_ptr += cgc_data_match(read_00224 + read_00224_ptr, read_00224_len - read_00224_ptr, match_00224_00000, 6);
      cgc_free(read_00224);
      if (read_00224_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\x31\x34\x0a";
      static unsigned int write_00179_00000_len = 3;
      unsigned char *write_00179 = NULL;
      unsigned int write_00179_len = 0;
      write_00179 = cgc_append_buf(write_00179, &write_00179_len, write_00179_00000, write_00179_00000_len);
      if (write_00179_len > 0) {
         cgc_transmit_all(1, write_00179, write_00179_len);
      }
      cgc_free(write_00179);
   } while (0);
   do {
      unsigned char *read_00225;
      unsigned int read_00225_len;
      unsigned int read_00225_ptr = 0;
      //**** delimited read
      static unsigned char read_00225_delim[] = 
         "\x0a";
      read_00225 = NULL;
      read_00225_len = 0;
      int read_00225_res = cgc_delimited_read(0, &read_00225, &read_00225_len, read_00225_delim, 1);
      if (read_00225_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00225_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00225_ptr += cgc_data_match(read_00225 + read_00225_ptr, read_00225_len - read_00225_ptr, match_00225_00000, 29);
      cgc_free(read_00225);
      if (read_00225_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00226;
      unsigned int read_00226_len;
      unsigned int read_00226_ptr = 0;
      //**** delimited read
      static unsigned char read_00226_delim[] = 
         "\x0a";
      read_00226 = NULL;
      read_00226_len = 0;
      int read_00226_res = cgc_delimited_read(0, &read_00226, &read_00226_len, read_00226_delim, 1);
      if (read_00226_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00226_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00226_ptr += cgc_data_match(read_00226 + read_00226_ptr, read_00226_len - read_00226_ptr, match_00226_00000, 42);
      cgc_free(read_00226);
      if (read_00226_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00227;
      unsigned int read_00227_len;
      unsigned int read_00227_ptr = 0;
      //**** delimited read
      static unsigned char read_00227_delim[] = 
         "\x0a";
      read_00227 = NULL;
      read_00227_len = 0;
      int read_00227_res = cgc_delimited_read(0, &read_00227, &read_00227_len, read_00227_delim, 1);
      if (read_00227_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00227_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00227_ptr += cgc_data_match(read_00227 + read_00227_ptr, read_00227_len - read_00227_ptr, match_00227_00000, 29);
      cgc_free(read_00227);
      if (read_00227_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00228;
      unsigned int read_00228_len;
      unsigned int read_00228_ptr = 0;
      //**** delimited read
      static unsigned char read_00228_delim[] = 
         "\x0a";
      read_00228 = NULL;
      read_00228_len = 0;
      int read_00228_res = cgc_delimited_read(0, &read_00228, &read_00228_len, read_00228_delim, 1);
      if (read_00228_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00228_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00228_ptr += cgc_data_match(read_00228 + read_00228_ptr, read_00228_len - read_00228_ptr, match_00228_00000, 42);
      cgc_free(read_00228);
      if (read_00228_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00229;
      unsigned int read_00229_len;
      unsigned int read_00229_ptr = 0;
      //**** delimited read
      static unsigned char read_00229_delim[] = 
         "\x0a";
      read_00229 = NULL;
      read_00229_len = 0;
      int read_00229_res = cgc_delimited_read(0, &read_00229, &read_00229_len, read_00229_delim, 1);
      if (read_00229_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00229_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00229_ptr += cgc_data_match(read_00229 + read_00229_ptr, read_00229_len - read_00229_ptr, match_00229_00000, 8);
      cgc_free(read_00229);
      if (read_00229_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00180_00000[] = 
         "\x44\x0a";
      static unsigned int write_00180_00000_len = 2;
      unsigned char *write_00180 = NULL;
      unsigned int write_00180_len = 0;
      write_00180 = cgc_append_buf(write_00180, &write_00180_len, write_00180_00000, write_00180_00000_len);
      if (write_00180_len > 0) {
         cgc_transmit_all(1, write_00180, write_00180_len);
      }
      cgc_free(write_00180);
   } while (0);
   do {
      unsigned char *read_00230;
      unsigned int read_00230_len;
      unsigned int read_00230_ptr = 0;
      //**** delimited read
      static unsigned char read_00230_delim[] = 
         "\x0a";
      read_00230 = NULL;
      read_00230_len = 0;
      int read_00230_res = cgc_delimited_read(0, &read_00230, &read_00230_len, read_00230_delim, 1);
      if (read_00230_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00230_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00230_ptr += cgc_data_match(read_00230 + read_00230_ptr, read_00230_len - read_00230_ptr, match_00230_00000, 47);
      cgc_free(read_00230);
      if (read_00230_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00231;
      unsigned int read_00231_len;
      unsigned int read_00231_ptr = 0;
      //**** delimited read
      static unsigned char read_00231_delim[] = 
         "\x0a";
      read_00231 = NULL;
      read_00231_len = 0;
      int read_00231_res = cgc_delimited_read(0, &read_00231, &read_00231_len, read_00231_delim, 1);
      if (read_00231_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00231_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00231_ptr += cgc_data_match(read_00231 + read_00231_ptr, read_00231_len - read_00231_ptr, match_00231_00000, 8);
      cgc_free(read_00231);
      if (read_00231_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00181_00000_len = 2;
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = cgc_append_buf(write_00181, &write_00181_len, write_00181_00000, write_00181_00000_len);
      if (write_00181_len > 0) {
         cgc_transmit_all(1, write_00181, write_00181_len);
      }
      cgc_free(write_00181);
   } while (0);
   do {
      unsigned char *read_00232;
      unsigned int read_00232_len;
      unsigned int read_00232_ptr = 0;
      //**** delimited read
      static unsigned char read_00232_delim[] = 
         "\x0a";
      read_00232 = NULL;
      read_00232_len = 0;
      int read_00232_res = cgc_delimited_read(0, &read_00232, &read_00232_len, read_00232_delim, 1);
      if (read_00232_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00232_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00232_ptr += cgc_data_match(read_00232 + read_00232_ptr, read_00232_len - read_00232_ptr, match_00232_00000, 6);
      cgc_free(read_00232);
      if (read_00232_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00182_00000[] = 
         "\x31\x35\x0a";
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
      unsigned char *read_00233;
      unsigned int read_00233_len;
      unsigned int read_00233_ptr = 0;
      //**** delimited read
      static unsigned char read_00233_delim[] = 
         "\x0a";
      read_00233 = NULL;
      read_00233_len = 0;
      int read_00233_res = cgc_delimited_read(0, &read_00233, &read_00233_len, read_00233_delim, 1);
      if (read_00233_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00233_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00233_ptr += cgc_data_match(read_00233 + read_00233_ptr, read_00233_len - read_00233_ptr, match_00233_00000, 47);
      cgc_free(read_00233);
      if (read_00233_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00234;
      unsigned int read_00234_len;
      unsigned int read_00234_ptr = 0;
      //**** delimited read
      static unsigned char read_00234_delim[] = 
         "\x0a";
      read_00234 = NULL;
      read_00234_len = 0;
      int read_00234_res = cgc_delimited_read(0, &read_00234, &read_00234_len, read_00234_delim, 1);
      if (read_00234_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00234_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00234_ptr += cgc_data_match(read_00234 + read_00234_ptr, read_00234_len - read_00234_ptr, match_00234_00000, 8);
      cgc_free(read_00234);
      if (read_00234_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00183_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00183_00000_len = 2;
      unsigned char *write_00183 = NULL;
      unsigned int write_00183_len = 0;
      write_00183 = cgc_append_buf(write_00183, &write_00183_len, write_00183_00000, write_00183_00000_len);
      if (write_00183_len > 0) {
         cgc_transmit_all(1, write_00183, write_00183_len);
      }
      cgc_free(write_00183);
   } while (0);
   do {
      unsigned char *read_00235;
      unsigned int read_00235_len;
      unsigned int read_00235_ptr = 0;
      //**** delimited read
      static unsigned char read_00235_delim[] = 
         "\x0a";
      read_00235 = NULL;
      read_00235_len = 0;
      int read_00235_res = cgc_delimited_read(0, &read_00235, &read_00235_len, read_00235_delim, 1);
      if (read_00235_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00235_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00235_ptr += cgc_data_match(read_00235 + read_00235_ptr, read_00235_len - read_00235_ptr, match_00235_00000, 6);
      cgc_free(read_00235);
      if (read_00235_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00184_00000[] = 
         "\x31\x36\x0a";
      static unsigned int write_00184_00000_len = 3;
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = cgc_append_buf(write_00184, &write_00184_len, write_00184_00000, write_00184_00000_len);
      if (write_00184_len > 0) {
         cgc_transmit_all(1, write_00184, write_00184_len);
      }
      cgc_free(write_00184);
   } while (0);
   do {
      unsigned char *read_00236;
      unsigned int read_00236_len;
      unsigned int read_00236_ptr = 0;
      //**** delimited read
      static unsigned char read_00236_delim[] = 
         "\x0a";
      read_00236 = NULL;
      read_00236_len = 0;
      int read_00236_res = cgc_delimited_read(0, &read_00236, &read_00236_len, read_00236_delim, 1);
      if (read_00236_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00236_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00236_ptr += cgc_data_match(read_00236 + read_00236_ptr, read_00236_len - read_00236_ptr, match_00236_00000, 29);
      cgc_free(read_00236);
      if (read_00236_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00237;
      unsigned int read_00237_len;
      unsigned int read_00237_ptr = 0;
      //**** delimited read
      static unsigned char read_00237_delim[] = 
         "\x0a";
      read_00237 = NULL;
      read_00237_len = 0;
      int read_00237_res = cgc_delimited_read(0, &read_00237, &read_00237_len, read_00237_delim, 1);
      if (read_00237_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00237_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00237_ptr += cgc_data_match(read_00237 + read_00237_ptr, read_00237_len - read_00237_ptr, match_00237_00000, 42);
      cgc_free(read_00237);
      if (read_00237_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00238;
      unsigned int read_00238_len;
      unsigned int read_00238_ptr = 0;
      //**** delimited read
      static unsigned char read_00238_delim[] = 
         "\x0a";
      read_00238 = NULL;
      read_00238_len = 0;
      int read_00238_res = cgc_delimited_read(0, &read_00238, &read_00238_len, read_00238_delim, 1);
      if (read_00238_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00238_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00238_ptr += cgc_data_match(read_00238 + read_00238_ptr, read_00238_len - read_00238_ptr, match_00238_00000, 29);
      cgc_free(read_00238);
      if (read_00238_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00239;
      unsigned int read_00239_len;
      unsigned int read_00239_ptr = 0;
      //**** delimited read
      static unsigned char read_00239_delim[] = 
         "\x0a";
      read_00239 = NULL;
      read_00239_len = 0;
      int read_00239_res = cgc_delimited_read(0, &read_00239, &read_00239_len, read_00239_delim, 1);
      if (read_00239_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00239_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00239_ptr += cgc_data_match(read_00239 + read_00239_ptr, read_00239_len - read_00239_ptr, match_00239_00000, 42);
      cgc_free(read_00239);
      if (read_00239_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00240;
      unsigned int read_00240_len;
      unsigned int read_00240_ptr = 0;
      //**** delimited read
      static unsigned char read_00240_delim[] = 
         "\x0a";
      read_00240 = NULL;
      read_00240_len = 0;
      int read_00240_res = cgc_delimited_read(0, &read_00240, &read_00240_len, read_00240_delim, 1);
      if (read_00240_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00240_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00240_ptr += cgc_data_match(read_00240 + read_00240_ptr, read_00240_len - read_00240_ptr, match_00240_00000, 8);
      cgc_free(read_00240);
      if (read_00240_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00185_00000[] = 
         "\x44\x0a";
      static unsigned int write_00185_00000_len = 2;
      unsigned char *write_00185 = NULL;
      unsigned int write_00185_len = 0;
      write_00185 = cgc_append_buf(write_00185, &write_00185_len, write_00185_00000, write_00185_00000_len);
      if (write_00185_len > 0) {
         cgc_transmit_all(1, write_00185, write_00185_len);
      }
      cgc_free(write_00185);
   } while (0);
   do {
      unsigned char *read_00241;
      unsigned int read_00241_len;
      unsigned int read_00241_ptr = 0;
      //**** delimited read
      static unsigned char read_00241_delim[] = 
         "\x0a";
      read_00241 = NULL;
      read_00241_len = 0;
      int read_00241_res = cgc_delimited_read(0, &read_00241, &read_00241_len, read_00241_delim, 1);
      if (read_00241_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00241_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00241_ptr += cgc_data_match(read_00241 + read_00241_ptr, read_00241_len - read_00241_ptr, match_00241_00000, 47);
      cgc_free(read_00241);
      if (read_00241_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00242;
      unsigned int read_00242_len;
      unsigned int read_00242_ptr = 0;
      //**** delimited read
      static unsigned char read_00242_delim[] = 
         "\x0a";
      read_00242 = NULL;
      read_00242_len = 0;
      int read_00242_res = cgc_delimited_read(0, &read_00242, &read_00242_len, read_00242_delim, 1);
      if (read_00242_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00242_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00242_ptr += cgc_data_match(read_00242 + read_00242_ptr, read_00242_len - read_00242_ptr, match_00242_00000, 8);
      cgc_free(read_00242);
      if (read_00242_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00186_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00186_00000_len = 2;
      unsigned char *write_00186 = NULL;
      unsigned int write_00186_len = 0;
      write_00186 = cgc_append_buf(write_00186, &write_00186_len, write_00186_00000, write_00186_00000_len);
      if (write_00186_len > 0) {
         cgc_transmit_all(1, write_00186, write_00186_len);
      }
      cgc_free(write_00186);
   } while (0);
   do {
      unsigned char *read_00243;
      unsigned int read_00243_len;
      unsigned int read_00243_ptr = 0;
      //**** delimited read
      static unsigned char read_00243_delim[] = 
         "\x0a";
      read_00243 = NULL;
      read_00243_len = 0;
      int read_00243_res = cgc_delimited_read(0, &read_00243, &read_00243_len, read_00243_delim, 1);
      if (read_00243_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00243_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00243_ptr += cgc_data_match(read_00243 + read_00243_ptr, read_00243_len - read_00243_ptr, match_00243_00000, 6);
      cgc_free(read_00243);
      if (read_00243_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00187_00000[] = 
         "\x31\x37\x0a";
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
      unsigned char *read_00244;
      unsigned int read_00244_len;
      unsigned int read_00244_ptr = 0;
      //**** delimited read
      static unsigned char read_00244_delim[] = 
         "\x0a";
      read_00244 = NULL;
      read_00244_len = 0;
      int read_00244_res = cgc_delimited_read(0, &read_00244, &read_00244_len, read_00244_delim, 1);
      if (read_00244_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00244_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00244_ptr += cgc_data_match(read_00244 + read_00244_ptr, read_00244_len - read_00244_ptr, match_00244_00000, 47);
      cgc_free(read_00244);
      if (read_00244_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00245;
      unsigned int read_00245_len;
      unsigned int read_00245_ptr = 0;
      //**** delimited read
      static unsigned char read_00245_delim[] = 
         "\x0a";
      read_00245 = NULL;
      read_00245_len = 0;
      int read_00245_res = cgc_delimited_read(0, &read_00245, &read_00245_len, read_00245_delim, 1);
      if (read_00245_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00245_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00245_ptr += cgc_data_match(read_00245 + read_00245_ptr, read_00245_len - read_00245_ptr, match_00245_00000, 8);
      cgc_free(read_00245);
      if (read_00245_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00188_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00188_00000_len = 2;
      unsigned char *write_00188 = NULL;
      unsigned int write_00188_len = 0;
      write_00188 = cgc_append_buf(write_00188, &write_00188_len, write_00188_00000, write_00188_00000_len);
      if (write_00188_len > 0) {
         cgc_transmit_all(1, write_00188, write_00188_len);
      }
      cgc_free(write_00188);
   } while (0);
   do {
      unsigned char *read_00246;
      unsigned int read_00246_len;
      unsigned int read_00246_ptr = 0;
      //**** delimited read
      static unsigned char read_00246_delim[] = 
         "\x0a";
      read_00246 = NULL;
      read_00246_len = 0;
      int read_00246_res = cgc_delimited_read(0, &read_00246, &read_00246_len, read_00246_delim, 1);
      if (read_00246_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00246_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00246_ptr += cgc_data_match(read_00246 + read_00246_ptr, read_00246_len - read_00246_ptr, match_00246_00000, 6);
      cgc_free(read_00246);
      if (read_00246_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00189_00000[] = 
         "\x31\x38\x0a";
      static unsigned int write_00189_00000_len = 3;
      unsigned char *write_00189 = NULL;
      unsigned int write_00189_len = 0;
      write_00189 = cgc_append_buf(write_00189, &write_00189_len, write_00189_00000, write_00189_00000_len);
      if (write_00189_len > 0) {
         cgc_transmit_all(1, write_00189, write_00189_len);
      }
      cgc_free(write_00189);
   } while (0);
   do {
      unsigned char *read_00247;
      unsigned int read_00247_len;
      unsigned int read_00247_ptr = 0;
      //**** delimited read
      static unsigned char read_00247_delim[] = 
         "\x0a";
      read_00247 = NULL;
      read_00247_len = 0;
      int read_00247_res = cgc_delimited_read(0, &read_00247, &read_00247_len, read_00247_delim, 1);
      if (read_00247_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00247_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00247_ptr += cgc_data_match(read_00247 + read_00247_ptr, read_00247_len - read_00247_ptr, match_00247_00000, 29);
      cgc_free(read_00247);
      if (read_00247_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00248;
      unsigned int read_00248_len;
      unsigned int read_00248_ptr = 0;
      //**** delimited read
      static unsigned char read_00248_delim[] = 
         "\x0a";
      read_00248 = NULL;
      read_00248_len = 0;
      int read_00248_res = cgc_delimited_read(0, &read_00248, &read_00248_len, read_00248_delim, 1);
      if (read_00248_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00248_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00248_ptr += cgc_data_match(read_00248 + read_00248_ptr, read_00248_len - read_00248_ptr, match_00248_00000, 42);
      cgc_free(read_00248);
      if (read_00248_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00249;
      unsigned int read_00249_len;
      unsigned int read_00249_ptr = 0;
      //**** delimited read
      static unsigned char read_00249_delim[] = 
         "\x0a";
      read_00249 = NULL;
      read_00249_len = 0;
      int read_00249_res = cgc_delimited_read(0, &read_00249, &read_00249_len, read_00249_delim, 1);
      if (read_00249_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00249_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00249_ptr += cgc_data_match(read_00249 + read_00249_ptr, read_00249_len - read_00249_ptr, match_00249_00000, 29);
      cgc_free(read_00249);
      if (read_00249_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00250;
      unsigned int read_00250_len;
      unsigned int read_00250_ptr = 0;
      //**** delimited read
      static unsigned char read_00250_delim[] = 
         "\x0a";
      read_00250 = NULL;
      read_00250_len = 0;
      int read_00250_res = cgc_delimited_read(0, &read_00250, &read_00250_len, read_00250_delim, 1);
      if (read_00250_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00250_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00250_ptr += cgc_data_match(read_00250 + read_00250_ptr, read_00250_len - read_00250_ptr, match_00250_00000, 42);
      cgc_free(read_00250);
      if (read_00250_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00251;
      unsigned int read_00251_len;
      unsigned int read_00251_ptr = 0;
      //**** delimited read
      static unsigned char read_00251_delim[] = 
         "\x0a";
      read_00251 = NULL;
      read_00251_len = 0;
      int read_00251_res = cgc_delimited_read(0, &read_00251, &read_00251_len, read_00251_delim, 1);
      if (read_00251_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00251_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00251_ptr += cgc_data_match(read_00251 + read_00251_ptr, read_00251_len - read_00251_ptr, match_00251_00000, 8);
      cgc_free(read_00251);
      if (read_00251_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00190_00000[] = 
         "\x44\x0a";
      static unsigned int write_00190_00000_len = 2;
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = cgc_append_buf(write_00190, &write_00190_len, write_00190_00000, write_00190_00000_len);
      if (write_00190_len > 0) {
         cgc_transmit_all(1, write_00190, write_00190_len);
      }
      cgc_free(write_00190);
   } while (0);
   do {
      unsigned char *read_00252;
      unsigned int read_00252_len;
      unsigned int read_00252_ptr = 0;
      //**** delimited read
      static unsigned char read_00252_delim[] = 
         "\x0a";
      read_00252 = NULL;
      read_00252_len = 0;
      int read_00252_res = cgc_delimited_read(0, &read_00252, &read_00252_len, read_00252_delim, 1);
      if (read_00252_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00252_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00252_ptr += cgc_data_match(read_00252 + read_00252_ptr, read_00252_len - read_00252_ptr, match_00252_00000, 47);
      cgc_free(read_00252);
      if (read_00252_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00253;
      unsigned int read_00253_len;
      unsigned int read_00253_ptr = 0;
      //**** delimited read
      static unsigned char read_00253_delim[] = 
         "\x0a";
      read_00253 = NULL;
      read_00253_len = 0;
      int read_00253_res = cgc_delimited_read(0, &read_00253, &read_00253_len, read_00253_delim, 1);
      if (read_00253_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00253_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00253_ptr += cgc_data_match(read_00253 + read_00253_ptr, read_00253_len - read_00253_ptr, match_00253_00000, 8);
      cgc_free(read_00253);
      if (read_00253_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00191_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00191_00000_len = 2;
      unsigned char *write_00191 = NULL;
      unsigned int write_00191_len = 0;
      write_00191 = cgc_append_buf(write_00191, &write_00191_len, write_00191_00000, write_00191_00000_len);
      if (write_00191_len > 0) {
         cgc_transmit_all(1, write_00191, write_00191_len);
      }
      cgc_free(write_00191);
   } while (0);
   do {
      unsigned char *read_00254;
      unsigned int read_00254_len;
      unsigned int read_00254_ptr = 0;
      //**** delimited read
      static unsigned char read_00254_delim[] = 
         "\x0a";
      read_00254 = NULL;
      read_00254_len = 0;
      int read_00254_res = cgc_delimited_read(0, &read_00254, &read_00254_len, read_00254_delim, 1);
      if (read_00254_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00254_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00254_ptr += cgc_data_match(read_00254 + read_00254_ptr, read_00254_len - read_00254_ptr, match_00254_00000, 6);
      cgc_free(read_00254);
      if (read_00254_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00192_00000[] = 
         "\x31\x39\x0a";
      static unsigned int write_00192_00000_len = 3;
      unsigned char *write_00192 = NULL;
      unsigned int write_00192_len = 0;
      write_00192 = cgc_append_buf(write_00192, &write_00192_len, write_00192_00000, write_00192_00000_len);
      if (write_00192_len > 0) {
         cgc_transmit_all(1, write_00192, write_00192_len);
      }
      cgc_free(write_00192);
   } while (0);
   do {
      unsigned char *read_00255;
      unsigned int read_00255_len;
      unsigned int read_00255_ptr = 0;
      //**** delimited read
      static unsigned char read_00255_delim[] = 
         "\x0a";
      read_00255 = NULL;
      read_00255_len = 0;
      int read_00255_res = cgc_delimited_read(0, &read_00255, &read_00255_len, read_00255_delim, 1);
      if (read_00255_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00255_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00255_ptr += cgc_data_match(read_00255 + read_00255_ptr, read_00255_len - read_00255_ptr, match_00255_00000, 47);
      cgc_free(read_00255);
      if (read_00255_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00256;
      unsigned int read_00256_len;
      unsigned int read_00256_ptr = 0;
      //**** delimited read
      static unsigned char read_00256_delim[] = 
         "\x0a";
      read_00256 = NULL;
      read_00256_len = 0;
      int read_00256_res = cgc_delimited_read(0, &read_00256, &read_00256_len, read_00256_delim, 1);
      if (read_00256_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00256_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00256_ptr += cgc_data_match(read_00256 + read_00256_ptr, read_00256_len - read_00256_ptr, match_00256_00000, 8);
      cgc_free(read_00256);
      if (read_00256_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00193_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00193_00000_len = 2;
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = cgc_append_buf(write_00193, &write_00193_len, write_00193_00000, write_00193_00000_len);
      if (write_00193_len > 0) {
         cgc_transmit_all(1, write_00193, write_00193_len);
      }
      cgc_free(write_00193);
   } while (0);
   do {
      unsigned char *read_00257;
      unsigned int read_00257_len;
      unsigned int read_00257_ptr = 0;
      //**** delimited read
      static unsigned char read_00257_delim[] = 
         "\x0a";
      read_00257 = NULL;
      read_00257_len = 0;
      int read_00257_res = cgc_delimited_read(0, &read_00257, &read_00257_len, read_00257_delim, 1);
      if (read_00257_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00257_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00257_ptr += cgc_data_match(read_00257 + read_00257_ptr, read_00257_len - read_00257_ptr, match_00257_00000, 6);
      cgc_free(read_00257);
      if (read_00257_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00194_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00194_00000_len = 3;
      unsigned char *write_00194 = NULL;
      unsigned int write_00194_len = 0;
      write_00194 = cgc_append_buf(write_00194, &write_00194_len, write_00194_00000, write_00194_00000_len);
      if (write_00194_len > 0) {
         cgc_transmit_all(1, write_00194, write_00194_len);
      }
      cgc_free(write_00194);
   } while (0);
   do {
      unsigned char *read_00258;
      unsigned int read_00258_len;
      unsigned int read_00258_ptr = 0;
      //**** delimited read
      static unsigned char read_00258_delim[] = 
         "\x0a";
      read_00258 = NULL;
      read_00258_len = 0;
      int read_00258_res = cgc_delimited_read(0, &read_00258, &read_00258_len, read_00258_delim, 1);
      if (read_00258_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00258_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00258_ptr += cgc_data_match(read_00258 + read_00258_ptr, read_00258_len - read_00258_ptr, match_00258_00000, 29);
      cgc_free(read_00258);
      if (read_00258_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00259;
      unsigned int read_00259_len;
      unsigned int read_00259_ptr = 0;
      //**** delimited read
      static unsigned char read_00259_delim[] = 
         "\x0a";
      read_00259 = NULL;
      read_00259_len = 0;
      int read_00259_res = cgc_delimited_read(0, &read_00259, &read_00259_len, read_00259_delim, 1);
      if (read_00259_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00259_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00259_ptr += cgc_data_match(read_00259 + read_00259_ptr, read_00259_len - read_00259_ptr, match_00259_00000, 42);
      cgc_free(read_00259);
      if (read_00259_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00260;
      unsigned int read_00260_len;
      unsigned int read_00260_ptr = 0;
      //**** delimited read
      static unsigned char read_00260_delim[] = 
         "\x0a";
      read_00260 = NULL;
      read_00260_len = 0;
      int read_00260_res = cgc_delimited_read(0, &read_00260, &read_00260_len, read_00260_delim, 1);
      if (read_00260_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00260_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00260_ptr += cgc_data_match(read_00260 + read_00260_ptr, read_00260_len - read_00260_ptr, match_00260_00000, 29);
      cgc_free(read_00260);
      if (read_00260_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00261;
      unsigned int read_00261_len;
      unsigned int read_00261_ptr = 0;
      //**** delimited read
      static unsigned char read_00261_delim[] = 
         "\x0a";
      read_00261 = NULL;
      read_00261_len = 0;
      int read_00261_res = cgc_delimited_read(0, &read_00261, &read_00261_len, read_00261_delim, 1);
      if (read_00261_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00261_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00261_ptr += cgc_data_match(read_00261 + read_00261_ptr, read_00261_len - read_00261_ptr, match_00261_00000, 42);
      cgc_free(read_00261);
      if (read_00261_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00262;
      unsigned int read_00262_len;
      unsigned int read_00262_ptr = 0;
      //**** delimited read
      static unsigned char read_00262_delim[] = 
         "\x0a";
      read_00262 = NULL;
      read_00262_len = 0;
      int read_00262_res = cgc_delimited_read(0, &read_00262, &read_00262_len, read_00262_delim, 1);
      if (read_00262_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00262_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00262_ptr += cgc_data_match(read_00262 + read_00262_ptr, read_00262_len - read_00262_ptr, match_00262_00000, 8);
      cgc_free(read_00262);
      if (read_00262_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00195_00000[] = 
         "\x44\x0a";
      static unsigned int write_00195_00000_len = 2;
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = cgc_append_buf(write_00195, &write_00195_len, write_00195_00000, write_00195_00000_len);
      if (write_00195_len > 0) {
         cgc_transmit_all(1, write_00195, write_00195_len);
      }
      cgc_free(write_00195);
   } while (0);
   do {
      unsigned char *read_00263;
      unsigned int read_00263_len;
      unsigned int read_00263_ptr = 0;
      //**** delimited read
      static unsigned char read_00263_delim[] = 
         "\x0a";
      read_00263 = NULL;
      read_00263_len = 0;
      int read_00263_res = cgc_delimited_read(0, &read_00263, &read_00263_len, read_00263_delim, 1);
      if (read_00263_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00263_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00263_ptr += cgc_data_match(read_00263 + read_00263_ptr, read_00263_len - read_00263_ptr, match_00263_00000, 47);
      cgc_free(read_00263);
      if (read_00263_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00264;
      unsigned int read_00264_len;
      unsigned int read_00264_ptr = 0;
      //**** delimited read
      static unsigned char read_00264_delim[] = 
         "\x0a";
      read_00264 = NULL;
      read_00264_len = 0;
      int read_00264_res = cgc_delimited_read(0, &read_00264, &read_00264_len, read_00264_delim, 1);
      if (read_00264_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00264_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00264_ptr += cgc_data_match(read_00264 + read_00264_ptr, read_00264_len - read_00264_ptr, match_00264_00000, 8);
      cgc_free(read_00264);
      if (read_00264_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00196_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00196_00000_len = 2;
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = cgc_append_buf(write_00196, &write_00196_len, write_00196_00000, write_00196_00000_len);
      if (write_00196_len > 0) {
         cgc_transmit_all(1, write_00196, write_00196_len);
      }
      cgc_free(write_00196);
   } while (0);
   do {
      unsigned char *read_00265;
      unsigned int read_00265_len;
      unsigned int read_00265_ptr = 0;
      //**** delimited read
      static unsigned char read_00265_delim[] = 
         "\x0a";
      read_00265 = NULL;
      read_00265_len = 0;
      int read_00265_res = cgc_delimited_read(0, &read_00265, &read_00265_len, read_00265_delim, 1);
      if (read_00265_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00265_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00265_ptr += cgc_data_match(read_00265 + read_00265_ptr, read_00265_len - read_00265_ptr, match_00265_00000, 6);
      cgc_free(read_00265);
      if (read_00265_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00197_00000[] = 
         "\x32\x31\x0a";
      static unsigned int write_00197_00000_len = 3;
      unsigned char *write_00197 = NULL;
      unsigned int write_00197_len = 0;
      write_00197 = cgc_append_buf(write_00197, &write_00197_len, write_00197_00000, write_00197_00000_len);
      if (write_00197_len > 0) {
         cgc_transmit_all(1, write_00197, write_00197_len);
      }
      cgc_free(write_00197);
   } while (0);
   do {
      unsigned char *read_00266;
      unsigned int read_00266_len;
      unsigned int read_00266_ptr = 0;
      //**** delimited read
      static unsigned char read_00266_delim[] = 
         "\x0a";
      read_00266 = NULL;
      read_00266_len = 0;
      int read_00266_res = cgc_delimited_read(0, &read_00266, &read_00266_len, read_00266_delim, 1);
      if (read_00266_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00266_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00266_ptr += cgc_data_match(read_00266 + read_00266_ptr, read_00266_len - read_00266_ptr, match_00266_00000, 47);
      cgc_free(read_00266);
      if (read_00266_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00267;
      unsigned int read_00267_len;
      unsigned int read_00267_ptr = 0;
      //**** delimited read
      static unsigned char read_00267_delim[] = 
         "\x0a";
      read_00267 = NULL;
      read_00267_len = 0;
      int read_00267_res = cgc_delimited_read(0, &read_00267, &read_00267_len, read_00267_delim, 1);
      if (read_00267_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00267_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00267_ptr += cgc_data_match(read_00267 + read_00267_ptr, read_00267_len - read_00267_ptr, match_00267_00000, 8);
      cgc_free(read_00267);
      if (read_00267_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00198_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00198_00000_len = 2;
      unsigned char *write_00198 = NULL;
      unsigned int write_00198_len = 0;
      write_00198 = cgc_append_buf(write_00198, &write_00198_len, write_00198_00000, write_00198_00000_len);
      if (write_00198_len > 0) {
         cgc_transmit_all(1, write_00198, write_00198_len);
      }
      cgc_free(write_00198);
   } while (0);
   do {
      unsigned char *read_00268;
      unsigned int read_00268_len;
      unsigned int read_00268_ptr = 0;
      //**** delimited read
      static unsigned char read_00268_delim[] = 
         "\x0a";
      read_00268 = NULL;
      read_00268_len = 0;
      int read_00268_res = cgc_delimited_read(0, &read_00268, &read_00268_len, read_00268_delim, 1);
      if (read_00268_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00268_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00268_ptr += cgc_data_match(read_00268 + read_00268_ptr, read_00268_len - read_00268_ptr, match_00268_00000, 6);
      cgc_free(read_00268);
      if (read_00268_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00199_00000[] = 
         "\x32\x32\x0a";
      static unsigned int write_00199_00000_len = 3;
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = cgc_append_buf(write_00199, &write_00199_len, write_00199_00000, write_00199_00000_len);
      if (write_00199_len > 0) {
         cgc_transmit_all(1, write_00199, write_00199_len);
      }
      cgc_free(write_00199);
   } while (0);
   do {
      unsigned char *read_00269;
      unsigned int read_00269_len;
      unsigned int read_00269_ptr = 0;
      //**** delimited read
      static unsigned char read_00269_delim[] = 
         "\x0a";
      read_00269 = NULL;
      read_00269_len = 0;
      int read_00269_res = cgc_delimited_read(0, &read_00269, &read_00269_len, read_00269_delim, 1);
      if (read_00269_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00269_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00269_ptr += cgc_data_match(read_00269 + read_00269_ptr, read_00269_len - read_00269_ptr, match_00269_00000, 29);
      cgc_free(read_00269);
      if (read_00269_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00270;
      unsigned int read_00270_len;
      unsigned int read_00270_ptr = 0;
      //**** delimited read
      static unsigned char read_00270_delim[] = 
         "\x0a";
      read_00270 = NULL;
      read_00270_len = 0;
      int read_00270_res = cgc_delimited_read(0, &read_00270, &read_00270_len, read_00270_delim, 1);
      if (read_00270_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00270_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00270_ptr += cgc_data_match(read_00270 + read_00270_ptr, read_00270_len - read_00270_ptr, match_00270_00000, 42);
      cgc_free(read_00270);
      if (read_00270_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00271;
      unsigned int read_00271_len;
      unsigned int read_00271_ptr = 0;
      //**** delimited read
      static unsigned char read_00271_delim[] = 
         "\x0a";
      read_00271 = NULL;
      read_00271_len = 0;
      int read_00271_res = cgc_delimited_read(0, &read_00271, &read_00271_len, read_00271_delim, 1);
      if (read_00271_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00271_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00271_ptr += cgc_data_match(read_00271 + read_00271_ptr, read_00271_len - read_00271_ptr, match_00271_00000, 29);
      cgc_free(read_00271);
      if (read_00271_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00272;
      unsigned int read_00272_len;
      unsigned int read_00272_ptr = 0;
      //**** delimited read
      static unsigned char read_00272_delim[] = 
         "\x0a";
      read_00272 = NULL;
      read_00272_len = 0;
      int read_00272_res = cgc_delimited_read(0, &read_00272, &read_00272_len, read_00272_delim, 1);
      if (read_00272_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00272_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00272_ptr += cgc_data_match(read_00272 + read_00272_ptr, read_00272_len - read_00272_ptr, match_00272_00000, 42);
      cgc_free(read_00272);
      if (read_00272_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00273;
      unsigned int read_00273_len;
      unsigned int read_00273_ptr = 0;
      //**** delimited read
      static unsigned char read_00273_delim[] = 
         "\x0a";
      read_00273 = NULL;
      read_00273_len = 0;
      int read_00273_res = cgc_delimited_read(0, &read_00273, &read_00273_len, read_00273_delim, 1);
      if (read_00273_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00273_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00273_ptr += cgc_data_match(read_00273 + read_00273_ptr, read_00273_len - read_00273_ptr, match_00273_00000, 8);
      cgc_free(read_00273);
      if (read_00273_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00200_00000[] = 
         "\x44\x0a";
      static unsigned int write_00200_00000_len = 2;
      unsigned char *write_00200 = NULL;
      unsigned int write_00200_len = 0;
      write_00200 = cgc_append_buf(write_00200, &write_00200_len, write_00200_00000, write_00200_00000_len);
      if (write_00200_len > 0) {
         cgc_transmit_all(1, write_00200, write_00200_len);
      }
      cgc_free(write_00200);
   } while (0);
   do {
      unsigned char *read_00274;
      unsigned int read_00274_len;
      unsigned int read_00274_ptr = 0;
      //**** delimited read
      static unsigned char read_00274_delim[] = 
         "\x0a";
      read_00274 = NULL;
      read_00274_len = 0;
      int read_00274_res = cgc_delimited_read(0, &read_00274, &read_00274_len, read_00274_delim, 1);
      if (read_00274_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00274_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00274_ptr += cgc_data_match(read_00274 + read_00274_ptr, read_00274_len - read_00274_ptr, match_00274_00000, 47);
      cgc_free(read_00274);
      if (read_00274_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00275;
      unsigned int read_00275_len;
      unsigned int read_00275_ptr = 0;
      //**** delimited read
      static unsigned char read_00275_delim[] = 
         "\x0a";
      read_00275 = NULL;
      read_00275_len = 0;
      int read_00275_res = cgc_delimited_read(0, &read_00275, &read_00275_len, read_00275_delim, 1);
      if (read_00275_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00275_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00275_ptr += cgc_data_match(read_00275 + read_00275_ptr, read_00275_len - read_00275_ptr, match_00275_00000, 8);
      cgc_free(read_00275);
      if (read_00275_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00201_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00201_00000_len = 2;
      unsigned char *write_00201 = NULL;
      unsigned int write_00201_len = 0;
      write_00201 = cgc_append_buf(write_00201, &write_00201_len, write_00201_00000, write_00201_00000_len);
      if (write_00201_len > 0) {
         cgc_transmit_all(1, write_00201, write_00201_len);
      }
      cgc_free(write_00201);
   } while (0);
   do {
      unsigned char *read_00276;
      unsigned int read_00276_len;
      unsigned int read_00276_ptr = 0;
      //**** delimited read
      static unsigned char read_00276_delim[] = 
         "\x0a";
      read_00276 = NULL;
      read_00276_len = 0;
      int read_00276_res = cgc_delimited_read(0, &read_00276, &read_00276_len, read_00276_delim, 1);
      if (read_00276_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00276_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00276_ptr += cgc_data_match(read_00276 + read_00276_ptr, read_00276_len - read_00276_ptr, match_00276_00000, 6);
      cgc_free(read_00276);
      if (read_00276_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00202_00000[] = 
         "\x32\x33\x0a";
      static unsigned int write_00202_00000_len = 3;
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = cgc_append_buf(write_00202, &write_00202_len, write_00202_00000, write_00202_00000_len);
      if (write_00202_len > 0) {
         cgc_transmit_all(1, write_00202, write_00202_len);
      }
      cgc_free(write_00202);
   } while (0);
   do {
      unsigned char *read_00277;
      unsigned int read_00277_len;
      unsigned int read_00277_ptr = 0;
      //**** delimited read
      static unsigned char read_00277_delim[] = 
         "\x0a";
      read_00277 = NULL;
      read_00277_len = 0;
      int read_00277_res = cgc_delimited_read(0, &read_00277, &read_00277_len, read_00277_delim, 1);
      if (read_00277_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00277_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00277_ptr += cgc_data_match(read_00277 + read_00277_ptr, read_00277_len - read_00277_ptr, match_00277_00000, 47);
      cgc_free(read_00277);
      if (read_00277_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00278;
      unsigned int read_00278_len;
      unsigned int read_00278_ptr = 0;
      //**** delimited read
      static unsigned char read_00278_delim[] = 
         "\x0a";
      read_00278 = NULL;
      read_00278_len = 0;
      int read_00278_res = cgc_delimited_read(0, &read_00278, &read_00278_len, read_00278_delim, 1);
      if (read_00278_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00278_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00278_ptr += cgc_data_match(read_00278 + read_00278_ptr, read_00278_len - read_00278_ptr, match_00278_00000, 8);
      cgc_free(read_00278);
      if (read_00278_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00203_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00203_00000_len = 2;
      unsigned char *write_00203 = NULL;
      unsigned int write_00203_len = 0;
      write_00203 = cgc_append_buf(write_00203, &write_00203_len, write_00203_00000, write_00203_00000_len);
      if (write_00203_len > 0) {
         cgc_transmit_all(1, write_00203, write_00203_len);
      }
      cgc_free(write_00203);
   } while (0);
   do {
      unsigned char *read_00279;
      unsigned int read_00279_len;
      unsigned int read_00279_ptr = 0;
      //**** delimited read
      static unsigned char read_00279_delim[] = 
         "\x0a";
      read_00279 = NULL;
      read_00279_len = 0;
      int read_00279_res = cgc_delimited_read(0, &read_00279, &read_00279_len, read_00279_delim, 1);
      if (read_00279_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00279_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00279_ptr += cgc_data_match(read_00279 + read_00279_ptr, read_00279_len - read_00279_ptr, match_00279_00000, 6);
      cgc_free(read_00279);
      if (read_00279_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00204_00000[] = 
         "\x32\x34\x0a";
      static unsigned int write_00204_00000_len = 3;
      unsigned char *write_00204 = NULL;
      unsigned int write_00204_len = 0;
      write_00204 = cgc_append_buf(write_00204, &write_00204_len, write_00204_00000, write_00204_00000_len);
      if (write_00204_len > 0) {
         cgc_transmit_all(1, write_00204, write_00204_len);
      }
      cgc_free(write_00204);
   } while (0);
   do {
      unsigned char *read_00280;
      unsigned int read_00280_len;
      unsigned int read_00280_ptr = 0;
      //**** delimited read
      static unsigned char read_00280_delim[] = 
         "\x0a";
      read_00280 = NULL;
      read_00280_len = 0;
      int read_00280_res = cgc_delimited_read(0, &read_00280, &read_00280_len, read_00280_delim, 1);
      if (read_00280_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00280_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00280_ptr += cgc_data_match(read_00280 + read_00280_ptr, read_00280_len - read_00280_ptr, match_00280_00000, 29);
      cgc_free(read_00280);
      if (read_00280_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00281;
      unsigned int read_00281_len;
      unsigned int read_00281_ptr = 0;
      //**** delimited read
      static unsigned char read_00281_delim[] = 
         "\x0a";
      read_00281 = NULL;
      read_00281_len = 0;
      int read_00281_res = cgc_delimited_read(0, &read_00281, &read_00281_len, read_00281_delim, 1);
      if (read_00281_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00281_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00281_ptr += cgc_data_match(read_00281 + read_00281_ptr, read_00281_len - read_00281_ptr, match_00281_00000, 42);
      cgc_free(read_00281);
      if (read_00281_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00282;
      unsigned int read_00282_len;
      unsigned int read_00282_ptr = 0;
      //**** delimited read
      static unsigned char read_00282_delim[] = 
         "\x0a";
      read_00282 = NULL;
      read_00282_len = 0;
      int read_00282_res = cgc_delimited_read(0, &read_00282, &read_00282_len, read_00282_delim, 1);
      if (read_00282_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00282_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00282_ptr += cgc_data_match(read_00282 + read_00282_ptr, read_00282_len - read_00282_ptr, match_00282_00000, 29);
      cgc_free(read_00282);
      if (read_00282_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00283;
      unsigned int read_00283_len;
      unsigned int read_00283_ptr = 0;
      //**** delimited read
      static unsigned char read_00283_delim[] = 
         "\x0a";
      read_00283 = NULL;
      read_00283_len = 0;
      int read_00283_res = cgc_delimited_read(0, &read_00283, &read_00283_len, read_00283_delim, 1);
      if (read_00283_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00283_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00283_ptr += cgc_data_match(read_00283 + read_00283_ptr, read_00283_len - read_00283_ptr, match_00283_00000, 42);
      cgc_free(read_00283);
      if (read_00283_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00284;
      unsigned int read_00284_len;
      unsigned int read_00284_ptr = 0;
      //**** delimited read
      static unsigned char read_00284_delim[] = 
         "\x0a";
      read_00284 = NULL;
      read_00284_len = 0;
      int read_00284_res = cgc_delimited_read(0, &read_00284, &read_00284_len, read_00284_delim, 1);
      if (read_00284_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00284_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00284_ptr += cgc_data_match(read_00284 + read_00284_ptr, read_00284_len - read_00284_ptr, match_00284_00000, 8);
      cgc_free(read_00284);
      if (read_00284_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00205_00000[] = 
         "\x44\x0a";
      static unsigned int write_00205_00000_len = 2;
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = cgc_append_buf(write_00205, &write_00205_len, write_00205_00000, write_00205_00000_len);
      if (write_00205_len > 0) {
         cgc_transmit_all(1, write_00205, write_00205_len);
      }
      cgc_free(write_00205);
   } while (0);
   do {
      unsigned char *read_00285;
      unsigned int read_00285_len;
      unsigned int read_00285_ptr = 0;
      //**** delimited read
      static unsigned char read_00285_delim[] = 
         "\x0a";
      read_00285 = NULL;
      read_00285_len = 0;
      int read_00285_res = cgc_delimited_read(0, &read_00285, &read_00285_len, read_00285_delim, 1);
      if (read_00285_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00285_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00285_ptr += cgc_data_match(read_00285 + read_00285_ptr, read_00285_len - read_00285_ptr, match_00285_00000, 47);
      cgc_free(read_00285);
      if (read_00285_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00286;
      unsigned int read_00286_len;
      unsigned int read_00286_ptr = 0;
      //**** delimited read
      static unsigned char read_00286_delim[] = 
         "\x0a";
      read_00286 = NULL;
      read_00286_len = 0;
      int read_00286_res = cgc_delimited_read(0, &read_00286, &read_00286_len, read_00286_delim, 1);
      if (read_00286_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00286_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00286_ptr += cgc_data_match(read_00286 + read_00286_ptr, read_00286_len - read_00286_ptr, match_00286_00000, 8);
      cgc_free(read_00286);
      if (read_00286_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00206_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00206_00000_len = 2;
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = cgc_append_buf(write_00206, &write_00206_len, write_00206_00000, write_00206_00000_len);
      if (write_00206_len > 0) {
         cgc_transmit_all(1, write_00206, write_00206_len);
      }
      cgc_free(write_00206);
   } while (0);
   do {
      unsigned char *read_00287;
      unsigned int read_00287_len;
      unsigned int read_00287_ptr = 0;
      //**** delimited read
      static unsigned char read_00287_delim[] = 
         "\x0a";
      read_00287 = NULL;
      read_00287_len = 0;
      int read_00287_res = cgc_delimited_read(0, &read_00287, &read_00287_len, read_00287_delim, 1);
      if (read_00287_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00287_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00287_ptr += cgc_data_match(read_00287 + read_00287_ptr, read_00287_len - read_00287_ptr, match_00287_00000, 6);
      cgc_free(read_00287);
      if (read_00287_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00207_00000[] = 
         "\x32\x35\x0a";
      static unsigned int write_00207_00000_len = 3;
      unsigned char *write_00207 = NULL;
      unsigned int write_00207_len = 0;
      write_00207 = cgc_append_buf(write_00207, &write_00207_len, write_00207_00000, write_00207_00000_len);
      if (write_00207_len > 0) {
         cgc_transmit_all(1, write_00207, write_00207_len);
      }
      cgc_free(write_00207);
   } while (0);
   do {
      unsigned char *read_00288;
      unsigned int read_00288_len;
      unsigned int read_00288_ptr = 0;
      //**** delimited read
      static unsigned char read_00288_delim[] = 
         "\x0a";
      read_00288 = NULL;
      read_00288_len = 0;
      int read_00288_res = cgc_delimited_read(0, &read_00288, &read_00288_len, read_00288_delim, 1);
      if (read_00288_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00288_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00288_ptr += cgc_data_match(read_00288 + read_00288_ptr, read_00288_len - read_00288_ptr, match_00288_00000, 47);
      cgc_free(read_00288);
      if (read_00288_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00289;
      unsigned int read_00289_len;
      unsigned int read_00289_ptr = 0;
      //**** delimited read
      static unsigned char read_00289_delim[] = 
         "\x0a";
      read_00289 = NULL;
      read_00289_len = 0;
      int read_00289_res = cgc_delimited_read(0, &read_00289, &read_00289_len, read_00289_delim, 1);
      if (read_00289_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00289_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00289_ptr += cgc_data_match(read_00289 + read_00289_ptr, read_00289_len - read_00289_ptr, match_00289_00000, 8);
      cgc_free(read_00289);
      if (read_00289_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00208_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00208_00000_len = 2;
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = cgc_append_buf(write_00208, &write_00208_len, write_00208_00000, write_00208_00000_len);
      if (write_00208_len > 0) {
         cgc_transmit_all(1, write_00208, write_00208_len);
      }
      cgc_free(write_00208);
   } while (0);
   do {
      unsigned char *read_00290;
      unsigned int read_00290_len;
      unsigned int read_00290_ptr = 0;
      //**** delimited read
      static unsigned char read_00290_delim[] = 
         "\x0a";
      read_00290 = NULL;
      read_00290_len = 0;
      int read_00290_res = cgc_delimited_read(0, &read_00290, &read_00290_len, read_00290_delim, 1);
      if (read_00290_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00290_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00290_ptr += cgc_data_match(read_00290 + read_00290_ptr, read_00290_len - read_00290_ptr, match_00290_00000, 6);
      cgc_free(read_00290);
      if (read_00290_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00209_00000[] = 
         "\x32\x36\x0a";
      static unsigned int write_00209_00000_len = 3;
      unsigned char *write_00209 = NULL;
      unsigned int write_00209_len = 0;
      write_00209 = cgc_append_buf(write_00209, &write_00209_len, write_00209_00000, write_00209_00000_len);
      if (write_00209_len > 0) {
         cgc_transmit_all(1, write_00209, write_00209_len);
      }
      cgc_free(write_00209);
   } while (0);
   do {
      unsigned char *read_00291;
      unsigned int read_00291_len;
      unsigned int read_00291_ptr = 0;
      //**** delimited read
      static unsigned char read_00291_delim[] = 
         "\x0a";
      read_00291 = NULL;
      read_00291_len = 0;
      int read_00291_res = cgc_delimited_read(0, &read_00291, &read_00291_len, read_00291_delim, 1);
      if (read_00291_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00291_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00291_ptr += cgc_data_match(read_00291 + read_00291_ptr, read_00291_len - read_00291_ptr, match_00291_00000, 29);
      cgc_free(read_00291);
      if (read_00291_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00292;
      unsigned int read_00292_len;
      unsigned int read_00292_ptr = 0;
      //**** delimited read
      static unsigned char read_00292_delim[] = 
         "\x0a";
      read_00292 = NULL;
      read_00292_len = 0;
      int read_00292_res = cgc_delimited_read(0, &read_00292, &read_00292_len, read_00292_delim, 1);
      if (read_00292_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00292_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00292_ptr += cgc_data_match(read_00292 + read_00292_ptr, read_00292_len - read_00292_ptr, match_00292_00000, 42);
      cgc_free(read_00292);
      if (read_00292_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00293;
      unsigned int read_00293_len;
      unsigned int read_00293_ptr = 0;
      //**** delimited read
      static unsigned char read_00293_delim[] = 
         "\x0a";
      read_00293 = NULL;
      read_00293_len = 0;
      int read_00293_res = cgc_delimited_read(0, &read_00293, &read_00293_len, read_00293_delim, 1);
      if (read_00293_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00293_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00293_ptr += cgc_data_match(read_00293 + read_00293_ptr, read_00293_len - read_00293_ptr, match_00293_00000, 29);
      cgc_free(read_00293);
      if (read_00293_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00294;
      unsigned int read_00294_len;
      unsigned int read_00294_ptr = 0;
      //**** delimited read
      static unsigned char read_00294_delim[] = 
         "\x0a";
      read_00294 = NULL;
      read_00294_len = 0;
      int read_00294_res = cgc_delimited_read(0, &read_00294, &read_00294_len, read_00294_delim, 1);
      if (read_00294_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00294_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00294_ptr += cgc_data_match(read_00294 + read_00294_ptr, read_00294_len - read_00294_ptr, match_00294_00000, 42);
      cgc_free(read_00294);
      if (read_00294_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00295;
      unsigned int read_00295_len;
      unsigned int read_00295_ptr = 0;
      //**** delimited read
      static unsigned char read_00295_delim[] = 
         "\x0a";
      read_00295 = NULL;
      read_00295_len = 0;
      int read_00295_res = cgc_delimited_read(0, &read_00295, &read_00295_len, read_00295_delim, 1);
      if (read_00295_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00295_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00295_ptr += cgc_data_match(read_00295 + read_00295_ptr, read_00295_len - read_00295_ptr, match_00295_00000, 8);
      cgc_free(read_00295);
      if (read_00295_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00210_00000[] = 
         "\x44\x0a";
      static unsigned int write_00210_00000_len = 2;
      unsigned char *write_00210 = NULL;
      unsigned int write_00210_len = 0;
      write_00210 = cgc_append_buf(write_00210, &write_00210_len, write_00210_00000, write_00210_00000_len);
      if (write_00210_len > 0) {
         cgc_transmit_all(1, write_00210, write_00210_len);
      }
      cgc_free(write_00210);
   } while (0);
   do {
      unsigned char *read_00296;
      unsigned int read_00296_len;
      unsigned int read_00296_ptr = 0;
      //**** delimited read
      static unsigned char read_00296_delim[] = 
         "\x0a";
      read_00296 = NULL;
      read_00296_len = 0;
      int read_00296_res = cgc_delimited_read(0, &read_00296, &read_00296_len, read_00296_delim, 1);
      if (read_00296_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00296_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00296_ptr += cgc_data_match(read_00296 + read_00296_ptr, read_00296_len - read_00296_ptr, match_00296_00000, 47);
      cgc_free(read_00296);
      if (read_00296_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00297;
      unsigned int read_00297_len;
      unsigned int read_00297_ptr = 0;
      //**** delimited read
      static unsigned char read_00297_delim[] = 
         "\x0a";
      read_00297 = NULL;
      read_00297_len = 0;
      int read_00297_res = cgc_delimited_read(0, &read_00297, &read_00297_len, read_00297_delim, 1);
      if (read_00297_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00297_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00297_ptr += cgc_data_match(read_00297 + read_00297_ptr, read_00297_len - read_00297_ptr, match_00297_00000, 8);
      cgc_free(read_00297);
      if (read_00297_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00211_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00211_00000_len = 2;
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = cgc_append_buf(write_00211, &write_00211_len, write_00211_00000, write_00211_00000_len);
      if (write_00211_len > 0) {
         cgc_transmit_all(1, write_00211, write_00211_len);
      }
      cgc_free(write_00211);
   } while (0);
   do {
      unsigned char *read_00298;
      unsigned int read_00298_len;
      unsigned int read_00298_ptr = 0;
      //**** delimited read
      static unsigned char read_00298_delim[] = 
         "\x0a";
      read_00298 = NULL;
      read_00298_len = 0;
      int read_00298_res = cgc_delimited_read(0, &read_00298, &read_00298_len, read_00298_delim, 1);
      if (read_00298_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00298_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00298_ptr += cgc_data_match(read_00298 + read_00298_ptr, read_00298_len - read_00298_ptr, match_00298_00000, 6);
      cgc_free(read_00298);
      if (read_00298_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00212_00000[] = 
         "\x32\x37\x0a";
      static unsigned int write_00212_00000_len = 3;
      unsigned char *write_00212 = NULL;
      unsigned int write_00212_len = 0;
      write_00212 = cgc_append_buf(write_00212, &write_00212_len, write_00212_00000, write_00212_00000_len);
      if (write_00212_len > 0) {
         cgc_transmit_all(1, write_00212, write_00212_len);
      }
      cgc_free(write_00212);
   } while (0);
   do {
      unsigned char *read_00299;
      unsigned int read_00299_len;
      unsigned int read_00299_ptr = 0;
      //**** delimited read
      static unsigned char read_00299_delim[] = 
         "\x0a";
      read_00299 = NULL;
      read_00299_len = 0;
      int read_00299_res = cgc_delimited_read(0, &read_00299, &read_00299_len, read_00299_delim, 1);
      if (read_00299_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00299_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00299_ptr += cgc_data_match(read_00299 + read_00299_ptr, read_00299_len - read_00299_ptr, match_00299_00000, 47);
      cgc_free(read_00299);
      if (read_00299_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00300;
      unsigned int read_00300_len;
      unsigned int read_00300_ptr = 0;
      //**** delimited read
      static unsigned char read_00300_delim[] = 
         "\x0a";
      read_00300 = NULL;
      read_00300_len = 0;
      int read_00300_res = cgc_delimited_read(0, &read_00300, &read_00300_len, read_00300_delim, 1);
      if (read_00300_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00300_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00300_ptr += cgc_data_match(read_00300 + read_00300_ptr, read_00300_len - read_00300_ptr, match_00300_00000, 8);
      cgc_free(read_00300);
      if (read_00300_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00213_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00213_00000_len = 2;
      unsigned char *write_00213 = NULL;
      unsigned int write_00213_len = 0;
      write_00213 = cgc_append_buf(write_00213, &write_00213_len, write_00213_00000, write_00213_00000_len);
      if (write_00213_len > 0) {
         cgc_transmit_all(1, write_00213, write_00213_len);
      }
      cgc_free(write_00213);
   } while (0);
   do {
      unsigned char *read_00301;
      unsigned int read_00301_len;
      unsigned int read_00301_ptr = 0;
      //**** delimited read
      static unsigned char read_00301_delim[] = 
         "\x0a";
      read_00301 = NULL;
      read_00301_len = 0;
      int read_00301_res = cgc_delimited_read(0, &read_00301, &read_00301_len, read_00301_delim, 1);
      if (read_00301_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00301_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00301_ptr += cgc_data_match(read_00301 + read_00301_ptr, read_00301_len - read_00301_ptr, match_00301_00000, 6);
      cgc_free(read_00301);
      if (read_00301_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00214_00000[] = 
         "\x32\x38\x0a";
      static unsigned int write_00214_00000_len = 3;
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = cgc_append_buf(write_00214, &write_00214_len, write_00214_00000, write_00214_00000_len);
      if (write_00214_len > 0) {
         cgc_transmit_all(1, write_00214, write_00214_len);
      }
      cgc_free(write_00214);
   } while (0);
   do {
      unsigned char *read_00302;
      unsigned int read_00302_len;
      unsigned int read_00302_ptr = 0;
      //**** delimited read
      static unsigned char read_00302_delim[] = 
         "\x0a";
      read_00302 = NULL;
      read_00302_len = 0;
      int read_00302_res = cgc_delimited_read(0, &read_00302, &read_00302_len, read_00302_delim, 1);
      if (read_00302_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00302_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00302_ptr += cgc_data_match(read_00302 + read_00302_ptr, read_00302_len - read_00302_ptr, match_00302_00000, 29);
      cgc_free(read_00302);
      if (read_00302_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00303;
      unsigned int read_00303_len;
      unsigned int read_00303_ptr = 0;
      //**** delimited read
      static unsigned char read_00303_delim[] = 
         "\x0a";
      read_00303 = NULL;
      read_00303_len = 0;
      int read_00303_res = cgc_delimited_read(0, &read_00303, &read_00303_len, read_00303_delim, 1);
      if (read_00303_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00303_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00303_ptr += cgc_data_match(read_00303 + read_00303_ptr, read_00303_len - read_00303_ptr, match_00303_00000, 42);
      cgc_free(read_00303);
      if (read_00303_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00304;
      unsigned int read_00304_len;
      unsigned int read_00304_ptr = 0;
      //**** delimited read
      static unsigned char read_00304_delim[] = 
         "\x0a";
      read_00304 = NULL;
      read_00304_len = 0;
      int read_00304_res = cgc_delimited_read(0, &read_00304, &read_00304_len, read_00304_delim, 1);
      if (read_00304_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00304_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00304_ptr += cgc_data_match(read_00304 + read_00304_ptr, read_00304_len - read_00304_ptr, match_00304_00000, 29);
      cgc_free(read_00304);
      if (read_00304_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00305;
      unsigned int read_00305_len;
      unsigned int read_00305_ptr = 0;
      //**** delimited read
      static unsigned char read_00305_delim[] = 
         "\x0a";
      read_00305 = NULL;
      read_00305_len = 0;
      int read_00305_res = cgc_delimited_read(0, &read_00305, &read_00305_len, read_00305_delim, 1);
      if (read_00305_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00305_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00305_ptr += cgc_data_match(read_00305 + read_00305_ptr, read_00305_len - read_00305_ptr, match_00305_00000, 42);
      cgc_free(read_00305);
      if (read_00305_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00306;
      unsigned int read_00306_len;
      unsigned int read_00306_ptr = 0;
      //**** delimited read
      static unsigned char read_00306_delim[] = 
         "\x0a";
      read_00306 = NULL;
      read_00306_len = 0;
      int read_00306_res = cgc_delimited_read(0, &read_00306, &read_00306_len, read_00306_delim, 1);
      if (read_00306_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00306_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00306_ptr += cgc_data_match(read_00306 + read_00306_ptr, read_00306_len - read_00306_ptr, match_00306_00000, 8);
      cgc_free(read_00306);
      if (read_00306_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00215_00000[] = 
         "\x44\x0a";
      static unsigned int write_00215_00000_len = 2;
      unsigned char *write_00215 = NULL;
      unsigned int write_00215_len = 0;
      write_00215 = cgc_append_buf(write_00215, &write_00215_len, write_00215_00000, write_00215_00000_len);
      if (write_00215_len > 0) {
         cgc_transmit_all(1, write_00215, write_00215_len);
      }
      cgc_free(write_00215);
   } while (0);
   do {
      unsigned char *read_00307;
      unsigned int read_00307_len;
      unsigned int read_00307_ptr = 0;
      //**** delimited read
      static unsigned char read_00307_delim[] = 
         "\x0a";
      read_00307 = NULL;
      read_00307_len = 0;
      int read_00307_res = cgc_delimited_read(0, &read_00307, &read_00307_len, read_00307_delim, 1);
      if (read_00307_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00307_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00307_ptr += cgc_data_match(read_00307 + read_00307_ptr, read_00307_len - read_00307_ptr, match_00307_00000, 47);
      cgc_free(read_00307);
      if (read_00307_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00308;
      unsigned int read_00308_len;
      unsigned int read_00308_ptr = 0;
      //**** delimited read
      static unsigned char read_00308_delim[] = 
         "\x0a";
      read_00308 = NULL;
      read_00308_len = 0;
      int read_00308_res = cgc_delimited_read(0, &read_00308, &read_00308_len, read_00308_delim, 1);
      if (read_00308_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00308_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00308_ptr += cgc_data_match(read_00308 + read_00308_ptr, read_00308_len - read_00308_ptr, match_00308_00000, 8);
      cgc_free(read_00308);
      if (read_00308_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00216_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00216_00000_len = 2;
      unsigned char *write_00216 = NULL;
      unsigned int write_00216_len = 0;
      write_00216 = cgc_append_buf(write_00216, &write_00216_len, write_00216_00000, write_00216_00000_len);
      if (write_00216_len > 0) {
         cgc_transmit_all(1, write_00216, write_00216_len);
      }
      cgc_free(write_00216);
   } while (0);
   do {
      unsigned char *read_00309;
      unsigned int read_00309_len;
      unsigned int read_00309_ptr = 0;
      //**** delimited read
      static unsigned char read_00309_delim[] = 
         "\x0a";
      read_00309 = NULL;
      read_00309_len = 0;
      int read_00309_res = cgc_delimited_read(0, &read_00309, &read_00309_len, read_00309_delim, 1);
      if (read_00309_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00309_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00309_ptr += cgc_data_match(read_00309 + read_00309_ptr, read_00309_len - read_00309_ptr, match_00309_00000, 6);
      cgc_free(read_00309);
      if (read_00309_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00217_00000[] = 
         "\x32\x39\x0a";
      static unsigned int write_00217_00000_len = 3;
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = cgc_append_buf(write_00217, &write_00217_len, write_00217_00000, write_00217_00000_len);
      if (write_00217_len > 0) {
         cgc_transmit_all(1, write_00217, write_00217_len);
      }
      cgc_free(write_00217);
   } while (0);
   do {
      unsigned char *read_00310;
      unsigned int read_00310_len;
      unsigned int read_00310_ptr = 0;
      //**** delimited read
      static unsigned char read_00310_delim[] = 
         "\x0a";
      read_00310 = NULL;
      read_00310_len = 0;
      int read_00310_res = cgc_delimited_read(0, &read_00310, &read_00310_len, read_00310_delim, 1);
      if (read_00310_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00310_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00310_ptr += cgc_data_match(read_00310 + read_00310_ptr, read_00310_len - read_00310_ptr, match_00310_00000, 47);
      cgc_free(read_00310);
      if (read_00310_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00311;
      unsigned int read_00311_len;
      unsigned int read_00311_ptr = 0;
      //**** delimited read
      static unsigned char read_00311_delim[] = 
         "\x0a";
      read_00311 = NULL;
      read_00311_len = 0;
      int read_00311_res = cgc_delimited_read(0, &read_00311, &read_00311_len, read_00311_delim, 1);
      if (read_00311_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00311_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00311_ptr += cgc_data_match(read_00311 + read_00311_ptr, read_00311_len - read_00311_ptr, match_00311_00000, 8);
      cgc_free(read_00311);
      if (read_00311_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00218_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00218_00000_len = 2;
      unsigned char *write_00218 = NULL;
      unsigned int write_00218_len = 0;
      write_00218 = cgc_append_buf(write_00218, &write_00218_len, write_00218_00000, write_00218_00000_len);
      if (write_00218_len > 0) {
         cgc_transmit_all(1, write_00218, write_00218_len);
      }
      cgc_free(write_00218);
   } while (0);
   do {
      unsigned char *read_00312;
      unsigned int read_00312_len;
      unsigned int read_00312_ptr = 0;
      //**** delimited read
      static unsigned char read_00312_delim[] = 
         "\x0a";
      read_00312 = NULL;
      read_00312_len = 0;
      int read_00312_res = cgc_delimited_read(0, &read_00312, &read_00312_len, read_00312_delim, 1);
      if (read_00312_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00312_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00312_ptr += cgc_data_match(read_00312 + read_00312_ptr, read_00312_len - read_00312_ptr, match_00312_00000, 6);
      cgc_free(read_00312);
      if (read_00312_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00219_00000[] = 
         "\x33\x30\x0a";
      static unsigned int write_00219_00000_len = 3;
      unsigned char *write_00219 = NULL;
      unsigned int write_00219_len = 0;
      write_00219 = cgc_append_buf(write_00219, &write_00219_len, write_00219_00000, write_00219_00000_len);
      if (write_00219_len > 0) {
         cgc_transmit_all(1, write_00219, write_00219_len);
      }
      cgc_free(write_00219);
   } while (0);
   do {
      unsigned char *read_00313;
      unsigned int read_00313_len;
      unsigned int read_00313_ptr = 0;
      //**** delimited read
      static unsigned char read_00313_delim[] = 
         "\x0a";
      read_00313 = NULL;
      read_00313_len = 0;
      int read_00313_res = cgc_delimited_read(0, &read_00313, &read_00313_len, read_00313_delim, 1);
      if (read_00313_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00313_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00313_ptr += cgc_data_match(read_00313 + read_00313_ptr, read_00313_len - read_00313_ptr, match_00313_00000, 29);
      cgc_free(read_00313);
      if (read_00313_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00314;
      unsigned int read_00314_len;
      unsigned int read_00314_ptr = 0;
      //**** delimited read
      static unsigned char read_00314_delim[] = 
         "\x0a";
      read_00314 = NULL;
      read_00314_len = 0;
      int read_00314_res = cgc_delimited_read(0, &read_00314, &read_00314_len, read_00314_delim, 1);
      if (read_00314_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00314_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00314_ptr += cgc_data_match(read_00314 + read_00314_ptr, read_00314_len - read_00314_ptr, match_00314_00000, 42);
      cgc_free(read_00314);
      if (read_00314_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00315;
      unsigned int read_00315_len;
      unsigned int read_00315_ptr = 0;
      //**** delimited read
      static unsigned char read_00315_delim[] = 
         "\x0a";
      read_00315 = NULL;
      read_00315_len = 0;
      int read_00315_res = cgc_delimited_read(0, &read_00315, &read_00315_len, read_00315_delim, 1);
      if (read_00315_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00315_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00315_ptr += cgc_data_match(read_00315 + read_00315_ptr, read_00315_len - read_00315_ptr, match_00315_00000, 29);
      cgc_free(read_00315);
      if (read_00315_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00316;
      unsigned int read_00316_len;
      unsigned int read_00316_ptr = 0;
      //**** delimited read
      static unsigned char read_00316_delim[] = 
         "\x0a";
      read_00316 = NULL;
      read_00316_len = 0;
      int read_00316_res = cgc_delimited_read(0, &read_00316, &read_00316_len, read_00316_delim, 1);
      if (read_00316_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00316_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00316_ptr += cgc_data_match(read_00316 + read_00316_ptr, read_00316_len - read_00316_ptr, match_00316_00000, 42);
      cgc_free(read_00316);
      if (read_00316_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00317;
      unsigned int read_00317_len;
      unsigned int read_00317_ptr = 0;
      //**** delimited read
      static unsigned char read_00317_delim[] = 
         "\x0a";
      read_00317 = NULL;
      read_00317_len = 0;
      int read_00317_res = cgc_delimited_read(0, &read_00317, &read_00317_len, read_00317_delim, 1);
      if (read_00317_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00317_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00317_ptr += cgc_data_match(read_00317 + read_00317_ptr, read_00317_len - read_00317_ptr, match_00317_00000, 8);
      cgc_free(read_00317);
      if (read_00317_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00220_00000[] = 
         "\x44\x0a";
      static unsigned int write_00220_00000_len = 2;
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = cgc_append_buf(write_00220, &write_00220_len, write_00220_00000, write_00220_00000_len);
      if (write_00220_len > 0) {
         cgc_transmit_all(1, write_00220, write_00220_len);
      }
      cgc_free(write_00220);
   } while (0);
   do {
      unsigned char *read_00318;
      unsigned int read_00318_len;
      unsigned int read_00318_ptr = 0;
      //**** delimited read
      static unsigned char read_00318_delim[] = 
         "\x0a";
      read_00318 = NULL;
      read_00318_len = 0;
      int read_00318_res = cgc_delimited_read(0, &read_00318, &read_00318_len, read_00318_delim, 1);
      if (read_00318_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00318_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00318_ptr += cgc_data_match(read_00318 + read_00318_ptr, read_00318_len - read_00318_ptr, match_00318_00000, 47);
      cgc_free(read_00318);
      if (read_00318_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00319;
      unsigned int read_00319_len;
      unsigned int read_00319_ptr = 0;
      //**** delimited read
      static unsigned char read_00319_delim[] = 
         "\x0a";
      read_00319 = NULL;
      read_00319_len = 0;
      int read_00319_res = cgc_delimited_read(0, &read_00319, &read_00319_len, read_00319_delim, 1);
      if (read_00319_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00319_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00319_ptr += cgc_data_match(read_00319 + read_00319_ptr, read_00319_len - read_00319_ptr, match_00319_00000, 8);
      cgc_free(read_00319);
      if (read_00319_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00221_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00221_00000_len = 2;
      unsigned char *write_00221 = NULL;
      unsigned int write_00221_len = 0;
      write_00221 = cgc_append_buf(write_00221, &write_00221_len, write_00221_00000, write_00221_00000_len);
      if (write_00221_len > 0) {
         cgc_transmit_all(1, write_00221, write_00221_len);
      }
      cgc_free(write_00221);
   } while (0);
   do {
      unsigned char *read_00320;
      unsigned int read_00320_len;
      unsigned int read_00320_ptr = 0;
      //**** delimited read
      static unsigned char read_00320_delim[] = 
         "\x0a";
      read_00320 = NULL;
      read_00320_len = 0;
      int read_00320_res = cgc_delimited_read(0, &read_00320, &read_00320_len, read_00320_delim, 1);
      if (read_00320_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00320_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00320_ptr += cgc_data_match(read_00320 + read_00320_ptr, read_00320_len - read_00320_ptr, match_00320_00000, 6);
      cgc_free(read_00320);
      if (read_00320_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00222_00000[] = 
         "\x33\x31\x0a";
      static unsigned int write_00222_00000_len = 3;
      unsigned char *write_00222 = NULL;
      unsigned int write_00222_len = 0;
      write_00222 = cgc_append_buf(write_00222, &write_00222_len, write_00222_00000, write_00222_00000_len);
      if (write_00222_len > 0) {
         cgc_transmit_all(1, write_00222, write_00222_len);
      }
      cgc_free(write_00222);
   } while (0);
   do {
      unsigned char *read_00321;
      unsigned int read_00321_len;
      unsigned int read_00321_ptr = 0;
      //**** delimited read
      static unsigned char read_00321_delim[] = 
         "\x0a";
      read_00321 = NULL;
      read_00321_len = 0;
      int read_00321_res = cgc_delimited_read(0, &read_00321, &read_00321_len, read_00321_delim, 1);
      if (read_00321_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00321_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00321_ptr += cgc_data_match(read_00321 + read_00321_ptr, read_00321_len - read_00321_ptr, match_00321_00000, 47);
      cgc_free(read_00321);
      if (read_00321_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00322;
      unsigned int read_00322_len;
      unsigned int read_00322_ptr = 0;
      //**** delimited read
      static unsigned char read_00322_delim[] = 
         "\x0a";
      read_00322 = NULL;
      read_00322_len = 0;
      int read_00322_res = cgc_delimited_read(0, &read_00322, &read_00322_len, read_00322_delim, 1);
      if (read_00322_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00322_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00322_ptr += cgc_data_match(read_00322 + read_00322_ptr, read_00322_len - read_00322_ptr, match_00322_00000, 8);
      cgc_free(read_00322);
      if (read_00322_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00223_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00223_00000_len = 2;
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = cgc_append_buf(write_00223, &write_00223_len, write_00223_00000, write_00223_00000_len);
      if (write_00223_len > 0) {
         cgc_transmit_all(1, write_00223, write_00223_len);
      }
      cgc_free(write_00223);
   } while (0);
   do {
      unsigned char *read_00323;
      unsigned int read_00323_len;
      unsigned int read_00323_ptr = 0;
      //**** delimited read
      static unsigned char read_00323_delim[] = 
         "\x0a";
      read_00323 = NULL;
      read_00323_len = 0;
      int read_00323_res = cgc_delimited_read(0, &read_00323, &read_00323_len, read_00323_delim, 1);
      if (read_00323_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00323_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00323_ptr += cgc_data_match(read_00323 + read_00323_ptr, read_00323_len - read_00323_ptr, match_00323_00000, 6);
      cgc_free(read_00323);
      if (read_00323_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00224_00000[] = 
         "\x33\x32\x0a";
      static unsigned int write_00224_00000_len = 3;
      unsigned char *write_00224 = NULL;
      unsigned int write_00224_len = 0;
      write_00224 = cgc_append_buf(write_00224, &write_00224_len, write_00224_00000, write_00224_00000_len);
      if (write_00224_len > 0) {
         cgc_transmit_all(1, write_00224, write_00224_len);
      }
      cgc_free(write_00224);
   } while (0);
   do {
      unsigned char *read_00324;
      unsigned int read_00324_len;
      unsigned int read_00324_ptr = 0;
      //**** delimited read
      static unsigned char read_00324_delim[] = 
         "\x0a";
      read_00324 = NULL;
      read_00324_len = 0;
      int read_00324_res = cgc_delimited_read(0, &read_00324, &read_00324_len, read_00324_delim, 1);
      if (read_00324_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00324_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00324_ptr += cgc_data_match(read_00324 + read_00324_ptr, read_00324_len - read_00324_ptr, match_00324_00000, 29);
      cgc_free(read_00324);
      if (read_00324_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00325;
      unsigned int read_00325_len;
      unsigned int read_00325_ptr = 0;
      //**** delimited read
      static unsigned char read_00325_delim[] = 
         "\x0a";
      read_00325 = NULL;
      read_00325_len = 0;
      int read_00325_res = cgc_delimited_read(0, &read_00325, &read_00325_len, read_00325_delim, 1);
      if (read_00325_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00325_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00325_ptr += cgc_data_match(read_00325 + read_00325_ptr, read_00325_len - read_00325_ptr, match_00325_00000, 42);
      cgc_free(read_00325);
      if (read_00325_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00326;
      unsigned int read_00326_len;
      unsigned int read_00326_ptr = 0;
      //**** delimited read
      static unsigned char read_00326_delim[] = 
         "\x0a";
      read_00326 = NULL;
      read_00326_len = 0;
      int read_00326_res = cgc_delimited_read(0, &read_00326, &read_00326_len, read_00326_delim, 1);
      if (read_00326_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00326_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00326_ptr += cgc_data_match(read_00326 + read_00326_ptr, read_00326_len - read_00326_ptr, match_00326_00000, 29);
      cgc_free(read_00326);
      if (read_00326_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00327;
      unsigned int read_00327_len;
      unsigned int read_00327_ptr = 0;
      //**** delimited read
      static unsigned char read_00327_delim[] = 
         "\x0a";
      read_00327 = NULL;
      read_00327_len = 0;
      int read_00327_res = cgc_delimited_read(0, &read_00327, &read_00327_len, read_00327_delim, 1);
      if (read_00327_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00327_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00327_ptr += cgc_data_match(read_00327 + read_00327_ptr, read_00327_len - read_00327_ptr, match_00327_00000, 42);
      cgc_free(read_00327);
      if (read_00327_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00328;
      unsigned int read_00328_len;
      unsigned int read_00328_ptr = 0;
      //**** delimited read
      static unsigned char read_00328_delim[] = 
         "\x0a";
      read_00328 = NULL;
      read_00328_len = 0;
      int read_00328_res = cgc_delimited_read(0, &read_00328, &read_00328_len, read_00328_delim, 1);
      if (read_00328_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00328_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00328_ptr += cgc_data_match(read_00328 + read_00328_ptr, read_00328_len - read_00328_ptr, match_00328_00000, 8);
      cgc_free(read_00328);
      if (read_00328_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00225_00000[] = 
         "\x44\x0a";
      static unsigned int write_00225_00000_len = 2;
      unsigned char *write_00225 = NULL;
      unsigned int write_00225_len = 0;
      write_00225 = cgc_append_buf(write_00225, &write_00225_len, write_00225_00000, write_00225_00000_len);
      if (write_00225_len > 0) {
         cgc_transmit_all(1, write_00225, write_00225_len);
      }
      cgc_free(write_00225);
   } while (0);
   do {
      unsigned char *read_00329;
      unsigned int read_00329_len;
      unsigned int read_00329_ptr = 0;
      //**** delimited read
      static unsigned char read_00329_delim[] = 
         "\x0a";
      read_00329 = NULL;
      read_00329_len = 0;
      int read_00329_res = cgc_delimited_read(0, &read_00329, &read_00329_len, read_00329_delim, 1);
      if (read_00329_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00329_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00329_ptr += cgc_data_match(read_00329 + read_00329_ptr, read_00329_len - read_00329_ptr, match_00329_00000, 47);
      cgc_free(read_00329);
      if (read_00329_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00330;
      unsigned int read_00330_len;
      unsigned int read_00330_ptr = 0;
      //**** delimited read
      static unsigned char read_00330_delim[] = 
         "\x0a";
      read_00330 = NULL;
      read_00330_len = 0;
      int read_00330_res = cgc_delimited_read(0, &read_00330, &read_00330_len, read_00330_delim, 1);
      if (read_00330_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00330_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00330_ptr += cgc_data_match(read_00330 + read_00330_ptr, read_00330_len - read_00330_ptr, match_00330_00000, 8);
      cgc_free(read_00330);
      if (read_00330_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00226_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00226_00000_len = 2;
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = cgc_append_buf(write_00226, &write_00226_len, write_00226_00000, write_00226_00000_len);
      if (write_00226_len > 0) {
         cgc_transmit_all(1, write_00226, write_00226_len);
      }
      cgc_free(write_00226);
   } while (0);
   do {
      unsigned char *read_00331;
      unsigned int read_00331_len;
      unsigned int read_00331_ptr = 0;
      //**** delimited read
      static unsigned char read_00331_delim[] = 
         "\x0a";
      read_00331 = NULL;
      read_00331_len = 0;
      int read_00331_res = cgc_delimited_read(0, &read_00331, &read_00331_len, read_00331_delim, 1);
      if (read_00331_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00331_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00331_ptr += cgc_data_match(read_00331 + read_00331_ptr, read_00331_len - read_00331_ptr, match_00331_00000, 6);
      cgc_free(read_00331);
      if (read_00331_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00227_00000[] = 
         "\x33\x33\x0a";
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
      unsigned char *read_00332;
      unsigned int read_00332_len;
      unsigned int read_00332_ptr = 0;
      //**** delimited read
      static unsigned char read_00332_delim[] = 
         "\x0a";
      read_00332 = NULL;
      read_00332_len = 0;
      int read_00332_res = cgc_delimited_read(0, &read_00332, &read_00332_len, read_00332_delim, 1);
      if (read_00332_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00332_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00332_ptr += cgc_data_match(read_00332 + read_00332_ptr, read_00332_len - read_00332_ptr, match_00332_00000, 47);
      cgc_free(read_00332);
      if (read_00332_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00333;
      unsigned int read_00333_len;
      unsigned int read_00333_ptr = 0;
      //**** delimited read
      static unsigned char read_00333_delim[] = 
         "\x0a";
      read_00333 = NULL;
      read_00333_len = 0;
      int read_00333_res = cgc_delimited_read(0, &read_00333, &read_00333_len, read_00333_delim, 1);
      if (read_00333_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00333_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00333_ptr += cgc_data_match(read_00333 + read_00333_ptr, read_00333_len - read_00333_ptr, match_00333_00000, 8);
      cgc_free(read_00333);
      if (read_00333_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00228_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00228_00000_len = 2;
      unsigned char *write_00228 = NULL;
      unsigned int write_00228_len = 0;
      write_00228 = cgc_append_buf(write_00228, &write_00228_len, write_00228_00000, write_00228_00000_len);
      if (write_00228_len > 0) {
         cgc_transmit_all(1, write_00228, write_00228_len);
      }
      cgc_free(write_00228);
   } while (0);
   do {
      unsigned char *read_00334;
      unsigned int read_00334_len;
      unsigned int read_00334_ptr = 0;
      //**** delimited read
      static unsigned char read_00334_delim[] = 
         "\x0a";
      read_00334 = NULL;
      read_00334_len = 0;
      int read_00334_res = cgc_delimited_read(0, &read_00334, &read_00334_len, read_00334_delim, 1);
      if (read_00334_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00334_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00334_ptr += cgc_data_match(read_00334 + read_00334_ptr, read_00334_len - read_00334_ptr, match_00334_00000, 6);
      cgc_free(read_00334);
      if (read_00334_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00229_00000[] = 
         "\x33\x34\x0a";
      static unsigned int write_00229_00000_len = 3;
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = cgc_append_buf(write_00229, &write_00229_len, write_00229_00000, write_00229_00000_len);
      if (write_00229_len > 0) {
         cgc_transmit_all(1, write_00229, write_00229_len);
      }
      cgc_free(write_00229);
   } while (0);
   do {
      unsigned char *read_00335;
      unsigned int read_00335_len;
      unsigned int read_00335_ptr = 0;
      //**** delimited read
      static unsigned char read_00335_delim[] = 
         "\x0a";
      read_00335 = NULL;
      read_00335_len = 0;
      int read_00335_res = cgc_delimited_read(0, &read_00335, &read_00335_len, read_00335_delim, 1);
      if (read_00335_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00335_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00335_ptr += cgc_data_match(read_00335 + read_00335_ptr, read_00335_len - read_00335_ptr, match_00335_00000, 29);
      cgc_free(read_00335);
      if (read_00335_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00336;
      unsigned int read_00336_len;
      unsigned int read_00336_ptr = 0;
      //**** delimited read
      static unsigned char read_00336_delim[] = 
         "\x0a";
      read_00336 = NULL;
      read_00336_len = 0;
      int read_00336_res = cgc_delimited_read(0, &read_00336, &read_00336_len, read_00336_delim, 1);
      if (read_00336_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00336_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00336_ptr += cgc_data_match(read_00336 + read_00336_ptr, read_00336_len - read_00336_ptr, match_00336_00000, 42);
      cgc_free(read_00336);
      if (read_00336_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00337;
      unsigned int read_00337_len;
      unsigned int read_00337_ptr = 0;
      //**** delimited read
      static unsigned char read_00337_delim[] = 
         "\x0a";
      read_00337 = NULL;
      read_00337_len = 0;
      int read_00337_res = cgc_delimited_read(0, &read_00337, &read_00337_len, read_00337_delim, 1);
      if (read_00337_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00337_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00337_ptr += cgc_data_match(read_00337 + read_00337_ptr, read_00337_len - read_00337_ptr, match_00337_00000, 29);
      cgc_free(read_00337);
      if (read_00337_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00338;
      unsigned int read_00338_len;
      unsigned int read_00338_ptr = 0;
      //**** delimited read
      static unsigned char read_00338_delim[] = 
         "\x0a";
      read_00338 = NULL;
      read_00338_len = 0;
      int read_00338_res = cgc_delimited_read(0, &read_00338, &read_00338_len, read_00338_delim, 1);
      if (read_00338_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00338_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00338_ptr += cgc_data_match(read_00338 + read_00338_ptr, read_00338_len - read_00338_ptr, match_00338_00000, 42);
      cgc_free(read_00338);
      if (read_00338_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00339;
      unsigned int read_00339_len;
      unsigned int read_00339_ptr = 0;
      //**** delimited read
      static unsigned char read_00339_delim[] = 
         "\x0a";
      read_00339 = NULL;
      read_00339_len = 0;
      int read_00339_res = cgc_delimited_read(0, &read_00339, &read_00339_len, read_00339_delim, 1);
      if (read_00339_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00339_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00339_ptr += cgc_data_match(read_00339 + read_00339_ptr, read_00339_len - read_00339_ptr, match_00339_00000, 8);
      cgc_free(read_00339);
      if (read_00339_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00230_00000[] = 
         "\x44\x0a";
      static unsigned int write_00230_00000_len = 2;
      unsigned char *write_00230 = NULL;
      unsigned int write_00230_len = 0;
      write_00230 = cgc_append_buf(write_00230, &write_00230_len, write_00230_00000, write_00230_00000_len);
      if (write_00230_len > 0) {
         cgc_transmit_all(1, write_00230, write_00230_len);
      }
      cgc_free(write_00230);
   } while (0);
   do {
      unsigned char *read_00340;
      unsigned int read_00340_len;
      unsigned int read_00340_ptr = 0;
      //**** delimited read
      static unsigned char read_00340_delim[] = 
         "\x0a";
      read_00340 = NULL;
      read_00340_len = 0;
      int read_00340_res = cgc_delimited_read(0, &read_00340, &read_00340_len, read_00340_delim, 1);
      if (read_00340_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00340_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00340_ptr += cgc_data_match(read_00340 + read_00340_ptr, read_00340_len - read_00340_ptr, match_00340_00000, 47);
      cgc_free(read_00340);
      if (read_00340_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00341;
      unsigned int read_00341_len;
      unsigned int read_00341_ptr = 0;
      //**** delimited read
      static unsigned char read_00341_delim[] = 
         "\x0a";
      read_00341 = NULL;
      read_00341_len = 0;
      int read_00341_res = cgc_delimited_read(0, &read_00341, &read_00341_len, read_00341_delim, 1);
      if (read_00341_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00341_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00341_ptr += cgc_data_match(read_00341 + read_00341_ptr, read_00341_len - read_00341_ptr, match_00341_00000, 8);
      cgc_free(read_00341);
      if (read_00341_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00231_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00231_00000_len = 2;
      unsigned char *write_00231 = NULL;
      unsigned int write_00231_len = 0;
      write_00231 = cgc_append_buf(write_00231, &write_00231_len, write_00231_00000, write_00231_00000_len);
      if (write_00231_len > 0) {
         cgc_transmit_all(1, write_00231, write_00231_len);
      }
      cgc_free(write_00231);
   } while (0);
   do {
      unsigned char *read_00342;
      unsigned int read_00342_len;
      unsigned int read_00342_ptr = 0;
      //**** delimited read
      static unsigned char read_00342_delim[] = 
         "\x0a";
      read_00342 = NULL;
      read_00342_len = 0;
      int read_00342_res = cgc_delimited_read(0, &read_00342, &read_00342_len, read_00342_delim, 1);
      if (read_00342_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00342_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00342_ptr += cgc_data_match(read_00342 + read_00342_ptr, read_00342_len - read_00342_ptr, match_00342_00000, 6);
      cgc_free(read_00342);
      if (read_00342_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00232_00000[] = 
         "\x32\x0a";
      static unsigned int write_00232_00000_len = 2;
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = cgc_append_buf(write_00232, &write_00232_len, write_00232_00000, write_00232_00000_len);
      if (write_00232_len > 0) {
         cgc_transmit_all(1, write_00232, write_00232_len);
      }
      cgc_free(write_00232);
   } while (0);
   do {
      unsigned char *read_00343;
      unsigned int read_00343_len;
      unsigned int read_00343_ptr = 0;
      //**** delimited read
      static unsigned char read_00343_delim[] = 
         "\x0a";
      read_00343 = NULL;
      read_00343_len = 0;
      int read_00343_res = cgc_delimited_read(0, &read_00343, &read_00343_len, read_00343_delim, 1);
      if (read_00343_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00343_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00343_ptr += cgc_data_match(read_00343 + read_00343_ptr, read_00343_len - read_00343_ptr, match_00343_00000, 47);
      cgc_free(read_00343);
      if (read_00343_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00344;
      unsigned int read_00344_len;
      unsigned int read_00344_ptr = 0;
      //**** delimited read
      static unsigned char read_00344_delim[] = 
         "\x0a";
      read_00344 = NULL;
      read_00344_len = 0;
      int read_00344_res = cgc_delimited_read(0, &read_00344, &read_00344_len, read_00344_delim, 1);
      if (read_00344_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00344_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00344_ptr += cgc_data_match(read_00344 + read_00344_ptr, read_00344_len - read_00344_ptr, match_00344_00000, 8);
      cgc_free(read_00344);
      if (read_00344_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00233_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00233_00000_len = 2;
      unsigned char *write_00233 = NULL;
      unsigned int write_00233_len = 0;
      write_00233 = cgc_append_buf(write_00233, &write_00233_len, write_00233_00000, write_00233_00000_len);
      if (write_00233_len > 0) {
         cgc_transmit_all(1, write_00233, write_00233_len);
      }
      cgc_free(write_00233);
   } while (0);
   do {
      unsigned char *read_00345;
      unsigned int read_00345_len;
      unsigned int read_00345_ptr = 0;
      //**** delimited read
      static unsigned char read_00345_delim[] = 
         "\x0a";
      read_00345 = NULL;
      read_00345_len = 0;
      int read_00345_res = cgc_delimited_read(0, &read_00345, &read_00345_len, read_00345_delim, 1);
      if (read_00345_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00345_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00345_ptr += cgc_data_match(read_00345 + read_00345_ptr, read_00345_len - read_00345_ptr, match_00345_00000, 6);
      cgc_free(read_00345);
      if (read_00345_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00234_00000[] = 
         "\x33\x0a";
      static unsigned int write_00234_00000_len = 2;
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = cgc_append_buf(write_00234, &write_00234_len, write_00234_00000, write_00234_00000_len);
      if (write_00234_len > 0) {
         cgc_transmit_all(1, write_00234, write_00234_len);
      }
      cgc_free(write_00234);
   } while (0);
   do {
      unsigned char *read_00346;
      unsigned int read_00346_len;
      unsigned int read_00346_ptr = 0;
      //**** delimited read
      static unsigned char read_00346_delim[] = 
         "\x0a";
      read_00346 = NULL;
      read_00346_len = 0;
      int read_00346_res = cgc_delimited_read(0, &read_00346, &read_00346_len, read_00346_delim, 1);
      if (read_00346_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00346_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00346_ptr += cgc_data_match(read_00346 + read_00346_ptr, read_00346_len - read_00346_ptr, match_00346_00000, 29);
      cgc_free(read_00346);
      if (read_00346_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00347;
      unsigned int read_00347_len;
      unsigned int read_00347_ptr = 0;
      //**** delimited read
      static unsigned char read_00347_delim[] = 
         "\x0a";
      read_00347 = NULL;
      read_00347_len = 0;
      int read_00347_res = cgc_delimited_read(0, &read_00347, &read_00347_len, read_00347_delim, 1);
      if (read_00347_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00347_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00347_ptr += cgc_data_match(read_00347 + read_00347_ptr, read_00347_len - read_00347_ptr, match_00347_00000, 65);
      cgc_free(read_00347);
      if (read_00347_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00348;
      unsigned int read_00348_len;
      unsigned int read_00348_ptr = 0;
      //**** delimited read
      static unsigned char read_00348_delim[] = 
         "\x0a";
      read_00348 = NULL;
      read_00348_len = 0;
      int read_00348_res = cgc_delimited_read(0, &read_00348, &read_00348_len, read_00348_delim, 1);
      if (read_00348_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00348_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00348_ptr += cgc_data_match(read_00348 + read_00348_ptr, read_00348_len - read_00348_ptr, match_00348_00000, 7);
      cgc_free(read_00348);
      if (read_00348_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00235_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00235_00000_len = 2;
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = cgc_append_buf(write_00235, &write_00235_len, write_00235_00000, write_00235_00000_len);
      if (write_00235_len > 0) {
         cgc_transmit_all(1, write_00235, write_00235_len);
      }
      cgc_free(write_00235);
   } while (0);
   do {
      unsigned char *read_00349;
      unsigned int read_00349_len;
      unsigned int read_00349_ptr = 0;
      //**** delimited read
      static unsigned char read_00349_delim[] = 
         "\x0a";
      read_00349 = NULL;
      read_00349_len = 0;
      int read_00349_res = cgc_delimited_read(0, &read_00349, &read_00349_len, read_00349_delim, 1);
      if (read_00349_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00349_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00349_ptr += cgc_data_match(read_00349 + read_00349_ptr, read_00349_len - read_00349_ptr, match_00349_00000, 17);
      cgc_free(read_00349);
      if (read_00349_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00236_00000[] = 
         "\x31\x0a";
      static unsigned int write_00236_00000_len = 2;
      unsigned char *write_00236 = NULL;
      unsigned int write_00236_len = 0;
      write_00236 = cgc_append_buf(write_00236, &write_00236_len, write_00236_00000, write_00236_00000_len);
      if (write_00236_len > 0) {
         cgc_transmit_all(1, write_00236, write_00236_len);
      }
      cgc_free(write_00236);
   } while (0);
   do {
      unsigned char *read_00350;
      unsigned int read_00350_len;
      unsigned int read_00350_ptr = 0;
      //**** delimited read
      static unsigned char read_00350_delim[] = 
         "\x0a";
      read_00350 = NULL;
      read_00350_len = 0;
      int read_00350_res = cgc_delimited_read(0, &read_00350, &read_00350_len, read_00350_delim, 1);
      if (read_00350_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00350_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00350_ptr += cgc_data_match(read_00350 + read_00350_ptr, read_00350_len - read_00350_ptr, match_00350_00000, 29);
      cgc_free(read_00350);
      if (read_00350_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00351;
      unsigned int read_00351_len;
      unsigned int read_00351_ptr = 0;
      //**** delimited read
      static unsigned char read_00351_delim[] = 
         "\x0a";
      read_00351 = NULL;
      read_00351_len = 0;
      int read_00351_res = cgc_delimited_read(0, &read_00351, &read_00351_len, read_00351_delim, 1);
      if (read_00351_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00351_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00351_ptr += cgc_data_match(read_00351 + read_00351_ptr, read_00351_len - read_00351_ptr, match_00351_00000, 65);
      cgc_free(read_00351);
      if (read_00351_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00352;
      unsigned int read_00352_len;
      unsigned int read_00352_ptr = 0;
      //**** delimited read
      static unsigned char read_00352_delim[] = 
         "\x0a";
      read_00352 = NULL;
      read_00352_len = 0;
      int read_00352_res = cgc_delimited_read(0, &read_00352, &read_00352_len, read_00352_delim, 1);
      if (read_00352_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00352_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00352_ptr += cgc_data_match(read_00352 + read_00352_ptr, read_00352_len - read_00352_ptr, match_00352_00000, 7);
      cgc_free(read_00352);
      if (read_00352_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00237_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00237_00000_len = 2;
      unsigned char *write_00237 = NULL;
      unsigned int write_00237_len = 0;
      write_00237 = cgc_append_buf(write_00237, &write_00237_len, write_00237_00000, write_00237_00000_len);
      if (write_00237_len > 0) {
         cgc_transmit_all(1, write_00237, write_00237_len);
      }
      cgc_free(write_00237);
   } while (0);
   do {
      unsigned char *read_00353;
      unsigned int read_00353_len;
      unsigned int read_00353_ptr = 0;
      //**** delimited read
      static unsigned char read_00353_delim[] = 
         "\x0a";
      read_00353 = NULL;
      read_00353_len = 0;
      int read_00353_res = cgc_delimited_read(0, &read_00353, &read_00353_len, read_00353_delim, 1);
      if (read_00353_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00353_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00353_ptr += cgc_data_match(read_00353 + read_00353_ptr, read_00353_len - read_00353_ptr, match_00353_00000, 17);
      cgc_free(read_00353);
      if (read_00353_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00238_00000[] = 
         "\x31\x0a";
      static unsigned int write_00238_00000_len = 2;
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = cgc_append_buf(write_00238, &write_00238_len, write_00238_00000, write_00238_00000_len);
      if (write_00238_len > 0) {
         cgc_transmit_all(1, write_00238, write_00238_len);
      }
      cgc_free(write_00238);
   } while (0);
   do {
      unsigned char *read_00354;
      unsigned int read_00354_len;
      unsigned int read_00354_ptr = 0;
      //**** delimited read
      static unsigned char read_00354_delim[] = 
         "\x0a";
      read_00354 = NULL;
      read_00354_len = 0;
      int read_00354_res = cgc_delimited_read(0, &read_00354, &read_00354_len, read_00354_delim, 1);
      if (read_00354_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00354_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00354_ptr += cgc_data_match(read_00354 + read_00354_ptr, read_00354_len - read_00354_ptr, match_00354_00000, 8);
      cgc_free(read_00354);
      if (read_00354_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00239_00000[] = 
         "\x44\x0a";
      static unsigned int write_00239_00000_len = 2;
      unsigned char *write_00239 = NULL;
      unsigned int write_00239_len = 0;
      write_00239 = cgc_append_buf(write_00239, &write_00239_len, write_00239_00000, write_00239_00000_len);
      if (write_00239_len > 0) {
         cgc_transmit_all(1, write_00239, write_00239_len);
      }
      cgc_free(write_00239);
   } while (0);
   do {
      unsigned char *read_00355;
      unsigned int read_00355_len;
      unsigned int read_00355_ptr = 0;
      //**** delimited read
      static unsigned char read_00355_delim[] = 
         "\x0a";
      read_00355 = NULL;
      read_00355_len = 0;
      int read_00355_res = cgc_delimited_read(0, &read_00355, &read_00355_len, read_00355_delim, 1);
      if (read_00355_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00355_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00355_ptr += cgc_data_match(read_00355 + read_00355_ptr, read_00355_len - read_00355_ptr, match_00355_00000, 47);
      cgc_free(read_00355);
      if (read_00355_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00356;
      unsigned int read_00356_len;
      unsigned int read_00356_ptr = 0;
      //**** delimited read
      static unsigned char read_00356_delim[] = 
         "\x0a";
      read_00356 = NULL;
      read_00356_len = 0;
      int read_00356_res = cgc_delimited_read(0, &read_00356, &read_00356_len, read_00356_delim, 1);
      if (read_00356_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00356_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00356_ptr += cgc_data_match(read_00356 + read_00356_ptr, read_00356_len - read_00356_ptr, match_00356_00000, 8);
      cgc_free(read_00356);
      if (read_00356_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00240_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00240_00000_len = 2;
      unsigned char *write_00240 = NULL;
      unsigned int write_00240_len = 0;
      write_00240 = cgc_append_buf(write_00240, &write_00240_len, write_00240_00000, write_00240_00000_len);
      if (write_00240_len > 0) {
         cgc_transmit_all(1, write_00240, write_00240_len);
      }
      cgc_free(write_00240);
   } while (0);
   do {
      unsigned char *read_00357;
      unsigned int read_00357_len;
      unsigned int read_00357_ptr = 0;
      //**** delimited read
      static unsigned char read_00357_delim[] = 
         "\x0a";
      read_00357 = NULL;
      read_00357_len = 0;
      int read_00357_res = cgc_delimited_read(0, &read_00357, &read_00357_len, read_00357_delim, 1);
      if (read_00357_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00357_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00357_ptr += cgc_data_match(read_00357 + read_00357_ptr, read_00357_len - read_00357_ptr, match_00357_00000, 6);
      cgc_free(read_00357);
      if (read_00357_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00241_00000[] = 
         "\x34\x0a";
      static unsigned int write_00241_00000_len = 2;
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = cgc_append_buf(write_00241, &write_00241_len, write_00241_00000, write_00241_00000_len);
      if (write_00241_len > 0) {
         cgc_transmit_all(1, write_00241, write_00241_len);
      }
      cgc_free(write_00241);
   } while (0);
   do {
      unsigned char *read_00358;
      unsigned int read_00358_len;
      unsigned int read_00358_ptr = 0;
      //**** delimited read
      static unsigned char read_00358_delim[] = 
         "\x0a";
      read_00358 = NULL;
      read_00358_len = 0;
      int read_00358_res = cgc_delimited_read(0, &read_00358, &read_00358_len, read_00358_delim, 1);
      if (read_00358_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00358_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00358_ptr += cgc_data_match(read_00358 + read_00358_ptr, read_00358_len - read_00358_ptr, match_00358_00000, 47);
      cgc_free(read_00358);
      if (read_00358_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00359;
      unsigned int read_00359_len;
      unsigned int read_00359_ptr = 0;
      //**** delimited read
      static unsigned char read_00359_delim[] = 
         "\x0a";
      read_00359 = NULL;
      read_00359_len = 0;
      int read_00359_res = cgc_delimited_read(0, &read_00359, &read_00359_len, read_00359_delim, 1);
      if (read_00359_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00359_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00359_ptr += cgc_data_match(read_00359 + read_00359_ptr, read_00359_len - read_00359_ptr, match_00359_00000, 8);
      cgc_free(read_00359);
      if (read_00359_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00242_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00242_00000_len = 2;
      unsigned char *write_00242 = NULL;
      unsigned int write_00242_len = 0;
      write_00242 = cgc_append_buf(write_00242, &write_00242_len, write_00242_00000, write_00242_00000_len);
      if (write_00242_len > 0) {
         cgc_transmit_all(1, write_00242, write_00242_len);
      }
      cgc_free(write_00242);
   } while (0);
   do {
      unsigned char *read_00360;
      unsigned int read_00360_len;
      unsigned int read_00360_ptr = 0;
      //**** delimited read
      static unsigned char read_00360_delim[] = 
         "\x0a";
      read_00360 = NULL;
      read_00360_len = 0;
      int read_00360_res = cgc_delimited_read(0, &read_00360, &read_00360_len, read_00360_delim, 1);
      if (read_00360_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00360_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00360_ptr += cgc_data_match(read_00360 + read_00360_ptr, read_00360_len - read_00360_ptr, match_00360_00000, 6);
      cgc_free(read_00360);
      if (read_00360_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00243_00000[] = 
         "\x35\x0a";
      static unsigned int write_00243_00000_len = 2;
      unsigned char *write_00243 = NULL;
      unsigned int write_00243_len = 0;
      write_00243 = cgc_append_buf(write_00243, &write_00243_len, write_00243_00000, write_00243_00000_len);
      if (write_00243_len > 0) {
         cgc_transmit_all(1, write_00243, write_00243_len);
      }
      cgc_free(write_00243);
   } while (0);
   do {
      unsigned char *read_00361;
      unsigned int read_00361_len;
      unsigned int read_00361_ptr = 0;
      //**** delimited read
      static unsigned char read_00361_delim[] = 
         "\x0a";
      read_00361 = NULL;
      read_00361_len = 0;
      int read_00361_res = cgc_delimited_read(0, &read_00361, &read_00361_len, read_00361_delim, 1);
      if (read_00361_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00361_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00361_ptr += cgc_data_match(read_00361 + read_00361_ptr, read_00361_len - read_00361_ptr, match_00361_00000, 29);
      cgc_free(read_00361);
      if (read_00361_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00362;
      unsigned int read_00362_len;
      unsigned int read_00362_ptr = 0;
      //**** delimited read
      static unsigned char read_00362_delim[] = 
         "\x0a";
      read_00362 = NULL;
      read_00362_len = 0;
      int read_00362_res = cgc_delimited_read(0, &read_00362, &read_00362_len, read_00362_delim, 1);
      if (read_00362_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00362_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00362_ptr += cgc_data_match(read_00362 + read_00362_ptr, read_00362_len - read_00362_ptr, match_00362_00000, 65);
      cgc_free(read_00362);
      if (read_00362_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00363;
      unsigned int read_00363_len;
      unsigned int read_00363_ptr = 0;
      //**** delimited read
      static unsigned char read_00363_delim[] = 
         "\x0a";
      read_00363 = NULL;
      read_00363_len = 0;
      int read_00363_res = cgc_delimited_read(0, &read_00363, &read_00363_len, read_00363_delim, 1);
      if (read_00363_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00363_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00363_ptr += cgc_data_match(read_00363 + read_00363_ptr, read_00363_len - read_00363_ptr, match_00363_00000, 7);
      cgc_free(read_00363);
      if (read_00363_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00244_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00244_00000_len = 2;
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = cgc_append_buf(write_00244, &write_00244_len, write_00244_00000, write_00244_00000_len);
      if (write_00244_len > 0) {
         cgc_transmit_all(1, write_00244, write_00244_len);
      }
      cgc_free(write_00244);
   } while (0);
   do {
      unsigned char *read_00364;
      unsigned int read_00364_len;
      unsigned int read_00364_ptr = 0;
      //**** delimited read
      static unsigned char read_00364_delim[] = 
         "\x0a";
      read_00364 = NULL;
      read_00364_len = 0;
      int read_00364_res = cgc_delimited_read(0, &read_00364, &read_00364_len, read_00364_delim, 1);
      if (read_00364_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00364_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00364_ptr += cgc_data_match(read_00364 + read_00364_ptr, read_00364_len - read_00364_ptr, match_00364_00000, 17);
      cgc_free(read_00364);
      if (read_00364_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00245_00000[] = 
         "\x31\x0a";
      static unsigned int write_00245_00000_len = 2;
      unsigned char *write_00245 = NULL;
      unsigned int write_00245_len = 0;
      write_00245 = cgc_append_buf(write_00245, &write_00245_len, write_00245_00000, write_00245_00000_len);
      if (write_00245_len > 0) {
         cgc_transmit_all(1, write_00245, write_00245_len);
      }
      cgc_free(write_00245);
   } while (0);
   do {
      unsigned char *read_00365;
      unsigned int read_00365_len;
      unsigned int read_00365_ptr = 0;
      //**** delimited read
      static unsigned char read_00365_delim[] = 
         "\x0a";
      read_00365 = NULL;
      read_00365_len = 0;
      int read_00365_res = cgc_delimited_read(0, &read_00365, &read_00365_len, read_00365_delim, 1);
      if (read_00365_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00365_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00365_ptr += cgc_data_match(read_00365 + read_00365_ptr, read_00365_len - read_00365_ptr, match_00365_00000, 29);
      cgc_free(read_00365);
      if (read_00365_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00366;
      unsigned int read_00366_len;
      unsigned int read_00366_ptr = 0;
      //**** delimited read
      static unsigned char read_00366_delim[] = 
         "\x0a";
      read_00366 = NULL;
      read_00366_len = 0;
      int read_00366_res = cgc_delimited_read(0, &read_00366, &read_00366_len, read_00366_delim, 1);
      if (read_00366_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00366_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00366_ptr += cgc_data_match(read_00366 + read_00366_ptr, read_00366_len - read_00366_ptr, match_00366_00000, 65);
      cgc_free(read_00366);
      if (read_00366_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00367;
      unsigned int read_00367_len;
      unsigned int read_00367_ptr = 0;
      //**** delimited read
      static unsigned char read_00367_delim[] = 
         "\x0a";
      read_00367 = NULL;
      read_00367_len = 0;
      int read_00367_res = cgc_delimited_read(0, &read_00367, &read_00367_len, read_00367_delim, 1);
      if (read_00367_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00367_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00367_ptr += cgc_data_match(read_00367 + read_00367_ptr, read_00367_len - read_00367_ptr, match_00367_00000, 7);
      cgc_free(read_00367);
      if (read_00367_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00246_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00246_00000_len = 2;
      unsigned char *write_00246 = NULL;
      unsigned int write_00246_len = 0;
      write_00246 = cgc_append_buf(write_00246, &write_00246_len, write_00246_00000, write_00246_00000_len);
      if (write_00246_len > 0) {
         cgc_transmit_all(1, write_00246, write_00246_len);
      }
      cgc_free(write_00246);
   } while (0);
   do {
      unsigned char *read_00368;
      unsigned int read_00368_len;
      unsigned int read_00368_ptr = 0;
      //**** delimited read
      static unsigned char read_00368_delim[] = 
         "\x0a";
      read_00368 = NULL;
      read_00368_len = 0;
      int read_00368_res = cgc_delimited_read(0, &read_00368, &read_00368_len, read_00368_delim, 1);
      if (read_00368_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00368_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00368_ptr += cgc_data_match(read_00368 + read_00368_ptr, read_00368_len - read_00368_ptr, match_00368_00000, 17);
      cgc_free(read_00368);
      if (read_00368_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00247_00000[] = 
         "\x31\x0a";
      static unsigned int write_00247_00000_len = 2;
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = cgc_append_buf(write_00247, &write_00247_len, write_00247_00000, write_00247_00000_len);
      if (write_00247_len > 0) {
         cgc_transmit_all(1, write_00247, write_00247_len);
      }
      cgc_free(write_00247);
   } while (0);
   do {
      unsigned char *read_00369;
      unsigned int read_00369_len;
      unsigned int read_00369_ptr = 0;
      //**** delimited read
      static unsigned char read_00369_delim[] = 
         "\x0a";
      read_00369 = NULL;
      read_00369_len = 0;
      int read_00369_res = cgc_delimited_read(0, &read_00369, &read_00369_len, read_00369_delim, 1);
      if (read_00369_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00369_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00369_ptr += cgc_data_match(read_00369 + read_00369_ptr, read_00369_len - read_00369_ptr, match_00369_00000, 8);
      cgc_free(read_00369);
      if (read_00369_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00248_00000[] = 
         "\x44\x0a";
      static unsigned int write_00248_00000_len = 2;
      unsigned char *write_00248 = NULL;
      unsigned int write_00248_len = 0;
      write_00248 = cgc_append_buf(write_00248, &write_00248_len, write_00248_00000, write_00248_00000_len);
      if (write_00248_len > 0) {
         cgc_transmit_all(1, write_00248, write_00248_len);
      }
      cgc_free(write_00248);
   } while (0);
   do {
      unsigned char *read_00370;
      unsigned int read_00370_len;
      unsigned int read_00370_ptr = 0;
      //**** delimited read
      static unsigned char read_00370_delim[] = 
         "\x0a";
      read_00370 = NULL;
      read_00370_len = 0;
      int read_00370_res = cgc_delimited_read(0, &read_00370, &read_00370_len, read_00370_delim, 1);
      if (read_00370_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00370_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00370_ptr += cgc_data_match(read_00370 + read_00370_ptr, read_00370_len - read_00370_ptr, match_00370_00000, 47);
      cgc_free(read_00370);
      if (read_00370_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00371;
      unsigned int read_00371_len;
      unsigned int read_00371_ptr = 0;
      //**** delimited read
      static unsigned char read_00371_delim[] = 
         "\x0a";
      read_00371 = NULL;
      read_00371_len = 0;
      int read_00371_res = cgc_delimited_read(0, &read_00371, &read_00371_len, read_00371_delim, 1);
      if (read_00371_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00371_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00371_ptr += cgc_data_match(read_00371 + read_00371_ptr, read_00371_len - read_00371_ptr, match_00371_00000, 8);
      cgc_free(read_00371);
      if (read_00371_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00249_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00249_00000_len = 2;
      unsigned char *write_00249 = NULL;
      unsigned int write_00249_len = 0;
      write_00249 = cgc_append_buf(write_00249, &write_00249_len, write_00249_00000, write_00249_00000_len);
      if (write_00249_len > 0) {
         cgc_transmit_all(1, write_00249, write_00249_len);
      }
      cgc_free(write_00249);
   } while (0);
   do {
      unsigned char *read_00372;
      unsigned int read_00372_len;
      unsigned int read_00372_ptr = 0;
      //**** delimited read
      static unsigned char read_00372_delim[] = 
         "\x0a";
      read_00372 = NULL;
      read_00372_len = 0;
      int read_00372_res = cgc_delimited_read(0, &read_00372, &read_00372_len, read_00372_delim, 1);
      if (read_00372_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00372_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00372_ptr += cgc_data_match(read_00372 + read_00372_ptr, read_00372_len - read_00372_ptr, match_00372_00000, 6);
      cgc_free(read_00372);
      if (read_00372_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00250_00000[] = 
         "\x36\x0a";
      static unsigned int write_00250_00000_len = 2;
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = cgc_append_buf(write_00250, &write_00250_len, write_00250_00000, write_00250_00000_len);
      if (write_00250_len > 0) {
         cgc_transmit_all(1, write_00250, write_00250_len);
      }
      cgc_free(write_00250);
   } while (0);
   do {
      unsigned char *read_00373;
      unsigned int read_00373_len;
      unsigned int read_00373_ptr = 0;
      //**** delimited read
      static unsigned char read_00373_delim[] = 
         "\x0a";
      read_00373 = NULL;
      read_00373_len = 0;
      int read_00373_res = cgc_delimited_read(0, &read_00373, &read_00373_len, read_00373_delim, 1);
      if (read_00373_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00373_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00373_ptr += cgc_data_match(read_00373 + read_00373_ptr, read_00373_len - read_00373_ptr, match_00373_00000, 47);
      cgc_free(read_00373);
      if (read_00373_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00374;
      unsigned int read_00374_len;
      unsigned int read_00374_ptr = 0;
      //**** delimited read
      static unsigned char read_00374_delim[] = 
         "\x0a";
      read_00374 = NULL;
      read_00374_len = 0;
      int read_00374_res = cgc_delimited_read(0, &read_00374, &read_00374_len, read_00374_delim, 1);
      if (read_00374_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00374_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00374_ptr += cgc_data_match(read_00374 + read_00374_ptr, read_00374_len - read_00374_ptr, match_00374_00000, 8);
      cgc_free(read_00374);
      if (read_00374_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00251_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00251_00000_len = 2;
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = cgc_append_buf(write_00251, &write_00251_len, write_00251_00000, write_00251_00000_len);
      if (write_00251_len > 0) {
         cgc_transmit_all(1, write_00251, write_00251_len);
      }
      cgc_free(write_00251);
   } while (0);
   do {
      unsigned char *read_00375;
      unsigned int read_00375_len;
      unsigned int read_00375_ptr = 0;
      //**** delimited read
      static unsigned char read_00375_delim[] = 
         "\x0a";
      read_00375 = NULL;
      read_00375_len = 0;
      int read_00375_res = cgc_delimited_read(0, &read_00375, &read_00375_len, read_00375_delim, 1);
      if (read_00375_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00375_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00375_ptr += cgc_data_match(read_00375 + read_00375_ptr, read_00375_len - read_00375_ptr, match_00375_00000, 6);
      cgc_free(read_00375);
      if (read_00375_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00252_00000[] = 
         "\x37\x0a";
      static unsigned int write_00252_00000_len = 2;
      unsigned char *write_00252 = NULL;
      unsigned int write_00252_len = 0;
      write_00252 = cgc_append_buf(write_00252, &write_00252_len, write_00252_00000, write_00252_00000_len);
      if (write_00252_len > 0) {
         cgc_transmit_all(1, write_00252, write_00252_len);
      }
      cgc_free(write_00252);
   } while (0);
   do {
      unsigned char *read_00376;
      unsigned int read_00376_len;
      unsigned int read_00376_ptr = 0;
      //**** delimited read
      static unsigned char read_00376_delim[] = 
         "\x0a";
      read_00376 = NULL;
      read_00376_len = 0;
      int read_00376_res = cgc_delimited_read(0, &read_00376, &read_00376_len, read_00376_delim, 1);
      if (read_00376_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00376_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00376_ptr += cgc_data_match(read_00376 + read_00376_ptr, read_00376_len - read_00376_ptr, match_00376_00000, 29);
      cgc_free(read_00376);
      if (read_00376_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00377;
      unsigned int read_00377_len;
      unsigned int read_00377_ptr = 0;
      //**** delimited read
      static unsigned char read_00377_delim[] = 
         "\x0a";
      read_00377 = NULL;
      read_00377_len = 0;
      int read_00377_res = cgc_delimited_read(0, &read_00377, &read_00377_len, read_00377_delim, 1);
      if (read_00377_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00377_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00377_ptr += cgc_data_match(read_00377 + read_00377_ptr, read_00377_len - read_00377_ptr, match_00377_00000, 65);
      cgc_free(read_00377);
      if (read_00377_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00378;
      unsigned int read_00378_len;
      unsigned int read_00378_ptr = 0;
      //**** delimited read
      static unsigned char read_00378_delim[] = 
         "\x0a";
      read_00378 = NULL;
      read_00378_len = 0;
      int read_00378_res = cgc_delimited_read(0, &read_00378, &read_00378_len, read_00378_delim, 1);
      if (read_00378_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00378_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00378_ptr += cgc_data_match(read_00378 + read_00378_ptr, read_00378_len - read_00378_ptr, match_00378_00000, 7);
      cgc_free(read_00378);
      if (read_00378_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00253_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00253_00000_len = 2;
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = cgc_append_buf(write_00253, &write_00253_len, write_00253_00000, write_00253_00000_len);
      if (write_00253_len > 0) {
         cgc_transmit_all(1, write_00253, write_00253_len);
      }
      cgc_free(write_00253);
   } while (0);
   do {
      unsigned char *read_00379;
      unsigned int read_00379_len;
      unsigned int read_00379_ptr = 0;
      //**** delimited read
      static unsigned char read_00379_delim[] = 
         "\x0a";
      read_00379 = NULL;
      read_00379_len = 0;
      int read_00379_res = cgc_delimited_read(0, &read_00379, &read_00379_len, read_00379_delim, 1);
      if (read_00379_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00379_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00379_ptr += cgc_data_match(read_00379 + read_00379_ptr, read_00379_len - read_00379_ptr, match_00379_00000, 17);
      cgc_free(read_00379);
      if (read_00379_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00254_00000[] = 
         "\x31\x0a";
      static unsigned int write_00254_00000_len = 2;
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = cgc_append_buf(write_00254, &write_00254_len, write_00254_00000, write_00254_00000_len);
      if (write_00254_len > 0) {
         cgc_transmit_all(1, write_00254, write_00254_len);
      }
      cgc_free(write_00254);
   } while (0);
   do {
      unsigned char *read_00380;
      unsigned int read_00380_len;
      unsigned int read_00380_ptr = 0;
      //**** delimited read
      static unsigned char read_00380_delim[] = 
         "\x0a";
      read_00380 = NULL;
      read_00380_len = 0;
      int read_00380_res = cgc_delimited_read(0, &read_00380, &read_00380_len, read_00380_delim, 1);
      if (read_00380_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00380_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00380_ptr += cgc_data_match(read_00380 + read_00380_ptr, read_00380_len - read_00380_ptr, match_00380_00000, 29);
      cgc_free(read_00380);
      if (read_00380_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00381;
      unsigned int read_00381_len;
      unsigned int read_00381_ptr = 0;
      //**** delimited read
      static unsigned char read_00381_delim[] = 
         "\x0a";
      read_00381 = NULL;
      read_00381_len = 0;
      int read_00381_res = cgc_delimited_read(0, &read_00381, &read_00381_len, read_00381_delim, 1);
      if (read_00381_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00381_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00381_ptr += cgc_data_match(read_00381 + read_00381_ptr, read_00381_len - read_00381_ptr, match_00381_00000, 65);
      cgc_free(read_00381);
      if (read_00381_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00382;
      unsigned int read_00382_len;
      unsigned int read_00382_ptr = 0;
      //**** delimited read
      static unsigned char read_00382_delim[] = 
         "\x0a";
      read_00382 = NULL;
      read_00382_len = 0;
      int read_00382_res = cgc_delimited_read(0, &read_00382, &read_00382_len, read_00382_delim, 1);
      if (read_00382_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00382_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00382_ptr += cgc_data_match(read_00382 + read_00382_ptr, read_00382_len - read_00382_ptr, match_00382_00000, 7);
      cgc_free(read_00382);
      if (read_00382_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00255_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00255_00000_len = 2;
      unsigned char *write_00255 = NULL;
      unsigned int write_00255_len = 0;
      write_00255 = cgc_append_buf(write_00255, &write_00255_len, write_00255_00000, write_00255_00000_len);
      if (write_00255_len > 0) {
         cgc_transmit_all(1, write_00255, write_00255_len);
      }
      cgc_free(write_00255);
   } while (0);
   do {
      unsigned char *read_00383;
      unsigned int read_00383_len;
      unsigned int read_00383_ptr = 0;
      //**** delimited read
      static unsigned char read_00383_delim[] = 
         "\x0a";
      read_00383 = NULL;
      read_00383_len = 0;
      int read_00383_res = cgc_delimited_read(0, &read_00383, &read_00383_len, read_00383_delim, 1);
      if (read_00383_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00383_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00383_ptr += cgc_data_match(read_00383 + read_00383_ptr, read_00383_len - read_00383_ptr, match_00383_00000, 17);
      cgc_free(read_00383);
      if (read_00383_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00256_00000[] = 
         "\x31\x0a";
      static unsigned int write_00256_00000_len = 2;
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = cgc_append_buf(write_00256, &write_00256_len, write_00256_00000, write_00256_00000_len);
      if (write_00256_len > 0) {
         cgc_transmit_all(1, write_00256, write_00256_len);
      }
      cgc_free(write_00256);
   } while (0);
   do {
      unsigned char *read_00384;
      unsigned int read_00384_len;
      unsigned int read_00384_ptr = 0;
      //**** delimited read
      static unsigned char read_00384_delim[] = 
         "\x0a";
      read_00384 = NULL;
      read_00384_len = 0;
      int read_00384_res = cgc_delimited_read(0, &read_00384, &read_00384_len, read_00384_delim, 1);
      if (read_00384_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00384_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00384_ptr += cgc_data_match(read_00384 + read_00384_ptr, read_00384_len - read_00384_ptr, match_00384_00000, 8);
      cgc_free(read_00384);
      if (read_00384_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00257_00000[] = 
         "\x44\x0a";
      static unsigned int write_00257_00000_len = 2;
      unsigned char *write_00257 = NULL;
      unsigned int write_00257_len = 0;
      write_00257 = cgc_append_buf(write_00257, &write_00257_len, write_00257_00000, write_00257_00000_len);
      if (write_00257_len > 0) {
         cgc_transmit_all(1, write_00257, write_00257_len);
      }
      cgc_free(write_00257);
   } while (0);
   do {
      unsigned char *read_00385;
      unsigned int read_00385_len;
      unsigned int read_00385_ptr = 0;
      //**** delimited read
      static unsigned char read_00385_delim[] = 
         "\x0a";
      read_00385 = NULL;
      read_00385_len = 0;
      int read_00385_res = cgc_delimited_read(0, &read_00385, &read_00385_len, read_00385_delim, 1);
      if (read_00385_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00385_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00385_ptr += cgc_data_match(read_00385 + read_00385_ptr, read_00385_len - read_00385_ptr, match_00385_00000, 47);
      cgc_free(read_00385);
      if (read_00385_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00386;
      unsigned int read_00386_len;
      unsigned int read_00386_ptr = 0;
      //**** delimited read
      static unsigned char read_00386_delim[] = 
         "\x0a";
      read_00386 = NULL;
      read_00386_len = 0;
      int read_00386_res = cgc_delimited_read(0, &read_00386, &read_00386_len, read_00386_delim, 1);
      if (read_00386_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00386_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00386_ptr += cgc_data_match(read_00386 + read_00386_ptr, read_00386_len - read_00386_ptr, match_00386_00000, 8);
      cgc_free(read_00386);
      if (read_00386_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00258_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00258_00000_len = 2;
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = cgc_append_buf(write_00258, &write_00258_len, write_00258_00000, write_00258_00000_len);
      if (write_00258_len > 0) {
         cgc_transmit_all(1, write_00258, write_00258_len);
      }
      cgc_free(write_00258);
   } while (0);
   do {
      unsigned char *read_00387;
      unsigned int read_00387_len;
      unsigned int read_00387_ptr = 0;
      //**** delimited read
      static unsigned char read_00387_delim[] = 
         "\x0a";
      read_00387 = NULL;
      read_00387_len = 0;
      int read_00387_res = cgc_delimited_read(0, &read_00387, &read_00387_len, read_00387_delim, 1);
      if (read_00387_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00387_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00387_ptr += cgc_data_match(read_00387 + read_00387_ptr, read_00387_len - read_00387_ptr, match_00387_00000, 6);
      cgc_free(read_00387);
      if (read_00387_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00259_00000[] = 
         "\x38\x0a";
      static unsigned int write_00259_00000_len = 2;
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = cgc_append_buf(write_00259, &write_00259_len, write_00259_00000, write_00259_00000_len);
      if (write_00259_len > 0) {
         cgc_transmit_all(1, write_00259, write_00259_len);
      }
      cgc_free(write_00259);
   } while (0);
   do {
      unsigned char *read_00388;
      unsigned int read_00388_len;
      unsigned int read_00388_ptr = 0;
      //**** delimited read
      static unsigned char read_00388_delim[] = 
         "\x0a";
      read_00388 = NULL;
      read_00388_len = 0;
      int read_00388_res = cgc_delimited_read(0, &read_00388, &read_00388_len, read_00388_delim, 1);
      if (read_00388_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00388_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00388_ptr += cgc_data_match(read_00388 + read_00388_ptr, read_00388_len - read_00388_ptr, match_00388_00000, 47);
      cgc_free(read_00388);
      if (read_00388_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00389;
      unsigned int read_00389_len;
      unsigned int read_00389_ptr = 0;
      //**** delimited read
      static unsigned char read_00389_delim[] = 
         "\x0a";
      read_00389 = NULL;
      read_00389_len = 0;
      int read_00389_res = cgc_delimited_read(0, &read_00389, &read_00389_len, read_00389_delim, 1);
      if (read_00389_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00389_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00389_ptr += cgc_data_match(read_00389 + read_00389_ptr, read_00389_len - read_00389_ptr, match_00389_00000, 8);
      cgc_free(read_00389);
      if (read_00389_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00260_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00260_00000_len = 2;
      unsigned char *write_00260 = NULL;
      unsigned int write_00260_len = 0;
      write_00260 = cgc_append_buf(write_00260, &write_00260_len, write_00260_00000, write_00260_00000_len);
      if (write_00260_len > 0) {
         cgc_transmit_all(1, write_00260, write_00260_len);
      }
      cgc_free(write_00260);
   } while (0);
   do {
      unsigned char *read_00390;
      unsigned int read_00390_len;
      unsigned int read_00390_ptr = 0;
      //**** delimited read
      static unsigned char read_00390_delim[] = 
         "\x0a";
      read_00390 = NULL;
      read_00390_len = 0;
      int read_00390_res = cgc_delimited_read(0, &read_00390, &read_00390_len, read_00390_delim, 1);
      if (read_00390_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00390_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00390_ptr += cgc_data_match(read_00390 + read_00390_ptr, read_00390_len - read_00390_ptr, match_00390_00000, 6);
      cgc_free(read_00390);
      if (read_00390_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00261_00000[] = 
         "\x39\x0a";
      static unsigned int write_00261_00000_len = 2;
      unsigned char *write_00261 = NULL;
      unsigned int write_00261_len = 0;
      write_00261 = cgc_append_buf(write_00261, &write_00261_len, write_00261_00000, write_00261_00000_len);
      if (write_00261_len > 0) {
         cgc_transmit_all(1, write_00261, write_00261_len);
      }
      cgc_free(write_00261);
   } while (0);
   do {
      unsigned char *read_00391;
      unsigned int read_00391_len;
      unsigned int read_00391_ptr = 0;
      //**** delimited read
      static unsigned char read_00391_delim[] = 
         "\x0a";
      read_00391 = NULL;
      read_00391_len = 0;
      int read_00391_res = cgc_delimited_read(0, &read_00391, &read_00391_len, read_00391_delim, 1);
      if (read_00391_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00391_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00391_ptr += cgc_data_match(read_00391 + read_00391_ptr, read_00391_len - read_00391_ptr, match_00391_00000, 29);
      cgc_free(read_00391);
      if (read_00391_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00392;
      unsigned int read_00392_len;
      unsigned int read_00392_ptr = 0;
      //**** delimited read
      static unsigned char read_00392_delim[] = 
         "\x0a";
      read_00392 = NULL;
      read_00392_len = 0;
      int read_00392_res = cgc_delimited_read(0, &read_00392, &read_00392_len, read_00392_delim, 1);
      if (read_00392_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00392_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00392_ptr += cgc_data_match(read_00392 + read_00392_ptr, read_00392_len - read_00392_ptr, match_00392_00000, 65);
      cgc_free(read_00392);
      if (read_00392_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00393;
      unsigned int read_00393_len;
      unsigned int read_00393_ptr = 0;
      //**** delimited read
      static unsigned char read_00393_delim[] = 
         "\x0a";
      read_00393 = NULL;
      read_00393_len = 0;
      int read_00393_res = cgc_delimited_read(0, &read_00393, &read_00393_len, read_00393_delim, 1);
      if (read_00393_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00393_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00393_ptr += cgc_data_match(read_00393 + read_00393_ptr, read_00393_len - read_00393_ptr, match_00393_00000, 7);
      cgc_free(read_00393);
      if (read_00393_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00262_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00262_00000_len = 2;
      unsigned char *write_00262 = NULL;
      unsigned int write_00262_len = 0;
      write_00262 = cgc_append_buf(write_00262, &write_00262_len, write_00262_00000, write_00262_00000_len);
      if (write_00262_len > 0) {
         cgc_transmit_all(1, write_00262, write_00262_len);
      }
      cgc_free(write_00262);
   } while (0);
   do {
      unsigned char *read_00394;
      unsigned int read_00394_len;
      unsigned int read_00394_ptr = 0;
      //**** delimited read
      static unsigned char read_00394_delim[] = 
         "\x0a";
      read_00394 = NULL;
      read_00394_len = 0;
      int read_00394_res = cgc_delimited_read(0, &read_00394, &read_00394_len, read_00394_delim, 1);
      if (read_00394_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00394_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00394_ptr += cgc_data_match(read_00394 + read_00394_ptr, read_00394_len - read_00394_ptr, match_00394_00000, 17);
      cgc_free(read_00394);
      if (read_00394_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00263_00000[] = 
         "\x31\x0a";
      static unsigned int write_00263_00000_len = 2;
      unsigned char *write_00263 = NULL;
      unsigned int write_00263_len = 0;
      write_00263 = cgc_append_buf(write_00263, &write_00263_len, write_00263_00000, write_00263_00000_len);
      if (write_00263_len > 0) {
         cgc_transmit_all(1, write_00263, write_00263_len);
      }
      cgc_free(write_00263);
   } while (0);
   do {
      unsigned char *read_00395;
      unsigned int read_00395_len;
      unsigned int read_00395_ptr = 0;
      //**** delimited read
      static unsigned char read_00395_delim[] = 
         "\x0a";
      read_00395 = NULL;
      read_00395_len = 0;
      int read_00395_res = cgc_delimited_read(0, &read_00395, &read_00395_len, read_00395_delim, 1);
      if (read_00395_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00395_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00395_ptr += cgc_data_match(read_00395 + read_00395_ptr, read_00395_len - read_00395_ptr, match_00395_00000, 29);
      cgc_free(read_00395);
      if (read_00395_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00396;
      unsigned int read_00396_len;
      unsigned int read_00396_ptr = 0;
      //**** delimited read
      static unsigned char read_00396_delim[] = 
         "\x0a";
      read_00396 = NULL;
      read_00396_len = 0;
      int read_00396_res = cgc_delimited_read(0, &read_00396, &read_00396_len, read_00396_delim, 1);
      if (read_00396_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00396_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00396_ptr += cgc_data_match(read_00396 + read_00396_ptr, read_00396_len - read_00396_ptr, match_00396_00000, 65);
      cgc_free(read_00396);
      if (read_00396_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00397;
      unsigned int read_00397_len;
      unsigned int read_00397_ptr = 0;
      //**** delimited read
      static unsigned char read_00397_delim[] = 
         "\x0a";
      read_00397 = NULL;
      read_00397_len = 0;
      int read_00397_res = cgc_delimited_read(0, &read_00397, &read_00397_len, read_00397_delim, 1);
      if (read_00397_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00397_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00397_ptr += cgc_data_match(read_00397 + read_00397_ptr, read_00397_len - read_00397_ptr, match_00397_00000, 7);
      cgc_free(read_00397);
      if (read_00397_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00264_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00264_00000_len = 2;
      unsigned char *write_00264 = NULL;
      unsigned int write_00264_len = 0;
      write_00264 = cgc_append_buf(write_00264, &write_00264_len, write_00264_00000, write_00264_00000_len);
      if (write_00264_len > 0) {
         cgc_transmit_all(1, write_00264, write_00264_len);
      }
      cgc_free(write_00264);
   } while (0);
   do {
      unsigned char *read_00398;
      unsigned int read_00398_len;
      unsigned int read_00398_ptr = 0;
      //**** delimited read
      static unsigned char read_00398_delim[] = 
         "\x0a";
      read_00398 = NULL;
      read_00398_len = 0;
      int read_00398_res = cgc_delimited_read(0, &read_00398, &read_00398_len, read_00398_delim, 1);
      if (read_00398_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00398_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00398_ptr += cgc_data_match(read_00398 + read_00398_ptr, read_00398_len - read_00398_ptr, match_00398_00000, 17);
      cgc_free(read_00398);
      if (read_00398_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00265_00000[] = 
         "\x31\x0a";
      static unsigned int write_00265_00000_len = 2;
      unsigned char *write_00265 = NULL;
      unsigned int write_00265_len = 0;
      write_00265 = cgc_append_buf(write_00265, &write_00265_len, write_00265_00000, write_00265_00000_len);
      if (write_00265_len > 0) {
         cgc_transmit_all(1, write_00265, write_00265_len);
      }
      cgc_free(write_00265);
   } while (0);
   do {
      unsigned char *read_00399;
      unsigned int read_00399_len;
      unsigned int read_00399_ptr = 0;
      //**** delimited read
      static unsigned char read_00399_delim[] = 
         "\x0a";
      read_00399 = NULL;
      read_00399_len = 0;
      int read_00399_res = cgc_delimited_read(0, &read_00399, &read_00399_len, read_00399_delim, 1);
      if (read_00399_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00399_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00399_ptr += cgc_data_match(read_00399 + read_00399_ptr, read_00399_len - read_00399_ptr, match_00399_00000, 8);
      cgc_free(read_00399);
      if (read_00399_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00266_00000[] = 
         "\x44\x0a";
      static unsigned int write_00266_00000_len = 2;
      unsigned char *write_00266 = NULL;
      unsigned int write_00266_len = 0;
      write_00266 = cgc_append_buf(write_00266, &write_00266_len, write_00266_00000, write_00266_00000_len);
      if (write_00266_len > 0) {
         cgc_transmit_all(1, write_00266, write_00266_len);
      }
      cgc_free(write_00266);
   } while (0);
   do {
      unsigned char *read_00400;
      unsigned int read_00400_len;
      unsigned int read_00400_ptr = 0;
      //**** delimited read
      static unsigned char read_00400_delim[] = 
         "\x0a";
      read_00400 = NULL;
      read_00400_len = 0;
      int read_00400_res = cgc_delimited_read(0, &read_00400, &read_00400_len, read_00400_delim, 1);
      if (read_00400_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00400_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00400_ptr += cgc_data_match(read_00400 + read_00400_ptr, read_00400_len - read_00400_ptr, match_00400_00000, 47);
      cgc_free(read_00400);
      if (read_00400_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00401;
      unsigned int read_00401_len;
      unsigned int read_00401_ptr = 0;
      //**** delimited read
      static unsigned char read_00401_delim[] = 
         "\x0a";
      read_00401 = NULL;
      read_00401_len = 0;
      int read_00401_res = cgc_delimited_read(0, &read_00401, &read_00401_len, read_00401_delim, 1);
      if (read_00401_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00401_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00401_ptr += cgc_data_match(read_00401 + read_00401_ptr, read_00401_len - read_00401_ptr, match_00401_00000, 8);
      cgc_free(read_00401);
      if (read_00401_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00267_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00267_00000_len = 2;
      unsigned char *write_00267 = NULL;
      unsigned int write_00267_len = 0;
      write_00267 = cgc_append_buf(write_00267, &write_00267_len, write_00267_00000, write_00267_00000_len);
      if (write_00267_len > 0) {
         cgc_transmit_all(1, write_00267, write_00267_len);
      }
      cgc_free(write_00267);
   } while (0);
   do {
      unsigned char *read_00402;
      unsigned int read_00402_len;
      unsigned int read_00402_ptr = 0;
      //**** delimited read
      static unsigned char read_00402_delim[] = 
         "\x0a";
      read_00402 = NULL;
      read_00402_len = 0;
      int read_00402_res = cgc_delimited_read(0, &read_00402, &read_00402_len, read_00402_delim, 1);
      if (read_00402_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00402_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00402_ptr += cgc_data_match(read_00402 + read_00402_ptr, read_00402_len - read_00402_ptr, match_00402_00000, 6);
      cgc_free(read_00402);
      if (read_00402_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00268_00000[] = 
         "\x31\x30\x0a";
      static unsigned int write_00268_00000_len = 3;
      unsigned char *write_00268 = NULL;
      unsigned int write_00268_len = 0;
      write_00268 = cgc_append_buf(write_00268, &write_00268_len, write_00268_00000, write_00268_00000_len);
      if (write_00268_len > 0) {
         cgc_transmit_all(1, write_00268, write_00268_len);
      }
      cgc_free(write_00268);
   } while (0);
   do {
      unsigned char *read_00403;
      unsigned int read_00403_len;
      unsigned int read_00403_ptr = 0;
      //**** delimited read
      static unsigned char read_00403_delim[] = 
         "\x0a";
      read_00403 = NULL;
      read_00403_len = 0;
      int read_00403_res = cgc_delimited_read(0, &read_00403, &read_00403_len, read_00403_delim, 1);
      if (read_00403_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00403_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00403_ptr += cgc_data_match(read_00403 + read_00403_ptr, read_00403_len - read_00403_ptr, match_00403_00000, 47);
      cgc_free(read_00403);
      if (read_00403_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00404;
      unsigned int read_00404_len;
      unsigned int read_00404_ptr = 0;
      //**** delimited read
      static unsigned char read_00404_delim[] = 
         "\x0a";
      read_00404 = NULL;
      read_00404_len = 0;
      int read_00404_res = cgc_delimited_read(0, &read_00404, &read_00404_len, read_00404_delim, 1);
      if (read_00404_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00404_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00404_ptr += cgc_data_match(read_00404 + read_00404_ptr, read_00404_len - read_00404_ptr, match_00404_00000, 8);
      cgc_free(read_00404);
      if (read_00404_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00269_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00269_00000_len = 2;
      unsigned char *write_00269 = NULL;
      unsigned int write_00269_len = 0;
      write_00269 = cgc_append_buf(write_00269, &write_00269_len, write_00269_00000, write_00269_00000_len);
      if (write_00269_len > 0) {
         cgc_transmit_all(1, write_00269, write_00269_len);
      }
      cgc_free(write_00269);
   } while (0);
   do {
      unsigned char *read_00405;
      unsigned int read_00405_len;
      unsigned int read_00405_ptr = 0;
      //**** delimited read
      static unsigned char read_00405_delim[] = 
         "\x0a";
      read_00405 = NULL;
      read_00405_len = 0;
      int read_00405_res = cgc_delimited_read(0, &read_00405, &read_00405_len, read_00405_delim, 1);
      if (read_00405_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00405_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00405_ptr += cgc_data_match(read_00405 + read_00405_ptr, read_00405_len - read_00405_ptr, match_00405_00000, 6);
      cgc_free(read_00405);
      if (read_00405_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00270_00000[] = 
         "\x31\x31\x0a";
      static unsigned int write_00270_00000_len = 3;
      unsigned char *write_00270 = NULL;
      unsigned int write_00270_len = 0;
      write_00270 = cgc_append_buf(write_00270, &write_00270_len, write_00270_00000, write_00270_00000_len);
      if (write_00270_len > 0) {
         cgc_transmit_all(1, write_00270, write_00270_len);
      }
      cgc_free(write_00270);
   } while (0);
   do {
      unsigned char *read_00406;
      unsigned int read_00406_len;
      unsigned int read_00406_ptr = 0;
      //**** delimited read
      static unsigned char read_00406_delim[] = 
         "\x0a";
      read_00406 = NULL;
      read_00406_len = 0;
      int read_00406_res = cgc_delimited_read(0, &read_00406, &read_00406_len, read_00406_delim, 1);
      if (read_00406_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00406_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00406_ptr += cgc_data_match(read_00406 + read_00406_ptr, read_00406_len - read_00406_ptr, match_00406_00000, 29);
      cgc_free(read_00406);
      if (read_00406_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00407;
      unsigned int read_00407_len;
      unsigned int read_00407_ptr = 0;
      //**** delimited read
      static unsigned char read_00407_delim[] = 
         "\x0a";
      read_00407 = NULL;
      read_00407_len = 0;
      int read_00407_res = cgc_delimited_read(0, &read_00407, &read_00407_len, read_00407_delim, 1);
      if (read_00407_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00407_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00407_ptr += cgc_data_match(read_00407 + read_00407_ptr, read_00407_len - read_00407_ptr, match_00407_00000, 65);
      cgc_free(read_00407);
      if (read_00407_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00408;
      unsigned int read_00408_len;
      unsigned int read_00408_ptr = 0;
      //**** delimited read
      static unsigned char read_00408_delim[] = 
         "\x0a";
      read_00408 = NULL;
      read_00408_len = 0;
      int read_00408_res = cgc_delimited_read(0, &read_00408, &read_00408_len, read_00408_delim, 1);
      if (read_00408_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00408_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00408_ptr += cgc_data_match(read_00408 + read_00408_ptr, read_00408_len - read_00408_ptr, match_00408_00000, 7);
      cgc_free(read_00408);
      if (read_00408_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00271_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00271_00000_len = 2;
      unsigned char *write_00271 = NULL;
      unsigned int write_00271_len = 0;
      write_00271 = cgc_append_buf(write_00271, &write_00271_len, write_00271_00000, write_00271_00000_len);
      if (write_00271_len > 0) {
         cgc_transmit_all(1, write_00271, write_00271_len);
      }
      cgc_free(write_00271);
   } while (0);
   do {
      unsigned char *read_00409;
      unsigned int read_00409_len;
      unsigned int read_00409_ptr = 0;
      //**** delimited read
      static unsigned char read_00409_delim[] = 
         "\x0a";
      read_00409 = NULL;
      read_00409_len = 0;
      int read_00409_res = cgc_delimited_read(0, &read_00409, &read_00409_len, read_00409_delim, 1);
      if (read_00409_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00409_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00409_ptr += cgc_data_match(read_00409 + read_00409_ptr, read_00409_len - read_00409_ptr, match_00409_00000, 17);
      cgc_free(read_00409);
      if (read_00409_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00272_00000[] = 
         "\x31\x0a";
      static unsigned int write_00272_00000_len = 2;
      unsigned char *write_00272 = NULL;
      unsigned int write_00272_len = 0;
      write_00272 = cgc_append_buf(write_00272, &write_00272_len, write_00272_00000, write_00272_00000_len);
      if (write_00272_len > 0) {
         cgc_transmit_all(1, write_00272, write_00272_len);
      }
      cgc_free(write_00272);
   } while (0);
   do {
      unsigned char *read_00410;
      unsigned int read_00410_len;
      unsigned int read_00410_ptr = 0;
      //**** delimited read
      static unsigned char read_00410_delim[] = 
         "\x0a";
      read_00410 = NULL;
      read_00410_len = 0;
      int read_00410_res = cgc_delimited_read(0, &read_00410, &read_00410_len, read_00410_delim, 1);
      if (read_00410_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00410_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00410_ptr += cgc_data_match(read_00410 + read_00410_ptr, read_00410_len - read_00410_ptr, match_00410_00000, 29);
      cgc_free(read_00410);
      if (read_00410_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00411;
      unsigned int read_00411_len;
      unsigned int read_00411_ptr = 0;
      //**** delimited read
      static unsigned char read_00411_delim[] = 
         "\x0a";
      read_00411 = NULL;
      read_00411_len = 0;
      int read_00411_res = cgc_delimited_read(0, &read_00411, &read_00411_len, read_00411_delim, 1);
      if (read_00411_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00411_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00411_ptr += cgc_data_match(read_00411 + read_00411_ptr, read_00411_len - read_00411_ptr, match_00411_00000, 65);
      cgc_free(read_00411);
      if (read_00411_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00412;
      unsigned int read_00412_len;
      unsigned int read_00412_ptr = 0;
      //**** delimited read
      static unsigned char read_00412_delim[] = 
         "\x0a";
      read_00412 = NULL;
      read_00412_len = 0;
      int read_00412_res = cgc_delimited_read(0, &read_00412, &read_00412_len, read_00412_delim, 1);
      if (read_00412_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00412_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00412_ptr += cgc_data_match(read_00412 + read_00412_ptr, read_00412_len - read_00412_ptr, match_00412_00000, 7);
      cgc_free(read_00412);
      if (read_00412_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00273_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00273_00000_len = 2;
      unsigned char *write_00273 = NULL;
      unsigned int write_00273_len = 0;
      write_00273 = cgc_append_buf(write_00273, &write_00273_len, write_00273_00000, write_00273_00000_len);
      if (write_00273_len > 0) {
         cgc_transmit_all(1, write_00273, write_00273_len);
      }
      cgc_free(write_00273);
   } while (0);
   do {
      unsigned char *read_00413;
      unsigned int read_00413_len;
      unsigned int read_00413_ptr = 0;
      //**** delimited read
      static unsigned char read_00413_delim[] = 
         "\x0a";
      read_00413 = NULL;
      read_00413_len = 0;
      int read_00413_res = cgc_delimited_read(0, &read_00413, &read_00413_len, read_00413_delim, 1);
      if (read_00413_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00413_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00413_ptr += cgc_data_match(read_00413 + read_00413_ptr, read_00413_len - read_00413_ptr, match_00413_00000, 17);
      cgc_free(read_00413);
      if (read_00413_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00274_00000[] = 
         "\x31\x0a";
      static unsigned int write_00274_00000_len = 2;
      unsigned char *write_00274 = NULL;
      unsigned int write_00274_len = 0;
      write_00274 = cgc_append_buf(write_00274, &write_00274_len, write_00274_00000, write_00274_00000_len);
      if (write_00274_len > 0) {
         cgc_transmit_all(1, write_00274, write_00274_len);
      }
      cgc_free(write_00274);
   } while (0);
   do {
      unsigned char *read_00414;
      unsigned int read_00414_len;
      unsigned int read_00414_ptr = 0;
      //**** delimited read
      static unsigned char read_00414_delim[] = 
         "\x0a";
      read_00414 = NULL;
      read_00414_len = 0;
      int read_00414_res = cgc_delimited_read(0, &read_00414, &read_00414_len, read_00414_delim, 1);
      if (read_00414_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00414_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00414_ptr += cgc_data_match(read_00414 + read_00414_ptr, read_00414_len - read_00414_ptr, match_00414_00000, 8);
      cgc_free(read_00414);
      if (read_00414_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00275_00000[] = 
         "\x44\x0a";
      static unsigned int write_00275_00000_len = 2;
      unsigned char *write_00275 = NULL;
      unsigned int write_00275_len = 0;
      write_00275 = cgc_append_buf(write_00275, &write_00275_len, write_00275_00000, write_00275_00000_len);
      if (write_00275_len > 0) {
         cgc_transmit_all(1, write_00275, write_00275_len);
      }
      cgc_free(write_00275);
   } while (0);
   do {
      unsigned char *read_00415;
      unsigned int read_00415_len;
      unsigned int read_00415_ptr = 0;
      //**** delimited read
      static unsigned char read_00415_delim[] = 
         "\x0a";
      read_00415 = NULL;
      read_00415_len = 0;
      int read_00415_res = cgc_delimited_read(0, &read_00415, &read_00415_len, read_00415_delim, 1);
      if (read_00415_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00415_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00415_ptr += cgc_data_match(read_00415 + read_00415_ptr, read_00415_len - read_00415_ptr, match_00415_00000, 47);
      cgc_free(read_00415);
      if (read_00415_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00416;
      unsigned int read_00416_len;
      unsigned int read_00416_ptr = 0;
      //**** delimited read
      static unsigned char read_00416_delim[] = 
         "\x0a";
      read_00416 = NULL;
      read_00416_len = 0;
      int read_00416_res = cgc_delimited_read(0, &read_00416, &read_00416_len, read_00416_delim, 1);
      if (read_00416_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00416_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00416_ptr += cgc_data_match(read_00416 + read_00416_ptr, read_00416_len - read_00416_ptr, match_00416_00000, 8);
      cgc_free(read_00416);
      if (read_00416_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00276_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00276_00000_len = 2;
      unsigned char *write_00276 = NULL;
      unsigned int write_00276_len = 0;
      write_00276 = cgc_append_buf(write_00276, &write_00276_len, write_00276_00000, write_00276_00000_len);
      if (write_00276_len > 0) {
         cgc_transmit_all(1, write_00276, write_00276_len);
      }
      cgc_free(write_00276);
   } while (0);
   do {
      unsigned char *read_00417;
      unsigned int read_00417_len;
      unsigned int read_00417_ptr = 0;
      //**** delimited read
      static unsigned char read_00417_delim[] = 
         "\x0a";
      read_00417 = NULL;
      read_00417_len = 0;
      int read_00417_res = cgc_delimited_read(0, &read_00417, &read_00417_len, read_00417_delim, 1);
      if (read_00417_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00417_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00417_ptr += cgc_data_match(read_00417 + read_00417_ptr, read_00417_len - read_00417_ptr, match_00417_00000, 6);
      cgc_free(read_00417);
      if (read_00417_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00277_00000[] = 
         "\x31\x32\x0a";
      static unsigned int write_00277_00000_len = 3;
      unsigned char *write_00277 = NULL;
      unsigned int write_00277_len = 0;
      write_00277 = cgc_append_buf(write_00277, &write_00277_len, write_00277_00000, write_00277_00000_len);
      if (write_00277_len > 0) {
         cgc_transmit_all(1, write_00277, write_00277_len);
      }
      cgc_free(write_00277);
   } while (0);
   do {
      unsigned char *read_00418;
      unsigned int read_00418_len;
      unsigned int read_00418_ptr = 0;
      //**** delimited read
      static unsigned char read_00418_delim[] = 
         "\x0a";
      read_00418 = NULL;
      read_00418_len = 0;
      int read_00418_res = cgc_delimited_read(0, &read_00418, &read_00418_len, read_00418_delim, 1);
      if (read_00418_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00418_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00418_ptr += cgc_data_match(read_00418 + read_00418_ptr, read_00418_len - read_00418_ptr, match_00418_00000, 47);
      cgc_free(read_00418);
      if (read_00418_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00419;
      unsigned int read_00419_len;
      unsigned int read_00419_ptr = 0;
      //**** delimited read
      static unsigned char read_00419_delim[] = 
         "\x0a";
      read_00419 = NULL;
      read_00419_len = 0;
      int read_00419_res = cgc_delimited_read(0, &read_00419, &read_00419_len, read_00419_delim, 1);
      if (read_00419_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00419_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00419_ptr += cgc_data_match(read_00419 + read_00419_ptr, read_00419_len - read_00419_ptr, match_00419_00000, 8);
      cgc_free(read_00419);
      if (read_00419_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00278_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00278_00000_len = 2;
      unsigned char *write_00278 = NULL;
      unsigned int write_00278_len = 0;
      write_00278 = cgc_append_buf(write_00278, &write_00278_len, write_00278_00000, write_00278_00000_len);
      if (write_00278_len > 0) {
         cgc_transmit_all(1, write_00278, write_00278_len);
      }
      cgc_free(write_00278);
   } while (0);
   do {
      unsigned char *read_00420;
      unsigned int read_00420_len;
      unsigned int read_00420_ptr = 0;
      //**** delimited read
      static unsigned char read_00420_delim[] = 
         "\x0a";
      read_00420 = NULL;
      read_00420_len = 0;
      int read_00420_res = cgc_delimited_read(0, &read_00420, &read_00420_len, read_00420_delim, 1);
      if (read_00420_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00420_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00420_ptr += cgc_data_match(read_00420 + read_00420_ptr, read_00420_len - read_00420_ptr, match_00420_00000, 6);
      cgc_free(read_00420);
      if (read_00420_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00279_00000[] = 
         "\x31\x33\x0a";
      static unsigned int write_00279_00000_len = 3;
      unsigned char *write_00279 = NULL;
      unsigned int write_00279_len = 0;
      write_00279 = cgc_append_buf(write_00279, &write_00279_len, write_00279_00000, write_00279_00000_len);
      if (write_00279_len > 0) {
         cgc_transmit_all(1, write_00279, write_00279_len);
      }
      cgc_free(write_00279);
   } while (0);
   do {
      unsigned char *read_00421;
      unsigned int read_00421_len;
      unsigned int read_00421_ptr = 0;
      //**** delimited read
      static unsigned char read_00421_delim[] = 
         "\x0a";
      read_00421 = NULL;
      read_00421_len = 0;
      int read_00421_res = cgc_delimited_read(0, &read_00421, &read_00421_len, read_00421_delim, 1);
      if (read_00421_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00421_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00421_ptr += cgc_data_match(read_00421 + read_00421_ptr, read_00421_len - read_00421_ptr, match_00421_00000, 29);
      cgc_free(read_00421);
      if (read_00421_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00422;
      unsigned int read_00422_len;
      unsigned int read_00422_ptr = 0;
      //**** delimited read
      static unsigned char read_00422_delim[] = 
         "\x0a";
      read_00422 = NULL;
      read_00422_len = 0;
      int read_00422_res = cgc_delimited_read(0, &read_00422, &read_00422_len, read_00422_delim, 1);
      if (read_00422_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00422_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00422_ptr += cgc_data_match(read_00422 + read_00422_ptr, read_00422_len - read_00422_ptr, match_00422_00000, 65);
      cgc_free(read_00422);
      if (read_00422_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00423;
      unsigned int read_00423_len;
      unsigned int read_00423_ptr = 0;
      //**** delimited read
      static unsigned char read_00423_delim[] = 
         "\x0a";
      read_00423 = NULL;
      read_00423_len = 0;
      int read_00423_res = cgc_delimited_read(0, &read_00423, &read_00423_len, read_00423_delim, 1);
      if (read_00423_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00423_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00423_ptr += cgc_data_match(read_00423 + read_00423_ptr, read_00423_len - read_00423_ptr, match_00423_00000, 7);
      cgc_free(read_00423);
      if (read_00423_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00280_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00280_00000_len = 2;
      unsigned char *write_00280 = NULL;
      unsigned int write_00280_len = 0;
      write_00280 = cgc_append_buf(write_00280, &write_00280_len, write_00280_00000, write_00280_00000_len);
      if (write_00280_len > 0) {
         cgc_transmit_all(1, write_00280, write_00280_len);
      }
      cgc_free(write_00280);
   } while (0);
   do {
      unsigned char *read_00424;
      unsigned int read_00424_len;
      unsigned int read_00424_ptr = 0;
      //**** delimited read
      static unsigned char read_00424_delim[] = 
         "\x0a";
      read_00424 = NULL;
      read_00424_len = 0;
      int read_00424_res = cgc_delimited_read(0, &read_00424, &read_00424_len, read_00424_delim, 1);
      if (read_00424_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00424_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00424_ptr += cgc_data_match(read_00424 + read_00424_ptr, read_00424_len - read_00424_ptr, match_00424_00000, 17);
      cgc_free(read_00424);
      if (read_00424_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00281_00000[] = 
         "\x31\x0a";
      static unsigned int write_00281_00000_len = 2;
      unsigned char *write_00281 = NULL;
      unsigned int write_00281_len = 0;
      write_00281 = cgc_append_buf(write_00281, &write_00281_len, write_00281_00000, write_00281_00000_len);
      if (write_00281_len > 0) {
         cgc_transmit_all(1, write_00281, write_00281_len);
      }
      cgc_free(write_00281);
   } while (0);
   do {
      unsigned char *read_00425;
      unsigned int read_00425_len;
      unsigned int read_00425_ptr = 0;
      //**** delimited read
      static unsigned char read_00425_delim[] = 
         "\x0a";
      read_00425 = NULL;
      read_00425_len = 0;
      int read_00425_res = cgc_delimited_read(0, &read_00425, &read_00425_len, read_00425_delim, 1);
      if (read_00425_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00425_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00425_ptr += cgc_data_match(read_00425 + read_00425_ptr, read_00425_len - read_00425_ptr, match_00425_00000, 29);
      cgc_free(read_00425);
      if (read_00425_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00426;
      unsigned int read_00426_len;
      unsigned int read_00426_ptr = 0;
      //**** delimited read
      static unsigned char read_00426_delim[] = 
         "\x0a";
      read_00426 = NULL;
      read_00426_len = 0;
      int read_00426_res = cgc_delimited_read(0, &read_00426, &read_00426_len, read_00426_delim, 1);
      if (read_00426_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00426_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00426_ptr += cgc_data_match(read_00426 + read_00426_ptr, read_00426_len - read_00426_ptr, match_00426_00000, 65);
      cgc_free(read_00426);
      if (read_00426_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00427;
      unsigned int read_00427_len;
      unsigned int read_00427_ptr = 0;
      //**** delimited read
      static unsigned char read_00427_delim[] = 
         "\x0a";
      read_00427 = NULL;
      read_00427_len = 0;
      int read_00427_res = cgc_delimited_read(0, &read_00427, &read_00427_len, read_00427_delim, 1);
      if (read_00427_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00427_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00427_ptr += cgc_data_match(read_00427 + read_00427_ptr, read_00427_len - read_00427_ptr, match_00427_00000, 7);
      cgc_free(read_00427);
      if (read_00427_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00282_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00282_00000_len = 2;
      unsigned char *write_00282 = NULL;
      unsigned int write_00282_len = 0;
      write_00282 = cgc_append_buf(write_00282, &write_00282_len, write_00282_00000, write_00282_00000_len);
      if (write_00282_len > 0) {
         cgc_transmit_all(1, write_00282, write_00282_len);
      }
      cgc_free(write_00282);
   } while (0);
   do {
      unsigned char *read_00428;
      unsigned int read_00428_len;
      unsigned int read_00428_ptr = 0;
      //**** delimited read
      static unsigned char read_00428_delim[] = 
         "\x0a";
      read_00428 = NULL;
      read_00428_len = 0;
      int read_00428_res = cgc_delimited_read(0, &read_00428, &read_00428_len, read_00428_delim, 1);
      if (read_00428_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00428_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00428_ptr += cgc_data_match(read_00428 + read_00428_ptr, read_00428_len - read_00428_ptr, match_00428_00000, 17);
      cgc_free(read_00428);
      if (read_00428_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00283_00000[] = 
         "\x31\x0a";
      static unsigned int write_00283_00000_len = 2;
      unsigned char *write_00283 = NULL;
      unsigned int write_00283_len = 0;
      write_00283 = cgc_append_buf(write_00283, &write_00283_len, write_00283_00000, write_00283_00000_len);
      if (write_00283_len > 0) {
         cgc_transmit_all(1, write_00283, write_00283_len);
      }
      cgc_free(write_00283);
   } while (0);
   do {
      unsigned char *read_00429;
      unsigned int read_00429_len;
      unsigned int read_00429_ptr = 0;
      //**** delimited read
      static unsigned char read_00429_delim[] = 
         "\x0a";
      read_00429 = NULL;
      read_00429_len = 0;
      int read_00429_res = cgc_delimited_read(0, &read_00429, &read_00429_len, read_00429_delim, 1);
      if (read_00429_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00429_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00429_ptr += cgc_data_match(read_00429 + read_00429_ptr, read_00429_len - read_00429_ptr, match_00429_00000, 8);
      cgc_free(read_00429);
      if (read_00429_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00284_00000[] = 
         "\x44\x0a";
      static unsigned int write_00284_00000_len = 2;
      unsigned char *write_00284 = NULL;
      unsigned int write_00284_len = 0;
      write_00284 = cgc_append_buf(write_00284, &write_00284_len, write_00284_00000, write_00284_00000_len);
      if (write_00284_len > 0) {
         cgc_transmit_all(1, write_00284, write_00284_len);
      }
      cgc_free(write_00284);
   } while (0);
   do {
      unsigned char *read_00430;
      unsigned int read_00430_len;
      unsigned int read_00430_ptr = 0;
      //**** delimited read
      static unsigned char read_00430_delim[] = 
         "\x0a";
      read_00430 = NULL;
      read_00430_len = 0;
      int read_00430_res = cgc_delimited_read(0, &read_00430, &read_00430_len, read_00430_delim, 1);
      if (read_00430_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00430_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00430_ptr += cgc_data_match(read_00430 + read_00430_ptr, read_00430_len - read_00430_ptr, match_00430_00000, 47);
      cgc_free(read_00430);
      if (read_00430_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00431;
      unsigned int read_00431_len;
      unsigned int read_00431_ptr = 0;
      //**** delimited read
      static unsigned char read_00431_delim[] = 
         "\x0a";
      read_00431 = NULL;
      read_00431_len = 0;
      int read_00431_res = cgc_delimited_read(0, &read_00431, &read_00431_len, read_00431_delim, 1);
      if (read_00431_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00431_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00431_ptr += cgc_data_match(read_00431 + read_00431_ptr, read_00431_len - read_00431_ptr, match_00431_00000, 8);
      cgc_free(read_00431);
      if (read_00431_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00285_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00285_00000_len = 2;
      unsigned char *write_00285 = NULL;
      unsigned int write_00285_len = 0;
      write_00285 = cgc_append_buf(write_00285, &write_00285_len, write_00285_00000, write_00285_00000_len);
      if (write_00285_len > 0) {
         cgc_transmit_all(1, write_00285, write_00285_len);
      }
      cgc_free(write_00285);
   } while (0);
   do {
      unsigned char *read_00432;
      unsigned int read_00432_len;
      unsigned int read_00432_ptr = 0;
      //**** delimited read
      static unsigned char read_00432_delim[] = 
         "\x0a";
      read_00432 = NULL;
      read_00432_len = 0;
      int read_00432_res = cgc_delimited_read(0, &read_00432, &read_00432_len, read_00432_delim, 1);
      if (read_00432_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00432_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00432_ptr += cgc_data_match(read_00432 + read_00432_ptr, read_00432_len - read_00432_ptr, match_00432_00000, 6);
      cgc_free(read_00432);
      if (read_00432_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00286_00000[] = 
         "\x31\x34\x0a";
      static unsigned int write_00286_00000_len = 3;
      unsigned char *write_00286 = NULL;
      unsigned int write_00286_len = 0;
      write_00286 = cgc_append_buf(write_00286, &write_00286_len, write_00286_00000, write_00286_00000_len);
      if (write_00286_len > 0) {
         cgc_transmit_all(1, write_00286, write_00286_len);
      }
      cgc_free(write_00286);
   } while (0);
   do {
      unsigned char *read_00433;
      unsigned int read_00433_len;
      unsigned int read_00433_ptr = 0;
      //**** delimited read
      static unsigned char read_00433_delim[] = 
         "\x0a";
      read_00433 = NULL;
      read_00433_len = 0;
      int read_00433_res = cgc_delimited_read(0, &read_00433, &read_00433_len, read_00433_delim, 1);
      if (read_00433_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00433_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00433_ptr += cgc_data_match(read_00433 + read_00433_ptr, read_00433_len - read_00433_ptr, match_00433_00000, 47);
      cgc_free(read_00433);
      if (read_00433_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00434;
      unsigned int read_00434_len;
      unsigned int read_00434_ptr = 0;
      //**** delimited read
      static unsigned char read_00434_delim[] = 
         "\x0a";
      read_00434 = NULL;
      read_00434_len = 0;
      int read_00434_res = cgc_delimited_read(0, &read_00434, &read_00434_len, read_00434_delim, 1);
      if (read_00434_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00434_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00434_ptr += cgc_data_match(read_00434 + read_00434_ptr, read_00434_len - read_00434_ptr, match_00434_00000, 8);
      cgc_free(read_00434);
      if (read_00434_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00287_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00287_00000_len = 2;
      unsigned char *write_00287 = NULL;
      unsigned int write_00287_len = 0;
      write_00287 = cgc_append_buf(write_00287, &write_00287_len, write_00287_00000, write_00287_00000_len);
      if (write_00287_len > 0) {
         cgc_transmit_all(1, write_00287, write_00287_len);
      }
      cgc_free(write_00287);
   } while (0);
   do {
      unsigned char *read_00435;
      unsigned int read_00435_len;
      unsigned int read_00435_ptr = 0;
      //**** delimited read
      static unsigned char read_00435_delim[] = 
         "\x0a";
      read_00435 = NULL;
      read_00435_len = 0;
      int read_00435_res = cgc_delimited_read(0, &read_00435, &read_00435_len, read_00435_delim, 1);
      if (read_00435_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00435_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00435_ptr += cgc_data_match(read_00435 + read_00435_ptr, read_00435_len - read_00435_ptr, match_00435_00000, 6);
      cgc_free(read_00435);
      if (read_00435_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00288_00000[] = 
         "\x31\x35\x0a";
      static unsigned int write_00288_00000_len = 3;
      unsigned char *write_00288 = NULL;
      unsigned int write_00288_len = 0;
      write_00288 = cgc_append_buf(write_00288, &write_00288_len, write_00288_00000, write_00288_00000_len);
      if (write_00288_len > 0) {
         cgc_transmit_all(1, write_00288, write_00288_len);
      }
      cgc_free(write_00288);
   } while (0);
   do {
      unsigned char *read_00436;
      unsigned int read_00436_len;
      unsigned int read_00436_ptr = 0;
      //**** delimited read
      static unsigned char read_00436_delim[] = 
         "\x0a";
      read_00436 = NULL;
      read_00436_len = 0;
      int read_00436_res = cgc_delimited_read(0, &read_00436, &read_00436_len, read_00436_delim, 1);
      if (read_00436_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00436_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00436_ptr += cgc_data_match(read_00436 + read_00436_ptr, read_00436_len - read_00436_ptr, match_00436_00000, 29);
      cgc_free(read_00436);
      if (read_00436_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00437;
      unsigned int read_00437_len;
      unsigned int read_00437_ptr = 0;
      //**** delimited read
      static unsigned char read_00437_delim[] = 
         "\x0a";
      read_00437 = NULL;
      read_00437_len = 0;
      int read_00437_res = cgc_delimited_read(0, &read_00437, &read_00437_len, read_00437_delim, 1);
      if (read_00437_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00437_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00437_ptr += cgc_data_match(read_00437 + read_00437_ptr, read_00437_len - read_00437_ptr, match_00437_00000, 65);
      cgc_free(read_00437);
      if (read_00437_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00438;
      unsigned int read_00438_len;
      unsigned int read_00438_ptr = 0;
      //**** delimited read
      static unsigned char read_00438_delim[] = 
         "\x0a";
      read_00438 = NULL;
      read_00438_len = 0;
      int read_00438_res = cgc_delimited_read(0, &read_00438, &read_00438_len, read_00438_delim, 1);
      if (read_00438_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00438_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00438_ptr += cgc_data_match(read_00438 + read_00438_ptr, read_00438_len - read_00438_ptr, match_00438_00000, 7);
      cgc_free(read_00438);
      if (read_00438_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00289_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00289_00000_len = 2;
      unsigned char *write_00289 = NULL;
      unsigned int write_00289_len = 0;
      write_00289 = cgc_append_buf(write_00289, &write_00289_len, write_00289_00000, write_00289_00000_len);
      if (write_00289_len > 0) {
         cgc_transmit_all(1, write_00289, write_00289_len);
      }
      cgc_free(write_00289);
   } while (0);
   do {
      unsigned char *read_00439;
      unsigned int read_00439_len;
      unsigned int read_00439_ptr = 0;
      //**** delimited read
      static unsigned char read_00439_delim[] = 
         "\x0a";
      read_00439 = NULL;
      read_00439_len = 0;
      int read_00439_res = cgc_delimited_read(0, &read_00439, &read_00439_len, read_00439_delim, 1);
      if (read_00439_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00439_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00439_ptr += cgc_data_match(read_00439 + read_00439_ptr, read_00439_len - read_00439_ptr, match_00439_00000, 17);
      cgc_free(read_00439);
      if (read_00439_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00290_00000[] = 
         "\x31\x0a";
      static unsigned int write_00290_00000_len = 2;
      unsigned char *write_00290 = NULL;
      unsigned int write_00290_len = 0;
      write_00290 = cgc_append_buf(write_00290, &write_00290_len, write_00290_00000, write_00290_00000_len);
      if (write_00290_len > 0) {
         cgc_transmit_all(1, write_00290, write_00290_len);
      }
      cgc_free(write_00290);
   } while (0);
   do {
      unsigned char *read_00440;
      unsigned int read_00440_len;
      unsigned int read_00440_ptr = 0;
      //**** delimited read
      static unsigned char read_00440_delim[] = 
         "\x0a";
      read_00440 = NULL;
      read_00440_len = 0;
      int read_00440_res = cgc_delimited_read(0, &read_00440, &read_00440_len, read_00440_delim, 1);
      if (read_00440_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00440_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00440_ptr += cgc_data_match(read_00440 + read_00440_ptr, read_00440_len - read_00440_ptr, match_00440_00000, 29);
      cgc_free(read_00440);
      if (read_00440_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00441;
      unsigned int read_00441_len;
      unsigned int read_00441_ptr = 0;
      //**** delimited read
      static unsigned char read_00441_delim[] = 
         "\x0a";
      read_00441 = NULL;
      read_00441_len = 0;
      int read_00441_res = cgc_delimited_read(0, &read_00441, &read_00441_len, read_00441_delim, 1);
      if (read_00441_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00441_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00441_ptr += cgc_data_match(read_00441 + read_00441_ptr, read_00441_len - read_00441_ptr, match_00441_00000, 65);
      cgc_free(read_00441);
      if (read_00441_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00442;
      unsigned int read_00442_len;
      unsigned int read_00442_ptr = 0;
      //**** delimited read
      static unsigned char read_00442_delim[] = 
         "\x0a";
      read_00442 = NULL;
      read_00442_len = 0;
      int read_00442_res = cgc_delimited_read(0, &read_00442, &read_00442_len, read_00442_delim, 1);
      if (read_00442_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00442_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00442_ptr += cgc_data_match(read_00442 + read_00442_ptr, read_00442_len - read_00442_ptr, match_00442_00000, 7);
      cgc_free(read_00442);
      if (read_00442_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00291_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00291_00000_len = 2;
      unsigned char *write_00291 = NULL;
      unsigned int write_00291_len = 0;
      write_00291 = cgc_append_buf(write_00291, &write_00291_len, write_00291_00000, write_00291_00000_len);
      if (write_00291_len > 0) {
         cgc_transmit_all(1, write_00291, write_00291_len);
      }
      cgc_free(write_00291);
   } while (0);
   do {
      unsigned char *read_00443;
      unsigned int read_00443_len;
      unsigned int read_00443_ptr = 0;
      //**** delimited read
      static unsigned char read_00443_delim[] = 
         "\x0a";
      read_00443 = NULL;
      read_00443_len = 0;
      int read_00443_res = cgc_delimited_read(0, &read_00443, &read_00443_len, read_00443_delim, 1);
      if (read_00443_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00443_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00443_ptr += cgc_data_match(read_00443 + read_00443_ptr, read_00443_len - read_00443_ptr, match_00443_00000, 17);
      cgc_free(read_00443);
      if (read_00443_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00292_00000[] = 
         "\x31\x0a";
      static unsigned int write_00292_00000_len = 2;
      unsigned char *write_00292 = NULL;
      unsigned int write_00292_len = 0;
      write_00292 = cgc_append_buf(write_00292, &write_00292_len, write_00292_00000, write_00292_00000_len);
      if (write_00292_len > 0) {
         cgc_transmit_all(1, write_00292, write_00292_len);
      }
      cgc_free(write_00292);
   } while (0);
   do {
      unsigned char *read_00444;
      unsigned int read_00444_len;
      unsigned int read_00444_ptr = 0;
      //**** delimited read
      static unsigned char read_00444_delim[] = 
         "\x0a";
      read_00444 = NULL;
      read_00444_len = 0;
      int read_00444_res = cgc_delimited_read(0, &read_00444, &read_00444_len, read_00444_delim, 1);
      if (read_00444_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00444_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00444_ptr += cgc_data_match(read_00444 + read_00444_ptr, read_00444_len - read_00444_ptr, match_00444_00000, 8);
      cgc_free(read_00444);
      if (read_00444_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00293_00000[] = 
         "\x44\x0a";
      static unsigned int write_00293_00000_len = 2;
      unsigned char *write_00293 = NULL;
      unsigned int write_00293_len = 0;
      write_00293 = cgc_append_buf(write_00293, &write_00293_len, write_00293_00000, write_00293_00000_len);
      if (write_00293_len > 0) {
         cgc_transmit_all(1, write_00293, write_00293_len);
      }
      cgc_free(write_00293);
   } while (0);
   do {
      unsigned char *read_00445;
      unsigned int read_00445_len;
      unsigned int read_00445_ptr = 0;
      //**** delimited read
      static unsigned char read_00445_delim[] = 
         "\x0a";
      read_00445 = NULL;
      read_00445_len = 0;
      int read_00445_res = cgc_delimited_read(0, &read_00445, &read_00445_len, read_00445_delim, 1);
      if (read_00445_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00445_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00445_ptr += cgc_data_match(read_00445 + read_00445_ptr, read_00445_len - read_00445_ptr, match_00445_00000, 47);
      cgc_free(read_00445);
      if (read_00445_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00446;
      unsigned int read_00446_len;
      unsigned int read_00446_ptr = 0;
      //**** delimited read
      static unsigned char read_00446_delim[] = 
         "\x0a";
      read_00446 = NULL;
      read_00446_len = 0;
      int read_00446_res = cgc_delimited_read(0, &read_00446, &read_00446_len, read_00446_delim, 1);
      if (read_00446_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00446_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00446_ptr += cgc_data_match(read_00446 + read_00446_ptr, read_00446_len - read_00446_ptr, match_00446_00000, 8);
      cgc_free(read_00446);
      if (read_00446_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00294_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00294_00000_len = 2;
      unsigned char *write_00294 = NULL;
      unsigned int write_00294_len = 0;
      write_00294 = cgc_append_buf(write_00294, &write_00294_len, write_00294_00000, write_00294_00000_len);
      if (write_00294_len > 0) {
         cgc_transmit_all(1, write_00294, write_00294_len);
      }
      cgc_free(write_00294);
   } while (0);
   do {
      unsigned char *read_00447;
      unsigned int read_00447_len;
      unsigned int read_00447_ptr = 0;
      //**** delimited read
      static unsigned char read_00447_delim[] = 
         "\x0a";
      read_00447 = NULL;
      read_00447_len = 0;
      int read_00447_res = cgc_delimited_read(0, &read_00447, &read_00447_len, read_00447_delim, 1);
      if (read_00447_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00447_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00447_ptr += cgc_data_match(read_00447 + read_00447_ptr, read_00447_len - read_00447_ptr, match_00447_00000, 6);
      cgc_free(read_00447);
      if (read_00447_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00295_00000[] = 
         "\x31\x36\x0a";
      static unsigned int write_00295_00000_len = 3;
      unsigned char *write_00295 = NULL;
      unsigned int write_00295_len = 0;
      write_00295 = cgc_append_buf(write_00295, &write_00295_len, write_00295_00000, write_00295_00000_len);
      if (write_00295_len > 0) {
         cgc_transmit_all(1, write_00295, write_00295_len);
      }
      cgc_free(write_00295);
   } while (0);
   do {
      unsigned char *read_00448;
      unsigned int read_00448_len;
      unsigned int read_00448_ptr = 0;
      //**** delimited read
      static unsigned char read_00448_delim[] = 
         "\x0a";
      read_00448 = NULL;
      read_00448_len = 0;
      int read_00448_res = cgc_delimited_read(0, &read_00448, &read_00448_len, read_00448_delim, 1);
      if (read_00448_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00448_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00448_ptr += cgc_data_match(read_00448 + read_00448_ptr, read_00448_len - read_00448_ptr, match_00448_00000, 47);
      cgc_free(read_00448);
      if (read_00448_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00449;
      unsigned int read_00449_len;
      unsigned int read_00449_ptr = 0;
      //**** delimited read
      static unsigned char read_00449_delim[] = 
         "\x0a";
      read_00449 = NULL;
      read_00449_len = 0;
      int read_00449_res = cgc_delimited_read(0, &read_00449, &read_00449_len, read_00449_delim, 1);
      if (read_00449_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00449_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00449_ptr += cgc_data_match(read_00449 + read_00449_ptr, read_00449_len - read_00449_ptr, match_00449_00000, 8);
      cgc_free(read_00449);
      if (read_00449_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00296_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00296_00000_len = 2;
      unsigned char *write_00296 = NULL;
      unsigned int write_00296_len = 0;
      write_00296 = cgc_append_buf(write_00296, &write_00296_len, write_00296_00000, write_00296_00000_len);
      if (write_00296_len > 0) {
         cgc_transmit_all(1, write_00296, write_00296_len);
      }
      cgc_free(write_00296);
   } while (0);
   do {
      unsigned char *read_00450;
      unsigned int read_00450_len;
      unsigned int read_00450_ptr = 0;
      //**** delimited read
      static unsigned char read_00450_delim[] = 
         "\x0a";
      read_00450 = NULL;
      read_00450_len = 0;
      int read_00450_res = cgc_delimited_read(0, &read_00450, &read_00450_len, read_00450_delim, 1);
      if (read_00450_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00450_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00450_ptr += cgc_data_match(read_00450 + read_00450_ptr, read_00450_len - read_00450_ptr, match_00450_00000, 6);
      cgc_free(read_00450);
      if (read_00450_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00297_00000[] = 
         "\x31\x37\x0a";
      static unsigned int write_00297_00000_len = 3;
      unsigned char *write_00297 = NULL;
      unsigned int write_00297_len = 0;
      write_00297 = cgc_append_buf(write_00297, &write_00297_len, write_00297_00000, write_00297_00000_len);
      if (write_00297_len > 0) {
         cgc_transmit_all(1, write_00297, write_00297_len);
      }
      cgc_free(write_00297);
   } while (0);
   do {
      unsigned char *read_00451;
      unsigned int read_00451_len;
      unsigned int read_00451_ptr = 0;
      //**** delimited read
      static unsigned char read_00451_delim[] = 
         "\x0a";
      read_00451 = NULL;
      read_00451_len = 0;
      int read_00451_res = cgc_delimited_read(0, &read_00451, &read_00451_len, read_00451_delim, 1);
      if (read_00451_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00451_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00451_ptr += cgc_data_match(read_00451 + read_00451_ptr, read_00451_len - read_00451_ptr, match_00451_00000, 29);
      cgc_free(read_00451);
      if (read_00451_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00452;
      unsigned int read_00452_len;
      unsigned int read_00452_ptr = 0;
      //**** delimited read
      static unsigned char read_00452_delim[] = 
         "\x0a";
      read_00452 = NULL;
      read_00452_len = 0;
      int read_00452_res = cgc_delimited_read(0, &read_00452, &read_00452_len, read_00452_delim, 1);
      if (read_00452_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00452_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00452_ptr += cgc_data_match(read_00452 + read_00452_ptr, read_00452_len - read_00452_ptr, match_00452_00000, 65);
      cgc_free(read_00452);
      if (read_00452_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00453;
      unsigned int read_00453_len;
      unsigned int read_00453_ptr = 0;
      //**** delimited read
      static unsigned char read_00453_delim[] = 
         "\x0a";
      read_00453 = NULL;
      read_00453_len = 0;
      int read_00453_res = cgc_delimited_read(0, &read_00453, &read_00453_len, read_00453_delim, 1);
      if (read_00453_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00453_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00453_ptr += cgc_data_match(read_00453 + read_00453_ptr, read_00453_len - read_00453_ptr, match_00453_00000, 7);
      cgc_free(read_00453);
      if (read_00453_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00298_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00298_00000_len = 2;
      unsigned char *write_00298 = NULL;
      unsigned int write_00298_len = 0;
      write_00298 = cgc_append_buf(write_00298, &write_00298_len, write_00298_00000, write_00298_00000_len);
      if (write_00298_len > 0) {
         cgc_transmit_all(1, write_00298, write_00298_len);
      }
      cgc_free(write_00298);
   } while (0);
   do {
      unsigned char *read_00454;
      unsigned int read_00454_len;
      unsigned int read_00454_ptr = 0;
      //**** delimited read
      static unsigned char read_00454_delim[] = 
         "\x0a";
      read_00454 = NULL;
      read_00454_len = 0;
      int read_00454_res = cgc_delimited_read(0, &read_00454, &read_00454_len, read_00454_delim, 1);
      if (read_00454_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00454_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00454_ptr += cgc_data_match(read_00454 + read_00454_ptr, read_00454_len - read_00454_ptr, match_00454_00000, 17);
      cgc_free(read_00454);
      if (read_00454_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00299_00000[] = 
         "\x31\x0a";
      static unsigned int write_00299_00000_len = 2;
      unsigned char *write_00299 = NULL;
      unsigned int write_00299_len = 0;
      write_00299 = cgc_append_buf(write_00299, &write_00299_len, write_00299_00000, write_00299_00000_len);
      if (write_00299_len > 0) {
         cgc_transmit_all(1, write_00299, write_00299_len);
      }
      cgc_free(write_00299);
   } while (0);
   do {
      unsigned char *read_00455;
      unsigned int read_00455_len;
      unsigned int read_00455_ptr = 0;
      //**** delimited read
      static unsigned char read_00455_delim[] = 
         "\x0a";
      read_00455 = NULL;
      read_00455_len = 0;
      int read_00455_res = cgc_delimited_read(0, &read_00455, &read_00455_len, read_00455_delim, 1);
      if (read_00455_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00455_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00455_ptr += cgc_data_match(read_00455 + read_00455_ptr, read_00455_len - read_00455_ptr, match_00455_00000, 29);
      cgc_free(read_00455);
      if (read_00455_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00456;
      unsigned int read_00456_len;
      unsigned int read_00456_ptr = 0;
      //**** delimited read
      static unsigned char read_00456_delim[] = 
         "\x0a";
      read_00456 = NULL;
      read_00456_len = 0;
      int read_00456_res = cgc_delimited_read(0, &read_00456, &read_00456_len, read_00456_delim, 1);
      if (read_00456_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00456_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00456_ptr += cgc_data_match(read_00456 + read_00456_ptr, read_00456_len - read_00456_ptr, match_00456_00000, 65);
      cgc_free(read_00456);
      if (read_00456_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00457;
      unsigned int read_00457_len;
      unsigned int read_00457_ptr = 0;
      //**** delimited read
      static unsigned char read_00457_delim[] = 
         "\x0a";
      read_00457 = NULL;
      read_00457_len = 0;
      int read_00457_res = cgc_delimited_read(0, &read_00457, &read_00457_len, read_00457_delim, 1);
      if (read_00457_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00457_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00457_ptr += cgc_data_match(read_00457 + read_00457_ptr, read_00457_len - read_00457_ptr, match_00457_00000, 7);
      cgc_free(read_00457);
      if (read_00457_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00300_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00300_00000_len = 2;
      unsigned char *write_00300 = NULL;
      unsigned int write_00300_len = 0;
      write_00300 = cgc_append_buf(write_00300, &write_00300_len, write_00300_00000, write_00300_00000_len);
      if (write_00300_len > 0) {
         cgc_transmit_all(1, write_00300, write_00300_len);
      }
      cgc_free(write_00300);
   } while (0);
   do {
      unsigned char *read_00458;
      unsigned int read_00458_len;
      unsigned int read_00458_ptr = 0;
      //**** delimited read
      static unsigned char read_00458_delim[] = 
         "\x0a";
      read_00458 = NULL;
      read_00458_len = 0;
      int read_00458_res = cgc_delimited_read(0, &read_00458, &read_00458_len, read_00458_delim, 1);
      if (read_00458_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00458_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00458_ptr += cgc_data_match(read_00458 + read_00458_ptr, read_00458_len - read_00458_ptr, match_00458_00000, 17);
      cgc_free(read_00458);
      if (read_00458_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00301_00000[] = 
         "\x31\x0a";
      static unsigned int write_00301_00000_len = 2;
      unsigned char *write_00301 = NULL;
      unsigned int write_00301_len = 0;
      write_00301 = cgc_append_buf(write_00301, &write_00301_len, write_00301_00000, write_00301_00000_len);
      if (write_00301_len > 0) {
         cgc_transmit_all(1, write_00301, write_00301_len);
      }
      cgc_free(write_00301);
   } while (0);
   do {
      unsigned char *read_00459;
      unsigned int read_00459_len;
      unsigned int read_00459_ptr = 0;
      //**** delimited read
      static unsigned char read_00459_delim[] = 
         "\x0a";
      read_00459 = NULL;
      read_00459_len = 0;
      int read_00459_res = cgc_delimited_read(0, &read_00459, &read_00459_len, read_00459_delim, 1);
      if (read_00459_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00459_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00459_ptr += cgc_data_match(read_00459 + read_00459_ptr, read_00459_len - read_00459_ptr, match_00459_00000, 8);
      cgc_free(read_00459);
      if (read_00459_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00302_00000[] = 
         "\x44\x0a";
      static unsigned int write_00302_00000_len = 2;
      unsigned char *write_00302 = NULL;
      unsigned int write_00302_len = 0;
      write_00302 = cgc_append_buf(write_00302, &write_00302_len, write_00302_00000, write_00302_00000_len);
      if (write_00302_len > 0) {
         cgc_transmit_all(1, write_00302, write_00302_len);
      }
      cgc_free(write_00302);
   } while (0);
   do {
      unsigned char *read_00460;
      unsigned int read_00460_len;
      unsigned int read_00460_ptr = 0;
      //**** delimited read
      static unsigned char read_00460_delim[] = 
         "\x0a";
      read_00460 = NULL;
      read_00460_len = 0;
      int read_00460_res = cgc_delimited_read(0, &read_00460, &read_00460_len, read_00460_delim, 1);
      if (read_00460_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00460_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00460_ptr += cgc_data_match(read_00460 + read_00460_ptr, read_00460_len - read_00460_ptr, match_00460_00000, 47);
      cgc_free(read_00460);
      if (read_00460_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00461;
      unsigned int read_00461_len;
      unsigned int read_00461_ptr = 0;
      //**** delimited read
      static unsigned char read_00461_delim[] = 
         "\x0a";
      read_00461 = NULL;
      read_00461_len = 0;
      int read_00461_res = cgc_delimited_read(0, &read_00461, &read_00461_len, read_00461_delim, 1);
      if (read_00461_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00461_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00461_ptr += cgc_data_match(read_00461 + read_00461_ptr, read_00461_len - read_00461_ptr, match_00461_00000, 8);
      cgc_free(read_00461);
      if (read_00461_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00303_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00303_00000_len = 2;
      unsigned char *write_00303 = NULL;
      unsigned int write_00303_len = 0;
      write_00303 = cgc_append_buf(write_00303, &write_00303_len, write_00303_00000, write_00303_00000_len);
      if (write_00303_len > 0) {
         cgc_transmit_all(1, write_00303, write_00303_len);
      }
      cgc_free(write_00303);
   } while (0);
   do {
      unsigned char *read_00462;
      unsigned int read_00462_len;
      unsigned int read_00462_ptr = 0;
      //**** delimited read
      static unsigned char read_00462_delim[] = 
         "\x0a";
      read_00462 = NULL;
      read_00462_len = 0;
      int read_00462_res = cgc_delimited_read(0, &read_00462, &read_00462_len, read_00462_delim, 1);
      if (read_00462_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00462_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00462_ptr += cgc_data_match(read_00462 + read_00462_ptr, read_00462_len - read_00462_ptr, match_00462_00000, 6);
      cgc_free(read_00462);
      if (read_00462_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00304_00000[] = 
         "\x31\x38\x0a";
      static unsigned int write_00304_00000_len = 3;
      unsigned char *write_00304 = NULL;
      unsigned int write_00304_len = 0;
      write_00304 = cgc_append_buf(write_00304, &write_00304_len, write_00304_00000, write_00304_00000_len);
      if (write_00304_len > 0) {
         cgc_transmit_all(1, write_00304, write_00304_len);
      }
      cgc_free(write_00304);
   } while (0);
   do {
      unsigned char *read_00463;
      unsigned int read_00463_len;
      unsigned int read_00463_ptr = 0;
      //**** delimited read
      static unsigned char read_00463_delim[] = 
         "\x0a";
      read_00463 = NULL;
      read_00463_len = 0;
      int read_00463_res = cgc_delimited_read(0, &read_00463, &read_00463_len, read_00463_delim, 1);
      if (read_00463_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00463_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00463_ptr += cgc_data_match(read_00463 + read_00463_ptr, read_00463_len - read_00463_ptr, match_00463_00000, 47);
      cgc_free(read_00463);
      if (read_00463_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00464;
      unsigned int read_00464_len;
      unsigned int read_00464_ptr = 0;
      //**** delimited read
      static unsigned char read_00464_delim[] = 
         "\x0a";
      read_00464 = NULL;
      read_00464_len = 0;
      int read_00464_res = cgc_delimited_read(0, &read_00464, &read_00464_len, read_00464_delim, 1);
      if (read_00464_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00464_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00464_ptr += cgc_data_match(read_00464 + read_00464_ptr, read_00464_len - read_00464_ptr, match_00464_00000, 8);
      cgc_free(read_00464);
      if (read_00464_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00305_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00305_00000_len = 2;
      unsigned char *write_00305 = NULL;
      unsigned int write_00305_len = 0;
      write_00305 = cgc_append_buf(write_00305, &write_00305_len, write_00305_00000, write_00305_00000_len);
      if (write_00305_len > 0) {
         cgc_transmit_all(1, write_00305, write_00305_len);
      }
      cgc_free(write_00305);
   } while (0);
   do {
      unsigned char *read_00465;
      unsigned int read_00465_len;
      unsigned int read_00465_ptr = 0;
      //**** delimited read
      static unsigned char read_00465_delim[] = 
         "\x0a";
      read_00465 = NULL;
      read_00465_len = 0;
      int read_00465_res = cgc_delimited_read(0, &read_00465, &read_00465_len, read_00465_delim, 1);
      if (read_00465_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00465_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00465_ptr += cgc_data_match(read_00465 + read_00465_ptr, read_00465_len - read_00465_ptr, match_00465_00000, 6);
      cgc_free(read_00465);
      if (read_00465_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00306_00000[] = 
         "\x31\x39\x0a";
      static unsigned int write_00306_00000_len = 3;
      unsigned char *write_00306 = NULL;
      unsigned int write_00306_len = 0;
      write_00306 = cgc_append_buf(write_00306, &write_00306_len, write_00306_00000, write_00306_00000_len);
      if (write_00306_len > 0) {
         cgc_transmit_all(1, write_00306, write_00306_len);
      }
      cgc_free(write_00306);
   } while (0);
   do {
      unsigned char *read_00466;
      unsigned int read_00466_len;
      unsigned int read_00466_ptr = 0;
      //**** delimited read
      static unsigned char read_00466_delim[] = 
         "\x0a";
      read_00466 = NULL;
      read_00466_len = 0;
      int read_00466_res = cgc_delimited_read(0, &read_00466, &read_00466_len, read_00466_delim, 1);
      if (read_00466_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00466_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00466_ptr += cgc_data_match(read_00466 + read_00466_ptr, read_00466_len - read_00466_ptr, match_00466_00000, 29);
      cgc_free(read_00466);
      if (read_00466_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00467;
      unsigned int read_00467_len;
      unsigned int read_00467_ptr = 0;
      //**** delimited read
      static unsigned char read_00467_delim[] = 
         "\x0a";
      read_00467 = NULL;
      read_00467_len = 0;
      int read_00467_res = cgc_delimited_read(0, &read_00467, &read_00467_len, read_00467_delim, 1);
      if (read_00467_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00467_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00467_ptr += cgc_data_match(read_00467 + read_00467_ptr, read_00467_len - read_00467_ptr, match_00467_00000, 65);
      cgc_free(read_00467);
      if (read_00467_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00468;
      unsigned int read_00468_len;
      unsigned int read_00468_ptr = 0;
      //**** delimited read
      static unsigned char read_00468_delim[] = 
         "\x0a";
      read_00468 = NULL;
      read_00468_len = 0;
      int read_00468_res = cgc_delimited_read(0, &read_00468, &read_00468_len, read_00468_delim, 1);
      if (read_00468_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00468_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00468_ptr += cgc_data_match(read_00468 + read_00468_ptr, read_00468_len - read_00468_ptr, match_00468_00000, 7);
      cgc_free(read_00468);
      if (read_00468_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00307_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00307_00000_len = 2;
      unsigned char *write_00307 = NULL;
      unsigned int write_00307_len = 0;
      write_00307 = cgc_append_buf(write_00307, &write_00307_len, write_00307_00000, write_00307_00000_len);
      if (write_00307_len > 0) {
         cgc_transmit_all(1, write_00307, write_00307_len);
      }
      cgc_free(write_00307);
   } while (0);
   do {
      unsigned char *read_00469;
      unsigned int read_00469_len;
      unsigned int read_00469_ptr = 0;
      //**** delimited read
      static unsigned char read_00469_delim[] = 
         "\x0a";
      read_00469 = NULL;
      read_00469_len = 0;
      int read_00469_res = cgc_delimited_read(0, &read_00469, &read_00469_len, read_00469_delim, 1);
      if (read_00469_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00469_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00469_ptr += cgc_data_match(read_00469 + read_00469_ptr, read_00469_len - read_00469_ptr, match_00469_00000, 17);
      cgc_free(read_00469);
      if (read_00469_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00308_00000[] = 
         "\x31\x0a";
      static unsigned int write_00308_00000_len = 2;
      unsigned char *write_00308 = NULL;
      unsigned int write_00308_len = 0;
      write_00308 = cgc_append_buf(write_00308, &write_00308_len, write_00308_00000, write_00308_00000_len);
      if (write_00308_len > 0) {
         cgc_transmit_all(1, write_00308, write_00308_len);
      }
      cgc_free(write_00308);
   } while (0);
   do {
      unsigned char *read_00470;
      unsigned int read_00470_len;
      unsigned int read_00470_ptr = 0;
      //**** delimited read
      static unsigned char read_00470_delim[] = 
         "\x0a";
      read_00470 = NULL;
      read_00470_len = 0;
      int read_00470_res = cgc_delimited_read(0, &read_00470, &read_00470_len, read_00470_delim, 1);
      if (read_00470_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00470_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00470_ptr += cgc_data_match(read_00470 + read_00470_ptr, read_00470_len - read_00470_ptr, match_00470_00000, 29);
      cgc_free(read_00470);
      if (read_00470_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00471;
      unsigned int read_00471_len;
      unsigned int read_00471_ptr = 0;
      //**** delimited read
      static unsigned char read_00471_delim[] = 
         "\x0a";
      read_00471 = NULL;
      read_00471_len = 0;
      int read_00471_res = cgc_delimited_read(0, &read_00471, &read_00471_len, read_00471_delim, 1);
      if (read_00471_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00471_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00471_ptr += cgc_data_match(read_00471 + read_00471_ptr, read_00471_len - read_00471_ptr, match_00471_00000, 65);
      cgc_free(read_00471);
      if (read_00471_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00472;
      unsigned int read_00472_len;
      unsigned int read_00472_ptr = 0;
      //**** delimited read
      static unsigned char read_00472_delim[] = 
         "\x0a";
      read_00472 = NULL;
      read_00472_len = 0;
      int read_00472_res = cgc_delimited_read(0, &read_00472, &read_00472_len, read_00472_delim, 1);
      if (read_00472_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00472_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00472_ptr += cgc_data_match(read_00472 + read_00472_ptr, read_00472_len - read_00472_ptr, match_00472_00000, 7);
      cgc_free(read_00472);
      if (read_00472_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00309_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00309_00000_len = 2;
      unsigned char *write_00309 = NULL;
      unsigned int write_00309_len = 0;
      write_00309 = cgc_append_buf(write_00309, &write_00309_len, write_00309_00000, write_00309_00000_len);
      if (write_00309_len > 0) {
         cgc_transmit_all(1, write_00309, write_00309_len);
      }
      cgc_free(write_00309);
   } while (0);
   do {
      unsigned char *read_00473;
      unsigned int read_00473_len;
      unsigned int read_00473_ptr = 0;
      //**** delimited read
      static unsigned char read_00473_delim[] = 
         "\x0a";
      read_00473 = NULL;
      read_00473_len = 0;
      int read_00473_res = cgc_delimited_read(0, &read_00473, &read_00473_len, read_00473_delim, 1);
      if (read_00473_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00473_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00473_ptr += cgc_data_match(read_00473 + read_00473_ptr, read_00473_len - read_00473_ptr, match_00473_00000, 17);
      cgc_free(read_00473);
      if (read_00473_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00310_00000[] = 
         "\x31\x0a";
      static unsigned int write_00310_00000_len = 2;
      unsigned char *write_00310 = NULL;
      unsigned int write_00310_len = 0;
      write_00310 = cgc_append_buf(write_00310, &write_00310_len, write_00310_00000, write_00310_00000_len);
      if (write_00310_len > 0) {
         cgc_transmit_all(1, write_00310, write_00310_len);
      }
      cgc_free(write_00310);
   } while (0);
   do {
      unsigned char *read_00474;
      unsigned int read_00474_len;
      unsigned int read_00474_ptr = 0;
      //**** delimited read
      static unsigned char read_00474_delim[] = 
         "\x0a";
      read_00474 = NULL;
      read_00474_len = 0;
      int read_00474_res = cgc_delimited_read(0, &read_00474, &read_00474_len, read_00474_delim, 1);
      if (read_00474_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00474_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00474_ptr += cgc_data_match(read_00474 + read_00474_ptr, read_00474_len - read_00474_ptr, match_00474_00000, 8);
      cgc_free(read_00474);
      if (read_00474_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00311_00000[] = 
         "\x44\x0a";
      static unsigned int write_00311_00000_len = 2;
      unsigned char *write_00311 = NULL;
      unsigned int write_00311_len = 0;
      write_00311 = cgc_append_buf(write_00311, &write_00311_len, write_00311_00000, write_00311_00000_len);
      if (write_00311_len > 0) {
         cgc_transmit_all(1, write_00311, write_00311_len);
      }
      cgc_free(write_00311);
   } while (0);
   do {
      unsigned char *read_00475;
      unsigned int read_00475_len;
      unsigned int read_00475_ptr = 0;
      //**** delimited read
      static unsigned char read_00475_delim[] = 
         "\x0a";
      read_00475 = NULL;
      read_00475_len = 0;
      int read_00475_res = cgc_delimited_read(0, &read_00475, &read_00475_len, read_00475_delim, 1);
      if (read_00475_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00475_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00475_ptr += cgc_data_match(read_00475 + read_00475_ptr, read_00475_len - read_00475_ptr, match_00475_00000, 47);
      cgc_free(read_00475);
      if (read_00475_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00476;
      unsigned int read_00476_len;
      unsigned int read_00476_ptr = 0;
      //**** delimited read
      static unsigned char read_00476_delim[] = 
         "\x0a";
      read_00476 = NULL;
      read_00476_len = 0;
      int read_00476_res = cgc_delimited_read(0, &read_00476, &read_00476_len, read_00476_delim, 1);
      if (read_00476_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00476_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00476_ptr += cgc_data_match(read_00476 + read_00476_ptr, read_00476_len - read_00476_ptr, match_00476_00000, 8);
      cgc_free(read_00476);
      if (read_00476_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00312_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00312_00000_len = 2;
      unsigned char *write_00312 = NULL;
      unsigned int write_00312_len = 0;
      write_00312 = cgc_append_buf(write_00312, &write_00312_len, write_00312_00000, write_00312_00000_len);
      if (write_00312_len > 0) {
         cgc_transmit_all(1, write_00312, write_00312_len);
      }
      cgc_free(write_00312);
   } while (0);
   do {
      unsigned char *read_00477;
      unsigned int read_00477_len;
      unsigned int read_00477_ptr = 0;
      //**** delimited read
      static unsigned char read_00477_delim[] = 
         "\x0a";
      read_00477 = NULL;
      read_00477_len = 0;
      int read_00477_res = cgc_delimited_read(0, &read_00477, &read_00477_len, read_00477_delim, 1);
      if (read_00477_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00477_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00477_ptr += cgc_data_match(read_00477 + read_00477_ptr, read_00477_len - read_00477_ptr, match_00477_00000, 6);
      cgc_free(read_00477);
      if (read_00477_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00313_00000[] = 
         "\x32\x30\x0a";
      static unsigned int write_00313_00000_len = 3;
      unsigned char *write_00313 = NULL;
      unsigned int write_00313_len = 0;
      write_00313 = cgc_append_buf(write_00313, &write_00313_len, write_00313_00000, write_00313_00000_len);
      if (write_00313_len > 0) {
         cgc_transmit_all(1, write_00313, write_00313_len);
      }
      cgc_free(write_00313);
   } while (0);
   do {
      unsigned char *read_00478;
      unsigned int read_00478_len;
      unsigned int read_00478_ptr = 0;
      //**** delimited read
      static unsigned char read_00478_delim[] = 
         "\x0a";
      read_00478 = NULL;
      read_00478_len = 0;
      int read_00478_res = cgc_delimited_read(0, &read_00478, &read_00478_len, read_00478_delim, 1);
      if (read_00478_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00478_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00478_ptr += cgc_data_match(read_00478 + read_00478_ptr, read_00478_len - read_00478_ptr, match_00478_00000, 47);
      cgc_free(read_00478);
      if (read_00478_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00479;
      unsigned int read_00479_len;
      unsigned int read_00479_ptr = 0;
      //**** delimited read
      static unsigned char read_00479_delim[] = 
         "\x0a";
      read_00479 = NULL;
      read_00479_len = 0;
      int read_00479_res = cgc_delimited_read(0, &read_00479, &read_00479_len, read_00479_delim, 1);
      if (read_00479_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00479_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00479_ptr += cgc_data_match(read_00479 + read_00479_ptr, read_00479_len - read_00479_ptr, match_00479_00000, 8);
      cgc_free(read_00479);
      if (read_00479_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00314_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00314_00000_len = 2;
      unsigned char *write_00314 = NULL;
      unsigned int write_00314_len = 0;
      write_00314 = cgc_append_buf(write_00314, &write_00314_len, write_00314_00000, write_00314_00000_len);
      if (write_00314_len > 0) {
         cgc_transmit_all(1, write_00314, write_00314_len);
      }
      cgc_free(write_00314);
   } while (0);
   do {
      unsigned char *read_00480;
      unsigned int read_00480_len;
      unsigned int read_00480_ptr = 0;
      //**** delimited read
      static unsigned char read_00480_delim[] = 
         "\x0a";
      read_00480 = NULL;
      read_00480_len = 0;
      int read_00480_res = cgc_delimited_read(0, &read_00480, &read_00480_len, read_00480_delim, 1);
      if (read_00480_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00480_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00480_ptr += cgc_data_match(read_00480 + read_00480_ptr, read_00480_len - read_00480_ptr, match_00480_00000, 6);
      cgc_free(read_00480);
      if (read_00480_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00315_00000[] = 
         "\x32\x31\x0a";
      static unsigned int write_00315_00000_len = 3;
      unsigned char *write_00315 = NULL;
      unsigned int write_00315_len = 0;
      write_00315 = cgc_append_buf(write_00315, &write_00315_len, write_00315_00000, write_00315_00000_len);
      if (write_00315_len > 0) {
         cgc_transmit_all(1, write_00315, write_00315_len);
      }
      cgc_free(write_00315);
   } while (0);
   do {
      unsigned char *read_00481;
      unsigned int read_00481_len;
      unsigned int read_00481_ptr = 0;
      //**** delimited read
      static unsigned char read_00481_delim[] = 
         "\x0a";
      read_00481 = NULL;
      read_00481_len = 0;
      int read_00481_res = cgc_delimited_read(0, &read_00481, &read_00481_len, read_00481_delim, 1);
      if (read_00481_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00481_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00481_ptr += cgc_data_match(read_00481 + read_00481_ptr, read_00481_len - read_00481_ptr, match_00481_00000, 29);
      cgc_free(read_00481);
      if (read_00481_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00482;
      unsigned int read_00482_len;
      unsigned int read_00482_ptr = 0;
      //**** delimited read
      static unsigned char read_00482_delim[] = 
         "\x0a";
      read_00482 = NULL;
      read_00482_len = 0;
      int read_00482_res = cgc_delimited_read(0, &read_00482, &read_00482_len, read_00482_delim, 1);
      if (read_00482_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00482_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00482_ptr += cgc_data_match(read_00482 + read_00482_ptr, read_00482_len - read_00482_ptr, match_00482_00000, 65);
      cgc_free(read_00482);
      if (read_00482_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00483;
      unsigned int read_00483_len;
      unsigned int read_00483_ptr = 0;
      //**** delimited read
      static unsigned char read_00483_delim[] = 
         "\x0a";
      read_00483 = NULL;
      read_00483_len = 0;
      int read_00483_res = cgc_delimited_read(0, &read_00483, &read_00483_len, read_00483_delim, 1);
      if (read_00483_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00483_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00483_ptr += cgc_data_match(read_00483 + read_00483_ptr, read_00483_len - read_00483_ptr, match_00483_00000, 7);
      cgc_free(read_00483);
      if (read_00483_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00316_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00316_00000_len = 2;
      unsigned char *write_00316 = NULL;
      unsigned int write_00316_len = 0;
      write_00316 = cgc_append_buf(write_00316, &write_00316_len, write_00316_00000, write_00316_00000_len);
      if (write_00316_len > 0) {
         cgc_transmit_all(1, write_00316, write_00316_len);
      }
      cgc_free(write_00316);
   } while (0);
   do {
      unsigned char *read_00484;
      unsigned int read_00484_len;
      unsigned int read_00484_ptr = 0;
      //**** delimited read
      static unsigned char read_00484_delim[] = 
         "\x0a";
      read_00484 = NULL;
      read_00484_len = 0;
      int read_00484_res = cgc_delimited_read(0, &read_00484, &read_00484_len, read_00484_delim, 1);
      if (read_00484_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00484_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00484_ptr += cgc_data_match(read_00484 + read_00484_ptr, read_00484_len - read_00484_ptr, match_00484_00000, 17);
      cgc_free(read_00484);
      if (read_00484_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00317_00000[] = 
         "\x31\x0a";
      static unsigned int write_00317_00000_len = 2;
      unsigned char *write_00317 = NULL;
      unsigned int write_00317_len = 0;
      write_00317 = cgc_append_buf(write_00317, &write_00317_len, write_00317_00000, write_00317_00000_len);
      if (write_00317_len > 0) {
         cgc_transmit_all(1, write_00317, write_00317_len);
      }
      cgc_free(write_00317);
   } while (0);
   do {
      unsigned char *read_00485;
      unsigned int read_00485_len;
      unsigned int read_00485_ptr = 0;
      //**** delimited read
      static unsigned char read_00485_delim[] = 
         "\x0a";
      read_00485 = NULL;
      read_00485_len = 0;
      int read_00485_res = cgc_delimited_read(0, &read_00485, &read_00485_len, read_00485_delim, 1);
      if (read_00485_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00485_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00485_ptr += cgc_data_match(read_00485 + read_00485_ptr, read_00485_len - read_00485_ptr, match_00485_00000, 29);
      cgc_free(read_00485);
      if (read_00485_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00486;
      unsigned int read_00486_len;
      unsigned int read_00486_ptr = 0;
      //**** delimited read
      static unsigned char read_00486_delim[] = 
         "\x0a";
      read_00486 = NULL;
      read_00486_len = 0;
      int read_00486_res = cgc_delimited_read(0, &read_00486, &read_00486_len, read_00486_delim, 1);
      if (read_00486_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00486_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00486_ptr += cgc_data_match(read_00486 + read_00486_ptr, read_00486_len - read_00486_ptr, match_00486_00000, 65);
      cgc_free(read_00486);
      if (read_00486_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00487;
      unsigned int read_00487_len;
      unsigned int read_00487_ptr = 0;
      //**** delimited read
      static unsigned char read_00487_delim[] = 
         "\x0a";
      read_00487 = NULL;
      read_00487_len = 0;
      int read_00487_res = cgc_delimited_read(0, &read_00487, &read_00487_len, read_00487_delim, 1);
      if (read_00487_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00487_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00487_ptr += cgc_data_match(read_00487 + read_00487_ptr, read_00487_len - read_00487_ptr, match_00487_00000, 7);
      cgc_free(read_00487);
      if (read_00487_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00318_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00318_00000_len = 2;
      unsigned char *write_00318 = NULL;
      unsigned int write_00318_len = 0;
      write_00318 = cgc_append_buf(write_00318, &write_00318_len, write_00318_00000, write_00318_00000_len);
      if (write_00318_len > 0) {
         cgc_transmit_all(1, write_00318, write_00318_len);
      }
      cgc_free(write_00318);
   } while (0);
   do {
      unsigned char *read_00488;
      unsigned int read_00488_len;
      unsigned int read_00488_ptr = 0;
      //**** delimited read
      static unsigned char read_00488_delim[] = 
         "\x0a";
      read_00488 = NULL;
      read_00488_len = 0;
      int read_00488_res = cgc_delimited_read(0, &read_00488, &read_00488_len, read_00488_delim, 1);
      if (read_00488_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00488_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00488_ptr += cgc_data_match(read_00488 + read_00488_ptr, read_00488_len - read_00488_ptr, match_00488_00000, 17);
      cgc_free(read_00488);
      if (read_00488_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00319_00000[] = 
         "\x31\x0a";
      static unsigned int write_00319_00000_len = 2;
      unsigned char *write_00319 = NULL;
      unsigned int write_00319_len = 0;
      write_00319 = cgc_append_buf(write_00319, &write_00319_len, write_00319_00000, write_00319_00000_len);
      if (write_00319_len > 0) {
         cgc_transmit_all(1, write_00319, write_00319_len);
      }
      cgc_free(write_00319);
   } while (0);
   do {
      unsigned char *read_00489;
      unsigned int read_00489_len;
      unsigned int read_00489_ptr = 0;
      //**** delimited read
      static unsigned char read_00489_delim[] = 
         "\x0a";
      read_00489 = NULL;
      read_00489_len = 0;
      int read_00489_res = cgc_delimited_read(0, &read_00489, &read_00489_len, read_00489_delim, 1);
      if (read_00489_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00489_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00489_ptr += cgc_data_match(read_00489 + read_00489_ptr, read_00489_len - read_00489_ptr, match_00489_00000, 8);
      cgc_free(read_00489);
      if (read_00489_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00320_00000[] = 
         "\x44\x0a";
      static unsigned int write_00320_00000_len = 2;
      unsigned char *write_00320 = NULL;
      unsigned int write_00320_len = 0;
      write_00320 = cgc_append_buf(write_00320, &write_00320_len, write_00320_00000, write_00320_00000_len);
      if (write_00320_len > 0) {
         cgc_transmit_all(1, write_00320, write_00320_len);
      }
      cgc_free(write_00320);
   } while (0);
   do {
      unsigned char *read_00490;
      unsigned int read_00490_len;
      unsigned int read_00490_ptr = 0;
      //**** delimited read
      static unsigned char read_00490_delim[] = 
         "\x0a";
      read_00490 = NULL;
      read_00490_len = 0;
      int read_00490_res = cgc_delimited_read(0, &read_00490, &read_00490_len, read_00490_delim, 1);
      if (read_00490_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00490_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00490_ptr += cgc_data_match(read_00490 + read_00490_ptr, read_00490_len - read_00490_ptr, match_00490_00000, 47);
      cgc_free(read_00490);
      if (read_00490_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00491;
      unsigned int read_00491_len;
      unsigned int read_00491_ptr = 0;
      //**** delimited read
      static unsigned char read_00491_delim[] = 
         "\x0a";
      read_00491 = NULL;
      read_00491_len = 0;
      int read_00491_res = cgc_delimited_read(0, &read_00491, &read_00491_len, read_00491_delim, 1);
      if (read_00491_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00491_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00491_ptr += cgc_data_match(read_00491 + read_00491_ptr, read_00491_len - read_00491_ptr, match_00491_00000, 8);
      cgc_free(read_00491);
      if (read_00491_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00321_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00321_00000_len = 2;
      unsigned char *write_00321 = NULL;
      unsigned int write_00321_len = 0;
      write_00321 = cgc_append_buf(write_00321, &write_00321_len, write_00321_00000, write_00321_00000_len);
      if (write_00321_len > 0) {
         cgc_transmit_all(1, write_00321, write_00321_len);
      }
      cgc_free(write_00321);
   } while (0);
   do {
      unsigned char *read_00492;
      unsigned int read_00492_len;
      unsigned int read_00492_ptr = 0;
      //**** delimited read
      static unsigned char read_00492_delim[] = 
         "\x0a";
      read_00492 = NULL;
      read_00492_len = 0;
      int read_00492_res = cgc_delimited_read(0, &read_00492, &read_00492_len, read_00492_delim, 1);
      if (read_00492_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00492_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00492_ptr += cgc_data_match(read_00492 + read_00492_ptr, read_00492_len - read_00492_ptr, match_00492_00000, 6);
      cgc_free(read_00492);
      if (read_00492_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00322_00000[] = 
         "\x32\x32\x0a";
      static unsigned int write_00322_00000_len = 3;
      unsigned char *write_00322 = NULL;
      unsigned int write_00322_len = 0;
      write_00322 = cgc_append_buf(write_00322, &write_00322_len, write_00322_00000, write_00322_00000_len);
      if (write_00322_len > 0) {
         cgc_transmit_all(1, write_00322, write_00322_len);
      }
      cgc_free(write_00322);
   } while (0);
   do {
      unsigned char *read_00493;
      unsigned int read_00493_len;
      unsigned int read_00493_ptr = 0;
      //**** delimited read
      static unsigned char read_00493_delim[] = 
         "\x0a";
      read_00493 = NULL;
      read_00493_len = 0;
      int read_00493_res = cgc_delimited_read(0, &read_00493, &read_00493_len, read_00493_delim, 1);
      if (read_00493_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00493_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00493_ptr += cgc_data_match(read_00493 + read_00493_ptr, read_00493_len - read_00493_ptr, match_00493_00000, 47);
      cgc_free(read_00493);
      if (read_00493_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00494;
      unsigned int read_00494_len;
      unsigned int read_00494_ptr = 0;
      //**** delimited read
      static unsigned char read_00494_delim[] = 
         "\x0a";
      read_00494 = NULL;
      read_00494_len = 0;
      int read_00494_res = cgc_delimited_read(0, &read_00494, &read_00494_len, read_00494_delim, 1);
      if (read_00494_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00494_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00494_ptr += cgc_data_match(read_00494 + read_00494_ptr, read_00494_len - read_00494_ptr, match_00494_00000, 8);
      cgc_free(read_00494);
      if (read_00494_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00323_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00323_00000_len = 2;
      unsigned char *write_00323 = NULL;
      unsigned int write_00323_len = 0;
      write_00323 = cgc_append_buf(write_00323, &write_00323_len, write_00323_00000, write_00323_00000_len);
      if (write_00323_len > 0) {
         cgc_transmit_all(1, write_00323, write_00323_len);
      }
      cgc_free(write_00323);
   } while (0);
   do {
      unsigned char *read_00495;
      unsigned int read_00495_len;
      unsigned int read_00495_ptr = 0;
      //**** delimited read
      static unsigned char read_00495_delim[] = 
         "\x0a";
      read_00495 = NULL;
      read_00495_len = 0;
      int read_00495_res = cgc_delimited_read(0, &read_00495, &read_00495_len, read_00495_delim, 1);
      if (read_00495_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00495_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00495_ptr += cgc_data_match(read_00495 + read_00495_ptr, read_00495_len - read_00495_ptr, match_00495_00000, 6);
      cgc_free(read_00495);
      if (read_00495_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00324_00000[] = 
         "\x32\x33\x0a";
      static unsigned int write_00324_00000_len = 3;
      unsigned char *write_00324 = NULL;
      unsigned int write_00324_len = 0;
      write_00324 = cgc_append_buf(write_00324, &write_00324_len, write_00324_00000, write_00324_00000_len);
      if (write_00324_len > 0) {
         cgc_transmit_all(1, write_00324, write_00324_len);
      }
      cgc_free(write_00324);
   } while (0);
   do {
      unsigned char *read_00496;
      unsigned int read_00496_len;
      unsigned int read_00496_ptr = 0;
      //**** delimited read
      static unsigned char read_00496_delim[] = 
         "\x0a";
      read_00496 = NULL;
      read_00496_len = 0;
      int read_00496_res = cgc_delimited_read(0, &read_00496, &read_00496_len, read_00496_delim, 1);
      if (read_00496_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00496_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00496_ptr += cgc_data_match(read_00496 + read_00496_ptr, read_00496_len - read_00496_ptr, match_00496_00000, 29);
      cgc_free(read_00496);
      if (read_00496_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00497;
      unsigned int read_00497_len;
      unsigned int read_00497_ptr = 0;
      //**** delimited read
      static unsigned char read_00497_delim[] = 
         "\x0a";
      read_00497 = NULL;
      read_00497_len = 0;
      int read_00497_res = cgc_delimited_read(0, &read_00497, &read_00497_len, read_00497_delim, 1);
      if (read_00497_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00497_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00497_ptr += cgc_data_match(read_00497 + read_00497_ptr, read_00497_len - read_00497_ptr, match_00497_00000, 65);
      cgc_free(read_00497);
      if (read_00497_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00498;
      unsigned int read_00498_len;
      unsigned int read_00498_ptr = 0;
      //**** delimited read
      static unsigned char read_00498_delim[] = 
         "\x0a";
      read_00498 = NULL;
      read_00498_len = 0;
      int read_00498_res = cgc_delimited_read(0, &read_00498, &read_00498_len, read_00498_delim, 1);
      if (read_00498_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00498_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00498_ptr += cgc_data_match(read_00498 + read_00498_ptr, read_00498_len - read_00498_ptr, match_00498_00000, 7);
      cgc_free(read_00498);
      if (read_00498_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00325_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00325_00000_len = 2;
      unsigned char *write_00325 = NULL;
      unsigned int write_00325_len = 0;
      write_00325 = cgc_append_buf(write_00325, &write_00325_len, write_00325_00000, write_00325_00000_len);
      if (write_00325_len > 0) {
         cgc_transmit_all(1, write_00325, write_00325_len);
      }
      cgc_free(write_00325);
   } while (0);
   do {
      unsigned char *read_00499;
      unsigned int read_00499_len;
      unsigned int read_00499_ptr = 0;
      //**** delimited read
      static unsigned char read_00499_delim[] = 
         "\x0a";
      read_00499 = NULL;
      read_00499_len = 0;
      int read_00499_res = cgc_delimited_read(0, &read_00499, &read_00499_len, read_00499_delim, 1);
      if (read_00499_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00499_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00499_ptr += cgc_data_match(read_00499 + read_00499_ptr, read_00499_len - read_00499_ptr, match_00499_00000, 17);
      cgc_free(read_00499);
      if (read_00499_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00326_00000[] = 
         "\x31\x0a";
      static unsigned int write_00326_00000_len = 2;
      unsigned char *write_00326 = NULL;
      unsigned int write_00326_len = 0;
      write_00326 = cgc_append_buf(write_00326, &write_00326_len, write_00326_00000, write_00326_00000_len);
      if (write_00326_len > 0) {
         cgc_transmit_all(1, write_00326, write_00326_len);
      }
      cgc_free(write_00326);
   } while (0);
   do {
      unsigned char *read_00500;
      unsigned int read_00500_len;
      unsigned int read_00500_ptr = 0;
      //**** delimited read
      static unsigned char read_00500_delim[] = 
         "\x0a";
      read_00500 = NULL;
      read_00500_len = 0;
      int read_00500_res = cgc_delimited_read(0, &read_00500, &read_00500_len, read_00500_delim, 1);
      if (read_00500_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00500_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00500_ptr += cgc_data_match(read_00500 + read_00500_ptr, read_00500_len - read_00500_ptr, match_00500_00000, 29);
      cgc_free(read_00500);
      if (read_00500_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00501;
      unsigned int read_00501_len;
      unsigned int read_00501_ptr = 0;
      //**** delimited read
      static unsigned char read_00501_delim[] = 
         "\x0a";
      read_00501 = NULL;
      read_00501_len = 0;
      int read_00501_res = cgc_delimited_read(0, &read_00501, &read_00501_len, read_00501_delim, 1);
      if (read_00501_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00501_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00501_ptr += cgc_data_match(read_00501 + read_00501_ptr, read_00501_len - read_00501_ptr, match_00501_00000, 65);
      cgc_free(read_00501);
      if (read_00501_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00502;
      unsigned int read_00502_len;
      unsigned int read_00502_ptr = 0;
      //**** delimited read
      static unsigned char read_00502_delim[] = 
         "\x0a";
      read_00502 = NULL;
      read_00502_len = 0;
      int read_00502_res = cgc_delimited_read(0, &read_00502, &read_00502_len, read_00502_delim, 1);
      if (read_00502_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00502_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00502_ptr += cgc_data_match(read_00502 + read_00502_ptr, read_00502_len - read_00502_ptr, match_00502_00000, 7);
      cgc_free(read_00502);
      if (read_00502_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00327_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00327_00000_len = 2;
      unsigned char *write_00327 = NULL;
      unsigned int write_00327_len = 0;
      write_00327 = cgc_append_buf(write_00327, &write_00327_len, write_00327_00000, write_00327_00000_len);
      if (write_00327_len > 0) {
         cgc_transmit_all(1, write_00327, write_00327_len);
      }
      cgc_free(write_00327);
   } while (0);
   do {
      unsigned char *read_00503;
      unsigned int read_00503_len;
      unsigned int read_00503_ptr = 0;
      //**** delimited read
      static unsigned char read_00503_delim[] = 
         "\x0a";
      read_00503 = NULL;
      read_00503_len = 0;
      int read_00503_res = cgc_delimited_read(0, &read_00503, &read_00503_len, read_00503_delim, 1);
      if (read_00503_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00503_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00503_ptr += cgc_data_match(read_00503 + read_00503_ptr, read_00503_len - read_00503_ptr, match_00503_00000, 17);
      cgc_free(read_00503);
      if (read_00503_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00328_00000[] = 
         "\x31\x0a";
      static unsigned int write_00328_00000_len = 2;
      unsigned char *write_00328 = NULL;
      unsigned int write_00328_len = 0;
      write_00328 = cgc_append_buf(write_00328, &write_00328_len, write_00328_00000, write_00328_00000_len);
      if (write_00328_len > 0) {
         cgc_transmit_all(1, write_00328, write_00328_len);
      }
      cgc_free(write_00328);
   } while (0);
   do {
      unsigned char *read_00504;
      unsigned int read_00504_len;
      unsigned int read_00504_ptr = 0;
      //**** delimited read
      static unsigned char read_00504_delim[] = 
         "\x0a";
      read_00504 = NULL;
      read_00504_len = 0;
      int read_00504_res = cgc_delimited_read(0, &read_00504, &read_00504_len, read_00504_delim, 1);
      if (read_00504_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00504_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00504_ptr += cgc_data_match(read_00504 + read_00504_ptr, read_00504_len - read_00504_ptr, match_00504_00000, 8);
      cgc_free(read_00504);
      if (read_00504_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00329_00000[] = 
         "\x44\x0a";
      static unsigned int write_00329_00000_len = 2;
      unsigned char *write_00329 = NULL;
      unsigned int write_00329_len = 0;
      write_00329 = cgc_append_buf(write_00329, &write_00329_len, write_00329_00000, write_00329_00000_len);
      if (write_00329_len > 0) {
         cgc_transmit_all(1, write_00329, write_00329_len);
      }
      cgc_free(write_00329);
   } while (0);
   do {
      unsigned char *read_00505;
      unsigned int read_00505_len;
      unsigned int read_00505_ptr = 0;
      //**** delimited read
      static unsigned char read_00505_delim[] = 
         "\x0a";
      read_00505 = NULL;
      read_00505_len = 0;
      int read_00505_res = cgc_delimited_read(0, &read_00505, &read_00505_len, read_00505_delim, 1);
      if (read_00505_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00505_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00505_ptr += cgc_data_match(read_00505 + read_00505_ptr, read_00505_len - read_00505_ptr, match_00505_00000, 47);
      cgc_free(read_00505);
      if (read_00505_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00506;
      unsigned int read_00506_len;
      unsigned int read_00506_ptr = 0;
      //**** delimited read
      static unsigned char read_00506_delim[] = 
         "\x0a";
      read_00506 = NULL;
      read_00506_len = 0;
      int read_00506_res = cgc_delimited_read(0, &read_00506, &read_00506_len, read_00506_delim, 1);
      if (read_00506_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00506_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00506_ptr += cgc_data_match(read_00506 + read_00506_ptr, read_00506_len - read_00506_ptr, match_00506_00000, 8);
      cgc_free(read_00506);
      if (read_00506_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00330_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00330_00000_len = 2;
      unsigned char *write_00330 = NULL;
      unsigned int write_00330_len = 0;
      write_00330 = cgc_append_buf(write_00330, &write_00330_len, write_00330_00000, write_00330_00000_len);
      if (write_00330_len > 0) {
         cgc_transmit_all(1, write_00330, write_00330_len);
      }
      cgc_free(write_00330);
   } while (0);
   do {
      unsigned char *read_00507;
      unsigned int read_00507_len;
      unsigned int read_00507_ptr = 0;
      //**** delimited read
      static unsigned char read_00507_delim[] = 
         "\x0a";
      read_00507 = NULL;
      read_00507_len = 0;
      int read_00507_res = cgc_delimited_read(0, &read_00507, &read_00507_len, read_00507_delim, 1);
      if (read_00507_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00507_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00507_ptr += cgc_data_match(read_00507 + read_00507_ptr, read_00507_len - read_00507_ptr, match_00507_00000, 6);
      cgc_free(read_00507);
      if (read_00507_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00331_00000[] = 
         "\x32\x34\x0a";
      static unsigned int write_00331_00000_len = 3;
      unsigned char *write_00331 = NULL;
      unsigned int write_00331_len = 0;
      write_00331 = cgc_append_buf(write_00331, &write_00331_len, write_00331_00000, write_00331_00000_len);
      if (write_00331_len > 0) {
         cgc_transmit_all(1, write_00331, write_00331_len);
      }
      cgc_free(write_00331);
   } while (0);
   do {
      unsigned char *read_00508;
      unsigned int read_00508_len;
      unsigned int read_00508_ptr = 0;
      //**** delimited read
      static unsigned char read_00508_delim[] = 
         "\x0a";
      read_00508 = NULL;
      read_00508_len = 0;
      int read_00508_res = cgc_delimited_read(0, &read_00508, &read_00508_len, read_00508_delim, 1);
      if (read_00508_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00508_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00508_ptr += cgc_data_match(read_00508 + read_00508_ptr, read_00508_len - read_00508_ptr, match_00508_00000, 47);
      cgc_free(read_00508);
      if (read_00508_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00509;
      unsigned int read_00509_len;
      unsigned int read_00509_ptr = 0;
      //**** delimited read
      static unsigned char read_00509_delim[] = 
         "\x0a";
      read_00509 = NULL;
      read_00509_len = 0;
      int read_00509_res = cgc_delimited_read(0, &read_00509, &read_00509_len, read_00509_delim, 1);
      if (read_00509_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00509_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00509_ptr += cgc_data_match(read_00509 + read_00509_ptr, read_00509_len - read_00509_ptr, match_00509_00000, 8);
      cgc_free(read_00509);
      if (read_00509_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00332_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00332_00000_len = 2;
      unsigned char *write_00332 = NULL;
      unsigned int write_00332_len = 0;
      write_00332 = cgc_append_buf(write_00332, &write_00332_len, write_00332_00000, write_00332_00000_len);
      if (write_00332_len > 0) {
         cgc_transmit_all(1, write_00332, write_00332_len);
      }
      cgc_free(write_00332);
   } while (0);
   do {
      unsigned char *read_00510;
      unsigned int read_00510_len;
      unsigned int read_00510_ptr = 0;
      //**** delimited read
      static unsigned char read_00510_delim[] = 
         "\x0a";
      read_00510 = NULL;
      read_00510_len = 0;
      int read_00510_res = cgc_delimited_read(0, &read_00510, &read_00510_len, read_00510_delim, 1);
      if (read_00510_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00510_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00510_ptr += cgc_data_match(read_00510 + read_00510_ptr, read_00510_len - read_00510_ptr, match_00510_00000, 6);
      cgc_free(read_00510);
      if (read_00510_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00333_00000[] = 
         "\x32\x35\x0a";
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
      unsigned char *read_00511;
      unsigned int read_00511_len;
      unsigned int read_00511_ptr = 0;
      //**** delimited read
      static unsigned char read_00511_delim[] = 
         "\x0a";
      read_00511 = NULL;
      read_00511_len = 0;
      int read_00511_res = cgc_delimited_read(0, &read_00511, &read_00511_len, read_00511_delim, 1);
      if (read_00511_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00511_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00511_ptr += cgc_data_match(read_00511 + read_00511_ptr, read_00511_len - read_00511_ptr, match_00511_00000, 29);
      cgc_free(read_00511);
      if (read_00511_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00512;
      unsigned int read_00512_len;
      unsigned int read_00512_ptr = 0;
      //**** delimited read
      static unsigned char read_00512_delim[] = 
         "\x0a";
      read_00512 = NULL;
      read_00512_len = 0;
      int read_00512_res = cgc_delimited_read(0, &read_00512, &read_00512_len, read_00512_delim, 1);
      if (read_00512_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00512_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00512_ptr += cgc_data_match(read_00512 + read_00512_ptr, read_00512_len - read_00512_ptr, match_00512_00000, 65);
      cgc_free(read_00512);
      if (read_00512_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00513;
      unsigned int read_00513_len;
      unsigned int read_00513_ptr = 0;
      //**** delimited read
      static unsigned char read_00513_delim[] = 
         "\x0a";
      read_00513 = NULL;
      read_00513_len = 0;
      int read_00513_res = cgc_delimited_read(0, &read_00513, &read_00513_len, read_00513_delim, 1);
      if (read_00513_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00513_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00513_ptr += cgc_data_match(read_00513 + read_00513_ptr, read_00513_len - read_00513_ptr, match_00513_00000, 7);
      cgc_free(read_00513);
      if (read_00513_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00334_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00334_00000_len = 2;
      unsigned char *write_00334 = NULL;
      unsigned int write_00334_len = 0;
      write_00334 = cgc_append_buf(write_00334, &write_00334_len, write_00334_00000, write_00334_00000_len);
      if (write_00334_len > 0) {
         cgc_transmit_all(1, write_00334, write_00334_len);
      }
      cgc_free(write_00334);
   } while (0);
   do {
      unsigned char *read_00514;
      unsigned int read_00514_len;
      unsigned int read_00514_ptr = 0;
      //**** delimited read
      static unsigned char read_00514_delim[] = 
         "\x0a";
      read_00514 = NULL;
      read_00514_len = 0;
      int read_00514_res = cgc_delimited_read(0, &read_00514, &read_00514_len, read_00514_delim, 1);
      if (read_00514_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00514_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00514_ptr += cgc_data_match(read_00514 + read_00514_ptr, read_00514_len - read_00514_ptr, match_00514_00000, 17);
      cgc_free(read_00514);
      if (read_00514_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00335_00000[] = 
         "\x31\x0a";
      static unsigned int write_00335_00000_len = 2;
      unsigned char *write_00335 = NULL;
      unsigned int write_00335_len = 0;
      write_00335 = cgc_append_buf(write_00335, &write_00335_len, write_00335_00000, write_00335_00000_len);
      if (write_00335_len > 0) {
         cgc_transmit_all(1, write_00335, write_00335_len);
      }
      cgc_free(write_00335);
   } while (0);
   do {
      unsigned char *read_00515;
      unsigned int read_00515_len;
      unsigned int read_00515_ptr = 0;
      //**** delimited read
      static unsigned char read_00515_delim[] = 
         "\x0a";
      read_00515 = NULL;
      read_00515_len = 0;
      int read_00515_res = cgc_delimited_read(0, &read_00515, &read_00515_len, read_00515_delim, 1);
      if (read_00515_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00515_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00515_ptr += cgc_data_match(read_00515 + read_00515_ptr, read_00515_len - read_00515_ptr, match_00515_00000, 29);
      cgc_free(read_00515);
      if (read_00515_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00516;
      unsigned int read_00516_len;
      unsigned int read_00516_ptr = 0;
      //**** delimited read
      static unsigned char read_00516_delim[] = 
         "\x0a";
      read_00516 = NULL;
      read_00516_len = 0;
      int read_00516_res = cgc_delimited_read(0, &read_00516, &read_00516_len, read_00516_delim, 1);
      if (read_00516_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00516_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00516_ptr += cgc_data_match(read_00516 + read_00516_ptr, read_00516_len - read_00516_ptr, match_00516_00000, 65);
      cgc_free(read_00516);
      if (read_00516_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00517;
      unsigned int read_00517_len;
      unsigned int read_00517_ptr = 0;
      //**** delimited read
      static unsigned char read_00517_delim[] = 
         "\x0a";
      read_00517 = NULL;
      read_00517_len = 0;
      int read_00517_res = cgc_delimited_read(0, &read_00517, &read_00517_len, read_00517_delim, 1);
      if (read_00517_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00517_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00517_ptr += cgc_data_match(read_00517 + read_00517_ptr, read_00517_len - read_00517_ptr, match_00517_00000, 7);
      cgc_free(read_00517);
      if (read_00517_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00336_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00336_00000_len = 2;
      unsigned char *write_00336 = NULL;
      unsigned int write_00336_len = 0;
      write_00336 = cgc_append_buf(write_00336, &write_00336_len, write_00336_00000, write_00336_00000_len);
      if (write_00336_len > 0) {
         cgc_transmit_all(1, write_00336, write_00336_len);
      }
      cgc_free(write_00336);
   } while (0);
   do {
      unsigned char *read_00518;
      unsigned int read_00518_len;
      unsigned int read_00518_ptr = 0;
      //**** delimited read
      static unsigned char read_00518_delim[] = 
         "\x0a";
      read_00518 = NULL;
      read_00518_len = 0;
      int read_00518_res = cgc_delimited_read(0, &read_00518, &read_00518_len, read_00518_delim, 1);
      if (read_00518_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00518_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00518_ptr += cgc_data_match(read_00518 + read_00518_ptr, read_00518_len - read_00518_ptr, match_00518_00000, 17);
      cgc_free(read_00518);
      if (read_00518_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00337_00000[] = 
         "\x31\x0a";
      static unsigned int write_00337_00000_len = 2;
      unsigned char *write_00337 = NULL;
      unsigned int write_00337_len = 0;
      write_00337 = cgc_append_buf(write_00337, &write_00337_len, write_00337_00000, write_00337_00000_len);
      if (write_00337_len > 0) {
         cgc_transmit_all(1, write_00337, write_00337_len);
      }
      cgc_free(write_00337);
   } while (0);
   do {
      unsigned char *read_00519;
      unsigned int read_00519_len;
      unsigned int read_00519_ptr = 0;
      //**** delimited read
      static unsigned char read_00519_delim[] = 
         "\x0a";
      read_00519 = NULL;
      read_00519_len = 0;
      int read_00519_res = cgc_delimited_read(0, &read_00519, &read_00519_len, read_00519_delim, 1);
      if (read_00519_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00519_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00519_ptr += cgc_data_match(read_00519 + read_00519_ptr, read_00519_len - read_00519_ptr, match_00519_00000, 8);
      cgc_free(read_00519);
      if (read_00519_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00338_00000[] = 
         "\x44\x0a";
      static unsigned int write_00338_00000_len = 2;
      unsigned char *write_00338 = NULL;
      unsigned int write_00338_len = 0;
      write_00338 = cgc_append_buf(write_00338, &write_00338_len, write_00338_00000, write_00338_00000_len);
      if (write_00338_len > 0) {
         cgc_transmit_all(1, write_00338, write_00338_len);
      }
      cgc_free(write_00338);
   } while (0);
   do {
      unsigned char *read_00520;
      unsigned int read_00520_len;
      unsigned int read_00520_ptr = 0;
      //**** delimited read
      static unsigned char read_00520_delim[] = 
         "\x0a";
      read_00520 = NULL;
      read_00520_len = 0;
      int read_00520_res = cgc_delimited_read(0, &read_00520, &read_00520_len, read_00520_delim, 1);
      if (read_00520_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00520_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00520_ptr += cgc_data_match(read_00520 + read_00520_ptr, read_00520_len - read_00520_ptr, match_00520_00000, 47);
      cgc_free(read_00520);
      if (read_00520_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00521;
      unsigned int read_00521_len;
      unsigned int read_00521_ptr = 0;
      //**** delimited read
      static unsigned char read_00521_delim[] = 
         "\x0a";
      read_00521 = NULL;
      read_00521_len = 0;
      int read_00521_res = cgc_delimited_read(0, &read_00521, &read_00521_len, read_00521_delim, 1);
      if (read_00521_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00521_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00521_ptr += cgc_data_match(read_00521 + read_00521_ptr, read_00521_len - read_00521_ptr, match_00521_00000, 8);
      cgc_free(read_00521);
      if (read_00521_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00339_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00339_00000_len = 2;
      unsigned char *write_00339 = NULL;
      unsigned int write_00339_len = 0;
      write_00339 = cgc_append_buf(write_00339, &write_00339_len, write_00339_00000, write_00339_00000_len);
      if (write_00339_len > 0) {
         cgc_transmit_all(1, write_00339, write_00339_len);
      }
      cgc_free(write_00339);
   } while (0);
   do {
      unsigned char *read_00522;
      unsigned int read_00522_len;
      unsigned int read_00522_ptr = 0;
      //**** delimited read
      static unsigned char read_00522_delim[] = 
         "\x0a";
      read_00522 = NULL;
      read_00522_len = 0;
      int read_00522_res = cgc_delimited_read(0, &read_00522, &read_00522_len, read_00522_delim, 1);
      if (read_00522_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00522_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00522_ptr += cgc_data_match(read_00522 + read_00522_ptr, read_00522_len - read_00522_ptr, match_00522_00000, 6);
      cgc_free(read_00522);
      if (read_00522_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00340_00000[] = 
         "\x32\x36\x0a";
      static unsigned int write_00340_00000_len = 3;
      unsigned char *write_00340 = NULL;
      unsigned int write_00340_len = 0;
      write_00340 = cgc_append_buf(write_00340, &write_00340_len, write_00340_00000, write_00340_00000_len);
      if (write_00340_len > 0) {
         cgc_transmit_all(1, write_00340, write_00340_len);
      }
      cgc_free(write_00340);
   } while (0);
   do {
      unsigned char *read_00523;
      unsigned int read_00523_len;
      unsigned int read_00523_ptr = 0;
      //**** delimited read
      static unsigned char read_00523_delim[] = 
         "\x0a";
      read_00523 = NULL;
      read_00523_len = 0;
      int read_00523_res = cgc_delimited_read(0, &read_00523, &read_00523_len, read_00523_delim, 1);
      if (read_00523_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00523_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00523_ptr += cgc_data_match(read_00523 + read_00523_ptr, read_00523_len - read_00523_ptr, match_00523_00000, 47);
      cgc_free(read_00523);
      if (read_00523_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00524;
      unsigned int read_00524_len;
      unsigned int read_00524_ptr = 0;
      //**** delimited read
      static unsigned char read_00524_delim[] = 
         "\x0a";
      read_00524 = NULL;
      read_00524_len = 0;
      int read_00524_res = cgc_delimited_read(0, &read_00524, &read_00524_len, read_00524_delim, 1);
      if (read_00524_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00524_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00524_ptr += cgc_data_match(read_00524 + read_00524_ptr, read_00524_len - read_00524_ptr, match_00524_00000, 8);
      cgc_free(read_00524);
      if (read_00524_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00341_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00341_00000_len = 2;
      unsigned char *write_00341 = NULL;
      unsigned int write_00341_len = 0;
      write_00341 = cgc_append_buf(write_00341, &write_00341_len, write_00341_00000, write_00341_00000_len);
      if (write_00341_len > 0) {
         cgc_transmit_all(1, write_00341, write_00341_len);
      }
      cgc_free(write_00341);
   } while (0);
   do {
      unsigned char *read_00525;
      unsigned int read_00525_len;
      unsigned int read_00525_ptr = 0;
      //**** delimited read
      static unsigned char read_00525_delim[] = 
         "\x0a";
      read_00525 = NULL;
      read_00525_len = 0;
      int read_00525_res = cgc_delimited_read(0, &read_00525, &read_00525_len, read_00525_delim, 1);
      if (read_00525_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00525_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00525_ptr += cgc_data_match(read_00525 + read_00525_ptr, read_00525_len - read_00525_ptr, match_00525_00000, 6);
      cgc_free(read_00525);
      if (read_00525_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00342_00000[] = 
         "\x32\x37\x0a";
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
      unsigned char *read_00526;
      unsigned int read_00526_len;
      unsigned int read_00526_ptr = 0;
      //**** delimited read
      static unsigned char read_00526_delim[] = 
         "\x0a";
      read_00526 = NULL;
      read_00526_len = 0;
      int read_00526_res = cgc_delimited_read(0, &read_00526, &read_00526_len, read_00526_delim, 1);
      if (read_00526_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00526_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00526_ptr += cgc_data_match(read_00526 + read_00526_ptr, read_00526_len - read_00526_ptr, match_00526_00000, 29);
      cgc_free(read_00526);
      if (read_00526_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00527;
      unsigned int read_00527_len;
      unsigned int read_00527_ptr = 0;
      //**** delimited read
      static unsigned char read_00527_delim[] = 
         "\x0a";
      read_00527 = NULL;
      read_00527_len = 0;
      int read_00527_res = cgc_delimited_read(0, &read_00527, &read_00527_len, read_00527_delim, 1);
      if (read_00527_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00527_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00527_ptr += cgc_data_match(read_00527 + read_00527_ptr, read_00527_len - read_00527_ptr, match_00527_00000, 65);
      cgc_free(read_00527);
      if (read_00527_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00528;
      unsigned int read_00528_len;
      unsigned int read_00528_ptr = 0;
      //**** delimited read
      static unsigned char read_00528_delim[] = 
         "\x0a";
      read_00528 = NULL;
      read_00528_len = 0;
      int read_00528_res = cgc_delimited_read(0, &read_00528, &read_00528_len, read_00528_delim, 1);
      if (read_00528_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00528_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00528_ptr += cgc_data_match(read_00528 + read_00528_ptr, read_00528_len - read_00528_ptr, match_00528_00000, 7);
      cgc_free(read_00528);
      if (read_00528_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00343_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00343_00000_len = 2;
      unsigned char *write_00343 = NULL;
      unsigned int write_00343_len = 0;
      write_00343 = cgc_append_buf(write_00343, &write_00343_len, write_00343_00000, write_00343_00000_len);
      if (write_00343_len > 0) {
         cgc_transmit_all(1, write_00343, write_00343_len);
      }
      cgc_free(write_00343);
   } while (0);
   do {
      unsigned char *read_00529;
      unsigned int read_00529_len;
      unsigned int read_00529_ptr = 0;
      //**** delimited read
      static unsigned char read_00529_delim[] = 
         "\x0a";
      read_00529 = NULL;
      read_00529_len = 0;
      int read_00529_res = cgc_delimited_read(0, &read_00529, &read_00529_len, read_00529_delim, 1);
      if (read_00529_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00529_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00529_ptr += cgc_data_match(read_00529 + read_00529_ptr, read_00529_len - read_00529_ptr, match_00529_00000, 17);
      cgc_free(read_00529);
      if (read_00529_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00344_00000[] = 
         "\x31\x0a";
      static unsigned int write_00344_00000_len = 2;
      unsigned char *write_00344 = NULL;
      unsigned int write_00344_len = 0;
      write_00344 = cgc_append_buf(write_00344, &write_00344_len, write_00344_00000, write_00344_00000_len);
      if (write_00344_len > 0) {
         cgc_transmit_all(1, write_00344, write_00344_len);
      }
      cgc_free(write_00344);
   } while (0);
   do {
      unsigned char *read_00530;
      unsigned int read_00530_len;
      unsigned int read_00530_ptr = 0;
      //**** delimited read
      static unsigned char read_00530_delim[] = 
         "\x0a";
      read_00530 = NULL;
      read_00530_len = 0;
      int read_00530_res = cgc_delimited_read(0, &read_00530, &read_00530_len, read_00530_delim, 1);
      if (read_00530_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00530_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00530_ptr += cgc_data_match(read_00530 + read_00530_ptr, read_00530_len - read_00530_ptr, match_00530_00000, 29);
      cgc_free(read_00530);
      if (read_00530_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00531;
      unsigned int read_00531_len;
      unsigned int read_00531_ptr = 0;
      //**** delimited read
      static unsigned char read_00531_delim[] = 
         "\x0a";
      read_00531 = NULL;
      read_00531_len = 0;
      int read_00531_res = cgc_delimited_read(0, &read_00531, &read_00531_len, read_00531_delim, 1);
      if (read_00531_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00531_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00531_ptr += cgc_data_match(read_00531 + read_00531_ptr, read_00531_len - read_00531_ptr, match_00531_00000, 65);
      cgc_free(read_00531);
      if (read_00531_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00532;
      unsigned int read_00532_len;
      unsigned int read_00532_ptr = 0;
      //**** delimited read
      static unsigned char read_00532_delim[] = 
         "\x0a";
      read_00532 = NULL;
      read_00532_len = 0;
      int read_00532_res = cgc_delimited_read(0, &read_00532, &read_00532_len, read_00532_delim, 1);
      if (read_00532_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00532_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00532_ptr += cgc_data_match(read_00532 + read_00532_ptr, read_00532_len - read_00532_ptr, match_00532_00000, 7);
      cgc_free(read_00532);
      if (read_00532_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00345_00000[] = 
         "\x4f\x0a";
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
      unsigned char *read_00533;
      unsigned int read_00533_len;
      unsigned int read_00533_ptr = 0;
      //**** delimited read
      static unsigned char read_00533_delim[] = 
         "\x0a";
      read_00533 = NULL;
      read_00533_len = 0;
      int read_00533_res = cgc_delimited_read(0, &read_00533, &read_00533_len, read_00533_delim, 1);
      if (read_00533_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00533_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00533_ptr += cgc_data_match(read_00533 + read_00533_ptr, read_00533_len - read_00533_ptr, match_00533_00000, 17);
      cgc_free(read_00533);
      if (read_00533_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00346_00000[] = 
         "\x31\x0a";
      static unsigned int write_00346_00000_len = 2;
      unsigned char *write_00346 = NULL;
      unsigned int write_00346_len = 0;
      write_00346 = cgc_append_buf(write_00346, &write_00346_len, write_00346_00000, write_00346_00000_len);
      if (write_00346_len > 0) {
         cgc_transmit_all(1, write_00346, write_00346_len);
      }
      cgc_free(write_00346);
   } while (0);
   do {
      unsigned char *read_00534;
      unsigned int read_00534_len;
      unsigned int read_00534_ptr = 0;
      //**** delimited read
      static unsigned char read_00534_delim[] = 
         "\x0a";
      read_00534 = NULL;
      read_00534_len = 0;
      int read_00534_res = cgc_delimited_read(0, &read_00534, &read_00534_len, read_00534_delim, 1);
      if (read_00534_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00534_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00534_ptr += cgc_data_match(read_00534 + read_00534_ptr, read_00534_len - read_00534_ptr, match_00534_00000, 8);
      cgc_free(read_00534);
      if (read_00534_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00347_00000[] = 
         "\x44\x0a";
      static unsigned int write_00347_00000_len = 2;
      unsigned char *write_00347 = NULL;
      unsigned int write_00347_len = 0;
      write_00347 = cgc_append_buf(write_00347, &write_00347_len, write_00347_00000, write_00347_00000_len);
      if (write_00347_len > 0) {
         cgc_transmit_all(1, write_00347, write_00347_len);
      }
      cgc_free(write_00347);
   } while (0);
   do {
      unsigned char *read_00535;
      unsigned int read_00535_len;
      unsigned int read_00535_ptr = 0;
      //**** delimited read
      static unsigned char read_00535_delim[] = 
         "\x0a";
      read_00535 = NULL;
      read_00535_len = 0;
      int read_00535_res = cgc_delimited_read(0, &read_00535, &read_00535_len, read_00535_delim, 1);
      if (read_00535_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00535_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00535_ptr += cgc_data_match(read_00535 + read_00535_ptr, read_00535_len - read_00535_ptr, match_00535_00000, 47);
      cgc_free(read_00535);
      if (read_00535_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00536;
      unsigned int read_00536_len;
      unsigned int read_00536_ptr = 0;
      //**** delimited read
      static unsigned char read_00536_delim[] = 
         "\x0a";
      read_00536 = NULL;
      read_00536_len = 0;
      int read_00536_res = cgc_delimited_read(0, &read_00536, &read_00536_len, read_00536_delim, 1);
      if (read_00536_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00536_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00536_ptr += cgc_data_match(read_00536 + read_00536_ptr, read_00536_len - read_00536_ptr, match_00536_00000, 8);
      cgc_free(read_00536);
      if (read_00536_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00348_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00348_00000_len = 2;
      unsigned char *write_00348 = NULL;
      unsigned int write_00348_len = 0;
      write_00348 = cgc_append_buf(write_00348, &write_00348_len, write_00348_00000, write_00348_00000_len);
      if (write_00348_len > 0) {
         cgc_transmit_all(1, write_00348, write_00348_len);
      }
      cgc_free(write_00348);
   } while (0);
   do {
      unsigned char *read_00537;
      unsigned int read_00537_len;
      unsigned int read_00537_ptr = 0;
      //**** delimited read
      static unsigned char read_00537_delim[] = 
         "\x0a";
      read_00537 = NULL;
      read_00537_len = 0;
      int read_00537_res = cgc_delimited_read(0, &read_00537, &read_00537_len, read_00537_delim, 1);
      if (read_00537_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00537_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00537_ptr += cgc_data_match(read_00537 + read_00537_ptr, read_00537_len - read_00537_ptr, match_00537_00000, 6);
      cgc_free(read_00537);
      if (read_00537_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00349_00000[] = 
         "\x32\x38\x0a";
      static unsigned int write_00349_00000_len = 3;
      unsigned char *write_00349 = NULL;
      unsigned int write_00349_len = 0;
      write_00349 = cgc_append_buf(write_00349, &write_00349_len, write_00349_00000, write_00349_00000_len);
      if (write_00349_len > 0) {
         cgc_transmit_all(1, write_00349, write_00349_len);
      }
      cgc_free(write_00349);
   } while (0);
   do {
      unsigned char *read_00538;
      unsigned int read_00538_len;
      unsigned int read_00538_ptr = 0;
      //**** delimited read
      static unsigned char read_00538_delim[] = 
         "\x0a";
      read_00538 = NULL;
      read_00538_len = 0;
      int read_00538_res = cgc_delimited_read(0, &read_00538, &read_00538_len, read_00538_delim, 1);
      if (read_00538_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00538_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00538_ptr += cgc_data_match(read_00538 + read_00538_ptr, read_00538_len - read_00538_ptr, match_00538_00000, 47);
      cgc_free(read_00538);
      if (read_00538_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00539;
      unsigned int read_00539_len;
      unsigned int read_00539_ptr = 0;
      //**** delimited read
      static unsigned char read_00539_delim[] = 
         "\x0a";
      read_00539 = NULL;
      read_00539_len = 0;
      int read_00539_res = cgc_delimited_read(0, &read_00539, &read_00539_len, read_00539_delim, 1);
      if (read_00539_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00539_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00539_ptr += cgc_data_match(read_00539 + read_00539_ptr, read_00539_len - read_00539_ptr, match_00539_00000, 8);
      cgc_free(read_00539);
      if (read_00539_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00350_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00350_00000_len = 2;
      unsigned char *write_00350 = NULL;
      unsigned int write_00350_len = 0;
      write_00350 = cgc_append_buf(write_00350, &write_00350_len, write_00350_00000, write_00350_00000_len);
      if (write_00350_len > 0) {
         cgc_transmit_all(1, write_00350, write_00350_len);
      }
      cgc_free(write_00350);
   } while (0);
   do {
      unsigned char *read_00540;
      unsigned int read_00540_len;
      unsigned int read_00540_ptr = 0;
      //**** delimited read
      static unsigned char read_00540_delim[] = 
         "\x0a";
      read_00540 = NULL;
      read_00540_len = 0;
      int read_00540_res = cgc_delimited_read(0, &read_00540, &read_00540_len, read_00540_delim, 1);
      if (read_00540_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00540_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00540_ptr += cgc_data_match(read_00540 + read_00540_ptr, read_00540_len - read_00540_ptr, match_00540_00000, 6);
      cgc_free(read_00540);
      if (read_00540_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00351_00000[] = 
         "\x32\x39\x0a";
      static unsigned int write_00351_00000_len = 3;
      unsigned char *write_00351 = NULL;
      unsigned int write_00351_len = 0;
      write_00351 = cgc_append_buf(write_00351, &write_00351_len, write_00351_00000, write_00351_00000_len);
      if (write_00351_len > 0) {
         cgc_transmit_all(1, write_00351, write_00351_len);
      }
      cgc_free(write_00351);
   } while (0);
   do {
      unsigned char *read_00541;
      unsigned int read_00541_len;
      unsigned int read_00541_ptr = 0;
      //**** delimited read
      static unsigned char read_00541_delim[] = 
         "\x0a";
      read_00541 = NULL;
      read_00541_len = 0;
      int read_00541_res = cgc_delimited_read(0, &read_00541, &read_00541_len, read_00541_delim, 1);
      if (read_00541_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00541_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00541_ptr += cgc_data_match(read_00541 + read_00541_ptr, read_00541_len - read_00541_ptr, match_00541_00000, 29);
      cgc_free(read_00541);
      if (read_00541_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00542;
      unsigned int read_00542_len;
      unsigned int read_00542_ptr = 0;
      //**** delimited read
      static unsigned char read_00542_delim[] = 
         "\x0a";
      read_00542 = NULL;
      read_00542_len = 0;
      int read_00542_res = cgc_delimited_read(0, &read_00542, &read_00542_len, read_00542_delim, 1);
      if (read_00542_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00542_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00542_ptr += cgc_data_match(read_00542 + read_00542_ptr, read_00542_len - read_00542_ptr, match_00542_00000, 65);
      cgc_free(read_00542);
      if (read_00542_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00543;
      unsigned int read_00543_len;
      unsigned int read_00543_ptr = 0;
      //**** delimited read
      static unsigned char read_00543_delim[] = 
         "\x0a";
      read_00543 = NULL;
      read_00543_len = 0;
      int read_00543_res = cgc_delimited_read(0, &read_00543, &read_00543_len, read_00543_delim, 1);
      if (read_00543_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00543_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00543_ptr += cgc_data_match(read_00543 + read_00543_ptr, read_00543_len - read_00543_ptr, match_00543_00000, 7);
      cgc_free(read_00543);
      if (read_00543_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00352_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00352_00000_len = 2;
      unsigned char *write_00352 = NULL;
      unsigned int write_00352_len = 0;
      write_00352 = cgc_append_buf(write_00352, &write_00352_len, write_00352_00000, write_00352_00000_len);
      if (write_00352_len > 0) {
         cgc_transmit_all(1, write_00352, write_00352_len);
      }
      cgc_free(write_00352);
   } while (0);
   do {
      unsigned char *read_00544;
      unsigned int read_00544_len;
      unsigned int read_00544_ptr = 0;
      //**** delimited read
      static unsigned char read_00544_delim[] = 
         "\x0a";
      read_00544 = NULL;
      read_00544_len = 0;
      int read_00544_res = cgc_delimited_read(0, &read_00544, &read_00544_len, read_00544_delim, 1);
      if (read_00544_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00544_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00544_ptr += cgc_data_match(read_00544 + read_00544_ptr, read_00544_len - read_00544_ptr, match_00544_00000, 17);
      cgc_free(read_00544);
      if (read_00544_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00353_00000[] = 
         "\x31\x0a";
      static unsigned int write_00353_00000_len = 2;
      unsigned char *write_00353 = NULL;
      unsigned int write_00353_len = 0;
      write_00353 = cgc_append_buf(write_00353, &write_00353_len, write_00353_00000, write_00353_00000_len);
      if (write_00353_len > 0) {
         cgc_transmit_all(1, write_00353, write_00353_len);
      }
      cgc_free(write_00353);
   } while (0);
   do {
      unsigned char *read_00545;
      unsigned int read_00545_len;
      unsigned int read_00545_ptr = 0;
      //**** delimited read
      static unsigned char read_00545_delim[] = 
         "\x0a";
      read_00545 = NULL;
      read_00545_len = 0;
      int read_00545_res = cgc_delimited_read(0, &read_00545, &read_00545_len, read_00545_delim, 1);
      if (read_00545_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00545_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00545_ptr += cgc_data_match(read_00545 + read_00545_ptr, read_00545_len - read_00545_ptr, match_00545_00000, 29);
      cgc_free(read_00545);
      if (read_00545_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00546;
      unsigned int read_00546_len;
      unsigned int read_00546_ptr = 0;
      //**** delimited read
      static unsigned char read_00546_delim[] = 
         "\x0a";
      read_00546 = NULL;
      read_00546_len = 0;
      int read_00546_res = cgc_delimited_read(0, &read_00546, &read_00546_len, read_00546_delim, 1);
      if (read_00546_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00546_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00546_ptr += cgc_data_match(read_00546 + read_00546_ptr, read_00546_len - read_00546_ptr, match_00546_00000, 65);
      cgc_free(read_00546);
      if (read_00546_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00547;
      unsigned int read_00547_len;
      unsigned int read_00547_ptr = 0;
      //**** delimited read
      static unsigned char read_00547_delim[] = 
         "\x0a";
      read_00547 = NULL;
      read_00547_len = 0;
      int read_00547_res = cgc_delimited_read(0, &read_00547, &read_00547_len, read_00547_delim, 1);
      if (read_00547_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00547_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00547_ptr += cgc_data_match(read_00547 + read_00547_ptr, read_00547_len - read_00547_ptr, match_00547_00000, 7);
      cgc_free(read_00547);
      if (read_00547_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00354_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00354_00000_len = 2;
      unsigned char *write_00354 = NULL;
      unsigned int write_00354_len = 0;
      write_00354 = cgc_append_buf(write_00354, &write_00354_len, write_00354_00000, write_00354_00000_len);
      if (write_00354_len > 0) {
         cgc_transmit_all(1, write_00354, write_00354_len);
      }
      cgc_free(write_00354);
   } while (0);
   do {
      unsigned char *read_00548;
      unsigned int read_00548_len;
      unsigned int read_00548_ptr = 0;
      //**** delimited read
      static unsigned char read_00548_delim[] = 
         "\x0a";
      read_00548 = NULL;
      read_00548_len = 0;
      int read_00548_res = cgc_delimited_read(0, &read_00548, &read_00548_len, read_00548_delim, 1);
      if (read_00548_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00548_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00548_ptr += cgc_data_match(read_00548 + read_00548_ptr, read_00548_len - read_00548_ptr, match_00548_00000, 17);
      cgc_free(read_00548);
      if (read_00548_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00355_00000[] = 
         "\x31\x0a";
      static unsigned int write_00355_00000_len = 2;
      unsigned char *write_00355 = NULL;
      unsigned int write_00355_len = 0;
      write_00355 = cgc_append_buf(write_00355, &write_00355_len, write_00355_00000, write_00355_00000_len);
      if (write_00355_len > 0) {
         cgc_transmit_all(1, write_00355, write_00355_len);
      }
      cgc_free(write_00355);
   } while (0);
   do {
      unsigned char *read_00549;
      unsigned int read_00549_len;
      unsigned int read_00549_ptr = 0;
      //**** delimited read
      static unsigned char read_00549_delim[] = 
         "\x0a";
      read_00549 = NULL;
      read_00549_len = 0;
      int read_00549_res = cgc_delimited_read(0, &read_00549, &read_00549_len, read_00549_delim, 1);
      if (read_00549_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00549_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00549_ptr += cgc_data_match(read_00549 + read_00549_ptr, read_00549_len - read_00549_ptr, match_00549_00000, 8);
      cgc_free(read_00549);
      if (read_00549_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00356_00000[] = 
         "\x44\x0a";
      static unsigned int write_00356_00000_len = 2;
      unsigned char *write_00356 = NULL;
      unsigned int write_00356_len = 0;
      write_00356 = cgc_append_buf(write_00356, &write_00356_len, write_00356_00000, write_00356_00000_len);
      if (write_00356_len > 0) {
         cgc_transmit_all(1, write_00356, write_00356_len);
      }
      cgc_free(write_00356);
   } while (0);
   do {
      unsigned char *read_00550;
      unsigned int read_00550_len;
      unsigned int read_00550_ptr = 0;
      //**** delimited read
      static unsigned char read_00550_delim[] = 
         "\x0a";
      read_00550 = NULL;
      read_00550_len = 0;
      int read_00550_res = cgc_delimited_read(0, &read_00550, &read_00550_len, read_00550_delim, 1);
      if (read_00550_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00550_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00550_ptr += cgc_data_match(read_00550 + read_00550_ptr, read_00550_len - read_00550_ptr, match_00550_00000, 47);
      cgc_free(read_00550);
      if (read_00550_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00551;
      unsigned int read_00551_len;
      unsigned int read_00551_ptr = 0;
      //**** delimited read
      static unsigned char read_00551_delim[] = 
         "\x0a";
      read_00551 = NULL;
      read_00551_len = 0;
      int read_00551_res = cgc_delimited_read(0, &read_00551, &read_00551_len, read_00551_delim, 1);
      if (read_00551_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00551_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00551_ptr += cgc_data_match(read_00551 + read_00551_ptr, read_00551_len - read_00551_ptr, match_00551_00000, 8);
      cgc_free(read_00551);
      if (read_00551_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00357_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00357_00000_len = 2;
      unsigned char *write_00357 = NULL;
      unsigned int write_00357_len = 0;
      write_00357 = cgc_append_buf(write_00357, &write_00357_len, write_00357_00000, write_00357_00000_len);
      if (write_00357_len > 0) {
         cgc_transmit_all(1, write_00357, write_00357_len);
      }
      cgc_free(write_00357);
   } while (0);
   do {
      unsigned char *read_00552;
      unsigned int read_00552_len;
      unsigned int read_00552_ptr = 0;
      //**** delimited read
      static unsigned char read_00552_delim[] = 
         "\x0a";
      read_00552 = NULL;
      read_00552_len = 0;
      int read_00552_res = cgc_delimited_read(0, &read_00552, &read_00552_len, read_00552_delim, 1);
      if (read_00552_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00552_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00552_ptr += cgc_data_match(read_00552 + read_00552_ptr, read_00552_len - read_00552_ptr, match_00552_00000, 6);
      cgc_free(read_00552);
      if (read_00552_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00358_00000[] = 
         "\x33\x30\x0a";
      static unsigned int write_00358_00000_len = 3;
      unsigned char *write_00358 = NULL;
      unsigned int write_00358_len = 0;
      write_00358 = cgc_append_buf(write_00358, &write_00358_len, write_00358_00000, write_00358_00000_len);
      if (write_00358_len > 0) {
         cgc_transmit_all(1, write_00358, write_00358_len);
      }
      cgc_free(write_00358);
   } while (0);
   do {
      unsigned char *read_00553;
      unsigned int read_00553_len;
      unsigned int read_00553_ptr = 0;
      //**** delimited read
      static unsigned char read_00553_delim[] = 
         "\x0a";
      read_00553 = NULL;
      read_00553_len = 0;
      int read_00553_res = cgc_delimited_read(0, &read_00553, &read_00553_len, read_00553_delim, 1);
      if (read_00553_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00553_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00553_ptr += cgc_data_match(read_00553 + read_00553_ptr, read_00553_len - read_00553_ptr, match_00553_00000, 47);
      cgc_free(read_00553);
      if (read_00553_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00554;
      unsigned int read_00554_len;
      unsigned int read_00554_ptr = 0;
      //**** delimited read
      static unsigned char read_00554_delim[] = 
         "\x0a";
      read_00554 = NULL;
      read_00554_len = 0;
      int read_00554_res = cgc_delimited_read(0, &read_00554, &read_00554_len, read_00554_delim, 1);
      if (read_00554_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00554_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00554_ptr += cgc_data_match(read_00554 + read_00554_ptr, read_00554_len - read_00554_ptr, match_00554_00000, 8);
      cgc_free(read_00554);
      if (read_00554_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00359_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00359_00000_len = 2;
      unsigned char *write_00359 = NULL;
      unsigned int write_00359_len = 0;
      write_00359 = cgc_append_buf(write_00359, &write_00359_len, write_00359_00000, write_00359_00000_len);
      if (write_00359_len > 0) {
         cgc_transmit_all(1, write_00359, write_00359_len);
      }
      cgc_free(write_00359);
   } while (0);
   do {
      unsigned char *read_00555;
      unsigned int read_00555_len;
      unsigned int read_00555_ptr = 0;
      //**** delimited read
      static unsigned char read_00555_delim[] = 
         "\x0a";
      read_00555 = NULL;
      read_00555_len = 0;
      int read_00555_res = cgc_delimited_read(0, &read_00555, &read_00555_len, read_00555_delim, 1);
      if (read_00555_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00555_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00555_ptr += cgc_data_match(read_00555 + read_00555_ptr, read_00555_len - read_00555_ptr, match_00555_00000, 6);
      cgc_free(read_00555);
      if (read_00555_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00360_00000[] = 
         "\x33\x31\x0a";
      static unsigned int write_00360_00000_len = 3;
      unsigned char *write_00360 = NULL;
      unsigned int write_00360_len = 0;
      write_00360 = cgc_append_buf(write_00360, &write_00360_len, write_00360_00000, write_00360_00000_len);
      if (write_00360_len > 0) {
         cgc_transmit_all(1, write_00360, write_00360_len);
      }
      cgc_free(write_00360);
   } while (0);
   do {
      unsigned char *read_00556;
      unsigned int read_00556_len;
      unsigned int read_00556_ptr = 0;
      //**** delimited read
      static unsigned char read_00556_delim[] = 
         "\x0a";
      read_00556 = NULL;
      read_00556_len = 0;
      int read_00556_res = cgc_delimited_read(0, &read_00556, &read_00556_len, read_00556_delim, 1);
      if (read_00556_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00556_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00556_ptr += cgc_data_match(read_00556 + read_00556_ptr, read_00556_len - read_00556_ptr, match_00556_00000, 29);
      cgc_free(read_00556);
      if (read_00556_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00557;
      unsigned int read_00557_len;
      unsigned int read_00557_ptr = 0;
      //**** delimited read
      static unsigned char read_00557_delim[] = 
         "\x0a";
      read_00557 = NULL;
      read_00557_len = 0;
      int read_00557_res = cgc_delimited_read(0, &read_00557, &read_00557_len, read_00557_delim, 1);
      if (read_00557_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00557_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00557_ptr += cgc_data_match(read_00557 + read_00557_ptr, read_00557_len - read_00557_ptr, match_00557_00000, 65);
      cgc_free(read_00557);
      if (read_00557_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00558;
      unsigned int read_00558_len;
      unsigned int read_00558_ptr = 0;
      //**** delimited read
      static unsigned char read_00558_delim[] = 
         "\x0a";
      read_00558 = NULL;
      read_00558_len = 0;
      int read_00558_res = cgc_delimited_read(0, &read_00558, &read_00558_len, read_00558_delim, 1);
      if (read_00558_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00558_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00558_ptr += cgc_data_match(read_00558 + read_00558_ptr, read_00558_len - read_00558_ptr, match_00558_00000, 7);
      cgc_free(read_00558);
      if (read_00558_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00361_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00361_00000_len = 2;
      unsigned char *write_00361 = NULL;
      unsigned int write_00361_len = 0;
      write_00361 = cgc_append_buf(write_00361, &write_00361_len, write_00361_00000, write_00361_00000_len);
      if (write_00361_len > 0) {
         cgc_transmit_all(1, write_00361, write_00361_len);
      }
      cgc_free(write_00361);
   } while (0);
   do {
      unsigned char *read_00559;
      unsigned int read_00559_len;
      unsigned int read_00559_ptr = 0;
      //**** delimited read
      static unsigned char read_00559_delim[] = 
         "\x0a";
      read_00559 = NULL;
      read_00559_len = 0;
      int read_00559_res = cgc_delimited_read(0, &read_00559, &read_00559_len, read_00559_delim, 1);
      if (read_00559_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00559_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00559_ptr += cgc_data_match(read_00559 + read_00559_ptr, read_00559_len - read_00559_ptr, match_00559_00000, 17);
      cgc_free(read_00559);
      if (read_00559_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00362_00000[] = 
         "\x31\x0a";
      static unsigned int write_00362_00000_len = 2;
      unsigned char *write_00362 = NULL;
      unsigned int write_00362_len = 0;
      write_00362 = cgc_append_buf(write_00362, &write_00362_len, write_00362_00000, write_00362_00000_len);
      if (write_00362_len > 0) {
         cgc_transmit_all(1, write_00362, write_00362_len);
      }
      cgc_free(write_00362);
   } while (0);
   do {
      unsigned char *read_00560;
      unsigned int read_00560_len;
      unsigned int read_00560_ptr = 0;
      //**** delimited read
      static unsigned char read_00560_delim[] = 
         "\x0a";
      read_00560 = NULL;
      read_00560_len = 0;
      int read_00560_res = cgc_delimited_read(0, &read_00560, &read_00560_len, read_00560_delim, 1);
      if (read_00560_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00560_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00560_ptr += cgc_data_match(read_00560 + read_00560_ptr, read_00560_len - read_00560_ptr, match_00560_00000, 29);
      cgc_free(read_00560);
      if (read_00560_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00561;
      unsigned int read_00561_len;
      unsigned int read_00561_ptr = 0;
      //**** delimited read
      static unsigned char read_00561_delim[] = 
         "\x0a";
      read_00561 = NULL;
      read_00561_len = 0;
      int read_00561_res = cgc_delimited_read(0, &read_00561, &read_00561_len, read_00561_delim, 1);
      if (read_00561_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00561_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00561_ptr += cgc_data_match(read_00561 + read_00561_ptr, read_00561_len - read_00561_ptr, match_00561_00000, 65);
      cgc_free(read_00561);
      if (read_00561_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00562;
      unsigned int read_00562_len;
      unsigned int read_00562_ptr = 0;
      //**** delimited read
      static unsigned char read_00562_delim[] = 
         "\x0a";
      read_00562 = NULL;
      read_00562_len = 0;
      int read_00562_res = cgc_delimited_read(0, &read_00562, &read_00562_len, read_00562_delim, 1);
      if (read_00562_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00562_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00562_ptr += cgc_data_match(read_00562 + read_00562_ptr, read_00562_len - read_00562_ptr, match_00562_00000, 7);
      cgc_free(read_00562);
      if (read_00562_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00363_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00363_00000_len = 2;
      unsigned char *write_00363 = NULL;
      unsigned int write_00363_len = 0;
      write_00363 = cgc_append_buf(write_00363, &write_00363_len, write_00363_00000, write_00363_00000_len);
      if (write_00363_len > 0) {
         cgc_transmit_all(1, write_00363, write_00363_len);
      }
      cgc_free(write_00363);
   } while (0);
   do {
      unsigned char *read_00563;
      unsigned int read_00563_len;
      unsigned int read_00563_ptr = 0;
      //**** delimited read
      static unsigned char read_00563_delim[] = 
         "\x0a";
      read_00563 = NULL;
      read_00563_len = 0;
      int read_00563_res = cgc_delimited_read(0, &read_00563, &read_00563_len, read_00563_delim, 1);
      if (read_00563_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00563_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00563_ptr += cgc_data_match(read_00563 + read_00563_ptr, read_00563_len - read_00563_ptr, match_00563_00000, 17);
      cgc_free(read_00563);
      if (read_00563_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00364_00000[] = 
         "\x31\x0a";
      static unsigned int write_00364_00000_len = 2;
      unsigned char *write_00364 = NULL;
      unsigned int write_00364_len = 0;
      write_00364 = cgc_append_buf(write_00364, &write_00364_len, write_00364_00000, write_00364_00000_len);
      if (write_00364_len > 0) {
         cgc_transmit_all(1, write_00364, write_00364_len);
      }
      cgc_free(write_00364);
   } while (0);
   do {
      unsigned char *read_00564;
      unsigned int read_00564_len;
      unsigned int read_00564_ptr = 0;
      //**** delimited read
      static unsigned char read_00564_delim[] = 
         "\x0a";
      read_00564 = NULL;
      read_00564_len = 0;
      int read_00564_res = cgc_delimited_read(0, &read_00564, &read_00564_len, read_00564_delim, 1);
      if (read_00564_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00564_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00564_ptr += cgc_data_match(read_00564 + read_00564_ptr, read_00564_len - read_00564_ptr, match_00564_00000, 8);
      cgc_free(read_00564);
      if (read_00564_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00365_00000[] = 
         "\x44\x0a";
      static unsigned int write_00365_00000_len = 2;
      unsigned char *write_00365 = NULL;
      unsigned int write_00365_len = 0;
      write_00365 = cgc_append_buf(write_00365, &write_00365_len, write_00365_00000, write_00365_00000_len);
      if (write_00365_len > 0) {
         cgc_transmit_all(1, write_00365, write_00365_len);
      }
      cgc_free(write_00365);
   } while (0);
   do {
      unsigned char *read_00565;
      unsigned int read_00565_len;
      unsigned int read_00565_ptr = 0;
      //**** delimited read
      static unsigned char read_00565_delim[] = 
         "\x0a";
      read_00565 = NULL;
      read_00565_len = 0;
      int read_00565_res = cgc_delimited_read(0, &read_00565, &read_00565_len, read_00565_delim, 1);
      if (read_00565_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00565_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00565_ptr += cgc_data_match(read_00565 + read_00565_ptr, read_00565_len - read_00565_ptr, match_00565_00000, 47);
      cgc_free(read_00565);
      if (read_00565_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00566;
      unsigned int read_00566_len;
      unsigned int read_00566_ptr = 0;
      //**** delimited read
      static unsigned char read_00566_delim[] = 
         "\x0a";
      read_00566 = NULL;
      read_00566_len = 0;
      int read_00566_res = cgc_delimited_read(0, &read_00566, &read_00566_len, read_00566_delim, 1);
      if (read_00566_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00566_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00566_ptr += cgc_data_match(read_00566 + read_00566_ptr, read_00566_len - read_00566_ptr, match_00566_00000, 8);
      cgc_free(read_00566);
      if (read_00566_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00366_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00366_00000_len = 2;
      unsigned char *write_00366 = NULL;
      unsigned int write_00366_len = 0;
      write_00366 = cgc_append_buf(write_00366, &write_00366_len, write_00366_00000, write_00366_00000_len);
      if (write_00366_len > 0) {
         cgc_transmit_all(1, write_00366, write_00366_len);
      }
      cgc_free(write_00366);
   } while (0);
   do {
      unsigned char *read_00567;
      unsigned int read_00567_len;
      unsigned int read_00567_ptr = 0;
      //**** delimited read
      static unsigned char read_00567_delim[] = 
         "\x0a";
      read_00567 = NULL;
      read_00567_len = 0;
      int read_00567_res = cgc_delimited_read(0, &read_00567, &read_00567_len, read_00567_delim, 1);
      if (read_00567_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00567_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00567_ptr += cgc_data_match(read_00567 + read_00567_ptr, read_00567_len - read_00567_ptr, match_00567_00000, 6);
      cgc_free(read_00567);
      if (read_00567_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00367_00000[] = 
         "\x33\x32\x0a";
      static unsigned int write_00367_00000_len = 3;
      unsigned char *write_00367 = NULL;
      unsigned int write_00367_len = 0;
      write_00367 = cgc_append_buf(write_00367, &write_00367_len, write_00367_00000, write_00367_00000_len);
      if (write_00367_len > 0) {
         cgc_transmit_all(1, write_00367, write_00367_len);
      }
      cgc_free(write_00367);
   } while (0);
   do {
      unsigned char *read_00568;
      unsigned int read_00568_len;
      unsigned int read_00568_ptr = 0;
      //**** delimited read
      static unsigned char read_00568_delim[] = 
         "\x0a";
      read_00568 = NULL;
      read_00568_len = 0;
      int read_00568_res = cgc_delimited_read(0, &read_00568, &read_00568_len, read_00568_delim, 1);
      if (read_00568_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00568_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00568_ptr += cgc_data_match(read_00568 + read_00568_ptr, read_00568_len - read_00568_ptr, match_00568_00000, 47);
      cgc_free(read_00568);
      if (read_00568_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00569;
      unsigned int read_00569_len;
      unsigned int read_00569_ptr = 0;
      //**** delimited read
      static unsigned char read_00569_delim[] = 
         "\x0a";
      read_00569 = NULL;
      read_00569_len = 0;
      int read_00569_res = cgc_delimited_read(0, &read_00569, &read_00569_len, read_00569_delim, 1);
      if (read_00569_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00569_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00569_ptr += cgc_data_match(read_00569 + read_00569_ptr, read_00569_len - read_00569_ptr, match_00569_00000, 8);
      cgc_free(read_00569);
      if (read_00569_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00368_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00368_00000_len = 2;
      unsigned char *write_00368 = NULL;
      unsigned int write_00368_len = 0;
      write_00368 = cgc_append_buf(write_00368, &write_00368_len, write_00368_00000, write_00368_00000_len);
      if (write_00368_len > 0) {
         cgc_transmit_all(1, write_00368, write_00368_len);
      }
      cgc_free(write_00368);
   } while (0);
   do {
      unsigned char *read_00570;
      unsigned int read_00570_len;
      unsigned int read_00570_ptr = 0;
      //**** delimited read
      static unsigned char read_00570_delim[] = 
         "\x0a";
      read_00570 = NULL;
      read_00570_len = 0;
      int read_00570_res = cgc_delimited_read(0, &read_00570, &read_00570_len, read_00570_delim, 1);
      if (read_00570_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00570_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00570_ptr += cgc_data_match(read_00570 + read_00570_ptr, read_00570_len - read_00570_ptr, match_00570_00000, 6);
      cgc_free(read_00570);
      if (read_00570_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00369_00000[] = 
         "\x33\x33\x0a";
      static unsigned int write_00369_00000_len = 3;
      unsigned char *write_00369 = NULL;
      unsigned int write_00369_len = 0;
      write_00369 = cgc_append_buf(write_00369, &write_00369_len, write_00369_00000, write_00369_00000_len);
      if (write_00369_len > 0) {
         cgc_transmit_all(1, write_00369, write_00369_len);
      }
      cgc_free(write_00369);
   } while (0);
   do {
      unsigned char *read_00571;
      unsigned int read_00571_len;
      unsigned int read_00571_ptr = 0;
      //**** delimited read
      static unsigned char read_00571_delim[] = 
         "\x0a";
      read_00571 = NULL;
      read_00571_len = 0;
      int read_00571_res = cgc_delimited_read(0, &read_00571, &read_00571_len, read_00571_delim, 1);
      if (read_00571_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00571_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00571_ptr += cgc_data_match(read_00571 + read_00571_ptr, read_00571_len - read_00571_ptr, match_00571_00000, 29);
      cgc_free(read_00571);
      if (read_00571_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00572;
      unsigned int read_00572_len;
      unsigned int read_00572_ptr = 0;
      //**** delimited read
      static unsigned char read_00572_delim[] = 
         "\x0a";
      read_00572 = NULL;
      read_00572_len = 0;
      int read_00572_res = cgc_delimited_read(0, &read_00572, &read_00572_len, read_00572_delim, 1);
      if (read_00572_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00572_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00572_ptr += cgc_data_match(read_00572 + read_00572_ptr, read_00572_len - read_00572_ptr, match_00572_00000, 65);
      cgc_free(read_00572);
      if (read_00572_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00573;
      unsigned int read_00573_len;
      unsigned int read_00573_ptr = 0;
      //**** delimited read
      static unsigned char read_00573_delim[] = 
         "\x0a";
      read_00573 = NULL;
      read_00573_len = 0;
      int read_00573_res = cgc_delimited_read(0, &read_00573, &read_00573_len, read_00573_delim, 1);
      if (read_00573_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00573_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00573_ptr += cgc_data_match(read_00573 + read_00573_ptr, read_00573_len - read_00573_ptr, match_00573_00000, 7);
      cgc_free(read_00573);
      if (read_00573_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00370_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00370_00000_len = 2;
      unsigned char *write_00370 = NULL;
      unsigned int write_00370_len = 0;
      write_00370 = cgc_append_buf(write_00370, &write_00370_len, write_00370_00000, write_00370_00000_len);
      if (write_00370_len > 0) {
         cgc_transmit_all(1, write_00370, write_00370_len);
      }
      cgc_free(write_00370);
   } while (0);
   do {
      unsigned char *read_00574;
      unsigned int read_00574_len;
      unsigned int read_00574_ptr = 0;
      //**** delimited read
      static unsigned char read_00574_delim[] = 
         "\x0a";
      read_00574 = NULL;
      read_00574_len = 0;
      int read_00574_res = cgc_delimited_read(0, &read_00574, &read_00574_len, read_00574_delim, 1);
      if (read_00574_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00574_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00574_ptr += cgc_data_match(read_00574 + read_00574_ptr, read_00574_len - read_00574_ptr, match_00574_00000, 17);
      cgc_free(read_00574);
      if (read_00574_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00371_00000[] = 
         "\x31\x0a";
      static unsigned int write_00371_00000_len = 2;
      unsigned char *write_00371 = NULL;
      unsigned int write_00371_len = 0;
      write_00371 = cgc_append_buf(write_00371, &write_00371_len, write_00371_00000, write_00371_00000_len);
      if (write_00371_len > 0) {
         cgc_transmit_all(1, write_00371, write_00371_len);
      }
      cgc_free(write_00371);
   } while (0);
   do {
      unsigned char *read_00575;
      unsigned int read_00575_len;
      unsigned int read_00575_ptr = 0;
      //**** delimited read
      static unsigned char read_00575_delim[] = 
         "\x0a";
      read_00575 = NULL;
      read_00575_len = 0;
      int read_00575_res = cgc_delimited_read(0, &read_00575, &read_00575_len, read_00575_delim, 1);
      if (read_00575_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00575_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00575_ptr += cgc_data_match(read_00575 + read_00575_ptr, read_00575_len - read_00575_ptr, match_00575_00000, 29);
      cgc_free(read_00575);
      if (read_00575_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00576;
      unsigned int read_00576_len;
      unsigned int read_00576_ptr = 0;
      //**** delimited read
      static unsigned char read_00576_delim[] = 
         "\x0a";
      read_00576 = NULL;
      read_00576_len = 0;
      int read_00576_res = cgc_delimited_read(0, &read_00576, &read_00576_len, read_00576_delim, 1);
      if (read_00576_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00576_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00576_ptr += cgc_data_match(read_00576 + read_00576_ptr, read_00576_len - read_00576_ptr, match_00576_00000, 65);
      cgc_free(read_00576);
      if (read_00576_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00577;
      unsigned int read_00577_len;
      unsigned int read_00577_ptr = 0;
      //**** delimited read
      static unsigned char read_00577_delim[] = 
         "\x0a";
      read_00577 = NULL;
      read_00577_len = 0;
      int read_00577_res = cgc_delimited_read(0, &read_00577, &read_00577_len, read_00577_delim, 1);
      if (read_00577_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00577_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00577_ptr += cgc_data_match(read_00577 + read_00577_ptr, read_00577_len - read_00577_ptr, match_00577_00000, 7);
      cgc_free(read_00577);
      if (read_00577_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00372_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00372_00000_len = 2;
      unsigned char *write_00372 = NULL;
      unsigned int write_00372_len = 0;
      write_00372 = cgc_append_buf(write_00372, &write_00372_len, write_00372_00000, write_00372_00000_len);
      if (write_00372_len > 0) {
         cgc_transmit_all(1, write_00372, write_00372_len);
      }
      cgc_free(write_00372);
   } while (0);
   do {
      unsigned char *read_00578;
      unsigned int read_00578_len;
      unsigned int read_00578_ptr = 0;
      //**** delimited read
      static unsigned char read_00578_delim[] = 
         "\x0a";
      read_00578 = NULL;
      read_00578_len = 0;
      int read_00578_res = cgc_delimited_read(0, &read_00578, &read_00578_len, read_00578_delim, 1);
      if (read_00578_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00578_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00578_ptr += cgc_data_match(read_00578 + read_00578_ptr, read_00578_len - read_00578_ptr, match_00578_00000, 17);
      cgc_free(read_00578);
      if (read_00578_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00373_00000[] = 
         "\x31\x0a";
      static unsigned int write_00373_00000_len = 2;
      unsigned char *write_00373 = NULL;
      unsigned int write_00373_len = 0;
      write_00373 = cgc_append_buf(write_00373, &write_00373_len, write_00373_00000, write_00373_00000_len);
      if (write_00373_len > 0) {
         cgc_transmit_all(1, write_00373, write_00373_len);
      }
      cgc_free(write_00373);
   } while (0);
   do {
      unsigned char *read_00579;
      unsigned int read_00579_len;
      unsigned int read_00579_ptr = 0;
      //**** delimited read
      static unsigned char read_00579_delim[] = 
         "\x0a";
      read_00579 = NULL;
      read_00579_len = 0;
      int read_00579_res = cgc_delimited_read(0, &read_00579, &read_00579_len, read_00579_delim, 1);
      if (read_00579_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00579_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00579_ptr += cgc_data_match(read_00579 + read_00579_ptr, read_00579_len - read_00579_ptr, match_00579_00000, 8);
      cgc_free(read_00579);
      if (read_00579_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00374_00000[] = 
         "\x44\x0a";
      static unsigned int write_00374_00000_len = 2;
      unsigned char *write_00374 = NULL;
      unsigned int write_00374_len = 0;
      write_00374 = cgc_append_buf(write_00374, &write_00374_len, write_00374_00000, write_00374_00000_len);
      if (write_00374_len > 0) {
         cgc_transmit_all(1, write_00374, write_00374_len);
      }
      cgc_free(write_00374);
   } while (0);
   do {
      unsigned char *read_00580;
      unsigned int read_00580_len;
      unsigned int read_00580_ptr = 0;
      //**** delimited read
      static unsigned char read_00580_delim[] = 
         "\x0a";
      read_00580 = NULL;
      read_00580_len = 0;
      int read_00580_res = cgc_delimited_read(0, &read_00580, &read_00580_len, read_00580_delim, 1);
      if (read_00580_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00580_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00580_ptr += cgc_data_match(read_00580 + read_00580_ptr, read_00580_len - read_00580_ptr, match_00580_00000, 47);
      cgc_free(read_00580);
      if (read_00580_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00581;
      unsigned int read_00581_len;
      unsigned int read_00581_ptr = 0;
      //**** delimited read
      static unsigned char read_00581_delim[] = 
         "\x0a";
      read_00581 = NULL;
      read_00581_len = 0;
      int read_00581_res = cgc_delimited_read(0, &read_00581, &read_00581_len, read_00581_delim, 1);
      if (read_00581_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00581_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00581_ptr += cgc_data_match(read_00581 + read_00581_ptr, read_00581_len - read_00581_ptr, match_00581_00000, 8);
      cgc_free(read_00581);
      if (read_00581_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00375_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00375_00000_len = 2;
      unsigned char *write_00375 = NULL;
      unsigned int write_00375_len = 0;
      write_00375 = cgc_append_buf(write_00375, &write_00375_len, write_00375_00000, write_00375_00000_len);
      if (write_00375_len > 0) {
         cgc_transmit_all(1, write_00375, write_00375_len);
      }
      cgc_free(write_00375);
   } while (0);
   do {
      unsigned char *read_00582;
      unsigned int read_00582_len;
      unsigned int read_00582_ptr = 0;
      //**** delimited read
      static unsigned char read_00582_delim[] = 
         "\x0a";
      read_00582 = NULL;
      read_00582_len = 0;
      int read_00582_res = cgc_delimited_read(0, &read_00582, &read_00582_len, read_00582_delim, 1);
      if (read_00582_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00582_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00582_ptr += cgc_data_match(read_00582 + read_00582_ptr, read_00582_len - read_00582_ptr, match_00582_00000, 6);
      cgc_free(read_00582);
      if (read_00582_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00376_00000[] = 
         "\x33\x34\x0a";
      static unsigned int write_00376_00000_len = 3;
      unsigned char *write_00376 = NULL;
      unsigned int write_00376_len = 0;
      write_00376 = cgc_append_buf(write_00376, &write_00376_len, write_00376_00000, write_00376_00000_len);
      if (write_00376_len > 0) {
         cgc_transmit_all(1, write_00376, write_00376_len);
      }
      cgc_free(write_00376);
   } while (0);
   do {
      unsigned char *read_00583;
      unsigned int read_00583_len;
      unsigned int read_00583_ptr = 0;
      //**** delimited read
      static unsigned char read_00583_delim[] = 
         "\x0a";
      read_00583 = NULL;
      read_00583_len = 0;
      int read_00583_res = cgc_delimited_read(0, &read_00583, &read_00583_len, read_00583_delim, 1);
      if (read_00583_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00583_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00583_ptr += cgc_data_match(read_00583 + read_00583_ptr, read_00583_len - read_00583_ptr, match_00583_00000, 47);
      cgc_free(read_00583);
      if (read_00583_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00584;
      unsigned int read_00584_len;
      unsigned int read_00584_ptr = 0;
      //**** delimited read
      static unsigned char read_00584_delim[] = 
         "\x0a";
      read_00584 = NULL;
      read_00584_len = 0;
      int read_00584_res = cgc_delimited_read(0, &read_00584, &read_00584_len, read_00584_delim, 1);
      if (read_00584_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00584_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00584_ptr += cgc_data_match(read_00584 + read_00584_ptr, read_00584_len - read_00584_ptr, match_00584_00000, 8);
      cgc_free(read_00584);
      if (read_00584_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00377_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00377_00000_len = 2;
      unsigned char *write_00377 = NULL;
      unsigned int write_00377_len = 0;
      write_00377 = cgc_append_buf(write_00377, &write_00377_len, write_00377_00000, write_00377_00000_len);
      if (write_00377_len > 0) {
         cgc_transmit_all(1, write_00377, write_00377_len);
      }
      cgc_free(write_00377);
   } while (0);
   do {
      unsigned char *read_00585;
      unsigned int read_00585_len;
      unsigned int read_00585_ptr = 0;
      //**** delimited read
      static unsigned char read_00585_delim[] = 
         "\x0a";
      read_00585 = NULL;
      read_00585_len = 0;
      int read_00585_res = cgc_delimited_read(0, &read_00585, &read_00585_len, read_00585_delim, 1);
      if (read_00585_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00585_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00585_ptr += cgc_data_match(read_00585 + read_00585_ptr, read_00585_len - read_00585_ptr, match_00585_00000, 6);
      cgc_free(read_00585);
      if (read_00585_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00378_00000[] = 
         "\x33\x35\x0a";
      static unsigned int write_00378_00000_len = 3;
      unsigned char *write_00378 = NULL;
      unsigned int write_00378_len = 0;
      write_00378 = cgc_append_buf(write_00378, &write_00378_len, write_00378_00000, write_00378_00000_len);
      if (write_00378_len > 0) {
         cgc_transmit_all(1, write_00378, write_00378_len);
      }
      cgc_free(write_00378);
   } while (0);
   do {
      unsigned char *read_00586;
      unsigned int read_00586_len;
      unsigned int read_00586_ptr = 0;
      //**** delimited read
      static unsigned char read_00586_delim[] = 
         "\x0a";
      read_00586 = NULL;
      read_00586_len = 0;
      int read_00586_res = cgc_delimited_read(0, &read_00586, &read_00586_len, read_00586_delim, 1);
      if (read_00586_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00586_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x31\x2e\x0a";
      read_00586_ptr += cgc_data_match(read_00586 + read_00586_ptr, read_00586_len - read_00586_ptr, match_00586_00000, 29);
      cgc_free(read_00586);
      if (read_00586_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00587;
      unsigned int read_00587_len;
      unsigned int read_00587_ptr = 0;
      //**** delimited read
      static unsigned char read_00587_delim[] = 
         "\x0a";
      read_00587 = NULL;
      read_00587_len = 0;
      int read_00587_res = cgc_delimited_read(0, &read_00587, &read_00587_len, read_00587_delim, 1);
      if (read_00587_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00587_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74"
         "\x69\x6f\x6e\x20\x62\x79\x20\x28\x4e\x29\x75\x6d\x62\x65\x72\x2c"
         "\x20\x28\x4c\x29\x69\x73\x74\x2c\x20\x6f\x72\x20\x73\x65\x74\x20"
         "\x74\x6f\x20\x4e\x28\x4f\x29\x54\x44\x45\x46\x49\x4e\x45\x44\x2e"
         "\x0a";
      read_00587_ptr += cgc_data_match(read_00587 + read_00587_ptr, read_00587_len - read_00587_ptr, match_00587_00000, 65);
      cgc_free(read_00587);
      if (read_00587_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00588;
      unsigned int read_00588_len;
      unsigned int read_00588_ptr = 0;
      //**** delimited read
      static unsigned char read_00588_delim[] = 
         "\x0a";
      read_00588 = NULL;
      read_00588_len = 0;
      int read_00588_res = cgc_delimited_read(0, &read_00588, &read_00588_len, read_00588_delim, 1);
      if (read_00588_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00588_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a";
      read_00588_ptr += cgc_data_match(read_00588 + read_00588_ptr, read_00588_len - read_00588_ptr, match_00588_00000, 7);
      cgc_free(read_00588);
      if (read_00588_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00379_00000[] = 
         "\x4f\x0a";
      static unsigned int write_00379_00000_len = 2;
      unsigned char *write_00379 = NULL;
      unsigned int write_00379_len = 0;
      write_00379 = cgc_append_buf(write_00379, &write_00379_len, write_00379_00000, write_00379_00000_len);
      if (write_00379_len > 0) {
         cgc_transmit_all(1, write_00379, write_00379_len);
      }
      cgc_free(write_00379);
   } while (0);
   do {
      unsigned char *read_00589;
      unsigned int read_00589_len;
      unsigned int read_00589_ptr = 0;
      //**** delimited read
      static unsigned char read_00589_delim[] = 
         "\x0a";
      read_00589 = NULL;
      read_00589_len = 0;
      int read_00589_res = cgc_delimited_read(0, &read_00589, &read_00589_len, read_00589_delim, 1);
      if (read_00589_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00589_00000[] = 
         "\x44\x69\x73\x74\x61\x6e\x63\x65\x20\x74\x6f\x20\x6e\x65\x78\x74"
         "\x0a";
      read_00589_ptr += cgc_data_match(read_00589 + read_00589_ptr, read_00589_len - read_00589_ptr, match_00589_00000, 17);
      cgc_free(read_00589);
      if (read_00589_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00380_00000[] = 
         "\x31\x0a";
      static unsigned int write_00380_00000_len = 2;
      unsigned char *write_00380 = NULL;
      unsigned int write_00380_len = 0;
      write_00380 = cgc_append_buf(write_00380, &write_00380_len, write_00380_00000, write_00380_00000_len);
      if (write_00380_len > 0) {
         cgc_transmit_all(1, write_00380, write_00380_len);
      }
      cgc_free(write_00380);
   } while (0);
   do {
      unsigned char *read_00590;
      unsigned int read_00590_len;
      unsigned int read_00590_ptr = 0;
      //**** delimited read
      static unsigned char read_00590_delim[] = 
         "\x0a";
      read_00590 = NULL;
      read_00590_len = 0;
      int read_00590_res = cgc_delimited_read(0, &read_00590, &read_00590_len, read_00590_delim, 1);
      if (read_00590_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00590_00000[] = 
         "\x50\x72\x65\x76\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f"
         "\x6e\x20\x6f\x6e\x20\x72\x6f\x61\x64\x20\x32\x2e\x0a";
      read_00590_ptr += cgc_data_match(read_00590 + read_00590_ptr, read_00590_len - read_00590_ptr, match_00590_00000, 29);
      cgc_free(read_00590);
      if (read_00590_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00591;
      unsigned int read_00591_len;
      unsigned int read_00591_ptr = 0;
      //**** delimited read
      static unsigned char read_00591_delim[] = 
         "\x0a";
      read_00591 = NULL;
      read_00591_len = 0;
      int read_00591_res = cgc_delimited_read(0, &read_00591, &read_00591_len, read_00591_delim, 1);
      if (read_00591_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00591_00000[] = 
         "\x54\x68\x69\x73\x20\x72\x6f\x61\x64\x20\x68\x61\x73\x20\x6e\x6f"
         "\x20\x69\x6e\x74\x65\x72\x73\x65\x63\x74\x69\x6f\x6e\x73\x20\x74"
         "\x6f\x20\x63\x68\x6f\x6f\x73\x65\x2e\x0a";
      read_00591_ptr += cgc_data_match(read_00591 + read_00591_ptr, read_00591_len - read_00591_ptr, match_00591_00000, 42);
      cgc_free(read_00591);
      if (read_00591_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00592;
      unsigned int read_00592_len;
      unsigned int read_00592_ptr = 0;
      //**** delimited read
      static unsigned char read_00592_delim[] = 
         "\x0a";
      read_00592 = NULL;
      read_00592_len = 0;
      int read_00592_res = cgc_delimited_read(0, &read_00592, &read_00592_len, read_00592_delim, 1);
      if (read_00592_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00592_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00592_ptr += cgc_data_match(read_00592 + read_00592_ptr, read_00592_len - read_00592_ptr, match_00592_00000, 8);
      cgc_free(read_00592);
      if (read_00592_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00381_00000[] = 
         "\x49\x0a";
      static unsigned int write_00381_00000_len = 2;
      unsigned char *write_00381 = NULL;
      unsigned int write_00381_len = 0;
      write_00381 = cgc_append_buf(write_00381, &write_00381_len, write_00381_00000, write_00381_00000_len);
      if (write_00381_len > 0) {
         cgc_transmit_all(1, write_00381, write_00381_len);
      }
      cgc_free(write_00381);
   } while (0);
   do {
      unsigned char *read_00593;
      unsigned int read_00593_len;
      unsigned int read_00593_ptr = 0;
      //**** delimited read
      static unsigned char read_00593_delim[] = 
         "\x0a";
      read_00593 = NULL;
      read_00593_len = 0;
      int read_00593_res = cgc_delimited_read(0, &read_00593, &read_00593_len, read_00593_delim, 1);
      if (read_00593_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00593_00000[] = 
         "\x66\x72\x6f\x6d\x20\x61\x64\x64\x72\x65\x73\x73\x20\x0a";
      read_00593_ptr += cgc_data_match(read_00593 + read_00593_ptr, read_00593_len - read_00593_ptr, match_00593_00000, 14);
      cgc_free(read_00593);
      if (read_00593_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00594;
      unsigned int read_00594_len;
      unsigned int read_00594_ptr = 0;
      //**** delimited read
      static unsigned char read_00594_delim[] = 
         "\x0a";
      read_00594 = NULL;
      read_00594_len = 0;
      int read_00594_res = cgc_delimited_read(0, &read_00594, &read_00594_len, read_00594_delim, 1);
      if (read_00594_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00594_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00594_ptr += cgc_data_match(read_00594 + read_00594_ptr, read_00594_len - read_00594_ptr, match_00594_00000, 47);
      cgc_free(read_00594);
      if (read_00594_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00595;
      unsigned int read_00595_len;
      unsigned int read_00595_ptr = 0;
      //**** delimited read
      static unsigned char read_00595_delim[] = 
         "\x0a";
      read_00595 = NULL;
      read_00595_len = 0;
      int read_00595_res = cgc_delimited_read(0, &read_00595, &read_00595_len, read_00595_delim, 1);
      if (read_00595_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00595_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00595_ptr += cgc_data_match(read_00595 + read_00595_ptr, read_00595_len - read_00595_ptr, match_00595_00000, 8);
      cgc_free(read_00595);
      if (read_00595_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00382_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00382_00000_len = 2;
      unsigned char *write_00382 = NULL;
      unsigned int write_00382_len = 0;
      write_00382 = cgc_append_buf(write_00382, &write_00382_len, write_00382_00000, write_00382_00000_len);
      if (write_00382_len > 0) {
         cgc_transmit_all(1, write_00382, write_00382_len);
      }
      cgc_free(write_00382);
   } while (0);
   do {
      unsigned char *read_00596;
      unsigned int read_00596_len;
      unsigned int read_00596_ptr = 0;
      //**** delimited read
      static unsigned char read_00596_delim[] = 
         "\x0a";
      read_00596 = NULL;
      read_00596_len = 0;
      int read_00596_res = cgc_delimited_read(0, &read_00596, &read_00596_len, read_00596_delim, 1);
      if (read_00596_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00596_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00596_ptr += cgc_data_match(read_00596 + read_00596_ptr, read_00596_len - read_00596_ptr, match_00596_00000, 6);
      cgc_free(read_00596);
      if (read_00596_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00383_00000[] = 
         "\x31\x0a";
      static unsigned int write_00383_00000_len = 2;
      unsigned char *write_00383 = NULL;
      unsigned int write_00383_len = 0;
      write_00383 = cgc_append_buf(write_00383, &write_00383_len, write_00383_00000, write_00383_00000_len);
      if (write_00383_len > 0) {
         cgc_transmit_all(1, write_00383, write_00383_len);
      }
      cgc_free(write_00383);
   } while (0);
   do {
      unsigned char *read_00597;
      unsigned int read_00597_len;
      unsigned int read_00597_ptr = 0;
      //**** delimited read
      static unsigned char read_00597_delim[] = 
         "\x0a";
      read_00597 = NULL;
      read_00597_len = 0;
      int read_00597_res = cgc_delimited_read(0, &read_00597, &read_00597_len, read_00597_delim, 1);
      if (read_00597_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00597_00000[] = 
         "\x4f\x6e\x6c\x79\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x6e\x20"
         "\x72\x6f\x61\x64\x20\x77\x61\x73\x20\x73\x65\x6c\x65\x63\x74\x65"
         "\x64\x0a";
      read_00597_ptr += cgc_data_match(read_00597 + read_00597_ptr, read_00597_len - read_00597_ptr, match_00597_00000, 34);
      cgc_free(read_00597);
      if (read_00597_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00598;
      unsigned int read_00598_len;
      unsigned int read_00598_ptr = 0;
      //**** delimited read
      static unsigned char read_00598_delim[] = 
         "\x0a";
      read_00598 = NULL;
      read_00598_len = 0;
      int read_00598_res = cgc_delimited_read(0, &read_00598, &read_00598_len, read_00598_delim, 1);
      if (read_00598_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00598_00000[] = 
         "\x74\x6f\x20\x61\x64\x64\x72\x65\x73\x73\x20\x0a";
      read_00598_ptr += cgc_data_match(read_00598 + read_00598_ptr, read_00598_len - read_00598_ptr, match_00598_00000, 12);
      cgc_free(read_00598);
      if (read_00598_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00599;
      unsigned int read_00599_len;
      unsigned int read_00599_ptr = 0;
      //**** delimited read
      static unsigned char read_00599_delim[] = 
         "\x0a";
      read_00599 = NULL;
      read_00599_len = 0;
      int read_00599_res = cgc_delimited_read(0, &read_00599, &read_00599_len, read_00599_delim, 1);
      if (read_00599_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00599_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x52\x6f\x61\x64\x20\x62\x79\x20\x28"
         "\x4e\x29\x75\x6d\x62\x65\x72\x2c\x20\x6f\x72\x20\x28\x4c\x29\x69"
         "\x73\x74\x20\x6f\x72\x20\x28\x30\x29\x45\x78\x69\x74\x2e\x0a";
      read_00599_ptr += cgc_data_match(read_00599 + read_00599_ptr, read_00599_len - read_00599_ptr, match_00599_00000, 47);
      cgc_free(read_00599);
      if (read_00599_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00600;
      unsigned int read_00600_len;
      unsigned int read_00600_ptr = 0;
      //**** delimited read
      static unsigned char read_00600_delim[] = 
         "\x0a";
      read_00600 = NULL;
      read_00600_len = 0;
      int read_00600_res = cgc_delimited_read(0, &read_00600, &read_00600_len, read_00600_delim, 1);
      if (read_00600_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00600_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00600_ptr += cgc_data_match(read_00600 + read_00600_ptr, read_00600_len - read_00600_ptr, match_00600_00000, 8);
      cgc_free(read_00600);
      if (read_00600_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00384_00000[] = 
         "\x4e\x0a";
      static unsigned int write_00384_00000_len = 2;
      unsigned char *write_00384 = NULL;
      unsigned int write_00384_len = 0;
      write_00384 = cgc_append_buf(write_00384, &write_00384_len, write_00384_00000, write_00384_00000_len);
      if (write_00384_len > 0) {
         cgc_transmit_all(1, write_00384, write_00384_len);
      }
      cgc_free(write_00384);
   } while (0);
   do {
      unsigned char *read_00601;
      unsigned int read_00601_len;
      unsigned int read_00601_ptr = 0;
      //**** delimited read
      static unsigned char read_00601_delim[] = 
         "\x0a";
      read_00601 = NULL;
      read_00601_len = 0;
      int read_00601_res = cgc_delimited_read(0, &read_00601, &read_00601_len, read_00601_delim, 1);
      if (read_00601_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00601_00000[] = 
         "\x31\x2d\x34\x35\x3a\x0a";
      read_00601_ptr += cgc_data_match(read_00601 + read_00601_ptr, read_00601_len - read_00601_ptr, match_00601_00000, 6);
      cgc_free(read_00601);
      if (read_00601_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00385_00000[] = 
         "\x33\x34\x0a";
      static unsigned int write_00385_00000_len = 3;
      unsigned char *write_00385 = NULL;
      unsigned int write_00385_len = 0;
      write_00385 = cgc_append_buf(write_00385, &write_00385_len, write_00385_00000, write_00385_00000_len);
      if (write_00385_len > 0) {
         cgc_transmit_all(1, write_00385, write_00385_len);
      }
      cgc_free(write_00385);
   } while (0);
   do {
      unsigned char *read_00602;
      unsigned int read_00602_len;
      unsigned int read_00602_ptr = 0;
      //**** delimited read
      static unsigned char read_00602_delim[] = 
         "\x0a";
      read_00602 = NULL;
      read_00602_len = 0;
      int read_00602_res = cgc_delimited_read(0, &read_00602, &read_00602_len, read_00602_delim, 1);
      if (read_00602_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00602_00000[] = 
         "\x4f\x6e\x6c\x79\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x6e\x20"
         "\x72\x6f\x61\x64\x20\x77\x61\x73\x20\x73\x65\x6c\x65\x63\x74\x65"
         "\x64\x0a";
      read_00602_ptr += cgc_data_match(read_00602 + read_00602_ptr, read_00602_len - read_00602_ptr, match_00602_00000, 34);
      cgc_free(read_00602);
      if (read_00602_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00603;
      unsigned int read_00603_len;
      unsigned int read_00603_ptr = 0;
      //**** delimited read
      static unsigned char read_00603_delim[] = 
         "\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23"
         "\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x0a";
      read_00603 = NULL;
      read_00603_len = 0;
      int read_00603_res = cgc_delimited_read(0, &read_00603, &read_00603_len, read_00603_delim, 30);
      if (read_00603_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00603_00000[] = 
         "\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23"
         "\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x0a";
      read_00603_ptr += cgc_data_match(read_00603 + read_00603_ptr, read_00603_len - read_00603_ptr, match_00603_00000, 30);
      cgc_free(read_00603);
      if (read_00603_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00604;
      unsigned int read_00604_len;
      unsigned int read_00604_ptr = 0;
      //**** delimited read
      static unsigned char read_00604_delim[] = 
         "\x0a";
      read_00604 = NULL;
      read_00604_len = 0;
      int read_00604_res = cgc_delimited_read(0, &read_00604, &read_00604_len, read_00604_delim, 1);
      if (read_00604_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00604_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00604_ptr += cgc_data_match(read_00604 + read_00604_ptr, read_00604_len - read_00604_ptr, match_00604_00000, 8);
      cgc_free(read_00604);
      if (read_00604_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00386_00000[] = 
         "\x45\x0a";
      static unsigned int write_00386_00000_len = 2;
      unsigned char *write_00386 = NULL;
      unsigned int write_00386_len = 0;
      write_00386 = cgc_append_buf(write_00386, &write_00386_len, write_00386_00000, write_00386_00000_len);
      if (write_00386_len > 0) {
         cgc_transmit_all(1, write_00386, write_00386_len);
      }
      cgc_free(write_00386);
   } while (0);
   do {
      unsigned char *read_00605;
      unsigned int read_00605_len;
      unsigned int read_00605_ptr = 0;
      //**** delimited read
      static unsigned char read_00605_delim[] = 
         "\x0a";
      read_00605 = NULL;
      read_00605_len = 0;
      int read_00605_res = cgc_delimited_read(0, &read_00605, &read_00605_len, read_00605_delim, 1);
      if (read_00605_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00605_00000[] = 
         "\x0a";
      read_00605_ptr += cgc_data_match(read_00605 + read_00605_ptr, read_00605_len - read_00605_ptr, match_00605_00000, 1);
      cgc_free(read_00605);
      if (read_00605_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00387_00000[] = 
         "\x30\x0a";
      static unsigned int write_00387_00000_len = 2;
      unsigned char *write_00387 = NULL;
      unsigned int write_00387_len = 0;
      write_00387 = cgc_append_buf(write_00387, &write_00387_len, write_00387_00000, write_00387_00000_len);
      if (write_00387_len > 0) {
         cgc_transmit_all(1, write_00387, write_00387_len);
      }
      cgc_free(write_00387);
   } while (0);
   do {
      unsigned char *read_00606;
      unsigned int read_00606_len;
      unsigned int read_00606_ptr = 0;
      //**** delimited read
      static unsigned char read_00606_delim[] = 
         "\x0a";
      read_00606 = NULL;
      read_00606_len = 0;
      int read_00606_res = cgc_delimited_read(0, &read_00606, &read_00606_len, read_00606_delim, 1);
      if (read_00606_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00606_00000[] = 
         "\x0a";
      read_00606_ptr += cgc_data_match(read_00606 + read_00606_ptr, read_00606_len - read_00606_ptr, match_00606_00000, 1);
      cgc_free(read_00606);
      if (read_00606_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00607;
      unsigned int read_00607_len;
      unsigned int read_00607_ptr = 0;
      //**** delimited read
      static unsigned char read_00607_delim[] = 
         "\x0a";
      read_00607 = NULL;
      read_00607_len = 0;
      int read_00607_res = cgc_delimited_read(0, &read_00607, &read_00607_len, read_00607_delim, 1);
      if (read_00607_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00607_00000[] = 
         "\x0a";
      read_00607_ptr += cgc_data_match(read_00607 + read_00607_ptr, read_00607_len - read_00607_ptr, match_00607_00000, 1);
      cgc_free(read_00607);
      if (read_00607_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00608;
      unsigned int read_00608_len;
      unsigned int read_00608_ptr = 0;
      //**** delimited read
      static unsigned char read_00608_delim[] = 
         "\x0a";
      read_00608 = NULL;
      read_00608_len = 0;
      int read_00608_res = cgc_delimited_read(0, &read_00608, &read_00608_len, read_00608_delim, 1);
      if (read_00608_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00608_00000[] = 
         "\x0a";
      read_00608_ptr += cgc_data_match(read_00608 + read_00608_ptr, read_00608_len - read_00608_ptr, match_00608_00000, 1);
      cgc_free(read_00608);
      if (read_00608_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00609;
      unsigned int read_00609_len;
      unsigned int read_00609_ptr = 0;
      //**** delimited read
      static unsigned char read_00609_delim[] = 
         "\x0a";
      read_00609 = NULL;
      read_00609_len = 0;
      int read_00609_res = cgc_delimited_read(0, &read_00609, &read_00609_len, read_00609_delim, 1);
      if (read_00609_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00609_00000[] = 
         "\x0a";
      read_00609_ptr += cgc_data_match(read_00609 + read_00609_ptr, read_00609_len - read_00609_ptr, match_00609_00000, 1);
      cgc_free(read_00609);
      if (read_00609_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00610;
      unsigned int read_00610_len;
      unsigned int read_00610_ptr = 0;
      //**** delimited read
      static unsigned char read_00610_delim[] = 
         "\x0a";
      read_00610 = NULL;
      read_00610_len = 0;
      int read_00610_res = cgc_delimited_read(0, &read_00610, &read_00610_len, read_00610_delim, 1);
      if (read_00610_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00610_00000[] = 
         "\x0a";
      read_00610_ptr += cgc_data_match(read_00610 + read_00610_ptr, read_00610_len - read_00610_ptr, match_00610_00000, 1);
      cgc_free(read_00610);
      if (read_00610_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00611;
      unsigned int read_00611_len;
      unsigned int read_00611_ptr = 0;
      //**** delimited read
      static unsigned char read_00611_delim[] = 
         "\x0a";
      read_00611 = NULL;
      read_00611_len = 0;
      int read_00611_res = cgc_delimited_read(0, &read_00611, &read_00611_len, read_00611_delim, 1);
      if (read_00611_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00611_00000[] = 
         "\x0a";
      read_00611_ptr += cgc_data_match(read_00611 + read_00611_ptr, read_00611_len - read_00611_ptr, match_00611_00000, 1);
      cgc_free(read_00611);
      if (read_00611_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00612;
      unsigned int read_00612_len;
      unsigned int read_00612_ptr = 0;
      //**** delimited read
      static unsigned char read_00612_delim[] = 
         "\x0a";
      read_00612 = NULL;
      read_00612_len = 0;
      int read_00612_res = cgc_delimited_read(0, &read_00612, &read_00612_len, read_00612_delim, 1);
      if (read_00612_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00612_00000[] = 
         "\x0a";
      read_00612_ptr += cgc_data_match(read_00612 + read_00612_ptr, read_00612_len - read_00612_ptr, match_00612_00000, 1);
      cgc_free(read_00612);
      if (read_00612_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00613;
      unsigned int read_00613_len;
      unsigned int read_00613_ptr = 0;
      //**** delimited read
      static unsigned char read_00613_delim[] = 
         "\x0a";
      read_00613 = NULL;
      read_00613_len = 0;
      int read_00613_res = cgc_delimited_read(0, &read_00613, &read_00613_len, read_00613_delim, 1);
      if (read_00613_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00613_00000[] = 
         "\x0a";
      read_00613_ptr += cgc_data_match(read_00613 + read_00613_ptr, read_00613_len - read_00613_ptr, match_00613_00000, 1);
      cgc_free(read_00613);
      if (read_00613_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00614;
      unsigned int read_00614_len;
      unsigned int read_00614_ptr = 0;
      //**** delimited read
      static unsigned char read_00614_delim[] = 
         "\x0a";
      read_00614 = NULL;
      read_00614_len = 0;
      int read_00614_res = cgc_delimited_read(0, &read_00614, &read_00614_len, read_00614_delim, 1);
      if (read_00614_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00614_00000[] = 
         "\x0a";
      read_00614_ptr += cgc_data_match(read_00614 + read_00614_ptr, read_00614_len - read_00614_ptr, match_00614_00000, 1);
      cgc_free(read_00614);
      if (read_00614_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00615;
      unsigned int read_00615_len;
      unsigned int read_00615_ptr = 0;
      //**** delimited read
      static unsigned char read_00615_delim[] = 
         "\x0a";
      read_00615 = NULL;
      read_00615_len = 0;
      int read_00615_res = cgc_delimited_read(0, &read_00615, &read_00615_len, read_00615_delim, 1);
      if (read_00615_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00615_00000[] = 
         "\x0a";
      read_00615_ptr += cgc_data_match(read_00615 + read_00615_ptr, read_00615_len - read_00615_ptr, match_00615_00000, 1);
      cgc_free(read_00615);
      if (read_00615_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00616;
      unsigned int read_00616_len;
      unsigned int read_00616_ptr = 0;
      //**** delimited read
      static unsigned char read_00616_delim[] = 
         "\x0a";
      read_00616 = NULL;
      read_00616_len = 0;
      int read_00616_res = cgc_delimited_read(0, &read_00616, &read_00616_len, read_00616_delim, 1);
      if (read_00616_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00616_00000[] = 
         "\x0a";
      read_00616_ptr += cgc_data_match(read_00616 + read_00616_ptr, read_00616_len - read_00616_ptr, match_00616_00000, 1);
      cgc_free(read_00616);
      if (read_00616_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00617;
      unsigned int read_00617_len;
      unsigned int read_00617_ptr = 0;
      //**** delimited read
      static unsigned char read_00617_delim[] = 
         "\x0a";
      read_00617 = NULL;
      read_00617_len = 0;
      int read_00617_res = cgc_delimited_read(0, &read_00617, &read_00617_len, read_00617_delim, 1);
      if (read_00617_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00617_00000[] = 
         "\x0a";
      read_00617_ptr += cgc_data_match(read_00617 + read_00617_ptr, read_00617_len - read_00617_ptr, match_00617_00000, 1);
      cgc_free(read_00617);
      if (read_00617_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00618;
      unsigned int read_00618_len;
      unsigned int read_00618_ptr = 0;
      //**** delimited read
      static unsigned char read_00618_delim[] = 
         "\x0a";
      read_00618 = NULL;
      read_00618_len = 0;
      int read_00618_res = cgc_delimited_read(0, &read_00618, &read_00618_len, read_00618_delim, 1);
      if (read_00618_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00618_00000[] = 
         "\x0a";
      read_00618_ptr += cgc_data_match(read_00618 + read_00618_ptr, read_00618_len - read_00618_ptr, match_00618_00000, 1);
      cgc_free(read_00618);
      if (read_00618_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00619;
      unsigned int read_00619_len;
      unsigned int read_00619_ptr = 0;
      //**** delimited read
      static unsigned char read_00619_delim[] = 
         "\x0a";
      read_00619 = NULL;
      read_00619_len = 0;
      int read_00619_res = cgc_delimited_read(0, &read_00619, &read_00619_len, read_00619_delim, 1);
      if (read_00619_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00619_00000[] = 
         "\x0a";
      read_00619_ptr += cgc_data_match(read_00619 + read_00619_ptr, read_00619_len - read_00619_ptr, match_00619_00000, 1);
      cgc_free(read_00619);
      if (read_00619_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00620;
      unsigned int read_00620_len;
      unsigned int read_00620_ptr = 0;
      //**** delimited read
      static unsigned char read_00620_delim[] = 
         "\x0a";
      read_00620 = NULL;
      read_00620_len = 0;
      int read_00620_res = cgc_delimited_read(0, &read_00620, &read_00620_len, read_00620_delim, 1);
      if (read_00620_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00620_00000[] = 
         "\x0a";
      read_00620_ptr += cgc_data_match(read_00620 + read_00620_ptr, read_00620_len - read_00620_ptr, match_00620_00000, 1);
      cgc_free(read_00620);
      if (read_00620_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00621;
      unsigned int read_00621_len;
      unsigned int read_00621_ptr = 0;
      //**** delimited read
      static unsigned char read_00621_delim[] = 
         "\x0a";
      read_00621 = NULL;
      read_00621_len = 0;
      int read_00621_res = cgc_delimited_read(0, &read_00621, &read_00621_len, read_00621_delim, 1);
      if (read_00621_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00621_00000[] = 
         "\x0a";
      read_00621_ptr += cgc_data_match(read_00621 + read_00621_ptr, read_00621_len - read_00621_ptr, match_00621_00000, 1);
      cgc_free(read_00621);
      if (read_00621_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00622;
      unsigned int read_00622_len;
      unsigned int read_00622_ptr = 0;
      //**** delimited read
      static unsigned char read_00622_delim[] = 
         "\x0a";
      read_00622 = NULL;
      read_00622_len = 0;
      int read_00622_res = cgc_delimited_read(0, &read_00622, &read_00622_len, read_00622_delim, 1);
      if (read_00622_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00622_00000[] = 
         "\x0a";
      read_00622_ptr += cgc_data_match(read_00622 + read_00622_ptr, read_00622_len - read_00622_ptr, match_00622_00000, 1);
      cgc_free(read_00622);
      if (read_00622_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00623;
      unsigned int read_00623_len;
      unsigned int read_00623_ptr = 0;
      //**** delimited read
      static unsigned char read_00623_delim[] = 
         "\x0a";
      read_00623 = NULL;
      read_00623_len = 0;
      int read_00623_res = cgc_delimited_read(0, &read_00623, &read_00623_len, read_00623_delim, 1);
      if (read_00623_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00623_00000[] = 
         "\x0a";
      read_00623_ptr += cgc_data_match(read_00623 + read_00623_ptr, read_00623_len - read_00623_ptr, match_00623_00000, 1);
      cgc_free(read_00623);
      if (read_00623_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00624;
      unsigned int read_00624_len;
      unsigned int read_00624_ptr = 0;
      //**** delimited read
      static unsigned char read_00624_delim[] = 
         "\x0a";
      read_00624 = NULL;
      read_00624_len = 0;
      int read_00624_res = cgc_delimited_read(0, &read_00624, &read_00624_len, read_00624_delim, 1);
      if (read_00624_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00624_00000[] = 
         "\x0a";
      read_00624_ptr += cgc_data_match(read_00624 + read_00624_ptr, read_00624_len - read_00624_ptr, match_00624_00000, 1);
      cgc_free(read_00624);
      if (read_00624_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00625;
      unsigned int read_00625_len;
      unsigned int read_00625_ptr = 0;
      //**** delimited read
      static unsigned char read_00625_delim[] = 
         "\x0a";
      read_00625 = NULL;
      read_00625_len = 0;
      int read_00625_res = cgc_delimited_read(0, &read_00625, &read_00625_len, read_00625_delim, 1);
      if (read_00625_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00625_00000[] = 
         "\x0a";
      read_00625_ptr += cgc_data_match(read_00625 + read_00625_ptr, read_00625_len - read_00625_ptr, match_00625_00000, 1);
      cgc_free(read_00625);
      if (read_00625_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00626;
      unsigned int read_00626_len;
      unsigned int read_00626_ptr = 0;
      //**** delimited read
      static unsigned char read_00626_delim[] = 
         "\x0a";
      read_00626 = NULL;
      read_00626_len = 0;
      int read_00626_res = cgc_delimited_read(0, &read_00626, &read_00626_len, read_00626_delim, 1);
      if (read_00626_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00626_00000[] = 
         "\x0a";
      read_00626_ptr += cgc_data_match(read_00626 + read_00626_ptr, read_00626_len - read_00626_ptr, match_00626_00000, 1);
      cgc_free(read_00626);
      if (read_00626_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00627;
      unsigned int read_00627_len;
      unsigned int read_00627_ptr = 0;
      //**** delimited read
      static unsigned char read_00627_delim[] = 
         "\x0a";
      read_00627 = NULL;
      read_00627_len = 0;
      int read_00627_res = cgc_delimited_read(0, &read_00627, &read_00627_len, read_00627_delim, 1);
      if (read_00627_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00627_00000[] = 
         "\x0a";
      read_00627_ptr += cgc_data_match(read_00627 + read_00627_ptr, read_00627_len - read_00627_ptr, match_00627_00000, 1);
      cgc_free(read_00627);
      if (read_00627_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00628;
      unsigned int read_00628_len;
      unsigned int read_00628_ptr = 0;
      //**** delimited read
      static unsigned char read_00628_delim[] = 
         "\x0a";
      read_00628 = NULL;
      read_00628_len = 0;
      int read_00628_res = cgc_delimited_read(0, &read_00628, &read_00628_len, read_00628_delim, 1);
      if (read_00628_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00628_00000[] = 
         "\x0a";
      read_00628_ptr += cgc_data_match(read_00628 + read_00628_ptr, read_00628_len - read_00628_ptr, match_00628_00000, 1);
      cgc_free(read_00628);
      if (read_00628_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00629;
      unsigned int read_00629_len;
      unsigned int read_00629_ptr = 0;
      //**** delimited read
      static unsigned char read_00629_delim[] = 
         "\x0a";
      read_00629 = NULL;
      read_00629_len = 0;
      int read_00629_res = cgc_delimited_read(0, &read_00629, &read_00629_len, read_00629_delim, 1);
      if (read_00629_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00629_00000[] = 
         "\x0a";
      read_00629_ptr += cgc_data_match(read_00629 + read_00629_ptr, read_00629_len - read_00629_ptr, match_00629_00000, 1);
      cgc_free(read_00629);
      if (read_00629_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00630;
      unsigned int read_00630_len;
      unsigned int read_00630_ptr = 0;
      //**** delimited read
      static unsigned char read_00630_delim[] = 
         "\x0a";
      read_00630 = NULL;
      read_00630_len = 0;
      int read_00630_res = cgc_delimited_read(0, &read_00630, &read_00630_len, read_00630_delim, 1);
      if (read_00630_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00630_00000[] = 
         "\x0a";
      read_00630_ptr += cgc_data_match(read_00630 + read_00630_ptr, read_00630_len - read_00630_ptr, match_00630_00000, 1);
      cgc_free(read_00630);
      if (read_00630_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00631;
      unsigned int read_00631_len;
      unsigned int read_00631_ptr = 0;
      //**** delimited read
      static unsigned char read_00631_delim[] = 
         "\x0a";
      read_00631 = NULL;
      read_00631_len = 0;
      int read_00631_res = cgc_delimited_read(0, &read_00631, &read_00631_len, read_00631_delim, 1);
      if (read_00631_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00631_00000[] = 
         "\x0a";
      read_00631_ptr += cgc_data_match(read_00631 + read_00631_ptr, read_00631_len - read_00631_ptr, match_00631_00000, 1);
      cgc_free(read_00631);
      if (read_00631_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00632;
      unsigned int read_00632_len;
      unsigned int read_00632_ptr = 0;
      //**** delimited read
      static unsigned char read_00632_delim[] = 
         "\x0a";
      read_00632 = NULL;
      read_00632_len = 0;
      int read_00632_res = cgc_delimited_read(0, &read_00632, &read_00632_len, read_00632_delim, 1);
      if (read_00632_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00632_00000[] = 
         "\x0a";
      read_00632_ptr += cgc_data_match(read_00632 + read_00632_ptr, read_00632_len - read_00632_ptr, match_00632_00000, 1);
      cgc_free(read_00632);
      if (read_00632_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00633;
      unsigned int read_00633_len;
      unsigned int read_00633_ptr = 0;
      //**** delimited read
      static unsigned char read_00633_delim[] = 
         "\x0a";
      read_00633 = NULL;
      read_00633_len = 0;
      int read_00633_res = cgc_delimited_read(0, &read_00633, &read_00633_len, read_00633_delim, 1);
      if (read_00633_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00633_00000[] = 
         "\x0a";
      read_00633_ptr += cgc_data_match(read_00633 + read_00633_ptr, read_00633_len - read_00633_ptr, match_00633_00000, 1);
      cgc_free(read_00633);
      if (read_00633_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00634;
      unsigned int read_00634_len;
      unsigned int read_00634_ptr = 0;
      //**** delimited read
      static unsigned char read_00634_delim[] = 
         "\x0a";
      read_00634 = NULL;
      read_00634_len = 0;
      int read_00634_res = cgc_delimited_read(0, &read_00634, &read_00634_len, read_00634_delim, 1);
      if (read_00634_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00634_00000[] = 
         "\x0a";
      read_00634_ptr += cgc_data_match(read_00634 + read_00634_ptr, read_00634_len - read_00634_ptr, match_00634_00000, 1);
      cgc_free(read_00634);
      if (read_00634_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00635;
      unsigned int read_00635_len;
      unsigned int read_00635_ptr = 0;
      //**** delimited read
      static unsigned char read_00635_delim[] = 
         "\x0a";
      read_00635 = NULL;
      read_00635_len = 0;
      int read_00635_res = cgc_delimited_read(0, &read_00635, &read_00635_len, read_00635_delim, 1);
      if (read_00635_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00635_00000[] = 
         "\x0a";
      read_00635_ptr += cgc_data_match(read_00635 + read_00635_ptr, read_00635_len - read_00635_ptr, match_00635_00000, 1);
      cgc_free(read_00635);
      if (read_00635_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00636;
      unsigned int read_00636_len;
      unsigned int read_00636_ptr = 0;
      //**** delimited read
      static unsigned char read_00636_delim[] = 
         "\x0a";
      read_00636 = NULL;
      read_00636_len = 0;
      int read_00636_res = cgc_delimited_read(0, &read_00636, &read_00636_len, read_00636_delim, 1);
      if (read_00636_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00636_00000[] = 
         "\x0a";
      read_00636_ptr += cgc_data_match(read_00636 + read_00636_ptr, read_00636_len - read_00636_ptr, match_00636_00000, 1);
      cgc_free(read_00636);
      if (read_00636_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00637;
      unsigned int read_00637_len;
      unsigned int read_00637_ptr = 0;
      //**** delimited read
      static unsigned char read_00637_delim[] = 
         "\x0a";
      read_00637 = NULL;
      read_00637_len = 0;
      int read_00637_res = cgc_delimited_read(0, &read_00637, &read_00637_len, read_00637_delim, 1);
      if (read_00637_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00637_00000[] = 
         "\x0a";
      read_00637_ptr += cgc_data_match(read_00637 + read_00637_ptr, read_00637_len - read_00637_ptr, match_00637_00000, 1);
      cgc_free(read_00637);
      if (read_00637_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00638;
      unsigned int read_00638_len;
      unsigned int read_00638_ptr = 0;
      //**** delimited read
      static unsigned char read_00638_delim[] = 
         "\x0a";
      read_00638 = NULL;
      read_00638_len = 0;
      int read_00638_res = cgc_delimited_read(0, &read_00638, &read_00638_len, read_00638_delim, 1);
      if (read_00638_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00638_00000[] = 
         "\x0a";
      read_00638_ptr += cgc_data_match(read_00638 + read_00638_ptr, read_00638_len - read_00638_ptr, match_00638_00000, 1);
      cgc_free(read_00638);
      if (read_00638_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00639;
      unsigned int read_00639_len;
      unsigned int read_00639_ptr = 0;
      //**** delimited read
      static unsigned char read_00639_delim[] = 
         "\x0a";
      read_00639 = NULL;
      read_00639_len = 0;
      int read_00639_res = cgc_delimited_read(0, &read_00639, &read_00639_len, read_00639_delim, 1);
      if (read_00639_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00639_00000[] = 
         "\x0a";
      read_00639_ptr += cgc_data_match(read_00639 + read_00639_ptr, read_00639_len - read_00639_ptr, match_00639_00000, 1);
      cgc_free(read_00639);
      if (read_00639_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00640;
      unsigned int read_00640_len;
      unsigned int read_00640_ptr = 0;
      //**** delimited read
      static unsigned char read_00640_delim[] = 
         "\x0a";
      read_00640 = NULL;
      read_00640_len = 0;
      int read_00640_res = cgc_delimited_read(0, &read_00640, &read_00640_len, read_00640_delim, 1);
      if (read_00640_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00640_00000[] = 
         "\x0a";
      read_00640_ptr += cgc_data_match(read_00640 + read_00640_ptr, read_00640_len - read_00640_ptr, match_00640_00000, 1);
      cgc_free(read_00640);
      if (read_00640_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00641;
      unsigned int read_00641_len;
      unsigned int read_00641_ptr = 0;
      //**** delimited read
      static unsigned char read_00641_delim[] = 
         "\x0a";
      read_00641 = NULL;
      read_00641_len = 0;
      int read_00641_res = cgc_delimited_read(0, &read_00641, &read_00641_len, read_00641_delim, 1);
      if (read_00641_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00641_00000[] = 
         "\x0a";
      read_00641_ptr += cgc_data_match(read_00641 + read_00641_ptr, read_00641_len - read_00641_ptr, match_00641_00000, 1);
      cgc_free(read_00641);
      if (read_00641_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00642;
      unsigned int read_00642_len;
      unsigned int read_00642_ptr = 0;
      //**** delimited read
      static unsigned char read_00642_delim[] = 
         "\x0a";
      read_00642 = NULL;
      read_00642_len = 0;
      int read_00642_res = cgc_delimited_read(0, &read_00642, &read_00642_len, read_00642_delim, 1);
      if (read_00642_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00642_00000[] = 
         "\x0a";
      read_00642_ptr += cgc_data_match(read_00642 + read_00642_ptr, read_00642_len - read_00642_ptr, match_00642_00000, 1);
      cgc_free(read_00642);
      if (read_00642_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00643;
      unsigned int read_00643_len;
      unsigned int read_00643_ptr = 0;
      //**** delimited read
      static unsigned char read_00643_delim[] = 
         "\x0a";
      read_00643 = NULL;
      read_00643_len = 0;
      int read_00643_res = cgc_delimited_read(0, &read_00643, &read_00643_len, read_00643_delim, 1);
      if (read_00643_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00643_00000[] = 
         "\x0a";
      read_00643_ptr += cgc_data_match(read_00643 + read_00643_ptr, read_00643_len - read_00643_ptr, match_00643_00000, 1);
      cgc_free(read_00643);
      if (read_00643_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00644;
      unsigned int read_00644_len;
      unsigned int read_00644_ptr = 0;
      //**** delimited read
      static unsigned char read_00644_delim[] = 
         "\x0a";
      read_00644 = NULL;
      read_00644_len = 0;
      int read_00644_res = cgc_delimited_read(0, &read_00644, &read_00644_len, read_00644_delim, 1);
      if (read_00644_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00644_00000[] = 
         "\x0a";
      read_00644_ptr += cgc_data_match(read_00644 + read_00644_ptr, read_00644_len - read_00644_ptr, match_00644_00000, 1);
      cgc_free(read_00644);
      if (read_00644_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00645;
      unsigned int read_00645_len;
      unsigned int read_00645_ptr = 0;
      //**** delimited read
      static unsigned char read_00645_delim[] = 
         "\x0a";
      read_00645 = NULL;
      read_00645_len = 0;
      int read_00645_res = cgc_delimited_read(0, &read_00645, &read_00645_len, read_00645_delim, 1);
      if (read_00645_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00645_00000[] = 
         "\x0a";
      read_00645_ptr += cgc_data_match(read_00645 + read_00645_ptr, read_00645_len - read_00645_ptr, match_00645_00000, 1);
      cgc_free(read_00645);
      if (read_00645_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00646;
      unsigned int read_00646_len;
      unsigned int read_00646_ptr = 0;
      //**** delimited read
      static unsigned char read_00646_delim[] = 
         "\x0a";
      read_00646 = NULL;
      read_00646_len = 0;
      int read_00646_res = cgc_delimited_read(0, &read_00646, &read_00646_len, read_00646_delim, 1);
      if (read_00646_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00646_00000[] = 
         "\x0a";
      read_00646_ptr += cgc_data_match(read_00646 + read_00646_ptr, read_00646_len - read_00646_ptr, match_00646_00000, 1);
      cgc_free(read_00646);
      if (read_00646_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00647;
      unsigned int read_00647_len;
      unsigned int read_00647_ptr = 0;
      //**** delimited read
      static unsigned char read_00647_delim[] = 
         "\x0a";
      read_00647 = NULL;
      read_00647_len = 0;
      int read_00647_res = cgc_delimited_read(0, &read_00647, &read_00647_len, read_00647_delim, 1);
      if (read_00647_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00647_00000[] = 
         "\x0a";
      read_00647_ptr += cgc_data_match(read_00647 + read_00647_ptr, read_00647_len - read_00647_ptr, match_00647_00000, 1);
      cgc_free(read_00647);
      if (read_00647_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00648;
      unsigned int read_00648_len;
      unsigned int read_00648_ptr = 0;
      //**** delimited read
      static unsigned char read_00648_delim[] = 
         "\x0a";
      read_00648 = NULL;
      read_00648_len = 0;
      int read_00648_res = cgc_delimited_read(0, &read_00648, &read_00648_len, read_00648_delim, 1);
      if (read_00648_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00648_00000[] = 
         "\x0a";
      read_00648_ptr += cgc_data_match(read_00648 + read_00648_ptr, read_00648_len - read_00648_ptr, match_00648_00000, 1);
      cgc_free(read_00648);
      if (read_00648_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00649;
      unsigned int read_00649_len;
      unsigned int read_00649_ptr = 0;
      //**** delimited read
      static unsigned char read_00649_delim[] = 
         "\x0a";
      read_00649 = NULL;
      read_00649_len = 0;
      int read_00649_res = cgc_delimited_read(0, &read_00649, &read_00649_len, read_00649_delim, 1);
      if (read_00649_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00649_00000[] = 
         "\x0a";
      read_00649_ptr += cgc_data_match(read_00649 + read_00649_ptr, read_00649_len - read_00649_ptr, match_00649_00000, 1);
      cgc_free(read_00649);
      if (read_00649_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00650;
      unsigned int read_00650_len;
      unsigned int read_00650_ptr = 0;
      //**** delimited read
      static unsigned char read_00650_delim[] = 
         "\x0a";
      read_00650 = NULL;
      read_00650_len = 0;
      int read_00650_res = cgc_delimited_read(0, &read_00650, &read_00650_len, read_00650_delim, 1);
      if (read_00650_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00650_00000[] = 
         "\x0a";
      read_00650_ptr += cgc_data_match(read_00650 + read_00650_ptr, read_00650_len - read_00650_ptr, match_00650_00000, 1);
      cgc_free(read_00650);
      if (read_00650_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00651;
      unsigned int read_00651_len;
      unsigned int read_00651_ptr = 0;
      //**** delimited read
      static unsigned char read_00651_delim[] = 
         "\x0a";
      read_00651 = NULL;
      read_00651_len = 0;
      int read_00651_res = cgc_delimited_read(0, &read_00651, &read_00651_len, read_00651_delim, 1);
      if (read_00651_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00651_00000[] = 
         "\x0a";
      read_00651_ptr += cgc_data_match(read_00651 + read_00651_ptr, read_00651_len - read_00651_ptr, match_00651_00000, 1);
      cgc_free(read_00651);
      if (read_00651_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00652;
      unsigned int read_00652_len;
      unsigned int read_00652_ptr = 0;
      //**** delimited read
      static unsigned char read_00652_delim[] = 
         "\x0a";
      read_00652 = NULL;
      read_00652_len = 0;
      int read_00652_res = cgc_delimited_read(0, &read_00652, &read_00652_len, read_00652_delim, 1);
      if (read_00652_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00652_00000[] = 
         "\x0a";
      read_00652_ptr += cgc_data_match(read_00652 + read_00652_ptr, read_00652_len - read_00652_ptr, match_00652_00000, 1);
      cgc_free(read_00652);
      if (read_00652_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00653;
      unsigned int read_00653_len;
      unsigned int read_00653_ptr = 0;
      //**** delimited read
      static unsigned char read_00653_delim[] = 
         "\x0a";
      read_00653 = NULL;
      read_00653_len = 0;
      int read_00653_res = cgc_delimited_read(0, &read_00653, &read_00653_len, read_00653_delim, 1);
      if (read_00653_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00653_00000[] = 
         "\x0a";
      read_00653_ptr += cgc_data_match(read_00653 + read_00653_ptr, read_00653_len - read_00653_ptr, match_00653_00000, 1);
      cgc_free(read_00653);
      if (read_00653_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00654;
      unsigned int read_00654_len;
      unsigned int read_00654_ptr = 0;
      //**** delimited read
      static unsigned char read_00654_delim[] = 
         "\x0a";
      read_00654 = NULL;
      read_00654_len = 0;
      int read_00654_res = cgc_delimited_read(0, &read_00654, &read_00654_len, read_00654_delim, 1);
      if (read_00654_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00654_00000[] = 
         "\x0a";
      read_00654_ptr += cgc_data_match(read_00654 + read_00654_ptr, read_00654_len - read_00654_ptr, match_00654_00000, 1);
      cgc_free(read_00654);
      if (read_00654_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00655;
      unsigned int read_00655_len;
      unsigned int read_00655_ptr = 0;
      //**** delimited read
      static unsigned char read_00655_delim[] = 
         "\x0a";
      read_00655 = NULL;
      read_00655_len = 0;
      int read_00655_res = cgc_delimited_read(0, &read_00655, &read_00655_len, read_00655_delim, 1);
      if (read_00655_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00655_00000[] = 
         "\x0a";
      read_00655_ptr += cgc_data_match(read_00655 + read_00655_ptr, read_00655_len - read_00655_ptr, match_00655_00000, 1);
      cgc_free(read_00655);
      if (read_00655_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00656;
      unsigned int read_00656_len;
      unsigned int read_00656_ptr = 0;
      //**** delimited read
      static unsigned char read_00656_delim[] = 
         "\x0a";
      read_00656 = NULL;
      read_00656_len = 0;
      int read_00656_res = cgc_delimited_read(0, &read_00656, &read_00656_len, read_00656_delim, 1);
      if (read_00656_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00656_00000[] = 
         "\x0a";
      read_00656_ptr += cgc_data_match(read_00656 + read_00656_ptr, read_00656_len - read_00656_ptr, match_00656_00000, 1);
      cgc_free(read_00656);
      if (read_00656_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00657;
      unsigned int read_00657_len;
      unsigned int read_00657_ptr = 0;
      //**** delimited read
      static unsigned char read_00657_delim[] = 
         "\x0a";
      read_00657 = NULL;
      read_00657_len = 0;
      int read_00657_res = cgc_delimited_read(0, &read_00657, &read_00657_len, read_00657_delim, 1);
      if (read_00657_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00657_00000[] = 
         "\x0a";
      read_00657_ptr += cgc_data_match(read_00657 + read_00657_ptr, read_00657_len - read_00657_ptr, match_00657_00000, 1);
      cgc_free(read_00657);
      if (read_00657_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00658;
      unsigned int read_00658_len;
      unsigned int read_00658_ptr = 0;
      //**** delimited read
      static unsigned char read_00658_delim[] = 
         "\x0a";
      read_00658 = NULL;
      read_00658_len = 0;
      int read_00658_res = cgc_delimited_read(0, &read_00658, &read_00658_len, read_00658_delim, 1);
      if (read_00658_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00658_00000[] = 
         "\x0a";
      read_00658_ptr += cgc_data_match(read_00658 + read_00658_ptr, read_00658_len - read_00658_ptr, match_00658_00000, 1);
      cgc_free(read_00658);
      if (read_00658_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00659;
      unsigned int read_00659_len;
      unsigned int read_00659_ptr = 0;
      //**** delimited read
      static unsigned char read_00659_delim[] = 
         "\x0a";
      read_00659 = NULL;
      read_00659_len = 0;
      int read_00659_res = cgc_delimited_read(0, &read_00659, &read_00659_len, read_00659_delim, 1);
      if (read_00659_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00659_00000[] = 
         "\x0a";
      read_00659_ptr += cgc_data_match(read_00659 + read_00659_ptr, read_00659_len - read_00659_ptr, match_00659_00000, 1);
      cgc_free(read_00659);
      if (read_00659_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00660;
      unsigned int read_00660_len;
      unsigned int read_00660_ptr = 0;
      //**** delimited read
      static unsigned char read_00660_delim[] = 
         "\x0a";
      read_00660 = NULL;
      read_00660_len = 0;
      int read_00660_res = cgc_delimited_read(0, &read_00660, &read_00660_len, read_00660_delim, 1);
      if (read_00660_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00660_00000[] = 
         "\x0a";
      read_00660_ptr += cgc_data_match(read_00660 + read_00660_ptr, read_00660_len - read_00660_ptr, match_00660_00000, 1);
      cgc_free(read_00660);
      if (read_00660_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00661;
      unsigned int read_00661_len;
      unsigned int read_00661_ptr = 0;
      //**** delimited read
      static unsigned char read_00661_delim[] = 
         "\x0a";
      read_00661 = NULL;
      read_00661_len = 0;
      int read_00661_res = cgc_delimited_read(0, &read_00661, &read_00661_len, read_00661_delim, 1);
      if (read_00661_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00661_00000[] = 
         "\x0a";
      read_00661_ptr += cgc_data_match(read_00661 + read_00661_ptr, read_00661_len - read_00661_ptr, match_00661_00000, 1);
      cgc_free(read_00661);
      if (read_00661_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00662;
      unsigned int read_00662_len;
      unsigned int read_00662_ptr = 0;
      //**** delimited read
      static unsigned char read_00662_delim[] = 
         "\x0a";
      read_00662 = NULL;
      read_00662_len = 0;
      int read_00662_res = cgc_delimited_read(0, &read_00662, &read_00662_len, read_00662_delim, 1);
      if (read_00662_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00662_00000[] = 
         "\x63\x68\x6f\x69\x63\x65\x3a\x0a";
      read_00662_ptr += cgc_data_match(read_00662 + read_00662_ptr, read_00662_len - read_00662_ptr, match_00662_00000, 8);
      cgc_free(read_00662);
      if (read_00662_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00388_00000[] = 
         "\x30\x0a";
      static unsigned int write_00388_00000_len = 2;
      unsigned char *write_00388 = NULL;
      unsigned int write_00388_len = 0;
      write_00388 = cgc_append_buf(write_00388, &write_00388_len, write_00388_00000, write_00388_00000_len);
      if (write_00388_len > 0) {
         cgc_transmit_all(1, write_00388, write_00388_len);
      }
      cgc_free(write_00388);
   } while (0);
}
