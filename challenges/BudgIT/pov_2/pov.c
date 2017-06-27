#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x68\x59\x59\x77\x35\x65\x50\x56\x53\x07";
      static unsigned int write_00001_00000_len = 10;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\xf9\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 20);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x59\x7a\x48\x46\x47\x78\x35\x6d\x56\x07";
      static unsigned int write_00004_00000_len = 10;
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
         "\x53\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 20);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x78\x73\x6b\x6d\x4c\x4a\x61\x73\x6f\x07";
      static unsigned int write_00007_00000_len = 10;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\xe7\x02\x00\x00";
      static unsigned int write_00008_00000_len = 4;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 20);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x54\x66\x77\x71\x53\x43\x74\x4a\x33\x07";
      static unsigned int write_00010_00000_len = 10;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\xa6\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 20);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x65\x71\x6b\x56\x36\x42\x76\x30\x51\x07";
      static unsigned int write_00013_00000_len = 10;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\xd0\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 20);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x6d\x6f\x76\x79\x75\x32\x31\x46\x47\x07";
      static unsigned int write_00016_00000_len = 10;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x2b\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 20);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x46\x48\x6b\x4b\x65\x51\x4c\x35\x72\x07";
      static unsigned int write_00019_00000_len = 10;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x77\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 20);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x72\x4f\x32\x6e\x54\x67\x61\x63\x6e\x07";
      static unsigned int write_00022_00000_len = 10;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x68\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 20);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x70\x70\x63\x63\x38\x72\x41\x75\x4f\x07";
      static unsigned int write_00025_00000_len = 10;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x9b\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 20);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x75\x4e\x78\x69\x47\x71\x31\x35\x4c\x07";
      static unsigned int write_00028_00000_len = 10;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x4b\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 20);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x37\x52\x32\x65\x48\x42\x46\x35\x75\x07";
      static unsigned int write_00031_00000_len = 10;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x94\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 20);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x66\x6d\x39\x59\x62\x6e\x33\x6f\x6e\x07";
      static unsigned int write_00034_00000_len = 10;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x8b\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 20);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x32\x4d\x52\x34\x43\x59\x37\x50\x67\x07";
      static unsigned int write_00037_00000_len = 10;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x48\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 20);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x34\x38\x35\x6b\x71\x43\x43\x6d\x43\x07";
      static unsigned int write_00040_00000_len = 10;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\xaa\x01\x00\x00";
      static unsigned int write_00041_00000_len = 4;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 20);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x71\x52\x72\x38\x4b\x6a\x6f\x6d\x75\x07";
      static unsigned int write_00043_00000_len = 10;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x79\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 20);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x70\x59\x33\x39\x64\x6c\x54\x48\x64\x07";
      static unsigned int write_00046_00000_len = 10;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x51\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 20);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00048_00000_len = 4;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x76\x69\x71\x5a\x66\x30\x56\x6f\x4a\x07";
      static unsigned int write_00049_00000_len = 10;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\xfd\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 20);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x36\x74\x65\x70\x49\x67\x64\x57\x42\x07";
      static unsigned int write_00052_00000_len = 10;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x32\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 20);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x6a\x4c\x53\x45\x7a\x46\x47\x4a\x34\x07";
      static unsigned int write_00055_00000_len = 10;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\xc1\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 20);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x45\x72\x69\x79\x54\x32\x6e\x42\x44\x07";
      static unsigned int write_00058_00000_len = 10;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\xdd\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 20);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x4e\x36\x72\x41\x71\x71\x6a\x6e\x35\x07";
      static unsigned int write_00061_00000_len = 10;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x84\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 20);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x62\x59\x6a\x6a\x6a\x55\x5a\x35\x51\x07";
      static unsigned int write_00064_00000_len = 10;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x0e\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 20);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x4a\x63\x4d\x43\x41\x79\x32\x7a\x65\x07";
      static unsigned int write_00067_00000_len = 10;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x57\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 20);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x6d\x73\x38\x73\x54\x70\x53\x56\x70\x07";
      static unsigned int write_00070_00000_len = 10;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\xd1\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 20);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x61\x54\x66\x59\x48\x46\x45\x55\x37\x07";
      static unsigned int write_00073_00000_len = 10;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\xde\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 20);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x66\x64\x49\x79\x77\x64\x37\x7a\x50\x07";
      static unsigned int write_00076_00000_len = 10;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\xdd\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 20);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x49\x71\x64\x72\x4c\x4c\x34\x36\x33\x07";
      static unsigned int write_00079_00000_len = 10;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x1a\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 20);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x32\x31\x59\x42\x51\x37\x4d\x35\x51\x07";
      static unsigned int write_00082_00000_len = 10;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\xbc\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 20);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x4f\x31\x73\x66\x6b\x47\x33\x6d\x71\x07";
      static unsigned int write_00085_00000_len = 10;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x2e\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 20);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x43\x42\x4e\x68\x4f\x66\x58\x71\x46\x07";
      static unsigned int write_00088_00000_len = 10;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x8d\x03\x00\x00";
      static unsigned int write_00089_00000_len = 4;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 20);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x64\x46\x4c\x69\x31\x38\x33\x37\x62\x07";
      static unsigned int write_00091_00000_len = 10;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x6e\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 20);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x7a\x31\x4c\x6a\x36\x63\x51\x43\x44\x07";
      static unsigned int write_00094_00000_len = 10;
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = cgc_append_buf(write_00094, &write_00094_len, write_00094_00000, write_00094_00000_len);
      if (write_00094_len > 0) {
         cgc_transmit_all(1, write_00094, write_00094_len);
      }
      cgc_free(write_00094);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\xa7\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 20);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x59\x42\x59\x34\x72\x39\x37\x46\x65\x07";
      static unsigned int write_00097_00000_len = 10;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x2b\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00032_ptr += cgc_data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 20);
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x30\x79\x4f\x56\x58\x4c\x46\x4e\x69\x07";
      static unsigned int write_00100_00000_len = 10;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x0c\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00033_ptr += cgc_data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 20);
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x38\x65\x65\x6c\x65\x63\x54\x58\x70\x07";
      static unsigned int write_00103_00000_len = 10;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x35\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00034_ptr += cgc_data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 20);
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x38\x30\x35\x6f\x4f\x53\x47\x32\x69\x07";
      static unsigned int write_00106_00000_len = 10;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\xe1\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00035_ptr += cgc_data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 20);
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x41\x45\x6b\x6b\x43\x4c\x75\x51\x4a\x07";
      static unsigned int write_00109_00000_len = 10;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x35\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00036_ptr += cgc_data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 20);
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x50\x64\x76\x72\x51\x48\x41\x77\x46\x07";
      static unsigned int write_00112_00000_len = 10;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x8e\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 20);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00114_00000_len = 4;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x63\x54\x4a\x4e\x53\x4b\x31\x6f\x73\x07";
      static unsigned int write_00115_00000_len = 10;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x9f\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 20);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x62\x70\x44\x32\x30\x68\x41\x54\x36\x07";
      static unsigned int write_00118_00000_len = 10;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x13\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 20);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x59\x6d\x71\x55\x59\x6a\x46\x4f\x43\x07";
      static unsigned int write_00121_00000_len = 10;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x5a\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 20);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x7a\x38\x5a\x4f\x46\x6a\x73\x49\x38\x07";
      static unsigned int write_00124_00000_len = 10;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x75\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 20);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00126_00000_len = 4;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x5a\x72\x49\x42\x5a\x46\x76\x7a\x32\x07";
      static unsigned int write_00127_00000_len = 10;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\xc6\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 20);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x50\x52\x32\x4a\x61\x49\x45\x55\x56\x07";
      static unsigned int write_00130_00000_len = 10;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x25\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 20);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x5a\x4a\x77\x69\x72\x7a\x44\x4b\x66\x07";
      static unsigned int write_00133_00000_len = 10;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x62\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 20);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x31\x39\x4d\x62\x74\x6e\x6c\x61\x6a\x07";
      static unsigned int write_00136_00000_len = 10;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x50\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 20);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x42\x35\x42\x73\x74\x39\x4f\x62\x56\x07";
      static unsigned int write_00139_00000_len = 10;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x26\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 20);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x56\x71\x4e\x4e\x4d\x62\x4c\x55\x53\x07";
      static unsigned int write_00142_00000_len = 10;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x8f\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 20);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x6a\x6c\x39\x4d\x58\x65\x63\x35\x6c\x07";
      static unsigned int write_00145_00000_len = 10;
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = cgc_append_buf(write_00145, &write_00145_len, write_00145_00000, write_00145_00000_len);
      if (write_00145_len > 0) {
         cgc_transmit_all(1, write_00145, write_00145_len);
      }
      cgc_free(write_00145);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00146_00000[] = 
         "\x16\x00\x00\x00";
      static unsigned int write_00146_00000_len = 4;
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = cgc_append_buf(write_00146, &write_00146_len, write_00146_00000, write_00146_00000_len);
      if (write_00146_len > 0) {
         cgc_transmit_all(1, write_00146, write_00146_len);
      }
      cgc_free(write_00146);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 20);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00148_00000[] = 
         "\x48\x6a\x6f\x75\x61\x55\x76\x36\x76\x07";
      static unsigned int write_00148_00000_len = 10;
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = cgc_append_buf(write_00148, &write_00148_len, write_00148_00000, write_00148_00000_len);
      if (write_00148_len > 0) {
         cgc_transmit_all(1, write_00148, write_00148_len);
      }
      cgc_free(write_00148);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x47\x00\x00\x00";
      static unsigned int write_00149_00000_len = 4;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = cgc_append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         cgc_transmit_all(1, write_00149, write_00149_len);
      }
      cgc_free(write_00149);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 20);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00150_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x57\x4b\x49\x49\x47\x73\x54\x6a\x52\x07";
      static unsigned int write_00151_00000_len = 10;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = cgc_append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         cgc_transmit_all(1, write_00151, write_00151_len);
      }
      cgc_free(write_00151);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00152_00000[] = 
         "\x9c\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00050_ptr += cgc_data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 20);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00154_00000[] = 
         "\x48\x31\x59\x6c\x59\x38\x33\x6b\x76\x07";
      static unsigned int write_00154_00000_len = 10;
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = cgc_append_buf(write_00154, &write_00154_len, write_00154_00000, write_00154_00000_len);
      if (write_00154_len > 0) {
         cgc_transmit_all(1, write_00154, write_00154_len);
      }
      cgc_free(write_00154);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x07\x00\x00\x00";
      static unsigned int write_00155_00000_len = 4;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = cgc_append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         cgc_transmit_all(1, write_00155, write_00155_len);
      }
      cgc_free(write_00155);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 20);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00156_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x4b\x6b\x56\x44\x62\x69\x65\x4a\x50\x07";
      static unsigned int write_00157_00000_len = 10;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = cgc_append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         cgc_transmit_all(1, write_00157, write_00157_len);
      }
      cgc_free(write_00157);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00158_00000[] = 
         "\x6f\x02\x00\x00";
      static unsigned int write_00158_00000_len = 4;
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = cgc_append_buf(write_00158, &write_00158_len, write_00158_00000, write_00158_00000_len);
      if (write_00158_len > 0) {
         cgc_transmit_all(1, write_00158, write_00158_len);
      }
      cgc_free(write_00158);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 20);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00160_00000[] = 
         "\x30\x6b\x76\x45\x6a\x62\x77\x36\x41\x07";
      static unsigned int write_00160_00000_len = 10;
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = cgc_append_buf(write_00160, &write_00160_len, write_00160_00000, write_00160_00000_len);
      if (write_00160_len > 0) {
         cgc_transmit_all(1, write_00160, write_00160_len);
      }
      cgc_free(write_00160);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x59\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 20);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00162_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00162_00000_len = 4;
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = cgc_append_buf(write_00162, &write_00162_len, write_00162_00000, write_00162_00000_len);
      if (write_00162_len > 0) {
         cgc_transmit_all(1, write_00162, write_00162_len);
      }
      cgc_free(write_00162);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x62\x49\x52\x49\x66\x70\x35\x43\x45\x07";
      static unsigned int write_00163_00000_len = 10;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = cgc_append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         cgc_transmit_all(1, write_00163, write_00163_len);
      }
      cgc_free(write_00163);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00164_00000[] = 
         "\xd5\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00054_ptr += cgc_data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 20);
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00166_00000[] = 
         "\x48\x35\x74\x62\x42\x50\x56\x69\x53\x07";
      static unsigned int write_00166_00000_len = 10;
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = cgc_append_buf(write_00166, &write_00166_len, write_00166_00000, write_00166_00000_len);
      if (write_00166_len > 0) {
         cgc_transmit_all(1, write_00166, write_00166_len);
      }
      cgc_free(write_00166);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x76\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00055_ptr += cgc_data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 20);
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00168_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00168_00000_len = 4;
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = cgc_append_buf(write_00168, &write_00168_len, write_00168_00000, write_00168_00000_len);
      if (write_00168_len > 0) {
         cgc_transmit_all(1, write_00168, write_00168_len);
      }
      cgc_free(write_00168);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x65\x37\x6f\x7a\x77\x57\x71\x4b\x66\x07";
      static unsigned int write_00169_00000_len = 10;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = cgc_append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         cgc_transmit_all(1, write_00169, write_00169_len);
      }
      cgc_free(write_00169);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00170_00000[] = 
         "\xe6\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00056_ptr += cgc_data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 20);
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00172_00000[] = 
         "\x52\x34\x69\x45\x67\x4b\x68\x4f\x58\x07";
      static unsigned int write_00172_00000_len = 10;
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = cgc_append_buf(write_00172, &write_00172_len, write_00172_00000, write_00172_00000_len);
      if (write_00172_len > 0) {
         cgc_transmit_all(1, write_00172, write_00172_len);
      }
      cgc_free(write_00172);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\xb7\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00057_ptr += cgc_data_match(read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, match_00057_00000, 20);
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00174_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x78\x52\x58\x59\x74\x56\x4b\x37\x70\x07";
      static unsigned int write_00175_00000_len = 10;
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = cgc_append_buf(write_00175, &write_00175_len, write_00175_00000, write_00175_00000_len);
      if (write_00175_len > 0) {
         cgc_transmit_all(1, write_00175, write_00175_len);
      }
      cgc_free(write_00175);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00176_00000[] = 
         "\x81\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00058_ptr += cgc_data_match(read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, match_00058_00000, 20);
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00178_00000[] = 
         "\x32\x6d\x42\x65\x39\x4c\x49\x4e\x41\x07";
      static unsigned int write_00178_00000_len = 10;
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = cgc_append_buf(write_00178, &write_00178_len, write_00178_00000, write_00178_00000_len);
      if (write_00178_len > 0) {
         cgc_transmit_all(1, write_00178, write_00178_len);
      }
      cgc_free(write_00178);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\xd3\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00059_ptr += cgc_data_match(read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, match_00059_00000, 20);
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00180_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x33\x44\x39\x56\x62\x76\x52\x31\x66\x07";
      static unsigned int write_00181_00000_len = 10;
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = cgc_append_buf(write_00181, &write_00181_len, write_00181_00000, write_00181_00000_len);
      if (write_00181_len > 0) {
         cgc_transmit_all(1, write_00181, write_00181_len);
      }
      cgc_free(write_00181);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00182_00000[] = 
         "\x8a\x00\x00\x00";
      static unsigned int write_00182_00000_len = 4;
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = cgc_append_buf(write_00182, &write_00182_len, write_00182_00000, write_00182_00000_len);
      if (write_00182_len > 0) {
         cgc_transmit_all(1, write_00182, write_00182_len);
      }
      cgc_free(write_00182);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00060_ptr += cgc_data_match(read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, match_00060_00000, 20);
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00183_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00184_00000[] = 
         "\x45\x45\x36\x30\x4e\x56\x62\x63\x67\x07";
      static unsigned int write_00184_00000_len = 10;
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = cgc_append_buf(write_00184, &write_00184_len, write_00184_00000, write_00184_00000_len);
      if (write_00184_len > 0) {
         cgc_transmit_all(1, write_00184, write_00184_len);
      }
      cgc_free(write_00184);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00185_00000[] = 
         "\x7d\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00061_ptr += cgc_data_match(read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, match_00061_00000, 20);
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00186_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00187_00000[] = 
         "\x35\x41\x4e\x4e\x46\x33\x63\x5a\x52\x07";
      static unsigned int write_00187_00000_len = 10;
      unsigned char *write_00187 = NULL;
      unsigned int write_00187_len = 0;
      write_00187 = cgc_append_buf(write_00187, &write_00187_len, write_00187_00000, write_00187_00000_len);
      if (write_00187_len > 0) {
         cgc_transmit_all(1, write_00187, write_00187_len);
      }
      cgc_free(write_00187);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00188_00000[] = 
         "\x83\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00062_ptr += cgc_data_match(read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, match_00062_00000, 20);
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00189_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00190_00000[] = 
         "\x48\x79\x59\x4e\x6f\x6d\x56\x52\x57\x07";
      static unsigned int write_00190_00000_len = 10;
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = cgc_append_buf(write_00190, &write_00190_len, write_00190_00000, write_00190_00000_len);
      if (write_00190_len > 0) {
         cgc_transmit_all(1, write_00190, write_00190_len);
      }
      cgc_free(write_00190);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00191_00000[] = 
         "\x61\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00063_ptr += cgc_data_match(read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, match_00063_00000, 20);
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00192_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00193_00000[] = 
         "\x49\x7a\x4f\x62\x61\x77\x51\x36\x76\x07";
      static unsigned int write_00193_00000_len = 10;
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = cgc_append_buf(write_00193, &write_00193_len, write_00193_00000, write_00193_00000_len);
      if (write_00193_len > 0) {
         cgc_transmit_all(1, write_00193, write_00193_len);
      }
      cgc_free(write_00193);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00194_00000[] = 
         "\x20\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00064_ptr += cgc_data_match(read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, match_00064_00000, 20);
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00195_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00195_00000_len = 4;
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = cgc_append_buf(write_00195, &write_00195_len, write_00195_00000, write_00195_00000_len);
      if (write_00195_len > 0) {
         cgc_transmit_all(1, write_00195, write_00195_len);
      }
      cgc_free(write_00195);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00196_00000[] = 
         "\x77\x55\x6f\x36\x77\x45\x6d\x51\x68\x07";
      static unsigned int write_00196_00000_len = 10;
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = cgc_append_buf(write_00196, &write_00196_len, write_00196_00000, write_00196_00000_len);
      if (write_00196_len > 0) {
         cgc_transmit_all(1, write_00196, write_00196_len);
      }
      cgc_free(write_00196);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00197_00000[] = 
         "\xe6\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00065_ptr += cgc_data_match(read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, match_00065_00000, 20);
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00198_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00199_00000[] = 
         "\x30\x4e\x6d\x4b\x6d\x43\x4c\x41\x78\x07";
      static unsigned int write_00199_00000_len = 10;
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = cgc_append_buf(write_00199, &write_00199_len, write_00199_00000, write_00199_00000_len);
      if (write_00199_len > 0) {
         cgc_transmit_all(1, write_00199, write_00199_len);
      }
      cgc_free(write_00199);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00200_00000[] = 
         "\xbd\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00066_ptr += cgc_data_match(read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, match_00066_00000, 20);
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00201_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00202_00000[] = 
         "\x66\x51\x36\x6f\x35\x68\x30\x49\x4c\x07";
      static unsigned int write_00202_00000_len = 10;
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = cgc_append_buf(write_00202, &write_00202_len, write_00202_00000, write_00202_00000_len);
      if (write_00202_len > 0) {
         cgc_transmit_all(1, write_00202, write_00202_len);
      }
      cgc_free(write_00202);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00203_00000[] = 
         "\xb6\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00067_ptr += cgc_data_match(read_00067 + read_00067_ptr, read_00067_len - read_00067_ptr, match_00067_00000, 20);
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00204_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00205_00000[] = 
         "\x35\x77\x62\x4c\x78\x6d\x4a\x55\x7a\x07";
      static unsigned int write_00205_00000_len = 10;
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = cgc_append_buf(write_00205, &write_00205_len, write_00205_00000, write_00205_00000_len);
      if (write_00205_len > 0) {
         cgc_transmit_all(1, write_00205, write_00205_len);
      }
      cgc_free(write_00205);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00206_00000[] = 
         "\xb8\x01\x00\x00";
      static unsigned int write_00206_00000_len = 4;
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = cgc_append_buf(write_00206, &write_00206_len, write_00206_00000, write_00206_00000_len);
      if (write_00206_len > 0) {
         cgc_transmit_all(1, write_00206, write_00206_len);
      }
      cgc_free(write_00206);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00068_ptr += cgc_data_match(read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, match_00068_00000, 20);
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00207_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00208_00000[] = 
         "\x33\x42\x49\x5a\x68\x63\x54\x6d\x33\x07";
      static unsigned int write_00208_00000_len = 10;
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = cgc_append_buf(write_00208, &write_00208_len, write_00208_00000, write_00208_00000_len);
      if (write_00208_len > 0) {
         cgc_transmit_all(1, write_00208, write_00208_len);
      }
      cgc_free(write_00208);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00209_00000[] = 
         "\x92\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00069_ptr += cgc_data_match(read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, match_00069_00000, 20);
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00210_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00211_00000[] = 
         "\x68\x4b\x72\x44\x72\x31\x48\x43\x64\x07";
      static unsigned int write_00211_00000_len = 10;
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = cgc_append_buf(write_00211, &write_00211_len, write_00211_00000, write_00211_00000_len);
      if (write_00211_len > 0) {
         cgc_transmit_all(1, write_00211, write_00211_len);
      }
      cgc_free(write_00211);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00212_00000[] = 
         "\x2f\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00070_ptr += cgc_data_match(read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, match_00070_00000, 20);
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00213_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00214_00000[] = 
         "\x69\x71\x4a\x34\x54\x57\x64\x4c\x36\x07";
      static unsigned int write_00214_00000_len = 10;
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = cgc_append_buf(write_00214, &write_00214_len, write_00214_00000, write_00214_00000_len);
      if (write_00214_len > 0) {
         cgc_transmit_all(1, write_00214, write_00214_len);
      }
      cgc_free(write_00214);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00215_00000[] = 
         "\x03\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00071_ptr += cgc_data_match(read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, match_00071_00000, 20);
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00216_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00217_00000[] = 
         "\x6f\x66\x51\x4d\x46\x74\x63\x74\x76\x07";
      static unsigned int write_00217_00000_len = 10;
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = cgc_append_buf(write_00217, &write_00217_len, write_00217_00000, write_00217_00000_len);
      if (write_00217_len > 0) {
         cgc_transmit_all(1, write_00217, write_00217_len);
      }
      cgc_free(write_00217);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00218_00000[] = 
         "\x21\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00072_ptr += cgc_data_match(read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, match_00072_00000, 20);
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00219_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00220_00000[] = 
         "\x58\x33\x52\x4b\x69\x41\x72\x48\x34\x07";
      static unsigned int write_00220_00000_len = 10;
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = cgc_append_buf(write_00220, &write_00220_len, write_00220_00000, write_00220_00000_len);
      if (write_00220_len > 0) {
         cgc_transmit_all(1, write_00220, write_00220_len);
      }
      cgc_free(write_00220);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00221_00000[] = 
         "\x9f\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00073_ptr += cgc_data_match(read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, match_00073_00000, 20);
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00222_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00223_00000[] = 
         "\x68\x6b\x33\x74\x75\x6c\x35\x72\x73\x07";
      static unsigned int write_00223_00000_len = 10;
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = cgc_append_buf(write_00223, &write_00223_len, write_00223_00000, write_00223_00000_len);
      if (write_00223_len > 0) {
         cgc_transmit_all(1, write_00223, write_00223_len);
      }
      cgc_free(write_00223);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00224_00000[] = 
         "\x51\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00074_ptr += cgc_data_match(read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, match_00074_00000, 20);
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00225_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00226_00000[] = 
         "\x72\x39\x4a\x55\x4e\x49\x7a\x55\x58\x07";
      static unsigned int write_00226_00000_len = 10;
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = cgc_append_buf(write_00226, &write_00226_len, write_00226_00000, write_00226_00000_len);
      if (write_00226_len > 0) {
         cgc_transmit_all(1, write_00226, write_00226_len);
      }
      cgc_free(write_00226);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00227_00000[] = 
         "\x87\x02\x00\x00";
      static unsigned int write_00227_00000_len = 4;
      unsigned char *write_00227 = NULL;
      unsigned int write_00227_len = 0;
      write_00227 = cgc_append_buf(write_00227, &write_00227_len, write_00227_00000, write_00227_00000_len);
      if (write_00227_len > 0) {
         cgc_transmit_all(1, write_00227, write_00227_len);
      }
      cgc_free(write_00227);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00075_ptr += cgc_data_match(read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, match_00075_00000, 20);
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00228_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00229_00000[] = 
         "\x6e\x5a\x54\x6b\x56\x4e\x6f\x62\x4e\x07";
      static unsigned int write_00229_00000_len = 10;
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = cgc_append_buf(write_00229, &write_00229_len, write_00229_00000, write_00229_00000_len);
      if (write_00229_len > 0) {
         cgc_transmit_all(1, write_00229, write_00229_len);
      }
      cgc_free(write_00229);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00230_00000[] = 
         "\x1f\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00076_ptr += cgc_data_match(read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, match_00076_00000, 20);
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00231_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00232_00000[] = 
         "\x68\x56\x43\x65\x69\x4e\x5a\x31\x52\x07";
      static unsigned int write_00232_00000_len = 10;
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = cgc_append_buf(write_00232, &write_00232_len, write_00232_00000, write_00232_00000_len);
      if (write_00232_len > 0) {
         cgc_transmit_all(1, write_00232, write_00232_len);
      }
      cgc_free(write_00232);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00233_00000[] = 
         "\xd4\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00077_ptr += cgc_data_match(read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, match_00077_00000, 20);
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00234_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00234_00000_len = 4;
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = cgc_append_buf(write_00234, &write_00234_len, write_00234_00000, write_00234_00000_len);
      if (write_00234_len > 0) {
         cgc_transmit_all(1, write_00234, write_00234_len);
      }
      cgc_free(write_00234);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00235_00000[] = 
         "\x73\x74\x6e\x4e\x4f\x6e\x64\x4f\x35\x07";
      static unsigned int write_00235_00000_len = 10;
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = cgc_append_buf(write_00235, &write_00235_len, write_00235_00000, write_00235_00000_len);
      if (write_00235_len > 0) {
         cgc_transmit_all(1, write_00235, write_00235_len);
      }
      cgc_free(write_00235);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00236_00000[] = 
         "\x95\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00078_ptr += cgc_data_match(read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, match_00078_00000, 20);
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00237_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00238_00000[] = 
         "\x56\x63\x36\x67\x59\x76\x51\x54\x32\x07";
      static unsigned int write_00238_00000_len = 10;
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = cgc_append_buf(write_00238, &write_00238_len, write_00238_00000, write_00238_00000_len);
      if (write_00238_len > 0) {
         cgc_transmit_all(1, write_00238, write_00238_len);
      }
      cgc_free(write_00238);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00239_00000[] = 
         "\x6d\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00079_ptr += cgc_data_match(read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, match_00079_00000, 20);
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00240_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00241_00000[] = 
         "\x38\x4c\x44\x6b\x54\x4a\x72\x64\x4f\x07";
      static unsigned int write_00241_00000_len = 10;
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = cgc_append_buf(write_00241, &write_00241_len, write_00241_00000, write_00241_00000_len);
      if (write_00241_len > 0) {
         cgc_transmit_all(1, write_00241, write_00241_len);
      }
      cgc_free(write_00241);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00242_00000[] = 
         "\x19\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00080_ptr += cgc_data_match(read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, match_00080_00000, 20);
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00243_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00244_00000[] = 
         "\x39\x5a\x47\x51\x50\x42\x33\x34\x4b\x07";
      static unsigned int write_00244_00000_len = 10;
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = cgc_append_buf(write_00244, &write_00244_len, write_00244_00000, write_00244_00000_len);
      if (write_00244_len > 0) {
         cgc_transmit_all(1, write_00244, write_00244_len);
      }
      cgc_free(write_00244);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00245_00000[] = 
         "\xd9\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00081_ptr += cgc_data_match(read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, match_00081_00000, 20);
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00246_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00247_00000[] = 
         "\x79\x6b\x53\x54\x6e\x4f\x39\x70\x7a\x07";
      static unsigned int write_00247_00000_len = 10;
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = cgc_append_buf(write_00247, &write_00247_len, write_00247_00000, write_00247_00000_len);
      if (write_00247_len > 0) {
         cgc_transmit_all(1, write_00247, write_00247_len);
      }
      cgc_free(write_00247);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00248_00000[] = 
         "\x41\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00082_ptr += cgc_data_match(read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, match_00082_00000, 20);
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00249_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00250_00000[] = 
         "\x62\x6a\x32\x66\x67\x4f\x58\x68\x75\x07";
      static unsigned int write_00250_00000_len = 10;
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = cgc_append_buf(write_00250, &write_00250_len, write_00250_00000, write_00250_00000_len);
      if (write_00250_len > 0) {
         cgc_transmit_all(1, write_00250, write_00250_len);
      }
      cgc_free(write_00250);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00251_00000[] = 
         "\x22\x00\x00\x00";
      static unsigned int write_00251_00000_len = 4;
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = cgc_append_buf(write_00251, &write_00251_len, write_00251_00000, write_00251_00000_len);
      if (write_00251_len > 0) {
         cgc_transmit_all(1, write_00251, write_00251_len);
      }
      cgc_free(write_00251);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00083_ptr += cgc_data_match(read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, match_00083_00000, 20);
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00252_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00253_00000[] = 
         "\x77\x4a\x6b\x56\x31\x49\x43\x65\x45\x07";
      static unsigned int write_00253_00000_len = 10;
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = cgc_append_buf(write_00253, &write_00253_len, write_00253_00000, write_00253_00000_len);
      if (write_00253_len > 0) {
         cgc_transmit_all(1, write_00253, write_00253_len);
      }
      cgc_free(write_00253);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00254_00000[] = 
         "\x41\x02\x00\x00";
      static unsigned int write_00254_00000_len = 4;
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = cgc_append_buf(write_00254, &write_00254_len, write_00254_00000, write_00254_00000_len);
      if (write_00254_len > 0) {
         cgc_transmit_all(1, write_00254, write_00254_len);
      }
      cgc_free(write_00254);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00084_ptr += cgc_data_match(read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, match_00084_00000, 20);
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00255_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00256_00000[] = 
         "\x66\x43\x4a\x35\x36\x6f\x56\x55\x61\x07";
      static unsigned int write_00256_00000_len = 10;
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = cgc_append_buf(write_00256, &write_00256_len, write_00256_00000, write_00256_00000_len);
      if (write_00256_len > 0) {
         cgc_transmit_all(1, write_00256, write_00256_len);
      }
      cgc_free(write_00256);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00257_00000[] = 
         "\x30\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00085_ptr += cgc_data_match(read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, match_00085_00000, 20);
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00258_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00258_00000_len = 4;
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = cgc_append_buf(write_00258, &write_00258_len, write_00258_00000, write_00258_00000_len);
      if (write_00258_len > 0) {
         cgc_transmit_all(1, write_00258, write_00258_len);
      }
      cgc_free(write_00258);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00259_00000[] = 
         "\x37\x41\x7a\x6a\x75\x32\x52\x59\x4e\x07";
      static unsigned int write_00259_00000_len = 10;
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = cgc_append_buf(write_00259, &write_00259_len, write_00259_00000, write_00259_00000_len);
      if (write_00259_len > 0) {
         cgc_transmit_all(1, write_00259, write_00259_len);
      }
      cgc_free(write_00259);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00260_00000[] = 
         "\x55\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00086_ptr += cgc_data_match(read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, match_00086_00000, 20);
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00261_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00262_00000[] = 
         "\x4c\x63\x49\x6d\x37\x49\x34\x74\x51\x07";
      static unsigned int write_00262_00000_len = 10;
      unsigned char *write_00262 = NULL;
      unsigned int write_00262_len = 0;
      write_00262 = cgc_append_buf(write_00262, &write_00262_len, write_00262_00000, write_00262_00000_len);
      if (write_00262_len > 0) {
         cgc_transmit_all(1, write_00262, write_00262_len);
      }
      cgc_free(write_00262);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00263_00000[] = 
         "\x36\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00087_ptr += cgc_data_match(read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, match_00087_00000, 20);
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00264_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00264_00000_len = 4;
      unsigned char *write_00264 = NULL;
      unsigned int write_00264_len = 0;
      write_00264 = cgc_append_buf(write_00264, &write_00264_len, write_00264_00000, write_00264_00000_len);
      if (write_00264_len > 0) {
         cgc_transmit_all(1, write_00264, write_00264_len);
      }
      cgc_free(write_00264);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00265_00000[] = 
         "\x42\x41\x38\x5a\x63\x43\x45\x49\x57\x07";
      static unsigned int write_00265_00000_len = 10;
      unsigned char *write_00265 = NULL;
      unsigned int write_00265_len = 0;
      write_00265 = cgc_append_buf(write_00265, &write_00265_len, write_00265_00000, write_00265_00000_len);
      if (write_00265_len > 0) {
         cgc_transmit_all(1, write_00265, write_00265_len);
      }
      cgc_free(write_00265);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00266_00000[] = 
         "\xff\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00088_ptr += cgc_data_match(read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, match_00088_00000, 20);
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00267_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00268_00000[] = 
         "\x63\x36\x5a\x6d\x4c\x42\x43\x31\x4f\x07";
      static unsigned int write_00268_00000_len = 10;
      unsigned char *write_00268 = NULL;
      unsigned int write_00268_len = 0;
      write_00268 = cgc_append_buf(write_00268, &write_00268_len, write_00268_00000, write_00268_00000_len);
      if (write_00268_len > 0) {
         cgc_transmit_all(1, write_00268, write_00268_len);
      }
      cgc_free(write_00268);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00269_00000[] = 
         "\x67\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00089_ptr += cgc_data_match(read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, match_00089_00000, 20);
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00270_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00271_00000[] = 
         "\x46\x6a\x76\x51\x38\x6a\x32\x63\x42\x07";
      static unsigned int write_00271_00000_len = 10;
      unsigned char *write_00271 = NULL;
      unsigned int write_00271_len = 0;
      write_00271 = cgc_append_buf(write_00271, &write_00271_len, write_00271_00000, write_00271_00000_len);
      if (write_00271_len > 0) {
         cgc_transmit_all(1, write_00271, write_00271_len);
      }
      cgc_free(write_00271);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00272_00000[] = 
         "\xc1\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00090_ptr += cgc_data_match(read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, match_00090_00000, 20);
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00273_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00274_00000[] = 
         "\x31\x54\x4c\x6f\x6d\x35\x73\x4e\x61\x07";
      static unsigned int write_00274_00000_len = 10;
      unsigned char *write_00274 = NULL;
      unsigned int write_00274_len = 0;
      write_00274 = cgc_append_buf(write_00274, &write_00274_len, write_00274_00000, write_00274_00000_len);
      if (write_00274_len > 0) {
         cgc_transmit_all(1, write_00274, write_00274_len);
      }
      cgc_free(write_00274);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00275_00000[] = 
         "\x7a\x00\x00\x00";
      static unsigned int write_00275_00000_len = 4;
      unsigned char *write_00275 = NULL;
      unsigned int write_00275_len = 0;
      write_00275 = cgc_append_buf(write_00275, &write_00275_len, write_00275_00000, write_00275_00000_len);
      if (write_00275_len > 0) {
         cgc_transmit_all(1, write_00275, write_00275_len);
      }
      cgc_free(write_00275);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00091_ptr += cgc_data_match(read_00091 + read_00091_ptr, read_00091_len - read_00091_ptr, match_00091_00000, 20);
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00276_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00277_00000[] = 
         "\x45\x55\x58\x61\x4e\x78\x73\x34\x33\x07";
      static unsigned int write_00277_00000_len = 10;
      unsigned char *write_00277 = NULL;
      unsigned int write_00277_len = 0;
      write_00277 = cgc_append_buf(write_00277, &write_00277_len, write_00277_00000, write_00277_00000_len);
      if (write_00277_len > 0) {
         cgc_transmit_all(1, write_00277, write_00277_len);
      }
      cgc_free(write_00277);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00278_00000[] = 
         "\x11\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00092_ptr += cgc_data_match(read_00092 + read_00092_ptr, read_00092_len - read_00092_ptr, match_00092_00000, 20);
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00279_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00280_00000[] = 
         "\x37\x6f\x70\x41\x39\x75\x61\x49\x73\x07";
      static unsigned int write_00280_00000_len = 10;
      unsigned char *write_00280 = NULL;
      unsigned int write_00280_len = 0;
      write_00280 = cgc_append_buf(write_00280, &write_00280_len, write_00280_00000, write_00280_00000_len);
      if (write_00280_len > 0) {
         cgc_transmit_all(1, write_00280, write_00280_len);
      }
      cgc_free(write_00280);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00281_00000[] = 
         "\x51\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00093_ptr += cgc_data_match(read_00093 + read_00093_ptr, read_00093_len - read_00093_ptr, match_00093_00000, 20);
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00282_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00283_00000[] = 
         "\x56\x73\x52\x78\x50\x33\x72\x71\x6d\x07";
      static unsigned int write_00283_00000_len = 10;
      unsigned char *write_00283 = NULL;
      unsigned int write_00283_len = 0;
      write_00283 = cgc_append_buf(write_00283, &write_00283_len, write_00283_00000, write_00283_00000_len);
      if (write_00283_len > 0) {
         cgc_transmit_all(1, write_00283, write_00283_len);
      }
      cgc_free(write_00283);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00284_00000[] = 
         "\x3d\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00094_ptr += cgc_data_match(read_00094 + read_00094_ptr, read_00094_len - read_00094_ptr, match_00094_00000, 20);
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00285_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00286_00000[] = 
         "\x58\x61\x31\x32\x52\x72\x4b\x69\x35\x07";
      static unsigned int write_00286_00000_len = 10;
      unsigned char *write_00286 = NULL;
      unsigned int write_00286_len = 0;
      write_00286 = cgc_append_buf(write_00286, &write_00286_len, write_00286_00000, write_00286_00000_len);
      if (write_00286_len > 0) {
         cgc_transmit_all(1, write_00286, write_00286_len);
      }
      cgc_free(write_00286);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00287_00000[] = 
         "\x4f\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00095_ptr += cgc_data_match(read_00095 + read_00095_ptr, read_00095_len - read_00095_ptr, match_00095_00000, 20);
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00288_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00289_00000[] = 
         "\x71\x6f\x56\x5a\x34\x6e\x79\x4d\x34\x07";
      static unsigned int write_00289_00000_len = 10;
      unsigned char *write_00289 = NULL;
      unsigned int write_00289_len = 0;
      write_00289 = cgc_append_buf(write_00289, &write_00289_len, write_00289_00000, write_00289_00000_len);
      if (write_00289_len > 0) {
         cgc_transmit_all(1, write_00289, write_00289_len);
      }
      cgc_free(write_00289);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00290_00000[] = 
         "\xa2\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00096_ptr += cgc_data_match(read_00096 + read_00096_ptr, read_00096_len - read_00096_ptr, match_00096_00000, 20);
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00291_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00291_00000_len = 4;
      unsigned char *write_00291 = NULL;
      unsigned int write_00291_len = 0;
      write_00291 = cgc_append_buf(write_00291, &write_00291_len, write_00291_00000, write_00291_00000_len);
      if (write_00291_len > 0) {
         cgc_transmit_all(1, write_00291, write_00291_len);
      }
      cgc_free(write_00291);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00292_00000[] = 
         "\x68\x67\x54\x34\x6c\x54\x4c\x58\x57\x07";
      static unsigned int write_00292_00000_len = 10;
      unsigned char *write_00292 = NULL;
      unsigned int write_00292_len = 0;
      write_00292 = cgc_append_buf(write_00292, &write_00292_len, write_00292_00000, write_00292_00000_len);
      if (write_00292_len > 0) {
         cgc_transmit_all(1, write_00292, write_00292_len);
      }
      cgc_free(write_00292);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00293_00000[] = 
         "\x80\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00097_ptr += cgc_data_match(read_00097 + read_00097_ptr, read_00097_len - read_00097_ptr, match_00097_00000, 20);
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00294_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00295_00000[] = 
         "\x6e\x65\x74\x76\x69\x72\x55\x32\x4f\x07";
      static unsigned int write_00295_00000_len = 10;
      unsigned char *write_00295 = NULL;
      unsigned int write_00295_len = 0;
      write_00295 = cgc_append_buf(write_00295, &write_00295_len, write_00295_00000, write_00295_00000_len);
      if (write_00295_len > 0) {
         cgc_transmit_all(1, write_00295, write_00295_len);
      }
      cgc_free(write_00295);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00296_00000[] = 
         "\xe5\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00098_ptr += cgc_data_match(read_00098 + read_00098_ptr, read_00098_len - read_00098_ptr, match_00098_00000, 20);
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00297_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00298_00000[] = 
         "\x58\x70\x43\x58\x69\x43\x38\x33\x70\x07";
      static unsigned int write_00298_00000_len = 10;
      unsigned char *write_00298 = NULL;
      unsigned int write_00298_len = 0;
      write_00298 = cgc_append_buf(write_00298, &write_00298_len, write_00298_00000, write_00298_00000_len);
      if (write_00298_len > 0) {
         cgc_transmit_all(1, write_00298, write_00298_len);
      }
      cgc_free(write_00298);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00299_00000[] = 
         "\x62\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00099_ptr += cgc_data_match(read_00099 + read_00099_ptr, read_00099_len - read_00099_ptr, match_00099_00000, 20);
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00300_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00301_00000[] = 
         "\x44\x4c\x31\x73\x4c\x31\x43\x4e\x4a\x07";
      static unsigned int write_00301_00000_len = 10;
      unsigned char *write_00301 = NULL;
      unsigned int write_00301_len = 0;
      write_00301 = cgc_append_buf(write_00301, &write_00301_len, write_00301_00000, write_00301_00000_len);
      if (write_00301_len > 0) {
         cgc_transmit_all(1, write_00301, write_00301_len);
      }
      cgc_free(write_00301);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00302_00000[] = 
         "\x21\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00100_ptr += cgc_data_match(read_00100 + read_00100_ptr, read_00100_len - read_00100_ptr, match_00100_00000, 20);
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00303_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00304_00000[] = 
         "\x50\x45\x6c\x6f\x55\x4c\x44\x6a\x79\x07";
      static unsigned int write_00304_00000_len = 10;
      unsigned char *write_00304 = NULL;
      unsigned int write_00304_len = 0;
      write_00304 = cgc_append_buf(write_00304, &write_00304_len, write_00304_00000, write_00304_00000_len);
      if (write_00304_len > 0) {
         cgc_transmit_all(1, write_00304, write_00304_len);
      }
      cgc_free(write_00304);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00305_00000[] = 
         "\x4c\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00101_ptr += cgc_data_match(read_00101 + read_00101_ptr, read_00101_len - read_00101_ptr, match_00101_00000, 20);
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00306_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00307_00000[] = 
         "\x4f\x62\x73\x57\x43\x72\x6f\x78\x54\x07";
      static unsigned int write_00307_00000_len = 10;
      unsigned char *write_00307 = NULL;
      unsigned int write_00307_len = 0;
      write_00307 = cgc_append_buf(write_00307, &write_00307_len, write_00307_00000, write_00307_00000_len);
      if (write_00307_len > 0) {
         cgc_transmit_all(1, write_00307, write_00307_len);
      }
      cgc_free(write_00307);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00308_00000[] = 
         "\x0d\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00102_ptr += cgc_data_match(read_00102 + read_00102_ptr, read_00102_len - read_00102_ptr, match_00102_00000, 20);
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00309_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00310_00000[] = 
         "\x51\x6e\x54\x73\x6f\x4b\x63\x76\x4f\x07";
      static unsigned int write_00310_00000_len = 10;
      unsigned char *write_00310 = NULL;
      unsigned int write_00310_len = 0;
      write_00310 = cgc_append_buf(write_00310, &write_00310_len, write_00310_00000, write_00310_00000_len);
      if (write_00310_len > 0) {
         cgc_transmit_all(1, write_00310, write_00310_len);
      }
      cgc_free(write_00310);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00311_00000[] = 
         "\xd8\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00103_ptr += cgc_data_match(read_00103 + read_00103_ptr, read_00103_len - read_00103_ptr, match_00103_00000, 20);
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00312_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00313_00000[] = 
         "\x4d\x5a\x4f\x68\x64\x39\x59\x77\x54\x07";
      static unsigned int write_00313_00000_len = 10;
      unsigned char *write_00313 = NULL;
      unsigned int write_00313_len = 0;
      write_00313 = cgc_append_buf(write_00313, &write_00313_len, write_00313_00000, write_00313_00000_len);
      if (write_00313_len > 0) {
         cgc_transmit_all(1, write_00313, write_00313_len);
      }
      cgc_free(write_00313);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00314_00000[] = 
         "\x7d\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00104_ptr += cgc_data_match(read_00104 + read_00104_ptr, read_00104_len - read_00104_ptr, match_00104_00000, 20);
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00315_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00316_00000[] = 
         "\x37\x45\x79\x70\x41\x62\x33\x74\x61\x07";
      static unsigned int write_00316_00000_len = 10;
      unsigned char *write_00316 = NULL;
      unsigned int write_00316_len = 0;
      write_00316 = cgc_append_buf(write_00316, &write_00316_len, write_00316_00000, write_00316_00000_len);
      if (write_00316_len > 0) {
         cgc_transmit_all(1, write_00316, write_00316_len);
      }
      cgc_free(write_00316);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00317_00000[] = 
         "\x7c\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00105_ptr += cgc_data_match(read_00105 + read_00105_ptr, read_00105_len - read_00105_ptr, match_00105_00000, 20);
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00318_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00319_00000[] = 
         "\x71\x69\x51\x76\x6c\x34\x57\x78\x6e\x07";
      static unsigned int write_00319_00000_len = 10;
      unsigned char *write_00319 = NULL;
      unsigned int write_00319_len = 0;
      write_00319 = cgc_append_buf(write_00319, &write_00319_len, write_00319_00000, write_00319_00000_len);
      if (write_00319_len > 0) {
         cgc_transmit_all(1, write_00319, write_00319_len);
      }
      cgc_free(write_00319);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00320_00000[] = 
         "\x52\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00106_ptr += cgc_data_match(read_00106 + read_00106_ptr, read_00106_len - read_00106_ptr, match_00106_00000, 20);
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00321_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00322_00000[] = 
         "\x4f\x44\x6b\x61\x56\x32\x56\x53\x50\x07";
      static unsigned int write_00322_00000_len = 10;
      unsigned char *write_00322 = NULL;
      unsigned int write_00322_len = 0;
      write_00322 = cgc_append_buf(write_00322, &write_00322_len, write_00322_00000, write_00322_00000_len);
      if (write_00322_len > 0) {
         cgc_transmit_all(1, write_00322, write_00322_len);
      }
      cgc_free(write_00322);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00323_00000[] = 
         "\xa4\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00107_ptr += cgc_data_match(read_00107 + read_00107_ptr, read_00107_len - read_00107_ptr, match_00107_00000, 20);
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00324_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00325_00000[] = 
         "\x59\x6b\x4d\x4f\x47\x5a\x7a\x73\x41\x07";
      static unsigned int write_00325_00000_len = 10;
      unsigned char *write_00325 = NULL;
      unsigned int write_00325_len = 0;
      write_00325 = cgc_append_buf(write_00325, &write_00325_len, write_00325_00000, write_00325_00000_len);
      if (write_00325_len > 0) {
         cgc_transmit_all(1, write_00325, write_00325_len);
      }
      cgc_free(write_00325);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00326_00000[] = 
         "\xdf\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00108_ptr += cgc_data_match(read_00108 + read_00108_ptr, read_00108_len - read_00108_ptr, match_00108_00000, 20);
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00327_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00328_00000[] = 
         "\x69\x4c\x41\x41\x39\x38\x4c\x71\x6c\x07";
      static unsigned int write_00328_00000_len = 10;
      unsigned char *write_00328 = NULL;
      unsigned int write_00328_len = 0;
      write_00328 = cgc_append_buf(write_00328, &write_00328_len, write_00328_00000, write_00328_00000_len);
      if (write_00328_len > 0) {
         cgc_transmit_all(1, write_00328, write_00328_len);
      }
      cgc_free(write_00328);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00329_00000[] = 
         "\x42\x03\x00\x00";
      static unsigned int write_00329_00000_len = 4;
      unsigned char *write_00329 = NULL;
      unsigned int write_00329_len = 0;
      write_00329 = cgc_append_buf(write_00329, &write_00329_len, write_00329_00000, write_00329_00000_len);
      if (write_00329_len > 0) {
         cgc_transmit_all(1, write_00329, write_00329_len);
      }
      cgc_free(write_00329);
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00109_ptr += cgc_data_match(read_00109 + read_00109_ptr, read_00109_len - read_00109_ptr, match_00109_00000, 20);
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00330_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00331_00000[] = 
         "\x57\x56\x52\x6a\x30\x75\x4d\x78\x5a\x07";
      static unsigned int write_00331_00000_len = 10;
      unsigned char *write_00331 = NULL;
      unsigned int write_00331_len = 0;
      write_00331 = cgc_append_buf(write_00331, &write_00331_len, write_00331_00000, write_00331_00000_len);
      if (write_00331_len > 0) {
         cgc_transmit_all(1, write_00331, write_00331_len);
      }
      cgc_free(write_00331);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00332_00000[] = 
         "\x60\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00110_ptr += cgc_data_match(read_00110 + read_00110_ptr, read_00110_len - read_00110_ptr, match_00110_00000, 20);
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00333_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00333_00000_len = 4;
      unsigned char *write_00333 = NULL;
      unsigned int write_00333_len = 0;
      write_00333 = cgc_append_buf(write_00333, &write_00333_len, write_00333_00000, write_00333_00000_len);
      if (write_00333_len > 0) {
         cgc_transmit_all(1, write_00333, write_00333_len);
      }
      cgc_free(write_00333);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00334_00000[] = 
         "\x61\x56\x4a\x4e\x41\x66\x36\x5a\x68\x07";
      static unsigned int write_00334_00000_len = 10;
      unsigned char *write_00334 = NULL;
      unsigned int write_00334_len = 0;
      write_00334 = cgc_append_buf(write_00334, &write_00334_len, write_00334_00000, write_00334_00000_len);
      if (write_00334_len > 0) {
         cgc_transmit_all(1, write_00334, write_00334_len);
      }
      cgc_free(write_00334);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00335_00000[] = 
         "\xe6\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00111_ptr += cgc_data_match(read_00111 + read_00111_ptr, read_00111_len - read_00111_ptr, match_00111_00000, 20);
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00336_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00337_00000[] = 
         "\x35\x52\x38\x41\x31\x74\x77\x7a\x6e\x07";
      static unsigned int write_00337_00000_len = 10;
      unsigned char *write_00337 = NULL;
      unsigned int write_00337_len = 0;
      write_00337 = cgc_append_buf(write_00337, &write_00337_len, write_00337_00000, write_00337_00000_len);
      if (write_00337_len > 0) {
         cgc_transmit_all(1, write_00337, write_00337_len);
      }
      cgc_free(write_00337);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00338_00000[] = 
         "\x34\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00112_ptr += cgc_data_match(read_00112 + read_00112_ptr, read_00112_len - read_00112_ptr, match_00112_00000, 20);
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00339_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00339_00000_len = 4;
      unsigned char *write_00339 = NULL;
      unsigned int write_00339_len = 0;
      write_00339 = cgc_append_buf(write_00339, &write_00339_len, write_00339_00000, write_00339_00000_len);
      if (write_00339_len > 0) {
         cgc_transmit_all(1, write_00339, write_00339_len);
      }
      cgc_free(write_00339);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00340_00000[] = 
         "\x33\x62\x4f\x73\x47\x41\x35\x44\x4a\x07";
      static unsigned int write_00340_00000_len = 10;
      unsigned char *write_00340 = NULL;
      unsigned int write_00340_len = 0;
      write_00340 = cgc_append_buf(write_00340, &write_00340_len, write_00340_00000, write_00340_00000_len);
      if (write_00340_len > 0) {
         cgc_transmit_all(1, write_00340, write_00340_len);
      }
      cgc_free(write_00340);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00341_00000[] = 
         "\x09\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00113_ptr += cgc_data_match(read_00113 + read_00113_ptr, read_00113_len - read_00113_ptr, match_00113_00000, 20);
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00342_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00342_00000_len = 4;
      unsigned char *write_00342 = NULL;
      unsigned int write_00342_len = 0;
      write_00342 = cgc_append_buf(write_00342, &write_00342_len, write_00342_00000, write_00342_00000_len);
      if (write_00342_len > 0) {
         cgc_transmit_all(1, write_00342, write_00342_len);
      }
      cgc_free(write_00342);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00343_00000[] = 
         "\x4b\x4b\x4f\x50\x41\x5a\x53\x58\x63\x07";
      static unsigned int write_00343_00000_len = 10;
      unsigned char *write_00343 = NULL;
      unsigned int write_00343_len = 0;
      write_00343 = cgc_append_buf(write_00343, &write_00343_len, write_00343_00000, write_00343_00000_len);
      if (write_00343_len > 0) {
         cgc_transmit_all(1, write_00343, write_00343_len);
      }
      cgc_free(write_00343);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00344_00000[] = 
         "\x87\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00114_ptr += cgc_data_match(read_00114 + read_00114_ptr, read_00114_len - read_00114_ptr, match_00114_00000, 20);
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00345_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00345_00000_len = 4;
      unsigned char *write_00345 = NULL;
      unsigned int write_00345_len = 0;
      write_00345 = cgc_append_buf(write_00345, &write_00345_len, write_00345_00000, write_00345_00000_len);
      if (write_00345_len > 0) {
         cgc_transmit_all(1, write_00345, write_00345_len);
      }
      cgc_free(write_00345);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00346_00000[] = 
         "\x4c\x6f\x7a\x70\x6d\x5a\x59\x48\x6a\x07";
      static unsigned int write_00346_00000_len = 10;
      unsigned char *write_00346 = NULL;
      unsigned int write_00346_len = 0;
      write_00346 = cgc_append_buf(write_00346, &write_00346_len, write_00346_00000, write_00346_00000_len);
      if (write_00346_len > 0) {
         cgc_transmit_all(1, write_00346, write_00346_len);
      }
      cgc_free(write_00346);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00347_00000[] = 
         "\x2a\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00115_ptr += cgc_data_match(read_00115 + read_00115_ptr, read_00115_len - read_00115_ptr, match_00115_00000, 20);
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00348_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00349_00000[] = 
         "\x4a\x64\x57\x77\x75\x55\x54\x36\x50\x07";
      static unsigned int write_00349_00000_len = 10;
      unsigned char *write_00349 = NULL;
      unsigned int write_00349_len = 0;
      write_00349 = cgc_append_buf(write_00349, &write_00349_len, write_00349_00000, write_00349_00000_len);
      if (write_00349_len > 0) {
         cgc_transmit_all(1, write_00349, write_00349_len);
      }
      cgc_free(write_00349);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00350_00000[] = 
         "\x71\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00116_ptr += cgc_data_match(read_00116 + read_00116_ptr, read_00116_len - read_00116_ptr, match_00116_00000, 20);
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00351_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00352_00000[] = 
         "\x49\x71\x31\x4f\x31\x7a\x4a\x30\x4e\x07";
      static unsigned int write_00352_00000_len = 10;
      unsigned char *write_00352 = NULL;
      unsigned int write_00352_len = 0;
      write_00352 = cgc_append_buf(write_00352, &write_00352_len, write_00352_00000, write_00352_00000_len);
      if (write_00352_len > 0) {
         cgc_transmit_all(1, write_00352, write_00352_len);
      }
      cgc_free(write_00352);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00353_00000[] = 
         "\x49\x01\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00117_ptr += cgc_data_match(read_00117 + read_00117_ptr, read_00117_len - read_00117_ptr, match_00117_00000, 20);
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00354_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00355_00000[] = 
         "\x43\x37\x75\x74\x4e\x78\x70\x53\x63\x07";
      static unsigned int write_00355_00000_len = 10;
      unsigned char *write_00355 = NULL;
      unsigned int write_00355_len = 0;
      write_00355 = cgc_append_buf(write_00355, &write_00355_len, write_00355_00000, write_00355_00000_len);
      if (write_00355_len > 0) {
         cgc_transmit_all(1, write_00355, write_00355_len);
      }
      cgc_free(write_00355);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00356_00000[] = 
         "\xca\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00118_ptr += cgc_data_match(read_00118 + read_00118_ptr, read_00118_len - read_00118_ptr, match_00118_00000, 20);
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00357_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00358_00000[] = 
         "\x45\x72\x6e\x56\x4b\x58\x30\x39\x38\x07";
      static unsigned int write_00358_00000_len = 10;
      unsigned char *write_00358 = NULL;
      unsigned int write_00358_len = 0;
      write_00358 = cgc_append_buf(write_00358, &write_00358_len, write_00358_00000, write_00358_00000_len);
      if (write_00358_len > 0) {
         cgc_transmit_all(1, write_00358, write_00358_len);
      }
      cgc_free(write_00358);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00359_00000[] = 
         "\x95\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00119_ptr += cgc_data_match(read_00119 + read_00119_ptr, read_00119_len - read_00119_ptr, match_00119_00000, 20);
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00360_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00361_00000[] = 
         "\x52\x64\x66\x30\x75\x68\x6e\x4d\x32\x07";
      static unsigned int write_00361_00000_len = 10;
      unsigned char *write_00361 = NULL;
      unsigned int write_00361_len = 0;
      write_00361 = cgc_append_buf(write_00361, &write_00361_len, write_00361_00000, write_00361_00000_len);
      if (write_00361_len > 0) {
         cgc_transmit_all(1, write_00361, write_00361_len);
      }
      cgc_free(write_00361);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00362_00000[] = 
         "\x98\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00120_ptr += cgc_data_match(read_00120 + read_00120_ptr, read_00120_len - read_00120_ptr, match_00120_00000, 20);
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00363_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00364_00000[] = 
         "\x6e\x78\x36\x71\x71\x42\x64\x67\x77\x07";
      static unsigned int write_00364_00000_len = 10;
      unsigned char *write_00364 = NULL;
      unsigned int write_00364_len = 0;
      write_00364 = cgc_append_buf(write_00364, &write_00364_len, write_00364_00000, write_00364_00000_len);
      if (write_00364_len > 0) {
         cgc_transmit_all(1, write_00364, write_00364_len);
      }
      cgc_free(write_00364);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00365_00000[] = 
         "\x23\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00121_ptr += cgc_data_match(read_00121 + read_00121_ptr, read_00121_len - read_00121_ptr, match_00121_00000, 20);
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00366_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00367_00000[] = 
         "\x4b\x6d\x69\x6b\x33\x4e\x6d\x4d\x65\x07";
      static unsigned int write_00367_00000_len = 10;
      unsigned char *write_00367 = NULL;
      unsigned int write_00367_len = 0;
      write_00367 = cgc_append_buf(write_00367, &write_00367_len, write_00367_00000, write_00367_00000_len);
      if (write_00367_len > 0) {
         cgc_transmit_all(1, write_00367, write_00367_len);
      }
      cgc_free(write_00367);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00368_00000[] = 
         "\xa6\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00122_ptr += cgc_data_match(read_00122 + read_00122_ptr, read_00122_len - read_00122_ptr, match_00122_00000, 20);
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00369_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00370_00000[] = 
         "\x44\x6a\x70\x6b\x71\x5a\x74\x74\x4b\x07";
      static unsigned int write_00370_00000_len = 10;
      unsigned char *write_00370 = NULL;
      unsigned int write_00370_len = 0;
      write_00370 = cgc_append_buf(write_00370, &write_00370_len, write_00370_00000, write_00370_00000_len);
      if (write_00370_len > 0) {
         cgc_transmit_all(1, write_00370, write_00370_len);
      }
      cgc_free(write_00370);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00371_00000[] = 
         "\x40\x03\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00123_ptr += cgc_data_match(read_00123 + read_00123_ptr, read_00123_len - read_00123_ptr, match_00123_00000, 20);
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00372_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00372_00000_len = 4;
      unsigned char *write_00372 = NULL;
      unsigned int write_00372_len = 0;
      write_00372 = cgc_append_buf(write_00372, &write_00372_len, write_00372_00000, write_00372_00000_len);
      if (write_00372_len > 0) {
         cgc_transmit_all(1, write_00372, write_00372_len);
      }
      cgc_free(write_00372);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00373_00000[] = 
         "\x45\x65\x43\x4f\x6c\x41\x49\x77\x7a\x07";
      static unsigned int write_00373_00000_len = 10;
      unsigned char *write_00373 = NULL;
      unsigned int write_00373_len = 0;
      write_00373 = cgc_append_buf(write_00373, &write_00373_len, write_00373_00000, write_00373_00000_len);
      if (write_00373_len > 0) {
         cgc_transmit_all(1, write_00373, write_00373_len);
      }
      cgc_free(write_00373);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00374_00000[] = 
         "\xc3\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00124_ptr += cgc_data_match(read_00124 + read_00124_ptr, read_00124_len - read_00124_ptr, match_00124_00000, 20);
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00375_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00376_00000[] = 
         "\x41\x42\x5a\x69\x70\x48\x32\x68\x4a\x07";
      static unsigned int write_00376_00000_len = 10;
      unsigned char *write_00376 = NULL;
      unsigned int write_00376_len = 0;
      write_00376 = cgc_append_buf(write_00376, &write_00376_len, write_00376_00000, write_00376_00000_len);
      if (write_00376_len > 0) {
         cgc_transmit_all(1, write_00376, write_00376_len);
      }
      cgc_free(write_00376);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00377_00000[] = 
         "\xb7\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00125_ptr += cgc_data_match(read_00125 + read_00125_ptr, read_00125_len - read_00125_ptr, match_00125_00000, 20);
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00378_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00379_00000[] = 
         "\x53\x6e\x41\x32\x79\x58\x30\x65\x63\x07";
      static unsigned int write_00379_00000_len = 10;
      unsigned char *write_00379 = NULL;
      unsigned int write_00379_len = 0;
      write_00379 = cgc_append_buf(write_00379, &write_00379_len, write_00379_00000, write_00379_00000_len);
      if (write_00379_len > 0) {
         cgc_transmit_all(1, write_00379, write_00379_len);
      }
      cgc_free(write_00379);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00380_00000[] = 
         "\xcf\x02\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00126_ptr += cgc_data_match(read_00126 + read_00126_ptr, read_00126_len - read_00126_ptr, match_00126_00000, 20);
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00381_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00382_00000[] = 
         "\x78\x32\x77\x37\x48\x30\x4a\x6e\x51\x07";
      static unsigned int write_00382_00000_len = 10;
      unsigned char *write_00382 = NULL;
      unsigned int write_00382_len = 0;
      write_00382 = cgc_append_buf(write_00382, &write_00382_len, write_00382_00000, write_00382_00000_len);
      if (write_00382_len > 0) {
         cgc_transmit_all(1, write_00382, write_00382_len);
      }
      cgc_free(write_00382);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00383_00000[] = 
         "\x79\x00\x00\x00";
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
         "\x4e\x65\x77\x20\x62\x75\x64\x67\x65\x74\x20\x63\x72\x65\x61\x74"
         "\x65\x64\x21\x0a";
      read_00127_ptr += cgc_data_match(read_00127 + read_00127_ptr, read_00127_len - read_00127_ptr, match_00127_00000, 20);
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00384_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00385_00000[] = 
         "\x67\x63\x78\x74\x30\x51\x77\x47\x4b\x07";
      static unsigned int write_00385_00000_len = 10;
      unsigned char *write_00385 = NULL;
      unsigned int write_00385_len = 0;
      write_00385 = cgc_append_buf(write_00385, &write_00385_len, write_00385_00000, write_00385_00000_len);
      if (write_00385_len > 0) {
         cgc_transmit_all(1, write_00385, write_00385_len);
      }
      cgc_free(write_00385);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00386_00000[] = 
         "\x9a\x01\x00\x00";
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00128_ptr += cgc_data_match(read_00128 + read_00128_ptr, read_00128_len - read_00128_ptr, match_00128_00000, 16);
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00387_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00388_00000[] = 
         "\x70\x39\x4d\x59\x35\x6c\x58\x4c\x6b\x07";
      static unsigned int write_00388_00000_len = 10;
      unsigned char *write_00388 = NULL;
      unsigned int write_00388_len = 0;
      write_00388 = cgc_append_buf(write_00388, &write_00388_len, write_00388_00000, write_00388_00000_len);
      if (write_00388_len > 0) {
         cgc_transmit_all(1, write_00388, write_00388_len);
      }
      cgc_free(write_00388);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00389_00000[] = 
         "\x5e\x01\x00\x00";
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00129_ptr += cgc_data_match(read_00129 + read_00129_ptr, read_00129_len - read_00129_ptr, match_00129_00000, 16);
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00390_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00391_00000[] = 
         "\x72\x30\x77\x63\x76\x49\x45\x6c\x4f\x07";
      static unsigned int write_00391_00000_len = 10;
      unsigned char *write_00391 = NULL;
      unsigned int write_00391_len = 0;
      write_00391 = cgc_append_buf(write_00391, &write_00391_len, write_00391_00000, write_00391_00000_len);
      if (write_00391_len > 0) {
         cgc_transmit_all(1, write_00391, write_00391_len);
      }
      cgc_free(write_00391);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00392_00000[] = 
         "\xa7\x00\x00\x00";
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00130_ptr += cgc_data_match(read_00130 + read_00130_ptr, read_00130_len - read_00130_ptr, match_00130_00000, 16);
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00393_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00394_00000[] = 
         "\x4d\x49\x72\x7a\x30\x63\x54\x39\x36\x07";
      static unsigned int write_00394_00000_len = 10;
      unsigned char *write_00394 = NULL;
      unsigned int write_00394_len = 0;
      write_00394 = cgc_append_buf(write_00394, &write_00394_len, write_00394_00000, write_00394_00000_len);
      if (write_00394_len > 0) {
         cgc_transmit_all(1, write_00394, write_00394_len);
      }
      cgc_free(write_00394);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00395_00000[] = 
         "\x2a\x00\x00\x00";
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00131_ptr += cgc_data_match(read_00131 + read_00131_ptr, read_00131_len - read_00131_ptr, match_00131_00000, 16);
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00396_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00397_00000[] = 
         "\x30\x56\x37\x47\x66\x38\x6e\x63\x59\x07";
      static unsigned int write_00397_00000_len = 10;
      unsigned char *write_00397 = NULL;
      unsigned int write_00397_len = 0;
      write_00397 = cgc_append_buf(write_00397, &write_00397_len, write_00397_00000, write_00397_00000_len);
      if (write_00397_len > 0) {
         cgc_transmit_all(1, write_00397, write_00397_len);
      }
      cgc_free(write_00397);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00398_00000[] = 
         "\x16\x01\x00\x00";
      static unsigned int write_00398_00000_len = 4;
      unsigned char *write_00398 = NULL;
      unsigned int write_00398_len = 0;
      write_00398 = cgc_append_buf(write_00398, &write_00398_len, write_00398_00000, write_00398_00000_len);
      if (write_00398_len > 0) {
         cgc_transmit_all(1, write_00398, write_00398_len);
      }
      cgc_free(write_00398);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00132_ptr += cgc_data_match(read_00132 + read_00132_ptr, read_00132_len - read_00132_ptr, match_00132_00000, 16);
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00399_00000[] = 
         "\x01\x00\x00\x00";
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
      //*** writing data
      static unsigned char write_00400_00000[] = 
         "\x4e\x6f\x78\x43\x46\x79\x45\x4c\x54\x07";
      static unsigned int write_00400_00000_len = 10;
      unsigned char *write_00400 = NULL;
      unsigned int write_00400_len = 0;
      write_00400 = cgc_append_buf(write_00400, &write_00400_len, write_00400_00000, write_00400_00000_len);
      if (write_00400_len > 0) {
         cgc_transmit_all(1, write_00400, write_00400_len);
      }
      cgc_free(write_00400);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00401_00000[] = 
         "\xb0\x03\x00\x00";
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00133_ptr += cgc_data_match(read_00133 + read_00133_ptr, read_00133_len - read_00133_ptr, match_00133_00000, 16);
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00402_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00402_00000_len = 4;
      unsigned char *write_00402 = NULL;
      unsigned int write_00402_len = 0;
      write_00402 = cgc_append_buf(write_00402, &write_00402_len, write_00402_00000, write_00402_00000_len);
      if (write_00402_len > 0) {
         cgc_transmit_all(1, write_00402, write_00402_len);
      }
      cgc_free(write_00402);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00403_00000[] = 
         "\x51\x6b\x5a\x67\x42\x32\x44\x39\x68\x07";
      static unsigned int write_00403_00000_len = 10;
      unsigned char *write_00403 = NULL;
      unsigned int write_00403_len = 0;
      write_00403 = cgc_append_buf(write_00403, &write_00403_len, write_00403_00000, write_00403_00000_len);
      if (write_00403_len > 0) {
         cgc_transmit_all(1, write_00403, write_00403_len);
      }
      cgc_free(write_00403);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00404_00000[] = 
         "\xdc\x02\x00\x00";
      static unsigned int write_00404_00000_len = 4;
      unsigned char *write_00404 = NULL;
      unsigned int write_00404_len = 0;
      write_00404 = cgc_append_buf(write_00404, &write_00404_len, write_00404_00000, write_00404_00000_len);
      if (write_00404_len > 0) {
         cgc_transmit_all(1, write_00404, write_00404_len);
      }
      cgc_free(write_00404);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00134_ptr += cgc_data_match(read_00134 + read_00134_ptr, read_00134_len - read_00134_ptr, match_00134_00000, 16);
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00405_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00405_00000_len = 4;
      unsigned char *write_00405 = NULL;
      unsigned int write_00405_len = 0;
      write_00405 = cgc_append_buf(write_00405, &write_00405_len, write_00405_00000, write_00405_00000_len);
      if (write_00405_len > 0) {
         cgc_transmit_all(1, write_00405, write_00405_len);
      }
      cgc_free(write_00405);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00406_00000[] = 
         "\x52\x54\x63\x74\x4b\x51\x63\x47\x72\x07";
      static unsigned int write_00406_00000_len = 10;
      unsigned char *write_00406 = NULL;
      unsigned int write_00406_len = 0;
      write_00406 = cgc_append_buf(write_00406, &write_00406_len, write_00406_00000, write_00406_00000_len);
      if (write_00406_len > 0) {
         cgc_transmit_all(1, write_00406, write_00406_len);
      }
      cgc_free(write_00406);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00407_00000[] = 
         "\x05\x00\x00\x00";
      static unsigned int write_00407_00000_len = 4;
      unsigned char *write_00407 = NULL;
      unsigned int write_00407_len = 0;
      write_00407 = cgc_append_buf(write_00407, &write_00407_len, write_00407_00000, write_00407_00000_len);
      if (write_00407_len > 0) {
         cgc_transmit_all(1, write_00407, write_00407_len);
      }
      cgc_free(write_00407);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00135_ptr += cgc_data_match(read_00135 + read_00135_ptr, read_00135_len - read_00135_ptr, match_00135_00000, 16);
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00408_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00408_00000_len = 4;
      unsigned char *write_00408 = NULL;
      unsigned int write_00408_len = 0;
      write_00408 = cgc_append_buf(write_00408, &write_00408_len, write_00408_00000, write_00408_00000_len);
      if (write_00408_len > 0) {
         cgc_transmit_all(1, write_00408, write_00408_len);
      }
      cgc_free(write_00408);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00409_00000[] = 
         "\x37\x4b\x59\x43\x73\x78\x56\x46\x5a\x07";
      static unsigned int write_00409_00000_len = 10;
      unsigned char *write_00409 = NULL;
      unsigned int write_00409_len = 0;
      write_00409 = cgc_append_buf(write_00409, &write_00409_len, write_00409_00000, write_00409_00000_len);
      if (write_00409_len > 0) {
         cgc_transmit_all(1, write_00409, write_00409_len);
      }
      cgc_free(write_00409);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00410_00000[] = 
         "\xfa\x02\x00\x00";
      static unsigned int write_00410_00000_len = 4;
      unsigned char *write_00410 = NULL;
      unsigned int write_00410_len = 0;
      write_00410 = cgc_append_buf(write_00410, &write_00410_len, write_00410_00000, write_00410_00000_len);
      if (write_00410_len > 0) {
         cgc_transmit_all(1, write_00410, write_00410_len);
      }
      cgc_free(write_00410);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00136_ptr += cgc_data_match(read_00136 + read_00136_ptr, read_00136_len - read_00136_ptr, match_00136_00000, 16);
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00411_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00411_00000_len = 4;
      unsigned char *write_00411 = NULL;
      unsigned int write_00411_len = 0;
      write_00411 = cgc_append_buf(write_00411, &write_00411_len, write_00411_00000, write_00411_00000_len);
      if (write_00411_len > 0) {
         cgc_transmit_all(1, write_00411, write_00411_len);
      }
      cgc_free(write_00411);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00412_00000[] = 
         "\x74\x42\x6f\x73\x32\x63\x79\x4a\x61\x07";
      static unsigned int write_00412_00000_len = 10;
      unsigned char *write_00412 = NULL;
      unsigned int write_00412_len = 0;
      write_00412 = cgc_append_buf(write_00412, &write_00412_len, write_00412_00000, write_00412_00000_len);
      if (write_00412_len > 0) {
         cgc_transmit_all(1, write_00412, write_00412_len);
      }
      cgc_free(write_00412);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00413_00000[] = 
         "\xb3\x00\x00\x00";
      static unsigned int write_00413_00000_len = 4;
      unsigned char *write_00413 = NULL;
      unsigned int write_00413_len = 0;
      write_00413 = cgc_append_buf(write_00413, &write_00413_len, write_00413_00000, write_00413_00000_len);
      if (write_00413_len > 0) {
         cgc_transmit_all(1, write_00413, write_00413_len);
      }
      cgc_free(write_00413);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00137_ptr += cgc_data_match(read_00137 + read_00137_ptr, read_00137_len - read_00137_ptr, match_00137_00000, 16);
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00414_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00414_00000_len = 4;
      unsigned char *write_00414 = NULL;
      unsigned int write_00414_len = 0;
      write_00414 = cgc_append_buf(write_00414, &write_00414_len, write_00414_00000, write_00414_00000_len);
      if (write_00414_len > 0) {
         cgc_transmit_all(1, write_00414, write_00414_len);
      }
      cgc_free(write_00414);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00415_00000[] = 
         "\x4c\x31\x77\x76\x34\x75\x72\x45\x30\x07";
      static unsigned int write_00415_00000_len = 10;
      unsigned char *write_00415 = NULL;
      unsigned int write_00415_len = 0;
      write_00415 = cgc_append_buf(write_00415, &write_00415_len, write_00415_00000, write_00415_00000_len);
      if (write_00415_len > 0) {
         cgc_transmit_all(1, write_00415, write_00415_len);
      }
      cgc_free(write_00415);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00416_00000[] = 
         "\xd9\x00\x00\x00";
      static unsigned int write_00416_00000_len = 4;
      unsigned char *write_00416 = NULL;
      unsigned int write_00416_len = 0;
      write_00416 = cgc_append_buf(write_00416, &write_00416_len, write_00416_00000, write_00416_00000_len);
      if (write_00416_len > 0) {
         cgc_transmit_all(1, write_00416, write_00416_len);
      }
      cgc_free(write_00416);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00138_ptr += cgc_data_match(read_00138 + read_00138_ptr, read_00138_len - read_00138_ptr, match_00138_00000, 16);
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00417_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00417_00000_len = 4;
      unsigned char *write_00417 = NULL;
      unsigned int write_00417_len = 0;
      write_00417 = cgc_append_buf(write_00417, &write_00417_len, write_00417_00000, write_00417_00000_len);
      if (write_00417_len > 0) {
         cgc_transmit_all(1, write_00417, write_00417_len);
      }
      cgc_free(write_00417);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00418_00000[] = 
         "\x71\x73\x54\x4b\x54\x54\x44\x53\x53\x07";
      static unsigned int write_00418_00000_len = 10;
      unsigned char *write_00418 = NULL;
      unsigned int write_00418_len = 0;
      write_00418 = cgc_append_buf(write_00418, &write_00418_len, write_00418_00000, write_00418_00000_len);
      if (write_00418_len > 0) {
         cgc_transmit_all(1, write_00418, write_00418_len);
      }
      cgc_free(write_00418);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00419_00000[] = 
         "\x39\x03\x00\x00";
      static unsigned int write_00419_00000_len = 4;
      unsigned char *write_00419 = NULL;
      unsigned int write_00419_len = 0;
      write_00419 = cgc_append_buf(write_00419, &write_00419_len, write_00419_00000, write_00419_00000_len);
      if (write_00419_len > 0) {
         cgc_transmit_all(1, write_00419, write_00419_len);
      }
      cgc_free(write_00419);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00139_ptr += cgc_data_match(read_00139 + read_00139_ptr, read_00139_len - read_00139_ptr, match_00139_00000, 16);
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00420_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00420_00000_len = 4;
      unsigned char *write_00420 = NULL;
      unsigned int write_00420_len = 0;
      write_00420 = cgc_append_buf(write_00420, &write_00420_len, write_00420_00000, write_00420_00000_len);
      if (write_00420_len > 0) {
         cgc_transmit_all(1, write_00420, write_00420_len);
      }
      cgc_free(write_00420);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00421_00000[] = 
         "\x53\x39\x6b\x51\x39\x39\x45\x6b\x4b\x07";
      static unsigned int write_00421_00000_len = 10;
      unsigned char *write_00421 = NULL;
      unsigned int write_00421_len = 0;
      write_00421 = cgc_append_buf(write_00421, &write_00421_len, write_00421_00000, write_00421_00000_len);
      if (write_00421_len > 0) {
         cgc_transmit_all(1, write_00421, write_00421_len);
      }
      cgc_free(write_00421);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00422_00000[] = 
         "\xec\x02\x00\x00";
      static unsigned int write_00422_00000_len = 4;
      unsigned char *write_00422 = NULL;
      unsigned int write_00422_len = 0;
      write_00422 = cgc_append_buf(write_00422, &write_00422_len, write_00422_00000, write_00422_00000_len);
      if (write_00422_len > 0) {
         cgc_transmit_all(1, write_00422, write_00422_len);
      }
      cgc_free(write_00422);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00140_ptr += cgc_data_match(read_00140 + read_00140_ptr, read_00140_len - read_00140_ptr, match_00140_00000, 16);
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00423_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00423_00000_len = 4;
      unsigned char *write_00423 = NULL;
      unsigned int write_00423_len = 0;
      write_00423 = cgc_append_buf(write_00423, &write_00423_len, write_00423_00000, write_00423_00000_len);
      if (write_00423_len > 0) {
         cgc_transmit_all(1, write_00423, write_00423_len);
      }
      cgc_free(write_00423);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00424_00000[] = 
         "\x71\x6c\x72\x68\x45\x45\x59\x70\x79\x07";
      static unsigned int write_00424_00000_len = 10;
      unsigned char *write_00424 = NULL;
      unsigned int write_00424_len = 0;
      write_00424 = cgc_append_buf(write_00424, &write_00424_len, write_00424_00000, write_00424_00000_len);
      if (write_00424_len > 0) {
         cgc_transmit_all(1, write_00424, write_00424_len);
      }
      cgc_free(write_00424);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00425_00000[] = 
         "\xd3\x00\x00\x00";
      static unsigned int write_00425_00000_len = 4;
      unsigned char *write_00425 = NULL;
      unsigned int write_00425_len = 0;
      write_00425 = cgc_append_buf(write_00425, &write_00425_len, write_00425_00000, write_00425_00000_len);
      if (write_00425_len > 0) {
         cgc_transmit_all(1, write_00425, write_00425_len);
      }
      cgc_free(write_00425);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00141_ptr += cgc_data_match(read_00141 + read_00141_ptr, read_00141_len - read_00141_ptr, match_00141_00000, 16);
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00426_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00426_00000_len = 4;
      unsigned char *write_00426 = NULL;
      unsigned int write_00426_len = 0;
      write_00426 = cgc_append_buf(write_00426, &write_00426_len, write_00426_00000, write_00426_00000_len);
      if (write_00426_len > 0) {
         cgc_transmit_all(1, write_00426, write_00426_len);
      }
      cgc_free(write_00426);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00427_00000[] = 
         "\x56\x44\x4d\x31\x69\x71\x56\x49\x7a\x07";
      static unsigned int write_00427_00000_len = 10;
      unsigned char *write_00427 = NULL;
      unsigned int write_00427_len = 0;
      write_00427 = cgc_append_buf(write_00427, &write_00427_len, write_00427_00000, write_00427_00000_len);
      if (write_00427_len > 0) {
         cgc_transmit_all(1, write_00427, write_00427_len);
      }
      cgc_free(write_00427);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00428_00000[] = 
         "\x95\x00\x00\x00";
      static unsigned int write_00428_00000_len = 4;
      unsigned char *write_00428 = NULL;
      unsigned int write_00428_len = 0;
      write_00428 = cgc_append_buf(write_00428, &write_00428_len, write_00428_00000, write_00428_00000_len);
      if (write_00428_len > 0) {
         cgc_transmit_all(1, write_00428, write_00428_len);
      }
      cgc_free(write_00428);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00142_ptr += cgc_data_match(read_00142 + read_00142_ptr, read_00142_len - read_00142_ptr, match_00142_00000, 16);
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00429_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00429_00000_len = 4;
      unsigned char *write_00429 = NULL;
      unsigned int write_00429_len = 0;
      write_00429 = cgc_append_buf(write_00429, &write_00429_len, write_00429_00000, write_00429_00000_len);
      if (write_00429_len > 0) {
         cgc_transmit_all(1, write_00429, write_00429_len);
      }
      cgc_free(write_00429);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00430_00000[] = 
         "\x58\x47\x4b\x46\x4a\x6a\x52\x70\x72\x07";
      static unsigned int write_00430_00000_len = 10;
      unsigned char *write_00430 = NULL;
      unsigned int write_00430_len = 0;
      write_00430 = cgc_append_buf(write_00430, &write_00430_len, write_00430_00000, write_00430_00000_len);
      if (write_00430_len > 0) {
         cgc_transmit_all(1, write_00430, write_00430_len);
      }
      cgc_free(write_00430);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00431_00000[] = 
         "\x1e\x01\x00\x00";
      static unsigned int write_00431_00000_len = 4;
      unsigned char *write_00431 = NULL;
      unsigned int write_00431_len = 0;
      write_00431 = cgc_append_buf(write_00431, &write_00431_len, write_00431_00000, write_00431_00000_len);
      if (write_00431_len > 0) {
         cgc_transmit_all(1, write_00431, write_00431_len);
      }
      cgc_free(write_00431);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00143_ptr += cgc_data_match(read_00143 + read_00143_ptr, read_00143_len - read_00143_ptr, match_00143_00000, 16);
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00432_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00432_00000_len = 4;
      unsigned char *write_00432 = NULL;
      unsigned int write_00432_len = 0;
      write_00432 = cgc_append_buf(write_00432, &write_00432_len, write_00432_00000, write_00432_00000_len);
      if (write_00432_len > 0) {
         cgc_transmit_all(1, write_00432, write_00432_len);
      }
      cgc_free(write_00432);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00433_00000[] = 
         "\x6d\x30\x75\x61\x56\x4d\x46\x33\x34\x07";
      static unsigned int write_00433_00000_len = 10;
      unsigned char *write_00433 = NULL;
      unsigned int write_00433_len = 0;
      write_00433 = cgc_append_buf(write_00433, &write_00433_len, write_00433_00000, write_00433_00000_len);
      if (write_00433_len > 0) {
         cgc_transmit_all(1, write_00433, write_00433_len);
      }
      cgc_free(write_00433);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00434_00000[] = 
         "\xc8\x03\x00\x00";
      static unsigned int write_00434_00000_len = 4;
      unsigned char *write_00434 = NULL;
      unsigned int write_00434_len = 0;
      write_00434 = cgc_append_buf(write_00434, &write_00434_len, write_00434_00000, write_00434_00000_len);
      if (write_00434_len > 0) {
         cgc_transmit_all(1, write_00434, write_00434_len);
      }
      cgc_free(write_00434);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00144_ptr += cgc_data_match(read_00144 + read_00144_ptr, read_00144_len - read_00144_ptr, match_00144_00000, 16);
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00435_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00435_00000_len = 4;
      unsigned char *write_00435 = NULL;
      unsigned int write_00435_len = 0;
      write_00435 = cgc_append_buf(write_00435, &write_00435_len, write_00435_00000, write_00435_00000_len);
      if (write_00435_len > 0) {
         cgc_transmit_all(1, write_00435, write_00435_len);
      }
      cgc_free(write_00435);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00436_00000[] = 
         "\x78\x6b\x65\x55\x78\x50\x43\x4f\x41\x07";
      static unsigned int write_00436_00000_len = 10;
      unsigned char *write_00436 = NULL;
      unsigned int write_00436_len = 0;
      write_00436 = cgc_append_buf(write_00436, &write_00436_len, write_00436_00000, write_00436_00000_len);
      if (write_00436_len > 0) {
         cgc_transmit_all(1, write_00436, write_00436_len);
      }
      cgc_free(write_00436);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00437_00000[] = 
         "\x8f\x00\x00\x00";
      static unsigned int write_00437_00000_len = 4;
      unsigned char *write_00437 = NULL;
      unsigned int write_00437_len = 0;
      write_00437 = cgc_append_buf(write_00437, &write_00437_len, write_00437_00000, write_00437_00000_len);
      if (write_00437_len > 0) {
         cgc_transmit_all(1, write_00437, write_00437_len);
      }
      cgc_free(write_00437);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00145_ptr += cgc_data_match(read_00145 + read_00145_ptr, read_00145_len - read_00145_ptr, match_00145_00000, 16);
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00438_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00438_00000_len = 4;
      unsigned char *write_00438 = NULL;
      unsigned int write_00438_len = 0;
      write_00438 = cgc_append_buf(write_00438, &write_00438_len, write_00438_00000, write_00438_00000_len);
      if (write_00438_len > 0) {
         cgc_transmit_all(1, write_00438, write_00438_len);
      }
      cgc_free(write_00438);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00439_00000[] = 
         "\x47\x55\x51\x6f\x59\x57\x38\x37\x57\x07";
      static unsigned int write_00439_00000_len = 10;
      unsigned char *write_00439 = NULL;
      unsigned int write_00439_len = 0;
      write_00439 = cgc_append_buf(write_00439, &write_00439_len, write_00439_00000, write_00439_00000_len);
      if (write_00439_len > 0) {
         cgc_transmit_all(1, write_00439, write_00439_len);
      }
      cgc_free(write_00439);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00440_00000[] = 
         "\x1d\x03\x00\x00";
      static unsigned int write_00440_00000_len = 4;
      unsigned char *write_00440 = NULL;
      unsigned int write_00440_len = 0;
      write_00440 = cgc_append_buf(write_00440, &write_00440_len, write_00440_00000, write_00440_00000_len);
      if (write_00440_len > 0) {
         cgc_transmit_all(1, write_00440, write_00440_len);
      }
      cgc_free(write_00440);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00146_ptr += cgc_data_match(read_00146 + read_00146_ptr, read_00146_len - read_00146_ptr, match_00146_00000, 16);
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00441_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00441_00000_len = 4;
      unsigned char *write_00441 = NULL;
      unsigned int write_00441_len = 0;
      write_00441 = cgc_append_buf(write_00441, &write_00441_len, write_00441_00000, write_00441_00000_len);
      if (write_00441_len > 0) {
         cgc_transmit_all(1, write_00441, write_00441_len);
      }
      cgc_free(write_00441);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00442_00000[] = 
         "\x33\x6d\x36\x50\x4f\x63\x37\x59\x4e\x07";
      static unsigned int write_00442_00000_len = 10;
      unsigned char *write_00442 = NULL;
      unsigned int write_00442_len = 0;
      write_00442 = cgc_append_buf(write_00442, &write_00442_len, write_00442_00000, write_00442_00000_len);
      if (write_00442_len > 0) {
         cgc_transmit_all(1, write_00442, write_00442_len);
      }
      cgc_free(write_00442);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00443_00000[] = 
         "\x03\x01\x00\x00";
      static unsigned int write_00443_00000_len = 4;
      unsigned char *write_00443 = NULL;
      unsigned int write_00443_len = 0;
      write_00443 = cgc_append_buf(write_00443, &write_00443_len, write_00443_00000, write_00443_00000_len);
      if (write_00443_len > 0) {
         cgc_transmit_all(1, write_00443, write_00443_len);
      }
      cgc_free(write_00443);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00147_ptr += cgc_data_match(read_00147 + read_00147_ptr, read_00147_len - read_00147_ptr, match_00147_00000, 16);
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00444_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00444_00000_len = 4;
      unsigned char *write_00444 = NULL;
      unsigned int write_00444_len = 0;
      write_00444 = cgc_append_buf(write_00444, &write_00444_len, write_00444_00000, write_00444_00000_len);
      if (write_00444_len > 0) {
         cgc_transmit_all(1, write_00444, write_00444_len);
      }
      cgc_free(write_00444);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00445_00000[] = 
         "\x39\x50\x33\x53\x65\x4e\x5a\x52\x62\x07";
      static unsigned int write_00445_00000_len = 10;
      unsigned char *write_00445 = NULL;
      unsigned int write_00445_len = 0;
      write_00445 = cgc_append_buf(write_00445, &write_00445_len, write_00445_00000, write_00445_00000_len);
      if (write_00445_len > 0) {
         cgc_transmit_all(1, write_00445, write_00445_len);
      }
      cgc_free(write_00445);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00446_00000[] = 
         "\x99\x02\x00\x00";
      static unsigned int write_00446_00000_len = 4;
      unsigned char *write_00446 = NULL;
      unsigned int write_00446_len = 0;
      write_00446 = cgc_append_buf(write_00446, &write_00446_len, write_00446_00000, write_00446_00000_len);
      if (write_00446_len > 0) {
         cgc_transmit_all(1, write_00446, write_00446_len);
      }
      cgc_free(write_00446);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00148_ptr += cgc_data_match(read_00148 + read_00148_ptr, read_00148_len - read_00148_ptr, match_00148_00000, 16);
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00447_00000[] = 
         "\x01\x00\x00\x00";
      static unsigned int write_00447_00000_len = 4;
      unsigned char *write_00447 = NULL;
      unsigned int write_00447_len = 0;
      write_00447 = cgc_append_buf(write_00447, &write_00447_len, write_00447_00000, write_00447_00000_len);
      if (write_00447_len > 0) {
         cgc_transmit_all(1, write_00447, write_00447_len);
      }
      cgc_free(write_00447);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00448_00000[] = 
         "\x7a\x30\x73\x76\x61\x57\x69\x64\x6c\x07";
      static unsigned int write_00448_00000_len = 10;
      unsigned char *write_00448 = NULL;
      unsigned int write_00448_len = 0;
      write_00448 = cgc_append_buf(write_00448, &write_00448_len, write_00448_00000, write_00448_00000_len);
      if (write_00448_len > 0) {
         cgc_transmit_all(1, write_00448, write_00448_len);
      }
      cgc_free(write_00448);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00449_00000[] = 
         "\xc7\x00\x00\x00";
      static unsigned int write_00449_00000_len = 4;
      unsigned char *write_00449 = NULL;
      unsigned int write_00449_len = 0;
      write_00449 = cgc_append_buf(write_00449, &write_00449_len, write_00449_00000, write_00449_00000_len);
      if (write_00449_len > 0) {
         cgc_transmit_all(1, write_00449, write_00449_len);
      }
      cgc_free(write_00449);
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
         "\x4e\x6f\x20\x6d\x6f\x72\x65\x20\x65\x6e\x74\x72\x69\x65\x73\x0a";
      read_00149_ptr += cgc_data_match(read_00149 + read_00149_ptr, read_00149_len - read_00149_ptr, match_00149_00000, 16);
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00450_00000[] = 
         "\x08\x00\x00\x00";
      static unsigned int write_00450_00000_len = 4;
      unsigned char *write_00450 = NULL;
      unsigned int write_00450_len = 0;
      write_00450 = cgc_append_buf(write_00450, &write_00450_len, write_00450_00000, write_00450_00000_len);
      if (write_00450_len > 0) {
         cgc_transmit_all(1, write_00450, write_00450_len);
      }
      cgc_free(write_00450);
   } while (0);
}
