#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x04\x04\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb9\xd4\xa2\x27"
         "\x1b\xdd\x53\xba\x23\x4c\xf1\xc5\xb5\xce\x0c\x47\xbe\xb8\x0f\x29"
         "\x67\x00\x00\x00\xf0\xff\x70\xf9\x3d\x90\x9d\x57\x52\x8a\x58\x5a"
         "\x54\x19\xde\xd7\x86\x72\xe7\xf6\x48\x34\xd7\x97\x18\x6e\x49\xc6"
         "\x1c\x34\x1e\x96\xc4\x7c\x6b\xbb\xef\xd2\x76\xac\xc9\xcb\x49\xd1"
         "\x68\x07\xb5\x5e\xb8\x33\x66\xe5\x0d\x50\xf8\xdf\xff\x12\x4c\xc9"
         "\x25\x8e\x69\x45\xa4\xcd\xa6\x21\x60\x77\x86\x8e\xe1\x20\xe8\x5b"
         "\xe0\x90\xf9\x6b\x3c\x57\xdc\xd9\x38\x51\x84\xf0\x7a\x8b\xce\x38"
         "\xd9\x7c\x6c\x6f\xf3\xd6\xcf\xc3\x76\x10\xed\x61\x47\xc8\xb2\x82"
         "\xcc\xe5\x6f\x23\x1f\x4d\x25\xc4\x6c\x1e\x0b\xaf\xf4\x9e\x20\xe2"
         "\x45\xcf\xbb\xf9\x4f\x1c\x79\xe9\xf1\x58\x11\x91\xe0\x94\x4b\xa8"
         "\x9b\x58\xa1\xa3\x30\xb5\x1f\x24\x14\xb9\x14\x4a\x68\xd7\xb9\xce"
         "\x3c\xa0\x64\xd6\x73\x2b\x48\x81\xe5\x1b\x7c\xc7\x12\x00\x01\x6d"
         "\x0c\x78\x0e\xf9\x99\xd5\xe1\x1d\x3b\xcf\x08\xa9\xc4\xda\xe8\x47"
         "\x84\xd7\x98\xd4\x3e\x92\x3b\xb8\x15\xe1\xff\xb6\x4a\x36\x56\xc5"
         "\xbc\x09\x9d\x0c\x0d\x20\x95\xd1\x12\xca\xb9\x79\xc5\xf2\xa3\x47"
         "\x9a\xbe\xd8\x06\x13\x08\x2c\xb3\xcd\xa2\xf2\x0f\x15\xe7\x29\xc7"
         "\x6c\xf9\x4d\x5e\x0e\x9e\xd3\xa5\xec\x69\xe5\xa1\x7c\xa6\x71\xf4"
         "\xb8\xe3\x5b\xc0\x2f\x5d\x10\xf5\x1f\x0a\x86\x0f\x8e\xff\x60\x9e"
         "\xf6\x3f\x23\xcf\x46\x8e\x39\xe9\xee\xe9\xea\xb0\xf4\x17\xb0\x0e"
         "\xb5\x4a\x9d\x96\x47\x15\x00\x69\xa5\x74\xa4\x20\x19\xbb\x62\x73"
         "\x2d\x60\xba\x96\x9a\x8f\x3e\xa0\xa0\x87\xd7\xbc\x82\x73\xec\x7a"
         "\xa0\xab\xf9\x40\x59\xde\x3b\x47\xc6\x46\x30\x4f\xca\x84\x68\x9c"
         "\x31\x4d\xb0\x48\xe7\x7e\x9c\x32\x58\x58\x00\x4b\xb8\x79\x81\x69"
         "\x4b\xb5\x3a\xcc\x9d\x22\xd2\x2a\x98\xb5\x9b\x61\xeb\x93\x68\x32"
         "\xf6\xa6\xe9\x2b\x87\x32\x13\x32\x79\x1a\x0d\x5c\xab\x54\x6a\x6c"
         "\x6a\xc3\x1c\x77\x37\xec\x14\x00\xf9\x1c\xf6\x61\xa4\x5b\xa1\x77"
         "\x86\x24\xdd\xaa\x18\x38\xd5\xea\x6b\xa9\x3a\xf4\x9b\xc8\xe1\x79"
         "\xec\xbe\x71\x15\x3e\xeb\x44\xee\x07\x52\x8a\x52\x71\xeb\x0d\x9a"
         "\xdd\x36\x2b\xe7\x23\x8f\x2d\x8c\xb4\xac\xd0\x60\x49\xe2\x8c\x97"
         "\x03\xbe\xb6\xd6\x58\xf6\x32\x2c\x03\x03\x7d\x51\x89\xb3\x68\x71"
         "\x47\x72\xae\xd7\x63\x7a\x1f\xf2\x56\x94\xd6\xb7\xff\x60\x57\xe8"
         "\x9b\xc1\x35\x3e\x19\x71\x9f\xa9\x21\xb8\x4a\x47\xc6\x37\x62\x09"
         "\xda\xda\xdd\xfd\xaf\x8c\x68\x60\x3a\xb2\x04\x35\xe5\x61\x65\x20"
         "\x57\x19\x6b\x2f\xd8\x82\x4c\xf3\x80\x1f\x32\xa0\x24\x96\x94\x8f"
         "\xa5\x3a\xc0\x7a\xac\x54\xcb\x2d\x5c\x77\xce\x28\xc6\x97\xa1\xf5"
         "\xee\x2b\x9e\x95\x35\x6d\x0e\x02\x71\xc2\xd3\x2a\x2f\xb0\x72\x8b"
         "\x14\x68\x29\xf2\xa4\x67\x13\x37\xe5\xa9\x5f\xfb\xf5\x15\x44\xd5"
         "\xbf\x2d\x13\x82\x88\x58\xdc\x90\x31\x95\xcc\xe9\xdc\x14\x6d\x43"
         "\x0c\x49\x22\x44\x8f\xae\xc7\xcc\x4d\xf8\x80\x38\xa1\xef\xdd\xfd"
         "\x4c\x6d\xac\xb1\xc8\x7e\xdf\x5d\x95\x3b\x34\xfe\xc5\xd9\x27\x22"
         "\xaf\xe6\xc4\xa5\x9c\x27\x99\xc3\x9b\x84\x2c\x8b\xcb\x39\xe2\xe9"
         "\xaa\x6d\x35\x7a\xb7\xa3\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20";
      static unsigned int write_00001_00000_len = 1028;
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
.*===rofl
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x66\x6c";
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
.*===mammillationpemphigous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x61\x6d\x6d\x69\x6c\x6c\x61\x74\x69\x6f"
         "\x6e\x70\x65\x6d\x70\x68\x69\x67\x6f\x75\x73";
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
.*===Carpathianmetanephron
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x43\x61\x72\x70\x61\x74\x68\x69\x61\x6e\x6d"
         "\x65\x74\x61\x6e\x65\x70\x68\x72\x6f\x6e";
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
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
