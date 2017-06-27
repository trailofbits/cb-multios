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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xff\x9d\x72\x66"
         "\xd6\x4e\xbe\xf9\x25\x92\xaa\xec\x85\xf3\xac\xaa\x51\x54\xa1\x3b"
         "\x75\x00\x00\x00\x79\x67\x7b\x66\x37\xab\xfa\x16\x4e\x84\x86\x7f"
         "\x0d\x25\x0b\x5d\x2f\xae\xe2\xf4\x9f\x1d\x8f\x0c\xd3\x14\x7a\x72"
         "\xa0\x4d\x9f\x70\x8b\x00\x9a\x9f\x2f\x7b\x14\x96\x0b\x3e\x4a\x1d"
         "\xd4\xc3\x27\xe4\x46\xd5\x6b\x5e\x12\xdb\x5b\xcc\x45\x7d\xcd\xb1"
         "\x39\xd5\x84\x94\xa0\x85\xa0\x47\xeb\xb1\xa6\x31\xdd\xd6\x3d\x64"
         "\x74\xda\x61\x6a\x63\xe3\xfe\x0b\x1f\xac\xc1\xa5\xd1\xff\x42\xbc"
         "\xb0\xf7\x5b\x69\xc9\x82\xfd\x3c\xb5\xfc\xcc\xb2\xce\x71\xd9\x3e"
         "\x7e\x33\x52\xc7\x84\x26\xf6\xae\xc7\x6f\xc5\xb8\x79\x9b\xba\xff"
         "\x89\xb9\xcc\x2c\xf4\x5f\x7a\x37\xe8\x45\x20\x14\xd2\x1d\x25\x46"
         "\x4e\x00\x70\xce\x38\x18\xf6\x42\xbb\x37\x81\xc0\xa0\x41\x4e\xa5"
         "\xdd\x59\x5f\x5c\x0c\xe9\xdb\x78\xc6\x31\x49\x0b\x6c\x2c\x23\x9a"
         "\x67\x3d\x20\xfb\x9e\x91\xae\xe7\x3e\x13\x7c\xc2\x08\x25\x26\xac"
         "\x5a\x28\xca\xfa\x0c\x7e\xcc\xf5\xfa\x5d\x25\xdc\x6a\x10\x52\xfb"
         "\x12\x6a\xfd\x8c\x7e\xcf\xa3\x59\x4b\x71\x90\xcf\xe2\xf1\x69\xfe"
         "\x88\x5a\x8f\x9f\x98\x5e\xa2\xc7\xf7\xb9\xbd\x3f\x78\xc7\x1d\xd3"
         "\xe0\xbb\x70\x00\x96\x78\x57\x00\x2a\xff\xf0\xab\x87\x7a\xca\x6a"
         "\x6d\x87\x96\x46\xfe\x2d\xbe\xe4\x66\xd3\xe2\xe7\x44\xcc\xe0\x09"
         "\x06\x56\x66\x34\x78\x69\xb9\xbc\xaa\xd1\x80\xed\x99\x9c\x47\xc9"
         "\x0c\x5f\xce\x1d\x53\x5d\xee\x41\x4f\xd6\x4e\x42\x11\x24\x57\x22"
         "\x11\x31\x79\x65\x52\x3c\x6e\x49\x5c\x60\xeb\x2f\x09\x6c\x1f\xac"
         "\xd8\x77\xdd\x76\x8f\x05\xe2\x55\xcc\x12\xdd\x50\x50\x4a\x7e\xd4"
         "\x9e\xaa\xe3\xbb\xfb\x49\x3f\x6e\x1a\x01\xb8\xa5\x77\xfe\xcb\x65"
         "\x0a\x09\x70\x79\x67\xb2\xfa\xfc\xc6\xe7\x49\x2e\x7b\x98\xf5\x72"
         "\xa2\xb1\x96\xfb\x99\xb7\xfa\x1b\x7d\xe2\xd2\xa0\x32\x4a\x98\x77"
         "\x7d\xc3\x77\x1f\x12\x59\x11\x2e\xe6\x60\x58\xbf\x9f\x22\x36\x64"
         "\x76\x53\xa8\x98\x7f\xee\xbf\x44\x88\xc5\xe1\xd3\xd8\x1c\x46\x8a"
         "\x1c\x91\x8f\xc0\x2f\xd6\xeb\x6b\x68\x98\xd2\x43\xb8\xfd\x50\x8f"
         "\x7c\x60\xc3\xe5\x83\x36\x84\x7e\x89\x95\xd8\xae\xc9\x3d\x17\x8b"
         "\x3d\x0b\x58\x37\x2b\x65\x77\xbc\xb6\x2b\xe2\x03\x4f\xd6\x8f\x58"
         "\x49\x8c\x33\x07\x5a\x65\xde\xc4\x41\x65\xaf\xd1\xc2\x15\x76\x54"
         "\x27\xf6\x59\x12\x8d\xb9\xd2\x70\xbb\xa0\x22\x9b\x75\x4e\x06\x87"
         "\x51\xf6\xc8\x32\x5e\x43\x24\x8d\x6f\x1a\x3c\x62\x56\x5b\x2a\x4f"
         "\x7c\xcf\x53\x2b\x49\x9f\x16\x92\x81\x7e\x1f\x10\x55\x3a\xe8\x51"
         "\xac\xd7\xbb\x23\xf9\xd7\xf0\xb0\x2b\x73\x2e\x31\xed\x2c\x2f\x49"
         "\xbb\xe4\x64\xb7\xa6\x50\x91\xbd\xfc\x0f\xd0\xc3\xfb\x2f\x0e\xa0"
         "\x51\x4e\x36\x97\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===outwindowmesothoracic
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6f\x75\x74\x77\x69\x6e\x64\x6f\x77\x6d\x65"
         "\x73\x6f\x74\x68\x6f\x72\x61\x63\x69\x63";
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
.*===Fichteanismconjobble
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x46\x69\x63\x68\x74\x65\x61\x6e\x69\x73\x6d"
         "\x63\x6f\x6e\x6a\x6f\x62\x62\x6c\x65";
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
