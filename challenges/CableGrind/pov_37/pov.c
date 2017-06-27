#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x04\x04\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4b\x60\xcf\x0c"
         "\x6c\xe4\x39\x58\x5c\xba\x1e\xca\xd0\x03\xd2\xcd\xf5\x2e\x70\x66"
         "\xd9\x00\x00\x00\x26\x6d\xef\xb6\x32\x72\xd8\xc9\x77\x6b\x16\x9e"
         "\x9f\x3d\xbc\xc5\x39\x2a\x38\xfd\x1a\x42\xa9\x71\x6c\xb0\x48\x16"
         "\x00\x16\x00\xac\xc6\x64\x52\x19\x67\xff\x1d\x2f\x2c\xbc\x32\x16"
         "\x61\x16\xf2\x75\xb7\x28\x6a\xe3\x1d\xbe\xe7\xed\xe2\xce\x3a\x93"
         "\xc2\x69\x1e\x1d\x38\xf5\x54\xc2\xb9\xcb\x55\xf0\x94\x36\x14\xe6"
         "\x7f\x23\x3d\xd7\x2e\x47\x36\x9a\xd0\x2d\x3d\xff\x61\x7b\xa4\x55"
         "\xe7\x72\xcc\xb9\xa7\xce\xce\x11\x7b\x04\x3d\x0a\xdd\x0f\x92\x97"
         "\xcb\x86\xbc\x04\x2a\x16\xd8\xb2\xd4\x2b\x76\x01\x55\xba\x95\x47"
         "\xfb\x6a\x5c\xb5\x87\x7f\xce\xdf\xb0\x72\x37\xe1\x3a\xa3\x19\x1f"
         "\xe7\x71\x45\x98\xff\x83\x98\x49\xf1\x31\x0c\x9d\xb3\xb6\x9a\x0d"
         "\x6b\x14\x41\xe9\x11\xcf\x14\xac\x32\x8e\xd7\x16\x6b\x52\x99\xd2"
         "\x5e\xb1\xa3\xdd\xe7\x30\x61\x7d\xe8\x09\xb4\x6d\x80\x98\x84\x6f"
         "\xd5\xab\x14\xb8\xc2\x36\xf1\xbc\x7d\x0b\xaa\x35\xb6\x17\x1a\xee"
         "\x35\xc4\xc2\x5d\xd1\x43\x7f\x5c\xa9\xc4\xee\xce\xf6\xc9\x16\xdc"
         "\x2b\x45\xd0\x45\xaf\xfa\x82\xed\x6a\x4c\x62\x25\x87\x2d\xd4\xc4"
         "\xd4\xad\x97\x12\x4e\x2b\xdb\xf7\x6b\xbb\xf5\x2a\x99\x1b\xcf\x5e"
         "\x34\xed\xa2\xde\xd4\x86\xfc\x4f\xb5\x09\xda\x67\xb4\x46\x59\x7d"
         "\xe3\x29\xf4\xf9\x91\x4b\xeb\xaa\x96\x9e\x06\x84\x18\x1b\x55\xc3"
         "\x7e\xd3\x14\xd6\x53\xf6\xc7\x5f\xde\x49\x80\xdf\x6a\x1d\x2f\x3b"
         "\x06\x25\x1f\x21\xf9\x00\xdd\x5b\xd6\x32\x80\x27\x99\xaa\x6d\xc3"
         "\x9a\x4d\xa0\xbd\xc6\x68\x46\x73\xd8\xb8\xc4\x83\x39\x77\x71\xcc"
         "\xfa\x1c\x8f\x33\xec\x38\x95\xd3\xb7\x3e\xd7\x38\x3b\x1f\x88\x62"
         "\xb8\xdb\x3d\x2c\xe3\x9d\x01\x7d\xef\xf7\x7a\x04\xea\x9e\x8f\x90"
         "\x36\x0b\x36\xc4\xc7\xaf\x6a\x5b\xf3\x31\x9e\xa9\x61\x0e\x10\x5b"
         "\x96\xac\x5a\xa2\xe8\xbf\x99\x6c\x9d\x8f\x41\xb8\xed\xcb\x6e\xc8"
         "\xd1\xb1\xc5\x17\x60\x1b\x49\x26\xf8\xe0\x14\x29\x2b\xc7\x39\xe1"
         "\x67\x1c\xcb\x2d\x18\xdd\xf0\xab\x3d\x6f\xd4\xbf\x13\x09\x11\x7d"
         "\xb7\x2a\x5a\xe3\x1e\x12\x97\x3a\x21\x3b\xc2\x40\xe9\x1d\x42\x04"
         "\xc0\x1b\xad\x93\x33\x46\x5a\x4a\x1f\xb7\xf4\xaa\xe9\x3c\x49\xc1"
         "\x78\x02\x76\xe6\x9c\x00\xe0\xf2\x6e\x7a\x07\xa2\xd8\x34\x20\xb9"
         "\x67\xb6\x89\x65\x11\x5a\xf2\x9a\x05\x0f\x3d\x58\xab\x74\x13\xf8"
         "\x0d\x1d\x2b\x9e\x09\x86\xeb\x60\xf0\x41\x4a\xe5\xd8\xf1\x21\xa2"
         "\x00\x70\xbd\xea\x94\x6a\x20\xc0\x40\x45\x88\x7b\x38\x7b\xc1\xda"
         "\xdc\xf4\x0b\x96\x97\x14\x6d\x3b\x5a\xcc\xc2\x0d\x39\x7c\xfe\xb5"
         "\x1b\x4b\x6b\xbb\x41\x77\x34\x8c\x0a\x37\x37\x8b\xa3\x7d\x60\x69"
         "\xf6\xf3\xb9\x6b\x01\xa0\x85\x5d\x60\xf1\xe8\xa1\x80\xb2\x73\x37"
         "\x86\xb6\x96\xd1\x33\x55\x31\x9d\x14\x36\x17\x18\x75\xe8\x24\xea"
         "\xba\xf3\x6a\xa5\xb7\x99\x4f\x0f\xfe\x06\xf9\x77\x3c\x3d\xbb\x34"
         "\xf0\xd3\xa6\x4b\x1a\x4f\xa4\x64\x7b\xa0\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20";
      static unsigned int write_00001_00000_len = 1028;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
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
         "\x53\x74\x61\x72\x74\x69\x6e\x67\x20\x64\x69\x73\x73\x65\x63\x74"
         "\x69\x6f\x6e\x2e\x2e\x2e";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 22);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x3d\x3d\x3d\x3d\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 5);
      if (read_00001_res) {} //silence unused variable warning
      /* read match pcre:
.*New Packet
*/
      static char read_00001_00000_regex[] = 
         "\x2e\x2a\x4e\x65\x77\x20\x50\x61\x63\x6b\x65\x74";
      static match_result read_00001_00000_match;
      pcre *read_00001_00000_pcre = cgc_init_regex(read_00001_00000_regex);
      if (read_00001_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00001_00000_pcre, 0, read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, &read_00001_00000_match);
         if (rc > 0) {
            read_00001_ptr += read_00001_00000_match.match_end - read_00001_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00001_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 4);
      if (read_00002_res) {} //silence unused variable warning
      /* read match pcre:
.*===rofl
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x66\x6c";
      static match_result read_00002_00000_match;
      pcre *read_00002_00000_pcre = cgc_init_regex(read_00002_00000_regex);
      if (read_00002_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00002_00000_pcre, 0, read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, &read_00002_00000_match);
         if (rc > 0) {
            read_00002_ptr += read_00002_00000_match.match_end - read_00002_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00002_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 4);
      if (read_00003_res) {} //silence unused variable warning
      /* read match pcre:
.*===intorsiondermatograph
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x74\x6f\x72\x73\x69\x6f\x6e\x64\x65"
         "\x72\x6d\x61\x74\x6f\x67\x72\x61\x70\x68";
      static match_result read_00003_00000_match;
      pcre *read_00003_00000_pcre = cgc_init_regex(read_00003_00000_regex);
      if (read_00003_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00003_00000_pcre, 0, read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, &read_00003_00000_match);
         if (rc > 0) {
            read_00003_ptr += read_00003_00000_match.match_end - read_00003_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00003_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 4);
      if (read_00004_res) {} //silence unused variable warning
      /* read match pcre:
.*===ExobasidialesEppy
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x45\x78\x6f\x62\x61\x73\x69\x64\x69\x61\x6c"
         "\x65\x73\x45\x70\x70\x79";
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
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
