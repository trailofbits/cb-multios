#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x53\x45\x4e\x44\x08\x2f\x56\x46\x4b\x41\x6e\x73\x62\x60\x00\x6a"
         "\x4a\x41\x52\x79\x45\x4d\x45\x41\x4d\x4c\x36\x75\x44\x62\x43\x4e"
         "\x62\x39\x51\x58\x79\x58\x70\x53\x31\x79\x54\x43\x4c\x33\x36\x74"
         "\x70\x50\x37\x30\x35\x4c\x76\x67\x57\x76\x69\x37\x6b\x43\x62\x6c"
         "\x6b\x4a\x70\x46\x30\x7a\x6e\x62\x41\x75\x54\x4c\x4d\x36\x4b\x72"
         "\x37\x6c\x47\x6e\x7a\x46\x45\x4b\x6e\x71\x32\x43\x66\x57\x65\x6e"
         "\x4c\x55\x68\x35\x30\x79\x76\x49\x6e\x73\x4f\x67\x76\x6b\x33";
      static unsigned int write_00000_00000_len = 111;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x46\x69\x6c\x65\x20\x72\x65\x63\x65"
         "\x69\x76\x65\x64\x3a\x20\x2f\x56\x46\x4b\x41\x6e\x73\x62\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 31);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x53\x45\x4e\x44\x0a\x2f\x44\x4a\x41\x50\x6e\x4e\x58\x69\x5a\x4a"
         "\x00\x4a\x68\x4c\x62\x32\x47\x31\x73\x53\x65\x4b\x35\x42\x37\x39"
         "\x61\x70\x67\x45\x41\x6b\x49\x4b\x42\x71\x67\x72\x4b\x68\x36\x4a"
         "\x45\x73\x43\x73\x4b\x44\x79\x74\x4a\x4a\x4b\x52\x37\x6f\x54\x4c"
         "\x66\x72\x65\x79\x34\x4a\x75\x33\x47\x6b\x77\x33\x62\x4b\x34\x74"
         "\x62\x75\x77\x37\x62\x56\x48\x36\x61\x54\x76";
      static unsigned int write_00001_00000_len = 91;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x46\x69\x6c\x65\x20\x72\x65\x63\x65"
         "\x69\x76\x65\x64\x3a\x20\x2f\x44\x4a\x41\x50\x6e\x4e\x58\x69\x5a"
         "\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 33);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x53\x45\x4e\x44\x0b\x2f\x6c\x75\x73\x66\x63\x74\x53\x34\x61\x74"
         "\x44\x00\x58\x66\x77\x6d\x58\x47\x6b\x68\x6d\x4e\x47\x50\x76\x77"
         "\x78\x48\x4f\x58\x54\x74\x73\x42\x30\x59\x45\x67\x77\x35\x6e\x53"
         "\x6b\x63\x6b\x55\x59\x67\x45\x61\x79\x32\x67\x32\x7a\x36\x46\x59"
         "\x5a\x37\x36\x43\x76\x55\x78\x34\x4e\x4a\x75\x33\x71\x43\x6e\x56"
         "\x58\x66\x48\x74\x52\x48";
      static unsigned int write_00002_00000_len = 86;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x46\x69\x6c\x65\x20\x72\x65\x63\x65"
         "\x69\x76\x65\x64\x3a\x20\x2f\x6c\x75\x73\x66\x63\x74\x53\x34\x61"
         "\x74\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 34);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x53\x45\x4e\x44\x0b\x2f\x51\x75\x49\x35\x62\x43\x50\x43\x50\x33"
         "\x21\x00\x46\x58\x70\x47\x39\x73\x5a\x73\x4d\x64\x6b\x75\x33\x6c"
         "\x46\x71\x69\x5a\x4e\x67\x47\x7a\x56\x6b\x72\x66\x54\x47\x53\x6e"
         "\x56\x6d\x45";
      static unsigned int write_00003_00000_len = 51;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x46\x69\x6c\x65\x20\x72\x65\x63\x65"
         "\x69\x76\x65\x64\x3a\x20\x2f\x51\x75\x49\x35\x62\x43\x50\x43\x50"
         "\x33\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 34);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x52\x45\x50\x4f\x0a\x2f\x44\x4a\x41\x50\x6e\x4e\x58\x69\x5a";
      static unsigned int write_00004_00000_len = 15;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x44\x4a\x41\x50\x6e\x4e\x58\x69\x5a"
         "\x20\x72\x65\x6d\x6f\x76\x65\x64\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 25);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x50\x52\x4e\x54";
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x4c\x69\x73\x74\x69\x6e\x67\x20\x66"
         "\x69\x6c\x65\x73\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 21);
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
         "\x2f\x51\x75\x49\x35\x62\x43\x50\x43\x50\x33\x20\x20\x20\x20\x20"
         "\x46\x69\x6c\x65\x20\x20\x20\x20\x20\x33\x33\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 28);
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
         "\x2f\x56\x46\x4b\x41\x6e\x73\x62\x20\x20\x20\x20\x20\x46\x69\x6c"
         "\x65\x20\x20\x20\x20\x20\x39\x36\x0a";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 25);
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
         "\x2f\x6c\x75\x73\x66\x63\x74\x53\x34\x61\x74\x20\x20\x20\x20\x20"
         "\x46\x69\x6c\x65\x20\x20\x20\x20\x20\x36\x38\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 28);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x53\x54\x4f\x50";
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
         "\x5b\x49\x4e\x46\x4f\x5d\x20\x54\x65\x72\x6d\x69\x6e\x61\x74\x69"
         "\x6e\x67\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 19);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
}
