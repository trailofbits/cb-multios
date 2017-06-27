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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x26\xac\x12\x15"
         "\x7b\xad\x7f\x1d\x7e\xd0\xeb\x72\x6c\x00\x00\x00\x14\x56\x20\x01"
         "\xcc\x51\xfe\x30\x54\x8a\xdb\x78\x94\x55\x9d\xb3\xb6\x3d\x77\x15"
         "\x7b\xe8\x10\x85\xb8\x56\x38\x1f\x1c\x2e\x57\x66\x00\x96\x96\xe9"
         "\xc2\x99\x97\x51\xdc\x23\x7a\xe6\xb1\xf0\x7e\xca\x38\xe3\x43\x64"
         "\x40\xc4\xc4\x29\x6a\x53\x35\xca\x58\x02\xd0\xf6\x55\x83\xac\x1e"
         "\x61\x2e\x76\x2c\x69\xd1\x93\xb0\x65\xe6\x68\xb5\xea\xcc\xc6\xfa"
         "\x57\xec\x02\x87\x53\x9b\x20\x14\x14\xaf\x80\x10\xc9\xa3\xe9\x86"
         "\xe8\x9f\x2b\xe3\x2e\x49\xb2\xa0\x1d\xf6\x50\x3e\x17\x20\xbc\x9c"
         "\x0c\xfd\x54\xba\xe8\xf4\x9f\x34\x5b\x18\xf1\x95\x20\xfb\x98\x11"
         "\x4c\x39\x45\x04\xd1\x7b\xb5\xc4\xf5\x8d\xb1\xcb\xd9\x2f\xb2\xb8"
         "\x69\xc7\x1d\xe6\x3a\x25\x1e\xbd\x2a\xa3\xa7\x4b\x71\x2c\x9c\x8b"
         "\xcd\x8d\xd6\xef\x50\xd7\x52\x66\x6b\x92\xa9\x68\x38\x5b\x69\xcc"
         "\x54\x2f\xfc\x6d\x70\x45\x78\x65\x0a\x86\x6c\xd5\x73\xed\x04\x65"
         "\xf3\xc1\x0a\x40\x6c\x68\xed\xbe\x22\x1e\x38\x93\xc1\xb8\x1c\xce"
         "\x03\x52\x6e\xda\x47\x35\xff\x60\x11\x35\xf0\x26\x1e\x73\x8a\xea"
         "\xf5\xe0\xfe\x70\xed\x8e\x1a\x0b\x22\x37\xd8\x04\xdc\x4e\x0d\xfd"
         "\xb8\x08\x81\x83\xb0\x44\x0c\x87\xcd\xec\x1b\x8a\x14\x62\x34\x36"
         "\x68\x07\xa4\x5b\x30\xfe\x42\x8c\xa6\x45\x45\xd8\xeb\xdc\x37\x07"
         "\xe7\xdc\x38\x1a\x2e\x45\xa7\xde\x3c\x43\x15\x04\x20\x2b\x79\x0a"
         "\x32\x73\x2c\xf2\x94\xfe\x47\xd8\x85\x58\x8a\x3f\x47\x9e\x25\x32"
         "\x0f\xe2\xb5\x54\x4b\xa5\xf4\xa8\xd1\x77\x17\x0d\xb3\x44\x4b\x08"
         "\xe5\x80\x85\x0c\x32\x70\x8b\xa4\x46\x45\x47\x61\x67\x74\xc9\xca"
         "\xef\xe9\x86\xcd\x8b\xb8\x82\x71\x2d\x21\xdc\xbd\x80\xe1\xee\x45"
         "\x00\x94\xb3\xce\x2a\xe5\x62\xc9\xc8\x44\xf0\x73\xec\x30\x56\x45"
         "\x4a\x17\xd0\xbc\x11\x63\x84\xb6\x45\xd0\x29\x69\x18\xdc\x6c\x6b"
         "\x47\xee\xc7\xd8\xa7\xef\x9d\x5c\xab\xeb\xaf\x61\xbb\x70\x30\xd6"
         "\xdb\x28\xeb\x47\xfe\x9f\xfb\x78\x56\x30\xdd\xa6\xd5\xf2\x33\x6b"
         "\xe9\x6e\xc0\xb7\x8a\x51\x6d\x44\xd4\xc7\x1f\x5e\xc4\xe7\xd3\xca"
         "\xe2\x8f\x7d\x0e\xde\x2a\x5c\x21\x20\xeb\xcf\x1a\x7c\x48\xd6\x0a"
         "\x5c\xe7\x0e\xaa\xfe\x69\x34\x02\x24\xd4\x9c\x05\xbf\x20\xb7\xf8"
         "\xc2\xec\x50\xdc\xd2\x01\x82\xec\xfb\xbc\x9e\x51\xfc\x6b\x7b\x27"
         "\xe9\xb5\x51\x04\xd7\x41\x4f\x1d\x23\x5c\x18\xb4\xeb\xb7\xed\x9f"
         "\x94\x63\x1b\xc2\x40\xc9\x1b\x7f\x79\x3e\x44\xc9\xb4\x73\xcc\x4a"
         "\x4e\xc6\xea\x09\x11\xa7\x96\xb2\xc9\x1e\xd7\x9e\xeb\xe4\xeb\x3a"
         "\x0d\x5f\xdd\xc4\xa2\xd2\x88\x03\xc2\x37\xe6\x68\x02\x77\x94\x29"
         "\x89\xe8\x3f\xc6\x1c\x9a\x13\x10\xed\x7f\xbc\x12\x90\x86\xb0\x70"
         "\x1f\x37\x54\xde\xda\x4b\x1b\x5f\x6b\x26\x73\x0c\xff\xac\x6c\x07"
         "\x9d\xb3\xb5\x7c\x6c\xb7\x6f\x6a\x6b\xa6\x47\xde\x20\x05\xc5\xc6"
         "\x07\x45\xbf\x26\x64\x8c\xf7\x58\x8d\xfb\xda\x4a\x56\x99\xce\xb0"
         "\xf2\x1e\x5f\xe7\xb5\x32\xaf\x34\xc9\x69\x76\xf8\xdd\xe6\x83\xd0"
         "\x4b\xdc\xbe\x51\xb6\x08\x53\xd0\xb9\x35\x1c\x20\x20\x20\x20\x20"
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
.*===micrencephalypalpus
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x69\x63\x72\x65\x6e\x63\x65\x70\x68\x61"
         "\x6c\x79\x70\x61\x6c\x70\x75\x73";
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
.*===intrathoraciccoemployment
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x74\x72\x61\x74\x68\x6f\x72\x61\x63"
         "\x69\x63\x63\x6f\x65\x6d\x70\x6c\x6f\x79\x6d\x65\x6e\x74";
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
