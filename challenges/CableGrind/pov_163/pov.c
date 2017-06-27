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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4d\x06\x7a\x46"
         "\x6f\xec\x1e\xa3\x7e\xbf\x50\x77\x8f\x01\x00\x00\x45\x34\x77\xa1"
         "\xd5\x26\x40\xb6\xc7\xee\x57\xe2\x14\xb8\x1c\x64\xe5\x3d\xdd\x38"
         "\xae\xfd\x74\xca\xdd\x1e\x82\x6e\x5d\xf5\xdf\x18\x03\x17\x75\x97"
         "\x99\x90\xf1\xeb\xc2\x54\xb6\x55\x15\x59\xcd\xd2\xf5\x58\x4a\xba"
         "\x06\x5c\x66\xbb\x43\x29\x3f\x6b\xd4\x89\xe7\x3e\x54\x25\x98\xf1"
         "\x84\xd9\x5c\x3e\x10\xd9\x43\xf6\x62\xfd\x4d\x28\xf7\xf7\x10\xd6"
         "\x5d\xeb\x69\xa6\x5f\x25\x75\x4b\x4a\x36\x8b\x1c\x15\xbe\xa8\x9d"
         "\x88\x41\x9f\xc5\x74\xd2\x86\x9c\xf2\x61\x0f\x55\xde\x5a\x68\x91"
         "\x70\x75\x48\x73\xe8\x04\x48\xc8\x25\xcb\x31\x7e\xc9\xb3\x63\x18"
         "\xa3\x6c\xe6\xa3\xd3\x11\x12\xd2\x60\x97\x11\x60\x4c\xbd\x24\x4f"
         "\x26\xd1\x71\x85\xa4\x11\xc1\x05\x03\xb3\x82\xeb\xe1\x0f\xce\x25"
         "\x57\xd7\x75\x04\xe0\xda\x95\x9d\x7e\x00\x5b\xaf\x53\xf1\x33\x49"
         "\xc2\x0d\x31\x98\x42\x9d\x2e\x81\xee\x9a\xdb\xf9\x36\x26\x17\x58"
         "\x6e\x4a\xaf\x09\xf8\xc7\xdf\xee\xcd\x89\x06\x4b\xb9\xaa\xff\x6d"
         "\xa0\x16\x6d\x80\xb8\x59\x97\x6d\x24\x28\x94\xd8\x84\x66\xf4\x46"
         "\xda\x4d\x50\xa4\x97\x81\xa2\xa1\x06\xc1\xa1\x30\x75\x8c\x09\x06"
         "\x27\x95\x4c\x99\xe3\x26\x8d\xa2\xaa\xcd\xe1\xe7\xe2\x60\x53\x1b"
         "\x34\x36\xfd\x4f\x1e\x80\x4d\xac\x84\x95\x88\x89\x2c\xc2\x83\xc3"
         "\x9e\x62\xe1\xd9\xe6\x5a\x53\x2e\x02\xea\xe4\xfe\x13\x68\x70\xe6"
         "\x6a\x33\x97\x3f\xc6\x4a\x24\x7e\xe4\xd2\xf0\xb8\x8b\xb6\xd3\xf6"
         "\x15\xf2\xcd\xa3\xab\x03\x8d\x11\x72\x98\xb3\x30\xc9\xf0\x94\x01"
         "\xcb\x43\x68\x30\xdf\x82\xcc\x3e\x34\x49\xeb\xfa\x08\xf5\x2e\x32"
         "\xff\x8d\x65\x66\xf6\x7d\x0e\x53\x3a\xb9\x87\x38\x32\xd4\x16\x48"
         "\x7a\x20\xca\x54\x79\x9b\x15\xb0\x05\x21\x10\x0c\xa3\x83\xd8\x41"
         "\xe5\x95\xdb\xb0\x0d\x8e\x27\xad\x47\xf4\x27\x23\xb0\x95\x01\x51"
         "\xbd\x0c\xa3\x7b\xb2\xfc\xf0\x56\xdf\x91\xa5\xb2\x95\x04\xb1\x10"
         "\xdc\xa8\x9e\x4d\xfc\xc5\xba\x08\xe4\x74\x2f\x6e\xa5\x8b\xcd\x48"
         "\xbf\x62\x12\xee\x5b\x88\xf5\xe6\xc8\x47\xc0\xd2\xb4\x4d\x9e\x3c"
         "\xf1\x7e\x57\xc1\x11\x16\xf4\x25\x28\x78\xec\x91\x69\xe6\x3d\x74"
         "\xea\x0d\xc1\xcc\xec\x0c\xb6\x15\x2d\xe1\x66\x17\x03\xaa\x87\x85"
         "\x13\xb3\x55\x90\xfc\x66\x90\xf9\xa5\x9d\x58\x2a\xd4\xa6\x05\x00"
         "\xe2\xd9\x53\x0e\xe1\x82\xc7\x5f\xb9\x55\xfa\xb2\xd7\x4d\x29\xf8"
         "\x01\x63\xa2\x76\x35\x8d\xa7\xa5\xbf\x5f\x51\x4a\x78\xcd\x5b\xf8"
         "\x20\x22\xeb\xc3\xec\x87\xaf\x27\x17\x5d\xd7\x33\x21\x7b\x81\xe6"
         "\xe5\x74\x14\x6e\x83\xc2\x2e\x7e\x06\xd2\x05\xc5\x95\x02\x28\x3c"
         "\x52\x64\x7e\xf1\x15\x40\xed\x91\x6b\x59\x49\xea\xbe\xdc\x31\x2e"
         "\x2d\x15\xa0\xe9\xdd\x73\xd7\x7f\xf6\xd7\xfa\xc9\x3b\xb7\xa4\x50"
         "\x58\x6e\x0c\xed\xe4\xeb\xab\x95\xc5\x5a\x2d\x42\x8a\x40\x63\x70"
         "\x47\x9d\x16\xd7\x4f\x61\x38\xaf\xd3\x56\x62\xef\x4f\xcd\xe9\x0d"
         "\xe9\xf0\xc0\xd1\x9a\xa6\xfe\x95\x30\xaa\x2e\xf3\xc9\x13\xaa\xcf"
         "\x4b\x2b\x5e\x1a\xea\x04\xa4\xca\x4d\x20\xd5\x6a\xc5\xd6\xf3\x7d"
         "\xe4\x60\x92\x2c\xf7\xb1\x1f\xf0\xf6\x21\x62\xaa\xa5\x07\x88\xdb"
         "\xea\x76\xa7\x8f\xff\xf8\x0c\x48\x9a\xde\xfb\xfb\x1e\xd5\x09\xc5"
         "\x8b\x12\x95\x0c\x5c\xa1\x26\x0b\x9c\xb4\xdc\xe6\x1d\x1e\x40\xc3"
         "\x8f\x15\x98\x11\x69\xe4\x63\x15\xc4\x29\x0c\x58\x05\x93\x63\xaf"
         "\xee\xc8\x2e\x28\x67\x68\x9f\x79\x3a\x59\x87\x62\xf5\x7c\x6c\x81"
         "\xed\xcb\x06\x41\x4d\x37\x7a\x50\x51\xfa\x3f\x11\x99\x1b\xb1\x7c"
         "\x16\x63\x1c\x10\xa0\xab\x14\x60\x39\x10\xf7\xc4\x3e\x12\x9a\x1e"
         "\x40\xcc\x00\x10\xb8\xeb\xe3\x2b\xba\x27\x79\xf8\xb6\xe7\x51\x8d"
         "\x34\x43\xac\x60\xb6\x51\x6a\x41\x26\x9c\x4b\x8d\x58\x3c\x53\x7c"
         "\x0f\x72\xcf\x63\xb9\xaf\xff\x76\x21\xab\x96\xc7\x18\x13\x6d\x5c"
         "\xd1\xdb\xb4\x6e\x3e\xa1\x44\x84\x1f\xcb\x3f\x26\x77\x0c\x92\x07"
         "\xf3\x96\xf2\xe0\xfd\xdd\xc0\xe5\xc1\x63\x69\x3d\x00\x0b\x64\xb0"
         "\xc5\x04\x32\xb0\x82\x3d\x00\x8c\xb6\x43\xcc\xee\xd6\x8d\x1c\xde"
         "\x89\x3b\xd4\x59\x28\x32\x05\xff\xe6\x2d\x69\x52\x78\x39\x32\xaf"
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
.*===indubitablenoncollaboration
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x64\x75\x62\x69\x74\x61\x62\x6c\x65"
         "\x6e\x6f\x6e\x63\x6f\x6c\x6c\x61\x62\x6f\x72\x61\x74\x69\x6f\x6e";
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
.*===pedestrianateStromateidae
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x64\x65\x73\x74\x72\x69\x61\x6e\x61"
         "\x74\x65\x53\x74\x72\x6f\x6d\x61\x74\x65\x69\x64\x61\x65";
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
