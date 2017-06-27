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
         "\x01\x00\x00\x00\x01\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4f\x17\x0a\x24"
         "\x9c\x68\x6a\x22\x30\x4a\xec\x19\xfb\x00\x00\x00\xbe\x8f\xb0\xd2"
         "\xa1\x5e\xbc\x00\x29\xb7\xe8\xa9\x55\x0b\x66\x0c\xcd\xe2\x47\xd6"
         "\x25\x5f\x5a\x14\x90\x90\x58\xf3\xa7\x93\x01\x00\xbd\x01\xb6\xf0"
         "\x15\xc5\x00\xac\xab\x8f\xa0\x53\x6c\xa5\x54\xc6\xc0\x3a\xc1\xb2"
         "\x8a\x36\xa0\xd6\x09\x16\xb9\x5e\x3d\x4f\x8a\x8a\xbb\xec\x12\x49"
         "\xfe\x81\x56\x82\x28\xf9\xba\xd5\xb4\xd7\xf3\x8e\x71\x4c\x68\x29"
         "\x0c\x37\xb3\x70\x15\x07\xa3\xd3\x0a\x8c\x92\xaa\xfb\x64\x7a\x80"
         "\xf5\x38\x87\xdc\xa3\xcd\xa9\x05\xf3\x95\x50\xac\x90\x89\xbb\x70"
         "\xac\xe2\xb4\x64\x91\x3f\x6b\x08\xcc\x51\x2e\x07\x55\xa7\xb3\x39"
         "\x7e\x87\x86\xd3\xbb\x0b\xee\x0f\xe2\x12\x5f\x02\x4c\x1b\x23\xe1"
         "\xf6\xd1\x7e\xe4\x44\x97\x02\xf3\xab\x72\x8c\x7e\x25\x7f\x50\x05"
         "\xe7\x38\x2b\x32\x76\xdb\x3d\x18\x11\xab\x70\x0a\xc9\xd0\xd5\xa4"
         "\x9f\x34\x1b\x18\x72\xc0\xf9\x64\x82\xc5\xa1\x27\x46\x00\x98\x4c"
         "\x09\x77\xf4\x79\x56\xed\x02\xc1\x35\xae\xb5\x8e\x6e\xe9\xd6\x12"
         "\x9c\xda\xc6\x0c\x23\xbb\x21\x3a\x83\x33\xd0\xa6\x84\x0c\xc0\xca"
         "\xb5\xfd\x4d\x7a\x76\xc2\xa7\xa9\x76\x31\x35\xa7\x29\x41\xa7\x13"
         "\x59\x8e\x9f\x4c\x69\x67\xb8\x70\xca\x5f\xb8\xf7\x2e\xbe\x83\x46"
         "\x8f\x71\x43\x74\x37\x5c\xb6\xc2\x05\xa3\xcf\x67\xa3\x20\x5b\xb7"
         "\x94\xdb\x55\xee\xbd\x4b\x4f\xc4\x88\x19\x93\x62\x59\x02\x9b\x89"
         "\xcc\x9c\xe8\xcc\xa1\xe1\xea\xfc\xa0\x25\x08\xe4\xec\x47\x48\x21"
         "\x9c\xc8\x12\x7c\xd5\xbf\x09\x0c\xec\xb8\x44\x0a\xc4\xe4\x39\x25"
         "\x15\x6a\x1b\x0e\x75\x8c\x08\xe2\xae\x0b\x74\xee\xe3\x6c\x7a\xc8"
         "\xc6\x73\x97\x35\x35\x23\x76\x34\x2e\x36\xee\x91\x96\x05\xbf\x00"
         "\xb5\x38\x5b\xad\x84\x20\x2a\xf2\xea\x60\x70\x7f\x9a\x30\xc3\x15"
         "\xb8\x40\x25\xc1\x23\xa2\xde\xe7\x03\xe3\xde\x71\xa0\x49\x4b\xe6"
         "\xdf\x6e\x0b\xa4\x38\xa9\xf7\xe6\xc0\x35\xf1\xe3\x84\x31\xe4\x11"
         "\xcf\x75\x50\xd3\x9b\xcd\xb2\x52\xc8\x81\xa9\x64\x80\x89\xc8\x3e"
         "\xc7\xe6\x75\xb7\x47\x95\xe7\xeb\x06\xcd\xe1\xed\xfa\x91\xbb\x38"
         "\x90\x53\x3b\xca\xa3\xdc\xc0\x54\xf1\xbd\x8f\x36\x88\xd8\x4b\x48"
         "\x08\xe7\x9f\x4b\xf5\xb9\x42\xfc\xcd\xdb\x2a\xd6\xd2\x6f\xcf\x71"
         "\xe6\xcf\x4b\xe2\x0e\x4e\x96\x8c\x60\xac\x4f\x67\x1d\x0e\x0a\x85"
         "\x76\xb9\x52\x4d\x43\x73\x13\x0d\xd0\x2f\x10\x99\x66\x4c\x8b\xba"
         "\x05\x0d\x07\xd5\x42\xec\x37\x88\xea\x27\x0e\xb6\x12\x51\xda\xce"
         "\xbd\xb0\x89\x97\xf7\x8f\xa7\x7a\xf1\x42\xb0\x6a\xe7\xbf\xd5\x69"
         "\x75\x13\xd4\xfa\x68\x5f\xac\x3a\x78\x18\x6a\x9f\xaa\x73\x13\x51"
         "\x87\xf2\xa6\xa7\x54\x8f\x33\xa8\xb8\xac\x82\x7f\xf8\x6e\x87\x93"
         "\x5d\xb2\x02\x11\x41\x39\x2c\x54\x25\xcd\xc8\xfa\x5a\xa1\x2f\x25"
         "\xd6\xd3\xf2\xdb\x08\xbc\x88\x4e\x03\xd8\x26\x05\x21\xf0\x7a\xd9"
         "\x58\x89\x28\x20\x7f\x55\xbc\xa9\x79\x96\x51\x1c\x7d\x37\x79\x85"
         "\xfb\x91\x5d\x65\xf5\xab\x0f\xef\x7b\x93\x23\xa1\xa0\x18\xef\xe6"
         "\xcc\x42\x0f\xa2\x23\x67\x86\x90\x9a\x74\x70\x85\xa3\x07\x7c\x24"
         "\xb7\x55\xc2\x3b\x15\x41\xbb\x02\xa5\x23\x5f\xc6\x73\x02\x25\x13"
         "\xb1\x84\x32\xfe\xcb\x39\xf7\x7e\xc5\xf8\xa9\x6c\xbe\xbf\xa1\xc2"
         "\xc7\xa6\x39\xb2\x48\xdd\x18\x70\xd7\xb1\x3c\x34\x0a\x01\xfa\x32"
         "\xd1\xdf\x3c\x7d\x1d\xab\x63\x87\x80\xdf\x59\xb6\x52\xc5\x6e\x36"
         "\xbf\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===lol
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x6c";
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
.*===cineplastyanonang
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x69\x6e\x65\x70\x6c\x61\x73\x74\x79\x61"
         "\x6e\x6f\x6e\x61\x6e\x67";
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
.*===dermobranchiataboyardom
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x64\x65\x72\x6d\x6f\x62\x72\x61\x6e\x63\x68"
         "\x69\x61\x74\x61\x62\x6f\x79\x61\x72\x64\x6f\x6d";
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
