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
         "\x01\x00\x00\x00\x01\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x00\xa3\x0e\xfe"
         "\xbf\x2e\x22\xfd\xda\x4d\x37\x4d\x4d\x00\x00\x00\xea\x14\x73\x93"
         "\x60\xc4\xe9\x18\xd1\x5c\x60\x34\x14\xc2\xe1\x8d\x49\xc9\x7e\x02"
         "\x0c\x07\x62\x57\xb2\x03\x94\xd8\xee\x8a\x63\x26\x1c\x5d\x2a\xba"
         "\xd3\x65\xdc\xe6\x59\x0a\xb4\x73\x31\x02\x9e\xc3\xee\xff\x68\x80"
         "\x46\x48\x90\x92\xe6\x6b\x87\x26\x66\x17\x68\x3f\xb9\x02\x5f\x94"
         "\x18\xf5\x56\x16\x0e\xb1\x77\xb1\x59\xf4\xf7\xfc\x5a\xb6\xa6\xfe"
         "\x27\xc7\x22\x89\x27\xc2\xff\x0d\x47\x4d\xc9\x4a\x92\x8e\xfa\xf6"
         "\x6a\x9f\xc3\x93\x86\x6e\xd9\x58\xab\x2c\x47\x96\xdb\xed\x1e\x59"
         "\xbd\x59\x9f\xb4\x27\xfa\xd0\x63\x2c\xc1\x64\x6b\x7e\x35\x04\x4b"
         "\x2f\x63\x9a\x51\xd7\xa1\x65\x00\xcd\xc6\x81\x15\x05\x06\xe8\x5f"
         "\xe6\x22\x78\x91\xa7\xf4\xec\x42\x84\x7a\x69\x20\xae\x6e\xdc\x5d"
         "\xeb\xc5\x72\x6d\x0a\x00\x37\x8d\x07\xdc\x2f\x73\xc8\xf6\x12\xc3"
         "\x2c\xee\x08\xa6\xbb\xf9\x7b\xe8\x89\x98\xf4\x13\x30\x2d\x72\x22"
         "\xc6\xb8\x51\x96\xbd\x10\xd8\x42\x27\xe0\xdf\xc9\x09\xc4\x6b\x06"
         "\x4d\x24\xfe\x47\x46\x8c\xbc\xa0\xc4\xdc\x83\xa0\x33\xda\x71\xc0"
         "\xd4\xe3\x9d\x8c\x19\x2a\x5f\x89\xcc\xd7\x54\xe3\x41\x99\x5e\xd0"
         "\x94\x0b\xb3\x9b\x4a\x50\xfb\x3a\x78\xa1\xac\xd5\x48\x55\xa2\xc8"
         "\x18\x23\x5a\x3c\x34\x2e\xaf\xc2\xe6\x2e\xfc\x27\x78\x9e\xef\x5a"
         "\xe4\x54\xf7\x79\x41\x44\x65\xdd\x3e\xa2\xb0\x3e\xeb\xf6\x79\x6f"
         "\xf8\x58\x7f\xbf\xf4\xff\x24\x1d\xce\x63\x51\xe2\x89\xc3\x10\x5a"
         "\x1e\x35\x00\x05\x38\xce\xd1\x4a\x7c\xa8\xb1\xc0\xd0\x02\xa4\xf1"
         "\x5b\x52\xa8\x5d\x23\x55\x65\x9e\x14\xee\x5c\x62\x59\x35\xe1\x98"
         "\xe1\xfe\xc1\x53\xe2\x65\x22\x49\xbd\xda\xdc\x4b\x28\xaa\xbc\x1c"
         "\x76\xf0\x78\x08\x7c\xe7\xe4\xec\xd2\x41\xb3\x7d\x68\x8e\x80\x26"
         "\x83\xc8\x9c\x9f\x79\xff\xbb\x1e\x0f\x06\x73\x04\xd9\xdb\x30\xd3"
         "\xf1\x50\x7d\x24\x11\xc5\x52\xd3\xe7\x0b\xbc\x68\xc5\xdf\xf0\xd1"
         "\xcb\x47\xda\x70\x8a\x2a\x51\x4c\x79\xb6\x52\x23\x44\x31\x8f\xe5"
         "\x50\x62\xdb\x32\x30\x25\xec\x70\xd6\x58\x58\x12\xc5\x6f\xec\xf1"
         "\x29\xa3\xb6\x21\xb2\x5e\x44\xa3\xc0\xb3\x1d\xd2\x6a\x71\x59\x92"
         "\x99\xa3\xea\x61\x9f\x15\xa5\xa7\xae\x27\x2d\xf5\x08\x8d\x2f\xf8"
         "\xdd\x77\x73\x52\xc3\x71\x8a\xcc\x03\x9d\x08\xa9\x01\x38\xab\x84"
         "\x23\x61\x46\xe4\x73\xcf\x06\x1c\x94\x42\x8d\xb6\xd4\xbf\xb5\xb9"
         "\x5f\x7c\xb8\x3a\xe6\xa9\x8f\x24\x50\xcd\x92\x0b\x89\xd5\xe7\xa5"
         "\xe3\x7a\x20\x5c\x5e\xe6\xaf\x82\xf9\x88\xe6\x4d\x18\x27\xee\x1b"
         "\xf5\x8b\xe2\xc3\xb7\x0e\x3d\xf0\x07\x65\x4d\x08\x19\xea\xc7\x94"
         "\x9f\x07\x2c\x00\xd4\x38\x7b\xb8\xca\x69\xdb\x3e\x38\x6a\x2f\xc1"
         "\xe5\x54\x04\x0f\xcb\xda\xe7\xd7\xe6\x4d\x0d\x34\xdd\x68\x0b\x6b"
         "\x24\x55\x79\x54\x3c\xc4\x49\x2b\xd4\x93\xb9\x0a\xd1\xd3\xf9\xd4"
         "\x7b\xa0\x24\xeb\x53\x7f\xd7\x9e\xa7\xdc\xd0\xdb\x6a\x82\x57\x32"
         "\x23\x10\x17\xf6\x7e\xd1\xd4\xbb\x7d\x79\xc1\xa3\x13\x32\xb0\x6f"
         "\x7c\x46\x7e\xc0\x7d\xcb\xa8\x21\x73\x51\xff\xd8\x22\x20\x20\x20"
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
.*===lol
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x6c";
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
