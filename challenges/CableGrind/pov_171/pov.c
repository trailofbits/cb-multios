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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xe2\xb4\x61\x49"
         "\xa5\x7e\x2f\xa4\xc5\xe0\x63\x4e\xc4\x01\x00\x00\x69\x05\x3c\x89"
         "\x55\x88\x57\x11\x14\xf9\x58\xf4\xa2\x07\xd2\x5f\xad\xd1\x1b\x8c"
         "\xb8\x15\xe8\x88\x60\x5e\x3f\x56\x30\x5d\x15\x3b\x09\x98\xb1\xee"
         "\x2a\x3a\x56\xbe\x6b\x0c\x25\x65\xe3\x78\xfa\xae\xc9\xc7\x02\x69"
         "\x59\x03\xd3\x8f\x5d\x39\x91\x71\x2e\xd5\xaa\x06\xf1\x4c\x09\x6c"
         "\x4d\xcd\x8f\x5a\x3c\x32\xa5\x42\x22\x58\x7b\x7d\xfc\xf6\x63\x91"
         "\xba\x71\xe2\xc7\x8d\x66\x63\xdd\xeb\x1d\xfe\x38\x08\xaa\xde\xbf"
         "\xa7\xdb\x5f\x7c\xee\xd0\xf8\x43\x01\x81\x06\x4e\x0b\x52\x19\x34"
         "\x30\x5c\x10\x85\x2f\xad\x30\x3c\x26\x8d\x24\xef\x3d\xe7\x71\xff"
         "\x33\x0a\xd6\x6f\x8d\x7b\x4a\x44\x39\xfc\xd7\xfc\x2c\x6c\x22\xb3"
         "\xed\x17\x4e\x87\x2a\xb3\x37\xa9\x37\x08\x36\xa5\x3c\x26\xea\x97"
         "\x19\x87\x22\xd5\x90\x36\x4b\x8f\x0b\x82\xd2\xdc\x59\xed\xd6\x06"
         "\xb2\x2c\x58\x0d\xca\x9c\xbe\x67\x97\x77\xff\xee\x19\xd7\x3b\x48"
         "\xc2\xbe\x86\x82\x5a\x04\xfa\xdf\x44\x45\xc1\xa4\x05\x47\x8e\x89"
         "\xcf\xfa\xc3\xe8\x45\x2a\xe5\x85\x1c\xb9\x5b\x6d\xd1\x30\x27\x11"
         "\x0d\x55\x18\x5d\xab\x7e\x50\xe5\x0c\xfe\xea\x80\x93\xea\xe5\x0e"
         "\x91\xd0\x1a\xa0\x54\x4c\x0e\x85\xc0\x58\x4e\x5c\x04\xfe\xd8\x0b"
         "\x31\x7d\xdd\x9b\xaf\xf7\x9d\x4e\xeb\xef\x1c\x40\xc2\x4c\x6c\xca"
         "\x48\x11\x31\xb5\x66\xf0\x45\x11\x3a\xd3\xf2\x15\x88\xd1\x55\x79"
         "\x3b\x4c\x0a\xe2\xaa\xe7\x78\x01\x8a\xc0\x8d\xbe\x39\x63\xcb\xcd"
         "\xec\x75\xcc\x0d\xf4\x30\xbf\x33\x71\x4c\x60\xf1\x30\xbe\xcd\x53"
         "\x27\x15\xa9\x1b\x92\xd1\x6f\x5d\xd9\x65\x05\x71\xfa\x2d\x8e\xe3"
         "\xd8\x05\xdc\x49\xa8\x99\x79\x45\x00\x9c\x58\x5e\x76\x54\x86\x8c"
         "\xb0\x8b\xe5\xe3\xc7\xd3\xb0\xa6\xe7\x6c\x96\x45\xbd\x37\x58\x3c"
         "\x0a\xe2\x87\xeb\xa4\xd1\xa6\x4e\x51\x07\xef\x0f\x6d\xa0\x11\x6f"
         "\x59\xaf\x65\x11\xc9\x9d\x60\xaf\x6b\x38\xdc\x31\xbf\x96\x85\xa5"
         "\xda\x28\x90\x41\xef\xdb\x09\xfc\xf8\x59\xa8\xa2\xb0\x62\xe9\xba"
         "\x09\x24\xd1\xde\xa6\xff\x4e\xe7\x09\x31\x17\xf7\x08\x72\x80\x16"
         "\x2e\x58\xe4\x8b\xc4\x8c\xd6\x6b\x62\xa7\xb7\xba\xe9\x5b\xc7\x23"
         "\x5a\x7b\x39\xae\xf1\x44\xe6\x7e\x37\xef\xea\x05\xcd\x7a\x01\x06"
         "\x38\x62\x0c\xdc\x25\xec\x4e\x08\xbc\xd3\xe5\xf6\xb8\xac\x0e\x58"
         "\x7d\xb1\xa8\x51\xc2\xd2\x89\xd2\x26\x58\x10\xc7\x82\xe2\xbd\x59"
         "\xb0\xea\xc3\xb2\x21\x05\x7e\xa0\xb7\x2a\xe2\xde\xa3\x5c\xa4\x48"
         "\x29\x4b\x11\x33\x42\xbb\x26\x0b\x08\x70\x4c\x23\xc9\x22\x00\x04"
         "\x64\x5d\xfd\x65\x82\xbf\x6d\x11\x87\x35\xe0\x98\x49\x2d\xf2\xc3"
         "\x90\xbf\xba\x4f\x2d\xbf\x35\x13\x0a\xe0\xe3\x9b\x39\xc2\xd1\x01"
         "\x86\xe1\xfa\x61\x8d\x75\xa9\xa4\x10\x36\xef\xd1\x1e\xc3\x3d\xcd"
         "\xde\x6d\xed\x83\x91\x31\x31\x66\x1d\x2a\xec\xb9\x8e\x09\x8d\xc9"
         "\x19\x21\x81\x37\xcc\x17\x2a\x85\x1c\x4a\x58\xfd\x88\x80\x49\x6d"
         "\x57\x65\x6b\x29\x5f\xe5\xbf\x3a\x3e\x96\x83\x90\x89\xfb\x05\x14"
         "\xeb\x43\xad\xda\x4c\xf8\xe0\xb5\x0d\xeb\xf8\xf1\x8b\xd1\x72\x9c"
         "\x7a\x88\xf1\x6f\xf9\xb2\xee\x98\xda\x23\xb9\x0b\x42\x38\x11\xbc"
         "\x3b\xd9\x5c\x52\xec\xeb\xf3\xe8\x22\xa5\xde\x8c\xc3\x26\x3b\x2c"
         "\x35\x97\x55\xc3\x66\x10\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===androgynyvegetoalkaline
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x6e\x64\x72\x6f\x67\x79\x6e\x79\x76\x65"
         "\x67\x65\x74\x6f\x61\x6c\x6b\x61\x6c\x69\x6e\x65";
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
.*===undercovertcoloss
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x64\x65\x72\x63\x6f\x76\x65\x72\x74"
         "\x63\x6f\x6c\x6f\x73\x73";
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
