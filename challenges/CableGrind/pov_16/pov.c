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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4b\x57\x87\x87"
         "\xb7\x00\x29\x15\x3f\x05\xff\xdc\xa8\xe1\xce\x88\xb3\xc9\x91\xca"
         "\x52\x00\x00\x00\x8c\x7c\x02\x42\xf1\x5b\xdc\xb1\x2e\xad\x27\x98"
         "\xc8\x2b\xac\x05\xdf\xa6\x6a\xc4\x32\x88\x1a\x9e\x5f\x5c\x2a\xf1"
         "\x5f\xff\x40\xe9\xd4\x5d\x75\x0a\x06\xd6\xd4\x20\xfc\x9f\xa7\xf9"
         "\x82\xbb\x21\xa3\x3d\xe3\x33\x21\x73\xab\x63\xa8\x7f\xd9\xb2\xb6"
         "\x8e\xdf\xb6\xe1\x3a\x48\x2b\x32\xc6\x2b\x9b\xc2\x6a\xfc\xe0\xe7"
         "\x06\x41\x2a\x09\x29\xf1\xc6\x53\xda\x9d\x49\xe2\xba\xdb\xf9\x31"
         "\xff\x8b\x8a\x4b\x30\xf2\x90\x0d\x09\x0b\x16\xe8\x83\x35\x00\x2d"
         "\xd8\x6f\x62\x75\xf7\xe1\x70\x7d\x32\xb6\xec\x50\x61\x90\xb9\xda"
         "\xdc\x23\xfe\x9c\x14\x00\xe9\x78\x20\x07\x71\x2f\x4a\xf0\x17\x16"
         "\xdf\xf8\xcf\xe7\x01\x0e\x96\xaf\x85\x0d\xb6\x87\x2c\x09\x4f\x1a"
         "\x0a\xaf\xc4\x14\x18\xb2\x4d\x5b\x69\x60\x54\xfd\x16\xd3\x99\x34"
         "\xe5\x9a\xc9\xb2\xbc\x43\x9d\xdb\xb5\xcd\x5b\x55\xd0\xf3\x0f\xe3"
         "\x2e\x29\xb9\x25\xa2\x14\xf2\x83\xe2\x84\x7c\x80\x8a\x4c\x4e\xc4"
         "\x18\x16\xa8\x5d\x1a\x3d\x7b\x52\x90\xa0\x08\x33\xc0\x50\x7b\xc8"
         "\xa3\x0b\x12\x87\x9d\x9e\x18\xce\xbf\x70\x37\x24\xa1\xd0\x81\x5f"
         "\xfc\x4e\x23\xe4\xf5\x78\x7a\xa5\x30\xa7\x9f\x32\xbf\x2b\x5d\x15"
         "\x97\xea\xba\xf6\xe8\x8a\x67\x3a\x90\x60\x65\x37\x39\x2d\x47\x5c"
         "\xc9\x63\xe9\x48\xd2\x70\xb4\x04\xde\xdf\x8a\x2b\xcf\x19\xfb\x3c"
         "\x7a\xa7\x03\xe0\x47\x64\x97\xe8\x85\x35\x38\x21\x00\xdd\xf7\x60"
         "\x8b\x76\x71\x20\x60\xc9\x25\x80\x57\xa1\xa8\x62\x6a\xe7\x64\xe3"
         "\xe8\x41\x44\xb7\xd5\xef\xc0\x4f\x21\xfb\xb6\x00\x4a\x2a\x2e\x60"
         "\xe4\x0e\x5b\xe6\x05\x13\xb2\xa0\x95\x6a\x24\x80\x16\x71\xc5\x25"
         "\x6c\x31\x92\xb5\x12\x89\x94\x82\x0f\xf3\x47\xbd\xbd\xa6\x36\xe1"
         "\xa5\x40\x8a\xc7\x6f\x60\xbe\x17\xd1\x78\xbd\x52\x8e\x13\x8f\xd1"
         "\xb6\x63\xc4\x69\xd9\x29\x25\xc9\x27\x1c\x43\x9a\x42\x4b\xa1\x6e"
         "\xe8\x2c\x14\x10\xbd\xcf\x72\xb9\x88\x4d\x82\xd5\x49\xfc\x72\x36"
         "\xb2\xd1\xa6\x2b\x4f\x64\x13\xc4\x48\xd6\xc9\xe4\x79\x36\xa2\xd9"
         "\x3e\x9c\x9e\x44\x5a\x67\x6a\x76\x84\xf6\x4e\xc7\xe5\xe4\x88\x18"
         "\x9e\x81\x27\x6f\x3b\xa4\xda\x55\x07\x01\xe1\xde\x92\xf1\x30\x2c"
         "\x60\x67\xe5\x98\xee\xc5\xb3\x98\xb4\xde\x21\x52\x1e\x7b\x56\xd1"
         "\xbd\xf8\x72\x15\x6e\x35\xd9\xf2\xfa\x0f\x6e\xb9\xc1\x5c\xdf\x70"
         "\x28\xcf\x55\x80\x16\xce\xa9\xef\x85\x5b\x1a\x12\xe3\x83\xce\xf3"
         "\xff\x81\x0b\x53\xdb\xc4\x7f\xa7\xe9\x06\xf1\x2a\x35\xc4\xa5\x0f"
         "\xca\x87\x63\xea\x42\x81\xc2\x1c\x2f\x03\x3a\xff\x7c\x5f\x25\x66"
         "\x28\x58\x44\x0c\x77\x7d\xbb\xec\xf7\xf8\x67\x4e\x84\x8f\xab\xde"
         "\x95\xca\x32\x3e\x95\x03\x1b\x16\xa5\x4e\x0c\x4d\xf4\x20\x20\x20"
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
.*===uncomminutedcommix
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x63\x6f\x6d\x6d\x69\x6e\x75\x74\x65"
         "\x64\x63\x6f\x6d\x6d\x69\x78";
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
.*===ineloquentundishonored
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x65\x6c\x6f\x71\x75\x65\x6e\x74\x75"
         "\x6e\x64\x69\x73\x68\x6f\x6e\x6f\x72\x65\x64";
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
.*===goniometerhexameral
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x67\x6f\x6e\x69\x6f\x6d\x65\x74\x65\x72\x68"
         "\x65\x78\x61\x6d\x65\x72\x61\x6c";
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
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 4);
      if (read_00006_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00006_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
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
}
