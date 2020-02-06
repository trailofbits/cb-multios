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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x0d\x35\x9a\xfd"
         "\xa7\xcf\x3f\x1f\x7a\xba\x41\x0c\x81\x01\x00\x00\x18\xfa\x3c\x93"
         "\x41\x4e\x4c\xed\xe0\xbd\x5a\x9d\xf3\x7e\x05\x9a\x22\x0f\x54\x24"
         "\x92\xe2\x93\x0b\x22\x8e\x7d\x54\x00\x4d\xea\x77\x0b\xc0\xb2\xd3"
         "\xe8\x1a\xfa\xa3\xa4\xcf\x04\x4d\x3a\xc5\x59\x41\x1b\x1d\xc2\xe5"
         "\xd2\x93\x86\xef\x93\xe8\x23\x69\xd4\xaa\xb9\x4a\x9d\xeb\xf8\x72"
         "\xa5\x79\xf9\x43\xcc\x13\x83\xe1\xc0\x18\xa1\xf2\xca\x12\x8b\x22"
         "\x9c\x13\x3d\x28\x57\x16\xec\xd8\x76\x64\xde\xec\xdb\xc0\x0c\x06"
         "\xfc\xfa\x14\xfe\x8a\x39\x32\xf1\x3c\x93\x20\xbd\x05\x56\x4e\x0a"
         "\xb9\x1b\x87\x64\xbd\x75\xd7\x91\xd1\xba\x11\x92\xdb\xd2\xde\x19"
         "\x18\xdb\x47\x4b\x76\x2d\x54\xd6\xb9\x1f\xd8\x67\x11\x01\xba\xb9"
         "\x2b\xcf\xda\x95\xc1\xec\x41\x48\x98\x37\x1e\x6b\xae\x54\x78\x00"
         "\xd3\x66\x86\x90\x53\x54\x00\xaa\x39\x07\xdd\x94\x45\x4f\xd1\x14"
         "\x54\x77\x6b\x7c\x54\x00\x14\x90\xd7\xf4\xb1\x9f\xf1\x8a\x84\x43"
         "\x20\xb6\xec\x73\xfe\x20\xf5\xd3\x22\x22\xef\x3f\x2d\xad\x3f\x88"
         "\x9e\x21\xa8\xcf\x39\x37\xff\x49\xc3\xad\x06\x78\x17\x52\x01\xca"
         "\x56\x69\x27\xda\x38\x6b\x06\x96\xcf\xf2\x50\xf8\xf1\xd3\xa0\x40"
         "\x25\x67\x72\x42\x07\x8c\xab\x78\x07\x57\x04\xc6\x4c\x73\x0d\x80"
         "\x05\x80\x1f\x50\xd9\x23\xf6\xbf\x73\x25\xc1\xe5\xae\x21\xdd\x33"
         "\xc7\x9a\x5c\x10\xbb\x6e\xde\xd3\x90\xad\x86\xfd\x1b\xcb\xe6\x46"
         "\xbd\x2a\x4b\x00\x58\x61\x4e\xa0\x1b\x25\xcf\x2b\x06\xf5\x30\x65"
         "\xdd\x84\xf0\xc3\xa5\x8c\x9f\x87\xb4\xad\x5c\x0a\x6a\xe7\xb4\xd9"
         "\x68\x03\x19\x7c\x72\xa5\x84\x56\x32\x13\x41\x21\x66\xb5\xc2\xed"
         "\xb6\xef\xfb\xaf\x22\xd7\x8b\x7d\x9f\x2a\x28\x1a\xfc\x98\x85\xba"
         "\x0d\x52\x6f\x77\xc4\x4b\x97\x6d\x78\x5d\xda\x06\xdf\x58\x1b\x96"
         "\x7b\x74\x6e\x09\xe1\xd5\x55\xa9\xa1\x06\x13\xea\xa5\x9c\x3d\xfd"
         "\x1f\x2f\xc2\x10\x97\xdf\x10\xbd\xc7\xee\xa6\x4b\x34\xec\xf5\x6f"
         "\xd3\xab\x74\x11\x36\xa0\x6b\xc3\xcf\x84\x7c\xba\x92\x67\x7e\x23"
         "\xeb\x5e\xb3\xb0\xb3\x5c\x3c\x4d\xd7\x77\x2c\x6b\xcd\x81\xd5\x5e"
         "\x53\x23\x78\xcd\x9b\x03\x00\x59\xc9\xec\x0e\x34\x31\x1b\x0e\x8c"
         "\x0a\x44\x6c\x01\x52\x21\xe0\x4a\xe6\xee\xe0\xb6\xe5\x39\xe0\xd3"
         "\xa9\x80\xa0\xcd\x01\x97\x2f\x3c\x10\x90\xf7\x06\x71\xb1\xd5\xc7"
         "\x5f\xdc\x1d\x0a\xb1\x23\x73\xb3\xec\x47\x6a\x5c\x77\xea\x0d\xfd"
         "\xc1\xc5\xeb\x3f\x57\x83\x77\xa0\x9c\xd1\x4c\xed\x3d\xb0\x84\x3d"
         "\x53\x55\x39\x27\x39\xf4\xd6\x31\x9e\x9a\x97\x60\xdf\x2f\xd6\x40"
         "\x00\xa9\x05\xbc\x98\x8c\x82\x00\x05\x8a\x90\x50\x2c\x61\xff\xd2"
         "\x75\x22\xbc\x98\x98\x1e\xc7\x92\x08\x3f\x27\x4d\x39\xcf\x87\xef"
         "\x0a\xdc\x3a\x5e\x3d\x3b\xf3\xac\xc1\xbb\x09\x3b\x1e\x53\x0b\xa8"
         "\x88\xe7\x52\xe1\x87\xdf\x56\x1c\xb4\xda\xa9\x88\x7f\x7d\xfe\x43"
         "\xee\x80\x3f\x0a\xe0\xd7\x62\x22\xc5\x6c\xee\x38\x4c\x1a\x96\xa9"
         "\xd9\xba\x5e\x41\xe8\x0c\x4d\x9c\xf0\x13\x30\xeb\xe6\x2d\xc2\xb2"
         "\x0f\xd8\xfb\xf3\xa3\x06\x4e\x7e\x33\xcb\x10\x1c\xe2\x78\x35\xfb"
         "\x32\x66\x61\x4f\x45\x78\x16\x09\x44\x74\x7c\xaa\x5e\x50\xfd\xa7"
         "\x00\x55\xba\x53\x5a\xfb\x97\x4b\x4e\x4a\xd8\xc8\xa9\x86\xbc\x77"
         "\x78\xba\x61\x97\x70\x2c\xcf\x5f\x00\xcf\x7c\x9a\x67\xe2\xa6\xd0"
         "\xff\x6b\x38\xcb\x17\xff\x2c\x2a\x28\x11\x14\xda\x67\x8a\xfb\x61"
         "\xdf\xe7\x0f\x8d\xad\x1c\x82\x59\x64\x0a\xa1\x99\x65\x3a\x27\x74"
         "\x46\xde\xf1\x29\xa9\x05\xf7\x68\x19\x7f\xa1\xdf\x20\x20\x20\x20"
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
.*===stickleafethenyl
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x74\x69\x63\x6b\x6c\x65\x61\x66\x65\x74"
         "\x68\x65\x6e\x79\x6c";
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
.*===saltlypropugnator
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x61\x6c\x74\x6c\x79\x70\x72\x6f\x70\x75"
         "\x67\x6e\x61\x74\x6f\x72";
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
