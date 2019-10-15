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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb3\xcf\xb3\x0c"
         "\x2d\x39\x04\xe6\x4a\xc0\xab\xce\x8d\x9c\x7d\x6f\xc2\x15\x7a\x5a"
         "\x66\x00\x00\x00\xdb\x1b\x0e\xfb\x79\xc0\x69\x37\xdb\xc6\x41\xef"
         "\xf3\xb8\x6e\x67\x0d\x54\x45\xc3\x32\x91\x07\x8e\x79\x36\x69\xef"
         "\xe0\x0a\xee\x05\x97\xf4\x48\x41\x8c\x60\x86\xac\x02\x9a\xf4\x3c"
         "\x63\xe0\x59\x39\x75\x56\xd2\x05\x40\x5f\x85\x00\xf8\x7d\x7f\x2f"
         "\xfc\x84\xfa\x5c\x15\x39\xfa\x38\xde\x67\x15\x70\x40\x4f\xc8\x1e"
         "\xe3\x75\xb8\x9a\x2b\x09\xb3\x31\x49\x9d\xea\xac\x2e\x38\x62\xb4"
         "\xbd\xad\x6a\xb4\x49\xc2\x16\x79\x28\x9f\x23\x12\x07\x2c\xa8\x65"
         "\x43\xda\x93\xfc\x39\x43\x23\x3c\x66\xaf\xd5\x97\x97\xeb\x53\xbc"
         "\x1a\xfa\x91\x87\xac\xeb\x10\x0c\xd2\x68\x76\x1d\xec\x74\x5f\x7e"
         "\xaa\xcd\x88\xc8\x18\x7b\x9e\x1a\x90\x32\xd2\x84\xf2\x46\xec\xbc"
         "\xe6\x15\x0d\x0c\xd6\x6c\x87\x4b\x7a\x55\xa8\xfa\xf6\x2b\x04\x12"
         "\x0d\xb6\xdb\x0e\x9c\xcb\x00\x52\xe0\x3a\xe9\xd0\xdb\x6a\xd0\x17"
         "\x66\x69\x53\xb0\x2b\x2c\x33\x9f\x0b\x2b\x07\xa7\x28\x9e\x04\x5a"
         "\x65\x6a\x5f\xf4\x66\x91\xac\xf9\xc7\xa0\xbb\xc3\x97\x30\x8c\x5c"
         "\xc4\x3b\xdf\x53\x5f\xf6\x7d\xe6\xc3\x8d\x01\x3a\x06\x46\xa3\x65"
         "\x7f\xac\xb0\xc2\x9e\x54\x26\x00\xa1\x08\x26\x10\x6c\x8d\x7b\x6b"
         "\x41\x7c\xef\x4c\x0a\x5d\x04\x19\x73\x5e\x85\x38\x9a\xe2\xcc\x3e"
         "\xfb\x36\x8d\x08\x65\xa2\x5d\xe5\xa9\x8f\x84\x4b\xfd\x00\x45\xc5"
         "\x0b\x1e\xb1\xaa\xc8\xf1\xe6\xde\x48\xea\x2e\x72\x49\x50\x9e\x57"
         "\xb4\xb1\x3a\xba\x90\x93\x31\xee\x9f\x7d\x9c\x22\xdc\xf0\x1d\x61"
         "\x8f\x04\x1b\x3f\x77\x7e\xe0\x85\x5e\x3f\xd7\xee\x85\xb0\x95\xfc"
         "\x71\x2e\x1f\x59\x54\x84\x44\x42\x2c\x37\xe4\xd4\x3b\x14\x5c\x61"
         "\x1c\xfb\x40\x25\x76\x8e\x43\x02\xa8\x99\x32\xe5\x15\xfa\x56\xb2"
         "\xf4\x4e\x27\xa8\x8f\x6b\xd0\xd0\xc1\xb8\xce\xe4\xd5\x0c\xda\x50"
         "\x52\xaf\x78\xf0\xbc\x18\x73\x72\x01\x2e\xb3\xac\xe0\x8a\x75\xf7"
         "\xda\x02\x26\x68\x42\x10\x7b\xbf\xc9\x4b\xbe\x30\xb8\x2c\x48\xcc"
         "\x21\xf7\xb5\xa4\x32\x23\xfd\x8a\xb9\xcd\x3f\x7a\x2d\x1c\x13\xa3"
         "\x72\x16\xa5\x4d\x30\x8a\xbc\x43\x07\xce\xdf\x11\xaf\x4b\xec\x34"
         "\xda\x4d\x55\xcf\xa1\x79\xbb\x8f\x73\xaf\xd3\x4d\x98\x29\x53\x08"
         "\x9d\xa6\x2a\x03\x6b\x8d\x4e\x33\xed\xcb\x60\x71\xf4\xd7\x87\xcd"
         "\xb4\xb9\x29\xcc\x4a\x6f\x41\xa6\xc7\x24\x3d\x70\x4b\xe6\x3c\x32"
         "\xdf\x13\xc7\xdb\x9c\x9d\x2e\xfa\xb4\x55\x2f\x2b\x26\xea\x5a\x92"
         "\xa5\x22\xec\xc1\xa7\x77\x8e\xc0\x00\xcd\x91\xe3\xc2\xfb\x32\x5f"
         "\xaf\x7a\xfe\x89\x95\xf1\x4d\xe1\x1a\x1f\x0b\xb9\xa1\xb1\x21\x4a"
         "\xc2\x77\x6d\xea\xa0\x50\xd0\xee\x78\x82\xe4\x3a\x7d\x3b\xd7\x63"
         "\xc6\x6f\x9e\x6f\xd0\x4a\xc6\x58\xad\x93\xdc\xff\x12\x16\xd4\xa6"
         "\x7e\xe8\x43\x2d\x87\x35\x07\xde\x3e\x4d\x77\xbf\x30\xa4\xeb\x10"
         "\x0e\xb0\xec\x3a\x82\xe2\xa2\xe2\x62\x17\xca\x7b\xeb\x96\xb9\xeb"
         "\x08\xd5\xda\x95\xed\xcf\xec\xa2\x47\x7b\x7d\x2e\xda\xfa\xd9\x49"
         "\x78\xe4\x2a\x1d\x29\x1d\xa2\x61\xaa\xc1\x91\x4c\xcb\x16\x3a\x2a"
         "\x9d\xf7\x3a\xa9\xd8\xf6\xc1\x72\x41\xd9\xd2\x62\x67\xa9\x79\x51"
         "\x73\x4e\xeb\x20\x08\xa8\x37\xc8\x5e\xc4\xc3\x03\x00\x73\x89\xfd"
         "\x04\x5e\xdc\xec\x3b\x62\x2e\x7f\x25\xcf\x3b\x04\x43\x24\x83\xcb"
         "\x1d\x0d\x4d\x4f\xd4\x7c\x5f\xdf\x02\x3e\x75\x98\x8b\x22\xcc\xa0"
         "\xba\xaa\x4b\x84\x3f\x7e\x58\x75\x09\x07\x9c\x52\x76\xdc\xf3\x45"
         "\x66\xf3\x8c\x51\xfe\x7d\x45\xb5\x69\xf2\x0b\xc7\xa6\xf0\xa1\xf0"
         "\xab\x28\x4d\x37\x02\x23\x0d\xbd\x5f\xf1\xdd\x45\x03\x96\x30\x9b"
         "\x4c\xa9\x60\xd4\x4a\xda\x30\x5c\x21\x2e\xc6\x7e\x37\x9c\x94\xe6"
         "\x0f\x5b\xe8\x44\x83\x22\xf8\xf8\x06\x83\x85\xdc\x73\xaf\xe4\xea"
         "\x94\x7d\xde\x29\x7f\x78\xa6\xd1\xb8\x87\xd1\x17\x16\x03\xb2\x88"
         "\xa6\xc4\x7d\xfc\x40\x6d\xb1\x9b\xb7\x36\x34\x87\x48\xe2\x2f\xb2"
         "\x49\x29\x04\x29\x3b\x34\x0f\x22\x5c\xae\x2e\x47\x91\xec\xc3\x4d"
         "\xb5\x83\x98\x88\x93\x4c\x2b\x72\x99\xba\x55\x56\x9b\xb7\x80\x45"
         "\x35\x7d\x55\x27\x72\x70\x6e\x90\xfb\x05\x95\x09\xf2\x8b\xf1\x81"
         "\xe7\x4f\x46\x6a\x76\x84\x0f\x43\x3a\x6c\xe3\x32\x96\xf7\x71\xde"
         "\x82\x73\x04\xfe\x52\x95\x31\x07\xdc\xc8\x90\x9e\xca\x7c\x8e\x8d"
         "\x65\xfd\x7d\x3a\xc9\xc8\xd6\x78\xae\x3f\x3f\x12\x49\xbc\xb2\xd0"
         "\x76\x7a\x62\x0d\x9d\xde\xd2\xae\xbb\xe6\x84\x33\x40\xf1\x2c\x59"
         "\xe5\x01\x7f\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===acanthopterygianMuranese
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x63\x61\x6e\x74\x68\x6f\x70\x74\x65\x72"
         "\x79\x67\x69\x61\x6e\x4d\x75\x72\x61\x6e\x65\x73\x65";
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
.*===tecalipalingenesy
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x65\x63\x61\x6c\x69\x70\x61\x6c\x69\x6e"
         "\x67\x65\x6e\x65\x73\x79";
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
