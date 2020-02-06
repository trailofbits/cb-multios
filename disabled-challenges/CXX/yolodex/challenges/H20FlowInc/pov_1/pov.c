#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 27;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x49\x4e\x46\x4f\x3a\x20\x48\x32\x46\x4c\x4f\x57\x20\x53\x65\x72"
         "\x76\x69\x63\x65\x20\x52\x65\x61\x64\x79\x2e";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 27);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 8;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x01\x00\x00\x00\xff\x5a\x06\x00";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 8);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x0f";
      static unsigned int write_00000_00000_len = 1;
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
      read_00002_len = 8;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x02\x00\x00\x00\xff\x5a\x06\x00";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 8);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x0f";
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
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 8;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x03\x00\x00\x00\xff\x5a\x06\x00";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 8);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x0f";
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
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 8;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x04\x00\x00\x00\xff\x5a\x06\x00";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 8);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x0f";
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
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 8;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x05\x00\x00\x00\xff\x5a\x06\x00";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 8);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x0f";
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
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 8;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x06\x00\x00\x00\xff\x5a\x06\x00";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 8);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x0f";
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
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 8;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x07\x00\x00\x00\xff\x5a\x06\x00";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 8);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x0f";
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
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 8;
      read_00008 = (unsigned char*)cgc_malloc(read_00008_len);
      int read_00008_res = cgc_length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x08\x00\x00\x00\xff\x5a\x06\x00";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 8);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x0f";
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
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 8;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x09\x00\x00\x00\xff\x5a\x06\x00";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 8);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x0f";
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
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 8;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x0a\x00\x00\x00\xff\x5a\x06\x00";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 8);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x0f";
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
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 8;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x01\x0c\x03\x00\xff\x5a\x02\x00";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 8);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x0c";
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
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 8;
      read_00012 = (unsigned char*)cgc_malloc(read_00012_len);
      int read_00012_res = cgc_length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x02\x0c\x01\x00\xff\x5a\x02\x00";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 8);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x0c";
      static unsigned int write_00011_00000_len = 1;
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
      //**** length read
      read_00013_len = 8;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x03\x0c\x08\x00\xff\x5a\x02\x00";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 8);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x0c";
      static unsigned int write_00012_00000_len = 1;
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
      //**** length read
      read_00014_len = 8;
      read_00014 = (unsigned char*)cgc_malloc(read_00014_len);
      int read_00014_res = cgc_length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x04\x0c\x01\x00\xff\x5a\x02\x00";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 8);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x0c";
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
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length read
      read_00015_len = 8;
      read_00015 = (unsigned char*)cgc_malloc(read_00015_len);
      int read_00015_res = cgc_length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x05\x0c\x05\x00\xff\x5a\x02\x00";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 8);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x0c";
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
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length read
      read_00016_len = 8;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x06\x0c\x09\x00\xff\x5a\x02\x00";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 8);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x0c";
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
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 8;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00017_00000[] = 
         "\x07\x0c\x04\x00\xff\x5a\x02\x00";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 8);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x0c";
      static unsigned int write_00016_00000_len = 1;
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
      //**** length read
      read_00018_len = 8;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x08\x0c\x0c\x00\xff\x5a\x02\x00";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 8);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x0c";
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
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 8;
      read_00019 = (unsigned char*)cgc_malloc(read_00019_len);
      int read_00019_res = cgc_length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00019_00000[] = 
         "\x09\x0c\x05\x00\xff\x5a\x02\x00";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 8);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x0c";
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
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length read
      read_00020_len = 8;
      read_00020 = (unsigned char*)cgc_malloc(read_00020_len);
      int read_00020_res = cgc_length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00020_00000[] = 
         "\x0a\x0c\x03\x00\xff\x5a\x02\x00";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 8);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x0c";
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
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** length read
      read_00021_len = 8;
      read_00021 = (unsigned char*)cgc_malloc(read_00021_len);
      int read_00021_res = cgc_length_read(0, read_00021, read_00021_len);
      if (read_00021_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00021_00000[] = 
         "\x01\x0c\x05\x01\xff\x63\x02\x00";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 8);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x0c";
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
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** length read
      read_00022_len = 8;
      read_00022 = (unsigned char*)cgc_malloc(read_00022_len);
      int read_00022_res = cgc_length_read(0, read_00022, read_00022_len);
      if (read_00022_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00022_00000[] = 
         "\x02\x0c\x10\x01\xff\x65\x02\x00";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 8);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x0c";
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
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length read
      read_00023_len = 8;
      read_00023 = (unsigned char*)cgc_malloc(read_00023_len);
      int read_00023_res = cgc_length_read(0, read_00023, read_00023_len);
      if (read_00023_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00023_00000[] = 
         "\x03\x0c\x09\x01\xff\x5e\x02\x00";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 8);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x0c";
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
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** length read
      read_00024_len = 8;
      read_00024 = (unsigned char*)cgc_malloc(read_00024_len);
      int read_00024_res = cgc_length_read(0, read_00024, read_00024_len);
      if (read_00024_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00024_00000[] = 
         "\x04\x0c\x07\x01\xff\x65\x02\x00";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 8);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x0c";
      static unsigned int write_00023_00000_len = 1;
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
      //**** length read
      read_00025_len = 8;
      read_00025 = (unsigned char*)cgc_malloc(read_00025_len);
      int read_00025_res = cgc_length_read(0, read_00025, read_00025_len);
      if (read_00025_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00025_00000[] = 
         "\x05\x0c\x09\x01\xff\x61\x02\x00";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 8);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x0c";
      static unsigned int write_00024_00000_len = 1;
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
      //**** length read
      read_00026_len = 8;
      read_00026 = (unsigned char*)cgc_malloc(read_00026_len);
      int read_00026_res = cgc_length_read(0, read_00026, read_00026_len);
      if (read_00026_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00026_00000[] = 
         "\x06\x0c\x03\x01\xff\x5d\x02\x00";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 8);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x0c";
      static unsigned int write_00025_00000_len = 1;
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
      //**** length read
      read_00027_len = 8;
      read_00027 = (unsigned char*)cgc_malloc(read_00027_len);
      int read_00027_res = cgc_length_read(0, read_00027, read_00027_len);
      if (read_00027_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00027_00000[] = 
         "\x07\x0c\x04\x01\xff\x62\x02\x00";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 8);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x0c";
      static unsigned int write_00026_00000_len = 1;
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
      //**** length read
      read_00028_len = 8;
      read_00028 = (unsigned char*)cgc_malloc(read_00028_len);
      int read_00028_res = cgc_length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00028_00000[] = 
         "\x08\x0c\x03\x01\xff\x5a\x02\x00";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 8);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x0c";
      static unsigned int write_00027_00000_len = 1;
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
      //**** length read
      read_00029_len = 8;
      read_00029 = (unsigned char*)cgc_malloc(read_00029_len);
      int read_00029_res = cgc_length_read(0, read_00029, read_00029_len);
      if (read_00029_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00029_00000[] = 
         "\x09\x0c\x10\x01\xff\x61\x02\x00";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 8);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x0c";
      static unsigned int write_00028_00000_len = 1;
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
      //**** length read
      read_00030_len = 8;
      read_00030 = (unsigned char*)cgc_malloc(read_00030_len);
      int read_00030_res = cgc_length_read(0, read_00030, read_00030_len);
      if (read_00030_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00030_00000[] = 
         "\x0a\x0c\x08\x01\xff\x63\x02\x00";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 8);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x0c";
      static unsigned int write_00029_00000_len = 1;
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
      //**** length read
      read_00031_len = 8;
      read_00031 = (unsigned char*)cgc_malloc(read_00031_len);
      int read_00031_res = cgc_length_read(0, read_00031, read_00031_len);
      if (read_00031_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00031_00000[] = 
         "\x01\x0c\x0c\x01\xff\x6a\x02\x00";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 8);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x0c";
      static unsigned int write_00030_00000_len = 1;
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
      //**** length read
      read_00032_len = 8;
      read_00032 = (unsigned char*)cgc_malloc(read_00032_len);
      int read_00032_res = cgc_length_read(0, read_00032, read_00032_len);
      if (read_00032_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00032_00000[] = 
         "\x02\x0c\x04\x01\xff\x61\x02\x00";
      read_00032_ptr += cgc_data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 8);
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x0c";
      static unsigned int write_00031_00000_len = 1;
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
      //**** length read
      read_00033_len = 8;
      read_00033 = (unsigned char*)cgc_malloc(read_00033_len);
      int read_00033_res = cgc_length_read(0, read_00033, read_00033_len);
      if (read_00033_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00033_00000[] = 
         "\x03\x0c\x0c\x01\xff\x61\x02\x00";
      read_00033_ptr += cgc_data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 8);
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x0c";
      static unsigned int write_00032_00000_len = 1;
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
      //**** length read
      read_00034_len = 8;
      read_00034 = (unsigned char*)cgc_malloc(read_00034_len);
      int read_00034_res = cgc_length_read(0, read_00034, read_00034_len);
      if (read_00034_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00034_00000[] = 
         "\x04\x0c\x08\x01\xff\x6a\x02\x00";
      read_00034_ptr += cgc_data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 8);
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x0c";
      static unsigned int write_00033_00000_len = 1;
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
      //**** length read
      read_00035_len = 8;
      read_00035 = (unsigned char*)cgc_malloc(read_00035_len);
      int read_00035_res = cgc_length_read(0, read_00035, read_00035_len);
      if (read_00035_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00035_00000[] = 
         "\x05\x0c\x03\x01\xff\x64\x02\x00";
      read_00035_ptr += cgc_data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 8);
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x0c";
      static unsigned int write_00034_00000_len = 1;
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
      //**** length read
      read_00036_len = 8;
      read_00036 = (unsigned char*)cgc_malloc(read_00036_len);
      int read_00036_res = cgc_length_read(0, read_00036, read_00036_len);
      if (read_00036_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00036_00000[] = 
         "\x06\x0c\x03\x01\xff\x66\x02\x00";
      read_00036_ptr += cgc_data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 8);
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x0c";
      static unsigned int write_00035_00000_len = 1;
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
      //**** length read
      read_00037_len = 8;
      read_00037 = (unsigned char*)cgc_malloc(read_00037_len);
      int read_00037_res = cgc_length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00037_00000[] = 
         "\x07\x0c\x10\x01\xff\x6a\x02\x00";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 8);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x0c";
      static unsigned int write_00036_00000_len = 1;
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
      //**** length read
      read_00038_len = 8;
      read_00038 = (unsigned char*)cgc_malloc(read_00038_len);
      int read_00038_res = cgc_length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00038_00000[] = 
         "\x08\x0c\x03\x01\xff\x63\x02\x00";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 8);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x0c";
      static unsigned int write_00037_00000_len = 1;
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
      //**** length read
      read_00039_len = 8;
      read_00039 = (unsigned char*)cgc_malloc(read_00039_len);
      int read_00039_res = cgc_length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00039_00000[] = 
         "\x09\x0c\x04\x01\xff\x5d\x02\x00";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 8);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x0c";
      static unsigned int write_00038_00000_len = 1;
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
      //**** length read
      read_00040_len = 8;
      read_00040 = (unsigned char*)cgc_malloc(read_00040_len);
      int read_00040_res = cgc_length_read(0, read_00040, read_00040_len);
      if (read_00040_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00040_00000[] = 
         "\x0a\x0c\x07\x01\xff\x67\x02\x00";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 8);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x0c";
      static unsigned int write_00039_00000_len = 1;
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
      //**** length read
      read_00041_len = 8;
      read_00041 = (unsigned char*)cgc_malloc(read_00041_len);
      int read_00041_res = cgc_length_read(0, read_00041, read_00041_len);
      if (read_00041_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00041_00000[] = 
         "\x01\x0c\x09\x01\xff\x6a\x02\x00";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 8);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x0c";
      static unsigned int write_00040_00000_len = 1;
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
      //**** length read
      read_00042_len = 8;
      read_00042 = (unsigned char*)cgc_malloc(read_00042_len);
      int read_00042_res = cgc_length_read(0, read_00042, read_00042_len);
      if (read_00042_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00042_00000[] = 
         "\x02\x0c\x05\x01\xff\x69\x02\x00";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 8);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x0c";
      static unsigned int write_00041_00000_len = 1;
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
      //**** length read
      read_00043_len = 8;
      read_00043 = (unsigned char*)cgc_malloc(read_00043_len);
      int read_00043_res = cgc_length_read(0, read_00043, read_00043_len);
      if (read_00043_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00043_00000[] = 
         "\x03\x0c\x00\x01\xff\x61\x02\x00";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 8);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x0c";
      static unsigned int write_00042_00000_len = 1;
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
      //**** length read
      read_00044_len = 8;
      read_00044 = (unsigned char*)cgc_malloc(read_00044_len);
      int read_00044_res = cgc_length_read(0, read_00044, read_00044_len);
      if (read_00044_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00044_00000[] = 
         "\x04\x0c\x04\x01\xff\x6e\x02\x00";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 8);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x0c";
      static unsigned int write_00043_00000_len = 1;
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
      //**** length read
      read_00045_len = 8;
      read_00045 = (unsigned char*)cgc_malloc(read_00045_len);
      int read_00045_res = cgc_length_read(0, read_00045, read_00045_len);
      if (read_00045_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00045_00000[] = 
         "\x05\x0c\x10\x01\xff\x6d\x02\x00";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 8);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x0c";
      static unsigned int write_00044_00000_len = 1;
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
      //**** length read
      read_00046_len = 8;
      read_00046 = (unsigned char*)cgc_malloc(read_00046_len);
      int read_00046_res = cgc_length_read(0, read_00046, read_00046_len);
      if (read_00046_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00046_00000[] = 
         "\x06\x0c\x10\x01\xff\x6f\x02\x00";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 8);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x0c";
      static unsigned int write_00045_00000_len = 1;
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
      //**** length read
      read_00047_len = 8;
      read_00047 = (unsigned char*)cgc_malloc(read_00047_len);
      int read_00047_res = cgc_length_read(0, read_00047, read_00047_len);
      if (read_00047_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00047_00000[] = 
         "\x07\x0c\x08\x01\xff\x66\x02\x00";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 8);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x0c";
      static unsigned int write_00046_00000_len = 1;
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
      //**** length read
      read_00048_len = 8;
      read_00048 = (unsigned char*)cgc_malloc(read_00048_len);
      int read_00048_res = cgc_length_read(0, read_00048, read_00048_len);
      if (read_00048_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00048_00000[] = 
         "\x08\x0c\x01\x01\xff\x6c\x02\x00";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 8);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x0c";
      static unsigned int write_00047_00000_len = 1;
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
      //**** length read
      read_00049_len = 8;
      read_00049 = (unsigned char*)cgc_malloc(read_00049_len);
      int read_00049_res = cgc_length_read(0, read_00049, read_00049_len);
      if (read_00049_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00049_00000[] = 
         "\x09\x0c\x09\x01\xff\x65\x02\x00";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 8);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x0c";
      static unsigned int write_00048_00000_len = 1;
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
      //**** length read
      read_00050_len = 8;
      read_00050 = (unsigned char*)cgc_malloc(read_00050_len);
      int read_00050_res = cgc_length_read(0, read_00050, read_00050_len);
      if (read_00050_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00050_00000[] = 
         "\x0a\x0c\x07\x01\xff\x6c\x02\x00";
      read_00050_ptr += cgc_data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 8);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x0c";
      static unsigned int write_00049_00000_len = 1;
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
      //**** length read
      read_00051_len = 8;
      read_00051 = (unsigned char*)cgc_malloc(read_00051_len);
      int read_00051_res = cgc_length_read(0, read_00051, read_00051_len);
      if (read_00051_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00051_00000[] = 
         "\x01\x0c\x01\x01\xff\x6d\x02\x00";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 8);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x0c";
      static unsigned int write_00050_00000_len = 1;
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
      //**** length read
      read_00052_len = 8;
      read_00052 = (unsigned char*)cgc_malloc(read_00052_len);
      int read_00052_res = cgc_length_read(0, read_00052, read_00052_len);
      if (read_00052_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00052_00000[] = 
         "\x02\x0c\x0c\x01\xff\x70\x02\x00";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 8);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x0c";
      static unsigned int write_00051_00000_len = 1;
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
      //**** length read
      read_00053_len = 8;
      read_00053 = (unsigned char*)cgc_malloc(read_00053_len);
      int read_00053_res = cgc_length_read(0, read_00053, read_00053_len);
      if (read_00053_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00053_00000[] = 
         "\x03\x0c\x09\x01\xff\x6d\x02\x00";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 8);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x0c";
      static unsigned int write_00052_00000_len = 1;
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
      //**** length read
      read_00054_len = 8;
      read_00054 = (unsigned char*)cgc_malloc(read_00054_len);
      int read_00054_res = cgc_length_read(0, read_00054, read_00054_len);
      if (read_00054_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00054_00000[] = 
         "\x04\x0c\x03\x01\xff\x76\x02\x00";
      read_00054_ptr += cgc_data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 8);
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x0c";
      static unsigned int write_00053_00000_len = 1;
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
      //**** length read
      read_00055_len = 8;
      read_00055 = (unsigned char*)cgc_malloc(read_00055_len);
      int read_00055_res = cgc_length_read(0, read_00055, read_00055_len);
      if (read_00055_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00055_00000[] = 
         "\x05\x0c\x09\x01\xff\x69\x02\x00";
      read_00055_ptr += cgc_data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 8);
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x0c";
      static unsigned int write_00054_00000_len = 1;
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
      //**** length read
      read_00056_len = 8;
      read_00056 = (unsigned char*)cgc_malloc(read_00056_len);
      int read_00056_res = cgc_length_read(0, read_00056, read_00056_len);
      if (read_00056_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00056_00000[] = 
         "\x06\x0c\x09\x01\xff\x6b\x02\x00";
      read_00056_ptr += cgc_data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 8);
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x0c";
      static unsigned int write_00055_00000_len = 1;
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
      //**** length read
      read_00057_len = 8;
      read_00057 = (unsigned char*)cgc_malloc(read_00057_len);
      int read_00057_res = cgc_length_read(0, read_00057, read_00057_len);
      if (read_00057_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00057_00000[] = 
         "\x07\x0c\x03\x01\xff\x6a\x02\x00";
      read_00057_ptr += cgc_data_match(read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, match_00057_00000, 8);
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x0c";
      static unsigned int write_00056_00000_len = 1;
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
      //**** length read
      read_00058_len = 8;
      read_00058 = (unsigned char*)cgc_malloc(read_00058_len);
      int read_00058_res = cgc_length_read(0, read_00058, read_00058_len);
      if (read_00058_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00058_00000[] = 
         "\x08\x0c\x07\x01\xff\x77\x02\x00";
      read_00058_ptr += cgc_data_match(read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, match_00058_00000, 8);
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x0c";
      static unsigned int write_00057_00000_len = 1;
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
      //**** length read
      read_00059_len = 8;
      read_00059 = (unsigned char*)cgc_malloc(read_00059_len);
      int read_00059_res = cgc_length_read(0, read_00059, read_00059_len);
      if (read_00059_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00059_00000[] = 
         "\x09\x0c\x05\x01\xff\x68\x02\x00";
      read_00059_ptr += cgc_data_match(read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, match_00059_00000, 8);
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x0c";
      static unsigned int write_00058_00000_len = 1;
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
      //**** length read
      read_00060_len = 8;
      read_00060 = (unsigned char*)cgc_malloc(read_00060_len);
      int read_00060_res = cgc_length_read(0, read_00060, read_00060_len);
      if (read_00060_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00060_00000[] = 
         "\x0a\x0c\x01\x01\xff\x71\x02\x00";
      read_00060_ptr += cgc_data_match(read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, match_00060_00000, 8);
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x0c";
      static unsigned int write_00059_00000_len = 1;
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
      //**** length read
      read_00061_len = 8;
      read_00061 = (unsigned char*)cgc_malloc(read_00061_len);
      int read_00061_res = cgc_length_read(0, read_00061, read_00061_len);
      if (read_00061_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00061_00000[] = 
         "\x01\x0c\x00\x01\xff\x78\x02\x00";
      read_00061_ptr += cgc_data_match(read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, match_00061_00000, 8);
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x0c";
      static unsigned int write_00060_00000_len = 1;
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
      //**** length read
      read_00062_len = 8;
      read_00062 = (unsigned char*)cgc_malloc(read_00062_len);
      int read_00062_res = cgc_length_read(0, read_00062, read_00062_len);
      if (read_00062_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00062_00000[] = 
         "\x02\x0c\x05\x01\xff\x70\x02\x00";
      read_00062_ptr += cgc_data_match(read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, match_00062_00000, 8);
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x0c";
      static unsigned int write_00061_00000_len = 1;
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
      //**** length read
      read_00063_len = 8;
      read_00063 = (unsigned char*)cgc_malloc(read_00063_len);
      int read_00063_res = cgc_length_read(0, read_00063, read_00063_len);
      if (read_00063_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00063_00000[] = 
         "\x03\x0c\x10\x01\xff\x70\x02\x00";
      read_00063_ptr += cgc_data_match(read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, match_00063_00000, 8);
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x0c";
      static unsigned int write_00062_00000_len = 1;
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
      //**** length read
      read_00064_len = 8;
      read_00064 = (unsigned char*)cgc_malloc(read_00064_len);
      int read_00064_res = cgc_length_read(0, read_00064, read_00064_len);
      if (read_00064_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00064_00000[] = 
         "\x04\x0c\x04\x01\xff\x7f\x02\x00";
      read_00064_ptr += cgc_data_match(read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, match_00064_00000, 8);
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x0c";
      static unsigned int write_00063_00000_len = 1;
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
      //**** length read
      read_00065_len = 8;
      read_00065 = (unsigned char*)cgc_malloc(read_00065_len);
      int read_00065_res = cgc_length_read(0, read_00065, read_00065_len);
      if (read_00065_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00065_00000[] = 
         "\x05\x0c\x00\x01\xff\x6c\x02\x00";
      read_00065_ptr += cgc_data_match(read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, match_00065_00000, 8);
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x0c";
      static unsigned int write_00064_00000_len = 1;
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
      //**** length read
      read_00066_len = 8;
      read_00066 = (unsigned char*)cgc_malloc(read_00066_len);
      int read_00066_res = cgc_length_read(0, read_00066, read_00066_len);
      if (read_00066_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00066_00000[] = 
         "\x06\x0c\x09\x01\xff\x6e\x02\x00";
      read_00066_ptr += cgc_data_match(read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, match_00066_00000, 8);
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x0c";
      static unsigned int write_00065_00000_len = 1;
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
      //**** length read
      read_00067_len = 8;
      read_00067 = (unsigned char*)cgc_malloc(read_00067_len);
      int read_00067_res = cgc_length_read(0, read_00067, read_00067_len);
      if (read_00067_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00067_00000[] = 
         "\x07\x0c\x07\x01\xff\x73\x02\x00";
      read_00067_ptr += cgc_data_match(read_00067 + read_00067_ptr, read_00067_len - read_00067_ptr, match_00067_00000, 8);
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x0c";
      static unsigned int write_00066_00000_len = 1;
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
      //**** length read
      read_00068_len = 8;
      read_00068 = (unsigned char*)cgc_malloc(read_00068_len);
      int read_00068_res = cgc_length_read(0, read_00068, read_00068_len);
      if (read_00068_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00068_00000[] = 
         "\x08\x0c\x08\x01\xff\x7c\x02\x00";
      read_00068_ptr += cgc_data_match(read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, match_00068_00000, 8);
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x0c";
      static unsigned int write_00067_00000_len = 1;
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
      //**** length read
      read_00069_len = 8;
      read_00069 = (unsigned char*)cgc_malloc(read_00069_len);
      int read_00069_res = cgc_length_read(0, read_00069, read_00069_len);
      if (read_00069_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00069_00000[] = 
         "\x09\x0c\x09\x01\xff\x6f\x02\x00";
      read_00069_ptr += cgc_data_match(read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, match_00069_00000, 8);
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x0c";
      static unsigned int write_00068_00000_len = 1;
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
      //**** length read
      read_00070_len = 8;
      read_00070 = (unsigned char*)cgc_malloc(read_00070_len);
      int read_00070_res = cgc_length_read(0, read_00070, read_00070_len);
      if (read_00070_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00070_00000[] = 
         "\x0a\x0c\x08\x01\xff\x7c\x02\x00";
      read_00070_ptr += cgc_data_match(read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, match_00070_00000, 8);
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x0c";
      static unsigned int write_00069_00000_len = 1;
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
      //**** length read
      read_00071_len = 8;
      read_00071 = (unsigned char*)cgc_malloc(read_00071_len);
      int read_00071_res = cgc_length_read(0, read_00071, read_00071_len);
      if (read_00071_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00071_00000[] = 
         "\x01\x0c\x08\x01\xff\x84\x02\x00";
      read_00071_ptr += cgc_data_match(read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, match_00071_00000, 8);
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x0c";
      static unsigned int write_00070_00000_len = 1;
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
      //**** length read
      read_00072_len = 8;
      read_00072 = (unsigned char*)cgc_malloc(read_00072_len);
      int read_00072_res = cgc_length_read(0, read_00072, read_00072_len);
      if (read_00072_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00072_00000[] = 
         "\x02\x0c\x05\x01\xff\x77\x02\x00";
      read_00072_ptr += cgc_data_match(read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, match_00072_00000, 8);
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x0c";
      static unsigned int write_00071_00000_len = 1;
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
      //**** length read
      read_00073_len = 8;
      read_00073 = (unsigned char*)cgc_malloc(read_00073_len);
      int read_00073_res = cgc_length_read(0, read_00073, read_00073_len);
      if (read_00073_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00073_00000[] = 
         "\x03\x0c\x09\x01\xff\x6c\x02\x00";
      read_00073_ptr += cgc_data_match(read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, match_00073_00000, 8);
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x0c";
      static unsigned int write_00072_00000_len = 1;
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
      //**** length read
      read_00074_len = 8;
      read_00074 = (unsigned char*)cgc_malloc(read_00074_len);
      int read_00074_res = cgc_length_read(0, read_00074, read_00074_len);
      if (read_00074_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00074_00000[] = 
         "\x04\x0c\x04\x01\xff\x87\x02\x00";
      read_00074_ptr += cgc_data_match(read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, match_00074_00000, 8);
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x0c";
      static unsigned int write_00073_00000_len = 1;
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
      //**** length read
      read_00075_len = 8;
      read_00075 = (unsigned char*)cgc_malloc(read_00075_len);
      int read_00075_res = cgc_length_read(0, read_00075, read_00075_len);
      if (read_00075_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00075_00000[] = 
         "\x05\x0c\x03\x01\xff\x78\x02\x00";
      read_00075_ptr += cgc_data_match(read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, match_00075_00000, 8);
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x0c";
      static unsigned int write_00074_00000_len = 1;
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
      //**** length read
      read_00076_len = 8;
      read_00076 = (unsigned char*)cgc_malloc(read_00076_len);
      int read_00076_res = cgc_length_read(0, read_00076, read_00076_len);
      if (read_00076_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00076_00000[] = 
         "\x06\x0c\x00\x01\xff\x71\x02\x00";
      read_00076_ptr += cgc_data_match(read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, match_00076_00000, 8);
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x0c";
      static unsigned int write_00075_00000_len = 1;
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
      //**** length read
      read_00077_len = 8;
      read_00077 = (unsigned char*)cgc_malloc(read_00077_len);
      int read_00077_res = cgc_length_read(0, read_00077, read_00077_len);
      if (read_00077_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00077_00000[] = 
         "\x07\x0c\x07\x01\xff\x78\x02\x00";
      read_00077_ptr += cgc_data_match(read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, match_00077_00000, 8);
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x0c";
      static unsigned int write_00076_00000_len = 1;
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
      //**** length read
      read_00078_len = 8;
      read_00078 = (unsigned char*)cgc_malloc(read_00078_len);
      int read_00078_res = cgc_length_read(0, read_00078, read_00078_len);
      if (read_00078_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00078_00000[] = 
         "\x08\x0c\x10\x01\xff\x80\x02\x00";
      read_00078_ptr += cgc_data_match(read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, match_00078_00000, 8);
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x0c";
      static unsigned int write_00077_00000_len = 1;
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
      //**** length read
      read_00079_len = 8;
      read_00079 = (unsigned char*)cgc_malloc(read_00079_len);
      int read_00079_res = cgc_length_read(0, read_00079, read_00079_len);
      if (read_00079_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00079_00000[] = 
         "\x09\x0c\x01\x01\xff\x72\x02\x00";
      read_00079_ptr += cgc_data_match(read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, match_00079_00000, 8);
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x0c";
      static unsigned int write_00078_00000_len = 1;
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
      //**** length read
      read_00080_len = 8;
      read_00080 = (unsigned char*)cgc_malloc(read_00080_len);
      int read_00080_res = cgc_length_read(0, read_00080, read_00080_len);
      if (read_00080_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00080_00000[] = 
         "\x0a\x0c\x0c\x01\xff\x80\x02\x00";
      read_00080_ptr += cgc_data_match(read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, match_00080_00000, 8);
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x0c";
      static unsigned int write_00079_00000_len = 1;
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
      //**** length read
      read_00081_len = 8;
      read_00081 = (unsigned char*)cgc_malloc(read_00081_len);
      int read_00081_res = cgc_length_read(0, read_00081, read_00081_len);
      if (read_00081_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00081_00000[] = 
         "\x01\x0c\x08\x01\xff\x88\x02\x00";
      read_00081_ptr += cgc_data_match(read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, match_00081_00000, 8);
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x0c";
      static unsigned int write_00080_00000_len = 1;
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
      //**** length read
      read_00082_len = 8;
      read_00082 = (unsigned char*)cgc_malloc(read_00082_len);
      int read_00082_res = cgc_length_read(0, read_00082, read_00082_len);
      if (read_00082_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00082_00000[] = 
         "\x02\x0c\x00\x01\xff\x7e\x02\x00";
      read_00082_ptr += cgc_data_match(read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, match_00082_00000, 8);
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x0c";
      static unsigned int write_00081_00000_len = 1;
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
      //**** length read
      read_00083_len = 8;
      read_00083 = (unsigned char*)cgc_malloc(read_00083_len);
      int read_00083_res = cgc_length_read(0, read_00083, read_00083_len);
      if (read_00083_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00083_00000[] = 
         "\x03\x0c\x0c\x01\xff\x6f\x02\x00";
      read_00083_ptr += cgc_data_match(read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, match_00083_00000, 8);
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x0c";
      static unsigned int write_00082_00000_len = 1;
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
      //**** length read
      read_00084_len = 8;
      read_00084 = (unsigned char*)cgc_malloc(read_00084_len);
      int read_00084_res = cgc_length_read(0, read_00084, read_00084_len);
      if (read_00084_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00084_00000[] = 
         "\x04\x0c\x04\x01\xff\x8f\x02\x00";
      read_00084_ptr += cgc_data_match(read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, match_00084_00000, 8);
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x0c";
      static unsigned int write_00083_00000_len = 1;
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
      //**** length read
      read_00085_len = 8;
      read_00085 = (unsigned char*)cgc_malloc(read_00085_len);
      int read_00085_res = cgc_length_read(0, read_00085, read_00085_len);
      if (read_00085_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00085_00000[] = 
         "\x05\x0c\x10\x01\xff\x81\x02\x00";
      read_00085_ptr += cgc_data_match(read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, match_00085_00000, 8);
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x0c";
      static unsigned int write_00084_00000_len = 1;
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
      //**** length read
      read_00086_len = 8;
      read_00086 = (unsigned char*)cgc_malloc(read_00086_len);
      int read_00086_res = cgc_length_read(0, read_00086, read_00086_len);
      if (read_00086_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00086_00000[] = 
         "\x06\x0c\x0c\x01\xff\x7d\x02\x00";
      read_00086_ptr += cgc_data_match(read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, match_00086_00000, 8);
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x0c";
      static unsigned int write_00085_00000_len = 1;
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
      //**** length read
      read_00087_len = 8;
      read_00087 = (unsigned char*)cgc_malloc(read_00087_len);
      int read_00087_res = cgc_length_read(0, read_00087, read_00087_len);
      if (read_00087_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00087_00000[] = 
         "\x07\x0c\x04\x01\xff\x7d\x02\x00";
      read_00087_ptr += cgc_data_match(read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, match_00087_00000, 8);
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x0c";
      static unsigned int write_00086_00000_len = 1;
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
      //**** length read
      read_00088_len = 8;
      read_00088 = (unsigned char*)cgc_malloc(read_00088_len);
      int read_00088_res = cgc_length_read(0, read_00088, read_00088_len);
      if (read_00088_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00088_00000[] = 
         "\x08\x0c\x00\x01\xff\x7c\x02\x00";
      read_00088_ptr += cgc_data_match(read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, match_00088_00000, 8);
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x0c";
      static unsigned int write_00087_00000_len = 1;
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
      //**** length read
      read_00089_len = 8;
      read_00089 = (unsigned char*)cgc_malloc(read_00089_len);
      int read_00089_res = cgc_length_read(0, read_00089, read_00089_len);
      if (read_00089_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00089_00000[] = 
         "\x09\x0c\x10\x01\xff\x7d\x02\x00";
      read_00089_ptr += cgc_data_match(read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, match_00089_00000, 8);
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x0c";
      static unsigned int write_00088_00000_len = 1;
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
      //**** length read
      read_00090_len = 8;
      read_00090 = (unsigned char*)cgc_malloc(read_00090_len);
      int read_00090_res = cgc_length_read(0, read_00090, read_00090_len);
      if (read_00090_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00090_00000[] = 
         "\x0a\x0c\x09\x01\xff\x80\x02\x00";
      read_00090_ptr += cgc_data_match(read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, match_00090_00000, 8);
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x0c";
      static unsigned int write_00089_00000_len = 1;
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
      //**** length read
      read_00091_len = 8;
      read_00091 = (unsigned char*)cgc_malloc(read_00091_len);
      int read_00091_res = cgc_length_read(0, read_00091, read_00091_len);
      if (read_00091_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00091_00000[] = 
         "\x01\x0c\x09\x01\xff\x8c\x02\x00";
      read_00091_ptr += cgc_data_match(read_00091 + read_00091_ptr, read_00091_len - read_00091_ptr, match_00091_00000, 8);
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x0c";
      static unsigned int write_00090_00000_len = 1;
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
      //**** length read
      read_00092_len = 8;
      read_00092 = (unsigned char*)cgc_malloc(read_00092_len);
      int read_00092_res = cgc_length_read(0, read_00092, read_00092_len);
      if (read_00092_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00092_00000[] = 
         "\x02\x0c\x10\x01\xff\x8a\x02\x00";
      read_00092_ptr += cgc_data_match(read_00092 + read_00092_ptr, read_00092_len - read_00092_ptr, match_00092_00000, 8);
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x0c";
      static unsigned int write_00091_00000_len = 1;
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
      //**** length read
      read_00093_len = 8;
      read_00093 = (unsigned char*)cgc_malloc(read_00093_len);
      int read_00093_res = cgc_length_read(0, read_00093, read_00093_len);
      if (read_00093_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00093_00000[] = 
         "\x03\x0c\x0c\x01\xff\x6f\x02\x00";
      read_00093_ptr += cgc_data_match(read_00093 + read_00093_ptr, read_00093_len - read_00093_ptr, match_00093_00000, 8);
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x0c";
      static unsigned int write_00092_00000_len = 1;
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
      //**** length read
      read_00094_len = 8;
      read_00094 = (unsigned char*)cgc_malloc(read_00094_len);
      int read_00094_res = cgc_length_read(0, read_00094, read_00094_len);
      if (read_00094_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00094_00000[] = 
         "\x04\x0c\x04\x01\xff\x97\x02\x00";
      read_00094_ptr += cgc_data_match(read_00094 + read_00094_ptr, read_00094_len - read_00094_ptr, match_00094_00000, 8);
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x0c";
      static unsigned int write_00093_00000_len = 1;
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
      //**** length read
      read_00095_len = 8;
      read_00095 = (unsigned char*)cgc_malloc(read_00095_len);
      int read_00095_res = cgc_length_read(0, read_00095, read_00095_len);
      if (read_00095_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00095_00000[] = 
         "\x05\x0c\x10\x01\xff\x7d\x02\x00";
      read_00095_ptr += cgc_data_match(read_00095 + read_00095_ptr, read_00095_len - read_00095_ptr, match_00095_00000, 8);
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x0c";
      static unsigned int write_00094_00000_len = 1;
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
      //**** length read
      read_00096_len = 8;
      read_00096 = (unsigned char*)cgc_malloc(read_00096_len);
      int read_00096_res = cgc_length_read(0, read_00096, read_00096_len);
      if (read_00096_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00096_00000[] = 
         "\x06\x0c\x00\x01\xff\x7d\x02\x00";
      read_00096_ptr += cgc_data_match(read_00096 + read_00096_ptr, read_00096_len - read_00096_ptr, match_00096_00000, 8);
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x0c";
      static unsigned int write_00095_00000_len = 1;
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
      //**** length read
      read_00097_len = 8;
      read_00097 = (unsigned char*)cgc_malloc(read_00097_len);
      int read_00097_res = cgc_length_read(0, read_00097, read_00097_len);
      if (read_00097_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00097_00000[] = 
         "\x07\x0c\x03\x01\xff\x85\x02\x00";
      read_00097_ptr += cgc_data_match(read_00097 + read_00097_ptr, read_00097_len - read_00097_ptr, match_00097_00000, 8);
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x0c";
      static unsigned int write_00096_00000_len = 1;
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
      //**** length read
      read_00098_len = 8;
      read_00098 = (unsigned char*)cgc_malloc(read_00098_len);
      int read_00098_res = cgc_length_read(0, read_00098, read_00098_len);
      if (read_00098_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00098_00000[] = 
         "\x08\x0c\x08\x01\xff\x88\x02\x00";
      read_00098_ptr += cgc_data_match(read_00098 + read_00098_ptr, read_00098_len - read_00098_ptr, match_00098_00000, 8);
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x0c";
      static unsigned int write_00097_00000_len = 1;
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
      //**** length read
      read_00099_len = 8;
      read_00099 = (unsigned char*)cgc_malloc(read_00099_len);
      int read_00099_res = cgc_length_read(0, read_00099, read_00099_len);
      if (read_00099_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00099_00000[] = 
         "\x09\x0c\x10\x01\xff\x79\x02\x00";
      read_00099_ptr += cgc_data_match(read_00099 + read_00099_ptr, read_00099_len - read_00099_ptr, match_00099_00000, 8);
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x0c";
      static unsigned int write_00098_00000_len = 1;
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
      //**** length read
      read_00100_len = 8;
      read_00100 = (unsigned char*)cgc_malloc(read_00100_len);
      int read_00100_res = cgc_length_read(0, read_00100, read_00100_len);
      if (read_00100_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00100_00000[] = 
         "\x0a\x0c\x04\x01\xff\x83\x02\x00";
      read_00100_ptr += cgc_data_match(read_00100 + read_00100_ptr, read_00100_len - read_00100_ptr, match_00100_00000, 8);
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x0c";
      static unsigned int write_00099_00000_len = 1;
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
      //**** length read
      read_00101_len = 8;
      read_00101 = (unsigned char*)cgc_malloc(read_00101_len);
      int read_00101_res = cgc_length_read(0, read_00101, read_00101_len);
      if (read_00101_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00101_00000[] = 
         "\x01\x0c\x05\x01\xff\x8f\x02\x00";
      read_00101_ptr += cgc_data_match(read_00101 + read_00101_ptr, read_00101_len - read_00101_ptr, match_00101_00000, 8);
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x0c";
      static unsigned int write_00100_00000_len = 1;
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
      //**** length read
      read_00102_len = 8;
      read_00102 = (unsigned char*)cgc_malloc(read_00102_len);
      int read_00102_res = cgc_length_read(0, read_00102, read_00102_len);
      if (read_00102_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00102_00000[] = 
         "\x02\x0c\x03\x01\xff\x86\x02\x00";
      read_00102_ptr += cgc_data_match(read_00102 + read_00102_ptr, read_00102_len - read_00102_ptr, match_00102_00000, 8);
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x0c";
      static unsigned int write_00101_00000_len = 1;
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
      //**** length read
      read_00103_len = 8;
      read_00103 = (unsigned char*)cgc_malloc(read_00103_len);
      int read_00103_res = cgc_length_read(0, read_00103, read_00103_len);
      if (read_00103_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00103_00000[] = 
         "\x03\x0c\x08\x01\xff\x6f\x02\x00";
      read_00103_ptr += cgc_data_match(read_00103 + read_00103_ptr, read_00103_len - read_00103_ptr, match_00103_00000, 8);
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x0c";
      static unsigned int write_00102_00000_len = 1;
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
      //**** length read
      read_00104_len = 8;
      read_00104 = (unsigned char*)cgc_malloc(read_00104_len);
      int read_00104_res = cgc_length_read(0, read_00104, read_00104_len);
      if (read_00104_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00104_00000[] = 
         "\x04\x0c\x04\x01\xff\x9f\x02\x00";
      read_00104_ptr += cgc_data_match(read_00104 + read_00104_ptr, read_00104_len - read_00104_ptr, match_00104_00000, 8);
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x0c";
      static unsigned int write_00103_00000_len = 1;
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
      //**** length read
      read_00105_len = 8;
      read_00105 = (unsigned char*)cgc_malloc(read_00105_len);
      int read_00105_res = cgc_length_read(0, read_00105, read_00105_len);
      if (read_00105_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00105_00000[] = 
         "\x05\x0c\x01\x01\xff\x79\x02\x00";
      read_00105_ptr += cgc_data_match(read_00105 + read_00105_ptr, read_00105_len - read_00105_ptr, match_00105_00000, 8);
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x0c";
      static unsigned int write_00104_00000_len = 1;
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
      //**** length read
      read_00106_len = 8;
      read_00106 = (unsigned char*)cgc_malloc(read_00106_len);
      int read_00106_res = cgc_length_read(0, read_00106, read_00106_len);
      if (read_00106_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00106_00000[] = 
         "\x06\x0c\x01\x01\xff\x89\x02\x00";
      read_00106_ptr += cgc_data_match(read_00106 + read_00106_ptr, read_00106_len - read_00106_ptr, match_00106_00000, 8);
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x0c";
      static unsigned int write_00105_00000_len = 1;
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
      //**** length read
      read_00107_len = 8;
      read_00107 = (unsigned char*)cgc_malloc(read_00107_len);
      int read_00107_res = cgc_length_read(0, read_00107, read_00107_len);
      if (read_00107_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00107_00000[] = 
         "\x07\x0c\x07\x01\xff\x8e\x02\x00";
      read_00107_ptr += cgc_data_match(read_00107 + read_00107_ptr, read_00107_len - read_00107_ptr, match_00107_00000, 8);
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x0c";
      static unsigned int write_00106_00000_len = 1;
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
      //**** length read
      read_00108_len = 8;
      read_00108 = (unsigned char*)cgc_malloc(read_00108_len);
      int read_00108_res = cgc_length_read(0, read_00108, read_00108_len);
      if (read_00108_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00108_00000[] = 
         "\x08\x0c\x00\x01\xff\x8c\x02\x00";
      read_00108_ptr += cgc_data_match(read_00108 + read_00108_ptr, read_00108_len - read_00108_ptr, match_00108_00000, 8);
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x0c";
      static unsigned int write_00107_00000_len = 1;
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
      //**** length read
      read_00109_len = 8;
      read_00109 = (unsigned char*)cgc_malloc(read_00109_len);
      int read_00109_res = cgc_length_read(0, read_00109, read_00109_len);
      if (read_00109_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00109_00000[] = 
         "\x09\x0c\x0c\x01\xff\x75\x02\x00";
      read_00109_ptr += cgc_data_match(read_00109 + read_00109_ptr, read_00109_len - read_00109_ptr, match_00109_00000, 8);
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x0c";
      static unsigned int write_00108_00000_len = 1;
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
      //**** length read
      read_00110_len = 8;
      read_00110 = (unsigned char*)cgc_malloc(read_00110_len);
      int read_00110_res = cgc_length_read(0, read_00110, read_00110_len);
      if (read_00110_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00110_00000[] = 
         "\x0a\x0c\x07\x01\xff\x8b\x02\x00";
      read_00110_ptr += cgc_data_match(read_00110 + read_00110_ptr, read_00110_len - read_00110_ptr, match_00110_00000, 8);
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x0c";
      static unsigned int write_00109_00000_len = 1;
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
      //**** length read
      read_00111_len = 8;
      read_00111 = (unsigned char*)cgc_malloc(read_00111_len);
      int read_00111_res = cgc_length_read(0, read_00111, read_00111_len);
      if (read_00111_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00111_00000[] = 
         "\x01\x0c\x09\x01\xff\x96\x02\x00";
      read_00111_ptr += cgc_data_match(read_00111 + read_00111_ptr, read_00111_len - read_00111_ptr, match_00111_00000, 8);
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x0c";
      static unsigned int write_00110_00000_len = 1;
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
      //**** length read
      read_00112_len = 8;
      read_00112 = (unsigned char*)cgc_malloc(read_00112_len);
      int read_00112_res = cgc_length_read(0, read_00112, read_00112_len);
      if (read_00112_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00112_00000[] = 
         "\x02\x0c\x10\x01\xff\x8f\x02\x00";
      read_00112_ptr += cgc_data_match(read_00112 + read_00112_ptr, read_00112_len - read_00112_ptr, match_00112_00000, 8);
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x0c";
      static unsigned int write_00111_00000_len = 1;
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
      //**** length read
      read_00113_len = 8;
      read_00113 = (unsigned char*)cgc_malloc(read_00113_len);
      int read_00113_res = cgc_length_read(0, read_00113, read_00113_len);
      if (read_00113_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00113_00000[] = 
         "\x03\x0c\x04\x01\xff\x73\x02\x00";
      read_00113_ptr += cgc_data_match(read_00113 + read_00113_ptr, read_00113_len - read_00113_ptr, match_00113_00000, 8);
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x0c";
      static unsigned int write_00112_00000_len = 1;
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
      //**** length read
      read_00114_len = 8;
      read_00114 = (unsigned char*)cgc_malloc(read_00114_len);
      int read_00114_res = cgc_length_read(0, read_00114, read_00114_len);
      if (read_00114_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00114_00000[] = 
         "\x04\x0c\x01\x01\xff\xa7\x02\x00";
      read_00114_ptr += cgc_data_match(read_00114 + read_00114_ptr, read_00114_len - read_00114_ptr, match_00114_00000, 8);
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x0c";
      static unsigned int write_00113_00000_len = 1;
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
      //**** length read
      read_00115_len = 8;
      read_00115 = (unsigned char*)cgc_malloc(read_00115_len);
      int read_00115_res = cgc_length_read(0, read_00115, read_00115_len);
      if (read_00115_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00115_00000[] = 
         "\x05\x0c\x08\x01\xff\x84\x02\x00";
      read_00115_ptr += cgc_data_match(read_00115 + read_00115_ptr, read_00115_len - read_00115_ptr, match_00115_00000, 8);
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x0c";
      static unsigned int write_00114_00000_len = 1;
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
      //**** length read
      read_00116_len = 8;
      read_00116 = (unsigned char*)cgc_malloc(read_00116_len);
      int read_00116_res = cgc_length_read(0, read_00116, read_00116_len);
      if (read_00116_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00116_00000[] = 
         "\x06\x0c\x10\x01\xff\x94\x02\x00";
      read_00116_ptr += cgc_data_match(read_00116 + read_00116_ptr, read_00116_len - read_00116_ptr, match_00116_00000, 8);
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x0c";
      static unsigned int write_00115_00000_len = 1;
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
      //**** length read
      read_00117_len = 8;
      read_00117 = (unsigned char*)cgc_malloc(read_00117_len);
      int read_00117_res = cgc_length_read(0, read_00117, read_00117_len);
      if (read_00117_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00117_00000[] = 
         "\x07\x0c\x00\x01\xff\x93\x02\x00";
      read_00117_ptr += cgc_data_match(read_00117 + read_00117_ptr, read_00117_len - read_00117_ptr, match_00117_00000, 8);
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x0c";
      static unsigned int write_00116_00000_len = 1;
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
      //**** length read
      read_00118_len = 8;
      read_00118 = (unsigned char*)cgc_malloc(read_00118_len);
      int read_00118_res = cgc_length_read(0, read_00118, read_00118_len);
      if (read_00118_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00118_00000[] = 
         "\x08\x0c\x10\x01\xff\x98\x02\x00";
      read_00118_ptr += cgc_data_match(read_00118 + read_00118_ptr, read_00118_len - read_00118_ptr, match_00118_00000, 8);
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x0c";
      static unsigned int write_00117_00000_len = 1;
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
      //**** length read
      read_00119_len = 8;
      read_00119 = (unsigned char*)cgc_malloc(read_00119_len);
      int read_00119_res = cgc_length_read(0, read_00119, read_00119_len);
      if (read_00119_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00119_00000[] = 
         "\x09\x0c\x0c\x01\xff\x75\x02\x00";
      read_00119_ptr += cgc_data_match(read_00119 + read_00119_ptr, read_00119_len - read_00119_ptr, match_00119_00000, 8);
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x0c";
      static unsigned int write_00118_00000_len = 1;
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
      //**** length read
      read_00120_len = 8;
      read_00120 = (unsigned char*)cgc_malloc(read_00120_len);
      int read_00120_res = cgc_length_read(0, read_00120, read_00120_len);
      if (read_00120_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00120_00000[] = 
         "\x0a\x0c\x05\x01\xff\x90\x02\x00";
      read_00120_ptr += cgc_data_match(read_00120 + read_00120_ptr, read_00120_len - read_00120_ptr, match_00120_00000, 8);
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x0c";
      static unsigned int write_00119_00000_len = 1;
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
      //**** length read
      read_00121_len = 8;
      read_00121 = (unsigned char*)cgc_malloc(read_00121_len);
      int read_00121_res = cgc_length_read(0, read_00121, read_00121_len);
      if (read_00121_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00121_00000[] = 
         "\x01\x0c\x01\x01\xff\x99\x02\x00";
      read_00121_ptr += cgc_data_match(read_00121 + read_00121_ptr, read_00121_len - read_00121_ptr, match_00121_00000, 8);
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x0c";
      static unsigned int write_00120_00000_len = 1;
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
      //**** length read
      read_00122_len = 8;
      read_00122 = (unsigned char*)cgc_malloc(read_00122_len);
      int read_00122_res = cgc_length_read(0, read_00122, read_00122_len);
      if (read_00122_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00122_00000[] = 
         "\x02\x0c\x03\x01\xff\x8b\x02\x00";
      read_00122_ptr += cgc_data_match(read_00122 + read_00122_ptr, read_00122_len - read_00122_ptr, match_00122_00000, 8);
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x0c";
      static unsigned int write_00121_00000_len = 1;
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
      //**** length read
      read_00123_len = 8;
      read_00123 = (unsigned char*)cgc_malloc(read_00123_len);
      int read_00123_res = cgc_length_read(0, read_00123, read_00123_len);
      if (read_00123_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00123_00000[] = 
         "\x03\x0c\x04\x01\xff\x7b\x02\x00";
      read_00123_ptr += cgc_data_match(read_00123 + read_00123_ptr, read_00123_len - read_00123_ptr, match_00123_00000, 8);
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x0c";
      static unsigned int write_00122_00000_len = 1;
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
      //**** length read
      read_00124_len = 8;
      read_00124 = (unsigned char*)cgc_malloc(read_00124_len);
      int read_00124_res = cgc_length_read(0, read_00124, read_00124_len);
      if (read_00124_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00124_00000[] = 
         "\x04\x0c\x10\x01\xff\xb2\x02\x00";
      read_00124_ptr += cgc_data_match(read_00124 + read_00124_ptr, read_00124_len - read_00124_ptr, match_00124_00000, 8);
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x0c";
      static unsigned int write_00123_00000_len = 1;
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
      //**** length read
      read_00125_len = 8;
      read_00125 = (unsigned char*)cgc_malloc(read_00125_len);
      int read_00125_res = cgc_length_read(0, read_00125, read_00125_len);
      if (read_00125_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00125_00000[] = 
         "\x05\x0c\x04\x01\xff\x88\x02\x00";
      read_00125_ptr += cgc_data_match(read_00125 + read_00125_ptr, read_00125_len - read_00125_ptr, match_00125_00000, 8);
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x0c";
      static unsigned int write_00124_00000_len = 1;
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
      //**** length read
      read_00126_len = 8;
      read_00126 = (unsigned char*)cgc_malloc(read_00126_len);
      int read_00126_res = cgc_length_read(0, read_00126, read_00126_len);
      if (read_00126_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00126_00000[] = 
         "\x06\x0c\x03\x01\xff\x90\x02\x00";
      read_00126_ptr += cgc_data_match(read_00126 + read_00126_ptr, read_00126_len - read_00126_ptr, match_00126_00000, 8);
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x0c";
      static unsigned int write_00125_00000_len = 1;
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
      //**** length read
      read_00127_len = 8;
      read_00127 = (unsigned char*)cgc_malloc(read_00127_len);
      int read_00127_res = cgc_length_read(0, read_00127, read_00127_len);
      if (read_00127_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00127_00000[] = 
         "\x07\x0c\x00\x01\xff\x9f\x02\x00";
      read_00127_ptr += cgc_data_match(read_00127 + read_00127_ptr, read_00127_len - read_00127_ptr, match_00127_00000, 8);
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x0c";
      static unsigned int write_00126_00000_len = 1;
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
      //**** length read
      read_00128_len = 8;
      read_00128 = (unsigned char*)cgc_malloc(read_00128_len);
      int read_00128_res = cgc_length_read(0, read_00128, read_00128_len);
      if (read_00128_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00128_00000[] = 
         "\x08\x0c\x0c\x01\xff\x94\x02\x00";
      read_00128_ptr += cgc_data_match(read_00128 + read_00128_ptr, read_00128_len - read_00128_ptr, match_00128_00000, 8);
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x0c";
      static unsigned int write_00127_00000_len = 1;
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
      //**** length read
      read_00129_len = 8;
      read_00129 = (unsigned char*)cgc_malloc(read_00129_len);
      int read_00129_res = cgc_length_read(0, read_00129, read_00129_len);
      if (read_00129_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00129_00000[] = 
         "\x09\x0c\x0c\x01\xff\x75\x02\x00";
      read_00129_ptr += cgc_data_match(read_00129 + read_00129_ptr, read_00129_len - read_00129_ptr, match_00129_00000, 8);
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x0c";
      static unsigned int write_00128_00000_len = 1;
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
      //**** length read
      read_00130_len = 8;
      read_00130 = (unsigned char*)cgc_malloc(read_00130_len);
      int read_00130_res = cgc_length_read(0, read_00130, read_00130_len);
      if (read_00130_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00130_00000[] = 
         "\x0a\x0c\x08\x01\xff\x97\x02\x00";
      read_00130_ptr += cgc_data_match(read_00130 + read_00130_ptr, read_00130_len - read_00130_ptr, match_00130_00000, 8);
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x0c";
      static unsigned int write_00129_00000_len = 1;
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
      //**** length read
      read_00131_len = 8;
      read_00131 = (unsigned char*)cgc_malloc(read_00131_len);
      int read_00131_res = cgc_length_read(0, read_00131, read_00131_len);
      if (read_00131_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00131_00000[] = 
         "\x01\x0c\x07\x01\xff\xa4\x02\x00";
      read_00131_ptr += cgc_data_match(read_00131 + read_00131_ptr, read_00131_len - read_00131_ptr, match_00131_00000, 8);
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x0c";
      static unsigned int write_00130_00000_len = 1;
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
      //**** length read
      read_00132_len = 8;
      read_00132 = (unsigned char*)cgc_malloc(read_00132_len);
      int read_00132_res = cgc_length_read(0, read_00132, read_00132_len);
      if (read_00132_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00132_00000[] = 
         "\x02\x0c\x00\x01\xff\x94\x02\x00";
      read_00132_ptr += cgc_data_match(read_00132 + read_00132_ptr, read_00132_len - read_00132_ptr, match_00132_00000, 8);
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x0c";
      static unsigned int write_00131_00000_len = 1;
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
      //**** length read
      read_00133_len = 8;
      read_00133 = (unsigned char*)cgc_malloc(read_00133_len);
      int read_00133_res = cgc_length_read(0, read_00133, read_00133_len);
      if (read_00133_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00133_00000[] = 
         "\x03\x0c\x09\x01\xff\x83\x02\x00";
      read_00133_ptr += cgc_data_match(read_00133 + read_00133_ptr, read_00133_len - read_00133_ptr, match_00133_00000, 8);
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x0c";
      static unsigned int write_00132_00000_len = 1;
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
      //**** length read
      read_00134_len = 8;
      read_00134 = (unsigned char*)cgc_malloc(read_00134_len);
      int read_00134_res = cgc_length_read(0, read_00134, read_00134_len);
      if (read_00134_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00134_00000[] = 
         "\x04\x0c\x03\x01\xff\xae\x02\x00";
      read_00134_ptr += cgc_data_match(read_00134 + read_00134_ptr, read_00134_len - read_00134_ptr, match_00134_00000, 8);
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x0c";
      static unsigned int write_00133_00000_len = 1;
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
      //**** length read
      read_00135_len = 8;
      read_00135 = (unsigned char*)cgc_malloc(read_00135_len);
      int read_00135_res = cgc_length_read(0, read_00135, read_00135_len);
      if (read_00135_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00135_00000[] = 
         "\x05\x0c\x10\x01\xff\x90\x02\x00";
      read_00135_ptr += cgc_data_match(read_00135 + read_00135_ptr, read_00135_len - read_00135_ptr, match_00135_00000, 8);
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x0c";
      static unsigned int write_00134_00000_len = 1;
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
      //**** length read
      read_00136_len = 8;
      read_00136 = (unsigned char*)cgc_malloc(read_00136_len);
      int read_00136_res = cgc_length_read(0, read_00136, read_00136_len);
      if (read_00136_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00136_00000[] = 
         "\x06\x0c\x08\x01\xff\x99\x02\x00";
      read_00136_ptr += cgc_data_match(read_00136 + read_00136_ptr, read_00136_len - read_00136_ptr, match_00136_00000, 8);
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x0c";
      static unsigned int write_00135_00000_len = 1;
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
      //**** length read
      read_00137_len = 8;
      read_00137 = (unsigned char*)cgc_malloc(read_00137_len);
      int read_00137_res = cgc_length_read(0, read_00137, read_00137_len);
      if (read_00137_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00137_00000[] = 
         "\x07\x0c\x08\x01\xff\xab\x02\x00";
      read_00137_ptr += cgc_data_match(read_00137 + read_00137_ptr, read_00137_len - read_00137_ptr, match_00137_00000, 8);
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x0c";
      static unsigned int write_00136_00000_len = 1;
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
      //**** length read
      read_00138_len = 8;
      read_00138 = (unsigned char*)cgc_malloc(read_00138_len);
      int read_00138_res = cgc_length_read(0, read_00138, read_00138_len);
      if (read_00138_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00138_00000[] = 
         "\x08\x0c\x0c\x01\xff\x94\x02\x00";
      read_00138_ptr += cgc_data_match(read_00138 + read_00138_ptr, read_00138_len - read_00138_ptr, match_00138_00000, 8);
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x0c";
      static unsigned int write_00137_00000_len = 1;
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
      //**** length read
      read_00139_len = 8;
      read_00139 = (unsigned char*)cgc_malloc(read_00139_len);
      int read_00139_res = cgc_length_read(0, read_00139, read_00139_len);
      if (read_00139_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00139_00000[] = 
         "\x09\x0c\x00\x01\xff\x75\x02\x00";
      read_00139_ptr += cgc_data_match(read_00139 + read_00139_ptr, read_00139_len - read_00139_ptr, match_00139_00000, 8);
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x0c";
      static unsigned int write_00138_00000_len = 1;
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
      //**** length read
      read_00140_len = 8;
      read_00140 = (unsigned char*)cgc_malloc(read_00140_len);
      int read_00140_res = cgc_length_read(0, read_00140, read_00140_len);
      if (read_00140_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00140_00000[] = 
         "\x0a\x0c\x09\x01\xff\x9b\x02\x00";
      read_00140_ptr += cgc_data_match(read_00140 + read_00140_ptr, read_00140_len - read_00140_ptr, match_00140_00000, 8);
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x0c";
      static unsigned int write_00139_00000_len = 1;
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
      //**** length read
      read_00141_len = 8;
      read_00141 = (unsigned char*)cgc_malloc(read_00141_len);
      int read_00141_res = cgc_length_read(0, read_00141, read_00141_len);
      if (read_00141_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00141_00000[] = 
         "\x01\x0c\x05\x01\xff\xa9\x02\x00";
      read_00141_ptr += cgc_data_match(read_00141 + read_00141_ptr, read_00141_len - read_00141_ptr, match_00141_00000, 8);
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x0c";
      static unsigned int write_00140_00000_len = 1;
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
      //**** length read
      read_00142_len = 8;
      read_00142 = (unsigned char*)cgc_malloc(read_00142_len);
      int read_00142_res = cgc_length_read(0, read_00142, read_00142_len);
      if (read_00142_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00142_00000[] = 
         "\x02\x0c\x05\x01\xff\xa0\x02\x00";
      read_00142_ptr += cgc_data_match(read_00142 + read_00142_ptr, read_00142_len - read_00142_ptr, match_00142_00000, 8);
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x0c";
      static unsigned int write_00141_00000_len = 1;
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
      //**** length read
      read_00143_len = 8;
      read_00143 = (unsigned char*)cgc_malloc(read_00143_len);
      int read_00143_res = cgc_length_read(0, read_00143, read_00143_len);
      if (read_00143_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00143_00000[] = 
         "\x03\x0c\x00\x01\xff\x86\x02\x00";
      read_00143_ptr += cgc_data_match(read_00143 + read_00143_ptr, read_00143_len - read_00143_ptr, match_00143_00000, 8);
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x0c";
      static unsigned int write_00142_00000_len = 1;
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
      //**** length read
      read_00144_len = 8;
      read_00144 = (unsigned char*)cgc_malloc(read_00144_len);
      int read_00144_res = cgc_length_read(0, read_00144, read_00144_len);
      if (read_00144_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00144_00000[] = 
         "\x04\x0c\x05\x01\xff\xb7\x02\x00";
      read_00144_ptr += cgc_data_match(read_00144 + read_00144_ptr, read_00144_len - read_00144_ptr, match_00144_00000, 8);
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x0c";
      static unsigned int write_00143_00000_len = 1;
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
      //**** length read
      read_00145_len = 8;
      read_00145 = (unsigned char*)cgc_malloc(read_00145_len);
      int read_00145_res = cgc_length_read(0, read_00145, read_00145_len);
      if (read_00145_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00145_00000[] = 
         "\x05\x0c\x10\x01\xff\x8c\x02\x00";
      read_00145_ptr += cgc_data_match(read_00145 + read_00145_ptr, read_00145_len - read_00145_ptr, match_00145_00000, 8);
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x0c";
      static unsigned int write_00144_00000_len = 1;
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
      //**** length read
      read_00146_len = 8;
      read_00146 = (unsigned char*)cgc_malloc(read_00146_len);
      int read_00146_res = cgc_length_read(0, read_00146, read_00146_len);
      if (read_00146_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00146_00000[] = 
         "\x06\x0c\x04\x01\xff\x9d\x02\x00";
      read_00146_ptr += cgc_data_match(read_00146 + read_00146_ptr, read_00146_len - read_00146_ptr, match_00146_00000, 8);
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x0c";
      static unsigned int write_00145_00000_len = 1;
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
      //**** length read
      read_00147_len = 8;
      read_00147 = (unsigned char*)cgc_malloc(read_00147_len);
      int read_00147_res = cgc_length_read(0, read_00147, read_00147_len);
      if (read_00147_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00147_00000[] = 
         "\x07\x0c\x04\x01\xff\xaf\x02\x00";
      read_00147_ptr += cgc_data_match(read_00147 + read_00147_ptr, read_00147_len - read_00147_ptr, match_00147_00000, 8);
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00146_00000[] = 
         "\x0c";
      static unsigned int write_00146_00000_len = 1;
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = cgc_append_buf(write_00146, &write_00146_len, write_00146_00000, write_00146_00000_len);
      if (write_00146_len > 0) {
         cgc_transmit_all(1, write_00146, write_00146_len);
      }
      cgc_free(write_00146);
   } while (0);
   do {
      unsigned char *read_00148;
      unsigned int read_00148_len;
      unsigned int read_00148_ptr = 0;
      //**** length read
      read_00148_len = 8;
      read_00148 = (unsigned char*)cgc_malloc(read_00148_len);
      int read_00148_res = cgc_length_read(0, read_00148, read_00148_len);
      if (read_00148_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00148_00000[] = 
         "\x08\x0c\x03\x01\xff\x94\x02\x00";
      read_00148_ptr += cgc_data_match(read_00148 + read_00148_ptr, read_00148_len - read_00148_ptr, match_00148_00000, 8);
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x0c";
      static unsigned int write_00147_00000_len = 1;
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = cgc_append_buf(write_00147, &write_00147_len, write_00147_00000, write_00147_00000_len);
      if (write_00147_len > 0) {
         cgc_transmit_all(1, write_00147, write_00147_len);
      }
      cgc_free(write_00147);
   } while (0);
   do {
      unsigned char *read_00149;
      unsigned int read_00149_len;
      unsigned int read_00149_ptr = 0;
      //**** length read
      read_00149_len = 8;
      read_00149 = (unsigned char*)cgc_malloc(read_00149_len);
      int read_00149_res = cgc_length_read(0, read_00149, read_00149_len);
      if (read_00149_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00149_00000[] = 
         "\x09\x0c\x01\x01\xff\x81\x02\x00";
      read_00149_ptr += cgc_data_match(read_00149 + read_00149_ptr, read_00149_len - read_00149_ptr, match_00149_00000, 8);
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00148_00000[] = 
         "\x0c";
      static unsigned int write_00148_00000_len = 1;
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = cgc_append_buf(write_00148, &write_00148_len, write_00148_00000, write_00148_00000_len);
      if (write_00148_len > 0) {
         cgc_transmit_all(1, write_00148, write_00148_len);
      }
      cgc_free(write_00148);
   } while (0);
   do {
      unsigned char *read_00150;
      unsigned int read_00150_len;
      unsigned int read_00150_ptr = 0;
      //**** length read
      read_00150_len = 8;
      read_00150 = (unsigned char*)cgc_malloc(read_00150_len);
      int read_00150_res = cgc_length_read(0, read_00150, read_00150_len);
      if (read_00150_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00150_00000[] = 
         "\x0a\x0c\x07\x01\xff\x9e\x02\x00";
      read_00150_ptr += cgc_data_match(read_00150 + read_00150_ptr, read_00150_len - read_00150_ptr, match_00150_00000, 8);
      cgc_free(read_00150);
      if (read_00150_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x0c";
      static unsigned int write_00149_00000_len = 1;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = cgc_append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         cgc_transmit_all(1, write_00149, write_00149_len);
      }
      cgc_free(write_00149);
   } while (0);
   do {
      unsigned char *read_00151;
      unsigned int read_00151_len;
      unsigned int read_00151_ptr = 0;
      //**** length read
      read_00151_len = 8;
      read_00151 = (unsigned char*)cgc_malloc(read_00151_len);
      int read_00151_res = cgc_length_read(0, read_00151, read_00151_len);
      if (read_00151_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00151_00000[] = 
         "\x01\x0c\x04\x01\xff\xb0\x02\x00";
      read_00151_ptr += cgc_data_match(read_00151 + read_00151_ptr, read_00151_len - read_00151_ptr, match_00151_00000, 8);
      cgc_free(read_00151);
      if (read_00151_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00150_00000[] = 
         "\x0c";
      static unsigned int write_00150_00000_len = 1;
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = cgc_append_buf(write_00150, &write_00150_len, write_00150_00000, write_00150_00000_len);
      if (write_00150_len > 0) {
         cgc_transmit_all(1, write_00150, write_00150_len);
      }
      cgc_free(write_00150);
   } while (0);
   do {
      unsigned char *read_00152;
      unsigned int read_00152_len;
      unsigned int read_00152_ptr = 0;
      //**** length read
      read_00152_len = 8;
      read_00152 = (unsigned char*)cgc_malloc(read_00152_len);
      int read_00152_res = cgc_length_read(0, read_00152, read_00152_len);
      if (read_00152_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00152_00000[] = 
         "\x02\x0c\x05\x01\xff\xa7\x02\x00";
      read_00152_ptr += cgc_data_match(read_00152 + read_00152_ptr, read_00152_len - read_00152_ptr, match_00152_00000, 8);
      cgc_free(read_00152);
      if (read_00152_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x0c";
      static unsigned int write_00151_00000_len = 1;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = cgc_append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         cgc_transmit_all(1, write_00151, write_00151_len);
      }
      cgc_free(write_00151);
   } while (0);
   do {
      unsigned char *read_00153;
      unsigned int read_00153_len;
      unsigned int read_00153_ptr = 0;
      //**** length read
      read_00153_len = 8;
      read_00153 = (unsigned char*)cgc_malloc(read_00153_len);
      int read_00153_res = cgc_length_read(0, read_00153, read_00153_len);
      if (read_00153_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00153_00000[] = 
         "\x03\x0c\x03\x01\xff\x92\x02\x00";
      read_00153_ptr += cgc_data_match(read_00153 + read_00153_ptr, read_00153_len - read_00153_ptr, match_00153_00000, 8);
      cgc_free(read_00153);
      if (read_00153_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00152_00000[] = 
         "\x0c";
      static unsigned int write_00152_00000_len = 1;
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = cgc_append_buf(write_00152, &write_00152_len, write_00152_00000, write_00152_00000_len);
      if (write_00152_len > 0) {
         cgc_transmit_all(1, write_00152, write_00152_len);
      }
      cgc_free(write_00152);
   } while (0);
   do {
      unsigned char *read_00154;
      unsigned int read_00154_len;
      unsigned int read_00154_ptr = 0;
      //**** length read
      read_00154_len = 8;
      read_00154 = (unsigned char*)cgc_malloc(read_00154_len);
      int read_00154_res = cgc_length_read(0, read_00154, read_00154_len);
      if (read_00154_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00154_00000[] = 
         "\x04\x0c\x05\x01\xff\xbe\x02\x00";
      read_00154_ptr += cgc_data_match(read_00154 + read_00154_ptr, read_00154_len - read_00154_ptr, match_00154_00000, 8);
      cgc_free(read_00154);
      if (read_00154_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x0c";
      static unsigned int write_00153_00000_len = 1;
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = cgc_append_buf(write_00153, &write_00153_len, write_00153_00000, write_00153_00000_len);
      if (write_00153_len > 0) {
         cgc_transmit_all(1, write_00153, write_00153_len);
      }
      cgc_free(write_00153);
   } while (0);
   do {
      unsigned char *read_00155;
      unsigned int read_00155_len;
      unsigned int read_00155_ptr = 0;
      //**** length read
      read_00155_len = 8;
      read_00155 = (unsigned char*)cgc_malloc(read_00155_len);
      int read_00155_res = cgc_length_read(0, read_00155, read_00155_len);
      if (read_00155_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00155_00000[] = 
         "\x05\x0c\x09\x01\xff\x88\x02\x00";
      read_00155_ptr += cgc_data_match(read_00155 + read_00155_ptr, read_00155_len - read_00155_ptr, match_00155_00000, 8);
      cgc_free(read_00155);
      if (read_00155_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00154_00000[] = 
         "\x0c";
      static unsigned int write_00154_00000_len = 1;
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = cgc_append_buf(write_00154, &write_00154_len, write_00154_00000, write_00154_00000_len);
      if (write_00154_len > 0) {
         cgc_transmit_all(1, write_00154, write_00154_len);
      }
      cgc_free(write_00154);
   } while (0);
   do {
      unsigned char *read_00156;
      unsigned int read_00156_len;
      unsigned int read_00156_ptr = 0;
      //**** length read
      read_00156_len = 8;
      read_00156 = (unsigned char*)cgc_malloc(read_00156_len);
      int read_00156_res = cgc_length_read(0, read_00156, read_00156_len);
      if (read_00156_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00156_00000[] = 
         "\x06\x0c\x08\x01\xff\xa5\x02\x00";
      read_00156_ptr += cgc_data_match(read_00156 + read_00156_ptr, read_00156_len - read_00156_ptr, match_00156_00000, 8);
      cgc_free(read_00156);
      if (read_00156_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x0c";
      static unsigned int write_00155_00000_len = 1;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = cgc_append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         cgc_transmit_all(1, write_00155, write_00155_len);
      }
      cgc_free(write_00155);
   } while (0);
   do {
      unsigned char *read_00157;
      unsigned int read_00157_len;
      unsigned int read_00157_ptr = 0;
      //**** length read
      read_00157_len = 8;
      read_00157 = (unsigned char*)cgc_malloc(read_00157_len);
      int read_00157_res = cgc_length_read(0, read_00157, read_00157_len);
      if (read_00157_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00157_00000[] = 
         "\x07\x0c\x00\x01\xff\xb7\x02\x00";
      read_00157_ptr += cgc_data_match(read_00157 + read_00157_ptr, read_00157_len - read_00157_ptr, match_00157_00000, 8);
      cgc_free(read_00157);
      if (read_00157_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00156_00000[] = 
         "\x0c";
      static unsigned int write_00156_00000_len = 1;
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = cgc_append_buf(write_00156, &write_00156_len, write_00156_00000, write_00156_00000_len);
      if (write_00156_len > 0) {
         cgc_transmit_all(1, write_00156, write_00156_len);
      }
      cgc_free(write_00156);
   } while (0);
   do {
      unsigned char *read_00158;
      unsigned int read_00158_len;
      unsigned int read_00158_ptr = 0;
      //**** length read
      read_00158_len = 8;
      read_00158 = (unsigned char*)cgc_malloc(read_00158_len);
      int read_00158_res = cgc_length_read(0, read_00158, read_00158_len);
      if (read_00158_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00158_00000[] = 
         "\x08\x0c\x10\x01\xff\x9d\x02\x00";
      read_00158_ptr += cgc_data_match(read_00158 + read_00158_ptr, read_00158_len - read_00158_ptr, match_00158_00000, 8);
      cgc_free(read_00158);
      if (read_00158_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x0c";
      static unsigned int write_00157_00000_len = 1;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = cgc_append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         cgc_transmit_all(1, write_00157, write_00157_len);
      }
      cgc_free(write_00157);
   } while (0);
   do {
      unsigned char *read_00159;
      unsigned int read_00159_len;
      unsigned int read_00159_ptr = 0;
      //**** length read
      read_00159_len = 8;
      read_00159 = (unsigned char*)cgc_malloc(read_00159_len);
      int read_00159_res = cgc_length_read(0, read_00159, read_00159_len);
      if (read_00159_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00159_00000[] = 
         "\x09\x0c\x01\x01\xff\x8c\x02\x00";
      read_00159_ptr += cgc_data_match(read_00159 + read_00159_ptr, read_00159_len - read_00159_ptr, match_00159_00000, 8);
      cgc_free(read_00159);
      if (read_00159_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00158_00000[] = 
         "\x0c";
      static unsigned int write_00158_00000_len = 1;
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = cgc_append_buf(write_00158, &write_00158_len, write_00158_00000, write_00158_00000_len);
      if (write_00158_len > 0) {
         cgc_transmit_all(1, write_00158, write_00158_len);
      }
      cgc_free(write_00158);
   } while (0);
   do {
      unsigned char *read_00160;
      unsigned int read_00160_len;
      unsigned int read_00160_ptr = 0;
      //**** length read
      read_00160_len = 8;
      read_00160 = (unsigned char*)cgc_malloc(read_00160_len);
      int read_00160_res = cgc_length_read(0, read_00160, read_00160_len);
      if (read_00160_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00160_00000[] = 
         "\x0a\x0c\x04\x01\xff\xa3\x02\x00";
      read_00160_ptr += cgc_data_match(read_00160 + read_00160_ptr, read_00160_len - read_00160_ptr, match_00160_00000, 8);
      cgc_free(read_00160);
      if (read_00160_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x0c";
      static unsigned int write_00159_00000_len = 1;
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = cgc_append_buf(write_00159, &write_00159_len, write_00159_00000, write_00159_00000_len);
      if (write_00159_len > 0) {
         cgc_transmit_all(1, write_00159, write_00159_len);
      }
      cgc_free(write_00159);
   } while (0);
   do {
      unsigned char *read_00161;
      unsigned int read_00161_len;
      unsigned int read_00161_ptr = 0;
      //**** length read
      read_00161_len = 8;
      read_00161 = (unsigned char*)cgc_malloc(read_00161_len);
      int read_00161_res = cgc_length_read(0, read_00161, read_00161_len);
      if (read_00161_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00161_00000[] = 
         "\x01\x0c\x10\x01\xff\xb8\x02\x00";
      read_00161_ptr += cgc_data_match(read_00161 + read_00161_ptr, read_00161_len - read_00161_ptr, match_00161_00000, 8);
      cgc_free(read_00161);
      if (read_00161_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00160_00000[] = 
         "\x0c";
      static unsigned int write_00160_00000_len = 1;
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = cgc_append_buf(write_00160, &write_00160_len, write_00160_00000, write_00160_00000_len);
      if (write_00160_len > 0) {
         cgc_transmit_all(1, write_00160, write_00160_len);
      }
      cgc_free(write_00160);
   } while (0);
   do {
      unsigned char *read_00162;
      unsigned int read_00162_len;
      unsigned int read_00162_ptr = 0;
      //**** length read
      read_00162_len = 8;
      read_00162 = (unsigned char*)cgc_malloc(read_00162_len);
      int read_00162_res = cgc_length_read(0, read_00162, read_00162_len);
      if (read_00162_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00162_00000[] = 
         "\x02\x0c\x08\x01\xff\xae\x02\x00";
      read_00162_ptr += cgc_data_match(read_00162 + read_00162_ptr, read_00162_len - read_00162_ptr, match_00162_00000, 8);
      cgc_free(read_00162);
      if (read_00162_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x0c";
      static unsigned int write_00161_00000_len = 1;
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = cgc_append_buf(write_00161, &write_00161_len, write_00161_00000, write_00161_00000_len);
      if (write_00161_len > 0) {
         cgc_transmit_all(1, write_00161, write_00161_len);
      }
      cgc_free(write_00161);
   } while (0);
   do {
      unsigned char *read_00163;
      unsigned int read_00163_len;
      unsigned int read_00163_ptr = 0;
      //**** length read
      read_00163_len = 8;
      read_00163 = (unsigned char*)cgc_malloc(read_00163_len);
      int read_00163_res = cgc_length_read(0, read_00163, read_00163_len);
      if (read_00163_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00163_00000[] = 
         "\x03\x0c\x10\x01\xff\x9b\x02\x00";
      read_00163_ptr += cgc_data_match(read_00163 + read_00163_ptr, read_00163_len - read_00163_ptr, match_00163_00000, 8);
      cgc_free(read_00163);
      if (read_00163_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00162_00000[] = 
         "\x0c";
      static unsigned int write_00162_00000_len = 1;
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = cgc_append_buf(write_00162, &write_00162_len, write_00162_00000, write_00162_00000_len);
      if (write_00162_len > 0) {
         cgc_transmit_all(1, write_00162, write_00162_len);
      }
      cgc_free(write_00162);
   } while (0);
   do {
      unsigned char *read_00164;
      unsigned int read_00164_len;
      unsigned int read_00164_ptr = 0;
      //**** length read
      read_00164_len = 8;
      read_00164 = (unsigned char*)cgc_malloc(read_00164_len);
      int read_00164_res = cgc_length_read(0, read_00164, read_00164_len);
      if (read_00164_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00164_00000[] = 
         "\x04\x0c\x01\x01\xff\xc5\x02\x00";
      read_00164_ptr += cgc_data_match(read_00164 + read_00164_ptr, read_00164_len - read_00164_ptr, match_00164_00000, 8);
      cgc_free(read_00164);
      if (read_00164_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x0c";
      static unsigned int write_00163_00000_len = 1;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = cgc_append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         cgc_transmit_all(1, write_00163, write_00163_len);
      }
      cgc_free(write_00163);
   } while (0);
   do {
      unsigned char *read_00165;
      unsigned int read_00165_len;
      unsigned int read_00165_ptr = 0;
      //**** length read
      read_00165_len = 8;
      read_00165 = (unsigned char*)cgc_malloc(read_00165_len);
      int read_00165_res = cgc_length_read(0, read_00165, read_00165_len);
      if (read_00165_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00165_00000[] = 
         "\x05\x0c\x01\x01\xff\x8b\x02\x00";
      read_00165_ptr += cgc_data_match(read_00165 + read_00165_ptr, read_00165_len - read_00165_ptr, match_00165_00000, 8);
      cgc_free(read_00165);
      if (read_00165_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00164_00000[] = 
         "\x0c";
      static unsigned int write_00164_00000_len = 1;
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = cgc_append_buf(write_00164, &write_00164_len, write_00164_00000, write_00164_00000_len);
      if (write_00164_len > 0) {
         cgc_transmit_all(1, write_00164, write_00164_len);
      }
      cgc_free(write_00164);
   } while (0);
   do {
      unsigned char *read_00166;
      unsigned int read_00166_len;
      unsigned int read_00166_ptr = 0;
      //**** length read
      read_00166_len = 8;
      read_00166 = (unsigned char*)cgc_malloc(read_00166_len);
      int read_00166_res = cgc_length_read(0, read_00166, read_00166_len);
      if (read_00166_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00166_00000[] = 
         "\x06\x0c\x01\x01\xff\xa9\x02\x00";
      read_00166_ptr += cgc_data_match(read_00166 + read_00166_ptr, read_00166_len - read_00166_ptr, match_00166_00000, 8);
      cgc_free(read_00166);
      if (read_00166_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x0c";
      static unsigned int write_00165_00000_len = 1;
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = cgc_append_buf(write_00165, &write_00165_len, write_00165_00000, write_00165_00000_len);
      if (write_00165_len > 0) {
         cgc_transmit_all(1, write_00165, write_00165_len);
      }
      cgc_free(write_00165);
   } while (0);
   do {
      unsigned char *read_00167;
      unsigned int read_00167_len;
      unsigned int read_00167_ptr = 0;
      //**** length read
      read_00167_len = 8;
      read_00167 = (unsigned char*)cgc_malloc(read_00167_len);
      int read_00167_res = cgc_length_read(0, read_00167, read_00167_len);
      if (read_00167_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00167_00000[] = 
         "\x07\x0c\x07\x01\xff\xc3\x02\x00";
      read_00167_ptr += cgc_data_match(read_00167 + read_00167_ptr, read_00167_len - read_00167_ptr, match_00167_00000, 8);
      cgc_free(read_00167);
      if (read_00167_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00166_00000[] = 
         "\x0c";
      static unsigned int write_00166_00000_len = 1;
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = cgc_append_buf(write_00166, &write_00166_len, write_00166_00000, write_00166_00000_len);
      if (write_00166_len > 0) {
         cgc_transmit_all(1, write_00166, write_00166_len);
      }
      cgc_free(write_00166);
   } while (0);
   do {
      unsigned char *read_00168;
      unsigned int read_00168_len;
      unsigned int read_00168_ptr = 0;
      //**** length read
      read_00168_len = 8;
      read_00168 = (unsigned char*)cgc_malloc(read_00168_len);
      int read_00168_res = cgc_length_read(0, read_00168, read_00168_len);
      if (read_00168_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00168_00000[] = 
         "\x08\x0c\x08\x01\xff\x99\x02\x00";
      read_00168_ptr += cgc_data_match(read_00168 + read_00168_ptr, read_00168_len - read_00168_ptr, match_00168_00000, 8);
      cgc_free(read_00168);
      if (read_00168_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x0c";
      static unsigned int write_00167_00000_len = 1;
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = cgc_append_buf(write_00167, &write_00167_len, write_00167_00000, write_00167_00000_len);
      if (write_00167_len > 0) {
         cgc_transmit_all(1, write_00167, write_00167_len);
      }
      cgc_free(write_00167);
   } while (0);
   do {
      unsigned char *read_00169;
      unsigned int read_00169_len;
      unsigned int read_00169_ptr = 0;
      //**** length read
      read_00169_len = 8;
      read_00169 = (unsigned char*)cgc_malloc(read_00169_len);
      int read_00169_res = cgc_length_read(0, read_00169, read_00169_len);
      if (read_00169_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00169_00000[] = 
         "\x09\x0c\x05\x01\xff\x97\x02\x00";
      read_00169_ptr += cgc_data_match(read_00169 + read_00169_ptr, read_00169_len - read_00169_ptr, match_00169_00000, 8);
      cgc_free(read_00169);
      if (read_00169_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00168_00000[] = 
         "\x0c";
      static unsigned int write_00168_00000_len = 1;
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = cgc_append_buf(write_00168, &write_00168_len, write_00168_00000, write_00168_00000_len);
      if (write_00168_len > 0) {
         cgc_transmit_all(1, write_00168, write_00168_len);
      }
      cgc_free(write_00168);
   } while (0);
   do {
      unsigned char *read_00170;
      unsigned int read_00170_len;
      unsigned int read_00170_ptr = 0;
      //**** length read
      read_00170_len = 8;
      read_00170 = (unsigned char*)cgc_malloc(read_00170_len);
      int read_00170_res = cgc_length_read(0, read_00170, read_00170_len);
      if (read_00170_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00170_00000[] = 
         "\x0a\x0c\x00\x01\xff\xab\x02\x00";
      read_00170_ptr += cgc_data_match(read_00170 + read_00170_ptr, read_00170_len - read_00170_ptr, match_00170_00000, 8);
      cgc_free(read_00170);
      if (read_00170_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x0c";
      static unsigned int write_00169_00000_len = 1;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = cgc_append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         cgc_transmit_all(1, write_00169, write_00169_len);
      }
      cgc_free(write_00169);
   } while (0);
   do {
      unsigned char *read_00171;
      unsigned int read_00171_len;
      unsigned int read_00171_ptr = 0;
      //**** length read
      read_00171_len = 8;
      read_00171 = (unsigned char*)cgc_malloc(read_00171_len);
      int read_00171_res = cgc_length_read(0, read_00171, read_00171_len);
      if (read_00171_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00171_00000[] = 
         "\x01\x0c\x04\x01\xff\xb4\x02\x00";
      read_00171_ptr += cgc_data_match(read_00171 + read_00171_ptr, read_00171_len - read_00171_ptr, match_00171_00000, 8);
      cgc_free(read_00171);
      if (read_00171_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00170_00000[] = 
         "\x0c";
      static unsigned int write_00170_00000_len = 1;
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = cgc_append_buf(write_00170, &write_00170_len, write_00170_00000, write_00170_00000_len);
      if (write_00170_len > 0) {
         cgc_transmit_all(1, write_00170, write_00170_len);
      }
      cgc_free(write_00170);
   } while (0);
   do {
      unsigned char *read_00172;
      unsigned int read_00172_len;
      unsigned int read_00172_ptr = 0;
      //**** length read
      read_00172_len = 8;
      read_00172 = (unsigned char*)cgc_malloc(read_00172_len);
      int read_00172_res = cgc_length_read(0, read_00172, read_00172_len);
      if (read_00172_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00172_00000[] = 
         "\x02\x0c\x10\x01\xff\xb2\x02\x00";
      read_00172_ptr += cgc_data_match(read_00172 + read_00172_ptr, read_00172_len - read_00172_ptr, match_00172_00000, 8);
      cgc_free(read_00172);
      if (read_00172_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x0c";
      static unsigned int write_00171_00000_len = 1;
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = cgc_append_buf(write_00171, &write_00171_len, write_00171_00000, write_00171_00000_len);
      if (write_00171_len > 0) {
         cgc_transmit_all(1, write_00171, write_00171_len);
      }
      cgc_free(write_00171);
   } while (0);
   do {
      unsigned char *read_00173;
      unsigned int read_00173_len;
      unsigned int read_00173_ptr = 0;
      //**** length read
      read_00173_len = 8;
      read_00173 = (unsigned char*)cgc_malloc(read_00173_len);
      int read_00173_res = cgc_length_read(0, read_00173, read_00173_len);
      if (read_00173_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00173_00000[] = 
         "\x03\x0c\x08\x01\xff\x97\x02\x00";
      read_00173_ptr += cgc_data_match(read_00173 + read_00173_ptr, read_00173_len - read_00173_ptr, match_00173_00000, 8);
      cgc_free(read_00173);
      if (read_00173_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00172_00000[] = 
         "\x0c";
      static unsigned int write_00172_00000_len = 1;
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = cgc_append_buf(write_00172, &write_00172_len, write_00172_00000, write_00172_00000_len);
      if (write_00172_len > 0) {
         cgc_transmit_all(1, write_00172, write_00172_len);
      }
      cgc_free(write_00172);
   } while (0);
   do {
      unsigned char *read_00174;
      unsigned int read_00174_len;
      unsigned int read_00174_ptr = 0;
      //**** length read
      read_00174_len = 8;
      read_00174 = (unsigned char*)cgc_malloc(read_00174_len);
      int read_00174_res = cgc_length_read(0, read_00174, read_00174_len);
      if (read_00174_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00174_00000[] = 
         "\x04\x0c\x01\x01\xff\xd0\x02\x00";
      read_00174_ptr += cgc_data_match(read_00174 + read_00174_ptr, read_00174_len - read_00174_ptr, match_00174_00000, 8);
      cgc_free(read_00174);
      if (read_00174_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\x0c";
      static unsigned int write_00173_00000_len = 1;
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = cgc_append_buf(write_00173, &write_00173_len, write_00173_00000, write_00173_00000_len);
      if (write_00173_len > 0) {
         cgc_transmit_all(1, write_00173, write_00173_len);
      }
      cgc_free(write_00173);
   } while (0);
   do {
      unsigned char *read_00175;
      unsigned int read_00175_len;
      unsigned int read_00175_ptr = 0;
      //**** length read
      read_00175_len = 8;
      read_00175 = (unsigned char*)cgc_malloc(read_00175_len);
      int read_00175_res = cgc_length_read(0, read_00175, read_00175_len);
      if (read_00175_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00175_00000[] = 
         "\x05\x0c\x00\x01\xff\x96\x02\x00";
      read_00175_ptr += cgc_data_match(read_00175 + read_00175_ptr, read_00175_len - read_00175_ptr, match_00175_00000, 8);
      cgc_free(read_00175);
      if (read_00175_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00174_00000[] = 
         "\x0c";
      static unsigned int write_00174_00000_len = 1;
      unsigned char *write_00174 = NULL;
      unsigned int write_00174_len = 0;
      write_00174 = cgc_append_buf(write_00174, &write_00174_len, write_00174_00000, write_00174_00000_len);
      if (write_00174_len > 0) {
         cgc_transmit_all(1, write_00174, write_00174_len);
      }
      cgc_free(write_00174);
   } while (0);
   do {
      unsigned char *read_00176;
      unsigned int read_00176_len;
      unsigned int read_00176_ptr = 0;
      //**** length read
      read_00176_len = 8;
      read_00176 = (unsigned char*)cgc_malloc(read_00176_len);
      int read_00176_res = cgc_length_read(0, read_00176, read_00176_len);
      if (read_00176_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00176_00000[] = 
         "\x06\x0c\x04\x01\xff\xb4\x02\x00";
      read_00176_ptr += cgc_data_match(read_00176 + read_00176_ptr, read_00176_len - read_00176_ptr, match_00176_00000, 8);
      cgc_free(read_00176);
      if (read_00176_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x0c";
      static unsigned int write_00175_00000_len = 1;
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = cgc_append_buf(write_00175, &write_00175_len, write_00175_00000, write_00175_00000_len);
      if (write_00175_len > 0) {
         cgc_transmit_all(1, write_00175, write_00175_len);
      }
      cgc_free(write_00175);
   } while (0);
   do {
      unsigned char *read_00177;
      unsigned int read_00177_len;
      unsigned int read_00177_ptr = 0;
      //**** length read
      read_00177_len = 8;
      read_00177 = (unsigned char*)cgc_malloc(read_00177_len);
      int read_00177_res = cgc_length_read(0, read_00177, read_00177_len);
      if (read_00177_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00177_00000[] = 
         "\x07\x0c\x07\x01\xff\xc8\x02\x00";
      read_00177_ptr += cgc_data_match(read_00177 + read_00177_ptr, read_00177_len - read_00177_ptr, match_00177_00000, 8);
      cgc_free(read_00177);
      if (read_00177_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00176_00000[] = 
         "\x0c";
      static unsigned int write_00176_00000_len = 1;
      unsigned char *write_00176 = NULL;
      unsigned int write_00176_len = 0;
      write_00176 = cgc_append_buf(write_00176, &write_00176_len, write_00176_00000, write_00176_00000_len);
      if (write_00176_len > 0) {
         cgc_transmit_all(1, write_00176, write_00176_len);
      }
      cgc_free(write_00176);
   } while (0);
   do {
      unsigned char *read_00178;
      unsigned int read_00178_len;
      unsigned int read_00178_ptr = 0;
      //**** length read
      read_00178_len = 8;
      read_00178 = (unsigned char*)cgc_malloc(read_00178_len);
      int read_00178_res = cgc_length_read(0, read_00178, read_00178_len);
      if (read_00178_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00178_00000[] = 
         "\x08\x0c\x00\x01\xff\x9d\x02\x00";
      read_00178_ptr += cgc_data_match(read_00178 + read_00178_ptr, read_00178_len - read_00178_ptr, match_00178_00000, 8);
      cgc_free(read_00178);
      if (read_00178_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x0c";
      static unsigned int write_00177_00000_len = 1;
      unsigned char *write_00177 = NULL;
      unsigned int write_00177_len = 0;
      write_00177 = cgc_append_buf(write_00177, &write_00177_len, write_00177_00000, write_00177_00000_len);
      if (write_00177_len > 0) {
         cgc_transmit_all(1, write_00177, write_00177_len);
      }
      cgc_free(write_00177);
   } while (0);
   do {
      unsigned char *read_00179;
      unsigned int read_00179_len;
      unsigned int read_00179_ptr = 0;
      //**** length read
      read_00179_len = 8;
      read_00179 = (unsigned char*)cgc_malloc(read_00179_len);
      int read_00179_res = cgc_length_read(0, read_00179, read_00179_len);
      if (read_00179_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00179_00000[] = 
         "\x09\x0c\x01\x01\xff\x9e\x02\x00";
      read_00179_ptr += cgc_data_match(read_00179 + read_00179_ptr, read_00179_len - read_00179_ptr, match_00179_00000, 8);
      cgc_free(read_00179);
      if (read_00179_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00178_00000[] = 
         "\x0c";
      static unsigned int write_00178_00000_len = 1;
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = cgc_append_buf(write_00178, &write_00178_len, write_00178_00000, write_00178_00000_len);
      if (write_00178_len > 0) {
         cgc_transmit_all(1, write_00178, write_00178_len);
      }
      cgc_free(write_00178);
   } while (0);
   do {
      unsigned char *read_00180;
      unsigned int read_00180_len;
      unsigned int read_00180_ptr = 0;
      //**** length read
      read_00180_len = 8;
      read_00180 = (unsigned char*)cgc_malloc(read_00180_len);
      int read_00180_res = cgc_length_read(0, read_00180, read_00180_len);
      if (read_00180_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00180_00000[] = 
         "\x0a\x0c\x09\x01\xff\xb7\x02\x00";
      read_00180_ptr += cgc_data_match(read_00180 + read_00180_ptr, read_00180_len - read_00180_ptr, match_00180_00000, 8);
      cgc_free(read_00180);
      if (read_00180_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\x0c";
      static unsigned int write_00179_00000_len = 1;
      unsigned char *write_00179 = NULL;
      unsigned int write_00179_len = 0;
      write_00179 = cgc_append_buf(write_00179, &write_00179_len, write_00179_00000, write_00179_00000_len);
      if (write_00179_len > 0) {
         cgc_transmit_all(1, write_00179, write_00179_len);
      }
      cgc_free(write_00179);
   } while (0);
   do {
      unsigned char *read_00181;
      unsigned int read_00181_len;
      unsigned int read_00181_ptr = 0;
      //**** length read
      read_00181_len = 8;
      read_00181 = (unsigned char*)cgc_malloc(read_00181_len);
      int read_00181_res = cgc_length_read(0, read_00181, read_00181_len);
      if (read_00181_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00181_00000[] = 
         "\x01\x0c\x03\x01\xff\xbc\x02\x00";
      read_00181_ptr += cgc_data_match(read_00181 + read_00181_ptr, read_00181_len - read_00181_ptr, match_00181_00000, 8);
      cgc_free(read_00181);
      if (read_00181_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00180_00000[] = 
         "\x0c";
      static unsigned int write_00180_00000_len = 1;
      unsigned char *write_00180 = NULL;
      unsigned int write_00180_len = 0;
      write_00180 = cgc_append_buf(write_00180, &write_00180_len, write_00180_00000, write_00180_00000_len);
      if (write_00180_len > 0) {
         cgc_transmit_all(1, write_00180, write_00180_len);
      }
      cgc_free(write_00180);
   } while (0);
   do {
      unsigned char *read_00182;
      unsigned int read_00182_len;
      unsigned int read_00182_ptr = 0;
      //**** length read
      read_00182_len = 8;
      read_00182 = (unsigned char*)cgc_malloc(read_00182_len);
      int read_00182_res = cgc_length_read(0, read_00182, read_00182_len);
      if (read_00182_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00182_00000[] = 
         "\x02\x0c\x10\x01\xff\xae\x02\x00";
      read_00182_ptr += cgc_data_match(read_00182 + read_00182_ptr, read_00182_len - read_00182_ptr, match_00182_00000, 8);
      cgc_free(read_00182);
      if (read_00182_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x0c";
      static unsigned int write_00181_00000_len = 1;
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = cgc_append_buf(write_00181, &write_00181_len, write_00181_00000, write_00181_00000_len);
      if (write_00181_len > 0) {
         cgc_transmit_all(1, write_00181, write_00181_len);
      }
      cgc_free(write_00181);
   } while (0);
   do {
      unsigned char *read_00183;
      unsigned int read_00183_len;
      unsigned int read_00183_ptr = 0;
      //**** length read
      read_00183_len = 8;
      read_00183 = (unsigned char*)cgc_malloc(read_00183_len);
      int read_00183_res = cgc_length_read(0, read_00183, read_00183_len);
      if (read_00183_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00183_00000[] = 
         "\x03\x0c\x05\x01\xff\x9b\x02\x00";
      read_00183_ptr += cgc_data_match(read_00183 + read_00183_ptr, read_00183_len - read_00183_ptr, match_00183_00000, 8);
      cgc_free(read_00183);
      if (read_00183_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00182_00000[] = 
         "\x0c";
      static unsigned int write_00182_00000_len = 1;
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = cgc_append_buf(write_00182, &write_00182_len, write_00182_00000, write_00182_00000_len);
      if (write_00182_len > 0) {
         cgc_transmit_all(1, write_00182, write_00182_len);
      }
      cgc_free(write_00182);
   } while (0);
   do {
      unsigned char *read_00184;
      unsigned int read_00184_len;
      unsigned int read_00184_ptr = 0;
      //**** length read
      read_00184_len = 8;
      read_00184 = (unsigned char*)cgc_malloc(read_00184_len);
      int read_00184_res = cgc_length_read(0, read_00184, read_00184_len);
      if (read_00184_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00184_00000[] = 
         "\x04\x0c\x04\x01\xff\xdb\x02\x00";
      read_00184_ptr += cgc_data_match(read_00184 + read_00184_ptr, read_00184_len - read_00184_ptr, match_00184_00000, 8);
      cgc_free(read_00184);
      if (read_00184_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00183_00000[] = 
         "\x0c";
      static unsigned int write_00183_00000_len = 1;
      unsigned char *write_00183 = NULL;
      unsigned int write_00183_len = 0;
      write_00183 = cgc_append_buf(write_00183, &write_00183_len, write_00183_00000, write_00183_00000_len);
      if (write_00183_len > 0) {
         cgc_transmit_all(1, write_00183, write_00183_len);
      }
      cgc_free(write_00183);
   } while (0);
   do {
      unsigned char *read_00185;
      unsigned int read_00185_len;
      unsigned int read_00185_ptr = 0;
      //**** length read
      read_00185_len = 8;
      read_00185 = (unsigned char*)cgc_malloc(read_00185_len);
      int read_00185_res = cgc_length_read(0, read_00185, read_00185_len);
      if (read_00185_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00185_00000[] = 
         "\x05\x0c\x01\x01\xff\xa2\x02\x00";
      read_00185_ptr += cgc_data_match(read_00185 + read_00185_ptr, read_00185_len - read_00185_ptr, match_00185_00000, 8);
      cgc_free(read_00185);
      if (read_00185_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00184_00000[] = 
         "\x0c";
      static unsigned int write_00184_00000_len = 1;
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = cgc_append_buf(write_00184, &write_00184_len, write_00184_00000, write_00184_00000_len);
      if (write_00184_len > 0) {
         cgc_transmit_all(1, write_00184, write_00184_len);
      }
      cgc_free(write_00184);
   } while (0);
   do {
      unsigned char *read_00186;
      unsigned int read_00186_len;
      unsigned int read_00186_ptr = 0;
      //**** length read
      read_00186_len = 8;
      read_00186 = (unsigned char*)cgc_malloc(read_00186_len);
      int read_00186_res = cgc_length_read(0, read_00186, read_00186_len);
      if (read_00186_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00186_00000[] = 
         "\x06\x0c\x01\x01\xff\xbc\x02\x00";
      read_00186_ptr += cgc_data_match(read_00186 + read_00186_ptr, read_00186_len - read_00186_ptr, match_00186_00000, 8);
      cgc_free(read_00186);
      if (read_00186_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00185_00000[] = 
         "\x0c";
      static unsigned int write_00185_00000_len = 1;
      unsigned char *write_00185 = NULL;
      unsigned int write_00185_len = 0;
      write_00185 = cgc_append_buf(write_00185, &write_00185_len, write_00185_00000, write_00185_00000_len);
      if (write_00185_len > 0) {
         cgc_transmit_all(1, write_00185, write_00185_len);
      }
      cgc_free(write_00185);
   } while (0);
   do {
      unsigned char *read_00187;
      unsigned int read_00187_len;
      unsigned int read_00187_ptr = 0;
      //**** length read
      read_00187_len = 8;
      read_00187 = (unsigned char*)cgc_malloc(read_00187_len);
      int read_00187_res = cgc_length_read(0, read_00187, read_00187_len);
      if (read_00187_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00187_00000[] = 
         "\x07\x0c\x00\x01\xff\xcd\x02\x00";
      read_00187_ptr += cgc_data_match(read_00187 + read_00187_ptr, read_00187_len - read_00187_ptr, match_00187_00000, 8);
      cgc_free(read_00187);
      if (read_00187_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00186_00000[] = 
         "\x0c";
      static unsigned int write_00186_00000_len = 1;
      unsigned char *write_00186 = NULL;
      unsigned int write_00186_len = 0;
      write_00186 = cgc_append_buf(write_00186, &write_00186_len, write_00186_00000, write_00186_00000_len);
      if (write_00186_len > 0) {
         cgc_transmit_all(1, write_00186, write_00186_len);
      }
      cgc_free(write_00186);
   } while (0);
   do {
      unsigned char *read_00188;
      unsigned int read_00188_len;
      unsigned int read_00188_ptr = 0;
      //**** length read
      read_00188_len = 8;
      read_00188 = (unsigned char*)cgc_malloc(read_00188_len);
      int read_00188_res = cgc_length_read(0, read_00188, read_00188_len);
      if (read_00188_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00188_00000[] = 
         "\x08\x0c\x05\x01\xff\xa9\x02\x00";
      read_00188_ptr += cgc_data_match(read_00188 + read_00188_ptr, read_00188_len - read_00188_ptr, match_00188_00000, 8);
      cgc_free(read_00188);
      if (read_00188_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00187_00000[] = 
         "\x0c";
      static unsigned int write_00187_00000_len = 1;
      unsigned char *write_00187 = NULL;
      unsigned int write_00187_len = 0;
      write_00187 = cgc_append_buf(write_00187, &write_00187_len, write_00187_00000, write_00187_00000_len);
      if (write_00187_len > 0) {
         cgc_transmit_all(1, write_00187, write_00187_len);
      }
      cgc_free(write_00187);
   } while (0);
   do {
      unsigned char *read_00189;
      unsigned int read_00189_len;
      unsigned int read_00189_ptr = 0;
      //**** length read
      read_00189_len = 8;
      read_00189 = (unsigned char*)cgc_malloc(read_00189_len);
      int read_00189_res = cgc_length_read(0, read_00189, read_00189_len);
      if (read_00189_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00189_00000[] = 
         "\x09\x0c\x05\x01\xff\xa9\x02\x00";
      read_00189_ptr += cgc_data_match(read_00189 + read_00189_ptr, read_00189_len - read_00189_ptr, match_00189_00000, 8);
      cgc_free(read_00189);
      if (read_00189_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00188_00000[] = 
         "\x0c";
      static unsigned int write_00188_00000_len = 1;
      unsigned char *write_00188 = NULL;
      unsigned int write_00188_len = 0;
      write_00188 = cgc_append_buf(write_00188, &write_00188_len, write_00188_00000, write_00188_00000_len);
      if (write_00188_len > 0) {
         cgc_transmit_all(1, write_00188, write_00188_len);
      }
      cgc_free(write_00188);
   } while (0);
   do {
      unsigned char *read_00190;
      unsigned int read_00190_len;
      unsigned int read_00190_ptr = 0;
      //**** length read
      read_00190_len = 8;
      read_00190 = (unsigned char*)cgc_malloc(read_00190_len);
      int read_00190_res = cgc_length_read(0, read_00190, read_00190_len);
      if (read_00190_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00190_00000[] = 
         "\x0a\x0c\x05\x01\xff\xba\x02\x00";
      read_00190_ptr += cgc_data_match(read_00190 + read_00190_ptr, read_00190_len - read_00190_ptr, match_00190_00000, 8);
      cgc_free(read_00190);
      if (read_00190_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00189_00000[] = 
         "\x0c";
      static unsigned int write_00189_00000_len = 1;
      unsigned char *write_00189 = NULL;
      unsigned int write_00189_len = 0;
      write_00189 = cgc_append_buf(write_00189, &write_00189_len, write_00189_00000, write_00189_00000_len);
      if (write_00189_len > 0) {
         cgc_transmit_all(1, write_00189, write_00189_len);
      }
      cgc_free(write_00189);
   } while (0);
   do {
      unsigned char *read_00191;
      unsigned int read_00191_len;
      unsigned int read_00191_ptr = 0;
      //**** length read
      read_00191_len = 8;
      read_00191 = (unsigned char*)cgc_malloc(read_00191_len);
      int read_00191_res = cgc_length_read(0, read_00191, read_00191_len);
      if (read_00191_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00191_00000[] = 
         "\x01\x0c\x09\x01\xff\xc5\x02\x00";
      read_00191_ptr += cgc_data_match(read_00191 + read_00191_ptr, read_00191_len - read_00191_ptr, match_00191_00000, 8);
      cgc_free(read_00191);
      if (read_00191_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00190_00000[] = 
         "\x0c";
      static unsigned int write_00190_00000_len = 1;
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = cgc_append_buf(write_00190, &write_00190_len, write_00190_00000, write_00190_00000_len);
      if (write_00190_len > 0) {
         cgc_transmit_all(1, write_00190, write_00190_len);
      }
      cgc_free(write_00190);
   } while (0);
   do {
      unsigned char *read_00192;
      unsigned int read_00192_len;
      unsigned int read_00192_ptr = 0;
      //**** length read
      read_00192_len = 8;
      read_00192 = (unsigned char*)cgc_malloc(read_00192_len);
      int read_00192_res = cgc_length_read(0, read_00192, read_00192_len);
      if (read_00192_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00192_00000[] = 
         "\x02\x0c\x0c\x01\xff\xaa\x02\x00";
      read_00192_ptr += cgc_data_match(read_00192 + read_00192_ptr, read_00192_len - read_00192_ptr, match_00192_00000, 8);
      cgc_free(read_00192);
      if (read_00192_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00191_00000[] = 
         "\x0c";
      static unsigned int write_00191_00000_len = 1;
      unsigned char *write_00191 = NULL;
      unsigned int write_00191_len = 0;
      write_00191 = cgc_append_buf(write_00191, &write_00191_len, write_00191_00000, write_00191_00000_len);
      if (write_00191_len > 0) {
         cgc_transmit_all(1, write_00191, write_00191_len);
      }
      cgc_free(write_00191);
   } while (0);
   do {
      unsigned char *read_00193;
      unsigned int read_00193_len;
      unsigned int read_00193_ptr = 0;
      //**** length read
      read_00193_len = 8;
      read_00193 = (unsigned char*)cgc_malloc(read_00193_len);
      int read_00193_res = cgc_length_read(0, read_00193, read_00193_len);
      if (read_00193_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00193_00000[] = 
         "\x03\x0c\x08\x01\xff\xa2\x02\x00";
      read_00193_ptr += cgc_data_match(read_00193 + read_00193_ptr, read_00193_len - read_00193_ptr, match_00193_00000, 8);
      cgc_free(read_00193);
      if (read_00193_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00192_00000[] = 
         "\x0c";
      static unsigned int write_00192_00000_len = 1;
      unsigned char *write_00192 = NULL;
      unsigned int write_00192_len = 0;
      write_00192 = cgc_append_buf(write_00192, &write_00192_len, write_00192_00000, write_00192_00000_len);
      if (write_00192_len > 0) {
         cgc_transmit_all(1, write_00192, write_00192_len);
      }
      cgc_free(write_00192);
   } while (0);
   do {
      unsigned char *read_00194;
      unsigned int read_00194_len;
      unsigned int read_00194_ptr = 0;
      //**** length read
      read_00194_len = 8;
      read_00194 = (unsigned char*)cgc_malloc(read_00194_len);
      int read_00194_res = cgc_length_read(0, read_00194, read_00194_len);
      if (read_00194_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00194_00000[] = 
         "\x04\x0c\x08\x01\xff\xe3\x02\x00";
      read_00194_ptr += cgc_data_match(read_00194 + read_00194_ptr, read_00194_len - read_00194_ptr, match_00194_00000, 8);
      cgc_free(read_00194);
      if (read_00194_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00193_00000[] = 
         "\x0c";
      static unsigned int write_00193_00000_len = 1;
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = cgc_append_buf(write_00193, &write_00193_len, write_00193_00000, write_00193_00000_len);
      if (write_00193_len > 0) {
         cgc_transmit_all(1, write_00193, write_00193_len);
      }
      cgc_free(write_00193);
   } while (0);
   do {
      unsigned char *read_00195;
      unsigned int read_00195_len;
      unsigned int read_00195_ptr = 0;
      //**** length read
      read_00195_len = 8;
      read_00195 = (unsigned char*)cgc_malloc(read_00195_len);
      int read_00195_res = cgc_length_read(0, read_00195, read_00195_len);
      if (read_00195_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00195_00000[] = 
         "\x05\x0c\x0c\x01\xff\xad\x02\x00";
      read_00195_ptr += cgc_data_match(read_00195 + read_00195_ptr, read_00195_len - read_00195_ptr, match_00195_00000, 8);
      cgc_free(read_00195);
      if (read_00195_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00194_00000[] = 
         "\x0c";
      static unsigned int write_00194_00000_len = 1;
      unsigned char *write_00194 = NULL;
      unsigned int write_00194_len = 0;
      write_00194 = cgc_append_buf(write_00194, &write_00194_len, write_00194_00000, write_00194_00000_len);
      if (write_00194_len > 0) {
         cgc_transmit_all(1, write_00194, write_00194_len);
      }
      cgc_free(write_00194);
   } while (0);
   do {
      unsigned char *read_00196;
      unsigned int read_00196_len;
      unsigned int read_00196_ptr = 0;
      //**** length read
      read_00196_len = 8;
      read_00196 = (unsigned char*)cgc_malloc(read_00196_len);
      int read_00196_res = cgc_length_read(0, read_00196, read_00196_len);
      if (read_00196_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00196_00000[] = 
         "\x06\x0c\x04\x01\xff\xc7\x02\x00";
      read_00196_ptr += cgc_data_match(read_00196 + read_00196_ptr, read_00196_len - read_00196_ptr, match_00196_00000, 8);
      cgc_free(read_00196);
      if (read_00196_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00195_00000[] = 
         "\x0c";
      static unsigned int write_00195_00000_len = 1;
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = cgc_append_buf(write_00195, &write_00195_len, write_00195_00000, write_00195_00000_len);
      if (write_00195_len > 0) {
         cgc_transmit_all(1, write_00195, write_00195_len);
      }
      cgc_free(write_00195);
   } while (0);
   do {
      unsigned char *read_00197;
      unsigned int read_00197_len;
      unsigned int read_00197_ptr = 0;
      //**** length read
      read_00197_len = 8;
      read_00197 = (unsigned char*)cgc_malloc(read_00197_len);
      int read_00197_res = cgc_length_read(0, read_00197, read_00197_len);
      if (read_00197_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00197_00000[] = 
         "\x07\x0c\x04\x01\xff\xd9\x02\x00";
      read_00197_ptr += cgc_data_match(read_00197 + read_00197_ptr, read_00197_len - read_00197_ptr, match_00197_00000, 8);
      cgc_free(read_00197);
      if (read_00197_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00196_00000[] = 
         "\x0c";
      static unsigned int write_00196_00000_len = 1;
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = cgc_append_buf(write_00196, &write_00196_len, write_00196_00000, write_00196_00000_len);
      if (write_00196_len > 0) {
         cgc_transmit_all(1, write_00196, write_00196_len);
      }
      cgc_free(write_00196);
   } while (0);
   do {
      unsigned char *read_00198;
      unsigned int read_00198_len;
      unsigned int read_00198_ptr = 0;
      //**** length read
      read_00198_len = 8;
      read_00198 = (unsigned char*)cgc_malloc(read_00198_len);
      int read_00198_res = cgc_length_read(0, read_00198, read_00198_len);
      if (read_00198_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00198_00000[] = 
         "\x08\x0c\x09\x01\xff\xb0\x02\x00";
      read_00198_ptr += cgc_data_match(read_00198 + read_00198_ptr, read_00198_len - read_00198_ptr, match_00198_00000, 8);
      cgc_free(read_00198);
      if (read_00198_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00197_00000[] = 
         "\x0c";
      static unsigned int write_00197_00000_len = 1;
      unsigned char *write_00197 = NULL;
      unsigned int write_00197_len = 0;
      write_00197 = cgc_append_buf(write_00197, &write_00197_len, write_00197_00000, write_00197_00000_len);
      if (write_00197_len > 0) {
         cgc_transmit_all(1, write_00197, write_00197_len);
      }
      cgc_free(write_00197);
   } while (0);
   do {
      unsigned char *read_00199;
      unsigned int read_00199_len;
      unsigned int read_00199_ptr = 0;
      //**** length read
      read_00199_len = 8;
      read_00199 = (unsigned char*)cgc_malloc(read_00199_len);
      int read_00199_res = cgc_length_read(0, read_00199, read_00199_len);
      if (read_00199_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00199_00000[] = 
         "\x09\x0c\x08\x01\xff\xb0\x02\x00";
      read_00199_ptr += cgc_data_match(read_00199 + read_00199_ptr, read_00199_len - read_00199_ptr, match_00199_00000, 8);
      cgc_free(read_00199);
      if (read_00199_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00198_00000[] = 
         "\x0c";
      static unsigned int write_00198_00000_len = 1;
      unsigned char *write_00198 = NULL;
      unsigned int write_00198_len = 0;
      write_00198 = cgc_append_buf(write_00198, &write_00198_len, write_00198_00000, write_00198_00000_len);
      if (write_00198_len > 0) {
         cgc_transmit_all(1, write_00198, write_00198_len);
      }
      cgc_free(write_00198);
   } while (0);
   do {
      unsigned char *read_00200;
      unsigned int read_00200_len;
      unsigned int read_00200_ptr = 0;
      //**** length read
      read_00200_len = 8;
      read_00200 = (unsigned char*)cgc_malloc(read_00200_len);
      int read_00200_res = cgc_length_read(0, read_00200, read_00200_len);
      if (read_00200_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00200_00000[] = 
         "\x0a\x0c\x10\x01\xff\xc1\x02\x00";
      read_00200_ptr += cgc_data_match(read_00200 + read_00200_ptr, read_00200_len - read_00200_ptr, match_00200_00000, 8);
      cgc_free(read_00200);
      if (read_00200_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00199_00000[] = 
         "\x0c";
      static unsigned int write_00199_00000_len = 1;
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = cgc_append_buf(write_00199, &write_00199_len, write_00199_00000, write_00199_00000_len);
      if (write_00199_len > 0) {
         cgc_transmit_all(1, write_00199, write_00199_len);
      }
      cgc_free(write_00199);
   } while (0);
   do {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** length read
      read_00201_len = 8;
      read_00201 = (unsigned char*)cgc_malloc(read_00201_len);
      int read_00201_res = cgc_length_read(0, read_00201, read_00201_len);
      if (read_00201_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00201_00000[] = 
         "\x01\x0c\x09\x01\xff\xc8\x02\x00";
      read_00201_ptr += cgc_data_match(read_00201 + read_00201_ptr, read_00201_len - read_00201_ptr, match_00201_00000, 8);
      cgc_free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00200_00000[] = 
         "\x0c";
      static unsigned int write_00200_00000_len = 1;
      unsigned char *write_00200 = NULL;
      unsigned int write_00200_len = 0;
      write_00200 = cgc_append_buf(write_00200, &write_00200_len, write_00200_00000, write_00200_00000_len);
      if (write_00200_len > 0) {
         cgc_transmit_all(1, write_00200, write_00200_len);
      }
      cgc_free(write_00200);
   } while (0);
   do {
      unsigned char *read_00202;
      unsigned int read_00202_len;
      unsigned int read_00202_ptr = 0;
      //**** length read
      read_00202_len = 8;
      read_00202 = (unsigned char*)cgc_malloc(read_00202_len);
      int read_00202_res = cgc_length_read(0, read_00202, read_00202_len);
      if (read_00202_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00202_00000[] = 
         "\x02\x0c\x05\x01\xff\xaa\x02\x00";
      read_00202_ptr += cgc_data_match(read_00202 + read_00202_ptr, read_00202_len - read_00202_ptr, match_00202_00000, 8);
      cgc_free(read_00202);
      if (read_00202_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00201_00000[] = 
         "\x0c";
      static unsigned int write_00201_00000_len = 1;
      unsigned char *write_00201 = NULL;
      unsigned int write_00201_len = 0;
      write_00201 = cgc_append_buf(write_00201, &write_00201_len, write_00201_00000, write_00201_00000_len);
      if (write_00201_len > 0) {
         cgc_transmit_all(1, write_00201, write_00201_len);
      }
      cgc_free(write_00201);
   } while (0);
   do {
      unsigned char *read_00203;
      unsigned int read_00203_len;
      unsigned int read_00203_ptr = 0;
      //**** length read
      read_00203_len = 8;
      read_00203 = (unsigned char*)cgc_malloc(read_00203_len);
      int read_00203_res = cgc_length_read(0, read_00203, read_00203_len);
      if (read_00203_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00203_00000[] = 
         "\x03\x0c\x08\x01\xff\xa6\x02\x00";
      read_00203_ptr += cgc_data_match(read_00203 + read_00203_ptr, read_00203_len - read_00203_ptr, match_00203_00000, 8);
      cgc_free(read_00203);
      if (read_00203_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00202_00000[] = 
         "\x0c";
      static unsigned int write_00202_00000_len = 1;
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = cgc_append_buf(write_00202, &write_00202_len, write_00202_00000, write_00202_00000_len);
      if (write_00202_len > 0) {
         cgc_transmit_all(1, write_00202, write_00202_len);
      }
      cgc_free(write_00202);
   } while (0);
   do {
      unsigned char *read_00204;
      unsigned int read_00204_len;
      unsigned int read_00204_ptr = 0;
      //**** length read
      read_00204_len = 8;
      read_00204 = (unsigned char*)cgc_malloc(read_00204_len);
      int read_00204_res = cgc_length_read(0, read_00204, read_00204_len);
      if (read_00204_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00204_00000[] = 
         "\x04\x0c\x09\x01\xff\xe7\x02\x00";
      read_00204_ptr += cgc_data_match(read_00204 + read_00204_ptr, read_00204_len - read_00204_ptr, match_00204_00000, 8);
      cgc_free(read_00204);
      if (read_00204_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00203_00000[] = 
         "\x0c";
      static unsigned int write_00203_00000_len = 1;
      unsigned char *write_00203 = NULL;
      unsigned int write_00203_len = 0;
      write_00203 = cgc_append_buf(write_00203, &write_00203_len, write_00203_00000, write_00203_00000_len);
      if (write_00203_len > 0) {
         cgc_transmit_all(1, write_00203, write_00203_len);
      }
      cgc_free(write_00203);
   } while (0);
   do {
      unsigned char *read_00205;
      unsigned int read_00205_len;
      unsigned int read_00205_ptr = 0;
      //**** length read
      read_00205_len = 8;
      read_00205 = (unsigned char*)cgc_malloc(read_00205_len);
      int read_00205_res = cgc_length_read(0, read_00205, read_00205_len);
      if (read_00205_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00205_00000[] = 
         "\x05\x0c\x03\x01\xff\xad\x02\x00";
      read_00205_ptr += cgc_data_match(read_00205 + read_00205_ptr, read_00205_len - read_00205_ptr, match_00205_00000, 8);
      cgc_free(read_00205);
      if (read_00205_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00204_00000[] = 
         "\x0c";
      static unsigned int write_00204_00000_len = 1;
      unsigned char *write_00204 = NULL;
      unsigned int write_00204_len = 0;
      write_00204 = cgc_append_buf(write_00204, &write_00204_len, write_00204_00000, write_00204_00000_len);
      if (write_00204_len > 0) {
         cgc_transmit_all(1, write_00204, write_00204_len);
      }
      cgc_free(write_00204);
   } while (0);
   do {
      unsigned char *read_00206;
      unsigned int read_00206_len;
      unsigned int read_00206_ptr = 0;
      //**** length read
      read_00206_len = 8;
      read_00206 = (unsigned char*)cgc_malloc(read_00206_len);
      int read_00206_res = cgc_length_read(0, read_00206, read_00206_len);
      if (read_00206_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00206_00000[] = 
         "\x06\x0c\x00\x01\xff\xcf\x02\x00";
      read_00206_ptr += cgc_data_match(read_00206 + read_00206_ptr, read_00206_len - read_00206_ptr, match_00206_00000, 8);
      cgc_free(read_00206);
      if (read_00206_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00205_00000[] = 
         "\x0c";
      static unsigned int write_00205_00000_len = 1;
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = cgc_append_buf(write_00205, &write_00205_len, write_00205_00000, write_00205_00000_len);
      if (write_00205_len > 0) {
         cgc_transmit_all(1, write_00205, write_00205_len);
      }
      cgc_free(write_00205);
   } while (0);
   do {
      unsigned char *read_00207;
      unsigned int read_00207_len;
      unsigned int read_00207_ptr = 0;
      //**** length read
      read_00207_len = 8;
      read_00207 = (unsigned char*)cgc_malloc(read_00207_len);
      int read_00207_res = cgc_length_read(0, read_00207, read_00207_len);
      if (read_00207_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00207_00000[] = 
         "\x07\x0c\x03\x01\xff\xe1\x02\x00";
      read_00207_ptr += cgc_data_match(read_00207 + read_00207_ptr, read_00207_len - read_00207_ptr, match_00207_00000, 8);
      cgc_free(read_00207);
      if (read_00207_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00206_00000[] = 
         "\x0c";
      static unsigned int write_00206_00000_len = 1;
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = cgc_append_buf(write_00206, &write_00206_len, write_00206_00000, write_00206_00000_len);
      if (write_00206_len > 0) {
         cgc_transmit_all(1, write_00206, write_00206_len);
      }
      cgc_free(write_00206);
   } while (0);
   do {
      unsigned char *read_00208;
      unsigned int read_00208_len;
      unsigned int read_00208_ptr = 0;
      //**** length read
      read_00208_len = 8;
      read_00208 = (unsigned char*)cgc_malloc(read_00208_len);
      int read_00208_res = cgc_length_read(0, read_00208, read_00208_len);
      if (read_00208_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00208_00000[] = 
         "\x08\x0c\x10\x01\xff\xb3\x02\x00";
      read_00208_ptr += cgc_data_match(read_00208 + read_00208_ptr, read_00208_len - read_00208_ptr, match_00208_00000, 8);
      cgc_free(read_00208);
      if (read_00208_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00207_00000[] = 
         "\x0c";
      static unsigned int write_00207_00000_len = 1;
      unsigned char *write_00207 = NULL;
      unsigned int write_00207_len = 0;
      write_00207 = cgc_append_buf(write_00207, &write_00207_len, write_00207_00000, write_00207_00000_len);
      if (write_00207_len > 0) {
         cgc_transmit_all(1, write_00207, write_00207_len);
      }
      cgc_free(write_00207);
   } while (0);
   do {
      unsigned char *read_00209;
      unsigned int read_00209_len;
      unsigned int read_00209_ptr = 0;
      //**** length read
      read_00209_len = 8;
      read_00209 = (unsigned char*)cgc_malloc(read_00209_len);
      int read_00209_res = cgc_length_read(0, read_00209, read_00209_len);
      if (read_00209_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00209_00000[] = 
         "\x09\x0c\x01\x01\xff\xb4\x02\x00";
      read_00209_ptr += cgc_data_match(read_00209 + read_00209_ptr, read_00209_len - read_00209_ptr, match_00209_00000, 8);
      cgc_free(read_00209);
      if (read_00209_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00208_00000[] = 
         "\x0c";
      static unsigned int write_00208_00000_len = 1;
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = cgc_append_buf(write_00208, &write_00208_len, write_00208_00000, write_00208_00000_len);
      if (write_00208_len > 0) {
         cgc_transmit_all(1, write_00208, write_00208_len);
      }
      cgc_free(write_00208);
   } while (0);
   do {
      unsigned char *read_00210;
      unsigned int read_00210_len;
      unsigned int read_00210_ptr = 0;
      //**** length read
      read_00210_len = 8;
      read_00210 = (unsigned char*)cgc_malloc(read_00210_len);
      int read_00210_res = cgc_length_read(0, read_00210, read_00210_len);
      if (read_00210_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00210_00000[] = 
         "\x0a\x0c\x09\x01\xff\xbd\x02\x00";
      read_00210_ptr += cgc_data_match(read_00210 + read_00210_ptr, read_00210_len - read_00210_ptr, match_00210_00000, 8);
      cgc_free(read_00210);
      if (read_00210_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00209_00000[] = 
         "\x0c";
      static unsigned int write_00209_00000_len = 1;
      unsigned char *write_00209 = NULL;
      unsigned int write_00209_len = 0;
      write_00209 = cgc_append_buf(write_00209, &write_00209_len, write_00209_00000, write_00209_00000_len);
      if (write_00209_len > 0) {
         cgc_transmit_all(1, write_00209, write_00209_len);
      }
      cgc_free(write_00209);
   } while (0);
   do {
      unsigned char *read_00211;
      unsigned int read_00211_len;
      unsigned int read_00211_ptr = 0;
      //**** length read
      read_00211_len = 8;
      read_00211 = (unsigned char*)cgc_malloc(read_00211_len);
      int read_00211_res = cgc_length_read(0, read_00211, read_00211_len);
      if (read_00211_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00211_00000[] = 
         "\x01\x0c\x0c\x01\xff\xcb\x02\x00";
      read_00211_ptr += cgc_data_match(read_00211 + read_00211_ptr, read_00211_len - read_00211_ptr, match_00211_00000, 8);
      cgc_free(read_00211);
      if (read_00211_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00210_00000[] = 
         "\x0c";
      static unsigned int write_00210_00000_len = 1;
      unsigned char *write_00210 = NULL;
      unsigned int write_00210_len = 0;
      write_00210 = cgc_append_buf(write_00210, &write_00210_len, write_00210_00000, write_00210_00000_len);
      if (write_00210_len > 0) {
         cgc_transmit_all(1, write_00210, write_00210_len);
      }
      cgc_free(write_00210);
   } while (0);
   do {
      unsigned char *read_00212;
      unsigned int read_00212_len;
      unsigned int read_00212_ptr = 0;
      //**** length read
      read_00212_len = 8;
      read_00212 = (unsigned char*)cgc_malloc(read_00212_len);
      int read_00212_res = cgc_length_read(0, read_00212, read_00212_len);
      if (read_00212_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00212_00000[] = 
         "\x02\x0c\x08\x01\xff\xb1\x02\x00";
      read_00212_ptr += cgc_data_match(read_00212 + read_00212_ptr, read_00212_len - read_00212_ptr, match_00212_00000, 8);
      cgc_free(read_00212);
      if (read_00212_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00211_00000[] = 
         "\x0c";
      static unsigned int write_00211_00000_len = 1;
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = cgc_append_buf(write_00211, &write_00211_len, write_00211_00000, write_00211_00000_len);
      if (write_00211_len > 0) {
         cgc_transmit_all(1, write_00211, write_00211_len);
      }
      cgc_free(write_00211);
   } while (0);
   do {
      unsigned char *read_00213;
      unsigned int read_00213_len;
      unsigned int read_00213_ptr = 0;
      //**** length read
      read_00213_len = 8;
      read_00213 = (unsigned char*)cgc_malloc(read_00213_len);
      int read_00213_res = cgc_length_read(0, read_00213, read_00213_len);
      if (read_00213_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00213_00000[] = 
         "\x03\x0c\x08\x01\xff\xaa\x02\x00";
      read_00213_ptr += cgc_data_match(read_00213 + read_00213_ptr, read_00213_len - read_00213_ptr, match_00213_00000, 8);
      cgc_free(read_00213);
      if (read_00213_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00212_00000[] = 
         "\x0c";
      static unsigned int write_00212_00000_len = 1;
      unsigned char *write_00212 = NULL;
      unsigned int write_00212_len = 0;
      write_00212 = cgc_append_buf(write_00212, &write_00212_len, write_00212_00000, write_00212_00000_len);
      if (write_00212_len > 0) {
         cgc_transmit_all(1, write_00212, write_00212_len);
      }
      cgc_free(write_00212);
   } while (0);
   do {
      unsigned char *read_00214;
      unsigned int read_00214_len;
      unsigned int read_00214_ptr = 0;
      //**** length read
      read_00214_len = 8;
      read_00214 = (unsigned char*)cgc_malloc(read_00214_len);
      int read_00214_res = cgc_length_read(0, read_00214, read_00214_len);
      if (read_00214_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00214_00000[] = 
         "\x04\x0c\x04\x01\xff\xea\x02\x00";
      read_00214_ptr += cgc_data_match(read_00214 + read_00214_ptr, read_00214_len - read_00214_ptr, match_00214_00000, 8);
      cgc_free(read_00214);
      if (read_00214_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00213_00000[] = 
         "\x0c";
      static unsigned int write_00213_00000_len = 1;
      unsigned char *write_00213 = NULL;
      unsigned int write_00213_len = 0;
      write_00213 = cgc_append_buf(write_00213, &write_00213_len, write_00213_00000, write_00213_00000_len);
      if (write_00213_len > 0) {
         cgc_transmit_all(1, write_00213, write_00213_len);
      }
      cgc_free(write_00213);
   } while (0);
   do {
      unsigned char *read_00215;
      unsigned int read_00215_len;
      unsigned int read_00215_ptr = 0;
      //**** length read
      read_00215_len = 8;
      read_00215 = (unsigned char*)cgc_malloc(read_00215_len);
      int read_00215_res = cgc_length_read(0, read_00215, read_00215_len);
      if (read_00215_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00215_00000[] = 
         "\x05\x0c\x10\x01\xff\xb6\x02\x00";
      read_00215_ptr += cgc_data_match(read_00215 + read_00215_ptr, read_00215_len - read_00215_ptr, match_00215_00000, 8);
      cgc_free(read_00215);
      if (read_00215_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00214_00000[] = 
         "\x0c";
      static unsigned int write_00214_00000_len = 1;
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = cgc_append_buf(write_00214, &write_00214_len, write_00214_00000, write_00214_00000_len);
      if (write_00214_len > 0) {
         cgc_transmit_all(1, write_00214, write_00214_len);
      }
      cgc_free(write_00214);
   } while (0);
   do {
      unsigned char *read_00216;
      unsigned int read_00216_len;
      unsigned int read_00216_ptr = 0;
      //**** length read
      read_00216_len = 8;
      read_00216 = (unsigned char*)cgc_malloc(read_00216_len);
      int read_00216_res = cgc_length_read(0, read_00216, read_00216_len);
      if (read_00216_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00216_00000[] = 
         "\x06\x0c\x10\x01\xff\xdb\x02\x00";
      read_00216_ptr += cgc_data_match(read_00216 + read_00216_ptr, read_00216_len - read_00216_ptr, match_00216_00000, 8);
      cgc_free(read_00216);
      if (read_00216_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00215_00000[] = 
         "\x0c";
      static unsigned int write_00215_00000_len = 1;
      unsigned char *write_00215 = NULL;
      unsigned int write_00215_len = 0;
      write_00215 = cgc_append_buf(write_00215, &write_00215_len, write_00215_00000, write_00215_00000_len);
      if (write_00215_len > 0) {
         cgc_transmit_all(1, write_00215, write_00215_len);
      }
      cgc_free(write_00215);
   } while (0);
   do {
      unsigned char *read_00217;
      unsigned int read_00217_len;
      unsigned int read_00217_ptr = 0;
      //**** length read
      read_00217_len = 8;
      read_00217 = (unsigned char*)cgc_malloc(read_00217_len);
      int read_00217_res = cgc_length_read(0, read_00217, read_00217_len);
      if (read_00217_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00217_00000[] = 
         "\x07\x0c\x01\x01\xff\xea\x02\x00";
      read_00217_ptr += cgc_data_match(read_00217 + read_00217_ptr, read_00217_len - read_00217_ptr, match_00217_00000, 8);
      cgc_free(read_00217);
      if (read_00217_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00216_00000[] = 
         "\x0c";
      static unsigned int write_00216_00000_len = 1;
      unsigned char *write_00216 = NULL;
      unsigned int write_00216_len = 0;
      write_00216 = cgc_append_buf(write_00216, &write_00216_len, write_00216_00000, write_00216_00000_len);
      if (write_00216_len > 0) {
         cgc_transmit_all(1, write_00216, write_00216_len);
      }
      cgc_free(write_00216);
   } while (0);
   do {
      unsigned char *read_00218;
      unsigned int read_00218_len;
      unsigned int read_00218_ptr = 0;
      //**** length read
      read_00218_len = 8;
      read_00218 = (unsigned char*)cgc_malloc(read_00218_len);
      int read_00218_res = cgc_length_read(0, read_00218, read_00218_len);
      if (read_00218_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00218_00000[] = 
         "\x08\x0c\x00\x01\xff\xaf\x02\x00";
      read_00218_ptr += cgc_data_match(read_00218 + read_00218_ptr, read_00218_len - read_00218_ptr, match_00218_00000, 8);
      cgc_free(read_00218);
      if (read_00218_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00217_00000[] = 
         "\x0c";
      static unsigned int write_00217_00000_len = 1;
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = cgc_append_buf(write_00217, &write_00217_len, write_00217_00000, write_00217_00000_len);
      if (write_00217_len > 0) {
         cgc_transmit_all(1, write_00217, write_00217_len);
      }
      cgc_free(write_00217);
   } while (0);
   do {
      unsigned char *read_00219;
      unsigned int read_00219_len;
      unsigned int read_00219_ptr = 0;
      //**** length read
      read_00219_len = 8;
      read_00219 = (unsigned char*)cgc_malloc(read_00219_len);
      int read_00219_res = cgc_length_read(0, read_00219, read_00219_len);
      if (read_00219_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00219_00000[] = 
         "\x09\x0c\x09\x01\xff\xbf\x02\x00";
      read_00219_ptr += cgc_data_match(read_00219 + read_00219_ptr, read_00219_len - read_00219_ptr, match_00219_00000, 8);
      cgc_free(read_00219);
      if (read_00219_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00218_00000[] = 
         "\x0c";
      static unsigned int write_00218_00000_len = 1;
      unsigned char *write_00218 = NULL;
      unsigned int write_00218_len = 0;
      write_00218 = cgc_append_buf(write_00218, &write_00218_len, write_00218_00000, write_00218_00000_len);
      if (write_00218_len > 0) {
         cgc_transmit_all(1, write_00218, write_00218_len);
      }
      cgc_free(write_00218);
   } while (0);
   do {
      unsigned char *read_00220;
      unsigned int read_00220_len;
      unsigned int read_00220_ptr = 0;
      //**** length read
      read_00220_len = 8;
      read_00220 = (unsigned char*)cgc_malloc(read_00220_len);
      int read_00220_res = cgc_length_read(0, read_00220, read_00220_len);
      if (read_00220_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00220_00000[] = 
         "\x0a\x0c\x07\x01\xff\xc0\x02\x00";
      read_00220_ptr += cgc_data_match(read_00220 + read_00220_ptr, read_00220_len - read_00220_ptr, match_00220_00000, 8);
      cgc_free(read_00220);
      if (read_00220_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00219_00000[] = 
         "\x0c";
      static unsigned int write_00219_00000_len = 1;
      unsigned char *write_00219 = NULL;
      unsigned int write_00219_len = 0;
      write_00219 = cgc_append_buf(write_00219, &write_00219_len, write_00219_00000, write_00219_00000_len);
      if (write_00219_len > 0) {
         cgc_transmit_all(1, write_00219, write_00219_len);
      }
      cgc_free(write_00219);
   } while (0);
   do {
      unsigned char *read_00221;
      unsigned int read_00221_len;
      unsigned int read_00221_ptr = 0;
      //**** length read
      read_00221_len = 8;
      read_00221 = (unsigned char*)cgc_malloc(read_00221_len);
      int read_00221_res = cgc_length_read(0, read_00221, read_00221_len);
      if (read_00221_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00221_00000[] = 
         "\x01\x0c\x05\x01\xff\xcb\x02\x00";
      read_00221_ptr += cgc_data_match(read_00221 + read_00221_ptr, read_00221_len - read_00221_ptr, match_00221_00000, 8);
      cgc_free(read_00221);
      if (read_00221_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00220_00000[] = 
         "\x0c";
      static unsigned int write_00220_00000_len = 1;
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = cgc_append_buf(write_00220, &write_00220_len, write_00220_00000, write_00220_00000_len);
      if (write_00220_len > 0) {
         cgc_transmit_all(1, write_00220, write_00220_len);
      }
      cgc_free(write_00220);
   } while (0);
   do {
      unsigned char *read_00222;
      unsigned int read_00222_len;
      unsigned int read_00222_ptr = 0;
      //**** length read
      read_00222_len = 8;
      read_00222 = (unsigned char*)cgc_malloc(read_00222_len);
      int read_00222_res = cgc_length_read(0, read_00222, read_00222_len);
      if (read_00222_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00222_00000[] = 
         "\x02\x0c\x0c\x01\xff\xb5\x02\x00";
      read_00222_ptr += cgc_data_match(read_00222 + read_00222_ptr, read_00222_len - read_00222_ptr, match_00222_00000, 8);
      cgc_free(read_00222);
      if (read_00222_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00221_00000[] = 
         "\x0c";
      static unsigned int write_00221_00000_len = 1;
      unsigned char *write_00221 = NULL;
      unsigned int write_00221_len = 0;
      write_00221 = cgc_append_buf(write_00221, &write_00221_len, write_00221_00000, write_00221_00000_len);
      if (write_00221_len > 0) {
         cgc_transmit_all(1, write_00221, write_00221_len);
      }
      cgc_free(write_00221);
   } while (0);
   do {
      unsigned char *read_00223;
      unsigned int read_00223_len;
      unsigned int read_00223_ptr = 0;
      //**** length read
      read_00223_len = 8;
      read_00223 = (unsigned char*)cgc_malloc(read_00223_len);
      int read_00223_res = cgc_length_read(0, read_00223, read_00223_len);
      if (read_00223_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00223_00000[] = 
         "\x03\x0c\x0c\x01\xff\xae\x02\x00";
      read_00223_ptr += cgc_data_match(read_00223 + read_00223_ptr, read_00223_len - read_00223_ptr, match_00223_00000, 8);
      cgc_free(read_00223);
      if (read_00223_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00222_00000[] = 
         "\x0c";
      static unsigned int write_00222_00000_len = 1;
      unsigned char *write_00222 = NULL;
      unsigned int write_00222_len = 0;
      write_00222 = cgc_append_buf(write_00222, &write_00222_len, write_00222_00000, write_00222_00000_len);
      if (write_00222_len > 0) {
         cgc_transmit_all(1, write_00222, write_00222_len);
      }
      cgc_free(write_00222);
   } while (0);
   do {
      unsigned char *read_00224;
      unsigned int read_00224_len;
      unsigned int read_00224_ptr = 0;
      //**** length read
      read_00224_len = 8;
      read_00224 = (unsigned char*)cgc_malloc(read_00224_len);
      int read_00224_res = cgc_length_read(0, read_00224, read_00224_len);
      if (read_00224_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00224_00000[] = 
         "\x04\x0c\x05\x01\xff\xf2\x02\x00";
      read_00224_ptr += cgc_data_match(read_00224 + read_00224_ptr, read_00224_len - read_00224_ptr, match_00224_00000, 8);
      cgc_free(read_00224);
      if (read_00224_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00223_00000[] = 
         "\x0c";
      static unsigned int write_00223_00000_len = 1;
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = cgc_append_buf(write_00223, &write_00223_len, write_00223_00000, write_00223_00000_len);
      if (write_00223_len > 0) {
         cgc_transmit_all(1, write_00223, write_00223_len);
      }
      cgc_free(write_00223);
   } while (0);
   do {
      unsigned char *read_00225;
      unsigned int read_00225_len;
      unsigned int read_00225_ptr = 0;
      //**** length read
      read_00225_len = 8;
      read_00225 = (unsigned char*)cgc_malloc(read_00225_len);
      int read_00225_res = cgc_length_read(0, read_00225, read_00225_len);
      if (read_00225_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00225_00000[] = 
         "\x05\x0c\x09\x01\xff\xb2\x02\x00";
      read_00225_ptr += cgc_data_match(read_00225 + read_00225_ptr, read_00225_len - read_00225_ptr, match_00225_00000, 8);
      cgc_free(read_00225);
      if (read_00225_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00224_00000[] = 
         "\x0c";
      static unsigned int write_00224_00000_len = 1;
      unsigned char *write_00224 = NULL;
      unsigned int write_00224_len = 0;
      write_00224 = cgc_append_buf(write_00224, &write_00224_len, write_00224_00000, write_00224_00000_len);
      if (write_00224_len > 0) {
         cgc_transmit_all(1, write_00224, write_00224_len);
      }
      cgc_free(write_00224);
   } while (0);
   do {
      unsigned char *read_00226;
      unsigned int read_00226_len;
      unsigned int read_00226_ptr = 0;
      //**** length read
      read_00226_len = 8;
      read_00226 = (unsigned char*)cgc_malloc(read_00226_len);
      int read_00226_res = cgc_length_read(0, read_00226, read_00226_len);
      if (read_00226_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00226_00000[] = 
         "\x06\x0c\x03\x01\xff\xd7\x02\x00";
      read_00226_ptr += cgc_data_match(read_00226 + read_00226_ptr, read_00226_len - read_00226_ptr, match_00226_00000, 8);
      cgc_free(read_00226);
      if (read_00226_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00225_00000[] = 
         "\x0c";
      static unsigned int write_00225_00000_len = 1;
      unsigned char *write_00225 = NULL;
      unsigned int write_00225_len = 0;
      write_00225 = cgc_append_buf(write_00225, &write_00225_len, write_00225_00000, write_00225_00000_len);
      if (write_00225_len > 0) {
         cgc_transmit_all(1, write_00225, write_00225_len);
      }
      cgc_free(write_00225);
   } while (0);
   do {
      unsigned char *read_00227;
      unsigned int read_00227_len;
      unsigned int read_00227_ptr = 0;
      //**** length read
      read_00227_len = 8;
      read_00227 = (unsigned char*)cgc_malloc(read_00227_len);
      int read_00227_res = cgc_length_read(0, read_00227, read_00227_len);
      if (read_00227_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00227_00000[] = 
         "\x07\x0c\x03\x01\xff\xf5\x02\x00";
      read_00227_ptr += cgc_data_match(read_00227 + read_00227_ptr, read_00227_len - read_00227_ptr, match_00227_00000, 8);
      cgc_free(read_00227);
      if (read_00227_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00226_00000[] = 
         "\x0c";
      static unsigned int write_00226_00000_len = 1;
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = cgc_append_buf(write_00226, &write_00226_len, write_00226_00000, write_00226_00000_len);
      if (write_00226_len > 0) {
         cgc_transmit_all(1, write_00226, write_00226_len);
      }
      cgc_free(write_00226);
   } while (0);
   do {
      unsigned char *read_00228;
      unsigned int read_00228_len;
      unsigned int read_00228_ptr = 0;
      //**** length read
      read_00228_len = 8;
      read_00228 = (unsigned char*)cgc_malloc(read_00228_len);
      int read_00228_res = cgc_length_read(0, read_00228, read_00228_len);
      if (read_00228_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00228_00000[] = 
         "\x08\x0c\x08\x01\xff\xbb\x02\x00";
      read_00228_ptr += cgc_data_match(read_00228 + read_00228_ptr, read_00228_len - read_00228_ptr, match_00228_00000, 8);
      cgc_free(read_00228);
      if (read_00228_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00227_00000[] = 
         "\x0c";
      static unsigned int write_00227_00000_len = 1;
      unsigned char *write_00227 = NULL;
      unsigned int write_00227_len = 0;
      write_00227 = cgc_append_buf(write_00227, &write_00227_len, write_00227_00000, write_00227_00000_len);
      if (write_00227_len > 0) {
         cgc_transmit_all(1, write_00227, write_00227_len);
      }
      cgc_free(write_00227);
   } while (0);
   do {
      unsigned char *read_00229;
      unsigned int read_00229_len;
      unsigned int read_00229_ptr = 0;
      //**** length read
      read_00229_len = 8;
      read_00229 = (unsigned char*)cgc_malloc(read_00229_len);
      int read_00229_res = cgc_length_read(0, read_00229, read_00229_len);
      if (read_00229_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00229_00000[] = 
         "\x09\x0c\x08\x01\xff\xc2\x02\x00";
      read_00229_ptr += cgc_data_match(read_00229 + read_00229_ptr, read_00229_len - read_00229_ptr, match_00229_00000, 8);
      cgc_free(read_00229);
      if (read_00229_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00228_00000[] = 
         "\x0c";
      static unsigned int write_00228_00000_len = 1;
      unsigned char *write_00228 = NULL;
      unsigned int write_00228_len = 0;
      write_00228 = cgc_append_buf(write_00228, &write_00228_len, write_00228_00000, write_00228_00000_len);
      if (write_00228_len > 0) {
         cgc_transmit_all(1, write_00228, write_00228_len);
      }
      cgc_free(write_00228);
   } while (0);
   do {
      unsigned char *read_00230;
      unsigned int read_00230_len;
      unsigned int read_00230_ptr = 0;
      //**** length read
      read_00230_len = 8;
      read_00230 = (unsigned char*)cgc_malloc(read_00230_len);
      int read_00230_res = cgc_length_read(0, read_00230, read_00230_len);
      if (read_00230_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00230_00000[] = 
         "\x0a\x0c\x0c\x01\xff\xc5\x02\x00";
      read_00230_ptr += cgc_data_match(read_00230 + read_00230_ptr, read_00230_len - read_00230_ptr, match_00230_00000, 8);
      cgc_free(read_00230);
      if (read_00230_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00229_00000[] = 
         "\x0c";
      static unsigned int write_00229_00000_len = 1;
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = cgc_append_buf(write_00229, &write_00229_len, write_00229_00000, write_00229_00000_len);
      if (write_00229_len > 0) {
         cgc_transmit_all(1, write_00229, write_00229_len);
      }
      cgc_free(write_00229);
   } while (0);
   do {
      unsigned char *read_00231;
      unsigned int read_00231_len;
      unsigned int read_00231_ptr = 0;
      //**** length read
      read_00231_len = 8;
      read_00231 = (unsigned char*)cgc_malloc(read_00231_len);
      int read_00231_res = cgc_length_read(0, read_00231, read_00231_len);
      if (read_00231_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00231_00000[] = 
         "\x01\x0c\x01\x01\xff\xd2\x02\x00";
      read_00231_ptr += cgc_data_match(read_00231 + read_00231_ptr, read_00231_len - read_00231_ptr, match_00231_00000, 8);
      cgc_free(read_00231);
      if (read_00231_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00230_00000[] = 
         "\x0c";
      static unsigned int write_00230_00000_len = 1;
      unsigned char *write_00230 = NULL;
      unsigned int write_00230_len = 0;
      write_00230 = cgc_append_buf(write_00230, &write_00230_len, write_00230_00000, write_00230_00000_len);
      if (write_00230_len > 0) {
         cgc_transmit_all(1, write_00230, write_00230_len);
      }
      cgc_free(write_00230);
   } while (0);
   do {
      unsigned char *read_00232;
      unsigned int read_00232_len;
      unsigned int read_00232_ptr = 0;
      //**** length read
      read_00232_len = 8;
      read_00232 = (unsigned char*)cgc_malloc(read_00232_len);
      int read_00232_res = cgc_length_read(0, read_00232, read_00232_len);
      if (read_00232_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00232_00000[] = 
         "\x02\x0c\x04\x01\xff\xb5\x02\x00";
      read_00232_ptr += cgc_data_match(read_00232 + read_00232_ptr, read_00232_len - read_00232_ptr, match_00232_00000, 8);
      cgc_free(read_00232);
      if (read_00232_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00231_00000[] = 
         "\x0c";
      static unsigned int write_00231_00000_len = 1;
      unsigned char *write_00231 = NULL;
      unsigned int write_00231_len = 0;
      write_00231 = cgc_append_buf(write_00231, &write_00231_len, write_00231_00000, write_00231_00000_len);
      if (write_00231_len > 0) {
         cgc_transmit_all(1, write_00231, write_00231_len);
      }
      cgc_free(write_00231);
   } while (0);
   do {
      unsigned char *read_00233;
      unsigned int read_00233_len;
      unsigned int read_00233_ptr = 0;
      //**** length read
      read_00233_len = 8;
      read_00233 = (unsigned char*)cgc_malloc(read_00233_len);
      int read_00233_res = cgc_length_read(0, read_00233, read_00233_len);
      if (read_00233_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00233_00000[] = 
         "\x03\x0c\x10\x01\xff\xae\x02\x00";
      read_00233_ptr += cgc_data_match(read_00233 + read_00233_ptr, read_00233_len - read_00233_ptr, match_00233_00000, 8);
      cgc_free(read_00233);
      if (read_00233_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00232_00000[] = 
         "\x0c";
      static unsigned int write_00232_00000_len = 1;
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = cgc_append_buf(write_00232, &write_00232_len, write_00232_00000, write_00232_00000_len);
      if (write_00232_len > 0) {
         cgc_transmit_all(1, write_00232, write_00232_len);
      }
      cgc_free(write_00232);
   } while (0);
   do {
      unsigned char *read_00234;
      unsigned int read_00234_len;
      unsigned int read_00234_ptr = 0;
      //**** length read
      read_00234_len = 8;
      read_00234 = (unsigned char*)cgc_malloc(read_00234_len);
      int read_00234_res = cgc_length_read(0, read_00234, read_00234_len);
      if (read_00234_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00234_00000[] = 
         "\x04\x0c\x08\x01\xff\xf9\x02\x00";
      read_00234_ptr += cgc_data_match(read_00234 + read_00234_ptr, read_00234_len - read_00234_ptr, match_00234_00000, 8);
      cgc_free(read_00234);
      if (read_00234_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00233_00000[] = 
         "\x0c";
      static unsigned int write_00233_00000_len = 1;
      unsigned char *write_00233 = NULL;
      unsigned int write_00233_len = 0;
      write_00233 = cgc_append_buf(write_00233, &write_00233_len, write_00233_00000, write_00233_00000_len);
      if (write_00233_len > 0) {
         cgc_transmit_all(1, write_00233, write_00233_len);
      }
      cgc_free(write_00233);
   } while (0);
   do {
      unsigned char *read_00235;
      unsigned int read_00235_len;
      unsigned int read_00235_ptr = 0;
      //**** length read
      read_00235_len = 8;
      read_00235 = (unsigned char*)cgc_malloc(read_00235_len);
      int read_00235_res = cgc_length_read(0, read_00235, read_00235_len);
      if (read_00235_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00235_00000[] = 
         "\x05\x0c\x07\x01\xff\xb5\x02\x00";
      read_00235_ptr += cgc_data_match(read_00235 + read_00235_ptr, read_00235_len - read_00235_ptr, match_00235_00000, 8);
      cgc_free(read_00235);
      if (read_00235_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00234_00000[] = 
         "\x0c";
      static unsigned int write_00234_00000_len = 1;
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = cgc_append_buf(write_00234, &write_00234_len, write_00234_00000, write_00234_00000_len);
      if (write_00234_len > 0) {
         cgc_transmit_all(1, write_00234, write_00234_len);
      }
      cgc_free(write_00234);
   } while (0);
   do {
      unsigned char *read_00236;
      unsigned int read_00236_len;
      unsigned int read_00236_ptr = 0;
      //**** length read
      read_00236_len = 8;
      read_00236 = (unsigned char*)cgc_malloc(read_00236_len);
      int read_00236_res = cgc_length_read(0, read_00236, read_00236_len);
      if (read_00236_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00236_00000[] = 
         "\x06\x0c\x05\x01\xff\xe0\x02\x00";
      read_00236_ptr += cgc_data_match(read_00236 + read_00236_ptr, read_00236_len - read_00236_ptr, match_00236_00000, 8);
      cgc_free(read_00236);
      if (read_00236_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00235_00000[] = 
         "\x0c";
      static unsigned int write_00235_00000_len = 1;
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = cgc_append_buf(write_00235, &write_00235_len, write_00235_00000, write_00235_00000_len);
      if (write_00235_len > 0) {
         cgc_transmit_all(1, write_00235, write_00235_len);
      }
      cgc_free(write_00235);
   } while (0);
   do {
      unsigned char *read_00237;
      unsigned int read_00237_len;
      unsigned int read_00237_ptr = 0;
      //**** length read
      read_00237_len = 8;
      read_00237 = (unsigned char*)cgc_malloc(read_00237_len);
      int read_00237_res = cgc_length_read(0, read_00237, read_00237_len);
      if (read_00237_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00237_00000[] = 
         "\x07\x0c\x0c\x01\xff\xfe\x02\x00";
      read_00237_ptr += cgc_data_match(read_00237 + read_00237_ptr, read_00237_len - read_00237_ptr, match_00237_00000, 8);
      cgc_free(read_00237);
      if (read_00237_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00236_00000[] = 
         "\x0c";
      static unsigned int write_00236_00000_len = 1;
      unsigned char *write_00236 = NULL;
      unsigned int write_00236_len = 0;
      write_00236 = cgc_append_buf(write_00236, &write_00236_len, write_00236_00000, write_00236_00000_len);
      if (write_00236_len > 0) {
         cgc_transmit_all(1, write_00236, write_00236_len);
      }
      cgc_free(write_00236);
   } while (0);
   do {
      unsigned char *read_00238;
      unsigned int read_00238_len;
      unsigned int read_00238_ptr = 0;
      //**** length read
      read_00238_len = 8;
      read_00238 = (unsigned char*)cgc_malloc(read_00238_len);
      int read_00238_res = cgc_length_read(0, read_00238, read_00238_len);
      if (read_00238_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00238_00000[] = 
         "\x08\x0c\x08\x01\xff\xbf\x02\x00";
      read_00238_ptr += cgc_data_match(read_00238 + read_00238_ptr, read_00238_len - read_00238_ptr, match_00238_00000, 8);
      cgc_free(read_00238);
      if (read_00238_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00237_00000[] = 
         "\x0c";
      static unsigned int write_00237_00000_len = 1;
      unsigned char *write_00237 = NULL;
      unsigned int write_00237_len = 0;
      write_00237 = cgc_append_buf(write_00237, &write_00237_len, write_00237_00000, write_00237_00000_len);
      if (write_00237_len > 0) {
         cgc_transmit_all(1, write_00237, write_00237_len);
      }
      cgc_free(write_00237);
   } while (0);
   do {
      unsigned char *read_00239;
      unsigned int read_00239_len;
      unsigned int read_00239_ptr = 0;
      //**** length read
      read_00239_len = 8;
      read_00239 = (unsigned char*)cgc_malloc(read_00239_len);
      int read_00239_res = cgc_length_read(0, read_00239, read_00239_len);
      if (read_00239_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00239_00000[] = 
         "\x09\x0c\x10\x01\xff\xc6\x02\x00";
      read_00239_ptr += cgc_data_match(read_00239 + read_00239_ptr, read_00239_len - read_00239_ptr, match_00239_00000, 8);
      cgc_free(read_00239);
      if (read_00239_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00238_00000[] = 
         "\x0c";
      static unsigned int write_00238_00000_len = 1;
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = cgc_append_buf(write_00238, &write_00238_len, write_00238_00000, write_00238_00000_len);
      if (write_00238_len > 0) {
         cgc_transmit_all(1, write_00238, write_00238_len);
      }
      cgc_free(write_00238);
   } while (0);
   do {
      unsigned char *read_00240;
      unsigned int read_00240_len;
      unsigned int read_00240_ptr = 0;
      //**** length read
      read_00240_len = 8;
      read_00240 = (unsigned char*)cgc_malloc(read_00240_len);
      int read_00240_res = cgc_length_read(0, read_00240, read_00240_len);
      if (read_00240_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00240_00000[] = 
         "\x0a\x0c\x04\x01\xff\xc5\x02\x00";
      read_00240_ptr += cgc_data_match(read_00240 + read_00240_ptr, read_00240_len - read_00240_ptr, match_00240_00000, 8);
      cgc_free(read_00240);
      if (read_00240_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00239_00000[] = 
         "\x0c";
      static unsigned int write_00239_00000_len = 1;
      unsigned char *write_00239 = NULL;
      unsigned int write_00239_len = 0;
      write_00239 = cgc_append_buf(write_00239, &write_00239_len, write_00239_00000, write_00239_00000_len);
      if (write_00239_len > 0) {
         cgc_transmit_all(1, write_00239, write_00239_len);
      }
      cgc_free(write_00239);
   } while (0);
   do {
      unsigned char *read_00241;
      unsigned int read_00241_len;
      unsigned int read_00241_ptr = 0;
      //**** length read
      read_00241_len = 8;
      read_00241 = (unsigned char*)cgc_malloc(read_00241_len);
      int read_00241_res = cgc_length_read(0, read_00241, read_00241_len);
      if (read_00241_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00241_00000[] = 
         "\x01\x0c\x03\x01\xff\xdd\x02\x00";
      read_00241_ptr += cgc_data_match(read_00241 + read_00241_ptr, read_00241_len - read_00241_ptr, match_00241_00000, 8);
      cgc_free(read_00241);
      if (read_00241_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00240_00000[] = 
         "\x0c";
      static unsigned int write_00240_00000_len = 1;
      unsigned char *write_00240 = NULL;
      unsigned int write_00240_len = 0;
      write_00240 = cgc_append_buf(write_00240, &write_00240_len, write_00240_00000, write_00240_00000_len);
      if (write_00240_len > 0) {
         cgc_transmit_all(1, write_00240, write_00240_len);
      }
      cgc_free(write_00240);
   } while (0);
   do {
      unsigned char *read_00242;
      unsigned int read_00242_len;
      unsigned int read_00242_ptr = 0;
      //**** length read
      read_00242_len = 8;
      read_00242 = (unsigned char*)cgc_malloc(read_00242_len);
      int read_00242_res = cgc_length_read(0, read_00242, read_00242_len);
      if (read_00242_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00242_00000[] = 
         "\x02\x0c\x03\x01\xff\xbd\x02\x00";
      read_00242_ptr += cgc_data_match(read_00242 + read_00242_ptr, read_00242_len - read_00242_ptr, match_00242_00000, 8);
      cgc_free(read_00242);
      if (read_00242_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00241_00000[] = 
         "\x0c";
      static unsigned int write_00241_00000_len = 1;
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = cgc_append_buf(write_00241, &write_00241_len, write_00241_00000, write_00241_00000_len);
      if (write_00241_len > 0) {
         cgc_transmit_all(1, write_00241, write_00241_len);
      }
      cgc_free(write_00241);
   } while (0);
   do {
      unsigned char *read_00243;
      unsigned int read_00243_len;
      unsigned int read_00243_ptr = 0;
      //**** length read
      read_00243_len = 8;
      read_00243 = (unsigned char*)cgc_malloc(read_00243_len);
      int read_00243_res = cgc_length_read(0, read_00243, read_00243_len);
      if (read_00243_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00243_00000[] = 
         "\x03\x0c\x07\x01\xff\xaa\x02\x00";
      read_00243_ptr += cgc_data_match(read_00243 + read_00243_ptr, read_00243_len - read_00243_ptr, match_00243_00000, 8);
      cgc_free(read_00243);
      if (read_00243_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00242_00000[] = 
         "\x0c";
      static unsigned int write_00242_00000_len = 1;
      unsigned char *write_00242 = NULL;
      unsigned int write_00242_len = 0;
      write_00242 = cgc_append_buf(write_00242, &write_00242_len, write_00242_00000, write_00242_00000_len);
      if (write_00242_len > 0) {
         cgc_transmit_all(1, write_00242, write_00242_len);
      }
      cgc_free(write_00242);
   } while (0);
   do {
      unsigned char *read_00244;
      unsigned int read_00244_len;
      unsigned int read_00244_ptr = 0;
      //**** length read
      read_00244_len = 8;
      read_00244 = (unsigned char*)cgc_malloc(read_00244_len);
      int read_00244_res = cgc_length_read(0, read_00244, read_00244_len);
      if (read_00244_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00244_00000[] = 
         "\x04\x0c\x10\x01\xff\xfd\x02\x00";
      read_00244_ptr += cgc_data_match(read_00244 + read_00244_ptr, read_00244_len - read_00244_ptr, match_00244_00000, 8);
      cgc_free(read_00244);
      if (read_00244_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00243_00000[] = 
         "\x0c";
      static unsigned int write_00243_00000_len = 1;
      unsigned char *write_00243 = NULL;
      unsigned int write_00243_len = 0;
      write_00243 = cgc_append_buf(write_00243, &write_00243_len, write_00243_00000, write_00243_00000_len);
      if (write_00243_len > 0) {
         cgc_transmit_all(1, write_00243, write_00243_len);
      }
      cgc_free(write_00243);
   } while (0);
   do {
      unsigned char *read_00245;
      unsigned int read_00245_len;
      unsigned int read_00245_ptr = 0;
      //**** length read
      read_00245_len = 8;
      read_00245 = (unsigned char*)cgc_malloc(read_00245_len);
      int read_00245_res = cgc_length_read(0, read_00245, read_00245_len);
      if (read_00245_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00245_00000[] = 
         "\x05\x0c\x0c\x01\xff\xba\x02\x00";
      read_00245_ptr += cgc_data_match(read_00245 + read_00245_ptr, read_00245_len - read_00245_ptr, match_00245_00000, 8);
      cgc_free(read_00245);
      if (read_00245_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00244_00000[] = 
         "\x0c";
      static unsigned int write_00244_00000_len = 1;
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = cgc_append_buf(write_00244, &write_00244_len, write_00244_00000, write_00244_00000_len);
      if (write_00244_len > 0) {
         cgc_transmit_all(1, write_00244, write_00244_len);
      }
      cgc_free(write_00244);
   } while (0);
   do {
      unsigned char *read_00246;
      unsigned int read_00246_len;
      unsigned int read_00246_ptr = 0;
      //**** length read
      read_00246_len = 8;
      read_00246 = (unsigned char*)cgc_malloc(read_00246_len);
      int read_00246_res = cgc_length_read(0, read_00246, read_00246_len);
      if (read_00246_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00246_00000[] = 
         "\x06\x0c\x07\x01\xff\xe7\x02\x00";
      read_00246_ptr += cgc_data_match(read_00246 + read_00246_ptr, read_00246_len - read_00246_ptr, match_00246_00000, 8);
      cgc_free(read_00246);
      if (read_00246_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00245_00000[] = 
         "\x0c";
      static unsigned int write_00245_00000_len = 1;
      unsigned char *write_00245 = NULL;
      unsigned int write_00245_len = 0;
      write_00245 = cgc_append_buf(write_00245, &write_00245_len, write_00245_00000, write_00245_00000_len);
      if (write_00245_len > 0) {
         cgc_transmit_all(1, write_00245, write_00245_len);
      }
      cgc_free(write_00245);
   } while (0);
   do {
      unsigned char *read_00247;
      unsigned int read_00247_len;
      unsigned int read_00247_ptr = 0;
      //**** length read
      read_00247_len = 8;
      read_00247 = (unsigned char*)cgc_malloc(read_00247_len);
      int read_00247_res = cgc_length_read(0, read_00247, read_00247_len);
      if (read_00247_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00247_00000[] = 
         "\x07\x0c\x10\x01\xff\xfe\x02\x00";
      read_00247_ptr += cgc_data_match(read_00247 + read_00247_ptr, read_00247_len - read_00247_ptr, match_00247_00000, 8);
      cgc_free(read_00247);
      if (read_00247_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00246_00000[] = 
         "\x0c";
      static unsigned int write_00246_00000_len = 1;
      unsigned char *write_00246 = NULL;
      unsigned int write_00246_len = 0;
      write_00246 = cgc_append_buf(write_00246, &write_00246_len, write_00246_00000, write_00246_00000_len);
      if (write_00246_len > 0) {
         cgc_transmit_all(1, write_00246, write_00246_len);
      }
      cgc_free(write_00246);
   } while (0);
   do {
      unsigned char *read_00248;
      unsigned int read_00248_len;
      unsigned int read_00248_ptr = 0;
      //**** length read
      read_00248_len = 8;
      read_00248 = (unsigned char*)cgc_malloc(read_00248_len);
      int read_00248_res = cgc_length_read(0, read_00248, read_00248_len);
      if (read_00248_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00248_00000[] = 
         "\x08\x0c\x03\x01\xff\xc3\x02\x00";
      read_00248_ptr += cgc_data_match(read_00248 + read_00248_ptr, read_00248_len - read_00248_ptr, match_00248_00000, 8);
      cgc_free(read_00248);
      if (read_00248_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00247_00000[] = 
         "\x0c";
      static unsigned int write_00247_00000_len = 1;
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = cgc_append_buf(write_00247, &write_00247_len, write_00247_00000, write_00247_00000_len);
      if (write_00247_len > 0) {
         cgc_transmit_all(1, write_00247, write_00247_len);
      }
      cgc_free(write_00247);
   } while (0);
   do {
      unsigned char *read_00249;
      unsigned int read_00249_len;
      unsigned int read_00249_ptr = 0;
      //**** length read
      read_00249_len = 8;
      read_00249 = (unsigned char*)cgc_malloc(read_00249_len);
      int read_00249_res = cgc_length_read(0, read_00249, read_00249_len);
      if (read_00249_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00249_00000[] = 
         "\x09\x0c\x01\x01\xff\xc2\x02\x00";
      read_00249_ptr += cgc_data_match(read_00249 + read_00249_ptr, read_00249_len - read_00249_ptr, match_00249_00000, 8);
      cgc_free(read_00249);
      if (read_00249_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00248_00000[] = 
         "\x0c";
      static unsigned int write_00248_00000_len = 1;
      unsigned char *write_00248 = NULL;
      unsigned int write_00248_len = 0;
      write_00248 = cgc_append_buf(write_00248, &write_00248_len, write_00248_00000, write_00248_00000_len);
      if (write_00248_len > 0) {
         cgc_transmit_all(1, write_00248, write_00248_len);
      }
      cgc_free(write_00248);
   } while (0);
   do {
      unsigned char *read_00250;
      unsigned int read_00250_len;
      unsigned int read_00250_ptr = 0;
      //**** length read
      read_00250_len = 8;
      read_00250 = (unsigned char*)cgc_malloc(read_00250_len);
      int read_00250_res = cgc_length_read(0, read_00250, read_00250_len);
      if (read_00250_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00250_00000[] = 
         "\x0a\x0c\x0c\x01\xff\xcd\x02\x00";
      read_00250_ptr += cgc_data_match(read_00250 + read_00250_ptr, read_00250_len - read_00250_ptr, match_00250_00000, 8);
      cgc_free(read_00250);
      if (read_00250_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00249_00000[] = 
         "\x0c";
      static unsigned int write_00249_00000_len = 1;
      unsigned char *write_00249 = NULL;
      unsigned int write_00249_len = 0;
      write_00249 = cgc_append_buf(write_00249, &write_00249_len, write_00249_00000, write_00249_00000_len);
      if (write_00249_len > 0) {
         cgc_transmit_all(1, write_00249, write_00249_len);
      }
      cgc_free(write_00249);
   } while (0);
   do {
      unsigned char *read_00251;
      unsigned int read_00251_len;
      unsigned int read_00251_ptr = 0;
      //**** length read
      read_00251_len = 8;
      read_00251 = (unsigned char*)cgc_malloc(read_00251_len);
      int read_00251_res = cgc_length_read(0, read_00251, read_00251_len);
      if (read_00251_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00251_00000[] = 
         "\x01\x0c\x05\x01\xff\xe6\x02\x00";
      read_00251_ptr += cgc_data_match(read_00251 + read_00251_ptr, read_00251_len - read_00251_ptr, match_00251_00000, 8);
      cgc_free(read_00251);
      if (read_00251_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00250_00000[] = 
         "\x0c";
      static unsigned int write_00250_00000_len = 1;
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = cgc_append_buf(write_00250, &write_00250_len, write_00250_00000, write_00250_00000_len);
      if (write_00250_len > 0) {
         cgc_transmit_all(1, write_00250, write_00250_len);
      }
      cgc_free(write_00250);
   } while (0);
   do {
      unsigned char *read_00252;
      unsigned int read_00252_len;
      unsigned int read_00252_ptr = 0;
      //**** length read
      read_00252_len = 8;
      read_00252 = (unsigned char*)cgc_malloc(read_00252_len);
      int read_00252_res = cgc_length_read(0, read_00252, read_00252_len);
      if (read_00252_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00252_00000[] = 
         "\x02\x0c\x04\x01\xff\xc6\x02\x00";
      read_00252_ptr += cgc_data_match(read_00252 + read_00252_ptr, read_00252_len - read_00252_ptr, match_00252_00000, 8);
      cgc_free(read_00252);
      if (read_00252_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00251_00000[] = 
         "\x0c";
      static unsigned int write_00251_00000_len = 1;
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = cgc_append_buf(write_00251, &write_00251_len, write_00251_00000, write_00251_00000_len);
      if (write_00251_len > 0) {
         cgc_transmit_all(1, write_00251, write_00251_len);
      }
      cgc_free(write_00251);
   } while (0);
   do {
      unsigned char *read_00253;
      unsigned int read_00253_len;
      unsigned int read_00253_ptr = 0;
      //**** length read
      read_00253_len = 8;
      read_00253 = (unsigned char*)cgc_malloc(read_00253_len);
      int read_00253_res = cgc_length_read(0, read_00253, read_00253_len);
      if (read_00253_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00253_00000[] = 
         "\x03\x0c\x07\x01\xff\xaf\x02\x00";
      read_00253_ptr += cgc_data_match(read_00253 + read_00253_ptr, read_00253_len - read_00253_ptr, match_00253_00000, 8);
      cgc_free(read_00253);
      if (read_00253_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00252_00000[] = 
         "\x0c";
      static unsigned int write_00252_00000_len = 1;
      unsigned char *write_00252 = NULL;
      unsigned int write_00252_len = 0;
      write_00252 = cgc_append_buf(write_00252, &write_00252_len, write_00252_00000, write_00252_00000_len);
      if (write_00252_len > 0) {
         cgc_transmit_all(1, write_00252, write_00252_len);
      }
      cgc_free(write_00252);
   } while (0);
   do {
      unsigned char *read_00254;
      unsigned int read_00254_len;
      unsigned int read_00254_ptr = 0;
      //**** length read
      read_00254_len = 8;
      read_00254 = (unsigned char*)cgc_malloc(read_00254_len);
      int read_00254_res = cgc_length_read(0, read_00254, read_00254_len);
      if (read_00254_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00254_00000[] = 
         "\x04\x0c\x01\x01\xff\xf9\x02\x00";
      read_00254_ptr += cgc_data_match(read_00254 + read_00254_ptr, read_00254_len - read_00254_ptr, match_00254_00000, 8);
      cgc_free(read_00254);
      if (read_00254_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00253_00000[] = 
         "\x0c";
      static unsigned int write_00253_00000_len = 1;
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = cgc_append_buf(write_00253, &write_00253_len, write_00253_00000, write_00253_00000_len);
      if (write_00253_len > 0) {
         cgc_transmit_all(1, write_00253, write_00253_len);
      }
      cgc_free(write_00253);
   } while (0);
   do {
      unsigned char *read_00255;
      unsigned int read_00255_len;
      unsigned int read_00255_ptr = 0;
      //**** length read
      read_00255_len = 8;
      read_00255 = (unsigned char*)cgc_malloc(read_00255_len);
      int read_00255_res = cgc_length_read(0, read_00255, read_00255_len);
      if (read_00255_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00255_00000[] = 
         "\x05\x0c\x04\x01\xff\xba\x02\x00";
      read_00255_ptr += cgc_data_match(read_00255 + read_00255_ptr, read_00255_len - read_00255_ptr, match_00255_00000, 8);
      cgc_free(read_00255);
      if (read_00255_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00254_00000[] = 
         "\x0c";
      static unsigned int write_00254_00000_len = 1;
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = cgc_append_buf(write_00254, &write_00254_len, write_00254_00000, write_00254_00000_len);
      if (write_00254_len > 0) {
         cgc_transmit_all(1, write_00254, write_00254_len);
      }
      cgc_free(write_00254);
   } while (0);
   do {
      unsigned char *read_00256;
      unsigned int read_00256_len;
      unsigned int read_00256_ptr = 0;
      //**** length read
      read_00256_len = 8;
      read_00256 = (unsigned char*)cgc_malloc(read_00256_len);
      int read_00256_res = cgc_length_read(0, read_00256, read_00256_len);
      if (read_00256_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00256_00000[] = 
         "\x06\x0c\x00\x01\xff\xec\x02\x00";
      read_00256_ptr += cgc_data_match(read_00256 + read_00256_ptr, read_00256_len - read_00256_ptr, match_00256_00000, 8);
      cgc_free(read_00256);
      if (read_00256_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00255_00000[] = 
         "\x0c";
      static unsigned int write_00255_00000_len = 1;
      unsigned char *write_00255 = NULL;
      unsigned int write_00255_len = 0;
      write_00255 = cgc_append_buf(write_00255, &write_00255_len, write_00255_00000, write_00255_00000_len);
      if (write_00255_len > 0) {
         cgc_transmit_all(1, write_00255, write_00255_len);
      }
      cgc_free(write_00255);
   } while (0);
   do {
      unsigned char *read_00257;
      unsigned int read_00257_len;
      unsigned int read_00257_ptr = 0;
      //**** length read
      read_00257_len = 8;
      read_00257 = (unsigned char*)cgc_malloc(read_00257_len);
      int read_00257_res = cgc_length_read(0, read_00257, read_00257_len);
      if (read_00257_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00257_00000[] = 
         "\x07\x0c\x01\x01\xff\xfa\x02\x00";
      read_00257_ptr += cgc_data_match(read_00257 + read_00257_ptr, read_00257_len - read_00257_ptr, match_00257_00000, 8);
      cgc_free(read_00257);
      if (read_00257_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00256_00000[] = 
         "\x0c";
      static unsigned int write_00256_00000_len = 1;
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = cgc_append_buf(write_00256, &write_00256_len, write_00256_00000, write_00256_00000_len);
      if (write_00256_len > 0) {
         cgc_transmit_all(1, write_00256, write_00256_len);
      }
      cgc_free(write_00256);
   } while (0);
   do {
      unsigned char *read_00258;
      unsigned int read_00258_len;
      unsigned int read_00258_ptr = 0;
      //**** length read
      read_00258_len = 8;
      read_00258 = (unsigned char*)cgc_malloc(read_00258_len);
      int read_00258_res = cgc_length_read(0, read_00258, read_00258_len);
      if (read_00258_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00258_00000[] = 
         "\x08\x0c\x09\x01\xff\xcc\x02\x00";
      read_00258_ptr += cgc_data_match(read_00258 + read_00258_ptr, read_00258_len - read_00258_ptr, match_00258_00000, 8);
      cgc_free(read_00258);
      if (read_00258_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00257_00000[] = 
         "\x0c";
      static unsigned int write_00257_00000_len = 1;
      unsigned char *write_00257 = NULL;
      unsigned int write_00257_len = 0;
      write_00257 = cgc_append_buf(write_00257, &write_00257_len, write_00257_00000, write_00257_00000_len);
      if (write_00257_len > 0) {
         cgc_transmit_all(1, write_00257, write_00257_len);
      }
      cgc_free(write_00257);
   } while (0);
   do {
      unsigned char *read_00259;
      unsigned int read_00259_len;
      unsigned int read_00259_ptr = 0;
      //**** length read
      read_00259_len = 8;
      read_00259 = (unsigned char*)cgc_malloc(read_00259_len);
      int read_00259_res = cgc_length_read(0, read_00259, read_00259_len);
      if (read_00259_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00259_00000[] = 
         "\x09\x0c\x00\x01\xff\xcd\x02\x00";
      read_00259_ptr += cgc_data_match(read_00259 + read_00259_ptr, read_00259_len - read_00259_ptr, match_00259_00000, 8);
      cgc_free(read_00259);
      if (read_00259_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00258_00000[] = 
         "\x0c";
      static unsigned int write_00258_00000_len = 1;
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = cgc_append_buf(write_00258, &write_00258_len, write_00258_00000, write_00258_00000_len);
      if (write_00258_len > 0) {
         cgc_transmit_all(1, write_00258, write_00258_len);
      }
      cgc_free(write_00258);
   } while (0);
   do {
      unsigned char *read_00260;
      unsigned int read_00260_len;
      unsigned int read_00260_ptr = 0;
      //**** length read
      read_00260_len = 8;
      read_00260 = (unsigned char*)cgc_malloc(read_00260_len);
      int read_00260_res = cgc_length_read(0, read_00260, read_00260_len);
      if (read_00260_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00260_00000[] = 
         "\x0a\x0c\x09\x01\xff\xcd\x02\x00";
      read_00260_ptr += cgc_data_match(read_00260 + read_00260_ptr, read_00260_len - read_00260_ptr, match_00260_00000, 8);
      cgc_free(read_00260);
      if (read_00260_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00259_00000[] = 
         "\x0c";
      static unsigned int write_00259_00000_len = 1;
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = cgc_append_buf(write_00259, &write_00259_len, write_00259_00000, write_00259_00000_len);
      if (write_00259_len > 0) {
         cgc_transmit_all(1, write_00259, write_00259_len);
      }
      cgc_free(write_00259);
   } while (0);
}
