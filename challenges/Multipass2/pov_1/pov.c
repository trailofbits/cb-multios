#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00"
         "\xe8\x03\x00\x00";
      static unsigned int write_00000_00000_len = 20;
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
      //**** length read
      read_00000_len = 16;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x00\x04\x00\x00\xaf\xed\x02\x00";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 16);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x03\x04\x00\x00\xaf\xed\x02\x00";
      static unsigned int write_00001_00000_len = 16;
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
      //**** length read
      read_00001_len = 16;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x03\x04\x00\x00\xaf\xed\x02\x00";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 16);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x00\x00\x00\x00\x00\x00\x00";
      static unsigned int write_00002_00000_len = 16;
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
      //**** length read
      read_00002_len = 16;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x00\x00\x00\xb0\xed\x02\x00";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 16);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x00\x00\x00\xb0\xed\x02\x00"
         "\x16\x61\x01\x00\x0d\x03\x00\x00\xf5\xa1\x0e\x00\x05\x86\x6f\x47"
         "\x67\x75\x4c\x48\x63\x69\x6f\x78\x55\x71\x4c\x34\x78\x66\x76\x4b"
         "\x4b\x71\x35\x70\x4a\x42\x49\x67\x6b\x45\x53\x47\x72\x47\x57\x77"
         "\x58\x76\x64\x52\x74\x34\x78\x62\x69\x4b\x30\x4d\x50\x58\x56\x73"
         "\x35\x6b\x6a\x68\x59\x6f\x6b\x55\x59\x67\x7a\x67\x4b\x55\x77\x43"
         "\x30\x47\x49\x44\x74\x43\x6b\x61\x52\x70\x42\x4e\x77\x4e\x58\x63"
         "\x6a\x42\x4f\x56\x43\x75\x42\x35\x31\x36\x47\x58\x66\x47\x5a\x31"
         "\x74\x79\x69\x78\x5a\x75\x33\x4f\x52\x65\x4f\x75\x78\x34\x30\x7a"
         "\x48\x32\x39\x4a\x32\x58\x62\x54\x4a\x55\x57\x32\x6b\x35\x61\x4d"
         "\x32\x75\x67\x33";
      static unsigned int write_00003_00000_len = 164;
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
      //**** length read
      read_00003_len = 16;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x00\x00\x00\xb0\xed\x02\x00";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 16);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x03\x00\x00\x00\xb0\xed\x02\x00";
      static unsigned int write_00004_00000_len = 16;
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
      //**** length read
      read_00004_len = 16;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x03\x00\x00\x00\xb0\xed\x02\x00";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 16);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x05\x00\x00\x00\x00\x00\x00";
      static unsigned int write_00005_00000_len = 16;
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
      //**** length read
      read_00005_len = 16;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x05\x00\x00\xb1\xed\x02\x00";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 16);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x05\x00\x00\xb1\xed\x02\x00"
         "\x16\x61\x01\x00\xb0\xed\x02\x00";
      static unsigned int write_00006_00000_len = 24;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 16;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x05\x00\x00\xb1\xed\x02\x00";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 16);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x03\x00\x00\x00\x00\x00\x00";
      static unsigned int write_00007_00000_len = 16;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 16;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x01\x03\x00\x00\xb2\xed\x02\x00";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 16);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x03\x00\x00\xb2\xed\x02\x00"
         "\x06\x00\x00\x00";
      static unsigned int write_00008_00000_len = 20;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 20;
      read_00008 = (unsigned char*)cgc_malloc(read_00008_len);
      int read_00008_res = cgc_length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x70\x68\x03\x00\x22\xbf\x01\x00\x02\x03\x00\x00\xb2\xed\x02\x00"
         "\x04\x00\x00\x00";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 20);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 12;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x03\x02\x00\x00\x70\x68\x03\x00\xb2\xed\x02\x00";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 12);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 4;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x06\x00\x00\x00";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 4);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 12;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x05\x02\x00\x00\x70\x68\x03\x00\xb1\xed\x02\x00";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 12);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
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
         "\x16\x61\x01\x00\xb0\xed\x02\x00";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 8);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 12;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x00\x03\x00\x00\x70\x68\x03\x00\xb0\xed\x02\x00";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 12);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
}
