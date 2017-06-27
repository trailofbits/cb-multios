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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x3d\x2b\x17\xce"
         "\x2c\x72\x53\xba\x52\xd9\x5a\xc5\x4f\x01\x00\x00\x0a\x0d\x01\xd3"
         "\x05\x2b\xd4\x7b\x3a\x22\x84\x34\x11\xef\x20\x19\xbd\xc9\x26\x66"
         "\x27\x97\x75\x75\xe6\x8f\xed\x13\x13\xf5\xd1\x32\x86\x07\x65\x7c"
         "\xfe\x75\x60\x3f\x00\xf0\x7e\x32\x0b\x58\xa2\x21\xd5\x90\xe4\x35"
         "\x70\x07\x5b\x9b\x55\x0e\x5b\x61\xf5\x97\x78\xf3\xc9\x1d\xc4\x91"
         "\x19\x66\xf8\x20\x39\x6b\xb4\xb2\xfc\x37\x51\xa8\x50\x75\x27\x1e"
         "\x2b\x36\x12\x87\x57\x49\xb5\x88\x2f\xcb\x41\x09\xa3\xd1\xcc\x4c"
         "\x28\x14\x8b\x5f\x72\x69\x0a\x96\x89\x84\x74\xab\x20\x67\x72\x6c"
         "\x3a\xde\x48\xa2\x52\x3d\x0f\xb6\x96\x4b\xf3\x5a\x12\x0f\xf0\xa0"
         "\xfd\xbd\x59\xc5\x65\xab\x5f\xa9\xc6\xf6\xc8\xa0\x58\xca\x61\x18"
         "\x5e\xbb\xca\xb8\xc1\x40\x1d\x79\x46\x20\x6e\xee\x4d\xcb\x59\x9a"
         "\x60\xf7\xe3\xbe\xb4\xff\xa2\xee\x86\x0a\x25\x33\x2c\x64\x83\xd0"
         "\xce\xb2\xd7\x3b\x21\x6b\x3b\x65\xb4\x06\xb5\x3d\x9c\x1b\x69\x6c"
         "\x28\xef\x02\x05\x55\x92\x76\x98\x54\x4f\x7a\x23\x63\xd7\xb7\xe2"
         "\x12\x30\xc2\x08\xba\xca\x40\x0f\x40\xbf\xdf\xc9\xd3\x18\xdd\xc4"
         "\x79\x37\xa7\x14\x62\xfe\xc5\x6f\x2a\x7b\xcc\x9e\xd2\x9f\xc1\x9a"
         "\xe0\x1e\xbc\x62\xe2\x8d\xdd\x3d\x98\xd8\x57\xa4\x2a\xa6\x80\xcb"
         "\xec\xe6\xaa\x25\x2b\x34\xcd\xad\x1e\xd5\x36\xff\xe0\x1c\xc1\xa0"
         "\xf8\x6b\xa2\xf8\x31\x5f\x68\x03\xed\xe8\x2e\x5e\x3a\x72\x76\x8e"
         "\xf5\x89\xfe\x95\xb2\x8d\x92\x05\x60\x49\x9d\x82\x1c\xc4\x8e\x20"
         "\x4d\x15\x5f\xd3\xf2\xce\xff\x5a\x02\x3c\xae\x3d\xe3\x9f\x34\x4d"
         "\x47\x17\xd1\x0d\x9d\x0b\x22\x10\xb0\x97\xfd\x7d\xe8\x18\x06\x73"
         "\x5d\xe3\x4f\xd2\xfc\x07\x17\x95\xbe\x5a\x43\x4f\x8d\x18\xaa\x5e"
         "\x7e\xc3\x9f\xb3\x1c\xa2\x42\x9a\x7b\xc4\xce\x1f\x9a\x72\x21\x14"
         "\x19\x6e\xd8\x67\xde\x89\x6b\xf3\xd9\x69\xfc\xdc\x48\x09\x4d\x6b"
         "\x76\xc3\xfb\x23\x0d\xad\xf4\x08\x7a\x3d\xe2\x73\x73\xe0\x2f\xa4"
         "\xc6\xd4\x7f\x95\x20\xee\x81\xbf\x74\x7c\x4a\xcb\x56\xfe\x08\xac"
         "\xe5\x97\xda\x7c\xda\x52\x1c\x24\x42\xf9\x99\x4e\x28\x32\x21\x91"
         "\xe4\xfc\xbf\xb6\xab\xee\x29\x9d\xa0\x04\xf1\xa3\xc2\x56\x5e\xc0"
         "\x67\x26\xea\xef\x06\x5d\xfa\x1e\x9a\x36\x60\x1f\xef\x7d\xfd\x44"
         "\xe6\x41\xb8\x5a\xa7\x19\x27\xc1\x68\x15\xd6\xf7\xd9\x4d\x51\xc5"
         "\xc5\x87\x9a\x46\x0b\x02\x3b\xe1\x1e\x00\xec\x5d\x8c\xa4\x29\x96"
         "\x70\x89\x57\x0b\xa1\x28\xd9\x55\x5c\xaf\xcc\x9b\x7a\x5b\x34\x8b"
         "\xc5\x25\x63\x50\xec\x8f\xf0\x14\x96\xc2\xfe\x69\x5b\x0b\x2d\xff"
         "\x9e\xe0\x28\x9c\x42\xe0\xa9\xed\x58\xfd\xfb\xe5\xd0\xef\x20\x63"
         "\xeb\x31\x2b\x9d\x81\x99\x4c\x04\x06\x7a\x3c\x5b\x19\x7d\x26\x61"
         "\x0e\x21\x94\xd9\x5f\xf0\xa6\xd4\xca\x94\x93\x3d\x14\xcc\xbc\xa4"
         "\x6e\x2f\x64\x06\xf9\x21\x92\x79\x13\x1d\x65\x3f\x40\x0a\x56\x69"
         "\x9e\x0f\x0c\x9c\x18\xbd\x86\x9c\x12\x84\xc5\x6e\xaf\x1d\x40\x11"
         "\x3a\xc9\x2f\x86\xaf\xe4\x00\xaa\xf9\xf6\x65\x13\x16\xe2\xcc\x26"
         "\x51\x70\xdc\xf5\xbb\x96\x3a\xb9\xeb\x3f\xd7\x25\x73\xec\x52\xf8"
         "\x5d\x94\x03\x17\xc0\x7d\x91\x29\x66\xb3\x9f\x6f\x66\x61\x1f\xe6"
         "\x0a\x08\x02\xee\x08\x19\x36\xb7\x02\x4d\x48\x29\x35\x66\x9e\x5b"
         "\x9f\x38\x34\xa2\xc0\x47\xde\x64\x42\x5e\x3a\x08\x8b\x45\x74\x9d"
         "\x5f\xd1\x51\x7f\x90\xd1\x64\xb3\x62\xe6\xd2\x71\x45\x18\x25\x7b"
         "\x59\xfa\x2a\x6d\x0e\x3e\x7d\xd9\xb2\xb7\x47\x9c\x69\x9f\x3b\xda"
         "\x04\xb8\xd8\xf1\x21\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===steinkirkmisaffection
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x74\x65\x69\x6e\x6b\x69\x72\x6b\x6d\x69"
         "\x73\x61\x66\x66\x65\x63\x74\x69\x6f\x6e";
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
.*===adminiculatephosphosilicate
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x64\x6d\x69\x6e\x69\x63\x75\x6c\x61\x74"
         "\x65\x70\x68\x6f\x73\x70\x68\x6f\x73\x69\x6c\x69\x63\x61\x74\x65";
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
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
