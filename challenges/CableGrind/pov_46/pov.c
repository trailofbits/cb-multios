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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xff\x1f\xd7\xb4"
         "\x0c\xb0\xab\x3f\x07\xe6\x36\xd5\xc5\x61\xbb\xcb\xfd\x8a\x3f\x87"
         "\x02\x01\x00\x00\x18\xb4\xb9\x87\xe2\xec\x3a\x6f\x9c\xae\x75\xd8"
         "\x31\x38\xf4\x35\xde\x29\x7c\x77\x61\x00\x7f\x61\x00\xaa\xf2\xc7"
         "\xa6\x1d\x6b\xa4\x8e\x5b\x86\x80\xe2\x37\xe8\x24\xc8\x1b\xe5\xdc"
         "\x50\xe3\xf4\x9d\x65\x08\x86\xd0\x97\xb2\x0e\x96\x73\xdd\x50\x77"
         "\x1d\xf7\x81\xa7\xcb\x35\x7c\x4d\xb2\xae\xa0\xff\xc5\x7c\xfa\xab"
         "\x7f\x10\xf6\xa4\x8a\x2a\xa5\xe5\x92\x64\x3e\x7f\x3c\x2a\x48\x1a"
         "\x5d\x70\xe1\x90\x02\xa2\xc7\x04\x76\xa7\x85\xd2\xfd\x52\x19\x63"
         "\xbe\x7e\xc3\x76\x52\xb7\xee\x65\xb9\x4a\x46\x9e\xad\x44\x9a\x62"
         "\x1d\x0c\x70\x77\xb3\x11\xcb\x56\x3a\x5f\x0e\xcf\x89\x5e\xda\xf2"
         "\x04\x00\x20\x7b\xde\x56\x07\xcc\x87\x2e\x2a\x5d\xe4\x40\xaa\x3c"
         "\x55\x19\x5c\x72\x43\x9f\x7d\x01\x6e\x94\x54\x26\x58\xbf\xf9\xfc"
         "\xe4\x43\x0f\xed\xb7\xcf\x79\x8f\x00\x95\xe3\xbe\x21\xd3\x6c\x9f"
         "\x2f\x5d\x01\xcd\xd5\xa9\x76\x85\x33\x1d\x77\x71\xa5\x32\x45\x7d"
         "\x13\x4c\xfc\x5a\x07\x95\xfb\x2c\x61\x26\x28\x09\x8e\x07\xbe\x97"
         "\xd8\x57\x03\x3e\x1a\x14\xc0\xbe\x55\xcf\xe0\xfa\x88\x3a\x69\x9a"
         "\xdb\xb8\xe4\x99\x94\xa5\x5f\x45\xc1\xf4\xb4\xfe\x8a\x96\xab\x7a"
         "\x15\x4b\x8f\xb9\xea\x42\x13\x3e\x4a\xc7\x20\xee\x73\x16\x34\xde"
         "\xe2\xb0\x65\xa9\xaa\xdc\x2d\x66\xad\xf0\xdb\x5e\x40\xdf\xda\xb9"
         "\x6a\x17\xee\x38\x01\xc4\xd0\xfe\x96\xb9\x97\x5e\x95\xe2\x76\x0f"
         "\x38\xb1\x18\x5c\x0b\x33\xbe\xcc\x0d\x96\x6b\xf6\xe6\x2b\x6b\x91"
         "\x50\xf0\x99\xf0\x92\xf1\x08\xd7\xeb\x0e\xc8\x50\x2d\xd3\xfb\xfd"
         "\xa5\x63\x03\xde\x8c\xee\x18\x53\xa7\x06\x69\x19\xe1\x52\x27\x1a"
         "\xb7\xf3\x22\x56\x37\x3b\x64\xa7\x1c\x53\x68\xac\xa8\xf0\x0a\x37"
         "\x28\x2f\xa2\x34\x32\x93\xb1\x61\x00\xff\x11\xcf\x48\x0c\x18\x18"
         "\xad\x30\xad\x61\x61\x00\x23\x4e\xe5\x77\x32\x55\xf3\x10\x9a\x5d"
         "\x96\x22\xb3\x09\x55\xa4\x95\x40\x48\xd9\xa7\x5e\xeb\x08\x65\x57"
         "\xa3\x36\x43\x79\xc9\xf0\x70\xa6\x22\x40\xf6\x77\x37\xf2\xb9\xa1"
         "\x23\xf6\xea\xe9\xfc\xd3\x77\x5f\x15\x97\xc8\x3b\xec\xdd\x7b\x5a"
         "\x40\xff\x17\x93\xdd\x8e\x76\x3c\x5a\xad\xb5\x6d\x00\x26\xba\x66"
         "\xab\xd9\xd4\x26\x95\xd3\xb8\xeb\x51\x87\xb1\x95\x90\x27\x9c\xb7"
         "\xf3\xdb\x4f\x86\x1f\x4e\x4e\xe9\x26\x12\xee\xfe\x4d\x10\xd8\x2c"
         "\xfb\xc7\x0e\xe2\xe0\x6f\x55\xcf\x1e\x1c\x0f\xb9\x23\x87\xf0\x3d"
         "\x3a\x09\x50\x23\xe0\xb2\x8f\xbd\x4a\xde\xe0\x16\xf0\xcb\x12\xe4"
         "\x1f\x16\x2a\x99\x89\x01\x3a\xc2\xf5\x8f\xdc\xff\x94\xee\x37\x54"
         "\x68\x94\x58\xa9\xd2\xa9\x2c\x95\x44\xb9\x98\xd3\x9d\x75\xc1\xe1"
         "\xd3\x21\x42\x3f\xa0\x7a\xb8\x15\xcd\x2c\x2d\xac\x87\xe7\x7a\x59"
         "\x4b\xc4\x05\x63\x3e\x6a\xd2\x31\xc9\xd6\xb8\x24\x2f\x48\x62\x1a"
         "\xff\x3c\xe9\xf3\xfa\x65\xac\xa6\x70\x60\x9e\x1d\x26\x51\x01\x48"
         "\x48\xd6\x6a\x7e\xcf\x96\x64\xb8\x36\x6c\x03\x86\xbb\x39\xa2\x26"
         "\xf9\xc0\x6d\x7c\x4f\xa1\x1c\xad\xf6\xad\x00\xf3\x29\x3d\x8d\x6a"
         "\x55\xc2\x25\x58\x61\x81\xaf\xf4\x50\xc8\x58\xba\x70\x0f\xce\xb7"
         "\xdd\x52\x19\x14\x0d\x7f\x66\x07\xc7\xcd\x2d\x5b\xf9\x00\xa6\x15"
         "\xea\x15\x15\x63\x8f\x99\xdc\xec\x63\xfd\xa9\x6c\x93\x35\xb4\xea"
         "\x89\x94\x50\x57\x0f\xc2\x86\xc6\xb7\x2f\xcd\xa5\x6f\x3a\x50\x6c"
         "\x52\xf1\x3c\x44\x54\xc2\xdd\xa4\x33\xc6\x33\xfd\xc7\x06\xab\xde"
         "\x47\x94\x5d\xf2\xf9\x1b\x23\xeb\x8b\xf6\x08\x68\xf2\xb2\xe1\x52"
         "\xdf\x3f\xa1\xd8\x6e\xc1\x7a\xfe\xf2\xde\x3c\x52\xe3\x1a\x75\x4c"
         "\x12\xb5\x37\xa3\x62\x21\x02\x47\x7a\x89\x1f\x21\x16\x4f\x91\x5a"
         "\x78\xd6\x25\x3c\xba\x50\xbf\x5e\x73\x88\x58\x2b\x63\xe6\xff\x34"
         "\x04\xdd\x86\xeb\xfd\xd5\xe6\x14\x06\xf6\xa0\xbb\x39\xa7\x8b\x10"
         "\xc9\xb7\xce\x2e\x89\xee\x14\x19\x66\x5a\x9a\x5c\x6f\x2e\xd5\xbc"
         "\x99\x74\x3b\x5b\x6e\x8a\xf2\x84\x4b\x6e\x25\x08\xb3\x12\x20\x20"
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
.*===semiduplexskirt
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x65\x6d\x69\x64\x75\x70\x6c\x65\x78\x73"
         "\x6b\x69\x72\x74";
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
.*===focoidsstackfreed
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x66\x6f\x63\x6f\x69\x64\x73\x73\x74\x61\x63"
         "\x6b\x66\x72\x65\x65\x64";
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
