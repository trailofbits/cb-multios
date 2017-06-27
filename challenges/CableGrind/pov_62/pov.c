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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x26\xeb\xdf\xd5"
         "\x1e\xe8\xbd\x53\x10\x83\x11\x6f\xc0\x7a\x76\x38\x5d\x32\xfb\x29"
         "\x52\x01\x00\x00\xb2\x08\x13\x5e\xe4\xd9\xef\xe7\xfa\x7e\x3a\xd0"
         "\xc1\x05\xc7\x16\x9f\xac\x9f\x8c\x52\x7f\xd1\x9a\xe1\xc8\xe9\xdc"
         "\x28\x52\xe2\x2f\xa9\x42\xcd\x88\x54\x07\x54\x80\xd6\x54\xea\x00"
         "\x12\xc4\x4d\xc9\xf1\x69\x55\x46\x93\xc4\xff\x5c\x5f\x1f\x12\x4d"
         "\xf0\xc5\xdc\xc1\xe2\xac\x50\xc4\x48\xc5\x8b\x7d\xb2\xe7\xd1\x85"
         "\x51\xd4\x2f\x3e\xd2\x17\xa4\x0d\x5c\xf0\xdc\x88\xd3\xe2\xc3\x27"
         "\x45\x77\x8a\x79\xbf\xde\xb4\x85\xaa\x14\x8a\x80\x16\x8d\xc2\x13"
         "\x5a\x20\x51\x54\xba\x6a\xc4\xdc\x9d\xac\x78\xbd\x13\xbb\x7b\xcb"
         "\x31\x2e\x56\x00\x6c\x0b\x48\xa7\xf4\x90\xce\xe7\x53\x36\x36\x9a"
         "\x68\x5b\xea\xee\x05\xae\x1a\x69\xcc\xce\x92\x41\x3b\x4f\x74\xf1"
         "\x21\xf2\x64\xed\x03\xee\xf6\x5c\xfe\xb9\x95\x58\x56\xe8\xb2\x22"
         "\x30\xe8\xff\xd0\xed\x77\xc7\x91\xfa\x56\xa5\x5f\x7c\x10\x6e\xf1"
         "\x6a\x12\xfc\x39\x76\xb0\xc7\x8f\x4a\xef\x8c\x59\x33\x69\x5a\xb6"
         "\xa3\xde\x9f\xa6\x0d\x0f\x5e\x3c\x97\x66\xb3\xaa\x1c\x88\x27\xa4"
         "\x14\x9c\xc7\x5c\x6c\x2f\x64\xa9\xc6\xa3\x88\xea\xd7\x57\xf6\xd6"
         "\x0e\x78\x30\x95\x90\xe1\x2c\x67\x47\xa0\x24\x97\x35\x46\x9c\xd2"
         "\x26\xff\xdd\xca\x32\xfa\xad\x0c\xd5\x01\x2c\x34\x61\x3d\xa4\x27"
         "\xc8\x64\x80\x2e\xed\x8b\x75\x6a\x95\x86\x0b\xf9\xca\x9c\xef\x50"
         "\xb7\x5e\xbb\x83\xda\xf9\x90\xb5\xf4\xf3\x7a\xcd\x70\x5a\xc8\xb9"
         "\x6f\x09\xdb\xd0\x95\x07\x16\xd4\x77\x94\xcd\xeb\x7b\xf9\x98\xb6"
         "\xb8\xe7\xf5\x06\x12\xd2\xab\x3e\xfd\x7b\xb4\x1c\xcc\x73\xe9\x81"
         "\x4f\x34\xe6\xb5\x82\xe3\x51\xea\xaa\xf8\xfd\x3a\x32\xd8\xbf\xc6"
         "\xc9\x36\xb9\xe6\xf8\x1a\xdd\x22\x44\x53\x43\xa4\x93\xf0\xbe\x74"
         "\x45\x1a\x77\x1e\x77\x2a\xd5\x67\x9a\xb6\x66\x0f\xba\xf6\x9c\x4e"
         "\xd3\xa2\x5b\xa4\xc0\x8d\xc7\x02\x50\x6f\xd7\x45\xe3\x59\x7f\xa7"
         "\x0b\x14\x8b\x59\xdb\x2f\x99\x9d\x4a\x0e\x79\xec\xdd\xad\x73\x03"
         "\x31\x62\x52\xfe\xd9\xb6\x54\xea\xac\x26\x16\x5c\xd3\xc5\x61\x6a"
         "\x14\x8a\x69\x99\xbd\x24\x76\xcd\x2c\xf3\xd1\xa4\x82\xc3\x8a\x0a"
         "\x46\xcf\x0b\x23\x6e\x51\xf9\xbf\x04\x80\x84\x36\x68\x93\x4c\x8a"
         "\x4f\xdd\x3b\xc2\xa7\x96\x31\xe5\xff\x33\xa9\xee\x5a\x1e\x21\x29"
         "\xf0\x5b\x45\x0f\x1d\xeb\xf9\xf0\x08\x3b\x7b\xa3\x24\xbd\x0f\x50"
         "\x1f\x83\x31\xd0\xc9\x19\x53\xe8\xd0\x4c\xe8\x1a\x9f\xba\xbe\xa3"
         "\xcc\x32\xd7\x55\xbb\x8f\xa1\x68\xce\xe1\x9b\xb7\x80\xf2\xac\x05"
         "\x7e\xab\x65\x63\x30\x9e\xfc\x48\x9f\x41\xa7\xe3\x88\xe8\x84\x65"
         "\x32\x0b\xa0\x28\x3b\x2d\x2d\x98\xfa\xb4\xde\x00\xdb\x54\x41\x27"
         "\x38\x5b\xa5\xf5\x55\x51\x06\xdf\x9d\x4a\xac\x73\xc8\x3e\x32\xaf"
         "\xac\xe9\x02\x15\x1b\xfd\x45\xe2\xd1\x08\x9c\x9d\x02\x4a\xc3\x2b"
         "\x96\x14\x06\x91\x0c\x4e\x67\xc7\x07\x3f\x8c\xef\x74\xd8\xe3\xb0"
         "\x7a\xaf\xe0\x10\x0d\x09\x6c\x82\x25\xd7\xc6\x99\x4e\x50\x45\xc6"
         "\xa3\xc3\x13\x9c\x0c\xc2\xd1\x30\x4a\x19\xf0\x9d\x2c\xde\x9f\xdd"
         "\x22\x8a\x58\x55\x38\x11\xce\xa6\xed\xf9\xe0\x1d\xe1\xee\xcf\x30"
         "\x16\x9c\x07\x71\x4a\xe3\x3a\xc4\x3d\x8f\x12\xf6\x6e\xac\x64\xb6"
         "\x79\xe2\x70\x0d\x0e\x7b\xfb\x50\x0f\xb3\xa5\xaa\xc3\xe6\xfd\x11"
         "\x3e\x0d\x48\xf2\x94\x5e\xe1\x08\x9e\xaa\xb6\x0c\xbd\x7a\x11\x38"
         "\x2d\x6b\xd9\xaa\xfb\xfe\x7a\x4d\x31\xa9\xfa\x66\x5b\xd4\x62\x66"
         "\x54\x2d\x90\x94\x58\xc7\x2d\x00\x55\xb2\x97\x7e\x75\x55\x94\x9c"
         "\x82\x9a\x62\xe0\x01\x49\x2a\x82\x3f\x97\xcc\x25\xf3\xc9\xb1\x65"
         "\xdc\xed\x76\x06\x18\xa6\x1d\xd5\xa5\xfc\x82\xd5\xa6\x09\xc5\x52"
         "\x42\x06\x2c\xdb\x25\xf2\xef\x36\x33\xbf\xeb\xdf\x29\x86\x69\x92"
         "\xf4\x83\x4f\x0e\x54\x01\xd5\xed\xd6\xce\x39\x51\x7f\x63\xc2\x9e"
         "\x0f\x4b\x98\xd3\x90\x8a\x6e\xed\x6e\x79\x2e\xbf\x63\xf4\x0a\xd0"
         "\x29\x1d\x19\x27\xd6\x9d\x92\x0e\x28\x30\xe9\xec\x0b\xfb\xdb\xe6"
         "\xa8\x10\x02\xc4\x18\xc4\x8d\xf2\x06\xf7\xb8\xe6\x8c\xd0\xc7\x11"
         "\x3d\x7a\x2f\xbf\x60\xed\x61\x89\x79\x61\x98\xf7\xb7\x20\x20\x20"
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
.*===Moorshipspermatova
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x4d\x6f\x6f\x72\x73\x68\x69\x70\x73\x70\x65"
         "\x72\x6d\x61\x74\x6f\x76\x61";
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
.*===pegologyscavenage
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x67\x6f\x6c\x6f\x67\x79\x73\x63\x61"
         "\x76\x65\x6e\x61\x67\x65";
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
