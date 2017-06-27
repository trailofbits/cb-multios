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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4b\x05\x49\x61"
         "\xe1\xaa\x4f\x18\x98\xfd\x12\xa3\xc5\xc0\xa0\xe2\xe4\x67\x10\x27"
         "\xa2\x00\x00\x00\x21\x84\x21\x5a\x3b\xe9\x6e\xd9\x32\xf1\x5a\x06"
         "\x33\x85\xf8\xb4\xd2\x9d\x4e\x50\x46\xf4\x62\x4e\x41\x3c\xf0\x50"
         "\x07\xa1\xd3\x77\xc3\xf3\xcf\x78\x27\x4a\x2e\x83\x71\x15\x1f\x10"
         "\xfc\xc6\xcd\x2a\x0f\x55\x0d\x95\x0f\x58\x3f\x71\x72\xb2\xab\x5f"
         "\x47\x3f\x09\x1d\x25\x2f\x11\xb0\x4f\xbb\x9e\xa4\xee\xc5\x0a\x57"
         "\xb0\x99\xa8\x84\x66\x51\x5d\x98\x32\x94\x37\x9c\xba\xc6\xd4\x3d"
         "\x61\x72\xa9\xa6\x7f\xa7\xd8\xd8\xdf\x87\xa7\xa2\x03\x46\x86\x24"
         "\x75\xe8\x17\xbe\xce\x7a\x9e\x25\xf6\x1d\x37\x5f\xda\xd0\xaf\xf9"
         "\x66\xd6\xd6\x93\xbf\x18\x27\xed\x49\x7b\x07\xc7\xb3\x83\x53\x79"
         "\xf0\x20\x69\x31\xc6\xb1\x4f\x6a\x3c\xf2\xf1\xaf\xd3\x9e\x76\xc7"
         "\xc8\x94\xa1\xeb\x81\xcf\x7b\xc5\xee\x35\x8a\xfe\xc1\xa7\x4c\xa3"
         "\x41\xc4\x19\x2f\x24\x20\x82\x99\x71\x60\xed\x98\x5f\x7d\xe5\xd3"
         "\x0c\xaf\x5c\x62\x38\x34\x7e\x5f\x9b\x67\x30\x0c\x14\x88\x0b\xda"
         "\x2b\x0b\x68\xf5\x44\x97\xb4\x58\x6b\x0b\x6f\x11\x80\xa6\xce\x93"
         "\x96\xfd\xe1\xd3\x37\x61\x44\xd1\x67\x71\xbc\x9d\x07\x18\x9c\xbf"
         "\x34\x20\xce\x79\xd7\x1d\x13\x4e\xae\x9e\x3e\x0a\x6f\x43\x20\xe3"
         "\x7f\xda\xb7\xfc\xba\xd4\x40\x01\xa9\xfa\x45\x9f\xc2\x86\x94\x4b"
         "\xc4\x03\xe1\xd5\xe9\x3b\x07\x8d\x5f\xa4\xe5\x35\xf5\x36\x59\x95"
         "\x3d\x42\x6d\x54\x72\x08\x74\xd6\x72\xca\xe9\x62\x7b\xdf\xc0\xe3"
         "\xb3\x24\xc2\x7c\x19\xed\xa2\x37\x13\x1c\x7f\xea\x6a\x4e\xfc\x6b"
         "\x4e\xae\x5b\x31\xb6\x16\xb7\x55\xa0\xea\x53\xb7\x96\x12\x48\x29"
         "\x79\x2f\xda\x85\xd9\xb3\x8f\xbd\x76\xbd\x91\x33\x34\x87\x4b\xf6"
         "\xab\x16\x52\xcf\x20\xe3\x8b\x98\xbd\x9f\xaf\xa3\x5a\x91\xfb\x49"
         "\x09\x07\xb4\xa7\x42\x68\x64\xfd\x24\xa5\x9c\xff\x9e\x51\x5c\xa1"
         "\x68\x20\xfb\x7f\xee\x23\xb3\x7a\x2e\x03\xad\x34\x83\x88\x01\xe1"
         "\x4d\x51\x9b\x91\xb3\xed\x8b\x6a\x30\x9e\x46\x5a\x51\xa2\xe2\x8c"
         "\xbb\x1a\x98\xb9\xe1\x14\x7a\x6e\x63\x40\xfd\x74\x1c\xf9\x17\xcf"
         "\xbf\xf6\x02\x04\x80\xf3\x0d\xd2\x71\xd8\x7c\x96\x26\x13\x9a\x82"
         "\x2a\xce\x72\xcb\xff\x57\x37\x08\xcb\x67\x7e\x52\x71\x91\xa6\xd6"
         "\xd8\x9f\x90\xad\x69\x36\xa2\xec\xef\x32\x6d\x61\x7c\x8e\xe5\x01"
         "\xc2\x69\xeb\x71\x24\x94\x0d\x8b\x04\xb6\x18\x54\x9d\x91\x41\x73"
         "\xc7\x8d\x61\x24\xaf\x44\x77\x0e\xef\x9c\xdc\x8f\xd0\xff\xae\xc3"
         "\x09\x90\xaa\xb9\x2f\x35\xb8\x6d\x37\xbb\x04\x0a\x11\x8c\xd8\x9c"
         "\x6b\xb0\xab\x7b\x8c\xfe\xc4\x1b\xd0\x40\x8c\x23\xd1\x9e\x68\xa1"
         "\xe0\x34\xee\x71\x47\x38\x80\xff\xa0\x35\x71\x91\xcf\xf0\x85\x65"
         "\x6a\xa9\x35\x52\x04\x89\x8e\xb2\x28\x8a\x0e\x54\xde\xb7\xe7\xbf"
         "\x15\xc4\x57\x41\x59\x7d\xc8\xb8\xb5\x2c\x4a\xa1\x34\x00\x6b\x0c"
         "\x6c\x0b\xe9\x5d\x96\xb9\x33\x64\x9f\x57\xdc\xed\xac\x71\x2a\x12"
         "\x21\x45\xcf\xcf\x05\x8d\x29\x65\xfd\x79\x15\x08\xe6\xd8\x8c\x7d"
         "\x6b\xea\x0f\x62\x6e\xcd\x42\xb8\x38\xee\x6e\x15\x9e\xe9\xee\x1c"
         "\x98\xa3\x12\x38\xbd\xd8\x04\xf6\x5f\x99\x35\x19\xdd\xf6\x73\x09"
         "\x62\xf3\x46\x6b\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===imperializetrispaston
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6d\x70\x65\x72\x69\x61\x6c\x69\x7a\x65"
         "\x74\x72\x69\x73\x70\x61\x73\x74\x6f\x6e";
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
.*===veldcraftsubprefect
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x76\x65\x6c\x64\x63\x72\x61\x66\x74\x73\x75"
         "\x62\x70\x72\x65\x66\x65\x63\x74";
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
